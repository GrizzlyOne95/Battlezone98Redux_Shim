# Raw mouse input

## Summary

Battlezone 98 Redux already contains a complete Win32 raw-input mouse path. It
registers the mouse with `RegisterRawInputDevices`, handles `WM_INPUT`, decodes
`RAWMOUSE`, and feeds relative deltas into the same look accumulator and the
same sensitivity setting the ordinary mouse path uses. It never runs, because
the flag that gates it lives in zero-initialised `.data` and the only thing in
the shipping build that ever writes it is the `rawinput` command-line token.

OpenShim does not add a second implementation. It turns the stock one on, guards
the write, and fixes the one case the stock handler gets wrong.

## How the stock path works

Addresses are from the GOG 2.2.301 image (`battlezone98redux.exe`, image base
`0x00400000`). The Steam image has the same layout once SteamStub has decrypted
`.text`; it is only encrypted on disk, which is why the derivation below was done
against the GOG copy.

| Address | Role |
| --- | --- |
| `0x00918424` | `int g_RawInputEnabled` — the gate. Uninitialised `.data`, so 0 at launch. |
| `0x007D5282` | Command-line parser: `-rawinput` writes 1. |
| `0x007D52AF` | Command-line parser: `-norawinput` writes 0. |
| `0x00618E82` | Startup gate inside window init (`0x00618C10`, runs once). |
| `0x00618EC2` | `RegisterRawInputDevices({usagePage 1, usage 2, flags 0, hwnd 0})`. |
| `0x00619340` | WndProc. |
| `0x006194C0` | `WM_INPUT` case → `GetRawInputData` ×2 → `ProcessMouseRawInput`. |
| `0x00619717` | Mouse-message gate — skips the legacy path when raw is on. |
| `0x004357D0` | `ProcessMouseRawInput(RAWMOUSE*)`. |
| `0x00435400` | `ProcessMouseMessages(uMsg, wParam, lParam)` — the legacy path. |
| `0x02CEBCA0` / `0x02CEBCA4` | Look delta accumulators, X and Y. |
| `0x02CEBCA8` / `0x02CEBCAC` | Mouse button state / edge masks. |
| `0x00623AC0` | Look consumer — applies sensitivity, then drains the accumulators. |

Three properties of this design matter, and together they satisfy most of what a
raw-input feature normally has to build by hand.

**The two paths are already mutually exclusive.** At `0x00619717`:

```
cmp dword ptr [0x00918424], 0
jne skip                        ; raw enabled -> legacy never runs
call ProcessMouseMessages
```

So nothing has to suppress the legacy mouse path; the engine does it. Setting
the flag swaps the source of look deltas atomically rather than adding a second
contributor.

**The deltas are accumulated, not sampled.** `ProcessMouseRawInput` ends with:

```c
if (raw->lLastX || raw->lLastY) {
    *(int*)0x02CEBCA0 += raw->lLastX;
    *(int*)0x02CEBCA4 += raw->lLastY;
}
```

Every packet is summed, and the consumer at `0x00623AC0` drains the accumulators
to zero once per look update. Motion that arrives between two updates is
therefore preserved rather than dropped, which is what keeps a high polling-rate
mouse from behaving differently to a 125 Hz one, and what keeps sensitivity
independent of frame rate. OpenShim does no scaling of its own; adding any would
break this.

By contrast the legacy path *assigns* rather than accumulates, and it derives
its value from the cursor position relative to the window centre:

```c
accumX = (short)LOWORD(lParam) - (screenWidth  >> 1);
accumY = (short)HIWORD(lParam) - (screenHeight >> 1);
```

which is the classic warp-to-centre scheme, and the reason the legacy path is
subject to pointer acceleration, the desktop pointer-speed slider, and the
screen edge.

**Sensitivity is shared.** The consumer reads one sensitivity value from the
stock table at `0x008EC494` and applies it to whichever accumulator values are
present, so the in-game sensitivity setting keeps working unchanged. The raw
branch additionally applies the stock magnitude-based acceleration curve:

```c
if (rawEnabled) {
    mag = sqrt(dx*dx + dy*dy) / k;
    sensitivity = (mag >= 0x180) ? sensitivity * 2
                                 : ((mag + 0x80) * sensitivity) >> 8;
}
```

That curve is stock behaviour on the raw path and is left alone.

## What OpenShim adds

**Enables the flag**, subject to byte guards (below), from `ResolveBzrHooks`.
It also calls `RegisterRawInputDevices` itself. That is deliberate: OpenShim can
resolve on either side of the engine's one-shot window-init pass, so registering
directly covers the ordering where the stock gate at `0x00618E82` has already
run and will not run again. Registration is idempotent, and `hwndTarget = 0`
means `WM_INPUT` follows keyboard focus.

