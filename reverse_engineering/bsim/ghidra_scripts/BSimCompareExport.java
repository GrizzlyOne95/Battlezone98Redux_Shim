// Headless BSim two-program comparison exporter.
//
// Compares every "named" function in the CURRENT program (source, e.g. legacy bzone.exe
// with bzint.pdb symbols applied) against every function in a TARGET program that lives
// in the SAME Ghidra project (e.g. the unpacked Battlezone 98 Redux exe), using the same
// in-memory BSim algorithm as Ghidra's stock LocalBSimQueryScript (GenSignatures +
// LSHVectorFactory, medium_nosize template). Instead of a GUI table it writes CSV so the
// result can be joined into the legacy->redux symbol-map pipeline.
//
// Run headless, e.g.:
//   analyzeHeadless <projDir> <projName> -process bzone.exe \
//       -scriptPath <this_dir> \
//       -postScript BSimCompareExport.java <targetProgramName> <outCsvPath> [maxMatches] [minSim]
//
// Args:
//   [0] targetProgramName  domain-file name of the target program in the current project
//   [1] outCsvPath         absolute path of the CSV to write
//   [2] maxMatches         (optional) top-N matches kept per source function (default 5)
//   [3] minSim             (optional) minimum similarity to emit (default 0.50)
//
//@category BSim

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.util.*;

import generic.lsh.vector.*;
import ghidra.app.script.GhidraScript;
import ghidra.features.bsim.query.FunctionDatabase;
import ghidra.features.bsim.query.client.Configuration;
import ghidra.features.bsim.query.description.FunctionDescription;
import ghidra.features.bsim.query.GenSignatures;
import ghidra.framework.model.DomainFile;
import ghidra.framework.model.ProjectData;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.SourceType;

public class BSimCompareExport extends GhidraScript {

	// Signature settings must match the template used everywhere else in the pipeline.
	private static final String TEMPLATE_NAME = "medium_nosize";
	// Functions whose self-significance is below this are too small/common to trust.
	private static final double SELF_SIGNIFICANCE_BOUND = 15.0;

	@Override
	protected void run() throws Exception {
		String[] args = getScriptArgs();
		if (args.length < 2) {
			println("ERROR: need <targetProgramName> <outCsvPath> [maxMatches] [minSim]");
			return;
		}
		String targetName = args[0];
		String outPath = args[1];
		int maxMatches = args.length >= 3 ? Integer.parseInt(args[2]) : 5;
		double minSim = args.length >= 4 ? Double.parseDouble(args[3]) : 0.50;

		if (currentProgram == null) {
			println("ERROR: no current (source) program; run with -process <sourceProgram>");
			return;
		}
		Program source = currentProgram;

		Program target = openTargetFromProject(targetName);
		if (target == null) {
			println("ERROR: target program '" + targetName + "' not found in project");
			return;
		}

		try {
			LSHVectorFactory vf = getVectorFactory();

			// Source signatures: only "named" functions worth transferring a name for.
			List<Function> srcFuncs = collectNamedFunctions(source);
			println("Source named functions to query: " + srcFuncs.size());
			GenSignatures srcSigs =
				generateSignatures(source, srcFuncs.iterator(), srcFuncs.size(), vf);

			// Target signatures: every real function.
			FunctionManager tfm = target.getFunctionManager();
			GenSignatures tgtSigs = generateSignatures(target,
				tfm.getFunctions(true), tfm.getFunctionCount(), vf);

			long srcImage = source.getImageBase().getOffset();
			long tgtImage = target.getImageBase().getOffset();

			// Pre-materialize target descriptors (with a usable self-significance) once.
			List<FunctionDescription> targets = new ArrayList<>();
			Iterator<FunctionDescription> ti = tgtSigs.getDescriptionManager().listAllFunctions();
			while (ti.hasNext()) {
				FunctionDescription td = ti.next();
				LSHVector tv = td.getSignatureRecord().getLSHVector();
				if (vf.getSelfSignificance(tv) <= SELF_SIGNIFICANCE_BOUND) {
					continue;
				}
				targets.add(td);
			}
			println("Target functions with usable signatures: " + targets.size());

			int written = 0;
			try (BufferedWriter w = new BufferedWriter(new FileWriter(outPath))) {
				w.write("legacy_va,legacy_name,legacy_namespace,target_rva,target_va," +
					"target_name,similarity,significance\n");

				VectorCompare vc = new VectorCompare();
				Iterator<FunctionDescription> si =
					srcSigs.getDescriptionManager().listAllFunctions();
				while (si.hasNext()) {
					monitor.checkCancelled();
					FunctionDescription sd = si.next();
					LSHVector sv = sd.getSignatureRecord().getLSHVector();
					if (vf.getSelfSignificance(sv) <= SELF_SIGNIFICANCE_BOUND) {
						continue;
					}
					Function sf = funcAt(source, sd.getAddress());
					if (sf == null) {
						continue;
					}

					// Rank this source function's matches, keep the best maxMatches.
					PriorityQueue<Match> best =
						new PriorityQueue<>(Comparator.comparingDouble(m -> m.significance));
					for (FunctionDescription td : targets) {
						LSHVector tv = td.getSignatureRecord().getLSHVector();
						double sim = sv.compare(tv, vc);
						if (sim < minSim) {
							continue;
						}
						double sig = vf.calculateSignificance(vc);
						best.add(new Match(td, sim, sig));
						if (best.size() > maxMatches) {
							best.poll(); // drop lowest-significance
						}
					}
					if (best.isEmpty()) {
						continue;
					}
					List<Match> ordered = new ArrayList<>(best);
					ordered.sort((a, b) -> Double.compare(b.significance, a.significance));

					String legName = sf.getName(false);
					String legNs = sf.getParentNamespace() != null
						? sf.getParentNamespace().getName(true) : "";
					long legVa = sd.getAddress();
					for (Match m : ordered) {
						long tva = m.desc.getAddress();
						Function tf = funcAt(target, tva);
						String tname = tf != null ? tf.getName(false) : "";
						w.write(String.format("0x%x,%s,%s,0x%x,0x%x,%s,%.4f,%.2f%n",
							legVa, csv(legName), csv(legNs),
							(tva - tgtImage), tva, csv(tname),
							m.similarity, m.significance));
						written++;
					}
				}
			}
			println("Wrote " + written + " match rows to " + outPath);
			println("SRC_IMAGE_BASE=0x" + Long.toHexString(srcImage));
			println("TGT_IMAGE_BASE=0x" + Long.toHexString(tgtImage));
		}
		finally {
			target.release(this);
		}
	}

