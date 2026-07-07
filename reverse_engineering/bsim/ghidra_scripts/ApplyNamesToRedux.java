// Applies high-confidence 1.5 names onto the Redux program and attaches each function's
// original 1.5 prototype + BSim provenance as a plate comment. Run headless with
// -process <reduxProgram> (writable). The 1.5 source program is opened read-only from the
// same project for signature lookup.
//
//   -postScript ApplyNamesToRedux.java <applyInputTsv> <sourceProgramName> <outNamedCsv>
//@category BSim

import java.io.*;
import java.util.*;

import ghidra.app.script.GhidraScript;
import ghidra.framework.model.*;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;

public class ApplyNamesToRedux extends GhidraScript {

	@Override
	protected void run() throws Exception {
		String[] args = getScriptArgs();
		if (args.length < 3) {
			println("ERROR: <applyInputTsv> <sourceProgramName> <outNamedCsv>");
			return;
		}
		File tsv = new File(args[0]);
		String srcName = args[1];
		String outCsv = args[2];

		Program redux = currentProgram;
		Program src = openReadOnly(srcName);
		if (src == null) {
			println("ERROR: could not open source program " + srcName);
			return;
		}

		int applied = 0, commentOnly = 0, noReduxFunc = 0, renameFail = 0, lines = 0;
		Set<Long> named = new HashSet<>();
		Map<String, Namespace> nsCache = new HashMap<>();

		int txId = redux.startTransaction("apply BSim names");
		BufferedWriter log = new BufferedWriter(new FileWriter(outCsv));
		log.write("redux_va,applied_name,namespace,combined_confidence,similarity,significance,legacy_va,status\n");
		try (BufferedReader br = new BufferedReader(new FileReader(tsv))) {
			String header = br.readLine(); // skip
			String line;
			while ((line = br.readLine()) != null) {
				if (line.isBlank()) {
					continue;
				}
				lines++;
				String[] f = line.split("\t", -1);
				// legacy_entry_va, bsim_redux_va, legacy_name, legacy_namespace, conf, sim, sig, agree
				long legacyVa = parseHex(f[0]);
				long reduxVa = parseHex(f[1]);
				String name = f[2];
				String ns = f[3];
				String conf = f[4], sim = f[5], sig = f[6], agree = f[7];

				Function rf = redux.getFunctionManager()
					.getFunctionAt(addr(redux, reduxVa));
				if (rf == null) {
					noReduxFunc++;
					writeRow(log, reduxVa, name, ns, conf, sim, sig, legacyVa, "no_redux_func");
					continue;
				}

				// Build provenance comment, including the exact 1.5 prototype.
				String proto = "";
				Function sf = src.getFunctionManager().getFunctionAt(addr(src, legacyVa));
				if (sf != null) {
					proto = sf.getSignature().getPrototypeString(true);
				}
				String comment = "BSim<-BZ1.5  " + (ns.isEmpty() ? "" : ns + "::") + name +
					"\n  similarity=" + sim + " significance=" + sig +
					" agreement=" + agree + " confidence=" + conf +
					"\n  1.5 VA=0x" + Long.toHexString(legacyVa) +
					(proto.isEmpty() ? "" : "\n  1.5 proto: " + proto);
				setPlateComment(rf.getEntryPoint(), comment);

				if (named.contains(reduxVa)) {
					// already renamed by a higher-confidence row; keep comment only
					commentOnly++;
					writeRow(log, reduxVa, name, ns, conf, sim, sig, legacyVa, "comment_only_dup");
					continue;
				}

				boolean ok = tryRename(redux, rf, name, ns, nsCache);
				if (ok) {
					applied++;
					named.add(reduxVa);
					writeRow(log, reduxVa, name, ns, conf, sim, sig, legacyVa, "applied");
				}
				else {
					renameFail++;
					writeRow(log, reduxVa, name, ns, conf, sim, sig, legacyVa, "rename_failed");
				}
			}
		}
		finally {
			redux.endTransaction(txId, true);
			log.close();
			src.release(this);
		}

		println("input rows: " + lines);
		println("APPLIED (renamed): " + applied);
		println("comment-only (dup redux target): " + commentOnly);
		println("no redux function at RVA: " + noReduxFunc);
		println("rename failures: " + renameFail);
		println("wrote " + outCsv);
	}

	private boolean tryRename(Program p, Function fn, String name, String ns,
			Map<String, Namespace> cache) {
		try {
			Namespace parent = resolveNamespace(p, ns, cache);
			fn.setParentNamespace(parent);
			fn.setName(name, SourceType.IMPORTED);
			return true;
		}
		catch (Exception e) {
			// retry with a sanitized identifier
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
		if (df == null) {
			return null;
		}
		return (Program) df.getReadOnlyDomainObject(this, DomainFile.DEFAULT_VERSION, monitor);
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

	private void writeRow(BufferedWriter w, long rva, String name, String ns, String conf,
			String sim, String sig, long legacyVa, String status) throws IOException {
		w.write("0x" + Long.toHexString(rva) + "," + name + "," + ns + "," + conf + "," +
			sim + "," + sig + ",0x" + Long.toHexString(legacyVa) + "," + status + "\n");
	}
}
