# Renderer Startup & DX9/DX11 Backend Selection — RE Report (2026-08-25)

> **STATUS: RE COMPLETE / IMPLEMENTATION READY.**
> All primary questions answered; device-failure path and Steam subset closed
> 2026-08-25. Selected seam: Option A (pre-read `Ogre.cfg` transport rewrite).
> Implementation proceeds on an isolated branch; see §7 for the recommended
> shape and the validation matrix derived from §5. No further renderer-selection
> archaeology planned.
>
> **2026-08-25 hardening pass:** implementation complete and requalified; the
> transport's execution moved off DllMain onto a configuration-load
> interception seam — see §11 (the RE findings in §§1–10 are unchanged).

Target: Battlezone 98 Redux **2.2.301**, GOG `battlezone98redux.exe`
SHA-256 `8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413`.
Steam build (`D298782F…`, SteamStub) compared statically where practical.
All addresses below are GOG static VAs (image base `0x00400000`). The shipped
`battlezone98redux.pdb` (2016, mismatched) was **not** used for any address or
behavior claim; Ghidra auto-analysis names (`FUN_…`) are from the repo's
persistent model and were verified against raw disassembly.

Evidence labels: **PROVEN-runtime** / **PROVEN-binary** / SUPPORTED / INFERRED /
UNKNOWN.

---

## 1. Executive finding

**Redux game code selects the backend — not Ogre defaults, not the launcher,
not the registry.** The decision is a four-step ladder executed inside two game
functions before `Root::initialise()`:

1. **Command line override.** `/renderer:dx9|dx11|gl` (also `=`), parsed by
   `FUN_007D5120`, mapped to an exact Ogre subsystem name by `FUN_00663D50`,
   stored in a global desired-renderer string at `DAT_025F8D94`. Case-insensitive.
   **PROVEN-binary + PROVEN-runtime** (matrix case `cmdline-dx9`: cfg said
   DX11, boot came up D3D9).
2. **Persisted preference.** If the global is still empty, the game copies the
   `Render System=` value it just read out of `<game root>\Ogre.cfg`
   (`ConfigFile::getSetting("Render System", "", "")`) into that same global.
   This is the effective "Auto" source. **PROVEN-binary** (`mov ecx,0x25F8D94`
   empty-test → assign from local at `0x66441D–0x66443C`);
   **PROVEN-runtime** (`stock`/`cfg-dx9`/`cfg-dx11` cases).
3. **Validation fallbacks.** `getRenderSystemByName(desired)` is tried; on miss
   the desired name is replaced with the literal `"Direct3D9 Rendering
   Subsystem"`; on second miss with the *name of the first available renderer*;
   a third miss aborts graphics init entirely. **PROVEN-binary**
   (`0x66443C–0x6644CD`); steps 1–2 of the ladder **PROVEN-runtime**
   (`cfg-missing`, `cfg-invalid`, `dx11-plugin-absent` all booted D3D9);
   step 3 (first-available) INFERRED from code only.
4. **Enforcement + persistence.** `FUN_00664905` compares the active render
   system's name to the desired name after `restoreConfig()`; on mismatch it
   walks `getAvailableRenderers()` and calls `setRenderSystem()` on the match,
   then `saveConfig()`. **Whatever becomes active is written back into
   `Ogre.cfg`** — including fallback outcomes (a failed DX11 request rewrites
   the file to DX9). **PROVEN-runtime** (all four non-stock-favorable cases
   ended with `Render System=Direct3D9 Rendering Subsystem` on disk).

Not involved: registry state, GOG Galaxy/Steam launcher state, `showConfigDialog`
(not imported), `ogre.cfg` naming variants, plugin `.cfg` files on current builds.

---

## 2. Native chain

### 2.1 Imports used (IAT slots in battlezone98redux.exe)

| IAT | Import |
|---|---|
| `0x00869CD8` | `Ogre::Root::Root(String pluginFileName, String configFileName, String logFileName)` |
| `0x00869CE0` | `Ogre::Root::saveConfig` |
| `0x00869CE4` | `Ogre::Root::restoreConfig` |
| `0x00869CE8` | `Ogre::Root::getAvailableRenderers` |
| `0x00869CEC` | `Ogre::Root::getRenderSystemByName(String)` |
| `0x00869CF0` | `Ogre::Root::setRenderSystem(RenderSystem*)` |
| `0x00869CF4` | `Ogre::Root::initialise(bool, String title, String)` |
| `0x00869CF8` | `Ogre::Root::createSceneManager` |
| `0x00869D08/D0C` | `Ogre::ConfigFile::load` / `getSetting` |
| `0x00869E80/CFC` | `Root::getRenderSystem` / `getSingletonPtr` |
| `0x00869EC8` | `Ogre::Root::loadPlugin(String)` |

