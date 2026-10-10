"""Synthetic tests for p2p_netfix_score.py (no game launches).

  python -m unittest test_p2p_netfix_score     (from reverse_engineering)
"""
import json
import os
import shutil
import subprocess
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


    # ------------------------------------------------------ impairment --
    def impair(self, spec="loss=3,seed=7", matched=500, dropped=15):
        with open(os.path.join(self.run, "flow-inputs.json"), "w", encoding="utf-8") as f:
            json.dump({"impair": spec}, f)
        with open(os.path.join(self.run, "relay-impairment-final.json"), "w", encoding="utf-8") as f:
            json.dump({"ok": True, "impairment": {"active": True, "spec": spec, "matched": matched,
                                                  "dropped_loss": dropped}}, f)

    def test_blackout_runs_from_first_rejection_to_next_accepted_update(self):
        # Reliable 1 never reaches the receiver until 1600 ms: the updates
        # stamped 2 at 1010 and 1300 are rejected, the one at 1700 accepted.
        s = [packet(1, 2, 0, True, 1000), packet(1, 2, 2, False, 1010), packet(1, 2, 2, False, 1300),
             packet(1, 2, 1, True, 1600), packet(1, 2, 2, False, 1700)]
        self.make_run({(1, 2): s})
        r = self.score()
        link = r["links"]["c1->c2"]
        self.assertEqual((link["blackouts"], link["blackoutTotalMs"], link["blackoutMaxMs"]), (1, 690, 690))
        self.assertEqual(link["blackoutsOver500Ms"], 1)
        self.assertEqual(r["maxBlackoutMs"], 690)
        self.assertEqual(self.score()["links"]["c2->c1"]["blackouts"], 0)

    def test_open_blackout_is_closed_at_the_last_packet(self):
        s = [packet(1, 2, 0, True, 1000), packet(1, 2, 2, False, 1010), packet(1, 2, 2, False, 1210)]
        self.make_run({(1, 2): s})
        self.assertEqual(self.score()["links"]["c1->c2"]["blackoutTotalMs"], 200)

    def test_delivery_order_follows_impairment_delays(self):
        # At the relay, reliable 1 arrives before update 2, but it was held
        # back 300 ms, so the receiver gets the update first: a gap.
        r1 = packet(1, 2, 1, True, 1010) | {"impairment": {"drop": None, "delaysMs": [300.0], "reordered": True}}
        s = [packet(1, 2, 0, True, 1000), r1, packet(1, 2, 2, False, 1020), packet(1, 2, 2, False, 1400)]
        self.make_run({(1, 2): s})
        link = self.score()["links"]["c1->c2"]
        self.assertEqual(link["futureStampedGaps"], 1)
        self.assertEqual(link["blackoutTotalMs"], 380)

    def test_duplicated_copy_is_replayed_twice(self):
        r1 = packet(1, 2, 1, True, 1010) | {"impairment": {"drop": None, "delaysMs": [0.0, 0.0], "reordered": False}}
        s = [packet(1, 2, 0, True, 1000), r1, packet(1, 2, 2, False, 1020)]
        self.make_run({(1, 2): s})
        link = self.score()["links"]["c1->c2"]
        self.assertEqual((link["duplicateReliable"], link["futureStampedGaps"]), (1, 0))

    def test_relay_dropped_rows_are_not_delivered(self):
        lost = dict(packet(1, 2, 1, True, 1010), disposition="dropped_impair_loss")
        s = [packet(1, 2, 0, True, 1000), lost, packet(1, 2, 2, False, 1020), packet(1, 2, 1, True, 2010),
             packet(1, 2, 2, False, 2020)]
        self.make_run({(1, 2): s})
        link = self.score()["links"]["c1->c2"]
        self.assertEqual((link["futureStampedGaps"], link["blackoutTotalMs"]), (1, 1000))

    def test_impaired_run_with_gaps_is_impaired_ok(self):
        self.make_run({(1, 2): [packet(1, 2, 0, True, 1000), packet(1, 2, 2, False, 1010), packet(1, 2, 1, True, 1500)]})
        self.impair()
        r = self.score()
        self.assertEqual((r["class"], r["impair"]), ("IMPAIRED_OK", "loss=3,seed=7"))
        self.assertEqual(self.score("off")["class"], "ARM_MISMATCH")

    def test_impaired_run_without_relay_counters_is_incomplete(self):
        self.make_run()
        self.impair(matched=0)
        r = self.score()
        self.assertEqual(r["class"], "INCOMPLETE")
        os.remove(os.path.join(self.run, "relay-impairment-final.json"))
        self.assertEqual(self.score()["class"], "INCOMPLETE")

    def test_impaired_gameplay_failure_is_flow_fail(self):
        checks = GOOD_CHECKS + [{"check": "c1 sees every ping", "status": "fail"}]
        self.make_run(checks=checks)
        self.impair()
        self.assertEqual(self.score()["class"], "FLOW_FAIL")

    def test_aggregate_impaired(self):
        self.make_run()
        self.impair()
        base = self.score("on")
        plan = [{"index": 1, "arm": "on", "pass": 1, "case": "x", "run": "run1", "impair": "loss=3,seed=7"},
                {"index": 2, "arm": "off", "pass": 1, "case": "x", "run": "run2", "impair": "loss=3,seed=7"}]

        def scored(index, arm, cls):
            return dict(base, index=index, arm=arm, run=f"run{index}", **{"class": cls})
        cases = [
            ([scored(1, "on", "IMPAIRED_OK"), scored(2, "off", "IMPAIRED_OK")], "PASS"),
            # a stock run that becomes unplayable under impairment is evidence
            ([scored(1, "on", "IMPAIRED_OK"), scored(2, "off", "FLOW_FAIL")], "PASS"),
            ([scored(1, "on", "FLOW_FAIL"), scored(2, "off", "IMPAIRED_OK")], "FAIL"),
            ([scored(1, "on", "IMPAIRED_OK"), scored(2, "off", "CRASH")], "FAIL"),
            ([scored(1, "on", "IMPAIRED_OK")], "FAIL"),
        ]
        for scores, verdict in cases:
            matrix = tempfile.mkdtemp(prefix="netfix-matrix-test-")
            try:
                self.write_matrix(matrix, plan, scores)
                s = score.aggregate(matrix)
                self.assertEqual((s["kind"], s["verdict"]), ("impairment", verdict), [x["class"] for x in scores])
                self.assertEqual([g["arm"] for g in s["groups"]], ["on", "off"])
                self.assertEqual(s["groups"][0]["relayDropPct"], 3.0)
            finally:
                shutil.rmtree(matrix, ignore_errors=True)

