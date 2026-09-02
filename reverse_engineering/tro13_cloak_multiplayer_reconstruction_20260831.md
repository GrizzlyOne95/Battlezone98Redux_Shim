# The Red Odyssey 1.3 — Cloak and Multiplayer Host-Rule Reconstruction

**Date:** 2026-08-31
**Target:** `C:\Program Files (x86)\The Red Odyssey 1.3\odyssey.exe` (756 428 B, `7b503759…c4ea`)
**Corpus:** `BZ1_Source/TRO1.3/` — statically unpacked image + rebuilt PE + 6312 Ghidra decompilations
**Companion:** `mp_allnations_cloakdisabled_15_reconstruction_20260831.md` (BZ 1.5 / Redux)

---

## 0. Headline

* **TRO's `odyssey.exe` was unpacked statically.** It is not Shrinker despite the header banner —
  it is **UPX `--lzma` with blanked section names**. Full parameters, OEP (`0x005BE5D0`) and all
  339 imports recovered; see `BZ1_Source/TRO1.3/README.md`.
* **Cloak in TRO is a real, first-class engine feature** — unlike BZ 1.5, where it exists only as
  latent `Craft::` PDB symbols. TRO ships ODF properties, a 4-state transition machine, a render
  flag, a command-menu entry, a keybind, and a script API.
* **There is a global cloak enable/disable flag: `g_CloakEnabled` at `0x005E10A4`.** It is checked
  at every cloak decision point. It has **exactly one writer** — the script API `EnableCloaking(bool)`
  at `0x0042B270` — and **exactly two callers, both passing `false`**: the built-in campaign scripts
  for Chinese missions **ch01** and **ch02**.
* **It is *not* a multiplayer host option.** TRO's host-rule set is the stock BZ 1.4 eight
  (sniper / lives / kill / time / players / barracks / sync / comm-sat). No cloak rule exists in the
  UI, the help block, the session description, or the netcode.
* **Latent bug:** `g_CloakEnabled` is a statically-initialised `1` and is **never set back to `1`
  anywhere in the image**. Playing ch01 or ch02 and then hosting or joining a multiplayer game in the
  same process leaves cloak globally dead for that player until the exe is restarted.
* **There is a ready-made spare host-rule bit.** The anet session description carries four
  high-bit boolean slots; the pair at **byte 56** (setter `0x0054F200`, getter `0x0054F250`) is
  **fully compiled and never called by anything**. It is the natural carrier for a synchronized
  `Cloak Disabled` rule.

---

## 1. Cloak — the data model

### 1.1 ODF class properties (prototype object)

Read in the class initialiser ending at `0x0045C182` (`ret 0xC`), which copies parent defaults
from `ebx` into the new class at `esi`:

| Class offset | ODF key | Reader | Type |
|---|---|---|---|
| `+0x2D0` | `cloakAllowed` | `0x0046DC70` | bool |
| `+0x2D4` | `cloakTime` | `0x0046DD30` | float (transition duration, seconds) |
| `+0x2D8` | `forceCloak` | `0x0046DD30` | float (**not** a bool — see §1.3) |
| `+0x2DC` | `cloakOnSound` | `0x0046DE50` | string[16] |
| `+0x2EC` | `cloakOffSound` | `0x0046DE50` | string[16] |

Shipping data confirms the intent — `addon/bvrmpa.odf`, `bvrmpb.odf`, `cvhraz.odf`, `cvhtnk.odf`,
`cvrmpa.odf`, `cvwalk.odf`, `cvhzmp.odf` all carry `cloakAllowed = true`, and their `.des` files
say `Can cloak.`

### 1.2 Instance fields (craft object)

Established from the constructor at `0x0045783F`–`0x0045786A` and the save/load record at
`0x00457BD0`:

| Object offset | Field | Notes |
|---|---|---|
| `+0x2A4` | `cloakAllowed` | copied from class `+0x2D0` at construction |
| `+0x2A5` | runtime cloak-enable | per-object; written only by script API `0x0042B280` |
| `+0x2A8` | `forceCloak` | copied from class `+0x2D8` |
| `+0x2AC` | `cloakTime` | copied from class `+0x2D4` |
| `+0x2B0` | `cloakState` | 0 = clear, 1 = cloaking, 2 = cloaked, 3 = decloaking |
| `+0x2B4` | `cloakTransBeginTime` | float |
| `+0x2B8` | `cloakTransEndTime` | float |

