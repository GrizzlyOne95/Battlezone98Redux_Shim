"""Score co-op runs for the P2P reliable-send backlog fix.

  python p2p_netfix_score.py score <run dir> [--arm on|off] [--out run-score.json]
  python p2p_netfix_score.py aggregate <matrix dir>      (reads <matrix dir>/scores/*.json)

Each directed link's relay-trace.jsonl stream goes through the native accept
rule (receive 0x0075D800, GOG 2.2.301: a packet is accepted only when its stamp
equals the peer's expected sequence; reliable ones advance it), which splits
the clients' "Dropping Packet Type 0" lines into
  * future-stamped gaps: stamp > expected, i.e. an update rejected because a
    reliable message stamped before it never arrived; the backlog bug, and
  * duplicate reliable retransmits: stamp < expected, harmless.
It also measures reliable messages held back before their first transmission
(see p2p_reliable_backlog_replay.py for the method).

The class reports failures separately so a matrix can tell netcode results
from harness or machine trouble: INCOMPLETE (capture or summary missing),
CRASH (a [CRASH] record or a dump written during the run), GPU (display driver
reset events during the run), ARM_MISMATCH (the clients' patch state differs
from the intended arm), FLOW_FAIL (scenario verdict), then per arm
STRICT_PASS / LOSS for the fix and REPRODUCED / NOT_REPRODUCED for the stock
control. The generic native-network-health verdict is reported unchanged and
is not used for the strict result.

Impaired runs (flow-inputs.json "impair": a relay impairment spec applied once
the mission loaded) replay each link in the order the receiver got it: relay
drops are left out and delayed, reordered or duplicated copies are placed at
their delivery time. A run that passes its gameplay checks under impairment
is IMPAIRED_OK, since some gaps are then expected. Every run also reports
update blackouts: from the first update a receiver rejects as future-stamped
until it next accepts one from that peer, the time the player sees that peer
frozen.
"""
import argparse
import collections
import datetime
import glob
import json
import math
import os
import re
import statistics
import subprocess


def load_ports(run):
    ports = {}
    for log in glob.glob(os.path.join(run, "client*", "logs", "BZLogger.txt")):
        client = "c" + re.search(r"client(\d+)", log).group(1)
        with open(log, encoding="utf-8", errors="replace") as f:
            for line in f:
                m = re.search(r"P2P Socket Opened With .* port (\d+)", line)
                if m:
                    ports[m.group(1)] = client
    return ports


HOLD_SPAN_LIMIT = 1 << 20
EARLY_MAX_AHEAD = 4096  # include/p2p_early_unreliable_policy.h kMaxAhead
U32 = 0xFFFFFFFF