def raw(seq, flags, ts, kind=0):
    return {"source": "127.0.0.1:50001", "target": "127.0.0.1:50002", "tsUnixMs": ts, "disposition": "forwarded",
            "transport": {"seqA": seq, "flagsByte": f"0x{flags:02X}", "kindNibble": kind}}


REL_FINAL, REL_PART, UNREL_FINAL, UNREL_PART = 0xC0, 0x80, 0x40, 0x00


class EarlyReplayTests(unittest.TestCase):
    """The receiver-side early rule (include/p2p_early_unreliable_policy.h)."""

    def run_link(self, packets, early=True):
        return score.analyse_link(score.delivered(packets), early)

    def test_future_stamped_final_unreliable_is_delivered_only_in_early_mode(self):
        s = [raw(0, REL_FINAL, 1000), raw(2, UNREL_FINAL, 1010), raw(2, UNREL_FINAL, 1300), raw(1, REL_FINAL, 1600)]
        stock, early = self.run_link(s, False), self.run_link(s, True)
        self.assertEqual((stock["futureStampedGaps"], stock["unreliableRejected"], stock["blackoutTotalMs"]), (2, 2, 590))
        self.assertEqual((early["futureStampedGaps"], early["unreliableRejected"], early["blackouts"]), (0, 0, 0))
        # both models are always reported, whatever mode drove the legacy fields
        for link in (stock, early):
            self.assertEqual(link["modeledStock"]["unreliableRejected"], 2)
            self.assertEqual(link["modeledEarly"]["unreliableRejected"], 0)
            self.assertEqual(link["modeledStock"]["blackoutTotalMs"], 590)
            self.assertEqual(link["modeledEarly"]["blackoutMaxMs"], 0)

    def test_expected_advances_only_on_accepted_reliable(self):
        # a delivered early update must not move expected: reliable 1 still lands
        s = [raw(0, REL_FINAL, 1000), raw(2, UNREL_FINAL, 1010), raw(1, REL_FINAL, 1020), raw(2, UNREL_FINAL, 1030)]
        link = self.run_link(s)
        self.assertEqual((link["futureStampedGaps"], link["duplicateReliable"], link["unreliableRejected"]), (0, 0, 0))

    def test_stale_unreliable_stays_rejected(self):
        s = [raw(5, REL_FINAL, 1000), raw(6, REL_FINAL, 1010), raw(5, UNREL_FINAL, 1020)]
        link = self.run_link(s)
        self.assertEqual((link["unreliableRejected"], link["futureStampedGaps"]), (1, 0))

    def test_future_reliable_is_still_rejected(self):
        s = [raw(0, REL_FINAL, 1000), raw(3, REL_FINAL, 1010), raw(1, UNREL_FINAL, 1020)]
        link = self.run_link(s)
        self.assertEqual(link["futureStampedGaps"], 1)
        self.assertEqual(link["unreliableRejected"], 0)

    def test_non_final_unreliable_is_rejected_and_opens_a_blackout(self):
        s = [raw(0, REL_FINAL, 1000), raw(2, UNREL_PART, 1010), raw(1, REL_FINAL, 1100), raw(2, UNREL_FINAL, 1200)]
        link = self.run_link(s)
        self.assertEqual((link["futureStampedGaps"], link["unreliableRejected"], link["blackoutTotalMs"]), (1, 1, 190))

    def test_partial_reliable_reassembly_blocks_until_final_fragment(self):
        s = [raw(0, REL_FINAL, 1000), raw(1, REL_PART, 1010), raw(3, UNREL_FINAL, 1020),
             raw(2, REL_FINAL, 1030), raw(4, UNREL_FINAL, 1040)]
        link = self.run_link(s)
        # stamp 3 vs expected 2 is blocked mid-reassembly; after the final fragment stamp 4 vs 3 is delivered
        self.assertEqual((link["futureStampedGaps"], link["unreliableRejected"]), (1, 1))
        self.assertEqual(link["blackoutTotalMs"], 20)

    def test_window_limit_and_u32_wrap(self):
        far = [raw(0, REL_FINAL, 1000), raw(1 + 4096, UNREL_FINAL, 1010), raw(1 + 4097, UNREL_FINAL, 1020)]
        link = self.run_link(far)
        self.assertEqual(link["unreliableRejected"], 1)  # +4096 delivered, +4097 rejected
        wrap = [raw(0xFFFFFFFE, REL_FINAL, 1000), raw(0xFFFFFFFF, REL_FINAL, 1010), raw(2, UNREL_FINAL, 1020),
                raw(0, REL_FINAL, 1030), raw(0xFFFFFFFF, UNREL_FINAL, 1040)]
        link = self.run_link(wrap)
        # stamp 2 is 3 ahead of expected 0 (wrapped): delivered; reliable 0 is accepted;
        # stamp 0xFFFFFFFF is then behind expected 1: stale, rejected
        self.assertEqual((link["futureStampedGaps"], link["unreliableRejected"], link["duplicateReliable"]), (0, 1, 0))