`Craft::Save` at `0x00457BD0` serialises `abandoned` (`+0x224`), then `cloakState`,
`cloakTransBeginTime`, `cloakTransEndTime` — so cloak survives save/load, and the field-name
literals in the save record are what make the exact offsets provable.

### 1.3 `forceCloak` is an alpha override, not a flag

`Craft::UpdateCloak` (`0x0045B790`) tests `[this+0x2A8] > 0` **before** the state machine and, when
true, drives the render object's translucency directly to that value, clamped to 1.0, bypassing
cloakState entirely. So `forceCloak = 0.5` yields a permanently half-transparent craft. This is
worth flagging because the name reads like a boolean and an OpenShim ODF parser that treats it as
one would be wrong.

---

## 2. The cloak capability predicate — and the global gate

The same three-term test is inlined at five sites:

```c
CanCloak(obj) =  obj[+0x2A4]        /* per-craft cloakAllowed, from ODF   */
              && DAT_005E10A4       /* g_CloakEnabled — GLOBAL            */
              && obj[+0x2A5];       /* per-craft runtime enable           */
```

| Site | Function | Role |
|---|---|---|
| `0x0045B74B` | `0x0045B740` — `Craft::ForceCloakNow` | jams `cloakState = 2` with no transition |
| `0x0045B885` | `0x0045B790` — `Craft::UpdateCloak` | if capability is revoked mid-cloak, forces state 3 (decloaking) |
| `0x0045BAD0` | `0x0045BAC0` — command dispatch | gates command id 7 (Cloak) |
| `0x00438E85` | `0x004389C0` — command-menu build | gates the `Cloak`/`Decloak` menu entry |
| `0x00487C22` | `0x00487C10` | order handler; issues cloak command 7 when allowed |

**`g_CloakEnabled` lives at `0x005E10A4`, in initialised data, with the value `1`.**
(Raw bytes at `0x005E10A0`: `A8 10 5E 00 | 01 00 00 00 | "bail.wav"` — the dword before the
`bail.wav` pointer.)

### 2.1 Exactly one writer

```
0042B270  push ebp
0042B271  mov  ebp, esp
0042B273  mov  al, byte ptr [ebp + 8]
0042B276  mov  byte ptr [0x5E10A4], al     ; <-- the only write in the image
0042B27B  pop  ebp
0042B27C  ret
```

`0x0042B270` sits in a contiguous block of mission-script API wrappers (`0x0042B1B0` cloak,
`0x0042B1F0` decloak, `0x0042B230` is-cloaked, `0x0042B280` set per-object cloak enable), each of
which resolves a handle through `0x00461690` and checks the object flag `0x200`. This is the
BZ1 `ScriptUtils` surface; TRO's names for these are almost certainly
`SetCloaked` / `SetDecloaked` / `IsCloaked` / `EnableCloaking` / `SetCloakAllowed`.

### 2.2 Exactly two callers, both `false`

| Call site | Argument | Mission |
|---|---|---|
| `0x005AE6A9` (`push edi`, `edi` zeroed at `0x005AE679`) | `0` | **ch01** — nearby literals `ch01001.wav`, `ch01001.otf`, `CCA Base`, `relic_tug` |
| `0x005B049B` (`push 0`) | `0` | **ch02** — nearby literals `ch02001.otf`, `hanger_attack_2`, `walker_spawn` |

Both sit behind a one-shot latch (`[this+0x4C]`) in the mission's first update, i.e. "on mission
start, turn cloak off". Narratively consistent: cloak is not yet available in the first two
Chinese missions.

### 2.3 The latch is never released — a real bug

*Proven disassembly.* `g_CloakEnabled` is written only by `0x0042B270`; `0x0042B270` is called only
from the two sites above; both pass `0`. Nothing in the image writes `1`. The exe has **no export
directory** (`DATA_DIRECTORY[0]` rva/size = 0/0) and no pointer table references `0x0042B270`, so
an external mission DLL cannot reach it either. The only thing that restores the value is the
static initialiser at image load.

