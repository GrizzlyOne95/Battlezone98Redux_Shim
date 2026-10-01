"""Capture exact GOG weapon-presentation sites from an explicit Windows PID.

Byte capture uses only PROCESS_QUERY_INFORMATION/PROCESS_VM_READ. Optional
Frida observation installs temporary instrumentation, forwards all calls, and
never creates effects, calls engine functions or enables the native candidate.
Reports contain private instruction bytes; keep them out of the public repo.
"""
from __future__ import annotations

import argparse
from datetime import datetime, timezone
import hashlib
import json
import math
from pathlib import Path
import sys
import threading
import time


SITE_NAMES = frozenset((
    "WeaponCtor", "WeaponDtor", "SimulationPass", "SetWeapon", "ModelPose",
    "OrdnanceFactory", "PopScope", "RawGet", "RenderFind", "RenderUpdate",
    "RenderDetach", "CannonShotCall", "WeaponClassPopCall", "CraftClassPopCall",
))
PREFIX = "WeaponPresentation::"


def catalog_rows(catalog):
    rows = [row for row in catalog["resolves"] if row["name"].startswith(PREFIX)]
    names = [row["name"][len(PREFIX):] for row in rows]
    if len(names) != len(SITE_NAMES) or set(names) != SITE_NAMES:
        raise ValueError("Incomplete or duplicate weapon-presentation catalog")
    for row in rows:
        if row.get("mode") != "address" or row.get("require_unique") is not True:
            raise ValueError(f"{row['name']}: requires a unique address signature")
        if not bytes.fromhex(row["pattern"]):
            raise ValueError(f"{row['name']}: empty signature")
    return rows


def verify_sites(static, rows, sections, read_exact, image_base):
    """Pure validation seam: sections and reader must come from the same PID.

    Compare every full signature, instruction steal and original call target.
    Do not accept a JMP trampoline as proof of the underlying stock bytes.
    """
    if image_base != int(static["image_base"], 0) or image_base != 0x400000:
        raise ValueError("Unexpected live image base")
    if set(static["sites"]) != SITE_NAMES:
        raise ValueError("Incomplete static proof")
    catalog_rows({"resolves": rows})
    result = {"sites": {}, "calls": {}, "steals": {}}
    for row in rows:
        name = row["name"][len(PREFIX):]
        site = int(static["sites"][name], 0)
        if site != int(row["fallback"], 0):
            raise ValueError(f"{name}: static/catalog address disagreement")
        pattern = bytes.fromhex(row["pattern"])
        hits = []
        for base, data in sections:
            cursor = 0
            while True:
                cursor = data.find(pattern, cursor)
                if cursor < 0:
                    break
                hits.append(base + cursor)
                cursor += 1
        if len(hits) != 1 or hits[0] + row["offset"] != site:
            raise ValueError(f"{name}: live signature missing, duplicated or moved")
        start = site - row["offset"]
        actual = read_exact(start, len(pattern))
        if actual != pattern:
            raise ValueError(f"{name}: live signature changed during capture")
        result["sites"][name] = {
            "site": hex(site), "signature_start": hex(start),
            "bytes": actual.hex(" "), "match_count": len(hits),
        }
    for name, proof in static["call_targets"].items():
        site = int(proof["site"], 0)
        actual = read_exact(site, 5)
        if len(actual) != 5 or actual[0] != 0xe8:
            raise ValueError(f"{name}: live call unreadable or patched")
        target = site + 5 + int.from_bytes(actual[1:], "little", signed=True)
        if actual != bytes.fromhex(proof["bytes"]) or target != int(proof["target"], 0):
            raise ValueError(f"{name}: live call target disagreement")
        result["calls"][name] = {"site": hex(site), "bytes": actual.hex(" "), "target": hex(target)}
    for name, proof in static["steals"].items():
        actual = read_exact(int(proof["site"], 0), proof["size"])
        if actual != bytes.fromhex(proof["bytes"]):
            raise ValueError(f"{name}: stolen instruction bytes disagree")
        result["steals"][name] = {"site": proof["site"], "size": proof["size"], "bytes": actual.hex(" ")}
    if len(result["calls"]) != 3 or len(result["steals"]) != 5:
        raise ValueError("Incomplete call/steal proof")
    return result


