# Porting the Battlezone 1.5 multiplayer UI into Redux

The 1.5 multiplayer shell is worth reconstructing: it has a transport picker, a
persistent character/profile list, a flag selector, a player-information card
and a game-setup screen with per-option buttons — most of which Redux either cut
or never had. OpenShim already grows a couple of widgets onto the Redux lobby
(`Ban User`, `Flag Select` and a 1.5-style flag preview tile in
`bzr_hooks.cpp`), so the mechanism exists; what is missing is the *design*, and
that can be recovered exactly rather than guessed.

`tools/export-bz15-ui.py` produces that recovery as a JSON manifest. Run it
against a 1.5 install and the decompile:

```bash
python tools/export-bz15-ui.py --install <Battlezone_Install> --decompile <BZ1_Source/1.5> --out out --bitmaps
```

The output is deliberately **not** committed: `--bitmaps` extracts retail button
art out of `bzone.exe`, which belongs in a local working directory, not in this
repository. The tool is reproducible, so the manifest can be regenerated any
time.

## Why an exporter rather than a transcription

The 1.5 shell is not a normal Win32 dialog. `Shell_DialogBoxParam` loads a
template that contains only the *real* controls — edit boxes, list boxes, the
rich-edit chat pane — while every visible button, label, option box, background
plate and the flag picker is a C++ object built in the dialog procedure with
hard-coded 640x480 pixel coordinates. Both halves are needed, and neither is
readable by eye at any useful scale:

| screen | proc | dialog | Win32 controls | constructed widgets |
|---|---|---|---|---|
| Transport / profile / flags | `STransportDlgProc` `0x00569627` | 105 | 8 | 21 buttons, 11 labels, 3 option boxes, 4 plates, 1 flag list |
| Game setup | `NetGameDlgProc` `0x0055DA02` | 2029 | 9 | 29 buttons, 17 labels, 12 option boxes |
| Nickname | `NameDlgProc` `0x0055714B` | 150 | 1 | 2 buttons, 1 label |
| Room | `RoomDlgProc` `0x00564E09` | 152 | 2 | 2 buttons, 2 labels |
| Game name/password | `GameDlgProc` / `PasswordDlgProc` | 154 / 155 | 2 / 1 | |

`NetGameDlgProc` and `ShellDlgProc` both exceeded Ghidra's decompiler timeout,
so the game-setup screen exists only as disassembly. The exporter scrapes the
constructor calls straight out of the listing — arguments are pushed
right-to-left, so walking backwards from the `call` meets them in declaration
order — and constant-propagates registers where it can. On `NetGameDlgProc` that
resolves all but 4 of 236 coordinate slots; the rest are reported as `null`
rather than guessed.

## The transport screen (dialog 105)

This is the screen the request describes. Everything below is in 640x480 shell
pixels, straight out of the manifest.

**Navigation**, shared with every shell screen:

| button | bitmaps (off/over/on) | rect |
|---|---|---|
| `BACK` | 259 / 258 / 260 | 1, 0, 152x34 |
| `NEXT` | 202 / 201 / 203 | 488, 0, 152x34 |
| `OPTIONS` | 199 / 198 / 200 | 1, 445, 199x34 |

**Connection picker** — `LISTBOX 0x041F` at 334, 65, 258x72, filled by
`dpEnumTransports`, labelled "Connection". Selecting an entry sets
`nTransportMode` and reshapes the rest of the screen:

| mode | transport | background plate |
|---|---|---|
| 1 | Modem | `bitmap\multip1b.bmp` |
| 2 | Null Modem (serial) | `bitmap\multip1a.bmp` |
| 3 | **Internet (TCP/IP)** | `bitmap\multip1c.bmp` |
| 4 | **IPX (LAN)** | `bitmap\multip1.bmp` |
| 5 | none selected | `bitmap\multip1.bmp` |

Mode 3 builds a `ServerList` into `LISTBOX 0x0820` and reveals the
`Server` / `pl` / `ms` column headers; mode 1 reveals the phone book, dial and
answer controls; mode 2 reveals only the null-modem COM port box. That
show/hide table is the actual "LAN options vs TCP/IP options" behaviour and it
is all in the manifest.

**Character (profile) list** — `LISTBOX 0x07D9` at 145, 65, 141x156, labelled
"Characters", with `New` (142, 229, 82x26) and `Delete` (227, 229, 82x26)
buttons and a 19x18 scroll pair at 289, 188 / 289, 206. Selection is owned by
`PlayerNameList::Load`, which binds the list together with the e-mail, web-page
and description fields and the flag list in one call.

