# Direct peer packet path and Redux callback bridge

`direct_lan_mesh.cpp` and `direct_lan_redux_peer.cpp` now provide an embedded
client-to-client packet path and the native P2P send/pump/receive ABI bridge.
They compile into the plugin and run in the independent-process qualification
fixtures. They are **not activated as the game's networking backend**.
The existing Server Connect choices and LAN UI preview remain unchanged.

## Direct transport

Every participating process binds a TCP listener and UDP socket on the same
private IPv4 address and gameplay port, and publishes that bound port in the
accepted session roster. This replaces the earlier fixture's reserved-but-idle
UDP endpoint. The lower opaque local ID (lexicographic byte order) initiates
each pair's TCP connection; the other peer accepts. Both exchange session and
sender IDs before the link becomes ready. The observed TCP source address must
match the accepted roster. Connections originate from the chosen LAN interface.
For automatic port selection, TCP reserves the port first so its allocator can
avoid TIME_WAIT reservations; UDP then binds that same port. UDP-first selection
failed during repeated Win32 sessions and was corrected. Fixed-port conflicts
fail without adopting another listener or changing firewall rules.
There is no relay, helper, account provider, DNS or public endpoint. A host
participates in the same direct mesh; it does not forward the guests' packets.

Reliable messages use the pair's TCP stream. Unreliable messages use UDP to the
roster's observed address and advertised bound port. UDP reception requires
the session, member ID, matching source address/port, a completed TCP greeting,
and a newer serial. Reordered/stale unreliable messages are discarded. This
does not provide encryption or authenticate a malicious LAN participant.
Reliable and unreliable traffic are not mutually ordered. Physical latency,
loss, throughput, firewall/adapter variation and actual Redux tolerance remain
native acceptance work.

This is a new OpenShim packet transport. The earlier feasibility preference
was to reuse stock BZRNet UDP and its peer records. This milestone instead
implements a direct TCP/UDP candidate under the adapter: it avoids coupling
initial direct traffic to online peer creation or designing another reliable
UDP protocol. No stock networking code is replaced or removed. Selecting the
final gameplay implementation still requires native load/performance/match
qualification. It is not wire-compatible with 1.5, stock Redux or BZRNet.

The peer wire uses the bounded frame codec with a distinct **`BZLANM01`** magic
(control stays `BZLANP02`). The header is body length u32, magic[8], type u8,
three zero bytes, session[16], sender[16], serial u64; integers are big endian.
Within this separate peer protocol only types 1 (TCP greeting), 2 (TCP payload),
10 (TCP heartbeat), and 3 (UDP payload) are accepted in their respective states.
Greeting/heartbeat bodies are empty; payloads contain 1..1152 unmodified bytes.
A UDP datagram is exactly one complete frame. Each protocol has its own magic
and semantics; a control frame cannot be delivered as a gameplay message.

Sockets are nonblocking and explicitly owned, with delayed Winsock loading.
Bounds include 30 accepted/pending channels, eight accepts per poll, four 4KiB
reads and 32 send calls per channel per poll, 128 UDP datagrams per poll,
256KiB queued TCP bytes per peer, and 1024/1MiB received packet limits. The peer
bridge adds an equivalent bounded pending callback queue and at most 128
callback dispatches per pump. Reliable enqueue returns false on backpressure;
unreliable receive can drop on queue exhaustion. Initial connect attempts
retry at one-second intervals, greetings expire at five seconds, and active
links heartbeat each second with a ten-second receive deadline. These timings
need native loading/stall qualification.

An established reliable connection that breaks becomes unavailable and is not
silently reconnected: otherwise its queued payloads could vanish while the
game continued. The session/native lifecycle must remove the peer or end the
session. Applying membership removal drops its link and queued deliveries;
remaining pairs keep their direct connections. A transport-only test removes
its first participant and exchanges data between the other two; this does not
implement session host migration. The control model still ends on host exit.

`Mesh::Ready()` means all accepted transport links completed their greetings.
It says nothing about native players, callback installation, map load or engine
readiness. A game adapter must establish those separately before Prepared.

## Released native ABI evidence

Baseline: **Redux 2.2.301 GOG**, SHA256
`8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413`,
Ghidra `/battlezone98redux.exe-007c64`. Private decomp path:
`Battlezone_Source/BZ1/Redux/openshim_re_corpus/bzr_gog_best_effort/ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps/`;
each function has its lowercase `FUN_<address>-<address>.c` file. The research
inventory now records 36 vtable pointers and 39 boundaries with assembly.

