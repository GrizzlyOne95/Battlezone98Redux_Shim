"""Summarize PresentMon v1 captures, grouped by whatever varies between them.

Written for the Phase 2 shim A/B, where a first pass produced a 36% "improvement"
that turned out to be mostly a change of DWM present mode between runs. The same
scene with identical GPU-active time measures about 3.4 ms as
"Hardware: Independent Flip" and about 9.6 ms as "Composed: Flip", so present
mode is reported for every run and results are grouped by it. Two captures in
different present modes are not comparable and this tool will not average them
together.

Usage:
    python analyze_presentmon_runs.py <root> [--csv OUT.csv]

`root` is searched recursively for presentmon.csv files. Each capture's arm,
repeat and scenario are taken from its path and metadata.json.
"""

from __future__ import annotations

import argparse
import collections
import csv
import glob
import json
import os
import statistics
import sys


def percentile(values: list[float], share: float) -> float:
    ordered = sorted(values)
    index = int(round(share / 100.0 * (len(ordered) - 1)))
    return ordered[min(max(index, 0), len(ordered) - 1)]


def load(path: str) -> dict | None:
    with open(path, newline="", encoding="utf-8-sig") as handle:
        rows = list(csv.DictReader(handle))
    frames = [float(row["msBetweenPresents"]) for row in rows
              if row.get("msBetweenPresents") not in (None, "", "NA")]
    if len(frames) < 50:
        return None
    gpu = [float(row["msGPUActive"]) for row in rows
           if row.get("msGPUActive") not in (None, "", "NA")]
    times = [float(row["TimeInSeconds"]) for row in rows
             if row.get("TimeInSeconds") not in (None, "", "NA")]
    modes = collections.Counter(row.get("PresentMode", "?") for row in rows)
    dominant, dominant_count = modes.most_common(1)[0]

    # Drift: mean of the last whole second minus mean of the first. A workload
    # whose cost is proportional to something that accumulates during a battle
    # -- ordnance in flight, impact lights -- is not stationary, and then the
    # mean over the window depends on how long the window is. Reporting drift
    # keeps that visible instead of hiding it inside a single average.
    drift = float("nan")
    if times and len(times) == len(frames):
        start, end = min(times), max(times)
        if end - start >= 2.0:
            first = [f for t, f in zip(times, frames) if t < start + 1.0]
            last = [f for t, f in zip(times, frames) if t > end - 1.0]
            if first and last:
                drift = statistics.mean(last) - statistics.mean(first)

    run_root = os.path.dirname(path)
    metadata = {}
    meta_path = os.path.join(run_root, "metadata.json")
    if os.path.exists(meta_path):
        try:
            with open(meta_path, encoding="utf-8-sig") as handle:
                metadata = json.load(handle)
        except (OSError, ValueError):
            metadata = {}

    return {
        "path": path,
        "run_id": metadata.get("run_id", os.path.basename(run_root)),
        "scenario": metadata.get("scenario", "?"),
        "count": metadata.get("count", ""),
        "isolate": metadata.get("isolate", ""),
        "renderer": metadata.get("renderer", ""),
        "frames": len(frames),
        "span_s": (max(times) - min(times)) if times else 0.0,
        "mean_ms": statistics.mean(frames),
        "median_ms": statistics.median(frames),
        "p95_ms": percentile(frames, 95),
        "p99_ms": percentile(frames, 99),
        "gpu_ms": statistics.mean(gpu) if gpu else float("nan"),
        "drift_ms": drift,
        "present_mode": dominant,
        "present_mode_purity": dominant_count / len(rows),
        "dropped": sum(1 for row in rows if row.get("Dropped") == "1"),
    }


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("root")
    parser.add_argument("--arm-depth", type=int, default=4,
                        help="path component (from the end) naming the arm")
    parser.add_argument("--csv", default=None)
    args = parser.parse_args(argv)

    captures = []
    for path in sorted(glob.glob(os.path.join(args.root, "**", "presentmon.csv"),
                                 recursive=True)):
        record = load(path)
        if not record:
            print("skipped (too few frames): %s" % path, file=sys.stderr)
            continue
        parts = os.path.normpath(path).split(os.sep)
        label = parts[-args.arm_depth] if len(parts) >= args.arm_depth else "?"
        record["arm"] = label.rsplit("_r", 1)[0] if "_r" in label else label
        record["repeat"] = label.rsplit("_r", 1)[1] if "_r" in label else ""
        captures.append(record)

    if not captures:
        print("no PresentMon captures found under %s" % args.root, file=sys.stderr)
        return 1

    print("%-8s %-3s %-14s %-27s %7s %7s %7s %7s %7s %6s" % (
        "arm", "rep", "scenario", "present mode", "frames", "mean", "median",
        "drift", "gpuAct", "drop%"))
    for record in captures:
        print("%-8s %-3s %-14s %-27s %7d %7.3f %7.3f %+7.2f %7.2f %5.1f%%" % (
            record["arm"], record["repeat"], record["scenario"],
            record["present_mode"], record["frames"], record["mean_ms"],
            record["median_ms"], record["drift_ms"], record["gpu_ms"],
            100.0 * record["dropped"] / record["frames"]))

    groups: dict[tuple, list[dict]] = collections.defaultdict(list)
    for record in captures:
        groups[(record["scenario"], record["present_mode"], record["arm"])].append(record)

    print("\n-- grouped by scenario and present mode (never across modes) --")
    print("%-14s %-27s %-8s %5s %8s %8s %8s %8s" % (
        "scenario", "present mode", "arm", "runs", "mean", "sd", "median", "drift"))
    for key in sorted(groups):
        means = [record["mean_ms"] for record in groups[key]]
        drifts = [record["drift_ms"] for record in groups[key]
                  if record["drift_ms"] == record["drift_ms"]]
        print("%-14s %-27s %-8s %5d %8.3f %8.3f %8.3f %+8.2f   %s" % (
            key[0], key[1], key[2], len(means), statistics.mean(means),
            statistics.stdev(means) if len(means) > 1 else 0.0,
            statistics.median(means),
            statistics.mean(drifts) if drifts else float("nan"),
            ", ".join("%.2f" % value for value in means)))

    print("\n-- arm deltas within one scenario and present mode --")
    by_cell: dict[tuple, dict[str, list[float]]] = collections.defaultdict(dict)
    for (scenario, mode, arm), records in groups.items():
        by_cell[(scenario, mode)][arm] = [record["mean_ms"] for record in records]
    for cell in sorted(by_cell):
        arms = by_cell[cell]
        if len(arms) < 2:
            continue
        baseline = "before" if "before" in arms else sorted(arms)[0]
        base_mean = statistics.mean(arms[baseline])
        for arm in sorted(arms):
            if arm == baseline:
                continue
            arm_mean = statistics.mean(arms[arm])
            print("%-14s %-27s %s -> %s: %.3f -> %.3f ms  delta=%+.3f ms (%+.1f%%)  "
                  "fps %.1f -> %.1f" % (
                      cell[0], cell[1], baseline, arm, base_mean, arm_mean,
                      arm_mean - base_mean, 100.0 * (arm_mean - base_mean) / base_mean,
                      1000.0 / base_mean, 1000.0 / arm_mean))

    if args.csv:
        fields = ["arm", "repeat", "run_id", "scenario", "count", "renderer",
                  "isolate", "present_mode", "present_mode_purity", "frames",
                  "span_s", "mean_ms", "median_ms", "p95_ms", "p99_ms",
                  "drift_ms", "gpu_ms", "dropped", "path"]
        with open(args.csv, "w", newline="", encoding="utf-8") as handle:
            writer = csv.DictWriter(handle, fieldnames=fields, extrasaction="ignore")
            writer.writeheader()
            for record in captures:
                writer.writerow(record)
        print("\nwrote %s" % args.csv)
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
