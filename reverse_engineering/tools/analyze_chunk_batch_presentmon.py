"""Summarises PresentMon captures from the chunk-batch reuse A/B.

The profiler perturbs frame time, so the profiler-enabled matrix cannot support
a frame-rate claim; these runs are profiler-disabled and measured externally by
PresentMon at the ETW level. Frame time is taken from msBetweenPresents, and GPU
work from msUntilRenderComplete where the capture provides it.

Percentiles are computed on the raw per-present samples rather than on
per-second aggregates, so a brief hitch is visible in p99 instead of being
averaged away.
"""

import csv
import statistics
import sys
from pathlib import Path


def load_frame_times(path: Path) -> tuple[list[float], list[float]]:
    frame_times: list[float] = []
    gpu_times: list[float] = []
    with path.open(newline="", encoding="utf-8", errors="replace") as handle:
        reader = csv.DictReader(handle)
        for row in reader:
            raw = row.get("msBetweenPresents") or row.get("MsBetweenPresents")
            if raw:
                try:
                    value = float(raw)
                except ValueError:
                    continue
                # PresentMon emits a 0 for the first present of a capture.
                if value > 0.0:
                    frame_times.append(value)
            gpu = (row.get("msUntilRenderComplete") or row.get("MsUntilRenderComplete")
                   or row.get("msGPUActive") or row.get("MsGPUActive"))
            if gpu:
                try:
                    gpu_value = float(gpu)
                except ValueError:
                    continue
                if gpu_value > 0.0:
                    gpu_times.append(gpu_value)
    return frame_times, gpu_times


def percentile(values: list[float], fraction: float) -> float:
    if not values:
        return float("nan")
    ordered = sorted(values)
    index = min(len(ordered) - 1, max(0, int(round(fraction * (len(ordered) - 1)))))
    return ordered[index]


def summarise(run_dir: Path) -> dict | None:
    csv_path = run_dir / "presentmon.csv"
    if not csv_path.exists():
        return None
    frame_times, gpu_times = load_frame_times(csv_path)
    if len(frame_times) < 30:
        return None
    return {
        "run": run_dir.name,
        "frames": len(frame_times),
        "fps": 1000.0 / statistics.mean(frame_times),
        "mean": statistics.mean(frame_times),
        "p50": percentile(frame_times, 0.50),
        "p95": percentile(frame_times, 0.95),
        "p99": percentile(frame_times, 0.99),
        "gpu_mean": statistics.mean(gpu_times) if gpu_times else float("nan"),
    }


def main() -> int:
    root = Path(sys.argv[1]) if len(sys.argv) > 1 else Path(
        "reverse_engineering/snapshots/chunk_pm")
    arms = {}
    for arm_dir in sorted(root.iterdir()):
        if not arm_dir.is_dir():
            continue
        for run_dir in sorted(arm_dir.rglob("*")):
            if not run_dir.is_dir():
                continue
            summary = summarise(run_dir)
            if summary:
                arms.setdefault(arm_dir.name, []).append(summary)

    if not arms:
        print(f"no PresentMon captures under {root}")
        return 1

    header = (f"{'arm':<10}{'run':<40}{'frames':>8}{'fps':>8}"
              f"{'mean':>8}{'p50':>8}{'p95':>8}{'p99':>8}{'gpuMean':>9}")
    print(header)
    print("-" * len(header))
    for arm, runs in arms.items():
        for run in runs:
            print(f"{arm:<10}{run['run']:<40}{run['frames']:>8d}{run['fps']:>8.1f}"
                  f"{run['mean']:>8.2f}{run['p50']:>8.2f}{run['p95']:>8.2f}"
                  f"{run['p99']:>8.2f}{run['gpu_mean']:>9.2f}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
