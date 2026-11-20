# Single-player player paint

Design: item 17 in `Docs/APPROVED_DESIGNS.md`. OpenShim paints the ship itself; no mod, EXU or Lua is needed.

## What it does

- Options > Video > Effects > **Paint** stores `[SinglePlayer] PlayerPaint` in `openshim.ini`. The row applies live.
- Only the local player's own ship is painted. AI and other units keep stock paint.
- When the player leaves a ship (hop out, switch craft), that ship gets its stock paint back and the new ship is painted.
- Off in network games: co-op keeps Campaign Reimagined's own team paint.
- Visible only on DX11 Enhanced at the `en-high*` quality. Lower quality levels keep stock paint, because only the en-high programs read the mask.

| Row choice | Ini value | teamPaint (sRGB r, g, b, on) |
| --- | --- | --- |
| Stock (default) | `stock` | none |
| Red | `t2` | 0.80, 0.18, 0.12, 2.0 |
| Blue | `t3` | 0.20, 0.38, 0.85, 2.0 |
| Gold | `t4` | 0.90, 0.68, 0.12, 2.0 |

The tints are CR's co-op guest tints (`Scripts/CRTeamSkins.lua`). A missing or unknown value (including the old `host`) reads as `stock`. The variants are a data table, `SpPlayerPaint::kVariants` in `include/sp_player_paint_policy.h`: a new solid tint is one row there plus one Options value. Camo needs an RGB pattern mask, which the single-channel masks below cannot carry.

## How it works

Shader (`openshim_enhanced_base-sm4.hlsl`):
- `TEAM_PAINT_ENABLED` no longer needs `ACT_MAP_ENABLED`. Without actMap, `teamMap` takes the register right after `brdfLut` (t10 PSSM, t8 shadow receiver, t7 plain). With actMap (CR's wrappers define both), the registers are unchanged (t11/t9/t8).
- `OSE_TEAM_MASK_R` reads the paint weight from `.r` instead of `.a`. The paint is skipped unless `teamPaint.a > 1.5`.
- The `OSE_BaseIBLHigh*_fragmentHLSL4` programs define both and declare `teamPaint` (default 0, so off).

Import: `scripts/generate_stock_enhanced_base.py` adds a `teamMap` unit after `brdfLut` in each `OSE_BaseIBLHigh*` pass of `openshim_stock_bzbase.import`. It is bound to `openshim_team_off.dds` (4x4 BC4, zero), which is a required Enhanced resource. Regenerate from CR commit `bc1487ac` Materials; later CR materials use `CR_ShimOrStock_*` programs the generator does not map yet.

Native (`src/patches/sp_player_paint.cpp`, render thread, frame start):
1. At the first world render of a mission: read the setting, then gate on net game, DX11 Enhanced and the Ogre exports. Each outcome writes one `[PAINT]` line, only when it changes.
2. Every frame: resolve the player handle's root Entity. If it is not the last painted ship, put the last ship's materials back (when it is still in the scene).
3. For each SubEntity whose stock material has a mask, clone its current material as `<current>@ospaint_<variant>`. In every en-high pass with a `teamMap` unit and a `teamPaint` constant, bind the mask and set `teamPaint`. Then assign the clone to that SubEntity only.
   - A pass that also binds `actMap` runs a CR program, which reads alpha. It gets CR's own crteam mask, taken from CR's `<material>_tm` twin. Without CR's twin, that pass is skipped.
   - GPU skinning: the clone of a skinned clone keeps its vertex programs, and the change is handed to `OpenShimAdoptSurfaceVariant`. If GPU skinning refuses, the SubEntity is put back and stays stock.
4. At mission end, the ship's materials are restored and every clone is removed from the MaterialManager. At world teardown the clones are removed. A load or restart starts clean.

Each material that cannot be painted is logged once per mission, with the reason: no mask, no en-high technique, no teamMap pass, no teamPaint constant, CR program without CR mask, or clone failed. The frame also logs the active material scheme when it changes, so en-medium shows up in the log.

Faults: SEH and C++ exceptions are caught per frame. A fault restores the ship, removes the clones and turns the feature off for the session. There is no engine patch and no `patches.json` row.

## Mask pipeline

`scripts/build_sp_paint_masks.py --game-dir "<Redux>" --cr-dir "<Campaign-Reimagined>" [--check]`:
- reads CR's `Materials/CR_TeamSkins.material` (115 `<material>_tm` twins) and keeps the 71 whose `<material>` is a stock Redux material with the same DiffuseMap. The 44 CR-only twins (`*_nacjet`, `*_hpmount`, `avsav00`, `avsav14`) are skipped.
- converts each used `crteam_<stem>_d.dds` (512x512 DXT5, full mips, weight in alpha) to `resources/renderer/enhanced/openshim_paint_<stem>.dds`, BC4 (FourCC `ATI1`), full mips. A DXT5 alpha block is bit-identical to a BC4 block, so the conversion is lossless (checked: the decoded BC4 matches CR's alpha exactly).
- writes `openshim_team_off.dds` and `include/sp_player_paint_masks.inc` (material to mask table).

Output: 71 materials, 70 masks (one is shared), about 11.7 MB with the off texture. DXT5 would be about twice that. The masks are flat in `openshim/renderer/enhanced` because the deploy copy is not recursive.

## Verification

Host test `sp_player_paint_policy_tests` covers the variant table, the mask table and clone naming. The shader compile CI step compiles the new `OSE_BaseIBLHigh*` variants. Nothing here is live-tested yet.

Live checklist (CR off and on, DX11 Enhanced, en-high):
1. Each tint (Red, Blue, Gold) shows on the player's ship. `[PAINT] <material> -> <material>@ospaint_<key>` lines appear in the log.
2. Hop into another ship: the new ship is painted and the old one goes back to stock (`[PAINT] restored ...`).
3. AI ships of the same type stay stock.
4. Switch quality to en-medium: the ship shows stock paint and the log names the scheme.
5. Network game: `[PAINT] network game: player paint off`, and co-op paint is unchanged.
6. Reload the mission and restart it twice: `[PAINT] removed N clone material(s)` each time, with no growth in the clone count and no stale paint.
7. Change the row to Stock mid-mission: the ship goes back to stock at once.
8. BC4 loads on D3D11: a painted ship, not a blank or fully painted hull. A load failure shows up in Ogre.log for `openshim_paint_*.dds`.
