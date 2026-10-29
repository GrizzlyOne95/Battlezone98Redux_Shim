# Direct LAN backend target and feasibility

## Agreed behavior

Direct LAN is an additional connection option alongside the existing Official
(Rebellion), Custom and Local choices. Those choices keep their current
behavior. The existing Local choice means a lobby service on this PC; the
preview helper/discovery tools belong to that service-based workflow.

Direct LAN must provide the 1.5-style player experience requested by the user:

- The hosting game process creates and advertises the session.
- Other game processes discover it or join its LAN address directly.
- Session-scoped identities and display names are created locally.
- No matchmaking/lobby service, separate helper process, account sign-in,
  Steam/Galaxy ticket, public endpoint probe, NAT service or relay is required.
- Session membership, settings, readiness, launch and disconnect handling live
  in the participating clients. A host can coordinate these functions, as a
  player participating in that session.
- Selecting Direct LAN changes only that session's networking backend.
  Returning to Official/Custom/Local restores the applicable existing backend.

The current helper prototype does **not** meet this target. It remains useful
as optional Local host tooling and must not be presented as standalone LAN.

## Current evidence

The evidence baseline is the released GOG Redux **2.2.301** executable, SHA256
`8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413`.
Ghidra project `/battlezone98redux.exe-007c64` corroborates the existing private
corpus `BZ1/Redux/openshim_re_corpus/bzr_gog_best_effort`, whose function files
are under `ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps/`.
Each address below has the corresponding `FUN_<address>-<address>.c` file there.
These are static conclusions, not live hook qualification.

| Evidence | Conclusion |
|---|---|
| `FUN_00764870`, `FUN_007647F0`, `FUN_00764810`, `FUN_00764840` | **PROVEN:** default mode 4 requires a platform-ready path and a BZRNet-ready path. The UI check is more than a network socket readiness test. |
| `FUN_00764D80`, `FUN_00764F50` | **PROVEN:** provider initialization and backend construction are distinct stages; startup constructs provider-specific objects and publishes their pointers. |
| `FUN_00764760` | **PROVEN:** the lobby accessor returns the global at `0x00945470`. This does not prove it is safe to replace that pointer without its callback/lifetime contracts. |
| `FUN_0074B3D0`, `FUN_0075A2B0` | **PROVEN:** the BZRNet lobby and P2P objects also register themselves with the interface helper at `+0xC38` and `+0xC3C`. Replacing a single accessor would leave other references behind. |
| `BZRNetLobby` vtable `0x0089ADDC` | **PROVEN:** this image has 32 contiguous code pointers before the next non-code entry. These include inherited base functions; this is not a list of 32 fully qualified replacement signatures. |
| `BZRNetP2P` vtable `0x0089BE78` | **PROVEN:** four contiguous code pointers, including the send path at `FUN_0075BEB0` and the pump at `FUN_0075AAF0`. This does not imply the complete network implementation has only four functions. |
| `FUN_0075EEA0`, `FUN_0075D800`, existing networking investigation | **PROVEN:** direct LAN gameplay handshakes and packet transport exist. Their peer records and identities normally come from the online lobby contract. |
| `FUN_0078C6C0` | **PROVEN:** the stock Multiplayer click checks readiness and the lobby pointer before opening the lobby screen. Merely enabling the button does not create a session. |

**STRONG INFERENCE:** a native backend can reuse substantial game simulation,
packet and lobby presentation code while supplying local session and identity
functions. Redux already has several provider implementations beneath shared
game interfaces. This is a useful seam, not proof that a vtable swap is enough.

**UNKNOWN:** the full ownership/callback contract for replacing or adapting
those objects, the identity representation required by every consumer, and the
smallest safe adapter for preserving the existing reliable packet transport.
These require further qualification before installing native replacement hooks.
The current identity/ABI findings are recorded in
[DIRECT_LAN_NATIVE_IDENTITY.md](DIRECT_LAN_NATIVE_IDENTITY.md).

