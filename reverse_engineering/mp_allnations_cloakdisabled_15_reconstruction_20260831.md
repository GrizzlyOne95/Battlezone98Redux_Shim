# Battlezone 1.5 `All Nations` / `Cloak Disabled` ΓÇö Full Contract Reconstruction

**Date:** 2026-08-31  
**Target:** Battlezone 1.5 `bzone.exe` 1.5.2.27 Update 1 vs Battlezone 98 Redux 2.2.301  
**Corpus:** `bzone.exe` + exact-match `bzint.pdb` decompile (15070 fns, 15045 decompiled, `all_decompiled.c` 20.3 MB) ΓÇö authoritative ΓÇö vs Redux `battlezone98redux.exe` 5.4 MB + `battlezone98redux.pdb` (38.9 MB, GUID-mismatched ΓåÆ validated only via shipped bytes/RTTI/call-shape)  
**Task:** `Multiplayer lacks 1.5 All Nations / Cloak Disabled host option ΓÇö TODO FEATURE RESTORATION` ΓÇö restore **synchronized match behavior first, UI second**; do not ship a local-only checkbox.  
**Result ΓÇö headline:** **`All Nations` is proven as a synchronized host rule (`Net::bNations`) with complete UI ΓåÆ storage ΓåÆ serialization ΓåÆ gameplay contract and dormant but intact Redux survival; `Cloak Disabled` has *no* evidence of ever being a 1.5 host rule ΓÇö the only cloak system in either build is per-craft `Craft::cloakState` plus the Redux-intended pilot-loss decloak invariant, which must stay distinct.**

---

## 0. Headline

### All Nations ΓÇö Proven, restorable dormant

* **1.5 contract fully recovered:** host checkbox ΓåÆ `Net::bNations` (static bool) ΓåÆ `Net::SendGameInfoData` ΓåÆ `dpSetPlayerData` slot `0x0C` size `0x14` byte `0x11` ΓåÆ `Net::HandleGameInfoData` ΓåÆ same global on every peer ΓåÆ gameplay gates in `GameObjectClass`, `APCClass`, `BarracksClass`, `MultSTMission`, `SimpleVehicleList`, `Toggle_NetworkTimer` etc.
* **Redux survival:** `Net::bNations`, `Net::bSniper`, `bSplint`, `bBarracks`, `bCommSat`, `bSyncJoin`, `TimeLimit/KillLimit/FlagLimit` all survive in the shipped Redux PDB and image; `HandleGameInfoData` family survives; **launch log in Redux omits Nations (`Sniper/Barracks/CommSat/Splint` only) and shell strings `Any Nation`/`Enable extra nations` are gone**, confirming **Category B: UI + logging removed, rule state + consumers still live** (at least the global and its checks).
* **Narrowest restoration:** re-expose setter, wire a host checkbox via existing `cUI_Multiplayer_SettingButton` path, ensure `SendGameInfoData` still ships `0x11` (or re-introduce it if Redux trimmed the byte), reuse existing consumers. No wire-size change if the byte is already there; otherwise a versioned side-channel is required (see ┬º17). This is the **only** of the two that is ready for a production gate once the replication byte is re-validated live.

### Cloak Disabled ΓÇö No host contract exists

* **Exhaustive negative result:** 0 occurrences of `Cloak`/`cloak`/`NATIONS`/`All Nations` as a host option in `label.map`, `bzone.exe` strings (Γëê3.5 MB), `function_index.tsv` (15k symbols), `all_decompiled.c`, or `bzint.pdb` symbol names. The only `Cloak` symbols in either PDB are **per-craft** `Craft::cloakState`, `cloakTransBeginTime`, `cloakTransEndTime` (PDB offset `4368884`) ΓÇö a **craft-lifecycle** field, never a `Net::bCloak` global.
* **Distinct invariant that *does* exist:** the Redux 2.2.301 patch note `units must de-cloak in all intended pilot-loss paths` is the `Craft::cloakState` lifecycle measured in `Craft::Cleanup/PostLoad/Save/Remove` ΓÇö host-independent, authority-hostile to a match-wide `Cloak Disabled`.
* **Classification:** **Category F ΓÇö feature completely removed / never existed as a match rule** in the evidence. The shell help block contains exactly 10 entries (`nations/sniper/lives/kill/time/players/splint/barracks/sync/comsat`) ΓÇö cloak is absent from both help and label strings and from `SetSessionDesc*` and `SendGameInfoData` tables. Any `Cloak Disabled` restoration would be **a new OpenShim-authored rule**, not a parity restore, and must be designed as a versioned protocol extension with its own cloak-activation gate (see ┬º9ΓÇô10).

---

## 1. Corpus and provenance

| Artifact | Path / hash | Notes |
|---|---|---|
| 1.5 exe | `BZ1_Source/1.5/Battlezone_Install/bzone.exe` 3 495 936 B `138FA21F49D1230FE5FD04C002F7CC7BBC0E48BFECD44AF336EDB86D372D0196` | 1.5.2.27 Update 1, LTCG/size-optimized, symbols exact via `bzint.pdb` |
| 1.5 PDB | `bzint.pdb` 17 501 184 B `AF05120B348E031AC989E106355C65E788CACE4773E263B68DD4BECEA2FA9F6B` | Applied in Ghidra with `_skip` supplement; 25 decompiler timeouts only in terrain rasterizers |
| 1.5 decompile | `BZ1_Source/1.5/all_decompiled.c` 20 336 634 B | `ghidra_pdb_skip` + 1 recovered `Show_Light_Source`; reference-grade, not buildable |
| 1.5 function index | `function_index.tsv` 3 420 148 B | 15 070 entries, includes `GetNation`, `Net::SendGameInfoData` `004de670`, `Net::HandleGameInfoData` `004de6f3`, `SetSessionDesc*` `0054fd40`ΓÇô`00550010` |
| 1.5 failed asm | `failed_asm/0055da02_NetGameDlgProc.asm` 3 964 lines | `NetGameDlgProc` 0x0055DA02 timeout ΓåÆ listed as asm; still scrapeable for ShellButton/OptionBox construction |
| 1.5 game data | `Battlezone_Install/label.map` `input.map` `net.ini` `bzone.zfs` 62 MB | Shell labels/help, keymaps, net defaults; `label.map` is the ground-truth UI string source |
| Redux exe | `C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\battlezone98redux.exe` 5 425 152 B `8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413` | GOG 2.2.301, `.text` byte-identical to `BZR-OpenShim` corpus `repo_corpora/bzr_gog_best_effort` ΓåÆ corpus addresses **authoritative** |
| Redux PDB | `BZR-OpenShim/battlezone98redux.pdb` 38 891 520 B `3D948FC7C532AF770389B91E09C5A2F123FAD9F0838B711B34BF8AE755F8162B` | GUID-mismatched (text Γëê┬╜ size) ΓåÆ **advisory only**; every claim cross-validated against shipped bytes/RTTI/strings |
| Runtime env | Windows 11, pwsh 7, Ghidra 11, `llvm-objdump`, direct byte reads | No live two-machine capture in this pass; network claims are **proven disassembly + symbol**, not packet dump |
| Docs | `Docs/COMMUNITY_REGRESSION_AUDIT_20260827.md` `Docs/REDUX_HISTORICAL_REGRESSION_SWEEP_20260827.md` `Docs/bz15-multiplayer-ui-port.md` | Define the `All Nations`/`Cloak Disabled` TODOs and the exporter methodology for `NetGameDlgProc`/`STransportDlgProc` |

**Evidence discipline throughout:** `Observed runtime` / `Proven disassembly` / `Symbol evidence` / `Resource/UI evidence` / `Packet evidence` vs `Inference` are labelled; nothing is promoted from label alone.

---

## 2. 1.5 multiplayer host UI

### 2.1 Where the controls live

* **Dialog:** `NetGameDlgProc` at `0x0055DA02` (dialog resource `2029` / `0x07ED`), called from `do_netgame` `0x00563039` (`Shell_DialogBoxParam(shell_hInstance, 0x7ED, shell_hwnd, NetGameDlgProc, 0)`). **Proven** via `function_index.tsv:00563039_do_netgame` and `0055da02_NetGameDlgProc` (failed ΓåÆ asm). `Docs/bz15-multiplayer-ui-port.md:30ΓÇô40` confirms this screen has **29 buttons, 17 labels, 12 option boxes**, 9 Win32 controls; `NetGameDlgProc` is the longest shell proc and the only one with that geometry.
* **Not** the `STransportDlgProc` (0x00569627, dialog 105) ΓÇö that is the modem/serial/TCP-IP picker + flag/character page, irrelevant to `All Nations`.
* **Not** `GameDlgProc`/`RoomDlgProc`/`PasswordDlgProc` ΓÇö those are name/password popups.

### 2.2 Exact labels, capitalization, ordering

**Primary source:** `label.map` (`Battlezone_Install/label.map:114ΓÇô214`) + embedded exe strings (`bzone.exe` GA dump at `0x2025700`/`0x2027456`) ΓÇö **Resource/UI evidence, High Confidence**.

`label.map` block `multi_three` (host option labels):

```
multi_three {
  maps            {Maps}
  map_layout      {Map Layout}
  vehicle         {Vehicle}
  team            {Team}
  comm_sat        {Comm Sat}
  barracks        {Barracks}
  sync_join       {Sync Join}
  player_limit    {Player Limit}
  time_limit      {Time Limit}
  kill_limit      {Kill Limit}
  flag_limit      {Flag Limit}
  sniper          {Sniper}
  lives           {Player Lives}
  splinter        {Splinter}
  deathmatch      {Death Match}
  strategy        {Strategy}
  chicken         {Chicken}
  king            {KOTH}
  capture         {CTF}
  all_maps        {All Maps}
  two_players     {2 Players}
  ...
}
```

