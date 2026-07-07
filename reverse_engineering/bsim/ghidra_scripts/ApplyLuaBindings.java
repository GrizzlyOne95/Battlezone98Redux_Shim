// Applies the recovered Lua script-binding names onto the Redux program. Unlike the BSim
// apply, these come from the engine's own registration table (name string paired with
// function pointer), so each name maps to a UNIQUE, certain function -- this is what
// disambiguates the getter/setter clusters BSim collapsed onto one address.
//
// For rows with a 1.5 counterpart it attaches the exact 1.5 prototype + provenance; for
// Redux-only rows (BZ2/Redux back-ported primitives) it tags them LuaAPI.
//
//   -process <reduxProgram> (writable)
//   -postScript ApplyLuaBindings.java <luaApplyInputTsv> <sourceProgramName> <outCsv>
//@category BSim

import java.io.*;
import java.util.*;

import ghidra.app.script.GhidraScript;
import ghidra.framework.model.*;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;

public class ApplyLuaBindings extends GhidraScript {

	@Override
	protected void run() throws Exception {
		String[] args = getScriptArgs();
		if (args.length < 3) {
			println("ERROR: <luaApplyInputTsv> <sourceProgramName> <outCsv>");
			return;
		}
		File tsv = new File(args[0]);
		Program src = openReadOnly(args[1]);
		if (src == null) {
			println("ERROR: could not open source " + args[1]);
			return;
		}
		Program redux = currentProgram;
		Map<String, Namespace> nsCache = new HashMap<>();
		int applied = 0, noFunc = 0, renameFail = 0, rows = 0;

		int tx = redux.startTransaction("apply Lua bindings");
		BufferedWriter log = new BufferedWriter(new FileWriter(args[2]));
		log.write("redux_va,applied_name,namespace,api_name,source_tag,legacy_va,status\n");
		try (BufferedReader br = new BufferedReader(new FileReader(tsv))) {
			br.readLine(); // header
			String line;
			while ((line = br.readLine()) != null) {
				if (line.isBlank()) {
					continue;
				}
				rows++;
				String[] f = line.split("\t", -1);
				long reduxVa = parseHex(f[0]);
				String name = f[1], ns = f[2], api = f[3], legacyVaStr = f[4], tag = f[5];

				Function rf = redux.getFunctionManager().getFunctionAt(addr(redux, reduxVa));
				if (rf == null) {
					noFunc++;
					writeRow(log, reduxVa, name, ns, api, tag, legacyVaStr, "no_redux_func");
					continue;
				}

				String proto = "";
				if (!legacyVaStr.isEmpty()) {
					Function sf = src.getFunctionManager()
						.getFunctionAt(addr(src, parseHex(legacyVaStr)));
					if (sf != null) {
						proto = sf.getSignature().getPrototypeString(true);
					}
				}
				String comment = "LuaAPI  " + api + "   (BZ mission-script primitive)"
					+ "\n  recovered from engine luaL_reg registration table [" + tag + "]"
					+ (legacyVaStr.isEmpty()
						? "\n  no 1.5 counterpart (BZ2/Redux back-port)"
						: "\n  1.5 impl " + (ns.equals("LuaAPI") ? "" : ns + "::") + name
							+ " @ VA " + legacyVaStr)
					+ (proto.isEmpty() ? "" : "\n  1.5 proto: " + proto);
				setPlateComment(rf.getEntryPoint(), comment);

				if (tryRename(redux, rf, name, ns, nsCache)) {
					applied++;
					writeRow(log, reduxVa, name, ns, api, tag, legacyVaStr, "applied");
				}
				else {
					renameFail++;
					writeRow(log, reduxVa, name, ns, api, tag, legacyVaStr, "rename_failed");
				}
			}
		}
		finally {
			redux.endTransaction(tx, true);
			log.close();
			src.release(this);
		}
		println("input rows: " + rows);
		println("APPLIED (renamed): " + applied);
		println("no redux function: " + noFunc);
		println("rename failures: " + renameFail);
		println("wrote " + args[2]);
	}

	private boolean tryRename(Program p, Function fn, String name, String ns,
			Map<String, Namespace> cache) {
		try {
			fn.setParentNamespace(resolveNamespace(p, ns, cache));
			fn.setName(name, SourceType.IMPORTED);
			return true;
		}
		catch (Exception e) {
			try {
				String safe = name.replaceAll("[^A-Za-z0-9_]", "_");
				if (safe.isEmpty() || Character.isDigit(safe.charAt(0))) {
					safe = "f_" + safe;
				}
				fn.setName(safe, SourceType.IMPORTED);
				return true;
			}
			catch (Exception e2) {
				return false;
			}
		}
	}

	private Namespace resolveNamespace(Program p, String ns, Map<String, Namespace> cache)
			throws Exception {
		if (ns == null || ns.isEmpty() || ns.equalsIgnoreCase("Global")) {
			return p.getGlobalNamespace();
		}
		Namespace cached = cache.get(ns);
		if (cached != null) {
			return cached;
		}
		SymbolTable st = p.getSymbolTable();
		Namespace existing = st.getNamespace(ns, p.getGlobalNamespace());
		if (existing == null) {
			existing = st.createClass(p.getGlobalNamespace(), ns, SourceType.IMPORTED);
		}
		cache.put(ns, existing);
		return existing;
	}

	private Program openReadOnly(String name) throws Exception {
		ProjectData pd = state.getProject().getProjectData();
		DomainFile df = pd.getFile("/" + name);
		if (df == null) {
			for (DomainFile d : pd.getRootFolder().getFiles()) {
				if (d.getName().equals(name)) {
					df = d;
					break;
				}
			}
		}
		return df == null ? null
			: (Program) df.getReadOnlyDomainObject(this, DomainFile.DEFAULT_VERSION, monitor);
	}

	private Address addr(Program p, long off) {
		return p.getAddressFactory().getDefaultAddressSpace().getAddress(off);
	}

	private long parseHex(String s) {
		s = s.trim();
		if (s.startsWith("0x") || s.startsWith("0X")) {
			s = s.substring(2);
		}
		return Long.parseLong(s, 16);
	}

	private void writeRow(BufferedWriter w, long rva, String name, String ns, String api,
			String tag, String legacyVa, String status) throws IOException {
		w.write("0x" + Long.toHexString(rva) + "," + name + "," + ns + "," + api + ","
			+ tag + "," + legacyVa + "," + status + "\n");
	}
}
