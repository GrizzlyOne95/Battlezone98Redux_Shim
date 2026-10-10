"""List engine-range address literals in the C++ sources that patches.json does
not mention, as input for ValidateHardcoded.java.

Usage: python scan_hardcoded.py [out_dir]
Writes hardcoded.json to out_dir (default: the system temp dir), the file
ValidateHardcoded.java reads. Keep both scripts' out_dir the same.
"""
import collections, glob, json, os, re, sys, tempfile

repo = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
out_dir = sys.argv[1] if len(sys.argv) > 1 else tempfile.gettempdir()
os.chdir(repo)

known = set(re.findall(r'0x([0-9a-f]{8})', open('scripts/patches.json', encoding='utf-8').read().lower()))
pat = re.compile(r'\b0[xX]0?([0-9a-fA-F]{6,7})\b')
hits = collections.defaultdict(set)
for f in (glob.glob('src/**/*.cpp', recursive=True) + glob.glob('src/**/*.h', recursive=True)
          + glob.glob('include/**/*.h', recursive=True)):
    text = open(f, encoding='utf-8', errors='ignore').read()
    for m in pat.finditer(text):
        v = int(m.group(1), 16)
        if 0x401000 <= v <= 0x2D10000:      # GOG Redux image range
            hits[v].add(f.replace(os.sep, '/'))

unmapped = {v: fs for v, fs in hits.items() if '%08x' % v not in known}
path = os.path.join(out_dir, 'hardcoded.json')
json.dump({hex(v): sorted(fs) for v, fs in unmapped.items()}, open(path, 'w'))
print(len(hits), 'engine-range literals,', len(unmapped), 'not in patches.json ->', path)