**Nickname** is not on this screen — it is dialog 150, a single
`EDIT 0x07E0` at 69, 7, 104x21 in a 185x77 popup driven by `NameDlgProc`,
reached from the `New` button.

**Flag selector** — `FlagList` at 52, 71, with `flagLeftButton`
(90, 114, 18x19, bitmaps 0/2071/2049) and `flagRightButton`
(108, 114, 18x19, bitmaps 0/2070/2050), under a "Flags" label at 57, 46.

**Player information** — a multiline `EDIT 0x0429` at 46, 299, 261x93, plus
`E-Mail` (`EDIT 0x07E1`, 164, 397, 143x15) and `Web Page`
(`EDIT 0x07DF`, 164, 418, 143x15).

Every label carries its localisation key (`read_text_label("multi_one",
"flags", ...)`), so the strings can be pulled from the game's own text data
rather than hard-coded.

## Mapping onto the Redux widget API

OpenShim already resolves three constructors (`bzr_options_ui.h`):

```cpp
ButtonCtor (self, label, x, y, w, h, flags, parent, a, b)
LabelCtor  (self, label, x, y, w, h, flags, parent, a)
OverlayCtor(self, label, x, y, w, h, flags, parent, a)
```

plus `SetTextureOff/Over/On`, `SetButtonLabel`, `SetTooltip`, `SetOnClick`,
`SetOnHover`, `SetActive` and `AddChild`. The 1.5 widget kinds map onto these
as follows.

| 1.5 | Redux | notes |
|---|---|---|
| `ShellButton` | `ButtonCtor` | direct; three bitmaps map onto the off/over/on texture setters |
| `TextLabel` | `LabelCtor` | direct |
| `ShellBitmap` background | `OverlayCtor` | one full-screen plate per transport mode |
| `FlagList` | existing flag preview tile | `CreateFlagButtonCommon` already does this |
| `OptionBox` | `cUI_Multiplayer_SettingButton` | Redux's own per-setting control on the create-game screen |
| `LISTBOX` | `cUI_Selectlist` | resolved, see below |
| `EDIT` | `cUI_TextEntry` | resolved, see below |

### The rest of the toolkit, located

Redux has a far richer widget set than the three constructors OpenShim
currently binds. The shipped executable carries RTTI, so every polymorphic
`cUI_*` class can be found by name; `tools/find-redux-ui-ctors.py` walks
`.?AVcUI_X@@` → TypeDescriptor → CompleteObjectLocator → vftable → the
functions that store that vftable, and tells the constructor from the
destructors by its `ret N` (a `__thiscall` cleans its own arguments, so N is
four times the argument count).

The method is calibrated: it reproduces all three addresses OpenShim already
had hard-coded — `cUI_Button` `0x007C2480`, `cUI_Text` `0x007CC390` and
`cUI_View` `0x007D1CC0`, which is what `g_BzrFn_OverlayCtor` actually is.

| class | ctor | args |
|---|---|---|
| `cUI_View` | `0x007D1CC0` | 8 |
| `cUI_Button` | `0x007C2480` | 9 |
| `cUI_Text` | `0x007CC390` | 8 |
| **`cUI_TextEntry`** | **`0x007CF410`** | **10** |
| **`cUI_Selectlist`** | **`0x007C9DE0`** | **11** |
| `cUI_Checklist` | `0x007C3150` | 7 |
| `cUI_Slider` | `0x007CBD60` | 7 |
| `cUI_ProgressBar` | `0x007C9A10` | 7 |
| `cUI_Alert` | `0x007C1EF0` | 7 |
| `cUI_Parent` | `0x007C6360` | 3 |
| `cUI_Multiplayer_SettingButton` | `0x007C3E30` | 16 |

`cUI_TextPopup`'s vftable is at `0x008A0B54` but no function with the expected
`ret` was found, so its argument count differs from the reference PDB and is
still open. `cUI_UserBar` and `cUI_Multiplayer_UserSelect` exist in the PDB but
have **no RTTI in the shipped build** — assume they were cut.

### The two that matter, with signatures

The private PDB in this repo is from a *different* build (different CodeView
GUID, `.text` about half the size), so its RVAs are unusable and several
constructors gained parameters. The signatures below were therefore measured at
the shipped call sites rather than taken from the PDB — `--call-sites` on the
tool dumps them, resolving string pointers and the `movss` constants used to
pass floats.

