#!/usr/bin/env python3
from __future__ import annotations

import json
import struct
import tempfile
import unittest
from pathlib import Path

from correlate_bzrnet_wire import HEADER, MAGIC, fnv1a64, load_buffer_records, summarize


class BzrNetWireCorrelationTests(unittest.TestCase):
    def make_buffer(self, payload: bytes, *, event_type: int = 6, tick_ms: int = 1000, port: int = 1339, payload_bytes: int = 64) -> tuple[Path, Path]:
        header = HEADER.pack(
            MAGIC,
            2,
            event_type,
            7,
            tick_ms,
            1,
            len(payload),
            len(payload),
            0,
            0,
            port,
            0,
            len(payload),
            0,
        )
        blob = header + payload + bytes(payload_bytes - len(payload))
        bin_handle = tempfile.NamedTemporaryFile("wb", delete=False, suffix=".bin")
        with bin_handle:
            bin_handle.write(blob)
        meta_handle = tempfile.NamedTemporaryFile("w", encoding="utf-8", delete=False, suffix=".txt")
        with meta_handle:
            meta_handle.write("format=buffer_log_v2\n")
            meta_handle.write(f"payload_bytes={payload_bytes}\n")
            meta_handle.write(f"record_stride={HEADER.size + payload_bytes}\n")
        return Path(bin_handle.name), Path(meta_handle.name)

    def test_exact_hash_match_and_relay_inner_offset(self) -> None:
        inner = bytes.fromhex("aabbccdd")
        wire = bytes.fromhex("01020304") + inner + bytes.fromhex("9988")
        bin_path, meta_path = self.make_buffer(wire)
        records = load_buffer_records(bin_path, meta_path)
        events = [
            {
                "seq": 10,
                "tickMs": 998,
                "event": "PRE_RELAY_ENCAP",
                "direction": "outbound",
                "details": {"innerPayloadHex": inner.hex()},
            },
            {
                "seq": 11,
                "tickMs": 1000,
                "event": "UDP_WIRE_TX",
                "direction": "outbound",
                "details": {
                    "port": 1339,
                    "payloadLength": len(wire),
                    "fnv1a64": fnv1a64(wire),
                    "payloadPrefixHex": wire.hex(),
                },
            },
        ]
        report = summarize(events, records)
        self.assertEqual(report["matched"], 1)
        self.assertEqual(report["exactHashMatches"], 1)
        self.assertEqual(len(report["relayBoundaryCorrelations"]), 1)
        boundary = report["relayBoundaryCorrelations"][0]
        self.assertTrue(boundary["innerVerbatim"])
        self.assertEqual(boundary["innerOffset"], 4)
        self.assertEqual(boundary["suffixLength"], 2)

    def test_prefix_match_when_binary_payload_is_truncated(self) -> None:
        full_length = 100
        captured = bytes(range(16))
        payload_bytes = 16
        header = HEADER.pack(MAGIC, 2, 6, 3, 2000, 2, full_length, full_length, 0, 0, 1339, 0, len(captured), 0)
        bin_handle = tempfile.NamedTemporaryFile("wb", delete=False, suffix=".bin")
        with bin_handle:
            bin_handle.write(header + captured)
        meta_handle = tempfile.NamedTemporaryFile("w", encoding="utf-8", delete=False, suffix=".txt")
        with meta_handle:
            meta_handle.write(f"payload_bytes={payload_bytes}\nrecord_stride={HEADER.size + payload_bytes}\n")
        records = load_buffer_records(Path(bin_handle.name), Path(meta_handle.name))
        events = [{
            "seq": 5,
            "tickMs": 2001,
            "event": "UDP_WIRE_TX",
            "direction": "outbound",
            "details": {"port": 1339, "payloadLength": full_length, "fnv1a64": "0000000000000000", "payloadPrefixHex": captured.hex()},
        }]
        report = summarize(events, records)
        self.assertEqual(report["matched"], 1)
        self.assertEqual(report["prefixMatches"], 1)
        self.assertEqual(report["exactHashMatches"], 0)


if __name__ == "__main__":
    unittest.main()