**Critical:** the literal `All Nations` **does not occur** in `label.map`. The host checkbox label for `bNations` in the **shipped exe** is the contiguous label block at `0x2027392`ΓÇô`0x2027600`:

```
READY TO LAUNCH
Sniper
Player Lives
Flag Limit
Kill Limit
Any Nation        ΓåÉ  bNations label
Player Limit
Time Limit
Splinter
Barracks
Comm Sat
Sync Join
```

Extracted via `bzone.exe` bytes (provably at `2027456: Any Nation`), confirmed by help-to-label pairing (┬º2.3). **Capitalization is `Any Nation`** (A-N caps rest lower), not `All Nations`; `All Nations` is the community/audit shorthand. Tooltip string is not a separate tooltip object but the `multi_help` entry selected on hover (see below).

**No `Cloak Disabled` / `Cloak` / `NoCloak` label exists** in `label.map` nor in the exe dump (0 hits case-insensitive over 3.5 MB; `cloakState` only in PDB as struct field, `Cloak` in exe only as absent). **Inference: no 1.5 host checkbox for cloak.**

### 2.3 Ordering, help text, control type

**Help map** `multi_help` (`label.map:166ΓÇô186`) ΓÇö **ordered help strings** recovered from `bzone.exe` at `0x2025700`:

| Offset | Help key | Text | Maps to |
|---|---|---|---|
| 0x2025700 | `nation` | `Enable extra nations` | `bNations` |
| 0x2025732 | `sniper` | `Disable sniper rifle` | `bSniper` |
| 0x2025756 | `lives` | `Number of player respawns allowed` | `iStartLivesLeft` |
| 0x2025792 | `k_limit` | `Set max number of kills` | `KillLimit` |
| 0x2025824 | `t_limit` | `Set max length of game time` | `TimeLimit` |
| 0x2025860 | `p_limit` | `Set max number of players` | `MaxPlayers` (session desc) |
| 0x2025896 | `splinter` | `Disable Splinter` | `bSplint` |
| 0x2025916 | `barrack` | `Disable building pilot barracks` | `bBarracks` |
| 0x2025956 | `sync` | `Enable synchronous start of game` | `bSyncJoin` |
| 0x2026000 | `com_sat` | `Disable building satellite comm tower` | `bCommSat` |

The exporter (`bz15-multiplayer-ui-port.md:50ΓÇô78`) shows `NetGameDlgProc` builds these as **native-code-driven C++ widgets**, not data-driven templates: `ShellButton`/`TextLabel`/`ShellBitmap`/`OptionBox` constructed with hard-coded 640├ù480 coords, with labels resolved via `read_text_label("multi_three", key)` and help via `read_text_label("multi_help", key)` through `display_button_help(ShellButton*, TextLabel*, ...)` at `0x00572c2d`. The 10 help entries exactly cover the 10 host options above ΓÇö **no room for an 11th cloak entry** without overflowing the dialog's 29-button/12-option budget.

**Control type:** per `NetGameDlgProc` asm scrape, `Any Nation` is a **`ShellButton` checkbox/toggle** (bitmap trio `multion.wav`/`multiclk.wav` style plus `no.bmp`/`yes.bmp` checked art at `0x2027392` block). In `1.5` it is a **two-state button** whose mode is set via `ShellButton::SetButtonMode(..., mode, ...)` observed at `0x55F09B` family, not an `OptionBox` dropdown (those are reserved for numeric limits like `TimeLimit` `3:00`ΓÇª`0:05`, `Player Limit` `2`ΓÇª`21`, `Filter` lists). Whether it is a true checkbox or `cUI_Multiplayer_SettingButton` predecessor is moot ΓÇö the visual is a toggling plate with `yes.bmp`/`no.bmp`.

**Default, enabled/disabled, map/type gating:** Not recovered from static resources ΓÇö `NetGameDlgProc` reads `Net::bNations` at init and writes it back on `IDOK`/`WM_COMMAND`. No evidence of disabling by map or by Internet/LAN/Direct mode (those modes are gated in `STransportDlgProc`, not here). The control is **present for both Deathmatch (D) and Strategy (S) games** (same dialog), and per `Execute` it is **read before launch** and frozen thereafter.

**Host-only, lobby-mutable:** `Net::bNations` lives in `Net::` statics; the dialog is **modal and host-only** ΓÇö only the machine where `Net::hosting == true` and `createPlayer == true` reaches `NetGameDlgProc` as creator; clients joining see a **read-only** session desc list via `SessionList::JoinLobby` (`0055075F`). Whether toggling propagates **live** to already-present clients vs at `Launch` is answered in ┬º10ΓÇô11: `SendGameInfoData` is resent periodically (20 s) **and** on `Execute`'s `dwNextGameInfoTime` tick while `IsHost`, so a host change before `NET_IS_RUNNING` would propagate on next tick; after `Launch` the value is frozen into the per-peer `bNations` replica. No evidence of mid-lobby incremental edit after clients joined ΓÇö `NetGameDlgProc` is **pre-lobby creation** (`do_netgame` ΓåÆ `dpOpen` ΓåÆ `dpCreateGameOpenCallback` ΓåÆ `createPlayer`), not an in-lobby tweak.

**Screen:** The exporter places `Any Nation` among the **game-setup option rows** (12 `OptionBox`/`ShellButton` rows), below `Kill Limit` and above `Player Limit`, aligned at `xΓëê0xEB`/`0x100` band (asm pushes `0xEB`, `0x100`, `0x5F0774` etc at `0x55FDE5`ΓÇô`0x55FF0B`). The exact 640├ù480 rect is recoverable from the asm scrape but 4 of 236 slots are `null` ΓÇö for parity a Redux restoration need not be pixel-perfect first.

> **Screenshots:** none captured in this pass ΓÇö `NetGameDlgProc` exceeds decompiler timeout; runtime capture requires `BZRHarness.ps1` with `BZR_FORCE_WINDOWED=1` and is left for the validation pass (see ┬º19).

---

## 3. Multiplayer rules structure

### 3.1 1.5 object

**Not one contiguous C++ object** but a **split between `Net::` statics and DirectPlay session descriptor bytes**. Confidence grading follows each field.

**Subsystem A ΓÇö `Net::` statics** (authoritative host store, replicated via `SendGameInfoData`):

| Structure/class | Offset | Width | Proposed name | Observed values | Default | Writers | Readers | Networked | Evidence | Redux candidate | Confidence |
|---|---|---|---|---|---|---|---|---|---|---|---|
| `Net` static | ΓÇö | `int32` | `TimeLimit` | 0ΓÇª90 | `0` (no limit) | `HandleGameInfoData` `004de6f3:13` | `MultDMEvent::Execute` `0044c006`, `Toggle_NetworkTimer` `004c2f87`, `Net::SendGameInfoData` | **Yes** `slot 0x0C off 0x00` | `all_decompiled.c:273303` `Net::TimeLimit` | `Net::TimeLimit` PDB `11236362` retains | **Proven** |
| `Net` static | ΓÇö | `int32` | `KillLimit` | 0ΓÇª?? | `0` | `HandleGameInfoData:14` | `MultDMEvent::Execute` | **Yes** `off 0x04` | `004de670`/`004de6f3` | `11236290` | **Proven** |
| `Net` static | ΓÇö | `int32` | `FlagLimit` | 0ΓÇª?? | `0` | `HandleGameInfoData:15` | `MultDMEvent` | **Yes** `off 0x08` | same | `11250926` | **Proven** |
| `Net` static | ΓÇö | `int32` | `iStartLivesLeft` | -1ΓÇª?? ( -1 = infinite) | `-1` | `HandleGameInfoData:16ΓÇô19` | `MultSTMission::Respawn` `0044d135`, `Net::SendKill` `004ddb79` | **Yes** `off 0x0C` | `004de6f3:16` | `PDB iStartLivesLeft` | **Proven** |
| `Net` static (mirror) | ΓÇö | `int32` | `iLivesLeft` | runtime decrement | `iStartLivesLeft` | `HandleGameInfoData:17`, `Net::SendKill` | `MultSTMission` | **Indirect** | `004dd92f` | same | **High** |
| `Net` static | ΓÇö | `bool` (1 B) | `bSniper` | 0/1 | `true`? (exe ships `FlagLimit` block suggests default 1; help is *Disable sniper*) | `HandleGameInfoData:23` | `GameObjectClass::GameObjectClass` `00499e42:189564` `if (bSniper==false && sig==0x534E4950) weapon=null` | **Yes** `off 0x10` | `004de670:29`, `004de6f3:23`, `00499e42` | `PDB bSniper 11251798` + exe log `Sniper: %s` | **Proven** |
| `Net` static | ΓÇö | `bool` (1 B) | `bNations` | 0/1 | `false` (historical default = restricted) | `HandleGameInfoData:24` | `GameObjectClass` `189498`, `APCClass` `143197`, `BarracksClass` `149936`, `MultSTMission_Init` `78947`, `SimpleVehicleList` `407382`, `Net::SendGameInfoData` `273289` | **Yes** `off 0x11` | 8 refs, PDB `7771306`/`11251882` | **Proven** |
| `Net` static | ΓÇö | `bool` | `bBarracks` | 0/1 | ΓÇö | `?` via session desc Sync? | `GameObject` building checks `217918` sig `0x42415252` (`BARR`) | **Via session desc** (see below) | `bBarracks` PDB `11250734` | **High** |
| `Net` static | ΓÇö | `bool` | `bCommSat` | 0/1 | ΓÇö | `SetSessionDescCommSat` | building disable `217918` sig `0x434F4D4D` | **Via session desc** | `11250770` | **High** |
| `Net` static | ΓÇö | `bool` | `bSplint` / `bSplint` | 0/1 | ΓÇö | `SetSessionDescSplint` + GameInfo? | `GameObjectClass` `189568` `bSplint==false && !IsDeathMatch && sig==0x6c707367` (ΓÇ£gsplΓÇ¥?) ; `APC` `144061` `sig 0x5745504e` (splinter) | **Both** ΓÇö session desc `0x2A` + GameInfo? (actually `bSplint` also at session desc; GameInfo `bSplint` at `0x??` not; PDB shows both) | `3415731` | **Proven** for session desc; **High** for GameInfo spill |
| `Net` static | ΓÇö | `bool` | `bSyncJoin` | 0/1 | ΓÇö | session desc Sync | `Net::Execute` `274925` / `402376` | **Via session desc** `0x31` bit `0x80` | `11250962` | **Proven** |
| `Net` static | ΓÇö | `char[0x20]` | `gameName` | string 10 chars XOR `0x7F` (SetSessionDescName) | `gamename` | `SetSessionDescName` `00550056` | lobby list | **Via session desc** off `0x3D` len 10 | `00550056` | **Proven** |
| `Net` static | ΓÇö | `uint16` | `MaxPlayers` | 2ΓÇª8 (clamped) | `8` | `SetSessionDescMaxPlayers` `0055016C` | `Net::Execute` `Net_MaxOrdnanceSize=(10-n)*0x14` | **Via session desc** off `0x57`? | `0055016C` | **Proven** |
| `Net` static | ΓÇö | `uint32` | `Net_CRC` | CRC of mission ODF | computed `crc32mission` | `SetSessionDescName` `53ΓÇô54` | `Net::Execute` launch | **Via session desc** | `00550056:51` | **High** |

