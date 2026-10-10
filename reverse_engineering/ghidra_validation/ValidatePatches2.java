import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.symbol.*;
import com.google.gson.*;
import java.io.*;
import java.nio.file.*;
import java.util.*;

public class ValidatePatches2 extends GhidraScript {
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

    Memory mem; Listing lst;
    Address A(long v) { return toAddr(v); }
    long parse(String s) { s = s.trim(); if (s.startsWith("0x")) s = s.substring(2); return Long.parseUnsignedLong(s, 16); }
    byte[][] hex(String s) {
        String[] t = s.trim().split("\\s+"); byte[] b = new byte[t.length], m = new byte[t.length];
        for (int i = 0; i < t.length; i++) { if (t[i].startsWith("?")) { b[i] = 0; m[i] = 0; } else { b[i] = (byte) Integer.parseInt(t[i], 16); m[i] = (byte) 0xFF; } }
        return new byte[][]{b, m};
    }
    List<Address> scan(byte[][] p, long lo, long hi, int limit) throws Exception {
        List<Address> r = new ArrayList<>(); Address cur = A(lo), end = A(hi);
        while (r.size() < limit) { Address f = mem.findBytes(cur, end, p[0], p[1], true, monitor); if (f == null) break; r.add(f); cur = f.add(1); }
        return r;
    }
    boolean matches(Address a, byte[][] p) throws Exception {
        byte[] b = new byte[p[0].length]; mem.getBytes(a, b);
        for (int i = 0; i < b.length; i++) if (((b[i] ^ p[0][i]) & p[1][i]) != 0) return false;
        return true;
    }
    String fn(Address a) { Function f = getFunctionContaining(a); return f == null ? "no-func" : (f.getEntryPoint().equals(a) ? "func-start:" : "in:") + f.getName(); }

    public void run() throws Exception {
        mem = currentProgram.getMemory(); lst = currentProgram.getListing();
        JsonObject d = JsonParser.parseString(new String(Files.readAllBytes(Paths.get(
            patchesPath())), "UTF-8")).getAsJsonObject();
        final long LO = 0x401000L, HI = 0x8E6FFFL;
        int ok = 0, bad = 0;

        println("== A: prefer=fallback resolves ==");
        for (JsonElement e : d.getAsJsonArray("resolves")) {
            JsonObject o = e.getAsJsonObject();
            if (!o.has("prefer") || !o.get("prefer").getAsString().equals("fallback")) continue;
            Address fb = A(parse(o.get("fallback").getAsString()));
            boolean pm = matches(fb, hex(o.get("pattern").getAsString()));
            String f = fn(fb); boolean good = pm && f.startsWith("func-start");
            if (good) ok++; else bad++;
            println((good ? "OK   " : "BAD  ") + o.get("name").getAsString() + " 0x" + fb + " prologue-match=" + pm + " " + f);
        }

        println("== B: UnitVo queue call sites ==");
        Map<String, Long> tgt = new LinkedHashMap<>();
        for (JsonElement e : d.getAsJsonArray("resolves")) {
            JsonObject o = e.getAsJsonObject(); String n = o.get("name").getAsString();
            if (!n.startsWith("UnitVo::")) continue;
            List<Address> h = scan(hex(o.get("pattern").getAsString()), LO, HI, 4);
            int off = o.has("offset") ? o.get("offset").getAsInt() : 0;
            String line = n + " matches=" + h.size();
            if (h.size() >= 1) {
                Address at = h.get(0).add(off);
                boolean call = (mem.getByte(at) & 0xFF) == 0xE8;
                line += " anchor=0x" + at + (call ? " E8" : " NOT-E8");
                if (call) { long t = (at.getOffset() + 5 + mem.getInt(at.add(1))) & 0xFFFFFFFFL; tgt.put(n, t); line += " target=0x" + Long.toHexString(t) + " " + fn(A(t)); }
            }
            boolean good = h.size() == 1; if (good) ok++; else bad++;
            println((good ? "OK   " : "BAD  ") + line);
        }
        if (new HashSet<>(tgt.values()).size() > 1) { bad++; println("BAD  UnitVo call-site targets differ: " + tgt); } else if (!tgt.isEmpty()) { ok++; println("OK   UnitVo call-site targets agree"); }

        println("== C: VTable globals ==");
        for (JsonElement e : d.getAsJsonArray("globals")) {
            JsonObject o = e.getAsJsonObject(); String n = o.get("name").getAsString();
            if (!n.contains("VTable")) continue;
            Address slot = A(parse(o.get("fallback").getAsString()));
            long p = mem.getInt(slot) & 0xFFFFFFFFL; Address pa = A(p);
            boolean exec = mem.contains(pa) && mem.getBlock(pa) != null && mem.getBlock(pa).isExecute();
            String f = fn(pa); boolean good = exec && f.startsWith("func-start");
            Symbol ps = currentProgram.getSymbolTable().getPrimarySymbol(slot);
            if (good) ok++; else bad++;
            println((good ? "OK   " : "BAD  ") + n + " slot=0x" + slot + " -> 0x" + Long.toHexString(p) + " " + f + " slotSym=" + (ps == null ? "-" : ps.getName()));
        }

        println("== D: code-address static pointers ==");
        for (JsonElement e : d.getAsJsonArray("static_pointers")) {
            JsonObject o = e.getAsJsonObject(); String n = o.get("name").getAsString();
            if (!(n.startsWith("RetAddr_") || n.startsWith("LensFlare"))) continue;
            Address a = A(parse(o.get("address").getAsString()));
            Instruction i = lst.getInstructionAt(a); Instruction pv = i == null ? null : i.getPrevious();
            boolean good = i != null; String det = "0x" + a + " " + (i == null ? "NO-INSN " + (lst.getDataContaining(a) != null ? "(data)" : "(undef)") : "[" + i + "]") + " " + fn(a);
            if (n.startsWith("RetAddr_")) { boolean afterCall = pv != null && pv.getFlowType().isCall() && pv.getFallThrough() != null && pv.getFallThrough().equals(a); good = good && afterCall; det += " prev=[" + pv + "]" + (afterCall ? " (after CALL)" : " NOT-AFTER-CALL"); }
            if (good) ok++; else bad++;
            println((good ? "OK   " : "BAD  ") + n + " " + det);
        }
        println("TOTAL ok=" + ok + " bad=" + bad);
    }
}
