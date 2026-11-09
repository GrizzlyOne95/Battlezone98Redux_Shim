# Briefing / archive text: scroll stride vs rendered page (2026-11-09)

Build: GOG Redux 2.2.301. Decompile citations are files under
`Battlezone_Source/BZ1/Redux/openshim_re_corpus/bzr_gog_best_effort/ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps/` (called `D/` below). Addresses were
also disassembled from the shipping exe. Not live-tested.

## BRIEFSCROLL removed (2026-11-09)

`D/` = the decomps dir named above. The earlier `[BRIEFSCROLL]` fix redirected the
briefing/archive up/down callbacks (`0x0078ED29/39`, `0x00790AF9/B09`) from
`FUN_007ce0e0/007ce110` to `FUN_007ce730/007ce6d0`. It is removed in this branch.

What it tried to fix (`mission_briefing_scroll_cutoff_notes_20260320.md`): the last
part of a long briefing is unreachable and authors pad the `.des` with 10-15 blank
lines. That symptom is the one explained below by the stride/page mismatch; the old
note guessed a clamp/reset path instead.

Why the premise is wrong:
- The briefing body is a `cUI_ScrollingTextBlock` (`D/FUN_0078f030:293-303`,
  `FUN_007cd8d0` sets `cUI_ScrollingTextBlock::vftable` at `D/FUN_007cd8d0:36`).
- `FUN_007ce6d0/007ce730/007ce580` are `cUI_ChatBlock` methods (ctor
  `D/FUN_007ce140:36`; callbacks wired to "chatText": `D/FUN_00796880:484-490`).
  They bound the scroll by the global chat list length (`D/FUN_007ce6d0:8-11`,
  `D/FUN_007ce580:20-23`), and `FUN_007ce580` zeroes `+0x2958` when that list is
  empty (`D/FUN_007ce580:23-24`) and refreshes the chat widgets' arrows
  (`D/FUN_007ce580:26-28`). Applied to a briefing in single player (empty chat
  list) the redirect can pin the page at 0 or stop the page advancing: UNVERIFIED
  live, but it is a sufficient reason not to keep it.
- The note's "refresh resets to 0" is the chat block's `FUN_007ce580`, not code the
  scrolling block runs. The stock scroll-down only does `++[this+0x2958]` and
  rebuilds (`D/FUN_007ce110:5-6`; up is `D/FUN_007ce0e0:5-6`).

Does a bound still matter once the stride is right? The page render has no reset
and, past the end, just skips every line and shows nothing
(`D/FUN_007cdd50:60-64`, loop ends when the list is empty). The only things that
stop the player going past the end are the arrows: `FUN_007cdd50` hides the down
arrow (`+0x2954`) at the top of every render (`:42`) and re-shows it only when the
page text still overflows the box (`:75-81`). With `BriefingPageStride`, `P` is the
true fit count, so the last page that holds <= `P` lines fits, the down arrow stays
hidden, and the offset cannot pass the end by clicking. Without it, a final page of
exactly `P` lines overflows, shows the arrow, and the next click lands on an empty
page (see below). Whether those arrows are click-disabled when hidden (vtable
`+0x24` is assumed to be SetVisible) is UNVERIFIED; no other writer of `+0x2958`
exists except the ctor (`D/FUN_007cd8d0:37`) and reset `D/FUN_007ce0b0:5`
(grep of `0x2958` over `D/`).

A native page-count clamp was not added: the line list is a local of the render
function (`D/FUN_007cdd50:46-74`), so the block has no stored page count to clamp
against, and a clamp hook cannot be validated without launching the game. If a live
test shows overscroll still reaches an empty page, add the clamp inside the render
(re-derive the list size and cap `+0x2958` at `ceil(lines/P) - 1`).

Removed: the four call-site redirects, ini-less switch
`OPENSHIM_DISABLE_BRIEFING_SCROLL_FIX` / `BZR_DISABLE_BRIEFING_SCROLL_FIX` (it never
had an ini key), the `[BRIEFSCROLL]` log lines and eight `patches.json` rows
(`BriefingScroll*Call`, `ArchiveScroll*Call`, `UiScroll*Guarded/Unguarded`).

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
4. Compare against the previous build (which still had BRIEFSCROLL) once, long
   unpadded `.des`, both scroll directions, in the briefing and the archive.
