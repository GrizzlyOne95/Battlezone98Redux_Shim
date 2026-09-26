# Control smoothing

## Summary

Every frame, `UserProcess::Execute` eases the player's steer, pitch, throttle and
strafe controls toward the value the input asks for, rather than applying it
directly. On mouse aim that is felt as drag. BZ2 exposes the same behaviour as
**Control Smoothing: On/Off** (`options.play.smoothing`); BZ1 only ever shipped
"On".

Redux already contains the "Off" path. It is gated by a flag that only the iOS
platform sets. OpenShim can set it on PC; it is opt-in.

Raw mouse input (`Docs/raw-mouse-input.md`) is independent: it changes how
mouse movement is read, not this filter, so it does not remove the drag.

## How the stock path works

Addresses are from the GOG 2.2.301 image (`battlezone98redux.exe`, SHA256
`8D71F56C…3377413`, image base `0x00400000`).

| Address | Role |
| --- | --- |
| `0x00623B20` | `giddi_read_channels`: mouse deltas → clamped virtual-stick position (±0x10000) and rate. |
| `0x0060AB..`–`0x0060B5..` | `UserProcess::Execute` steer/pitch/throttle/strafe update. |
| `0x009198F4` | `int` smoothing-bypass flag. 0 on PC. |
| `0x004344B0` | `SetPlatform(int)`: 0 pc, 1 osx, 2 ios. Writes the flag: 1 for ios, 0 otherwise (`0x004344D7`). |
| `0x00618D02` | Window init calls `SetPlatform`. |
| `0x007D5536` | The `-platform` command-line parser calls `SetPlatform`. |

With the flag clear, each control is filtered (1.5 decompile, confirmed against
the Redux disassembly):

```c
ctrl.steer += (target - ctrl.steer) * dt * 5.0f;   // analog / mouse
ctrl.steer += (target - ctrl.steer) * dt * 1.0f;   // keyboard left/right
```

Pitch uses the same rates; throttle and strafe use 3.0 for analog. The flag is
tested at ten sites (`0x60AEC5`, `0x60AF4F`, `0x60AFBC`, `0x60B1E8`, `0x60B280`,
`0x60B318`, `0x60B3A1`, `0x60B412`, `0x60B49B`, `0x60B50C`), each of which
assigns `ctrl = target` instead when it is set.

Launching as `-platform ios` is not a workaround: `SetPlatform(2)` also changes
UI/FOV globals (`0x00492DC0`) and `0x00915568`.

## What OpenShim changes

The `Disable Control Smoothing` patch rewrites the whole else-branch instruction
in `SetPlatform`:

```
0x004344D7  C7 05 F4 98 91 00 00 00 00 00   mov dword [0x009198F4], 0   ; stock
            C7 05 F4 98 91 00 01 00 00 00   mov dword [0x009198F4], 1   ; patched
```

Every call to `SetPlatform` then leaves the flag set, whichever runs first
relative to OpenShim's patch thread. The site is found by a unique pattern over
the function prologue, both platform branches and the literal flag address; a
miss or a guard mismatch skips the patch and leaves stock smoothing.

Like BZ2's option it is global: keyboard steer and throttle snap to full
instead of ramping, and joystick axes are unfiltered too.

## Configuration

`[General] DisableControlSmoothing` in `openshim.ini`, boolean, default OFF,
restart required. Exposed as **Unsmoothed Controls** on the OpenShim Settings
page. Env aliases: `OPENSHIM_DISABLE_CONTROL_SMOOTHING`,
`BZR_DISABLE_CONTROL_SMOOTHING`.

The smoothed value is the local player's own control input, so the setting is
not multiplayer-gated, matching BZ2 where it is a per-player option.

## Open questions for live testing

- `giddi_read_channels` only samples when at least 1/60 s has accumulated
  (`comiss` against `0.016666` at `0x00623C0F`). The smoothing hides that; with
  it off, turning may step visibly above 60 fps. Unverified.
- Confirm `[OK] Disable Control Smoothing` in `openshim.log` and that aim no
  longer lags, with and without `RawMouseInput`.