class ReliableFlowTests(unittest.TestCase):
    def flow(self, all_rows):
        fwd = [r for r in all_rows if r["disposition"] == "forwarded"]
        return score.reliable_flow(all_rows, score.delivered(fwd))

    def test_delay_is_first_relay_arrival_to_in_order_acceptance(self):
        lost = dict(raw(1, REL_FINAL, 1010), disposition="dropped_impair_loss", wireBytes=100)
        rows = [dict(raw(0, REL_FINAL, 1000), wireBytes=50), lost,
                dict(raw(2, REL_FINAL, 1020), wireBytes=70),        # arrives first, out of order
                dict(raw(1, REL_FINAL, 1500), wireBytes=100),       # retransmit of stamp 1
                dict(raw(2, REL_FINAL, 1520), wireBytes=70),        # retransmit of stamp 2
                dict(raw(3, UNREL_FINAL, 1530), wireBytes=30)]
        f = self.flow(rows)
        # stamp 0 accepted at once; stamp 1 at 1500 (first seen 1010); stamp 2 only after 1, at 1520 (first seen 1020)
        self.assertEqual(sorted(f["delays"]), [0, 490, 500])
        self.assertEqual((f["stamps"], f["undelivered"], f["retransmitCopies"], f["bytes"]), (3, 0, 2, 390))

    def test_never_accepted_stamp_is_undelivered(self):
        rows = [raw(0, REL_FINAL, 1000), dict(raw(1, REL_FINAL, 1010), disposition="dropped_impair_loss"), raw(2, REL_FINAL, 1020)]
        f = self.flow(rows)
        self.assertEqual((f["delays"], f["undelivered"]), ([0], 2))

    def test_nak_is_compared_with_the_links_stock_expected(self):
        rows = [raw(0, REL_FINAL, 1000), raw(2, REL_FINAL, 1010), raw(1, 0, 1020, kind=6),   # expected 1: equal
                raw(3, 0, 1030, kind=6), raw(0, 0, 1040, kind=6), raw(1, REL_FINAL, 1050),     # ahead; behind; reliable 1, then 2 follows
                raw(2, REL_FINAL, 1055), raw(2, 0, 1060, kind=6)]                              # expected is 3: behind
        self.assertEqual(self.flow(rows)["nak"], {"equal": 1, "ahead": 1, "behind": 2, "noExpectation": 0})

    def test_nak_before_any_data_has_no_expectation_and_u32_wrap(self):
        self.assertEqual(self.flow([raw(5, 0, 1000, kind=6)])["nak"]["noExpectation"], 1)
        rows = [raw(0xFFFFFFFF, REL_FINAL, 1000), raw(0, 0, 1010, kind=6), raw(0xFFFFFFFF, 0, 1020, kind=6)]
        self.assertEqual(self.flow(rows)["nak"], {"equal": 1, "ahead": 0, "behind": 1, "noExpectation": 0})

    def test_percentiles_and_score_summary(self):
        self.assertEqual([score.percentile(list(range(1, 101)), p) for p in (50, 95, 99, 100)], [50, 95, 99, 100])
        self.assertEqual(score.percentile([], 50), 0)
        t = ScoreTests("test_clean_fix_on_run_is_strict_pass")
        t.setUp()
        try:
            t.make_run({(1, 2): clean_stream(1, 2) + [dict(packet(1, 2, 0, True, 1100), wireBytes=40),
                                                      packet(1, 2, 9, False, 1110, kind=6)]})
            r = score.score(t.run, "on", gpu_query=lambda a, b: 0)
        finally:
            t.tearDown()
        d = r["reliableDelivery"]
        self.assertEqual((d["stamps"], d["count"], d["reliableRetransmitCopies"], d["reliableBytes"]), (12 * 5, 12 * 5, 1, 40))
        self.assertEqual(r["nakAcceptance"]["ahead"], 1)
        self.assertEqual(list(r["nakAcceptance"]["perLink"]), ["c1->c2"])


