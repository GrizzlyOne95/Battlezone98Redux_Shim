# Render-Profile Runtime Qualification — 2026-08-24

Merge-qualification pass for the render-profile ownership migration
(`agent/openshim-render-profiles`). Executed against the GOG install
`C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux` using the
headless `lcbench` harness. Driver: `scripts/render_profile_matrix.ps1`
(deploys the branch build, exercises each case, captures
`logs/openshim.log` per case into
`reverse_engineering/snapshots/render_profile_matrix/<case>/`, restores the
pre-existing deployment from `.matrix-bak` backups afterwards).

Result: **10/10 cases PASS** (plus one baseline control case).

## Matrix

| Case | Result | Key evidence (openshim.log) |
| --- | --- | --- |
| DX11 + Redux | PASS | takeover installed ×3 with byte verification; backend observed DX11; `resources compatible=yes`; Redux passthrough produced zero scheme rewrites; modern capability bits set; FXAA presentation attach unchanged |
| DX11 + Enhanced | PASS | effective Enhanced; engine schemes rewritten to `en-*` by the takeover; `enhanced.pssm=yes enhanced.lightSelection=yes`; FXAA attach unchanged |
| DX11 + Enhanced + new EXU (`dx11-enh-exu`) | PASS | canonical chain end-to-end: bridge-capable EXU paired with the new shim |
| DX11 + Retro | PASS | effective Retro; `og-*` rewrites applied by the takeover |
| DX9 + Redux | PASS | backend observed DX9; baseline intact; legacy-only capability bits |
| DX9 + Enhanced | PASS | **effective stays Enhanced** (no silent degrade to Redux); `en-*` SM3 delegates requested through the same policy layer; DX11-only bits honestly absent; no fallback line |
| resources.version mismatch | PASS | `Enhanced unavailable: resource version mismatch (expected=1 got=999)`; `resources.compatible=no`; scheme layer intact so Enhanced remains effective while the standalone retrofit path gates closed |
| resource set absent | PASS | `Enhanced resource set absent (...)` detection; CR-supplied techniques path unaffected |
| old EXU + new shim | PASS | production (pre-bridge) exu.dll keeps working; never touches the new exports |
| new EXU + pre-migration shim | PASS | no `[RENDER]` profile block emitted at all; EXU legacy local behavior unchanged |
| baseline control (`baseline-lightsel`) | PASS | pre-migration winmm+exu on the same harness behaves identically where a suspicion needed ruling out |

## Profile-independence invariants

- FXAA terminal presentation attached identically under Redux and Enhanced
  runs (`attached to swapchain` present in both snapshots).
- Sun-flash suppression, satellite visibility, chunk handling, TRN codec and
  raw-input paths share no call edges with the render-profile subsystem
  (source audit: `src/patches/ogre_render_profile.cpp` references none of
  their initializers), and their startup log lines are byte-identical across
  profile variants.

## Defects the pass caught (fixed in 57ff157d)

1. **Init ordering**: `InitializeOgreRenderProfiles()` ran before
   `RunPatcher()` produced the compatibility verdict, so the scheme takeover
   was skipped on every boot ("unsupported build"). Moved after the patcher.
2. **Backend detection raced Ogre plugin order**: all configured render-system
   DLLs load regardless of which is active, so module-presence polling
   misreported the backend. Replaced with pointer-identity comparison of
   `Root::getRenderSystem()` against `getRenderSystemByName()` for the known
   subsystem names — fully exported API; `RenderSystem::getName()` is virtual
   and NOT exported by this build (dumpbin-verified).
3. **Cached-null export resolution**: the observation thread's function-local
   static lookups executed before `OgreMain.dll` loaded once and stayed null
   for the process lifetime. Resolution now retries until resolvable.

Also restored rate-limited scheme-rewrite logging lost during an SEH refactor,
and re-applied the effective profile when observation lands so late detection
converges immediately.

## Environment artifacts ruled out

- `installed Enhanced-only selector` never fires under lcbench because that
  mission bypasses EXU entirely ("EXU module not loaded"), so the deferred
  retry that drives the light-selector install never runs post-renderer-load.
  The baseline control proved the pre-migration stack behaves identically;
  full-chain selector installation is validated with EXU-bearing content in
  the interactive pass.
- Occasional early process exits during rapid relaunch cycles are
  environmental (GOG/Galaxy overlay timing); the driver retries any case whose
  log shows no `[RENDER]` output.
- First-chance AV lines in `logs/openshim_crash.log` predate this work or are
  continued probes; none correlate with matrix runs.

## Remaining interactive sign-off (before merge)

1. Visual parity captures per profile (terrain/object lighting, shadows and
   cascade transitions, glow, IBL, cockpit, satellite view).
2. In-process Enhanced → Retro → Redux → Enhanced cycling repeated several
   times, watching specifically for material/technique state contamination.
3. Real-content transition matrix: CR mission → shell → stock mission →
   IA/MP → shell; confirm content overrides clear at every boundary.
4. Restart persistence exercised through the actual settings UI rows.
