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

### 1.3 What 1.5 kept

*Resource evidence, medium confidence — see the string-scan caveat in the companion doc.*
Searching the unpacked 1.5 `bzone.exe`: `nation`, `american`, `soviet`, `alien` are present;
**`chinese` and `blackdog` are not**. That is consistent with 1.5 carrying a reduced nation table,
which would matter directly to an `All Nations` restoration — the rule may be gating a four-value
enum there, not TRO's six.

**Do not treat that as settled.** The 1.5 exe omits most ODF key literals, so absence is weak.
Confirm against `bzint.pdb` symbols or the 1.5 decompile corpus before designing around it.

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

## 4. Status of a BZ 1.4 baseline

Still missing, and now understood to be harder than expected.

* `BZ1_Source/decomp1.4` is **not** a usable baseline: 805 KB of decompiled C over 693 files with
  only 323 distinct string literals, focused on AI/collision. Fine for what it was made for,
  useless for "did 1.4 have feature X".
* A real 1.4 install was located and its exe copied to **`BZ1_Source/1.4/bzone_shipped.exe`**
  (3 046 300 B, 2008-11-02, from a 1.4 patch installer). Supporting `label.map`, `Input.map`,
  `patch.txt`, `update.txt` copied alongside.
* **That exe is packed with genuine Shrinker** — the real thing this time, not TRO's inherited
  banner: `.text` `VirtualSize 0x1E4800` against `SizeOfRawData 0xA00`, `.data` with
  `PointerToRawData = 0`, entry at `0x00401000` jumping to a stub at `0x004010AA` whose API name
  strings are NOT-encoded (`kernel32` at file `0x4D2`), and an `LZO real-time data compression
  library` banner at file `0xD203`. Original section names and the full 16-DLL import table are
  preserved, which is Shrinker's signature.
* Roughly 1.88 MB of overlay sits past the last section (file `0x11B000`–`0x2E7A1C`) — the
  compressed payload.

**Unpacking it is a separate sub-project**, not a rerun of the TRO recipe: Shrinker/LZO needs the
block table located and `lzo1x` decompression applied, and Shrinker 3.x can decompress on demand
via a page-fault handler, which would also defeat a naive runtime dump. Do not point ghidrecomp at
`bzone_shipped.exe` as it stands — the analysis would be of the stub and 2.5 KB of `.text`.

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
