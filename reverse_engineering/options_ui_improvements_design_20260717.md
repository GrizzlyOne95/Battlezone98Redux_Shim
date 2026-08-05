# Options UI improvements — prepared designs (2026-07-17)

Status: items 1, 2, 3 and 5 IMPLEMENTED + verified in-game 2026-07-17
(4K GOG, scripted click harness). Item 4 remains deferred (see below).
All code references are to `src/patches/bzr_options_ui.cpp` unless noted.

Implementation notes beyond the original designs:

- **Native measure normalization:** `TryMeasureUiTextWidth` measures with the
  global char sizes, which track the *render resolution* (screen px), while
  all layout in this file is the fixed 1080-tall logical space. At 4K the raw
  measure was 2x and over-truncated every label ("Attack Al..."). Fixed by
  scaling the result by `1080 / GetSystemMetrics(SM_CYSCREEN)` when the
  display is taller than 1080. Windowed sub-1080 modes fall back to raw.
- **Label/value split rebalanced** on both pages: label box 285 (was 200/205),
  value button 175 at offset 292. Value enums shrink their own text scale, so
  they keep fitting; labels no longer truncate at all 16 registry entries.
- **Hover slot semantics:** the button +0x150 slot fires on hover-state
  *changes* (also bulk-invoked on screen open), so the firing widget lags one
  row behind the cursor. `OnShimSettingsRowHovered` therefore ignores the
  thunk index and resolves the hovered row from `GetCursorPos` by reversing
  the UI transform (uniform scale clientH/1080, 1440-design centered
  horizontally). Falls back to the thunk index if the resolve fails.
- **Coordinate mapping for synthetic input** (drive.ps1 harness, 4K): widgets
  on the hooked input screen map as `screenX = 480 + 2*logicalX`,
  `screenY = 2*logicalY`. The appended button on the Options *parent* screen
  does NOT follow this (the Middle_Overlay applies its own widescreen
  translation) — calibrate clicks there empirically.
- Masks: content mask now shares the top mask's x/width (one flush panel).
- Settings paging is fully wired but hidden while the registry fits one page
  (16/16 today); the 17th entry makes Prev/Next and the page label appear.

## 1. Setting descriptions on hover

Every settings row button currently installs `InputBindingUiButtonOnHoverNoop`
in its +0x150 hover slot. Replace with per-row hover thunks (same macro
pattern as `BZR_INPUT_BINDING_ROW_CLICK_DECL` / the row-click callback table):

- Add `const char* description;` to `ShimSettingDescriptor` and fill in one
  sentence per registry entry (16 today).
- Hover thunk `ShimSettingsRowHover<N>` writes the description into the status
  label directly via `SetInputBindingUiLabelTextFitted(g_ShimSettingsUiStatusLabel,
  desc, 800.0f)` — do NOT overwrite `g_ShimSettingsUiStatusText`, so the next
  full `RefreshShimSettingsUiControls()` restores the click/apply status.
- No hover-out event exists; the last description simply stays until another
  hover or a click refresh replaces it. That matches how the click status
  already behaves.
- Caution (known engine behavior, see AutoSaveButtonOnHoverNoop comment in
  bzr_hooks.cpp): some screens invoke every child's +0x150 slot when the
  screen opens, with an unspecified param. The hover thunks must therefore be
  cheap, parameterless in effect, and safe to call in bulk; writing a label is
  fine. If the open-walk makes descriptions flash on entry, gate the write on
  `g_ShimSettingsPageActive`.

## 2. Settings paging

The registry is at 16 entries — exactly `kShimSettingsUiVisibleRowCount`
(2 cols x 8). The static_assert at the registry will fire on the 17th entry.

- Add `g_ShimSettingsUiPageStart` + Prev/Next buttons cloned from the input
  page toolbar (Prev 905 w100 / Next 1015 w100 geometry already balanced
  there; reuse the same textures and text-fit calls).
- `RefreshShimSettingsUiControls()` maps registry index
  `pageStart + slot` -> row slot, blanks unused rows (`SetActive(false)` +
  blank caption — remember the caption-keeps-drawing gotcha: blank the text,
  not just the active flag).
- Row click/hover handlers translate slot -> `pageStart + slot`.
- Drop the static_assert; clamp pageStart like
  `ClampInputBindingUiPageStart` does.
- Page label ("Page 1/2") mirrors the input page's page label.

## 3. Restart-required badge

In `RefreshShimSettingsUiControls()`, when
`setting.applyGroup == ShimSettingApplyGroup::RestartRequired`, append `" *"`
to the value button text (goes through `SetInputBindingUiButtonTextFitted`, so
overflow is already handled). Extend the footer text with
"* takes effect after restart." — footer currently ends inside the header
plate at x=1135; re-measure with the new native `TryMeasureUiTextWidth` before
choosing final wording. The click status already says
"(takes effect after restart)", so the badge only adds passive visibility.

## 4. Options-screen Back quirk — ROOT-CAUSED 2026-07-17 (A/B confirmed)

Status upgraded from "investigation plan" to "confirmed root cause + fix
candidates". Reproduced live via computer-use during the 2026-07-17 retest.

