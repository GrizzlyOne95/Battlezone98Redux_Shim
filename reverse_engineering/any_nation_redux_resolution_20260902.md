# Any Nation / All Nations — resolution against Redux 2.2.301

**Date:** 2026-09-02
**Verdict:** **ROOT PATH PROVEN — IMPLEMENTED (restrictive half), NOT RUNTIME-QUALIFIED.**

Redux 2.2.301 already ships a superset of the *permissive* side of Battlezone 1.5 `Any Nation`,
permanently enabled, as a per-player **Faction** selector on the multiplayer vehicle-select screen. So
"restore cross-faction selection" needs no patch — it is already there.

What Redux lost is the **other half**: 1.5's `netveh.odf` (Any Nation **OFF**) was the *restricted* pool,
and Redux deleted the ability to ask for it. That is the half with real use — a host running a stock DM
map wants the balanced stock factions, not whatever the merged pool happens to contain. §8 implements it
as `[Network] StockFactionsOnly`, default off, local-only.

This document supersedes `mp_allnations_cloakdisabled_15_reconstruction_20260831.md` §5/§6/§16 (the
`SimpleVehicleList` / `bNations` restoration plan) and the scratch stub
`src/patches/all_nations_restore.cpp`, which has been removed.

**Corpus:** GOG `battlezone98redux.exe` `8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413`
(5 425 152 B, ImageBase `0x400000`) — all disassembly below was read **directly from the shipped binary**,
not from the corpus decompile. 1.5 side: `bzone.exe` 1.5.2.27 U1 + exact-match `bzint.pdb` decompile.

---

## 1. Two premises in the task brief are factually wrong

### 1.1 "Any Nation allowed NSDF and CCA only"

Measured from the shipped 1.5 stock data files
(`BZ1_Source/1.5/Battlezone_Install/stock/`):

| File | Used when | `a` NSDF | `s` CCA | `b` Black Dog | `c` CRA | total |
|---|---|---|---|---|---|---|
| `netveh.odf`  | Any Nation **OFF** | 13 | 9 | **5** | 0 | 27 |
| `netveh1.odf` | Any Nation **ON**  | 13 | 9 | **8** | **13** | 43 |

`netveh1.odf` is a strict superset — nothing is removed. Enabling Any Nation **added 13 CRA craft and 3
Black Dog craft**. NSDF, CCA *and* Black Dog were all selectable with the option **off**.

This matches the 1.5 help string exactly: `multi_help/nation` = **"Enable extra nations"**. The *extra*
nation is CRA.

So the requested policy — "Any Nation ON ⇒ NSDF+CCA only; Black Dog and CRA must not be added" — is the
inverse of what 1.5 did. Implementing it would have *removed* Black Dog (available in stock 1.5 with the
option off) and excluded CRA (the entire point of the option).

### 1.2 "There is a nation-equality filter to bypass"

There is no per-candidate nation comparison in 1.5 at all. The whole policy is a filename swap.

---

## 2. The exact 1.5 deciding code

`SimpleVehicleList::SimpleVehicleList` @ **`0x00556A2A`** (symbol from exact-match `bzint.pdb`):

```c
SimpleVehicleList * __thiscall SimpleVehicleList::SimpleVehicleList(SimpleVehicleList *this)
{
  this->s = (_s *)0x0;
  this->count = 0;
  if (Net::bNations != false) {
    if (ItemExists("netveh1.odf")) { pcVar2 = "netveh1.odf"; goto LAB_00556a55; }
  }
  pcVar2 = "netveh.odf";
LAB_00556a55:
  Load(this,pcVar2);
  return this;
}
```

Both literals are present in the 1.5 image at adjacent offsets `0x001EDDF4` (`netveh.odf`) and
`0x001EDE00` (`netveh1.odf`).

**Answer to "what makes a vehicle part of the 1.5 Any Nation pool?"** — being a line in the stock
`netveh1.odf` text file. Pure data. No nation ID, no class metadata, no prefix test.

---

## 3. What Redux did instead

### 3.1 The data was merged

Redux ships **one** list, `StockODFFiles/netveh.odf`, with **43 entries: a=12, s=8, b=9, c=14** — i.e. the
1.5 `netveh1.odf` (all-nations) content, with four minor swaps (`avtam2`/`svtamp`/`cvwalk`/`cvrmpa` out;
`bsuser`/`cvrckt`/`cvtnk`/`cvwamp` in).

