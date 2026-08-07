#!/usr/bin/env python3
from __future__ import annotations

import json
import tempfile
import unittest
from pathlib import Path

from bzrnet_session_report import build_report


class BzrNetSessionReportTests(unittest.TestCase):
    def test_valid_session_report(self) -> None:
        root = Path(tempfile.mkdtemp())
        session = {
            "captureId": "cap",
            "processId": 77,
            "privateForensic": False,
            "clockCalibration": {"qpc": 100, "qpcFrequency": 10_000_000, "fileTimeUtc": 20_000_000_000},
            "droppedEvents": 0,
            "writerShutdownClean": True,
        }
        (root / "bzrnet_session.json").write_text(json.dumps(session), encoding="utf-8")
        message = {"type": "Authorization", "content": {
            "steamAppTicket": "<REDACTED>",
            "userId": "player_1",
            "name": "identity_1",
            "wanAddress": "endpoint_1",
            "lanAddresses": ["endpoint_2"],
        }}
        event = {
            "captureId": "cap",
            "processId": 77,
            "seq": 1,
            "tickMs": 1000,
            "qpc": 101,
            "qpcFrequency": 10_000_000,
            "threadId": 1,
            "layer": "websocket",
            "event": "BZR_WS_TX",
            "direction": "outbound",
            "socketId": 1,
            "socketGeneration": 1,
            "messageType": "Authorization",
            "details": {"knownMessage": True, "messageJson": json.dumps(message)},
        }
        (root / "bzrnet_trace.jsonl").write_text(json.dumps(event) + "\n", encoding="utf-8")
        identity = {"formatVersion": 1, "platform": "Steam", "gameExecutable": {"sha256": "abc"}, "openShim": {"sha256": "def"}}
        (root / "bzrnet_capture_identity.json").write_text(json.dumps(identity), encoding="utf-8")

        report = build_report(root)
        self.assertTrue(report["validEvidence"])
        self.assertEqual(report["captureIdentity"]["platform"], "Steam")
        self.assertEqual(report["traceSummary"]["records"], 1)


if __name__ == "__main__":
    unittest.main()
