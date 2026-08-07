#!/usr/bin/env python3
from __future__ import annotations

import unittest

from bzrnet_capture_coverage import evaluate


class BzrNetCoverageTests(unittest.TestCase):
    @staticmethod
    def ws(message_type: str, *, reason_code: int | None = None, success: bool | None = None) -> dict:
        details: dict[str, object] = {}
        if reason_code is not None:
            details["reasonCode"] = reason_code
        if success is not None:
            details["success"] = success
        return {"event": "BZR_WS_RX", "messageType": message_type, "details": details}

    def test_control_and_relay_coverage(self) -> None:
        events = [
            self.ws("Authorization"),
            self.ws("OnAuthorization", success=True),
            self.ws("DoP2PRoute"),
            self.ws("OnP2PRoute"),
            {"event": "UDP_WIRE_TX", "direction": "outbound", "details": {"port": 1339}},
            {"event": "UDP_WIRE_RX", "direction": "inbound", "details": {"port": 1339}},
        ]
        report = evaluate(events)
        by_name = {row["scenario"]: row["status"] for row in report["checks"]}
        self.assertEqual(by_name["Authorization + initial bootstrap"], "OBSERVED")
        self.assertEqual(by_name["Relay route allocation control"], "OBSERVED")
        self.assertEqual(by_name["UDP 1339 relay wire"], "OBSERVED")
        self.assertEqual(by_name["Relay engine boundary"], "NOT_SEEN")

    def test_partial_request_reply_is_not_complete(self) -> None:
        report = evaluate([self.ws("DoSendChat")])
        by_name = {row["scenario"]: row["status"] for row in report["checks"]}
        self.assertEqual(by_name["Chat"], "PARTIAL")

    def test_failure_reason_requires_actual_failure(self) -> None:
        success_report = evaluate([self.ws("OnLobbyJoined", reason_code=0, success=True)])
        failure_report = evaluate([self.ws("OnFailure", reason_code=5, success=False)])
        success_by_name = {row["scenario"]: row["status"] for row in success_report["checks"]}
        failure_by_name = {row["scenario"]: row["status"] for row in failure_report["checks"]}
        self.assertEqual(success_by_name["Observed join/failure reasonCode"], "NOT_SEEN")
        self.assertEqual(failure_by_name["Observed join/failure reasonCode"], "OBSERVED")


if __name__ == "__main__":
    unittest.main()
