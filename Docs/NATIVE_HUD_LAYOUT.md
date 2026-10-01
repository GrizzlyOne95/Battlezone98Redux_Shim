# Native HUD layout provider

2026-09-30 checkpoint: the engine-independent full-meter transform, mission
intent, thread-serialized provider and SDK exports are implemented. **There is
no installed native render interception yet.** All production capabilities stay
zero. No new native patch sites, addresses, signatures or INI switches are
introduced. EXU's companion API/helper can be reviewed before the native adapter
has live Windows qualification.

## SDK

Resolve the optional exports through `winmm.dll`, as with the existing HUD
sprite and scrap/pilot APIs. All use `WINAPI` / stdcall and primitive arguments.

| Export | Contract |
| --- | --- |
| `DWORD OpenShimGetNativeHudLayoutCapabilities()` | Bit 0 hull; bit 1 ammo; zero unavailable/unqualified. |
| `BOOL OpenShimGetNativeHudMeterRect(LPCSTR,int*,int*,int*,int*)` | Effective full bar x/y/width/height after observing a stock frame. |
| `BOOL OpenShimGetNativeHudMeterDefaultRect(LPCSTR,int*,int*,int*,int*)` | Current stock full bar bounds before override. |
| `BOOL OpenShimSetNativeHudMeterRect(LPCSTR,int,int,int,int)` | Accept mission-scoped physical-pixel intent for the next draw. |
| `BOOL OpenShimSetNativeHudMeterVisible(LPCSTR,BOOL)` | Accept group visibility intent. |
| `BOOL OpenShimRestoreNativeHudMeter(LPCSTR)` | Clear one meter's geometry/visibility override. |
| `BOOL OpenShimRestoreAllNativeHudMeters()` | Clear all native-meter intent; does not affect radar, scrap/pilot or atlas overrides. |

Names are exactly `hull` and `ammo`. Getters fail without changing outputs for
unknown IDs, null outputs, an unavailable adapter or no stock snapshot. Setters
fail without storing intent when unsupported. Width/height are positive counts
up to 16384; coordinates/far edges lie within +/-65535. No engine pointers cross
the boundary. EXU restores only its own touched meter slots, rather than calling
the SDK's global native-meter restore.

These fields append **after the five existing legacy provider slots**. They
must not be inserted into the original alphabetic export block: that would
move offsets read by an older bootstrap/plugin pair. `OPENSHIM_SDK_EXPORT_APPEND`
keeps the same single export inventory for declarations, thunks and completeness
checks while the bridge places the extension after the previous table end.
The public `OpenShimApiV2` layout is unchanged. Windows thunk tests cover both
new forwarding and a provider whose size ends immediately before the HUD block.

## Adapter boundary

`include/native_hud_layout.h` and `src/engine/native_hud_layout.cpp` own pure
geometry/intent; `src/patches/native_hud_runtime.cpp` serializes bridge and
render access. `Runtime::SetAdapterCapabilities` is an internal native-adapter
boundary with **no production enabling caller**. A test's fake adapter exercises
it; no SDK or Lua function can turn it on.

A qualified adapter must:

1. Guard released-build identity, settled live bytes, calling convention, draw
   sites, pane layout and current status-object lifetime. Keep build addresses
   in `scripts/patches.json` and use existing named resolution/patch infrastructure.
2. Call `BeginFrame` within the current status render scope, before group draws.
   Supply the current full stock meter bounds to `Observe` before transforming
   the bar, label, marker or text origin. Frame/mission tokens reject a late
   observation from a previous render or mission; no object pointer is cached.
3. Resolve sprite alignment and pane-relative offsets first. Use one `RenderPlan`
   for that group's full sprite and inclusive clip. Keep native UV/texture,
   color, native smoothed ratio and animation. Map labels as sprites and map
   shots text origins without claiming native font rescaling. The ammo cost
   rows use the same edge map. `InferFullRect` is tested against observed trace
   semantics, including fully empty fill; a bar's later draw alone is too late
   to discover geometry for its already-submitted label.
4. Suppress only group visual submissions when hidden. Always execute the
   original status renderer and native warning/audio behavior. Scope all
   interception to the current renderer/thread and positively identified group
   draws; radar, weapons and other HUD elements must retain normal behavior.
5. Preserve and restore the native pane on every path. Dequalify on an ABI,
   target or lifetime mismatch; zero capabilities clear snapshots and intent.

`ResetMission` drops intent and source snapshots and invalidates frame tokens.
It is wired to the existing simulation-exit seam and mission-hook reset. Runtime
address rebinding dequalifies the adapter. Restoration reveals the newly
observed stock layout rather than persisting initial resolution-dependent data.
If the original renderer has no meter in a frame, `BeginFrame` makes its getter
unavailable instead of returning the preceding object's rectangle.

## Evidence and remaining gate

The released GOG static trace and guarded observational capture live in EXU's
`Docs/Research/NATIVE_HUD_LAYOUT_20260930.md` and `tools/trace_native_hud.py`.
The required native launch/byte capture is not available in this Linux workspace.
Per `AGENT_TOOLING.md`, perform it before authoring native patches/signatures.
No native draw hook is fabricated from decompiler addresses.

Host geometry/provider tests cover full/partial/empty fill, scale/translation,
labels/marker/text mapping, finite/overflow guards, late frame/mission rejection,
stock reflow, explicit restore, and unavailable exports. Win32 DLL/SDK checks
run separately in CI. Actual GOG and Steam gameplay, resolution/UI scale,
player/camera transitions, native audio and radar composition, followed by
Proton/Wine smoke tests, remain unverified and are required before enabling.
