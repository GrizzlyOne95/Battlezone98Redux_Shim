# OpenShim Network Patch Work Orders

This document converts the current network-hardening and clean-room matchmaking research into explicit, independently reviewable pull requests.

The sequence is deliberate: establish safe defaults first, make shutdown lifecycle-safe, build privacy-conscious telemetry, reconstruct matchmaking behavior from evidence, and only then apply broader tuning or packet-path experiments.

## Global rules

- Every memory write must be game-build gated and independently plausibility checked.
- Experimental packet-path behavior must be disabled by default.
- No packet may be silently dropped, truncated, duplicated, delayed, or reordered by a default configuration.
- Every feature must preserve stock behavior when disabled or when validation fails.
- Matchmaking and protocol telemetry must be explicit opt-in.
- Telemetry is local-only by default. No automatic upload endpoint is permitted without a separate design and consent review.
- Raw authentication material, cookies, access tokens, Steam/GOG tickets, and private message payloads must never be written to telemetry logs.
- Ordinary telemetry must not retain raw public peer IP addresses.
- Runtime hooks must not perform expensive parsing or synchronous disk I/O on latency-sensitive paths.
- Queue pressure may drop optional telemetry records, but must never drop or alter game traffic.

## Current execution order

1. PR1 — network correctness baseline
2. PR1.5 — loader-lock-safe shutdown and worker joining
3. PR3A — telemetry core and redaction
4. PR3B — matchmaking capture adapter
5. PR4 — transcript analyzer and replay corpus
6. PR2 — guarded direct `[Net]` tuning
7. PR5 — network-core refactor and deterministic tests
8. PR6 — outbound metrics and optional pacing
9. PR7 — controlled experiments

PR3A, PR3B, and PR4 are the direct path toward an independent clean-room matchmaking service. PR2 tuning should not precede protocol evidence collection unless a specific stability defect requires it.

---

## PR1 — Network correctness baseline

**Status:** Implemented in pull request #5. `Release|Win32` builds successfully with Visual Studio 2022/MSBuild and GitHub Actions. In-game smoke validation remains recommended before merge.

### Objective

Remove unsafe or unproven behavior from the default path and make experimental networking features unmistakable in configuration and logs.

### Scope

1. Disable packet reordering by default in both built-in configuration and the shipped `net.ini` profile.
2. Keep packet duplication disabled and label it deprecated/experimental.
3. Emit a prominent startup warning when packet reordering is explicitly enabled.
4. Emit a prominent startup warning when packet duplication is explicitly enabled.
5. Log the observed live governor value periodically while `GovernorStart` is enabled, including when the game overwrites or clamps the requested value.
6. Do not change socket-buffer sizing, DSCP marking, auto-kick relaxation, relay capture, or ordinary socket diagnostics.
7. Explain why reordering is opt-in: the sequence field is not sufficiently validated and overlapped `WSARecvFrom` traffic bypasses the existing synchronous reorder path.
8. Add a reproducible GitHub Actions `Release|Win32` build pinned to the Visual Studio 2022 runner.
9. Add a source/profile regression script that fails CI if PR1 safety invariants are reverted.

### Files expected to change

- `src/patches/net_optimizer.cpp`
- `net.ini`
- `.github/workflows/build-win32.yml`
- `tools/validate-network-baseline.ps1`
- Network documentation

### Acceptance criteria

- A stock/default launch reports packet reorder disabled.
- No reorder wake thread is created when reorder is disabled.
- `SendDup=0` remains the default.
- Enabling reorder produces one clear warning that it is experimental and depends on an unresolved wire-sequence interpretation.
- Enabling duplication produces one clear warning that testing found it may worsen constrained uplinks.
- With `GovernorStart=0`, no governor patch thread runs.
- With `GovernorStart>0`, logs show the requested value, every detected overwrite/clamp transition, periodic observed values, and a final shutdown snapshot.
- The regression script verifies built-in defaults, INI fallbacks, shipped profile values, worker-thread gates, and warning text.
- Release Win32 builds successfully locally and in GitHub Actions.

