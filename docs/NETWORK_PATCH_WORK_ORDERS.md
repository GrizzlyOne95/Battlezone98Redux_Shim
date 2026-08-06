# OpenShim Network Patch Work Orders

This document converts the current network-hardening and clean-room matchmaking research into explicit, independently reviewable pull requests.

The sequence is deliberate: establish a safe baseline first, add measured tuning second, then build privacy-conscious telemetry before making additional transport experiments.

## Global rules

- Every memory write must be game-build gated and independently plausibility checked.
- Experimental packet-path behavior must be disabled by default.
- No packet may be silently dropped, truncated, duplicated, delayed, or reordered by a default configuration.
- Matchmaking and protocol telemetry must be explicit opt-in.
- Telemetry is local-only by default. No automatic upload endpoint is permitted without a separate design and consent review.
- Raw authentication material, cookies, access tokens, Steam/GOG tickets, and private message payloads must never be written to telemetry logs.
- Public peer IP addresses are sensitive data. Do not collect them in ordinary telemetry. Deep packet captures may include them only under a clearly labeled diagnostic mode.
- Every PR must preserve stock behavior when its feature is disabled or when validation fails.

---

## PR1 — Network correctness baseline

**Status:** Implemented in pull request #5. Release|Win32 builds successfully. In-game smoke validation remains recommended before merge.

### Objective

Remove unsafe or unproven behavior from the default path and make experimental networking features unmistakable in configuration and logs.

### Scope

1. Disable packet reordering by default in both built-in configuration and the shipped `net.ini` profile.
2. Keep packet duplication disabled and label it deprecated/experimental.
3. Emit a prominent startup warning when packet reordering is explicitly enabled.
4. Emit a prominent startup warning when packet duplication is explicitly enabled.
5. Log the observed live governor value periodically while `GovernorStart` is enabled, including when the game overwrites or clamps the requested value.
6. Do not change socket-buffer sizing, DSCP marking, auto-kick relaxation, relay capture, or ordinary socket diagnostics.
7. Add documentation explaining why reordering is opt-in: the sequence field is not sufficiently validated and the game commonly uses overlapped receives that bypass the existing synchronous reorder path.

### Files expected to change

- `src/patches/net_optimizer.cpp`
- `net.ini`
- Network documentation

### Acceptance criteria

- A stock/default launch reports packet reorder disabled.
- No reorder wake thread is created when reorder is disabled.
- `SendDup=0` remains the default.
- Enabling reorder produces one clear warning that it is experimental and depends on an unresolved wire-sequence interpretation.
- Enabling duplication produces one clear warning that testing found it may worsen constrained uplinks.
- With `GovernorStart=0`, no governor patch thread runs.
- With `GovernorStart>0`, logs show the requested value, every detected overwrite/clamp transition, periodic observed values, and a final shutdown snapshot.
- Release Win32 builds successfully.
- Existing tests pass, where present.

### Out of scope

- Replacing the reorder algorithm.
- Declaring a final packet sequence field.
- Changing bandwidth tuning defaults.
- Adding outbound pacing.
- Uploading telemetry.

---

## PR2 — Guarded direct `[Net]` tuning

### Objective

Stop relying on the unreliable `net.ini` application path for measured network-governor settings while failing safely on unknown builds.

### Scope

1. Introduce a table-driven `NetGlobal` model for each known `[Net]` global.
2. Version-gate the table on the validated governor signature.
3. Plausibility-gate every address independently before the first write.
4. Permanently veto an entry if its live value is outside its expected range.
5. Reassert selected values after match setup rewrites them.
6. Add OpenShim configuration keys for:
   - `MaxBandwidth`
   - `UpCount`
   - `DownCount`
   - `MaxPing`
   - `MaxPingsLost`
   - existing auto-kick values
7. Leave `MinBandwidth` untouched by default because its address/meaning remains unconfirmed.
8. Preserve `0 = leave stock/live value unchanged` for every optional override.

### Recommended initial preset

- `MaxBandwidth=320000`
- `UpCount=100`
- `DownCount=50`
- `MaxPing=450`
- `MaxPingsLost=0` (leave unchanged)
- `MinBandwidth=0` (leave unchanged)

### Acceptance criteria

