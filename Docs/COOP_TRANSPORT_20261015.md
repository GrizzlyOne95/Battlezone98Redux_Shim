# Co-op transport observations

Workstream `agent/coop-transport-20261015`, based on current main `f60bfc964`.
The open renderer PR #452 does not change the transport/provider files; renderer
work is excluded. The Roadmap source is updated separately on its overlapping
branch. Reusable Lua consumption belongs in EXU; the PDA policy belongs in CR.

## SDK contract

`OpenShimGetNetworkTrafficSnapshot(void* output, DWORD size)` is an appended
provider slot and winmm export. It returns FALSE for an unavailable observer or
anything other than an exact 88-byte v1 caller buffer. The copied POD layout is
in `include/network_traffic.h`: version/size, available/window, wall-clock sample,
UDP byte/packet totals, byte/packet rates, recent observed route and receive ages,
and a coverage-limit flag. No addresses, identities, payloads or pointers escape.
The existing provider prefix and every prior slot remain unchanged.

Tx counts Winsock-accepted UDP submissions, including WSA_IO_PENDING. It is not
a delivery or send-completion claim. Rx counts successful observed synchronous,
IOCP or callback receive completions, claimed once to avoid immediate/async
double counting. Rejected calls are excluded. Other completion mechanisms are
not a completeness guarantee. Pending registrations are bounded; overflow marks
coverage limited instead of retaining arbitrary game buffers indefinitely.

Only recognizable 18-byte BZR transport headers are counted. Discovery kind 2,
UDP probe port 1338, matchmaking TCP and unrelated UDP are excluded. Datagram
bytes include the BZR header, exclude IP/UDP overhead and use the full call/read
length rather than the diagnostic capture prefix. Retransmissions are included.
Totals reset on observed lobby join/exit and process shutdown. These are local
client totals across peers; no per-player attribution is inferred.

Rates use eight 250 ms buckets divided by a fixed two seconds. They decay to
zero without further traffic; initial rates warm up over the same fixed window.
Recent route evidence expires with that window. Relay means traffic matches a
successful observed OnP2PRoute port on the connected matchmaking server address;
direct means an observed non-server peer address; other traffic stays unknown.
Mixed reports multiple observed route classes. Idle means no recent counted
traffic, not a disconnected engine state. No route preference, timeout, buffer,
retry policy or packet contents are changed to populate this display.

The small in-memory observer uses the existing observational Winsock hook layer
even with verbose RelayLogging off. The bounded WebSocket parser obtains route
signals, but trace writers, payload hashing and file output remain opt-in. Socket
last-error state is preserved by the existing scopes. No additional native
addresses, signatures, threads or non-system runtime dependencies are introduced.

## Validation and boundaries

Release Win32 load-chain build, Release EXU x86 build, network correctness
baseline and all 110 CTests pass, including rolling-window expiry/reset and SDK
export/table compatibility. The diagnostics Lua suite passes rate/route display,
unavailable providers and failed refresh clearing; existing co-op helpers pass.
Native acceptance and exact private hashes are recorded in the final local report.

`recovery1015-coop-transport` passes seven steps / 22 checks on three real GOG
DX11 clients and the existing native local DedicatedServer. Every client has
nonzero byte/packet rates, growing complete-datagram totals and observed relay
evidence; PDA text and foreground screenshots corroborate it. The previous
quiet/stalled/recovery checks also pass with the sensor present. All three
clients survive final clean Lua/Ogre/subtitle validation. RelayLogging is off
in the native log, establishing that telemetry does not require verbose capture.
The final two-client repeat uses the rebuilt EXU with its explicit unsupported-
game gate; its result is recorded separately in the final report.

Windows/GOG DX11 native local-server acceptance is separate from Steam, WAN,
Proton and Wine. The same Win32 ABI and optional-provider degradation apply to
all stores; those other runtime lanes remain unverified before release. No real
install, Workshop publication, merge or Mission 15 work is part of this change.
