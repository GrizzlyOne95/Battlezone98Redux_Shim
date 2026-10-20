# Frame-hitch and address-space measurement — 2026-10-20

Branch `agent/hitch-va-telemetry`. These are the first runs of the frame-boundary
recorder and address-space reporter in `src/patches/perf_telemetry.cpp`
(`OPENSHIM_PERF_TELEMETRY=1`, also on whenever the native CPU sampler is on).
The analyzer is `reverse_engineering/analyze_frame_hitches.py`.

## Bottom line

1. **The 32-bit address space is not the limiter.** The largest free block
   stayed at 2044.8 MiB, unchanged, in every run (LAA is on). Commit peaked at
   about 710 MiB in lcbench combat and 657 MiB in misn18. Fragmentation never
   showed up either: the largest block never moved.
2. **CPU work per frame is small:** about 8 ms in lcbench combat with 40 tanks
   and about 5 ms in misn18. The main thread is not CPU-bound at 60 Hz.
3. **Every captured hitch is a Present wait, not game work.** In hitch frames
   93% of main-thread samples sit in `SleepEx` beneath
   `D3D11RenderWindowSwap::swapBuffers` → dxgi. Frames strictly alternate
   short/long, for example 5–8 ms then about 31 ms; the analyzer reports 97–98%
   "uneven pairs".
4. **That alternation is at least partly an artifact of this machine being
   driven over RDP.** The RDP compositor presents at about 30 Hz. True frame
   pacing, and any flip-model swapchain evaluation, need a run at the physical
   console. The numbers below are therefore valid for CPU and address space,
   but **not** for judging on-screen smoothness.

The rare large hitches have real game-side stacks and are worth a follow-up.
For example, one 114 ms frame at +172 s in misn18 was 70% inside one engine
call chain, and one 48 ms frame was in the sound path (0x004378F0 / 0x0043A170).

## Runs

| run | mode | frames | mean fps | p50 / p90 / p99 ms | pacing (median abs Δdt, uneven) | VA largest free | commit |
|---|---|---|---|---|---|---|---|
| lcbench combat 40, 1920x1080 windowed | telemetry | 2279 / 56.9 s | 40.1 | 26.3 / 32.0 / 34.4 | 22.6 ms, 97.8% | 2044.8 MiB | 406 → 710 MiB |
| lcbench combat 40 | sampled 1 kHz | — | — | — | — | — | — |
| stock misn18 (CR inactive), 1920x1080 windowed | sampled 1 kHz | 9113 / 173 s | 52.6 | 17.2 / 31.6 / 32.3 | 29.1 ms, 97.0% | 2044.8 MiB | 404 → 657 MiB |
| CR Mars weather Severe (crsetup harness), 1920x1080 windowed | sampled 1 kHz | 6859 / 131 s | 52.3 | 30.3 / 31.8 / 32.5 | 27.8 ms, 99.8% | 2044.8 MiB | 404 → 806 MiB |
| CR Mars weather Severe | telemetry | 6892 / 132 s | 52.0 | 30.4 / 31.8 / 32.5 | 27.7 ms, 99.8% | 2044.8 MiB | → 806 MiB |

In the lcbench sampled pass, 82% of hitch-frame samples were kernel waits and
the excess is about 26 ms per long frame in the same Present sleep.

## CR weather run

The first attempt used `misn18.bzn` with `crcampgn.ini` temporarily set to
`mapType = "mod"`. It did **not** activate CR: BZLogger has no
`UNSAFE ...\mods\3686673790` line, the stock native mission ran (AiProcess
Recycler/Factory), and exu never loaded. Use the instant-action `crsetup.bzn`,
which does activate CR. Its `crsetup.lua` runs the CR installer, so the test
copy's file was temporarily replaced by a harness that requires exu,
Environment and CRMarsWeather, forces level 5 (Severe) and calls Update every
tick. The original was restored byte-for-byte afterwards.

Result: BZLogger shows `[wxperf] harness start exu=true` and `force severe true`, and
exu parsed `cr_weather.particle.payload`.

- **Weather costs no stutter here.** In both passes every frame over 45 ms is
  in frames 0–17, the load and voice-over tail. After that no frame exceeded
  the 33 ms RDP cadence; the rolling detector flagged 0 hitches.
- **CPU per frame is about 5 ms.** Short frames are 5–6 ms, and the rest of
  each long frame is the same Present sleep.
