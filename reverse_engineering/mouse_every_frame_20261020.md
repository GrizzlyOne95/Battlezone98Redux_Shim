# Per-frame mouse look (2026-10-20)

Branch `agent/mouse-every-frame`, stacked on `agent/precise-timestep` (PR #525).
Setting: `[Experimental] MouseEveryFrame = 1`, env `OPENSHIM_MOUSE_EVERY_FRAME=1`,
or the options menu row **Per-Frame Mouse**. Default off. Restart required.

## Summary

- **Stock Redux applies mouse movement in 1/60 s batches.** The mouse reader
  adds each frame's sim step to an accumulator. It writes new steer and pitch
  values only once that accumulator reaches 0.016666 s. Between batches the
  values stay where they were, so mouse aim updates at about 60 Hz at any frame
  rate. At 144 fps a batch closes every third frame.
- **The patch makes the batch one frame long in single player.** Network games
  and paused frames keep the stock batch.
- **Sensitivity should not change.** Steer reads a per-second rate and pitch
  reads an accumulated position (see below). The one exception is raw-input
  acceleration, covered under *Expected effects*.
- **Not yet felt by a person.** The automated runs below prove the patch
  installs and combat runs normally. They were unfocused, so the reader never
  ran. Per-frame bucket closes and the feel of aim both still need a
  physical-console test (see the end).

## What the engine does (GOG Redux 2.2.301)

The function is the mouse `giddi_read_channels` at 0x00623B20. It is reached
only through the mouse driver table (0x008EC6FC). BZ 1.5's
`giddi_read_channels` (0x004BDDB7) is the same code.
`NextInputs` calls it once per frame for every enabled input device.

1. **Focus check.** If `GetActiveWindow()` is not the game window, the
   accumulator is cleared and nothing else happens.
2. **Accumulate the step.** `call TimeStep (0x00822D60)` at 0x00623BF2, then
   `accum (0x02A17470) += step`.
3. **The gate.** `movss xmm0,[0x008A24F4]` (0.016666f) at 0x00623C0F, then
   `comiss xmm0,[accum]; jbe apply`. Below the threshold the function returns
   at once and the device's channel block is left unchanged.
4. **On apply** (one batch):
   - **Scale.** The raw deltas gathered since the last batch are multiplied by
     the profile sensitivity `DELTA_SCALE_FACTOR[index]`.
   - **Raw-input acceleration.** With raw input on (0x00918424), it also
     multiplies by `(speed + 128) / 256`, where
     `speed = |delta| / accum` in counts per second. Above 384 counts/s the
     factor is 2.
   - **Outputs.** It writes four channels:
     - `x += dx` and `y += dy`: the position channels, clamped to ±0x10000;
     - `dx / accum` and `dy / accum`: the rate channels, per second.
   - **Reset.** It recentres the cursor (0x004350E0) and clears the deltas and
     the accumulator.

**How the channels are consumed.** Stock `input.map`:

| control | source | kind |
|---|---|---|
| `steer` | `mouse HorizVel` | rate (per second) |
| `pitch` | `mouse VertPos` | accumulated position |
| `cmd_x` / `cmd_y` (overview cursor) | `HorizPos` / `VertPos` | position |
| `menu_pos` | `VertVel` | rate |

- `NextInputs` maps each source into its sink every frame. Mouse sources take
  the non-simulated path, `current = scale * *from`.
- `UserProcess::Execute` then eases steer and pitch toward their targets,
  `cur += (target - cur) * dt * 5`. `DisableControlSmoothing` turns that easing
  off.

**What this means for sensitivity:**

- **Rate (steer).** The rate is per second. Stock holds one batch's rate for
  the next three frames; per-frame updates each frame's own rate. The integral
  over time is the same.
- **Position (pitch).** Position is a running sum of deltas. Summing per frame
  instead of per batch reaches the same total. Truncation is negligible:
  deltas are multiplied by the sensitivity factor before any integer
  conversion.

**Not related.** 0x006A3490 also compares an accumulator against 0.016666. It
is a 60 Hz team/AI bookkeeping tick, not mouse input. It shares the constant
0x008A24F4, which is why the patch never writes that constant.

## The patch

`src/patches/mouse_every_frame.cpp`, resolves in `scripts/patches.json`. All
four resolves share one signature. A whole-image scan on 2026-10-20 found a
single match.

| resolve | what | fallback |
|---|---|---|
| `MouseReadChannels::TimeStepCall` | the `call TimeStep` in the reader | 0x00623BF2 |
| `MouseReadChannels::BucketThreshold` | code address of the gate's m32 operand | 0x00623C13 |
| `MouseReadChannels::Accumulator` | the accumulator (diagnostics only) | 0x02A17470 |
| `TimeStep` | the float step getter | 0x00822D60 |

**What it does:**

1. **Repoints the gate.** The `movss` operand now names a shim-owned float
   instead of the shared constant.
2. **Wraps the TimeStep call.** The wrapper sets that float just before the
   compare:
   - in single player with a positive step, it is 0.0001 s, below any real
     step, so the batch closes every frame;
   - in network games (`IsNetGameFlag`), and while the step is 0, it is the
     stock 0.016666.

   Zero would divide by a zero accumulator while paused, so the floor is
   positive.

**Fail-closed checks.** The patch stands down when any of these fails:
- every address resolves;
- the call targets `TimeStep`;
- the operand belongs to `movss xmm0,[m32]` (F3 0F 10 05);
- that operand names a readable float equal to 0.016666f.

The call is redirected first. While the operand is unpatched the wrapper only
returns the step, so a failed operand write leaves stock behaviour.

**Diagnostics.** Every 3000 reads (at most 20 lines), `openshim.log` gets:

```
[MouseEveryFrame] last N reads: P per-frame threshold, C with the bucket already closed
```

"Bucket already closed" means the accumulator was zero on entry, so the
previous read applied. With the patch active it should equal N. Stock at
144 fps would give about N/3.

## Interaction with other input settings

- **`DisableControlSmoothing` (Unsmoothed Controls)** rewrites one immediate in
  `SetPlatform` (0x004344D7). The flag it sets is read in
  `UserProcess::Execute`, downstream of the mouse read. The patched bytes do
  not overlap (0x00623BF3–F6 and 0x00623C13–16).
  - **Smoothing on (default):** the `dt * 5` easing (about a 200 ms time
    constant) already smooths most of the 60 Hz staircase, so the gain is
    small.
  - **Smoothing off:** the staircase reaches the screen directly. That is where
    per-frame mouse should matter most.
  - Both combinations are expected to work; see *Validation*.
- **`RawMouseInput`** reads its three gates (0x00618E82, 0x00619717, 0x00623C39)
  and hooks the raw packet handler 0x004357D0. 0x00623C39 is the raw-input
  test inside this same function, after the gate. It is only read, never
  written, and none of its bytes overlap.
- **`PreciseTimestep`** changes the step value the accumulator sums, not the
  call site. The two are independent.
- **`OPENSHIM_NEVER_CAPTURE_MOUSE`** (harness default) skips the recentre. The
  read path still runs.

## Expected effects and risks

- **Aim latency and cadence.** Mouse steer and pitch can change every frame
  instead of every 16.7 ms. Average added latency from the batch drops from
  about 8 ms to under one frame.
- **Low-poll mice at very high fps.** A 125 Hz mouse at 300 fps has no new
  movement on most frames.
  - Steer then alternates between 0 and a larger rate (stock instead averaged
    over a batch).
  - With smoothing on, the easing hides this. With smoothing off it may read
    as jitter. 1000 Hz mice are not affected.
  - This is the main feel question for the console test.
- **Raw-input acceleration** is linear in per-frame speed below 384 counts/s.
  When per-frame counts are uneven, the sum of squares is slightly higher than
  with batching, so accelerated raw mouse may feel marginally faster. The
  non-raw path has no acceleration and is unaffected.
- **Cursor recentre (`SetCursorPos`)** now runs every frame instead of at
  60 Hz. That is one cheap call per frame.

## Validation

- **Checks run:**
  - `scripts/run_ini_tests.ps1`;
  - CTest `-A Win32` (6/6): `patch_registration_tests`,
    `patch_config_parse_tests`, `resolve_table_tests`, `shared_bzr_docs_check`,
    `env_switch_table_tests`, `openshim_env_mapping_tests`;
  - a Release Win32 build of `BZROpenShim`, `BZLoader` and `Plugin_OpenShim`
    (no warnings in the new file).
- **Live run:** see the next section.

### Live run

**Setup.** GOG Redux 2.2.301 with the Release build deployed. The run used
`lcbench.bzn` through `BZRHarness.ps1`, under the launch lock, windowed, with
the harness defaults `OPENSHIM_NEVER_ACTIVATE=1` and
`OPENSHIM_NEVER_CAPTURE_MOUSE=1`, and with `OPENSHIM_MOUSE_EVERY_FRAME=1`. The
installed `openshim.ini` has Unsmoothed Controls on, so both runs also patched
`DisableControlSmoothing`.

**Results (two runs, 2026-10-20).**

- **Run 1.**
  - `[OK] Disable Control Smoothing wrote 10 bytes to 0x004344D7`.
  - `[MouseEveryFrame] enabled: bucket compare 0x00623C0F -> shim threshold`.
  - `MouseReadChannels::TimeStepCall`, `BucketThreshold` and `Accumulator`
    were each a single scan match, and each agreed with its fallback.
  - `TimeStep` scanned 0 matches and used its fallback. Its `rel32_target`
    offset pointed at the rel32 rather than at the `E8`.
  - The benchmark reached `benchmark-end` after 30 s and exited through
    `Stop-BZRGame`.
- **Run 2,** after fixing that offset to 0:
  - `TimeStep matches=1 scan=0x00822D60 agree=yes`;
  - the patch was enabled again;
  - `benchmark-end` after 30 s.
- **Both runs:** no stand-down line and no new errors in `openshim.log`.

**What this proves.** The patch installs next to `DisableControlSmoothing` and
`PreciseTimestep`, and combat runs normally with it in place.

**What it does not prove.** Because the harness never activates the window,
`GetActiveWindow()` never matches. The reader therefore returns at its focus
check before reaching the TimeStep call, so these runs logged no
`[MouseEveryFrame] last N reads` lines. Proving per-frame bucket closes needs a
focused run (`BZR_ALLOW_FOREGROUND_LAUNCH=1`, `OPENSHIM_NEVER_ACTIVATE=0`). That
run is part of the console test below.

## Still needed: physical-console feel test

Run this at the physical console with a real mouse and a high-refresh display
(144 Hz or more, VSync off or a high cap), in single player:

1. Pick one mission, for example a free-roam instant action map. Turn and aim
   at distant targets with `MouseEveryFrame = 0`, then with `1`.
2. Repeat with **Unsmoothed Controls** on. This is where the difference should
   be clearest.
3. Watch for:
   - **Responsiveness:** fine tracking feels more direct.
   - **Sensitivity:** the same mouse distance turns the same amount. Measure a
     180° turn by eye in both arms.
   - **Jitter at low mouse polling rates** (125/250 Hz) with smoothing off.
   - **Raw Mouse Input on:** acceleration feels the same.
4. After the `1` arm, check `logs\openshim.log` for the
   `[MouseEveryFrame] last N reads` lines. Expect P = N and
   "bucket already closed" close to N. Stock at 144 fps gives about N/3.
5. Join a multiplayer game with the setting on. Feel should match stock, and
   the diagnostic lines logged during the net game should show 0 per-frame
   reads.
