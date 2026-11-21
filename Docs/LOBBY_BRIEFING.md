# Lobby briefing overlay

The multiplayer lobby (host and client) gets a **Briefing** button. It opens a
panel over the lobby that shows the selected map's briefing text with its
picture beside it, one page at a time. Close or Esc returns to the lobby as it
was. No Lua runs, nothing is sent over the network, and each player pages on
their own.

Approved design: item 15 in `Docs/APPROVED_DESIGNS.md` (option A, an overlay
inside the lobby screen rather than a shell screen of its own).

Gate: `[Features] LobbyBriefing = 1` (default on), also the Options row
"Lobby Briefing" (Network page); read each time the lobby is built, so no
restart. Kill switch: `OPENSHIM_DISABLE_LOBBY_BRIEFING=1` (wins over the key).
Stock value for Reset to Stock is off.

Code: `src/patches/lobby_briefing.cpp`, policy `include/lobby_briefing_policy.h`
(tests `tests/lobby_briefing_policy_tests.cpp`), stock-screen observer in
`src/engine/shell_screens.cpp` (`ShellScreens::ObserveStockScreen`).

## Files

For a map file `<m>.bzn` the overlay reads the same files as the
single-player briefing pages (`Docs/BRIEFING_PAGES.md`, `briefing_pages_policy.h`):

| Page | Text | Picture (optional) |
| --- | --- | --- |
| 1 | `<m>.des` | `<m>_1.png` |
| N = 2..9 | `<m>_N.des` | `<m>_N.png` |

- No `<m>.des`: the button is greyed out and reads "No Briefing".
- Pages stop at the first missing `<m>_N.des`, as in `BriefingPagesPolicy::CountPages`.
- Every file name must fit in 15 characters, so pages 2+ need `<m>` of 8
  characters or fewer; longer names stay single-page.
