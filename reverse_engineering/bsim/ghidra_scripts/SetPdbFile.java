// Ghidra pre-analysis script: force the PDB analyzer to use the matching local PDB.

import ghidra.app.plugin.core.analysis.PdbUniversalAnalyzer;
import ghidra.app.script.GhidraScript;

import java.io.File;

public class SetPdbFile extends GhidraScript {
    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 1) {
            throw new IllegalArgumentException("Usage: SetPdbFile.java <pdb-path>");
        }

        File pdb = new File(args[0]);
        if (!pdb.isFile()) {
            throw new IllegalArgumentException("PDB does not exist: " + pdb.getAbsolutePath());
        }

        PdbUniversalAnalyzer.setPdbFileOption(currentProgram, pdb);
        println("Configured PDB file: " + pdb.getAbsolutePath());
    }
}
