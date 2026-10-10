"""Attribute load-window and first-use hitch samples to cost categories.

Reads an OpenShim native CPU sampler capture (cpu_samples .bin) with the
repository's analyze_cpu_samples.py reader/symbolizer, then classifies every
sample of the game's main thread by the *first matching rule over its whole
stack* (priority order below), so each sample lands in exactly one category.

Windows come from the logs captured alongside the samples:
  * BZOgreLogfile.log  (1 s resolution) - resource-group phases
  * BZLogger.txt       (us resolution)  - mission start and [PIVOTPROBE] events

Usage: python attribute_load_hitch.py <run-folder> [--dump-top N]
"""
from __future__ import annotations

import collections, datetime, glob, json, os, re, sys

REPO = r"C:\Users\iestu\Documents\GIT\BZR-OpenShim"
sys.path.insert(0, os.path.join(REPO, "reverse_engineering"))
import analyze_cpu_samples as acs  # noqa: E402

# (category, compiled pattern over "module!symbol" text). First match wins.
RULES = [
    ("shader-compile", r"(?i)d3dcompiler|d3dx9|D3DCompile|D3DXCompile|cg\.dll|CgProgram|HighLevelGpuProgram::loadHighLevelImpl|D3D11HLSLProgram::compileMicrocode|D3D9HLSLProgram::loadFromSource|GpuProgram::loadFromSource"),
    ("shader-cache", r"(?i)Microcode|GpuProgramManager::(get|add|isMicrocode)"),
    ("texture-decode", r"(?i)Codec|FreeImage|Image::(load|decode|scale|resize|generateMipmaps|flipAround)|PixelUtil::bulkPixelConversion|PixelBox|Image::Image"),
    ("texture-upload", r"(?i)D3D11Texture|D3D9Texture|HardwarePixelBuffer|D3D11HardwarePixelBuffer|D3D9HardwarePixelBuffer|Texture::(createInternalResources|_loadImages|loadImage|loadImpl|load)|TextureManager"),
    ("mesh-load", r"(?i)MeshSerializer|Mesh::(loadImpl|prepareImpl|load|prepare)|MeshManager::(load|prepare|createOrRetrieve)|SkeletonSerializer|Skeleton::(loadImpl|prepareImpl)"),
    ("script-parse", r"(?i)ScriptCompiler|ScriptLexer|ScriptParser|ScriptTranslator|parseScript|MaterialSerializer|ParticleSystemManager::parse|CompositorManager::parse|AbstractNode|ConcreteNode|ObjectAbstractNode"),
    ("material-teardown", r"(?i)ResourceGroupManager::(unload|clear|destroy)|ResourceManager::(remove|unload|destroy)|Material::(unload|~)|MaterialManager::remove|Resource::unload|~Material|Technique::~|Pass::~"),
    ("material-compile", r"(?i)Material::(compile|load|_|prepare)|Technique::(_compile|isSupported|_load)|Pass::_(load|prepare)|MaterialManager"),
    ("resource-index", r"(?i)FileSystemArchive::(find|list|load)|ResourceGroupManager::(addResourceLocation|initialise|_initialise|parseResourceGroupScripts|createDeclared|resourceExists|findResourceNames|openResource|_find)|Archive::find|FindFirstFile|FindNextFile|NtQueryDirectoryFile"),
    ("file-io", r"(?i)NtReadFile|NtCreateFile|NtOpenFile|ReadFile|CreateFile|FileSystemArchive::open|FileStreamDataStream|FileHandleDataStream|MemoryDataStream|DataStream::"),
]
RULES = [(name, re.compile(rx)) for name, rx in RULES]


def ogre_phases(path):
    """Return [(local datetime, text)] for resource-group lines (1 s stamps)."""
    out = []
    day = None
    with open(path, encoding="utf-8", errors="replace") as fh:
        for line in fh:
            m = re.match(r"(\d\d):(\d\d):(\d\d): (.*)", line)
            if m and ("resource group" in m.group(4)):
                out.append((tuple(map(int, m.groups()[:3])), m.group(4).strip()))
    return out


def bz_events(path):
    out = []
    with open(path, encoding="utf-8", errors="replace") as fh:
        for line in fh:
            m = re.match(r"(\d{4}-\d\d-\d\d \d\d:\d\d:\d\d\.\d+) (.*)", line)
            if not m:
                continue
            text = m.group(2)
            if ("PIVOTPROBE] destroyed" in text or "Game Simulation Initialized" in text
                    or "Starting BattleZone" in text):
                out.append((datetime.datetime.fromisoformat(m.group(1)), text.split("2026-")[0].strip()))
    return out


def classify(names):
    joined = "\n".join(names)
    for name, rx in RULES:
        if rx.search(joined):
            return name
    leaf = names[0]
    if any(tok in leaf for tok in acs.WAIT_SYMBOLS):
        return "wait-other"
    return "other"


