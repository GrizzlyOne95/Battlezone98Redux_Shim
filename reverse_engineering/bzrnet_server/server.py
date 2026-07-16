"""Experimental clean-room BZRNet control-plane emulator.

This implements the captured lobby/matchmaking state and the UDP endpoint
probe used by direct LAN/WAN peer negotiation. The UDP relay protocol on port
1339 is not yet implemented, so this remains a direct-connect development
server rather than a complete production replacement for BZRNet.
"""

from __future__ import annotations

import argparse
import asyncio
import ipaddress
import json
import logging
import struct
import time
from dataclasses import dataclass, field
from datetime import datetime, timezone
from typing import Any

import websockets


LOG = logging.getLogger("bzrnet_server")


@dataclass
class Client:
    connection: str
    client_id: str
    name: str
    realname: str
    auth_type: str
    client_version: str = ""
    ip_address: str = "unknown"
    metadata: dict[str, Any] = field(default_factory=dict)
    lan_addresses: list[str] = field(default_factory=list)
    wan_address: str = ""
    in_lounge: bool = False
    lobby_id: int | None = None

    def public(self) -> dict[str, Any]:
        return {
            "isInLounge": self.in_lounge,
            "lanAddresses": list(self.lan_addresses),
            "wanAddress": self.wan_address or "unknown",
            "metadata": dict(self.metadata),
            "ipAddress": self.ip_address,
            "isBB": False,
            "isAdmin": False,
            "isAuth": True,
            "lobby": self.lobby_id,
            "id": self.client_id,
            "name": self.name,
            "authType": self.auth_type,
            "clientVersion": self.client_version,
            "isTest": False,
        }


@dataclass
class Lobby:
    lobby_id: int
    owner: str
    member_limit: int
    is_private: bool
    password: str
    lobby_type: str
    client_version: str = ""
    created_time: str = field(
        default_factory=lambda: datetime.now(timezone.utc).isoformat(timespec="milliseconds").replace("+00:00", "Z")
    )
    locked: bool = False
    metadata: dict[str, Any] = field(default_factory=dict)
    members: list[str] = field(default_factory=list)


@dataclass(frozen=True)
class Delivery:
    connections: tuple[str, ...]
    payload: dict[str, Any]