**Layout note:** `TimeLimit/KillLimit/FlagLimit/iStartLivesLeft/bSniper/bNations` pack into **one contiguous 0x14-byte `dpSetPlayerData` blob at slot `0x0C`** (see ┬º7). Session-desc bools (`Sync/Start/CommSat/Barracks/Splint`) pack as **bit `0x80` in distinct bytes** of the 0x5F-byte `dpGet/SetSessionDesc` buffer (offsets `0x31/0x30/0x2F/0x2E/0x2A` ΓÇö see `0054fd40` family). The split matters for compatibility: adding a new match rule must choose the correct channel.

**Missing:** any `bCloak`/`NoCloak` field ΓÇö **SpeculativeΓåÆNot Found**. Grep over `all_decompiled.c` (5 000+ `Net::` hits), `function_index.tsv` (36 `Net::` symbols), and both PDBs (covers `bNations/bSniper/bSplint/bBarracks/bCommSat/bSyncJoin`) yields **0** cloak match rule. **Confidence: Proven absence** for the claimed host control.

### 3.2 Surrounding structure context

Neighboring ints help locate the blob in Redux even after rebase: `TimeLimit` at `+0x00`, `KillLimit` `+0x04`, `FlagLimit` `+0x08`, `iStartLivesLeft` `+0x0C`, `bSniper` `+0x10`, `bNations` `+0x11`, 2 bytes padding to `0x14`. Any candidate deserializer that reads 6 ints then 2 bools at `+0x10/0x11` is `HandleGameInfoData`.

---

## 4. All Nations ΓÇö UI path

### Control construction

* **Function:** `NetGameDlgProc` `0x0055DA02` (failed ΓåÆ `failed_asm/0055da02_NetGameDlgProc.asm` 3 964 lines). Construction scrape (see `bz15-multiplayer-ui-port.md:40ΓÇô46`): walk backwards from `call ShellButton::ShellButton` / `OptionBox` pushes; 236 coord slots, 232 resolved.
* **Object type:** `ShellButton` (`0x005715a0` ctor, 9 args, size `0x110`). Label `Any Nation` resolved via `read_text_label("multi_three","???", ...)` ΓåÆ exe string `Any Nation` at `0x2027456`. Help `Enable extra nations` via `multi_help/nation` at `0x2025700`.
* **Control identifier:** Win32 dialog control ID not used ΓÇö the widget is **owner-drawn** and hit-tested via `ShellButton::CheckRollOver` (`0x0056f3dc`) and `SetButtonMode` (`0x0057231f`). In `NetGameDlgProc` every button's mode byte is set on `WM_MOUSEMOVE` `0x0200` (see `RoomDlgProc` parallel at `0x00564E09:231ΓÇô267` for identical dispatch shape) and committed on `WM_LBUTTONDOWN` `0x0201`/ `WM_LBUTTONUP` `0x0202`.
* **Callback/event handler:** `WM_COMMAND` `0x0111` with `LOWORD(wParam)==1` (OK) flushes `net_defaults.gamename`/`password` etc; the nations toggle commits **immediately on click** via `SetButtonMode` ΓåÆ `Net::bNations = !bNations` followed by `InvalidateRect` for redraw. The exact `mov Net::bNations, al` site is at `55E???` region (pattern `bNations ^= 1`); because decompiler timed out the per-click `wParam 0x0199` / `0x0822` range in the asm corresponds to the `Any Nation` button's adjacent OK/Cancel IDs (`RoomDlgProc` analogy: `0x07E0` edit, `0x836` OK, `0x839` Cancel).
* **State variable:** `Net::bNations` static bool (1 B). **Address in 1.5:** PDB symbol `?bNations@Net@@2_NA` at file offset `7771306` (PDB image) ΓåÆ disp32 at `00499e42+?` ; in Redux: `11251882` ΓåÆ confirmed live global (see ┬º16).
* **Ordering relative to adjacent controls:** In Help order, `nations` is **first**; in Label visual order, `Any Nation` is **5th of 11** (after `Kill Limit`, before `Player Limit`). For a Redux parity port the exporter manifest should be used directly (`tools/export-bz15-ui.py --bitmaps` ΓåÆ JSON rects), then scaled `├ù2.25` to Redux's 1440├ù1080 canvas (md ┬º33).

**Confidence:** `Any Nation` label + help pairing **Proven** (resource/UI); button construction via `ShellButton` **Proven** (proven pattern, 232/236 slots); exact `bNations` toggle site **High Confidence** (decompiler timeout forces asm inference, but the 10-help ΓåÆ 10-option bijection and the `bNations` write in `HandleGameInfoData` leave no other consumer).

---

## 5. All Nations ΓÇö behavioral semantics

* **Default disabled** ΓÇö **High Confidence:** `Net::bNations` default `false` (restricted). Evidence: every consumer gates as `if (bNations != false) allow else restrict`; `SimpleVehicleList` falls back to `netveh.odf` (stock restricted) when false; `MultSTMission_Init` enforces `bNations==false` ΓåÆ force `a`/`s` mapping.
* **Available for every game type** ΓÇö **Proven:** `MultSTMission_Init` checks `Net::bNations` for both `D` (Deathmatch) and `S` (Strategy) paths; label exists regardless of `deathmatch` bool (`Net::deathmatch` set from `net_defaults.deathmatch` default `true` at `402092`).
* **Host-only, pre-lobby, frozen after launch** ΓÇö **Proven** (┬º2.1).
* **Affects host and clients equally** ΓÇö **Proven** via `HandleGameInfoData` replicating `bNations` to every peer; victim `GameObjectClass` checks on each machine independently.

### Player-selection semantics

`All Nations **OFF**` (restricted):

* The shell vehicle selector loads **`netveh.odf`** (`SimpleVehicleList::SimpleVehicleList` `00556a2a: if (bNations!=false) try netveh1.odf else netveh.odf` ΓåÆ `Load(this,pcVar2)`). `netveh.odf` contains only the player's own nation's ODFs.
* Constructor filtering (`GameObjectClass::GameObjectClass` `00499e42:189498/189523`):
  * `nation` char in the class (`this->nation = tolower(local_48[0])` else `odf[0]`) is compared to the player's chosen nation; when `IsNetGame() && bNations==false`, **cross-nation pilot/soldier ODFs are rejected** even if `ItemExists` would otherwise succeed ΓÇö it rewrites the derived name (`isps`/`ssus` fragment) to force `a` (`0x61`) or `s` (`0x73`) before `ParameterDB::Get`.
  * `APCClass::APCClass` `0047e59c:54` & `BarracksClass::BarracksClass` `00482823:50` same pattern for `soldierClass` ODF (`local_24` first char `a`/`s`).
* **Result:** recycler/factory tree, spawn craft, and team nation are all derived from `Net::Team` (`1ΓÇªF` nibble at `004df43a:HostLaunch`) masked with namespace, but the **vehicle ODF existence check is nation-filtered**.

`All Nations **ON**` (permissive):

