# Campaign Reimagined audit follow-through — 2026-09-29

**Audit recovery complete; campaign startup/exit smoke passes; release not
qualified.** EXU #72, OpenShim #374, and the recovery handoff #375 are pushed
and merged. A clean OpenShim main build runs the deployed CR mission with EXU
and bzfile on GOG, on both DX9 and DX11. The Workshop package/updater and the
separate release-validation edits still need work before publication.

## Revisions and scope

Origins were checked and fetched for all four repositories.

| Component | Revision used | Source state |
|---|---|---|
| OpenShim | `17d6cb5a5913e629617d62b2c92e405b7d89ad47` | Fresh Release/Win32 build in isolated `BZR-OpenShim-cr-audit-validation`, branch `agent/cr-audit-validation-20260929` |
| EXU | `2301ca7646cc77b6fc016698dd97137c13cf5e8e` | Canonical source matches origin/main; deployed DLL matches its existing Release build |
| bzfile | `e5c3a537db512c079962d2327861fae5adfabf49` | Canonical source matches origin/main; deployed DLL matches its existing Release build |
| Campaign Reimagined | `05803c416f6d5b030b592ffc6a6f4031e9912b5f` | Canonical checkout only; campaign source unchanged; generated binary caches and manifest/payload edits from the previous validation retained |

