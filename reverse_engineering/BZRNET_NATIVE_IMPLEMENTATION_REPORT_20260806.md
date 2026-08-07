# BZRNet Native Instrumentation — Implementation Report

Date: 2026-08-06 / 2026-08-07 UTC
Branch: `agent/bzrnet-native-instrumentation`
Draft PR: #8
Status: **build-validated first-pass native control/wire instrumentation; live Battlezone runtime validation still required**

## Executive summary

This implementation delivers the non-speculative, high-value portion of the BZRNet native instrumentation work order while preserving the architectural boundary that OpenShim observes and `Battlezone98Redux_DedicatedServer` implements server behavior.

The branch adds a dedicated BZRNet protocol/trace subsystem, complete WebSocket semantic observation, UDP 1338/1339 and optional dynamic-UDP wire highlights, asynchronous correlated logging, mandatory secret redaction, capture automation, evidence validation, two-PC clock alignment, targeted coverage analysis, semantic official-vs-replacement comparison, and correlation back to the existing lossless `bz_buffer_log.bin` v2 capture.

It deliberately does **not** install speculative engine detours at the known GOG addresses. Dispatcher, builder, lobby-state, P2P-state, and relay encapsulation/decapsulation hooks remain pending until their Steam/GOG signatures, ABI/calling convention, and safe detour boundaries are validated.

## Files added

Native code:

```text
include/bzrnet_protocol.h
include/bzrnet_trace.h
include/bzrnet_instrumentation.h
src/patches/bzrnet_protocol.cpp
src/patches/bzrnet_trace.cpp
src/patches/bzrnet_instrumentation.cpp
```

Capture / analysis tooling:

```text
bzrnet_capture_windows.ps1
reverse_engineering/analyze_bzrnet_trace.py
reverse_engineering/align_bzrnet_traces.py
reverse_engineering/compare_bzrnet_traces.py
reverse_engineering/validate_bzrnet_trace.py
reverse_engineering/bzrnet_capture_coverage.py
reverse_engineering/correlate_bzrnet_wire.py
reverse_engineering/bzrnet_session_report.py
```

Documentation:

```text
reverse_engineering/BZRNET_NATIVE_INSTRUMENTATION.md
reverse_engineering/BZRNET_NATIVE_IMPLEMENTATION_REPORT_20260806.md
```

Tests / CI:

```text
tests/bzrnet_protocol_tests.cpp
tests/CMakeLists.txt
reverse_engineering/test_bzrnet_trace_tools.py
reverse_engineering/test_bzrnet_capture_coverage.py
reverse_engineering/test_bzrnet_wire_correlation.py
reverse_engineering/test_bzrnet_session_report.py
.github/workflows/bzrnet-instrumentation.yml
```

## Files changed

```text
src/dllmain.cpp
BZROpenShim.vcxproj
```

`dllmain.cpp` initializes the BZRNet observation layer immediately after the existing network optimizer and shuts it down before the optimizer. `BZROpenShim.vcxproj` includes the new native modules.

## Hooks added

The implementation adds observational IAT taps for:

```text
closesocket
send
recv
sendto
recvfrom
WSASend
WSARecv
WSASendTo
WSARecvFrom
GetQueuedCompletionStatus
```

Target import surfaces are the main game executable and, when loaded, `Galaxy.dll`, `GalaxyPeer.dll`, and `steam_api.dll`.

Important safety behavior:

- The existing `net_optimizer.cpp` hooks are installed first.
- The BZRNet layer records the current IAT target and chains through it, so the new layer observes rather than replacing existing OpenShim network behavior.
- If a later module presents an unexpected/different prior target, the new layer skips that hook rather than constructing an unsafe chain.
- Import tables without `OriginalFirstThunk` are skipped with a warning instead of being guessed.
- No engine code bytes are modified by the new BZRNet instrumentation in this pass.

## Trace architecture

New native artifacts:

```text
logs/bzrnet_session.json
logs/bzrnet_trace.jsonl
```

Every semantic trace event carries:

```text
captureId
processId
seq
tickMs
qpc
qpcFrequency
threadId
layer
event
direction
socketId
socketGeneration
messageType
details
```

`seq` is process-wide and monotonically increasing. QPC, TickCount64, and UTC FILETIME calibration are recorded so a single process can be ordered precisely and two machines can be placed on one approximate UTC timeline.

