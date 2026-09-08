# OpenShim DLL-only Qualification Matrix

Validates the **OpenShim DLL-only degraded configuration** required by the
DLL-only installation objective: stock Battlezone 98 Redux 2.2.301 plus
`winmm.dll`/`openshim.ini` with **no** Workshop subscription and **no**
Campaign Reimagined / OpenShim asset package.

This matrix is the manual complement to the automated engine-independent tests
(`tests/openshim_assets_tests.cpp`, `tests/render_profile_resources_tests.cpp`,
`tests/render_profile_tests.cpp`). Automated tests prove the decision logic;
this matrix proves the real game does not crash, leak, or spam when those
decisions are exercised.

## Automated coverage (already gated in CI)

* `render_profile_resources_tests` — valid set passes, single missing mandatory
  file fails, empty file fails, version mismatch fails, absent directory fails.
* `render_profile_tests` — Enhanced without `CapEnhancedResources` cleanly
  falls back to Redux with a reason; DX9 Enhanced with missing resources also
  falls back; IBL loss is independent.
* `openshim_assets_tests` — manifest parsing (valid, missing Version,
  version mismatch, malformed, partial), destruction-chunk and enhanced-resource
  probing (absent vs present vs empty file), `EvaluateAssetCapabilitiesAt`
  for `NotDetected` / `Detected` / `Incompatible` / partial states, feature
  gating (`config true + asset unavailable → false`, `config false → false`,
  `Unknown → fail-closed`), HD terrain manifest resolution (default name,
  custom relative path, absolute path, unconfigured, zero-byte file),
  snapshot semantics across a concurrent refresh, UI formatting.
* `Build Linux Tests` (Ubuntu CTest) — `src/engine/openshim_assets.cpp` is
  engine- **and** OS-independent and is compiled by this workflow. The Win32
  pieces (module path, `openshim.ini` lookup) live in
  `src/engine/openshim_assets_platform.cpp` behind
  `ResolveAssetRuntimeEnvironment()`, which the test harness stubs.
* `BZROpenShim.sln Release|Win32` — still builds after the asset-capability
  layer and settings-UI status integration.

## Capability-service contracts

* **HD terrain is probed at the configured path.** `ProbeTerrainHdAt()` takes
  the `[Terrain] TerrainHdManifest` value and resolves it exactly as
  `terrain_proxy.cpp`'s `ResolveHdManifestPath()` does (absolute verbatim,
  relative against the game directory). A custom manifest location is therefore
  reported accurately instead of being called unavailable.
  `LoadTerrainHdManifest()` remains the complete gate — it additionally
  validates the JSON schema and soft-fails to the stock atlas.
* **Readers get snapshots.** `GetAssetCapabilities()` returns
  `AssetCapabilities` by value. A refresh may replace the cached object, and its
  `std::string` storage, from another thread, so a reference into the cache
  would dangle. All UI and runtime call sites hold their own copy.

## Manual matrix — stock BZR + OpenShim DLL only

### Prerequisites

* Clean Battlezone 98 Redux 2.2.301 install (Steam `battlezone98redux.exe` or
  GOG `BZR.exe` — run the matrix once per storefront).
* No Workshop content for app 301650. Verify
  `steamapps/workshop/content/301650` is empty or absent and `addon/`,
  `mods/`, `packaged_mods/` contain no `chunkMeshes` / `Chunks` payloads.
* No `BZ_ASSETS/common/models/OpenShimChunkPayloads` directory.
* No `openshim/renderer/enhanced/resources.version` override — use the stock
  game directory (which has no `openshim/renderer/enhanced` at all for a
  DLL-only test).
* Place only `winmm.dll` + `openshim.ini` (shipped `openshim.ini` has
  `ChunkMeshes=0`, `RenderProfile=Redux`) beside the exe.

### A — Baseline DLL-only (shipped openshim.ini)

| # | Step | Expected |
|---|------|----------|
| 1 | Launch game | No crash, reaches main menu; `openshim.log` contains `[assets] Asset pack state=NotDetected ... destructionChunks=0 enhancedResources=0` |
| 2 | Open **OpenShim Settings** (Options → OpenShim) | Header reads `OpenShim Settings`; status line shows `Runtime: Active Version: <ver> Game: Steam/GOG 2.2.301 Assets: NOT DETECTED` or similar; footer shows `Asset Pack: NOT DETECTED — Asset-dependent features are unavailable.` |
| 3 | Scroll settings rows | `Death Chunk Meshes`, `DX11 FXAA`, `DX11 Local Lights` show `Unavailable` and hover shows `Unavailable — OpenShim asset pack not detected`; clicking them does not cycle and status shows the same reason |
| 4 | Launch **Instant Action** (stock map) | Mission loads normally; stock rendering, stock terrain |
| 5 | Destroy several units / buildings | No crash, no invalid Ogre access, no `chunkMesh` debris (stock chunk behavior only); `openshim.log` shows at most one `[CHUNKMESH] Chunk mesh proxy requested but asset capability unavailable` line, not per-frame spam |
| 6 | Use player weapons / movement / camera | Normal |
| 7 | Return to menu | Clean |
| 8 | Host multiplayer lobby (if possible) | Lobby creates, map list intact, host controls work |
| 9 | Join multiplayer (second instance where available) | Join succeeds; `[SinglePlayer]` features remain gated |
|10 | Change maps / return to shell / exit | No crash or hang; normal process exit |

