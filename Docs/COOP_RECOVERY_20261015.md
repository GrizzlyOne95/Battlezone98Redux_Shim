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