The writer uses a bounded queue and a dedicated writer thread. Producer-side network hooks enqueue records instead of performing synchronous semantic-trace disk writes. Queue high-water and dropped-event counts are recorded. Queue overflow emits explicit `TRACE_DROPPED_EVENTS` evidence rather than silently losing trace integrity.

Socket generations distinguish recycled Windows `SOCKET` handles from earlier lifetimes.

## Full WebSocket semantic observation

The new layer reconstructs the HTTP/WebSocket transition and supports:

```text
masked outbound client frames
unmasked inbound server frames
16-bit and 64-bit WebSocket lengths
fragmented messages
immediate receive paths
overlapped receive paths
completion routines
IOCP / GetQueuedCompletionStatus
```

Complete text messages are emitted as:

```text
BZR_WS_TX
BZR_WS_RX
```

BZRNet tracing no longer requires `/iprelay`. Relay capture implies BZRNet trace mode, but ordinary control-plane tracing can run independently.

Unknown message types are preserved instead of discarded.

## Protocol registry / evidence provenance

The native protocol registry distinguishes evidence levels:

```text
binary_confirmed
capture_confirmed
high_confidence
inferred
replacement_only
unknown
```

The binary-confirmed client/server message set is represented separately from verbs known only from replacement-server or lower-confidence research. This prevents `server.py` implementation choices from being silently promoted to official protocol truth.

## Redaction behavior

Authentication tickets and lobby passwords are always redacted from semantic trace output, including private-forensic mode.

Recognized ticket keys:

```text
steamAppTicket
gogAppTicket
authTicket
platformTicket
```

Redaction is applied to **all occurrences** of these secret keys and `password`, including repeated/nested occurrences in unknown or malformed-but-parseable messages.

Normal sanitized mode also maps identities and endpoints to stable per-process aliases such as:

```text
player_1
identity_1
endpoint_1
```

Repeated values inside nested user structures and LAN address arrays are sanitized as well.

Private-forensic mode retains identity/endpoint values but does not disable ticket/password redaction.

Raw `bz_buffer_log.bin` and Wireshark captures remain sensitive and must be treated as private evidence.

## UDP observation / decoder

The semantic trace records `UDP_WIRE_TX` / `UDP_WIRE_RX` for BZRNet UDP endpoints and optionally all UDP during targeted capture.

Recorded wire highlights include:

```text
payload length
sanitized endpoint
FNV-1a diagnostic hash
bounded payload prefix
common-header kind nibble when present
known control marker / interpretation / evidence level
```

Read-only control marker support currently includes:

```text
PP  high-confidence ping/timing request
PR  high-confidence ping/timing response
PB  inferred timing/bandwidth sideband
SS  high-confidence session/bootstrap synchronization family
KA  high-confidence keepalive family
PO  unresolved/inferred control marker
PZ  unresolved/inferred control marker
```

The raw marker is retained even when the interpretation is not confirmed.

## Capture automation

New wrapper:

```powershell
.\bzrnet_capture_windows.ps1 -Action Start
```

Forced relay profile:

```powershell
.\bzrnet_capture_windows.ps1 -Action Start -RelayCapture
```

Relay mode composes the existing 2048-byte binary capture with native BZRNet semantic tracing and enables dynamic-UDP semantic highlights so direct/candidate/fallback attempts are not hidden.

The wrapper preserves the existing `buffer_logger_windows.ps1` workflow and augments its session bundle with:

```text
bzrnet_session.json
bzrnet_trace.jsonl
bzrnet_capture_identity.json
SHA256SUMS.txt
```

`bzrnet_capture_identity.json` records Steam/GOG classification, game executable version/size/SHA-256, installed `winmm.dll` version/size/SHA-256, capture start/stop UTC, and the **requested** capture profile. It explicitly does not claim that launch-requested values prove the engine's effective runtime configuration.

`Stop` preserves the profile recorded at `Start` even when the Stop command is invoked without repeating the Start switches.

## Analysis tooling

### `analyze_bzrnet_trace.py`

Summarizes:

```text
message/event counts
reasonCode observations
timeline duration
trace drops
relay-boundary correlations when boundary events become available
relay prefix byte stability
```

### `align_bzrnet_traces.py`

Maps two clients' QPC timestamps into a common approximate UTC FILETIME domain using each session's startup calibration. The output is a sanitized merged timeline.

### `compare_bzrnet_traces.py`

Performs semantic official-vs-replacement comparison.

