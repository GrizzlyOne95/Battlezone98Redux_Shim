# LAN host and discovery preview

Development branch: `agent/lan-host-discovery`, based on OpenShim `045035ea2`.
Companion server source: `e1544da7437b0b619502586f71725098911be82c`
([server draft PR #20](https://github.com/GrizzlyOne95/Battlezone98Redux_DedicatedServer/pull/20)).
The companion DedicatedServer branch supplies the Win32 helper. This is source
development, not a published release or native gameplay acceptance.

## Player flow

Open Multiplayer setup and select **LAN...**. **Host LAN** starts the helper on
this PC, waits for its readiness signal, and returns to setup with its LAN
address selected. Press **Continue**, then create the game in the normal Redux
lobby. Other players use **Refresh**, select that host, then press **Continue**.
The browser discovers lobby services; individual games appear in the normal
Redux lobby after connecting. **Use address** supports a manual host/IP and an
optional `:port` when broadcast discovery is unavailable.

The helper stays alive across Back, lobby and mission transitions. **Stop
Host** disconnects its users. Exiting the game closes the owned process job so
it cannot leave the helper running. A manually started server is never stopped
or adopted. An existing listener/port conflict fails startup without attaching
to an unrelated process. Start Host again for a new game process; a saved LAN
endpoint does not silently launch a helper at startup.

Steam/Galaxy sign-in is still required by the stock client. This preview removes
the need for the external matchmaking service during LAN play; it does not
provide an independent offline identity implementation.

## Implementation and evidence

| Surface | State |
|---|---|
| Existing Redux LAN UDP gameplay transport | PROVEN in the Redux 2.2.301 GOG corpus; see the networking investigation below |
| New registered LAN shell screen, host controls, manual address selection | Implemented; builds as Release Win32; native UI remains unverified |
| Hidden managed server launch, readiness, graceful Stop and process ownership | Implemented; Win32 lifecycle fixture and real frozen-helper checks pass |
| UDP broadcast discovery | Implemented; nonce, bounds, source/port validation and per-adapter broadcasts; local socket integration passes |
| Physical two-PC broadcast/join/gameplay | UNKNOWN; not run |
| No platform login / fully offline identity | Missing; stock authentication/readiness remains in use |

The recommended seam comes from
`reverse_engineering/redux_tcpip_lan_multiplayer_investigation_20260713.md` and
`reverse_engineering/netcode_matchmaking_server_plan_20260713.md`. For Redux
2.2.301, the former records socket creation at `0x006BE750`, LAN/WAN/relay peer
selection at `0x0075EEA0`, and the online endpoint/lobby contract. The feature
supplies that lobby contract locally through the existing server-selection
seam. It adds no executable patch addresses and does not replace simulation
packets. The new discovery wire format is an OpenShim protocol, not recovered
ANet or Redux behavior.

`include/lan_discovery.h` defines `BZRLAN1`: UDP 21337; a 96-byte query with an
eight-byte nonce; a 19–82-byte unicast response containing that nonce, a lobby
port, and a printable name. The client always uses the UDP source address.
Scans last three seconds, accept at most 32 hosts and process at most 64 packets
per UI frame. Active private IPv4 interfaces receive directed broadcasts;
limited broadcast and loopback are also queried. Names are untrusted labels,
not identity proof. The server bounds its per-source/global response rate.

LAN joins save `[Network] Server=LAN` and the endpoint in `CustomServer`.
Unlike Custom mode, a LAN endpoint keeps retrying locally when unavailable;
it never falls back to the official service. Choosing Rebellion or a different
Custom server restores the existing behavior. Existing test redirects retain
priority and suppress access to the LAN chooser.

## Helper packaging

The optional helper is `tools/lan/BZRServer.exe` relative to the game executable.
It is a standalone **i386 Win32 PE**, with Python and websockets bundled; the
player needs no Python installation. Build it in the companion DedicatedServer
repository using `build_lan_helper.py` with a Windows 32-bit Python interpreter.
The helper zip includes its source revision, hash, license, protocol guide and
the exact bundled Python/websockets/PyInstaller license notices.

Stage a clean helper build with:

```powershell
./scripts/Stage-LanHelper.ps1 -HelperDirectory <OpenShimLAN/tools/lan> -DestinationRoot <preview-or-game-root>
```

The script checks the clean source revision, executable and license hashes,
manifest protocol, and actual
PE architecture before copying. It neither downloads nor starts anything.
The ordinary OpenShim release pipeline does not yet bundle this optional
helper; use the combined preview package or stage it explicitly. Missing helper
files produce a visible status message and leave online play available.
`Package-LanPreview.ps1 -HelperDirectory <OpenShimLAN/tools/lan>` builds a local
combined overlay archive from a committed source tree and the complete Release
DLL/resource set. It includes `openshim.ini.example` and preserves active INIs.

Runtime state, audit output and diagnostics go under `openshim/lan/` in the game
root. Diagnostics use a file, avoiding a blocked stderr pipe during gameplay.
Only the readiness line uses stdout. The child is launched by an absolute
executable path, with a restricted inherited-handle list, hidden window,
stdin control and a kill-on-close process job. All discovery and launch work
starts from the UI thread after an explicit click, never during DLL loading.
System Winsock calls remain delay-loaded. No firewall rules are changed.

Allow the helper and game on the private network. A VPN/virtual adapter can be
selected first when hosting; use its correct physical LAN address manually if
necessary. Discovery supports RFC1918, IPv4 loopback and link-local addresses.
Client-isolated Wi-Fi, routed subnets and blocked broadcasts require manual IP
entry and reachable lobby/probe/game sockets. Full IPv6 discovery is not present.

## Validation

The focused C++ protocol suite rejects truncated/oversized packets, wrong
versions/nonces, control characters, invalid ports and nonlocal source ranges.
The Win32 runtime test uses a copied fixture in a Unicode/spaced path and checks
readiness, stderr backpressure, repeated start, stop, restart, child failure and
missing helper. `lan_session_tests --real-helper <scratch-root>` exercises the
same native client against the frozen helper: startup, discovery and shutdown.
The explicit Python runner `tests/lan_real_helper_test.py` also checks that
exiting the owning native process releases the helper sockets. All 155 CTest
cases, INI checks and the network safety baseline pass. The source and frozen
server pass 8 discovery/lifecycle cases, 48 stock-client compatibility cases,
8 protocol-parity cases and all 7 smoke lanes. These tests load no game and
establish no gameplay acceptance. The protocol and matchmaking configuration
suites also pass with GCC under Linux; this is not Proton/Wine runtime proof.

Required remaining acceptance: native screen layout/navigation/typing, two
physical PCs, host/guest launch and a complete match, multiple adapters,
firewall behavior, host exit/disconnect, GOG and Steam, plus Proton/Wine process
supervision and discovery. The same Win32 artifacts are intended for all four
platform lanes; their native behavior is currently unverified.
