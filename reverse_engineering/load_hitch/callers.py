import sys, os, glob, collections, datetime, json, re
sys.path.insert(0, r"C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering")
import analyze_cpu_samples as acs
run, b, e, leafrx, inclrx = sys.argv[1:6]
cap = acs.read_capture(glob.glob(os.path.join(run, "openshim_cpu_samples_*.bin"))[0])
sym = acs.Symbolizer(cap, None, "battlezone98redux.exe", False)
main = collections.Counter(s[0] for s in cap.samples).most_common(1)[0][0]
B, E = datetime.datetime.fromisoformat(b), datetime.datetime.fromisoformat(e)
paths = collections.Counter(); n = 0
for t, q, fl, fr in cap.samples:
    if t != main or not (B <= cap.local_time(q) <= E): continue
    names = [sym.symbol(a) for a in fr]
    if not re.search(leafrx, names[0]) or not re.search(inclrx, "\n".join(names)): continue
    n += 1
    keep = [(x if x.startswith("battlezone") else re.sub(r"\+0x[0-9a-f]+$", "", x)) for x in names[1:16]
            if not x.startswith(("ntdll", "MSVCR", "MSVCP", "ucrt"))][:9]
    paths[" <- ".join(keep)] += 1
print(n, "samples")
for p, c in paths.most_common(12): print(c, p[:400])
