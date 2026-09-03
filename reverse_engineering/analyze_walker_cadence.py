"""Measure the per-link update cadence of the walker cockpit transform chain.

Rendering runs far faster than the simulation tick, so the question that decides
where the jitter comes from is not "how big is each delta" but "how often does
each link change". If the camera is refreshed every rendered frame while the
cockpit only moves on a simulation tick (or vice versa), the cockpit visibly
judders against the view even though every individual transform is internally
consistent.

Reports per link, restricted to the possessed walker and one camera stream:
  changed%   fraction of rendered frames on which the link's value changed
  period     mean rendered-frames between changes
  step       mean magnitude of a change when one happens

Usage: python analyze_walker_cadence.py <run_dir> [vehicle_mesh]
"""
import math
import os
import re
import sys
from datetime import datetime

TS = re.compile(r"\[([^\]]+)\]")
NUM = r"[-\d.eE+]+"
POS = lambda tag: re.compile(tag + r"=\((" + NUM + r"),(" + NUM + r"),(" + NUM + r")\)")
QUAT = lambda tag: re.compile(tag + r"=\((" + NUM + r"),(" + NUM + r"),(" + NUM + r"),(" + NUM + r")\)")

P_VEH, P_CKPL, P_CKPD = POS("vehD"), POS("ckpL"), POS("ckpD")
P_POVL, P_POVD, P_CAM = POS("povL"), POS("povD"), POS("camD")
Q_VEH, Q_CKP, Q_CAM = QUAT("vehQ"), QUAT("ckpQ"), QUAT("camQ")
RE_VEH = re.compile(r" veh=(\S+)")
RE_CAM = re.compile(r"camPtr=(\S+)")
RE_VALID = re.compile(r" v=(\d+)")


def grab(rx, line, n):
    m = rx.search(line)
    return tuple(float(m.group(i + 1)) for i in range(n)) if m else None


def main(run_dir, want_vehicle=None):
    path = os.path.join(run_dir, "openshim.log")
    rows = []
    with open(path, "r", encoding="utf-8", errors="replace") as handle:
        for line in handle:
            if "[WALKF]" not in line or "camPtr=" not in line:
                continue
            veh = RE_VEH.search(line)
            cam = RE_CAM.search(line)
            valid = RE_VALID.search(line)
            if not (veh and cam and valid):
                continue
            rows.append({
                "veh": veh.group(1), "cam": cam.group(1), "valid": valid.group(1),
                "ts": datetime.fromisoformat(TS.search(line).group(1).replace("Z", "+00:00")),
                "vehD": grab(P_VEH, line, 3), "ckpL": grab(P_CKPL, line, 3),
                "ckpD": grab(P_CKPD, line, 3), "povL": grab(P_POVL, line, 3),
                "povD": grab(P_POVD, line, 3), "camD": grab(P_CAM, line, 3),
                "vehQ": grab(Q_VEH, line, 4), "ckpQ": grab(Q_CKP, line, 4),
                "camQ": grab(Q_CAM, line, 4),
            })

    if not rows:
        print("no parseable [WALKF] rows")
        return 1

    cams = {}
    for r in rows:
        cams[r["cam"]] = cams.get(r["cam"], 0) + 1
    primary = max(cams, key=cams.get)
    vehicles = {}
    for r in rows:
        vehicles[r["veh"]] = vehicles.get(r["veh"], 0) + 1
    vehicle = want_vehicle or max(vehicles, key=vehicles.get)

    sel = [r for r in rows if r["cam"] == primary and r["veh"] == vehicle and r["valid"][3] == "1"]
    print(f"rows={len(rows)} cameras={cams} vehicles={vehicles}")
    print(f"analysing vehicle={vehicle} camera={primary} frames={len(sel)}")
    if len(sel) < 10:
        print("not enough frames with a resolved cockpit")
        return 1

    span = (sel[-1]["ts"] - sel[0]["ts"]).total_seconds()
    print(f"span={span:.2f}s  render rate={len(sel)/span:.1f} frames/s\n")

    def cadence(key, dims):
        changes, steps, gap, gaps = 0, [], 0, []
        prev = None
        for r in sel:
            cur = r[key]
            if cur is None:
                continue
            if prev is not None:
                d = math.sqrt(sum((a - b) ** 2 for a, b in zip(cur, prev)))
                if d > 1e-6:
                    changes += 1
                    steps.append(d)
                    if gap:
                        gaps.append(gap)
                    gap = 1
                else:
                    gap += 1
            prev = cur
        n = len(sel) - 1
        return {
            "changed_pct": 100.0 * changes / n if n else 0.0,
            "period": (sum(gaps) / len(gaps)) if gaps else float("nan"),
            "step": (sum(steps) / len(steps)) if steps else 0.0,
            "max_step": max(steps) if steps else 0.0,
        }

    hdr = f"{'link':<10} {'changed%':>9} {'period(fr)':>11} {'mean step':>11} {'max step':>11}"
    print(hdr)
    print("-" * len(hdr))
    for key, dims in (("vehD", 3), ("ckpL", 3), ("ckpD", 3), ("povL", 3),
                      ("povD", 3), ("camD", 3), ("vehQ", 4), ("ckpQ", 4), ("camQ", 4)):
        c = cadence(key, dims)
        print(f"{key:<10} {c['changed_pct']:>8.2f}% {c['period']:>11.2f} "
              f"{c['step']:>11.6f} {c['max_step']:>11.6f}")

    # Direct cockpit-vs-vehicle agreement, and camera-vs-cockpit relative motion.
    gaps = [math.sqrt(sum((a - b) ** 2 for a, b in zip(r["vehD"], r["ckpD"]))) for r in sel]
    print(f"\n|vehD - ckpD|  mean={sum(gaps)/len(gaps):.6f}  max={max(gaps):.6f}")

    rel, prev = [], None
    for r in sel:
        v = tuple(a - b for a, b in zip(r["camD"], r["ckpD"]))
        if prev is not None:
            rel.append(math.sqrt(sum((a - b) ** 2 for a, b in zip(v, prev))))
        prev = v
    if rel:
        moved = [x for x in rel if x > 1e-6]
        print(f"cockpit->camera relative motion per frame: changed on {100.0*len(moved)/len(rel):.2f}% "
              f"of frames, mean={sum(rel)/len(rel):.6f}, max={max(rel):.6f}")
        print("(this is what the player sees as cockpit jitter: the cockpit moving relative to the eye)")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1] if len(sys.argv) > 1 else ".",
                  sys.argv[2] if len(sys.argv) > 2 else None))
