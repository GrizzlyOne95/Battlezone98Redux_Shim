"""Replay a co-op run's relay trace through Redux's BZRNet P2P accept rule.

The receive path (0x0075D800, GOG 2.2.301) accepts a data packet only when its
sequence stamp equals the peer's expected sequence (peer+0x84) and advances the
expectation on reliable packets alone. Replaying every relayed datagram through
that rule predicts each link's native "Dropping Packet Type 0" count; matching
the clients' own logs confirms the model. The script also measures how long the
sender held each reliable message back before its first transmission: an
unreliable packet stamped S proves every reliable message below S was already
queued, so a later first transmission is time the stock backlog gate (peer+0x1A)
kept it off the wire while the receiver dropped everything stamped after it.

Usage: python p2p_reliable_backlog_replay.py <run dir containing relay-trace.jsonl>
"""
import collections
import json
import os
import re
import statistics
import sys


def load_ports(run):
    """Client index for each local UDP port, from 'P2P Socket Opened ... port N'."""
    ports = {}
    for c in range(8):
        path = os.path.join(run, f"client{c}", "logs", "BZLogger.txt")
        if not os.path.exists(path):
            continue
        with open(path, encoding="utf-8", errors="replace") as f:
            for line in f:
                m = re.search(r"P2P Socket Opened With .* port (\d+)", line)
                if m:
                    ports[m.group(1)] = f"c{c}"
    return ports


def load_logged_drops(run):
    """Native drop counts per (receiving client, sending player id suffix)."""
    logged = collections.Counter()
    for c in range(8):
        path = os.path.join(run, f"client{c}", "logs", "BZLogger.txt")
        if not os.path.exists(path):
            continue
        with open(path, encoding="utf-8", errors="replace") as f:
            for line in f:
                m = re.search(r"Dropping Packet Type 0 For Client (S\d+)", line)
                if m:
                    logged[(f"c{c}", m.group(1))] += 1
    return logged


def replay(packets):
    expected = None
    reliable_drops = unreliable_drops = 0
    for r in packets:
        t = r["transport"]
        if t["kindNibble"] != 0:
            continue
        seq = t["seqA"]
        reliable = bool(int(t["flagsByte"], 16) & 0x80)
        if expected is None:
            expected = seq
        if seq == expected:
            if reliable:
                expected = seq + 1
        elif reliable:
            reliable_drops += 1
        else:
            unreliable_drops += 1
    return reliable_drops, unreliable_drops


def holds(packets):
    first_tx, queued_by = {}, {}
    high = -1
    for r in packets:
        t = r["transport"]
        if t["kindNibble"] != 0:
            continue
        seq, ts = t["seqA"], r["tsUnixMs"]
        if int(t["flagsByte"], 16) & 0x80:
            first_tx.setdefault(seq, ts)
        else:
            for k in range(high + 1, seq):
                queued_by.setdefault(k, ts)
            high = max(high, seq - 1)
    late = sorted(first_tx[k] - queued_by[k] for k in first_tx
                  if k in queued_by and first_tx[k] > queued_by[k])
    return len(first_tx), late


def main():
    run = sys.argv[1]
    with open(os.path.join(run, "relay-trace.jsonl"), encoding="utf-8") as f:
        rows = [json.loads(line) for line in f]
    rows = [r for r in rows if "transport" in r and r.get("disposition", "forwarded") == "forwarded"]
    streams = collections.defaultdict(list)
    for r in rows:
        streams[(r["source"].rsplit(":", 1)[1], r["target"].rsplit(":", 1)[1])].append(r)
    ports = load_ports(run)
    name = lambda p: ports.get(p, p)

    print("link      predicted drops (rel/unrel)   reliable held: count  median   p90    max")
    for (src, dst), packets in sorted(streams.items(), key=lambda kv: (name(kv[0][0]), name(kv[0][1]))):
        rd, ud = replay(packets)
        total, late = holds(packets)
        if late:
            held = (f"{len(late):5d}/{total:<5d} {statistics.median(late) / 1000:6.2f}s "
                    f"{late[int(len(late) * 0.9)] / 1000:6.2f}s {late[-1] / 1000:6.2f}s")
        else:
            held = f"{0:5d}/{total:<5d}"
        print(f"{name(src)}->{name(dst)}  {rd + ud:6d} ({rd:4d}/{ud:5d})            {held}")

    logged = load_logged_drops(run)
    if logged:
        print("\nnative logged drops (receiver <- sender id):")
        for (client, peer), n in sorted(logged.items()):
            print(f"  {client} <- {peer}: {n}")


if __name__ == "__main__":
    main()