The earlier EXU recovery's rebuild, 13 host suites, eight boundary cases,
113-call comparison, and three save tests remain documented in
[its validation note](https://github.com/GrizzlyOne95/ExtraUtilities/blob/main/Docs/LUA_BOUNDARY_VALIDATION_20260928.md).
Those save tests are not evidence of a complete campaign save/load playthrough.

## Checks completed in this pass

- Fresh OpenShim Release/Win32 solution build and **64/64 CTest** pass. The
  default local MSVC 14.38 build has existing unused-code, unused delay-load,
  and C++17 `<bit>` warnings; it is not described as warning-free.
- CR repository invariants pass for 3,764 files; all 778 generated subtitles
  match; mission-03 co-op and setup-shell contract checks pass.
- **12 Lua 5.1 test scripts** pass, and all **40 campaign Lua files** parse.
- All **1,025 owned program references** resolve against 641 declarations;
  **232 DX11 shader compilations** pass, along with 124 color/fog permutations,
  66 terrain-normal permutations, and the Enhanced PSSM material pairing check.
- `Manage-CampaignFiles.ps1 -verify` reports **3,673 shipped files**, zero
  missing, zero differing, and zero unexpected installed files.

## Real campaign runtime checks

Test copy: GOG Redux 2.2.301, windowed, `misn02b.bzn`. The test temporarily
enables **only CR** in `modEnabled.dat`, launches with the mission basename and
`OPENSHIM_FORCE_STARTUP_AUTOLOAD=1`, and observes a 40-second process run before
graceful shutdown via `Stop-BZRGame -Id`. This is a bounded startup/exit smoke,
not 40 seconds of guaranteed simulation time or a mission-completion test.

| Candidate | Renderer | Result |
|---|---|---|
| Clean OpenShim main `17d6cb5a` + installed CR/EXU/bzfile | DX11 | Pass: actual CR simulation, campaign EXU/bzfile loaded, 2,227 grass instances in four regions, normal exit, no new dump or Lua/load error |
| Same clean candidate | DX9 | Pass: actual CR simulation and native modules, normal shutdown, no new dump or Lua/load error |
| Existing local OpenShim build with uncommitted LensFlare guards, based on `80d290f1` | DX11 | Same bounded smoke passes; this does not validate or publish those uncommitted guards |

All tested artifact hashes were unchanged during each run. All original saves,
mod selection, player configuration, and temporarily deployed OpenShim paths
were restored and hash-verified. Two existing `TestGround.material` missing
reference messages occur in the local install's Ogre log, including the
pre-test baseline; the run is not claimed to have a warning-free renderer log.
Visual quality was not inspected.

Clean-candidate SHA-256 values:

| File | SHA-256 |
|---|---|
| GOG executable | `8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413` |
| `winmm.dll` | `FC8C719FDECEBE877C21D6A1315FF477672ACB8C323C8845897E789CE625053B` |
| `bzloader.dll` | `9A49416731BE5B0571ACCEC0A8ACB7FBBBAF285C73A26245DA2740DB1D7B6866` |
| `plugins/openshim.dll` | `1CE25A32BC32FD7CE0B1DFF99745BC322FBD81A3C1B266816D84005CAC740986` |
| `scripts/patches.json` | `84ED3D2F4337482F703CCAF3B4DF27AE3FD0B8D4B69E327922CD27936B5E9F25` |
| Campaign `exu.dll` | `57641B87D30C72BA7BEDFB998FDB083BCF916C417BD3BC5253EF50F31492C9A8` |
| Campaign `bzfile.dll` | `4C338E55A25F4A584984BFE9AC07AC99F418BACA25DC75DC5A55EE850334EF4A` |

## Corrections to the previous validation

The previous run's optimistic startup message was insufficient evidence:
the active mod list contained four pilot/animation test addons and **did not
enable CR**. A bare `misn02b.bzn` could run the stock mission. A long positional
path such as `mods/3686673790/misn02b.bzn` was truncated to the directory and
could return to the menu with a `Could not load` error. Asset listings containing
`AutoSave.lua` also do not prove that Lua executed. The replacement check requires
simulation initialization and native modules loaded from the campaign folder.

The old ignored `build/release-validation-20260928/run-gog-validation.ps1`
cleanup had moved existing save files into its evidence directory. On recovery,
only `cpProgress.def` remained in the game save directory. **24 missing files
were restored**, each matching both the archived file and its pre-run backup.
The existing progress file was preserved. Slot 10 again matches the original
`DCED05F4579F80D9EBFE38E0F05D1196BA732806C86ADA4450D9E3D54323F339` hash.
Do not reuse that legacy runner. The new runner uses canonical path keys, a
persisted snapshot, and verifies restoration; every subsequent test retained
all 25 original save files.

The previous final DX11 run recorded a shutdown dump at 20:04 on September 28;
later teardown investigations added uncommitted LensFlare patches. The clean
main CR-only tests here do not reproduce that crash. They neither establish
its root cause nor qualify the previous multi-addon configuration.

## Release blockers and next work

1. **CR still packages an incomplete OpenShim load chain.** The existing dry-run
   output under `Local/Workshop/content` contains `winmm.dll`, but lacks both
   `bzloader.dll` and `plugins/openshim.dll`. `Get-ShippingBinaryPlan` and
   `Update-OpenShimManifest` in CR's manager still describe the old single-DLL
   model. A successful shipping-lock check cannot detect this missing contract.
2. **Updater migration must accompany the packaging fix.** OpenShim's
   `OpenShimUpdateManifest` and `openshim_updater.cpp` still replace only
   winmm/net/patches. CR's `OpenShimInstaller.lua` and bzfile's constrained suite
   replacement path must be updated together for the complete chain, keeping
   hash checks, destination restrictions, rollback, and helper attestation.
   Merely adding the two DLLs to the ZIP is insufficient. Add a staged-package
   completeness test, then exercise fresh install and same-version update.
3. **The separate release-validation changes are not a pushed candidate.**
   Primary OpenShim is at `80d290f1`, six commits behind the fetched main, with
   uncommitted LensFlare hook/research edits plus a verifier/CI regression fix.
   CR retains its generated Bin/manifest/payload edits. They were preserved,
   not blanket-staged into this audit follow-through. Review/checkpoint the
   workstream before selecting a final release candidate.
4. **Qualification remains narrower than a release.** The full campaign,
   gameplay save/load/restart and mission transitions, multiplayer/visual
   acceptance, Windows/Steam, Proton, and Wine were not tested here. Follow
   [release qualification](RELEASE_QUALIFICATION.md) and CR's publication
   checklist using one frozen package after fixing the load-chain contract.

No release/tag, PR merge, history rewrite, Workshop upload, or public Roadmap
edit was performed. Existing audit follow-ups remain in
[the combined tracker](AUDIT_BACKLOG_STATUS.md).

## Reproduction and local evidence

The committed [campaign smoke runner](../reverse_engineering/test_campaign_reimagined.ps1)
requires PowerShell 7 and the already deployed canonical CR content. It uses
the shared launch harness; optional `-ShimRepo` temporarily deploys the complete
OpenShim chain and restores it afterward. Each label must be new.

```powershell
pwsh -NoProfile -File reverse_engineering/test_campaign_reimagined.ps1 `
  -Label main-dx11 -EvidenceDirectory C:\Temp\cr-validation `
  -ShimRepo C:\src\BZR-OpenShim -Renderer dx11
```

Logs, module paths, hashes, and save/configuration backups are retained locally:

- `%TEMP%\codex-cr-audit-validation-20260929` (this pass)
- `%USERPROFILE%\Documents\GIT\.research-archive\CodebaseAudit-20260929`
  (durable copy of this pass's evidence)
- `BZR-OpenShim\build\release-validation-20260928` (earlier interrupted pass)

Backups, crash dumps, runtime binaries, and raw logs are not committed.
