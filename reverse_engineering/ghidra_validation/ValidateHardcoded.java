import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.symbol.*;
import com.google.gson.*;
import java.io.*;
import java.nio.file.*;
import java.util.*;

public class ValidateHardcoded extends GhidraScript {
    // Paths: script args first, then environment, then repo-relative defaults
    // (this file lives in reverse_engineering/ghidra_validation/).
    String patchesPath() {
        String[] a = getScriptArgs();
        if (a != null && a.length > 0 && !a[0].isEmpty()) return a[0];
        String e = System.getenv("OPENSHIM_PATCHES_JSON");
        if (e != null && !e.isEmpty()) return e;
        return new File(getSourceFile().getFile(false).getParentFile(), "../../scripts/patches.json").getPath();
    }
    String outDir() {
        String[] a = getScriptArgs();
        if (a != null && a.length > 1 && !a[1].isEmpty()) return a[1];
        String e = System.getenv("OPENSHIM_VALIDATE_OUT");
        return (e != null && !e.isEmpty()) ? e : System.getProperty("java.io.tmpdir");
    }

    public void run() throws Exception {
        Memory mem = currentProgram.getMemory(); Listing lst = currentProgram.getListing();
        JsonObject d = JsonParser.parseString(new String(Files.readAllBytes(Paths.get(
            new File(outDir(), "hardcoded.json").getPath())), "UTF-8")).getAsJsonObject();
        PrintWriter out = new PrintWriter(new FileWriter(new File(outDir(), "hardcoded_report.txt").getPath()));
        Map<String,Integer> cnt = new TreeMap<>();
        for (Map.Entry<String, JsonElement> en : d.entrySet()) {
            long v = Long.parseUnsignedLong(en.getKey().substring(2), 16);
            Address a = toAddr(v);
            String cls, det = "";
            MemoryBlock b = mem.getBlock(a);
            if (b == null) { cls = "NOT-IN-IMAGE"; }
            else {
                Function f = getFunctionAt(a);
                Instruction i = lst.getInstructionContaining(a);
                Data dt = lst.getDataContaining(a);
                int refs = 0; ReferenceIterator ri = currentProgram.getReferenceManager().getReferencesTo(a); while (ri.hasNext() && refs < 50) { ri.next(); refs++; }
                if (f != null) { cls = "func-start"; det = f.getName(); }
                else if (i != null && i.getAddress().equals(a)) { Function c = getFunctionContaining(a); cls = c != null ? "insn-in-func" : "insn-no-func"; det = "[" + i + "]" + (c != null ? " in " + c.getName() : ""); }
                else if (i != null) { cls = "MID-INSTRUCTION"; det = "inside [" + i + "] @" + i.getAddress(); }
                else if (dt != null && b.isExecute() == false) { cls = "data"; det = "refs=" + refs + " " + dt.getDataType().getName(); }
                else if (dt != null) { cls = "exec-data"; det = "refs=" + refs + " " + dt.getDataType().getName(); }
                else { cls = b.isExecute() ? "UNDEFINED-in-code" : "undefined-data"; det = "refs=" + refs; }
                if (cls.equals("data") || cls.equals("undefined-data")) { if (refs == 0 && !b.getName().equals(".rdata")) cls += "-NOREFS"; }
            }
            cnt.merge(cls, 1, Integer::sum);
            out.println(cls + " | " + en.getKey() + " | " + det + " | " + en.getValue());
        }
        out.close();
        println("total=" + d.size());
        for (Map.Entry<String,Integer> e : cnt.entrySet()) println("  " + e.getKey() + " = " + e.getValue());
    }
}
