# Reliable-send backlog qualification (GOG, local four-player relay)

## Scope and inputs

GOG Redux 2.2.301, four disposable windowed DX9 clients on one Windows PC,
CR/EXU `misn05-coop` content, full native/shim/server capture, muted audio with
native playback enabled. No artificial loss, duplication or reorder injection.
Both retry timers remain stock (1000 / 2500 ms). The ON/OFF comparison changes
only `OPENSHIM_DISABLE_RELIABLE_SEND_BACKLOG_FIX=1`.

Client source: `53bae101` on `agent/p2p-reliable-backlog`. Matrix server:
`50b6b14` on `agent/four-client-relay`, using private ephemeral pair ports.
Harness: `d5a22aa2` plus its existing local capture/audio/session changes;
actual script hashes and dirty status are recorded in the runtime manifest.
Every generated content override file is hashed in `content-provenance.json`.

| Artifact | SHA-256 |
|---|---|
| GOG executable | `8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413` |
| OpenShim DLL | `12C7763B44A56B66D1D1041D5BEE641FA4F3F82A88087625C8FE106D529A0073` |
| winmm DLL | `CCD4E053567A284BAE033CA5B086D41098062CBFA87962E396758CF619E95267` |
| Patch registry | `5CE33CD29A91AFF8195A387355A036BFF7BB373C968C3B9625473AA9D45A79CD` |

All four instances matched the source load chain before launch. Static scans
found each of the three native signatures exactly once. Live memory reads
confirmed the six-byte NOP gate with the fix enabled, the stock conditional
branch with it disabled, and unchanged 1000/2500 ms timers.

## Checks before the matrix

Release Win32 build, 80 CTests, 179 INI settings (including writer/preset
migration checks), and the conservative network baseline passed. Strict retry
parsing rejects signs, suffixes, overflow and values outside 50–10000 ms.
The scorer's synthetic tests cover stale duplicate retransmits, future gaps,
missing/malformed capture evidence, arm mismatch and incomplete matrices.

The initial services A/B completed 14 gameplay steps and 22 checks per run:
ON had 0 rejected unreliable updates and 0/10,934 held reliable messages;
OFF had 75 rejected updates and 71/11,487 held messages (maximum 27 ms).
Both passed the generic native-health gate, illustrating that its sustained
rejection threshold does not imply zero rejected updates.

## Matrix

Two passes per arm across nine cases: services; default victory; guest 2 and
guest 3 victory; host-skip and full closing-film victory; factory and recycler
loss; host departure. All 18 ON runs precede the matching 18 OFF controls.

Runtime evidence: `C:\BZRCoop\runs\netfix-matrix-20261007-235807`.
The runner writes per-run scores, `summary.json` and `summary.md`. Qualification
requires all planned runs, complete captures, correct arm, successful gameplay
and no crashes/GPU resets; every ON run must have zero future-stamped gaps.
OFF native-health rejection alone is expected control evidence, while actual
gameplay/capture failures remain failures. Duplicate reliable retransmits are
counted separately from rejected position updates.

### Result: PASS

`summary.json`: verdict PASS (acceptance PASS, comparison REPRODUCED), 36/36
planned runs scored, no problems. Every run completed its gameplay steps and
captures with no crash and no GPU driver event.

| Arm | Runs | Class | Rejected updates (future gaps) | Held reliable | Longest hold | Duplicate retransmits |
|---|---|---|---|---|---|---|
| ON | 18 | STRICT_PASS 18 | 0 | 0 / 178,334 | 0 ms | 2,863 |
| OFF | 18 | REPRODUCED 18 | 8,190 | 10,072 / 175,515 | 11,760 ms | 3,313 |

Every case is 0 / 0 with the fix in both passes and reproduces the backlog
without it in both passes:

| Case | OFF gaps | OFF held | OFF longest hold |
|---|---|---|---|
| services | 1,427 | 1,032 / 19,450 | 1,441 ms |
| default victory | 1,174 | 984 / 22,367 | 1,011 ms |
| guest 2 victory | 304 | 148 / 21,445 | 125 ms |
| guest 3 victory | 2,396 | 1,850 / 22,067 | 11,760 ms |
| host-skip victory | 1,309 | 1,447 / 23,516 | 1,012 ms |
| full closing-film victory | 399 | 1,018 / 22,218 | 1,005 ms |
| factory loss | 269 | 2,034 / 14,276 | 1,451 ms |
| recycler loss | 741 | 669 / 15,027 | 1,281 ms |
| host departure | 171 | 890 / 15,149 | 629 ms |

Without the fix, every one of the twelve directed links lost updates in at
least 8 of 18 runs: host to guest 3,760 gaps, guest to guest 2,888, guest to
host 1,542 (worst single link host to guest 2, 2,258). The backlog is not
specific to guest-to-guest traffic; any link carrying reliable traffic is
exposed. The 11.8 s hold is the multi-second "100% loss" symptom players
report. Duplicate retransmits are similar in both arms, so sending new reliable
messages immediately adds no measurable retransmit overhead.

After the matrix, the scorer's GPU adapter was made fail-closed (only an
explicit `NoMatchingEventsFound` or a count is evidence; any query error,
non-zero exit or unparsable output is INCOMPLETE). All 36 captures were
re-scored with it into `rescore-failclosed-gpu\`: every class, total and GPU
count is identical and the verdict is unchanged. The original scores are kept.

## Server stability follow-up

Shared relay ports cannot distinguish a sender with multiple relayed peers.
The harness already selects separate pair ports. Manual startup now has an
explicit GUI control and optional bounded range in server branch
`agent/relay-bounded-pair-ports` (`fcccf8c`), preserving capture/health behavior.
The allocator skips occupied/reserved UDP ports and rejects exhaustion without
advertising an unusable endpoint. Four fully relayed players require six ports;
capacity is shared across active lobbies. LAN/WAN operators must allow/forward
the configured range, such as UDP 1340–1369.

20 new allocator/GUI tests and 16 existing capture/health tests passed on
Python 3.12 and 3.14, together with 45 stock compatibility checks and existing
mesh/injector/parity checks. Real bounded-port game qualification is pending.
Compose wiring was checked; Docker engine validation was unavailable.

## Limits

An earlier DX11 attempt crashed during a GPU driver reset and is excluded.
Completed DX9 evidence does not qualify graphics device restoration. This
local matrix does not establish WAN behavior under genuine packet loss,
lower retry timer values, mixed patched/stock clients, or Steam/Proton/Wine
compatibility. Those remain separate qualification lanes.

## Reproduce

With the Release build and four matching prepared DX9 harness instances:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File reverse_engineering/Run-NetfixStressMatrix.ps1 -DryRun
powershell -NoProfile -ExecutionPolicy Bypass -File reverse_engineering/Run-NetfixStressMatrix.ps1 -Passes 2
```

The existing game harness owns the machine-wide launch lock and graceful
shutdown. Runtime captures, dumps and real player identifiers remain local.
