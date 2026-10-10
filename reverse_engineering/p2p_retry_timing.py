"""Verify intended retry timers against archived INIs and successful native writes."""
from pathlib import Path
import re

TIMERS = (('ReliableFirstRetryMs', 'P2P Reliable First Retry', 1000),
          ('ReliableRetryIntervalMs', 'P2P Reliable Retry Interval', 2500))

def parse_timers(token):
    if not re.fullmatch(r'[0-9]+/[0-9]+', token):
        raise ValueError('timers must be decimal first/interval milliseconds')
    values = tuple(map(int, token.split('/')))
    if not all(50 <= value <= 10000 for value in values):
        raise ValueError('retry timers must be 50..10000 ms')
    return values

def configured_timers(text):
    section = ''; values = {}; sections = 0
    for line in text.splitlines():
        match = re.fullmatch(r'\s*\[([^]]+)\]\s*(?:;.*)?', line)
        if match:
            section = match[1].strip().lower()
            sections += section == 'network'
        elif section == 'network':
            match = re.fullmatch(r'\s*(ReliableFirstRetryMs|ReliableRetryIntervalMs)\s*=\s*([^;]*)(?:;.*)?', line, re.I)
            if match:
                key = match[1].lower(); value = match[2].strip()
                if key in values or not re.fullmatch('[0-9]+', value) or not 50 <= int(value) <= 10000:
                    raise ValueError('ambiguous or invalid timer config')
                values[key] = int(value)
    if sections > 1:
        raise ValueError('repeated Network sections')
    return tuple(values.get(key.lower(), stock) for key, _, stock in TIMERS)

def verify_client(ini, log, intended):
    values = parse_timers(intended)
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
    return {'status':'verified', 'timers':f'{values[0]}/{values[1]}', 'evidence':evidence}

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
    return {'intended':intended, 'status':'verified' if all(r['status']=='verified' for r in results.values()) else 'mismatch', 'clients':results}
