"""Frame-hitch attribution: join frame boundaries to CPU sampler stacks.

Inputs, all written by one game run into logs\\:

* openshim_frames_<label>_<pid>.bin   src/patches/perf_telemetry.cpp
* openshim_cpu_samples_<label>_<pid>.bin  src/patches/native_cpu_sampler.cpp
  (optional; without it only the frame-time picture is printed)
* openshim_va_<label>_<pid>.csv       (optional; address-space trend)

Both binaries stamp QueryPerformanceCounter on the same machine, so a sample
belongs to frame i when beginQpc_i <= sample.qpc < beginQpc_{i+1}. Only the
main thread's samples (the thread that called renderOneFrame) are binned.

What the hitch table means
--------------------------
A whole-capture profile cannot show what a 40 ms frame was doing, because a
few such frames are a rounding error among thousands of normal ones. Here the
main-thread samples are split into hitch frames and normal frames, and every
symbol gets an inclusive share in each group. The ranking is by the
difference: a function that is 3% of normal frames and 45% of hitch frames is
what the hitches are made of. "ms/hitch" converts the hitch-frame samples back
to time using the sampler's effective rate.

Timing caveat: the sampler suspends the main thread about a thousand times a
second, so frame times from a sampled run are inflated. Hitch *causes* are
still valid; hitch *rates and magnitudes* should come from a run with
OPENSHIM_PERF_TELEMETRY=1 and the sampler off.

Usage:
    python analyze_frame_hitches.py <frames.bin> [--samples cpu_samples.bin]
        [--functions functions.csv] [--va va.csv] [--all-states]
        [--threshold-ms N] [--top 25] [--per-hitch 10]
"""

from __future__ import annotations

import argparse
import bisect
import collections
import csv
import os
import statistics
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

FRAME_MAGIC = b"OSFRAME1"
FRAME_FLAG_HITCH = 1
RUN_STARTED = 5


class Frames:
    def __init__(self, path: str) -> None:
        with open(path, "rb") as handle:
            data = handle.read()
        if len(data) < 64 or data[:8] != FRAME_MAGIC:
            raise SystemExit(f"{path}: not a frame capture")
        (header_size, record_size, self.qpc_frequency, self.open_qpc,
         self.open_local_filetime, self.main_tid, self.process_id) = struct.unpack_from(
            "<IIQQQII", data, 8)
        count = (len(data) - header_size) // record_size
        self.begin: list[int] = []
        self.render_end: list[int] = []
        self.run_state: list[int] = []
        self.flags: list[int] = []
        for index in range(count):
            begin, render_end, run_state, flags = struct.unpack_from(
                "<QQiI", data, header_size + index * record_size)
            self.begin.append(begin)
            self.render_end.append(render_end)
            self.run_state.append(run_state)
            self.flags.append(flags)

    def __len__(self) -> int:
        return len(self.begin)

    def ms(self, ticks: int) -> float:
        return ticks * 1000.0 / self.qpc_frequency

    def interval_ms(self, index: int) -> float | None:
        """Frame index's duration; None for the last record (end unknown)."""
        if index + 1 >= len(self.begin):
            return None
        return self.ms(self.begin[index + 1] - self.begin[index])


def percentile(sorted_values: list[float], fraction: float) -> float:
    if not sorted_values:
        return 0.0
    rank = min(len(sorted_values) - 1, max(0, int(fraction * len(sorted_values))))
    return sorted_values[rank]


def classify(frames: Frames, selected: list[int], threshold_ms: float | None) -> set[int]:
    if threshold_ms is None:
        return {i for i in selected if frames.flags[i] & FRAME_FLAG_HITCH}
    return {i for i in selected if (frames.interval_ms(i) or 0.0) >= threshold_ms}


