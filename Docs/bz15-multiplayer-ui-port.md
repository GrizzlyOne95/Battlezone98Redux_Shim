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
| `OptionBox` | **no equivalent resolved** | a cycling `ButtonCtor` whose label shows the current value is the cheap substitute |
| `LISTBOX` | **no equivalent resolved** | the blocker; see below |
| `EDIT` | **no equivalent resolved** | the blocker; see below |

**This is the real gap, and it should be settled before any layout work.**
Redux plainly has list and text-entry widgets — the join-game browser and the
name field exist in its own shell — but OpenShim has not RE'd their
constructors, so today a nickname field or a session list cannot be built at
all. Finding those two constructors is worth more than everything else in this
document; without them the port is buttons and labels only, which is roughly
what the current hacked-together UI already is.

### Coordinate space

The 1.5 layout is 640x480. Redux's widgets are placed in a larger virtual
canvas — the existing OpenShim widgets sit at coordinates like
`(135, 860, 1100x58)` and `(270, 960, 338x43)`, which is consistent with
something near **1280x1024**, but that is inferred from the call sites rather
than established. **Confirm the canvas dimensions first**; a wrong assumption
scales the entire port.

Once known, the conversion is uniform:

```
redux_x = bz15_x * (canvas_w / 640)
redux_y = bz15_y * (canvas_h / 480)
```

The 1.5 shell is 4:3 and Redux is not, so a straight stretch will distort the
button art. Scale uniformly by the vertical ratio and centre horizontally, the
same choice `MirrorAspect=fit` makes in the 1.5 shim.

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

1. **RE the Redux list and edit-box constructors.** Everything else is gated on
   this. Confirm the UI canvas size in the same pass.
2. **Port the game-setup option rows.** `NetGameDlgProc`'s 12 option boxes and
   29 buttons are the highest-value cut content and need only buttons and
   labels, so they can land before step 1 completes.
3. **Port the transport screen's static furniture** — background plate,
   nav buttons, section labels — as a skeleton with the real 1.5 art.
4. **Wire the flag selector** to the existing OpenShim flag catalogue, replacing
   the single cycling `F` button with the 1.5 left/right pair and its label.
5. **Character profiles and the player-information card**, once edit boxes
   exist.

## Provenance

Everything above is derived from the shipped `bzone.exe` 1.5.2.27 and the
PDB-symbolised decompile in `BZ1_Source/1.5`; nothing was transcribed by hand.
Widget coordinates and bitmap ids were cross-checked against the extracted art —
e.g. `BACK` is declared 152x34 and RT_BITMAP 258/259/260 are each 152x34; the
flag arrows are declared 18x19 and bitmaps 2049/2050/2070/2071 are each 18x19.
The off/over/on ordering of the three bitmap ids is inferred from that pairing
and has not been confirmed against the running game.
