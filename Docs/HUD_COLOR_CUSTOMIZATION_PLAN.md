# HUD colour customization — plan

Status: **not started.** This records a decision and a scope so the work can be
picked up cleanly, and so the idea is not re-derived from scratch.

## Why this lives in OpenShim, not Campaign Reimagined

CR already ships a HUD colour concept: `PdaColorPreset` in
`Scripts/PersistentConfig.lua`, with four presets (Dark BZ, Classic BZ, BZ2,
Cyberzone) each defining twelve colour roles. It is deliberately scoped to the
**PDA overlay only** and must stay that way — confirmed by the author
2026-09-20. Do not extend it to HUD sprites.

Recolouring the actual HUD — radar icons, unit ammo and health bars, the scrap
and pilot readouts — belongs here instead, for a reason already written into
CR's own source. `PersistentConfig.ApplySettings` deliberately does not call
`ApplyScrapPilotHudLayout` and deliberately ignores `syncRadarSize`, with
comments stating that **OpenShim owns the persistent scrap/pilot HUD layout and
the process-wide radar size**, and that campaign settings must not overwrite the
player's `openshim.ini`. A HUD colour setting is the same kind of state: it is
process-wide player preference, not campaign art direction.

## What already exists

EXU exports exactly two HUD colour setters, both taking packed ARGB:

- `SetScrapHudColor`
- `SetPilotHudColor`

Today they are called from one place, `PersistentConfig.ApplyScrapPilotHudLayout`,
with hardcoded constants selected by `ScrapPilotHudLayout` — legacy uses
`0xFF007FFF` for scrap and `0xFF00FF00` for pilot, stock uses `0xFFFFFFFF`
(white, meaning "do not tint").

OpenShim already understands the radar deeply: `bzr_hooks.cpp` hooks the layout
builder at `0x00492EC0` and knows `CockpitRadar::Render` at `0x0049405B`, along
with the projection and backdrop globals. That is geometry, not colour, but it
means the render path is already mapped.

## What is missing

**There is no radar icon colour setter at all.** No EXU export, and nothing in
OpenShim's sources sets blip colour. Adding it means locating where
`CockpitRadar::Render` picks blip colours and exposing a setter before any
setting can exist. That is the expensive half of this work.

## Scope, in two independent pieces

1. **Scrap / pilot HUD tint.** Cheap. The setters exist and OpenShim already
   owns the layout. This is a colour source swap plus a settings-page row,
   with `defaultIndex` matching today's hardcoded constants so an absent key
   changes nothing.
2. **Radar icon colour.** Expensive. Needs new native API first, per above.

## Open design question — settle before building rows

The legacy layout distinguishes scrap (blue) from pilot (green). A single "HUD
tint" setting collapses that distinction. Options:

- two independent colour settings;
- one base colour plus a fixed hue offset for the second;
- a preset table of coordinated pairs, which is closest to how CR's PDA presets
  already read.

This changes the shape of the settings rows, so decide first.

## Caution

A HUD colour complaint is not automatically a colour-setting bug. CR's
`sprites.material` routes every `BZSprite/*` material — including the HUD path,
`AlphaHUDPixel` → `AlphaHUD` → `CR_UI_*` — through CR's own shaders, and those
apply an `iColor.bgra` red/blue swap on the SM4 (DX11) path that the SM3 (DX9)
path does not. Rule that out before attributing a wrong colour to a setting.
