"""Fail-closed retry-arm verification, including native writes and matrix attribution."""
import json
from pathlib import Path
import tempfile
import unittest

import p2p_retry_timing as timing
import p2p_netfix_score as scorer
import test_p2p_netfix_score as fixtures


def evidence(token):
    values = timing.parse_timers(token)
    ini = '[Network]\n' + ''.join(f'{key} = {value}\n' for (key, _, _), value in zip(timing.TIMERS, values))
    log = ''
    for (key, patch, stock), value in zip(timing.TIMERS, values):
        if value == stock:
            log += f'[SKIP] {patch} address=0x0075CA00 verified=yes payload=0\n'
        else:
            log += f'[P2PSEND] {key} requested {value} ms (stock {stock}); guarded write follows\n'
            log += f'[OK]   {patch} wrote 4 bytes to 0x0075CA00\n'
    return ini, log


class RetryEvidenceTests(unittest.TestCase):
    def test_stock_requires_verified_native_sites_even_without_overrides(self):
        _, log = evidence('1000/2500')
        self.assertEqual(timing.verify_client('[Network]\n', log, '1000/2500')['status'], 'verified')
        self.assertEqual(timing.verify_client('', log.replace('verified=yes', 'verified=no'), '1000/2500')['status'], 'mismatch')

    def test_each_nonstock_timer_requires_request_and_successful_write(self):
        ini, log = evidence('300/800')
        self.assertEqual(timing.verify_client(ini, log, '300/800')['status'], 'verified')
        for broken in (log.replace('wrote 4 bytes', 'wrote 0 bytes', 1), log.replace('requested 800', 'requested 900'), log+log):
            self.assertEqual(timing.verify_client(ini, broken, '300/800')['status'], 'mismatch')

    def test_mixed_stock_and_short_timer_is_supported(self):
        ini, log = evidence('1000/800')
        self.assertEqual(timing.verify_client(ini, log, '1000/800')['status'], 'verified')

    def test_wrong_or_ambiguous_config_cannot_inherit_successful_log(self):
        ini, log = evidence('300/800')
        for broken in (ini.replace('800', '900'), ini+'[Network]\n', ini+'ReliableFirstRetryMs=300\n', ini.replace('300', '300oops')):
            self.assertEqual(timing.verify_client(broken, log, '300/800')['status'], 'mismatch')

    def test_out_of_range_or_non_decimal_intent_rejected(self):
        for token in ('49/800', '300/10001', '+300/800', '300ms/800', '300/800/1', '999999999999999999999/800'):
            with self.assertRaises(ValueError):
                timing.parse_timers(token)

    def test_missing_client_evidence_is_mismatch(self):
        with tempfile.TemporaryDirectory() as run:
            for i in range(3):
                root = Path(run)/f'client{i}'; (root/'logs').mkdir(parents=True)
                ini, log = evidence('300/800')
                (root/'openshim.ini').write_text(ini)
                (root/'logs/openshim.log').write_text(log)
            result = timing.verify_run(run, '300/800', 4)
            self.assertEqual(result['status'], 'mismatch')
            self.assertEqual(result['clients']['c3']['status'], 'mismatch')


class RetryScoreTests(unittest.TestCase):
    setUp = fixtures.ScoreTests.setUp
    tearDown = fixtures.ScoreTests.tearDown
    make_run = fixtures.ScoreTests.make_run
    def test_wrong_timer_config_blocks_otherwise_clean_gameplay(self):
        self.make_run()
        ini, log = evidence('300/800')
        for i in range(4):
            root = Path(self.run)/f'client{i}'
            (root/'openshim.ini').write_text(ini if i != 3 else ini.replace('800', '900'))
            with (root/'logs/openshim.log').open('a') as output:
                output.write(log)
        result = scorer.score(self.run, 'on', gpu_query=lambda s,e: 0, timers='300/800')
        self.assertEqual(result['class'], 'ARM_MISMATCH')
        self.assertEqual(result['timerEvidence']['clients']['c3']['status'], 'mismatch')

    def test_verified_short_timer_score_is_attributed(self):
        self.make_run()
        ini, log = evidence('300/800')
        for i in range(4):
            root = Path(self.run)/f'client{i}'
            (root/'openshim.ini').write_text(ini)
            with (root/'logs/openshim.log').open('a') as output:
                output.write(log)
        result = scorer.score(self.run, 'on', gpu_query=lambda s,e: 0, timers='300/800')
        self.assertEqual(result['class'], 'STRICT_PASS')
        self.assertEqual(result['timers'], '300/800')


class RetryMatrixTests(unittest.TestCase):
    def test_wrong_timer_score_cannot_complete_plan(self):
        with tempfile.TemporaryDirectory() as matrix:
            root = Path(matrix); (root/'scores').mkdir()
            plan = {'index':1, 'run':'r', 'arm':'on', 'pass':1, 'case':'battle', 'impair':'loss=3', 'timers':'300/800'}
            (root/'matrix.json').write_text(json.dumps({'plan':[plan]}))
            score = dict(plan, timers='1000/2500', timerEvidence={'status':'verified'}, **{'class':'IMPAIRED_OK'})
            (root/'scores/01.json').write_text(json.dumps(score))
            result = scorer.aggregate(matrix)
            self.assertEqual(result['acceptance'], 'FAIL')
            self.assertTrue(any('verified timers 300/800' in p for p in result['problems']))


if __name__ == '__main__':
    unittest.main()