def replay_link(packets, early=False):
    """Accept rule over one link in delivery order. early=True adds the opt-in
    receiver policy (p2p_early_unreliable_policy.h): a final-fragment unreliable
    kind-0 packet stamped 1..4096 past expected is delivered while no multi-
    fragment reliable message is partly received. Expected advances only on
    accepted reliable packets. Stock mode keeps the legacy comparisons."""
    expected = None
    gaps = dups = rejected = 0
    blackouts, blackout_from, at = [], None, None
    reassembling = False  # accepted reliable fragment without 0x40 not yet completed
    for r in packets:
        t = r["transport"]
        if t["kindNibble"] != 0:
            continue
        seq = t["seqA"]
        at = r.get("deliveredMs", r["tsUnixMs"])
        flags = int(t["flagsByte"], 16)
        reliable = bool(flags & 0x80)
        if expected is None:
            expected = seq
        ahead = (seq - expected) & U32 if early else seq - expected
        if seq == expected:
            if reliable:
                expected = (seq + 1) & U32 if early else seq + 1
                reassembling = not flags & 0x40
            elif blackout_from is not None:
                blackouts.append(at - blackout_from)
                blackout_from = None
        elif early and not reliable and flags & 0x40 and not reassembling and 1 <= ahead <= EARLY_MAX_AHEAD:
            if blackout_from is not None:
                blackouts.append(at - blackout_from)
                blackout_from = None
        elif (0 < ahead <= U32 // 2) if early else ahead > 0:
            gaps += 1
            rejected += not reliable
            if not reliable and blackout_from is None:
                blackout_from = at
        elif reliable:
            dups += 1
        else:
            rejected += 1
    if blackout_from is not None:
        blackouts.append(at - blackout_from)
    return {"gaps": gaps, "dups": dups, "rejected": rejected, "blackouts": blackouts}


def percentile(sorted_values, pct):
    """Nearest-rank percentile of an ascending list (0 when empty)."""
    if not sorted_values:
        return 0
    return sorted_values[max(0, math.ceil(pct / 100.0 * len(sorted_values)) - 1)]


def reliable_flow(all_rows, forwarded):
    """Reliable delivery and NAK acceptance on one link under the stock rule.

    all_rows: every traced row of the link, any disposition (relay arrival order).
    forwarded: forwarded rows as delivered() orders them.
    Delay is first relay arrival of a reliable kind-0 stamp to the first
    forwarded copy accepted in order (expected advances only on in-order
    reliable). A kind-6 NAK carries the sender's next reliable stamp, so it is
    compared with the expected of this same link at its delivery time."""
    first_seen, copies, wire_bytes = {}, collections.Counter(), 0
    for r in all_rows:
        t = r["transport"]
        if t["kindNibble"] == 0 and int(t["flagsByte"], 16) & 0x80:
            first_seen.setdefault(t["seqA"], r["tsUnixMs"])
            copies[t["seqA"]] += 1
            wire_bytes += r.get("wireBytes", 0)
    accepted_at, expected = {}, None
    nak = {"equal": 0, "ahead": 0, "behind": 0, "noExpectation": 0}
    for r in forwarded:
        t = r["transport"]
        seq, at = t["seqA"], r.get("deliveredMs", r["tsUnixMs"])
        if t["kindNibble"] == 0:
            reliable = int(t["flagsByte"], 16) & 0x80
            if expected is None:
                expected = seq
            if reliable and seq == expected:
                accepted_at.setdefault(seq, at)
                expected = (seq + 1) & U32
        elif t["kindNibble"] == 6:
            if expected is None:
                nak["noExpectation"] += 1
            else:
                ahead = (seq - expected) & U32
                nak["equal" if ahead == 0 else "ahead" if ahead <= U32 // 2 else "behind"] += 1
    delays = [accepted_at[k] - first_seen[k] for k in accepted_at if k in first_seen]
    return {"delays": delays, "stamps": len(first_seen), "undelivered": len(set(first_seen) - set(accepted_at)),
            "retransmitCopies": sum(n - 1 for n in copies.values()), "bytes": wire_bytes, "nak": nak}


def modeled(replay):
    stats = blackout_stats(replay["blackouts"])
    return {"blackoutTotalMs": stats["blackoutTotalMs"], "blackoutMaxMs": stats["blackoutMaxMs"],
            "unreliableRejected": replay["rejected"]}


def analyse_link(packets, early=False):
    first_tx, queued_by, high = {}, {}, -1
    for r in packets:
        t = r["transport"]
        if t["kindNibble"] != 0:
            continue
        # ts: when the sender sent it (relay arrival).
        seq, ts = t["seqA"], r["tsUnixMs"]
        reliable = bool(int(t["flagsByte"], 16) & 0x80)
        if reliable:
            first_tx.setdefault(seq, ts)
        else:
            # A stamp wrapping or jumping far ahead is not a plausible backlog; do not enumerate it.
            for k in range(high + 1, seq if seq - high <= HOLD_SPAN_LIMIT else high + 1):
                queued_by.setdefault(k, ts)
            high = max(high, seq - 1)
    stock, early_replay = replay_link(packets), replay_link(packets, True)
    used = early_replay if early else stock
    gaps, dups, rejected = used["gaps"], used["dups"], used["rejected"]
    late = sorted(first_tx[k] - queued_by[k] for k in first_tx
                  if k in queued_by and first_tx[k] > queued_by[k])
    return {
        "futureStampedGaps": gaps,
        "unreliableRejected": rejected,
        "duplicateReliable": dups,
        "reliableMessages": len(first_tx),
        "reliableHeld": len(late),
        "holdMedianMs": statistics.median(late) if late else 0,
        "holdMaxMs": late[-1] if late else 0,
        "modeledStock": modeled(stock),
        "modeledEarly": modeled(early_replay),
    } | blackout_stats(used["blackouts"])


LONG_BLACKOUT_MS = 500


def blackout_stats(blackouts):
    return {
        "blackouts": len(blackouts),
        "blackoutTotalMs": round(sum(blackouts), 3),
        "blackoutMaxMs": round(max(blackouts, default=0), 3),
        "blackoutsOver500Ms": sum(1 for b in blackouts if b >= LONG_BLACKOUT_MS),
    }


def delivered(rows):
    """Forwarded trace rows as the receiver got them: one row per copy sent,
    at its delivery time, in delivery order (stable for equal times)."""
    out = []
    for r in rows:
        delays = (r.get("impairment") or {}).get("delaysMs")
        for d in (delays if delays else [0]):
            out.append(r | {"deliveredMs": r["tsUnixMs"] + d})
    out.sort(key=lambda r: r["deliveredMs"])
    return out


def fix_state(run):
    states = {}
    for log in sorted(glob.glob(os.path.join(run, "client*", "logs", "openshim.log"))):
        client = "c" + re.search(r"client(\d+)", log).group(1)
        with open(log, encoding="utf-8", errors="replace") as f:
            text = f.read()
        if "P2P Reliable Send Backlog wrote" in text:
            states[client] = "on"
        elif "[SKIP] P2P Reliable Send Backlog" in text or "backlog fix disabled" in text:
            states[client] = "off"
        else:
            states[client] = "unknown"
    values = set(states.values())
    return (values.pop() if len(values) == 1 else "mixed" if values else "unknown"), states


def run_window(run):
    # Live files only: summaries can be regenerated later, which would stretch
    # the window over unrelated driver events.
    start = os.path.getctime(run)
    live = [os.path.join(run, n) for n in ("relay-trace.jsonl", "coordinator.log", "server.log")]
    ends = [os.path.getmtime(p) for p in live if os.path.exists(p)]
    return start, max(ends) if ends else start


def crash_evidence(run, start, end):
    found = []
    for log in glob.glob(os.path.join(run, "client*", "logs", "openshim_crash.log")):
        with open(log, encoding="utf-8", errors="replace") as f:
            for line in f:
                if line.startswith("[CRASH]"):
                    found.append(f"{os.path.relpath(log, run)}: {line.strip()[:160]}")
    # Instance log folders carry older dumps forward; only dumps written
    # during this run count.
    for dmp in glob.glob(os.path.join(run, "client*", "logs", "*.dmp")):
        if start - 5 <= os.path.getmtime(dmp) <= end + 5:
            found.append(os.path.relpath(dmp, run))
    return found


GPU_EVENT_QUERY = r"""
$ErrorActionPreference = 'Stop'
try {
    $events = @(Get-WinEvent -FilterHashtable @{ LogName = 'System'; StartTime = [datetime]'%(start)s'; EndTime = [datetime]'%(end)s' })
} catch {
    # Only "no records in the window" is a genuine zero; anything else
    # (access denied, log unavailable, bad filter) is unknown evidence.
    if ($_.FullyQualifiedErrorId -like 'NoMatchingEventsFound*') { 'COUNT 0'; exit 0 }
    "ERR $($_.FullyQualifiedErrorId)"; exit 3
}
# Provider names are post-filtered: a FilterHashtable ProviderName list that
# names a provider not registered here (amdkmdag, igfx) throws instead.
'COUNT ' + @($events | Where-Object { $_.ProviderName -match 'nvlddmkm|dxgkrnl|amdkmdag|igfx' -or $_.Id -eq 4101 }).Count
"""


def run_powershell(script):
    return subprocess.run(["powershell", "-NoProfile", "-NonInteractive", "-Command", script],
                          capture_output=True, text=True, timeout=90)


def parse_gpu_query(returncode, stdout):
    """Driver reset count, or None when the evidence is unavailable."""
    if returncode != 0:
        return None
    lines = [l.strip() for l in (stdout or "").splitlines() if l.strip()]
    if len(lines) != 1 or not re.fullmatch(r"COUNT \d+", lines[0]):
        return None
    return int(lines[0].split()[1])


def gpu_events(start, end, runner=run_powershell):
    # Driver resets only: Display 4127 (an HDR/brightness notice) fires on
    # every client launch and is not one.
    fmt = "%Y-%m-%dT%H:%M:%S"
    script = GPU_EVENT_QUERY % {
        "start": datetime.datetime.fromtimestamp(start).strftime(fmt),
        "end": datetime.datetime.fromtimestamp(end + 10).strftime(fmt),  # small shutdown allowance only
    }
    try:
        out = runner(script)
    except (OSError, subprocess.SubprocessError):
        return None
    return parse_gpu_query(out.returncode, out.stdout)


def load_json(path):
    if not os.path.exists(path):
        return None
    with open(path, encoding="utf-8-sig") as f:
        return json.load(f)


HEALTH_CHECK = re.compile(r"native peers .*sequence rejection", re.I)
CAPTURE_CHECK = re.compile(r"complete maximum network captures", re.I)


def flow_breakdown(flow):
    """Split the scenario verdict: gameplay (every step and every check except
    the generic native-health one), capture completeness, and native health.
    A stock run that fails only the health check is evidence, not a flow
    failure."""
    if flow is None:
        return None, None, []
    failed = [f"step: {s.get('step')}" for s in flow.get("steps", []) if s.get("status") == "fail"]
    # The capture check must be present and every instance of it must pass;
    # its absence is not success.
    capture_seen = capture_failed = False
    for c in flow.get("checks", []):
        name = c.get("check") or ""
        if CAPTURE_CHECK.search(name):
            capture_seen = True
            capture_failed |= c.get("status") != "pass"
        elif not HEALTH_CHECK.search(name) and c.get("status") == "fail":
            failed.append(f"check: {name.strip()}")
    return ("PASS" if not failed else "FAIL"), capture_seen and not capture_failed, failed


def modeled_summary(links, key, link_minutes):
    total = sum(v[key]["blackoutTotalMs"] for v in links.values())
    return {"blackoutSPerLinkMinute": round(total / 1000.0 / link_minutes, 4) if link_minutes else None,
            "worstBlackoutMs": max((v[key]["blackoutMaxMs"] for v in links.values()), default=0),
            "unreliableRejected": sum(v[key]["unreliableRejected"] for v in links.values())}


def score(run, arm=None, clients=4, gpu_query=None, timers=None):
    run = os.path.abspath(run)
    early = False
    if timers is not None:
        from p2p_retry_timing import parse_timers, token_of
        values = parse_timers(timers)
        early = bool(values[2])
    result = {"run": os.path.basename(run), "runDir": run, "arm": arm, "problems": []}
    flow = load_json(os.path.join(run, "flow-summary.json"))
    health = load_json(os.path.join(run, "native-network-health.json"))
    trace_path = os.path.join(run, "relay-trace.jsonl")
    result["flowVerdict"] = flow.get("verdict") if flow else None
    result["gameplayVerdict"], capture_ok, result["gameplayFailures"] = flow_breakdown(flow)
    result["healthStatus"] = health.get("status") if health else None
    if health:
        result["missionObservedS"] = {f"c{c['client']}": c.get("missionObservedSeconds") for c in health.get("clients", [])}

    links, span, malformed = {}, 0.0, 0
    result["reliableDelivery"] = result["nakAcceptance"] = None
    if os.path.exists(trace_path):
        rows, traced = [], []
        with open(trace_path, encoding="utf-8") as f:
            for line in f:
                if not line.strip():
                    continue
                try:
                    r = json.loads(line)
                except ValueError:
                    malformed += 1
                    continue
                if "transport" in r:
                    traced.append(r)
                    if r.get("disposition", "forwarded") == "forwarded":
                        rows.append(r)
        if rows:
            span = (rows[-1]["tsUnixMs"] - rows[0]["tsUnixMs"]) / 1000
        ports = load_ports(run)
        streams, all_streams = collections.defaultdict(list), collections.defaultdict(list)
        for r in rows:
            streams[(r["source"].rsplit(":", 1)[1], r["target"].rsplit(":", 1)[1])].append(r)
        for r in traced:
            all_streams[(r["source"].rsplit(":", 1)[1], r["target"].rsplit(":", 1)[1])].append(r)
        flows = {}
        for (src, dst), packets in streams.items():
            name = f"{ports.get(src, src)}->{ports.get(dst, dst)}"
            links[name] = analyse_link(delivered(packets), early)
            flows[name] = reliable_flow(all_streams[(src, dst)], delivered(packets))
        for (src, dst), packets in all_streams.items():  # links whose every copy was dropped
            name = f"{ports.get(src, src)}->{ports.get(dst, dst)}"
            if name not in flows:
                flows[name] = reliable_flow(packets, [])
        delays = sorted(d for f in flows.values() for d in f["delays"])
        result["reliableDelivery"] = {
            "count": len(delays), "p50Ms": percentile(delays, 50), "p95Ms": percentile(delays, 95),
            "p99Ms": percentile(delays, 99), "maxMs": delays[-1] if delays else 0,
            "stamps": sum(f["stamps"] for f in flows.values()),
            "undelivered": sum(f["undelivered"] for f in flows.values()),
            "reliableRetransmitCopies": sum(f["retransmitCopies"] for f in flows.values()),
            "reliableBytes": sum(f["bytes"] for f in flows.values())}
        nak = {k: sum(f["nak"][k] for f in flows.values()) for k in ("equal", "ahead", "behind", "noExpectation")}
        result["nakAcceptance"] = nak | {"perLink": {n: f["nak"] for n, f in sorted(flows.items()) if any(f["nak"].values())}}
    result["traceSpanS"] = span
    result["links"] = dict(sorted(links.items()))
    totals = collections.Counter()
    for v in links.values():
        for k in ("futureStampedGaps", "unreliableRejected", "duplicateReliable", "reliableMessages", "reliableHeld",
                  "blackouts", "blackoutTotalMs", "blackoutsOver500Ms"):
            totals[k] += v[k]
    result["totals"] = dict(totals)
    result["maxHoldMs"] = max((v["holdMaxMs"] for v in links.values()), default=0)
    result["maxBlackoutMs"] = max((v["blackoutMaxMs"] for v in links.values()), default=0)
    link_minutes = len(links) * span / 60.0
    result["blackoutSPerLinkMinute"] = round(totals["blackoutTotalMs"] / 1000.0 / link_minutes, 4) if link_minutes else None
    # Both rules on the same trace, whatever arm ran; the legacy fields above follow the run's own rule.
    result["earlyModel"] = early
    result["modeledStock"] = modeled_summary(links, "modeledStock", link_minutes)
    result["modeledEarly"] = modeled_summary(links, "modeledEarly", link_minutes)
    inputs = load_json(os.path.join(run, "flow-inputs.json")) or {}
    result["impair"] = inputs.get("impair") or ""
    final = load_json(os.path.join(run, "relay-impairment-final.json"))
    result["impairment"] = (final or {}).get("impairment")
    result["worstLink"] = max(links, key=lambda k: links[k]["futureStampedGaps"]) if links else None

    result["fix"], result["fixPerClient"] = fix_state(run)
    if timers is not None:
        from p2p_retry_timing import verify_run
        result["timers"] = token_of(*values)
        result["timerEvidence"] = verify_run(run, result["timers"], clients)
    start, end = run_window(run)
    result["crashes"] = crash_evidence(run, start, end)
    # None means the event log could not be read: evidence unavailable, never
    # an implicit zero.
    result["gpuEvents"] = (gpu_query or gpu_events)(start, end)
    result["malformedTraceLines"] = malformed

    expected_links = clients * (clients - 1)
    incomplete = []
    missing = [n for n, v in (("flow-summary", flow), ("native-network-health", health), ("relay trace", links)) if not v]
    if missing:
        incomplete.append("missing " + ", ".join(missing))
    if links and len(links) < expected_links:
        incomplete.append(f"{len(links)}/{expected_links} links in the relay trace")
    if len(result["fixPerClient"]) < clients:
        incomplete.append(f"{len(result['fixPerClient'])}/{clients} client openshim logs")
    if malformed:
        incomplete.append(f"{malformed} malformed relay-trace line(s)")
    if flow is not None and not capture_ok:
        incomplete.append("harness capture-completeness check missing or failed")
    if result["gpuEvents"] is None:
        incomplete.append("GPU event evidence unavailable")
    if result["impair"] and not (result["impairment"] or {}).get("matched"):
        # The spec never reached the relay, or the relay never applied it.
        incomplete.append("impairment counters missing or nothing impaired")

    if incomplete:
        result["class"] = "INCOMPLETE"
        result["problems"] += incomplete
    elif result["crashes"]:
        result["class"] = "CRASH"
    elif result["gpuEvents"]:
        result["class"] = "GPU"
    elif not arm or result["fix"] != arm:
        # A strict result needs both an intended arm and every client's patch
        # log agreeing with it.
        result["class"] = "ARM_MISMATCH"
        result["problems"].append(f"intended {arm}, clients {result['fixPerClient']}")
    elif timers is not None and result["timerEvidence"]["status"] != "verified":
        result["class"] = "ARM_MISMATCH"
        result["problems"].append(f"retry timer evidence mismatch: {result['timerEvidence']['clients']}")
    elif result["gameplayVerdict"] != "PASS":
        result["class"] = "FLOW_FAIL"
        result["problems"] += result["gameplayFailures"]
    elif result["impair"]:
        result["class"] = "IMPAIRED_OK"
    elif arm == "on":
        result["class"] = "STRICT_PASS" if totals["futureStampedGaps"] == 0 else "LOSS"
    else:
        result["class"] = "REPRODUCED" if totals["futureStampedGaps"] else "NOT_REPRODUCED"
    return result


INFRA_CLASSES = ("INCOMPLETE", "CRASH", "GPU", "ARM_MISMATCH", "FLOW_FAIL", "UNSCORED")


def aggregate(matrix):
    """Summarise a matrix. With matrix.json present the verdict covers the
    whole plan: every planned run scored exactly once, so a partial or resumed
    matrix can never read as a complete PASS.

    acceptance  PASS when the plan is complete, every fix-ON run is
                STRICT_PASS and no stock-control run failed for
                infrastructure or gameplay reasons.
    comparison  REPRODUCED when at least one stock-control run shows
                future-stamped gaps, i.e. the matrix exercised the bug.
    verdict     PASS only when both hold.
    """
    plan_doc = load_json(os.path.join(matrix, "matrix.json")) or {}
    plan = plan_doc.get("plan") or []
    scores = []
    for path in sorted(glob.glob(os.path.join(matrix, "scores", "*.json"))):
        scores.append(load_json(path))
    by_index = collections.defaultdict(list)
    problems = []
    for s in scores:
        if s.get("index") is None:
            problems.append(f"score without a plan index: {s.get('run')}")
        else:
            by_index[s["index"]].append(s)
    if plan and len(scores) != len(plan):
        problems.append(f"{len(scores)} score files for {len(plan)} planned runs")
    if plan:
        for p in plan:
            got = by_index.get(p["index"], [])
            if len(got) != 1:
                problems.append(f"planned run {p['index']} ({p['arm']} p{p['pass']} {p['case']}) scored {len(got)} times")
            elif got[0].get("run") != p["run"] or got[0].get("arm") != p["arm"]:
                problems.append(f"planned run {p['index']} scored as {got[0].get('run')} arm {got[0].get('arm')}")
            elif p.get("timers") and (got[0].get("timers") != p["timers"] or
                                      (got[0].get("timerEvidence") or {}).get("status") != "verified"):
                problems.append(f"planned run {p['index']} lacks verified timers {p['timers']}")
            elif p.get("timers") and (got[0].get("impair") or "") != (p.get("impair") or ""):
                problems.append(f"planned run {p['index']} impairment differs from its timer comparison arm")
        extra = sorted(set(by_index) - {p["index"] for p in plan})
        if extra:
            problems.append(f"scores outside the plan: {extra}")
    else:
        problems.append("no matrix.json plan; completeness unknown")
    by_arm = collections.defaultdict(lambda: collections.Counter())
    for s in scores:
        c = by_arm[s.get("arm") or "none"]
        c["runs"] += 1
        c[s["class"]] += 1
        for k, v in s.get("totals", {}).items():
            c[k] += v
    if any(p.get("impair") or p.get("timers") for p in plan):
        return aggregate_impaired(matrix, plan, scores, problems)
    planned_arms = sorted({p["arm"] for p in plan})
    for arm in planned_arms:
        if not by_arm[arm]["runs"]:
            problems.append(f"no scored {arm} runs")
    on, off = by_arm.get("on", collections.Counter()), by_arm.get("off", collections.Counter())
    on_ok = bool(on["runs"]) and on["STRICT_PASS"] == on["runs"]
    off_bad = sum(off[k] for k in INFRA_CLASSES)
    if off_bad:
        problems.append(f"{off_bad} stock-control run(s) failed for infrastructure or gameplay reasons")
    acceptance = "PASS" if on_ok and not problems else "FAIL"
    if "off" in planned_arms:
        comparison = "REPRODUCED" if off["REPRODUCED"] else "NOT_REPRODUCED"
    else:
        comparison = "NO_CONTROL"
    summary = {
        "matrix": matrix,
        "verdict": "PASS" if acceptance == "PASS" and comparison == "REPRODUCED" else "FAIL",
        "acceptance": acceptance,
        "comparison": comparison,
        "acceptanceRule": "plan complete; every fix-ON run STRICT_PASS (complete capture, no crash/GPU event, gameplay PASS, "
                          "0 future-stamped gaps); no stock-control infrastructure/gameplay failure",
        "comparisonRule": "at least one stock-control run REPRODUCED (future-stamped gaps > 0)",
        "planned": len(plan), "scored": len(scores), "problems": problems,
        "stockReproduced": f"{off['REPRODUCED']}/{off['runs']}",
        "byArm": {k: dict(v) for k, v in by_arm.items()},
        "runs": [{k: s.get(k) for k in ("index", "run", "case", "pass", "arm", "class", "flowVerdict", "gameplayVerdict",
                                        "healthStatus", "traceSpanS", "maxHoldMs", "worstLink", "gpuEvents", "problems")}
                 | {"gaps": s.get("totals", {}).get("futureStampedGaps"),
                    "held": s.get("totals", {}).get("reliableHeld"),
                    "reliable": s.get("totals", {}).get("reliableMessages"),
                    "dups": s.get("totals", {}).get("duplicateReliable"),
                    "crashes": len(s.get("crashes") or [])} for s in scores],
    }
    with open(os.path.join(matrix, "summary.json"), "w", encoding="utf-8") as f:
        json.dump(summary, f, indent=1)
    lines = ["# P2P reliable-send backlog stress matrix", "",
             f"Matrix: `{os.path.basename(os.path.normpath(matrix))}`, {summary['scored']}/{summary['planned']} planned runs scored", "",
             f"**Verdict: {summary['verdict']}** (acceptance {acceptance}, comparison {comparison}, "
             f"stock reproduced {summary['stockReproduced']})", "",
             f"- Acceptance: {summary['acceptanceRule']}", f"- Comparison: {summary['comparisonRule']}"]
    lines += [f"- Problem: {p}" for p in problems]
    lines += ["", "| Arm | Runs | Classes | Gaps | Held / reliable | Duplicates |", "|---|---|---|---|---|---|"]
    for arm, c in sorted(summary["byArm"].items()):
        classes = ", ".join(f"{k} {v}" for k, v in sorted(c.items()) if k.isupper())
        lines.append(f"| {arm} | {c.get('runs', 0)} | {classes} | {c.get('futureStampedGaps', 0)} | "
                     f"{c.get('reliableHeld', 0)} / {c.get('reliableMessages', 0)} | {c.get('duplicateReliable', 0)} |")
    lines += ["", "| # | Run | Arm | Class | Gameplay | Health | Span s | Gaps | Held | Max hold ms | Worst link | GPU | Notes |",
              "|---|---|---|---|---|---|---|---|---|---|---|---|---|"]
    for r in summary["runs"]:
        notes = "; ".join(r.get("problems") or []) + (f" {r['crashes']} crash record(s)" if r.get("crashes") else "")
        lines.append(f"| {r['index']} | {r['run']} | {r['arm']} | {r['class']} | {r['gameplayVerdict']} | {r['healthStatus']} | "
                     f"{(r['traceSpanS'] or 0):.0f} | {r['gaps']} | {r['held']}/{r['reliable']} | {r['maxHoldMs']} | "
                     f"{r['worstLink']} | {r['gpuEvents']} | {notes.replace('|', '/')} |")
    with open(os.path.join(matrix, "summary.md"), "w", encoding="utf-8") as f:
        f.write("\n".join(lines) + "\n")
    print("\n".join(lines))
    return summary


HARD_FAIL_CLASSES = ("INCOMPLETE", "CRASH", "GPU", "ARM_MISMATCH", "UNSCORED")


def aggregate_impaired(matrix, plan, scores, problems):
    """An impairment matrix: every fix-ON run must stay playable (IMPAIRED_OK)
    and no stock-control run may fail for infrastructure reasons. A stock run
    whose gameplay fails under impairment is evidence, not a failure. The
    arms are then compared per impairment profile."""
    groups = collections.OrderedDict()
    for p in plan:
        groups.setdefault((p.get("impair") or "", p["arm"], p.get("timers") or ""), collections.Counter())
    for s in scores:
        c = groups.setdefault((s.get("impair") or "", s.get("arm") or "none", s.get("timers") or ""), collections.Counter())
        c["runs"] += 1
        c[s["class"]] += 1
        for k, v in s.get("totals", {}).items():
            c[k] += v
        c["linkMinutes"] += len(s.get("links") or {}) * (s.get("traceSpanS") or 0) / 60.0
        c["maxBlackoutMs"] = max(c["maxBlackoutMs"], s.get("maxBlackoutMs") or 0)
        imp = s.get("impairment") or {}
        c["relayMatched"] += imp.get("matched", 0)
        c["relayDropped"] += sum(imp.get(k, 0) for k in ("dropped_loss", "dropped_outage", "dropped_queue"))
    for s in scores:
        wanted = "IMPAIRED_OK" if s.get("impair") else "STRICT_PASS"
        if s.get("arm") == "on" and s["class"] != wanted:
            problems.append(f"fix-ON run {s.get('index')} ({s.get('impair')}) is {s['class']}")
        if s.get("arm") == "off" and s["class"] in HARD_FAIL_CLASSES:
            problems.append(f"stock run {s.get('index')} ({s.get('impair')}) failed for infrastructure: {s['class']}")
    rows = []
    for (impair, arm, timers), c in groups.items():
        lm = c["linkMinutes"]
        rows.append({
            "impair": impair, "arm": arm, "runs": c["runs"],
            "timers": timers,
            "classes": {k: v for k, v in c.items() if k.isupper()},
            "relayDropPct": round(100.0 * c["relayDropped"] / c["relayMatched"], 2) if c["relayMatched"] else None,
            "gapsPer1000Reliable": round(1000.0 * c["futureStampedGaps"] / c["reliableMessages"], 2) if c["reliableMessages"] else None,
            "blackoutSPerLinkMinute": round(c["blackoutTotalMs"] / 1000.0 / lm, 4) if lm else None,
            "blackoutsOver500MsPerLinkMinute": round(c["blackoutsOver500Ms"] / lm, 4) if lm else None,
            "maxBlackoutMs": c["maxBlackoutMs"],
            "duplicateReliable": c["duplicateReliable"],
            "reliableMessages": c["reliableMessages"],
        })
    acceptance = "PASS" if not problems else "FAIL"
    summary = {
        "matrix": matrix, "kind": "impairment",
        "verdict": acceptance, "acceptance": acceptance,
        "acceptanceRule": "plan complete; intended timer arms verified when specified; every fix-ON impaired run IMPAIRED_OK "
                          "(complete capture, impairment applied, no crash/GPU event, gameplay PASS), clean run STRICT_PASS; "
                          "no stock-control infrastructure failure. Native-health qualification remains separate.",
        "planned": len(plan), "scored": len(scores), "problems": problems,
        "groups": rows,
        "runs": [{k: s.get(k) for k in ("index", "run", "case", "pass", "arm", "impair", "timers", "timerEvidence", "class", "gameplayVerdict",
                                        "healthStatus", "traceSpanS", "maxBlackoutMs", "blackoutSPerLinkMinute",
                                        "worstLink", "gpuEvents", "problems")}
                 | {"gaps": s.get("totals", {}).get("futureStampedGaps"),
                    "longBlackouts": s.get("totals", {}).get("blackoutsOver500Ms"),
                    "crashes": len(s.get("crashes") or [])} for s in scores],
    }
    with open(os.path.join(matrix, "summary.json"), "w", encoding="utf-8") as f:
        json.dump(summary, f, indent=1)
    lines = ["# P2P impairment matrix", "",
             f"Matrix: `{os.path.basename(os.path.normpath(matrix))}`, {len(scores)}/{len(plan)} planned runs scored", "",
             f"**Verdict: {acceptance}**", "", f"- Acceptance: {summary['acceptanceRule']}",
             "- Blackout: a receiver rejecting a peer's updates as future-stamped until it next accepts one."]
    lines += [f"- Problem: {p}" for p in problems]
    lines += ["", "| Impairment | Arm | Timers ms | Runs | Classes | Relay drop % | Gaps / 1000 reliable | Blackout s / link-min | "
              ">=500 ms blackouts / link-min | Max blackout ms | Duplicates / reliable |", "|---|---|---|---|---|---|---|---|---|---|---|"]
    for r in rows:
        classes = ", ".join(f"{k} {v}" for k, v in sorted(r["classes"].items()))
        lines.append(f"| `{r['impair']}` | {r['arm']} | {r['timers'] or 'unspecified'} | {r['runs']} | {classes} | {r['relayDropPct']} | "
                     f"{r['gapsPer1000Reliable']} | {r['blackoutSPerLinkMinute']} | {r['blackoutsOver500MsPerLinkMinute']} | "
                     f"{r['maxBlackoutMs']:.0f} | {r['duplicateReliable']} / {r['reliableMessages']} |")
    lines += ["", "| # | Run | Arm | Impairment | Class | Gameplay | Span s | Gaps | Blackout s/link-min | Max blackout ms | "
              "GPU | Notes |", "|---|---|---|---|---|---|---|---|---|---|---|---|"]
    for r in summary["runs"]:
        notes = "; ".join(r.get("problems") or []) + (f" {r['crashes']} crash record(s)" if r.get("crashes") else "")
        lines.append(f"| {r['index']} | {r['run']} | {r['arm']} | `{r['impair']}` | {r['class']} | {r['gameplayVerdict']} | "
                     f"{(r['traceSpanS'] or 0):.0f} | {r['gaps']} | {r['blackoutSPerLinkMinute']} | "
                     f"{(r['maxBlackoutMs'] or 0):.0f} | {r['gpuEvents']} | {notes.replace('|', '/')} |")
    with open(os.path.join(matrix, "summary.md"), "w", encoding="utf-8") as f:
        f.write("\n".join(lines) + "\n")
    print("\n".join(lines))
    return summary


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("score")
    s.add_argument("run")
    s.add_argument("--arm", choices=("on", "off"))
    s.add_argument("--clients", type=int, default=4)
    s.add_argument("--timers", help="intended first/interval[+early] ms; requires matching archived INI and native apply logs")
    s.add_argument("--case", default=None)
    s.add_argument("--pass-index", type=int, default=None)
    s.add_argument("--index", type=int, default=None, help="position in the matrix plan")
    s.add_argument("--impair", default=None, help="the plan's impairment spec (checked against flow-inputs.json)")
    s.add_argument("--out")
    a = sub.add_parser("aggregate")
    a.add_argument("matrix")
    args = ap.parse_args()
    if args.cmd == "score":
        if args.timers is not None:
            from p2p_retry_timing import parse_timers
            try:
                parse_timers(args.timers)
            except ValueError as error:
                ap.error(str(error))
        r = score(args.run, args.arm, args.clients, timers=args.timers)
        r["case"], r["pass"], r["index"] = args.case, args.pass_index, args.index
        if args.impair is not None and args.impair != r["impair"]:
            r["class"] = "ARM_MISMATCH"
            r["problems"].append(f"planned impairment {args.impair!r}, run used {r['impair']!r}")
        text = json.dumps(r, indent=1)
        if args.out:
            os.makedirs(os.path.dirname(os.path.abspath(args.out)), exist_ok=True)
            with open(args.out, "w", encoding="utf-8") as f:
                f.write(text)
        t = r["totals"]
        print(f"[score] {r['run']}: {r['class']} arm={r['arm']} fix={r['fix']} flow={r['flowVerdict']} "
              f"health={r['healthStatus']} gaps={t.get('futureStampedGaps', 0)} held={t.get('reliableHeld', 0)}/"
              f"{t.get('reliableMessages', 0)} blackout={t.get('blackoutTotalMs', 0) / 1000:.1f}s "
              f"max={r['maxBlackoutMs']:.0f}ms gpu={r['gpuEvents']} crashes={len(r['crashes'])}")
    else:
        aggregate(args.matrix)


if __name__ == "__main__":
    main()
