# Co-op recovery, 15 October 2026

Recovered the interrupted October 14 validation work without modifying its dirty
checkout. The work is on `agent/coop-recovery-20261015`, based on current
`origin/main` (`d2443580d`); the open startup-hash and DLSS PRs did not change
these harness files. Campaign fixes are on CR's `agent/coop-validation-20261015`.

## Harness fixes

- Fail the verdict on both `Ogre Rendering Exception Seen:` and
  `Ogre Rendering Exception Seen from UI:`. Lua commands can keep responding
  while every frame throws. Do not accept that as a rendering smoke.
- The watchdog closes game clients through `Stop-BZRGame -Id -NoForce`, including
  when walking a coordinator's child tree. A game that ignores WM_CLOSE remains
  alive with its session record; its coordinator tree is retained.
- Private local-server launches pin the disposable clients' network route to
  Relay. Repository-default Stock routing reached the lobby but stalled at
  simulation Network Part 2, repeatedly rejecting a peer's source address.
- A second Create Game click handles a lost background-lounge activation click.
  The modal ignores that point once open; creation is still submitted once.
- `render-smoke` observes every client's probes for 45 seconds, then checks
  actual device-recreation diagnostics. It does not match the informational
  installation line that says recovery waits for the adapter to settle.
- Windows CI now exercises the log-verdict, participant and watchdog fixtures.

## DX11 source findings

The failures are reproducible with an active RDP desktop and no device-recreation
diagnostics. They must not be attributed to a driver problem without evidence.

Live inspection of Ogre's exported vertex-declaration/program methods identified
`CR_UI_vertexHLSL4` requiring POSITION0, COLOR0 and TEXCOORD0 on a panel that only
supplies POSITION0 and TEXCOORD0. CR's `CR_UI` material now chooses its existing
dedicated panel programs on DX11, preserving the previous backend fallback.

After that repair, a second error became visible: standalone `ScriptSubtitles`
in missions without `PersistentConfig` had no palette border material. Ogre's
BorderPanel queues its border anyway and substitutes shaderless
`BaseWhiteNoLighting`. CR now binds an explicit fallback border material before
showing the overlay. Both repairs belong to CR's content, not an engine address
patch or exception suppression.

One exception-tracing attempt crashed inside `frida_agent`; its dump was inspected
and the run is excluded from acceptance. The successful final control had no
instrumentation attached.

## Validation checkpoint