class GpuQueryTests(unittest.TestCase):
    """The event-log adapter fails closed: only an explicit count is evidence."""

    @staticmethod
    def runner(returncode=0, stdout="", raises=None):
        def run(script):
            if raises:
                raise raises
            # Errors must stop the query; nothing may silence them.
            assert "NoMatchingEventsFound" in script and "SilentlyContinue" not in script
            return subprocess.CompletedProcess(["powershell"], returncode, stdout, "")
        return run

    def test_explicit_zero_and_count(self):
        self.assertEqual(score.gpu_events(0, 1, self.runner(stdout="COUNT 0\r\n")), 0)
        self.assertEqual(score.gpu_events(0, 1, self.runner(stdout="COUNT 16\n")), 16)

    def test_query_error_is_unknown(self):
        out = "ERR UnauthorizedAccessException,Microsoft.PowerShell.Commands.GetWinEventCommand\n"
        self.assertIsNone(score.gpu_events(0, 1, self.runner(3, out)))

    def test_nonzero_returncode_is_unknown(self):
        self.assertIsNone(score.gpu_events(0, 1, self.runner(1, "COUNT 0\n")))

    def test_empty_or_garbage_output_is_unknown(self):
        for out in ("", "  \n", "0", "COUNT", "COUNT -1", "COUNT 3\nCOUNT 4", "Get-WinEvent : error"):
            self.assertIsNone(score.gpu_events(0, 1, self.runner(stdout=out)), out)

    def test_runner_failure_is_unknown(self):
        self.assertIsNone(score.gpu_events(0, 1, self.runner(raises=subprocess.TimeoutExpired("powershell", 90))))
        self.assertIsNone(score.gpu_events(0, 1, self.runner(raises=OSError("no powershell"))))

if __name__ == "__main__":
    unittest.main()