`showConfigDialog` is **not imported** (**PROVEN-binary**). RenderSystem virtuals
(`getName` vtable+4, option get/set at vtable+0xC/+0x10) are called through
vtables, not imports.

### 2.2 Startup sequence (functions, key addresses)

```
CRT startup
 └─ dynamic initializers
     └─ FUN_008677F0 @0x8677F0      default-constructs DAT_025F8D94 = "" (empty)
                                    (desired-renderer global starts empty)
 └─ main → command-line parse
     └─ FUN_007D5120 @0x7D5120      logs "Battlezone98 Command-Line: %s"
         ├─ /win        → FUN_00663D10(0)  → DAT_008ED0C4 = 0 (windowed)
         ├─ /fullscreen → FUN_00663D10(1)  → DAT_008ED0C4 = 1
         │   (DAT_008ED0C4 = 2 is the "unset" sentinel)
         └─ /renderer:TOKEN | /renderer=TOKEN
                        → FUN_00663D50 @0x663D50:
                            "dx9"  → DAT_025F8D94 = "Direct3D9 Rendering Subsystem"
                            "dx11" → DAT_025F8D94 = "Direct3D11 Rendering Subsystem"
                            "gl"   → DAT_025F8D94 = "OpenGL Rendering Subsystem"
                            (case-insensitive _stricmp; unknown token = no change)
 graphics bootstrap
 └─ FUN_00663ED0 @0x663ED0
     ├─ registers path-table entries "Ogre.cfg", "bz_resources.cfg" (0x663F2F)
     ├─ new Ogre::LogManager; createLog("BZOgreLogfile.log"); setDebugOutputEnabled(true)
     ├─ Ogre::ConfigFile::load(<path-table "Ogre.cfg">, …)   ← shares EBP frame
     └─ tail into FUN_00664110 (same frame; ConfigFile stays at [ebp-0x530])
 selection & init
 └─ FUN_00664110 @0x664110
     ├─ 0x664120  getSetting("Render System","","")          ← Auto source
     ├─ 0x664187  getSetting("Full Screen", <that value>, "")→ window-mode bool
     ├─ 0x664260  Root ctor args: logFileName="Ogre.log",
     │            configFileName=<path-table "Ogre.cfg">, pluginFileName=<global>
     │            (plugin-file global is never populated on current builds ⇒ no
     │             plugins.cfg/bz_plugins.cfg read — see §7 open questions)
     ├─ 0x66439A  FUN_00435CA0 hardcoded plugin ladder:
     │              loadPlugin("RenderSystem_Direct3D9") ; LoadLibraryA("D3DCompiler_43.dll")
     │              FUN_00435D41 → loadPlugin("RenderSystem_Direct3D11")
     │              FUN_00435DA5/FUN_00435E45 → loadPlugin("RenderSystem_GL"),
     │              Plugin_ParticleFX, Plugin_CgProgramManager
     ├─ 0x66441D  if DAT_025F8D94 empty → copy cfg "Render System" value into it
     ├─ 0x66443C  getRenderSystemByName(DAT_025F8D94)
     ├─ 0x664454    miss ⇒ assign literal "Direct3D9 Rendering Subsystem"
     ├─ 0x664463  retry ⇒ miss ⇒ take name of FIRST entry of
     │            getAvailableRenderers() (0x664484–0x6644B2)
     ├─ 0x6644B7  retry ⇒ still null ⇒ fatal cleanup (no renderer)
     ├─ 0x66453E  ok; DAT_008ED0C4==2 ⇒ derive mode from Full Screen setting
     ├─ 0x6648BD  try { restoreConfig() } catch @0x6648D7:
     │              "Failed to restore graphics configuration with error: %s"
     └─ → FUN_00664905
 └─ FUN_00664905 @0x664905  (enforcement)
     ├─ reads current RS name; needs-reselect iff restoreConfig failed OR
     │   fullscreen flag mismatch OR current name != DAT_025F8D94
     ├─ loop over getAvailableRenderers(); name == desired ⇒
     │      setRenderSystem(rs)                @0x664BC6
     ├─ saveConfig()                           @0x664BFD  ← persists outcome
     ├─ second restoreConfig() pass; per-game-settings option overrides
     ├─ initialise(fullscreen?, title, "")     @0x6651AB → RenderWindow
     │     title = "Battlezone 98 Redux (2.2.301)" (+ " DX11" suffix iff D3D11)
     │     null ⇒ secondary attempt FUN_00435A40; still null ⇒ abort gfx init
     ├─ FUN_00683620 (another saveConfig site), createSceneManager,
     │   cameras PlayerCam / TargetCam / SniperCam, SniperTex target
 in-session renderer change (options UI)
 └─ FUN_007AF170 @0x7AF170: pending choice (DAT_009455AC) differs from active ⇒
       setRenderSystem @0x7AF237, saveConfig @0x7AF245,
       log "Exiting Game from graphics options changing renderer", exit(0).
       (Stock itself treats backend changes as restart-scoped.)
 other call sites: FUN_007AF4A0 (options UI enumerates getAvailableRenderers),
 FUN_007AEBC0 / FUN_00683620 / FUN_007AF170 (saveConfig),
 FUN_004365C0 (per-backend default option seeding when restore failed),
 FUN_0067C950 / FUN_0067CF50 (graphics options UI, D3D9/D3D11 names).
```

