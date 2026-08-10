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
// 0x007CF410, 7 call sites
void* __thiscall cUI_TextEntry(void* self,
                               int   flagA,        // 1 mostly, 0 at one chatEntry
                               int   flagB,        // always 1 so far
                               int   maxLength,    // 42 or 36
                               const char* name,
                               float x, float y, float w, float h,
                               int   flags,        // 0x8020
                               void* parent);

// 0x007C9DE0, 18 call sites
void* __thiscall cUI_Selectlist(void* self,
                                const char* name,
                                float x, float y, float w, float h,
                                void (*onSelect)(),
                                void (*onDoubleClick)(),
                                int   flags,        // 0
                                void* parent,
                                uint32_t colour,    // 0xFF00FF00
                                float rowScale);    // 1.0f
```

Observed live examples: `("CreateTextEntry", 760, 945, 580x40)` and
`("chatEntry", 470, 945, 520x40)`; `("Mission_List", 290, 260, 530x450)` and
`("FriendList", 260, 160, 720x540)`. Note `cUI_TextEntry` takes flags `0x8020`
where the existing OpenShim buttons pass `0x20`.

Field offsets, from the other build's PDB and therefore **advisory — validate at
runtime before writing through them**:

```
cUI_TextEntry (extends cUI_Text)      cUI_Selectlist (extends cUI_View)
  +0x930  std::string  text            +0x14C  int   mCurrentSelectedIndex
  +0x948  uint  mBufferLength          +0x150  int   mCurrentPage
  +0x94C  void (*mEnterCallback)(...)  +0x154  float entryHeight
  +0x950  bool  mAllowEnter            +0x158  bool  mEnabled
  +0x954  cUI_View* mCursor            +0x15C  std::vector<cUI_Text*>
                                       +0x168  std::vector<valuedata>  // items
                                       +0x178  cUI_Button* mPageUp
                                       +0x17C  cUI_Button* mPageDn
```

`mBufferLength` lining up with the 42/36 third argument is what identifies that
parameter; the two leading flags are not yet pinned to `mAllowEnter` or
anything else, so treat them as opaque and copy a working call site.

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

1. **Bind the two new constructors** in `bzr_options_ui.h` / `bzr_hooks.cpp`
   alongside the existing three, and stand up one `cUI_TextEntry` and one
   `cUI_Selectlist` on the lobby to prove the ABI. Allocate with the same
   `::operator new` + `memset` pattern the button and label paths use; note
   that `cUI_TextEntry` is 2400 bytes in the reference build and
   `cUI_Selectlist` 384, both larger than the `0x1EC` currently used for
   buttons, so sizes must be re-measured rather than assumed.
2. **Port the game-setup option rows.** `NetGameDlgProc`'s 12 option boxes and
   29 buttons are the highest-value cut content, and
   `cUI_Multiplayer_SettingButton` is Redux's own equivalent.
3. **Port the transport screen's static furniture** — background plate, nav
   buttons, section labels — as a skeleton with the real 1.5 art at 2.25x.
4. **Wire the flag selector** to the existing OpenShim flag catalogue, replacing
   the single cycling `F` button with the 1.5 left/right pair and its label.
5. **Character profiles and the player-information card**, on `cUI_Selectlist`
   and `cUI_TextEntry`.

Two cautions carried over from the existing widgets: both callback slots
(`+0x150` / `+0x154`) must be non-null on any active dialog child or the lobby
crashes walking its children, and `IsWidgetLiveChildOfParent` exists because
widgets do not survive a parent rebuild.

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
