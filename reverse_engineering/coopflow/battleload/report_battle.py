"""Report measured combat/population and relay ingress rates, retaining raw data."""
import argparse
import collections
import datetime as dt
import hashlib
import json
import math
from pathlib import Path


def timestamp(value):
    return dt.datetime.fromisoformat(value.replace("Z", "+00:00")).timestamp()


def percentile(values, fraction):
    values = sorted(values)
    return values[max(0, math.ceil(len(values) * fraction) - 1)] if values else None


def summarize(run):
    samples = [json.loads(line) for line in (run / "battle-samples.jsonl").read_text(encoding="utf-8-sig").splitlines() if line]
    host = [s for s in samples if s["client"] == 0]
    idle = [s for s in host if s["phase"] == "idle"]
    combat = [s for s in host if s["phase"] == "combat"]
    if len(idle) < 2 or len(combat) < 2:
        raise ValueError("missing idle/combat evidence; no rate comparison produced")
    steady = [s for s in combat if s["state"].get("rampCompleted") and not s["state"].get("finished")]
    if not steady:
        # Older smoke had a single duration including ramp. Explicitly label it.
        steady = [s for s in combat if timestamp(s["at"]) >= timestamp(combat[0]["at"]) + 10]
    if len(steady) < 2:
        raise ValueError("insufficient sustained combat samples")
    windows = {"emptyMapIdle": (timestamp(idle[0]["at"]), timestamp(idle[-1]["at"])),
               "sustainedBattle": (timestamp(steady[0]["at"]), timestamp(steady[-1]["at"]))}
    packets = {phase: collections.defaultdict(list) for phase in windows}
    with (run / "relay-trace.jsonl").open(encoding="utf-8-sig") as stream:
        for line in stream:
            row = json.loads(line)
            if "transport" not in row:
                continue
            at = row["tsUnixMs"] / 1000
            for phase, (begin, end) in windows.items():
                if begin <= at < end:
                    packets[phase][row["source"] + "->" + row["target"]].append(row)
    rates = {}
    for phase, (begin, end) in windows.items():
        seconds = end - begin
        links = {}
        aggregate_bins = collections.Counter()
        for link, rows in sorted(packets[phase].items()):
            byte_count = sum(r["transport"]["wireBytes"] for r in rows)
            bins = collections.Counter()
            reliable = drops = copies = 0
            seen = set()
            for row in rows:
                transport = row["transport"]
                is_reliable = transport["kindNibble"] == 0 and bool(int(transport["flagsByte"], 16) & 0x80)
                reliable += is_reliable
                drops += row.get("disposition", "").startswith("dropped")
                if is_reliable:
                    payload = bytes.fromhex(row["datagramHex"])[transport["headerBytes"]:]
                    key = (transport["seqA"], hashlib.sha256(payload).hexdigest())
                    copies += key in seen
                    seen.add(key)
                bucket = int(row["tsUnixMs"] / 1000 - begin)
                bins[bucket] += transport["wireBytes"]
                aggregate_bins[bucket] += transport["wireBytes"]
            full_bins = [bins[i] * 8 / 1000 for i in range(int(seconds))]
            links[link] = {"datagrams": len(rows), "datagramsPerSecond": len(rows) / seconds,
                           "bzrDatagramKbps": byte_count * 8 / 1000 / seconds,
                           "reliableDatagrams": reliable, "reliableRepeatedDatagrams": copies,
                           "relayDrops": drops, "oneSecondKbpsP95": percentile(full_bins, .95),
                           "oneSecondKbpsMax": max(full_bins, default=0)}
        rates[phase] = {"beginUtc": dt.datetime.fromtimestamp(begin, dt.timezone.utc).isoformat(),
                        "endUtc": dt.datetime.fromtimestamp(end, dt.timezone.utc).isoformat(),
                        "seconds": seconds, "activeDirectedLinks": len(links), "links": links,
                        "aggregateDatagramsPerSecond": sum(l["datagramsPerSecond"] for l in links.values()),
                        "aggregateBzrDatagramKbps": sum(l["bzrDatagramKbps"] for l in links.values()),
                        "aggregateOneSecondKbpsMax": max((v * 8 / 1000 for k,v in aggregate_bins.items() if k < int(seconds)), default=0)}
    clients = {}
    for client in sorted({s["client"] for s in samples}):
        rows = [s for s in samples if s["client"] == client and s["phase"] == "combat"]
        first, last = rows[0], rows[-1]
        wall = timestamp(last["at"]) - timestamp(first["at"])
        clients[str(client)] = {"wallSeconds": wall, "cpuEquivalentCores": (last["cpuSeconds"] - first["cpuSeconds"]) / wall,
            "simulationSecondsPerWallSecond": (last["state"]["simulationTime"] - first["state"]["simulationTime"]) / wall,
            "missionUpdateCallsPerWallSecond": (last["state"]["updates"] - first["state"]["updates"]) / wall,
            "probeCommandMsP95": percentile([s["commandMs"] for s in rows], .95),
            "workingSetPeakBytes": max(s["workingSetBytes"] for s in rows),
            "peakAI": last["state"]["peakAI"], "peakScrap": last["state"]["peakScrap"],
            "newScrapObserved": last["state"]["scrapObserved"]}
    return {"run": str(run), "hostFinalMeasured": combat[-1]["state"], "clients": clients,
            "rates": rates, "limitations": [
                "Relay ingress bytes exclude UDP/IP headers; decision timestamps do not measure send completion.",
                "Reliable repeats use sequence+payload hash per directed link; these are send attempts, not receiver acceptance.",
                "Empty-map idle differs in object count; packet growth is not isolated to combat alone.",
                "CPU, mission updates and simulation clocks are not renderer FPS; four clients share this PC.",
                "Scrap is census-observed; short-lived pieces and reused native handles can be missed."]}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("run", type=Path)
    args = parser.parse_args()
    report = summarize(args.run)
    (args.run / "battle-network-report.json").write_text(json.dumps(report, indent=2), encoding="utf-8")
    lines = ["# Battle-load measurements", "", "| Phase | Seconds | Directed links | Datagrams/s | BZR datagram kbps |", "|---|---:|---:|---:|---:|"]
    for phase, rate in report["rates"].items():
        lines.append(f'| {phase} | {rate["seconds"]:.1f} | {rate["activeDirectedLinks"]} | {rate["aggregateDatagramsPerSecond"]:.1f} | {rate["aggregateBzrDatagramKbps"]:.1f} |')
    lines += ["", "| Client | Peak AI | Peak scrap | New scrap observed | CPU cores | Simulation/wall | Probe p95 ms |", "|---|---:|---:|---:|---:|---:|---:|"]
    for client, value in report["clients"].items():
        lines.append(f'| {client} | {value["peakAI"]} | {value["peakScrap"]} | {value["newScrapObserved"]} | {value["cpuEquivalentCores"]:.2f} | {value["simulationSecondsPerWallSecond"]:.3f} | {value["probeCommandMsP95"]:.1f} |')
    lines += ["", *["- " + limit for limit in report["limitations"]]]
    (args.run / "battle-network-report.md").write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(json.dumps({"report": str(args.run / "battle-network-report.md"), "host": report["hostFinalMeasured"], "rates": {p: {k:v for k,v in r.items() if k != "links"} for p,r in report["rates"].items()}}, indent=2))