### 2.3 Window-title discriminator

`_createRenderWindow` lines in `BZOgreLogfile.log` (rerouted by OpenShim to
`logs\BZOgreLogfile.log`): `D3D11RenderSystem::_createRenderWindow "Battlezone
98 Redux (2.2.301) DX11"` vs `D3D9RenderSystem::_createRenderWindow "Battlezone
98 Redux (2.2.301)"` (no suffix). **PROVEN-runtime** in every matrix capture.

---

## 3. Configuration source

Single authoritative file: `<game root>\Ogre.cfg`.

```ini
Render System=Direct3D11 Rendering Subsystem   ← THE selector (exact Ogre name)

[Direct3D9 Rendering Subsystem]
Allow DirectX9Ex=No … Full Screen=Yes … Video Mode=…

[Direct3D11 Rendering Subsystem]
Driver type=Hardware … Full Screen=Yes …

[OpenGL Rendering Subsystem] …
```

* Read by game code (`ConfigFile::getSetting`, `FUN_00664110`) **and** by stock
  Ogre `restoreConfig()` semantics inside `OgreMain.dll` — both consumers agree
  because they read the same key. **PROVEN-runtime**: editing only this line
  flips the backend on next launch (matrix cases `cfg-dx9`/`cfg-dx11`).
* Written by `Root::saveConfig()` whenever the game exits cleanly after init or
  applies a renderer change — including fallback outcomes. **PROVEN-runtime**:
  `cfg-missing`, `cfg-invalid`, `dx11-plugin-absent`, `cmdline-dx9` each ended
  with `Render System=Direct3D9 Rendering Subsystem` rewritten on disk.
* No registry involvement found for renderer selection. No per-user redirect;
  state lives beside the exe (relevant for multi-user/multi-install setups).
* Command line `/renderer:` is session-scoped input that gets *absorbed* into
  `Ogre.cfg` by the post-selection `saveConfig()`.

---

## 4. Startup timeline (GOG, OpenShim deployed, measured)

```
t=0        process start; loader resolves imports:
           app-dir winmm.dll (OpenShim) — exe statically imports WINMM
           (timeBeginPeriod/joyGetPosEx…)  [PROVEN-binary]
           OgreMain.dll also loads now (static import) [PROVEN-binary]
t≈0.0s     winmm!DllMain → OpenShim logger "session start"   (05:10:28.382Z)
t≈0.0s+    OpenShim Initialize/patch thread runs; render-profile observation
           thread polls (250 ms × ≤90 s)
t≈+6s      CRT → main → cmdline parse → FUN_00663ED0 creates BZOgreLogfile.log,
           ConfigFile::loads Ogre.cfg                      (00:10:34 local)
t≈+6s      FUN_00664110: Root ctor → hardcoded loadPlugin ladder
           ("Loading library RenderSystem_Direct3D9/Direct3D11/GL…" in log)
t≈+6..8s   seed desired-name → validate → restoreConfig → enforcement loop
           setRenderSystem → saveConfig → initialise → RenderWindow created
t≈+13s     first frames; OpenShim observation resolves active RS and emits
           backend identified/effective diagnostics
```

