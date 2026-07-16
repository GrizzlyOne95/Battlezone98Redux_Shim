import struct
import unittest

from server import EndpointProbeProtocol, ProtocolState


def message(message_type, content=True):
    return {"type": message_type, "content": content}


class ProtocolStateTests(unittest.TestCase):
    def setUp(self):
        self.state = ProtocolState()
        self.state.handle("a", message("Authorization", {"id": "A", "name": "Alpha"}))
        self.state.handle("b", message("Authorization", {"id": "B", "name": "Bravo"}))

    def test_create_join_and_metadata(self):
        created = self.state.handle("a", message("CreateGame", {"memberLimit": 4}))
        self.assertTrue(any(item.payload["type"] == "OnLobbyCreated" for item in created))
        lobby_id = self.state.clients_by_connection["a"].lobby_id

        joined = self.state.handle("b", message("DoJoinLobby", {"id": lobby_id, "password": ""}))
        self.assertTrue(any(item.payload["type"] == "OnLobbyJoined" for item in joined))
        self.assertEqual(self.state.lobbies[lobby_id].members, ["A", "B"])

        self.state.handle("a", message("SetLobbyData", {"key": "map", "value": "test.bzn"}))
        self.state.handle("b", message("SetPlayerData", {"key": "ready", "value": "1"}))
        view = self.state.lobby_view(self.state.lobbies[lobby_id])
        self.assertEqual(view["metadata"]["map"], "test.bzn")
        self.assertEqual(view["users"]["B"]["metadata"]["ready"], "1")
        self.assertEqual(view["userCount"], 2)
        self.assertFalse(view["isLocked"])

    def test_default_chat_lobby_is_seeded_for_stock_join_flow(self):
        default = self.state.lobbies[1]
        view = self.state.lobby_view(default)

        self.assertTrue(view["isChat"])
        self.assertEqual(view["metadata"]["name"], "~chat~pub~~default")
        self.assertEqual(view["metadata"]["userCount"], "1")
        self.assertEqual(view["metadata"]["userPack"], "!BRIDGE".ljust(32))
        self.assertIn("BLOCALBRIDGE", view["users"])

    def test_password_and_owner_enforcement(self):
        self.state.handle("a", message("CreateLobby", {"memberLimit": 2, "password": "secret"}))
        lobby_id = self.state.clients_by_connection["a"].lobby_id
        failed = self.state.handle("b", message("DoJoinLobby", {"id": lobby_id, "password": "wrong"}))
        self.assertFalse(failed[0].payload["data"]["success"])

        self.state.handle("b", message("SetLobbyData", {"key": "name", "value": "hijack"}))
        self.assertNotIn("name", self.state.lobbies[lobby_id].metadata)

    def test_chat_lobby_derives_user_pack_and_count(self):
        self.state.handle("a", message("CreateLobby", {"memberLimit": 4}))
        lobby_id = self.state.clients_by_connection["a"].lobby_id
        self.state.handle("b", message("DoJoinLobby", {"id": lobby_id}))

        view = self.state.lobby_view(self.state.lobbies[lobby_id])
        self.assertTrue(view["isChat"])
        self.assertEqual(view["metadata"]["userCount"], "2")
        self.assertEqual(view["metadata"]["userPack"], "Alpha".ljust(32) + "Bravo".ljust(32))

    def test_disconnect_migrates_owner_then_removes_lobby(self):
        self.state.handle("a", message("CreateLobby", {"memberLimit": 4}))
        lobby_id = self.state.clients_by_connection["a"].lobby_id
        self.state.handle("b", message("DoJoinLobby", {"id": lobby_id}))
        self.state.disconnect("a")
        self.assertEqual(self.state.lobbies[lobby_id].owner, "B")
        self.state.disconnect("b")
        self.assertNotIn(lobby_id, self.state.lobbies)

    def test_owner_can_transfer_lobby_ownership(self):
        self.state.handle("a", message("CreateLobby", {"memberLimit": 4}))
        lobby_id = self.state.clients_by_connection["a"].lobby_id
        self.state.handle("b", message("DoJoinLobby", {"id": lobby_id}))
        self.state.handle("a", message("DoSetLobbyOwner", "B"))
        self.assertEqual(self.state.lobbies[lobby_id].owner, "B")

    def test_p2p_connect_notifies_target_with_requester(self):
        self.state.handle("a", message("CreateGame", {"memberLimit": 4}))
        lobby_id = self.state.clients_by_connection["a"].lobby_id
        self.state.handle("b", message("DoJoinLobby", {"id": lobby_id}))

        deliveries = self.state.handle(
            "b", message("DoP2PConnect", {"player": "A", "reset": False})
        )
        self.assertEqual(deliveries[0].connections, ("a",))
        self.assertEqual(deliveries[0].payload["type"], "OnLobbyMemberP2PConnect")
        self.assertEqual(deliveries[0].payload["data"]["member"], "B")
        self.assertEqual(deliveries[0].payload["data"]["lobbyId"], lobby_id)


class EndpointProbeTests(unittest.TestCase):
    def test_ipv4_response_echoes_header_and_appends_observed_endpoint(self):
        now_ms = 1_774_116_680_947
        request = bytes((0x40, 0x02)) + now_ms.to_bytes(8, "big") + bytes(8)
        response = EndpointProbeProtocol.response_for(
            request, ("203.0.113.10", 42424), now_ms=now_ms + 125
        )
        self.assertEqual(
            response,
            request + b"\x04" + bytes((203, 0, 113, 10)) + struct.pack("!H", 42424),
        )

    def test_rejects_wrong_kind_length_and_stale_timestamp(self):
        now_ms = 1_774_116_680_947
        valid = bytes((0x40, 0x02)) + now_ms.to_bytes(8, "big") + bytes(8)
        self.assertIsNone(EndpointProbeProtocol.response_for(valid[:-1], ("127.0.0.1", 1), now_ms))
        self.assertIsNone(EndpointProbeProtocol.response_for(b"\x40\x03" + valid[2:], ("127.0.0.1", 1), now_ms))
        self.assertIsNone(
            EndpointProbeProtocol.response_for(valid, ("127.0.0.1", 1), now_ms + 60_001)
        )


if __name__ == "__main__":
    unittest.main()