def trace_config(capture, pid, module_path, max_events, model_ids):
    if not 1 <= max_events <= 20000:
        raise ValueError("Trace event limit must be 1..20000")
    if len(model_ids) > 16 or any(not 1 <= len(n) <= 8 or
            any(ord(c) < 0x20 or ord(c) > 0x7e for c in n) for n in model_ids):
        raise ValueError("Use at most sixteen exact printable 1..8-byte mesh IDs")
    return {
        "pid": pid, "module_path": module_path, "image_base": "0x400000",
        "sites": {name: row["site"] for name, row in capture["sites"].items()},
        "guards": [{"address": row["signature_start"], "bytes": row["bytes"]}
                   for row in capture["sites"].values()],
        "max_events": max_events, "model_ids": model_ids,
    }


def observe(pid, config, seconds, events_path, check_process):
    import frida

    failures = []
    counters = {"events_written": 0, "error_count": 0}
    detached = threading.Event()
    lock = threading.Lock()
    session = None
    script = None
    summary = None
    with events_path.open("x", encoding="utf-8") as output:
        def fail(reason):
            counters["error_count"] += 1
            if len(failures) < 32:
                failures.append(reason)

        def on_message(message, _data):
            with lock:
                try:
                    if message["type"] == "send":
                        payload = message["payload"]
                        if payload.get("type") != "events" or not isinstance(payload.get("events"), list):
                            fail("Unexpected trace message")
                            return
                        for event in payload["events"]:
                            if counters["events_written"] >= config["max_events"]:
                                fail("Host event limit exceeded")
                                return
                            output.write(json.dumps(event, allow_nan=False) + "\n")
                            counters["events_written"] += 1
                        output.flush()
                    else:
                        fail(message.get("description", str(message)))
                except Exception as error:
                    fail(f"Trace write failed: {error}")

        try:
            check_process()
            session = frida.attach(pid)  # explicit PID only; never spawn/resume/kill
            session.on("detached", lambda *_args: detached.set())
            source = Path(__file__).with_name("probe_weapon_presentation.js").read_bytes()
            script = session.create_script(source.decode("utf-8"))
            script.on("message", on_message)
            script.load()
            script.exports_sync.start(config)  # rechecks all guards before the first listener
            deadline = time.monotonic() + seconds
            while time.monotonic() < deadline and not detached.is_set():
                check_process()
                time.sleep(min(0.25, max(0, deadline - time.monotonic())))
            if detached.is_set():
                fail("Process/session detached before trace completion")
            else:
                summary = script.exports_sync.stop()
        finally:
            try:
                if script is not None and not detached.is_set():
                    script.unload()
            finally:
                if session is not None and not detached.is_set():
                    session.detach()
    if summary is None:
        summary = {"complete": False}
    summary.update(counters)
    summary.update({"frida_version": frida.__version__, "errors": failures,
                    "agent_sha256": hashlib.sha256(source).hexdigest(),
                    "evidence_kind": "instrumented_observation", "activation_qualified": False})
    if summary.get("events_emitted") != counters["events_written"]:
        fail("Trace delivery count disagrees with observer count")
        summary.update(counters)
    summary["complete"] = bool(summary.get("complete") and not counters["error_count"])
    return summary


