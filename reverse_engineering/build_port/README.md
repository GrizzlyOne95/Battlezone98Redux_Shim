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

Measured on the one consecutive pair of Steam builds available,
2016-04-19a (2.0.115.5) to 2016-04-19b (2.0.117.0), a hotfix that grew
`.text` by about 4 KB with edits spread through it (213 distinct shifts),
three samples of 300 each:

| kind | OK | safely flagged | genuinely wrong |
|---|---|---|---|
| code sites | 93-95% | 5-7% | 0 |
| function entries | 98% | 2% | 0 |
| data | 78-84% | 16-22% | 0 |

The oracle still prints a handful of `WRONG` lines; each was checked by hand
and is the oracle's own mistake: the version string itself changed
(`2.0.115.5` to `2.0.117.0`), or a random constant in a function body happens
to point at a string. Data is flagged more often by design: a single reference
is not accepted on its own (see `DataPorter._confirmed`).

The porter's rules came from failures this evaluation found: repeated Lua
binding and key-table code that let a unique-in-old signature land on a
neighbouring copy, and a mission script whose instruction now names a
different file. Re-run it after changing the porter.

Sanity check: porting the GOG exe onto itself must give OK for every entry
with a zero shift.
