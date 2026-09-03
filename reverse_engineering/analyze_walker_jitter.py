"""Attribute walker cockpit jitter to a link in the transform chain.

Joins the native per-frame [WALKF] capture (walker_cockpit_trace.cpp) with the
input driver's phases.csv, then reports per phase, per link:

  dP/dQ   frame-to-frame delta      -- how fast the link is moving
  jerk    |delta(n) - delta(n-1)|   -- the discontinuity that reads as jitter
  gap     |vehD - ckpD|             -- cockpit tracking error against the vehicle

The gap column is the direct test of the "cockpit node is a per-frame copy of
the vehicle node" hypothesis: stock parents the cockpit node to the scene root
as a SIBLING of the vehicle node with an identical transform, so any nonzero,
oscillating gap under motion is the cockpit consuming a stale vehicle transform.

Usage: python analyze_walker_jitter.py <run_dir>
"""
import csv
import math
import os
import re
import sys
from datetime import datetime, timezone

LINE = re.compile(
    r"\[(?P<ts>[^\]]+)\].*?\[WALKF\] f=(?P<f>\d+) dt=(?P<dt>[-\d.]+) case=(?P<case>\S+) veh=(?P<veh>\S+) "
    r"vehD=\((?P<vx>[-\d.]+),(?P<vy>[-\d.]+),(?P<vz>[-\d.]+)\) dP=(?P<vdp>[-\d.]+) dQ=(?P<vdq>[-\d.]+) jP=(?P<vjp>[-\d.]+) jQ=(?P<vjq>[-\d.]+) \| "
    r"ckpL=\([^)]*\) dP=(?P<cldp>[-\d.]+) jP=(?P<cljp>[-\d.]+) \| "
    r"ckpD=\((?P<cx>[-\d.]+),(?P<cy>[-\d.]+),(?P<cz>[-\d.]+)\) dP=(?P<cdp>[-\d.]+) dQ=(?P<cdq>[-\d.]+) jP=(?P<cjp>[-\d.]+) jQ=(?P<cjq>[-\d.]+) \| "
    r"povL=\([^)]*\) dP=(?P<pldp>[-\d.]+) jP=(?P<pljp>[-\d.]+) \| "
    r"povD=\([^)]*\) dP=(?P<pdp>[-\d.]+) dQ=(?P<pdq>[-\d.]+) jP=(?P<pjp>[-\d.]+) jQ=(?P<pjq>[-\d.]+) \| "
    r"camD=\((?P<mx>[-\d.]+),(?P<my>[-\d.]+),(?P<mz>[-\d.]+)\) dP=(?P<mdp>[-\d.]+) dQ=(?P<mdq>[-\d.]+) jP=(?P<mjp>[-\d.]+) jQ=(?P<mjq>[-\d.]+) \| "
    r"v=(?P<valid>\d+)"
)


def parse_ts(text):
    return datetime.fromisoformat(text.replace("Z", "+00:00"))


def load_frames(path):
    rows = []
    with open(path, "r", encoding="utf-8", errors="replace") as handle:
        for line in handle:
            if "[WALKF]" not in line:
                continue
            m = LINE.search(line)
            if not m:
                continue
            g = m.groupdict()
            rows.append({
                "ts": parse_ts(g["ts"]),
                "f": int(g["f"]),
                "dt": float(g["dt"]),
                "veh": g["veh"],
                "valid": g["valid"],
                "vpos": (float(g["vx"]), float(g["vy"]), float(g["vz"])),
                "cpos": (float(g["cx"]), float(g["cy"]), float(g["cz"])),
                "mpos": (float(g["mx"]), float(g["my"]), float(g["mz"])),
                "veh.dP": float(g["vdp"]), "veh.jP": float(g["vjp"]), "veh.jQ": float(g["vjq"]),
                "ckp.dP": float(g["cdp"]), "ckp.jP": float(g["cjp"]), "ckp.jQ": float(g["cjq"]),
                "ckpL.dP": float(g["cldp"]), "ckpL.jP": float(g["cljp"]),
                "pov.dP": float(g["pdp"]), "pov.jP": float(g["pjp"]), "pov.jQ": float(g["pjq"]),
                "povL.dP": float(g["pldp"]), "povL.jP": float(g["pljp"]),
                "cam.dP": float(g["mdp"]), "cam.jP": float(g["mjp"]), "cam.jQ": float(g["mjq"]),
            })
    return rows


