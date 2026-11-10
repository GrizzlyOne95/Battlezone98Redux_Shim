"""Join scrapbench census samples to perf-telemetry frame times.

Usage: python report_scrapbench.py <runDir>
Reads <runDir>/scrapbench-samples.jsonl and <runDir>/frames/openshim_frames_*_<pid>.bin.
Each census sample row gets the frame-time median/p95 of that client's frames
since its previous sample (frames in run state RUN_STARTED only).
"""
import datetime
import glob
import json
import os
import re
import statistics
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
from analyze_frame_hitches import Frames, RUN_STARTED, percentile  # noqa: E402

EPOCH_1601 = datetime.datetime(1601, 1, 1)


def frame_times(path):
    f = Frames(path)
    base = EPOCH_1601 + datetime.timedelta(microseconds=f.open_local_filetime / 10)
    out = []
    for i in range(len(f) - 1):
        if f.run_state[i] != RUN_STARTED:
            continue
        t = base + datetime.timedelta(seconds=(f.begin[i] - f.open_qpc) / f.qpc_frequency)
        out.append((t, f.interval_ms(i)))
    return out


def main(run_dir):
    samples = [json.loads(line) for line in open(os.path.join(run_dir, "scrapbench-samples.jsonl"), encoding="utf-8-sig")]
    frames = {}
    for path in glob.glob(os.path.join(run_dir, "frames", "openshim_frames_*.bin")):
        pid = int(re.search(r"_(\d+)\.bin$", path).group(1))
        frames[pid] = frame_times(path)
    print("# Scrap bench report: %s\n" % os.path.basename(run_dir))
    print("Frame times are frame-begin intervals (OPENSHIM_PERF_TELEMETRY), RUN_STARTED frames only.\n")
    for client in sorted({s["client"] for s in samples}):
        rows = [s for s in samples if s["client"] == client]
        ft = frames.get(rows[0]["pid"], [])
        print("## client %d (pid %d, %s)  frames=%d\n" % (client, rows[0]["pid"], "host" if client == 0 else "guest", len(ft)))
        print("| t s | phase | army5+6 | pilots | craft | scrap | objects | frames | p50 ms | p95 ms |")
        print("|---|---|---|---|---|---|---|---|---|---|")
        prev = None
        for s in rows:
            t = datetime.datetime.fromisoformat(s["local"][:26]) if len(s["local"]) > 26 else datetime.datetime.fromisoformat(s["local"])
            t = t.replace(tzinfo=None)
            st = s["state"]
            sel = sorted(ms for (ft_t, ms) in ft if prev is not None and prev <= ft_t < t)
            p50 = "%.1f" % percentile(sel, 0.5) if sel else "-"
            p95 = "%.1f" % percentile(sel, 0.95) if sel else "-"
            print("| %s | %s | %s | %s | %s | %s | %s | %d | %s | %s |" % (
                s["elapsed"], s["phase"], st.get("army5", 0) + st.get("army6", 0), st.get("pilots"),
                st.get("craftAlive"), st.get("scrap"), st.get("objects"), len(sel), p50, p95))
            prev = t
        print()
        last = rows[-1]["state"].get("classes", {})
        print("Final object classes: " + ", ".join("%s=%s" % kv for kv in sorted(last.items(), key=lambda kv: -kv[1])[:15]) + "\n")


if __name__ == "__main__":
    main(sys.argv[1])
