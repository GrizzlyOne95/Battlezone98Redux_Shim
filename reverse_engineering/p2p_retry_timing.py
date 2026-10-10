"""Verify intended retry timers and early-receive arm against archived INIs and native logs."""
from pathlib import Path
import re

TIMERS = (('ReliableFirstRetryMs', 'P2P Reliable First Retry', 1000),
          ('ReliableRetryIntervalMs', 'P2P Reliable Retry Interval', 2500))

ARMED = r'\[P2PRECV\] Early unreliable receive armed:'
UNAVAILABLE = r'\[P2PRECV\] Receive signatures unavailable; stock strict receive kept'
DELIVERED = r'\[P2PRECV\] Delivered early unreliable updates: total=(\d+)'

def parse_timers(token):
    """(first ms, interval ms, early 0|1) from first/interval[+early]."""
    match = re.fullmatch(r'([0-9]+)/([0-9]+)(\+early)?', token)
    if not match:
        raise ValueError('timers must be decimal first/interval milliseconds, optionally followed by +early')
    values = (int(match[1]), int(match[2]))
    if not all(50 <= value <= 10000 for value in values):
        raise ValueError('retry timers must be 50..10000 ms')
    return values + (int(bool(match[3])),)

def token_of(first, interval, early):
    return f'{first}/{interval}' + ('+early' if early else '')

def configured_timers(text):
    """(first, interval, early) from the single [Network] section; stock defaults, early 0."""
    section = ''; values = {}; sections = 0
    for line in text.splitlines():
        match = re.fullmatch(r'\s*\[([^]]+)\]\s*(?:;.*)?', line)
        if match:
            section = match[1].strip().lower()
            sections += section == 'network'
        elif section == 'network':
            match = re.fullmatch(r'\s*(ReliableFirstRetryMs|ReliableRetryIntervalMs|EarlyUnreliableAccept)\s*=\s*([^;]*)(?:;.*)?', line, re.I)
            if match:
                key = match[1].lower(); value = match[2].strip()
                if key == 'earlyunreliableaccept':
                    valid = value in ('0', '1')
                else:
                    valid = re.fullmatch('[0-9]+', value) and 50 <= int(value) <= 10000
                if key in values or not valid:
                    raise ValueError('ambiguous or invalid timer or early config')
                values[key] = int(value)
    if sections > 1:
        raise ValueError('repeated Network sections')
    return tuple(values.get(key.lower(), stock) for key, _, stock in TIMERS) + (values.get('earlyunreliableaccept', 0),)

def early_evidence(log, early):
    armed = len(re.findall(ARMED, log)); unavailable = len(re.findall(UNAVAILABLE, log))
    totals = [int(total) for total in re.findall(DELIVERED, log)]
    ok = armed == 1 and not unavailable if early else not armed
    return ok, {'early':early, 'armedLines':armed, 'signaturesUnavailableLines':unavailable,
                'deliveredTotal':max(totals, default=0)}

def verify_client(ini, log, intended):
    values = parse_timers(intended)
    early = values[2]
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
    ok, receive = early_evidence(log, early)
    if not ok:
        return {'status':'mismatch', 'reason':f'EarlyUnreliableAccept={early} lacks matching native receive evidence', 'receive':receive}
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
    return {'intended':intended, 'early':parse_timers(intended)[2], 'deliveredTotal':sum(totals),
            'status':'verified' if all(r['status']=='verified' for r in results.values()) else 'mismatch', 'clients':results}
