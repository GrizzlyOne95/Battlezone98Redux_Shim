"""Fail-closed capture tests without Windows, Frida, or a private executable."""
import copy
import contextlib
import io
import json
from pathlib import Path
import sys
import tempfile
import types
import unittest
from unittest.mock import Mock, patch

sys.path.insert(0, str(Path(__file__).resolve().parent))
from capture_weapon_presentation_live import (  # noqa: E402
    bounded_float, catalog_rows, main, observe, trace_config, verify_sites,
)


class CaptureTests(unittest.TestCase):
    def setUp(self):
        catalog = json.loads((Path(__file__).resolve().parents[1] / "scripts/patches.json").read_text())
        self.rows = catalog_rows(catalog)
        self.base = 0x400000
        self.memory = bytearray(0x310000)
        self.static = {"image_base": hex(self.base), "sites": {}, "call_targets": {}, "steals": {}}
        for row in self.rows:
            name = row["name"].split("::")[1]
            site = int(row["fallback"], 0)
            self.static["sites"][name] = hex(site)
            start = site - row["offset"] - self.base
            pattern = bytes.fromhex(row["pattern"])
            self.memory[start:start + len(pattern)] = pattern
        for name, target in (("CannonShotCall", "OrdnanceFactory"),
                             ("WeaponClassPopCall", "PopScope"), ("CraftClassPopCall", "PopScope")):
            site = int(self.static["sites"][name], 0)
            self.static["call_targets"][name] = {"site": hex(site), "bytes": self.read(site, 5).hex(),
                                                 "target": self.static["sites"][target]}
        for name, size in (("WeaponCtor", 9), ("WeaponDtor", 6), ("SimulationPass", 6),
                           ("SetWeapon", 7), ("ModelPose", 6)):
            site = int(self.static["sites"][name], 0)
            self.static["steals"][name] = {"site": hex(site), "size": size, "bytes": self.read(site, size).hex()}

    def read(self, address, size):
        return bytes(self.memory[address - self.base:address - self.base + size])

    def verify(self, reader=None, sections=None):
        return verify_sites(self.static, self.rows, sections or [(self.base, bytes(self.memory))],
                            reader or self.read, self.base)

    def test_exact_capture_and_trace_guard_coverage(self):
        verified = self.verify()
        self.assertEqual((len(verified["sites"]), len(verified["calls"]), len(verified["steals"])), (14, 3, 5))
        config = trace_config(verified, 42, r"C:\GOG\battlezone98redux.exe", 4096, ["barrel"])
        self.assertEqual(len(config["guards"]), 14)
        self.assertNotIn("activation_qualified", verified)  # bytes alone grant no activation

    def test_patched_prologue_rejected(self):
        site = int(self.static["sites"]["WeaponCtor"], 0)
        self.memory[site - self.base] = 0xe9
        with self.assertRaisesRegex(ValueError, "signature missing"):
            self.verify()

    def test_duplicate_runtime_signature_rejected(self):
        pattern = bytes.fromhex(self.rows[0]["pattern"])
        self.memory[0x100:0x100 + len(pattern)] = pattern
        with self.assertRaisesRegex(ValueError, "duplicated"):
            self.verify()

    def test_signature_moved_rejected(self):
        row = self.rows[0]
        start = int(row["fallback"], 0) - self.base
        pattern = bytes.fromhex(row["pattern"])
        self.memory[start:start + len(pattern)] = b"\0" * len(pattern)
        self.memory[0x100:0x100 + len(pattern)] = pattern
        with self.assertRaisesRegex(ValueError, "moved"):
            self.verify()

    def test_partial_or_racing_read_rejected(self):
        for reader in (lambda a, s: self.read(a, s)[:-1], lambda a, s: b"\0" * s):
            with self.subTest(reader=reader), self.assertRaisesRegex(ValueError, "changed during capture"):
                self.verify(reader=reader)

    def test_call_target_rechecked_even_after_signature_scan(self):
        site = int(self.static["sites"]["CannonShotCall"], 0)
        def racing_reader(address, size):
            if address == site and size == 5:
                return b"\xe8\0\0\0\0"
            return self.read(address, size)
        with self.assertRaisesRegex(ValueError, "call target disagreement"):
            self.verify(reader=racing_reader)

    def test_stolen_instructions_rechecked(self):
        site = int(self.static["sites"]["WeaponCtor"], 0)
        def racing_reader(address, size):
            if address == site and size == 9:
                return self.read(address, size)[:-1] + b"\xff"
            return self.read(address, size)
        with self.assertRaisesRegex(ValueError, "stolen instruction"):
            self.verify(reader=racing_reader)

    def test_catalog_drift_missing_and_duplicates_rejected(self):
        variants = [self.rows[:-1], self.rows + [self.rows[0]]]
        changed = copy.deepcopy(self.rows)
        changed[0]["require_unique"] = False
        variants.append(changed)
        for rows in variants:
            with self.subTest(rows=len(rows)), self.assertRaises(ValueError):
                catalog_rows({"resolves": rows})
        changed = copy.deepcopy(self.rows)
        changed[0]["fallback"] = "0x00611301"
        with self.assertRaisesRegex(ValueError, "address disagreement"):
            verify_sites(self.static, changed, [(self.base, bytes(self.memory))], self.read, self.base)

    def test_wrong_base_and_incomplete_static_proof_rejected(self):
        with self.assertRaisesRegex(ValueError, "image base"):
            verify_sites(self.static, self.rows, [], self.read, 0x500000)
        self.static["call_targets"].pop("CannonShotCall")
        with self.assertRaisesRegex(ValueError, "Incomplete call/steal"):
            self.verify()

    def test_trace_limits_and_ids_rejected_before_attach(self):
        for limit, ids in ((0, []), (20001, []), (1, ["too-long-name"]), (1, ["x\n"]), (1, [""]), (1, ["a"] * 17)):
            with self.subTest(limit=limit, ids=ids), self.assertRaises(ValueError):
                trace_config({"sites": {}}, 42, "", limit, ids)

    def test_nonfinite_or_unbounded_capture_duration_rejected(self):
        import argparse
        for value in ("nan", "inf", "-1", "301"):
            with self.subTest(value=value), self.assertRaises(argparse.ArgumentTypeError):
                bounded_float(0, 300)(value)


