# CLI Multi-Parameter Parser Compatibility Patch

**Date:** 2026-08-31  
**Status:** **ACTIVE PATCH — IMPLEMENTATION READY**  
**Scope:** Battlezone 98 Redux 2.2.301 / OpenShim  
**Patch class:** Legacy 1.5 parser defect compatibility repair, not a Redux-only regression

## Summary

Battlezone command-line options whose value syntax contains a comma can be corrupted before their option-specific parser sees the value.

The canonical reproduced case is:

```text
shellmap:216,178
```

The stock top-level tokenizer treats comma as a delimiter. It therefore transforms the intended single token into two tokens:

```text
shellmap:216
178
```

The later `shellmap` handler still expects the format:

```text
:%d,%d
```

but receives only `:216\0`. `sscanf` returns one successful conversion, and the stock handler ultimately produces a square `216 x 216` result instead of `216 x 178`. The orphaned `178` token is then available to the generic positional path.

This behavior is now proven in both Battlezone 1.5 and Battlezone 98 Redux. The defect is therefore **inherited legacy parser behavior**, not a Redux-specific regression.

OpenShim will repair the affected value from its already-preserved pristine process command line rather than replacing the entire stock parser.

## Reverse-engineering source

Primary report:

```text
reverse_engineering/redux_cli_multiparam_parser_root_cause_20260831.md
```

The report records the full binary trace, file/RVA evidence, corpus references, hashes, Steam/GOG comparison, offline parser model, and candidate patch strategies.

## Proven native chain

### 1. OpenShim already preserves the pristine command line

OpenShim snapshots `GetCommandLineA()` during process attach before the game performs destructive tokenization.

Relevant production storage:

```text
src/patches/ogre_render_profile.cpp:43
s_commandLineSnapshot[1200]
```

This snapshot must remain preserved. It is now a required compatibility input for this patch in addition to renderer/backend handling.

### 2. Redux obtains the CRT command-line buffer

GOG Redux:

```text
battlezone98redux.exe:0x83EF53
A1 18 97 86 00
```

This obtains `MSVCR120!_acmdln` through:

```text
0x00869718 -> char *
```

By this point OpenShim has already captured the original process command line at approximately process-start time.

### 3. Redux destructively tokenizes comma/space/tab

The relevant Redux parser is:

```text
FUN_007D5120
VA 0x007D5120
```

At:

```text
0x007D515F
FF 15 CC 94 86 00
call [0x008694CC]    ; strtok
```

The delimiter bytes at `DAT_008F068C` are:

```text
20 2C 09 00
" ,\t"
```

Therefore a value containing a comma is split before its option-specific `sscanf` parser executes.

Corpus reference:

```text
reverse_engineering/repo_corpora/bzr_gog_best_effort/ghidrecomp/results/bins/
battlezone98redux.exe-6777ca/decomps/FUN_007d5120-007d5120.c
```

### 4. `shellmap` still expects a comma-separated pair

Redux later reaches the `shellmap` parse path around:

```text
0x007D55EA - 0x007D5611
```

The handler calls `sscanf` with:

```text
":%d,%d"
```

For the original input:

```text
shellmap:216,178
```

the top-level `strtok` has already inserted a NUL at the comma. The handler therefore receives effectively:

```text
":216\0"
```

`sscanf` returns:

```text
res = 1
```

and the resulting stock state becomes:

```text
DAT_009183D4 = 216
_DAT_009183C4 = 216
```

rather than:

```text
width  = 216
height = 178
```

The observed packed result is consequently:

```text
0x00D800D8
```

instead of:

```text
0x00B200D8
```

The trailing `178` survives only as a separate positional token.

## Battlezone 1.5 parity result

Battlezone 1.5 contains the same fundamental contradiction.

Its `ProcessCommandLine` path uses delimiter bytes at:

```text
bzone.exe:0x006311D8
20 2C 00
" ,"
```

and the corresponding `shellmap` handler uses the same comma-bearing `sscanf` grammar around:

```text
bzone.exe:0x546847
```

Therefore:

```text
Top-level grammar: comma terminates a token
Option grammar:    comma separates two values inside one token
```

Both grammars cannot be satisfied simultaneously.

### Compatibility classification

The first literal 1.5-vs-Redux tokenizer divergence is that Redux adds tab (`0x09`) to the delimiter set:

```text
1.5:   " ,"
Redux: " ,\t"
```

That added tab is **not** the root cause of the multi-parameter failure. The defect is the comma delimiter shared by both builds.

Accordingly this patch must be documented and implemented as:

> **Legacy 1.5 CLI parser defect / OpenShim compatibility enhancement**

It must not be described as a Redux-only parser regression.

## Active patch strategy

### Selected strategy: post-parser narrow repair

Use the existing pristine `s_commandLineSnapshot`, parse only the affected multi-value option with whitespace-only token boundaries, and repair the native state after the stock parser returns but before the first known consumer.

