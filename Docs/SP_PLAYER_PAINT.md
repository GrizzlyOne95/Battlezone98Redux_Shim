# Single-player player paint

Design: item 17 in `Docs/APPROVED_DESIGNS.md`. OpenShim owns the setting; Campaign Reimagined (CR) does the painting.

## What OpenShim does

- Options > Video > Effects > **Paint** stores `[SinglePlayer] PlayerPaint` in `openshim.ini`.
- It paints nothing itself. No engine hook, no patch site, no new shader code.
- The row applies on next use: the getter below re-reads the ini on every call.

| Row choice | Ini value | CRTeamSkins entry |
| --- | --- | --- |
| Stock (default) | `stock` | none |
| Green digital camo | `host` | `T.HOST` (camo, ISDFC green) |
| Red | `t2` | guest team 2 tint |
| Blue | `t3` | guest team 3 tint |
| Gold | `t4` | guest team 4 tint |

The values are the `key` fields in CR's `Scripts/CRTeamSkins.lua`. A missing or unrecognised ini value reads as `stock`.

## Getter contract for CR

SDK export `OpenShimGetPlayerPaint` (winmm.dll), `const char* WINAPI OpenShimGetPlayerPaint(void)`:

- Returns one of `"stock"`, `"host"`, `"t2"`, `"t3"`, `"t4"`. Never null when OpenShim is loaded.
- Returns `"stock"` in network games (local player net id non-zero): co-op keeps its fixed host and guest paint.
- The pointer is a static string literal; the caller does not free it.
- When the provider is unavailable (no OpenShim winmm) the export returns `"stock"` too, so a binding never sees null.
- Net id 0 also holds in the shell, the lobby and before a session connects. CR must therefore also skip the SP rule when Lua `IsNetGame()` is true, so a co-op mission that calls the getter early never paints.

The Lua name is decided by the EXU binding that wraps the export. EXU is a separate repo, so the Lua function (suggested `exu.GetPlayerPaint()`) must be added there before CR can call it. Until then CR can read `[SinglePlayer] PlayerPaint` itself only if it has an ini reader, which it does not today.

CR should call it when the player's craft changes (mission start and each hop into another craft), not every frame, and treat `"stock"`, nil or an unknown key as "do not paint". The SP rule applies only to the player's own craft.

## Limits

- Only the `en-high*` enhanced techniques paint; other quality levels show stock paint.
- Needs CR: the masks, `Materials/CR_TeamSkins.material` and the clone path live there.
- Only the existing patterns. A new pattern needs a new per-unit mask set from CR's `Build-TeamSkins.py`.
- Single player only. Nothing is sent over the network.

## Verification

Host tests and CI cover the ini key, the options row, localization and the export table. The in-game result (row change, then a visible repaint of the player's ship in CR) is not yet live-tested.

Live checklist:
1. SP: change the Paint row, start a CR mission, and confirm the player's ship shows the chosen paint; hop into another craft and confirm the paint follows.
2. Stock: the ship shows stock paint and AI units keep theirs.
3. Co-op host and client: the getter returns `"stock"` when called from Lua `Start()`, and co-op paint is unchanged.
