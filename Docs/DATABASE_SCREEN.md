# Database screen

A **DATABASE** button on the stock Single Player screen opens an OpenShim
screen with faction tabs on the left (NSDF, CCA, Black Dogs, CRA,
Fury, Briefings), a paged entry list under them, and the selected entry on the
right. Back or Esc returns to Single Player. Nothing is sent over the network
and no Lua runs.

Approved design: item 16 in `Docs/APPROVED_DESIGNS.md`. Out of scope for v1:
unlocks, a PDA, 3D previews, multiplayer, and lore text (the content format
keeps an empty `lore` field for it).

Gate: `[Features] Database = 1` (default on). Env kill switch
`OPENSHIM_DISABLE_DATABASE=1` (alias `BZR_DISABLE_DATABASE`), honoured only when the ini key is absent (the ini key is read first). Options row
"Database" (System page) writes the key; read each time Single Player is
built, so no restart. Stock value for Reset to Stock is off.

Code: `src/patches/database_screen.cpp`; policy `include/database_policy.h`
(tests `tests/database_policy_tests.cpp`); the briefing page reader shared
with the lobby overlay, `src/patches/des_reader.cpp`; content
`resources/database/oshdb.cfg` (embedded through `database_content.rc`).

## The button

- Single Player Middle_Overlay, design rect **535.5, 4, 369x68** (top
  centre), stock `tomnoff/tomnon/tomnclk` skin.
- Why there: the stock Red Odyssey button uses the same 369x68 skin at the
  bottom centre, so this mirrors it at the top, between the top-corner Back
  (x 0..342) and the Campaign button on the right, above the posters video
  (y 85).
- To move it, edit `kDatabaseButtonRect` in `database_screen.cpp` (one
  commented constant).
- No button when Single Player shows the training prompt (the screen then
  builds none of its normal widgets).

## Layout and theme

The screen uses a painted 1440x1080 panel, `osh_database_center.png`
(`resources/ui/custom_widgets/mkscreens.py`, `DATABASE_LAYOUT` and
`database_center()`), like Career, Bans and LAN. The rects in
`database_screen.cpp` mirror `DATABASE_LAYOUT`; change both together.

- Frame with the brackets capped at y 828, title plate (470,132,500,56)
  with the title label on it.
- Tab strip: six 150x40 slots at y 236, pitch 160, from x 228.
- List box (228,288,400,630): **14 rows** a page (wells 368x36, pitch 40
  from y 300), then a Prev / "Page n/m" / Next footer at y 872.
- Detail box (644,288,568,630): 44 px header band holding the entry title,
  a 260x260 picture square at (798,346) (reserved for a later 3D preview),
  the text block (660,618,536,240) and a briefing Prev / Next footer.
- Tabs, rows and footer buttons use the flat `osh_tool_hv/ck` skins (stock
  skins when the art is not deployed). Back stays the top-corner button.
- Without `osh_database_center.png` (DLL updated without running the deploy
  script), the list and detail boxes get stock `uiplate.png` plates with
  `uiline.png` borders instead, at the same rects, and the log says so.
- The selected tab and row are shown by tinted quads (`osh_preview_white.png`,
  moved with `Shell::SetPanelRectColor`), created before the buttons so they
  sit behind them. The old `> ` caption prefixes are gone.
- Pictures are letterboxed inside the square, never stretched. Loading-screen
  pictures are wide; 16:9 is assumed (`kPictureAspect`) because no image size
  query exists.
- The panel is listed in `include/menu_theme_policy.h`, so the Blue, Red and
  Amber presets recolour it with the other `osh_*_center.png` panels. The
  panel is also in the deploy and install lists.

## Content file (`oshdb.cfg`)

INI-like text, `;` or `#` comments, one `[kind id]` header per section.
A header may carry a trailing comment (`[tab nsdf] ; x`). A value ends at a
` ;` or ` #` that follows whitespace and sits outside double quotes, so
`designation = text | citation; more` keeps its `;`.

| Section | Keys |
| --- | --- |
| `[tab <id>]` | `label` |
| `[unit <odf>]` | `tab`, `name` (role; overrides the .inf), `model` (overrides the .inf), `designation = text \| citation` (repeatable), `icon` (texture name), `lore` (empty in v1) |
| `[campaign <id>]` | `tab`, `label`, `source` (optional, shown in the title), `missions` (stems, space or comma separated; repeatable) |
| any other kind | `tab`, `label`, `text` (repeatable lines), `icon` |

Tabs show in file order and, inside a tab, its sections in file order.
Other kinds (relics, personnel) need no code: give them a `tab` and `text`
lines.

