#!/usr/bin/env python3
"""Compare the adapter with bounded released-code identity operations.

Requires pefile/unicorn in the existing RE Python environment. The exact GOG
image is hash checked, mapped as data into an x86 emulator, and only the named
identity leaves are executed. The optional Win32 owner-predicate test uses a
private mapping in its own standalone process, without executing game startup.
No game process, account provider, native hook or deployment is involved.
Generated reports remain in the ignored workshop directory.
"""
import argparse
import hashlib
import json
from pathlib import Path
import random
import struct
import subprocess
import sys

import pefile
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX, UC_X86_REG_EDX, UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP, UC_X86_REG_ESP, UC_X86_REG_EIP

BASELINE = "8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413"
# Research VAs for this image only; never installed as shipping patch sites.
INVALID, COPY, EQUAL, VALID, LOCAL = 0x73A6B0, 0x73A740, 0x56F780, 0x73A900, 0x74B670
LESS = 0x574A30
GLOBAL_LOCAL = 0x260B1C8
STACK, DATA, STOP = 0x10000000, 0x11000000, 0x12000000


def words(values):
    return struct.pack("<" + "I" * len(values), *values)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--exe", type=Path, required=True)
    parser.add_argument("--adapter-test", type=Path, required=True)
    parser.add_argument("--cases", type=int, default=1000)
    parser.add_argument("--output", type=Path, default=Path(__file__).resolve().parent / "workshop/direct_lan_backend/identity_oracle.json")
    args = parser.parse_args()
    if not 1 <= args.cases <= 5000:
        parser.error("cases must be 1..5000")
    digest = hashlib.sha256(args.exe.read_bytes()).hexdigest()
    if digest != BASELINE:
        parser.error("Executable differs from the released GOG 2.2.301 baseline")
    pe = pefile.PE(str(args.exe))
    image = pe.get_memory_mapped_image()
    machine = Uc(UC_ARCH_X86, UC_MODE_32)
    machine.mem_map(pe.OPTIONAL_HEADER.ImageBase, (pe.OPTIONAL_HEADER.SizeOfImage + 4095) & ~4095)
    machine.mem_write(pe.OPTIONAL_HEADER.ImageBase, image)
    for address in (STACK, DATA, STOP):
        machine.mem_map(address, 65536)
    saved = {UC_X86_REG_EBX: 0x12345678, UC_X86_REG_ESI: 0xA1B2C3D4, UC_X86_REG_EDI: 0x87654321, UC_X86_REG_EBP: 0xABCDEF12}
    calls = 0

    def call(va, ecx, *arguments):
        nonlocal calls
        sp = STACK + 32768
        machine.mem_write(sp, words((STOP, *arguments)))
        for register, value in saved.items():
            machine.reg_write(register, value)
        machine.reg_write(UC_X86_REG_EAX, 0xA5A5A500)
        machine.reg_write(UC_X86_REG_EDX, 0x5A5A5A5A)
        machine.reg_write(UC_X86_REG_ECX, ecx)
        machine.reg_write(UC_X86_REG_ESP, sp)
        machine.emu_start(va, STOP, count=256)
        assert machine.reg_read(UC_X86_REG_EIP) == STOP, f"unbounded/unsupported code path at {va:#x}"
        assert machine.reg_read(UC_X86_REG_ESP) == sp + 4 * (len(arguments) + 1), f"callee stack cleanup at {va:#x}"
        for register, value in saved.items():
            assert machine.reg_read(register) == value, f"callee-save register at {va:#x}"
        calls += 1
        return machine.reg_read(UC_X86_REG_EAX)

    randomizer = random.Random(301650)
    rows = []
    for index in range(args.cases):
        a = [randomizer.choice((0, 1, 2, 3, 99, 0xFFFFFFFF)), *(randomizer.getrandbits(32) for _ in range(3))]
        if index % 3 == 0:
            a[0] = 3
        if index % 7 == 0:
            a[2:] = [0, 0]
        b = a.copy()
        b[1] ^= 0xFFFFFFFF  # equality must ignore offset 4
        if index % 2:
            b[randomizer.choice((0, 2, 3))] ^= 1
        machine.mem_write(DATA, words(a))
        machine.mem_write(DATA + 32, words(b))
        machine.mem_write(DATA + 64, bytes([0xA5]) * 16)
        assert call(COPY, DATA + 64, DATA) == DATA + 64
        copied = list(struct.unpack("<4I", machine.mem_read(DATA + 64, 16)))
        assert copied == [a[0], 0xA5A5A5A5, a[2], a[3]]
        equality = call(EQUAL, DATA, DATA + 32) & 255
        less = call(LESS, DATA, DATA + 32) & 255
        # Generic provider kinds may have extra validation. The adapter emits
        # kind 3 only; check that actual native path, not a guessed int return.
        direct = bool(call(VALID, DATA) & 255) if a[0] == 3 else False
        machine.mem_write(GLOBAL_LOCAL, words(a))
        machine.mem_write(DATA + 64, bytes([0xA5]) * 16)
        assert call(LOCAL, DATA + 128, DATA + 64) == DATA + 64
        assert list(struct.unpack("<4I", machine.mem_read(DATA + 64, 16))) == copied
        machine.mem_write(DATA + 64, bytes([0xA5]) * 16)
        assert call(INVALID, DATA + 64) == DATA + 64
        assert list(struct.unpack("<4I", machine.mem_read(DATA + 64, 16))) == [0, 0xA5A5A5A5, 0, 0]
        rows.append(" ".join(map(str, (*a, *b, equality, int(direct), less))))
    command = [str(args.adapter_test.resolve()), "--identity-oracle"]
    subprocess.run(command, input="\n".join(rows) + "\n", text=True, check=True)
    native_owner_predicates = False
    if sys.platform == "win32":
        subprocess.run([str(args.adapter_test.resolve()), "--released-exe", str(args.exe.resolve())], check=True)
        native_owner_predicates = True
    report = {
        "build": "Battlezone 98 Redux 2.2.301 GOG", "sha256": digest,
        "evidence": "released leaf execution in x86 emulation plus compiled adapter comparison; not game acceptance",
        "cases": args.cases, "emulated_calls": calls, "callee_cleanup_and_saved_registers": "passed",
        "native_win32_owner_predicates_against_compiled_adapter": native_owner_predicates,
        "qualified_subset": ["invalid/copy preserving offset 4", "equality and ordering ignoring offset 4", "kind 3 validity AL", "local ID hidden output"],
        "not_qualified": ["all identity consumers", "full lobby ABI", "provider lifetimes/callbacks", "native peers/gameplay", "Steam/Proton/Wine"],
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(f"Passed {args.cases} released-code differential cases, {calls} emulated calls; native owner predicates={native_owner_predicates}")
    print(args.output)


if __name__ == "__main__":
    main()
