# Redux Command-Line Parser Multi-Parameter Argument Parity Investigation

**Author:** OpenShim Reverse Engineering Team
**Date:** 2026-08-27
**Branch:** `research/cli-multi-parameter-parser-parity-20260827`
**Status:** Static defect confirmed / exact delimiter tail partly unresolved / live repair qualification pending

---

## Executive Summary

Scott ("Herp")'s report that Redux breaks comma-separated multi-parameter command-line arguments such as `-shellmap:216,178` is strongly supported by the shipped Redux parser.

The independently rechecked Redux path is:

```text
FUN_007d5120
    -> strtok(param_1, &DAT_008f068c)
    -> shellmap handler matches "shellmap"
    -> sscanf(local_8 + 9, ":%d,%d", &width, &height)
```

The important contradiction is structural: the tokenizer delimiter set contains a comma, while the `shellmap` handler expects that same comma to survive inside the token for `sscanf`.

Therefore a command such as:

```text
-shellmap:216,178
```

cannot reach the `shellmap` `sscanf` intact if the comma is consumed by `strtok` first.

### Evidence correction from the original report

The first revision stated that Redux uses the exact delimiter string:

```text
", \t\r\n"
```

The repo-tracked portable corpus does **not** establish that complete literal. The binary-string dump contains a printable sequence at RVA `0x4F068A` corresponding to:

```text
#< ,
```

and `DAT_008f068c` points two bytes into that sequence, establishing at least the printable delimiter prefix:

```text
" ,"
```

That is enough to prove that **space and comma are delimiters**. The portable ASCII-string artifact cannot prove whether additional non-printable delimiter bytes such as tab/CR/LF follow the comma, because those characters are not represented reliably by the printable string extraction.

Accordingly this report now distinguishes:

- **proven:** comma is in Redux's tokenizer delimiter set;
- **not fully proven from the portable repo corpus:** the complete delimiter literal beyond its printable prefix.

This correction does **not** weaken the root-cause finding.

---

## 1. Redux Parser Evidence

### 1.1 Tokenization

Repo-tracked decompile:

```c
undefined4 FUN_007d5120(char *param_1)
{
    ...
    local_8 = strtok(param_1, &DAT_008f068c);
    while (local_8 != (char *)0x0) {
        ...
        local_8 = strtok((char *)0x0, &DAT_008f068c);
    }
}
```

`strtok` destructively replaces delimiters with NULs in the mutable input buffer.

The printable binary evidence around `DAT_008f068c` establishes comma as one of those delimiters.

### 1.2 `shellmap` consumer

The same Redux decompile contains:

```c
iVar2 = _strnicmp(local_8 + 1, "shellmap", 8);
if (iVar2 == 0) {
    local_50 = 0x6c; // width default = 108
    local_54 = 0x59; // height default = 89
    iVar2 = sscanf(local_8 + 9, ":%d,%d", &local_50, &local_54);
    if (iVar2 == 1) {
        local_54 = local_50;
    }
    DAT_009183d4 = 1;
    _DAT_009183c4 = local_54 << 0x10 | local_50;
}
```

The consumer explicitly requires a comma between two integers. Because the tokenizer treats comma as a delimiter, the second value cannot remain in the same token.

### 1.3 Direct defect model

For:

```text
-shellmap:216,178
```

the structurally expected Redux tokenization is:

```text
-shellmap:216
178
```

The first token causes `sscanf(..., ":%d,%d", ...)` to return `1`; stock fallback then sets:

```text
width  = 216
height = 216
```

The second token no longer has an option prefix and enters the parser's non-option/positional path.

This is sufficient to classify the `shellmap` two-value syntax as **broken in stock Redux by parser construction**.

---

## 2. 1.5 Comparison — Evidence Grade

The original investigation reports that Battlezone 1.5 tokenizes on whitespace without comma and therefore preserves:

```text
-shellmap:216,178
```

as one token for the same `:%d,%d` conversion pattern.

That comparison came from the local 1.5 executable/PDB research environment. The current portable OpenShim repository does not retain an equivalent complete 1.5 command-line decompile from which this audit could independently reconstruct the tokenizer literal.

