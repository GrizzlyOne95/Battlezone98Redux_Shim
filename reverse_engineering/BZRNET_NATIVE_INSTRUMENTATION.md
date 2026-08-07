# BZRNet Native Instrumentation

Status: **first-pass native control/wire instrumentation implemented; engine semantic hooks still pending validated anchors**.

This subsystem turns OpenShim into an observational BZRNet protocol microscope. It does not implement matchmaking-server business logic and does not synthesize or modify matchmaking traffic.

## Architectural boundary

The instrumentation is deliberately split from the replacement server and from OpenShim's existing socket optimizer:

```text
stock Redux client
    |
    | engine BZRNet/lobby/P2P state      (future validated hooks)
    |
    | WebSocket / UDP calls
    v
bzrnet_instrumentation.cpp               observational IAT tap
    |
    +--> bzrnet_protocol.cpp              registry, redaction, UDP semantics
    |
    +--> bzrnet_trace.cpp                 correlation + async trace writer
    |
    v
net_optimizer.cpp                         existing optimizer / wire capture
    |
    v
Winsock
```

`bzrnet_instrumentation.cpp` is installed **after** `InitializeNetworkOptimizer()`. Its saved IAT target is therefore the current OpenShim optimizer hook when one is present, so the BZRNet layer observes and then chains through the existing behavior instead of replacing it.

The DedicatedServer repository remains responsible for the WebSocket server, lobby state, authentication policy, relay service, matchmaking decisions, and other server-side behavior.

## Implemented now

### Global native trace

When enabled, OpenShim writes:

```text
logs/bzrnet_session.json
logs/bzrnet_trace.jsonl
```

Each JSONL event includes:

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

`seq` is process-wide and monotonic. `QueryPerformanceCounter`, `GetTickCount64`, and a UTC FILETIME calibration are captured so events can be aligned within a process and approximately aligned between two PCs.

Windows can recycle the numeric value of a closed `SOCKET`. `socketGeneration` gives each observed socket lifetime a unique process-local generation so a reused handle is not silently treated as the old connection.

### Asynchronous bounded writer

Network producer threads enqueue trace records into a bounded queue. A writer thread owns JSONL disk output and flushes in batches.

The session metadata records:

```text
traceQueueCapacity
traceQueueHighWater
droppedEvents
writerShutdownClean
```

If the queue overflows, the loss is not hidden: the trace writer emits `TRACE_DROPPED_EVENTS` records.

This removes synchronous disk writes from the new semantic trace path. Some temporary string/vector allocation still occurs while reconstructing and sanitizing messages; further hot-path optimization remains possible after runtime profiling.

### Full BZRNet WebSocket semantic trace

The instrumentation observes the TCP connection whose peer port is `1337`, reconstructs the HTTP/WebSocket upgrade boundary, unmasks client frames, accepts unmasked server frames, handles 16/64-bit WebSocket payload lengths, and reconstructs fragmented messages.

Every complete text JSON message is emitted as either:

```text
BZR_WS_TX
BZR_WS_RX
```

The trace is independent of `/iprelay`. Relay capture also enables BZRNet tracing, but ordinary BZRNet tracing does not force relay.

Unknown message types are preserved rather than dropped.

For known messages the registry records evidence provenance such as:

```text
binary_confirmed
capture_confirmed
high_confidence
inferred
replacement_only
unknown
```

A message existing in the replacement server is not automatically treated as evidence that the official service implements it.

### Failure/result extraction

Where present, the WebSocket semantic trace extracts:

```text
reasonCode
success
```

This is intended to support evidence-backed recovery of the official `reasonCode` enum. The replacement server's provisional failure values must not be treated as official truth.

### Privacy and redaction

Authentication tickets and lobby passwords are **always** redacted from `bzrnet_trace.jsonl`, including private-forensic mode.

Recognized ticket field names currently include:

```text
steamAppTicket
gogAppTicket
authTicket
platformTicket
```

The trace records redaction presence/length metadata instead of the secret value.

Normal sanitized mode additionally replaces identities and endpoints with stable per-process aliases. Examples:

