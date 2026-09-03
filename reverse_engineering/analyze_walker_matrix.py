"""Cross-walker comparison for the cockpit jitter investigation.

Produces the classification table: for each possessed vehicle, does the cockpit
diverge from the walker root, and does the camera move on frames where the
cockpit does not?

  gap        |vehD - ckpD| -- cockpit vs walker-root disagreement
  cam-only   frames where the camera moved but vehicle AND cockpit did not.
             In a first-person view the cockpit is meant to be rigidly locked to
             the eye, so every one of these frames is a visible cockpit slide.

Usage: python analyze_walker_matrix.py <run_dir> [<run_dir> ...]
"""
import math
import os
import re
import sys

NUM = r"[-\d.eE+]+"


def pos(tag):
    return re.compile(tag + r"=\((" + NUM + r"),(" + NUM + r"),(" + NUM + r")\)")


P_VEH, P_CKP, P_CAM = pos("vehD"), pos("ckpD"), pos("camD")
RE_VEH = re.compile(r" veh=(\S+)")
RE_CAM = re.compile(r"camPtr=(\S+)")
RE_VALID = re.compile(r" v=(\d+)")
RE_WRITER = re.compile(r"camWriter=(\S+)")
RE_CKPRES = re.compile(r"cockpit resolved entity=\S+ mesh=(\S+) node=(\S+)")
RE_CKPCHAIN = re.compile(r"ckp chain\[(\d+)\] node=(\S+) name=(\S+)")
RE_VEHCHAIN = re.compile(r"veh chain\[(\d+)\] node=(\S+) name=(\S+)")
RE_POV = re.compile(r"RESOLVED veh=(\S+) ckp=(\S+) pov=(\S+)")


def dist(a, b):
    return math.sqrt(sum((x - y) ** 2 for x, y in zip(a, b)))


def analyse(run_dir):
    path = os.path.join(run_dir, "openshim.log")
    if not os.path.exists(path):
        return None

    rows = []
    writers = {}
    ckp_mesh = ckp_node = None
    ckp_parent = veh_parent = None
    pov = None
    with open(path, "r", encoding="utf-8", errors="replace") as fh:
        for line in fh:
            m = RE_CKPRES.search(line)
            if m:
                ckp_mesh, ckp_node = m.group(1), m.group(2)
            m = RE_CKPCHAIN.search(line)
            if m and m.group(1) == "1":
                ckp_parent = m.group(3)
            m = RE_VEHCHAIN.search(line)
            if m and m.group(1) == "1":
                veh_parent = m.group(3)
            m = RE_POV.search(line)
            if m:
                pov = m.group(3)
            if "[WALKF]" not in line or "camPtr=" not in line:
                continue
            v, c, k = P_VEH.search(line), P_CKP.search(line), P_CAM.search(line)
            vh, cm, va = RE_VEH.search(line), RE_CAM.search(line), RE_VALID.search(line)
            if not (v and c and k and vh and cm and va):
                continue
            w = RE_WRITER.search(line)
            if w:
                writers[w.group(1)] = writers.get(w.group(1), 0) + 1
            rows.append((vh.group(1), cm.group(1), va.group(1),
                         tuple(map(float, v.groups())),
                         tuple(map(float, c.groups())),
                         tuple(map(float, k.groups()))))
    if not rows:
        return None

    veh_counts, cam_counts = {}, {}
    for r in rows:
        veh_counts[r[0]] = veh_counts.get(r[0], 0) + 1
        cam_counts[r[1]] = cam_counts.get(r[1], 0) + 1
    vehicle = max(veh_counts, key=veh_counts.get)
    camera = max(cam_counts, key=cam_counts.get)

    sel = [r for r in rows if r[0] == vehicle and r[1] == camera]
    has_ckp = [r for r in sel if r[2][3] == "1"]
    gaps = [dist(r[3], r[4]) for r in has_ckp]

    both = veh_only = cam_only = neither = 0
    cam_only_mag = []
    for i in range(1, len(sel)):
        dv = dist(sel[i][3], sel[i - 1][3]) > 1e-6
        dc = dist(sel[i][4], sel[i - 1][4]) > 1e-6
        dk = dist(sel[i][5], sel[i - 1][5]) > 1e-6
        moved_body = dv or dc
        if moved_body and dk:
            both += 1
        elif moved_body:
            veh_only += 1
        elif dk:
            cam_only += 1
            cam_only_mag.append(dist(sel[i][5], sel[i - 1][5]))
        else:
            neither += 1
    n = max(1, len(sel) - 1)
    body_moved = both + veh_only
    top_writer = max((w for w in writers if w != "0x00000000"),
                     key=lambda w: writers[w], default="n/a")
    return {
        "dir": os.path.basename(run_dir), "vehicle": vehicle, "frames": len(sel),
        "ckp_frames": len(has_ckp), "ckp_mesh": ckp_mesh or "<none>",
        "gap_mean": (sum(gaps) / len(gaps)) if gaps else float("nan"),
        "gap_max": max(gaps) if gaps else float("nan"),
        "cam_only_pct": 100.0 * cam_only / n, "cam_only": cam_only,
        "body_pct": 100.0 * body_moved / n, "body_moved": body_moved,
        "cam_only_mean": (sum(cam_only_mag) / len(cam_only_mag)) if cam_only_mag else 0.0,
        "cam_only_max": max(cam_only_mag) if cam_only_mag else 0.0,
        "writer": top_writer, "pov": pov or "<none>",
        "veh_parent": veh_parent or "?", "ckp_parent": ckp_parent or "?",
    }


def main(dirs):
    results = [r for r in (analyse(d) for d in dirs) if r]
    if not results:
        print("no analysable runs")
        return 1

    print("Cockpit vs walker-root agreement, and camera-vs-cockpit divergence\n")
    hdr = (f"{'vehicle':<14} {'cockpit mesh':<16} {'frames':>7} {'gap mean':>9} {'gap max':>9} "
           f"{'body-mv%':>9} {'cam-only':>9} {'cam-only%':>10} {'mean mag':>9} {'max mag':>9} {'writer RVA':>12}")
    print(hdr)
    print("-" * len(hdr))
    for r in results:
        print(f"{r['vehicle']:<14} {r['ckp_mesh']:<16} {r['frames']:>7} "
              f"{r['gap_mean']:>9.6f} {r['gap_max']:>9.6f} "
              f"{r['body_pct']:>8.2f}% {r['cam_only']:>9} {r['cam_only_pct']:>9.2f}% "
              f"{r['cam_only_mean']:>9.6f} {r['cam_only_max']:>9.6f} {r['writer']:>12}")

    print("\nHierarchy (both nodes hang off the scene root; the cockpit is a SIBLING of the")
    print("vehicle node, not a child of it):")
    print(f"  {'vehicle':<14} {'POV bone':<14} {'veh node parent':<18} {'ckp node parent':<18}")
    for r in results:
        print(f"  {r['vehicle']:<14} {r['pov']:<14} {r['veh_parent']:<18} {r['ckp_parent']:<18}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
