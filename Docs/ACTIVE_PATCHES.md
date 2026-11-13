# OpenShim Active Patches

This file tracks compatibility fixes whose reverse-engineering/root-cause phase is sufficiently complete to move into production implementation or runtime qualification.

An item belongs here only when the failure mechanism is understood well enough that the proposed patch can be narrowly scoped. Research-only hypotheses should remain in the regression/reverse-engineering backlog until that gate is met.

## Active

| Patch | Classification | Phase | Next gate |
| --- | --- | --- | --- |
| CLI multi-parameter / `shellmap:<W>,<H>` parser repair | **Legacy 1.5 defect / OpenShim compatibility enhancement** | **Implementation ready** | Implement the post-parser repair from the pristine command-line snapshot, then qualify Steam + GOG runtime behavior. |
| Producer rally points (`[Gameplay] ProducerRallyPoints`) | **OpenShim gameplay enhancement** | **Implemented, runtime qualification pending** | Live SP test of the checklist in `Docs/PRODUCER_RALLY_POINTS.md` (V sets, Shift+V clears, new units drive to the rally, HUD marker shows while selected, scavengers/constructors skipped, editor and MP untouched). |
| Auto-group new units (`[Gameplay] AutoGroupNewUnits`) | **OpenShim gameplay enhancement** | **Implemented, runtime qualification pending** | Live SP test of the checklist in `Docs/PRODUCER_RALLY_POINTS.md` (new tank on an F1-F7 group, all-same-ODF grouping and the 10-unit cap, save/load keeps the group, MP untouched). |
| HUD group strip (`[Gameplay] GroupStrip`) | **OpenShim UI enhancement** | **Implemented, runtime qualification pending** | Live test of the checklist in `Docs/PRODUCER_RALLY_POINTS.md` ("Group strip": unitName labels, no overlap with the scrap/pilot gauge from 640x480 to 4K, hidden in pause/shell/satellite). |

### CLI multi-parameter parser repair

Technical plan:

`Docs/CLI_MULTIPARAM_PARSER_ACTIVE_PATCH_20260831.md`

Primary RE deliverable:

`reverse_engineering/redux_cli_multiparam_parser_root_cause_20260831.md`

Proven invariant:

```text
1.5 top-level strtok delimiter:   " ,"
Redux top-level strtok delimiter: " ,\t"
option-specific shellmap grammar: ":%d,%d"
```

The comma conflict exists in both 1.5 and Redux. Redux's added tab delimiter is a real parser difference but is not the cause of the reproduced multi-value failure.

Selected production strategy:

```text
process attach
  -> preserve pristine GetCommandLineA()
  -> let stock Redux parser run unchanged
  -> after FUN_007D5120 returns, re-read only shellmap:<W>,<H>
     from the pristine snapshot using whitespace-only token boundaries
  -> validate both dimensions
  -> repair 0x009183D4 / 0x009183C4
  -> continue before the first known consumer at 0x00618D2C
```

Do not replace the complete stock parser for this patch.

### Promotion rule

Move the item out of **Active** only after:

- production repair is enabled;
- malformed-input tests pass;
- unrelated CLI switches remain unaffected;
- GOG 2.2.301 runtime qualification passes;
- Steam runtime qualification passes;
- diagnostics prove the repair is applied only when intended.

Once those gates are satisfied, preserve the case as a permanent regression test rather than deleting the documentation.