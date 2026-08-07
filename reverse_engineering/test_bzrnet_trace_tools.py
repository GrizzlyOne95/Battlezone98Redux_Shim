#!/usr/bin/env python3
from __future__ import annotations

import json
import tempfile
import unittest
from pathlib import Path

from analyze_bzrnet_trace import correlate_relay, load_trace, summarize
from compare_bzrnet_traces import compare_sequences, semantic_messages


class BzrNetTraceToolTests(unittest.TestCase):
    def write_trace(self, rows: list[dict]) -> Path:
        handle = tempfile.NamedTemporaryFile("w", encoding="utf-8", delete=False, suffix=".jsonl")
        with handle:
            for row in rows:
                handle.write(json.dumps(row) + "\n")
        return Path(handle.name)

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


if __name__ == "__main__":
    unittest.main()