### Out of scope

- Replacing the reorder algorithm.
- Declaring a final packet sequence field.
- Changing bandwidth tuning defaults.
- Adding outbound pacing.
- Uploading telemetry.
- Redesigning shutdown lifecycle.

---

## PR1.5 — Loader-lock-safe shutdown and worker joining

**Tracking:** Issue #6.

### Objective

Separate normal runtime shutdown from `DLL_PROCESS_DETACH` so workers cannot execute after their code or shared state is released, while avoiding blocking waits and complex cleanup under the Windows loader lock.

### Scope

1. Introduce an idempotent shutdown-request path that is safe from restricted contexts.
2. Introduce a normal shutdown-and-join path that runs outside `DllMain`.
3. Keep `DLL_PROCESS_DETACH` minimal and non-blocking.
4. Distinguish process termination from dynamic unload using the `reserved` argument.
5. Replace long worker `Sleep()` calls with stop-event waits where practical.
6. Keep thread handles open until workers exit or a documented timeout occurs.
7. Do not release worker-owned buffers, sockets, logging state, or imported modules while a worker may still access them.
8. Define whether dynamic `FreeLibrary` unload is supported.

### Acceptance criteria

- No blocking wait is performed from `DLL_PROCESS_DETACH`.
- Normal shutdown joins the patch thread and all network worker threads before releasing their state.
- Shutdown is idempotent.
- Workers in startup delays respond promptly to shutdown.
- Timeout paths identify the worker and do not free state it may still access.
- Logger teardown happens after worker logging has ended.
- Release Win32 builds locally and in GitHub Actions.

### Required tests

- shutdown during governor startup delay;
- shutdown during active governor polling;
- shutdown with reorder wake enabled;
- shutdown with duplication worker enabled;
- shutdown during buffer/relay capture;
- repeated shutdown requests;
- ordinary process exit;
- dynamic unload, if supported.

---

## PR3A — Telemetry core and redaction

**Tracking:** Issue #7.

### Objective

Create a structured, local-only telemetry foundation that can support performance analysis and later matchmaking protocol capture without putting authentication material or player identifiers at risk.

### Design constraints

- Disabled by default.
- Local file output only.
- No background upload.
- Human-readable session manifest plus append-only JSON Lines event stream.
- Stable schema version on every record.
- Bounded memory and disk usage.
- Crash-tolerant flushing and atomic manifest finalization where possible.
- Runtime hooks enqueue bounded records; a dedicated writer owns disk I/O.

### Proposed configuration

`[OpenShimTelemetry]`

- `Enabled=0`
- `Mode=Summary`
- `Directory=logs/telemetry`
- `MaxSessionMiB=64`
- `FlushIntervalMs=1000`
- `HashPeerAddresses=1`
- `RedactSecrets=1` — cannot be disabled in release builds

### Session manifest fields

- telemetry schema version;
- OpenShim file/product version;
- game executable identity and file version;
- Steam/GOG platform classification;
- process start/end timestamps in UTC;
- local UTC offset;
- clean/unclean shutdown marker;
- telemetry mode;
- active mod and map/mission identifiers when available;
- host/client/observer role when determinable;
- network configuration snapshot;
- effective socket-buffer readbacks;
- enabled experimental features;
- record count, byte count, dropped-record count, and truncation marker.

### Summary event classes

- process/session start and end;
- socket create, bind, connect, and close;
- DNS lookup and matchmaking redirect decisions;
- transport errors;
- bytes and packets sent/received by socket class;
- peak packet and byte rates;
- governor requested and observed values;
- auto-kick configuration and events;
- lobby and match enter/leave timing;
- crash or unclean shutdown detection.

### Redaction requirements

The writer must redact or omit:

- `Authorization` headers;
- cookies and `Set-Cookie`;
- bearer tokens;
- Steam authentication tickets;
- Galaxy/GOG authentication tickets;
- session secrets;
- email addresses;
- secret-like fields found in structured or unstructured payloads.