def print_frame_summary(frames: Frames, selected: list[int], hitches: set[int]) -> None:
    intervals = sorted(frames.interval_ms(i) for i in selected)
    seconds = sum(intervals) / 1000.0
    print("frames            : %d selected of %d recorded  (%.1f s, %.1f fps)" % (
        len(selected), len(frames), seconds, len(selected) / seconds if seconds else 0.0))
    print("frame time ms     : mean=%.2f p50=%.2f p90=%.2f p99=%.2f p99.9=%.2f max=%.1f" % (
        statistics.fmean(intervals), percentile(intervals, 0.50), percentile(intervals, 0.90),
        percentile(intervals, 0.99), percentile(intervals, 0.999), intervals[-1]))
    hitch_ms = sorted((frames.interval_ms(i) for i in hitches), reverse=True)
    print("hitches           : %d (%.2f/min)  time in hitches=%.1f%%" % (
        len(hitches), len(hitches) * 60.0 / seconds if seconds else 0.0,
        100.0 * sum(hitch_ms) / (seconds * 1000.0) if seconds else 0.0))
    buckets = collections.Counter()
    for value in hitch_ms:
        for edge in (8, 16, 33, 50, 100, 250, 1000):
            if value < edge:
                buckets["<%dms" % edge] += 1
                break
        else:
            buckets[">=1s"] += 1
    if buckets:
        print("hitch sizes       : %s" % "  ".join(
            "%s:%d" % (key, buckets[key]) for key in
            ("<8ms", "<16ms", "<33ms", "<50ms", "<100ms", "<250ms", "<1000ms", ">=1s")
            if buckets[key]))
    # Render share: renderOneFrame's own time inside the frame. A hitch whose
    # extra time is outside render is simulation/Lua/IO; inside is Ogre/driver.
    if hitches:
        render_share = [
            frames.ms(frames.render_end[i] - frames.begin[i]) / frames.interval_ms(i)
            for i in hitches if frames.render_end[i] > frames.begin[i]]
        normal = [i for i in selected if i not in hitches]
        normal_share = [
            frames.ms(frames.render_end[i] - frames.begin[i]) / frames.interval_ms(i)
            for i in normal[:: max(1, len(normal) // 5000)]
            if frames.render_end[i] > frames.begin[i]]
        if render_share and normal_share:
            print("renderOneFrame    : %.0f%% of hitch frames vs %.0f%% of normal frames" % (
                100.0 * statistics.fmean(render_share), 100.0 * statistics.fmean(normal_share)))


def attribute(frames: Frames, selected: list[int], hitches: set[int], samples_path: str,
              functions: str | None, top: int, per_hitch: int) -> None:
    from analyze_cpu_samples import Symbolizer, read_capture, WAIT_SYMBOLS

    capture = read_capture(samples_path)
    if capture.qpc_frequency != frames.qpc_frequency:
        raise SystemExit("frame and sample captures use different QPC frequencies")
    if capture.process_id != frames.process_id:
        print("warning: process ids differ (frames %d, samples %d)" % (
            frames.process_id, capture.process_id), file=sys.stderr)
    symbolizer = Symbolizer(capture, functions, "battlezone98redux.exe", False)
    selected_set = set(selected)

    groups: dict[str, collections.Counter[str]] = {
        "hitch": collections.Counter(), "normal": collections.Counter()}
    totals = collections.Counter()
    per_frame: dict[int, collections.Counter[str]] = collections.defaultdict(collections.Counter)
    per_frame_total = collections.Counter()
    waiting = collections.Counter()
    for tid, qpc, _flags, addresses in capture.samples:
        if tid != frames.main_tid:
            continue
        index = bisect.bisect_right(frames.begin, qpc) - 1
        if index < 0 or index not in selected_set:
            continue
        group = "hitch" if index in hitches else "normal"
        names = [symbolizer.symbol(address) for address in addresses]
        totals[group] += 1
        if any(token in names[0] for token in WAIT_SYMBOLS):
            waiting[group] += 1
        unique = set(names)
        groups[group].update(unique)
        if group == "hitch":
            per_frame[index].update(unique)
            per_frame_total[index] += 1

    if not totals["hitch"]:
        print("\nno main-thread samples fell inside hitch frames "
              "(sampler window, thread id or QPC mismatch?)")
        return
    hitch_frames_ms = sum(frames.interval_ms(i) for i in hitches)
    ms_per_sample = hitch_frames_ms / totals["hitch"]
    print("\nmain-thread samples: hitch=%d normal=%d  (%.2f ms/sample in hitch frames)" % (
        totals["hitch"], totals["normal"], ms_per_sample))
    print("waiting (kernel)   : hitch=%.1f%% normal=%.1f%%" % (
        100.0 * waiting["hitch"] / totals["hitch"],
        100.0 * waiting["normal"] / max(1, totals["normal"])))

    rows = []
    for name in set(groups["hitch"]) | set(groups["normal"]):
        hitch_share = groups["hitch"][name] / totals["hitch"]
        normal_share = groups["normal"][name] / max(1, totals["normal"])
        rows.append((hitch_share - normal_share, hitch_share, normal_share, name))
    rows.sort(reverse=True)
    print("\n-- over-represented in hitch frames (inclusive share) --")
    print("  %-62s %8s %8s %8s %9s" % ("symbol", "hitch%", "normal%", "excess", "ms/hitch"))
    for excess, hitch_share, normal_share, name in rows[:top]:
        print("  %-62s %7.1f%% %7.1f%% %+7.1f%% %9.2f" % (
            name[:62], 100 * hitch_share, 100 * normal_share, 100 * excess,
            hitch_share * totals["hitch"] * ms_per_sample / max(1, len(hitches))))

    if per_hitch:
        print("\n-- worst hitches, top excess symbols in each --")
        normal_shares = {name: groups["normal"][name] / max(1, totals["normal"])
                         for name in groups["hitch"]}
        worst = sorted(hitches, key=lambda i: -frames.interval_ms(i))[:per_hitch]
        for index in worst:
            count = per_frame_total[index]
            seconds_in = frames.ms(frames.begin[index] - frames.begin[selected[0]]) / 1000.0
            if not count:
                print("  %.1f ms at +%.1fs: no samples" % (frames.interval_ms(index), seconds_in))
                continue
            ranked = sorted(per_frame[index].items(),
                            key=lambda kv: -(kv[1] / count - normal_shares.get(kv[0], 0.0)))[:4]
            print("  %.1f ms at +%.1fs (%d samples): %s" % (
                frames.interval_ms(index), seconds_in, count,
                "; ".join("%s %.0f%%" % (name[:48], 100.0 * hits / count) for name, hits in ranked)))


def print_va(path: str) -> None:
    with open(path, newline="", encoding="utf-8") as handle:
        rows = list(csv.DictReader(handle))
    if not rows:
        return
    print("\n-- address space (%s) --" % os.path.basename(path))
    print("  %-23s %-14s %-10s %8s %9s %8s %8s %9s %9s" % (
        "time", "reason", "mission", "freeMiB", "largest", ">=16MiB", "commit", "private", "privUsage"))
    for row in rows:
        if row["reason"] == "periodic" and row is not rows[-1]:
            continue
        print("  %-23s %-14s %-10s %8.0f %9.1f %8s %8.0f %9.0f %9.0f" % (
            row["local_time"], row["reason"], row["mission"][:10], float(row["free_mib"]),
            float(row["largest_free_mib"]), row["free_ge_16mib"], float(row["committed_mib"]),
            float(row["private_mib"]), float(row["private_usage_mib"])))
    largest = [float(row["largest_free_mib"]) for row in rows]
    print("  periodic+transition rows=%d  largest free block: min=%.1f MiB max=%.1f MiB" % (
        len(rows), min(largest), max(largest)))


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("frames")
    parser.add_argument("--samples", default=None)
    parser.add_argument("--functions", default=None,
                        help="Ghidra inventory/functions.csv for the game module")
    parser.add_argument("--va", default=None)
    parser.add_argument("--all-states", action="store_true",
                        help="include shell/loading frames, not only RUN_STARTED")
    parser.add_argument("--skip-seconds", type=float, default=0.0,
                        help="drop this much from the start of the selection (load tail)")
    parser.add_argument("--threshold-ms", type=float, default=None,
                        help="fixed hitch threshold instead of the recorded flag")
    parser.add_argument("--top", type=int, default=25)
    parser.add_argument("--per-hitch", type=int, default=10)
    args = parser.parse_args(argv)

    frames = Frames(args.frames)
    selected = [i for i in range(len(frames) - 1)
                if args.all_states or frames.run_state[i] == RUN_STARTED]
    if selected and args.skip_seconds > 0:
        start = frames.begin[selected[0]] + int(args.skip_seconds * frames.qpc_frequency)
        selected = [i for i in selected if frames.begin[i] >= start]
    if not selected:
        print("no frames selected (no RUN_STARTED frames? try --all-states)", file=sys.stderr)
        return 1
    hitches = classify(frames, selected, args.threshold_ms)

    print("=== %s ===" % args.frames)
    print("process id        : %d  main thread=%d" % (frames.process_id, frames.main_tid))
    print_frame_summary(frames, selected, hitches)
    if args.samples:
        attribute(frames, selected, hitches, args.samples, args.functions, args.top, args.per_hitch)
    if args.va:
        print_va(args.va)
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