**OpenShim executes its entire early initialization ~5–6 s before renderer
discovery begins**, and seconds before the preference is read. The existing
`winmm.dll` proxy therefore initializes strictly *before* renderer discovery —
there is ample margin to influence selection safely. **PROVEN-runtime**
(timestamp deltas across `logs\openshim.log` vs `logs\BZOgreLogfile.log`;
identical ordering in all seven captures).

---

## 5. DX9/DX11 startup matrix (runtime, GOG 2.2.301)

Harness: `tmp/render_startup_matrix.ps1` (bounded 35 s `lcbench.bzn` launches;
full backup/restore; snapshots under
`reverse_engineering/snapshots/renderer_startup_matrix/<case>/`). Baseline
deployment: render-profile branch build already installed; no shim redeploy.

| Case | Pre-state | Booted backend | Evidence | Post-run `Ogre.cfg` |
|---|---|---|---|---|
| `stock` | `Render System=Direct3D11…` | **DX11** | `_createRenderWindow "…(2.2.301) DX11"` | unchanged (DX11) |
| `cfg-dx9` | line edited to Direct3D9 | **DX9** | `D3D9RenderSystem::_createRenderWindow` | unchanged (DX9) |
| `cfg-dx11` | line edited back to Direct3D11 | **DX11** | `"…(2.2.301) DX11"` | unchanged (DX11) |
| `cfg-missing` | `Ogre.cfg` deleted | **DX9** (default) | D3D9 window | **recreated**, `Render System=Direct3D9…` |
| `cfg-invalid` | `Render System=Garbage Backend 9000` | **DX9** (fallback) | D3D9 window | rewritten to `Direct3D9…` |
| `dx11-plugin-absent` | wants DX11; `RenderSystem_Direct3D11.dll` renamed away | **DX9** (fallback) | D3D9 window | rewritten to `Direct3D9…` |
| `cmdline-dx9` | cfg says DX11; launched `/renderer:dx9` | **DX9** (cmdline wins) | D3D9 window | rewritten to `Direct3D9…` |

Every case stayed alive through the sample window; no dialogs, no crash, no
retry-another-backend behavior within a boot. Failure modes observed:

* Requested subsystem name absent from loaded plugins → **silent fallback to
  D3D9, persisted to disk on the same boot**. A forced-DX11 preference whose
  plugin is missing is therefore consumed once and erased by the game itself.
* `restoreConfig()` exception path exists (`Failed to restore graphics
  configuration with error: %s`) but did not trigger even with `Ogre.cfg`
  deleted (the game-side `ConfigFile::getSetting` returned "" and the ladder
  handled it); treat it as a secondary safety net.
* Device-level failure with the plugin present: **PROVEN-runtime** (2026-08-25
  addendum, case `df-flmin`). Poisoning the D3D11 section
  (`Min Requested Feature Levels=11.0` + `Max Requested Feature Levels=9.1`)
  makes `D3D11RenderSystem::initialise` throw
  `OGRE EXCEPTION(7:InternalErrorException): Requested min level feature is
  bigger the requested max level feature.` **twice** (the game retries once via
  its secondary-attempt path) while the plugin is present and name validation
  passed. Outcome: the game **aborts with exit code −1** — no dialog, no
  re-entry into the selection ladder, no D3D9 retry. Crucially, the failed boot
  still rewrote `Ogre.cfg` at shutdown, but it only **normalized option values
  to defaults** (`Min=9.1/Max=11.0`) while **preserving `Render System=
  Direct3D11 Rendering Subsystem`**. The follow-up untouched boot (`df-recovery`)
  read DX11 and started DX11 normally — device failure is self-healing and does
  NOT burn the backend preference. Contrast with the name-ladder fallback
  (§5 rows `cfg-missing`/`cfg-invalid`/`dx11-plugin-absent`), which persists a
  real backend change.
  Implication for Seam A: a shutdown-time `saveConfig()` runs even on failed
  boots, so OpenShim must treat `Ogre.cfg` as effective-transport only and keep
  its own requested-state record; it cannot infer "user intent" from the file
  after any abnormal exit.

Steam subset: **PROVEN-runtime** (2026-08-25 addendum, tag `steam`). The Steam
build (appid 301650) requires either a client launch or a temporary
`steam_appid.txt` stub for direct launches; with the stub, the four key cases
reproduce the GOG contract exactly:

| Case | Boot | Post-run `Ogre.cfg` |
|---|---|---|
| valid DX11 config, no override | **DX11** (`"…(2.2.301) DX11"`) | unchanged |
| `/renderer:dx9` over DX11 config | **DX9** — CLI wins | rewritten to DX9 (absorbed) |
| invalid configured renderer | **DX9** fallback | rewritten to DX9 |
| relaunch after fallback | **DX9** from persisted cfg | unchanged |

Behavioral parity holds despite SteamStub encrypting `.text` at rest; the data
seam and selection logic are unaffected.

---

## 6. Intervention options (ranked)

Constraints: Auto must remain byte-for-byte stock; fail-open; restart-scoped;
requested ≠ effective preserved; content can never steer the backend.

### A — Preferred: write `Ogre.cfg`'s `Render System=` line before the game reads it

Pure data intervention; uses the exact persistent value the game itself owns.
Mechanics: when `[Graphics] Renderer=DX9|DX11` (non-Auto) at shim init, rewrite
only that line in `<game root>\Ogre.cfg` (create-from-template if absent, since
the game recreates it anyway). Never touch anything when `Auto`.

Why safest: no executable bytes, no Ogre ABI contact, identical mechanism to
what stock UI and the qualification harness already do, trivially reversible,
and timing risk is nil (shim acts ≥5 s before the read). Validation: check
`RenderSystem_Direct3D{9,11}.dll` presence next to the exe **before** writing a
request; if the requested plugin is missing, do not write (log
`fallback=plugin-missing`) — otherwise stock would persist DX9 and burn the
preference (§5).

Known consequence (acceptable, matches stock UI behavior): the override becomes
the new persisted value after one boot via `saveConfig()`. Idempotent re-write
each launch keeps `Auto` semantics clean; diagnostics must record requested vs
stock-file vs effective.

### B — Acceptable: IAT hook on `Root::getRenderSystemByName` (slot `0x00869CEC`)

The only import through which the validation ladder resolves names; all three
call sites live in `FUN_00664110`. Hook the IAT slot (existing hardened
`iat_patch.h` machinery): when called with a name that maps to OpenShim's
requested backend and that backend's RS exists, return the RS object for the
requested name instead; otherwise pass through untouched. Fail-open default is
one comparison. Byte-validate the three call sites' `FF 15` displacement
before install (pattern already proven by the scheme-takeover work). In-memory,
restart-scoped, nothing on disk changes except stock's own `saveConfig()` of
the effective result. Ranked below A only because it touches executable memory
and Ogre object pointers.

### C — Reject: everything else

* **Rename/block plugin DLLs** — destroys stock fallback semantics, causes the
  permanent cfg rewrite hazard, breaks other installs/tools.
* **Patch the fallback literals / jumps in `FUN_00664110`** — executable patch
  with no advantage over A/B; last-resort only, never for this feature.
* **Registry/launcher/env tricks** — no such mechanism exists (§3).
* **Hooking `restoreConfig`/`initialise`** — broader blast radius than B with
  no added control; reject.
* **In-memory overwrite of the `DAT_025F8D94` std::string object** — requires
  MSVC string-internals-aware writes at a fixed address; strictly worse than B.

---

## 7. Recommended implementation (smallest safe seam)

Implement **Option A** behind the existing `[Graphics] Renderer` key:

