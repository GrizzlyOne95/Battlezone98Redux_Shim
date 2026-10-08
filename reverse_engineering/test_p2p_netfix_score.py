"""Synthetic tests for p2p_netfix_score.py (no game launches).

  python -m unittest test_p2p_netfix_score     (from reverse_engineering)
"""
import json
import os
import shutil
import tempfile
import unittest

import p2p_netfix_score as score

PORTS = {0: 50000, 1: 50001, 2: 50002, 3: 50003}
GOOD_CHECKS = [
    {"check": "c0 no Lua or engine script errors", "status": "pass"},
    {"check": "all clients muted with complete maximum network captures", "status": "pass"},
    {"check": "native peers have no sustained post-loading sequence rejection", "status": "pass"},
]


def packet(src, dst, seq, reliable, ts, kind=0):
    return {"source": f"127.0.0.1:{PORTS[src]}", "target": f"127.0.0.1:{PORTS[dst]}", "tsUnixMs": ts,
            "disposition": "forwarded",
            "transport": {"seqA": seq, "flagsByte": "0xC0" if reliable else "0x40", "kindNibble": kind}}


def clean_stream(src, dst, t0=1000):
    """Reliable 0..4 each sent at once, an unreliable update after each."""
    out, ts = [], t0
    for s in range(5):
        out.append(packet(src, dst, s, True, ts)); ts += 10
        out.append(packet(src, dst, s + 1, False, ts)); ts += 10
    return out


