# Guarded retry timing qualification - 2026-10-09

The next reliability experiment compares existing guarded retry settings:
stock **1000/2500 ms** versus **300/800 ms** (first retry / later retry).
Every arm keeps the reliable-send backlog fix ON. The native DLL, wire
format, acknowledgement behavior and shipped defaults are unchanged.

## Hardening implemented

- `Run-P2PRetryBattleMatrix.ps1` runs four prepared internal battle clients,
  records the complete plan, verifies their matching load chains, and retains
  maximum network captures. Alternate passes reverse timer order.
- `P2PRetryTiming.ps1` accepts only decimal values in the native 50..10000 ms
  range, validates every INI before writing any, refuses repeated Network
  sections, and persists original bytes privately before the first write.
  It restores exact bytes only after all games have exited. A surviving game
  stops the next arm and defers restoration; never force-kill a game.
- `p2p_netfix_score.py score --timers first/interval` requires each archived
  INI to match the intended values and each native log to contain unique
  matching apply evidence. Stock values need a verified stock skip; overrides
  need both the requested value and a successful four-byte guarded write.
  Missing, ambiguous or wrong evidence produces ARM_MISMATCH once the other
  infrastructure evidence is complete. Historical scores without this option
  retain their original classifications.
- Matrix aggregation keeps timer arms separate and rejects a score that uses
  different timers, lacks verified apply evidence, or uses a different
  impairment profile. Gameplay acceptance does not replace native health.

Targeted verification: **41 Python tests passed**, including negative native
apply/config/matrix attribution fixtures. Windows PowerShell 5.1 passed
multi-client prevalidation, section isolation, durable backup and exact byte
restoration checks. Release x86 build and **81/81 CTest tests passed**.
An existing completed battle's archived stock evidence verified on all four
clients. The runner is an internal Windows test tool; Steam, Proton/Wine and
WAN runtime qualification remain unverified.

## Live experiment

Private control `retry-battle-control-20261009-182000` and matrix
`retry-battle-matrix-20261009-182000` started at 18:19 CDT. Its first stock-timer
arm stopped INCOMPLETE before impairment/combat: all four clients recorded a
DX9 device-loss/null-read crash at `RenderSystem_Direct3D9.dll+0x2213E`.
The active display changed from the phone-RDP 600-pixel mode to the normal
three-adapter desktop; the user subsequently confirmed direct sign-in. This
is consistent with a display transition, not proof of a networking cause.
No shorter-timer arm ran. Stock timer evidence verified on all four clients.
At 18:24 CDT an independent audit rehashed all 128 restored targets: zero
mismatch and zero games. Original failed score, logs and dumps remain private.

A fresh control/matrix with suffix `20261009-182600` started at 18:24 CDT
on the direct desktop with the original DX9 renderer and 1280x720 windowed
mode. The first failed matrix is retained separately. Planned profiles:

| Profile | Timer arms | Workload |
|---|---|---|
| 3% loss, seed 212 | 1000/2500 and 300/800 | 80 fighting AI, 16 MAV/nav beacons, 64 ammo/repair objects, 60 steady simulation seconds |
| 3% loss, 256 kbit/s per sending player, 200 ms queue limit, seed 213 | 1000/2500 and 300/800 | Same workload |

The outer controller backs up the full deployment/display/autosave targets,
deploys the matching Release chain, adapts the current phone-RDP mode, and
restores and hashes all targets after graceful teardown. The inner runner
also keeps exact timer backups per arm. Raw logs, payloads, endpoint identities
and original configuration backups remain private outside Git.

The `182600` retry never launched: the new outer matrix lock and the mission
coordinator's deliberate lock-state clearing caused a nested-lock wait. Root
stopped only the verified waiting coordinator; no game was running. The child
finally cleaned its local server and restored the files. Independent audit:
128 targets, zero mismatch, zero games. The harness now has an explicit
inherited-lock-owner option: it verifies a live ancestor, matching environment
and a held common mutex, and forbids keep-running/attach/play. Real-child
PowerShell 5.1 tests accept held ownership and reject wrong/free ownership.
Default coordinator-owned launch behavior is unchanged. Battle-harness Release
x86 CTest passed 79/79.

The corrected `183000` trial launched four clients, then stopped INCOMPLETE
before impairment/combat because the host never completed admission. The
passive lifecycle trace captures Q from one guest before Initialize, a K reply,
then Initialize clearing the ready flag and handle. The acknowledged guest
never requests another Q. Independent source/submission/receive audit confirms
both Q and K arrived; this state reset is not explained by relay loss.
All four stock timer configs/native logs verified; no crashes. Independent
restoration recheck at 19:24 CDT: 128 targets, zero mismatch, zero games.
Original failed scores and matrix plans stay retained.

The narrow CRCoop fix consumes early Q/K/P without admission/ACK until
Initialize completes, allowing existing guest retries to complete afterwards.
Its Lua regression fails on the original source and passes on the fix; existing
registry and three complete-script campaign checks pass. A private
`193200` trial is now active, using exactly this admission-only diff on the
respawn-enabled immutable test baseline in every arm. Variant SHA256:
`438DA35AAD3EF65A45881784466EFCDE105CEB3C0ED1D22815D885B080880B4E`.
Canonical CR owns the fix in `Scripts/CRCoop.lua`; it is not published to
Workshop or the user's installed campaign. The plan records override and
harness hashes and refuses an override changed between arms.

