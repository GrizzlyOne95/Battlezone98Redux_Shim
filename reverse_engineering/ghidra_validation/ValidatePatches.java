import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.symbol.*;
import com.google.gson.*;
import java.io.*;
import java.nio.file.*;
import java.util.*;

public class ValidatePatches extends GhidraScript {
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

    Memory mem; Listing lst; PrintWriter out;
    int ok = 0, warn = 0, fail = 0;
    Map<String,Integer> byStatus = new TreeMap<>();

    void rec(String status, String section, String name, String detail) {
        byStatus.merge(section + ":" + status, 1, Integer::sum);
        if (status.equals("OK")) ok++; else if (status.equals("WARN")) warn++; else fail++;
        out.println(status + " | " + section + " | " + name + " | " + detail);
    }

    Address A(long v) { return toAddr(v); }
    long parse(String s) { s = s.trim(); if (s.startsWith("0x") || s.startsWith("0X")) s = s.substring(2); return Long.parseUnsignedLong(s, 16); }

    byte[][] hex(String s) {
        String[] t = s.trim().split("\\s+");
        byte[] b = new byte[t.length], m = new byte[t.length];
        for (int i = 0; i < t.length; i++) {
            if (t[i].startsWith("?")) { b[i] = 0; m[i] = 0; }
            else { b[i] = (byte) Integer.parseInt(t[i], 16); m[i] = (byte) 0xFF; }
        }
        return new byte[][]{b, m};
    }

    List<Address> scan(byte[][] p, long lo, long hi, int limit) throws Exception {
        List<Address> r = new ArrayList<>();
        Address cur = A(lo), end = A(hi);
        while (cur != null && cur.compareTo(end) <= 0 && r.size() < limit) {
            Address f = mem.findBytes(cur, end, p[0], p[1], true, monitor);
            if (f == null) break;
            r.add(f);
            cur = f.add(1);
        }
        return r;
    }

    String insnInfo(Address a, int size) {
        Instruction i = lst.getInstructionContaining(a);
        if (i == null) return "no-insn(" + (lst.getDataContaining(a) != null ? "data" : "undef") + ")";
        long off = a.subtract(i.getAddress());
        boolean covers = off + size <= i.getLength();
        return (off == 0 ? "insn-start" : "in-insn+" + off) + (covers ? "" : " SPANS-INSN") + " [" + i + "]";
    }

    String funcInfo(Address a) {
        Function f = getFunctionContaining(a);
        if (f == null) return "no-func";
        return f.getEntryPoint().equals(a) ? "func-start:" + f.getName() : "in:" + f.getName();
    }

    String bytesAt(Address a, int n) throws Exception {
        byte[] b = new byte[n]; mem.getBytes(a, b);
        StringBuilder sb = new StringBuilder();
        for (byte x : b) sb.append(String.format("%02X ", x & 0xFF));
        return sb.toString().trim();
    }

    boolean matches(Address a, byte[][] p) throws Exception {
        byte[] b = new byte[p[0].length]; mem.getBytes(a, b);
        for (int i = 0; i < b.length; i++) if (((b[i] ^ p[0][i]) & p[1][i]) != 0) return false;
        return true;
    }