	private static class Match {
		final FunctionDescription desc;
		final double similarity;
		final double significance;

		Match(FunctionDescription d, double sim, double sig) {
			desc = d;
			similarity = sim;
			significance = sig;
		}
	}

	// Only functions with a real, user/import symbol name (skip FUN_, thunks, externals).
	private List<Function> collectNamedFunctions(Program p) {
		List<Function> out = new ArrayList<>();
		for (Function f : p.getFunctionManager().getFunctions(true)) {
			if (f.isThunk() || f.isExternal()) {
				continue;
			}
			if (f.getSymbol() != null && f.getSymbol().getSource() == SourceType.DEFAULT) {
				continue; // auto FUN_ name, nothing to transfer
			}
			String n = f.getName(false);
			if (n == null || n.startsWith("FUN_") || n.startsWith("thunk_")) {
				continue;
			}
			out.add(f);
		}
		return out;
	}

	private Function funcAt(Program p, long offset) {
		Address a = p.getAddressFactory().getDefaultAddressSpace().getAddress(offset);
		return p.getFunctionManager().getFunctionAt(a);
	}

	private Program openTargetFromProject(String name) throws Exception {
		ProjectData pd = state.getProject().getProjectData();
		DomainFile df = pd.getFile("/" + name);
		if (df == null) {
			// fall back: search all folders for a matching file name
			df = findByName(pd, name);
		}
		if (df == null) {
			return null;
		}
		return (Program) df.getDomainObject(this, false, false, monitor);
	}

	private DomainFile findByName(ProjectData pd, String name) {
		for (DomainFile df : pd.getRootFolder().getFiles()) {
			if (df.getName().equals(name)) {
				return df;
			}
		}
		return null;
	}

	private LSHVectorFactory getVectorFactory() throws Exception {
		LSHVectorFactory vf = FunctionDatabase.generateLSHVectorFactory();
		Configuration cfg = FunctionDatabase.loadConfigurationTemplate(TEMPLATE_NAME);
		vf.set(cfg.weightfactory, cfg.idflookup, cfg.info.settings);
		return vf;
	}

	private GenSignatures generateSignatures(Program p, Iterator<Function> funcs, int count,
			LSHVectorFactory vf) throws Exception {
		GenSignatures g = new GenSignatures(false);
		g.setVectorFactory(vf);
		g.openProgram(p, null, null, null, null, null);
		g.scanFunctions(funcs, count, monitor);
		return g;
	}

	private static String csv(String s) {
		if (s == null) {
			return "";
		}
		if (s.indexOf(',') >= 0 || s.indexOf('"') >= 0) {
			return '"' + s.replace("\"", "\"\"") + '"';
		}
		return s;
	}
}
