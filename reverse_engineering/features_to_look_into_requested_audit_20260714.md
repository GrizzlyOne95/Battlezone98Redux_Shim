# Requested FeaturesToLookInto Audit

Date: July 14, 2026

Source: <https://github.com/GrizzlyOne95/ExtraUtilities/blob/main/FeaturesToLookInto.txt>

Requested items: 24, 39, 46 A/B/C, 47, 49, 50, 54-59, 61, 63-66,
68, 77-79.

## Outcome summary

This pass added stock-preserving native fixes for 54, 55, 61, 64, 68, and 79,
and completed the engine/control surface for 39. Items 46A and 47 were already
implemented in the working tree and were rechecked. The remaining items are
documented below rather than being assigned speculative hooks.

Release|Win32 builds successfully. Debug|Win32 currently stops on three
pre-existing `C2712` errors where unrelated functions combine C++ object
unwinding with `__try`; the new hook locations are not among those diagnostics.
The new runtime patches still require focused gameplay repros before they
should be described as gameplay-validated.

## Implemented or verified

### 39 — raw mouse input

Verified in the settled Redux executable:

- `rawinput` and `norawinput` are stock command-line tokens
- the parser writes the enable flag at `0x00918424`
- startup registers usage page `1`, usage `2` with
  `RegisterRawInputDevices`
- the window path reads `WM_INPUT` through `GetRawInputData`

OpenShim now defaults this stock path on while respecting explicit
`norawinput`, `OPENSHIM_DISABLE_RAW_MOUSE_INPUT`, and
`BZR_DISABLE_RAW_MOUSE_INPUT`. Two exported bridge functions provide the PDA
or EXU-facing control surface:

- `OpenShimGetRawMouseInputEnabled`
- `OpenShimSetRawMouseInputEnabled`

The actual PDA toggle widget remains addon/UI work; the native toggle is ready.

### 46A — spraybomb splinter continues firing after destruction

Already implemented and rechecked. `SprayBuilding::Simulate` vtable slot
`0x00888228` points to settled stock body `0x005DA6E0`. Destroyed/remove-flagged
splinters are routed through `Building::Simulate` at `0x0047FCB0`, preserving
the stock destruction gate. Live splinters still use the original override.

### 47 — constructor remote build after death

Already implemented and rechecked. The `AI_UnitRemove` hook at `0x0068FC60`
performs construction-end, reserved-area removal, credit refund, stop-order,
and construction-field cleanup for the exact dead-constructor/in-progress
case before forwarding to stock removal.

### 54 — APC deployment while targeting an ally

Implemented in the settled `APC::Simulate` body (`0x0046FFC0`). The two failed
enemy-relation branches at `0x004700E6` and `0x00470108` previously skipped
straight to the failure result. They now enter the function's existing
no-target nearby-enemy scan at `0x004701AC`. Direct enemy targeting and the
stock 75-unit range test are unchanged.

Opt-out: `OPENSHIM_DISABLE_APC_DEPLOY_FIX=1` or
`BZR_DISABLE_APC_DEPLOY_FIX=1`.

### 55 — tug cargo after mission start/save load

Implemented at `Tug::PostLoad`, primary vtable slot 22 (`0x00889060`, stock
body `0x005EC430`). After the stock cargo relationship is restored, a tug with
cargo in state `UNDEPLOYED` has the normal `control.deploy` flag armed. Stock
`Tug::Simulate` then performs its existing animation and state transition.
This is the native equivalent of the documented Lua `HasCargo`/`Deploy`
workaround without forcing state 2 directly.

Opt-out: `OPENSHIM_DISABLE_TUG_CARGO_FIX=1` or
`BZR_DISABLE_TUG_CARGO_FIX=1`.

### 61 — undeployed howitzer sniper retaliation

Implemented in the RTTI-validated `OffensiveProcess::DoSubTask` vtable hook at
settled body `0x00583520`. That stock routine has a dedicated recent-SNIP
target override sourced from `craft+0x98`. For an ArtilleryProcess whose owner
is a Howitzer and whose deploy state at `+0x228` is not the stock deployed
state `2`, OpenShim hides only that SNIP source for the duration of the stock
call, then restores it. Follow/go processing and ordinary target acquisition
remain stock. Deployed howitzers and every other process are untouched.

The previously investigated `0x0042AF10` inline detour remains uninstalled;
that address is not used by this fix, and the older multi-weapon replay remains
disabled.

Opt-out: `OPENSHIM_DISABLE_HOWITZER_DEPLOY_FIX=1` or
`BZR_DISABLE_HOWITZER_DEPLOY_FIX=1`.

### 64 — zero MagnetClass range