Causal messages remain strict. Known asynchronous broadcasts may reorder only within the same gap between adjacent strict events and are compared as semantic multisets in that gap.

The comparator does not normalize meaningful differences such as:

```text
wrong reasonCode
wrong success result
missing or extra causal message
meaningful field mismatch
broadcast crossing a causal request/reply boundary
```

### `validate_bzrnet_trace.py`

Mechanically rejects invalid evidence when it sees:

```text
non-monotonic sequence IDs
inconsistent capture/process identity
invalid QPC calibration fields
known raw ticket/password values
unsanitized known identities/endpoints in sanitized mode
unclean trace-writer shutdown
trace queue drops (unless explicitly allowed)
```

Unknown BZRNet messages are warnings rather than evidence loss.

### `bzrnet_capture_coverage.py`

Scores the trace against targeted capture scenarios as:

```text
OBSERVED
PARTIAL
NOT_SEEN
```

Coverage is deliberately not described as proof of parity.

### `correlate_bzrnet_wire.py`

Bridges the new semantic trace to the existing `bz_buffer_log.bin` **version 2** format instead of prematurely replacing the working lossless capture format.

Correlation uses:

- direction
- observed port
- payload length
- timestamp proximity
- exact FNV-1a match when the binary record contains the full datagram
- prefix match when the binary capture payload is intentionally truncated

When future `PRE_RELAY_ENCAP` / `POST_RELAY_DECAP` events contain the inner gameplay packet, this tool uses the matched lossless binary datagram to calculate:

```text
innerVerbatim
innerOffset
prefixLength
suffixLength
```

This is the intended mechanical path for recovering UDP 1339 envelope structure without decoding gameplay semantics.

### `bzrnet_session_report.py`

Produces a one-command sanitized QA/coverage report for a completed session directory and recommends the next evidence action without printing private packet bodies.

## Known reverse-engineering anchors

GOG Redux 2.2.301 research currently identifies approximately:

```text
Inbound BZRNet dispatcher                    0x006BF2A0
Authorization / DoUpdateWAN / DoUpdateLAN   0x006C6E60
DoEnterLounge                               0x006C6320
DoExitLounge                                0x006C65B0
CreateLobby                                 0x006C3FB0
CreateGame                                  0x006C4350
DoJoinLobby                                 0x006C46B0
DoExitLobby                                 0x006C5760
DoSetLobbyOwner                             0x006C49F0
SetLobbyData                                0x006C4C50
SetPlayerData                               0x006C4F70
DeleteLobbyData                             0x006C6040
LockLobby                                   0x006C5290
SetLobbyMemberLimit                         0x006C54F0
DoSendChat                                  0x006C3D50
DoP2PConnect                                0x006C59C0
DoP2PRoute                                  0x006C5D20
```

These remain analysis anchors only. This branch does not detour them.

## Steam / GOG resolution strategy

Future engine-semantic hooks must be signature/semantic-first and fail closed.

Required procedure:

1. Identify a semantically unique target or call-site signature from the RE corpus.
2. Resolve/validate after SteamStub code pages are ready; retry/delay reads on Steam where needed.
3. Verify expected bytes/instruction shape before changing code.
4. Treat build-specific fixed addresses only as version/hash-gated fallback evidence.
5. Record resolved address, expected/actual validation, strategy, and install result in trace/session hook metadata.
6. Do not apply GOG addresses blindly to Steam.

The absence of validated signatures/ABI boundaries is why engine detours are intentionally deferred rather than guessed.

## New configuration

`net.ini`:

```ini
[OpenShimSocket]
EnableBZRNetTrace=0
BZRNetTracePrivate=0
BZRNetTraceAllUdp=0
BZRNetTraceQueueRecords=4096
```

Environment controls:

```text
BZ_BZRNET_TRACE
OPENSHIM_BZRNET_TRACE
BZ_BZRNET_TRACE_PRIVATE
OPENSHIM_BZRNET_TRACE_PRIVATE
BZ_BZRNET_TRACE_ALL_UDP
OPENSHIM_BZRNET_TRACE_ALL_UDP
BZ_BZRNET_TRACE_QUEUE
OPENSHIM_BZRNET_TRACE_QUEUE
```

Existing `BZ_RELAY_CAPTURE` / `OPENSHIM_RELAY_CAPTURE` imply semantic BZRNet tracing.

## Tests added

Native C++ tests currently cover:

