"""Phase 1 four-team attribution: fold contributor rows into ownership families.

Input is `render_contributors.csv` as produced by
`analyze_live_combat_benchmark.ps1`, whose rows are already one semantic group
(renderable type + mesh + material + technique + scheme + camera) averaged over
the measurement window. This script only classifies and totals them; it does not
re-derive any measurement.

Two rules matter and are easy to get wrong:

* An Ogre submission is not an API draw. Both are reported side by side and
  never summed together.
* A shadow-caster submission carries the depth-caster material, not the vehicle
  material, so shadow work must be classified by *camera* first and by material
  second -- otherwise every caster lands in one meaningless bucket.

Usage:
    python analyze_fourteam_phase1.py <render_contributors.csv> [--run RUN_ID]
                                      [--csv OUT.csv]
"""

from __future__ import annotations

import argparse
import collections
import csv
import sys


SHADOW_CAMERA_TOKEN = "shadowtexture"


def _number(row: dict, name: str) -> float:
    value = row.get(name, "")
    if value is None or value == "":
        return 0.0
    try:
        return float(value)
    except ValueError:
        return 0.0


def classify(row: dict, unit_mesh: str) -> tuple[str, str]:
    """Return (family, detail) for one contributor group."""
    rtype = row.get("type", "") or ""
    mesh = (row.get("mesh", "") or "").strip()
    material = (row.get("material", "") or "").strip()
    scheme = (row.get("scheme", "") or "").strip()
    camera = (row.get("camera", "") or "").strip()
    lod = (row.get("lod", "") or "").strip()

    is_shadow = SHADOW_CAMERA_TOKEN in camera.lower()
    short_type = rtype.split("@")[0].lstrip(".?AV") if rtype else "unknown"

    if is_shadow:
        cascade = camera.replace("Ogre/ShadowTexture", "").replace("Cam", "")
        if mesh.lower() == unit_mesh:
            return "vehicle shadow caster", f"cascade {cascade}"
        if mesh.lower().startswith("renderabletilecluster"):
            return "terrain shadow caster", f"cascade {cascade}"
        if mesh and mesh != "<none>":
            return "other mesh shadow caster", f"{mesh} cascade {cascade}"
        return "other shadow caster", f"{short_type} cascade {cascade}"

    if "DynamicGeometryBatch" in rtype:
        return "effects (DynamicGeometry)", f"{material} [{scheme}]"
    if "Rectangle2D" in rtype:
        return "post-process quads", material
    if "ManualObjectSection" in rtype:
        return "world manual geometry", f"{material} [{scheme}]"
    if "SubEntity" in rtype:
        if mesh.lower() == unit_mesh:
            return "vehicle main view", f"{material} [{scheme}] lod{lod}"
        if mesh.lower().startswith("renderabletilecluster"):
            return "terrain main view", f"{material} [{scheme}]"
        if mesh.lower() in ("sky", "skybox"):
            return "sky", material
        return "ordnance / prop meshes", f"{mesh} {material} [{scheme}]"
    return "unclassified", f"{short_type} {material} [{scheme}]"


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("contributors")
    parser.add_argument("--run", action="append", default=None,
                        help="restrict to these run_id values (repeatable)")
    parser.add_argument("--unit-mesh", default="avtank.mesh",
                        help="mesh treated as the benchmark vehicle")
    parser.add_argument("--csv", default=None, help="write the family table here")
    parser.add_argument("--detail", action="store_true",
                        help="also print every group inside each family")
    args = parser.parse_args(argv)

    with open(args.contributors, newline="", encoding="utf-8-sig") as handle:
        rows = list(csv.DictReader(handle))
    if args.run:
        wanted = set(args.run)
        rows = [r for r in rows if r.get("run_id") in wanted]
    if not rows:
        print("no contributor rows matched", file=sys.stderr)
        return 1

    unit_mesh = args.unit_mesh.lower()
    fields = ("ogre_submissions_per_frame", "draw_per_frame",
              "indexed_draw_per_frame", "operation_vertices_per_frame",
              "operation_indices_per_frame", "cpu_ms_per_frame",
              "no_draw_per_frame", "unobserved_per_frame")

    per_run: dict[str, dict] = collections.defaultdict(
        lambda: collections.defaultdict(lambda: collections.defaultdict(float)))
    detail: dict[str, dict] = collections.defaultdict(
        lambda: collections.defaultdict(lambda: collections.defaultdict(float)))

    for row in rows:
        run = row.get("run_id", "?")
        family, det = classify(row, unit_mesh)
        for field in fields:
            per_run[run][family][field] += _number(row, field)
            detail[run][(family, det)][field] += _number(row, field)

    out_rows = []
    for run in sorted(per_run):
        families = per_run[run]
        total_sub = sum(f["ogre_submissions_per_frame"] for f in families.values())
        total_cpu = sum(f["cpu_ms_per_frame"] for f in families.values())
        print(f"\n=== {run} ===")
        print(f"{'family':30} {'sub/f':>9} {'%sub':>6} {'draw/f':>9} "
              f"{'d/s':>5} {'tris/f':>11} {'cpu ms/f':>9} {'%cpu':>6}")
        for family in sorted(families, key=lambda k: -families[k]["ogre_submissions_per_frame"]):
            values = families[family]
            sub = values["ogre_submissions_per_frame"]
            draw = values["draw_per_frame"] + values["indexed_draw_per_frame"]
            tris = values["operation_indices_per_frame"] / 3.0
            cpu = values["cpu_ms_per_frame"]
            print(f"{family:30} {sub:9.1f} {100*sub/total_sub if total_sub else 0:5.1f}% "
                  f"{draw:9.1f} {draw/sub if sub else 0:5.2f} {tris:11.0f} "
                  f"{cpu:9.3f} {100*cpu/total_cpu if total_cpu else 0:5.1f}%")
            out_rows.append({
                "run_id": run, "family": family,
                "submissions_per_frame": round(sub, 2),
                "api_draws_per_frame": round(draw, 2),
                "draws_per_submission": round(draw / sub, 4) if sub else "",
                "triangles_per_frame": round(tris, 0),
                "cpu_ms_per_frame": round(cpu, 4),
                "no_draw_submissions_per_frame": round(values["no_draw_per_frame"], 2),
                "unobserved_submissions_per_frame": round(values["unobserved_per_frame"], 2),
            })
        total_draw = sum(f["draw_per_frame"] + f["indexed_draw_per_frame"]
                         for f in families.values())
        print(f"{'TOTAL':30} {total_sub:9.1f} {100.0:5.1f}% {total_draw:9.1f} "
              f"{total_draw/total_sub if total_sub else 0:5.2f} "
              f"{sum(f['operation_indices_per_frame'] for f in families.values())/3.0:11.0f} "
              f"{total_cpu:9.3f} {100.0:5.1f}%")

        if args.detail:
            groups = detail[run]
            for family, det in sorted(
                    groups, key=lambda k: -groups[k]["ogre_submissions_per_frame"]):
                values = groups[(family, det)]
                sub = values["ogre_submissions_per_frame"]
                draw = values["draw_per_frame"] + values["indexed_draw_per_frame"]
                print(f"    {family:26} {det:44} {sub:8.1f} {draw:8.1f} "
                      f"{values['cpu_ms_per_frame']:8.3f}")

    if args.csv and out_rows:
        with open(args.csv, "w", newline="", encoding="utf-8") as handle:
            writer = csv.DictWriter(handle, fieldnames=list(out_rows[0]))
            writer.writeheader()
            writer.writerows(out_rows)
        print(f"\nwrote {args.csv}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