Implemented in the existing `MagnetMine::Simulate` vtable path. A zero,
negative, or non-finite range at class offset `+0x16C` bypasses the unsafe
magnet attraction computation and calls stock `Mine::Simulate` instead. This
keeps ordinary mine lifecycle/removal behavior intact.

Opt-out: `OPENSHIM_DISABLE_MAGNET_ZERO_RANGE_FIX=1` or
`BZR_DISABLE_MAGNET_ZERO_RANGE_FIX=1`.

### 68 — PROD ScriptUtils IsBusy/CanBuild

Implemented at settled ScriptUtils entries `0x005CB4E0` (`CanBuild`) and
`0x005CB550` (`IsBusy`). The stock result is retained for RCYC/FACT/ARMR/CNST.
If stock returns false, the wrapper safely resolves the object, accepts only
the exact `PROD` class signature, and invokes the corresponding base Producer
predicate (`0x004738B0` / `0x004723D0`).

### 79 — mission briefing text cutoff

Implemented by redirecting the mission briefing and mission archive up/down
callbacks from the unguarded stock scroll routines to the guarded variants
already used elsewhere by the game. The four exact call sites are
`0x0078ED29`, `0x0078ED39`, `0x00790AF9`, and `0x00790B09`.

Opt-out: `OPENSHIM_DISABLE_BRIEFING_SCROLL_FIX=1` or
`BZR_DISABLE_BRIEFING_SCROLL_FIX=1`.

## Partially present

### 50 — dynamic HUD effects

The native primitives are already present:

- named HUD sprite rectangle lookup/update
- named HUD sprite visibility and restore
- under-attack alert event policy
- recent-hit/target-reticle event policy
- exported bridge calls suitable for EXU/native consumers

What is not yet present is a general Lua event-to-arbitrary-Ogre-widget API.
That is a larger API design item, not a single engine bug fix.

## Investigated but not patched in this pass

### 24 — 1.5 satellite fog of war

The scanner state and legacy illumination gate have been mapped, and the
existing `[SATVIS]` probe can confirm live `isVisible`, `seen`, and
`illumination`. Static evidence still points to the Redux overview/Ogre object
submission bridge as the missing gate. No submission hook was installed
without a live hidden-versus-visible object capture. See
`satellite_fow_static_handoff_20260323.md`.

### 46B — violent deployed SprayBuilding collision

The `SprayBuilding` type and simulation path are known, but the collision
impulse owner has not yet been isolated. The 46A lifecycle hook does not alter
collision response.

### 46C — multiplayer splinter payload duplication

This requires proving which peer owns payload creation and whether the stock
spray loop lacks a `DistributedObject::IsRemote`/authority gate. No network
authority patch was made from static inference alone.

### 49 — all-zero weaponMask follow crash

The encoded mask field and multiple consume paths are known, but no crash dump
or exact failing follow consumer is available. Blindly rewriting `00000` to a
weapon bit would change intentional no-fire behavior, so this remains open.

Update 2026-07-16: a crash-time logger now ships in the shim
(`src/engine/crash_logger.cpp`): unhandled-exception filter plus first-chance
vectored logger writing registers, module+RVA, a stack scan, and a minidump to
`logs\openshim_crash.log` / `openshim_crash_<timestamp>.dmp`. One in-game repro
of the follow crash now yields the exact failing consumer.

### 56 / 78 — stale target camera in satellite/F9 view — FIXED 2026-07-16

Root cause relocated statically. The Ogre frame driver (`0x00682540`) shows
the target-camera PiP viewport (bridge `0x00920EA0` + 0x20, camera +0x14)
while the legacy TargetCam enabled flag (`targetCam` `0x025F5FE0` + 0x1F1)
reads true; that flag is recomputed per frame by the legacy updater
(`0x005DDE00`, request latch at +0x1F0), which stops running in
satellite/editor overview, leaving the flag latched and the PiP frozen.
Fix: only the frame driver's enabled-predicate call (`0x00682679` ->
`0x005DDDE0`) is retargeted to a gate that reports disabled while the view
mode global (`0x008EAAD8`) is satellite (3) or editor (9). Stock code then
removes/re-creates the viewport itself; the gameplay target is untouched.
Kill switch: `OPENSHIM_DISABLE_TARGETCAM_FIX`. Log tag `[TARGETCAM]`.

### 57 — earthquake/dayquake repeated after load — FIXED 2026-07-16