- Text per page is clipped to 0x2700 characters (the text block's buffer).

## Controls

- Briefing button: in the lobby settings grid, the free slot right of
  AnyNation (design 1060,580, 300x60).
- Prev / Next buttons, Left/Right, PgUp/PgDn (the `StepForKey` keys): page.
- Up / Down: scroll the text within a page; the block's own arrows work too.
- Close button or Esc: close. While the panel is open every key and typed
  character stops at the panel (chat, map list and Enter do nothing).

## How it hooks in

| What | Where | Row (`scripts/patches.json`) |
| --- | --- | --- |
| Build | Stock-screen observer for shell id 0xF, run inside the factory call right after the stock factory returns; works with or without `mp_map_filter_extras` | existing factory rows (shell_screens.cpp) |
| Click blocking | Overlay view inserted as the screen's first child; hidden = +0xE9 clear | `AddChild` (existing) |
| Draw order | Overlay z 8, content z 1 (render queue 0x3C + summed z) | `UiViewSetZOrder` 0x007D3F20 |
| Keys | Lobby vtable slot 2 (char), slot 4 (KeyPressed), slot 5 (KeyReleased); slot 13 untouched | `MultiCreateChar` 0x0079CD20, `MultiCreateKeyPressed` 0x0079CD40, `UiViewKeyReleased` 0x007D2490 |
| Per-frame | The overlay view's own copy of the cUI_View vtable; slot 13 runs the tick after the stock update, slot 0 forgets the overlay | `UiViewVtable` (existing) |
| Text | `cUI_ScrollingTextBlock` | `ScrollingTextBlockCtor` 0x007CD8D0, `ScrollingTextBlockSetText` 0x007CE0B0 (existing), `ScrollingTextBlockScrollUp` 0x007CE0E0, `ScrollingTextBlockScrollDown` 0x007CE110 |
| Greyed out | `cUI_Button` enable byte +0x148 | `UiButtonSetEnabled` 0x007C3040 |
| Selected map | Map component selected entry, else the lobby record | `MapComponentSelectedEntry`, `AnyNationLobbyRecord` (existing) |
| Text load | Stock `.des` loader | `DescriptionFileLoad` (existing) |

The vtable audit (`scripts/audit_vtable_hooks.py`) lists the three slot wraps.

## RE facts

Addresses are GOG 2.2.301. Line references are to the Ghidra decompile of the
named function.

- The lobby is `cUI_Multiplayer_Create`, ctor FUN_00796880 (object 0x1D8,
  vtable 0x0089EBE0). Middle_Overlay at +0x150, net lobby +0x1BC, map
  component +0x1C8, chat entry +0x1D0 (ctor body, the stores after each
  sub-widget ctor).
- The ctor places the settings buttons (FUN_007C3E30, 300x60) at x 50/400
  (rows 510/575) and x 760/1060 (rows 470/525/580). Nothing sits at 1060,580,
  which is where the Briefing button goes. UNVERIFIED live: that nothing a
  later refresh shows (Splinter / KillLimit variants) lands there.
- The click walk `cUI_View::MousePressed` 0x007D2570 visits children that
  have children first, in vector order (+0x12C..+0x130), then leaves. A view
  claims the click when +0xE9 is set (FUN_007D3360) and the point is inside
  its pixel rect (FUN_007D2810). `cUI_Button` MousePressed 0x007C2BB0 also
  needs +0x148 and does not recurse, so the overlay root is a plain cUI_View.
- `AddChild` FUN_007D2110 takes (parent, child, before); a non-zero `before`
  inserts in front of that child. The overlay goes in front of the screen's
  first child.
- Child coordinates are relative to the layout parent: the ScrollingTextBlock
  ctor places its arrows at (w+5, h-70) and (w+5, h-35). The overlay reaches
  1200 design units past each side of the 1440 area so it also covers corner
  buttons anchored to a wide window's edges; its children add that offset.
- `cUI_View` SetActive 0x007D3310 sets +0xE9 and the Ogre visibility but does
  not recurse. `cUI_Button` overrides slot 9 (0x007C27F0) to also hide its
  caption label (+0x144), so buttons are hidden through the virtual call.
- The lobby update 0x0079CDA0 calls FUN_007D37F0, which calls slot 13 on each
  child: the overlay's own vtable gets a tick without touching the lobby's
  slot 13 (the map preview fix, `lobby_screen_hooks.cpp`).
- `cUI_ScrollingTextBlock` ctor 0x007CD8D0 (object 0x295C): scroll at
  +0x2958, arrows +0x2950/+0x2954, hidden at build and shown by the render
  FUN_007CDD50 as needed. ScrollUp/ScrollDown do not clamp, so the overlay
  scrolls up only above 0 and down only while the down arrow is shown.
  SetText 0x007CE0B0 resets the scroll and calls 0x007CCD50, whose
  `_snprintf(this+0x144, 0x2800, ...)` leaves no NUL on truncation; hence the
  0x2700 clip. cUI_Mission builds the same block at 0x0078FD91..0x0078FD9E.
- Lobby key slots: 2 = 0x0079CD20 (appends to chat +0x1D0), 4 = 0x0079CD40
  (Up/Down scroll the map list, else children dispatch FUN_007D2330),
  5 = 0x007D2490 (shared cUI_View KeyReleased; only the lobby's slot is
  rewritten).
- Map name: the map component's selected entry (FUN_007A4220) holds the file
  name std::string at +0x00 (as `mp_map_filter_extras.cpp` reads it); the
  fallback is the lobby record (FUN_0056F900) map file at +0xDC (as
  `mp_any_nation.cpp` reads it). UNVERIFIED: that the host's own pick is
  written to record+0xDC before the map list selects it.

## Known limits

- Pictures stretch to their 450x338 box; there is no aspect fit.
- A stock alert raised while the panel is open is drawn but cannot be clicked
  until the panel closes (Close or Esc still work). The panel does not yet
  close itself for an alert. The shell manager bytes +0x24/+0x28 are not an
  "alert pending" signal: FUN_007C9170 sets them (+0x24 = 1, +0x28 = arg) and
  its callers include the GameAlert OK callback FUN_00787CC0, so they are set
  once the alert is dismissed. The pending flag is the global DAT_00918132,
  read by the factory (FUN_007C7AD0 line 777), which attaches the GameAlert
  (FUN_00787DE0) only to a newly built screen. UNVERIFIED: whether a kick
  rebuilds the lobby (which would remove the panel) or adds the alert to the
  live one.
- Chat Enter while the panel is open is swallowed.
- Names over 15 characters are not looked up; pages 2+ need `<m>` of 8
  characters or fewer.
- Placement, z order and the greyed look are UNVERIFIED live.

## Log

`openshim.log` lines start with `[LOBBYBRIEF]`: install or the reason it is
off, build, each map change (`briefing available` / `no .des, button
greyed`), open, close (with the reason), and a one-time line if the tick
faults or the closed overlay was found shown.

## Live checklist

Host and client each on an OpenShim build. Use a map with `<m>.des`,
`<m>_2.des` and `<m>_1.png`, and a map with no `.des`.

1. Host: lobby shows Briefing in the 1060,580 slot, not overlapping
   AnyNation or KillLimit; log `[LOBBYBRIEF] installed` and `built`.
2. Host: pick the map without a `.des`: button greyed, reads "No Briefing",
   clicks do nothing. Pick the map with one: button live again (log line each
   change).
3. Host: open. Panel covers the lobby, text left, picture right, title and
   "Page 1/2". Clicks on lobby widgets behind it (map list, settings, chat,
   Back, Launch corner) do nothing, also on a wide window.
4. Host: Next / Right / PgDn to page 2, Prev back; Up/Down and the arrows
   scroll long text.
5. Host: Esc closes the panel and leaves the lobby (no Back to the previous
   screen). Close button does the same. Lobby state (map, settings, chat
   text) unchanged.
6. Client: joins, sees the host's map, button state follows it; open, page,
   close as above.
7. Host changes the map while the client's panel is open: the client's panel
   switches to the new map's page 1, or closes if that map has no briefing.
8. Launch while open: client has the panel open and the host launches. The
   game starts normally on the client; no crash, no stuck panel next time the
   lobby opens.
9. Kick while open: client has the panel open and the host kicks them. The
   client gets the stock kick handling and leaves the lobby; no crash.
10. `OPENSHIM_DISABLE_LOBBY_BRIEFING=1` at launch: no button, log says disabled. `[Features] LobbyBriefing = 0`: no button, no log line.
11. Options row off, then Reset to Stock: the feature is gone (no button in
    the next lobby; the row reads Off).
