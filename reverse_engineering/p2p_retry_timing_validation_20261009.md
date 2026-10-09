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

**Status: running; no final live verdict yet.** Compare conservative post-ramp
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
