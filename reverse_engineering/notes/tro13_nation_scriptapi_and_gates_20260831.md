# TRO 1.3 — Nation Model, Mission-Script API, and Engine Gate Sweep

**Date:** 2026-08-31
**Target:** `BZ1_Source/TRO1.3/unpacked/odyssey_unpacked.exe` (see that tree's `README.md` for provenance)
**Companions:** `tro13_cloak_multiplayer_reconstruction_20260831.md`,
`mp_allnations_cloakdisabled_15_reconstruction_20260831.md`

Three follow-ups to the cloak/multiplayer pass, written so a later agent can pick any one up cold.

---

## 1. The nation model — substrate for the `All Nations` task

The 1.5 reconstruction recovered the **host rule** (`Net::bNations`) but never the **object side**
it gates. TRO carries that side in readable form.

### 1.1 The enum

Name table at **`0x005E1CD0`**, six entries, index is the stored value:

| # | String | VA |
|---|---|---|
| 0 | `unknown` | `0x005E1D18` |
| 1 | `american` | `0x005E1D0C` |
| 2 | `soviet` | `0x005E1D04` |
| 3 | `alien` | `0x005E1CFC` |
| 4 | `chinese` | `0x005E1CF4` |
| 5 | `blackdog` | `0x005E1CE8` |

### 1.2 Where it lives and how it is resolved

`GameObjectClass` field **`+0xAC`** (`param_1[0x2B]` in the decompilation), set in the class ODF
reader at **`0x00465CD0`**; the `nation` key literal is at `0x005E1D78`, read at `0x004660F5`.

Resolution is three-stage:

1. **Default inferred from the first letter of the ODF/class name** — a `switch` at
   `0x00466083`:
   * `A`/`a` → 1 `american`
   * `S`/`s` → 2 `soviet`
   * `H`/`h`, `O`/`o` → 3 `alien`
   * `P`/`p` → falls through to `american`, **unless** the name is literally `player.odf`
     (`0x005E1D80`), which takes the default case
2. **ODF override** — `GetLabel("nation", buf, <default name from the table>)`
3. **Name mapped back to an index** by linear search over the table; **a miss yields index 6, which
   is then forced to 0 (`unknown`)**. So an unrecognised `nation =` value silently becomes
   `unknown` rather than erroring.

A diagnostic string `User got into vehicle with unknown nation` (`0x005DED38`) exists for the
index-0 case, which is a useful runtime tripwire.

### 1.3 Where the enum came from — and what 1.5 has

**BZ 1.4 already had it.** With a real 1.4 baseline now available (see §4), the table is at
**VA `0x00607110`** with **four** entries in exactly TRO's order:

```
0x00607110:  3C 71 60 00   30 71 60 00   28 71 60 00   20 71 60 00
             ->"unknown"   ->"american"  ->"soviet"    ->"alien"
```

So the nation mechanism is **stock BZ 1.4**, and **TRO extended the table from four values to six**
by appending `chinese` (4) and `blackdog` (5). Neither string exists anywhere in the 1.4 image.

The 1.4 decompilation makes this structural rather than circumstantial. `FUN_0049D7A0` is the same
class ODF reader as TRO's `0x00465CD0` — same class field `param_1[0x2b]` (`+0xAC`), same
default-from-first-letter switch, same `GetLabel("nation", …)` override, same linear search back
through the name table. The **only** difference is the not-found sentinel:

```
1.4  FUN_0049D7A0:   if (iVar13   == 4) iVar13   = 0;   // table 0x00607110, 4 entries
TRO  0x00465CD0:     if (local_14 == 6) local_14 = 0;   // table 0x005E1CD0, 6 entries
```

TRO did not add a nation system; it appended two values to a stock one.

**1.5 cannot be read off strings — do not try.** `american`, `alien`, `chinese` and `blackdog` do
not appear as null-terminated strings in the 1.5 exe at all, and its single `soviet` occurrence
(file `0x1ECF38`) sits inside a command-line/console token list
(`…net, netshell, soviet`), not a nation table. That is the string-scan caveat in the companion doc
biting again. **Determine 1.5's table from `bzint.pdb` symbols or the 1.5 decompile corpus, not
from strings.**

### 1.4 Why this matters

An `All Nations` restoration needs to know what "a nation" *is* at the object level: the field
offset, the enum, and the fact that the default is derived from a filename convention rather than
stored. TRO gives all three in one function. The first-letter inference in particular means any
new craft added by a mod inherits a nation from its filename — worth knowing before assuming the
ODF key is authoritative.

---

## 2. The mission-script API block

**Range `0x00428000`–`0x0042D000`. 155 functions, 93 of which resolve an object handle** through
`0x00461690`. This is TRO's `ScriptUtils` surface — the same family BZ1/BZ2 expose to mission DLLs.

Machine-readable inventory: **`BZ1_Source/TRO1.3/analysis/script_api_inventory.tsv`**, regenerate
with `python tools/script_api_inventory.py`. Columns: entry address, byte size, `ret N` arg bytes,
whether it resolves a handle, globals written, globals read, non-block call targets, string
literals referenced.

### 2.1 Calling convention — read this before inferring signatures

**147 of the 155 end in a bare `ret`; only 7 use `ret N`.** The API is `__cdecl` (caller-cleans),
as you would expect for an `extern "C"` DLL-facing surface. **Argument counts therefore cannot be
read off `ret N`** — the `arg_bytes`/`args` columns in the TSV are empty for almost every row by
design, not by failure. Take signatures from the Ghidra decompilation
(`ghidra/decomps/.../FUN_0042xxxx-*.c`), which infers them from call sites.

### 2.2 Shape of a wrapper

Nearly every handle-taking entry follows one template:

```c
void API_Something(Handle h, ...) {
    Object *o = ObjectFromHandle(h);              /* 0x00461690 */
    if (o && !(o->renderObj->flags & 0x200))      /* 0x200 == rejected/dead */
        o->DoSomething(...);
}
```

so an unnamed function can usually be identified from the single engine method it tails into.
The five cloak entries documented in the companion doc (`0x0042B1B0`, `0x0042B1F0`, `0x0042B230`,
`0x0042B270`, `0x0042B280`) are exactly this shape.

### 2.3 Named anchors found so far

| Address | Identification | Evidence |
|---|---|---|
| `0x00461690` | `ObjectFromHandle` | 426 call sites, all handle-shaped |
| `0x0042B1B0` / `0x0042B1F0` / `0x0042B230` | cloak / decloak / is-cloaked | companion doc |
| `0x0042B270` | `EnableCloaking(bool)` | sole writer of `g_CloakEnabled` |
| `0x0042B280` | per-object cloak enable | writes `obj+0x2A5` |
| `0x00428C40` / `0x00428C80` | add / remove object from the `0x006CC748` list, setting `obj+0x17C` | see §3.3 |
| `0x004280B0` / `0x00428140` | camera-FSM save / restore | field names in §3.2 |
| `0x0042ACF0` / `0x0042AF60` / `0x0042AFC0` | camera begin / finish / cancel | `CameraCancelled_called_outside_c…` at `0x005DEF1C` |

**Suggested next step:** the block is contiguous and uniform, so a pass that (a) pulls Ghidra's
inferred signature, (b) resolves the single tail-called engine method, and (c) matches against the
publicly documented BZ1/BZ2 `ScriptUtils` name list would name most of the 155 mechanically. The
TSV is laid out to feed exactly that.

---

## 3. Gate sweep — is there another `g_CloakEnabled`?

**Short answer: no. Cloak is the only feature gate in the script API.** This is a deliberate
negative result; it closes the question rather than leaving it open.

### 3.1 Method

`g_CloakEnabled` was found because a script wrapper wrote a bare absolute global. Generalising:
sweep `0x00428000`–`0x0042D000` for `mov [abs32], reg/imm` where the destination is a global. That
yields **15 global-writing functions** touching **~20 distinct globals** — reproduce with the
scanner in `BZ1_Source/TRO1.3/tools/scan_field_refs.py`.

### 3.2 What the writes actually are

Thirteen of the fifteen are one subsystem: the **cinematic / camera FSM**, plus difficulty. The
save/restore pair at `0x004280B0` / `0x00428140` names its own fields — the same
"save-record literals give you the layout" trick that pinned the cloak offsets:

| Global | Identification |
|---|---|
| `0x0061A99C` | `cameraReady` (byte) |
| `0x0061AA44` | camera-active latch (byte) |
| `0x0061AA28` | camera stack index, init `0xFFFFFFFF` |
| `0x0061A9A0` | camera stack, 5 dwords (0x14 bytes) per entry, indexed by `0x0061AA28` |
| `0x0061AA08`–`0x0061AA40` | camera path/interpolation state (block-initialised at `0x00429D70`) |
| `0x0061AA48` | camera call result / current op |
| `0x0061A998` | `difficultySetting` (compared against `_DAT_005C8CA0`) |
| `0x008244E8` | master disable guarding the whole FSM |
| `0x0061AA4C` | current script object handle (flag-`0x200` checked at `0x00428330`) |

Save-record field names observed: `aip_name`, `cameraCallCount`, `cameraReady`,
`difficultySetting`. Diagnostic strings: `fsm_pop_camera_called_again` (`0x005DEE88`),
`CameraCancelled_called_outside_c…` (`0x005DEF1C`).

### 3.3 The two non-camera globals

* **`0x006CC7D4`** — count of an object array at **`0x006CC748`**. `0x00428C40` appends an object
  and sets `obj+0x17C = 1`; `0x00428C80` removes it and clears the flag. Read by Craft
  (`0x0045B060`), `0x00461E90`, `0x004636A0`, `0x004703E0`, `0x004706A0`, `0x004942D0`,
  `0x004ADA00`. *Inference:* the objective-marker set (`SetObjectiveOn`/`SetObjectiveOff`), with
  `obj+0x17C` as the per-object "is objective" flag. Not verified.
* **`0x006D8A00`** — a word inside the HUD / command-menu state block spanning roughly
  `0x006D8A00`–`0x006D8A32`; zeroed by camera cancel, read by the command-menu builder
  `0x004389C0` (which also reads bytes `0x006D8A2B`, `0x006D8A2C`, `0x006D8A2D`, `0x006D8A2E`,
  `0x006D8A32`).

### 3.4 Conclusion

`0x005E10A4` (`g_CloakEnabled`) is the **only** script-settable global that gates a gameplay
capability. Everything else in the block is transient camera/HUD/objective state that is either
re-initialised per mission or saved and restored. So the "mission turns a feature off and never
turns it back on" bug documented in the companion doc is a **one-off, not a pattern** — worth
fixing, not worth building a general guard for.

---

## 4. The BZ 1.4 baseline — now available

`BZ1_Source/decomp1.4` is **not** a usable baseline: 805 KB of decompiled C over 693 files with
only 323 distinct string literals, focused on AI/collision. Fine for what it was made for, useless
for "did 1.4 have feature X".

A real 1.4 install was located and unpacked. Artifacts in **`BZ1_Source/1.4/`**:
`bzone_shipped.exe` (3 046 300 B, 2008-11-02, from a 1.4 patch installer),
`unpacked/bz14_image_dump.bin`, `unpacked/bzone14_unpacked.exe`, plus `label.map`, `Input.map`,
`patch.txt`, `update.txt`.

### 4.1 The container

Genuine **Shrinker over LZO** — the real thing, not TRO's inherited banner. `.text` `VirtualSize
0x1E4800` against `SizeOfRawData 0xA00`; `.data` with `PointerToRawData = 0`; entry `0x00401000`
into a stub at `0x004010AA` whose API names are NOT-encoded (`kernel32` at file `0x4D2`); an
`LZO real-time data compression library` banner at file `0xD203`. Original section names, headers
and the full 16-DLL import table are preserved — Shrinker's signature.

Overlay at file `0x11B000`, mapped as far as:

| Offset | Content |
|---|---|
| `+0x000` | header: version `1`, header size `0x110`, block size `0x20000`, then the original build path `..\debug\bzone.exe` |
| `+0x110` | **function table, 7090 entries × 16 bytes**: `(RVA, length, ?, flags)`, sorted ascending, covering RVA `0x1000`–`0x1DDDA1` and summing to `0x18EBD9` bytes of code |
| `0x136C30` | CodeView `NB10` record — original PDB path **`D:\Badlands\source\Release\bzone.pdb`** |
| `0x136E00` | payload header: magic `0x04181996`, section count, `.text`/`.data` characteristics (`0x60000020`, `0xC0000040`), `.text` VirtualSize `0x1E4800` |
| `0x136E24` | compressed payload to EOF |

### 4.2 How it was unpacked — runtime dump, not a static crack

Statically cracking the container was not necessary. The stub's decoded import set is
`CreateFileA`, `CreateFileMappingA`, `MapViewOfFile`, `UnmapViewOfFile`, `CloseHandle`,
`GetModuleFileNameA`, `GetModuleHandleA`, `GlobalAlloc`, `GlobalFree`, `VirtualProtect`,
`MessageBoxA` — **no exception-handler registration at all**, so there is no page-fault
decompression to defeat a dump. It maps its own file, allocates, decompresses and jumps.

`tools/dump_running_image.py` starts the process, waits, snapshots `0x400000`–`0x628000` and kills
it. Three things that cost time and are worth knowing:

1. **The exe alone will not start.** It needs its shipped, non-system DLLs beside it — `ANET2.DLL`,
   `STRLKUP.DLL`, `MSVCP50.DLL`, `MSVCRT.DLL` (plus `DKUPDDLL.DLL`, `dxver.dll`, `getinfo.dll`,
   `sysinv.dll`). Without them the process dies with `0xC0000135` STATUS_DLL_NOT_FOUND *before the
   entry point*, and a naive dump reads nothing.
2. **Under WOW64 a breakpoint arrives as `0x4000001F`** (STATUS_WX86_BREAKPOINT), not
   `0x80000003`, and there are **two** loader breakpoints (64-bit then 32-bit ntdll). Passing
   either back as `DBG_EXCEPTION_NOT_HANDLED` kills the process. `tools/dump_at_oep.py` records
   this; it is retained for reference but is not the tool that worked.
3. Missing game data is fine — the stub finishes long before the game looks for `.zfs` files.

`tools/rebuild_bz14_pe.py` then makes the on-disk layout match memory (FileAlignment ==
SectionAlignment == `0x1000`, `PointerToRawData == VirtualAddress`), drops relocations and marks
sections RWX. Result: **`unpacked/bzone14_unpacked.exe`, 6 455 296 B, 16 DLLs / 336 imports parsing
clean** (TRO has 339 — same engine family).

`tools/lzo1x.py` is a pure-Python LZO1X decompressor written during the static attempt. It is
**unvalidated** — it was never needed and never confirmed against a known stream. Do not trust it
without testing.

### 4.3 Validation

* `.text` entropy **6.61** against the TRO control's **6.67**; `E8` density 35 145 vs 32 980.
* Sampled functions from the table disassemble as clean, sensible x86 (`thiscall` methods with
  `mov esi, ecx`, FPU field loads, coherent control flow).
* 63.6 % of the 7090 table entries end on a `ret`/`jmp`/`nop` byte.
* Every ODF key literal that is absent from the 1.5 exe is **present** here — `classLabel`,
  `aiName`, `unitName`, `scrapValue`, `buildTime`, `heatSignature`, `collisionRadius`,
  `buildItem0`, `weaponMask`, `omegaSpin`, `velocJam`, `hardpoint`.
* Note `55 8B EC` appears only 173 times vs TRO's 5158 — **1.4 omits frame pointers**. That is a
  compiler-flag difference, not a bad dump; do not use prologue counts as a health check here.

### 4.4 First result from the baseline

**BZ 1.4 contains no cloak whatsoever** — `cloak`, `Cloak`, `Decloak`, `cloakAllowed`,
`forceCloak`, `cloakState` are all absent from the fully decompressed image. Cloak is entirely
TRO's addition to the engine, now established against a real baseline rather than inferred.

---

## 5. Tooling added

In `BZ1_Source/TRO1.3/tools/`:

| Script | Purpose |
|---|---|
| `scan_field_refs.py` | resyncing linear sweep; `sweep(lo, hi)` yields capstone instructions across data gaps |
| `xref_index.py` | direct call/jmp target index, cached to `xrefs.pkl` |
| `strxref.py` | string-literal reference index plus `cstr(va)`; `s:<text>` lookup by content |
| `script_api_inventory.py` | emits `analysis/script_api_inventory.tsv` |

The `.pkl` caches are gitignored; first run of each rebuilds in well under a minute.
