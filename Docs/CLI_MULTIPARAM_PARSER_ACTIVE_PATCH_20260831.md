# CLI Multi-Parameter Parser Compatibility Patch

**Date:** 2026-08-31  
**Status:** **IMPLEMENTED — GOG QUALIFIED, STEAM PARTIAL**  
**Scope:** Battlezone 98 Redux 2.2.301 / OpenShim  
**Patch class:** Legacy 1.5 parser defect compatibility repair, not a Redux-only regression

## Summary

Battlezone command-line options whose value syntax contains a comma can be corrupted before their option-specific parser sees the value.

The canonical reproduced case is:

```text
-shellmap:216,178
```

The stock top-level tokenizer treats comma as a delimiter. It therefore transforms the intended single token into two tokens:

```text
-shellmap:216
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
reverse_engineering/cli_multi_parameter_parser_parity_20260827.md
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
-shellmap:216,178
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
DAT_009183D4  = 1          ; mode selector, NOT a dimension
_DAT_009183C4 = 0x00D800D8 ; (height << 16) | width, both 216
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

### Selected strategy: narrow the parser's own delimiter set

Implemented in `src/patches/cli_multiparam_parser.cpp`. The four delimiter
bytes at `0x008F068C` are rewritten in place:

```text
0x008F068C   20 2C 09 00   " ,\t"   ->   20 09 00 00   " \t"
```

The string is referenced by exactly two instructions in the whole image,
both inside `FUN_007D5120`:

```text
0x007D5156  68 8C 06 8F 00  push offset 0x008F068C   ; strtok(cmdline, delims)
0x007D5FD1  68 8C 06 8F 00  push offset 0x008F068C   ; strtok(NULL, delims)
```

so the change cannot reach any other tokenizer. With the comma gone the
token is never split, `sscanf` returns 2, and no other native state is
touched at all.

Applied synchronously from `DllMain`, because the parser runs from WinMain
via the call at `0x00618D0E` long before `RunPatcher` reaches it.

`0x008F068C` is in `.data` (characteristics `0xC0000040`, writable,
non-executable), which SteamStub does not encrypt, so the write itself is
valid on both stores. The two `.text` push sites and the `":%d,%d"` format
site are checked as corroboration and logged, but are not required, because
at `DLL_PROCESS_ATTACH` a Steam image is still decrypting `.text` in stages
and requiring them would make the fix silently GOG-only. Identity therefore
rests on the exe file version (301) plus the exact bytes at a fixed, never
scanned address.

### Why the originally proposed post-parser repair was rejected

The first draft of this document proposed leaving the stock parser alone and
rewriting the parsed dimensions afterwards, from the pristine
`s_commandLineSnapshot`, at:

```text
FUN_007D5120 return: 0x007D5FE9
caller:              0x00618D0E
```

Two findings from reading the decompile through to the positional branch
rule that out.

**`0x009183D4` is a mode selector, not a width.** The consumer is
`FUN_00617110`, not anything near `0x00618D2C`:

```text
if (DAT_009183D4 == 1)
    FUN_0050F920(&DAT_00915540, _DAT_009183C4 & 0xFFFF, _DAT_009183C4 >> 16 & 0xFFFF);
else if (DAT_009183D4 == 2)
    FUN_0050FE80(&DAT_00915540, _DAT_009183C4);
