# Backend-Selection (Seam A) Runtime Qualification — 2026-08-25

Branch: `agent/openshim-backend-selection` (based on
`agent/openshim-render-profiles`). Evidence snapshots:
`reverse_engineering/snapshots/backend_selection_matrix/{gog,gog2,steam,steam2,steam3,concurrent}/`,
plus RE-phase evidence under `renderer_startup_matrix{,2}/`.

## Approved architecture (final)

The backend transport is **not** executed from DllMain and not from a patch
thread. DllMain only arms a narrow interception of the exact Ogre import the
game's graphics bootstrap uses to read `Ogre.cfg`
(`Ogre::ConfigFile::load(const String&, const String&, bool)` via IAT slot
`0x00869D08`); the transport then runs synchronously on the game thread inside
that load call — strictly before stock reads `"Render System="`, exactly once
per process, behind return-address/call-site-byte/filename validation that
fails closed on unsupported executables and fail-open per boot. The Steam ~1 s
startup cannot outrun this seam because the trigger IS the game's own
configuration read. Full rationale, binary facts and validation details:
`reverse_engineering/renderer_startup_backend_selection_20260825.md` §11.

Implementation notes captured by validation:

* An earlier patch-thread placement lost the startup race on Steam (~1 s engine
  init); a direct-DllMain placement fixed the race but did heavy work under the
  loader lock. Both are superseded; neither is the approved architecture.
* Stock's command-line parser strtok()s the PEB command-line buffer in place;
  the transport therefore consumes the DllMain command-line snapshot
  (`cmdline snapshot:` log line).
* On warm-cache Steam boots the hook can fire before renderer-profile
  initialization completes; the hook-time transport parses openshim.ini itself
  (proven by an early `requested=Auto` misfire, then fixed and re-proven).

## GOG install — 11/11 PASS (`gog2`, final build)

| Case | Setup | Asserted outcome |
|---|---|---|
| bs-auto | ini Auto; stock cfg DX11 | `backend.boot: requested=Auto source=stock transport=untouched`; `backend.selection=stock requested=Auto effective=DX11 reason=stock`; Ogre.cfg untouched |
| bs-persist-dx11 | ini DX11; stock cfg DX9 | `backend seam armed:` + `backend seam triggered at ConfigFile::load`; transport `'Direct3D9…' -> 'Direct3D11…'`; boot DX11; `reason=none` |
| bs-persist-dx9 | ini DX9; stock cfg DX11 | boot DX9; `requested=DX9 effective=DX9 reason=none` |
| bs-cli-over-persist | ini DX11 + `/renderer:dx9` | `requested=DX9 source=cli-override`; effective DX9; `reason=cli-override`; stock absorbs DX9 into cfg |
| bs-cli-relaunch | no setup (absorbed state) | transport re-asserts `'Direct3D9…' -> 'Direct3D11…'`; boots DX11 — **the absorption fix** |
| bs-plugin-absent | ini DX11; D3D9 stock line; DLL renamed away | `transport=plugin-missing`; stock fallback DX9; `reason=backend-unavailable`; `preserving requested backend=DX11` |
| bs-device-failure | ini DX11; poisoned FL section (Min>Max) | `transport=written`; process fast-fails (`0xC0000409`) with no window; pending marker survives |
| bs-recovery | clean cfg after failed boot | `previous boot ended before renderer establishment`; normal DX11 override boot; marker consumed |
| bs-killswitch (A) | ini DX11 + `[Startup] BackendTransport=0`; stock cfg DX9 | `transport=disabled ([Startup] BackendTransport=0)`; no write; stock DX9 boots; ini keeps DX11 |
| bs-gl-cli (B) | ini DX11 + stock cfg GL line + `/renderer:gl` | GL recognized-but-unsupported; at-launch cfg still OpenGL; no transport write; stock booted OpenGL; ini keeps DX11 |
| bs-missing-cfg (C) | ini DX11; Ogre.cfg deleted | `transport.bootstrap: Ogre.cfg absent`; `'' -> 'Direct3D11…'`; **DX11 on first boot** |

## Steam install — 7/7 PASS (`steam2`, final build; `steam3` stress rerun 3/3)

Direct launches used a temporary `steam_appid.txt` stub (appid 301650),
removed after the run. Cases bs-auto / bs-persist-dx11 / bs-cli-over-persist /
bs-cli-relaunch / bs-plugin-absent match the GOG contract exactly, including
the absorption fix — **the original Steam race stays eliminated** under the
non-DllMain architecture. New-case subset also passes on Steam:

| Case | Result |
|---|---|
| bs-killswitch (A) | transport disabled line present; cfg untouched (DX9); ini retains DX11 |
| bs-persist-dx11 | seam-triggered transport writes DX11 over stock DX9; boots DX11 |
| bs-missing-cfg (C) | bootstrap minimal image; DX11 on first boot |

## Case D — concurrent transport smoke test

Two fully isolated install copies launched simultaneously with opposite
requests (A: persistent DX11 over stock DX9 line; B: persistent DX9 over stock
DX11 line), harness `tmp/backend_concurrent_smoke.ps1`:

* both processes alive through the window; each root's `Ogre.cfg` ended on its
  own requested backend with its own transport write line in its own log;
* zero stale `*.openshim-*.tmp` files in either root (temp names are
  PID-unique: `Ogre.cfg.openshim-<pid>.tmp`).

## Regression status

* `scripts/run_backend_selection_tests.ps1` — PASS (decision-core tests,
  extended this pass: minimal-config bootstrap image, PID temp-name format,
  kill-switch resolver, GL-over-persistent persistence contract, startup
  filename recognition, plus the pre-existing token/CLI/transport/outcome
  suites).
* `scripts/run_render_profile_tests.ps1` — PASS (existing resolver suite).
* Full Release|Win32 shim build — clean.
* Auto invariance: with `[Graphics] Renderer=Auto` the transport touches
  nothing; bs-auto asserts the untouched path explicitly.