String scan of the shipped Redux exe:

| String | 1.5 | Redux |
|---|---|---|
| `netveh.odf` | `0x001EDDF4` | `0x00473AD0` |
| `netveh1.odf` | `0x001EDE00` | **absent** |
| `Any Nation` | `0x001EEFC0` | **absent** |
| `Enable extra nations` | `0x001EE8E4` | **absent** |

The two-file toggle is gone because there is only one file.

### 3.2 The list class became nation-partitioned

Global singleton **`DAT_0094548C`** (returned by `FUN_00764780`). Layout, recovered from the accessors:

| Offset | Field |
|---|---|
| `+0x00 .. +0x3B` | **five `std::vector`**, 12 B each — one bucket per nation, elements 0x60 B |
| `+0x3C` | current selection index within the active bucket |
| `+0x40 .. +0x57` | loaded filename (`std::string`) |
| `+0x58 / +0x5C` | source-file timestamp (cache validity) |
| `+0x60` | **current nation index** |

`FUN_00766F80` is `size()`: `return (v[1] - v[0]) / 0x60;` — confirming 0x60-byte elements.

**Loader `FUN_00766900(filename)`.** Per parsed line it reads the first character of the ODF name and maps
it to a nation index, then push_backs into `this + nation*0xC` **unconditionally**. Verified from the
shipped binary:

```
00766c93  e898020000  call 0x766f30            ; -> char* odf name
00766c98  8a10        mov  dl, byte ptr [eax]  ; first character
00766cb3  83e961      sub  ecx, 0x61           ; -= 'a'
00766cbc  83bd3cffffff12  cmp dword [ebp-0xc4], 0x12
00766cc3  7744        ja   0x766d09            ; -> default (4)
00766ccb  0fb682506e7600  movzx eax, byte [edx + 0x766e50]   ; byte map
00766cd2  ff24853c6e7600  jmp  dword [eax*4 + 0x766e3c]      ; jump table
   'a' -> 0 (NSDF)   's' -> 1 (CCA)   'b' -> 2 (Black Dog)   'c' -> 3 (CRA)   else -> 4 (Other)

00766d13  8b8d5cffffff  mov edx,[ebp-0xa4]     ; this
00766d19  8b5160        mov edx,[ecx+0x60]     ; this->currentNation
00766d1c  3b9558ffffff  cmp edx,[ebp-0xa8]     ; vs candidate nation
00766d22  7535          jne 0x766d59           ; <-- SKIPS ONLY THE SELECTION RESTORE
00766d2f  e8dc05ccff    call 0x427310          ;   string compare vs saved selection
00766d56  89413c        mov [ecx+0x3c], eax    ;   this->selIndex = size(bucket)

00766d60  6b8d58ffffff0c  imul ecx,[ebp-0xa8],0xc   ; nation * 12
00766d67  038d5cffffff    add  ecx,[ebp-0xa4]       ; + this
00766d6d  e84e020000      call 0x766fc0             ; push_back  <-- UNCONDITIONAL
```

**This is the single most important correction.** The `cmp/jne` at `0x00766D1C` looks like a nation filter
in the Ghidra output, but the disassembly shows it guards **only the restoration of the saved selection
index**. Membership is never filtered — every entry is stored in its own nation's bucket.

The "filter" is therefore architectural, not a branch: the UI displays `buckets[this->+0x60]`.

### 3.3 …and Redux added a Faction selector to drive it

| RVA | Role |
|---|---|
| `FUN_007667C0` | **Next Nation** — cycles `+0x60` 0→1→2→3→4→0, skipping empty buckets |
| `FUN_00766860` | **Prev Nation** |
| `FUN_00766710` / `FUN_00766770` | Next / Prev vehicle within the active bucket |
| `FUN_00766410` | SetNation + select-by-name (applies `multi.ini` `multi/faction` + `multi/vehicle`) |
| `FUN_00766560` | find-by-name **across all five buckets** — downstream resolution is nation-agnostic |

`FUN_007A9590` = **`cUI_Multiplayer_VehicleSelect`** ctor. It creates, in one straight-line block whose
only conditionals are `operator new == NULL` checks:

`VehicleSelectName`, `VehicleSelectPageLeft/Right`, **`Faction`**, **`FactionSelectPageLeft/Right`**,
`VehiclePreview`.

The faction arrows are wired through thunks `0x007A9430` / `0x007A9440`, which load the screen singleton
`DAT_00945598` and call `FUN_007AA4E0` / `FUN_007AA520`.

**The gate is not a nation restriction.** Both faction handlers test
`screen->+0x1C -> +0x50 == 4` — and so do the *vehicle* handlers `FUN_007AA460` / `FUN_007AA4A0`,
byte-for-byte:

```
007aa4ac  8b481c   mov ecx,[eax+0x1c]     007aa52c  8b481c   mov ecx,[eax+0x1c]
007aa4af  e89c1bf2ff call 0x6cc050        007aa52f  e81c1bf2ff call 0x6cc050
007aa4b7  837df804 cmp dword [ebp-8], 4   007aa537  837df804 cmp dword [ebp-8], 4
007aa4bb  751d     jne (skip)             007aa53b  7516     jne (skip)
   -> FUN_00766710 (next vehicle)            -> FUN_007667c0 (next nation)
```

It is a shared screen-state check. (`FUN_006CC050` is a folded generic `return *(this+0x50)` accessor —
its other 20-odd call sites are unrelated boilerplate. Cf. `unique-byte-signature-is-not-function-identity`.)

### 3.4 The feature is finished and localized

`localization_table.csv`, shipped in the game root, has one fully-translated row per bucket:

```
faction:usa        NSDF
faction:ussr       CCA
faction:blackdogs  Black Dog / Chien Noir / Dobermann / ...
faction:chinese    CRA
faction:other      Other / Autres / Andere / ...
```

Five factions, seven languages, matching indices 0–4 exactly. `FUN_007A9EA0` selects among them by
`+0x60`. **There is no `anynation` row** — consistent with the removed button label.

---

## 4. The dormant `AnyNationButton` is genuinely dead, and correctly so

Prior research's chain is confirmed. In `FUN_00796880` (`cUI_Multiplayer_Create`):

```c
local_12c = FUN_007c3e30("AnyNationButton", ..., FUN_00795d70);   // empty label string
param_1[0x68] = local_12c;
(**(code **)(*(int *)param_1[0x68] + 0x24))();                    // Hide()
```

* Constructed with an **empty label** (contrast `basic_string<>("Sniper")` for `SniperButton`).
* Immediately **hidden** — `vtable+0x24` is `Hide()`, used conditionally at line 176 as
  `if (!netService->IsHost()) Hide(param_1[0x58])`.
* Callback `FUN_00795D70` → `FUN_00417C60`, which is a **confirmed nullsub**:
  `push ebp; mov ebp,esp; push ecx; mov [ebp-4],ecx; mov esp,ebp; pop ebp; ret`.

Four setting buttons are hidden unconditionally: `TeamButton` `[0x62]`, `PlayerLivesButton` `[0x66]`,
`AnyNationButton` `[0x68]`, `SplinterButton` `[0x6B]`. **Only Any Nation's handler is a nullsub** —
Team / Lives / Splinter all retain live handlers (`FUN_0079B850`, …, `FUN_00795EF0`) and are merely hidden.

Redux did not "lose" Any Nation. It **deleted the rule logic on purpose**, because the always-available
Faction selector supersedes it.

---

## 5. Host authority

Unchanged and still intact:

* `FUN_007A3E60` builds `<mission>.vxt` from the mission name and loads it — this is the **map/host-provided
  starting-vehicle pool**.
* `FUN_00766900` falls back to `netveh.odf` only when that file is absent (`FUN_00481F10` existence test).
* The nation partition is computed *from whatever that pool contains*. Faction cycling can never introduce
  a craft the pool did not list, because buckets are populated exclusively from parsed pool lines.

A `.vxt` that omits a craft keeps it unavailable in every faction. Nothing here needed changing.

---

## 6. Which half needs building

