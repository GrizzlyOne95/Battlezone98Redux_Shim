# Redux Direct LAN adapter: qualified query subset

`direct_lan_redux_adapter.h/.cpp` now implements the identity/roster projection
and three native lobby query entries. This is **partial implementation**:
there is no complete replacement lobby/P2P backend and no live activation.
The source has no production API for publishing its incomplete native object.
Only a test build exposes that object to isolated ABI/released-code checks.

## Released-image contract

Baseline: **Battlezone 98 Redux 2.2.301 GOG**, SHA256
`8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413`.
Ghidra project `/battlezone98redux.exe-007c64`; private corpus path
`Battlezone_Source/BZ1/Redux/openshim_re_corpus/bzr_gog_best_effort/ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps/`.
Each listed function has the corresponding lowercase
`FUN_<address>-<address>.c` file there. Assembly is reproduced by
`reverse_engineering/inspect_direct_lan_backend.py`; generated material stays
in ignored workshop output. No PDB-derived layouts or decompiler bodies are
included in this implementation.

| Native boundary | Qualified register/stack behavior |
|---|---|
| Lobby `+0x38`, `FUN_0074B670` / `0x0074B670` | ECX is the lobby object; stack argument is the output identity pointer; returns that pointer in EAX, `ret 4`. |
| Lobby `+0x68`, `FUN_0074B600` / `0x0074B600` | ECX is the lobby object; stack arguments are output identity pointer and queried lobby identity pointer; returns output in EAX, `ret 8`. |
| Lobby `+0x48`, `FUN_0074B910` / `0x0074B910` | ECX is the lobby object; stack arguments are output identity pointer, lobby identity pointer and signed member index; returns output in EAX, `ret 12`. Iterates the native membership tree and copies the selected identity; unavailable/out-of-range results use the invalid constructor. |
| Current-lobby owner predicate, `FUN_00742CF0` / `0x00742CF0` | Checks identity at object `+0x28`, calls `+0x68` with that identity and a hidden output buffer, then `+0x38` with another output buffer, compares results and returns AL. `ret` with no stack arguments. |
| Explicit-lobby owner predicate, `FUN_00742D50` / `0x00742D50` | Same owner/local query sequence, using its stack-supplied lobby identity pointer; `ret 4`. |
| Identity equality, `FUN_0056F780` / `0x0056F780` | ECX lhs, stack rhs; compares discriminator and words at 8/12, ignores offset 4, returns AL, `ret 4`. |
| Identity ordering, `FUN_00574A30` / `0x00574A30` | ECX lhs, stack rhs; signed discriminator comparison, then unsigned high/low value comparison; ignores offset 4, returns AL, `ret 4`. |

These are **PROVEN for the stated operations in this image**, using assembly
and the execution checks below. The explicit-pointer declarations implement
the observed hidden-output ABI without relying on the compiler to infer a
source-level struct-return type. A fastcall bridge consumes ECX plus an unused
EDX argument while keeping the real arguments and callee cleanup on the stack.
No complete object layout, allocator or lifetime contract follows from these
three methods. The partial test object places current lobby at `+0x28` solely
for the two qualified predicates; its other fields are not a native layout.

## Implemented mapping and roster behavior

The adapter maps complete opaque 128-bit control IDs to discriminator-3 native
values using deterministic FNV-1a-64: offset basis `14695981039346656037`, prime
`1099511628211`, first the domain byte (1=lobby, 2=player), then all 16 ID bytes
in wire order. A zero hash becomes 1. This is an explicit adapter mapping,
not a Steam/Galaxy identity or authentication mechanism. Keep this algorithm
consistent between peers; changing it requires protocol compatibility handling.

Both directions are retained, collisions fail closed, and old identities are
not recycled into another player while the adapter lives. The registry caps
at 257 mappings (one lobby and up to 256 participant identities over time).
The active roster remains at most 16. Native enumeration sorts using the
qualified comparator, independently of snapshot traversal order. Both host and
guests project the same lobby, owner and peer values from the accepted snapshot.
Control slots remain distinct from Redux's uint16 gameplay player IDs; the
native gameplay-player mapping is not implemented.

