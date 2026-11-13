"""Summarises generic chunk batch rebuild rates from run_chunk_batch_reuse_matrix logs.

Per-frame rates are derived, not assumed: the batch telemetry and the profiler's
fps line are both emitted on a one-second interval, so each `[CHUNKBATCH] reuse`
record is paired with the `[OgreProfile] fps=` record closest to it in time and
the counters are divided by the frames that actually rendered in that window.
Windows without a usable fps pairing are dropped rather than guessed at.
"""

import re
import statistics
import sys
from pathlib import Path

REUSE_RE = re.compile(
    r"\[CHUNKBATCH\] reuse windowMs=(?P<window>\d+) requests=(?P<requests>\d+) "
    r"rebuilds=(?P<rebuilds>\d+) reused=(?P<reused>\d+) emptySkips=(?P<empty>\d+) "
    r"dedupPct=(?P<dedup>[\d.]+) verts=(?P<verts>\d+) indices=(?P<indices>\d+) "
    r"rebuildMs=(?P<ms>[\d.]+) maxRebuildMs=(?P<maxms>[\d.]+) mode=(?P<mode>\w[\w-]*)")
FPS_RE = re.compile(r"\[OgreProfile\] fps=(?P<fps>[\d.]+) frameMean=(?P<mean>[\d.]+) "
                    r"p50=(?P<p50>[\d.]+) p95=(?P<p95>[\d.]+) p99=(?P<p99>[\d.]+)")
TIME_RE = re.compile(r"^\[(?P<ts>[^\]]+)\]")
SCHEME_RE = re.compile(r"\[CHUNKBATCH\] reuse   scheme=(?P<name>\S+) "
                       r"requests=(?P<requests>\d+) rebuilds=(?P<rebuilds>\d+)")
SUBMIT_RE = re.compile(r"\[OgreProfile\]\[Render\] OgreSubmit=(?P<submit>[\d.]+)/f .*?"
                       r"Draw=(?P<draw>[\d.]+)/f .*?DrawIndexed=(?P<drawIndexed>[\d.]+)/f")


def parse_seconds(line: str) -> float | None:
    match = TIME_RE.match(line)
    if not match:
        return None
    text = match.group("ts")
    try:
        hh, mm, rest = text.split("T")[1].split(":")
        return int(hh) * 3600 + int(mm) * 60 + float(rest.rstrip("Z"))
    except (IndexError, ValueError):
        return None


def summarise(path: Path) -> dict | None:
    reuse_records: list[tuple[float, dict]] = []
    fps_records: list[tuple[float, dict]] = []
    schemes: dict[str, list[tuple[int, int]]] = {}
    submits: list[dict] = []

    for line in path.read_text(errors="replace").splitlines():
        seconds = parse_seconds(line)
        reuse = REUSE_RE.search(line)
        if reuse and seconds is not None:
            reuse_records.append((seconds, reuse.groupdict()))
            continue
        fps = FPS_RE.search(line)
        if fps and seconds is not None:
            fps_records.append((seconds, fps.groupdict()))
            continue
        scheme = SCHEME_RE.search(line)
        if scheme:
            schemes.setdefault(scheme.group("name"), []).append(
                (int(scheme.group("requests")), int(scheme.group("rebuilds"))))
            continue
        submit = SUBMIT_RE.search(line)
        if submit:
            submits.append(submit.groupdict())

    if not reuse_records or not fps_records:
        return None

    per_frame_requests: list[float] = []
    per_frame_rebuilds: list[float] = []
    mode = reuse_records[-1][1]["mode"]
    frame_means: list[float] = []
    p95s: list[float] = []
    p99s: list[float] = []

    for seconds, record in reuse_records:
        nearest = min(fps_records, key=lambda item: abs(item[0] - seconds))
        if abs(nearest[0] - seconds) > 1.5:
            continue
        fps = float(nearest[1]["fps"])
        if fps <= 1.0:
            continue
        per_frame_requests.append(int(record["requests"]) / fps)
        per_frame_rebuilds.append(int(record["rebuilds"]) / fps)
        frame_means.append(float(nearest[1]["mean"]))
        p95s.append(float(nearest[1]["p95"]))
        p99s.append(float(nearest[1]["p99"]))

    if not per_frame_rebuilds:
        return None

    total_rebuild_ms = sum(float(record["ms"]) for _, record in reuse_records)
    windows = len(reuse_records)

    return {
        "tag": path.stem,
        "mode": mode,
        "windows": windows,
        "requests_per_frame": statistics.mean(per_frame_requests),
        "rebuilds_per_frame": statistics.mean(per_frame_rebuilds),
        "rebuild_ms_per_s": total_rebuild_ms / max(windows, 1),
        "max_rebuild_ms": max(float(r["maxms"]) for _, r in reuse_records),
        "empty_skips": sum(int(r["empty"]) for _, r in reuse_records),
        "frame_mean": statistics.mean(frame_means) if frame_means else float("nan"),
        "p95": statistics.mean(p95s) if p95s else float("nan"),
        "p99": statistics.mean(p99s) if p99s else float("nan"),
        "submit_per_frame": (
            statistics.mean(float(s["submit"]) for s in submits) if submits else float("nan")),
        "draw_per_frame": (
            statistics.mean(float(s["draw"]) + float(s["drawIndexed"]) for s in submits)
            if submits else float("nan")),
        "schemes": {name: counts[-1] for name, counts in schemes.items()},
    }


def main() -> int:
    root = Path(sys.argv[1]) if len(sys.argv) > 1 else Path(
        "reverse_engineering/snapshots/chunk_batch_reuse")
    logs = sorted(root.rglob("*.log"))
    if not logs:
        print(f"no logs under {root}")
        return 1

    header = (f"{'run':<34}{'mode':<9}{'req/f':>7}{'rebuild/f':>11}"
              f"{'ms/s':>7}{'maxms':>7}{'empty':>7}{'frameMean':>11}{'p95':>8}{'p99':>8}"
              f"{'submit/f':>10}{'draw/f':>9}")
    print(header)
    print("-" * len(header))
    for log in logs:
        summary = summarise(log)
        if summary is None:
            print(f"{log.stem:<34}{'(no paired telemetry)':<9}")
            continue
        print(f"{summary['tag']:<34}{summary['mode']:<9}"
              f"{summary['requests_per_frame']:>7.2f}{summary['rebuilds_per_frame']:>11.2f}"
              f"{summary['rebuild_ms_per_s']:>7.2f}{summary['max_rebuild_ms']:>7.3f}"
              f"{summary['empty_skips']:>7d}{summary['frame_mean']:>11.3f}"
              f"{summary['p95']:>8.3f}{summary['p99']:>8.3f}"
              f"{summary['submit_per_frame']:>10.1f}{summary['draw_per_frame']:>9.1f}")

    print()
    for log in logs:
        summary = summarise(log)
        if summary and summary["schemes"]:
            parts = ", ".join(
                f"{name}={requests}req/{rebuilds}rb"
                for name, (requests, rebuilds) in sorted(summary["schemes"].items()))
            print(f"{summary['tag']:<34} {parts}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