**Consequence:** play Chinese mission 1 or 2, return to the shell, then host or join a multiplayer
match without quitting — every cloak-capable craft you own is silently un-cloakable for the rest of
the process. Other peers are unaffected, because the flag is local (§3.3), so this presents as
"cloak randomly stops working for one player".

This is a one-instruction fix for OpenShim (`EnableCloaking(true)` on mission teardown / shell
entry), and is independent of any new host option.

---

## 3. The cloak state machine

`0x0045B520` `Cloak()`, `0x0045B5A0` `Decloak()`, `0x0045B620` `ToggleCloak()` (jump table at
`0x0045B72C` → `{0045B63D, 0045B6B8, 0045B6B8, 0045B63D}`), `0x0045B790` `UpdateCloak()`.

* States 0→1→2 (cloaking) and 2→3→0 (decloaking); an interrupted transition is **reversed in place**
  — the remaining time is mirrored rather than restarted, so a decloak half-way through a cloak
  takes half as long. Good behaviour to preserve if this is ever reimplemented.
* Transition progress drives translucency through `0x004C81A0(renderObj, alpha)`.
* Whenever `cloakState != 0`, `UpdateCloak` sets bit **`0x02000000`** in the render object's flag
  word at `[renderObj+0x14]`, and clears it at state 0. That bit is the engine-wide "this thing is
  cloaked" signal; `cmp dword ptr [eax+0x2B0], 2` at `0x0041427B`, `0x0041CCFB`, `0x00430145`,
  `0x00430CCB` are the separate "fully cloaked" tests in targeting/AI.

### 3.3 Replication — cloak *is* networked, but only as a visual

`UpdateCloak` branches on `0x0045DDB0` (called with `this+0x18`) first. On that path it does **not**
run the state machine at all: it derives `cloakState` from the already-replicated translucency float
at `[renderObj+0xF0]` (`>= 1.0` → state 2, `> ~0` → state 3, else 0) and sets the `0x02000000` flag
to match.

`0x0045DDB0` is a one-liner: `return *(char *)(this + 0x18 + 0x68) == 2;` — a small control-mode
enum on the subobject at `+0x18`.

*Inference (medium confidence):* mode `2` is the remote/non-authoritative-object case. The
practical consequence is solid either way — **remote peers reconstruct cloak from the object's alpha
channel, not from a cloak message.** There is no cloak opcode on the wire, and `g_CloakEnabled` is
never transmitted. Any match-wide `Cloak Disabled` rule therefore needs its own replication; setting
the global locally on each peer would be a desync-free but unenforceable honour system, and setting
it only on the host would do nothing at all to clients.

### 3.4 Input and UI

* `input.map` line 346: command `cloak` bound to **`G`**, suppressed in `EditMode` — matching the
  shipped `readme.txt` ("To Cloak your Chinese 'Cloakable' vehicle press the 'G' key").
* Command-menu labels `Cloak` (`0x005E71A8`) / `Decloak` (`0x005E71A0`) appear in two label tables at
  `0x005E6BE0`/`0x005E6BE8` and `0x005E6CC8`/`0x005E6CD0`.
* `label.map` contains **no** cloak entry — the menu strings are exe literals, so a localisation or
  UI edit has to patch the image, not the data file.

---

## 4. Multiplayer host rules in TRO 1.3

### 4.1 The option set is stock BZ 1.4 — eight rules, no cloak

Help/tooltip block, `0x005FC06C`–`0x005FC188`, registered at `0x00569150`–`0x00569380` via
`0x00598CB0(widget, parent, helpText, helpKey)`:

| Help text | Key | Help widget global |
|---|---|---|
| Disable sniper rifle | `sniper` | `0x00824B88` |
| Number of player respawns allowed | `lives` | `0x00824D10` |
| Set max number of kills | `k_limit` | `0x00824DBC` |
| Set max length of game time | `t_limit` | `0x0082C698` |
| Set max number of players | `p_limit` | `0x0082478C` |
| Allow building pilot barracks | `barrack` | `0x0082C674` |
| Starts all players at the same time | `sync` | `0x00824CA4` |
| Allow building satellite comm tower | `com_sat` | `0x0082C68C` |

Display labels come from `label.map` sections `multi_three` / `multi_common` via `0x00489DD0`,
loaded at `0x00565430`–`0x005656E0`.