**Observation (with settings UI enabled, the appended button present):** the
Options *parent* screen's top-left "Back" button (Options -> main menu) does
NOT respond to synthetic clicks — instant or 150 ms-held, single or repeated.
By contrast the Graphic Options sub-screen's Back works on one instant click,
and every other button on the Options screen (the four stock options + our
appended OpenShim button + all settings/input-page buttons) works on one click.
This is the same "sometimes needs a second click" nit noted 2026-07-16, but
synthetic instant clicks expose it every time rather than intermittently.

**A/B test (decisive):** relaunched with `OPENSHIM_DISABLE_SETTINGS_UI=1` so the
appended button is never created. The Options screen then shows only the four
stock buttons AND the top-left Back works on a single instant click. Re-enabling
the button brings the quirk back. => **the appended "OpenShim Options" button is
the cause. It is NOT the 2026-07-17 ScreenBinding/lifetime refactor** (that only
renamed the parent-screen pointer into g_ParentScreenBinding with identical
semantics; the button injection predates the file split entirely).

**Mechanism (from FUN_007b61a0 decomp, the cUI_OptionsParent ctor):**
- The ctor creates a **"Middle_Overlay" sized 1440x1080 at (0,0)** — i.e.
  *full-screen* (FUN_007d1cc0("Middle_Overlay",0,0,0x44b40000,0x44870000,...)).
- The four stock option buttons (Play/Graphic/Audio/Input) are children of that
  overlay (parent arg = local_34).
- The **top-left Back button is a *direct child of the screen*** (parent arg 0),
  onClick = FUN_007b60d0 -> FUN_00788060 (a fixed callback; no child indexing).
- `EnsureShimSettingsMenuButton` adds our button to the middle overlay via
  ResolveOptionsParentMiddleOverlay -> AddChild. So our button becomes a 5th
  child of the *full-screen* overlay.
- Therefore the interference is in the screen's **click dispatch between the
  full-screen overlay subtree and the sibling Back button**, not in any onClick
  handler. Adding a child to the full-screen overlay perturbs which
  widget consumes the top-left click (two-phase press latch at text/button
  offset +0x92d: mousedown sets it, mouseup checks it — a mismatched
  press/release target across the overlay boundary yields "no click" or
  "needs a second click").

**Refined mechanism (from the 2026-07-17 fix attempt below):** the stock four
option buttons are overlay children and Back works fine with them, so it is not
"any overlay child" — it is specifically the *fifth* overlay child (our button)
that tips the screen's two-phase click dispatch. The click model is press/release
matched per widget (text/button latch at +0x92d: mousedown sets it, mouseup
checks it). Exactly one widget ends up "starved" of clean clicks, and which one
depends on which list our button sits in.

**Fix attempt 2026-07-17 (add to screen dispatch list) — FAILED, reverted:**
changed `AddChild(buttonParent,...)` to `AddChild(parentScreen,...)` so our
button joined the screen's own child list (keeping the overlay as ctor parent
for coordinates). Result live: **Back started working on a single click, but the
OpenShim button itself stopped navigating** (highlighted on hover, no onClick —
confirmed with both instant and 150 ms-held clicks). Cause: the Middle_Overlay
is full-screen and sits *earlier* in the screen's child list, so it consumes our
button's clicks before dispatch reaches our now-sibling button. This merely moves
the starved widget from Back to our own button — strictly worse, since our button
is the primary feature. **Reverted to the overlay parent (the original, working
trade-off: our button works; Back occasionally needs a second click).** So the
"parent to screen root" idea (old candidate 1) is disproven — do not retry it.

**Remaining fix candidates (harder; need dispatch RE, not a one-liner):**
1. **RE the screen's two-phase click/capture dispatch** (the per-frame routine
   that walks children calling their mouse handlers and the +0x92d press latch)
   and understand why the 5th overlay child starves Back specifically. The fix
   likely lives there (e.g. our button needs a flag the stock buttons carry, or
   the dispatch has an assumption about child count/order). This is the real fix
   and needs the dispatch decomp, not a reparent.
2. Add our button to the overlay but *not* as the last child (insert before an
   existing stock button via AddChild's sibling-anchor arg — FUN_007d2110's 2nd
   param is a sibling POINTER, 0 = append). Cheap to try; keeps our button in
   the overlay so it won't break. Only worth it if the starvation is a
   pure last-child artifact.
3. Give the stock Back button a redundant, robust click path (e.g. also handle
   ESC / hook the Options screen input) so it no longer depends on the perturbed
   dispatch. Sidesteps the root cause rather than fixing it.

Keep the OPENSHIM_DISABLE_SETTINGS_UI kill switch as the A/B harness. Note the
quirk is mild on real hardware ("sometimes a second click"); synthetic instant
clicks expose it every time, so weigh effort against a low user impact.

## 5. Row-step consistency (46 vs 38)

The settings page rows step 46px while the input page steps 38px. Change the
settings row step constant in `EnsureShimSettingsUiControls` to 38 and retune
row plate heights so both pages read as one family. Low risk; pure geometry.
With paging (#2) this also raises rows-per-column from 8 to 9-10 if desired —
decide after #2 lands rather than before.

## Suggested order

3 (trivial) -> 1 (hover) -> 5 (geometry) -> 2 (paging) -> 4 (investigation,
needs live game anyway). Items 1-3 and 5 are all confined to
bzr_options_ui.cpp and testable in one in-game pass.
