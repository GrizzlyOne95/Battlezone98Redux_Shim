# TRO 1.3 vs BZ 1.4 — what The Red Odyssey actually added to the engine

**Date:** 2026-09-01
**Corpora:** `BZ1_Source/1.4` (5832 fns, Shrinker-unpacked) vs `BZ1_Source/TRO1.3` (6312 fns, UPX-unpacked)
**Tooling / raw output:** `BZ1_Source/diff_14_tro/`
**Companions:** `tro13_cloak_multiplayer_reconstruction_20260831.md`,
`tro13_nation_scriptapi_and_gates_20260831.md`

---

## 0. Headline

**TRO added exactly two gameplay subsystems to the BZ 1.4 engine: Cloak and Portal.**
Everything else that looks like an addition is either content (missions, units, maps, audio) or
branding. A third, smaller change is that TRO extends the stock nation enum from four values to six.

**Portal is new here** — it was not found by the earlier cloak/multiplayer pass and is documented
for the first time in §2.

**Scale context:** 1.4 has 5832 functions and TRO 6312. BZ 1.5, for comparison, has **15 071** — and
Lua (`lua_`, `LUA_`, `Lua 5`) is present in 1.5 and in **neither** 1.4 nor TRO. So the 1.4→TRO step
is a small content-driven delta; the 1.4→1.5 step is the community rewrite, and the two should not
be reasoned about interchangeably.

---

## 1. Method, and a warning about the noisy half of it

### 1.1 Layer 1 — literal-pool set difference (reliable)

Set difference over string literals, with two filters that are **not optional**:

* The 1.4 side is a **runtime dump**, so `.data` carries live heap and `.rsrc` carries resource
  blobs. Both spray thousands of false-positive ASCII runs. Only the compiler literal pools are
  scanned — 1.4 RVA `0x1E6000`–`0x523000`, TRO VA `0x5C5000`–end.
* Literals must be **NUL-terminated**, plus a light junk filter.

Unfiltered this yields "24 805 vs 14 862 strings, 14 315 1.4-only" — pure noise. Filtered it yields
**5923 vs 5282, 4041 shared, 1241 TRO-only, 1882 1.4-only**, which is tractable.

Of the 1241 TRO-only strings, **17 are camelCase identifiers** — i.e. candidate ODF keys, the
signal that matters. The rest are mission-script object names (851), assets (176), mission titles
and Odyssey branding (53).

### 1.2 Layer 2 — function fingerprints (**90 of 118 hits were false positives**)

Addresses cannot be compared across builds, so functions were fingerprinted by the set of string
literals Ghidra shows them referencing (`s_<text>_<addr>` symbols). A TRO function referencing ≥2
literals, none of which appear in the 1.4 decompilation, is a candidate addition. That gave 118.

**Then verify every candidate against the raw 1.4 image bytes.** Ghidra's symbol names are mangled
(spaces and punctuation collapse to `_`) and are not stable between runs, so "token missing from the
1.4 decompilation" does **not** mean "string missing from the 1.4 image". After re-checking each
literal against 1.4's bytes with `_` treated as a wildcard:

| | |
|---|---|
| candidates before verification | 118 |
| survive verification | **28** |
| false positives removed | **90 (76 %)** |

Subsystems that the unverified pass would have reported as TRO additions, and which are **all
present in 1.4**: `special_forces_initialised` / `DefineSpecialForces` / `AI_RegionTweak` (an
apparent "Special Forces AI" — 1.4 `0x2128C4`), the objectives/Notepad system (`0x210018`),
extended joystick axes (`0x20A558`), the audio-config keys `audioMixRate` /
`explosionVolumeFactor` (`0x206190`), `buildStage`, and `Ally with %d` / `UnAlly` (`0x20DEA4`) —
that last one is worth calling out because team alliances would have been a genuinely interesting
multiplayer finding, and it is stock 1.4.

**Do not report a Layer 2 hit without the byte-level verification step.**

### 1.3 Layer 2's blind spot

Of the 28 verified survivors, 24 are TRO mission scripts (`bd01`–`bd15`, `ch04`, `ch08`) and the
rest are Portal plus Odyssey shell/registry branding. **Cloak does not appear at all** — its state
machine references no string literals, so a string-fingerprint method cannot see it.

Layer 2 therefore reports a **floor, not a census**. Layer 1 found both features; Layer 2 found only
Portal. Use them together.