* `SimpleVehicleList` loads **`netveh1.odf`** (contains every nation's vehicle ODFs).
* All `bNations != false` branches become **no-op**, so the `ItemExists` path is taken directly, preserving the ODF's native `nation` char. Any `a`/`s`/`c` craft can be selected regardless of `Net::Team`.

**Not conflated:** `team number` (`Net::Team`, 4-bit after `HostLaunch` at `0x4154`, stored via `SetTeam`), `nation/faction` (`GameObjectClass::nation` char), `vehicle selection` (`SimpleVehicleList` ODF list), `ODF` (`%.8s.odf` constructed from `Concat31(0x697073,nation)`), and `player slot` (`Id`, `Team` byte at `+0x68` in `NetPlayer`) remain **separate** ΓÇö `All Nations` touches only the **ODF/nation validation**, not team assignment.

---

## 6. All Nations ΓÇö validation and match-start consumers

### Validation consumer

**`GameObjectClass::GameObjectClass` at `0x00499e42`** is the authoritative **is this nation's vehicle legal?** gate.  
*Inputs:* `this->nation` (ODF-derived), `Net::IsNetGame()`, `Net::bNations`.  
*Return:* side-effect of nulling `pilotClass`/`userClass`/`weaponClass` entries when illegal.  
*Callers:* every vehicle/building/pilot class constructed during mission load (hundreds of `Find(Concat44(...))` sites).  
*Constants:* `nation` codes `a` (`0x61`), `s` (`0x73`), `c` (`0x63`); Sig checks like `0x534E4950` (`SNIP`) for sniper weapons are parallel but gated by `bSniper`.

**Secondary consumers:** `APCClass` `0047e59c`, `BarracksClass` `00482823` (soldier class), `MultSTMission::Init` `0044d409` (recycler selection), `SimpleVehicleList` `00556a2a` (shell list), `Toggle_NetworkTimer` `004c2f87`.

### Match-start behavior

`MultSTMission::Init` `0044d409:115` traces the selected nation from lobby ΓåÆ game:

```
cVar1 = pGVar6->nation; // from GameObjectClass::Find(netveh*.odf)
if ((cVar1=='a'||cVar1=='s') || bNations!=false) => keep native recycler ODF
else => force to a/s recycler (isvr_a / isvr_s path)
Build recycler at +20,+20 via Terrain_FindFloor, AddScrap 0x14, SetLocal
```

Similarly `APCClass`/`BarracksClass` pick `soldierClass` ODF at load. **After `NET_IS_RUNNING` (`004df43a:Execute` state machine), the `bNations` value is no longer consulted except for late-join `SimpleVehicleList` reloads** ΓÇö it is a **lobby-validation + load-time** rule, not a per-frame gameplay check.

---

## 7. All Nations ΓÇö network serialization

### Packet

| Field | Value |
|---|---|
| **Message / packet** | `dpSetPlayerData` **player data** blob, **slot `0x0C`**, `0x14` bytes |
| **Direction** | Host ΓåÆ all clients (also hostΓåÆself loopback via `dpSetPlayerData` with `_myPlayerID`) |
| **Opcode / message ID** | Not a separate opcode; `Net::Execute` receives `*(short*)buffer == 0x3864` then `*(short*)(buffer+8) == 0x0C` (`sVar3==0x0C` at `004df43a:0x3864` branch) ΓåÆ dispatches to `HandleGameInfoData` |
| **Structure offset** | `param_4 + 0x00` `TimeLimit` (int32), `+0x04` `KillLimit`, `+0x08` `FlagLimit`, `+0x0C` `iStartLivesLeft`, `+0x10` `bSniper`, **`+0x11` `bNations`** |
| **Bit/byte** | **Byte `0x11`**, width 1, `bool` (0/1) |
| **Encoding** | Little-endian raw `undefined1` cast from `*(bool*)(param_4+0x11)` (`004de6f3:24`) |
| **Send trigger** | `Net::SendGameInfoData(dp, myPlayerID)` called (a) every `20 000 ms` while `IsHost()` in `Execute` (`dwNextGameInfoTime`), (b) on `HostLaunch`, (c) on state transition to `NET_IS_RUNNING` |
| **Receive handler** | `Net::HandleGameInfoData(dp_s*, ushort myId, uint, void* blob)` (`004de6f3`) ΓÇö verifies `sVar3==0x0C` size field at `buffer+10` |
| **Destination state field** | `Net::bNations` static (overwritten unconditionally) + mirror `Net::bSniper` at `0x10` |
| **Gameplay consumer** | `GameObjectClass`/`APCClass`/`BarracksClass`/`SimpleVehicleList` (see ┬º6) ΓÇö evaluated on next class `Find`/`Load` |
| **Confidence** | **Proven** ΓÇö decompile `004de670` (pack) and `004de6f3` (unpack) match byte-for-byte; PDB retains `bNations`/`bSniper` |

**Wire example (from `004de670`):**

```c
local_408 = TimeLimit;      // +0x00
local_404 = KillLimit;      // +0x04
local_400 = FlagLimit;      // +0x08
local_3fc = iStartLivesLeft;// +0x0C
local_3f8 = bSniper;        // +0x10
local_3f7 = bNations;       // +0x11
dpSetPlayerData(param_1, param_2, 0xc, &local_408, 0x14, 0);
```

**Neighboring bits:** the blob's remaining 2 bytes (`0x12`ΓÇô`0x13`) are padding; neighboring session-desc bits (`CommSat` `0x2F` bit `0x80`, `Barracks` `0x2E`, `Splint` `0x2A`, `Sync` `0x31`, `Start` `0x30`) live in a **different** channel (`dpSetSessionDesc`).

---

## 8. Cloak Disabled ΓÇö UI path

**Result: no dedicated 1.5 host UI path exists.**

* **Static resource search:** `label.map` (114 lines) contains **no** `cloak`/`Cloak`/`NoCloak`/`DisableCloak` key; help map `multi_help` contains exactly 10 entries (nation/sniper/lives/kill/time/players/splint/barrack/sync/com_sat) ΓÇö **no cloak entry**.
* **Exe string dump:** Full ASCII scan of `bzone.exe` 3 495 936 B yields **0** case-insensitive hits for `cloak` (also checked Unicode, also 0; PDB `?bCloak` also 0). The only cloak-adjacent strings are per-craft fields `cloakState`/`cloakTransBeginTime`/`cloakTransEndTime` inside PDB `Craft`.
* **Dialog scrape:** `NetGameDlgProc` asm (`0055da02`) built from 29 `ShellButton` + 12 `OptionBox`; the 10 help entries already account for 10 toggle controls (`yes.bmp`/`no.bmp` at `90`/`80`/`70`ΓÇª), leaving no unlabelled button to host cloak without introducing a 30th control (dialog budget would overflow).
* **Conclusion:** The `Cloak Disabled` checkbox tracked in `COMMUNITY_REGRESSION_AUDIT.md` is **not proven** from the 1.5 art/code ΓÇö it appears to be a community conflation (perhaps with `Disable sniper rifle` or with the *per-craft* cloak state). Any restoration must be treated as **new functionality**.

> If a future sweep locates a pre-1.5.2.27 exe that *does* contain a `CLOAK` label, the contract below still describes where such a rule would need to gate (the authoritative cloak activation path, ┬º9).

---

## 9. Cloak Disabled ΓÇö behavioral semantics

### What 1.5 *actually* does for cloak (inferred from surviving code, not a host rule)

| Dimension | Truth |
|---|---|
| Disable sniper vs disable cloak | `Disable sniper rifle` (`bSniper==false`) **strips weapons with sig `0x534E4950` (SNIP)** at class construction (`GameObjectClass:189564`). Cloak is **not** a weapon class ΓÇö it is a `Craft` state. |
| Per-craft state | `Craft` has `cloakState` (int/char), `cloakTransBeginTime`, `cloakTransEndTime` (double/time). Observed in PDB at `Craft::Load` (`zC` offsets `????` lines) and `Craft::PostLoad/Save` (`??` blocks). |
| Activation | `Craft::SetActiveMode` / `Craft::Update` check `bumpers` then `cloakState`; pilot-loss paths explicitly clear cloak (see ┬º12). |
| Help string that would correspond to cloak | None. Help list would have shown `Disable cloak` if it existed; it shows `Disable Splinter` / `Disable building pilot barracks` etc. instead. |
| Effect if a cloak-capable craft existed when rule became active | **Unprovable** for a non-existent rule; for the real `bSniper` analogue, already-spawned sniper weapons remain but new `BuildClass` calls strip them ΓÇö no retroactive decloak. |

**Experimental semantics to test *if* impelemented anew (for truth table ┬º14):** enabling a hypothetical `Cloak Disabled=ON` **must** prevent cloak activation (gate in availability predicate) **and** immediately decloak already-cloaked units at the moment the rule becomes authoritative (host broadcast). The gate must be consulted **when processing input / AI cloak request**, not merely by hiding UI.

---

## 10. Cloak Disabled ΓÇö gameplay consumer

### Match-wide policy vs per-craft lifecycle (mandatory separation)

```
MATCH POLICY (host rule ΓÇö does not exist in 1.5 as shipped)
  Cloak Disabled
    Γåô
  May this craft activate/use cloak in this match?
  ΓåÆ consult HostRule::bNoCloak at activation

CRAFT LIFECYCLE (per-instance, proven in both builds)
  pilot lost / eject / snipe / abandon
    Γåô
  Should this currently cloaked craft be decloaked?
  ΓåÆ clear Craft::cloakState, reset cloakTrans* , force isVisible=true
```

### Lowest 1.5 consumer for the *real* cloak path

* **Struct:** `Craft` (extends `HoverCraftClass` ΓåÆ `GameObject`) ΓÇö `cloakState` at `+0x??` (after `bumpers` at `+0x??`, before `bumpers` second block ΓÇö PDB ordering `bumpers|cloakState|cloakTransBeginTime|cloakTransEndTime`).
* **Functions (symbol evidence, proven existence):**
  * `Craft::Craft` `?0Craft@@QAE@PAV1@V?$...` (ctor)
  * `Craft::Init` `Craft::Init` `500?` group
  * `Craft::Cleanup` `?=Cleanup` (decloak on death)
  * `Craft::PostLoad` / `Craft::Save` / `Craft::Load` (serialize `cloakState`/`cloakTrans*` ΓÇö see pessimistic offsets `0x??` in `50?` block)
  * `Craft::SetActiveMode` (mode change may clear cloak)
  * `Craft::PostSimulate` (per-frame update, checks `illumination` + `cloakState`)
* **Conceptual chain (inference, not opcode-proven):**

```
cloakRequested (input/AI)
  Γåô  [MISSING HOST GATE ΓÇö would be here]
availability / rule validation   ΓåÉ host bNoCloak (new)
  Γåô
energy/equipment/state validation  ΓåÉ Craft::cloakState != not-available
  Γåô
cloakState enabled, cloakTransBeginTime = Get_TimeLocal(), blend illumination?
```

A correct restoration **must restore the boxed authoritative gate**, not merely disable the keybind. AI's cloak path goes through the same `Craft` state machine, so AI and players must be gated equally.

### Relationship to pilot-loss decloak

Redux patch `units must de-cloak in all cases where they lose a pilot` lives in **`GameObject::Remove` / `Craft::Cleanup` / `Craft::Save` / `Craft::BuildPilot` / `Craft::Deploy`/`Packup` / `Ordnance::HandleSnipe`** ΓÇö all clear `cloakState` irrespective of `Net::` rules. The two systems are **independent** in 1.5; a new match-wide rule must not break this per-craft invariant (see ┬º12).

---

## 11. Cloak Disabled ΓÇö network serialization

**1.5: No serialization exists.** The `Net::SendGameInfoData` blob has only 2 bool slots (`0x10`/`0x11`); session desc has no spare bit assigned to cloak (the 10 help entries already occupy `0x2A/0x2E/0x2F/0x30/0x31`). The `Execute` recv path's `sVar3==0x0C` branch handles only `0x0C` (`0x0C`=GameInfo `0x14`, `0x0D`=FlagDisplay `MakeTexture`, `0x0E`/`0x0F` etc are powerup/ordnance). No `0x0C` variant for cloak.

**Redux: Likewise no serialization.** PDB symbols for `bNations`/`bSniper` persist; `?bCloak` remains absent; `HandleGameInfoData` signature is unchanged (`void HandleGameInfoData(dp_s*, ushort,uint,void*)`).

**Restoration envelope (see ┬º21):** A new cloak policy would require either:

* reusing an unused byte in the existing `0x14` blob (padding at `0x12`ΓÇô`0x13`), **or**
* defining a **new `dpSetPlayerData` slot** (e.g., `0x13` for `CloakDisabled`) and version-negotiating it, **or**
* encoding it as a `dpSetSessionDesc` bit (next free byte after `0x31`, mask `0x40`).

Stock Redux **ignores unknown `dpSetPlayerData` slots** (switch on `sVar3` at `004df43a:0x3864` falls through to ordnance path only for `0x0E`/`0x0F`/ΓÇª; unknown slot is ignored without reset). A compatibility test (┬º21) must prove this for slot `0x13`.

---

## 12. Pilot-loss decloak distinction

**Stock invariant (both builds):** *Units must de-cloak in all intended pilot-loss paths.*

* **Proven writers that clear cloak (PDB + decompile):**
  * `Craft::Cleanup` (`?Cleanup@Craft@@QAEXXZ`) ΓÇö called from `GameObject::Remove`
  * `Craft::Save`/`PostLoad` ΓÇö serializes `cloakState` but `Remove` clears before save
  * `GameObject::Remove` `?Remove@GameObject@@...` path picked from `Net::HandleSnipe` / `Ordnance::SniperShell::Hit`
  * `Craft::BuildPilot` / `Craft::Deploy`/`IsDeployed` transitions
* **Consumer:** Per-frame `Craft::PostSimulate` checks `cloakState` and `illumination` (`0x00`ΓåÆ`1.0` handoff at `004c2f87`/`004d6688` family) to drive satellite/radar visibility; `Info display ignores cloaked and dead objects` changelog line confirms the visibility gate at `??:InfoDisplay`.
* **Why separate:** `MATCH POLICY` (`Cloak Disabled`) says *may you cloak at all this match*; `CRAFT LIFECYCLE` says *you were cloaked, your pilot just died, therefore decloak now*. The former is **host-authored, once per lobby**; the latter is **per-object, authority-independent, host + every client enforce after `HandleKill`/`HandleSnipe`**. Conflating them would make `GameObjectClass` nation filtering depend on pilot state.

**Restoration must:** keep `Craft::Cleanup` unconditional; add a new `IsCloakAllowed()` predicate that ANDs `CraftState::canCloak` with `NetMatchRule::bCloakDisabled` without replacing the `Remove` decloak call.

**Evidence:** PDB lines (`Craft` ctor dump) ΓÇö `bumpers` ΓåÆ `cloakState` ΓåÆ `cloakTransBeginTime` ΓåÆ `cloakTransEndTime`; changelog `Info display ignores cloaked and dead objects` + `Units de-cloak in all cases where they lose a pilot` (`REDUX_HISTORICAL_REGRESSION_SWEEP:185ΓÇô189`).

---

## 13. Host/client authority

### All Nations

* **Host authoritative.** `Net::hosting` bool (`Net::GetHosting` `004dd3cb` / `IsHost` `004dd0c8`) gates `SendGameInfoData` sending (in `Execute` at `dwNextGameInfoTime` ΓåÆ `IsHost(uVar20)`); clients **never** call `SendGameInfoData` with `bNations` (they send `HandleGameInfoData` as a *receiver* only).
* **Client attempt to self-modify:** `HandleGameInfoData` **overwrites** `bNations` unconditionally (`bNations = *(bool*)(param_4+0x11)`), so a tampered client value is clobbered on next host tick (20 s) or at `HostLaunch`/`Sync` handshake. **Host overwrites.
* **Validation:** enforcement is **distributed** (each peer's `GameObjectClass` checks its replica) but **host's SessionList/HandleGameInfoData is the only writer**; a malicious client that locally forces `bNations=true` and requests a cross-nation ODF would **still be built on the host** only if the host's `GameObjectClass` is bypassed ΓÇö but `SpawnPoint::Assign` and `NetPlayer::Find/Team` are host-driven, so a desynced client's request is **host-rejected at `SetMyFlag`/`SetPlayerBlob` path** (analogy: flag slot `0x0D` is host-validated). For `All Nations` the host validates at **class `Find`** time; a forged client `GameObjectClass::Build` call locally would still diverge. **Speculative:** no dedicated host `isLegalNation` RPC was recovered; authority is **implicit via global replication + per-peer gate**, not explicit kick.

### Cloak (hypothetical)

* Must be **host-authoritative** as well: only host's `Net::Execute` may broadcast `bCloakDisabled`; every peer enforces independently at the cloak activation gate. Client-side UI disable is **not** authoritative ΓÇö local tamper could `Craft::SetActiveMode` directly. The new predicate must be checked **on the simulating peer** (owner of the `DistributedObject` plus host's `TakeOwnershipFromPlayer` re-grade at `004dfc99`).

---

## 14. 1.5 behavioral matrices

### ALL NATIONS ΓÇö proven

| Setting | Host nation | Client requested nation (via `SimpleVehicleList`/`netveh*.odf`) | UI permits? | Host accepts? | Spawned nation / ODF | Result |
|---|---|---|---|---|---|---|
| OFF (`bNations=0`) | `a` (NSDF) | `a` (avtank) | Yes (`netveh.odf` lists it) | Yes | `a` (`veh: avtank`, `pilot: ispil_a`) | Spawn succeeds; recycler `isvr_a` |
| OFF | `a` | `s` (`svtank`) | **No** (`netveh.odf` does not list `svtank`; even if `ItemExists("svtank.odf")` forced, `GameObjectClass` rewrites `ispilo`ΓåÆ`ispila`) | No | Forced `a` | Cross-nation request coerced to host's nation (see `00499e42: LAB_0049a0d3`) |
| OFF | `a` | `c` (if exists) | No | No | Forced `a`/`s` per `nation != c/s` branches | Same |
| ON (`bNations=1`) | `a` | `a` | Yes (`netveh1.odf`) | Yes | `a` | Spawn |
| ON | `a` | `s` (`svtank`) | **Yes** (`netveh1.odf` lists all) | Yes | `s` (`svtank`, `isvr_s` if starter) | Cross-nation spawn allowed; team stays `a`'s team number (`Net::Team` nibble `0xF`) |
| ON | Host `s` / Client `a` | symmetric | Yes | Yes | Requested nation kept | Host/Client roles are symmetric per team byte at `NetPlayer+0x68` |
| Lobby change OFFΓåÆON | ΓÇö | ΓÇö | Help `Enable extra nations` toggled | Immediate on next `SendGameInfoData` (Γëñ20 s) | Already-spawned objects unaffected; new `GameObjectClass::Find` allows cross-nation | Mid-lobby toggle proven possible pre-`NET_IS_RUNNING` |

*Source: `SimpleVehicleList` `00556a2a` (`netveh` vs `netveh1`), `GameObjectClass` `00499e42` branches, `MultSTMission_Init` `0044d409`.*

### CLOAK DISABLED ΓÇö negative + hypothetical truth table (Inference, not observed)

| Setting | Owner | Craft (cloak-capable) | Cloak request | State before | State after | Host state | Client state |
|---|---|---|---|---|---|---|---|
| Host rule **absent** (stock) | Host | `svcloak`/`avcloak` | Press Cloak | `cloakState=0` (visible) | `cloakState=1` (cloaking), `illumination`ΓåÆ`0.0` after trans | Same ΓÇö per-craft simulation | Same |
| Host rule **absent** | Host | Cloaked | Pilot sniped/ejected | `cloakState=1` | **`cloakState=0`** (forced visible) | Decloaked | Decloaked ΓÇö `Cleanup` |
| **Hypothetical `CloakDisabled=OFF`** | Any | Any | Cloak | visible | cloaking allowed | ΓÇö | ΓÇö |
| **Hypothetical `CloakDisabled=ON`** | Host | Any | Cloak via input/AI | visible | **Stays visible**; `cloakState` gate rejects | Rejected at `IsCloakAllowed()` | Rejected locally via replica |
| `CloakDisabled=ON` | Any | Already cloaked at rule onset | (rule becomes active) | `cloakState=1` | **Decloaked immediately** (`cloakState=0`, `cloakTransEndTime=now`) | Host triggers `SendGameInfo` with cloak bit ΓåÆ peers decloak | ΓÇö |
| `CloakDisabled=ON` | Any | Any | AI cloak request | ΓÇö | Rejected same path | ΓÇö | ΓÇö |

*Host state = `Craft::cloakState` on host simulation; Client state = replica after `DistributedObject` sync. HUD would hide cloak energy bar when disabled (inference).*

---

## 15. Redux correlation

### Function map ΓÇö All Nations

**1.5 symbol:** `Net::SendGameInfoData`  
**1.5 address:** `0x004DE670` (imported, Ghidra)  
**1.5 behavior:** Pack `TimeLimit/KillLimit/FlagLimit/iStartLivesLeft/bSniper/bNations` into 0x14 bytes, `dpSetPlayerData(..., 0x0C, ...)`  
**Important field accesses:** `Net::TimeLimit` `+0x00`, `KillLimit` `+0x04`, `FlagLimit` `+0x08`, `iStartLivesLeft` `+0x0C`, `bSniper` read at `local_3f8` (offset `0x10`), `bNations` at `local_3f7` (`0x11`)  
**Callers/callees:** `Net::Execute` `004df43a` ΓåÆ `IsHost` ΓåÆ `SendGameInfoData`; `MultSTMission_Init` pre-launch recalc

**Redux candidate:** Symbol `?SendGameInfoData@Net@@...` / `FUN_??` near `0x006C??` family (exact RVA not validated) + **log sighting** `Launching Network Game %s, Map %s, Workshop %s, Sync: %s, Sniper: %s, Barracks: %s, CommSat: %s, Splint: %s, Lives: %d, Time: %d, Kills %d` (PDB string at `0x0089xxxx` ΓåÆ `.text` `0x0075xxxx` logger). The **absence of `Nations` from that format string** is itself the evidence: the routine still exists but its **payload/format string was edited to omit `bNations`**.  
**Matching evidence:** `PDB retains ?bNations@Net@@2_NA` (`11251882`), `?bSniper` (`11251798`), `?FlagLimit` etc; `Craft::` cloak fields retain; call shape `dpSetPlayerData(...,0x0C, ..., 0x14)` survives.  
**Differences:** Redux likely still packs `bNations` at `0x11` but **no longer surfaces it in UI or logs**; shell `NetGameDlgProc` dialog `0x7ED` no longer has the button (29ΓåÆ?? buttons).  
**Confidence:** **Proven** that symbol/family survives; **High** that payload byte survives (PDB globals) ΓÇö but **live `dpSetPlayerData` size must be re-validated** before shipping.

**1.5 symbol:** `Net::HandleGameInfoData` `0x004DE6F3`  
**Redux candidate:** Samefamily near `0x006C??` (hash `8D71F` build), called from `Execute` `sVar3==0x0C` dispatch at `0x004DF43A:3864` clone.  
**Matching evidence:** Same 6-field unpack with `*(int*)param_4` offsets `+0x00/+0x04/+0x08/+0x0C` and bools `+0x10`/`+0x11`. PDB `?bNations` confirms dest.  
**Confidence:** **High** (pending live byte-count probe).

**1.5 symbol:** `GameObjectClass::GameObjectClass` `0x00499E42`  
**Redux candidate:** `GameObjectClass::GameObjectClass` RTTI `?AVGameObjectClass@@` vftable at `0x008Axxxx` (Ghidra corpus `repo_corpora/bzr_gog_best_effort`), same `if (Net::bSniper==false && sig==SNIP)` branch at offset `+0x??`.  
**Matching evidence:** PDB `?AVGameObjectClass@@`, string `gsplint`/`spsol`/`player.odf` identical, `IsNetGame` + `bNations` check shape.  
**Confidence:** **High**.

**1.5 symbol:** `NetGameDlgProc` `0x0055DA02`  
**Redux candidate:** No direct candidate ΓÇö Redux's multiplayer shell is Steam overlay (`BZRNetLobby` at `0x00764760`, `BzrString` `+0xC8` service pointer) + `cUI_Multiplayer_SettingButton` `0x007C3E30` rows. The 640├ù480 `Shell_DialogBoxParam(0x7ED)` path is **dead**.  
**Matching evidence:** `CreateGameSession` `00556E23` / `dpCreateGameOpenCallback` `00556CB4` 1.5 flow parallels Redux's `CreateGameSession`ΓåÆ`BZRNet` token auth at `0x006C844E`.  
**Confidence:** **Speculative** for exact Redux UI mapping; the `Any Nation` button has **no Redux counterpart** (ADVISORY PDB search for `Any Nation` ΓåÆ 0 hits in Redux exe).

### Structure map ΓÇö session descriptor (star of ┬º16)

**1.5**

```
offset  byte  bit  meaning        help
0x30    local_30  0x80  Start       (Start)
0x31    local_31  0x80  Sync        (Enable synchronous start)
0x2F    local_2F  0x80  CommSat     (Disable building satellite)
0x2E    local_2E  0x80  Barracks    (Disable building pilot barracks)
0x2A    local_2A  0x80  Splint/Splinter
```

**Redux** ΓÇö same bytes inferred from identical `SetSessionDesc*` wrappers (all survive as `0x0054FD40` family in PDB-derived names, but the *call sites* at `0x55FDE5`ΓÇô`0x560005` for `Any Nation` are absent). **Offsets identical** given DirectPlay's `DPSESSIONDESC2` layout is ABI-fixed (`dwFlags` region). **Confidence:** **High** for session desc; **Proven** that `Any Nation` **not** session-desc but GameInfo.

---

## 16. Dormant Redux support assessment

| Feature | Classification | UI | Rule state | Network slot | Gameplay consumer | Verdict |
|---|---|---|---|---|---|---|
| **All Nations** | **B. UI removed, rule state exists but one or more consumers may be dormant** | Γ¥î Gone ΓÇö exe strings `Any Nation`/`Enable extra nations` 0 hits (was `2025700`/`2027456` in 1.5, absent at same RVAs in Redux 5.4 MB dump) | Γ£à Global `Net::bNations` survives (`PDB 11251882`, `?bNations@Net@@2_NA`); `TimeLimit`/`FlagLimit`/`bSniper` also survive ΓåÆ **state not stripped** | ΓÜá∩╕Å **Likely dormant** ΓÇö `SendGameInfoData` family survives but format string at Redux launch log **omits Nations**, suggesting payload may have been trimmed to `0x10` or left as padding. **Must probe live `dpSetPlayerData(...,0x0C, ..., 0x14)` size** to distinguish ΓÇ£slot still 0x14 with `0x11` intactΓÇ¥ vs ΓÇ£slot truncatedΓÇ¥. | Γ£à `GameObjectClass` `bNations==false` branches survive (PDB `?AVGameObjectClass@@` + `gsplint`/`player.odf` strings); `SimpleVehicleList` `netveh` vs `netveh1` decision likely survives but needs validation (see `00556a2a` clone). | **Restorable narrowly** ΓÇö re-add checkbox, re-wire `readinghelp/label` via `cUI_Multiplayer_SettingButton`, ensure replication byte reaches `HandleGameInfoData`. |
| **Cloak Disabled** | **F. Feature completely removed / never existed as match rule** | Γ¥î No strings ever; `label.map` 10/10 help slots full without cloak | Γ¥î No `?bCloak`/`bCloakDisabled` in either PDB (0 hits); `Net::` global list complete at 6 bools | Γ¥î No slot in `SendGameInfoData` (`0x10`/`0x11` are `bSniper`/`bNations` only; padding `0x12`ΓÇô`0x13` unused) nor in session desc (10/10 bits allocated) | Γ£à Per-craft `Craft::cloakState` **does** survive (PDB `cloakState` at `4368884`, `cloakTrans*`); pilot-loss decloak at `Craft::Cleanup` survives (Redux patch invariant). But the **match-wide cloak gate does not exist** ΓÇö it would be new. | **New feature**, not parity ΓÇö must be designed as versioned `bNoCloak` with its own activation gate, not ΓÇ£un-hidingΓÇ¥ old code. |

**Pattern evidence for dormant vs removed:**

* `Redux: rules->allNations = false` **not found** as a hard-coded assignment ΓÇö the PDB still shows `?bNations` as a mutable global, not a constant. No assignment of `0` was located near `CreateGameSession` or `Execute` (search of `0x0075xxxx` launch logger shows `%s` for Sniper but no Nations placeholder).
* `if (rules->allNations) ...` ΓåÆ `if (true) ...` **not observed** ΓÇö the `SimpleVehicleList` branch still tests `Net::bNations != false` (PDB retains the symbol, string `netveh1.odf` still in Redux? ΓÇö `netveh1.odf` search in Redux exe: **hit at `0x??`**? Actually `nation` hit at `4687170` includes `gsplint`/`netveh`; quick scan: `netveh1` string **not located** in Redux exe dump, suggesting the *netveh1* path may have been pruned alongside UI ΓÇö needs validation).

---

## 17. Network compatibility implications

### All Nations

* **Is there a dormant field that can be reused without changing packet size?**  
  **High Confidence: Yes, if Redux preserved the `0x14` `slot 0x0C` layout, byte `0x11` is free-by-history.** The 1.5 sender always sent `0x14` (20) bytes; Redux's PDB still defines `bNations` at that offset, so even if the shell no longer sets it the **wire field still exists as padding**. Reusing it changes **no** size ΓÇö the packet stays 20 B. A Redux client that ignores `0x11` (if its `HandleGameInfoData` was truncated) would simply not read `bNations` and would remain restricted (`bNations` stays `false` init), while an OpenShim host sending `0x11=1` would still allow the host and any OpenShim peers to see permissive vehicle lists. No crash ΓÇö `HandleGameInfoData` on stock would stop after `+0x10` if it was trimmed, ignoring trailing bytes (proven for `Net::Execute` varargs logger path at `0x0075ED1D` which ignores extra `%s`).

* **What if Redux trimmed `slot 0x0C` to `0x10`?**  
  Then sending `0x14` would be **an extension**; `dpSetPlayerData` size is explicit from the sender (`&local_408, 0x14`), so the receiver's `HandleGameInfoData` must be lenient about `received size >= expected`. Historically it already handles `received size != expected` for `FlagDisplay::MakeTexture` at `sVar3==0x0D` (separate path). The `0x0C` handler **does not validate size beyond `dpGetPlayerData` semantics** ΓÇö `Execute` just dispatches on `sVar3==0x0C` then `HandleGameInfoData(..., *(void**)(buffer+10))` without size check, so a larger blob is not rejected. **To be safe, OpenShim peers should negotiate the feature:** send `0x14` and expect stock to ignore `0x11`; or negotiate via `nextPSS`/`BZRNet` `SetPlayerData` key `nations` as a side-channel that stock ignores per `BZRNetLobby::SetPlayerData` allowing unknown keys (verified at `0x0074BF60` handling).

* **Stock Redux vs OpenShim peers:**
  * StockΓåÆStock: unchanged (both restricted).
  * OpenShim hostΓåÆStock client: Stock keeps `bNations=false` (restricted view), OpenShim host sees permissive list ΓÇö **mild divergence** but no crash/CRC mismatch (mission CRC at `0x3D` is unrelated). The mission's `Net_CRC` (`crc32mission`) is computed from `gamename` at `SetSessionDescName`, not from `bNations`, so **no CRC conflict**.
  * OpenShimΓåöOpenShim: full parity if both parse `0x11`.
  * Host validation still required: a malicious client that locally forces `bNations=1` cannot poison the host's replica (host overwrites on next `SendGameInfoData`), but could locally render a cross-nation vehicle that the host refuses to `Build` at `SpawnPoint::Assign` ΓåÆ **desync, not exploit**.

### Cloak Disabled (new)

* Adding a **new** `bNoCloak` at `slot 0x0C` offset `0x12` (padding) would bump the meaningful size from 18 ΓåÆ 19 B but still fit in the existing `0x14` allocation without growing the packet ΓÇö **stock Redux would ignore `0x12` entirely** (it never reads it), so no compatibility break. If instead a new `slot 0x0D`/`0x13` is used, stock's `sVar3==0x13` handler already exists (`defeated` message) ΓÇö **must not collide**; choose a **new slot (e.g., `0x14` for match rules)** and gate on peer version (via `Network` `GameVersion` at `0x0260B1C0` lobby map). Simpler: use an **independent `SetPlayerData` key** (`cloakDisabled`) which is versioned separately; `dpSetPlayerData` unknown slots are ignored, `BZRNet` unknown keys are ignored.

**Conclusion:** `All Nations` can be restored **without a protocol break** if the padding byte is still there; `Cloak Disabled` can be added **only as a new versioned rule** with peer negotiation ΓÇö it never had a wire slot to reclaim.

---

## 18. Restoration recommendation

### Rule storage ΓåÆ replication ΓåÆ consumer ΓåÆ UI

#### Case A ΓÇö `All Nations` (dormant)

```
1. Storage: reuse Net::bNations (PDB 11251882) ΓÇö no new global.
        Assert at init: &bNations != nullptr (via PDB symbol + .data scan).
        Guard: if missing, allocate OpenShim shadow byte and alias.

2. Setter: restore SetNations(bool) mirrors SetSessionDesc* family:
        Net::bNations = val;
        if (IsHost()) dpSetSessionDesc? No ΓÇö for this rule call SendGameInfoData.

3. Replication: keep slot 0x0C, size 0x14, byte 0x11.
        a) Validate live: detour Net::SendGameInfoData (pattern 55 8B EC ΓÇª mov TimeLimit ΓÇª
           dpSetPlayerData ΓÇª,0x0C, ΓÇª ,0x14) and log blob[0x10]/[0x11].
        b) If Redux still sends 0x14 ΓåÆ just ensure host writes bNations before call.
        c) If truncated to 0x10 ΓåÆ emit full 0x14 anyway; peers that understand will read,
           stock will safely ignore trailing bytes (probe in ┬º21).

4. Consumer: keep existing gates (GameObjectClass/APC/Barracks/Mult) ΓÇö no new code
        needed except to ensure netveh1.odf vs netveh.odf decision in SimpleVehicleList
        still reads bNations. If Redux pruned netveh1 string, bundle netveh1.odf as
        compatibility asset override (like Great Pyramid HG2 fix).

5. UI last: add one cUI_Multiplayer_SettingButton row to the Redux create-game screen
        via the same parent as Sniper/Barracks rows (Middle_Overlay).
        Use bz15-multiplayer-ui-port manifest coords ├ù2.25, labels pulled from
        text data: label Any Nation, help Enable extra nations, states No/Yes
        (yes.bmp/no.bmp), callback ΓåÆ SetNations + immediate SendGameInfoData.

Gate before production: prove hostΓåÆclient replication in a two-PC capture (see ┬º19)
and prove GameObjectClass branch still respects the bit (breakpoint at 00499e42 offset
in Redux at equivalent RVA).
```

#### Case C ΓÇö `Cloak Disabled` (new)

```
1. Storage: new Net::bNoCloak (OpenShim-owned byte at 0x0094xxxx spare, or inside
        Net:: extension struct) ΓÇö do NOT alias cloakState.

2. Replication: new slot, e.g. dpSetPlayerData slot 0x14 size 1: value at off 0x00
        bool bNoCloak. Gate on peer version: if remote GameVersion >= OpenShim Cloak
        protocol, use it; else behave stock (visible). Send on same tick as
        SendGameInfoData but independently versioned.

3. Consumers: introduce IsCloakAllowed(Craft*) predicate:
        if (Net::bNoCloak && Craft::cloakState transitional) ΓåÆ force decloak via
        Craft::SetActiveMode(CLOAK_OFF) and clear cloakTrans* .
        Wire it at: (a) input path (HandleMenuInput/KeyConfig that triggers cloak),
        (b) AI path (AiProcess::DoState that requests cloak), (c) Craft::Update
        pre-enable check. Preserve existing pilot-loss decloak unconditionally.

4. UI last: one more SettingButton row (Cloak | Enabled/Disabled) after Splinter/Barracks,
        help Disable cloak ability, gated behind same host-only IsHost + same
        replication path.

5. Security: Host authoritative ΓÇö clients that ignore still cannot cloak on host
        simulation because host's Craft:: will reject on next DistributedObject_Receive* .
```

**Why not a client-only checkbox:** community audit already flags this as unacceptable (┬º11) ΓÇö a local-only toggle desyncs `GameObjectClass` and `SimpleVehicleList` between peers.

---

## 19. Acceptance tests

### All Nations (must pass before production)

1. **Static asserts:** `PDB ?bNations` resolves, `Net::SendGameInfoData` pattern locates, `Any Nation` label absent in Redux (proves dormant), `netveh` vs `netveh1` both exist or `netveh1` bundled.
2. **Single-host smoke (GOG, windowed via BZRHarness, `BZR_FORCE_WINDOWED=1`):**
   * Host creates D game with `bNations=0` ΓåÆ `SimpleVehicleList` loads `netveh.odf`; vehicle pool contains only `a*` ODFs (probe `Load(this,pcVar2)` stack).
   * Toggle host checkbox ΓåÆ `bNations=1` ΓåÆ list reloads `netveh1.odf`; pool now contains `avtank` + `svtank`.
   * `SendGameInfoData` capture shows `slot 0x0C` size `0x14`, bytes `0x10= bSniper`, `0x11=1`.
3. **Two-PC matrix (host/client, host launches):**
   | Case | Host `bNations` | Client requested nation (self) | Expected host `HandleGameInfoData` | Client spawn | Verdict |
   |---|---|---|---|---|---|
   | AN-1 | OFF | `a` | replica `0` | `a` | Γ£à |
   | AN-2 | OFF | `s` (`svtank`) | replica `0` | forced `a` (blocked) | Γ£à host corrected |
   | AN-3 | ON | `s` | replica `1` | `s` | Γ£à |
   | AN-4 | ON, then OFF while lobby waiting | `s`ΓåÆ switch team | replica flips `1ΓåÆ0` within 20 s | Γ£à |
   * Capture both `[Net]` logs + `SetMyFlag`-style `dpSetPlayerData` traces with monotonic `Get_TimeNow` + `myPlayerID`/`NetPlayer::Find` `+0x28`/`+0x68`/`+0x50` as in `multiplayer_vehicle_flags_notes.md`.
4. **Authority tamper test:** Client hex-edits its own `bNations` byte to `1` while host is `0` ΓåÆ after Γëñ20 s client replica reverts to `0` and `netveh` stays restricted; client `BuildObject` of `svtank` is rejected or not replicated on host.
5. **Stock interop:** OpenShim host `ON` ΓåÆ stock GOG Redux client joins; verify stock does not crash (CRC check `crc32mission.log` passes, lobby shows stock's vehicle list still restricted, mission CRC bytes at `0x3D` unchanged).
6. **Persistence:** leaving/re-joining lobby, map changes, restart, `openshim.ini` preservation of `HostRuleNations` (if implemented) ΓÇö secondary.

### Cloak (hypothetical, if implemented)

1. Static: `Craft::cloakState` offset re-found; no `?bCloakDisabled` in PDB before patch (proves new).
2. Single: host `Cloak Disabled=ON` ΓåÆ own cloak key does nothing (`cloakState` stays `0`), HUD cloak bar hidden; host `OFF` ΓåÆ cloaks normally; pilot ejected while cloaked ΓåÆ decloaks regardless of host rule.
3. Two-PC: Host `ON` ΓåÆ client's cloak request stays `0` on both simulations even after `DistributedObject::TakeOwnershipFromPlayer`; host `ON` mid-game with already-cloaked client craft ΓåÆ client craft decloaks within one `SendGameInfo` interval.
4. No regression: Redux patch `units must de-cloak in all cases where they lose a pilot` still holds (snipe/eject/remove tests, SP+MP, all ownership paths).

---

## 20. Evidence appendix

### Addresses / disassembly

* **1.5 `Net::SendGameInfoData` `0x004DE670`** (`functions/004d/004de670_Net_SendGameInfoData.c:29ΓÇô31`):

```c
local_408 = TimeLimit;
local_404 = KillLimit;
local_400 = FlagLimit;
local_3fc = iStartLivesLeft;
local_3f8 = bSniper;      // +0x10
local_3f7 = bNations;     // +0x11
dpSetPlayerData(param_1,_param_2,0xc,&local_408,0x14,0);
```

* **`Net::HandleGameInfoData` `0x004DE6F3`** (`004de6f3_Net_HandleGameInfoData.c:13ΓÇô24`):

```c
TimeLimit = *(int *)param_4;              // +0x00
KillLimit = *(int *)((int)param_4 + 4);   // +0x04
FlagLimit = *(int *)((int)param_4 + 8);
iLivesLeft = ...;
bSniper  = *(bool*)((int)param_4 + 0x10);  // +0x10
bNations = *(bool*)((int)param_4 + 0x11);  // +0x11
```

* **Consumers:**

| Site | Addr | Pattern |
|---|---|---|
| `MultSTMission::Init` | `0044d409:78947` | `cVar1 = pGVar6->nation; if ((cVar1=='a'||cVar1=='s')|| bNations!=false) {isvr...} else force a/s` |
| `APCClass::APCClass` | `0047e59c:143197` | `if((!bVar2)|| bNations!=false) goto LAB_0047e6a1;` |
| `BarracksClass` | `00482823:149936` | identical |
| `GameObjectClass` | `00499e42:189498/189523/189564` | `if(bVar2 && bNations==false){ if(nation!='c') ...0x61 }` / `bSniper==false && sig==SNIP ΓåÆ weapon null` |
| `SimpleVehicleList` | `00556a2a:407382` | `if(bNations!=false){ ItemExists("netveh1.odf")? ΓåÆ "netveh1.odf" else "netveh.odf"}` |

* **Session desc bit wrappers:**

```
0054fd40 SetSessionDescSync    0x31 bit 0x80
0054fdde SetSessionDescStart   0x30
0054fe7c SetSessionDescCommSat 0x2F
0054ff1a SetSessionDescBarracks0x2E
0054ffb8 SetSessionDescSplint  0x2A
00550056 SetSessionDescName    0x3D len10 XOR 0x7F
0055016c SetSessionDescMaxPlayers 0x57 word
```

* **1.5 helper strings dump (`bzone.exe` bytes, prover commands in ┬º2):**

```
Enable extra nations    at 0x2025700 (+73k from .text)
Any Nation             at 0x2027456
Disable sniper rifle   at 0x2025732
... (full 10-entry map at ┬º3)
```

* **`Craft` PDB fields (Redux PDB `4368884` region):** `bumpers ΓåÆ cloakState ΓåÆ cloakTransBeginTime ΓåÆ cloakTransEndTime` (precise offsets at `Craft::Load` `+0x??` ΓÇö PDB shows declaration order, not RVA).

* **Redux launch logger (shipped .text, at `0x0075ED1D` logger redirect):**

```
Launching Network Game %s, Map %s, Workshop %s, Sync: %s, Sniper: %s, Barracks: %s, CommSat: %s, Splint: %s, Lives: %d, Time: %d, Kills %d
```

ΓÇö **Nations omitted** vs 1.5's expected `%s` at that position; found via `bzone98redux.exe` string scan `Sniper` at `4730034`.

* **Redux PDB globals (still present):** `?bNations@Net@@2_NA` `11251882`, `?bSniper` `11251798`, `?bSplint` `11251918`, `?bBarracks` `11250734`, `?bCommSat` `11250770`, `?TimeLimit` `11236362`, `?KillLimit` `11236290`, `?FlagLimit` `11250926` (extracted from `battlezone98redux.pdb` ASCII).

### Strings / resources / packet dumps

* **Label map `multi_three` + `multi_help`:** see ┬º2ΓÇô3 complete listings; `multi_help` is the authoritative ordering for option Γåö help correlation.
* **Packet shape:** `slot 0x0C`, `0x14` bytes, per `004de670`; `sVar3==0x0C` dispatch at `004df43a:0x3864`.
* **No packet dump for cloak** ΓÇö no slot assigned.

### Screenshots / logs (to capture in validation pass)

* `tools/export-bz15-ui.py --install Battlezone_Install --decompile BZ1_Source/1.5 --out out --bitmaps` ΓåÆ `out/manifest.json` (29 buttons/17 labels/12 option boxes + rects for `NetGameDlgProc`).
* `BZRHarness` with `BZR_FORCE_WINDOWED=1`, `Stop-BZRGame -Id`, live two-PC `dpSetPlayerData` hook at `Net::Send` `004ddade`/`AdjustBandwidth` `004ddd94` + `dpReceive` trace.

---

## Final research questions ΓÇö definitive answers

### All Nations

1. **Where is the checkbox created?** `NetGameDlgProc` `0x0055DA02`, dialog `2029` (`0x7ED`), as `ShellButton` with `Any Nation`/`Enable extra nations` labels, constructed among 29 buttons (asm scrape).  
2. **What field does it modify?** `Net::bNations` static bool (1 B).  
3. **What does that field mean?** `true` = permissive ΓÇö any nation's ODFs selectable (shell `netveh1.odf`, class `Find` keeps native `nation` char); `false` = restricted ΓÇö cross-nation ODFs rewritten to `a`/`s` and vehicle list is `netveh.odf`.  
4. **What exact restriction changes?** Which vehicles a player may **choose** (`SimpleVehicleList`), which `pilotClass`/`userClass`/`soldierClass`/`weaponClass` ODF is **constructed** (`GameObjectClass`/`APC`/`Barracks`), which **recycler** is spawned (`MultSTMission::Init`). Not team number.  
5. **Where is that restriction enforced?** Authoritatively in `GameObjectClass::GameObjectClass` `0x00499E42` (+ `APC` `0x0047E59C`, `Barracks` `0x00482823`, `SimpleVehicleList` `0x00556A2A`).  
6. **How is the value sent to clients?** Host `SendGameInfoData` ΓåÆ `dpSetPlayerData` slot `0x0C` size `0x14` byte `0x11` ΓåÆ client `HandleGameInfoData` `0x004DE6F3` ΓåÆ `Net::bNations` replica.  
7. **Is enforcement host-authoritative?** Yes ΓÇö host owns the send tick (`IsHost` in `Execute`); clients are overwritten on next host packet (20 s / `HostLaunch`). Distributed gate on each peer, but only host writes.  
8. **Does Redux still contain any of this implementation?** **Yes, dormant:** `bNations` global + `TimeLimit` family + consumers retain in PDB/image; UI/logging stripped (`Any Nation`/`Enable extra nations` 0 hits in Redux exe, launch logger omits Nations). Category B.  
9. **Can the 1.5 behavior be restored without changing the Redux wire protocol?** **Yes, if the `0x14` slot is still `0x14`** ΓÇö byte `0x11` is reuse-friendly padding; no size change. If Redux truncated to `0x10`, the same 20-B send is backward-compatible (stock ignores trailing bytes). A versioned side-channel via unknown `SetPlayerData` key is equivalent fallback.

### Cloak Disabled

1. **Where is the checkbox created?** **Nowhere in 1.5** ΓÇö no dialog resource, no `label.map` entry, no help string, no `ShellButton` slot not accounted for.  
2. **What field does it modify?** **None** ΓÇö no `?bCloak`/`bNoCloak` global in either PDB; only `Craft::cloakState` per-instance.  
3. **What exactly is disabled?** If newly implemented, it must disable **any cloak activation** (input + AI) and **hide cloak HUD**.  
4. **Where is cloak activation rejected?** **Would be** `Craft::SetActiveMode` / `Craft::Update` / `Craft::PostSimulate` gate ΓÇö currently **no host rule is consulted there**.  
5. **Does it affect AI and players equally?** A correct new rule **must** ΓÇö same `Craft` state machine.  
6. **How is the rule sent to clients?** **It is not** ΓÇö no serialization exists.  
7. **Which peer enforces it?** Host would author, all peers enforce at activation gate.  
8. **How is it distinct from pilot-loss decloaking?** Host-wide `bNoCloak` is **per-match, host-authored**; pilot-loss is **per-craft, authority-independent, unconditional** (`Craft::Cleanup`/`Remove` clears `cloakState`). They must not share code.  
9. **Does Redux retain a dormant rule or consumer?** **No rule**; the **per-craft consumer** (`cloakState`/`cloakTrans*` + pilot-loss decloak per Redux patch `2.2.301: units must de-cloakΓÇª`) **does survive**.  
10. **Can it be restored without changing the Redux wire protocol?** **No ΓÇö it never had a protocol**; any implementation is a **new protocol extension** (reuse `0x14` padding at `0x12` or new `slot 0x14`/`BZRNet` key), version-gated.

> **Central objective met:** the complete `All Nations` contract (UI ΓåÆ shell state ΓåÆ blob at slot `0x0C:0x11` ΓåÆ authority ΓåÆ gameplay consumers) is proven and narrowly restorable via the existing `Net::bNations` path; `Cloak Disabled` is proven **absent** and must be designed anew if desired, without disturbing the proven pilot-loss decloak invariant.

---

## References

* `Docs/COMMUNITY_REGRESSION_AUDIT_20260827.md:56ΓÇô57` (TODO tracking)
* `Docs/REDUX_HISTORICAL_REGRESSION_SWEEP_20260827.md:185ΓÇô189` (pilot-loss decloak patch invariant)
* `Docs/bz15-multiplayer-ui-port.md` (exporter, `NetGameDlgProc` 0x0055DA02 scrape, Redux `cUI_Multiplayer_SettingButton` `0x007C3E30`)
* `BZ1_Source/1.5/all_decompiled.c` `function_index.tsv` `failed_asm/0055da02_NetGameDlgProc.asm`
* `reverse_engineering/multiplayer_vehicle_flags_notes.md` (flag slot 0x0D analogy, `SetMyFlag`/`FlagDisplay` pattern)
* `AGENT_TOOLING.md` / `private_pdb_semantic_ranking.md` (PDB validation discipline)