```text
message type extraction
protocol registry evidence
nested reasonCode extraction
nested success extraction
auth-ticket redaction
password redaction
identity redaction
endpoint redaction
repeated identity sanitization
repeated endpoint sanitization
repeated/nested secret redaction
PP decoder fields
```

Python tests cover trace health/analysis, relay-offset analysis, async-aware parity comparison, reason-code mismatch detection, causal-gap enforcement, two-PC clock alignment, evidence validation, capture-matrix coverage, semantic-to-binary wire correlation, truncated binary-prefix matching, and session reporting.

The capture wrapper is parsed by PowerShell's AST parser in CI.

## Tests / build run

Windows CI run on the feature branch has validated the actual project configuration:

```text
OpenShim Release|Win32 MSVC build: PASS
standalone native protocol tests: 12 checks, 0 failures
Python BZRNet analysis tests: 18 tests, PASS
PowerShell capture-wrapper parse: PASS
```

The first full Win32 compile found two `DWORD` vs `uint32_t` `std::min` mismatches in the new instrumentation; those were fixed. Subsequent full `Release|Win32` builds pass.

Compiler/unit/tool success is not runtime hook validation.

## Runtime validation performed

**Not performed in this environment.**

The available environment cannot launch Battlezone 98 Redux. Therefore this implementation does not claim:

```text
game launch success
multiplayer menu success
live official BZRNet traffic success
no measurable frame-time impact
runtime Steam/GOG IAT coverage
runtime trace flush behavior inside Redux
```

Those remain the next validation gate.

## Known unresolved items

The following work remains intentionally unresolved:

```text
master inbound BZRNet dispatcher engine hook
outbound BZRNet builder hooks
CNetGameLobby state-transition hooks
LAN/WAN/direct/relay engine state-machine hooks
PRE_RELAY_ENCAP engine boundary
POST_RELAY_DECAP engine boundary
effective engine startup-network configuration hook
confirmed official failure reasonCode enum
confirmed UDP 1339 relay envelope/routing identifiers
confirmed relay keepalive/ack format
confirmed relay timeout/retry/fallback policy
binary capture v3 lifecycle format
live Steam/GOG validation
```

The v3 binary format is no longer a prerequisite for initial protocol work because the new semantic-to-v2 wire correlator can already pair semantic events with the existing lossless UDP records. A v3 format should be introduced only when its additional lifecycle/correlation fields provide concrete value beyond the established v2 path.

## Exact recommended next validation / capture

### Step 1 — one-machine smoke validation

Before using the official relay service for the first new evidence run:

```powershell
.\bzrnet_capture_windows.ps1 -Action Start
```

Launch the game normally and verify:

```text
game launches
single player remains normal
multiplayer menu/lobby opens
logs/bzrnet_session.json exists
logs/bzrnet_trace.jsonl exists
Authorization is redacted
BZR_WS_TX / BZR_WS_RX events are present
no TRACE_DROPPED_EVENTS
normal exit reports writerShutdownClean=true
```

Then:

```powershell
.\bzrnet_capture_windows.ps1 -Action Stop
python reverse_engineering\bzrnet_session_report.py <session-directory>
```

### Step 2 — paired official forced-relay capture

After Step 1 passes on the build, run on both clients:

```powershell
.\bzrnet_capture_windows.ps1 -Action Start -RelayCapture
```

Use ordinary stock-client UI actions only. Create/join/start one game, generate active gameplay traffic, add markers, exit normally, and collect both OpenShim bundles plus Wireshark PCAPs.

Immediate evidence target:

```text
DoP2PRoute
OnP2PRoute
UDP 1339 from both viewpoints
dynamic UDP candidates/fallbacks
clean relay teardown
```

Then run:

```powershell
python reverse_engineering\bzrnet_session_report.py <host-session>
python reverse_engineering\bzrnet_session_report.py <joiner-session>
python reverse_engineering\correlate_bzrnet_wire.py <host-trace> <host-bz_buffer_log.bin>
python reverse_engineering\correlate_bzrnet_wire.py <joiner-trace> <joiner-bz_buffer_log.bin>
python reverse_engineering\align_bzrnet_traces.py <host-session.json> <host-trace.jsonl> <joiner-session.json> <joiner-trace.jsonl>
```

That paired evidence should drive the next engine-signature/relay-boundary work. Do not declare UDP 1339 reconstruction complete until the paired evidence supports it.