class ProtocolState:
    """Deterministic protocol model kept separate from WebSocket transport."""

    def __init__(self) -> None:
        self.clients_by_connection: dict[str, Client] = {}
        self.connections_by_id: dict[str, str] = {}
        self.system_clients_by_id: dict[str, Client] = {}
        self.lobbies: dict[int, Lobby] = {}
        self.next_client = 1
        self.next_lobby = 1
        self.seed_default_chat_lobby()

    def seed_default_chat_lobby(self) -> None:
        client_id = "BLOCALBRIDGE"
        lobby_id = self.next_lobby
        self.next_lobby += 1
        bridge = Client(
            connection="",
            client_id=client_id,
            name="!BRIDGE",
            realname="!BRIDGE",
            auth_type="bridge",
            client_version="2.2.301",
            in_lounge=True,
            lobby_id=lobby_id,
        )
        self.system_clients_by_id[client_id] = bridge
        self.lobbies[lobby_id] = Lobby(
            lobby_id=lobby_id,
            owner=client_id,
            member_limit=200,
            is_private=False,
            password="",
            lobby_type="CreateLobby",
            metadata={
                "name": "~chat~pub~~default",
                "gameType": "1",
                "gameSettings": "*",
                "GameVersion": "2.2.301",
            },
            members=[client_id],
        )

    @staticmethod
    def event(event_type: str, data: Any) -> dict[str, Any]:
        if isinstance(data, dict):
            body = {
                "type": event_type,
                "time": datetime.now(timezone.utc).strftime("%Y-%m-%d %H:%M:%S"),
                "success": True,
            }
            body.update(data)
        else:
            body = data
        return {"type": event_type, "data": body}

    def one(self, connection: str, event_type: str, data: Any) -> Delivery:
        return Delivery((connection,), self.event(event_type, data))

    def client(self, connection: str) -> Client | None:
        return self.clients_by_connection.get(connection)

    def connections(self, client_ids: list[str]) -> tuple[str, ...]:
        return tuple(
            self.connections_by_id[client_id]
            for client_id in client_ids
            if client_id in self.connections_by_id
        )

    def client_by_id(self, client_id: str) -> Client | None:
        connection = self.connections_by_id.get(client_id)
        if connection:
            return self.clients_by_connection.get(connection)
        return self.system_clients_by_id.get(client_id)

    def lounge_connections(self) -> tuple[str, ...]:
        return tuple(
            client.connection
            for client in self.clients_by_connection.values()
            if client.in_lounge
        )

    def lobby_metadata(self, lobby: Lobby) -> dict[str, Any]:
        metadata = dict(lobby.metadata)
        metadata["userCount"] = str(len(lobby.members))
        if lobby.lobby_type == "CreateLobby":
            names = []
            for client_id in lobby.members:
                client = self.client_by_id(client_id)
                if client:
                    names.append(client.name[:32].ljust(32))
            metadata["userPack"] = "".join(names)
        return metadata

    def lobby_view(self, lobby: Lobby) -> dict[str, Any]:
        return {
            "userCount": len(lobby.members),
            "memberLimit": lobby.member_limit,
            "isPrivate": lobby.is_private,
            "isLocked": lobby.locked,
            "metadata": self.lobby_metadata(lobby),
            "owner": lobby.owner,
            "isChat": lobby.lobby_type == "CreateLobby",
            "clientVersion": lobby.client_version,
            "id": lobby.lobby_id,
            "createdTime": lobby.created_time,
            "users": {
                client_id: self.client_by_id(client_id).public()
                for client_id in lobby.members
                if self.client_by_id(client_id) is not None
            },
        }

    def lobby_list(self) -> dict[str, Any]:
        return {str(lobby_id): self.lobby_view(lobby) for lobby_id, lobby in self.lobbies.items()}

    def list_changed(self) -> Delivery | None:
        recipients = self.lounge_connections()
        if not recipients:
            return None
        return Delivery(recipients, self.event(
            "OnLobbyListChanged",
            {"lobbies": self.lobby_list(), "totalUsers": len(self.clients_by_connection) + len(self.system_clients_by_id)},
        ))

    def lobby_changed(self, lobby: Lobby) -> Delivery:
        return Delivery(
            self.lounge_connections(),
            self.event("OnLobbyChanged", {
                "lobbies": {str(lobby.lobby_id): self.lobby_view(lobby)},
                "totalUsers": len(self.clients_by_connection) + len(self.system_clients_by_id),
            }),
        )

    def lobby_notice(self, lobby: Lobby, event_type: str, data: dict[str, Any]) -> Delivery:
        return Delivery(self.lounge_connections(), self.event(event_type, data))

    def allocate_client_id(self, requested: Any) -> str:
        candidate = str(requested or "")
        if candidate and candidate != "0" and candidate not in self.connections_by_id:
            return candidate
        while True:
            candidate = f"D{self.next_client}"
            self.next_client += 1
            if candidate not in self.connections_by_id:
                return candidate

    def authorize(self, connection: str, content: dict[str, Any]) -> list[Delivery]:
        old = self.clients_by_connection.get(connection)
        if old:
            return [self.one(connection, "OnAuthorization", {"success": True, "id": old.client_id})]

        client_id = self.allocate_client_id(content.get("id"))
        name = str(content.get("name") or content.get("playerName") or client_id)
        client = Client(
            connection=connection,
            client_id=client_id,
            name=name,
            realname=str(content.get("realname") or name),
            auth_type=str(content.get("authtype") or "dev"),
            client_version=str(content.get("clientVersion") or ""),
            ip_address=str(content.get("ipAddress") or "unknown"),
            lan_addresses=[str(value) for value in content.get("lanAddresses", [])],
            wan_address=str(content.get("wanAddress") or ""),
            in_lounge=bool(content.get("inLounge", False)),
        )
        self.clients_by_connection[connection] = client
        self.connections_by_id[client_id] = connection
        whitelist = {
            "list": ["*.wav", "*.ogg", "*.ini", "*.inf", "*.jpg", "*.txt", "*.stb", "*.des", "*.dds", "*.png", "*.sta", "*mod.material"],
            "major": 8,
            "minor": 0,
        }
        return [
            self.one(connection, "OnAuthorization", {
                "success": True, "isAdmin": False, "id": client_id, "isBB": False
            }),
            self.one(connection, "OnWhitelistUpdated", {"whitelist": whitelist}),
        ]

    def create_lobby(self, client: Client, content: dict[str, Any], lobby_type: str) -> list[Delivery]:
        deliveries = self.leave_lobby(client, notify=False)
        lobby_id = self.next_lobby
        self.next_lobby += 1
        lobby = Lobby(
            lobby_id=lobby_id,
            owner=client.client_id,
            member_limit=max(1, int(content.get("memberLimit", 16))),
            is_private=bool(content.get("isPrivate", False)),
            password=str(content.get("password") or ""),
            lobby_type=lobby_type,
            client_version=client.client_version,
            members=[client.client_id],
        )
        if content.get("name"):
            lobby.metadata["name"] = str(content["name"])
        self.lobbies[lobby_id] = lobby
        client.lobby_id = lobby_id
        deliveries.append(self.one(client.connection, "OnLobbyCreated", {"success": True, "id": lobby_id}))
        deliveries.append(self.lobby_changed(lobby))
        deliveries.append(self.lobby_notice(lobby, "OnLobbyMemberListChanged", {
            "member": client.client_id, "lobbyId": lobby_id, "removed": False
        }))
        changed = self.list_changed()
        if changed:
            deliveries.append(changed)
        return deliveries

    def join_lobby(self, client: Client, content: dict[str, Any]) -> list[Delivery]:
        try:
            lobby_id = int(content.get("id"))
        except (TypeError, ValueError):
            return [self.one(client.connection, "OnLobbyJoined", {"success": False, "reason": "invalid id"})]
        lobby = self.lobbies.get(lobby_id)
        reason = None
        if not lobby:
            reason = "not found"
        elif lobby.locked:
            reason = "locked"
        elif len(lobby.members) >= lobby.member_limit:
            reason = "full"
        elif lobby.password and str(content.get("password") or "") != lobby.password:
            reason = "bad password"
        if reason:
            reason_codes = {"not found": 1, "locked": 2, "full": 3, "bad password": 4}
            return [self.one(client.connection, "OnLobbyJoined", {
                "success": False, "id": lobby_id, "reason": reason,
                "reasonCode": reason_codes.get(reason, -1),
            })]

        deliveries = self.leave_lobby(client, notify=True)
        if client.client_id not in lobby.members:
            lobby.members.append(client.client_id)
        client.lobby_id = lobby_id
        deliveries.append(self.lobby_changed(lobby))
        deliveries.append(self.lobby_notice(lobby, "OnLobbyMemberListChanged", {
            "member": client.client_id, "lobbyId": lobby_id, "removed": False
        }))
        deliveries.append(self.one(client.connection, "OnLobbyJoined", {
            "success": True, "id": lobby_id, "reason": "", "reasonCode": 0
        }))
        changed = self.list_changed()
        if changed:
            deliveries.append(changed)
        return deliveries

    def leave_lobby(self, client: Client, notify: bool = True) -> list[Delivery]:
        if client.lobby_id is None:
            return []
        lobby = self.lobbies.get(client.lobby_id)
        client.lobby_id = None
        if not lobby:
            return []
        lobby.members = [member for member in lobby.members if member != client.client_id]
        deliveries: list[Delivery] = []
        recipients = self.lounge_connections()
        if not lobby.members:
            del self.lobbies[lobby.lobby_id]
            if notify:
                if recipients:
                    deliveries.append(Delivery(recipients, self.event("OnLobbyRemoved", {"id": lobby.lobby_id})))
            return deliveries
        if lobby.owner == client.client_id:
            lobby.owner = lobby.members[0]
        if notify:
            deliveries.append(self.lobby_changed(lobby))
            deliveries.append(Delivery(recipients, self.event("OnLobbyMemberListChanged", {
                "member": client.client_id, "lobbyId": lobby.lobby_id, "removed": True
            })))
        return deliveries

    def set_lobby_data(self, client: Client, content: dict[str, Any]) -> list[Delivery]:
        lobby = self.lobbies.get(client.lobby_id or -1)
        if not lobby or lobby.owner != client.client_id:
            return []
        key = str(content.get("key") or "")
        if not key:
            return []
        lobby.metadata[key] = content.get("value")
        deliveries = [
            self.lobby_changed(lobby),
            self.lobby_notice(lobby, "OnLobbyDataChanged", {"changedLobby": lobby.lobby_id}),
        ]
        changed = self.list_changed()
        if changed:
            deliveries.append(changed)
        return deliveries

    def set_player_data(self, client: Client, content: dict[str, Any]) -> list[Delivery]:
        key = str(content.get("key") or "")
        if not key:
            return []
        value = content.get("value")
        client.metadata[key] = value
        if key in {"name", "playerName"} and value:
            client.name = str(value)
        lobby = self.lobbies.get(client.lobby_id or -1)
        if lobby:
            return [
                self.lobby_changed(lobby),
                self.lobby_notice(lobby, "OnUserDataChanged", {
                    "member": client.client_id, "lobbyId": lobby.lobby_id
                }),
            ]
        return []

    def handle(self, connection: str, message: dict[str, Any]) -> list[Delivery]:
        message_type = str(message.get("type") or "")
        content = message.get("content", {})
        if message_type == "Authorization" and isinstance(content, dict):
            return self.authorize(connection, content)

        client = self.client(connection)
        if not client:
            return [self.one(connection, "OnAuthorization", {"success": False, "reason": "authorize first"})]

        if message_type == "DoEnterLounge":
            client.in_lounge = True
            return [self.one(connection, "OnLobbyListChanged", {
                "lobbies": self.lobby_list(), "totalUsers": len(self.clients_by_connection) + len(self.system_clients_by_id)
            })]
        if message_type == "DoExitLounge":
            client.in_lounge = False
            return []
        if message_type == "GetLobbyList":
            return [self.one(connection, "OnLobbyListChanged", {
                "lobbies": self.lobby_list(), "totalUsers": len(self.clients_by_connection) + len(self.system_clients_by_id)
            })]
        if message_type in {"CreateLobby", "CreateGame"} and isinstance(content, dict):
            return self.create_lobby(client, content, message_type)
        if message_type == "DoJoinLobby" and isinstance(content, dict):
            return self.join_lobby(client, content)
        if message_type == "DoExitLobby":
            deliveries = self.leave_lobby(client)
            changed = self.list_changed()
            if changed:
                deliveries.append(changed)
            return deliveries
        if message_type == "SetLobbyData" and isinstance(content, dict):
            return self.set_lobby_data(client, content)
        if message_type == "DeleteLobbyData" and isinstance(content, dict):
            lobby = self.lobbies.get(client.lobby_id or -1)
            if lobby and lobby.owner == client.client_id:
                lobby.metadata.pop(str(content.get("key") or content), None)
                return [
                    self.lobby_changed(lobby),
                    self.lobby_notice(lobby, "OnLobbyDataChanged", {"changedLobby": lobby.lobby_id}),
                ]
            return []
        if message_type == "SetPlayerData" and isinstance(content, dict):
            return self.set_player_data(client, content)
        if message_type == "LockLobby":
            lobby = self.lobbies.get(client.lobby_id or -1)
            if lobby and lobby.owner == client.client_id:
                lobby.locked = bool(content if not isinstance(content, dict) else content.get("locked", True))
                return [
                    self.lobby_changed(lobby),
                    self.lobby_notice(lobby, "OnLobbyDataChanged", {"changedLobby": lobby.lobby_id}),
                ]
            return []
        if message_type == "SetLobbyMemberLimit":
            lobby = self.lobbies.get(client.lobby_id or -1)
            if lobby and lobby.owner == client.client_id:
                value = content.get("memberLimit") if isinstance(content, dict) else content
                lobby.member_limit = max(len(lobby.members), int(value))
                return [
                    self.lobby_changed(lobby),
                    self.lobby_notice(lobby, "OnLobbyDataChanged", {"changedLobby": lobby.lobby_id}),
                ]
            return []
        if message_type == "DoSetLobbyOwner":
            lobby = self.lobbies.get(client.lobby_id or -1)
            if lobby and lobby.owner == client.client_id:
                value = content.get("player", content.get("owner")) if isinstance(content, dict) else content
                new_owner = str(value or "")
                if new_owner in lobby.members:
                    lobby.owner = new_owner
                    return [
                        self.lobby_changed(lobby),
                        self.lobby_notice(lobby, "OnLobbyDataChanged", {"changedLobby": lobby.lobby_id}),
                    ]
            return []
        if message_type in {"DoUpdateLAN", "DoUpdateWAN"}:
            if message_type == "DoUpdateLAN":
                values = content.get("lanAddresses", content) if isinstance(content, dict) else content
                client.lan_addresses = [str(value) for value in (values or [])]
            else:
                value = content.get("wanAddress", content) if isinstance(content, dict) else content
                client.wan_address = str(value or "")
            lobby = self.lobbies.get(client.lobby_id or -1)
            return [self.lobby_changed(lobby)] if lobby else []
        if message_type == "DoSendChat":
            lobby = self.lobbies.get(client.lobby_id or -1)
            if not lobby:
                return []
            text = content.get("text", content) if isinstance(content, dict) else content
            return [Delivery(self.connections(lobby.members), self.event(
                "OnChatMessage", {
                    "text": str(text), "lobbyId": lobby.lobby_id, "speakerId": client.client_id
                }
            ))]

        if message_type == "DoP2PConnect" and isinstance(content, dict):
            target_id = str(content.get("player") or "")
            target = self.connections_by_id.get(target_id)
            lobby = self.lobbies.get(client.lobby_id or -1)
            if not target or not lobby or target_id not in lobby.members:
                return []
            return [self.one(target, "OnLobbyMemberP2PConnect", {
                "member": client.client_id,
                "lobbyId": lobby.lobby_id,
                "connect": True,
                "reset": bool(content.get("reset", False)),
            })]

        # P2P/relay messages are deliberately left unanswered until their exact
        # response schemas and UDP wire formats are captured.
        LOG.warning("Unsupported message type from %s: %s", client.client_id, message_type)
        return []

    def disconnect(self, connection: str) -> list[Delivery]:
        client = self.clients_by_connection.get(connection)
        if not client:
            return []
        deliveries = self.leave_lobby(client)
        self.clients_by_connection.pop(connection, None)
        self.connections_by_id.pop(client.client_id, None)
        changed = self.list_changed()
        if changed:
            deliveries.append(changed)
        return deliveries


