# Chunk bridge first-chance AV, 2026-10-14

Exact input: `51d9fbb79`, Release/Win32, verify472's
`bin/Release/plugins/openshim.dll`, SHA-256
`128D1848A87D58A32AC7D533E54ACFDF209F279CFC204C9017568BABBA5D8B2D`.
DLL CodeView and `openshim.pdb` agree on GUID
`1B552FED-73F8-4553-A531-05D84A096022`, age 1. No rebuild was needed for symbols.

## Original binary symbol map

Own-build PDB function/line records, corroborated with disassembly:

| Shim RVA | Function / original source |
|---|---|
| DD78D | `Hooks::CaptureChunkBridgeSnapshot`, chunk_proxy_render.cpp:4718 |
| 21223A | `_except_handler4`, CRT chandler4gs.c:89; SEH registration |
| 81CF2 | `Hooks::TryGetGameObjectMeshName`, chunk_identity.cpp:1101 |
| 82828, 82835 | `CacheChunkObjectIdentityTreeForGameObject`, chunk_identity.cpp:1171 |
| 4BC10 | `EngineGlobals::UserObjectSlot` lambda callback, engine_globals.cpp:61 |
| 4BC05 | `EngineGlobals::UserObjectSlot`, engine_globals.cpp:62 |
| A407 | `ceilf`, corecrt_math.h:678 |
| 21B845 | Compiler `__ehhandler$CacheChunkObjectIdentityTreeForGameObject`; no source line |
| 605F0 | `ChunkEffectSimulateHook`, bzr_hooks.cpp:1795, inlined refresh at chunk_identity.cpp:1250 |
| 219D7D | Compiler `__ehhandler$ChunkEffectSimulateHook`; no source line |

These are stack-scan candidates, not an unwound stack. The globals/math entries
are residual values; the handler addresses are registrations. The two generated
handlers require PDB label records: nearest-public-symbol tools misleadingly
report `roundf` there.

Game candidates have no exact source-line symbols. Static instruction boundaries
on GOG SHA-256 `8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413`:

| Game VA | Containing function / interpretation |
|---|---|
| 4D460A | FUN_004D4580, GameFeature simulation dispatcher, after virtual slot +1C |
| 618121 | FUN_00618060, simulation substep, after call to 4D4580 |
| 618201 | FUN_00618130, frame body |
| 61832D | FUN_00618270, frame/pause wrapper |
| 618A97 | FUN_00618A40, simulation/shell loop |
| 619FC8 | FUN_00619FC0, loop repeatedly calling 618A40 |
| 619263 | FUN_00618FF0, outer application controller |
| 618B49 | FUN_00618B10, application entry wrapper |
| 83EF8D | Entry function at 0083EE5E, CRT startup |

## Cause and classification

`mov eax,[ecx+94h]` faults after loading ECX from `[objectBytes+F0h]`.
In the later run EDX identifies objectBytes (`1CF26638` / `224A3168`).
The candidate `000E0000` passes `IsPointerShaped` (aligned, above 64 KiB),
but the target `000E0094` is unreadable. Earlier clients similarly read
`00080094`. This is a speculative direct-bridge layout applied to an OBJ76
returned by the live GameObject arena, not a Lua handle conversion.
The precise meaning of the nonpointer slot is unproven without object memory.

The first local `__except(EXCEPTION_EXECUTE_HANDLER)` sets `directProbeOk=false`
and continues with the owner/name probes. Compiled filter DD7AC returns 1;
handler DD7B2 clears that flag. The logging VEH returns CONTINUE_SEARCH;
it neither handles this fault nor writes a dump, and logs each EIP only once.

Classification: intentional read-only probe with insufficient accessibility
validation. This captured failure writes only local snapshot state, provides
no evidence of engine corruption/leak, and has its own handler. Repetition can
cost simulation time despite one log record. SP reproduction is unverified;
the refresh has no MP gate.

All 26/27 complete text logs in the two supplied runs were inspected. Later
Formation: 09:31:29.770; AV: 09:31:37 on both clients; deliberate host Lua Update
error: 09:32:12.609. The error therefore does not coincide. Logs show ordinary
simulation, debris batching, stale-handle rejection and network keepalives.

## Fix and validation

`chunk_bridge_probe.h` checks the full readable span before either nested
Ogre-link read, preserves SEH for lifetime races, and publishes both links or
neither. Both direct and owner bridge paths use it. Accessibility is not type
or ownership proof; speculative layout/name probes elsewhere remain unchanged.

Release/Win32 solution build passed; 104/104 CTests and BZLoaderHostTest passed.
Regression tests observed zero first-chance exceptions across valid, unmapped,
unaligned, guarded, decommitted and boundary-spanning candidates. WSL refused
distribution enumeration with E_ACCESSDENIED; Linux and live game validation
remain unverified. No game launch, deployment, push or PR.

Tools: `llvm-readobj --coff-debug-directory`, `llvm-pdbutil dump -summary/-symbols`,
`llvm-symbolizer --relative-address`, `llvm-objdump -d`, `bzr-rizin.cmd`.
Raw outputs/build/test logs are ignored under `tooling_smoke/dd78d-av`.
Commit creation was blocked: shared worktree Git metadata is outside this
session's writable roots.
