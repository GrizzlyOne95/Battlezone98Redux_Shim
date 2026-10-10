"""Fail-closed retry-arm verification, including native writes and matrix attribution."""
import json
from pathlib import Path
import tempfile
import unittest

import p2p_retry_timing as timing
import p2p_netfix_score as scorer
import test_p2p_netfix_score as fixtures


def receive_log(early, armed=1, unavailable=0, totals=()):
    log = '[P2PRECV] Early unreliable receive armed: log=0x00 skip=0x00 return=0x00 deliver=0x00 window=4096\n' * armed
    log += '[P2PRECV] Receive signatures unavailable; stock strict receive kept\n' * unavailable
    for total in totals:
        log += f'[P2PRECV] Delivered early unreliable updates: total={total} (+1)\n'
    return log


def nak_log(nak, armed=1, unavailable=0, totals=()):
    log = '[P2PRECV] Early NAK receive armed: return=0x00 accept=0x00 window=4096\n' * armed
    log += '[P2PRECV] NAK signatures unavailable; stock NAK receive kept\n' * unavailable
    for total in totals:
        log += f'[P2PRECV] Accepted early NAKs: total={total} (+1)\n'
    return log


def evidence(token):
    values = timing.parse_timers(token)
    ini = '[Network]\n' + ''.join(f'{key} = {value}\n' for (key, _, _), value in zip(timing.TIMERS, values))
    ini += f'EarlyUnreliableAccept = {values[2]}\nEarlyNakAccept = {values[3]}\n'
    log = receive_log(values[2], armed=values[2]) + nak_log(values[3], armed=values[3])
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


class EarlyEvidenceTests(unittest.TestCase):
    def test_token_parse_and_round_trip(self):
        self.assertEqual(timing.parse_timers('1000/2500'), (1000, 2500, 0, 0))
        self.assertEqual(timing.parse_timers('300/800+early'), (300, 800, 1, 0))
        self.assertEqual(timing.token_of(*timing.parse_timers('300/800+early')), '300/800+early')
        for token in ('300/800+', '300/800+Early', '300/800+early+early', '+early', '49/800+early'):
            with self.assertRaises(ValueError):
                timing.parse_timers(token)

    def test_early_one_requires_exactly_one_armed_line(self):
        ini, log = evidence('1000/2500+early')
        log += receive_log(1, armed=0, totals=(3, 9, 5))
        result = timing.verify_client(ini, log, '1000/2500+early')
        self.assertEqual(result['status'], 'verified')
        self.assertEqual(result['timers'], '1000/2500+early')
        self.assertEqual(result['receive'], {'early':1, 'armedLines':1, 'signaturesUnavailableLines':0, 'deliveredTotal':9,
                                            'nak':0, 'nakArmedLines':0, 'nakSignaturesUnavailableLines':0, 'naksAcceptedTotal':0})

    def test_early_one_failures(self):
        ini, log = evidence('1000/2500+early')
        armed = receive_log(1)
        for broken_log in (log.replace(armed, ''), log + armed, log + receive_log(1, armed=0, unavailable=1)):
            self.assertEqual(timing.verify_client(ini, broken_log, '1000/2500+early')['status'], 'mismatch')
        for broken_ini in (ini.replace('EarlyUnreliableAccept = 1', 'EarlyUnreliableAccept = 0'),
                           ini.replace('EarlyUnreliableAccept = 1\n', ''), ini + 'EarlyUnreliableAccept = 1\n',
                           ini.replace('Accept = 1', 'Accept = 2')):
            self.assertEqual(timing.verify_client(broken_ini, log, '1000/2500+early')['status'], 'mismatch')

    def test_early_zero_forbids_armed_line_and_requires_ini_zero(self):
        ini, log = evidence('1000/2500')
        self.assertEqual(timing.verify_client(ini, log, '1000/2500')['receive']['early'], 0)
        self.assertEqual(timing.verify_client(ini, log + receive_log(1), '1000/2500')['status'], 'mismatch')
        self.assertEqual(timing.verify_client(ini.replace('Accept = 0', 'Accept = 1'), log, '1000/2500')['status'], 'mismatch')
        self.assertEqual(timing.verify_client('[Network]\n', log, '1000/2500')['status'], 'verified')

    def test_verify_run_reports_per_client_early_evidence(self):
        with tempfile.TemporaryDirectory() as run:
            for i in range(4):
                root = Path(run)/f'client{i}'; (root/'logs').mkdir(parents=True)
                ini, log = evidence('300/800+early')
                (root/'openshim.ini').write_text(ini)
                (root/'logs/openshim.log').write_text(log + receive_log(1, armed=0, totals=(i, 10 + i)))
            result = timing.verify_run(run, '300/800+early', 4)
            self.assertEqual((result['status'], result['early'], result['deliveredTotal']), ('verified', 1, 46))
            self.assertEqual(result['clients']['c2']['receive']['deliveredTotal'], 12)
            (Path(run)/'client1/logs/openshim.log').write_text(evidence('300/800+early')[1] + receive_log(1, armed=0, unavailable=1))
            self.assertEqual(timing.verify_run(run, '300/800+early', 4)['clients']['c1']['status'], 'mismatch')