class EndpointProbeProtocol(asyncio.DatagramProtocol):
    """BZRNet UDP/1338 public-endpoint discovery observed in stock captures."""

    HEADER_SIZE = 18
    MAX_CLOCK_SKEW_MS = 60_000

    def __init__(self) -> None:
        self.transport: asyncio.DatagramTransport | None = None

    def connection_made(self, transport: asyncio.BaseTransport) -> None:
        self.transport = transport  # type: ignore[assignment]

    @classmethod
    def response_for(cls, data: bytes, address: tuple[Any, ...], now_ms: int | None = None) -> bytes | None:
        if len(data) != cls.HEADER_SIZE:
            return None
        if not data[0] & 0x40 or data[0] & 0x80 or data[1] & 0x0F != 2:
            return None
        sent_ms = int.from_bytes(data[2:10], "big")
        current_ms = int(time.time() * 1000) if now_ms is None else now_ms
        if abs(current_ms - sent_ms) > cls.MAX_CLOCK_SKEW_MS:
            return None
        try:
            packed_ip = ipaddress.ip_address(str(address[0])).packed
            port = int(address[1])
        except (ValueError, TypeError, IndexError):
            return None
        if not 0 <= port <= 0xFFFF:
            return None
        return data + bytes((len(packed_ip),)) + packed_ip + struct.pack("!H", port)

    def datagram_received(self, data: bytes, address: tuple[Any, ...]) -> None:
        response = self.response_for(data, address)
        if response is not None and self.transport is not None:
            self.transport.sendto(response, address)


