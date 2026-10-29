# Direct LAN implementation milestone

Development branch: `agent/direct-lan-backend`, stacked on the existing Local
host tools branch. This is development source, not playable LAN or a release.
The target remains the seamless 1.5-style experience described in
[DIRECT_LAN_BACKEND.md](DIRECT_LAN_BACKEND.md). The new protocol is OpenShim's;
it is not wire-compatible with 1.5, ANet, the helper, or stock online clients.

## Connection screen

The intended player flow is:

```text
Multiplayer
  Server Connect -> Official (Rebellion) / Custom / Local -> existing lobby
  LAN            -> Host Game / Nearby Games / Join by IP -> direct session
```

`[Network] ConnectionSetupPreview=1` enables a development layout and discovery
preview. It defaults to **0** in both INIs. Server Connect retains the existing
nickname, flag, server selectors and optional Local host tools. LAN starts the
new browser automatically, supports Refresh, and shows the first six results.
Host/Join controls explain that gameplay is unavailable; they do not create a
native session. The address field accepts IPv4 syntax for this preview only.
No preview choice saves a server selection, starts a helper, supplies a fake
identity, or changes engine/platform readiness. Back uses normal shell history
and closing LAN releases its discovery socket and borrowed text-entry pointers.
Native layout, focus, typing and navigation remain unverified.

The final LAN flow should reuse the existing player name/flag preferences,
automatically choose the sole eligible LAN adapter, and offer an adapter choice
when several are present. These parts, map/options editing and paging are still
pending. A saved Server Connect preference must not select the Direct LAN
backend implicitly.

## Client-owned session layer

`include/direct_lan_session.h` and `src/network/direct_lan_session.cpp` implement
an engine-independent state machine. Each participant has a fresh opaque
128-bit local identity; these values are never platform identities. The host
owns the roster, slot allocation, map/settings revision and launch decision.
Joining validates protocol, game build, a nonzero 32-byte content fingerprint,
capacity, unique identity and unique gameplay endpoint. The transport supplies
the guest's observed source IP; a guest supplies its bound gameplay port.
The native adapter still needs to compute the actual content fingerprint and
serialize the agreed game settings. Test fingerprints/settings are fixtures.

Membership or settings changes invalidate readiness. A launch requires every
member ready at the current revision, followed by Prepare, each adapter's
Prepared response, and Commit. **Prepared must only be called after actual
native gameplay peer setup succeeds.** The standalone tests emulate that
adapter response and establish no engine or simulation readiness.

Heartbeats run every second; a silent peer expires after five seconds. A
ten-second prepare timeout cancels launch and resets readiness. Departure
during preparation also cancels launch. Guest departure during Running updates
the remaining roster; the adapter's corresponding gameplay cleanup is pending.
Events capture their state, preserving the committed launch roster when a
departure arrives in the same socket pump. The adapter must check that a
pending Prepare still matches current revision/phase before preparing peers.
Host departure ends the session; no host migration is implemented. Timeouts
need native loading/stall qualification before release. A new Node is required
for a new session; returning from a completed game to its lobby is pending.

## Transport and discovery

`direct_lan_transport.cpp` embeds a nonblocking TCP control listener in the
hosting **client process**. Other clients connect directly. There is no helper,
WebSocket, account provider, DNS lookup, public-IP probe, relay or remote
service dependency. It supports partial sends, fragmented/coalesced frames,
bounded work, send queues, connection limits, message rates, greeting/connect
deadlines and a bounded graceful half-close. Socket ownership is per object;
Winsock initialization occurs on explicit construction, never at DLL load.
The Win32 plugin retains delay-loading of `ws2_32.dll`.

