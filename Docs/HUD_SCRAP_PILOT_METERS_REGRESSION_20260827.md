# Scrap / Pilot HUD Meter Regression Plan

**Date:** 2026-08-27  
**Status:** OPEN - REPRO/RE NEEDED  
**Priority:** Minor visual bug, but user-visible and worth fixing

## Reported behavior

The scrap and pilot HUD meters in Battlezone 98 Redux do not always remain correctly anchored against the top-left command sprite/HUD cluster.

Observed failure modes:

- the scrap/pilot values can appear displaced far from the top-left HUD and sometimes end up around the middle of the screen;
- the expected green/blue tinting can be missing when the bad state occurs;
- positioning can become inconsistent across state changes rather than remaining clamped/anchored to the command sprite;
- Battlezone 1.5 had a black backing sprite behind these meters that improved contrast/readability; Redux should be compared against 1.5 and that backing element restored if the original behavior is confirmed.

Treat these as related symptoms until proven otherwise, but do not assume one root cause. Positioning, color/tint state, and background-sprite submission may be separate consumers that share the same HUD-layout lifecycle.

## Compatibility target

Use Battlezone 1.5 as the visual/layout reference.

The intended result should be:

1. scrap and pilot meters remain anchored/clamped to the top-left command/HUD sprite cluster;
2. scrap retains its intended green presentation and pilot retains its intended blue presentation;
3. the 1.5-style black backing sprite sits behind the values to improve legibility;
4. the layout survives save/load, HUD-scale changes, and resolution changes without drifting or losing tint/background state.

Do not hard-code a single pixel coordinate that only matches one resolution. Recover the native layout relationship and reapply it when the HUD transform changes.

## Research questions

### Positioning

Determine:

- which class/function owns the scrap meter;
- which class/function owns the pilot meter;
- whether both use one shared text/sprite widget type;
- which top-left command sprite or parent HUD element is the intended anchor;
- whether the meters store absolute pixels, normalized coordinates, virtual-screen coordinates, or coordinates already transformed by HUD scale;
- where clamping/anchoring occurs in 1.5;
- whether Redux dropped a parent-relative transform, clamp, or re-layout call;
- whether the bad middle-screen position is a stale/uninitialized/default coordinate rather than a bad clamp result.

### Tinting

Determine:

- where the green/blue color is authored in 1.5 and Redux;
- whether the color is applied through sprite modulation, text color, material/pass state, vertex color, or a HUD palette lookup;
- whether layout recreation/save-load/resolution-change paths reconstruct the meter without restoring its tint;
- whether the position and tint failures occur in the same widget recreation path.

### Black backing sprite

Confirm in 1.5:

- sprite/material/resource name;
- draw order relative to scrap/pilot values and command sprite;
- size and padding;
- alpha/blend state;
- whether it is one shared backing plate or separate plates;
- how its position/scale derives from the same anchor.

If Redux still ships the legacy sprite/resource, prefer reusing it. If it was removed, recreate equivalent presentation through OpenShim only after the original dimensions/material behavior are recovered.

## Required lifecycle matrix

Test at minimum:

| Case | Action | Expected |
| --- | --- | --- |
| HUD-1 | fresh mission at default resolution/scale | meters correctly anchored, tinted, backed |
| HUD-2 | save then load in same mission | identical placement/tint/backing |
| HUD-3 | save, return to shell, then load | identical placement/tint/backing |
| HUD-4 | change HUD scale smaller -> larger -> original | meters track anchor every time |
| HUD-5 | change game resolution | meters reflow to correct anchor |
| HUD-6 | windowed -> fullscreen / fullscreen -> windowed where supported | no drift/state loss |
| HUD-7 | mission restart | no stale coordinates/colors |
| HUD-8 | in-process mission transition | no stale parent/widget state |
| HUD-9 | eject/re-enter craft if HUD ownership changes | layout/tint remains correct |
| HUD-10 | satellite/F9/cinematic enter/exit | normal HUD restores correctly |

Where possible test both Steam and GOG 2.2.301 after the native producer is identified.

## Instrumentation minimum

For each meter/background element, log on creation/re-layout and only when state changes:

- widget/object pointer or native identity;
- parent/anchor identity;
- raw x/y;
- post-HUD-scale x/y;
- viewport width/height;
- current HUD/UI scale;
- clamp bounds;
- color/tint RGBA or palette/material identifier;
- visibility;
- background sprite/material identity;
- lifecycle reason: mission start, load, PostLoad, resolution change, HUD-scale change, view restore, mission restart.

A useful diagnostic should make a bad state obvious, for example:

```text
[HUDMETER] scrap reason=PostLoad raw=(...) final=(...) anchor=(...) scale=... rgba=... backing=...
[HUDMETER] pilot reason=ResolutionChanged raw=(...) final=(...) anchor=(...) scale=... rgba=... backing=...
```

Keep logging bounded/rate-limited; this must not become a per-frame spam path.

## Preferred implementation shape

If RE confirms a shared layout helper exists in 1.5 but is missing/broken in Redux, restore that relationship rather than adding independent per-resolution constants.

Conceptually:

```text
command HUD anchor
    -> native HUD scale transform
    -> scrap/pilot local offset
    -> viewport-safe clamp
    -> meter text/sprite
    -> 1.5 black backing sprite beneath it
```

The fix should be idempotent: repeated save/load, resize, or HUD-scale notifications should recalculate the same final layout rather than accumulating offsets.

Do not persist derived pixel coordinates into save data. Save/load should reconstruct from current viewport/HUD settings so loading a save at a different resolution or HUD scale still produces the correct result.

## Acceptance gate

Do not mark fixed until all of the following are demonstrated:

- no middle-screen displacement across the lifecycle matrix;
- scrap and pilot values retain their intended green/blue tint every time;
- the restored/confirmed 1.5 black backing sprite tracks the meters and renders behind them;
- loading a save created at one HUD scale/resolution into another current configuration produces correct current-layout coordinates rather than saved stale coordinates;
- repeated resolution/HUD-scale changes do not accumulate drift;
- satellite/cinematic/eject/re-enter transitions restore the same layout;
- no regression to other top-left command HUD elements.

## Suggested RE deliverable

`reverse_engineering/hud_scrap_pilot_meter_layout_20260827.md`

The report should include:

- 1.5 vs Redux function/layout comparison;
- exact anchor/coordinate-space semantics;
- tint/material path;
- black backing sprite/resource identification;
- first divergent lifecycle path;
- smallest compatibility restoration;
- runtime matrix and screenshots before/after.