---

## 2. Portal — TRO's second engine feature

Same design as Cloak, evidently written by the same hand.

### 2.1 ODF properties

| Class offset | ODF key | Reader |
|---|---|---|
| `+0x130` | `activationTime` | `0x0046DD30` (float) |
| `+0x134` | `soundActivate` | `0x0046DE50` (string) |

Read in the class constructor **`0x005BDBF0`**; the factory at **`0x005BDCB0`** allocates `0x148`
bytes. Class vtable `PTR_FUN_005D2740`. Two further TRO-only keys, `blobInTexture` and
`blobOutTexture` (referenced at `0x0059E124` / `0x0059E156`), carry the visual.

### 2.2 Instance fields

From the save record at **`0x005BD910`**, which names its own fields exactly as `Craft::Save` does
for cloak:

| Object offset | Field | Serializer |
|---|---|---|
| `+0x234` | `portalBeginTime` | `0x00543790` (float) |
| `+0x238` | `portalEndTime` | `0x00543790` (float) |
| `+0x23C` | `portalState` | `0x005435B0` |
| `+0x240` | `isIn` | `0x00543320` (1 byte) |

The `state / beginTime / endTime` triple is the same transition-machine shape as cloak's
`cloakState` `+0x2B0` / `cloakTransBeginTime` `+0x2B4` / `cloakTransEndTime` `+0x2B8`.

### 2.3 Script API

**`0x0042C5B0` = `IsPortalOpen(Handle)`** — resolves the handle through `ObjectFromHandle`
(`0x00461690`), checks the `0x200` reject flag, returns `portalState == 2`. Structurally identical
to the cloak entries at `0x0042B1B0`–`0x0042B280`, and it sits inside the same script-API block
catalogued in `analysis/script_api_inventory.tsv`.

Note `state == 2` means "fully open", mirroring cloak's `cloakState == 2` meaning "fully cloaked".

### 2.4 No global gate

Unlike cloak, **portal has no `g_PortalEnabled`**. The only absolute global near the portal code is
the `isIn` field-name literal. This independently corroborates §3.4 of the companion doc:
`g_CloakEnabled` at `0x005E10A4` is the *only* script-settable gameplay gate in the image.

Mission evidence that this is a real player-facing mechanic: the TRO mission title
**"Grand Theft Portal"** (`0x005FEDC0`), and portal-referencing mission scripts at `0x005A47C0`,
`0x005A7370`, `0x005A9F90`.

---

## 3. The complete TRO-only ODF key set

All 17 camelCase identifiers TRO adds, and nothing else:

**Cloak (8)** — `cloakAllowed`, `cloakTime`, `forceCloak`, `cloakOnSound`, `cloakOffSound`,
`cloakState`, `cloakTransBeginTime`, `cloakTransEndTime`

**Portal (7)** — `portalState`, `portalBeginTime`, `portalEndTime`, `activationTime`,
`soundActivate`, `blobInTexture`, `blobOutTexture`, `isIn`

**Other (1)** — `lastRecycled` (read at `0x00456594`, alongside the stock `dropClass` / `dropMat`)

---

## 4. What this settles

* **Cloak is TRO-only**, now proven against a real baseline rather than inferred from an unreliable
  1.5 string scan. 1.4 contains no `cloak`, `Cloak`, `Decloak`, `cloakAllowed`, `forceCloak` or
  `cloakState` anywhere.
* **The nation enum is stock 1.4**, extended by TRO — see the companion doc §1.3 for the structural
  proof (identical readers, sentinel `4` vs `6`).
* **Multiplayer host rules are unchanged.** Nothing in the TRO-only string set touches the option
  set, the session description, or the netcode. TRO ships the stock BZ 1.4 eight rules.
* **Team alliances are stock 1.4**, not TRO — retracted before it reached a conclusion, but worth
  recording since it is directly multiplayer-relevant and easy to re-misattribute.

## 5. Open

* `Schedule_Ai.cpp` and `RecycleTask::curState` are the only two non-portal literals that survive
  verification as TRO-only and are *not* obviously content or branding. Both are probably path- or
  build-string differences rather than features; neither has been chased.
* Layer 2 cannot see string-free code. A structural diff (BSim — the repo already carries scripts
  under `reverse_engineering/bsim/`) would close that gap and is the natural next step if a complete
  census is ever needed.