class ScoreTests(unittest.TestCase):
    def setUp(self):
        self.run = tempfile.mkdtemp(prefix="netfix-score-test-")

    def tearDown(self):
        shutil.rmtree(self.run, ignore_errors=True)

    def make_run(self, streams=None, fix="on", checks=None, health="pass", trace_extra="", clients=4):
        streams = streams or {}
        rows = []
        for a in range(clients):
            for b in range(clients):
                if a != b:
                    rows += streams.get((a, b), clean_stream(a, b))
        rows.sort(key=lambda r: r["tsUnixMs"])
        with open(os.path.join(self.run, "relay-trace.jsonl"), "w", encoding="utf-8") as f:
            f.write("".join(json.dumps(r) + "\n" for r in rows) + trace_extra)
        with open(os.path.join(self.run, "flow-summary.json"), "w", encoding="utf-8") as f:
            json.dump({"verdict": "PASS" if all(c["status"] == "pass" for c in (checks or GOOD_CHECKS)) else "FAIL",
                       "steps": [{"step": "join", "status": "pass"}], "checks": checks or GOOD_CHECKS}, f)
        with open(os.path.join(self.run, "native-network-health.json"), "w", encoding="utf-8") as f:
            json.dump({"status": health, "clients": [{"client": c, "missionObservedSeconds": 90} for c in range(clients)]}, f)
        for c in range(clients):
            logs = os.path.join(self.run, f"client{c}", "logs")
            os.makedirs(logs)
            with open(os.path.join(logs, "BZLogger.txt"), "w", encoding="utf-8") as f:
                f.write(f"BZRNet P2P Socket Opened With 127.0.0.1 port {PORTS[c]}\n")
            line = ("[OK]   P2P Reliable Send Backlog wrote 6 bytes to 0x0075C730\n" if fix == "on" else
                    "[SKIP] P2P Reliable Send Backlog address=0x0075C730 verified=yes payload=0\n" if fix == "off" else "")
            with open(os.path.join(logs, "openshim.log"), "w", encoding="utf-8") as f:
                f.write(line)
            with open(os.path.join(logs, "openshim_crash.log"), "w", encoding="utf-8") as f:
                f.write("[FIRST-CHANCE] benign\n")

    def score(self, arm="on", gpu=0):
        return score.score(self.run, arm, gpu_query=lambda s, e: gpu)

    def test_clean_fix_on_run_is_strict_pass(self):
        self.make_run()
        r = self.score()
        self.assertEqual(r["class"], "STRICT_PASS")
        self.assertEqual(r["totals"]["futureStampedGaps"], 0)
        self.assertEqual(len(r["links"]), 12)

    def test_gap_and_duplicate_split(self):
        # Reliable 1 is held: the update stamped 2 arrives first and is a gap;
        # reliable 0 is then retransmitted after delivery, a duplicate.
        s = [packet(1, 2, 0, True, 1000), packet(1, 2, 2, False, 1010), packet(1, 2, 1, True, 1500),
             packet(1, 2, 0, True, 1600), packet(1, 2, 2, False, 1700)]
        self.make_run({(1, 2): s})
        link = self.score()["links"]["c1->c2"]
        self.assertEqual(link["futureStampedGaps"], 1)
        self.assertEqual(link["unreliableRejected"], 1)
        self.assertEqual(link["duplicateReliable"], 1)
        self.assertEqual(link["reliableHeld"], 1)
        self.assertEqual(link["holdMaxMs"], 490)

    def test_fix_on_with_gap_is_loss(self):
        self.make_run({(1, 2): [packet(1, 2, 0, True, 1000), packet(1, 2, 2, False, 1010), packet(1, 2, 1, True, 1500)]})
        self.assertEqual(self.score()["class"], "LOSS")

    def test_stock_health_failure_alone_is_evidence_not_flow_fail(self):
        checks = [dict(c) for c in GOOD_CHECKS]
        checks[2]["status"] = "fail"
        self.make_run({(1, 2): [packet(1, 2, 0, True, 1000), packet(1, 2, 2, False, 1010), packet(1, 2, 1, True, 1500)]},
                      fix="off", checks=checks, health="fail")
        r = self.score("off")
        self.assertEqual(r["flowVerdict"], "FAIL")
        self.assertEqual(r["gameplayVerdict"], "PASS")
        self.assertEqual(r["class"], "REPRODUCED")

    def test_real_gameplay_check_failure_is_flow_fail(self):
        checks = [dict(c) for c in GOOD_CHECKS]
        checks[0]["status"] = "fail"
        self.make_run(fix="off", checks=checks)
        self.assertEqual(self.score("off")["class"], "FLOW_FAIL")

    def test_capture_check_failure_is_incomplete(self):
        checks = [dict(c) for c in GOOD_CHECKS]
        checks[1]["status"] = "fail"
        self.make_run(checks=checks)
        self.assertEqual(self.score()["class"], "INCOMPLETE")

    def test_absent_capture_check_is_incomplete(self):
        self.make_run(checks=[GOOD_CHECKS[0], GOOD_CHECKS[2]])
        self.assertEqual(self.score()["class"], "INCOMPLETE")

    def test_any_failing_capture_check_is_incomplete(self):
        fail = dict(GOOD_CHECKS[1], status="fail")
        self.make_run(checks=GOOD_CHECKS + [fail])
        self.assertEqual(self.score()["class"], "INCOMPLETE")

    def test_malformed_trace_line_is_incomplete_not_zero_loss(self):
        self.make_run(trace_extra='{"source": "127.0.0.1:50001", "trunc\n')
        r = self.score()
        self.assertEqual(r["class"], "INCOMPLETE")
        self.assertEqual(r["malformedTraceLines"], 1)

    def test_missing_link_is_incomplete(self):
        self.make_run({(3, 2): []})
        self.assertEqual(self.score()["class"], "INCOMPLETE")

    def test_unknown_gpu_evidence_is_incomplete(self):
        self.make_run()
        self.assertEqual(self.score(gpu=None)["class"], "INCOMPLETE")

    def test_gpu_event_is_gpu(self):
        self.make_run()
        self.assertEqual(self.score(gpu=3)["class"], "GPU")

    def test_crash_record_is_crash(self):
        self.make_run()
        with open(os.path.join(self.run, "client2", "logs", "openshim_crash.log"), "a", encoding="utf-8") as f:
            f.write("[CRASH] 2026-10-07 code=0xC0000005\n")
        self.assertEqual(self.score()["class"], "CRASH")

    def test_arm_mismatch_and_missing_arm(self):
        self.make_run(fix="off")
        self.assertEqual(self.score("on")["class"], "ARM_MISMATCH")
        self.assertEqual(self.score(None)["class"], "ARM_MISMATCH")

    def test_unknown_patch_state_is_arm_mismatch(self):
        self.make_run(fix="unknown")
        self.assertEqual(self.score("on")["class"], "ARM_MISMATCH")

    def test_stock_without_gaps_is_not_reproduced(self):
        self.make_run(fix="off")
        self.assertEqual(self.score("off")["class"], "NOT_REPRODUCED")

    def write_matrix(self, matrix, plan, scores):
        os.makedirs(os.path.join(matrix, "scores"), exist_ok=True)
        with open(os.path.join(matrix, "matrix.json"), "w", encoding="utf-8") as f:
            json.dump({"plan": plan}, f)
        for n, r in enumerate(scores):
            with open(os.path.join(matrix, "scores", f"{n:02d}.json"), "w", encoding="utf-8") as f:
                json.dump(r, f)

    def scored(self, index, arm, cls, gaps=0):
        base = self.score("on")
        return dict(base, index=index, arm=arm, run=f"run{index}", totals=dict(base["totals"], futureStampedGaps=gaps),
                    **{"class": cls})

    def test_aggregate_verdicts(self):
        self.make_run()
        plan = [{"index": 1, "arm": "on", "pass": 1, "case": "x", "run": "run1"},
                {"index": 2, "arm": "off", "pass": 1, "case": "x", "run": "run2"}]
        cases = [
            ([self.scored(1, "on", "STRICT_PASS"), self.scored(2, "off", "REPRODUCED", 5)], "PASS", "PASS", "REPRODUCED"),
            ([self.scored(1, "on", "STRICT_PASS"), self.scored(2, "off", "NOT_REPRODUCED")], "FAIL", "PASS", "NOT_REPRODUCED"),
            ([self.scored(1, "on", "LOSS", 3), self.scored(2, "off", "REPRODUCED", 5)], "FAIL", "FAIL", "REPRODUCED"),
            # partial or resumed matrix: a planned run is missing
            ([self.scored(1, "on", "STRICT_PASS")], "FAIL", "FAIL", "NOT_REPRODUCED"),
            # duplicate score for one planned run
            ([self.scored(1, "on", "STRICT_PASS"), self.scored(1, "on", "STRICT_PASS"),
              self.scored(2, "off", "REPRODUCED", 5)], "FAIL", "FAIL", "REPRODUCED"),
            # an extra unindexed score file
            ([self.scored(1, "on", "STRICT_PASS"), self.scored(2, "off", "REPRODUCED", 5),
              dict(self.scored(9, "on", "STRICT_PASS"), index=None)], "FAIL", "FAIL", "REPRODUCED"),
            # stock control infrastructure failure
            ([self.scored(1, "on", "STRICT_PASS"), self.scored(2, "off", "CRASH")], "FAIL", "FAIL", "NOT_REPRODUCED"),
        ]
        for scores, verdict, acceptance, comparison in cases:
            matrix = tempfile.mkdtemp(prefix="netfix-matrix-test-")
            try:
                self.write_matrix(matrix, plan, scores)
                s = score.aggregate(matrix)
                self.assertEqual((s["verdict"], s["acceptance"], s["comparison"]), (verdict, acceptance, comparison),
                                 [x["class"] for x in scores])
            finally:
                shutil.rmtree(matrix, ignore_errors=True)

    def test_aggregate_without_plan_never_passes(self):
        self.make_run()
        matrix = tempfile.mkdtemp(prefix="netfix-matrix-test-")
        try:
            os.makedirs(os.path.join(matrix, "scores"))
            with open(os.path.join(matrix, "scores", "00.json"), "w", encoding="utf-8") as f:
                json.dump(self.scored(1, "on", "STRICT_PASS"), f)
            self.assertEqual(score.aggregate(matrix)["acceptance"], "FAIL")
        finally:
            shutil.rmtree(matrix, ignore_errors=True)

if __name__ == "__main__":
    unittest.main()
