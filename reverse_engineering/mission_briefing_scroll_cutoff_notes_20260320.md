# Mission Briefing Scroll Cutoff Notes 2026-03-20

## Summary

Bug:

- the shell mission briefing panel shown immediately before `Launch` can cut off
  the lower part of the text when the briefing is longer than the first visible
  page
- once the user scrolls near the bottom, the last partial page can become
  unreachable
- content authors currently work around this by appending roughly `10-15` blank
  lines to the end of the `.des` file so the real text becomes visible again

Bottom line:

- this does not look like a `.des` authoring problem
- it looks like a shell `cUI_ScrollingTextBlock` bug in the mission briefing
  screen's scroll callbacks
- the most likely failure is an overscroll-by-one path that resets the scroll
  offset to `0` instead of clamping it to the final valid bottom position

## Evidence

### 1. The mission shell loads briefing text from `.des`

`FUN_004889c0` loads the mission description text by taking the mission name and
replacing its extension with `.des`. If the file is missing, it falls back to
`"NO DESCRIPTION"`.

That function is used by the pre-launch mission UI constructor
`FUN_0078f030`, which builds the shell page shown right before the player hits
`Launch`.

Inference:

- the in-game symptom matches a UI rendering or scrolling defect after the text
  is loaded, not a bad mission-file parse path

### 2. The briefing uses a scrolling text-block class

Inside `FUN_0078f030`, the mission UI builds two different text widgets:

- a plain text block path via `FUN_007ccb70`
- a scrolling text block path via `FUN_007cd8d0`

`FUN_007cd8d0` appears to construct `cUI_ScrollingTextBlock` on top of the base
text block and initializes these important fields:

- `+0x294c` visible lines per page
- `+0x2958` current scroll offset, initialized to `0`

This is the correct class family for the observed symptom: the text is present,
the first page draws, but scrolling fails near the bottom.

### 3. The mission briefing screen is wired to unguarded scroll handlers

The scrolling widget exposes two pairs of scroll routines:

- unguarded:
  - `FUN_007ce0e0` scroll up
  - `FUN_007ce110` scroll down
- guarded:
  - `FUN_007ce730` scroll up with clamp
  - `FUN_007ce6d0` scroll down with clamp

Mission-screen callbacks use the unguarded pair:

- `FUN_0078ed20 -> FUN_007ce0e0`
- `FUN_0078ed30 -> FUN_007ce110`

Mission-archives callbacks appear to use the same unguarded pair:

- `FUN_00790af0 -> FUN_007ce0e0`
- `FUN_00790b00 -> FUN_007ce110`

Other shell surfaces such as chat or lobby scrolling use the guarded pair
instead:

- `FUN_00795c50 -> FUN_007ce6d0`
- `FUN_00795c60 -> FUN_007ce730`
- `FUN_0079d550 -> FUN_007ce6d0`
- `FUN_0079d560 -> FUN_007ce730`

That split is the strongest direct indicator that the mission briefing page is
using the wrong callback flavor.

### 4. The shared refresh logic zeroes the scroll offset in the bad state

`FUN_007ce580` appears to be the scrolling text block's refresh or clamp path.
Its relevant behavior is:

- query total rendered line count
- if `total_lines == 0`, or if
  `(total_lines - scroll_offset) < lines_per_page`
- then set `scroll_offset = 0`
- rebuild the displayed lines and update arrow visibility

That means if the current offset ever advances far enough that the remaining
line count is less than one full page, the widget snaps back to the top instead
of holding the final partial page.

## Root Cause

Most likely bug chain:

1. The mission briefing contains more lines than fit in the initial window.
2. The shell uses the unguarded `FUN_007ce110` down-scroll path.
3. That path increments `scroll_offset` without checking whether the next
   position is still valid.
4. Once the user scrolls one step too far, `FUN_007ce580` sees
   `remaining_lines < lines_per_page`.
5. Instead of clamping to the last valid bottom offset, it resets the widget to
   `scroll_offset = 0`.
6. The final partial chunk of the briefing becomes unreachable.

Why the blank-line workaround helps:

- adding many empty trailing lines increases `total_lines`
- the user can overscroll into those blank lines while the real final text still
  falls within a "full page" range
- that makes the lower real content visible before the widget reaches the reset
  condition

So the extra blank lines are masking the bad clamp behavior, not fixing the
underlying content.

## Best Fix Direction

Lowest-risk fix target:

- keep the shared scrolling widget logic intact
- patch the mission briefing and mission-archives scroll actions to use the
  guarded handlers already used elsewhere in the shell

Concrete patch candidates:

- redirect `FUN_007ce110` callers on the mission pages to `FUN_007ce6d0`
- redirect `FUN_007ce0e0` callers on the mission pages to `FUN_007ce730`

Equivalent binary-level simplification:

- patch `FUN_007ce110` to jump to `FUN_007ce6d0`
- patch `FUN_007ce0e0` to jump to `FUN_007ce730`

Why this is preferable to editing `FUN_007ce580` directly:

- the guarded handlers already exist and are used successfully by other shell
  screens
- the mission pages are the suspicious outliers
- changing the large shared refresh routine is a broader behavioral risk than
  swapping the mission pages onto the already-clamped path

More invasive fallback:

- rewrite `FUN_007ce580` so that the bad state clamps to
  `max(0, total_lines - lines_per_page)` instead of resetting to `0`

That would also fix the symptom, but it touches common widget logic and should
only be preferred if the callback swap proves insufficient.

## Key Functions And Addresses

- `0x004889c0` `FUN_004889c0`
  - load mission description text from `.des`
- `0x0078f030` `FUN_0078f030`
  - construct the pre-launch mission UI
- `0x00792000` `FUN_00792000`
  - mission-failed screen also loads `.des`
- `0x007ccb70` `FUN_007ccb70`
  - base text block constructor
- `0x007cd8d0` `FUN_007cd8d0`
  - scrolling text block constructor
- `0x007cdd50`
  - scrolling text block display or rebuild logic
- `0x007ce580`
  - scrolling text block refresh or clamp logic
- `0x007ce110`
  - unguarded scroll down
- `0x007ce0e0`
  - unguarded scroll up
- `0x007ce6d0`
  - guarded scroll down
- `0x007ce730`
  - guarded scroll up
- `0x0078ed20`
  - mission page callback using unguarded scroll up
- `0x0078ed30`
  - mission page callback using unguarded scroll down
- `0x00790af0`
  - mission archives callback using unguarded scroll up
- `0x00790b00`
  - mission archives callback using unguarded scroll down

## Practical Conclusion

The mission briefing cutoff issue is best explained as a shell scroll-widget
bug, not a bad briefing-data format.

The user-facing workaround of appending blank lines to `.des` files fits the
overscroll-and-reset model exactly. Future implementation work should start by
moving the mission briefing screen onto the guarded scrolling handlers already
used by other shell pages.
