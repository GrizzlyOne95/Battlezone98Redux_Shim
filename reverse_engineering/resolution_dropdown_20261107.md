# Resolution dropdown (graphics options screen)

Build: released GOG 2.2.301. Everything below was read from the shipping exe
disassembly (no PDB data). Code: `src/patches/resolution_dropdown.cpp`; rows:
`ResDrop*` in `scripts/patches.json` `engine_addresses`.

## Screen
- `cUI_OptionsGraphics` ctor `0x007AF4A0`, thiscall(this), no stack args, plain
  `ret` at `0x007B1E6F`; sets vtable `0x0089F608` at `0x007AF4E9` (RTTI
  `.?AVcUI_OptionsGraphics@@`). Only caller is the screen factory.
- Widget parent (a view built by `0x007D1CC0`) is stored at screen+0x18C
  (`0x007AF63F`); children are added with `0x007D2110(parent, child, anchor)`.
  The second argument is an existing child to insert before (0 = append); the
  ctor's own adds pass 0.
- Resolution checklist: ctor `0x007C3150`, stored at screen+0x154 (`0x007B00C5`),
  filled by the add call at `0x007B01A8` (the `ResList*` rows of the list
  filter), selected by value at `0x007B01E2`, change callback `0x007AE820`
  installed at `0x007B01FD`.

## cUI_Checklist (vtable `0x008A04D0`, RTTI `.?AVcUI_Checklist@@`)
- Slot +0x20 = `0x007C3720`: thiscall(this, int x, int y, int button), `ret 0xC`,
  bool in al. Gates in order: `0x007D3360` (reads the byte at +0xE9), byte
  +0x1E0, hit test `0x007D2810(this, float x, float y)` (rect floats at
  +4 x, +8 y, +0xC w, +0x10 h, inclusive), byte +0x145. Then button 0 = next,
  1 = previous.
- Items vector at +0x1E4 (pointer elements, `0x004200B0` count, `0x004200D0`
  index), selected index +0x1DC, callback +0x1D8. Item = `{char text[0x40];
  int value}`.
- `0x007C3C10(this, int value)` selects by value (writes +0x1DC, updates text);
  it does not call +0x1D8.

- The vtable has exactly 17 slots (+0x00..+0x40): the COL `0x008B5F68` sits at
  `0x008A04CC`, and `0x008A0514` onward is string data, not code (read from the exe).
  The 18-dword instance copy (COL + 17 slots) therefore covers the whole table.
- AddChild `FUN_007d2110(parent, child, anchor)`: anchor 0 appends (line 13-14);
  a nonzero anchor inserts the child before the matching existing child
  (lines 17-27). An anchor that is not a child adds nothing.

## cUI_View (base of both widgets)
- Ctor `0x007D1CC0` stores the raw design-space x, y, w, h at +0xEC, +0xF0,
  +0xF4, +0xF8; the live screen-space rect (+4..+0x10) is set later through
  `0x007D14B0`. Child vector at +0x12C. `0x007D3310` is the non-virtual
  SetActive (writes +0xE9 and forwards to the element at +0x120).
- Container dispatch (`0x007D2420`, `0x007D2570`) walks children from index 0 and
  stops at the first handler, so a child inserted first sees clicks first.

## cUI_Selectlist (vtable `0x008A08B0`, RTTI `.?AVcUI_Selectlist@@`)
- Ctor `0x007C9DE0` (0x180 bytes), SetItem `0x007CABF0`, SetOnSelect `0x007CB3E0`
  (stores at +0x144; the callback is void(void)).
- Row labels: pointer vector at +0x15C; items: vector of 0x1C-byte elements at
  +0x168; selected absolute index +0x14C; scroll +0x150.
- Row refresh `0x007CB400(this)`; scroll up `0x007CB500(this)`, scroll down
  `0x007CB540(this)` (max scroll = items - rows). The arrow callbacks are
  void(void), so the dropdown reaches the list through its own global.
- Vtable slot +0x24 = `0x007CB1E0(this, byte)`: the list's virtual SetActive; it
  calls `0x007D3310` and then shows or hides every row label (and highlights the
  row where +0x14C - +0x150 equals the row). Mouse slots +0x1C/+0x20 test
  `0x007D3360`, so a hidden list ignores clicks.

## Design consequences
- Only the one checklist instance gets a private vtable copy (COL + 17 slots,
  slot +0x20 replaced); the class vtable is never written.
- The wrapper mirrors the stock gates (active, enabled, rect, clickable) with
  direct field reads instead of calling `0x007D3360`/`0x007D2810`.

## Ctor details used by the dropdown
Cited from the GOG ghidrecomp corpus, `FUN_007c9de0-007c9de0.c` and
`FUN_007cca20-007cca20.c` (bzr_gog_best_effort).
- Ctor param 10 is a text-colour enum, not an ARGB: it is passed to
  `FUN_007cca20` for each row label (7c9de0 line 423), which writes +0x91c as
  0 white, 1 black, 2 red, 4 0x3333ff, anything else green (7cca20 lines 9-37).
- Each row label then gets `FUN_007d2870("filton.png")` as its off texture
  (7c9de0 line 427): that bitmap is the selection bar. The dropdown replaces it
  with `uibtn.png` after construction so the selected row stays readable.
- Page arrows are stored at this[0x5e] (line 263) and this[0x5f] (line 327).

## Verified live (GOG 2.2.301, 2026-11-08, windowed 1600x900)
- A small `cUI_Overlay` backdrop drew nothing on this screen; a button-backed
  plate (flags 0x20, `uiplate.png` in all three states, enabled byte +0x148 = 0)
  draws and lets clicks through.
- Stock value captions draw above injected widgets, so the list opens in the
  empty column right of the values instead of over them.
- Pick updates the row value; reopening highlights the current choice; a click
  outside closes the list through the full-screen catcher.