For contrast, the BZ 1.5 help block has ten entries — it adds `nations` and `splint`. TRO has
neither, and neither build has cloak. **`Cloak` does not occur as a host option anywhere** in the
TRO image strings, `label.map`, `input.map`, or the netcode.

### 4.2 The wire format: high-bit stuffing in the anet session description

Host rules are advertised by read-modify-writing the **0x5F-byte anet session description**
(`dpGetSessionDesc` thunk `0x005BDE1C` → mutate → `dpSetSessionDesc` thunk `0x005BDE46`). Booleans
are carried as **bit `0x80` of an otherwise 7-bit field**:

| Desc byte | Setter | Getter | Meaning | Local global |
|---|---|---|---|---|
| 55 (`0x37`) | `0x0054F170` | `0x0054F1C0` | game type is Strategy (`'S'` in `netmis.txt`) | — |
| **56 (`0x38`)** | **`0x0054F200`** | **`0x0054F250`** | **unused — zero callers** | — |
| 57 (`0x39`) | `0x0054F290` | `0x0054F2E0` | allow Comm Sat | `DAT_005E9398` |
| 58 (`0x3A`) | `0x0054F320` | `0x0054F370` | allow Barracks | `DAT_005E939C` |
| 43–52 | `0x0054F3B0` | `0x0054F440` | map name, 10 chars stuffed into high bits | `DAT_00824D18` |
| 17 (`0x11`) | `0x0054F4A0` | `0x0054F4E0` | 16-bit field (player count) | — |

The host writes these from the lobby checkboxes at `0x005687DD` (comm sat) and `0x005688DC`
(barracks). The joining client reads them back with an **inlined** `dpGetSessionDesc` at
`0x00566xxx` (decompiled lines 6032–6055 of `FUN_00562940`), which is why the standalone getters
`0x0054F2E0` / `0x0054F370` show zero callers — they are dead duplicates of inlined code.

Consumption is client-side and shared: `ProducerClass`'s constructor at `0x004773E0` filters the
`buildItem0..8` list, dropping FourCC `BARR` when `DAT_005E939C` is clear and `COMM` when
`DAT_005E9398` is clear, guarded by `0x004B4D60` — a one-liner returning the netcode global
`DAT_00767E8C` (is-network-session; label inferred from the surrounding `0x004B4xxx` net module).

Both globals default to `1` and are reset to `0` on lobby entry (`0x00563B10` region).

`dpSetPlayerData` slots `0x0F`, `0x10`, `0x12`, `0x13` (`0x004B9530`, `0x004B95B0`, `0x004B9630`,
`0x004B96C0`) carry per-player **stats** — kills, deaths, accumulated time, ping — not rules.

### 4.3 The spare bit

`0x0054F200` (set byte 56 bit 0x80) and `0x0054F250` (read it) are **compiled into the shipping
image and referenced by nothing**. The client-side inlined reader skips index 1 of the same array
it uses for bytes 55/57/58. So the slot is:

* already in the 0x5F-byte description every peer already fetches;
* wire-compatible — stock TRO/BZ clients ignore an unknown high bit, and the field's low 7 bits are
  untouched;
* symmetrical with the two rules that already work end-to-end.

That is the cheapest correct carrier for a synchronized `Cloak Disabled` host rule.

---

## 5. What a `Cloak Disabled` host option would take

Ordered by dependency, narrowest first. **This is a new OpenShim-authored rule, not a parity
restore** — the same conclusion the 1.5 pass reached, but with a much better substrate.

1. **Fix the ch01/ch02 latch first** (§2.3). It is a standalone bug, it is one call, and leaving it
   in place will masquerade as a broken new option during testing.
2. **Host UI:** a ninth checkbox in the `multi_three` option column, following the `com_sat` /
   `barrack` construction pattern at `0x00569150`. Label needs an exe literal or a `label.map`
   addition plus a help entry via `0x00598CB0`.
3. **Host publish:** call `0x0054F200(host, disabled)` from the checkbox handler.
4. **Client apply:** extend the inlined session-desc read to index 1 and drive a new global.
5. **Gameplay bind:** the new global must feed `g_CloakEnabled` on **every** peer, not just the
   host — set it in the lobby-apply path where `DAT_005E9398` / `DAT_005E939C` are set. Because the
   capability predicate is inlined at five sites and already reads `g_CloakEnabled`, no gameplay
   code changes at all.