### B — DLL-only with *every* asset-dependent setting forced on

Replace `openshim.ini` with a copy of `openshim.ini.example` (which has
`ChunkMeshes=1`, `RenderProfile=Enhanced`, `FXAA=1`, `EnhancedLightSelectionV2=1`
and other asset-touched rows) or hand-edit to:

```ini
[General]
ChunkMeshes=1
[Graphics]
RenderProfile=Enhanced
[DX11Enhanced]
FXAA=1
EnhancedLightSelectionV2=1
```

Repeat steps 1–13 above. **Expected is identical to A:** no crash, no invalid
resource access, no persistent error spam, asset-dependent features are
suppressed, settings page still reports `NOT DETECTED` (or `VERSION MISMATCH`
if a stale manifest is present) and explains why, network/native fixes remain
operational, normal exit succeeds. `openshim.log` must not contain per-frame
`[CHUNKMESH] payload resolve miss` or `manual-submit-skip` spam — at most one
suppression diagnostic per capability.

### C — Partial pack

Create only the chunk payload sentinel without the enhanced renderer set
(or vice versa):

* **Chunks only:** `addon/TestMod/chunkMeshes/chunk_geo_manifest.txt` + one
  `chunkMeshes/chunk1/chunk1.mesh`; leave `openshim/renderer/enhanced`
  absent.
* **Enhanced only:** populate `openshim/renderer/enhanced` with a valid
  `resources.version` + 17 mandatory files; leave chunk payloads absent.

Repeat A. Expected: no crash; the present capability reports `Detected`,
the absent one reports unavailable; unrelated capabilities continue working;
diagnostic identifies which group is missing.

### D — Version mismatch

Create `openshim/OpenShimAssets.ini`:

```ini
[OpenShimAssets]
Version=999
ChunkMeshes=1
EnhancedResources=1
```

with otherwise valid payloads present. Expected: settings page shows
`Asset Pack: VERSION MISMATCH Installed: 999 Expected: 1`, all
asset-backed features are suppressed (mismatch is not trusted), native fixes
remain operational, log reports version mismatch exactly once.

### E — Full pack regression (no degradation)

Restore a valid asset pack (real Campaign Reimagined Workshop content or a
synthetic valid set: correct `openshim/OpenShimAssets.ini` `Version=1`,
valid chunk payloads, valid `openshim/renderer/enhanced` set). Set
`ChunkMeshes=1` and `RenderProfile=Enhanced` on DX11. Verify:

* Settings shows `Asset Pack: Detected` (or `Detected (full)`).
* Death-chunk debris renders with `chunkMeshes` meshes.
* Enhanced terrain/object shaders and light selection are active
  (check `[RENDER] effective=Enhanced` and no fallback reason).
* All previous matrices still pass — the DLL-only safety layer did not regress
  the normal installed-pack configuration.

## Logging expectations

* `[assets] Asset pack state=...` appears once at startup. Every explicit
  `RefreshAssetCapabilities()` — startup, and `ActivateShimSettingsPage()` on
  each settings-page entry — logs `[assets] Asset capabilities refreshed ...`,
  but only when the observed state actually changed, so repeatedly opening the
  settings page on an unchanged install does not spam the log.
* `[CHUNKMESH] Chunk mesh proxy requested but asset capability unavailable`
  appears at most once per process when a config requests chunks without
  assets.
* `[CHUNKMESH] payload resolve miss` is rate-limited (one per unique mesh
  candidate fingerprint, 512-entry LRU) and must not appear every frame.
* No per-frame `[CHUNKMESH] manual-submit-skip` or uncaught SEH faults.

## Sign-off

Complete A + B on both GOG and Steam. C, D, E may be exercised with synthetic
filesystem layouts on a single storefront but must pass before a release is
marked DLL-only qualified. Record the exact DLL SHA-256 and whether the run
was synthetic vs real Workshop content.
