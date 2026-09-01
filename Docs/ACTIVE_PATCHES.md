# OpenShim Active Patches

This file tracks compatibility fixes whose reverse-engineering/root-cause phase is sufficiently complete to move into production implementation or runtime qualification.

An item belongs here only when the failure mechanism is understood well enough that the proposed patch can be narrowly scoped. Research-only hypotheses should remain in the regression/reverse-engineering backlog until that gate is met.

## Active

| Patch | Classification | Phase | Next gate |
| --- | --- | --- | --- |
| CLI multi-parameter / `-shellmap:<W>,<H>` parser repair | **Legacy 1.5 defect / OpenShim compatibility enhancement** | **Implemented, GOG qualified** | Qualify Steam runtime behavior, then promote out of Active. |

### CLI multi-parameter parser repair

Technical plan:

`Docs/CLI_MULTIPARAM_PARSER_ACTIVE_PATCH_20260831.md`

Primary RE deliverable:

`reverse_engineering/cli_multi_parameter_parser_parity_20260827.md`

Proven invariant:

```text
1.5 top-level strtok delimiter:   " ,"
Redux top-level strtok delimiter: " ,\t"
option-specific shellmap grammar: ":%d,%d"
```

The comma conflict exists in both 1.5 and Redux. Redux's added tab delimiter is a real parser difference but is not the cause of the reproduced multi-value failure.

Implementation:

`src/patches/cli_multiparam_parser.cpp`

Selected production strategy:

```text
DllMain (before the parser runs from WinMain)
  -> require exe file version 301
  -> require the stock bytes 20 2C 09 00 at 0x008F068C
  -> write 20 09 00 00  (" ,\t" -> " \t")
  -> stock parses everything, unsplit, with its own grammar
```

The delimiter string is referenced by exactly two instructions in the image,
both inside `FUN_007D5120` (`0x007D5156`, `0x007D5FD1`), so no other
tokenizer is reachable from this change. It lives in `.data`, which
SteamStub does not encrypt, so the write is valid on both stores at
`DLL_PROCESS_ATTACH`.

The originally proposed post-parser repair of `0x009183D4` / `0x009183C4`
was rejected on two findings:

- `0x009183D4` is a mode selector (1 = shellmap, 2 = largemap), not a width;
  writing a dimension there disables the feature at `FUN_00617110`;
- the orphaned token is consumed by the positional branch, which overwrites
  `DAT_00915540` -- the map-name buffer the shellmap consumer itself reads --
  along with the mission path and run state, so repairing the dimension
  globals alone would not have made the feature work.

Opt-out: `[Fixes] CliMultiParameterOptions = 0`.

The complete stock parser is not replaced, and OpenShim parses no
command-line values of its own.

### Promotion rule

Move the item out of **Active** only after:

- ~~production repair is enabled~~ (done);
- ~~malformed-input tests pass~~ (done);
- ~~unrelated CLI switches remain unaffected~~ (done, offline);
- ~~GOG 2.2.301 runtime qualification passes~~ (done 2026-09-01: control arm
  0x00D800D8 with map name "178", test arm 0x00B200D8 with the orphan gone);
- Steam runtime qualification passes;
- diagnostics prove the repair is applied only when intended.

Once those gates are satisfied, preserve the case as a permanent regression test rather than deleting the documentation.