```c
// 0x007CF410, 7 call sites. Extends cUI_Text and forwards args 4..10 to it.
void* __thiscall cUI_TextEntry(void* self,
                               int   flagA,        // -> byte at +0x960; 1 or 0
                               int   allowEnter,   // -> byte at +0x950; always 1
                               int   maxLength,    // -> +0x948; 42 or 36
                               const char* name,
                               float x, float y, float w, float h,
                               int   flags,        // 0x8020
                               void* parent);

// 0x007C9DE0, 18 call sites. Extends cUI_View, which it calls with flags|0x20.
void* __thiscall cUI_Selectlist(void* self,
                                const char* name,
                                float x, float y, float w, float h,
                                void (*onPageUp)(),    // NOT selection handlers
                                void (*onPageDown)(),  // see below
                                int   flags,        // 0
                                void* parent,
                                uint32_t rowColour, // 0xFF00FF00
                                float rowScale);    // 1.0f
```

Observed live examples: `("CreateTextEntry", 760, 945, 580x40)` and
`("chatEntry", 470, 945, 520x40)`; `("Mission_List", 290, 260, 530x450)` and
`("FriendList", 260, 160, 720x540)`. Note `cUI_TextEntry` takes flags `0x8020`
where the existing OpenShim buttons pass `0x20`.

**The two `cUI_Selectlist` callbacks are not selection handlers.** The ctor
builds its own page-up/page-down arrow buttons and installs these as their
*click* callbacks via `0x007C23E0` — the same setter OpenShim already binds as
`g_BzrFn_SetOnClick`. Selection-changed is a separate setter, `0x007CB3E0`,
called right after construction at every stock site. An earlier draft of this
document had them as `onSelect`/`onDoubleClick`; that was wrong.

### Sizes and offsets, confirmed against this build

The repo also contains a Ghidra decompile of the *shipped* exe
(`reverse_engineering/repo_corpora/bzr_gog_best_effort/.../decomps/`), which
settles all of this from the binary itself — the PDB is not needed and is not
trusted here.

Every call site allocates with a literal `operator new`, and the two ctors are
unanimous across all of them:

```
sizeof(cUI_TextEntry)  = 0x968   (2408)   <-- PDB says 2400; it is EIGHT SHORT
sizeof(cUI_Selectlist) = 0x180   (384)
```

The undersized PDB figure is not academic: the shipped ctor writes a field at
`+0x964`, so a 2400-byte allocation would be overrun by the constructor itself.
The three sizes OpenShim already uses are confirmed the same way, because these
two ctors allocate those very classes for their own children — `0x1EC` for the
arrow buttons (`cUI_Button`), `0x930` for the row labels (`cUI_Text`), and
`0x144` for the text cursor (`cUI_View`).

Offsets below are read out of this build's constructor code, so they are no
longer advisory:

```
cUI_TextEntry (extends cUI_Text)       cUI_Selectlist (extends cUI_View)
  +0x930  std::string text              +0x14C  int  selectedIndex   (init -1)
  +0x948  uint  displayTail (= arg3)    +0x150  int  scrollOffset    (init 0)
  +0x94C  void (*enterCallback)()       +0x168  vector<item>         (items)
  +0x950  bool  allowEnter  (= arg2)    +0x174  float rowScale       (= arg11)
  +0x954  cUI_View* cursor              +0x178  cUI_Button* pageUp
  +0x960  bool  flagA       (= arg1)    +0x17C  cUI_Button* pageDown
  +0x964  int   inputLimit  (init -1)
```

RTTI vftables, for identifying an instance: `cUI_TextEntry` `0x008A0AA0`,
`cUI_Selectlist` `0x008A08B0` (`cUI_Button` `0x008A0470`, `cUI_Text`
`0x008A096C`, `cUI_View` `0x008A0B94`).

### Driving a list

Items are `{ std::string label; int value; }`, stride `0x1C`, value at `+0x18`.

* **`0x007CABF0`** `SetItem(const char* label, int index, int value)` — overwrites
  entry `index`, or **appends when `index == size()`**, so walking the index up
  from zero fills an empty list. It also truncates the label to the list width,
  relabels the affected visible row, and shows or hides the arrows.
* **`0x007CB1A0`** — already bound in OpenShim as `g_BzrFn_GetSelected`; it
  returns the selected item's `int` value, or 0 when `selectedIndex < 0`.
* **`0x007CB3E0`** — selection-changed callback setter.