```

Writing a dimension into `0x009183D4`, as the draft specified, would have
sent the dispatch down neither branch and disabled shellmap outright. Only
`_DAT_009183C4` carries dimensions, packed as `(height << 16) | width`.

**The orphaned token is consumed, not merely stranded.** `178` re-enters the
loop and takes the non-switch path, which writes:

```text
strncpy(&DAT_00945708, "178", 0x1000);   ; mission/save path
strncpy(&DAT_00915540, "178", 0x10);     ; map name
FUN_00434170(5);                         ; SetRunning(5)
DAT_0091556C = 1;
```

`DAT_00915540` is the same buffer the shellmap consumer above passes as the
map name. A post-parser repair of the dimension globals alone would hand the
consumer correct dimensions together with a map name of `"178"` and a changed
run state, so the feature would still not work. Reverting that collateral
means re-deriving the positional token as well, which is the parser
reimplementation the narrow strategy set out to avoid. Not splitting the
token in the first place avoids all of it.

### Accepted trade-off

A comma no longer separates arguments, so a command line that wrote
`-win,-nointro` where it meant `-win -nointro` now yields one unmatched
token. Space is the universal separator and every comma-bearing value is
broken today, so this is judged negligible. `[Fixes]
CliMultiParameterOptions = 0` restores stock tokenising.

### Why this strategy is preferred

It removes the contradiction instead of compensating for its output:

- the token is never split, so no orphan token is created and none of the
  positional-branch collateral above ever happens;
- stock keeps ownership of every value: OpenShim parses nothing, so there is
  no second grammar to drift out of step with the handler;
- it repairs every option in this parser whose value grammar contains a
  comma, not `shellmap` alone;
- four bytes in `.data`, no detour, no trampoline, no `.text` write, and
  nothing that can trip SteamStub's code-integrity check;
- idempotent and trivially revertible, with no ordering assumption between
  the parser and its consumers.

A wholesale replacement of `FUN_007D5120` remains unjustified.

## Production scope

Note the switch prefix. `FUN_007D5120` only reaches the option chain for
tokens beginning `/`, `-` or `+`; a bare `shellmap:...` goes to the
positional branch and is treated as a mission name. The canonical form is:

```text
-shellmap:<width>,<height>
```

What the patch does:

1. Read `[Fixes] CliMultiParameterOptions` from `openshim.ini` beside the
   executable (default ON), self-contained so it does not need the shim's
   config plumbing under the loader lock.
2. Require exe file version 301.
3. Return silently if the delimiters are already repaired (idempotence).
4. Require the exact stock bytes `20 2C 09 00` at `0x008F068C`.
5. Check the two `.text` push sites and the `":%d,%d"` format site as
   corroboration, and log the result without requiring it.
6. Write `20 09 00 00` under `VirtualProtect`, and log the applied repair.

What the patch deliberately does not do: it adds no value-level tolerance of
its own. `=` instead of `:`, quoted values and embedded spaces are all left
exactly as stock handles them, because the stock handler still does all the
value parsing.

## Tests

The offline model in `tests/cli_parser_tests.cpp` models `FUN_007D5120` once
and runs it twice, with the stock delimiters and with the repaired ones, so
the "fixed" arm is the stock parser fed the bytes that actually ship rather
than a separate reimplementation. It models the positional branch
(`DAT_00915540`, `DAT_00945708`, `SetRunning`, `DAT_0091556C`) so the orphan
collateral is asserted, not just described.

Value matrix, all through the repaired delimiters:

```text
-shellmap:216,178      -> 216 x 178
-shellmap:1920,1080    -> 1920 x 1080
-shellmap:216,216      -> 216 x 216
-shellmap:216          -> 216 x 216   (stock square fallback, res == 1)
-shellmap:216,         -> 216 x 216   (stock square fallback, res == 1)
-shellmap:216,abc      -> 216 x 216   (stock square fallback, res == 1)
-shellmap:abc,178      -> 108 x 89    (handler defaults, res == 0)
-shellmap:,178         -> 108 x 89    (handler defaults, res == 0)
-shellmap              -> 108 x 89    (handler defaults, res == EOF)
-shellmap:216,178,999  -> 216 x 178   (extra component ignored by ":%d,%d")
```

Interaction and non-regression coverage:

- space- and tab-separated surrounding switches;
- `-largemap:16` and `-disablemods` proven byte-for-byte identical between
  the stock and repaired delimiter runs;
- a genuine positional mission argument still reaches the positional branch,
  in either argument order;
- an unrelated comma-bearing option is not rewritten and its tail is not
  orphaned;
- quoted paths containing spaces behave exactly as stock (strtok has no
  quote awareness in either arm; documented, not claimed fixed);
- the accepted comma-as-separator behaviour change is asserted explicitly so
  it cannot regress silently.

All checks pass under `-Wall -Wextra -Werror`.
## Runtime acceptance

GOG 2.2.301 qualified 2026-09-01 by a two-arm live run against the installed
executable, reading the native globals out of the running process rather than
inferring them from behaviour. Steam remains outstanding.

Both arms launched with `-shellmap:216,178`, differing only in
`[Fixes] CliMultiParameterOptions`.

### Control arm (fix off) — reproduces the defect

```text
0x008F068C  20 2C 09 00   " ,\t"        (patch correctly stood down)
0x009183D4  1                          (mode selector, not a dimension)
0x009183C4  0x00D800D8                 width 216, height 216   <- height lost
0x00915540  "178"                      <- orphan token overwrote the map name
```

No `[cliparse]` log line, confirming the opt-out disables the patch silently.

### Test arm (fix on) — repaired

```text
0x008F068C  20 09 00 00   " \t"         (patch applied)
0x009183D4  1                          (unchanged)
0x009183C4  0x00B200D8                 width 216, height 178   <- correct
0x00915540  "misn03.bzn"               <- game default, no orphan collateral
```

```text
[INFO] [cliparse] CLI multi-parameter options repaired: strtok delimiters
" ,\t" -> " \t" at 0x008F068C
(text identity strtok1=ok strtok2=ok shellmapFormat=ok)
```

The control arm is also the direct live confirmation of both corrections in
this document: `0x009183D4` reads `1`, not `216`, and the orphaned `178` is
observably sitting in the map-name buffer the shellmap consumer reads.

### Steam 2.2.301 — partially qualified

What is proven:

- `.data` is **not** SteamStub-encrypted. `0x008F068C` reads `20 2C 09 00`
  in the at-rest Steam file, byte-identical to GOG, so the stub holds no
  ciphertext to restore over the write.
- `.text` **is** encrypted at rest: `0x007D5156` reads `2B 19 B1 5A 90...`
  instead of `68 8C 06 8F 00...`, and `0x00618D0E` reads `ED DB 46 C6 0B`
  instead of `E8 0D C4 1B 00`. Requiring the `.text` guards at attach would
  have made this fix silently GOG-only, exactly as the design assumed.
- The file version resource reads 301 on Steam, so the identity check passes.
  (It arrives as `HIWORD(dwFileVersionLS)`, which is why the accessor keeps
  the same fallback `patcher.cpp` uses.)
- The repair **applies** on Steam. A live process was sampled with
  `0x008F068C` reading `20 09 00 00` while `0x007D5156` was still
  ciphertext, and the log line reported
  `strtok1=unverified strtok2=unverified shellmapFormat=unverified`.
- **No regression.** With the stock shim DLL the Steam process behaves
  identically: the shim log ends at the same line, and the game exits the
  same way. The only difference between the two runs is the one added
  `[cliparse]` line.

What is not proven:

- End-to-end parsing on Steam (`0x009183C4 == 0x00B200D8`). The Steam copy
  in the test environment does not reach engine init at all: launched
  directly, SteamStub attaches the shim, exits, and never completes its
  relaunch; `steam://run/301650//-shellmap:216,178` does not start it
  either. It never writes `BZLogger.txt`. This happens **with the stock
  shim DLL too**, so it is environmental and not caused by this patch, but
  it means the parser never ran and the packed value could not be read.