Full Redux chain mapped: `quakeMag` global `0x02A13D88`; SaveScriptUtils
(`0x005C7B90`) refreshes it from `earthQuake` (`0x00992328`, scale +0x28);
LoadScriptUtils (`0x005C7510`) zeroes then reads it (save version > 0x40C);
PostLoadScriptUtils (`0x005C7A50`) restarts the quake via StartQuake
(`0x004C0BB0`, call site `0x005C7B83`) when nonzero. Quake ordnance
(QuakeBlast) drives the global quake but explosions are not persisted, so the
replayed quake has no owner left to stop it — endless shake plus looping
`gquak01.wav`. Fix: the restart call is retargeted to arm a fade watchdog and
EarthQuake::Simulate (`0x004C0CF0`) is entry-detoured; the watchdog ramps the
replayed scale to zero over `OPENSHIM_QUAKE_FADE_SECONDS` (default 5) using
UpdateQuake (`0x004C0C40`, also rescales the loop sound) and finishes with
StopQuake (`0x004C0CA0`), disarming immediately if any script writes the
scale (script-owned quakes keep stock behavior). Kill switch:
`OPENSHIM_DISABLE_QUAKE_FADE`. Log tag `[QUAKEFADE]`.

### 58 — cinematic camera zoom during satellite view — FIXED 2026-07-16

Transition owner found. Satellite entry (`0x0061BD20`) rebuilds the whole
main camera record (`0x00439E60`) via the camera-record builder
(`0x00688370`) with pi/2 FOV and the overview zoom; the cinematic begin
(`0x00821E30`, view mode 5) only reconfigures the window and reuses the
record's zoom-dependent scale fields, so cinematics triggered from satellite
inherit the overview zoom. Fix: both begin call sites (`0x004F5667`,
`0x005CD2D9`) are retargeted to a gate that, when the view mode global is
satellite (3) or editor (9), first rebuilds the record with cockpit
parameters (FOV bits `0x0087256C`, zoom 1.0 bits `0x008A2604`) exactly as the
cockpit view setter (`0x0061BAB0`) does, then runs the stock begin. Authored
cinematics from cockpit view are untouched. Kill switch:
`OPENSHIM_DISABLE_CINECAM_FIX`. Log tag `[CINECAM]`.

### 59 — walker cockpit jitter

The report points to parent-transform inheritance. No safe transform split was
identified that preserves cockpit animation, aiming, and first-person offsets.

### 63 — multiplayer freecam exploit

The user-visible free-camera activation route and the authoritative net-game
gate are not yet mapped together. No broad camera-command suppression was
installed.

### 65 — invalid renderCount allocation — FIXED 2026-07-16

Crash mechanism proven statically. The MultiRenderClass constructor
(`0x0044D7B0`, selected by `[Render] renderBase="draw_multi"`) reads the ODF
key `rendercount` (keys are lowercased before FNV-1a hashing; hash
`0x8C8E76EC`) into `this+0x108` via the ParameterDB getter (`0x005896C0`),
multiplies it by 4 with overflow saturation to `0xFFFFFFFF`, and passes the
result straight to `operator new[]` (`0x0083D92C`) — a missing/nil/garbage
count dies with "invalid allocation size". Fix: an 11-byte mid-function
detour at `0x0044D858` clamps the stored count to [0, 256] between the
ParameterDB read and the allocation; the same field bounds the `renderName%d`
copy loop, so one clamp protects both. Kill switch:
`OPENSHIM_DISABLE_RENDERCOUNT_CLAMP`. Log tag `[RENDERCOUNT]`.

### 66 — pilot hardpoints below CraftClass header

This is order-sensitive ODF parsing, but the specific Pilot/Craft parser handoff
has not been mapped. Moving or ignoring fields generically could silently alter
valid custom ODF inheritance.

Update 2026-07-16: 1.5's hardpoint build loop warns via `DEBUG_systemWarning`
rather than crashing, so the crash site is Redux-specific. The new crash
logger (see item 49) will pinpoint it from one repro with a malformed ODF.

### 77 — type-0 terrain texture deformation

This is the same terrain issue described as item 60 in the source list. It is
render/material-orientation work, not shown to originate in a native simulation
field. No shader or terrain bridge patch was made without a captured tile,
orientation, material, and render-state comparison.

## Runtime validation checklist

1. Deploy an APC near an enemy while an allied unit remains selected.
2. Start/load a tug with cargo, wait for its stock transition, then deploy to
   drop the cargo.
3. Snipe an undeployed following/going howitzer and confirm it waits to fire;
   repeat after full deployment.
4. Spawn a zero-range magnet and verify no crash while normal expiry remains.
5. Exercise `CanBuild`/`IsBusy` on a base `ProducerClass` object.
6. Scroll both a long briefing and mission archive to their final partial page.
7. Verify raw mouse startup, runtime disable, and runtime re-enable.