The ctor pre-creates as many row labels as fit the requested height and stops,
so **it is safe to construct a list with no items** — no separate "populate
before display" step is required.

### Hit-testing: decoration is not passive

`cUI_View::MousePressed` (`0x007D2570`, and `MouseReleased` `0x007D26C0` in the
same shape) walks the parent's children twice — first those that have children
of their own, then the leaves — in **insertion order**, stopping at the first
one that reports the event as handled. If no child takes it, the view reports
the event handled itself whenever the point is inside its own rect and its
input-active byte at **`+0xE9`** is set, and it invokes no callback while doing
so. A plain `cUI_View` is therefore a black hole for clicks, not a passive
backdrop.

That is the reverse of the drawing order in the sense that matters: a plate has
to be added *before* the widgets it frames so it draws behind them, and that is
exactly what puts it ahead of them in the walk. It swallowed every click on the
nickname entry and on `OK` — the callbacks were correct and simply never ran.

Two ways out, both used in this repo:

* Give the controls a **different parent that already has children**, so they
  are visited in the first pass ahead of the decoration in the second. This is
  what the injected options pages do: backdrops go on the screen, controls go on
  the stock `Middle_Overlay`.
* Clear `+0xE9` on the plate (`MakeViewInputTransparent` in `bzr_hooks.cpp`).
  Not `SetActive` (`0x007D3310`) — that forwards the same value to the Ogre
  element's visibility and would take the artwork down with the hit rectangle.
  Nothing else in the image reads `+0xE9`; every consumer goes through the
  getter at `0x007D3360`, and all of them are input handlers.

`cUI_Text` overrides `MousePressed` (`0x007CC9C0`) and claims a click only when
`flags & 0x400` is set, so labels and text entries are transparent by default.
`cUI_TextEntry::MouseReleased` additionally calls the global function pointer at
`0x009456C8` with `(entry, 1)` — the engine's own "focus this entry" hook, and
`(entry, 0)` from the destructor. **Nothing in `.text` ever writes that global**
(its only four references are the two `cmp`/`call` pairs), so the focus path is
dead in this build. That is the reason for the `AppendChar` detour below; it is
also an unused, code-free extension point, since installing a function there
would report entry focus without patching anything.

### Confirmed in the running game

Both bindings are exercised by an ABI probe in `bzr_hooks.cpp`
(`CreateUiWidgetProbe`), off unless `OPENSHIM_UI_WIDGET_PROBE=1`. It builds one
of each on the multiplayer screen through the same allocate + ctor + `AddChild`
sequence the ban and flag buttons use, then reads the fields back:

```
[UIPROBE] cUI_TextEntry  vtable=0x008A0AA0(ok) maxLength=36(ok) allowEnter=1(ok) text=""(readable)
[UIPROBE] cUI_Selectlist vtable=0x008A08B0(ok) selected=-1(ok) scroll=0 pageUp/pageDown(arrows built)
```

`maxLength` and `allowEnter` arriving intact is what proves the argument order:
they are arguments 3 and 2 of ten, so a misplaced parameter could not leave both
correct. The list also renders its five seeded rows on screen, which exercises
`SetItem`'s append path.

A whole-heap scan of the live process (walking committed private pages for the
five vftables) corroborates the offsets against **stock** instances rather than
only our own: a shipped `cUI_TextEntry` reads `maxLength=36, allowEnter=1,
enterCallback=0x0079D5F0` — that callback being exactly the function the
decompile passes to `0x007CF940` — while another reads `maxLength=15,
allowEnter=0`, so the fields track per-instance state rather than coincidence.
All live lists have `+0x178`/`+0x17C` pointing at objects whose vftable is
`cUI_Button`. The image loads at `0x400000` with no relocation, which is what
makes every hard-coded address here valid.

### Coordinate space — settled

The Redux UI canvas is **1440 x 1080**. `MainScreen_Overlay`, `Middle_Overlay`
and `temp overlay` are each constructed as `cUI_View(name, 0, 0, 1440, 1080,
0x60, ...)`. (The 1920x1080 `movie` views are a separate full-screen video
layer, not the UI canvas.)

That is 4:3, and so is the 1.5 shell, so the conversion is a single uniform
factor with no letterboxing and no distortion:

```
redux_x = bz15_x * 2.25          // 1440 / 640
redux_y = bz15_y * 2.25          // 1080 / 480
```

