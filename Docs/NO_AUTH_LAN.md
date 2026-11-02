# In-process LAN without platform sign-in (development)

Branch `agent/no-auth-lan` is stacked on the Local host/discovery work in PR
#642. It implements the requested game-process-only session host. No helper,
remote account, platform ticket, relay, public endpoint probe or child process
is needed by this mode. It remains disabled by default and is not a release or
a qualified two-PC multiplayer implementation.

## Try the prototype

On each PC, set `[Network] NoAuthLan=1` in the effective `openshim.ini` and
restart the game. Open Multiplayer setup, then **LAN (no sign-in)**. **Start
local host** opens the session listeners inside the hosting game and selects
its displayed private IPv4 address. Press **Continue** to enter the existing
Redux lobby. Guests refresh the LAN browser and select that host, or enter its
private numeric IPv4 address (optional `:port`). Create/join the game through
the normal Redux lobby. A saved host address does not silently start a host.

The host binds TCP 1337 and UDP 1338 to the displayed adapter; UDP 21337 serves
the existing versioned discovery protocol. Gameplay uses Redux's own UDP
socket and direct peer transport. The current UDP port is shown by the existing
network controls; a configured `UdpPort` can make firewall rules predictable.
Custom session ports require the adjacent UDP probe port to be free too.
Discovery can require manual IP entry across routed networks, blocked
broadcasts or client-isolated Wi-Fi. Inspect the displayed adapter on VPN or
multi-adapter systems.

Hosting survives menu/lobby/mission transitions. **Stop Host** disconnects its
clients; process exit releases its sockets. There is no host migration.
Official, Custom and Local keep their existing authentication behavior. Set
`NoAuthLan=0` and restart to return the host-tools screen to its older helper
preview. No helper is launched by the no-auth path.

## Implementation contract

The embedded host owns a bounded WebSocket session model and the stock UDP
endpoint-probe/discovery protocols. It supplies the default chat room, local
admission, game creation, password/full/locked checks, owner-only settings,
membership, string player metadata (including ready/launch), chat and same-room
peer endpoint exchange. It advertises no relay. Leaving a game's owner removes
that room and returns remaining members to the lounge; the hosting process may
continue serving other rooms. The default chat room survives empty membership.

Each game generates a process-scoped random `B` identity in Redux's existing
local/service namespace. This is a local label, not proof of account ownership.
It is not a fabricated Steam or Galaxy ID. Display names use Network/Nickname.
Local admission rejects platform identities/tickets, wrong client versions,
duplicate IDs and public observed source addresses. Endpoints are associated
with the observed peer IP, including values carried in the initial admission
request (Redux sends later endpoint updates only after a change), preventing another player's advertised public IP
from becoming a LAN route. Numeric private IPv4 selection is mandatory; DNS
names and public targets cannot activate the credential bypass.

Qualified native hooks bypass only the two credential-empty checks at the
connection initializer. The normal asynchronous connection/retry machinery
continues to run. An explicit LAN selection starts the initial connection when
there is no provider credential callback. The existing Authorization-content
hook clears all ticket/key fields and writes the local profile, publishing
`authtype=lan` only after the other fields succeed. Provider flags, platform
names and stored platform credentials are not altered. Readiness requires the
actual native admission state **and** the exact generated local identity; it
cannot be enabled by a socket connection or a forced UI flag. Other selections
call the original readiness code. A saved force-relay preference is temporarily
overridden for LAN and restored when leaving it.

The native boundaries live in `scripts/patches.json`, with released-image
byte guards and ABI evidence. Partial installation fails closed. The diagnostic
reads the original readiness trampoline when that function has been detoured.
No new lobby/P2P vtable objects are substituted or lifetime contracts guessed.
Network work runs on an owned worker, with socket/input/output/frame/metadata
bounds, handshake/admission deadlines and bounded shutdown. DLL detach does
not wait for networking.

The local 1.5 reconstruction was consulted for behavioral comparison: locally
owned sessions, admission/room checks, player identity and explicit readiness
before launch. It is a PDB-assisted reconstruction, not buildable original
source. No code, symbol tables, layouts or addresses from it are imported into
this implementation. Redux boundaries are verified independently.

## Validation and limits

The Release Win32 solution builds. The Win32 suite passed all 158 CTests;
targeted checks are repeated after native protocol corrections. INI policy and
network baseline checks pass. Portable model/policy tests cover rejected
admissions, duplicate IDs, cache-before-create ordering, password/owner rules,
metadata bounds, repeated joins, chat, peer signaling and owner departure.
The real socket fixture covers the WebSocket handshake, local admission,
canonical chat room, game creation/join, settings/ready/chat/peer signaling,
owner exit, observed-IP normalization, UDP probe/discovery, exclusive binding
and idle admission expiry. It is an isolated test executable, not a shipped
helper dependency. CTest registers it when Python and `websockets` are present.

An isolated, windowed GOG 2.2.301 launch reached native client state 3, local
identity kind 3 and `PlatformReady=1`. The stock readiness diagnostic reported
`code=3`, Steam uninitialized and Galaxy below its signed-in state. Windows
attributed the session listener to that same game PID. The native initial
connection ran without a provider callback. No installed game files were
replaced. Native testing found and corrected a numeric default-room owner
that Redux's string-typed variant reader rejected, and a zero lobby ID that
Redux treats as an invalid sentinel. A subsequent native test entered the
stock lobby, joined the canonical chat room and created a game. A second
observer confirmed the game's actual map settings, name, team, vehicle, local
player ID, initial UDP endpoints and membership in the in-process host. The stock Launch control
published the player's ready value; this did not establish a mission launch.

Remaining acceptance: native guest join and completed launch flow; actual
direct gameplay packet exchange and a full two-PC match; settings/ready
invalidation and mod/map compatibility; host-loss presentation; switching back
to every online backend; firewall and multi-adapter behavior; Steam, Proton and
Wine runtime lanes. The same Win32 artifact is intended for those platforms,
but host GCC tests do not qualify Proton/Wine. No playable-match claim follows
from admission or protocol tests alone.