Endpoint correlation must use a per-session HMAC pseudonym generated with a random key that remains only in memory. The key must never be written to disk. This permits within-session correlation without allowing trivial IPv4 enumeration or cross-session tracking.

### Acceptance criteria

- Default launch creates no telemetry files.
- Opt-in summary mode creates one manifest and one JSONL stream under a unique session directory.
- Abrupt process termination leaves the JSONL stream readable.
- Session-size caps stop additional optional records without affecting gameplay.
- Queue saturation increments a dropped-record counter and never alters game traffic.
- A redaction corpus proves known token, cookie, ticket, email, and secret forms never reach disk.
- Endpoint pseudonyms correlate within one session but not across sessions.
- Telemetry overhead is measured and documented.

---

## PR3B — Matchmaking capture adapter

**Tracking:** Issue #7.

### Objective

Add narrowly scoped protocol telemetry for the official or explicitly configured matchmaking service without turning the shim into a generic gameplay packet recorder.

### Scope

1. Associate DNS results and sockets with the configured matchmaking hostname.
2. Restrict protocol payload inspection to those associated connections.
3. Record TCP lifecycle and TLS presence/absence metadata without secret material.
4. Record WebSocket handshake start/result.
5. Record frame direction, opcode, FIN flag, payload length, and monotonic timestamp.
6. Parse message envelope/type names only when safe and bounded.
7. Add request/response correlation identifiers when safely derivable.
8. Infer lobby lifecycle transitions from protocol events while marking inference confidence.
9. Record heartbeat, ping, and pong cadence.
10. Keep deep capture behind a separate explicit warning and opt-in mode.

### Required event fields

- schema version;
- session identifier;
- monotonic timestamp;
- direction;
- source subsystem;
- connection/socket pseudonym;
- protocol stage;
- payload length;
- parse result and confidence.

### Acceptance criteria

- Ordinary protocol mode stores no raw authentication material or public peer IP addresses.
- Connections unrelated to the configured matchmaking service are excluded from protocol payload capture.
- Generic gameplay packet payloads are not captured by this adapter.
- Fragmented and binary WebSocket messages are handled without crashes or unbounded buffering.
- Malformed frames produce bounded error records and do not affect the game connection.
- Sanitized fixtures can be generated for the offline transcript/replay tool.

---

## PR4 — Matchmaking transcript analyzer and replay corpus

### Objective

Turn PR3A/PR3B telemetry into a protocol research corpus suitable for implementing a clean-room matchmaking service without embedding unverified guesses in the runtime shim.

### Scope

1. Add offline tools that ingest manifests and JSONL streams.
2. Normalize sessions into deterministic, redacted transcripts.
3. Infer request/response pairs and state-machine transitions.
4. Compare host, joiner, observer, reconnect, room-list, create-room, join-room, leave-room, and error paths.
5. Produce a protocol field catalog with confidence labels and source-session references.
6. Add a replay harness that feeds recorded server messages to a test parser/client without contacting the official service.
7. Add golden sanitized fixtures suitable for public repository storage.

### Required capture matrix

- Steam host creates and closes a room;
- Steam client lists and joins a room;
- GOG host creates and closes a room;
- GOG client lists and joins a room;
- cross-platform room visibility, if supported;
- passworded room;
- full room or rejected join;
- host disconnect;
- client disconnect;
- reconnect;
- map/mod change;
- ban/kick interaction where applicable;
- service unavailable, DNS failure, and connection timeout.

### Acceptance criteria

- Tools operate entirely offline.
- Public fixtures contain no credentials, raw public IPs, or private identifiers.
- Every inferred field or state is tagged `confirmed`, `probable`, or `unknown`.
- A state diagram and message catalog can be regenerated from fixtures.
- The replay harness is deterministic and covered by tests.

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
- `MaxPingsLost=0` — leave unchanged
- `MinBandwidth=0` — leave unchanged

