# Stock Asset LOD / Bounds / Renderability Audit (2026-08-24)

Branch: `agent/stock-asset-audit` (OpenShim).
Runtime: GOG Battlezone 98 Redux 2.2.301, `lcbench` harness, DX11 and DX9.
Static corpus: all 240 `.mesh`, 252 material files (419 material definitions),
and the 796-ODF inventory of `bzone.zfs` under the stock install.

Every claim below is labelled **measured**, **static**, **inference** or
**hypothesis**. Machine outputs live in `reverse_engineering/asset_audit/`
(gitignored): `stock_asset_inventory.json`, `stock_asset_manifest.csv`,
`runtime_evidence.json`. The manifest is the work-order deliverable; this
document is its evidence trail.

---

## 1. Method

**Static.** `reverse_engineering/audit_stock_assets.py` parses every stock
mesh with the BZ98R Blender ToolKit's Ogre v1.100 serializer plus a custom
walker for the chunks that serializer skips (`M_MESH_LOD`) or does not surface
(bounds-chunk presence). It decodes position streams and index buffers with
numpy and cross-references submesh materials against a full inheritance-aware
parse of every `.material` script in `BZ_ASSETS` and `BZ_ASSETS_CORE`.
ODF class labels come out of `bzone.zfs` via the toolkit's ZFS reader.

Format facts established while building the walker (they contradict common
Ogre assumptions and are easy to get wrong again):

- BZ98R mesh strings are **newline-terminated**, not null-terminated.
- Chunk lengths **include** the 6-byte chunk header.
- The stored bounding-sphere radius equals **max vertex distance from the
  origin** exactly (verified to float precision on every healthy mesh), not
  half-diagonal or corner-based box models.

**Runtime.** Controlled distance sweeps on the deterministic `lcbench` mission,
profiler contributor rows providing per-mesh scheme/technique/LOD/camera
submissions. Sessions: `20260824_000531` + `20260824_000840` (avtank x20 idle,
50..1000 m), `20260823_235617` + `20260824_001724` (sbsilo x4 props, 50..400 m),
`20260824_001021` (14-ODF skin-source survey), `20260824_001828` /
`20260824_001853` (DX9 spot checks).

## 2. Static inventory results

| Check | Result |
|---|---|
| Meshes audited | 240 (188 base + 52 TRO) |
| Finite bounds consistent with geometry | **238** (`ok_finite`) |
| Missing `M_MESH_BOUNDS` chunk | **2**: `gsand00.mesh`, `sbsilo.mesh` |
| NaN / infinite / zero-extent / implausibly-large serialized bounds | **0** |
| Stored bounds vs decoded geometry mismatch | **0** beyond 2% tolerance |
| Radius inconsistent with vertices | **0** |
| Malformed streams (buffer size, index range, op type) | **0** |
| Meshes shipping any `M_MESH_LOD` level | **0 of 240** — mesh LOD is absent stock-wide; all distance behaviour rides on material LOD |
| Dangling material references | 3 meshes: `apc11bda`, `apm11bda` -> `appowr00`; `cube_10x10x10` -> `lambert2` (defined nowhere in the install) |
| Material LOD at script level | BZBase family: 13 schemes x lod_index {0,1,2} at `lod_values 250 300`; cockpit family (`BZBaseCockpit`): own 13 techniques, single index (always full quality — coherent with the always-visible cockpit policy) |

The two "missing bounds chunk" meshes are the only bounds anomalies in the
entire stock corpus, and section 3 shows they are **not defects at runtime**.

## 3. Runtime verification

### 3.1 Material LOD selection vs distance (**measured**)

`avtank.mesh` / `avtank00`, DX11, 20 idle craft facing the camera; the player's
own tank at the camera accounts for the constant `lod=0` rows:

| Distance | high-pssm technique LODs observed |
|---:|---|
| 50 m | 0 |
| 100 m | 0 |
| 250 m | 0 and **1** |
| 300 m | 0 and **2** |
| 500 m | 0 and 2 |
| 1000 m | 0 and 2 |

Transitions land exactly on BZBase's `lod_values 250 300`. `glow` renders
lod 0 at every distance — the glow technique carries no `lod_index`; that is
stock behaviour on both renderers, not an OpenShim deviation.

`sbsilo.mesh` / `sbsilo00` (building, missing serialized bounds chunk)
reproduces the same thresholds: lod1 appears at 250 m, lod2 at >=300 m.

DX9 reproduces both cases exactly (lod2 at 300 m / 400 m).

**Conclusion (measured):** distant material LOD works correctly in stock for
craft *and* buildings on both renderers. In particular, the stock loader
compensates for a missing serialized bounds chunk — `sbsilo.mesh` selects
distance-appropriate techniques despite serializing no bounds at all.

### 3.2 GPU/CPU mesh source data (**measured**)

Fourteen additional unit ODFs were loaded five copies each and idled
(svwalk, svturr, svmine, svapc, sspilo, svtank, bvwalk, bvturr, bspilo,
bsheav, avhaul, avcnst, avrecy, avscav). Software skinning ran on all of them
(`SkinTop` rows present, 14k-40k verts/f) and **every sampled skinned
position/normal source reported `posShadow=yes`**; the retrofit counters read
queries=0 repairs=0 failures=0 across all fourteen runs.

Combined with the earlier sweep (`20260822_093849`: avmine and avturr were the
only GPU-only finds, repaired automatically by the generic retrofit), the
evidence says the GPU-only source class is **fully contained by the existing
load-time repair**. Do not assume other assets are affected: they were not
found in any sampled population, and the counter makes any future occurrence
visible in one log line.

### 3.3 Shadow behaviour (**measured**)

From the same sweep logs, shadow render-queue calls per frame:

| Distance | rqMain/f | rqShadow/f |
|---:|---:|---:|
| 50 m | 102.3 | 63.2 |
| 100 m | 102.2 | 63.2 |
| 250 m | 102.0 | 63.0 |
| 300 m | 101.9 | 62.9 |
| 1000 m | 102.0 | 62.9 |

Shadow submissions are **flat across distance**: ~63/frame = 3 PSSM cascades x
21 craft, because Redux writes `EXTENT_INFINITE` onto shared craft world meshes
on spawn (binary analysis and runtime trace:
`craft_bounds_architecture_20260822.md`). This is the single largest measured
render-work anomaly in stock assets, it scales with craft count, and it is
exactly what the existing opt-in repair fixes
(`OPENSHIM_RESTORE_CRAFT_BOUNDS=1`: -51% to -98% shadow traversal in the
documented A/B). Main-view submissions likewise never decay; fragment cost
drops past the material thresholds but submission count does not.

### 3.4 Attachment multiplication

Attachments (turret pieces, headlights, weapons) each submit separately per
scheme; contributor rows show e.g. `avtank01`/`avheadlight00` as independent
per-craft rows alongside hull submeshes. No attachment-specific defect was
found statically or at runtime; their cost profile is the same
no-decay-with-distance pattern as hulls (same infinite-bounds cause).

## 4. Repairs: what was done, attempted, and deliberately not done

| Candidate | Decision | Evidence |
|---|---|---|
| GPU-only skin sources (`avmine`, `avturr`) | **No new work.** Existing generic retrofit already repairs at load; survey found nothing new | 3.2 |
| Infinite bounds on shared craft meshes | **No new work.** Root-caused and repaired previously behind `OPENSHIM_RESTORE_CRAFT_BOUNDS=1` | 3.3 + prior doc |
| `gsand00`/`sbsilo` missing serialized bounds chunk | **Repair withdrawn after implementation.** A table-driven native repair (`createEntity` detours applying audited geometry-derived boxes) was built, validated for install safety, then reverted: runtime measurement proved stock already selects correct material LOD on these meshes (3.1), so there is no defect to fix. The two-string overload detour also hung mission load — recorded as evidence that hooking `createEntity(name, mesh)` needs its own investigation before anyone retries | 3.1; revert commit `f85952ee` |
| Dangling materials (`appowr00`, `lambert2`) | **Not repaired.** Ogre substitutes its error material; affected meshes (`apc11bda`, `apm11bda`, `cube_10x10x10`) look like unused editor/attachment leftovers. Recorded in the manifest; repairing would mean inventing appearance | static only |
| New artistic LODs, destructive simplification | **Rejected by mandate** | — |

## 5. Performance ranking of the findings

Ranked by measured runtime impact:

1. **Infinite craft bounds** — flat ~63 shadow submissions/f regardless of
   distance, multiplied by craft count and three cascades; largest verified
   recoverable cost; fix exists behind an env flag.
2. **Glow scheme has no material LOD stock-wide** — every glowing object pays
   full glow fragments at any distance. Stock behaviour on both paths;
   changing it changes appearance, so recorded, not touched.
3. **Chunk batch renders at material LOD 0** — OpenShim's own generic chunklet
   batch deviation, already documented in
   `live_render_optimization_20260822.md` (known limitation 3b); unchanged.
4. Everything else measured: no defect found. 238/240 meshes are internally
   consistent to float precision; the remaining two are compensated by the
   loader.

## 6. Validation performed

- Release Win32 build clean (pre-existing warning set only);
  deployed SHA-256 prefix `197864867B87D9F8`.
- Ogre profiler algorithm tests passed; INI/config tests 23 checks 0 failures.
- `luac -p` clean on modified `lcbench.lua`.
- 23 benchmark launches total this pass: quiet smoke, props matrix
  (50/250/300/400), craft distance sweep (50..1000), 14-ODF skin survey,
  DX9 spot checks. Two runs hit the documented rare pre-mission startup miss
  under heavy concurrent machine load; everything else reached
  `benchmark-end`.
- Log scan across sessions: no `[ERROR]`, no unhandled access violations, no
  shader/material failures. First-chance SEH records from existing guarded
  probes remain expected noise.
- Visual: silo formations rendered normally at 50 m (full-quality + shadows +
  glow) and dropped to low techniques past thresholds, as intended by the
  material authors. No code change ships in this branch, so stock appearance
  is preserved by construction outside the (reverted) experiment windows.

## 7. Limitations

- Runtime LOD was directly instrumented for `avtank` (craft class) and
  `sbsilo` (building class); other assets inherit class-level conclusions and
  are labelled as such in the manifest rather than overclaimed.
- Ordnance/debris/pilot classes were covered statically and via the skin
  survey's pilot entries, but not individually distance-swept.
- `gsand00` was validated by loader-path identity with `sbsilo` plus static
  size (17 verts), not spawned standalone; it is a tiny ground decal prop.
- The dangling-material meshes were not exercised in-engine; their runtime
  appearance (error material) is inferred from Ogre semantics.
- Steam binaries untouched; GOG 2.2.301 remains the supported evidence base.

## 8. Artifacts

- `reverse_engineering/audit_stock_assets.py` — static auditor (rerunnable).
- `reverse_engineering/merge_asset_audit_runtime.py` — manifest builder.
- `asset_audit/stock_asset_inventory.json` — full per-mesh/per-material record.
- `asset_audit/stock_asset_manifest.csv` — work-order manifest (240 rows).
- `asset_audit/runtime_evidence.json` — session IDs and headline measurements.
- Harness extensions: `props` scenario + expanded ODF allowlists
  (`lcbench.lua`, `run_live_combat_benchmark.ps1`).