Relevant Redux control-flow points from the RE report:

```text
FUN_007D5120 return: 0x007D5FE9
caller:              0x00618D0E
first known consume: before 0x00618D2C
```

For `shellmap`, the compatibility repair writes only:

```text
0x009183D4
0x009183C4
```

with the fully parsed dimensions recovered from the pristine snapshot.

### Why this strategy is preferred

This approach intentionally leaves the stock parser in control of all unrelated behavior.

Benefits:

- preserves stock positional argument handling;
- preserves all unrelated option aliases and side effects;
- avoids reimplementing the entire historical command-line grammar;
- avoids depending on the already-mutated CRT command-line buffer;
- uses an immutable command-line copy OpenShim already owns;
- repairs only state known to be corrupted by the top-level comma tokenizer;
- minimizes compatibility risk for unknown/custom launch arguments.

A wholesale replacement of `FUN_007D5120` is not justified by the current evidence.

## Initial production scope

The first production patch should be deliberately narrow.

Recognize the canonical form:

```text
shellmap:<width>,<height>
```

from `s_commandLineSnapshot` using **whitespace-only option boundaries**.

Requirements:

1. Parse both dimensions successfully.
2. Reject partial parses.
3. Reject additional unexpected comma components for the initial patch.
4. Apply reasonable integer/range validation consistent with the stock consumer.
5. Do not reinterpret unrelated comma-bearing arguments.
6. Do not modify stock parser token storage.
7. Write only the native width/height globals after stock parsing and before their first known consumption.
8. Emit diagnostic logging when a repair is applied.

The repair should be idempotent: if the stock result already matches the valid pristine pair, no state change is needed.

## Required tests

An offline model already exists in:

```text
tests/cli_parser_tests.cpp
```

It reproduces the destructive delimiter behavior. No production parser replacement is currently enabled.

The production patch must add/retain coverage for at least:

```text
shellmap:216,178
shellmap:1920,1080
shellmap:216,216

shellmap:216
shellmap:abc,178
shellmap:216,abc
shellmap:,178
shellmap:216,
shellmap:216,178,999
```

Also test interaction with surrounding arguments:

```text
<other-option> shellmap:216,178 <other-option>
<other-option>\tshellmap:216,178\t<other-option>
```

and verify that:

- unrelated switches remain unchanged;
- renderer/backend launch options remain functional;
- `-disablemods` remains a valid single-value/no-value parser baseline where applicable;
- executable paths and quoted arguments containing spaces remain unaffected;
- an unrelated argument containing commas is not silently rewritten;
- the orphan positional token created by the stock parser does not influence repaired `shellmap` state.

## Runtime acceptance

Patch acceptance requires a real-process qualification pass on supported Redux binaries.

### Positive case

Launch with:

```text
shellmap:216,178
```

and prove before the first consumer that native state contains:

```text
width  = 216
height = 178
```

rather than stock:

```text
width  = 216
height = 216
```

### Negative/control cases

Prove that:

- no `shellmap` option leaves native state entirely under stock control;
- malformed `shellmap` values are not "helpfully" rewritten into new semantics;
- single-value CLI options remain byte-for-byte behaviorally unaffected;
- command ordering does not change the result;
- Steam and GOG produce equivalent repaired behavior.

## Binary qualification

Hashes recorded by the root-cause report:

### Redux GOG 2.2.301

```text
SHA-256: 8D71F56C...
Size:    5425152
```

### Battlezone 1.5

```text
bzone.exe
SHA-256: 138FA21F...
Size:    3495936
```

### Battlezone 1.5 symbols

```text
bzint.pdb
SHA-256: AF05120B...
Size:    17501184
```

Steam-vs-GOG Redux parser parity for the investigated path is proven in the RE report.

## Patch status checklist

- [x] Preserve pristine process command line before CRT mutation.
- [x] Prove Redux top-level delimiter set.
- [x] Prove `shellmap` comma-bearing handler grammar.
- [x] Prove exact truncation and bad width/height result.
- [x] Reproduce defect in offline parser model.
- [x] Compare against Battlezone 1.5.
- [x] Classify as inherited 1.5 defect rather than Redux-only regression.
- [x] Select narrow repair point and native state targets.
- [ ] Implement production post-parser repair.
- [ ] Add production-facing diagnostics.
- [ ] Run malformed-input regression suite.
- [ ] Validate supported GOG executable at runtime.
- [ ] Validate supported Steam executable at runtime.
- [ ] Confirm no side effects on renderer/backend and other CLI controls.
- [ ] Promote to fixed only after runtime acceptance passes.

## Documentation invariant

Do not regress this item back to "RE needed." The parser root cause and 1.5 parity question are closed.

The remaining work is **implementation and runtime validation** of the narrow OpenShim repair.

Future research may inventory other stock options whose internal grammar also uses delimiters consumed by the top-level tokenizer, but that is not a prerequisite for shipping the scoped `shellmap` compatibility patch.
