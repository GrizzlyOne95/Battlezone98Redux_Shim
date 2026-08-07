#!/usr/bin/env python3
from __future__ import annotations

import json
import tempfile
import unittest
from pathlib import Path

from align_bzrnet_traces import merge_timelines
from analyze_bzrnet_trace import correlate_relay, load_trace, summarize
from compare_bzrnet_traces import compare_sequences, semantic_messages
from validate_bzrnet_trace import validate_trace


class BzrNetTraceToolTests(unittest.TestCase):
    def write_trace(self, rows: list[dict]) -> Path:
        handle = tempfile.NamedTemporaryFile("w", encoding="utf-8", delete=False, suffix=".jsonl")
        with handle:
            for row in rows:
                handle.write(json.dumps(row) + "\n")
        return Path(handle.name)

    def write_json(self, value: dict) -> Path:
        handle = tempfile.NamedTemporaryFile("w", encoding="utf-8", delete=False, suffix=".json")
        with handle:
            json.dump(value, handle)
        return Path(handle.name)

    @staticmethod
    def ws(message_type: str, payload: dict, direction: str = "inbound", **detail_fields: object) -> dict:
        envelope = "data" if direction == "inbound" else "content"
        details = {"messageJson": json.dumps({"type": message_type, envelope: payload}, separators=(",", ":"))}
        details.update(detail_fields)
        return {"event": "BZR_WS_RX" if direction == "inbound" else "BZR_WS_TX", "direction": direction, "messageType": message_type, "details": details}

    @staticmethod
    def traced(seq: int, event: str, details: dict, message_type: str = "") -> dict:
        return {
            "captureId": "capture-test",
            "processId": 123,
            "seq": seq,
            "tickMs": 100 + seq,
            "qpc": 1000 + seq,
            "qpcFrequency": 10_000_000,
            "threadId": 1,
            "layer": "websocket" if event.startswith("BZR_WS") else "trace",
            "event": event,
            "direction": "outbound" if event == "BZR_WS_TX" else "inbound",
            "socketId": 1,
            "socketGeneration": 1,
            "messageType": message_type,
            "details": details,
        }

    def valid_session(self, *, private: bool = False, dropped: int = 0) -> Path:
        return self.write_json({
            "captureId": "capture-test",
            "processId": 123,
            "privateForensic": private,
            "clockCalibration": {"qpc": 1000, "qpcFrequency": 10_000_000, "fileTimeUtc": 20_000_000_000},
            "droppedEvents": dropped,
            "writerShutdownClean": True,
        })

    def test_summary_and_drop(self) -> None:
        path = self.write_trace([
            {"seq": 1, "tickMs": 100, "event": "BZR_WS_TX", "direction": "outbound", "messageType": "DoEnterLounge", "details": {"messageJson": "{\"type\":\"DoEnterLounge\",\"content\":{}}"}},
            {"seq": 2, "tickMs": 110, "event": "TRACE_DROPPED_EVENTS", "details": {"droppedSinceLastReport": 3}},
        ])
        summary = summarize(load_trace(path))
        self.assertEqual(summary["records"], 2)
        self.assertEqual(summary["droppedEventsReported"], 3)
        self.assertEqual(summary["messageCounts"]["outbound DoEnterLounge"], 1)

    def test_relay_offset(self) -> None:
        path = self.write_trace([
            {"seq": 10, "socketId": 2, "event": "PRE_RELAY_ENCAP", "details": {"payloadHex": "aabbcc"}},
            {"seq": 11, "socketId": 2, "event": "UDP_WIRE_TX", "details": {"wireHex": "010203aabbcc99"}},
        ])
        rows = correlate_relay(load_trace(path))
        self.assertEqual(len(rows), 1)
        self.assertEqual(rows[0].inner_offset, 3)
        self.assertEqual(rows[0].prefix_len, 3)
        self.assertEqual(rows[0].suffix_len, 1)

    def test_comparator_normalizes_identity_and_key_order(self) -> None:
        official = self.write_trace([
            {"event": "BZR_WS_RX", "direction": "inbound", "messageType": "OnP2PRoute", "details": {"messageJson": "{\"type\":\"OnP2PRoute\",\"data\":{\"player\":\"A\",\"port\":1339}}"}},
        ])
        replacement = self.write_trace([
            {"event": "BZR_WS_RX", "direction": "inbound", "messageType": "OnP2PRoute", "details": {"messageJson": "{\"data\":{\"port\":1339,\"player\":\"B\"},\"type\":\"OnP2PRoute\"}"}},
        ])
        report = compare_sequences(semantic_messages(official), semantic_messages(replacement))
        self.assertTrue(report["pass"])

    def test_reason_code_mismatch_fails(self) -> None:
        official = self.write_trace([
            {"event": "BZR_WS_RX", "direction": "inbound", "messageType": "OnLobbyJoined", "details": {"reasonCode": 4, "success": False, "messageJson": "{\"type\":\"OnLobbyJoined\",\"data\":{\"reasonCode\":4}}"}},
        ])
        replacement = self.write_trace([
            {"event": "BZR_WS_RX", "direction": "inbound", "messageType": "OnLobbyJoined", "details": {"reasonCode": 5, "success": False, "messageJson": "{\"type\":\"OnLobbyJoined\",\"data\":{\"reasonCode\":5}}"}},
        ])
        report = compare_sequences(semantic_messages(official), semantic_messages(replacement))
        self.assertFalse(report["pass"])

    def test_async_broadcast_order_may_vary_within_same_causal_gap(self) -> None:
        official = self.write_trace([
            self.ws("DoEnterLounge", {}, direction="outbound"),
            self.ws("OnWANUpdated", {"userId": "A", "wanAddress": "1.1.1.1"}),
            self.ws("OnLobbyListChanged", {"lobbies": []}),
            self.ws("OnLobbyCreated", {"lobbyId": "L1"}),
        ])
        replacement = self.write_trace([
            self.ws("DoEnterLounge", {}, direction="outbound"),
            self.ws("OnLobbyListChanged", {"lobbies": []}),
            self.ws("OnWANUpdated", {"userId": "B", "wanAddress": "9.9.9.9"}),
            self.ws("OnLobbyCreated", {"lobbyId": "OTHER"}),
        ])
        report = compare_sequences(semantic_messages(official), semantic_messages(replacement))
        self.assertTrue(report["pass"])
        self.assertFalse(report["asyncMismatches"])

    def test_async_broadcast_cannot_cross_strict_boundary(self) -> None:
        official = self.write_trace([
            self.ws("DoEnterLounge", {}, direction="outbound"),
            self.ws("OnLobbyListChanged", {"lobbies": []}),
            self.ws("CreateGame", {"memberLimit": 4}, direction="outbound"),
        ])
        replacement = self.write_trace([
            self.ws("DoEnterLounge", {}, direction="outbound"),
            self.ws("CreateGame", {"memberLimit": 4}, direction="outbound"),
            self.ws("OnLobbyListChanged", {"lobbies": []}),
        ])
        report = compare_sequences(semantic_messages(official), semantic_messages(replacement))
        self.assertFalse(report["pass"])
        self.assertTrue(report["asyncMismatches"])

    def test_async_payload_difference_fails(self) -> None:
        official = self.write_trace([
            self.ws("DoEnterLounge", {}, direction="outbound"),
            self.ws("OnLobbyListChanged", {"lobbies": [{"memberLimit": 4}]}),
        ])
        replacement = self.write_trace([
            self.ws("DoEnterLounge", {}, direction="outbound"),
            self.ws("OnLobbyListChanged", {"lobbies": [{"memberLimit": 8}]}),
        ])
        report = compare_sequences(semantic_messages(official), semantic_messages(replacement))
        self.assertFalse(report["pass"])

    def test_two_pc_qpc_alignment(self) -> None:
        session_a = self.write_json({"clockCalibration": {"qpc": 1000, "qpcFrequency": 1000, "fileTimeUtc": 10_000_000_000}})
        session_b = self.write_json({"clockCalibration": {"qpc": 5000, "qpcFrequency": 2000, "fileTimeUtc": 10_000_000_000}})
        trace_a = self.write_trace([{ "qpc": 1010, "seq": 1, "layer": "websocket", "event": "BZR_WS_TX", "direction": "outbound", "messageType": "DoP2PRoute", "socketId": 1, "socketGeneration": 1 }])
        trace_b = self.write_trace([{ "qpc": 5024, "seq": 1, "layer": "websocket", "event": "BZR_WS_RX", "direction": "inbound", "messageType": "OnP2PRoute", "socketId": 2, "socketGeneration": 1 }])
        merged = merge_timelines([("A", session_a, trace_a), ("B", session_b, trace_b)])
        self.assertEqual([row["label"] for row in merged], ["A", "B"])
        self.assertAlmostEqual(merged[1]["relativeMs"], 2.0, places=3)

    def test_validator_accepts_redacted_sanitized_trace(self) -> None:
        message = {"type": "Authorization", "content": {
            "steamAppTicket": "<REDACTED>",
            "password": "<REDACTED>",
            "userId": "player_1",
            "name": "identity_1",
            "wanAddress": "endpoint_1",
            "lanAddresses": ["endpoint_2"],
        }}
        trace = self.write_trace([
            self.traced(1, "BZR_WS_TX", {"knownMessage": True, "messageJson": json.dumps(message)}, "Authorization")
        ])
        report = validate_trace(trace, self.valid_session())
        self.assertTrue(report["valid"], report["errors"])

    def test_validator_rejects_secret_leak(self) -> None:
        message = {"type": "Authorization", "content": {
            "steamAppTicket": "THIS-MUST-NOT-LEAK",
            "userId": "player_1",
            "name": "identity_1",
            "wanAddress": "endpoint_1",
            "lanAddresses": ["endpoint_2"],
        }}
        trace = self.write_trace([
            self.traced(1, "BZR_WS_TX", {"knownMessage": True, "messageJson": json.dumps(message)}, "Authorization")
        ])
        report = validate_trace(trace, self.valid_session())
        self.assertFalse(report["valid"])
        self.assertTrue(any("secret field" in error for error in report["errors"]))

    def test_validator_rejects_unsanitized_identity(self) -> None:
        message = {"type": "OnUserDataChanged", "data": {"userId": "raw-user", "name": "Raw Name", "wanAddress": "1.2.3.4"}}
        trace = self.write_trace([
            self.traced(1, "BZR_WS_RX", {"knownMessage": True, "messageJson": json.dumps(message)}, "OnUserDataChanged")
        ])
        report = validate_trace(trace, self.valid_session())
        self.assertFalse(report["valid"])
        self.assertTrue(any("not aliased" in error for error in report["errors"]))

    def test_validator_rejects_dropped_events_unless_allowed(self) -> None:
        trace = self.write_trace([
            self.traced(1, "TRACE_DROPPED_EVENTS", {"droppedSinceLastReport": 2})
        ])
        strict = validate_trace(trace, self.valid_session(dropped=2))
        permissive = validate_trace(trace, self.valid_session(dropped=2), allow_drops=True)
        self.assertFalse(strict["valid"])
        self.assertTrue(permissive["valid"])
        self.assertTrue(permissive["warnings"])


if __name__ == "__main__":
    unittest.main()
