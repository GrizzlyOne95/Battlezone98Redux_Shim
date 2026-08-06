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
- With `GovernorStart>0`, logs show the requested value, every detected overwrite/clamp transition, and the final observed value at shutdown.
- Release Win32 builds successfully.
- Existing tests pass.

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

- Core tests run without the game.
- Runtime hook code does not duplicate packet-algorithm logic.
- Existing runtime behavior remains unchanged unless explicitly configured.

---

## PR6 — Measured outbound telemetry and optional pacing

### Objective

Measure the sender-side retransmission/burst problem before introducing any new packet-shaping behavior.

### Scope

1. Always-on lightweight counters when network optimization is enabled:
   - packets and bytes sent
   - peak packets/second
   - peak bytes/second
   - burst-duration counters
2. Session summaries emitted on socket close and through a detach-safe fallback.
3. Optional token-bucket pacing, disabled by default.
4. Never delay short control/ping packets.
5. Never drop packets.
6. Preserve sequenced-packet order.
7. Abandon pacing and send immediately when the configured delay ceiling would be exceeded.

### Acceptance criteria

- Measurement-only mode has no intentional packet delay.
- Metrics survive a process exit that skips `closesocket` where loader-lock safety permits.
- Pacing remains disabled by default.
- Tests verify order preservation, no-drop behavior, delay ceilings, and socket purge behavior.

---

## PR7 — Experimental protocol/network changes

### Objective

Only after sufficient telemetry exists, evaluate transport changes against controlled multiplayer sessions.

### Candidate experiments

- definitive packet sequence-field validation
- role-controlled governor-start A/B tests
- `UpCount`/`DownCount` A/B tests
- auto-kick bad-link validation
- `syncJoin` correlation testing
- corrected reorder implementation, only if real links demonstrate meaningful reordering
- forward-error correction between patched peers, only after compatibility and packet-type safety are proven

### Rules

- Every experiment is opt-in.
- Every experiment has a kill switch.
- Every experiment records its configuration in the telemetry manifest.
- No experiment is promoted to default from a single session or uncontrolled host/client comparison.
- Results must separate host and client roles, map/mod, peer set, and network conditions.

---

## Proposed merge order

1. PR1 — Network correctness baseline
2. PR2 — Guarded direct `[Net]` tuning
3. PR3 — Telemetry foundation
4. PR4 — Matchmaking analyzer/replay corpus
5. PR5 — Core refactor/tests
6. PR6 — Outbound metrics and optional pacing
7. PR7 — Controlled experiments

PR3 and PR5 may be partially developed in parallel, but PR3 should not expose a stable schema until its redaction and serialization tests exist.