### Acceptance criteria

- Every write is preceded by build and per-address validation.
- A failed plausibility check logs a veto and never writes that address again during the process.
- Disabling the preset restores stock behavior on the next launch.
- Match-start rewrites are corrected within one polling interval.
- Unit tests cover configuration parsing, range rejection, veto persistence, and `0 = untouched` behavior.

---

## PR5 — Network-core refactor and deterministic tests

### Objective

Separate packet algorithms, tuning decisions, telemetry serialization, and redaction from Winsock/IAT plumbing so correctness can be tested without launching Battlezone.

### Scope

- extract the reorder state machine into a platform-independent module;
- extract outbound metrics/pacing decisions into a platform-independent module;
- extract guarded `[Net]` table logic into a platform-independent module;
- extract telemetry schema, serialization, queueing, and redaction into testable modules;
- keep `net_optimizer.cpp` responsible primarily for Windows hooks and lifecycle integration.

### Required tests

- sequence wrap behavior for every candidate wire width;
- stale and duplicate handling;
- full queue behavior with no silent packet loss;
- caller-buffer-too-small semantics (`WSAEMSGSIZE`/partial behavior);
- idle peer reclamation;
- round-robin fairness;
- socket-handle reuse;
- shutdown with pending work;
- telemetry redaction and size caps;
- queue saturation;
- malformed and fragmented WebSocket frames;
- invalid UTF-8 and binary payloads.

### Acceptance criteria

- Core tests build and run without Battlezone or live Winsock hooks.
- Runtime adapter behavior remains unchanged unless explicitly covered by another PR.
- Test fixtures are deterministic and contain no sensitive capture data.

---

## PR6 — Outbound metrics and optional pacing

### Objective

Measure actual sender behavior before deciding whether pacing improves constrained or burst-sensitive connections.

### Scope

- packets and bytes sent;
- peak packets per second;
- peak bytes per second;
- burst-second count;
- send API and socket class;
- per-session summaries at socket close and process shutdown;
- optional token-bucket pacing behind a default-off key;
- preserve packet order;
- never drop packets;
- exempt small control/ping traffic unless evidence supports pacing it.

### Acceptance criteria

- Metrics impose negligible measured overhead.
- Pacing disabled is behaviorally identical to the metrics-only path.
- Pacing cannot reorder or discard packets.
- Queue saturation fails open by sending immediately and logs the condition.
- Controlled A/B captures compare pacing off/on under constrained bandwidth and latency.

---

## PR7 — Controlled experiments

### Objective

Keep unresolved protocol and transport ideas out of production defaults while providing reproducible experiments to confirm or reject them.

### Candidate experiments

- wire sequence-field scanner across candidate offsets, widths, and byte orders;
- correlate candidate fields against capture order, duplicates, retransmits, and game state;
- governor target A/B tests with live readback;
- auto-kick threshold verification under simulated loss/latency;
- reorder necessity tests using observed out-of-order rates;
- patched-peer-only FEC or redundancy experiments, never enabled against stock peers by default.

### Promotion rule

An experiment can move into a production PR only when:

1. The field or behavior is reproducibly identified across Steam and GOG builds.
2. The implementation covers synchronous and overlapped I/O paths or proves one path irrelevant.
3. Tests cover wraparound, malformed traffic, queue pressure, shutdown, and caller-buffer semantics.
4. Controlled A/B captures show measurable benefit without regressions.
5. The feature remains opt-in until sufficient community validation exists.

---

## Merge policy

- PR1 should be squash-merged because its branch history contains many connector-generated incremental commits rather than meaningful review units.
- PR1.5 should remain isolated from telemetry and tuning changes.
- PR3A schema and redaction behavior must stabilize before PR3B payload parsing expands.
- PR4 must operate on sanitized fixtures and remain offline.
- PR2 tuning must not reinterpret captured protocol evidence.
- PR7 experiments must not contaminate normal telemetry with default packet manipulation.
