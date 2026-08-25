# Backend-Selection (Seam A) Runtime Qualification — 2026-08-25

Branch: `agent/openshim-backend-selection` (based on
`agent/openshim-render-profiles`). Evidence snapshots:
`reverse_engineering/snapshots/backend_selection_matrix/{gog,steam}/`,
plus RE-phase evidence under `renderer_startup_matrix{,2}/`.

## What was validated

The startup backend seam: persistent `[Graphics] Renderer` preference applied
via the pre-read `Ogre.cfg` transport line, launch-scoped `/renderer:` CLI
override, capability pre-validation, and requested/effective/reason telemetry.

Implementation notes captured by validation:

* The seam runs from DllMain (`RunStartupBackendSelectionEarly`). An earlier
  patch-thread placement lost a startup race on the Steam build, where engine
  init completes in ~1 s and the game read Ogre.cfg before OpenShim could write
  it (observed as spurious `backend-unavailable` on bs-persist-dx11).
* Stock's command-line parser strtok()s the PEB command-line buffer in place;
  the seam therefore consumes the DllMain command-line snapshot
  (`cmdline snapshot:` log line) rather than a late `GetCommandLineA()`.

## GOG install — 8/8 PASS

| Case | Setup | Asserted outcome |
|---|---|---|
| bs-auto | ini Auto; stock cfg DX11 | `backend.boot: requested=Auto source=stock transport=untouched`; `backend.selection=stock requested=Auto effective=DX11 reason=stock`; Ogre.cfg untouched |
| bs-persist-dx11 | ini DX11; stock cfg DX9 | transport `'Direct3D9…' -> 'Direct3D11…'`; boot DX11; `reason=none` |
| bs-persist-dx9 | ini DX9; stock cfg DX11 | boot DX9; `requested=DX9 effective=DX9 reason=none` |
| bs-cli-over-persist | ini DX11 + `/renderer:dx9` | `requested=DX9 source=cli-override`; effective DX9; `reason=cli-override`; stock absorbs DX9 into cfg |
| bs-cli-relaunch | no setup (absorbed state) | transport re-asserts `'Direct3D9…' -> 'Direct3D11…'`; boots DX11 — **the absorption fix** |
| bs-plugin-absent | ini DX11; D3D9 stock line; DLL renamed away | `transport=plugin-missing`; stock fallback DX9; `reason=backend-unavailable`; `preserving requested backend=DX11` |
| bs-device-failure | ini DX11; poisoned FL section (Min>Max) | `transport=written`; process fast-fails (`0xC0000409`) with no window; pending marker survives |
| bs-recovery | clean cfg after failed boot | `previous boot ended before renderer establishment`; normal DX11 override boot; marker consumed |

## Steam install — 5/5 PASS

Direct launches need a temporary `steam_appid.txt` (appid 301650); removed
afterwards. Cases bs-auto / bs-persist-dx11 / bs-cli-over-persist /
bs-cli-relaunch / bs-plugin-absent all match the GOG contract exactly,
including the absorption fix. SteamStub does not affect the data seam.

## Regression status

* `scripts/run_backend_selection_tests.ps1` — PASS (new decision-core tests).
* `scripts/run_render_profile_tests.ps1` — PASS (existing resolver suite).
* Full Release|Win32 shim build — clean.
* Auto invariance: with `[Graphics] Renderer=Auto` the seam touches nothing;
  bs-auto asserts the untouched path explicitly.