class NakEvidenceTests(unittest.TestCase):
    def test_token_order_and_round_trip(self):
        self.assertEqual(timing.parse_timers('300/800+nak'), (300, 800, 0, 1))
        self.assertEqual(timing.parse_timers('300/800+early+nak'), (300, 800, 1, 1))
        self.assertEqual(timing.token_of(*timing.parse_timers('300/800+early+nak')), '300/800+early+nak')
        self.assertEqual(timing.token_of(*timing.parse_timers('300/800+nak')), '300/800+nak')
        for token in ('300/800+nak+early', '300/800+nak+nak', '300/800+early+early+nak', '300/800+NAK', '300/800+Nak',
                      '300/800+early+', '300/800+nakk', '+nak', '49/800+nak'):
            with self.assertRaises(ValueError):
                timing.parse_timers(token)

    def test_nak_armed_line_does_not_count_as_early_and_vice_versa(self):
        ini, log = evidence('300/800+nak')
        result = timing.verify_client(ini, log, '300/800+nak')
        self.assertEqual(result['status'], 'verified')
        self.assertEqual((result['receive']['armedLines'], result['receive']['nakArmedLines']), (0, 1))
        ini, log = evidence('300/800+early')
        self.assertEqual(timing.verify_client(ini, log, '300/800+early')['receive']['nakArmedLines'], 0)
        # only the other feature's armed line present: both directions must fail
        self.assertEqual(timing.verify_client(ini, log.replace(receive_log(1), nak_log(1)), '300/800+early')['status'], 'mismatch')
        ini, log = evidence('300/800+nak')
        self.assertEqual(timing.verify_client(ini, log.replace(nak_log(1), receive_log(1)), '300/800+nak')['status'], 'mismatch')

    def test_nak_failures(self):
        ini, log = evidence('300/800+early+nak')
        self.assertEqual(timing.verify_client(ini, log, '300/800+early+nak')['status'], 'verified')
        for broken in (log.replace(nak_log(1), ''), log + nak_log(1), log + nak_log(1, armed=0, unavailable=1)):
            self.assertEqual(timing.verify_client(ini, broken, '300/800+early+nak')['status'], 'mismatch')
        for broken in (ini.replace('EarlyNakAccept = 1', 'EarlyNakAccept = 0'), ini.replace('EarlyNakAccept = 1\n', ''),
                       ini + 'EarlyNakAccept = 1\n', ini.replace('NakAccept = 1', 'NakAccept = 2')):
            self.assertEqual(timing.verify_client(broken, log, '300/800+early+nak')['status'], 'mismatch')
        ini, log = evidence('300/800')
        self.assertEqual(timing.verify_client(ini, log + nak_log(1), '300/800')['status'], 'mismatch')
        self.assertEqual(timing.verify_client(ini.replace('NakAccept = 0', 'NakAccept = 1'), log, '300/800')['status'], 'mismatch')

    def test_verify_run_reports_nak_totals(self):
        with tempfile.TemporaryDirectory() as run:
            for i in range(4):
                root = Path(run)/f'client{i}'; (root/'logs').mkdir(parents=True)
                ini, log = evidence('300/800+nak')
                (root/'openshim.ini').write_text(ini)
                (root/'logs/openshim.log').write_text(log + nak_log(1, armed=0, totals=(i, 5 + i)))
            result = timing.verify_run(run, '300/800+nak', 4)
            self.assertEqual((result['status'], result['nak'], result['early'], result['naksAcceptedTotal']), ('verified', 1, 0, 26))
            self.assertEqual(result['clients']['c3']['receive']['naksAcceptedTotal'], 8)


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


