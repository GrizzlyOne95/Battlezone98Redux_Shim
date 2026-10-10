"""Verify intended retry timers and early-receive arm against archived INIs and native logs."""
from pathlib import Path
import re

TIMERS = (('ReliableFirstRetryMs', 'P2P Reliable First Retry', 1000),
          ('ReliableRetryIntervalMs', 'P2P Reliable Retry Interval', 2500))

ARMED = r'\[P2PRECV\] Early unreliable receive armed:'
UNAVAILABLE = r'\[P2PRECV\] Receive signatures unavailable; stock strict receive kept'
DELIVERED = r'\[P2PRECV\] Delivered early unreliable updates: total=(\d+)'
NAK_ARMED = r'\[P2PRECV\] Early NAK receive armed:'
NAK_UNAVAILABLE = r'\[P2PRECV\] NAK signatures unavailable; stock NAK receive kept'
NAK_ACCEPTED = r'\[P2PRECV\] Accepted early NAKs: total=(\d+)'
NAK_HELD = r'\[P2PRECV\] Held repeat NAKs: total=(\d+)'

def parse_timers(token):
    """(first ms, interval ms, early 0|1, nak 0|1) from first/interval[+early][+nak]."""
    match = re.fullmatch(r'([0-9]+)/([0-9]+)(\+early)?(\+nak)?', token)
    if not match:
        raise ValueError('timers must be decimal first/interval milliseconds, optionally followed by +early then +nak')
    values = (int(match[1]), int(match[2]))
    if not all(50 <= value <= 10000 for value in values):
        raise ValueError('retry timers must be 50..10000 ms')
    return values + (int(bool(match[3])), int(bool(match[4])))

def token_of(first, interval, early=0, nak=0):
    return f'{first}/{interval}' + ('+early' if early else '') + ('+nak' if nak else '')

def configured_timers(text):
    """(first, interval, early, nak) from the single [Network] section; stock defaults, early/nak 0."""
    section = ''; values = {}; sections = 0
    for line in text.splitlines():
        match = re.fullmatch(r'\s*\[([^]]+)\]\s*(?:;.*)?', line)
        if match:
            section = match[1].strip().lower()
            sections += section == 'network'
        elif section == 'network':
            match = re.fullmatch(r'\s*(ReliableFirstRetryMs|ReliableRetryIntervalMs|EarlyUnreliableAccept|EarlyNakAccept)\s*=\s*([^;]*)(?:;.*)?', line, re.I)
            if match:
                key = match[1].lower(); value = match[2].strip()
                if key in ('earlyunreliableaccept', 'earlynakaccept'):
                    valid = value in ('0', '1')
                else:
                    valid = re.fullmatch('[0-9]+', value) and 50 <= int(value) <= 10000
                if key in values or not valid:
                    raise ValueError('ambiguous or invalid timer or early config')
                values[key] = int(value)
    if sections > 1:
        raise ValueError('repeated Network sections')
    return tuple(values.get(key.lower(), stock) for key, _, stock in TIMERS) + (values.get('earlyunreliableaccept', 0), values.get('earlynakaccept', 0))

def receive_evidence(log, early, nak):
    armed = len(re.findall(ARMED, log)); unavailable = len(re.findall(UNAVAILABLE, log))
    totals = [int(total) for total in re.findall(DELIVERED, log)]
    nak_armed = len(re.findall(NAK_ARMED, log)); nak_unavailable = len(re.findall(NAK_UNAVAILABLE, log))
    nak_totals = [int(total) for total in re.findall(NAK_ACCEPTED, log)]
    held = [int(total) for total in re.findall(NAK_HELD, log)]
    ok = armed == 1 and not unavailable if early else not armed
    ok = ok and (nak_armed == 1 and not nak_unavailable if nak else not nak_armed)
    return ok, {'early':early, 'armedLines':armed, 'signaturesUnavailableLines':unavailable,
                'deliveredTotal':max(totals, default=0),
                'nak':nak, 'nakArmedLines':nak_armed, 'nakSignaturesUnavailableLines':nak_unavailable,
                'naksAcceptedTotal':max(nak_totals, default=0), 'naksHeldTotal':max(held, default=0)}

def verify_client(ini, log, intended):
    values = parse_timers(intended)
    early, nak = values[2], values[3]
    try:
        configured = configured_timers(ini)
    except ValueError as error:
        return {'status':'mismatch', 'reason':str(error)}
    if configured != values:
        return {'status':'mismatch', 'reason':f'config {configured} differs from intended {values}'}
    evidence = []
    for (key, patch, stock), value in zip(TIMERS, values):
        requests = re.findall(r'\[P2PSEND\] ' + key + r' requested (\d+) ms \(stock \d+\); guarded write follows', log)
        written = re.findall(r'\[OK\]\s+' + patch + r' wrote 4 bytes to 0x[0-9A-Fa-f]+', log)
        skipped = re.findall(r'\[SKIP\] ' + patch + r' address=0x[0-9A-Fa-f]+ verified=yes payload=0', log)
        if value == stock:
            ok = len(skipped) == 1 and not requests and not written
        else:
            ok = requests == [str(value)] and len(written) == 1 and not skipped
        if not ok:
            return {'status':'mismatch', 'reason':f'{key} lacks unique matching native apply evidence'}
        evidence.append({'key':key, 'ms':value, 'evidence':'verified stock skip' if value==stock else 'requested + successful guarded write'})
    ok, receive = receive_evidence(log, early, nak)
    if not ok:
        return {'status':'mismatch', 'reason':f'EarlyUnreliableAccept={early} EarlyNakAccept={nak} lacks matching native receive evidence', 'receive':receive}
    return {'status':'verified', 'timers':token_of(*values), 'evidence':evidence, 'receive':receive}

def verify_run(run, intended, clients):
    parse_timers(intended)
    if not 2 <= clients <= 4:
        raise ValueError('retry qualification requires 2..4 clients')
    results={}
    for index in range(clients):
        root = Path(run)/f'client{index}'
        try:
            results[f'c{index}'] = verify_client((root/'openshim.ini').read_text(encoding='latin1'),
                                                (root/'logs/openshim.log').read_text(encoding='utf-8', errors='replace'), intended)
        except OSError as error:
            results[f'c{index}'] = {'status':'mismatch', 'reason':f'missing timer evidence: {error.filename}'}
    totals = [r['receive']['deliveredTotal'] for r in results.values() if 'receive' in r]
    naks = [r['receive']['naksAcceptedTotal'] for r in results.values() if 'receive' in r]
    held = [r['receive'].get('naksHeldTotal', 0) for r in results.values() if 'receive' in r]
    values = parse_timers(intended)
    return {'intended':intended, 'early':values[2], 'nak':values[3], 'deliveredTotal':sum(totals), 'naksAcceptedTotal':sum(naks), 'naksHeldTotal':sum(held),
            'status':'verified' if all(r['status']=='verified' for r in results.values()) else 'mismatch', 'clients':results}