- Every write is preceded by build and per-address validation.
- A failed plausibility check logs a veto and never writes that address again during the process.
- Disabling the preset restores stock behavior on the next launch.
- Match-start rewrites are corrected within one polling interval.
- Unit tests cover configuration parsing, range rejection, veto persistence, and `0 = untouched` behavior.

---

## PR3 — Opt-in network and matchmaking telemetry foundation

### Objective

Create structured local telemetry capable of supporting performance analysis and clean-room reconstruction of the current matchmaking protocol.

### Design constraints

- Disabled by default.
- Local file output only.
- No background upload.
- Human-readable session manifest plus append-only JSON Lines event stream.
- Stable schema version on every record.
- Bounded memory and disk use.
- Crash-tolerant flushing and atomic manifest finalization.

### Configuration

Proposed `[OpenShimTelemetry]` keys:

- `Enabled=0`
- `Mode=Summary|Protocol|DeepCapture`
- `Directory=logs/telemetry`
- `IncludePayloads=0`
- `HashPeerAddresses=1`
- `MaxSessionMiB=64`
- `FlushIntervalMs=1000`
- `RedactSecrets=1` (cannot be disabled in release builds)

Environment aliases may be added for test automation, but the INI remains the primary user-facing configuration.

### Session manifest fields

- telemetry schema version
- OpenShim file/product version
- game executable identity and file version
- Steam/GOG platform classification
- process start/end timestamps in UTC
- local UTC offset
- clean/unclean shutdown marker
- selected telemetry mode
- active mod identifier when available
- map/mission identifier when available
- host/client/observer role when determinable
- network configuration snapshot
- socket-buffer effective readbacks
- enabled experimental features
- record count, byte count, dropped-record count, and truncation marker

### Summary event classes

- process/session start and end
- socket create/bind/connect/close
- DNS lookup and matchmaking redirection
- transport errors
- bytes/packets sent and received by socket class
- peak packet and byte rates
- governor requested and observed values
- auto-kick configuration and events
- lobby connect/disconnect timing
- match enter/leave timing
- crash/unclean shutdown detection

### Matchmaking protocol event classes

- DNS resolution for the official matchmaking hostname
- TCP connection lifecycle
- TLS presence/absence and endpoint metadata without secret material
- WebSocket handshake start/result
- WebSocket direction, opcode, FIN flag, payload length, and timestamp
- message envelope/type name when safely parseable
- request/response correlation identifier when safely derivable
- lobby lifecycle state transition inferred from protocol messages
- redacted protocol error information
- heartbeat/ping/pong cadence

### Redaction requirements

The writer must redact or omit:

- `Authorization` headers
- cookies and `Set-Cookie`
- bearer tokens
- Steam authentication tickets
- Galaxy/GOG authentication tickets
- session secrets
- email addresses
- unstructured payload values matching secret-like fields

Ordinary `Summary` and `Protocol` modes must not store raw public peer IP addresses. Use per-session keyed hashes when correlation is required. `DeepCapture` may retain network endpoints only after a separate explicit warning and must remain local.

### Acceptance criteria

- Default launch creates no telemetry files.
- Opt-in launch creates one manifest and one JSONL stream under a unique session directory.
- Abrupt process termination leaves a readable JSONL stream and marks/finalizes the manifest on the next safe opportunity where possible.
- A redaction test corpus proves known token/cookie/auth fields never reach disk.
- Session size caps stop additional payload records without crashing or affecting gameplay.
- Telemetry overhead is measured and documented.

---

## PR4 — Matchmaking transcript analyzer and replay corpus

### Objective

Turn telemetry into a protocol research corpus suitable for implementing a clean-room matchmaking service without embedding game-specific guesses in the runtime shim.

### Scope

1. Add offline tools that ingest PR3 manifests and JSONL streams.
2. Normalize sessions into deterministic, redacted transcripts.
3. Infer request/response pairs and state-machine transitions.
4. Compare host, joiner, observer, reconnect, room-list, create-room, join-room, leave-room, and error paths.
5. Produce a protocol field catalog with confidence levels and source-session references.
6. Add a replay harness that can feed recorded server messages to a test client/parser without contacting the official service.
7. Add golden sanitized fixtures suitable for public repository storage.

### Required capture matrix

