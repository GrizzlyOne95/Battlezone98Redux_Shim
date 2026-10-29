#!/usr/bin/env python3
"""Execute the exact released P2P send wrapper against an isolated ABI sink.

The sink records the virtual call and returns a fixture boolean; it is NOT a
native gameplay transport. Separately run direct_lan_peer_bridge_tests for
the compiled bridge/socket/native-callback checks. No game process is started.
Requires the existing pefile/Unicorn RE environment; output stays ignored.
"""
import argparse
import hashlib
import json
from pathlib import Path
import random
import struct

import pefile
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX, UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP, UC_X86_REG_ESP, UC_X86_REG_EIP

BASELINE = "8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413"
WRAPPER, DIAGNOSTICS = 0x007592D0, 0x00917F6C
STACK, DATA, STOP = 0x10000000, 0x11000000, 0x12000000


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--exe", type=Path, required=True)
    parser.add_argument("--cases", type=int, default=1000)
    parser.add_argument("--output", type=Path, default=Path(__file__).resolve().parent / "workshop/direct_lan_backend/peer_oracle.json")
    args = parser.parse_args()
    if not 1 <= args.cases <= 5000:
        parser.error("cases must be 1..5000")
    if hashlib.sha256(args.exe.read_bytes()).hexdigest() != BASELINE:
        parser.error("Executable differs from released GOG baseline")
    pe = pefile.PE(str(args.exe))
    machine = Uc(UC_ARCH_X86, UC_MODE_32)
    machine.mem_map(pe.OPTIONAL_HEADER.ImageBase, (pe.OPTIONAL_HEADER.SizeOfImage + 4095) & ~4095)
    machine.mem_write(pe.OPTIONAL_HEADER.ImageBase, pe.get_memory_mapped_image())
    for address in (0, STACK, DATA, STOP):
        machine.mem_map(address, 65536)
    assert machine.mem_read(DIAGNOSTICS, 4) == bytes(4), "only log-off path qualified"
    pack = lambda *values: struct.pack("<" + "I" * len(values), *values)
    read = lambda at, n: struct.unpack("<" + "I" * n, machine.mem_read(at, 4 * n))
    object_address, table, target, payload, callback = DATA, DATA + 256, DATA + 512, DATA + 1024, STOP + 256
    machine.mem_write(object_address, pack(table))
    machine.mem_write(table + 12, pack(callback))
    # Only the test sink is generated code: mov al,1; ret 16.
    machine.mem_write(callback, bytes.fromhex("b0 01 c2 10 00"))
    observed = []

    def hook(uc, address, size, _):
        del size
        if address == callback:
            observed.append((uc.reg_read(UC_X86_REG_ECX), read(uc.reg_read(UC_X86_REG_ESP) + 4, 4)))

    machine.hook_add(UC_HOOK_CODE, hook, begin=callback, end=callback)
    randomizer = random.Random(301650)
    for _ in range(args.cases):
        count, reliable = randomizer.randrange(1153), randomizer.choice((0, 1, 9))
        result = randomizer.randrange(2)
        machine.mem_write(callback + 1, bytes([result]))
        machine.ctl_remove_cache(callback, callback + 5)
        previous_count, previous_bytes = randomizer.getrandbits(32), randomizer.getrandbits(32)
        machine.mem_write(object_address + 0x1C, pack(previous_count, previous_bytes))
        machine.mem_write(0, pack(0xFEE1DEAD))
        sp = STACK + 32768
        machine.mem_write(sp, pack(STOP, target, payload, count, reliable))
        saved = {UC_X86_REG_EBX: 0x11223344, UC_X86_REG_ESI: 0x88776655, UC_X86_REG_EDI: 0xF1F2F3F4, UC_X86_REG_EBP: 0x12345678}
        for register, value in saved.items():
            machine.reg_write(register, value)
        machine.reg_write(UC_X86_REG_ECX, object_address)
        machine.reg_write(UC_X86_REG_ESP, sp)
        observed.clear()
        machine.emu_start(WRAPPER, STOP, count=256)
        assert machine.reg_read(UC_X86_REG_EIP) == STOP
        assert machine.reg_read(UC_X86_REG_ESP) == sp + 20
        assert machine.reg_read(UC_X86_REG_EAX) & 255 == result
        assert read(0, 1) == (0xFEE1DEAD,), "SEH chain restored"
        assert observed == [(object_address, (target, payload, count, reliable))]
        assert read(object_address + 0x1C, 2) == ((previous_count + 1) & 0xFFFFFFFF, (previous_bytes + count) & 0xFFFFFFFF)
        for register, value in saved.items():
            assert machine.reg_read(register) == value
    report = {
        "build": "Redux 2.2.301 GOG", "sha256": BASELINE, "cases": args.cases,
        "original_wrapper_va": hex(WRAPPER), "path": "diagnostics off; virtual send callback returns fixture AL=0 or 1",
        "proven": ["ECX object and four stack arguments to vtable +0C", "AL propagation and ret16", "counter offsets 1C/20", "SEH chain and callee-save restoration"],
        "not_proven": ["native gameplay", "native callback registration/tree layout", "complete backend lifetime"],
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(f"Passed {args.cases} original P2P send-wrapper ABI/counter cases; virtual sink is a fixture")
    print(args.output)


if __name__ == "__main__":
    main()