```text
player_1
player_2
identity_1
endpoint_1
endpoint_2
```

This includes repeated identities/endpoints inside arrays and nested user objects.

`BZRNetTracePrivate=1` retains endpoint/identity values for a deliberately private forensic trace, but **does not** disable ticket/password redaction.

Raw `bz_buffer_log.bin` and Wireshark captures can still contain private network information and should remain private.

### UDP 1338 / 1339 wire highlights

By default the new semantic trace emits UDP wire events whose observed endpoint port is `1338` or `1339`:

```text
UDP_WIRE_TX
UDP_WIRE_RX
```

Each highlight includes a bounded payload prefix, stable FNV-1a diagnostic hash, payload length, sanitized endpoint, and the observed common-header kind nibble when enough bytes are present.

The existing `bz_buffer_log.bin` remains the lossless/high-volume binary capture path. The new JSONL trace is not intended to replace it.

`BZRNetTraceAllUdp=1` expands semantic wire highlights to other UDP endpoints when a targeted experiment requires dynamic direct-peer traffic.

### Known UDP control markers

The read-only native decoder recognizes:

| Marker | Current interpretation | Evidence classification |
|---|---|---|
| `PP` | peer ping/timing request | high confidence |
| `PR` | peer ping/timing response | high confidence |
| `PB` | timing/bandwidth sideband | inferred |
| `SS` | peer/session synchronization | high confidence |
| `KA` | keepalive family | high confidence |
| `PO` | unresolved peer control | inferred |
| `PZ` | unresolved peer control | inferred |

Raw marker names are retained even when their interpretation remains uncertain.

### Overlapped / IOCP observation

The BZRNet layer observes immediate and overlapped `WSARecv` / `WSARecvFrom` traffic, completion-routine callbacks, and `GetQueuedCompletionStatus` completions. Immediate completions are marked to avoid duplicate semantic capture.

## Configuration

BZRNet native tracing is **off by default**.

`net.ini`:

```ini
[OpenShimSocket]
EnableBZRNetTrace=0
BZRNetTracePrivate=0
BZRNetTraceAllUdp=0
BZRNetTraceQueueRecords=4096
```

Environment equivalents:

```text
BZ_BZRNET_TRACE=1
OPENSHIM_BZRNET_TRACE=1

BZ_BZRNET_TRACE_PRIVATE=1
OPENSHIM_BZRNET_TRACE_PRIVATE=1

BZ_BZRNET_TRACE_ALL_UDP=1
OPENSHIM_BZRNET_TRACE_ALL_UDP=1

BZ_BZRNET_TRACE_QUEUE=4096
OPENSHIM_BZRNET_TRACE_QUEUE=4096
```

`BZ_RELAY_CAPTURE=1` / `OPENSHIM_RELAY_CAPTURE=1` imply BZRNet tracing.

Queue capacity is clamped to `256..65536` records.

## Capture automation

The BZRNet-specific wrapper composes the existing buffer logger rather than replacing it:

```powershell
.\bzrnet_capture_windows.ps1 -Action Start
```

For a forced relay run:

```powershell
.\bzrnet_capture_windows.ps1 -Action Start -RelayCapture
```

Optional private forensic profile:

```powershell
.\bzrnet_capture_windows.ps1 -Action Start -RelayCapture -PrivateForensic
```

Optional direct/dynamic UDP semantic highlights:

```powershell
.\bzrnet_capture_windows.ps1 -Action Start -AllUdp
```

Add a marker through the same session state:

```powershell
.\bzrnet_capture_windows.ps1 -Action Mark -Message "relay gameplay active"
```

Stop and bundle:

```powershell
.\bzrnet_capture_windows.ps1 -Action Stop
```

The wrapper enables the native trace in the generated Steam/direct-launch artifacts and adds `bzrnet_trace.jsonl` / `bzrnet_session.json` to the evidence directory before the existing ZIP bundle is produced.

## Analysis

Summarize a native trace:

```powershell
python reverse_engineering\analyze_bzrnet_trace.py <session>\bzrnet_trace.jsonl
```

Machine-readable form:

