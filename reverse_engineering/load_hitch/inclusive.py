import sys, os, glob, collections, datetime, json, re
sys.path.insert(0, r"C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering")
import analyze_cpu_samples as acs
run, key = sys.argv[1], sys.argv[2]
pats = sys.argv[3:]
d = json.load(open(os.path.join(run, "attribution.json")))
cap = acs.read_capture(glob.glob(os.path.join(run, "openshim_cpu_samples_*.bin"))[0])
sym = acs.Symbolizer(cap, None, "battlezone98redux.exe", False)
main = d["main_tid"]
day = datetime.datetime.fromisoformat(d["startup_to_sim"]["begin"]).date()
def p(s):
    return datetime.datetime.fromisoformat(s) if "-" in s else datetime.datetime.combine(day, datetime.time.fromisoformat(s))
B, E = p(d[key]["begin"]), p(d[key]["end"])
cnt = collections.Counter(); n = 0
for t, q, fl, fr in cap.samples:
    if t != main or not (B <= cap.local_time(q) <= E): continue
    n += 1
    s = "\n".join(sym.symbol(a) for a in fr)
    for pat in pats:
        if re.search(pat, s): cnt[pat] += 1
print(run, key, "samples", n)
for pat in pats: print("  %-60s %6d ms  %5.1f%%" % (pat, cnt[pat], 100.0 * cnt[pat] / max(n, 1)))