| Boundary | PROVEN operation in the released image |
|---|---|
| `FUN_007592D0` / `0x007592D0` | Base send wrapper: ECX object, stack target identity pointer/data pointer/byte count/send flag, virtual `+0x0C`, result AL, `ret 16`. Increments counters at `+0x1C/+0x20`. |
| `FUN_0075BEB0` / `0x0075BEB0` | BZRNet send implementation: same four stack arguments, AL result, `ret 16`. Flag zero follows the unreliable branch; any nonzero flag follows reliable processing. |
| `FUN_00758C90` / `0x00758C90` | Base received-packet dispatch: ECX P2P object, stack bytes/count/sender identity pointer, `ret 12`. Counters at `+0x24/+0x28`; selects handler by first byte, or fallback at `+0x34`. Calls handler vtable `+4` with ECX=handler and stack P2P object/sender pointer/bytes/count. Bytes 0,0 cause reliable 0,1 reply before ordinary dispatch. |
| `FUN_00758AF0` / `0x00758AF0` | Register: ECX peer object, stack kind/handler pointer, `ret 8`; stores handler through native map at `+0x2C`. |
| `FUN_00758B20` / `0x00758B20` | Unregister: removes only when the current registered pointer equals the supplied handler. An old owner's destructor cannot unregister its replacement. |
| `FUN_00574BB0` / `0x00574BB0`, `FUN_00574C30` / `0x00574C30` | Player manager registers/unregisters kind `0x7A` with the P2P accessor's object. |
| `FUN_00508E50` / `0x00508E50` | Mission constructor registers kind `0x23`, passing its secondary callback subobject at `+0x54`. |
| `FUN_0073D690` / `0x0073D690` | Lobby base constructor registers kind 1. |
| `FUN_00742900` / `0x00742900` | Membership refresh calls lobby `+0x44` for count, then `+0x48` for identities, and populates native member records. The query adapter now supplies `+0x44` with verified x86 stack cleanup. |

The bridge implements explicit pointer-based signatures, preserving the
observed ABI without decompiler-inferred extra arguments or hidden returns.
Native handler pointers are borrowed; Set/Remove operations require their
owner to unregister before destruction. Conditional unregistration preserves
replacement handlers. Dispatch guards reentrancy and stops a callback batch
when ClearHandlers retires its generation. Sender identity and packet memory
are borrowed only for the callback's duration. One-byte kind-0 messages are
handled without the released dispatcher's unguarded second-byte access.

The test P2P object has four virtual entries: retire, no-op initialize, pump,
send. Its shim-owned storage is never passed to the engine allocator. The
deletion flag only retires handlers in the isolated fixture. The native map at
`+0x2C` is **not constructed**; production cannot call the stock registration
functions on this object. Counters occupy the qualified offsets, but they do
not establish the remainder of the base object layout. There is still no
production API for publishing this incomplete object.

## Tests and evidence limits

`direct_lan_peer_bridge_tests` exercises real TCP/UDP exchange, 1152-byte
payloads, size/identity rejection, ping/pong, queue backpressure, handler
replacement/removal, callback reentrancy/retirement, membership removal,
broken-link behavior and foreign UDP source-port rejection. On Win32 it calls
send/pump through native thiscall pointers for 10,000 stack-balance cycles and
delivers through a native vtable callback fixture. It checks AL semantics and
nonzero reliable flags. The fixture does not execute mission/player code.

The independent-process test now requires every peer to receive reliable and
unreliable test payloads from every other participant through its bridge
before its test Prepared response. Three/four client sessions also verify
matching native identities, discovery/manual joins, abrupt guest departure,
host shutdown, mismatch and hostile control inputs. Payload kinds `0x7A/0x23`
are routing fixtures, **not serialized NetPlayerMgr or mission messages**.

`reverse_engineering/qualify_direct_lan_peer.py --exe <exact-baseline-exe>`
executes 1,000 original send-wrapper calls in x86 emulation. A virtual ABI sink
records ECX/arguments and returns a fixture boolean. It verifies the wrapper's
AL propagation, `ret 16`, counter updates/wrap, saved registers and SEH-chain
restoration on the diagnostics-off path. It does not execute real transport.
The exact-image hash is required and the report is ignored workshop output.
An attempted native fixed-address wrapper mapping collided with the fixture's
own allocated memory; it was rejected without overwriting memory and that
harness experiment was removed. This is a harness limitation, not evidence
of an adapter/game fault.

## Next native contract

The shared lobby's metadata contract is now the critical missing connection:
`FUN_00744A50` / `0x00744A50` reads member data such as `ready`, `launched`,
`miniid`, `friendID` and `vehicle`, uses native name strings, and creates or
updates the uint16 gameplay-player mapping. **PROVEN:** its `ready` value is
compared with the lobby settings string, so it cannot simply be replaced by
the control model's boolean. `FUN_007436C0` / `0x007436C0` and
`FUN_00743F40` / `0x00743F40` also consume the native game-settings/version
serialization before callback completion. Their full calling/ownership/string
contracts remain to be qualified. Engine keys cited here come directly from
these consumers, not inferred offsets.

Remaining: native metadata/settings and string adapters, gameplay-player
mapping, full lobby callbacks, routing stock handler registration to the bridge,
backend construction/publication/restore, native map load and game launch,
then two-PC/full-match/platform acceptance. No readiness override, account-ID
fabrication, new executable hook or live deployment is included here.