One consequence to be aware of when reading logs: `RunPatcher` executes on
OpenShim's own patch thread, not the game's UI thread. `hwndTarget = 0` is what
makes that safe — a registration that named a window would have to be made from
the thread owning it. In the common case the patch thread wins the race, sets
the flag before the engine's window init runs, and the engine performs its own
registration from the UI thread a moment later, replacing ours. Both orderings
end in the same state, which is why the feature does not depend on which one
happens; the `First raw mouse packet received` line is what confirms it.

**Byte guards.** All the addresses above are absolute operands, so the guard
first requires the image to be at `0x00400000`, then checks the complete
`cmp dword ptr [0x00918424], 0` instruction *plus the branch opcode that
consumes it* at all three sites that read the flag, and the prologue of
`ProcessMouseRawInput`. Anchoring on the operand alone would match any unrelated
reference to the same address. If any site fails to match, OpenShim logs which
one and leaves the engine on its legacy path.

**An absolute-mode guard.** This is the one real defect in the stock handler.
`ProcessMouseRawInput` adds `lLastX` / `lLastY` into the accumulator without ever
testing `usFlags`. For a device that reports `MOUSE_MOVE_ABSOLUTE` — remote
desktop, most VM and KVM guest mice, pen tablets — those fields are a position in
a normalised 0..65535 space rather than a delta, so the stock code slams the
camera to the edge and pins it there. OpenShim detours `ProcessMouseRawInput`,
differences successive absolute positions back into relative movement, and
swallows the first sample where there is no previous position to difference
against. A gap of more than 500 ms re-seeds instead of differencing, so alt-tab
and menu excursions do not produce one huge jump on return.

This is why the option can default to on: absolute-mode devices were the one
concrete compatibility reason not to, and they are now handled.

If the detour fails to install, the raw path still runs for every ordinary
relative mouse; only the absolute guard and the packet diagnostics are lost.

## Failure behaviour

Every failure path leaves the flag clear, which means the engine keeps using its
own legacy mouse path — the stock behaviour. Specifically: a relocated image, any
byte-guard mismatch, a failed `RegisterRawInputDevices`, or a failed write to the
flag. None of them are fatal and none of them disable the mouse.

Controller and keyboard input are not touched by any of this. The flag is read
only by the three mouse sites listed above.

## Configuration

`[General] RawMouseInput` in `openshim.ini`, boolean, default OFF, restart
required. Set it to `1` to bypass the legacy smoothed/Windows-accelerated
mouse-message path; set it to `0` to retain stock mouse input.

Precedence, most specific first:

1. `rawinput` / `norawinput` on the command line (stock tokens; the negative is
   tested first, since `norawinput` contains `rawinput`)
2. `OPENSHIM_DISABLE_RAW_MOUSE_INPUT` / `BZR_DISABLE_RAW_MOUSE_INPUT`
3. `[General] RawMouseInput`
4. default OFF

Live toggling is available through the existing exported bridge
(`OpenShimGetRawMouseInputEnabled` / `OpenShimSetRawMouseInputEnabled`), which
registers or removes the device and flips the flag. The INI value itself is read
once at startup.

Not yet exposed in the OpenShim Settings UI page — that is a deliberate
follow-up.

## Diagnostics

All logging goes to the existing OpenShim log (`logs\`) under `[RAWINPUT]`.

At startup, unconditionally:

```
[RAWINPUT] Raw mouse input: enabled source=openshim.ini signatures=verified guard=installed trace=disabled
[RAWINPUT]   flag=0x00918424 process=0x004357D0 (stock command-line tokens: rawinput/norawinput)
```

`source` reports which precedence tier decided it, `signatures` whether the byte
guards passed, `guard` whether the absolute-mode detour installed.

On the first raw packet, once:

```
[RAWINPUT] First raw mouse packet received; raw look path is live
```

That line is the one that actually proves the path is working end to end —
registration succeeding does not, on its own, mean packets are arriving.

Set `OPENSHIM_TRACE_RAW_INPUT=1` (or `OPENSHIM_TRACE_MOUSE_INPUT=1`) for
per-packet detail, budgeted to 256 lines:

```
[RAWINPUT] packet #1 usFlags=0x0000 buttons=0x0000 data=0 dx=-3 dy=1
```

## Testing

See the test matrix in the pull request. The static derivation is complete and
the build is verified; everything about runtime behaviour needs a live session,
because none of it can be confirmed from the binary alone.
