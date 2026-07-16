# Experimental BZRNet Control-Plane Server

This is a clean-room development implementation of the observed Battlezone 98
Redux WebSocket lobby protocol. It is useful for protocol tests and for growing
a custom matchmaking service one message at a time.

The paired stock capture has now supplied the exact direct-connect control
event and UDP endpoint-probe format. This server implements the WebSocket
control plane, `DoP2PConnect` routing, and UDP probe service on port `1338`.

It is a direct-connect development replacement, not yet a production service.
UDP relay (`1339`) and `DoP2PRoute` remain unimplemented, authentication is
development-only, and no security review has been performed.

A filtered stock connection trace on 2026-07-13 showed that Rebellion seeds a
persistent default chat lobby and bridge user before the client enters the
lounge. The client then joins that existing lobby instead of creating one. The
server now reproduces that startup state and derives the stock chat-lobby
`userCount` and fixed-width `userPack` metadata.

Live validation with the stock 2.2.301 client now reaches a ready multiplayer
lobby through the local server: the `DEFAULT` room and both users appear, and
the "gathering information" overlay clears. The observed client sequence was
`Authorization`, `DoEnterLounge`, `DoJoinLobby`, and `SetPlayerData`. Game
creation, a second real client, and relay routing still need live validation.

```powershell
python -m pip install -r reverse_engineering/bzrnet_server/requirements.txt
python reverse_engineering/bzrnet_server/server.py
python -m unittest discover -s reverse_engineering/bzrnet_server -p 'test_*.py' -v
```

Use this OpenShim configuration to redirect the stock hostname while retaining
the stock ports:

```ini
[OpenShimSocket]
MatchmakingRedirectAddress=127.0.0.1
```

The default listeners are WebSocket TCP `1337` and endpoint-probe UDP `1338`.
Use `--disable-probe` only for isolated control-plane tests. The server binds to
loopback by default and accepts development identities without retaining or
validating Steam tickets. Do not expose it to an untrusted network.

Recovered wire details and capture limits are documented in
[`../bzrnet_protocol_capture_20260321.md`](../bzrnet_protocol_capture_20260321.md).