def load_phases(path):
    if not os.path.exists(path):
        return []
    out = []
    with open(path, newline="", encoding="utf-8-sig") as handle:
        for row in csv.DictReader(handle):
            start = parse_ts(row["startUtc"])
            out.append({"phase": row["phase"], "keys": row["keys"],
                        "start": start, "dur": float(row["durationSec"])})
    return out


def dist(a, b):
    return math.sqrt(sum((x - y) ** 2 for x, y in zip(a, b)))


def stats(values):
    if not values:
        return (0.0, 0.0)
    return (sum(values) / len(values), max(values))


def main(run_dir):
    frames = load_frames(os.path.join(run_dir, "openshim.log"))
    phases = load_phases(os.path.join(run_dir, "phases.csv"))
    if not frames:
        print("no [WALKF] frames found")
        return 1

    print(f"frames={len(frames)}  span={frames[0]['ts']} .. {frames[-1]['ts']}")
    vehicles = sorted({f["veh"] for f in frames})
    print(f"vehicles seen: {', '.join(vehicles)}")
    print(f"validity masks: {sorted({f['valid'] for f in frames})}"
          "  (order: veh.local veh.derived ckp.local ckp.derived pov.local pov.derived cam.derived)")
    print()

    if not phases:
        phases = [{"phase": "whole-run", "keys": "", "start": frames[0]["ts"],
                   "dur": (frames[-1]["ts"] - frames[0]["ts"]).total_seconds() + 1}]

    hdr = (f"{'phase':<10} {'keys':<12} {'n':>5} "
           f"{'veh.dP':>9} {'ckp.dP':>9} {'cam.dP':>9} "
           f"{'veh.jP':>9} {'ckp.jP':>9} {'pov.jP':>9} {'cam.jP':>9} "
           f"{'gap.mean':>9} {'gap.max':>9}")
    print(hdr)
    print("-" * len(hdr))

    for ph in phases:
        end = ph["start"].timestamp() + ph["dur"]
        sel = [f for f in frames if ph["start"].timestamp() <= f["ts"].timestamp() < end]
        if not sel:
            print(f"{ph['phase']:<10} {ph['keys']:<12} {0:>5}  (no frames)")
            continue
        gaps = [dist(f["vpos"], f["cpos"]) for f in sel if f["valid"][3] == "1"]
        print(f"{ph['phase']:<10} {ph['keys']:<12} {len(sel):>5} "
              f"{stats([f['veh.dP'] for f in sel])[0]:>9.5f} "
              f"{stats([f['ckp.dP'] for f in sel])[0]:>9.5f} "
              f"{stats([f['cam.dP'] for f in sel])[0]:>9.5f} "
              f"{stats([f['veh.jP'] for f in sel])[1]:>9.5f} "
              f"{stats([f['ckp.jP'] for f in sel])[1]:>9.5f} "
              f"{stats([f['pov.jP'] for f in sel])[1]:>9.5f} "
              f"{stats([f['cam.jP'] for f in sel])[1]:>9.5f} "
              f"{stats(gaps)[0]:>9.5f} {stats(gaps)[1]:>9.5f}")

    moving = [f for f in frames if f["veh.dP"] > 1e-4]
    print(f"\nframes with vehicle motion (veh.dP > 1e-4): {len(moving)} / {len(frames)}")
    if moving:
        print("peak jerk per link across moving frames (the first link to spike is the suspect):")
        for link in ("veh.jP", "ckpL.jP", "ckp.jP", "povL.jP", "pov.jP", "cam.jP"):
            mean, mx = stats([f[link] for f in moving])
            worst = max(moving, key=lambda f: f[link])
            print(f"  {link:<10} mean={mean:.6f} max={mx:.6f} @frame={worst['f']}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1] if len(sys.argv) > 1 else "."))
