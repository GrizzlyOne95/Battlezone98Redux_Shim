# weaponMask = 00000 Follow Crash - Investigation Status

Date: 2026-08-24
Build: GOG `battlezone98redux.exe` 2.2.301. Status: **not reproduced on the
current build; no patch installed** (deliberately - see below). This report
records everything the next investigator needs.

## Prior art

- `reverse_engineering/howitzer_minelayer_weapon_mask_root_cause_20260817.md`
  mapped the weapon-mask subsystem exhaustively (1.5 vs Redux): ODF
  `weaponMask` is a decimal digit string; `GameObject::GameObject` decodes it
  into a 5-bit mask at `GameObject+0x218`; consumers are `FireAt`
  (`0x005CB140`) and `UnitTask::UpdateWeapon` (`0x00604130`);
  `Carrier::SetSelected` (`0x004D9880`) masks with `existant`.
- EXU `FeaturesToLookInto` item 49 records the original report and that no
  crash dump was ever attached to a follow crash.

## Static re-check of zero-mask safety (this pass)

Decompiled and audited every mask consumer found so far for `mask == 0`:

| function | address | zero-mask behaviour |
|---|---|---|
| UnitTask weapon init | `0x005FEDD0` | special-slot scan (`0x00605270`) returns `-1`; the `mask & ~(1<<slot)` step is guarded by `if (-1 < slot)`; best-weapon pick (`0x00466BE0`) pre-initialises all out-params and loops over mask bits only |
| special-slot scan | `0x00605270` | returns -1 / null weapon pointer cleanly |
| best-weapon pick | `0x00466BE0` | no set bits -> defaults returned, no indexing |
| Carrier::SetSelected | `0x004D9880` | `selected = mask & existant` = 0, benign |

No unguarded index or pointer derivation from a zero mask is visible in any
of these. Whatever crashes for affected users either lives in a path not yet
identified or requires additional state (see experiments).

## Live repro attempts (GOG 2.2.301, this workstation)

Harness: dedicated addon mod `addon\wmtest0` (lcbench-derived terrain,
hex-patched `msn_filename`/`TerrainName`; Lua drives spawns/orders; stock
`avtank.odf` copied into the mod with `weaponMask=00000`, weapons removed in
one variant). Telemetry via Lua `print` -> `logs\BZLogger.txt`.

| attempt | configuration | outcome |
|---|---|---|
| 1 | unarmed follower Follow(player), enemy waves attacking player | both followers died in combat; no crash |
| 2 | unarmed (no weapon slots at all + mask 00000) Follow(armed ally) | follows indefinitely; no crash after 60 s |
| 3 | same, sustained waves | no crash |

Notes for future attempts:

- Custom unit names need matching `.vdf`/`.mesh` assets ("no hardpoint named
  'GC1'" otherwise); overriding stock-named ODFs (`avtank.odf` inside the mod)
  avoids this while still allowing field edits.
- `baseName = "avtank"` inheritance does not resolve stock archive ODFs;
  ship a full copy instead.
- The two unhandled crashes at `exe+0xF92F4` in `openshim_crash.log`
  (2026-08-23) are LensFlare-constructor faults (`FUN_004F9250`,
  MaterialManager singleton read during teardown), unrelated to weaponMask.
- Historical workaround lore says "do not ship all-zero weaponMask"; if the
  crash predates the current exe revision, byte-drift may have moved or fixed
  it. Run `bzr-ghidriff` against any older redistributable exe before
  assuming the defect is current.

## Next experiments (in order)

1. Drive the order through the real command UI (select unit, issue Follow,
   click ally) rather than Lua `Follow()` - rules out a UI-command-only
   consumer.
2. Repeat with the followed object destroyed mid-follow, and with
   Formation/Defend2 orders.
3. Exercise retaliation paths: damage the unarmed follower so its AI runs
   FireAt/target selection without an explicit attack order.
4. If a crash lands, the shim crash logger (`openshim_crash.log` +
   minidump) gives module+RVA immediately; map through the corpus as done
   above.

## Why no patch ships now

Every known consumer is provably zero-safe, and forcing the mask non-zero
globally would change intentional no-fire behaviour (per the 2026-08-17
report, artillery/minelayer paths ignore the mask entirely). A speculative
guard would be unvalidatable dead code; per the work order this issue stays
unpatched until a repro exists.