class EarlyScoreTests(unittest.TestCase):
    setUp = fixtures.ScoreTests.setUp
    tearDown = fixtures.ScoreTests.tearDown
    make_run = fixtures.ScoreTests.make_run

    def test_early_arm_uses_early_rule_and_reports_both_models(self):
        # reliable 1 never arrives: updates stamped 2 are future-stamped under the stock rule
        s = [fixtures.packet(1, 2, 0, True, 1000), fixtures.packet(1, 2, 2, False, 1010), fixtures.packet(1, 2, 2, False, 1900)]
        self.make_run({(1, 2): s})
        results = {}
        for token in ('300/800', '300/800+early'):
            ini, log = evidence(token)
            for i in range(4):
                root = Path(self.run)/f'client{i}'
                (root/'openshim.ini').write_text(ini)
                (root/'logs/openshim.log').write_text('[OK]   P2P Reliable Send Backlog wrote 6 bytes to 0x0075C730\n' + log)
            results[token] = scorer.score(self.run, 'on', gpu_query=lambda s,e: 0, timers=token)
        stock, early = results['300/800'], results['300/800+early']
        self.assertEqual((stock['timers'], early['timers']), ('300/800', '300/800+early'))
        self.assertEqual((stock['totals']['futureStampedGaps'], early['totals']['futureStampedGaps']), (2, 0))
        self.assertEqual((stock['class'], early['class']), ('LOSS', 'STRICT_PASS'))
        for r in (stock, early):
            self.assertEqual(r['modeledStock']['unreliableRejected'], 2)
            self.assertEqual(r['modeledEarly']['unreliableRejected'], 0)
            self.assertEqual(r['modeledStock']['worstBlackoutMs'], 890)
            self.assertEqual(r['modeledEarly']['worstBlackoutMs'], 0)
            self.assertGreater(r['modeledStock']['blackoutSPerLinkMinute'], 0)
        self.assertEqual(early['timerEvidence']['early'], 1)

    def test_early_token_cannot_complete_plain_plan_and_arms_stay_distinct(self):
        with tempfile.TemporaryDirectory() as matrix:
            root = Path(matrix); (root/'scores').mkdir()
            plan = [{'index':i, 'run':f'r{i}', 'arm':'on', 'pass':1, 'case':'battle', 'impair':'loss=3', 'timers':t}
                    for i, t in ((1, '1000/2500'), (2, '1000/2500+early'))]
            (root/'matrix.json').write_text(json.dumps({'plan':plan}))
            for p in plan:  # the second score claims the plain token
                score = dict(p, timers='1000/2500', timerEvidence={'status':'verified'}, totals={}, **{'class':'IMPAIRED_OK'})
                (root/f"scores/{p['index']:02d}.json").write_text(json.dumps(score))
            result = scorer.aggregate(matrix)
            self.assertTrue(any('verified timers 1000/2500+early' in x for x in result['problems']))
            (root/'scores/02.json').write_text(json.dumps(dict(plan[1], timerEvidence={'status':'verified'}, totals={}, **{'class':'IMPAIRED_OK'})))
            result = scorer.aggregate(matrix)
            self.assertEqual([g['timers'] for g in result['groups']], ['1000/2500', '1000/2500+early'])
            self.assertEqual(result['problems'], [])


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
