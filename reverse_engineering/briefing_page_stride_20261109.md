# Briefing / archive text: scroll stride vs rendered page (2026-11-09)

Build: GOG Redux 2.2.301. Decompile citations are files under
`Battlezone_Source/BZ1/Redux/openshim_re_corpus/bzr_gog_best_effort/ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps/` (called `D/` below). Addresses were
also disassembled from the shipping exe. Not live-tested.

## Relationship to the existing BRIEFSCROLL fix

`[BRIEFSCROLL]` (`ui_camera_fixes.cpp`) is installed (openshim.log, 2026-11-09 shows
`hook=installed`). It redirects the briefing/archive up/down callbacks from
`FUN_007ce0e0/007ce110` to `FUN_007ce730/007ce6d0`. This is a different defect from
the one fixed here, and the premise of that fix is doubtful:

- The briefing body is a `cUI_ScrollingTextBlock` (`D/FUN_0078f030:293-303`,
  `operator_new(0x295c)` + `FUN_007cd8d0`; vftable at `D/FUN_007cd8d0:36`).
- `FUN_007ce6d0/007ce730/007ce580` are `cUI_ChatBlock` methods: the chat block ctor
  `D/FUN_007ce140:36` sets `cUI_ChatBlock::vftable`, and its callbacks
  `FUN_00795c50 -> FUN_007ce6d0` are wired to the "chatText" widgets
  (`D/FUN_00796880:484-490`, `D/FUN_0079ea90:548-554`).
- Those methods bound the scroll by the length of the global session chat list
  (`FUN_00764760` returns `DAT_00945470`, `FUN_004b3210` = `+0xc`, `FUN_004170c0` =
  `+0x10`; `D/FUN_007ce6d0`, `D/FUN_007ce580` lines 22-29). The `+0x2958` offset is
  shared by both classes, which is why the swap "works" mechanically.
- The note `mission_briefing_scroll_cutoff_notes_20260320.md` called `FUN_007ce580`
  the scrolling block's clamp; it is the chat block's refresh. The stock
  `FUN_007ce110` scroll-down only does `++[this+0x2958]` and rebuilds
  (`D/FUN_007ce110`); `FUN_007cdd50` (the scrolling block render) hides the down
  arrow when nothing overflows (`D/FUN_007cdd50:41-45, 75-116`) and has no reset-to-0.
- UNVERIFIED (needs a live run): with the redirect, down-scroll advances only when
  `chatLines - page >= [this+0x294c]`, so a briefing may fail to scroll in single
  player when the chat list is short. If so, turn `[BRIEFSCROLL]` off
  (`OPENSHIM_DISABLE_BRIEFING_SCROLL_FIX=1`) when testing this fix.

## Root cause fixed here: stride probe vs page text

The scrolling block renders page `k` by skipping `k * P` lines, where `P` is
re-measured every render (`D/FUN_007cdd50:58-64`, `local_74 = FUN_007cce90()`), then
trimming trailing lines until the text fits (`D/FUN_007cdd50:75-116`; disassembly
`0x007cdf1e comiss; 0x007cdf26 jb` = fits when measured < box height).

`P` comes from the probe `0x007CCE90` (`D/FUN_007cce90:21-32`, disassembly
`0x007ccf2a..0x007ccf5b`): start with `"T"` (literal `0x008A09B8`), then while
`boxHeight > measure(text)` append `"\nT"` (literal `0x008A09B4`) and count. The
count is returned in `eax` (`0x007ccf80..0x007ccf95`). The probe string never ends
in a newline.

The page text is built as `line + "\n"` for every line
(`0x007cded7..0x007cdeed`, literal `0x0087A44C` = `"\n"`), so it always ends in a
newline.

The height measurer `D/FUN_00689ab0`:
- start `-yScale` (`FUN_00689a90`), each `'\n'` adds `9*yScale + 2*yScale`
  (`:43-44`, `FUN_00689a70` = `9*yScale`), integer-truncated each step;
- after the loop it adds one more `9*yScale` only if the last line is non-empty, or
  nothing has been counted yet (`:51-54`).

So n probe lines measure `11*n*s - 3*s` while n page lines (trailing newline)
measure `11*n*s - s`: the page is `2*s` taller. With `P` from the probe and box
height `H`, when `H` lies in `(11*P*s - 3*s, 11*P*s - s]` the page fits only `P-1`
lines but the next page skips `P`. One line is lost at every page break, and a final
page that holds exactly `P` lines overflows, enables the down arrow, hides its last
line, and the next page (which skips `P` lines) is empty. That is "the bottom cannot
be reached"; trailing blank lines make the real text no longer sit on that page.
For other `H`, `P` equals the lines shown and nothing changes.

Window frequency: `2s` of every `11s` (about 18% of box heights); whether the
briefing box at a given resolution lands in it is UNVERIFIED.

## Fix

Make the probe end every line with `"\n"` so it matches the page text: both `push imm32`
operands (`0x007CCEBB` -> `0x008A09B8`, `0x007CCF53` -> `0x008A09B4`; no other
references to either literal exist in the image) are retargeted to a DLL-owned
`"T\n"`. `h_probe(n) == h_page(n)` for every n, so `P` is exactly the number of lines
that fit. Where `P` was already right nothing changes. The same probe feeds the
chat block (`D/FUN_007ce140:38`), where it is equally a client-local UI quantity.

Flag: `[Fixes] BriefingPageStride` (default 1); env kill switch
`OPENSHIM_DISABLE_BRIEFING_PAGE_STRIDE_FIX`. Log tag `[BRIEFSTRIDE]`.
Archive page: it uses the same `cUI_ScrollingTextBlock` (callbacks `0x00790AF9/B09`
wired like the briefing's), so it is covered by the same fix.

## Live check (not performed; the game was not launched)

1. A `.des` with one very long paragraph (no padding, more than two pages) and at
   least 40 numbered lines. Page through with the down arrow: the last line must be
   visible on the final page and no numbered line may be skipped between pages.
2. A/B with `BriefingPageStride=0` at a resolution where the old build drops a
   numbered line at a page break. Confirm the old build reproduces first.
3. Repeat from the mission archive screen.
4. Test once with `OPENSHIM_DISABLE_BRIEFING_SCROLL_FIX=1` to see whether the
   BRIEFSCROLL redirect changes the result.