Every 1.5 coordinate in the manifest can be multiplied by 2.25 and used
directly. The `BACK` button at `(1, 0, 152x34)` becomes `(2.25, 0, 342x76.5)`;
the flag arrows at `(90, 114, 18x19)` become `(202.5, 256.5, 40.5x42.75)`.

## What already exists on the Redux side

Worth reusing rather than rebuilding:

* `CreateFlagButtonCommon` builds the flag button, its label and the 64x32
  preview tile, and `CycleSelectedFlag` walks the catalogue — the 1.5
  `flagLeftButton`/`flagRightButton` pair maps onto it directly by passing
  `delta = -1` and `+1` instead of one cycling button.
* Flag PNGs are already generated into a mod-adjacent directory and registered
  as an Ogre resource location, so the preview path is solved.
* The ban list and `/ban` plumbing show the pattern for a lobby-side action
  that needs host authority.
* `IsWidgetLiveChildOfParent` and the note about null callback slots crashing
  when the lobby walks its children: **both callback slots (+0x150/+0x154) must
  be non-null on any active dialog child.** Any new widget has to follow that,
  and it is not obvious from the API.

## Suggested order

1. ~~**Bind the two new constructors** and prove the ABI.~~ **Done** — bound in
   `bzr_options_ui.h` / `bzr_hooks.cpp` next to the existing three, with sizes,
   offsets and argument order confirmed in the running game (see above).
2. **Port the game-setup option rows.** `NetGameDlgProc`'s 12 option boxes and
   29 buttons are the highest-value cut content, and
   `cUI_Multiplayer_SettingButton` is Redux's own equivalent.
3. ~~**Port the transport screen's static furniture**~~ — **dropped.** The
   transport picker is the one piece of this screen that cannot be made to mean
   anything: Redux has no `dp_*` transport stack, no LAN browser and no
   direct-IP join, so every row would dead-end. See
   `reverse_engineering/redux_tcpip_lan_multiplayer_investigation_20260713.md`.
   What replaced it is the **route readout and preference** below, which
   describes and controls transport behaviour Redux genuinely has.
4. ~~**Wire the flag selector** to the existing OpenShim flag catalogue, replacing
   the single cycling `F` button with the 1.5 left/right pair and its label.~~
   **Done** — `CreateFlagButtonCommon` now builds the 1.5 pair at the retail
   40.5x42.75 (18x19 at 2.25x), side by side, driving `CycleSelectedFlag(-1)`
   and `(+1)`. The preview tile keeps the forward callback. Retail arrow art
   (bitmaps 2049/2050/2070/2071) is not extracted yet, so the buttons carry
   `<` / `>` captions over the stock Redux button texture.

   1.5 framed the flag in a recessed plate. Redux binds no 9-slice frame widget
   here, so the border is **baked into the generated PNG**: the image is the
   64x32 payload plus a 4px bezel (72x40), drawn at a flat 2x so the border is
   an even 8px on screen and the tile keeps the height it had before the frame
   existed. It is a *raised* bezel — grey body, dark rule inside and out,
   highlight along the top and left — because the lobby background is dark
   enough to swallow a sunken bevel's shadow side. The flag field is opaque for
   the same reason: translucent, it left the frame looking like it floated over
   nothing. The one-bit preview now follows the 1.5 palette as well: black
   emblem pixels on an opaque red field rather than Redux's earlier white-on-
   black diagnostic rendering.

   The flag summary text lives in the cluster's own column, above the preview
   tile. It used to sit at a fixed `(270, 960)`, which is the lobby's
   packet/latency strip — and since a `cUI_Text` is hover-reactive over its own
   rect, hovering the packet readout popped the flag text. The arrows were never
   the only trigger. The client-side nickname/route readouts moved from 746/798
   to 694/746 to open the slot at 802.