Therefore the correct wording is:

- **Redux defect itself:** confirmed from repo-tracked shipped Redux evidence.
- **Specific 1.5 tokenizer contrast:** previously reported static comparison; retain as high-confidence historical evidence, but do not describe it as independently repo-reproduced in this audit.

A future archival improvement would be to commit the minimal 1.5 disassembly/decompile excerpt or byte evidence for the tokenizer and `shellmap` handler so the parity comparison is portable.

---

## 3. Recovered Redux Option Table

The following options are visible in the inspected `FUN_007d5120` decompile. This is a decompiler-recovered table, not a public supported-CLI contract.

| Option | Syntax / separator | Relevant behavior |
| --- | --- | --- |
| `multi` / `nomulti` | flag | multiplayer override |
| `win` / `fullscreen` | flag | display mode |
| `rawinput` / `norawinput` | flag | raw input toggle |
| `noshell` | flag | bypass shell |
| `flagfile:` | `:` | flagfile string |
| `net:` / `net=` | `:` or `=` | network provider (`steam`, `gog`, `cp`, `bzr`) |
| `renderer:` / `renderer=` | `:` or `=` | renderer selection |
| `platform:` / `platform=` | `:` or `=` | platform override |
| `resave` | flag | resave mode |
| `asciisave` / `binarysave` | flag | save format |
| `shellmap` | `:W,H` | **two-value comma syntax broken by tokenizer** |
| `largemap` | `:N` | one-value map dimension |
| `nobodyhome` | flag | no player vehicle |
| `nointro` | flag | skip intro |
| `exitafterload` | flag | exit after load |
| `saveafterload` | flag | save after load |
| `edit` / `startedit` | flag | editor controls |
| `console` / `develop` | flag | developer controls |
| `showunloc` | flag | localization key display |
| `connect_lobby` | `=` payload | lobby connection |
| `connect-galaxy-lobby` | `=` payload | GOG lobby connection |
| `nickname=` | `=` | nickname override |
| `iorecord` / `noiorecord` | flag | I/O recording |
| `netpktlog` / `nonetpktlog` | flag | packet logging |
| `bzrnetlog`, `bzrnetlog=`, `nobzrnetlog` | flag/value | BZRNet logging |
| `netlog`, `netlog=`, `nonetlog` | flag/value | network logging |
| `nohgtsmoothing` / `dohgtsmoothing` | flag | heightfield smoothing toggle |
| `enablerenderselection` / `disablerenderselection` | flag | renderer-selection control |
| `disablemods` | flag | disable mods/workshop content |
| `iprelay` / `ipdirect` | flag | network path selection |
| `bzrserver=` | `=` | BZR server target |
| `bzrnetport=` | `=` | network port |
| `datadir=` | `=` | data directory |
| `zixlogindex` | flag | index logging |

The `nohgtsmoothing` / `dohgtsmoothing` options are relevant to the separate HGT compatibility investigation, but this report makes no claim about whether those options are exposed, documented, or sufficient for every terrain regression.

---

## 4. Validation Matrix — Static/Model vs Live

The original report labelled this section "Runtime Validation" even though the committed test is an offline parser model. That wording is corrected here.

| Case | Input | Stock/parser-model expectation | Legacy/parity expectation | Evidence status |
| --- | --- | --- | --- | --- |
| canonical two-value syntax | `-shellmap:216,178` | split at comma; W=216, H=216; orphan `178` | W=216, H=178 | **Static defect confirmed; live run desirable** |
| one-value fallback | `-shellmap:216` | W=216, H=216 | same fallback | **Supported by decompile/model** |
| control single-value option | `-largemap:16` | parses 16 | parses 16 | **Supported by decompile/model** |
| control flag | `-disablemods` | flag processed | flag processed | **Supported by decompile/model** |
| equals separator | `-shellmap=216,178` | stock handler expects `:` | not established as 1.5 syntax | **Do not call parity requirement** |
| quoted comma payload | `-shellmap:"216,178"` | `strtok` is not quote-aware | not established as 1.5 syntax | **Optional tolerance only** |
| spaces inside argument | `-shellmap: 216, 178` | tokenized into separate pieces | not established as 1.5 syntax | **Optional tolerance only** |
| duplicate `shellmap` options | two occurrences | stock ordering behavior needs preservation | last-wins is plausible but should be verified | **Implementation test case, not parity proof** |