1. In `InitializeOgreRenderProfiles()` (or immediately after INI load, well
   before the patch-thread's Ogre waits):
   * `Renderer == Auto` → return; emit `backend.selection=stock`; touch nothing.
   * Else resolve target name (`Direct3D9|Direct3D11 Rendering Subsystem`),
     verify sibling `RenderSystem_Direct3D{9,11}.dll` exists; if missing → log
     `backend.fallback=plugin-missing`, leave file alone.
   * Read `Ogre.cfg`; if line already correct → no write. Else rewrite only the
     `Render System=` line (atomic replace; keep every other byte).
   * Emit diagnostics in the established format:
     `backend.requested=DX11 backend.stock=<file value before edit>
     backend.selection=override` and let the existing observation thread supply
     `backend.effective=` afterwards; on any deviation emit
     `backend.fallback=<reason>` exactly as specified.
2. Preserve ownership rules: EXU/content bridge remains profile-only; nothing
   content-reachable may call the new writer; opt-out via existing settings
   plumbing (`Renderer=Auto`, plus an explicit `[Startup] RendererOverride`
   kill-switch defaulting to enabled-once-proven).
3. Keep the options-UI row hidden until a full matrix re-run passes both
   backends on GOG and Steam.
4. Add regression coverage: extend `render_profile_matrix.ps1` with
   `startup-dx9`/`startup-dx11`/`startup-auto-no-touch` cases asserting the new
   diagnostic substrings and that `Auto` leaves `Ogre.cfg` byte-identical.
5. Implementation gate status: the seam is decisively proven (§5); prototype
   may proceed on an isolated branch per the task constraints. Do not merge
   until Steam subset passes and the `Auto` no-touch invariant is asserted by
   tests.

---

## 8. Steam portability

* On-disk PE: identical section layout for `.text/.rdata/.data/.rsrc` plus an
  extra `.bind` section; DIE identifies **SteamStub**. `.rdata` strings are
  plaintext at the same file offsets as GOG (verified: `Ogre.cfg`,
  `"Render System"`, plugin-name cluster, failure-format string).
  **`.text` is encrypted at rest** (byte-level diff at `0x664120` shows
  ciphertext; self-decrypts at load). Therefore GOG static addresses hold on
  Steam **only after runtime settling** — consistent with AGENTS.md. Option A
  is unaffected (data-only). Option B's validations must run post-settle, which
  the existing runtime-byte conventions already require.
* Configuration mechanism identical: same code paths, `Ogre.cfg` in the Steam
  root (currently `Render System=Direct3D9 Rendering Subsystem`).
* Timing shifts slightly (steam_api init precedes engine init); winmm proxy
  loading is unchanged (static import resolution happens before steam_api work).
  The ≥5 s pre-read margin is expected to hold but was not measured on Steam.
* `bz_plugins.cfg` present in the Steam root is **inert on current builds**
  (neither exe contains any reference to a plugins-cfg filename; plugin loading
  is hardcoded). It is almost certainly residue from the `ogre_plugin_probe`
  experiment era; removing it is safe cleanup but unproven on a Steam launch.

## 9. Open questions

* ~~Device-level D3D11 initialization failure~~ — **closed 2026-08-25**: aborts
  with exit −1 after one retry; preference preserved; see §5 addendum.
* ~~Steam runtime launch subset~~ — **closed 2026-08-25**: four-case matrix
  matches GOG exactly; see §8.
* Final ladder step ("first available renderer" when even D3D9 is absent):
  PROVEN-binary only; deliberately not exercised (would require renaming two
  system-dependent DLLs).
* Whether GOG Galaxy/Steam launch shortcuts ever inject renderer-related args
  in default installs (parser support is proven; default-argument usage is not
  observed).
* Exact semantics of `DAT_008E7068` (both `/enablerenderselection` and
  `/disablerenderselection` write 0; suspected vestigial render-dialog flag).
  No impact on the selected design.
* `FUN_00427310` (name-compare helper gating `setRenderSystem` in the
  enforcement loop) decompiles as plain string equality; accepted without
  instruction-level verification.
* Which exact code path performs the shutdown-time `saveConfig()` on failed
  boots (observed effect: option normalization + Render System preserved);
  mechanism inferred to be the default-seeding retry path (`FUN_004365C0`)
  followed by an exit-path save. Effect is proven; the specific writer is not
  pinned and does not affect Seam A's design.
* Long-run SteamStub settle behavior for runtime-byte equality (AGENTS.md notes
  builds match post-settle) — irrelevant to Seam A, relevant only if Seam B were
  ever revisited.

## 10. Artifacts

* Matrix drivers (scratch, untracked): `tmp/render_startup_matrix.ps1` (phase 1),
  `tmp/render_startup_matrix2.ps1` (device-failure + Steam subset)
* Per-case evidence:
  * Phase 1: `reverse_engineering/snapshots/renderer_startup_matrix/<case>/…`
    + `matrix_summary.json`
  * Device-failure: `reverse_engineering/snapshots/renderer_startup_matrix2/gog-df/
    df-flmin.*` (atLaunch/after cfg, ogre log with the double
    `InternalErrorException`, BZLogger, shim log), `df-recovery.*`
  * Steam subset: `reverse_engineering/snapshots/renderer_startup_matrix2/steam/
    s-*.…` (same artifact set per case)
* Prior qualification snapshots corroborating observation behavior:
  `reverse_engineering/snapshots/render_profile_matrix/{dx11-redux,dx9-redux}/`

### Testing note for the Steam build

Direct exe launches exit with code 53 (steam_api init failure). For headless
test runs, write a temporary `steam_appid.txt` containing `301650` next to
`battlezone98redux.exe` (Steam client running) and delete it afterwards; this
is the standard steam_api dev bypass and was used for the matrix above.

---

## 11. Implementation/hardening addendum — startup execution rework (2026-08-25)

> **STATUS: HARDENING COMPLETE.** Same Seam A data transport, new execution
> seam. This section documents why the two earlier execution placements were
> rejected and pins the final architecture. Sections 1–10 above are unchanged
> RE findings.

### 11.1 Execution-placement history

* **v1 — patch thread (rejected).** The transport ran from OpenShim's patch
  thread shortly after `DLL_PROCESS_ATTACH`. On the Steam build the engine can
  reach graphics init in ~1 s, and the patch thread (queued behind several
  other initializers) lost that race: the game read Ogre.cfg before OpenShim
  wrote it, observed as spurious `backend-unavailable` on bs-persist-dx11.
* **v2 — direct DllMain execution (rejected).** `RunStartupBackendSelectionEarly()`
  was invoked directly under `DLL_PROCESS_ATTACH`, which did eliminate the
  race but performed substantial work while the loader lock was held: INI
  parsing, `std::string`/`std::filesystem` operations, SRW-lock acquisition,
  multiple file reads/writes, temp-file creation, `MoveFileExW`, directory
  manipulation, logging, and pending-marker handling. Too much for DllMain;
  any fault or loader-service dependency there risks deadlock or a dead process.

### 11.2 Final architecture — configuration-load interception seam

```
DllMain(DLL_PROCESS_ATTACH)
    ├─ CaptureCommandLineSnapshot()      bounded copy only (unchanged)
    ├─ InstallStartupBackendSeam()       identity checks + one IAT pointer swap
    └─ return from DllMain               no backend transport here
         ↓
Redux reaches its graphics bootstrap (FUN_00663ED0)
         ↓
game thread calls Ogre::ConfigFile::load(<root>\Ogre.cfg) through IAT 0x00869D08
         ↓
shim hook: validate retaddr/call-site bytes/filename argument
         ↓ (exactly once)
OpenShim runs the full backend transport ON THE GAME THREAD
(ini parse, plugin pre-validation, temp+MoveFileEx write, pending marker)
         ↓
original ConfigFile::load continues unchanged; stock ladder reads our line
```

The trigger is the game's own configuration read, so the Steam ~1 s startup
cannot outrun it by construction — the race is structurally gone, not merely
narrowed.

### 11.3 Binary facts used by the seam (all verified this pass)

| Fact | Value |
|---|---|
| Import | `Ogre::ConfigFile::load(const String&, const String&, bool)` |
| Mangled name | `?load@ConfigFile@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0_N@Z` |
| IAT slot | VA `0x00869D08` / RVA `0x00469D08` (OgreMain.dll import table, slot 377) |
| Startup call site | `0x006640E4` = `FF 15 08 9D 86 00` inside FUN_00663ED0 (return address `0x006640EA`) |
| Other callers | one more at `0x0066471E` inside FUN_00664110 — excluded by the return-address gate |
| `.rdata` identity marker | `"Ogre.cfg\0"` at VA `0x00892030` (identical both storefronts, plaintext even under SteamStub) |
| SizeOfImage | GOG `0x290F000`; Steam `0x292F000` (extra `.bind` section) |

Full `.text` scan of `FF 15 <0x00869D08>` found exactly those two call sites;
every other address in §2.1's IAT table was cross-checked the same way
(`restoreConfig@0x6648BD`, `setRenderSystem@0x664BC6`, `initialise@0x6651AB`,
options-UI `setRenderSystem@0x7AF237`, etc.), matching §2.2.

### 11.4 Hook validation (fail closed at install, fail open per boot)

Install-time (DllMain, loader-lock-bounded, **no `.text` access**, so
SteamStub-at-rest bytes are never consulted):

1. main module filename is `battlezone98redux.exe`;
2. PE `SizeOfImage` ∈ {GOG `0x290F000`, Steam `0x292F000`};
3. plaintext `.rdata` marker `"Ogre.cfg"` present at the qualified VA;
4. `OgreMain.dll` loaded (static import) and exports exactly the mangled name;
5. IAT slot `0x469D08` currently bound to that export.

Any miss ⇒ no hook installed; the feature is inert and selection is pure stock.

Call-time (game thread; `.text` settled by definition because the CPU is
executing it): return address == `0x006640EA` AND the six call-site bytes still
read `FF 15 08 9D 86 00` AND the first string argument names `Ogre.cfg`
(bare name or any path ending in `\Ogre.cfg`). Only then does the one-shot
atomic latch open and the heavy transport run; everything sits behind an SEH
boundary so a fault degrades to stock behavior for that boot. Unrelated
`ConfigFile::load` traffic passes through untouched.

Ordering note proven by runtime evidence: on warm-cache Steam boots the hook
can fire BEFORE the patch thread finishes renderer-profile initialization, so
the hook-time transport parses `openshim.ini` itself instead of assuming the
initializer already did (caught as `requested=Auto` in an early steam2-pre
matrix run, then fixed and re-proven).

### 11.5 Missing-Ogre.cfg bootstrap (closes the old one-boot limitation)

When `[Graphics] Renderer` is DX9/DX11, the requested plugin exists, and
`Ogre.cfg` does not exist (or is zero bytes), the transport writes a minimal
single-line image:

```
Render System=<requested subsystem>\r\n
```

Stock's own default-seeding path completes every remaining option on the same
boot (§5 case `cfg-missing` proved the game fully recreates the file even from
nothing; the minimal image is strictly better-formed than absence). Runtime
proof: bs-missing-cfg boots DX11 on the FIRST boot on GOG and Steam, with
`transport.bootstrap:` + `'Render System=' '' -> 'Direct3D11…'` diagnostics.
The writer remains fail-open: unreadable-but-present files still abort the
transport (stock selection preserved), matching the refuse-to-touch policy.

### 11.6 Process-unique transport temporary files

Temp name is now `Ogre.cfg.openshim-<pid>.tmp` (pure helper
`MakeTransportTempFileName`, unit-pinned), so two concurrent game processes
never share a temp path and cleanup deletes only the exact file this process
created. All known failure paths (temp open, short write, move failure) remove
the temp file; successful moves consume it atomically via `MOVEFILE_REPLACE_EXISTING`.
Concurrent smoke test (two isolated install copies, opposite requests, same
moment): both configs landed on their own requested backends, zero stale temps.

### 11.7 Kill switch and GL precedence (new pinned cases)

* **Case A (`bs-killswitch`)**: `[Graphics] Renderer=DX11` +
  `[Startup] BackendTransport=0` + stock cfg line DX9 ⇒ no Ogre.cfg write,
  stock DX9 boots, ini keeps DX11, log states
  `transport=disabled ([Startup] BackendTransport=0)`. Passes GOG + Steam.
* **Case B (`bs-gl-cli`)**: `/renderer:gl` over persistent DX11 ⇒ OpenShim
  recognizes GL as explicit-but-unsupported, leaves the stock GL request in
  place (at-launch cfg still reads OpenGL when the game boots), performs no
  transport write, and the persistent DX11 preference survives for the next
  normal boot (resolver statelessness unit-pinned). Runtime observation
  confirmed stock selected OpenGL.

### 11.8 Qualification status

Final matrices: GOG 11/11 and Steam 7/7 (+ a 3-case Steam stress rerun),
documented in `Docs/BACKEND_SELECTION_RUNTIME_QUALIFICATION_20260825.md`;
snapshots under `reverse_engineering/snapshots/backend_selection_matrix/
{gog,gog2,steam,steam2,steam3,concurrent}/`. Regression suites
(`run_backend_selection_tests.ps1`, `run_render_profile_tests.ps1`) and the
full Release|Win32 build pass on the final code.

### 11.9 Loader-lock audit (what remains in DllMain)

Backend-selection path reachable from `DllMain(DLL_PROCESS_ATTACH)`:

1. `CaptureCommandLineSnapshot()` — one bounded `strncpy_s` into a fixed
   static buffer (pre-existing; retained deliberately: the stock parser
   destroys `/renderer:` tokens before any later reader could see them).
2. `InstallStartupBackendSeam()` — module-name check, PE header reads,
   `GetProcAddress`, one guarded 4-byte slot read, one `VirtualProtect`
   round-trip, one guarded 4-byte store, `FlushInstructionCache`. No CRT
   containers, no filesystem, no normal logger calls, no waits, no `.text`
   reads, no process-wide mutations beyond the single reversed pointer. The
   result is stored as a fixed enum and logged later by the patch thread after
   the loader lock has been released.

Everything else (INI parse, resolver, plugin stat, config read/write, temp
file, marker, logging) executes on the game thread inside the intercepted
`ConfigFile::load`. Nothing unsafe was relocated INTO DllMain to make this
work — DllMain does strictly less than the rejected v2 design.
