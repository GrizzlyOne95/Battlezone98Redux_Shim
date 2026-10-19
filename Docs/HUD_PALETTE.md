# Native HUD colors

OpenShim Options → HUD → HUD Colors groups player preferences for radar,
cockpit meters and command/selection bars. The existing scrap/pilot colors,
Stock/Legacy layout and reticle controls remain independent.

## Controls

All settings live in `[Display]`. `HudColorPreset` defaults to `Stock` and
offers `Classic` and `HighContrast` as base palettes. Each color role defaults
to `Default`, meaning the selected base palette. Explicit per-role choices
override that base; changing the base does not discard those choices.

| Keys | Scope |
| --- | --- |
| `RadarGridColor` | Projected terrain grid lines; retains native alpha. |
| `RadarBackgroundOpacity` | Radar backdrop only, Default or 0–100 percent. |
| `RadarFriendlyColor`, `RadarEnemyColor`, `RadarNeutralColor` | Normal radar contacts; native dimming and animated alpha remain. |
| `HullHighColor`, `HullMediumColor`, `HullLowColor` | Cockpit health at ≥50%, 25–<50%, and <25%. |
| `AmmoHudColor` | Cockpit ammo bar and label; native shot-cost marker and text remain. |
| `UnitHealthHighColor`, `UnitHealthMediumColor`, `UnitHealthLowColor` | Command/selection health bars using the same native thresholds. |
| `UnitAmmoColor` | Command/selection ammo fill, independent of cockpit ammo. |
| `UnitEmptyColor` | Unfilled command/selection bar portions. |

Color choices: Default, White, Blue, Green, Cyan, Amber, Magenta, Red, Yellow.
The INI also accepts `#RRGGBB` or `0xAARRGGBB`. Radar line/contact overrides
preserve native alpha instead of honoring a custom alpha. Missing, Default
and malformed colors inherit the base palette. Unknown base palettes retain
Stock. A fresh launch with Stock and all roles Default installs none of these
adapters. Returning to those values after customization makes the installed
wrappers forward native draws; it does not remove live code redirects.

Unit bars retain their native recent-damage flash. Radar alert/special paths
retain native appearance. Disguised or ambiguous contact identities retain
native colors; classification must not disclose a hidden actual team.
This is local presentation only and changes no simulation, visibility, radar
range, health/ammo values, fill smoothing, thresholds, warning audio or layout.

## Native boundary

The adapter redirects guarded, semantic draw calls instead of overwriting
shared engine palette values. Addresses and expected bytes are named catalog
rows. Before installation, all rows must bind; unsupported builds stand down.
The initial adapter is GOG 2.2.301 only. Steam, Proton/Wine and other renderer
lanes require separate runtime qualification before release.

The projected grid color is substituted only during its own native submit,
then restored. Sized sprite tint and flags are scoped to backdrop/ammo draws;
the native tint is restored on exit. Unit bars forward the original rectangle,
ratio and empty/fill drawing. No game-object or grid pointer survives a draw.
Configuration snapshots are serialized with an SRW lock; hooks do not read
the INI or allocate.

## Evidence and acceptance

Released GOG executable SHA-256:
`8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413`.
Initial native capture PID 43392, 2026-10-19, verified direct CALL bytes and
targets against that image. Observations establish nine sized-sprite stack
arguments, cockpit label/fill IDs and clipping, grid dimensions 81×81 and
native grid color `0x3000FF00`. Static command gauge calls pass five arguments
with 0x14 caller cleanup. Static health selectors establish 0.25/0.5 thresholds.

Local GOG DX11 qualification, 2026-10-19:

- PID 37352, fresh Stock/Default: all 30 palette code guards match the released
  image, including the original draw CALLs. No color redirects are installed.
- PIDs 27776 and 24184: custom grid tint retains its changing native alpha and
  restores the original grid word after every observed submission. Cockpit
  health produces cyan/amber/magenta across the native thresholds; ammo label
  and fill use independent yellow. Backdrop draw alpha is 0x3F at 25 percent.
  Ten inspected shared palette colors remain unchanged.
- PID 13336: normal friendly/enemy contact color results are cyan/amber.
  When the enemy's perceived team differs from its actual team, its native
  color is retained. That trace ended during a graceful game exit; its partial
  records qualify the observed classifications, not a completed long session.
- PID 49932: all fifteen controls fit the compact options panel. Classic and
  High Contrast save/apply through the UI; Stock restores original cockpit
  health results green/yellow/red. The native color helper was sampled at
  three ratios after each change. Unit Ammo saves independently of cockpit
  ammo. This is not a rendered command-bar qualification.
- PID 12060: deliberately changing only the grid submit guard refuses the
  complete adapter group. ReadProcessMemory confirms all 30 source code guards,
  including every draw CALL, remain original. The deployed catalog is restored
  afterwards and all three DLLs/catalog match their source hashes.

Release Win32 solution build, all 116 Windows CTest cases, INI completeness
(228 settings), conservative defaults, writer and migration checks pass.
The new portable palette policy test also passes GCC `-Wall -Wextra -Werror`
under WSL. This does not qualify Wine/Proton or the full Linux host suite.

Remaining acceptance: rendered command/selection bars across their seventeen
native branches, recent-damage flash appearance, save/load, camera/vehicle
changes, faction/UI-scale variants, multiplayer, long sessions and the full
platform/renderer matrix. Aimed-at-unit vertical bars use separate baked
green/yellow/red sprites; they retain native art/colors in this implementation.
Recoloring those needs a neutral mask or a dedicated draw adapter and is a
separate follow-up. Raw probes and captures stay under ignored `bin/hud-colors/`.