5. **Character profiles and the player-information card**, on `cUI_Selectlist`
   and `cUI_TextEntry`. The nickname half of this is **done** — see below.

   The injected nickname row is a real `cUI_TextEntry`, not a button-shaped
   readout. It sits in a generated 240x144 Redux-style `PLAYER NAME` panel whose
   border and header are pre-rendered like the flag preview; the native entry
   and `OK` button are separate interactive children over that plate, which is
   held **input-transparent** because a live `cUI_View` would otherwise eat
   their clicks (see "Hit-testing" above — that bug shipped once).

   The entry gets the panel's full inner width, 216, with `OK` on its own row
   underneath. Constructor argument 3 is a *width budget*, not an input limit:
   the rendered string is the **last** N characters of the backing string, and
   stock entries spend about 14.4 units per glyph (`chatEntry` is 520 wide and
   asks for 36). While the entry shared its row with `OK` it was 164 wide at
   N = 10, which rendered `TheGrizzler` as `heGrizzler`. It is now derived from
   the field width rather than picked, and 216 units carry 15 characters.

   These lobby screens have no usable general text-focus path and do
   not share a single reliable `OnChar` target. They do all feed their stock
   chat entry through `cUI_TextEntry::AppendChar` (`0x007CFA70`), however. A
   transparent button over the row therefore enables a guarded detour of that
   common append operation while nickname editing is active. Enter invokes the
   injected entry's own callback; a small `OK` button invokes the same path.
   Applying persists the value to `openshim.ini` and the native `/nickname=`
   buffer, which is what the login message carries, and then tries to publish it
   on the open connection as player data (see "Renaming: what the client
   settles, and what it does not" below). The acknowledgment reports which of
   those happened — `Sent to server`, `Reconnecting...`, or `Saved-reconnect` —
   in the 15 characters the field renders, and stops short of claiming the
   rename took, because only another client can show that. Clicking the row
   restores the real backing value for another edit. `/name <text>` remains a
   chat fallback and goes through the same path.

   Do not call the button callback setters (`0x007C23C0` / `0x007C23E0`) on a
   text entry. Their `+0x150` / `+0x154` fields are valid only in `cUI_Button`;
   those offsets lie in `cUI_Text`'s inline display buffer. That mistake was the
   reason the first injected entry was unstable. The
   lobby-style input cap is installed with `0x00795BD0` at `+0x964`; constructor
   argument 3 at `+0x948` is only the number of trailing characters rendered.

## Transport, for real: what Redux actually exposes

Everything here is confirmed against the shipped GOG image, whose sha256
(`8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413`) is
byte-identical to the decompile corpus, so the corpus addresses are
authoritative rather than advisory. Each global below has exactly four `.text`
references and no others.

| what | address | width | guard site (instruction) | notes |
|---|---|---|---|---|
| force-relay flag | `0x00946708` | dword | `0x0075F09D` `83 3D ..` | `/iprelay` writes 1, `/ipdirect` 0; read per connection attempt |
| BZRNet UDP port | `0x00945704` | **uint16** | `0x006BE7B5` `0F B7 15 ..` | requested port read here, then overwritten at `0x006BE7FF` with the port Winsock bound |
| nickname override | `0x009453E0` | `char[0x80]` | `0x006C7D84` `0F BE 91 ..` | `/nickname=` copies at `0x007D5947`; consumed by `FUN_006C6E60` |

**The guard site is the instruction address, not the operand address.** A scan
for `.text` references to a global finds the 4-byte disp32 *operand*; the
instruction starts 2 bytes earlier for `83 3D` (cmp) and 3 for `0F B7 15` /
`0F BE 91` (movzx/movsx). Anchoring an exact-byte guard on the operand address
fails silently and stands the whole feature down — which is exactly what
happened on the first in-game run here (`relay=mismatch port=mismatch
nickname=mismatch`) even though every data address was correct.

Three consequences that are easy to get wrong:

* The port is a **word**, not a dword, and it is **read then overwritten**. It
  only takes effect while the peer socket is still closed, and afterwards the
  same variable reads back as the true bound port — which is what the lobby
  readout reports.
* The relay flag is re-read on **every** connection attempt, so it can be
  changed live; the port cannot.
* The nickname buffer is read when `FUN_006C6E60` builds the identity message,
  not latched at startup. Byte 0 being NUL is the "use the platform account
  name" signal. The field it fills is that message's `name`, which is the only
  name the service is ever told, so the buffer decides the displayed name from
  the **next connect** onwards — see below.

### Renaming: what the client settles, and what it does not

**The client tells the service its name exactly once per connection.** The
`Authorization` message's `name` field is built in `FUN_006C6E60`, which reads
the `/nickname=` buffer and falls back to the platform `realname` when byte 0 is
NUL. That builder has exactly one caller, inside the connect handshake
(`0x006C844E`), so the field is fixed for the lifetime of the connection.
Persisting the buffer is therefore the one thing guaranteed to work, and it is
done first and unconditionally on every apply.

**What the shipped binary does not settle is whether the service accepts a
rename over an open connection.** It is worth being precise about the limit of
the local evidence, because an earlier revision of this document overstated it:

* Redux never re-sends `name` after `Authorization`, and `playerName` does not
  appear in the image at all. That is evidence about *Redux*, which has no
  rename feature — not about what BZRNet does with those keys.
* Nothing in Redux reads a member-data key `name` back. The keys it consumes per
  member through vtable slot 10 (`GetLobbyMemberData(memberId, key)`) are
  `friendID`, `team`, `miniid` and `knownPlayers` — `0x0073D9C2` reads `team`.
  Every `name` in the lobby code is a *lobby* name: both uses (`0x00741041` in
  `OnLobbyListReceived`, `0x00743743`) sit beside `gameType`, `gameSettings` and
  `GameVersion` and feed the games list. So a local read-back cannot confirm a
  rename even if the service performed one.
* Other BZRNet clients write `name` and `playerName` together as an identity
  pair, including on an already-connected socket. The service may well treat
  that pair specially in its `SetPlayerData` handler.

So OpenShim sends the pair (`[Network] LiveNicknameKeys`, default on) and logs
every attempt, and treats re-authorisation as the fallback rather than the plan.
**Confirming the result has to come from outside this process**: a second client,
or an external BZRNet client watching the lobby. There is no inbound trace to
read (see the wire trace below).

`BZRNetLobby::SetPlayerData` is vtable slot 7 at `0x0074BF60`:

```c
// __thiscall on the lobby (vftable 0x0089ADDC).
void __thiscall BZRNetLobby::SetPlayerData(void* lobby,
                                           const StableId*    lobbyId,  // lobby+0x28
                                           const std::string* key,
                                           const std::string* value);
```

The first argument is the **lobby's** identity, not a player's — an earlier
comment here named it `playerId`, which is wrong even though the value passed was
right. The disassembly is unambiguous:

* `0x0074BF71` uses it as the key into the lobby map at `0x0260B1C0`.
* `0x0074BF99` pushes the *local user's* `StableId` global, `0x0260B1C8`, to find
  that user among the lobby's members at `entry+0x48`; only then is the pair
  written into the member's own map at `+0x4C`. The player is implicit, and this
  local cache write is conditional on the lookup succeeding.
* `0x0074BFFB` resolves `lobby+0xC8` and sends **unconditionally**, whether or
  not either lookup matched. The send is inline on the calling thread, not
  posted.

That last point is what makes the wire trace below usable, and it also means a
send with no local echo is still a send.

The live lobby is reachable without hooking anything: the accessor at
`0x00764760` (`mov eax,[0x00945470]; ret`) returns the instance published on
construction and zeroed on teardown. Validate `*(void**)lobby == 0x0089ADDC`
before use — that global also carries other lobby implementations.

**`StableId` is not a string**: `{ uint32 kind; uint32 pad; uint64 id }`, kind
indexing `ISGB` (`0x0073AAF5` builds the prefixes), the same pair the ban list
prints as `S<id>`/`G<id>`. `B` is a BZRNet-issued id, which is what lobbies get
— the live value read `B1004`, and the map at `0x0260B1C0` is keyed by it, with
the local user's own `StableId` in the global right after it at `0x0260B1C8`.

Overlaying `BzrString` on that struct is what crashed the game: `kind` landed on
the `heap` pointer and the bytes at the capacity offset happened to be > 0xF, so
`BzrStringData` returned `0x00000003` as a string. **A wrong overlay is silent
until something dereferences it** — here, a `%hs` in a log line.

**Do not call `0x006C4F70` directly.** It looks like the sender and its byte
guard passes, but it is a `__thiscall` on the *websocket service* the lobby
holds at `+0xC8`; its third instruction is `mov ecx,[ebp-0xC4]` / `add ecx,
0x2E0`, so calling it without that `this` faults immediately.

#### The wire trace

`0x006C4F70` prints the outgoing JSON under `WebSocket Message Sent:` when the
log level at `0x008EDA28` is at least 3. It ships at **1**, and the 48 `.text`
references to it are all `cmp` — nothing writes it, so raising it is safe and
entirely ours to undo. Guard on `0x006C5178` (`83 3D 28 DA 8E 00 03`), which is
the instruction; the reference scan lands on the operand at `0x006C517A`.

`SendBzrNetNicknameLive` raises the level, sends, and restores it, so
`BZLogger.txt` gains exactly the two messages a rename produces rather than
every websocket send for the rest of the session. This works only because the
send at `0x0074BFFB` is inline.

**There is no receive-side logger.** Every `WebSocket Message` string in the
image is `Sent`; the inbound dispatcher is `FUN_006BF2A0`, a long
`if`/`else if` chain over the message type at `[ebp-0x28]` — `OnUserDataChanged`
compares at `0x006C08AC`, `OnLobbyChanged` at `0x006C0A7C` — and it logs
nothing. Observing what the service sends back means either detouring into that
chain or, far more cheaply, watching from a second client.

#### Re-authorising on demand

Leaving the multiplayer screens does not help: the websocket lives for the whole
process, so no second `Authorization` is ever sent and only a restart changed
the name. OpenShim can queue one itself after a nickname change
(`ForceBzrNetReauth`, `[Network] ReauthOnNicknameChange`) — but this is **off by
default**. It is the most invasive of the options: nothing shows the protocol's
state machine accepts `AUTHORIZED -> Authorization`, and the service decides
what a second authorisation does to a lobby you are sitting in. The player-data
route above is tried first.

```
0x006C6DF0  void __thiscall BZRNetClient::SendAuthorization(void*)
```

It sends nothing directly — it binds the authorisation body (`0x006C83F0`)
with two flag bytes read through `0x0260B0CC` / `0x0260B098` and posts it to the
client's io context at `+0xC18`. **That is what makes it callable from a widget
callback**: the UI thread only enqueues, and the network thread does the work,
exactly as the engine's own connected-handler does at `0x0075E06A`.

The client comes from `0x00945484`, which holds the *address* of a shared_ptr
whose first dword is the object. It has no RTTI — the class is not polymorphic,
which is also why all of these are direct calls — so it cannot be validated the
way the lobby can. Instead it is cross-checked against the live lobby's copy of
the same shared_ptr at `lobby+0xC8` (`0x007656BA` is where the lobby ctor is
handed it), and refused if they disagree or if no lobby exists. No lobby means
no multiplayer screen, which is also the only place a rename happens.

### Reading the negotiated route without walking the peer container

Peer connection state lives at `peer+0x00`: 1 = LAN connecting, 2 = LAN
connected, 3 = WAN connecting, 4 = WAN connected, 7 = RELAY connected. That
2/4/7 mapping is exactly what `FUN_0075D800` uses to choose the literal it
prints.

The peer records are only reachable through opaque STL iteration inside that
function, so OpenShim does not walk the container. Instead it redirects the
`call` at two sites into the shared BZRNet logger (`0x007D6A70`, cdecl, 272
call sites image-wide) using the existing `RedirectCallTarget`:

```
0x0075ED1D  logger(fmt, route, name, address)   fmt @ 0x0089BC78
0x0075EF99  logger(fmt, name)                   fmt @ 0x0089BCBC  (reset)
```

Redirecting one `call` rel32 rather than detouring the logger itself means each
hook receives a **fixed, known signature instead of varargs**, and no other log
line in the game is affected. The argument order was read off the push sequence
at the call site (`push eax; push eax; push ecx; push fmt`), not guessed from
Ghidra's varargs reconstruction, which shows only two arguments for a
three-`%s` format. Each format string has exactly one push site in `.text`, so
there is no ambiguity about which call is being redirected.

Both hooks record and then forward to the real logger with identical arguments,
so the game's own log is unchanged.

Two cautions carried over from the existing widgets: both callback slots
(`+0x150` / `+0x154`) must be non-null on injected **buttons** used by the
active dialog, but those offsets must never be written on a `cUI_Text` or
`cUI_TextEntry`; and `IsWidgetLiveChildOfParent` exists because widgets do not
survive a parent rebuild.

## Also worth knowing

`FnUiButtonCtor` and `FnUiLabelCtor` in `bzr_options_ui.h` declare their
trailing parameters as `int`, but the decorated names say **float**
(`??0cUI_Button@@QAE@PBDMMMMHPAVcUI_View@@MM@Z`). The existing call sites pass
`0`, which has the same bit pattern as `0.0f`, so nothing is broken today —
but anything non-zero passed there would be wrong.

## Provenance

Everything above is derived from the shipped `bzone.exe` 1.5.2.27 and the
PDB-symbolised decompile in `BZ1_Source/1.5`; nothing was transcribed by hand.
Widget coordinates and bitmap ids were cross-checked against the extracted art —
e.g. `BACK` is declared 152x34 and RT_BITMAP 258/259/260 are each 152x34; the
flag arrows are declared 18x19 and bitmaps 2049/2050/2070/2071 are each 18x19.
The off/over/on ordering of the three bitmap ids is inferred from that pairing
and has not been confirmed against the running game.