**Status: stopped INCOMPLETE; no timer comparison is qualified.** Compare conservative post-ramp
windows with equal duration, retaining pre-window sequence state. Report
modeled blackout/accepted-update age, repeat reliable sequences, modeled
accepted duplicates, per-sender datagram byte rates, queue/drop behavior and
observed seqB progress. Wire progress does not establish when a native sender
processed an ACK; relay forwarding/submission is not native acceptance.
Equal seeds configure equal profiles, not identical loss schedules across
nondeterministic battles. RDP/probe simulation samples do not measure FPS.

Keep stock retry defaults until repeated clean/loss/burst/delay/bandwidth and
long-session comparisons establish benefit without traffic regressions. The
earlier services failure, admission failures, receive-capture discrepancy and
native rejection-frequency failures remain open.


## Completed stock arm and navigation interruption — 19:37 CDT

Trial `193200` completed the stock 1000/2500 arm under 3% loss seed 212:
80 steady fighting AI for 60 simulation seconds, 23 natural vehicle deaths,
94 new observed scrap handles, 16 beacons and 64 ammo/repair objects created.
Gameplay and cleanup passed; native rejection-frequency health failed, so
the full flow remains FAIL despite scorer class IMPAIRED_OK. Stock timer
configuration/native evidence verified on all four clients; no new crash or
GPU error was recorded. The host initialized before its incoming Q messages;
this arm did not reproduce the host race. Early guest Q was consumed without
admission and subsequent startup converged with the guard active.

Independent audit: 55,114 decisions = 53,446 submitted copies + 1,668 intended
loss drops across twelve links; zero missing outcomes, correlation errors or
source-TX mismatches. Four captures were clean/untruncated with zero dropped
events and full binary retention. Ninety-nine other target RX deficits remain,
84 after final target P2P RX and nine in the conservative 55.913-second
post-ramp interval. No same-hash copy ambiguity. That interval contains 28,369
submitted copies / 3,574,544 opaque UDP payload bytes. Socket submission does
not establish delivery or native acceptance. Queue wait p99/max was
0.166/76.947 ms; socket-call p99/max 0.057/0.510 ms.

The second, 300/800 arm timed out at `c0-lounge` before impairment/combat.
Its retained host screenshot shows Options rather than the expected lobby.
Four captures archived cleanly, with zero relay decisions. Both rate/queue
arms did not run. No completed pair or timer benefit can be claimed; defaults
remain 1000/2500. All four clients closed gracefully, the orphaned private
server stopped after client exit, and the outer controller restored its files.
Independent rehash at 19:36:59 CDT: 128 targets, zero mismatch and zero games.
The inherited-lock real-child test passed again after controller exit.

## Earlier build and UI provenance assessment (corrected below)

All four test clients used the same Oct 8 Release DLL, version 1.0.0.47,
SHA256 `7C2D20C047CAAB54D1D01C608A405CCD374A28972DDEC65F057514A3FC8E9C22`.
The ordinary GOG install held version 1.0.0.34 before catch-up. The top-level
stock Options layout in the user's screenshot is also present in current main;
the redesigned Settings and Keybind pages are separate sub-pages. Both source
fallbacks and the shipped INI default General/SettingsUi and CustomBindsUi ON.
The user requested those existing redesigned pages enabled by default, with
the top-level menu retained. Current main was fetched and merged after the
interrupted matrix; that merge changed the shared Lua guide and its test pin,
not native code or UI resources. Release x86 build, 81/81 CTest, INI policy/
writer/migration checks and network baseline validation passed before GOG
deployment. Runtime/deployment evidence is recorded separately below.

## Consolidated native UI build and local GOG catch-up

The initial main-only UI assessment above was incomplete. The intended category
hub and painted keybind implementation were on `ui/native-screens`, with
original commits `a9b567aa`, `3b3342fe` and `6ce2b808`. Turning on the existing
INI flags exposed the earlier flat UI because that implementation was absent.

`agent/gog-ui-network-catchup` now includes the native UI, network battle load,
impairment matrix, four-client tooling and latest device-loss/backlog branch
tips, plus current main. Combined Release x86 build, 82/82 CTest, INI checks,
network baseline and 41 Python P2P tests pass. Local GOG runs the new plugin
SHA256 `A1A3966EF25205634BF521485D700F75533076A5CEB8443FC4ADFA52763D6D4F`,
with matching full load chain, patch JSON and all 17 UI images. Actual GOG
Options/category hub/Video/Back/painted keybind smoke passes; the process
closed gracefully and display/input files were restored. These menu checks do
not rerun or alter the historical four-client results above.

Canonical Campaign Reimagined combines its admission guard and four-player
mission work; its manager packages the same native suite and complete UI
assets. Final local GOG shipping verification covers 3,789 files with zero
missing/differing/unexpected managed files. Existing INI preferences remain,
both redesigned pages are ON, and stock retry defaults remain 1000/2500.
The unified source map, related review links, exact deployed hashes and
qualification limits are in
[`Docs/NETWORK_UI_INTEGRATION_20261009.md`](../Docs/NETWORK_UI_INTEGRATION_20261009.md).
