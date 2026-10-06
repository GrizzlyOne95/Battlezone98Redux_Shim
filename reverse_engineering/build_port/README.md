# Porting OpenShim to a new battlezone98redux.exe

`port_patches.py` carries every address in `scripts/patches.json` from the
build it was written for to a new build, and writes a ported json plus a
report of everything it could not carry across with confidence. It is the
first step when BZR ships a patch.

Requires Python 3 with `capstone` and `pefile`. Steam executables are
SteamStub-encrypted on disk: unpack them with
[Steamless](https://github.com/atom0s/Steamless) first
(`Steamless.CLI.exe --quiet battlezone98redux.exe` writes
`battlezone98redux.exe.unpacked.exe`). The GOG exe needs nothing.

```
python reverse_engineering/build_port/port_patches.py OLD.exe NEW.exe \
    --out ported_patches.json --report port_report.md \
    [--addresses literals.txt]
```

`--addresses` takes extra hex addresses, one per line (for example ones still
written as literals in C++), and adds them to the report.

## What it does

- **Code** is found by its surrounding instructions with only the movable
  bytes masked: absolute addresses inside the image and branch/call
  displacements. Struct offsets and immediates stay exact, so a function whose
  field layout changed fails to port rather than porting silently.
- Code the compiler emitted several identical copies of (atexit stubs, the
  `*::BuildClass` family, repeated Lua binding code) is told apart by carrying
  the masked operands across too (the global it loads, the function it calls)
  and keeping the one candidate whose operands match; then by carrying its
  callers across; then by its containing function's entry.
- **Data** is found by carrying the instructions that reference it across and
  reading their operands back. A vtable slot is confirmed when the function it
  holds carries across to what the new slot holds.
- **Layout check.** Strings whose text is unique in both builds and that are
  referenced once in each pin pairs of instructions without using any byte
  signature. A patch inserts and removes bytes but keeps layout order, so the
  old-to-new shift is locally constant; an answer whose shift disagrees with
  the anchors on both sides is rejected as `SHIFT-MISMATCH`.
- `pattern`, `expected` and `expected_original` bytes are regenerated in the
  new build when the only bytes that differ are movable ones (an embedded
  address that moved); otherwise the entry is `CHANGED`.

## Reading the report

Only `OK` rows are written into the ported json. Every other row keeps its
old value, so OpenShim's byte guards keep refusing it until someone looks:

| status | meaning |
|---|---|
| OK | two or more independent signals agree (or operand-verified, or one signal bracketed by agreeing layout anchors) |
| WEAK | one signal only; the candidate is in the report, check it by hand |
| CHANGED | found, but bytes that matter differ: the code itself was edited |
| SHIFT-MISMATCH | a signature matched, but at a place the layout says is wrong |
| CONFLICT | strategies disagree |
| NOTFOUND / INFERRED | nothing usable / placed only relative to a neighbour |

## How far to trust it

`eval_port.py OLD NEW` measures the porter on two real builds with string
literals as an independent oracle (a carried-across `push "text"` must still
push the same text; a function must still reference the same strings; a
string's address must still hold its text). The figure that matters is
`WRONG`, a confident answer that fails the oracle; it should be zero.

Two real Steam build pairs (Steam depot 301652; unpack with Steamless):

- **Hotfix:** 2016-04-19a (2.0.115.5) to 2016-04-19b (2.0.117.0). `.text`
  grew about 4 KB, with edits spread through it (213 distinct shifts).
- **Release:** 2.1.201 (manifest 729440969425738960, August 2016) to today's
  2.2.301. `.text` grew by 1.1 MB, with much of it rewritten.

| pair | kind | OK | safely flagged | genuinely wrong |
|---|---|---|---|---|
| hotfix | code sites | 93% | 7% | 0 |
| hotfix | function entries | 94% | 6% | 0 |
| hotfix | data | 76% | 24% | 0 |
| release | code sites | 48% | 52% | ~0.3% |
| release | function entries | 52% | 48% | ~1% |
| release | data | 42% | 58% | ~0.3% |

The oracle's own `WRONG` lines were each checked by hand. Most are the oracle
being wrong, not the porter:

- a string's text changed between versions (`2.0.115.5` became `2.0.117.0`,
  `%d` became `%p`, `failture` became `failure`);
- a random constant in a function body happens to point at a string.

The genuine misses on the release pair are code that moved into a different
function between versions; there is no single right answer for those. So for a
patch on the scale of a hotfix, OK can be taken as is. After a release-sized
update, review the OK entries that belong to features the update touched, and
test them live. Data is flagged more often by design: a single reference is
not accepted on its own (see `DataPorter._confirmed`).

The porter's rules came from failures these evaluations found:

- repeated Lua binding and key-table code, where a signature unique in the old
  build landed on a neighbouring copy;
- a mission script whose instruction now names a different file;
- overlapping signature windows counted as independent agreement. A signature
  match is now one signal, and OK needs a second: exact layout, references,
  or verified operands.

Re-run the evaluations after changing the porter.

## On a BZR patch

1. Unpack the new Steam exe with Steamless (GOG needs nothing), then run
   `port_patches.py OLD NEW --label <version> --out scripts/patches.json`.
   This adds a `build_overlays` entry for the new build next to the existing
   one, so both builds work from the same file.
2. Read the report. Fix the CHANGED, CONFLICT, WEAK and NOTFOUND rows that
   matter by hand (Ghidra), by editing that overlay's entries.
3. Features whose addresses are still literals in C++ stand down on the new
   build (`HookEngine::IsReferenceBuild`); see "Literal addresses" below.
4. Launch both builds and read the `[BUILD]` and `[ADDR]` lines in
   `logs/openshim.log`.

`make_engine_rows.py` generates `engine_addresses` rows (with guard bytes)
for addresses being moved out of C++.

Sanity check: porting the GOG exe onto itself must give OK for every entry
with a zero shift.

## Literal addresses

Some feature code still writes engine addresses as literals (about 300 of
them, across 40 files). A patches.json overlay cannot move those, so on any
build other than the one they were taken from (2.2.301, link stamp
`0x58D9D6CC`, GOG and Steam alike), the features built on them stand down.
Each one logs a single line:

    [BUILD] <feature> stands down: its engine addresses are still literals for 2.2.301

The pieces that do this:

- `HookEngine::LiteralAddressesApply("<feature>")` gates each such file's
  entry points.
- `IsLiteralHandlerPatchName` in `patcher.cpp` lists the patches.json patches
  whose trampolines enter those files.
- `IsCompatibleGameVersion()` (public SDK) is true only on the reference
  build.

To bring a feature to a new build, move its literals into patches.json:

1. Generate rows with guard bytes:
   `python make_engine_rows.py <2.2.301 exe> Name=0xADDR:"identity note" ...`
   and add them to `engine_addresses`.
2. In the feature, read them with `HookEngine::BindEngineRows` (all or
   nothing, for a feature's own set) or `HookEngine::EngineAddress` (one
   shared address). Treat 0 as "stand down".
3. Remove the feature's `LiteralAddressesApply` gates, and its entry in
   `IsLiteralHandlerPatchName` if it has one.
4. Re-run `port_patches.py` so the new rows get carried to the other builds.

`ui_performance_hooks.cpp` is the worked example.