Evidence is local under `C:\BZRCoop\runs\`:

| Run | Result |
| --- | --- |
| `recovery1015-misn11-control` | Reproduced renderer failures with the installed Enhanced configuration; responsive Lua was not accepted. Its initial scenario device-pattern check also matched an informational line; that pattern was corrected. |
| `recovery1015-misn11-defaults` | Stalled in native network initialization under Stock route; stopped gracefully. |
| `recovery1015-misn11-relay` | Entered the mission after selecting Relay; DX11 vertex-layout failures remained. |
| `recovery1015-misn11-dx9` | PASS, four steps / 17 checks; diagnostic comparison only. |
| `recovery1015-dx11-trace` | Reproduced the original missing COLOR0 requirement. |
| `recovery1015-dx11-panel-fix` | Vertex-layout error removed; exposed missing-shader subtitle border error. |
| `recovery1015-dx11-subtitle-fix` | **PASS**, four steps / 17 checks, two DX11 clients, no Lua/rendering/unresolved-label errors or device-recreation diagnostics. |

OpenShim's 107/107 Release Win32 CTests pass. Log-verdict, participant, session IO,
diagnostics and watchdog PowerShell fixtures pass. CR's material-selected shader
reflection regression, 232 shader compilations, 17 mutation fixtures, Lua helper
suites and repository invariants pass at this checkpoint.

The native test chain is the already configured GOG test setup, copied from the
startup-hash build `a15765d27` (OpenShim #479), with freshly built EXU main
`043c2434d`. OpenShim DLL SHA-256:
`DEE8C2B10F0875CFC6AEAF5CE3A98E28121B575A3355E850F56557162AB46A4A`.
The existing DedicatedServer checkout is `50b6b14d8`; it is bound to loopback.
Current CR shipping-lock members were flattened into a private test stage, with
the source fixes and fresh EXU applied. Nothing was uploaded to Workshop.

Further live assistance and mission checks are recorded in the continuation of
this document. These controls do not establish full mission completion, remote
two-PC play, Steam delivery or Proton/Wine qualification.

## Continued native acceptance

CR repairs and the closed-PDA V/Z polling fix are in draft
[CR #214](https://github.com/GrizzlyOne95/Battlezone98Redux_CampaignReimagined/pull/214).
This harness is draft [OpenShim #480](https://github.com/GrizzlyOne95/Battlezone98Redux_Shim/pull/480).
Both Linux CTest and Release Win32 CI passed at `00212685b`.

An additional lost background click left a guest's game row unselected, so Join
was inert. Lobby automation now repeats only the idempotent row selection;
Join remains a single submission. The subsequent lobby and native session passed.

`recovery1015-assist-dx11-boarding/recovery1015-assist-dx11-services`
passes eight steps / 14 checks on two DX11 clients. It covers terrain markers,
expiry without destroying an existing objective, help/reply/cancel, same-object
adoption and guest movement orders, recall, and native rescue arrival. A native
probe confirmed the rescue craft empty at 28.04 m, command NONE. The user clarified
that this is sufficient rescue acceptance: boarding is the stock walk-into-craft
transition and H only hops out. No forced boarding or ownership mutation is used.

The first transfer fixture ran before initializing the recipient id; its Lua
false/reason tuple was mistakenly truthy to the fixture. The corrected fixture
initializes the id and compares the service's first return explicitly with true.
Only the subsequent successful run is acceptance. Earlier boarding and aiming
fixture failures are retained, not reclassified as product failures.

Physical X passed on both clients and native mouse aiming enabled a real J ping.
The physical V closed-PDA failure then exposed a source bug in CR's network
polling gate, now repaired in #214 with 24 edge/chat regression checks. Fresh
three-client witness and later mission controls are still being recorded.

## End-of-validation exit guard

The three-client witness run completed all nine scenario steps, including the
original unit's team/ownership change on the witness. Switching to intentional
foreground aiming then tripped BZRHarness's existing anti-focus-steal watchdog.
Its log records WM_CLOSE to scoped test clients; all exited with code 0 and no
new dump. The emitted PASS is not full acceptance because the clients disappeared
during final validation. Keep that artifact as bounded step evidence only.

The runner now records a mandatory final process-liveness check after log/probe
validation, honoring CRFlowExpectedExit for intentional departure scenarios.
Five regression cases cover live peers, a late unexpected exit, intentional host
departure, a missing coordinator, and an entirely exited session with clean logs.
The hands-on rerun explicitly disables only the foreground-focus watchdog via
its existing BZR_NO_FOREGROUND_WATCHDOG switch. Windowed mode and the graceful
session/hard-timeout teardown policies remain in force.

## Final local acceptance

`recovery1015-assist-three-final` passes nine steps / 22 checks including all
three clients alive at final validation. A nested physical-input run passes five
steps / 22 checks: X, native terrain-reticle J, closed-PDA V, Backspace cancel and
chat suppression without replay. Full physical Z aim-to-transfer remains open;
the experimental placement did not establish its native reticle precondition.

DX11 Enhanced controls for missions 12, 13 and 14 each pass four steps / 18 checks
with two clients, 45 seconds of observation, parity and final process survival.
They establish startup/render health, not full mission completion. Mission 15
was neither edited nor launched. Long assistance sessions have audio-pool
warnings, so physical-input acceptance does not qualify voice-over timing.

The new [EXU draft #110](https://github.com/GrizzlyOne95/ExtraUtilities/pull/110)
adds a guarded local kill-notice presentation switch and read-only native player
stats snapshots. CR #214 defaults notices and the stock scoreboard off once per
co-op mission while preserving M. `recovery1015-coop-hud-qualified` passes seven
steps / 15 checks on two DX11 GOG clients: identity/stats parity, physical M toggle,
reversible notices and a controlled guest death advancing deaths/lives on both
peers with notices hidden and kills unchanged. Clean Lua/Ogre checks and final
client survival pass. Both clients and the loopback server were stopped gracefully.

OpenShim Linux CTest and Release Win32 CI pass at `e635493c9`, which incorporates
the upstream main merge containing the already-tested startup-hash fix (#479).
Native tests keep the same installed startup-hash DLL described above. The final
HUD run replaces EXU with a fresh build of branch checkpoint `ef53397`; private
stage/provenance manifests record hashes. No real-install deployment or public
publication occurred. Windows Steam, Proton/Wine and two-PC qualification remain.