```powershell
python reverse_engineering\analyze_bzrnet_trace.py <trace> --json
```

The analyzer reports message/event counts, reason-code observations, trace drops, and timeline duration.

It also contains the relay payload-correlation path expected by future engine hooks. When `PRE_RELAY_ENCAP` / `POST_RELAY_DECAP` events contain an inner packet and a corresponding wire event contains the full datagram, the analyzer automatically searches for the inner packet and reports:

```text
innerOffset
prefixLength
suffixLength
```

Across multiple correlated packets it classifies relay-prefix byte positions as invariant or variable. This is intended to recover UDP `1339` envelope structure mechanically rather than by manually eyeballing packet dumps.

## Official vs replacement parity comparison

Run:

```powershell
python reverse_engineering\compare_bzrnet_traces.py <official.jsonl> <replacement.jsonl>
```

The comparator normalizes only legitimate variable fields such as platform tickets, endpoint values, generated identities/lobby IDs/route IDs, timestamps, and JSON object-key ordering.

Causal messages remain strictly ordered. Known asynchronous server broadcasts may reorder only inside the same gap between adjacent strict events. They are compared as semantic multisets inside that gap.

This means these differences still fail:

```text
wrong reasonCode
wrong success value
missing field
wrong meaningful field value
missing or extra causal message
wrong causal ordering
broadcast moved across a client request/reply boundary
```

`OnHeartbeat` is ignored by default and can be included with `--include-heartbeats`.

## Known GOG 2.2.301 reverse-engineering anchors

The current research corpus identifies these **analysis anchors**, not unconditional shipping addresses:

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

The current implementation **does not install detours at these addresses**.

## Steam safety

Steam's executable is subject to SteamStub behavior. `.text` reads performed too early may observe encrypted/not-yet-ready bytes. OpenShim has already encountered this in unrelated hooks.

Therefore future engine-level BZRNet hooks must:

1. Resolve semantically/signature-first where possible.
2. Retry/delay validation when Steam code pages are not settled.
3. Verify expected bytes/signature shape before writing a detour.
4. Treat a known build-specific address only as a validated fallback.
5. Fail closed and emit a hook-validation record when evidence does not match.
6. Never blindly apply the GOG addresses above to Steam.

## Not implemented yet

The current branch intentionally does **not** claim the following:

```text
master inbound dispatcher detour
outbound builder detours
CNetGameLobby semantic state hooks
LAN/WAN/direct/relay state-machine hooks
PRE_RELAY_ENCAP engine boundary
POST_RELAY_DECAP engine boundary
effective engine startup-network configuration hook
confirmed official failure reasonCode enum
confirmed UDP 1339 relay envelope/routing IDs
confirmed relay keepalive/ack/timeout policy
binary capture format v3
runtime validation inside Battlezone
```

Those items need either validated executable signatures/call graphs or new paired official-service evidence. They should not be fabricated from provisional replacement-server behavior.

## Validation

Standalone C++ tests cover the protocol registry, nested field extraction, mandatory ticket/password redaction, repeated identity/endpoint sanitization, and known UDP decoder behavior.

Python tests cover trace parsing, dropped-event accounting, relay inner-payload offset analysis, normalized parity comparison, async broadcast reordering, causal-gap enforcement, and reason-code mismatches.

The branch also contains a Windows GitHub Actions workflow that builds the standalone Win32 tests and the full `Release|Win32` OpenShim solution. A successful compiler run is still not proof that runtime hooks are safe; live game validation remains required before this work is considered production-ready.

## Recommended next evidence run

Once a build containing this instrumentation has passed compilation and basic launch validation, the highest-value capture remains a paired official-service forced-relay run:

```powershell
.\bzrnet_capture_windows.ps1 -Action Start -RelayCapture
```

Run it on both clients, verify `/iprelay`, create/join a game through ordinary stock UI, remain in active gameplay long enough to generate relay traffic, exit normally, and collect both bundles plus Wireshark captures.

The objective is evidence for `DoP2PRoute` / `OnP2PRoute` and UDP `1339`, not deep gameplay-payload decoding.