def main(argv):
    run = argv[0]
    dump_top = int(argv[argv.index("--dump-top") + 1]) if "--dump-top" in argv else 0
    bins = glob.glob(os.path.join(run, "openshim_cpu_samples_*.bin"))
    if not bins:
        raise SystemExit("no capture in " + run)
    cap = acs.read_capture(bins[0])
    sym = acs.Symbolizer(cap, None, "battlezone98redux.exe", False)
    per_thread = collections.Counter(s[0] for s in cap.samples)
    main_tid = per_thread.most_common(1)[0][0]
    samples = [(cap.local_time(q), fl, fr) for t, q, fl, fr in cap.samples if t == main_tid]
    hz = cap.requested_hz
    events = bz_events(os.path.join(run, "BZLogger.txt"))
    start = next(t for t, x in events if "Starting BattleZone" in x)
    sim = next(t for t, x in events if "Game Simulation Initialized" in x)
    destroyed = [(t, x.split("destroyed ")[1].split(" ")[0]) for t, x in events if "destroyed" in x]

    cache = {}

    def names_for(frames):
        key = tuple(frames)
        if key not in cache:
            cache[key] = tuple(sym.symbol(a) for a in frames)
        return cache[key]

    def window(begin, end, label, top=0):
        cats = collections.Counter()
        tops = collections.defaultdict(collections.Counter)
        n = 0
        for t, fl, fr in samples:
            if begin <= t <= end:
                names = names_for(fr)
                c = classify(names)
                cats[c] += 1
                n += 1
                if top:
                    tops[c][names[0]] += 1
        ms = {k: round(v * 1000.0 / hz, 1) for k, v in cats.most_common()}
        res = {"label": label, "begin": str(begin), "end": str(end),
               "wall_ms": round((end - begin).total_seconds() * 1000, 1),
               "sampled_ms": round(n * 1000.0 / hz, 1), "categories_ms": ms}
        if top:
            res["top_leaf"] = {k: tops[k].most_common(top) for k in tops}
        return res

    # Ogre phases are 1 s resolution; map h:m:s onto the BZLogger date.
    phases = ogre_phases(os.path.join(run, "BZOgreLogfile.log"))

    def at(hms):
        return start.replace(hour=hms[0], minute=hms[1], second=hms[2], microsecond=0)

    out = {"run": run, "main_tid": main_tid, "hz": hz,
           "threads": per_thread.most_common(6), "phases": [(str(at(h)), x) for h, x in phases]}
    out["startup_to_sim"] = window(start, sim, "process start -> Game Simulation Initialized", dump_top)
    # Mission Modable cycle: last 'Unloading resource group Modable' before sim
    # through the end of the following parse (+1 s for stamp rounding).
    # the unload that precedes the last Clearing of Modable before the mission starts
    idx_clear = [i for i, (h, x) in enumerate(phases) if x == "Clearing resource group Modable" and at(h) <= sim]
    if idx_clear:
        ic = idx_clear[-1]
        iu = max(i for i in range(ic) if phases[i][1] == "Unloading resource group Modable")
        idone = min(i for i in range(ic, len(phases))
                    if phases[i][1] == "Finished parsing scripts for resource group Modable")
        b, c, e = at(phases[iu][0]), at(phases[ic][0]), at(phases[idone][0]) + datetime.timedelta(seconds=1)
        out["mission_modable_unload_clear"] = window(b, c, "mission Modable unload -> clear (1 s stamps)", dump_top)
        out["mission_modable_init_parse"] = window(c, e, "mission Modable clear -> parsed (1 s stamps)", dump_top)
    first_parse_begin = [at(h) for h, x in phases if x == "Parsing scripts for resource group General"]
    first_done = [at(h) for h, x in phases if x == "Finished parsing scripts for resource group Modable"]
    if first_parse_begin and first_done:
        out["shell_parse"] = window(first_parse_begin[0], first_done[0] + datetime.timedelta(seconds=1),
                                    "first General+Modable parse (+-1 s stamps)", dump_top)
    hitches = []
    for t, what in destroyed:
        w = window(t - datetime.timedelta(milliseconds=50), t + datetime.timedelta(milliseconds=1500), what, dump_top)
        base = window(t - datetime.timedelta(milliseconds=1650), t - datetime.timedelta(milliseconds=150), what + " baseline", 0)
        w["baseline_categories_ms"] = base["categories_ms"]
        hitches.append(w)
    out["destroy_windows"] = hitches
    json.dump(out, open(os.path.join(run, "attribution.json"), "w"), indent=1, default=str)
    print(json.dumps({k: v for k, v in out.items() if k != "phases"}, indent=1, default=str))


if __name__ == "__main__":
    main(sys.argv[1:])
