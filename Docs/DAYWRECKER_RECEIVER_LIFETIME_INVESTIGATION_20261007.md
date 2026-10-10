# Daywrecker duplicate detonation: receiver lifetime investigation

Date: 2026-10-07. Branch: `agent/daywrecker-lifecycle-capture`.

**Outcome:** stale-state reconstruction remains the strongest specific candidate,
not a proven explanation of the reported match. The tester reports that the
launcher does not see the duplicate; only other players do. The earlier
[qualification](MP_EXPLOSIVE_AUTHORITY_QUALIFICATION.md#redux-receiver-replay-findings)
already identified this receiver path. This pass independently checked the
Armory launch chain, reviewed limitations in the existing trace, and prepared a
more discriminating standalone capture. No gameplay patch or deployment.

## What is established

Evidence is Windows GOG Redux 2.2.301, SHA256
`8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413`.
The install and both BZRCoop instance executables matched that hash.

| Finding | Grade | Released-build evidence |
| --- | --- | --- |
| Detonation is already guarded within one lifetime. | PROVEN static | Constructor `004b0420` resets complete-object byte `+230`; Simulate `004b0460` and adjusted-this Explode `004b07d0` share that byte and set it before effects. |
| The Armory's weapon builds a GameObject, rather than sending through the separate ordnance subsystem. | PROVEN static | Armory FinishBuild `004732c0` sets ObjectLobber target/class and triggers virtual `+8`; RTTI ObjectLobber vtable `00884bd8`, Simulate slot `+18`, points to `00582190`, which calls `004e1190`. |
| The launch path initializes airborne flags before ownership publication and first simulation. | PROVEN static | `00582190` sets PowerUp vehicle flags `0xc`, assigns its command, calls SetLocal `004b8460` in a network game, sets velocity, then invokes object Simulate `+3c`. No owner predicate immediately surrounds Build inside this body; outer dispatch authority remains unresolved. |
| A remote dynamic object can retire without a deleted-ID timestamp from this removal path. | PROVEN static | Daywrecker calls removal virtual `+10`; vtable target `004dae70` uses adjusted `this`, calls `004b7ab0`, and dispatches cleanup. `004b7ab0` calls deleted-ID recorder `004b7bd0` for type 1, or type 2 with ID below `10000`, but returns for remote dynamic IDs. Destructor `004b79f0` removes the ownership-map entry. |
| Missing IDs can be rebuilt from received state. | PROVEN static | Ordinary reader `004b8590` permits Create `004b9350` after a missing-ID lookup when its deleted-ID/time rejection does not apply. Permanent reader `004b8fa0` has a separate path to Create. Create installs the wire ID and calls SetRemote `004b7f20`; a new Daywrecker construction resets the byte. |
| State unpack restores deployment flags, not this consumed byte. | PROVEN static | PowerUp unpack `005aacf0` reconstructs vehicle flags. This supports a second first-time detonation in a new lifetime, rather than bypassing the existing one-shot test. |
| Receiver reconstruction caused the player's duplicate blast. | UNKNOWN | No capture of the reported event yet. Receiver-only visibility is consistent with the hypothesis, but does not exclude an extra receiver-local launch or other cause. |

Reference corroboration comes from private sibling `Battlezone_Source`, BZ1 1.5
named exports: `0047eff5_Armory_FinishBuild.c`,
`005327ca_ObjectLobber_Simulate.c`, and the DayWrecker functions. Those files
establish reference semantics, not released Redux behavior. Released evidence
uses the ignored GOG corpus under
`reverse_engineering/repo_corpora/bzr_gog_best_effort/ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps/`,
the current Ghidra MCP project `/battlezone98redux.exe-007c64`, and Rizin
disassembly/vtable/entry-byte reads of the hashed installed executable.

## Candidate sequence and fix boundary

1. Launcher assigns network ID X and launches one bomb.
2. Receiver detonates its remote copy X, consumes that lifetime, and removes it.
3. Late ordinary state, or a permanent-state record, reaches a missing-ID
   reconstruction path on the receiver.
4. Create constructs a fresh Daywrecker for X, whose consumed byte starts at zero.
5. That lifetime detonates, producing another local blast/crater call.

This can happen without duplicate packets: one delayed pre-detonation state can
be sufficient if the acceptance conditions and timing window are met. The
launcher follows different retirement bookkeeping, which fits the visibility
asymmetry. This is a conditional source-backed sequence, not runtime attribution.

If observed, the narrow repair candidate is suppression of stale reconstruction
for a retired consumed Daywrecker ID. A tombstone needs validated session/ID reuse,
ownership transfer, packet time, permanent-state, late-join and cleanup behavior.
An unlimited global ban on revival would change valid engine behavior. Do not
implement an owner-only Simulate/Explode guard from this evidence: each peer may
need its own terrain update and damage to locally owned targets.

## Why the old MPAUTH trace is insufficient by itself

`src/patches/diag_mpauth_trace.cpp` remains unchanged. Its existing messages have
material interpretation limits:

- `MPAUTH_DW_DETONATE sim` is emitted at every simulation entry, including flight;
  entry with `consumed_before=0` does not establish a detonation.
- `MPAUTH_DW_RX lookup=MISS` is based on a recently removed ID, not an observed
  ownership-map lookup. The ordinary reader may process multiple records, while
  this hook samples only the first record at entry.
- `deleted_record` predicts a bookkeeping branch from type/ID; it does not read
  the engine's deleted-ID map.
- Pointer equality is insufficient for lifetime identity because an allocator
  may reuse an address. SetRemote alone does not prove a new constructor ran.
- Ordinary and permanent readers have different acceptance rules; preserve the
  actual nested reader-to-Create-to-constructor relationship.

Consequently the older qualification's phrases "self-proving" and
"makes the receive edge indisputable" overstate what those hooks record. Keep
their outputs as leads, not proof of lookup, construction, or actual effects.

## Focused capture

The standalone scripts are
`reverse_engineering/capture_daywrecker_lifecycle.py` and
`reverse_engineering/daywrecker_lifecycle_trace.js`. They attach to explicitly
selected existing PIDs, require the exact disk hash, x86/base and all 17 live
entry-byte checks, then use temporary Frida Interceptors. They do not invoke
engine functions, alter arguments/game state, launch clients, or stop games.
Existing detours at a required site cause qualification to fail closed.

The capture records:

- constructor generation, including pointer reuse;
- assigned wire ID, type and ownership transitions;
- nested network reader/Create origin, actual creation record ID and flags;
- ObjectLobber carrier and constructor/Build caller, distinguishing launch from
  network reconstruction;
- collision/deployed/Explode entry, consumed byte and position;
- actual scoped crater and explosion Build calls, linked by invocation and
  generation; and removal/Destroy/destructor calls.

IDs in unowned constructor state are reported as null. Objects already alive
when attached have no constructor generation; capture before the launch.
`crater_call` means the routine was called, not that terrain was mutated
(TerrainEdit can return early). `explosion_build_call` is not a health-delta
measurement. No terrain-spire or double-damage claim follows from those alone.
The event budget is 20,000 per peer; `budget_exhausted`, a Frida error, premature
peer detach, or missing `ready` makes the relevant observation incomplete.

Run with the installed Python 3.12 runtime containing Frida and psutil:

```powershell
& "$env:LOCALAPPDATA\Programs\Python\Python312\python.exe" `
  reverse_engineering\capture_daywrecker_lifecycle.py `
  --pid <launcher-pid> --pid <receiver-pid> --seconds 180 `
  --output reverse_engineering\tooling_smoke\daywrecker_capture.jsonl
```

Use a new output filename. The runner refuses to overwrite a capture. Repeat
with launch roles reversed and one bomb per run; preserve launch and impact
locations. A same-machine two-client result is a controlled peer test, not
cross-machine/platform qualification.

| Observed sequence within one peer | Interpretation |
| --- | --- |
| Effects for X/generation A, remove/destructor, reader/Create with wire X, constructor generation B, SetRemote X, effects for B | Direct evidence of receiver recreation and repeated effect calls for one wire ID. Compare with the launcher's single creation/effect sequence. |
| Two constructor generations from ObjectLobber, each assigned a different local ID | Evidence of extra local creation, not stale-state revival; trace trigger and dispatch authority next. |
| Multiple effect invocations for one generation | Investigate consumed-byte corruption/reset, reentrancy, or lifetime observation; the intact binary normally excludes this. |
| One generation/effect invocation on each peer | Normal per-peer representation; insufficient to explain duplication or repeated mutation of one buffer. |

## Validation this pass

- Node syntax check and Python compilation passed.
- Frida smoke attached to BZRCoop PIDs **11500** and **60876** at
  **08:13 CDT**, 2026-10-07. Both hash/base/x86 and all 17 live entry-byte gates
  passed; both emitted `ready`, then detached after eight seconds without a
  Frida error. Raw output is ignored at
  `reverse_engineering/tooling_smoke/daywrecker_20261007/live_smoke.jsonl`.
- No Daywrecker fired during that interval: object fields, callbacks and the
  candidate gameplay sequence remain unexercised. This is attachment validation,
  not a reproduction or a complete two-peer capture.
- A first attempted attachment used PIDs from the previous co-op session; those
  peers had exited. PID validation rejected it before attaching or creating an
  output file. The subsequent smoke used newly discovered PIDs.
- The Ghidra wrapper on PATH initially selected Python 3.14 without
  `pyghidra_mcp`; starting the existing wrapper script with installed Python 3.12
  brought the local MCP service up. Targeted decompilation succeeded after
  analysis completed. No tool installation or user configuration change.

No production patch, authority guard, game restart, mission change, release,
or external publication was performed.