    public void run() throws Exception {
        mem = currentProgram.getMemory(); lst = currentProgram.getListing();
        out = new PrintWriter(new FileWriter(new File(outDir(), "validate_report.txt").getPath()));
        JsonObject d = JsonParser.parseString(new String(Files.readAllBytes(Paths.get(
            patchesPath())), "UTF-8")).getAsJsonObject();
        final long LO = 0x401000L, HI = 0x8E6FFFL;

        // ---- patches ----
        for (JsonElement e : d.getAsJsonArray("patches")) {
            JsonObject o = e.getAsJsonObject(); String n = o.get("name").getAsString();
            String plat = o.has("platforms") ? o.get("platforms").toString() : "";
            try {
                byte[][] p = hex(o.get("pattern").getAsString());
                int off = o.get("offset").getAsInt(), sz = o.get("expected_size").getAsInt();
                long fb = parse(o.get("fallback").getAsString());
                List<Address> hits = scan(p, LO, HI, 5);
                boolean uniq = o.has("require_unique") && o.get("require_unique").getAsBoolean();
                if (hits.isEmpty()) { rec(plat.contains("steam") && !plat.contains("gog") ? "WARN" : "FAIL", "patch", n, "pattern not found " + plat + " fallback=0x" + Long.toHexString(fb)); continue; }
                Address site = hits.get(0).add(off);
                String st = "OK"; String why = "";
                if (hits.size() > 1) { if (uniq) { st = "FAIL"; why += "NOT-UNIQUE(" + hits.size() + "+) "; } else { st = "WARN"; why += "multi(" + hits.size() + ") "; } }
                if (fb == 0) { why += "scan-only(no fallback) "; } else if (site.getOffset() != fb) { st = "FAIL"; why += "fallback 0x" + Long.toHexString(fb) + " != scan 0x" + site + " "; }
                String ii = insnInfo(site, sz);
                if (sz >= 5 && ii.startsWith("insn-start")) {
                    int tot = 0; Address q = site; while (tot < sz) { Instruction qi = lst.getInstructionAt(q); if (qi == null) { tot = -1; break; } tot += qi.getLength(); q = q.add(qi.getLength()); }
                    ii = "hook-site stolen=" + tot + "B(insn-aligned)" + (tot < 0 ? " BAD-DISASM" : "") + " [" + lst.getInstructionAt(site) + "]";
                    if (tot < 0) { if (st.equals("OK")) st = "WARN"; why += "site:" + ii + " "; }
                } else if (ii.contains("SPANS") || ii.startsWith("no-insn")) { if (st.equals("OK")) st = "WARN"; why += "site:" + ii + " "; }
                rec(st, "patch", n, why + "site=0x" + site + " " + ii + " " + funcInfo(site));
            } catch (Exception ex) { rec("FAIL", "patch", n, "exception " + ex); }
        }

        // ---- resolves ----
        for (JsonElement e : d.getAsJsonArray("resolves")) {
            JsonObject o = e.getAsJsonObject(); String n = o.get("name").getAsString();
            try {
                byte[][] p = hex(o.get("pattern").getAsString());
                List<Address> hits = scan(p, LO, HI, 5);
                boolean uniq = o.has("require_unique") && o.get("require_unique").getAsBoolean();
                String mode = o.has("mode") ? o.get("mode").getAsString() : "(none)";
                if (hits.isEmpty()) { rec("FAIL", "resolve", n, "pattern not found mode=" + mode); continue; }
                String st = "OK", why = "";
                boolean pinned = o.has("prefer") && o.get("prefer").getAsString().equals("fallback");
                if (hits.size() > 1) {
                    if (pinned) { why += "generic pattern, pinned to fallback (ValidatePatches2 checks the pin) "; }
                    else if (uniq) { st = "FAIL"; why += "NOT-UNIQUE(" + hits.size() + "+) "; }
                    else { st = "WARN"; why += "multi(" + hits.size() + ") "; }
                }
                if (!o.has("fallback") || !o.has("offset")) {
                    if (pinned) { rec(st, "resolve", n, why + "pinned fallback=" + o.get("fallback").getAsString() + " " + funcInfo(A(parse(o.get("fallback").getAsString())))); continue; } rec(st.equals("OK") ? "WARN" : st, "resolve", n, why + "no fallback/offset mode=" + mode + " match@0x" + hits.get(0)); continue; }
                int off = o.get("offset").getAsInt(); long fb = parse(o.get("fallback").getAsString());
                Address at = hits.get(0).add(off);
                long target = -1; String fi0 = "";
                if (mode.equals("rel32_target")) {
                    if ((mem.getByte(at) & 0xFF) != 0xE8) { st = "FAIL"; why += "anchor is not E8 CALL (" + bytesAt(at, 5) + ") "; }
                    else { int rel = mem.getInt(at.add(1)); target = (at.getOffset() + 5 + rel) & 0xFFFFFFFFL; }
                } else if (mode.equals("abs32_operand")) {
                    target = mem.getInt(at) & 0xFFFFFFFFL;
                    if (!mem.contains(A(target))) { st = "FAIL"; why += "operand 0x" + Long.toHexString(target) + " outside image "; }
                } else if (mode.equals("address")) {
                    target = at.getOffset();
                } else { why += "unknown-mode:" + mode + " "; st = "FAIL"; }
                if (target >= 0 && target != fb) { st = "FAIL"; why += "scan target 0x" + Long.toHexString(target) + " != fallback 0x" + Long.toHexString(fb) + " "; }
                String fi = funcInfo(A(fb));
                if (mode.equals("rel32_target") && !fi.startsWith("func-start")) { if (st.equals("OK")) st = "WARN"; why += "target not a function start (" + fi + ") "; }
                if (mode.equals("abs32_operand")) {
                    int refs = 0; ReferenceIterator ri = currentProgram.getReferenceManager().getReferencesTo(A(fb)); while (ri.hasNext() && refs < 3) { ri.next(); refs++; }
                    if (refs == 0) { if (st.equals("OK")) st = "WARN"; why += "operand has no xrefs "; }
                }
                if (mode.equals("address")) { String ii2 = insnInfo(at, 1); if (ii2.startsWith("no-insn") && st.equals("OK")) { st = "WARN"; why += "anchor " + ii2 + " "; } fi = fi + " " + ii2; }
                rec(st, "resolve", n, why + "mode=" + mode + " fb=0x" + Long.toHexString(fb) + " " + fi);
            } catch (Exception ex) { rec("FAIL", "resolve", n, "exception " + ex); }
        }

        // ---- globals (expected original bytes at fallback) ----
        for (JsonElement e : d.getAsJsonArray("globals")) {
            JsonObject o = e.getAsJsonObject(); String n = o.get("name").getAsString();
            try {
                long fb = parse(o.get("fallback").getAsString());
                byte[][] p = hex(o.get("expected_original").getAsString());
                Address a = A(fb);
                boolean m = matches(a, p);
                String ii = insnInfo(a, p[0].length);
                String st = m ? "OK" : "FAIL"; String why = m ? "" : "bytes " + bytesAt(a, p[0].length) + " != expected " + o.get("expected_original").getAsString() + " ";
                if (m && (ii.startsWith("no-insn"))) { st = "WARN"; why += "not code "; }
                rec(st, "global", n, why + "0x" + Long.toHexString(fb) + " " + ii + " " + funcInfo(a));
            } catch (Exception ex) { rec("FAIL", "global", n, "exception " + ex); }
        }

        // ---- engine_addresses ----
        for (JsonElement e : d.getAsJsonArray("engine_addresses")) {
            JsonObject o = e.getAsJsonObject(); String n = o.get("name").getAsString();
            try {
                long ad = parse(o.get("address").getAsString());
                String kind = o.has("kind") ? o.get("kind").getAsString() : "";
                Address a = A(ad);
                if (!mem.contains(a)) { rec("FAIL", "engine", n, "address 0x" + Long.toHexString(ad) + " not in program"); continue; }
                String st = "OK", why = "";
                if (o.has("expected")) {
                    byte[][] p = hex(o.get("expected").getAsString());
                    if (!matches(a, p)) { st = "FAIL"; why += "bytes " + bytesAt(a, p[0].length) + " != expected " + o.get("expected").getAsString() + " "; }
                }
                String fi = funcInfo(a);
                if (kind.equals("function") || kind.equals("code") || kind.equals("vtable_fn")) {
                    if (!fi.startsWith("func-start")) { if (st.equals("OK")) st = "WARN"; why += "not a function start (" + fi + ") "; }
                } else if (kind.equals("data") || kind.equals("global")) {
                    int refs = 0; ReferenceIterator ri = currentProgram.getReferenceManager().getReferencesTo(a); while (ri.hasNext() && refs < 3) { ri.next(); refs++; }
                    if (refs == 0) { if (st.equals("OK")) st = "WARN"; why += "no xrefs "; }
                }
                rec(st, "engine", n, why + "0x" + Long.toHexString(ad) + " kind=" + kind + " " + fi);
            } catch (Exception ex) { rec("FAIL", "engine", n, "exception " + ex); }
        }

        // ---- static_pointers ----
        for (JsonElement e : d.getAsJsonArray("static_pointers")) {
            JsonObject o = e.getAsJsonObject(); String n = o.get("name").getAsString();
            try {
                long ad = parse(o.get("address").getAsString()); Address a = A(ad);
                if (!mem.contains(a)) { rec("FAIL", "static", n, "not in program"); continue; }
                int refs = 0, wr = 0; ReferenceIterator ri = currentProgram.getReferenceManager().getReferencesTo(a);
                while (ri.hasNext()) { Reference r = ri.next(); refs++; if (r.getReferenceType().isWrite()) wr++; }
                rec(refs == 0 ? "WARN" : "OK", "static", n, "0x" + Long.toHexString(ad) + " xrefs=" + refs + " writes=" + wr);
            } catch (Exception ex) { rec("FAIL", "static", n, "exception " + ex); }
        }

        out.println("SUMMARY ok=" + ok + " warn=" + warn + " fail=" + fail);
        for (Map.Entry<String,Integer> en : byStatus.entrySet()) out.println("  " + en.getKey() + " = " + en.getValue());
        out.close();
        println("done ok=" + ok + " warn=" + warn + " fail=" + fail);
        for (Map.Entry<String,Integer> en : byStatus.entrySet()) println("  " + en.getKey() + " = " + en.getValue());
    }
}