Override: a mod (for example Campaign Reimagined) ships its own `oshdb.cfg`.
The screen reads it through the game's file system (`PathBlock::ReadFile`)
each time it opens and merges it over the built-in file:

- a section with the same `[kind id]` merges into the stock one: each key
  the mod names replaces every stock value of that key;
- `remove = 1` drops the section;
- a new section is appended (new tabs land after the stock tabs; up to 6
  tabs show).

Parse errors are logged as `[DATABASE] override line N: ...`. When a mod
removes a tab that still has entries, the log says `[DATABASE] override tab
'x' was removed but N entries still point at it`.

Files are checked with the game's size lookup (`Music::ResourceSize`) before
`ReadFile`, so an absent `oshdb.cfg`, `.inf` or ODF is never read.

Source rule: base-game text only (unit `.inf` / `.des`, briefings, voice
transcripts), plus the BZ98 Redux manual, the 1998 Brady strategy guide and
the official Red Odyssey manual, each cited in the `designation` line.
Nothing is inferred.

## Unit entries

- Caption: `<model> - <role>` from `<odf>.inf` line 1 (`MODEL - ROLE:`), or
  the ODF's `[GameObjectClass] unitName` when there is no `.inf`, else the
  ODF name.
- Detail: role, model, every cited model number with its citation, then live
  ODF stats from `<odf>.odf`: scrap cost (`scrapCost`), armor
  (`maxHealth`), ammo (`maxAmmo`), speed (`velocForward`), and weapons by
  slot (`weaponName1..8`, each named from its weapon ODF's `[WeaponClass]
  wpnName`). A missing ODF reads "ODF not found".
- Picture: stock Redux ships no per-unit icon texture. Units whose
  loading-screen picture ships (`LoadingScreen avfigh_v1.png` and so on, and
  the three Black Dogs `LoadingScreenBV*.png` and the three CRA
  `LoadingScreenCV*.png`) show it; the others show none.
- The Black Dogs, CRA and Fury entries need the Red Odyssey content; without it
  their ODFs are not found and the entries say so.

## Briefings tab

One row per mission, `<campaign> - <stem>`. Pages are `<stem>.des` then
`<stem>_N.des` with `<stem>_N.png` pictures, read exactly as the lobby
Briefing overlay reads them (`des_reader.cpp`, `LobbyBriefingPolicy`). Prev /
Next page through them. A mission with no `.des` reads "No briefing found".

## How it hooks in

No new hooks and no new `scripts/patches.json` rows.

| What | How | Row / evidence |
| --- | --- | --- |
| Button | `ShellScreens::ObserveStockScreen(2, ...)` | existing factory rows (shell_screens.cpp) |
| Screen | `ShellScreens::RegisterScreen`, id `kCustomScreenIdBase + 7` | existing |
| File reads | `PathBlock::ReadFile` | existing row 0x008290F0 |
| Text | `cUI_ScrollingTextBlock` | existing `ScrollingTextBlock*` rows |
| Briefing pages | `DescriptionFileLoad`, `Music::ResourceSize`, Ogre `resourceExistsInAnyGroup` | existing (shared with the lobby overlay) |

## RE facts

Addresses are GOG 2.2.301.

- Shell factory case 2 (FUN_007C7AD0 lines 88-107) builds `cUI_SinglePlayer`
  (new 0x180, ctor FUN_007BF440). Its vtable 0x008A0350 is stored at
  0x007BF489 and carries RTTI `.?AVcUI_SinglePlayer@@` (COL 0x008B5E6C); the
  observer checks that name on the live object before touching it.
- Middle_Overlay is at +0x14C: FUN_007BF440 `param_1[0x53] = local_4bc`;
  GOG exe 0x007BF5A8 `mov [eax+0x14c], ecx`.
- Training prompt byte +0x17C: FUN_007BF440 lines 63-66 store
  FUN_004894F0()'s result there (GOG exe 0x007BF4CA `call 0x4894f0`,
  0x007BF4D5 `mov [ecx+0x17c], al`); line 132 builds the normal widgets only
  when it is zero.
- `PathBlock::ReadFile` (FUN_00828DC0) returns 0 for a missing file without
  an alert (it only formats a message into DAT_009467C0 on an fopen failure),
  so looking up an absent `oshdb.cfg` is silent.

## Log

`openshim.log` lines start with `[DATABASE]`: install or the reason it is
off, the button being added (or why not), the screen build (tab and section
counts), an override merge, content parse errors, and `could not read
<file> (<n> bytes; cap <cap>)` when a file exists but cannot be read (for
example a record over the 1 MB cap; the buffer is sized from the reported
size).

## Live checklist

Use stock Redux with the Red Odyssey content present, then once with a test
mod that ships an `oshdb.cfg`.

1. Single Player shows DATABASE at the top centre, not overlapping Back
   (top left), the Campaign button (top right), the posters video or any
   other stock widget, at 16:9 and at a wide window. Log `[DATABASE]
   installed` and `DATABASE button added`. If it needs to move, note the
   wanted design rect for `kDatabaseButtonRect`.
2. The training-prompt variant of Single Player (fresh profile) shows no
   DATABASE button and works as stock.
3. Click DATABASE: the screen opens on the NSDF tab with the first unit
   selected. Tabs read NSDF, CCA, Black Dogs, CRA, Fury, Briefings; the selected
   tab and row show the tinted highlight quad.
4. NSDF list: captions are `MODEL - ROLE`; 14 rows a page, with Prev/Next
   and "Page 1/n" when there are more. Captions fit the wells.
5. Select avturr: role, model, the six cited Badger model numbers with
   citations; scrap cost, armor, ammo, speed and weapons match
   `avturr.odf`. Select avfigh: the loading-screen picture shows.
6. CCA, Black Dogs, CRA, Fury: each lists its units; Black Dogs show the Red
   Odyssey model numbers (CRA entries show none, because the manual gives CRA units no designations); no entry reads "ODF not found".
7. Briefings: Training, NSDF, CCA, Black Dogs and CRA missions listed; selecting
   one shows its `.des` text and the title names the campaign (Black Dogs and CRA
   end "(Red Odyssey)"); a multi-page mission pages with Prev/Next; long
   text scrolls with the block's arrows.
8. Unused list rows and hidden page buttons show no caption and do nothing
   when clicked.
9. Back and Esc both return to Single Player, which still works (Campaign,
   Instant Action, Red Odyssey). Open and close the screen three times: no
   crash or stale text.
10. Override: a mod `oshdb.cfg` with `[unit avfigh]` `designation = Test |
    test`, `[unit avmine]` `remove = 1`, a new `[tab relics]` `label =
    Relics`, and `[relic r1]` `tab = relics`, `label = Test relic`, `text =
    hello`. The avfigh entry shows only the test designation, avmine is gone,
    a Relics tab lists "Test relic" showing "hello". Log `[DATABASE] oshdb.cfg
    from the game file system merged`.
11. Regression: the MP lobby Briefing overlay still opens and pages
    (`Docs/LOBBY_BRIEFING.md` steps 1-5); it now uses the shared reader.
12. `[Features] Database = 0`, then `OPENSHIM_DISABLE_DATABASE=1`: no button
    next time Single Player opens.
13. Options row off, then Reset to Stock: the feature is gone (and the row
    shows Off after Reset to Stock).
14. Theme: for each Menu Colors preset (Stock, Blue, Red, Amber) at
    16:9 and at 4:3, open the screen. The painted panel recolours with the
    other screens; the frame, boxes, slots and wells line up with the tab,
    row, picture, text and footer widgets; nothing is clipped at 4:3.
15. Highlight quads: the selected tab and row show behind their captions in
    every preset, hover and click still work on tabs and rows, and clicking
    on a highlighted row selects it (the quad takes no click).
16. Loading-screen picture (select avfigh): it sits letterboxed inside the
    260x260 square with no stretch; note the real aspect if 16:9 is wrong.

## Known limits

- Layout, the text block's arrows and the picture box are UNVERIFIED live.
- UNVERIFIED: the highlight quads draw behind the transparent buttons (z
  order) and take no input; and how the Menu Colors shader treats the white
  `osh_preview_white.png` quad (it is not in the theme list, so only its
  argb tint applies). If a preset shows the wrong highlight colour, tint it
  per preset or drop the quad.
- `SetPanelRectColor` only works on DX11 (src/engine/shell_screens.cpp).
  On DX9, or with `osh_preview_white.png` missing,
  the quads stay hidden: the selected tab and row then fall back to a `> `
  caption prefix, and pictures fill the whole square (no letterbox).
- UNVERIFIED: the letterbox aspect (16:9 assumed) and that
  `SetPanelRectColor` on the picture panel keeps its texture.
- Briefings have no stock pictures, so the picture area stays empty for them.
- Rows past the end of the list are blanked by caption; their hover
  highlight may still show (they sit over painted empty wells).
- Up to 6 tabs, 30 characters per list caption and 12 per tab caption; cuts
  never split a UTF-8 character.
- File reads (ODF, weapon ODFs, `.inf`) run on the UI thread when the screen
  opens and on each selection; they are small and cached per open.