Copy/output calls preserve the bytes at offset 4 exactly as the released copy
and invalid constructors do. No meaning is assigned to those bytes. The local
identity remains valid before joining and after teardown, while owner/current
lobby/membership become invalid. This matters because the stock owner predicate
compares returned identities: clearing both local and owner to zero could make
a stale explicit-lobby query appear owned. Reset, rejected projections, missing
local members, duplicate identities/slots/endpoints, mapping exhaustion and
session changes all have explicit handling. A new session requires Reset or
a new adapter; a new game Node should generate fresh local IDs.

Returned `Peer` pointers are borrowed until Apply/Reset and must not be retained
by engine callbacks. No engine object is allocated, destroyed, registered or
overwritten by this subset. Standard C++ containers belong to the shim only.

## Execution qualification

The ordinary `direct_lan_redux_adapter_tests` CTest covers projections,
consistent enumeration, departure/rejoin, reverse mapping, rejection,
tombstone bounds and teardown. On Win32 it also calls all three native entries
through thiscall function pointers for 10,000 cycles, checking output buffers,
offset-4 preservation and stack balance. Unknown vtable slots remain null.
These tests do not publish the partial object to a game.

An explicit local test accepts `--released-exe <baseline-exe>`. It verifies the
full SHA256, privately maps the image into its own standalone Win32 process,
and executes **the original released owner predicates** against the compiled
adapter. Only the two predicates, their discriminator-3 validity leaf and
equality leaf are invoked. Those paths use relative calls and require no
imports, absolute relocation, game startup, SEH setup or provider initialization.
Host=true, guest=false, wrong-lobby=false, reset=false and stale-lobby=false
checks pass, including 1,000 repeated host/guest cycles for both predicates.
The private image mapping is freed by the test.

`qualify_direct_lan_identity.py` adds reproducible differential qualification:

```powershell
py -3.12 reverse_engineering/qualify_direct_lan_identity.py --exe <baseline-exe> --adapter-test build/tests/Release/direct_lan_redux_adapter_tests.exe
```

Use an RE Python environment containing pefile and Unicorn. For 1,000 seeded
cases it executes 5,450 released x86 leaf calls in emulation, checks callee-save
registers and stack cleanup, and compares copy/equality/ordering/local validity
results with the compiled adapter. Only AL is used for native booleans; offset
4 is varied independently. It also runs the native Win32 predicate test when
available. Reports are ignored research output. Failure on a different image
hash is intentional. This is bounded released-code execution, **not** a live
game hook or gameplay test.

The independent multi-process session test now projects every accepted roster
through this adapter. It checks that clients agree on native lobby/owner IDs
and retain distinct local IDs, alongside discovery, launch coordination and
disconnect cases. Its Prepared response still emulates gameplay readiness.
GCC/UBSan checks qualify the portable projection, not the Win32 ABI or Wine.

## Remaining adapter work

| Component | State |
|---|---|
| Local/owner/member query subset | Implemented; x86 ABI and bounded released owner predicates qualified |
| Identity copy/equality/ordering and candidate kind-3 validity | Implemented and differential-tested for this subset |
| Every native identity consumer, string/data serialization | UNKNOWN; partial paths do not qualify the entire engine |
| Full 32-entry lobby interface, UI/game callbacks and subscriptions | Incomplete |
| Native roster-to-game-player creation and uint16 IDs | Missing |
| P2P object, receive queue ownership and gameplay transport integration | Missing |
| Backend construction/publication, helper registrations and restore/teardown | Unqualified; no hooks installed |
| Native UI, no-login game operation, physical match, Steam/Proton/Wine | Unverified |

The P2P table also needs care: in this image `+0x04` is the empty
`FUN_00417C60`, `+0x08` is the pump `FUN_0075AAF0`, and `+0x0C` is send
`FUN_0075BEB0` (`ret 16`, byte result). The destructor is
`FUN_0075A390` (`ret 4`, deletion flag). Neither replacing just the send method
nor forwarding the control model's readiness provides a complete backend.
Backend objects also register at interface-helper `+0xC38/+0xC3C`, independently
of the primary accessor. Keep native activation gated until these contracts
and the full backend lifetime are qualified and implemented.