def capture(args, report):
    if sys.platform != "win32":
        raise RuntimeError("Live capture requires Windows; no live evidence was collected")
    import pefile
    from capture_runtime_layout import (
        PROCESS_QUERY_INFORMATION, PROCESS_VM_READ, enumerate_modules,
        find_process_by_pid, kernel32, read_process_memory,
    )
    from qualify_weapon_presentation_static import qualify

    proc = find_process_by_pid(args.pid)
    started = proc.create_time()
    executable = Path(proc.exe()).resolve()
    if proc.name().lower() != "battlezone98redux.exe" or executable.name.lower() != "battlezone98redux.exe":
        raise ValueError("PID is not the stock Redux executable")
    modules = [m for m in enumerate_modules(args.pid) if Path(m.path).resolve() == executable]
    if len(modules) != 1:
        raise ValueError("Cannot uniquely identify the process's executable module")
    module = modules[0]
    static = qualify(executable, args.catalog)
    pe = pefile.PE(str(executable), fast_load=True)
    try:
        if module.size != pe.OPTIONAL_HEADER.SizeOfImage:
            raise ValueError("Live module size disagrees with the exact executable")
        executable_ranges = [(module.base + s.VirtualAddress,
                              max(s.Misc_VirtualSize, s.SizeOfRawData))
                             for s in pe.sections if s.Characteristics & 0x20000000]
    finally:
        pe.close()
    report.update({"process": {"pid": args.pid, "exe": str(executable), "create_time": started,
                               "age_at_capture_seconds": time.time() - started,
                               "module_base": hex(module.base), "module_size": module.size},
                   "static_proof": static, "settle_seconds": args.settle_seconds})

    def check_process():
        # psutil protects against PID reuse; compare path and timestamp too.
        if not proc.is_running() or proc.create_time() != started or Path(proc.exe()).resolve() != executable:
            raise RuntimeError("Target exited or its process identity changed")

    handle = kernel32.OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, False, args.pid)
    if not handle:
        raise OSError("OpenProcess for read-only capture failed")
    try:
        def read_exact(address, size):
            data, error = read_process_memory(handle, address, size)
            if error or len(data) != size:
                raise ValueError(error or f"Partial live read at {address:#x}")
            return data

        rows = catalog_rows(json.loads(args.catalog.read_text(encoding="utf-8")))
        def snapshot():
            check_process()
            sections = [(base, read_exact(base, size)) for base, size in executable_ranges]
            verified = verify_sites(static, rows, sections, read_exact, module.base)
            check_process()
            return verified

        report["initial_capture"] = snapshot()
        time.sleep(args.settle_seconds)
        report["settled_capture"] = snapshot()
        if report["initial_capture"] != report["settled_capture"]:
            raise ValueError("Live target bytes did not remain stable across settling")
        report["byte_verification_passed"] = True
        if args.trace_seconds:
            report["trace"] = observe(args.pid, trace_config(report["settled_capture"], args.pid,
                str(executable), args.max_events, args.model_id), args.trace_seconds,
                args.output.with_suffix(".events.jsonl"), check_process)
            report["post_trace_capture"] = snapshot()
            if report["post_trace_capture"] != report["settled_capture"]:
                raise ValueError("Stock target bytes were not restored after observation")
            report["trace"]["restoration_verified"] = True
            if not report["trace"]["complete"]:
                raise RuntimeError("Trace incomplete; inspect its cap/error counters")
    finally:
        kernel32.CloseHandle(handle)


def bounded_float(minimum, maximum):
    def parse(value):
        number = float(value)
        if not math.isfinite(number) or not minimum <= number <= maximum:
            raise argparse.ArgumentTypeError(f"Use a finite value in {minimum}..{maximum}")
        return number
    return parse


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--pid", type=int, required=True)
    parser.add_argument("--catalog", type=Path, default=Path(__file__).resolve().parents[1] / "scripts/patches.json")
    parser.add_argument("--output", type=Path, required=True, help="New private report path; never overwrite evidence")
    parser.add_argument("--settle-seconds", type=bounded_float(0.5, 30), default=2.0)
    parser.add_argument("--trace-seconds", type=bounded_float(0, 300), default=0.0)
    parser.add_argument("--max-events", type=int, default=4096)
    parser.add_argument("--model-id", action="append", default=[], help="Exact mesh ID filter for model-write observations")
    args = parser.parse_args()
    if args.pid <= 0:
        parser.error("Use an explicit positive PID")
    # Validate trace bounds before attaching to anything.
    try:
        trace_config({"sites": {}}, args.pid, "", args.max_events, args.model_id)
    except ValueError as error:
        parser.error(str(error))
    args.output.parent.mkdir(parents=True, exist_ok=True)
    report = {"evidence_kind": "live_byte_capture", "backend": "Win32 ReadProcessMemory",
              "captured_at": datetime.now(timezone.utc).isoformat(), "command": sys.argv, "python_version": sys.version,
              "byte_verification_passed": False, "activation_qualified": False,
              "behavior_qualified": False, "trace": None}
    # Reserve the report before capture. Refuse accidental replacement of prior evidence.
    with args.output.open("x", encoding="utf-8") as output:
        try:
            capture(args, report)
            result = 0
        except KeyboardInterrupt:
            report["error"] = "KeyboardInterrupt: capture interrupted; evidence is incomplete"
            result = 130
        except Exception as error:
            report["error"] = f"{type(error).__name__}: {error}"
            result = 1
        output.write(json.dumps(report, indent=2, allow_nan=False) + "\n")
    print("Live byte verification passed; in-game qualification still required" if result == 0 else
          f"Capture rejected: {report['error']}")
    return result


if __name__ == "__main__":
    raise SystemExit(main())
