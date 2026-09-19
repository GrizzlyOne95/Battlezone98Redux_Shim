# TRN Key Liveness Audit — which `.trn` settings Redux still implements

Date: 2026-09-15
Binary: GOG Battlezone 98 Redux 2.2.301, `battlezone98redux.exe`, image base `0x400000`
(unencrypted — the Steam copy is SteamStub'd and useless for this).
Tool: `reverse_engineering/audit_trn_keys.py`

Redux parses more of the 1.5 TRN format than it implements. A key being read
into a global proves nothing, and mod authors have been setting dead keys for
years on the reasonable assumption that a parsed key does something. This is the
census, and the method to re-run it on any key.

---

## 1. Method

For each key literal: find its string, find the `.text` xref, identify which of
the three config readers is called, recover the **destination global**, then look
for any *read* of that global from outside the parser.

Two shapes count as live:

* an xref from another function (`SkyTexture` → `006152D1`, `00616594`, …), or
* the parser handing the buffer straight to a loader (`SunTexture` → the parser
  itself does `push 0x2a13dd8; call 0x68bed0`).

The three readers, and their argument shapes:

| helper | kind | args (cdecl, pushed right-to-left) |
|---|---|---|
| `0x787AC0` | int | `section, key, default, file` |
| `0x787A30` | string | `section, key, default, dest, size, file` |
| `0x787B60` | float | `section, key, default, file` |

`SkyTexture` and `SunTexture` are the positive controls — both demonstrably
render, and they exercise both live shapes.

### Four traps, each of which silently inverts a verdict

1. **A data xref lands 1–3 bytes into the instruction, not at its start.** For
   `push imm32` the operand sits at `insn+1`. Disassembling from the xref
   address finds no instruction there, every key reports "never read", and the
   whole census reads dead. Anchor on the instruction *covering* those bytes,
   and try several start offsets because a linear sweep from an arbitrary byte
   desynchronises. (Same root cause as the byte-guard anchoring note in
   `redux-pdb-is-advisory-only` territory.)
2. **A store is not a read.** The backdrop parser has a sibling at `0x00616E00`
   that zero-fills the whole struct — nine `mov [addr], eax`. Counting raw xrefs
   makes those look like nine consumers and marks a dead feature live.
3. **A global inside a `rep movsd` range is consumed with no direct xref.** The
   whole `[NormalView]` set is copied as 12 dwords from `0x008F0598` into the
   live view struct at `0x02C06748` by `0x007808A2`. Without tracking block
   copies, every key in that struct but the first reads as dead.
4. **A short key matches the tail of a longer one.** `Ambient\0` matches the end
   of `CarAmbient\0`. Require a NUL *before* the match too, and search every
   occurrence — the same literal lives in several string pools and only one is
   the one the parser pushes.

### Known limitation

Keys whose parsed value is stored through a register base (`mov [esi+0x10], eax`)
rather than an absolute address are reported `?`, not dead. That covers
`MinX/MinZ/Width/Depth`, `MusicTrack`, `MaterialName`, `Palette`, `Luma`,
`Solid`, and the indexed `[Stars]` keys (`Azimuth%02d` and friends, which reach
their reader through an indirect call). Several of those obviously work in game.
**`?` means "not determined", never "dead".**

---

## 2. Results

### Dead — parsed into a global, never read by anything

| key | stored at | note |
|---|---|---|
| `Wave` | `0x008F0594` | sits **4 bytes below** the 48-byte `[NormalView]` block at `0x008F0598` that is `rep movsd`'d into the live view struct — it misses the copy by exactly one dword |
| `BackdropTexture` | `0x02A13DA8` | |
| `BackdropDistance` | `0x02A13DB8` | default 400 |
| `BackdropHeight` | `0x02A13DBC` | default **50**, not the 100 every TRN writes |
| `BackdropBase` | `0x02A13DC4` | |
| `BackdropType` | `0x02A13DC8` | |
| `Time` | `0x02CD94E4` | |
| `ShadowLuma` | `0x02CD9444` | while `TerrainShadowLuma`, the very next dword at `0x02CD9448`, *is* read at `0x00783FBE` |

### Absent from the binary entirely — dead text in every TRN, stock templates included

`CarAmbient`, `BackdropWidth`, `FlatColor`, `Translucency`, `Alpha` /
`Alpha%02d`.

### Live

`VisibilityRange`, `FogStart`, `FogEnd`, `FogBreak`, `FlatRange`, `Intensity`,
`Ambient`, `FogDirection`, `TerrainShadowLuma`, `Lava`, `Waves` (the global
enable, from render.cfg), `SkyTexture`, `SunTexture`, `SkyType`, `SkyHeight`,
and the `[Clouds]` set: `Count`, `Duration`, `Distance`, `Sound`, `Bolts`,
`minDelay`, `maxDelay`, `Type`, `TileSize`.

---

## 3. The backdrop is the trap worth naming

The parser at `0x00616CA7`–`0x00616D58` is convincing: it early-outs on an empty
name, reads Distance / Height / Base / Type, and then computes `sqrt(d²+h²)` into
`0x02A13DC0` and a `1/tan` term into `0x02A13DCC` — exactly the derived values a
band mesh needs. Then it returns, and nothing ever reads any of the seven fields.

Consequences for mod authors:

* `BackdropWidth = 800`, present in every stock editor template, is not even a
  string in the exe.
* ISDF Chronicles' `isdfms16.trn` sets `BackdropTexture = DARKFLAT.map`, and
  `darkflat3.material` does declare `material DARKFLAT.MAP` — so the material
  resolves. **A material resolving is not evidence the engine asks for it.** It
  has never drawn.

This matters because the backdrop is the one mechanism designed for "the horizon
is flat against the cubemap until terrain comes inside `VisibilityRange`", and
it is not available. The only lever for that today is `VisibilityRange` itself.

---

## 4. `VisibilityRange` is a horizontal distance-squared cull

Cost goes as radius², which is worth knowing before a mod sets it to 1500.

* TRN reader at `0x0077E5CD`, default 250, writes `0x008F0598`.
* `0x007808A2` `rep movsd`s that 12-dword block into the live view struct at
  `0x02C06748`.
* `0x007808E6` squares it into `0x02CD9134`.
* Four sites — `0x00781A59`, `0x007820A3`, `0x00782249`, `0x0078259E` — compute
  `x*x + z*z` and subtract it from that square. **Y is ignored**; it is a
  cylinder, not a sphere.

1500 against the stock 250 is 36× the culled-in area.

---

## 5. Correction: `Lava` is live, and it keys off the `.mat`

`animated_terrain_waves_design_20260716.md` treats `Lava=N` as a 1.5-only colour
feature with only the config path surviving into Redux. That is wrong.

`0x00782DD1` reads a 16-bit terrain cell, masks `0xF000`, shifts down 12, and
compares that nibble against the Lava id at `0x008F05C8`, selecting colour table
`0x02CD9460` on a match and `0x02CD9500` otherwise — the 1.5
`LavaColors[]` vs `GreyColors[]` behaviour, still running. `0x0077D680` is a
plain `return lavaMat` getter.

The word being tested is the **`.mat`**, not the `.hg2`: the `.hg2` high nibble
is 0 on every cell of every map measured, while `.mat` high nibbles are the paint
type indices. So **`Lava=N` means "TextureType N takes the lava ramp"**, and it
is configured correctly in the wild — ISDF Chronicles `isdfms02` sets `Lava=1`,
which matches 38.4% of its cells, and its `[TextureType1]` is labelled "Lava
Pool". `isdfms12` `lava=0` → 58.9%; `isdfm13b` `lava=4` → 33.5%;
`isdfms04` `lava=5` → 0.9%, which is close to pointless.

`Wave`, by contrast, is genuinely dead, which is consistent with that document's
conclusion for the wave half.

---

## 6. If either feature is to be implemented in OpenShim

Neither can be "re-enabled" — there is no consumer to feed. Both mean
implementing the feature.

**Backdrop is the easier of the two**, which is the opposite of the intuition.
Because nothing reads the struct there is no engine path to fight: OpenShim adds
scene content of its own — a camera-parented cylinder or billboard chain, its own
material, rendered in the sky queue group with `depth_write off`, driven by TRN
values OpenShim parses itself (it does not need the engine's copy). The plumbing
already exists: SceneManager at `0x00920EA0`, Ogre proc resolution, the per-frame
render-queue hook. The risks are the familiar ones rather than unknowns —
mission-lifetime teardown, calling Ogre through resolved exports rather than
header vtables, and needing an `en-*` technique or it renders black under DX11
Enhanced.

**Wave is harder**, though less so than `animated_terrain_waves_design_20260716.md`
assumed. That document's blocker was step 2: terrain is one atlased material, so
"which submesh is the lava tile" looked unrecoverable. The `Lava` finding above
weakens that — the render path at `0x00782DD1` **already classifies terrain cells
by their `.mat` nibble at draw time**, so a per-cell type does exist in there.
Getting that classification to reach an Ogre material or shader is still the
whole job, but it is a far better starting hook than nothing. Avenue B1 (UV
scroll) remains the right shape.

---

## 7. Re-running it

```
python reverse_engineering/audit_trn_keys.py VisibilityRange Wave BackdropTexture Lava
```

Prints verdict, destination global and the evidence (`read at …`,
`copied by … (+n)`, `consumed in parser`, or `parsed, never read`). Point `EXE`
at the GOG binary; the method generalises to any `GetPrivateProfile`-style key
in this build, not just TRN ones.