To close this gate, run the two-arm procedure above on a machine where the
Steam build starts normally and confirm `0x009183C4 == 0x00B200D8`.

### Post-settle self-check

Because the attach-time `.text` corroboration has to be skipped on Steam,
`VerifyCliMultiParameterOptionFix()` runs from the patch thread after
`WaitForSignature`, which is the first moment `.text` is decrypted. It:

- settles the `.text` identity that could not be checked at attach, so a
  Steam run proves the delimiter belongs to `ProcessCommandLine`;
- reports at ERROR if the delimiter has been restored to `20 2C 09 00`,
  turning a hypothetical packer restore over `.data` from a silent failure
  into a log line (it re-applies, though by then the command line has
  almost certainly already been parsed).

Observed on GOG:

```text
[INFO] [cliparse] CLI multi-parameter options repaired: ... strtok1=ok strtok2=ok shellmapFormat=ok
[INFO] [cliparse] CLI multi-parameter repair held after image settle (text identity strtok1=ok strtok2=ok shellmapFormat=ok)
```

### Still outstanding

- Steam end-to-end parse, per above.
- Broader confirmation that renderer/backend and other CLI controls are
  unaffected across a longer session.
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
- [x] Correct `0x009183D4` from "width" to mode selector, and identify the
      real consumer as `FUN_00617110`.
- [x] Identify the orphan-token collateral that rules out a post-parser
      dimension-only repair.
- [x] Select narrow repair point and native state target.
- [x] Implement production repair (`src/patches/cli_multiparam_parser.cpp`).
- [x] Add production-facing diagnostics.
- [x] Add the `[Fixes] CliMultiParameterOptions` opt-out.
- [x] Run malformed-input regression suite.
- [x] Verify every guard byte against the shipped GOG executable.
- [x] Validate supported GOG executable at runtime (2026-09-01, two-arm live run).
- [~] Validate supported Steam executable at runtime (applies + no regression
      proven 2026-09-01; end-to-end parse blocked by an environmental
      launch failure present with the stock shim DLL too).
- [ ] Confirm no side effects on renderer/backend and other CLI controls.
- [ ] Promote to fixed only after runtime acceptance passes.
## Documentation invariant

Do not regress this item back to "RE needed." The parser root cause and 1.5 parity question are closed.

The remaining work is **runtime validation** of the shipped repair.

Removing the comma from the delimiter set repairs every option in this parser whose internal grammar uses it, so the inventory of other affected options is no longer a prerequisite for anything. It remains worth compiling as documentation of what the fix unblocks.