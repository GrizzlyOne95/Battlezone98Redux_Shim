// Recovers the Battlezone Lua script-binding entry points by reading the engine's
// luaL_reg-style registration table(s): a run of { const char *name; lua_CFunction func; }
// structs in .rdata. For each documented mission-script API name we (1) find its C-string
// address, (2) find the table slot that points at that string, (3) read the adjacent
// function pointer -> the exact C function that implements that script primitive.
//
// This is precise where BSim is not: tiny getters/setters (GetCurAmmo, GetOwner, ...) all
// compile to near-identical code and collide under BSim, but the registration table pairs
// each name string with its unique function pointer, so we recover them with certainty.
//
// Run read-only on either program:
//   -process <program> -noanalysis -scriptPath <dir>
//   -postScript LuaBindingTableExtractor.java <apiNamesTxt> <outCsv>
// Output CSV: api_name,string_addr,table_entry,func_ptr,func_rva,func_name,func_defined
//@category BSim

import java.io.*;
import java.util.*;

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.program.model.mem.*;

public class LuaBindingTableExtractor extends GhidraScript {

	@Override
	protected void run() throws Exception {
		String[] args = getScriptArgs();
		if (args.length < 2) {
			println("ERROR: <apiNamesTxt> <outCsv>");
			return;
		}
		List<String> names = new ArrayList<>();
		Set<String> nameSet = new HashSet<>();
		try (BufferedReader br = new BufferedReader(new FileReader(args[0]))) {
			String l;
			while ((l = br.readLine()) != null) {
				l = l.trim();
				if (!l.isEmpty() && nameSet.add(l)) {
					names.add(l);
				}
			}
		}
		String outCsv = args[1];

		Memory mem = currentProgram.getMemory();
		long imageBase = currentProgram.getImageBase().getOffset();

		// 1) Map every wanted name -> its defined-string address(es).
		Map<String, List<Address>> strAddrs = new HashMap<>();
		int definedHits = 0;
		DataIterator dit = currentProgram.getListing().getDefinedData(true);
		while (dit.hasNext()) {
			Data d = dit.next();
			Object v = d.getValue();
			if (v instanceof String) {
				String s = (String) v;
				if (nameSet.contains(s)) {
					strAddrs.computeIfAbsent(s, k -> new ArrayList<>()).add(d.getAddress());
					definedHits++;
				}
			}
		}
		// Fallback: raw byte search (null-terminated) for names with no defined string.
		int rawHits = 0;
		for (String n : names) {
			if (strAddrs.containsKey(n)) {
				continue;
			}
			byte[] pat = (n + "\0").getBytes("US-ASCII");
			Address found = mem.findBytes(null, pat, null, true, monitor);
			while (found != null) {
				strAddrs.computeIfAbsent(n, k -> new ArrayList<>()).add(found);
				rawHits++;
				Address next = found.add(1);
				found = mem.findBytes(next, pat, null, true, monitor);
			}
		}
		println("names: " + names.size() + "  defined-string hits: " + definedHits
			+ "  raw-search hits: " + rawHits + "  names located: " + strAddrs.size());

		// Reverse index: string address offset -> name (for the pointer scan).
		Map<Long, String> addrToName = new HashMap<>();
		for (Map.Entry<String, List<Address>> e : strAddrs.entrySet()) {
			for (Address a : e.getValue()) {
				addrToName.put(a.getOffset(), e.getKey());
			}
		}

		// 2) Scan initialized, non-executable memory for 4-byte pointers equal to a name
		//    string address; the following dword is the candidate lua_CFunction pointer.
		FunctionManager fm = currentProgram.getFunctionManager();
		// name -> best (entryAddr, funcPtr) chosen by "func pointer resolves to a function".
		Map<String, Object[]> best = new LinkedHashMap<>();
		int scannedSlots = 0, tableSlots = 0;
		for (MemoryBlock b : mem.getBlocks()) {
			if (!b.isInitialized() || b.isExecute()) {
				continue;
			}
			long start = b.getStart().getOffset();
			long end = b.getEnd().getOffset();
			// align to 4
			long a = (start + 3) & ~3L;
			for (; a + 7 <= end; a += 4) {
				scannedSlots++;
				Address ea = toAddr(a);
				int ptr;
				try {
					ptr = mem.getInt(ea);
				}
				catch (MemoryAccessException ex) {
					continue;
				}
				long pv = Integer.toUnsignedLong(ptr);
				String nm = addrToName.get(pv);
				if (nm == null) {
					continue;
				}
				// candidate registration slot: read the adjacent function pointer
				int fptr;
				try {
					fptr = mem.getInt(ea.add(4));
				}
				catch (MemoryAccessException ex) {
					continue;
				}
				long fv = Integer.toUnsignedLong(fptr);
				Address fa;
				try {
					fa = toAddr(fv);
				}
				catch (Exception ex) {
					continue;
				}
				MemoryBlock fb = mem.getBlock(fa);
				boolean inCode = fb != null && fb.isExecute();
				if (!inCode) {
					continue; // adjacent value isn't a code pointer -> not a reg slot
				}
				tableSlots++;
				Function fn = fm.getFunctionAt(fa);
				boolean defined = fn != null;
				// prefer a slot whose func pointer is an actual function entry
				Object[] prev = best.get(nm);
				if (prev == null || (defined && !((Boolean) prev[3]))) {
					best.put(nm, new Object[] { ea, fa, fn, defined });
				}
			}
		}
		println("scanned dword slots: " + scannedSlots + "  reg-table slots found: " + tableSlots
			+ "  distinct API names bound: " + best.size());

		// 3) Emit.
		int resolvedFuncs = 0;
		try (BufferedWriter w = new BufferedWriter(new FileWriter(outCsv))) {
			w.write("api_name,string_addr,table_entry,func_ptr,func_rva,func_name,func_defined\n");
			for (String n : names) {
				Object[] r = best.get(n);
				if (r == null) {
					w.write(n + ",,,,,,MISSING\n");
					continue;
				}
				Address ea = (Address) r[0];
				Address fa = (Address) r[1];
				Function fn = (Function) r[2];
				boolean defined = (Boolean) r[3];
				if (defined) {
					resolvedFuncs++;
				}
				long rva = fa.getOffset() - imageBase;
				String fname = fn != null ? fn.getName(true) : "";
				w.write(n + ",0x" + hex(firstStr(strAddrs, n)) + ",0x" + hex(ea.getOffset())
					+ ",0x" + hex(fa.getOffset()) + ",0x" + Long.toHexString(rva)
					+ "," + fname + "," + defined + "\n");
			}
		}
		println("func pointers landing on a defined function: " + resolvedFuncs);
		println("wrote " + outCsv);
	}

	private long firstStr(Map<String, List<Address>> m, String n) {
		List<Address> l = m.get(n);
		return (l == null || l.isEmpty()) ? 0 : l.get(0).getOffset();
	}

	private String hex(long v) {
		return Long.toHexString(v);
	}
}