### Key correction

Only syntax proven to be part of the compatibility target should be described as **legacy parity**. Supporting `=` syntax, quotes, or extra whitespace may be reasonable OpenShim robustness, but those are extensions unless 1.5 evidence establishes them.

---

## 5. Offline Test Suite Status

PR #69 adds:

```text
tests/cli_parser_tests.cpp
```

The test models:

- Redux-style comma tokenization;
- the canonical `-shellmap:216,178` failure (proven parity);
- a proposed pristine-command-line parser/repair;
- optional tolerance cases (`-shellmap=...`, quoted, whitespace) explicitly marked as extensions, not parity.

The test was reported as manually compiled with `g++` and passing.

**Update 2026-08-28:** `tests/cli_parser_tests.cpp` is now registered in
`tests/CMakeLists.txt` (`cli_parser_tests` executable, `add_test` via CTest).
A standalone CMake `configure` + `build` + `ctest` proves the model compiles
and runs, and the normal MSVC `Build Win32` workflow now includes it. See the
local verification notes in this PR for the `ctest -R cli_parser` output.
This is still an **offline model test**, not a live Battlezone runtime
validation – see §7.

---

## 6. OpenShim Repair Architecture

The narrow repair strategy remains preferable to replacing Redux's whole parser.

OpenShim already has an immutable/pristine command-line capture for renderer-profile handling. A compatibility repair can reuse that snapshot to recover only the affected multi-value argument.

### Requirements

1. Parse the pristine snapshot without allowing Redux's destructive `strtok` mutation to erase the comma.
2. Restore only **proven legacy syntax** by default, starting with:
   ```text
   -shellmap:W,H
   ```
3. Preserve stock ordering semantics if multiple relevant options are present.
4. Apply the correction only after the stock parser has initialized the affected state and before that state is consumed.
5. Resolve/validate destination addresses rather than relying on unchecked fixed absolute addresses across storefronts/builds.
6. Keep optional tolerant forms (`=`, quoting, whitespace normalization) separate from strict compatibility behavior.

### Candidate state

The current decompile shows:

```text
DAT_009183d4  = shellmap mode
_DAT_009183c4 = (height << 16) | width
```

These are useful targets for a narrow post-parse fixup, but implementation must verify their resolved addresses and timing on the supported GOG/Steam executables.

---

## 7. Required Live Qualification

Before calling the production repair proven, run at minimum:

1. stock Redux with `-shellmap:216,178` and capture the resulting parser/state/load behavior;
2. OpenShim repair enabled with the same command and verify W=216/H=178;
3. `-shellmap:216` control to preserve one-value fallback;
4. `-largemap:16` control;
5. normal startup with no affected option;
6. `-disablemods` plus canonical `shellmap` to ensure unrelated option processing is preserved;
7. Steam and GOG if the target globals/resolution seam differs.

If available, run the canonical command on 1.5 as a direct parity control.

---

## 8. Final Evidence Classification

| Claim | Classification |
| --- | --- |
| Redux `FUN_007d5120` tokenizes with `strtok(..., &DAT_008f068c)` | **Directly verified** |
| Redux tokenizer delimiter set contains comma | **Directly supported by repo portable corpus** |
| Complete delimiter literal is exactly `", \t\r\n"` | **Not proven from portable corpus; printable prefix establishes `" ,"`** |
| Redux `shellmap` handler expects `:%d,%d` | **Directly verified** |
| Comma tokenization breaks canonical two-value `shellmap` syntax | **Static root cause confirmed** |
| 1.5 preserves comma in the same syntax | **Previously reported 1.5 static comparison; portable archival evidence desirable** |
| New offline test is part of normal CTest/CI | **False at current PR head** |
| `=` / quoted / whitespace-tolerant forms are required 1.5 parity | **Not established** |
| Narrow pristine-snapshot fixup is preferable to replacing global parser | **Recommended architecture; implementation not yet qualified** |