6. **Mid-cloak revocation is already handled:** `UpdateCloak` at `0x0045B885` detects a lost
   capability and forces state 3, so enabling the rule mid-match decloaks gracefully rather than
   freezing craft invisible.

Not required: any change to packet size, opcode set, or object replication — cloak visuals already
ride the alpha channel (§3.3).

---

## 6. Caveat on the BZ 1.5 negative result

The companion 1.5 document rests part of its `Cloak Disabled` negative on "0 occurrences of
`Cloak`/`cloak` in `bzone.exe` strings (≈3.5 MB)". That test is **weaker than it looks** and should
not be re-used as-is.

`BZ1_Source/1.5/Battlezone_Install/bzone.exe` contains essentially **no ODF property-name literals
in plain ASCII**. The probe was re-run against 46 keys **observed in the TRO image** rather than
guessed (an earlier pass included `hoverSpeed`, which turns out not to be a BZ1 key at all and is
absent from TRO too — that pass should be disregarded). Result: **10 of 46 present in 1.5**.

Absent from 1.5 include `classLabel`, `aiName`, `unitName`, `scrapValue`, `scrapCost`, `buildTime`,
`baseName`, `weaponMask`, `collisionRadius`, `heatSignature`, `radarSignature`, `imageSignature`,
`buildItem0` — all of which are unquestionably real BZ1 ODF keys present in every shipped `.odf`.
Present are `nation`, `american`, `soviet`, `alien`, `dropClass`, `dropMat`, `commtower`,
`camerapod`, `abandoned`, `timeDeploy`. The region between `camerapod` (`0x1DC2A8`) and `commtower`
(`0x1DC380`) — which in TRO holds `periodScan`/`rangeScan`/`omegaSpin` — is a table of `.text`
function pointers in 1.5.

So "no cloak strings in the 1.5 exe" is consistent with 1.5 simply not emitting *any* ODF key
literals, and carries little signal either way. The 1.5 conclusion still stands on its **PDB symbol
evidence** (`Craft::cloakState` et al. present as members, no `Net::bCloak` global) and on
`label.map`, which are sound. Only the string-scan leg should be retired.

---

## 7. Address quick reference

| Address | Meaning |
|---|---|
| `0x005E10A4` | `g_CloakEnabled` (byte, init 1) |
| `0x0042B270` | `EnableCloaking(bool)` — sole writer |
| `0x0042B1B0` / `0x0042B1F0` / `0x0042B230` / `0x0042B280` | script API cloak / decloak / is-cloaked / per-object enable |
| `0x0045B520` / `0x0045B5A0` / `0x0045B620` | `Craft::Cloak` / `Decloak` / `ToggleCloak` |
| `0x0045B740` / `0x0045B780` | force cloaked (state 2) / force clear (state 0) |
| `0x0045B790` | `Craft::UpdateCloak` |
| `0x0045BAC0` | craft command dispatch (cloak = command id 7) |
| `0x00457BD0` | `Craft::Save` cloak record |
| `0x0045C0A0`… | class ODF init for the five cloak keys |
| `0x004389C0` | command-menu build (gates Cloak/Decloak entry) |
| `0x004C81A0` | set render-object translucency |
| `0x00599F50` | current game time (float) |
| `0x0054F170`–`0x0054F4E0` | session-description rule setters/getters |
| `0x005BDE1C` / `0x005BDE46` | `dpGetSessionDesc` / `dpSetSessionDesc` thunks |
| `0x00562940` | multiplayer shell page (lobby, options, join-apply) |
| `0x004773E0` | `ProducerClass` ctor — barracks/comm-sat build filter |
| `0x005AE660` / `0x005B0460` | ch01 / ch02 mission update — the `EnableCloaking(false)` callers |

Evidence class for every address above: **proven disassembly** against
`BZ1_Source/TRO1.3/unpacked/odyssey_unpacked.exe`, cross-read in the Ghidra 12.0.4 decompilation.
No live capture was taken; §3.3's remote-object identification is the one inference flagged as such.