| Direction | Redux state | Action |
|---|---|---|
| Cross-faction selection **available** (1.5 "Any Nation ON") | Already the shipped default, via the Faction arrows | none needed |
| Pool **restricted** to the balanced stock factions (1.5 "Any Nation OFF") | **Gone.** Redux deleted the toggle and the rule logic | implemented, §8 |
| Host pool stays authoritative | Already true (`.vxt` → buckets) | preserved |
| Don't expose arbitrary ODFs | Already true (buckets only hold parsed pool lines) | preserved |

Restoring the hidden `AnyNationButton` itself is still not worth doing — its handler is a nullsub, its
label string is gone, and it would be a host-lobby control for a rule that cannot be enforced on clients
(§8). The rule is exposed as an OpenShim setting instead.

---

## 7. Runtime qualification — not performed, and why

The Windows session was **disconnected** (`query session` → `iestu … Disc`) for the whole pass, so there
was no live desktop to render or drive the shell in. Per `locked-session-defeats-live-validation`, a run
under those conditions measures nothing. No runtime claim is made here.

Everything above is read from the **shipped GOG binary and shipped data files**, not from an advisory PDB
or a corpus decompile, so the static chain is solid; but the two on-screen facts below are still unverified
by observation.

### Runbook (≈3 minutes at a connected console)

`Ogre.cfg` already has `Full Screen=No` (required — see `fullscreen-dxgi-defeats-screen-capture`).

1. Launch Redux → **Multiplayer** → create or join a room.
2. On the vehicle-select panel, confirm a **`Faction`** label with **left/right arrows** beside the
   vehicle arrows.
3. Cycle faction: expect **NSDF → CCA → Black Dog → CRA** (and `Other` only if the pool contains ODFs
   whose name starts with something other than `a`/`s`/`b`/`c`). Empty buckets are skipped automatically.
4. Pick a craft from a faction opposite your team, launch, and confirm you spawn in it with your own team
   colour and team number unchanged (nation and team are independent — `+0x60` is list state only, never
   written to team state).
5. Host authority: edit the mission's `.vxt` to drop one craft, relaunch, confirm it is absent from every
   faction.

If step 2 fails, the only remaining suspect is the shared screen-state gate `screen->+0x1C -> +0x50 == 4`
— and because the vehicle arrows share it byte-for-byte, a failure there would disable vehicle selection
too, which would be an obvious and separate bug.

---

## 8. Implementation — `[Network] StockFactionsOnly`

### What ships