- **Address space grows but has plenty of room.** Severe weather adds memory:
  commit reached 806 MiB, private usage 509 MiB, and the working set 478 MiB.
  The largest free block stayed at 2044.8 MiB.

Caveat: crsetup is a small instant-action map with little else going on. The
result says the weather systems themselves are cheap. It does not cover a full
Mars campaign mission with a base, AI and weather together.

## Harness bugs found on the way

- **`Win32_Process.Create` does not inherit the caller's environment.**
  `run_live_combat_benchmark.ps1` launched through WMI, so every
  `OPENSHIM_PROFILE_NATIVE_CPU*` variable it set was silently dropped. Earlier
  `-SampleCpu` lcbench runs were probably never sampled. Fixed by passing the
  environment through `Win32_ProcessStartup.EnvironmentVariables`.
- **A command-line mission is already in run state 5 on its first frame,** so
  the SetRunning seam never reports mission entry. The telemetry now treats the
  first frame in run state 5 as an entry.
- **The hitch reference was taken per 5 s window.** A step change in load made
  every frame of the next window a "hitch" (805 in lcbench). It is now a rolling
  median of the last 120 frames, refreshed every 15. The two telemetry rows
  above predate this fix; their hitch counts are inflated, but their frame-time
  and pacing figures are unaffected.

## Simulation rate (for the "BZCC has a lower tick rate" question)

Traced in Ghidra on the GOG exe, 2026-10-20.

**The loop.** 0x00618270 is the per-frame entry. It calls 0x00822AE0, the
Redux `SetLoopTimes`, and then the frame function 0x00618130. 0x00618130 runs
input, net execute, AI and the world sim tick (0x006175C0), then render prep
(0x00682540). Each of them is called once. There is no accumulator, no
fixed-step loop and no interpolation. **The simulation runs once per rendered
frame, and nothing waits for a tick.**

**The timestep (0x00822AE0):**
- **Clock.** It reads 0x00822E60, which is a `boost::posix_time` clock: the
  helper raises boost date_time's "could not convert calendar time to UTC time"
  error. That is wall-clock system time, converted to whole milliseconds.
- **Wait.** It calls `Sleep(1)` until that millisecond value changes, then
  takes `dt = now - prev` as an integer number of milliseconds. Multiplayer
  replaces this with a net-time path.
- **Clamp.** It copies the raw dt to 0x0094679C, clamps the working value to
  200 ms, and stores `dt * 0.001` as the float timestep at 0x00946790. The
  getter 0x00822D60 returns it, and 0x00618060 passes it to the sim.
- **No smoothing.** 1.5 averaged the last two frame times. Redux uses each
  frame's raw dt.
- `prev` only advances when dt is non-zero, so total game time never drifts.
  Only the per-frame step is quantised.

**What this means:**
- A low fixed tick, as described for BZCC, does not apply to BZR. The
  simulation already runs at the render rate.
- **The step is quantised to whole milliseconds and not smoothed** (high
  confidence). At 144 fps the true frame time of 6.94 ms becomes alternating
  6 and 7 ms steps, a ±7% per-frame velocity wobble. At 60 fps it is 16/17 ms
  (±3%).
- **Hypothesis, unmeasured:** this wobble may add to the "feels uneven"
  impression at high refresh rates. A possible fix is an OpenShim hook that
  writes a QPC-precise float step to 0x00946790. It would keep the integer
  millisecond accumulators unchanged, so game time and networking stay
  identical. Measure first: log the raw dt (0x0094679C) next to the
  frame QPC in the telemetry.
- The clock is system time, not a monotonic counter. A backward clock
  adjustment wraps the unsigned dt, and the 200 ms clamp turns it into one long
  step.
- The exe imports `timeBeginPeriod`, so `Sleep(1)` and system-time granularity
  are expected to be about 1 ms. This is not verified at runtime.

The judder captured in these runs is Present pacing, not the timestep.

## Recommended next steps

1. Repeat one lcbench and one CR weather pass **at the physical console**,
   fullscreen and windowed. If the short/long alternation disappears, the
   pacing problem was RDP only. If it stays, it is the present model.
2. Then implement the flip-model swapchain (`DXGI_SWAP_EFFECT_FLIP_DISCARD`
   plus a waitable object) behind a setting, and A/B it with this telemetry.
   The pacing line is the metric.
3. Use the sampled worst-hitch list to chase the rare >40 ms game-side spikes
   (a sound path, and one long engine chain at mission end).
