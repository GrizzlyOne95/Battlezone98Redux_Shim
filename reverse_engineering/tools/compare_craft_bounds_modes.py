"""Join the per-mode benchmark results of run_craft_bounds_matrix.ps1 into one
comparison table.

Usage:
    python compare_craft_bounds_modes.py <matrixRoot> [--modes stock,private,restore]

<matrixRoot> is the directory holding one subdirectory per mode, each of which
already has a results.csv and render_contributors.csv written by
analyze_live_combat_benchmark.ps1.
"""

import argparse
import csv
import os
import sys
from collections import defaultdict

WORKLOAD_KEYS = ("renderer", "unit_odf", "scenario", "count", "orientation")

# Reported for every workload. Submission counts are the load-independent
# evidence; frame times are kept but are single runs on a machine in use.
METRICS = (
    ("ogre_submissions_per_frame", "submissions/f", 1),
    ("ogre_submission_cpu_ms_per_frame", "submitCPU ms/f", 3),
    ("main_render_queue_per_frame", "rqMain/f", 1),
    ("shadow_render_queue_per_frame", "rqShadow/f", 1),
    ("frame_mean_ms", "frame mean ms", 3),
    ("frame_p95_ms", "p95 ms", 3),
    ("frame_p99_ms", "p99 ms", 3),
    ("draw_calls_per_frame", "draws/f", 1),
    ("indexed_draw_calls_per_frame", "indexedDraws/f", 1),
)


def read_rows(path):
    if not os.path.isfile(path):
        return []
    with open(path, newline="", encoding="utf-8-sig") as handle:
        return list(csv.DictReader(handle))


def workload_key(row):
    return tuple(row.get(name, "") for name in WORKLOAD_KEYS)


def as_float(text):
    if text is None or text == "":
        return None
    try:
        return float(text)
    except ValueError:
        return None


def format_delta(baseline, value):
    if baseline in (None, 0) or value is None:
        return ""
    return "%+.1f%%" % (100.0 * (value - baseline) / baseline)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("root")
    parser.add_argument("--modes", default="stock,private,restore")
    parser.add_argument("--baseline", default="stock")
    args = parser.parse_args()

    modes = [m.strip() for m in args.modes.split(",") if m.strip()]
    results = {m: {workload_key(r): r for r in
                   read_rows(os.path.join(args.root, m, "results.csv"))}
               for m in modes}

    workloads = []
    for mode in modes:
        for key in results[mode]:
            if key not in workloads:
                workloads.append(key)
    workloads.sort()

    if not workloads:
        sys.exit("no results found under %s" % args.root)

    for metric, label, digits in METRICS:
        print("\n### %s" % label)
        header = ["workload"] + modes + ["%s vs %s" % (m, args.baseline)
                                         for m in modes if m != args.baseline]
        print(" | ".join(header))
        print(" | ".join("---" for _ in header))
        for key in workloads:
            values = {}
            for mode in modes:
                row = results[mode].get(key)
                values[mode] = as_float(row.get(metric)) if row else None
            cells = ["%s %s %s %s %s" % key]
            for mode in modes:
                v = values[mode]
                cells.append("" if v is None else ("%.*f" % (digits, v)))
            for mode in modes:
                if mode == args.baseline:
                    continue
                cells.append(format_delta(values.get(args.baseline), values[mode]))
            print(" | ".join(cells))

    # Per-camera contributor rollup, which is what separates a main-view saving
    # from a shadow-cascade saving.
    print("\n### submissions per frame by camera")
    rollup = defaultdict(lambda: defaultdict(float))
    cameras = []
    for mode in modes:
        rows = read_rows(os.path.join(args.root, mode, "render_contributors.csv"))
        for row in rows:
            key = (workload_key(row), row.get("camera", "?"))
            value = as_float(row.get("ogre_submissions_per_frame"))
            if value is None:
                continue
            rollup[key][mode] += value
            if row.get("camera", "?") not in cameras:
                cameras.append(row.get("camera", "?"))
    if rollup:
        print(" | ".join(["workload", "camera"] + modes))
        print(" | ".join("---" for _ in range(2 + len(modes))))
        for (key, camera) in sorted(rollup, key=lambda k: (k[0], k[1])):
            row = rollup[(key, camera)]
            print(" | ".join(
                ["%s %s %s %s %s" % key, camera] +
                ["%.1f" % row[m] if m in row else "" for m in modes]))
    else:
        print("(no contributor rows)")


if __name__ == "__main__":
    main()