| File | Change |
|---|---|
| `include/mp_faction_restrict.h` | Nation enum (matching the engine's own 0–4 bucket indices) and the install entry point |
| `src/patches/mp_faction_restrict.cpp` | The hook, the pruning pass, and the identity checks |
| `scripts/patches.json` | Two new resolves for the loader call sites |
| `src/patches/openshim_env_config.cpp` | `OPENSHIM_STOCK_FACTIONS_ONLY` / `OPENSHIM_STOCK_FACTION_SET` → `[Network]` keys |
| `openshim.ini.example` | Documented `StockFactionsOnly` and `StockFactionSet` |
| `src/patches/bzr_options_ui.cpp` | One settings row, "Stock Factions", `defaultIndex` 1 = the absent-key behaviour |
| `src/dllmain.cpp`, `BZROpenShim.vcxproj` | Install after `RunPatcher`; build wiring |

### Where it hooks, and why there

`FUN_00766900` has exactly two callers in the image, so its two `call rel32` operands are rewritten to an
interceptor that calls the original and then prunes. No trampoline, no byte relocation, and no path other
than multiplayer starting-vehicle list construction can be affected.

| Resolve | Address | Anchored on |
|---|---|---|
| `MPVehicleList::LoadCallSiteNetveh` | `0x00798BE1` | the CALL, plus the preceding `mov byte [ebp-4],0x22` / `lea ecx / push ecx` / `call FUN_00764780` / `mov ecx,eax` |
| `MPVehicleList::LoadCallSiteMission` | `0x007A3EDF` | the CALL, plus the trailing `mov edx,[ebp-0x2C] / mov dword [edx+0x38],-1` |

Both verified against the shipped exe: **1 match each, landing exactly on the fallback**.

Identity is not taken from the signatures alone — at install time both sites must resolve to *one and the
same* loader, or the hook stands down.

### The one address that is NOT pattern-scanned

The bucket `clear` (`0x007670D0`) is a `std::vector<T>::clear` template instantiation. With its import and
call operands wildcarded, its body matches **16 unrelated addresses** in this image — a signature scan
cannot establish identity (cf. `unique-byte-signature-is-not-function-identity`,
`bsim-matches-boilerplate-across-unrelated-functions`). It is therefore derived from the *verified* loader
via the call in its own bucket-reset loop (`loader + 0x158`), and then confirmed by checking 39 body bytes
with the two operand fields skipped. Anything else fails closed.

Pruning calls that engine function rather than resetting `end = begin` by hand, because the 0x60-byte
entries own heap strings and must have their destructors run.

### Semantics

```
allowed = hostPoolProvidedIt        // <mission>.vxt, else netveh.odf — unchanged
          AND ( !StockFactionsOnly
                OR nationOf(candidate) ∈ StockFactionSet )
```

`StockFactionSet` defaults to `as` (NSDF + CCA). `asb` reproduces the 1.5 `netveh.odf` pool exactly,
Black Dog included.

Safety properties, all deliberate:

* **Only ever subtracts.** It cannot add a craft, expose an arbitrary ODF, or reach content the pool did
  not list.
* **Empty-result guard.** If the pool contains nothing from the allowed set, nothing is pruned and the
  full pool stands — a map that ships only Black Dog craft stays playable.
* **Selection repair.** `+0x60` is reseeded to the first allowed non-empty bucket and `+0x3C` reset when
  the active faction was one that got pruned (it is seeded from `multi.ini multi/faction`).
* **Cache invalidation.** The loader early-outs when the same file and timestamp are already loaded, so a
  changed setting zeroes `+0x58/+0x5C` first, forcing a genuine rebuild.
* **Layout validation.** Any bucket whose span is not a multiple of `0x60` aborts the whole pass.
* **Nation is list state only.** `+0x60` is never written to team state, so team ownership, nation
  assignment, ODF resolution, producer/build menus, AI production and physics are untouched.

### Not synchronized — say so plainly

Each client builds this list locally from its own copy of the same map files. Nothing here goes over the
wire. With a stock client, or an OpenShim client with the setting off, that client still sees the full
pool. This is a **reference implementation and a matched-mod convenience, not enforcement**, and the INI
comment says exactly that.

Making it authoritative would need the host's rule to reach clients. The 1.5 channel was
`Net::bNations` in the `dpSetPlayerData` slot `0x0C` blob at byte `0x11`; Redux is on BZRNet/Galaxy with
named room key-values instead (`FUN_0079C620` writes `"sniper"` through `FUN_0056F900` →
`FUN_0079B880`), which unknown-key-tolerant clients ignore. That is the path if this is ever promoted —
it is out of scope here and unproven.

### Expected effect on the shipped pool

Redux `StockODFFiles/netveh.odf` classifies as NSDF 12, CCA 8, Black Dog 9, CRA 14, Other 0.

| Setting | Kept | Pruned |
|---|---|---|
| `StockFactionsOnly = 0` (default) | 43 | 0 |
| `= 1`, set `as` | 20 | 23 |
| `= 1`, set `asb` (1.5-exact) | 29 | 14 |

### Verification performed

* Release build clean (`winmm.dll`).
* `resolve_table_tests` — all checks passed, including the shipped-`patches.json` schema and identity-note
  requirements.
* Both new resolves re-verified against the shipped exe: unique match on the expected address.
* Pruning arithmetic simulated against the real shipped `netveh.odf`.

**Not performed: any runtime test.** See §7 — the session was disconnected throughout. The qualification
matrix below has not been executed.

### Qualification runbook

Set `[Network] StockFactionsOnly = 1`, then at a connected console:

| Case | Expected |
|---|---|
| OFF (default) | Faction arrows cycle NSDF → CCA → Black Dog → CRA exactly as stock |
| ON, stock map | Only NSDF and CCA reachable; `[FACTION] pruned 23 craft ... ` in the log |
| ON, select a CCA craft while on the NSDF side | Selects, survives ready/launch, spawns correctly, team unchanged |
| ON, `StockFactionSet = asb` | Black Dog reachable again, CRA still not |
| Host authority | Drop a craft from the map's `.vxt`; it stays gone in every faction, both settings |
| Empty-set guard | A `.vxt` with only Black Dog craft ⇒ nothing pruned, log says so |
