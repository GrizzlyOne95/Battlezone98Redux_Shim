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
Both are explained in [Mid-mission spike causes](#mid-mission-spike-causes)
below. The 114 ms frame is a mission-script spawn, not mission end.

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

## Precise timestep (branch `agent/precise-timestep`)

Added on 2026-10-20, stacked on the telemetry above.

### What the step drives

These findings come from Ghidra xrefs on the GOG exe, plus 1.5 source where Redux functions were not found.

- **Only one path reads the float step.** Every consumer reads 0x00946790 through the getter 0x00822D60, which has about 80 callers. They include:
  - the sim entry 0x00618060;
  - mouse input 0x00623B20;
  - UserProcess and AI;
  - physics, weapons and render clusters.

  Nothing outside SetLoopTimes reads the integer copies 0x00946794 and 0x0094679C. 1/step (0x02CC1B34) is written but never read.
- **Game time is separate.** The integer game clock (0x02CC1B28, getter 0x00822D90, 15 callers: timers and net) accumulates the integer dt inside SetLoopTimes. A float-step override therefore cannot desync game time or networking.
- **Motion integrates the step directly** (1.5 source, medium confidence):
  - HoverCraft uses explicit Euler, `pos += vel * dt`;
  - friction is capped by `1/dt`;
  - there are no `dt²` terms.

  A ±1 ms step error at 144 fps moves a craft about 15% too far or too short on that frame. The cockpit camera copies the craft matrix, so the error reaches the screen unfiltered.
- **Mouse aim is bucketed** (high confidence, Redux 0x00623B20, the same as 1.5 `giddi_read_channels`).
  - Mouse deltas are applied only once the summed step reaches 1/60 s.
  - The rate output is `delta / accumulated step`.
  - At 144 fps a bucket closes after 3 frames of 6/7/7 ms. Mouse response is therefore quantised to about 60 Hz at any frame rate.
  - A precise step only makes bucket lengths exact. **Removing the 60 Hz mouse bucket is a separate patch.** It is the bigger aim-responsiveness lever at high refresh.
- **Stick steering and pitch** pass through a dt-dependent low-pass, `s += (in - s) * dt * 5` (1.5 source). Step jitter adds a small wobble to it.

### The hook

`[Fixes] PreciseTimestep` (default ON; `= 0` or `OPENSHIM_DISABLE_PRECISE_TIMESTEP=1` turns it off) redirects the frame-loop call to SetLoopTimes (0x006182F6, resolve `SetLoopTimes::FrameCall`) through a wrapper.

- **What it does.** After the real function runs, the wrapper replaces the three float globals (step, unclamped step and inverse) with the QPC interval between consecutive frame-loop calls.
- **When it keeps the engine value:**
  - in network games (it is a SinglePlayer-tier entry in the multiplayer gate registry, and the wrapper also checks the engine's net-game byte every frame);
  - when dt is 0 (paused);
  - at the 200 ms clamp;
  - when the two clocks disagree by more than 1.5 ms.
- **Drift.** A small feedback term, 10% of the running difference capped at 0.25 ms per frame, keeps Σstep tracking the integer clock.
- **Telemetry.** Frame records grew to 32 bytes: raw integer ms, float step and a "precise" flag. The analyzer prints step-vs-real error, step jitter and drift, and still reads old 24-byte captures.

### A/B, lcbench combat 40, 1920x1080 windowed, over RDP

| run | fps | step error vs render interval, p50 (relative) | p99 | precise frames | drift over about 46 s |
|---|---|---|---|---|---|
| r1 off | 169 | 0.43 ms (7.7%) | 1.88 ms | 0% | −127 ms |
| r1–r4 off, RDP-throttled | 48–49 | 0.50–0.52 ms (2.8–2.9%) | 2.5–2.6 ms | 0% | −8 to −109 ms |
| r1–r4 on, RDP-throttled | 48–49 | 0.39–0.47 ms (2.3–2.7%) | 2.5–3.2 ms | 98.9–99.4% | −2 to −147 ms |

**Reading it:**
- **The hook works.**
  - It is active on 99% of frames; the rest are load-tail and spike frames.
  - Game time does not drift.
  - Combat ran normally in all four "on" arms.
- **Over RDP the gain is small** (relative error p50 2.9% → 2.3%). The RDP compositor makes frames alternate about 8/31 ms. The remaining error is the phase difference between the SetLoopTimes and renderOneFrame boundaries, which no step fix removes.
- **The case the hook targets was not captured with the hook on.** Only the r1 "off" run happened to escape the RDP throttle, at 169 fps. There the stock step was off by a median 7.7% per frame, and by up to 35% at p99. That high-refresh condition still needs an "on" run at the physical console, together with the flip-model A/B (PR #524).

### Default-on smoke run

A default-on run with no env override, lcbench combat 40 unthrottled, gave these numbers:
- 160 fps;
- 99.0% precise frames;
- step error p50 2.9%, against 7.7% for the stock r1 "off" run at 169 fps;
- step jitter 0.29 ms, against 1.0 ms stock;
- drift −72 ms over 46 s.

That build resolved `SetLoopTimes` through its fallback address, because the `rel32_target` offset pointed one byte past the `E8`. The offset is now 13, which is the call opcode.

### Next

1. Physical console, 144 Hz or uncapped: repeat the lcbench off/on rounds (off = `OPENSHIM_DISABLE_PRECISE_TIMESTEP=1`), then look at the step error line and judge motion by eye.
2. A separate experiment that removes the 60 Hz mouse bucket in 0x00623B20 (per-frame mouse at high refresh). This is the likelier aim win. Prototyped as `[Experimental] MouseEveryFrame`; see `mouse_every_frame_20261020.md`.

## Recommended next steps

1. Repeat one lcbench and one CR weather pass **at the physical console**,
   fullscreen and windowed. If the short/long alternation disappears, the
   pacing problem was RDP only. If it stays, it is the present model.
2. Then implement the flip-model swapchain (`DXGI_SWAP_EFFECT_FLIP_DISCARD`
   plus a waitable object) behind a setting, and A/B it with this telemetry.
   The pacing line is the metric.
3. Use the sampled worst-hitch list to chase the rare >40 ms game-side spikes
   (a sound path, and one long engine chain at mission end). Done; see
   [Mid-mission spike causes](#mid-mission-spike-causes). The "mission end"
   chain was a mid-mission spawn.

## Mid-mission spike causes

Branch `agent/frame-spike-causes`, stacked on `agent/precise-timestep`.

### Runs

The deployed DLL was the same for every run. Each run used 1920x1080 windowed over RDP and frame telemetry. The sampled runs also used the 1 kHz CPU sampler at depth 48.

| run | length | post-load median | post-load frames ≥ 2× median or 40 ms |
|---|---|---|---|
| stock misn18, sampled | 420 s | 17.0 ms | +148.3 s, +172.5 s, +274.6 s, +402.5 s, plus RDP Present slot misses |
| stock misn18, telemetry only | 420 s | 18.6 ms | the same four times, plus misses |
| CR crsetup, weather Severe, sampled | 300 s | 14.1 ms | +138.6 s, +269.2 s, plus one miss |

"Post-load" means from 8 s after the last frame over 1 s within the first 90 s, and never earlier than +12 s. Frames are then grouped by the call chain that holds most of their main-thread samples. The sampler inflates syscall-heavy frames: the spawn frame below was 114 ms sampled and 49 ms unsampled in the first capture. So costs are quoted from the telemetry-only run where possible.

In crsetup, the load tail extends to about +15 s:
- texture `prepare` under the mission-start loop 0x00617110;
- the first ever music Play, at 249 ms, mostly in DirectSound/audio-service ALPC.

Both are load-time costs and are left out.

### Ranked causes

1. **Music track change.** This is the most frequent, and it is now fixed in part.
   - **How often:** once per track, about every 126–130 s in both missions. The times repeat run to run: misn18 at +148, +274 and +402 s.
   - **Cost:** the frame is 48–49 ms unsampled in misn18 and 48–70 ms sampled in CR, against a 17–19 ms median.
   - **Chain:** the per-frame music update 0x0043A170 → 0x00437B00 notices the end of the track, stops it (0x00437A70, which frees the cached file) and calls track start 0x004378F0. All of it runs on the main thread.
   - **Main-thread work, 7–15 ms of the frame, broken down:**
     - **Opening the file, 0–7 ms.** The size probe 0x00481A60 → 0x00481A80 → `_fsopen` 0x00829150 sits in `ZwCreateFile`. It is near zero when the file is in cache. In CR it was 5–7 ms, because the tracks were cold.
     - **Reading the file, 1–3 ms.** 0x00481AF0 → 0x00481B80 reads the whole 1.5–3.7 MB `.ogg` into the resource cache.
     - **Constructor decode, 3–4 ms.** OggManager setup 0x0043F050 builds the streaming sound (0x0043EC90 → constructor 0x00416830). The constructor calls FillBufferWithSound 0x00416E10 and decodes a 3 s DirectSound buffer.
     - **Play decode, 2–3 ms.** OggManager::Play 0x0043F320 calls Reset 0x00416CF0, which does `ov_raw_seek` to 0 and zeroes every stream position. It then calls FillBufferWithSound again over the same 3 s.
   - **The constructor decode is never heard.** Every path that makes a track audible goes through Play (0x00437800, 0x004378F0, and 0x00437B00 → 0x0043F9E0 → 0x0043F320). Play rewinds and refills before the buffer starts.
   - **Fix:** `[Fixes] MusicSingleFill` (default ON; `OPENSHIM_DISABLE_MUSIC_SINGLE_FILL=1` turns it off). It replaces that one call at 0x004168E9, `E8 rel32` → `add esp,8; nop; nop`. The call is `__thiscall` with two stack arguments and its result is unused. The patch first checks that the call still targets FillBufferWithSound. Both addresses are named resolves in `scripts/patches.json`.
   - **A/B, same build, misn18, 300 s each, over RDP:**

     | arm | +148 s frame | +274 s frame | median |
     |---|---|---|---|
     | `OPENSHIM_DISABLE_MUSIC_SINGLE_FILL=1` (off), telemetry | 42.4 ms | 41.3 ms | 16.6 ms |
     | on, telemetry | 36.9 ms | 31.8 ms | 16.5 ms |
     | on, sampled | 37.4 ms | 38.2 ms | 16.3 ms |

     - In the sampled "on" run, no samples remain under the constructor 0x00416830, and the main-thread music samples per track start fall from 7–9 to 5.
     - Track changes still land every ~126 s (BZLogger `Starting Music Playback`), so each track streams through to its end.
     - Audibility was not checked by ear: there was no audio over RDP.
     - RDP rounds frames to ~33 ms slots, so the deltas are approximate.
   - **Not fixed: opening and reading the file.** These are the remaining cost; with cold files they are the larger part. Prefetching the next track on a worker thread would warm the OS cache and the on-access scan. The next index is deterministic: the current index + 1, skipping the excluded track, wrapping at the upper bound (0x008E75F0–0x008E7600). It is a follow-up because it needs the engine's music path resolution, and mods can override tracks.
2. **First spawn of an object class not yet loaded.** This is the most expensive single event, and it is rare.
   - **When:** misn18 +172.4 s, 111 ms plus 51 ms over two frames, unsampled.
   - **Chain:** 0x0045BF90 → the misn18 native mission script 0x005522E0 / 0x0054FE40 → BuildObject 0x005C8250 / 0x005C8380 / 0x005C82B0 → GameObjectClass load 0x004E1190 → the Ogre entity/mesh create 0x0067F480 (`%.*s.mesh`).
   - **What it loads:** the Ogre log shows `hvsav.mesh`, `hvsav.skeleton` and three 2048² DXT1 textures (`hvsav00_D/_S/_E.dds`, about 8 MB) at that second. In other words, the script spawns the first Scavenger of the mission.
   - **Where the samples are:** 45 of 81 samples are in `ZwReadFile`, reached through Ogre `FileStreamDataStream::read` → `std::istream::read` → the exe's streambuf underflow 0x00421520 → 0x00417E60 (`getc`) → `_filbuf`. In other words, the data is read in 4 KB CRT buffer refills. In the first capture `ZwCreateFile` via the Ogre FileSystemArchive open 0x006687B0 → 0x004220F0 → `_Fiopen` 0x00423150 also showed.
   - **How often:** about once per class per mission, so a handful per mission.
   - **No contained fix.** It would need either preloading every class a script might build, which is unknown in advance, or a larger-buffer streambuf for Ogre resource reads. The second might be worth measuring on its own.
3. **RDP Present slot misses.** Not game work.
   - **Where:** misn18 +252.5 s and +332.5 s, and CR +84.8 s; each 38–46 ms.
   - **What they are:** 73% `ZwDelayExecution` inside the DXGI Present sleep, with no game frame over 2 ms. A frame just misses a ~33 ms RDP slot and waits for the next. They need a physical-console run to judge.

One unsampled outlier is unexplained: misn18 telemetry +121.0 s, 56 ms. It did not recur in the sampled run.