- Steam host creates and closes a room
- Steam client lists and joins a room
- GOG host creates and closes a room
- GOG client lists and joins a room
- cross-platform room visibility if supported
- passworded room
- full room / rejected join
- host disconnect
- client disconnect
- reconnect
- map/mod change
- ban/kick interaction where applicable
- official service unavailable / DNS failure / connection timeout

### Acceptance criteria

- Tools operate entirely offline.
- Public fixtures contain no credentials, raw public IPs, or private identifiers.
- Every inferred field/state is tagged `confirmed`, `probable`, or `unknown`.
- A state diagram and message catalog can be regenerated from fixtures.
- The replay harness is deterministic and covered by tests.

---

## PR5 — Network-core refactor and deterministic tests

### Objective

Separate packet algorithms and telemetry serialization from Winsock/IAT plumbing so correctness can be tested without launching Battlezone.

### Scope

- Extract reorder state machine into a platform-independent module.
- Extract outbound metrics/pacing decisions into a platform-independent module.
- Extract guarded `[Net]` table logic into a platform-independent module.
- Extract telemetry schema/serialization and redaction into testable modules.
- Keep `net_optimizer.cpp` responsible primarily for Windows hooks and lifecycle integration.

### Required tests

- sequence wrap behavior for every candidate wire width
- stale and duplicate handling
- full queue behavior with no silent packet loss
- caller-buffer-too-small semantics (`WSAEMSGSIZE`/partial behavior)
- idle peer reclamation
- round-robin fairness
- socket-handle reuse
- shutdown with pending work
- telemetry redaction
- telemetry size caps
- malformed WebSocket frames and fragmented messages
- invalid UTF-8 and binary protocol payloads

### Acceptance criteria

- Core tests build and run without Battlezone or Winsock hooks.
- Runtime adapter behavior remains unchanged unless explicitly covered by another PR.
- Test fixtures are deterministic and contain no sensitive capture data.

---

## PR6 — Outbound metrics and optional pacing

### Objective

Measure actual sender behavior before deciding whether pacing improves constrained or burst-sensitive connections.

### Scope

- Always-on counters when network diagnostics are enabled:
  - packets and bytes sent
  - peak packets per second
  - peak bytes per second
  - burst-second count
  - send API and socket class
- Per-session summary at socket close and process shutdown.
- Optional token-bucket pacing behind a default-off key.
- Preserve packet order.
- Never drop packets.
- Exempt small control/ping traffic from pacing unless evidence supports pacing it.

### Acceptance criteria

- Metrics impose negligible measured overhead.
- Pacing disabled is behaviorally identical to the metrics-only path.
- Pacing cannot reorder or discard packets.
- Queue saturation fails open by sending immediately and logs the condition.
- A/B captures compare pacing off/on under controlled bandwidth and latency conditions.

---

## PR7 — Controlled experiments

### Objective

Keep unresolved protocol and transport ideas out of production defaults while providing reproducible experiments to confirm or reject them.

### Candidate experiments

- Wire sequence-field scanner across candidate offsets, widths, and byte orders.
- Correlate candidate fields against capture order, duplicates, retransmits, and game state.
- Governor target A/B tests with live readback.
- Auto-kick threshold verification under simulated loss/latency.
- Reorder necessity test using observed out-of-order rates.
- Patched-peer-only FEC or redundancy experiments, never enabled against stock peers by default.

### Promotion rule

An experiment can move into a production PR only when:

1. The field or behavior is reproducibly identified across Steam and GOG builds.
2. The implementation covers synchronous and overlapped I/O paths or explicitly proves one path is irrelevant.
3. Tests cover wraparound, malformed traffic, queue pressure, shutdown, and caller-buffer semantics.
4. Controlled A/B captures show a measurable benefit without regressions.
5. The feature remains opt-in until sufficient community validation exists.

---

## Merge order

1. PR1 — correctness baseline
2. PR2 — guarded direct tuning
3. PR3 — telemetry foundation
4. PR4 — transcript analyzer and replay corpus
5. PR5 — core refactor/tests (may begin in parallel after PR3 schema stabilizes)
6. PR6 — outbound metrics/pacing
7. PR7 — experiments as evidence becomes available

PR3 and PR4 are the path toward an independent clean-room matchmaking service. PR7 experiments must not block that work or contaminate its protocol evidence with default packet manipulation.
