# HUD colour customization — plan

Status: **scrap/pilot customization implemented, opt-in.** Radar grid/contact,
cockpit meter and unit-bar preferences are implemented separately in
[`HUD_PALETTE.md`](HUD_PALETTE.md), with native acceptance tracked there.
OpenShim Options → HUD keeps the existing `Scrap/Pilot HUD`
Stock/Legacy choice and adds independent Scrap Color and Pilot Color controls.

## Player controls

`[Display] ScrapHudColor` and `PilotHudColor` default to `Default`, which uses
the selected layout's existing native palette: white in Stock, scrap blue and
pilot green in Legacy. Choosing a color changes each readout's title and value
together. It does not move the readout, change alignment, alter plate geometry,
or modify other HUD colors. Both settings apply live and persist separately
from the Stock/Legacy layout setting.

Menu choices are Default, White, Blue, Green, Cyan, Amber, Magenta, Red and Yellow. The INI
also accepts `#RRGGBB` and `0xAARRGGBB`; explicit alpha is preserved. Invalid
values fall back to the layout palette. Custom hex values display as Custom
in Options. Choosing Default restores the native palette references.

## Native implementation

The existing guarded four string-color operands in `scrap_pilot_hud.cpp` can
reference either their original engine palette globals or two aligned,
shim-owned ARGB values. The shared engine palette is never recolored. The
alignment decision still comes exclusively from the layout switch; its
backplate hooks, command-menu-relative anchor, viewport clamp and mission
position overrides retain their existing paths. Layout palette references
remain live, so engine palette reloads still work with Default.

These are process-wide player preferences, independent of campaign PDA
presets. EXU already relinquishes its four HUD color hooks when the OpenShim
restore export is present; this work adds no competing Lua color hooks or
new reusable Lua API. The portable parser has malformed-input, preset,
ARGB-order and alpha tests. No new native address is needed for meter colors.

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

Historically they were called from `PersistentConfig.ApplyScrapPilotHudLayout`,
with hardcoded constants selected by `ScrapPilotHudLayout` — legacy uses
`0xFF007FFF` for scrap and `0xFF00FF00` for pilot, stock uses `0xFFFFFFFF`
(white, meaning "do not tint"). OpenShim owns native text colors when its HUD
bridge is available; the current player controls are implemented here.

OpenShim already understands the radar deeply: `bzr_hooks.cpp` hooks the layout
builder at `0x00492EC0` and knows `CockpitRadar::Render` at `0x0049405B`, along
with the projection and backdrop globals. That is geometry, not colour, but it
means the render path is already mapped.

## Radar follow-up

The player-facing radar grid and normal-contact colors now use isolated
native draw adapters in OpenShim. Special/alert icons retain native colors,
and ambiguous/disguised identities retain stock appearance. A reusable EXU
radar color API remains out of scope; these are persistent player preferences.

## Scope, in two independent pieces

1. **Scrap / pilot HUD tint.** Implemented with two independent settings.
   Missing keys and Default preserve the selected layout's colors.
2. **Radar and meter colors.** Implemented as persistent player preferences;
   see the separate HUD palette document for scope and qualification.

## Selected design

Two independent color settings preserve the legacy blue/green distinction by
default and let players choose different contrast for each readout.

## Local qualification, 2026-10-19

Released GOG 2.2.301 / DX11, using the serialized harness and temporary INI
settings that were restored after each run:

| Run | Result |
| --- | --- |
| PID 54068, Legacy + Amber/Cyan | Colored titles and values visibly retain stacked black plates; native text remains left-aligned. |
| PID 43996, Stock + Amber/Cyan | Colored titles and values visibly retain centered Stock panels. All four alignment immediates remain 1 and both submit CALLs retain original bytes. |
| PID 37508, Stock + Default | All four color operands use the original white palette address; geometry equals Stock + custom colors. |
| PID 36028, Legacy + Default | Original blue/green palette references and left alignment restore; legacy geometry and plates remain selected. |

Across the inspected runs, shared palette values remain White `0xFFFFFFFF`,
Blue `0xFF007FFF`, Green `0xFF00FF00`. Custom values use shim-owned storage.
Frontend controls independently save/apply both colors and still switch
Stock/Legacy. Full save/load, resize/UI-scale and cross-platform acceptance
remain separate gates. A debugger-invoked reload experiment raised Frida
system errors and is not counted as live-transition acceptance; fresh-process
snapshots above provide the native evidence.

Release Win32 build and all 115 Windows CTest cases pass. The three changed
portable HUD/layout policy tests also compile with GCC `-Wall -Wextra -Werror` and
pass under WSL. INI completeness (213 settings), shipping policy, writer and
migration checks pass. Full Linux-suite logs were not retained across the
local WSL session; no new full Linux-suite result is claimed here.

## Colour-order finding

The reported orange/blue inversion was not limited to a PDA preset and was not
a reason to remove `iColor.bgra` from every stock/CR sprite shader. Two vertex
producers share those shader families but do not share a packed-colour
convention:

- native BZR sprite/HUD vertices use the stock SM4 BGRA correction;
- Ogre-generated TextArea and ParticleFX vertices have already passed through
  Ogre's render-system `convertColourValue` and arrive in D3D11 RGBA order.

Applying the native correction to the second category swaps red and blue a
second time. The narrow fixes therefore live with the authored consumers:

- CR's `CR_OverlayFont` uses an Ogre-TextArea vertex program that preserves
  `iColor` order;
- EXU's weather materials inherit stock blend/depth behavior through an
  Ogre-particle vertex program that preserves `iColor` order.

Do not globally remove the stock/CR `.bgra` paths without a separate native
sprite qualification. Future generated overlays or billboards should select an
Ogre-colour material explicitly instead of inheriting a native BZR sprite
vertex program by accident.