class TraceHostTests(unittest.TestCase):
    def run_observer(self, directory, emitted=1, fail_unload=False, messages=None):
        script = Mock()
        script.exports_sync.stop.return_value = {"complete": True, "events_emitted": emitted}
        if fail_unload:
            script.unload.side_effect = RuntimeError("unload failure")
        def subscribe(_event, callback):
            script.exports_sync.start.side_effect = lambda _config: [callback(m, None) for m in (
                messages or [{"type": "send", "payload": {"type": "events", "events": [{"kind": "fixture"}]}}])]
        script.on.side_effect = subscribe
        session = Mock()
        session.create_script.return_value = script
        frida = types.SimpleNamespace(attach=Mock(return_value=session), __version__="fixture")
        with patch.dict(sys.modules, {"frida": frida}):
            result = observe(42, {"max_events": 1}, 0, Path(directory) / "trace.jsonl", lambda: None)
        return result, session, script

    def test_delivery_complete_and_cleanup(self):
        with tempfile.TemporaryDirectory() as directory:
            result, session, script = self.run_observer(directory)
            self.assertTrue(result["complete"])
            self.assertFalse(result["activation_qualified"])
            script.unload.assert_called_once()
            session.detach.assert_called_once()

    def test_delivery_disagreement_fails_closed(self):
        with tempfile.TemporaryDirectory() as directory:
            result, _, _ = self.run_observer(directory, emitted=2)
            self.assertFalse(result["complete"])
            self.assertEqual(result["error_count"], 1)

    def test_error_reports_are_bounded(self):
        with tempfile.TemporaryDirectory() as directory:
            result, _, _ = self.run_observer(directory, emitted=0,
                messages=[{"type": "error", "description": "fixture"}] * 100)
            self.assertFalse(result["complete"])
            self.assertEqual(result["error_count"], 100)
            self.assertEqual(len(result["errors"]), 32)

    def test_unload_failure_still_detaches(self):
        with tempfile.TemporaryDirectory() as directory:
            # Keep the mock outside the call to assert cleanup even when it raises.
            session = Mock()
            script = session.create_script.return_value
            script.exports_sync.stop.return_value = {"complete": True, "events_emitted": 0}
            script.unload.side_effect = RuntimeError("fixture")
            frida = types.SimpleNamespace(attach=Mock(return_value=session), __version__="fixture")
            with patch.dict(sys.modules, {"frida": frida}), self.assertRaises(RuntimeError):
                observe(42, {"max_events": 1}, 0, Path(directory) / "trace.jsonl", lambda: None)
            session.detach.assert_called_once()

    def test_existing_trace_refuses_before_attach(self):
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "trace.jsonl"
            output.write_text("prior evidence")
            frida = types.SimpleNamespace(attach=Mock())
            with patch.dict(sys.modules, {"frida": frida}), self.assertRaises(FileExistsError):
                observe(42, {"max_events": 1}, 0, output, lambda: None)
            frida.attach.assert_not_called()
            self.assertEqual(output.read_text(), "prior evidence")

    def test_interruption_preserves_rejected_report(self):
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / "report.json"
            with patch.object(sys, "argv", ["collector", "--pid", "42", "--output", str(output)]), \
                    patch("capture_weapon_presentation_live.capture", side_effect=KeyboardInterrupt), \
                    contextlib.redirect_stdout(io.StringIO()):
                self.assertEqual(main(), 130)
            report = json.loads(output.read_text())
            self.assertFalse(report["activation_qualified"])
            self.assertFalse(report["byte_verification_passed"])
            self.assertIn("incomplete", report["error"])


if __name__ == "__main__":
    unittest.main()