class WebSocketServer:
    def __init__(self) -> None:
        self.state = ProtocolState()
        self.websockets: dict[str, Any] = {}
        self.next_connection = 1

    async def deliver(self, deliveries: list[Delivery]) -> None:
        for delivery in deliveries:
            encoded = json.dumps(delivery.payload, separators=(",", ":"))
            for connection in delivery.connections:
                websocket = self.websockets.get(connection)
                if websocket:
                    await websocket.send(encoded)

    async def handler(self, websocket: Any) -> None:
        connection = f"connection-{self.next_connection}"
        self.next_connection += 1
        self.websockets[connection] = websocket
        try:
            async for raw in websocket:
                try:
                    message = json.loads(raw)
                    if not isinstance(message, dict):
                        raise ValueError("message must be an object")
                    if message.get("type") == "Authorization" and isinstance(message.get("content"), dict):
                        message = dict(message)
                        content = dict(message["content"])
                        peer = getattr(websocket, "remote_address", None)
                        if peer:
                            peer_ip = str(peer[0])
                            if ":" not in peer_ip:
                                peer_ip = f"::ffff:{peer_ip}"
                            content.setdefault("ipAddress", peer_ip)
                        message["content"] = content
                except (ValueError, json.JSONDecodeError) as exc:
                    await websocket.send(json.dumps(self.state.event("OnError", {"reason": str(exc)})))
                    continue
                LOG.info("%s message type=%s", connection, message.get("type"))
                await self.deliver(self.state.handle(connection, message))
        finally:
            self.websockets.pop(connection, None)
            await self.deliver(self.state.disconnect(connection))


async def run(host: str, port: int, probe_port: int | None) -> None:
    server = WebSocketServer()
    LOG.info("Listening on ws://%s:%d", host, port)
    loop = asyncio.get_running_loop()
    probe_transport: asyncio.DatagramTransport | None = None
    if probe_port is not None:
        probe_transport, _ = await loop.create_datagram_endpoint(
            EndpointProbeProtocol, local_addr=(host, probe_port)
        )
        LOG.info("Listening for endpoint probes on udp://%s:%d", host, probe_port)
    try:
        async with websockets.serve(server.handler, host, port, max_size=2**20):
            await asyncio.Future()
    finally:
        if probe_transport is not None:
            probe_transport.close()


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--host", default="127.0.0.1")
    parser.add_argument("--port", type=int, default=1337)
    parser.add_argument("--probe-port", type=int, default=1338)
    parser.add_argument("--disable-probe", action="store_true")
    parser.add_argument("--verbose", action="store_true")
    args = parser.parse_args()
    logging.basicConfig(level=logging.DEBUG if args.verbose else logging.INFO)
    asyncio.run(run(args.host, args.port, None if args.disable_probe else args.probe_port))


if __name__ == "__main__":
    main()
