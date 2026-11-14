# Stock bug: strategic-AI scrap scan writes past a remote scavenger's NetProcess

Date: 2026-10-14. Branch: `agent/fix-scav-netprocess-overwrite`.
Evidence: crash-dump investigation `analysis_20261014/REPORT.md` (kept outside the repository with the dumps and debugger transcripts).

**Status: patch implemented and unit-tested; live validation pending.** The causal chain is reconstructed from four intact dumps, not from a first-write capture. A pageheap or hardware-watchpoint capture of the write is the remaining confirmation.

## Symptom

`0xC0000374` (`STATUS_HEAP_CORRUPTION`) minutes into a co-op session on the host, when a team runs an AIP and a guest owns scavengers. The fatal stack is whichever allocation or free first notices the damage (Ogre, Lua, EXU, game destruction); it is not the writer. All seven gameplay dumps show `0xBF800000` (`-1.0f`) in the second dword of a damaged heap entry header.

## Mechanism (GOG Redux 2.2.301, SHA-256 `8d71f56c...3377413`)

| Step | Address | What happens |
| --- | --- | --- |
| 1 | `AI_Team_Compute_Other` `0x006A3870` | Enumerates GameObjects, keeps class signature `SCAV` whose team matches the scanned team. |
| 2 | `0x006A3950` | `0x0045BDF0` returns the AI process at `GameObject+0xFC`. Only a null test follows. |
| 3 | `0x006A3961` (`E8 4A 07 F2 FF`) | Calls `ScavengerProcess::GetScrapPosition` (`0x005C40B0`) with ECX = that process, without checking its type. |
| 4 | `0x005C40B0` | If `[this+0x1C] == 4` and `[this+0x58] != 0` it copies a position; otherwise it loads `-1.0f` (`0x008A2EFC`) and stores it at **`this+0x3C`** (`0x005C4126`), returning `this+0x38`. |
| 5 | remote scavenger | Its process is a `NetProcess` (vtable `0x00884BB4`, RTTI `.?AVNetProcess@@`), a **0x18-byte** allocation. `this+0x3C` is the second dword of the next heap entry's header. |

Intact chains in four dumps (owner Scavenger vtable `0x00886FE8`, `owner+0xFC` -> NetProcess, `NetProcess+0x3C` = the corrupt header word holding `BF800000`) are tabulated in the report.

## The guard

`Scavenger Process Scrap Position Guard` redirects only the call at `0x006A3961`; the callee, and every other caller (all local `ScavengerProcess` code), are untouched.

* **Accept** a process whose first word (vtable) is one of the three ScavengerProcess-family vtables, and forward to the stock function. The set comes from a walk of the shipping image's MSVC RTTI class hierarchy descriptors: every concrete class with `.?AVScavengerProcess@@` in its base list.

  | Class | Vtable |
  | --- | --- |
  | `ScavengerProcess` | `0x008871D8` |
  | `ScavengerFriend` | `0x00887190` |
  | `ScavengerEnemy` | `0x008871B4` |

  The other `Scav*` RTTI names (`ScavGotoDrop/Repair/Scrap`) are tasks (`AiTask` family), not processes. The base class is accepted because it is a legitimate instantiable type; an object already in destruction presents the `AiProcess`/`SObject` vtable and is rejected.
* **Reject** `NetProcess`, null, unreadable memory (SEH-guarded read of the first word), and any other vtable. The stock function is not called, nothing is written, and a pointer to a static read-only `{0, -1, 0}` is returned.

### Why returning a y = -1 vector is safe for this caller

The caller copies `x,y,z` from the returned pointer into locals and promotes the scavenger's contribution only when `y > 0.0f` (`comiss` against `0x008A2498`, which holds `0.0f`; `jbe` skips at `0x006A397C`). `-1.0f` is also what stock `GetScrapPosition` returns for "no scrap position known", so a rejected process takes the existing no-scrap path and the loop continues with the next object. The caller never writes through the returned pointer, so const storage is fine. Skipping the scavenger therefore cannot change the team map for local scavengers and only withholds a contribution the remote scavenger could never have produced locally.

## Fail-closed binding

* Gog-only (`"platforms": ["gog"]`). Steam addresses are not qualified.
* Site: `scripts/patches.json` patch with a 25-byte pattern covering the pre-call `mov ecx,[ebp-0x24]` and the post-call copy-out, `require_unique`, fallback `0x006A3962` (only taken when the same pattern is present at the fallback).
* The patcher resolves the existing call's target and compares it with the pinned `engine_addresses` row `ScavengerProcessGetScrapPosition` (`0x005C40B0`, with a 25-byte prologue guard). Mismatch leaves the stock call.
* Each of the three vtables (`engine_addresses` data rows) must carry the expected RTTI type name behind `vtable[-1]`, read under SEH. Any miss leaves the stock call; an empty or duplicate-entry vtable set is refused.
* Rejection logs `[SCAVGUARD]` (first eight occurrences) with the process pointer, vtable and RTTI name; arming logs the resolved addresses.

## Switch

`[Fixes] ScavengerNetProcessGuard` (default 1). Env alias to disable: `OPENSHIM_DISABLE_SCAVENGER_NETPROCESS_GUARD` / `BZR_DISABLE_SCAVENGER_NETPROCESS_GUARD`. Unlike the simulation fixes it does not stand down in network games, because that is where the bug occurs. When disabled the hook forwards every process to the stock function.

## Tests

* `tests/scavenger_process_guard_tests.cpp` (CTest `scavenger_process_guard_tests`): family accepted, NetProcess and foreign vtables rejected, null/unreadable rejected, unusable configuration fails closed, and a rejected process allocation and its neighbour are byte-identical afterwards.
* `tests/patch_registration_tests.cpp` covers the `patches.json` / `patches.h` registration; `scripts/run_ini_tests.ps1` covers the ini key.

## Live validation still needed

1. Co-op host, team with an AIP, guest owns a scavenger: confirm `[SCAVGUARD] armed` and rejection lines, and no `0xC0000374`.
2. Control with `ScavengerNetProcessGuard = 0` under pageheap: expect the original corruption (first-write capture at `0x005C4126`).
3. Local scavengers across several teams, plus remote-object destruction: unchanged AI scrap behaviour, no `[SCAVGUARD]` rejection lines for local ones.