The control TCP socket carries small session messages only. A separate direct
peer candidate now carries reliable payloads over pairwise TCP and unreliable
payloads over UDP through a Redux callback bridge. See
[DIRECT_LAN_PEER_BRIDGE.md](DIRECT_LAN_PEER_BRIDGE.md) for its contract and
validation limits. Reuse of stock BZRNet UDP remains an alternative requiring
native peer-record qualification. This avoids designing another reliable UDP protocol:
[RFC 8085](https://www.rfc-editor.org/rfc/rfc8085.html) describes the reliability
and congestion responsibilities of UDP applications. This is a design choice,
not a claim about the exact transport used in 1.5.

Control frames have a four-byte big-endian body length, at most 4096 body bytes:
eight-byte `BZLANP02`, type byte, three zero bytes, 16-byte session ID, 16-byte
sender ID, eight-byte serial, then the typed payload. Unknown versions/types,
nonzero reserved bytes, invalid lengths and malformed state are rejected.
Serials and revisions prevent stale control updates; they are not cryptographic
authentication. A connection binds its accepted local ID to its roster entry.

`direct_lan_discovery.cpp` uses UDP **21338**, separately from the helper's
`BZRLAN1`/21337. A `BZRLAN2?` request is exactly 192 bytes: magic, a random
16-byte nonce, zero padding. A `BZRLAN2!` response is 80..173 bytes: magic,
echoed nonce, session ID, actual control port, member/capacity bytes, content
fingerprint, length-prefixed build and session name. Integers use big endian.
The browser uses the response's source address and requires the expected UDP
source port. Replies are smaller than queries and are rate limited per source
and globally. Discovery labels are untrusted printable text, not identity proof.

Scans last three seconds, query every 750ms, and retain at most 32 results.
Targets include active private-interface broadcasts, limited broadcast and
loopback; Winsock explicitly enables
[SO_BROADCAST](https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-sendto).
Discovery listens on ANY to receive broadcasts and only answers sources on the
host's selected adapter subnet. Control binds to that adapter's explicit IPv4
address. Only RFC1918, IPv4 loopback and link-local peers are accepted. No
firewall rules change. Multi-adapter routing, VPNs, isolated Wi-Fi and physical
two-PC broadcast behavior still require qualification. IPv6 is not implemented.
The Node API accepts an explicit control port for direct-IP fallback; choosing
a stable default port and the final UI's optional `:port` handling are pending.

The mode assumes a trusted LAN. It has no encryption, password, account
verification or protection against a malicious session host. Nonces and random
IDs identify sessions without establishing trust. No internet hosting or
interoperability with unpatched/older clients is promised.

## Native adapter boundary

The session/control code builds into `openshim.dll` but no gameplay Node is
created by the UI. Discovery preview alone uses the new Browser. No new native
patch address or authentication bypass is installed. A partial identity/roster
query adapter is implemented and tested against bounded released-code paths;
see [DIRECT_LAN_ADAPTER.md](DIRECT_LAN_ADAPTER.md). It is not a complete backend.
See
[DIRECT_LAN_NATIVE_IDENTITY.md](DIRECT_LAN_NATIVE_IDENTITY.md) for the current
released-image identity evidence and remaining ABI work.

The remaining implementation must qualify lobby ownership and callbacks, all
identity serialization/equality, roster-to-native-player creation, peer
endpoint publication, reliable/unreliable gameplay I/O, launch and teardown.
Activation must bind the entire required adapter or fail visibly before
entering a stock lobby. Switching back must restore the previous backend's
full object lifetime and provider behavior. Reusing stock gameplay transport
is still a **STRONG INFERENCE**, not an implemented native contract.

## Validation and acceptance

The CTest additions cover state/wire validation, real loopback TCP/UDP sockets,
and independent native processes running the same Node. Process cases include
discovered and manual joins, three/four participants, the prepare/commit
barrier, abrupt guest departure, explicit host shutdown, content mismatch,
malformed framing, a stalled greeting and control flooding followed by a valid
session. Each fixture now opens pairwise TCP/UDP endpoints and exchanges routing
test payloads through the peer bridge. Those payloads are not serialized native
game messages. Linux also checks a subnet-broadcast query so a unicast-only listener
cannot pass solely through loopback discovery.

Run the five `direct_lan_` CTests after building tests in Release Win32.
GCC host checks use the same sources with `-Wall -Wextra -Werror` and UBSan;
they are host qualification, not Proton/Wine proof. Full CTest, INI and network
baseline results belong to this branch's PR, not to a deployed game build.

Remaining release acceptance: qualified native adapter, native UI, no-login
operation with external networking unavailable, two physical PCs discovering,
joining, exchanging gameplay and completing a match; map/settings mismatches;
host/guest exit and repeated sessions; adapter/firewall variations; switching
back to Official/Custom/Local; Windows GOG, Windows Steam, Steam Proton and
GOG Wine/Proton. No game launch, deployment or gameplay acceptance is implied
by this milestone.