## Calling convention caution

The lobby vtable's `+0x38` entry is `FUN_0074B670`, used as GetMyID by the
already-researched owner comparison. Ghidra renders a one-parameter function
returning that parameter. Static disassembly instead shows it saves ECX, takes
the stack pointer at `[ebp+8]` as the destination object's ECX, pushes source
`0x0260B1C8`, calls the copy routine `FUN_0073A740`, returns the destination in
EAX and executes `ret 4`. **STRONG INFERENCE:** this is a hidden
structure-return destination (the equivalent explicit-output ABI must also be
considered), not an input player-ID value. The destination/copy/register facts
are directly supported by the disassembly. The copy routine copies words at offsets
0, 8 and 12; these facts alone do not establish semantic field names or a safe
new identity layout.

Consequently, the direct backend must qualify ECX/EDX use, stack cleanup,
hidden returns, allocation and destruction for each native boundary. It must
not assign fake Steam IDs, reinterpret offsets as guessed semantic fields, or
globally force the existing authentication-ready checks to succeed.

## Implementation sequence

1. Preserve the current selectors and classify the helper as Local tooling.
2. Qualify the native session, identity and peer boundaries with a small,
   reproducible static inventory and caller/assembly checks.
3. Build the client-owned session model: local identities, discovery, join,
   membership, settings/version checks, ready/launch and disconnect handling.
   No external authentication or service dependency is part of that model.
4. Connect that model to qualified native interfaces. Activate a separate
   Direct LAN mode only when the entire required adapter is bound; partial
   readiness must not enter a stock lobby with missing identities or peers.
5. Verify no-login operation with external networking unavailable, then
   physical two-PC discovery, launch, packet exchange and a complete match.
   Test switching back to each existing backend as well.

First multiplayer acceptance may end the session when its host exits, with an
explicit message; host migration must be separately implemented and proven.
Password support and version/mod compatibility must be explicit session
features rather than assumptions inherited from the online lobby service.

## Status

| Component | State |
|---|---|
| Official / Custom / Local selector preservation | Implemented in the development branch |
| Local helper host/discovery | Existing experimental prototype; still needs platform sign-in |
| Released-image backend inventory | Implemented research tool; 36 vtable pointers and 39 boundaries inspected |
| Complete native ABI / ownership qualification | Partial |
| Native identity/roster query adapter | Partial implementation; local/owner/member/count queries, x86 ABI and bounded released owner-predicate execution qualified; see `DIRECT_LAN_ADAPTER.md` |
| Native peer bridge and direct packet mesh | Send/pump/callback ABI, direct TCP reliable and UDP unreliable payloads implemented; fixtures exchange across all pairs; native engine activation remains missing; see `DIRECT_LAN_PEER_BRIDGE.md` |
| Client-owned direct LAN session implementation | Implemented in `agent/direct-lan-backend`; independent state, sockets and multi-process tests; no native gameplay adapter |
| Direct game discovery | Implemented; separate protocol/port from helper service discovery |
| Server Connect / LAN screen split | Default-off layout/discovery preview; native UI unverified; Host/Join gameplay unavailable |
| No-account native host/join/gameplay | UNKNOWN; not implemented or tested |

See [DIRECT_LAN_IMPLEMENTATION.md](DIRECT_LAN_IMPLEMENTATION.md) for transport,
protocol, preview behavior, validation boundaries and the native adapter work
remaining. The session layer has no account/service dependency; this alone does
not establish no-login operation of the game.

Run `reverse_engineering/inspect_direct_lan_backend.py --exe <baseline-exe>
--corpus <private-corpus>` to reproduce the bounded static inventory. It rejects
other executable hashes and stores generated material in the ignored workshop
directory, separately from this hand-authored analysis. The tool's inferred
signature hints are explicitly unqualified and are not a shipping API contract.
