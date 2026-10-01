# Singleplayer weapon presentation implementation

Implementation milestone: 2026-10-01.

**Status: the runtime, lifecycle bridge and GOG cannon native adapter candidate
are implemented. The native installer is deliberately closed until live Windows
qualification. This branch does not yet produce visible effects in the game.**

The scope is singleplayer muzzle flash and primary mesh recoil. Existing weapon
convergence remains the aiming implementation. The bridge uses the existing
`IsSinglePlayerSession()` predicate, including its unreadable-state rejection,
and requires the verified mission seam to report a running mission. There are
no multiplayer packets, SDK exports or Lua events. `SinglePlayer/MuzzleFlash`
and `SinglePlayer/MeshRecoil` both default to 0. While qualification is pending,
setting either key only logs why the native candidate remains inactive.

The [research handoff](https://github.com/GrizzlyOne95/Battlezone_Source/pull/12)
contains the pinned Redux integration map and original evidence. The GOG
executable is in the private evidence repository at
`BZ1/Redux/bin/stock/battlezone98redux.exe`; its researched SHA-256 is
`8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413`.
Do not import the executable, PDB, decompiler output or copied binary material
into this public repository.

## Implemented

| Surface | Behavior |
|---|---|
| `include/weapon_presentation.h` and `src/patches/weapon_presentation.cpp` | Engine-independent presentation coordinator, copied configuration/poses, lifetime identities, binding tokens and bounded shared-node lookup |
| Flash configuration | Absent values inherit; explicit empty name disables; missing, malformed or nonpositive duration is inert; effect identifiers retain case |
| Mesh lookup | Exact printable ASCII IDs of at most eight bytes; bounded child/sibling traversal rejects cycles, duplicate names, unreadable nodes and partial graphs |
| Accepted-shot policy | Caller supplies the copied final factory matrix after native shot acceptance; per-binding monotonic logical-shot serial rejects duplicate pellet notifications |
| Flash timing | Simulation-time duration begins at accepted fire; repeated fire cannot restart an active or pending flash; expired pending flashes do not appear late |
| Recoil | One controller per owner/node lifetime; reset to −0.6, recover at +3 units/s; once per global simulation pass, independent of weapon/slot count |
| Pose staging | Preserve live local orientation and captured rest translation; output a separate visual pose; do not modify the supplied gameplay matrix |
| Stable native pointer storage | Heap-stable per-weapon record; partial factory failure and failed detach retain its pointer slot for native back-reference writes |
| Lifecycle bridge | Render synchronization, mission departure/reentry, hook reset and nested Ogre teardown use existing OpenShim seams |
| Native candidate | Scoped ParameterDB reads; constructor generation; pre-destruction/pre-replacement release; cannon factory observer; global simulation clock; native renderer backend; interception of later stock model pose writes |
| Build integration | Native and portable source units compile in Plugin_OpenShim; portable policy tests and a real MSVC x86 assembly-bridge harness are included |

The first recoil binding contract supports static local translation with live
orientation updates. It rejects an animated/displaced translation instead of
recapturing it as rest. Animated-translation composition needs its own qualified
baseline writer before support is added.

## Native adapter contract

`RegisterQualifiedWeaponPresentationBackend` is an internal connection point,
not a claim of runtime qualification. The candidate supplies a caller, guarded
by `kNativePresentationLiveQualified = false`. Initialization records requests
but installs no candidate hooks and allocates no presentation runtime while
that gate is closed. Once qualified, registration runs lazily on the pinned
engine thread. A producer on another thread forwards stock behavior.

The actual GOG executable was transferred through a private GitHub Actions ZIP,
then independently checked by file size, SHA-256 and Git blob SHA. All fourteen
named resolves are unique exact-build signatures in `scripts/patches.json`;
the three call sites also check their original rel32 destinations before any
write. Static evidence is separate from live qualification.

| Native surface | Resolved site | Recovered contract |
|---|---|---|
| Cannon accepted factory call | `0x005A7195` | ECX=OrdnanceClass; final Matrix and owner OBJ on stack; original RET 8/EAX retained; weapon recovered from caller `[EBP-190]` |
| Weapon ODF scope pop | `0x00611DE4` | ECX=live ParameterDB scope; class at caller `[EBP-3C]`; read flashName/flashDuration before original pop |
| Craft ODF scope pop | `0x004E1138` | Successful new-class path only; class at caller `[EBP-4C]`; read recoilName1..5 before original pop |
| Global simulation | `0x00611270` | cdecl(float dt), plain RET; tick once before original weapon list pass |
| Constructor/destructor | `0x00611300` / `0x00611500` | Constructor thiscall two args/RET 8, destructor thiscall no args/plain RET; native lifetime serial never inferred from address alone |
| Slot replacement | `0x004A77A0` | thiscall slot/weapon, RET 8; release old slot before stock store |
| Model pose writer | `0x00681A00` | cdecl(OBJ*, Matrix*); output a copied local matrix to Ogre, including subsequent stock/convergence updates |
| Raw ParameterDB read | `0x00589620` | thiscall(scope, section FNV, key FNV), RET 8; copy borrowed value before scope ends |
| Native render resolver | `0x0044E4C0` | cdecl(effect name), class returned in EAX; native class vtable+08 builds renderer |
| Renderer update/detach | `0x0044DCA0` / `0x0044DC60` | thiscall on the same stable Render** slot; RET 4 / RET 8; stock detach uses null Matrix and zero float |

The constructor steal is **9 bytes**, ending after `sub esp,0xE4`; a five-byte
steal would split that instruction. Other steals end on qualified instruction
boundaries. The assembly harness calls the production bridges using synthetic
stock frames and checks factory argument forwarding, post-factory order, EAX,
callee stack cleanup, nonvolatile registers and pre-pop scope reads.

The native update ABI required changing `Backend::UpdateFlash` to accept
`void*& storage`. Native Attach writes and retains the slot address again;
passing a temporary pointer variable could cause a later native destructor to
write into a dead stack frame. Tests check slot identity during updates too.

The cannon follow pose retains the committed correction relative to the stock
barrel/mount matrix, then applies it to current stock poses. Recoil modifies
only a copy passed to Ogre. Translation animation, ambiguous slot/node matches,
missed constructors, missed class loads and reload/lifetime disagreement fail
closed. Bindings and class caches are bounded; configuration failures cannot
abort native class loading or an already-created projectile. Other firing
families and hot enabling after class loading are not implemented.

### Required before activation

`AGENT_TOOLING.md` requires a native live launch and target-byte capture before
patch installation. This Linux environment cannot perform that Windows/game
qualification. Keep the gate closed until the following evidence is recorded:

1. Capture exact GOG build identity, settled PID, all fourteen resolves, three
   call targets and five stolen instruction ranges. Check startup timing so
   class/weapon constructors are observed before mission loading.
2. Trace the cannon bridge on accepted/rejected shots and verify the factory
   Matrix, owner, native result and caller-frame weapon. Confirm the one engine
   thread also owns simulation, model writes, render sync and lifecycle seams.
3. Use an audited single-sprite effect to prove create/update, no timer restart,
   native self-expiry, detach visibility and eventual native list cleanup.
   Check that render-queue ordering makes the flash visible at the proper pose.
4. Use a static barrel with rotated axis, nonzero rest position and a child
   marker. Prove subsequent stock writers retain recoil, descendants follow,
   projectile origin/aim remains stock, and native model reload cannot reuse a
   node under a still-valid owner identity without retiring its binding.
5. Run pause/resume, replacement, failed detach, mission hops, save load and
   nested scene teardown. Verify restoration retries never touch reused nodes.
   Enter MP after SP and confirm no new flashes/recoil; return to SP with fresh
   tokens. Steam remains unsupported pending independent build/lifecycle proof.

Only after that evidence passes should an agent change the qualification gate.
Do not treat a successful ABI harness or plugin build as these game tests.

The native adapter must:

1. Recover signatures, exact call instructions and ABI from the released
   executable and validate them against a settled live Windows PID. Register
   build-specific addresses in `scripts/patches.json` when they are known.
   Do not enable guessed decompiler declarations or generic-prologue resolves.
2. Read extension keys within the engine's active ParameterDB scope, copying
   strings and inherited values before that scope ends. The candidate captures
   every observed class load and checks the native packed name on cache use;
   missed loads and late enable remain unsupported.
3. Bind only after the weapon/carrier slot and model exist. Supply native
   lifetime/handle identity, not address alone. Release before replacement or
   destruction. Catch allocation failures at this native boundary and allow the
   original weapon to continue firing.
4. At **global simulation-pass entry**, call
   `BeginSimulationStep(stepSerial, dt)` once. Then run the original simulation.
   Pass only its actual dt; a rendered frame never advances the timers.
5. Observe a successful committed shot, starting with cannon. Supply the actual
   final factory matrix, including aiming and class-specific corrections. Use
   one logical serial for a pellet group; do not synthesize accepted fire from
   trigger input, ammo guesses or a general scripted ordnance spawn.
6. Update followed muzzle pose and unrecoiled local node orientation from
   verified snapshots. The current backend synchronization point is after the
   stock render-queue call; native visibility and subsequent pose writers still
   need live ordering qualification.
7. Implement `Backend` through the verified native render factory and pointer
   helpers. Validate pointer/object/resource generation before each native call,
   catch native faults, and keep the backend alive for the process lifetime.
   Backend callbacks must not reenter the coordinator.
8. Apply recoil to presentation only through the qualified native/Ogre bridge;
   prove rotated-axis sign, descendant behavior and projectile invariance.

The backend is called only by `SynchronizeVisuals`, never directly inside
`Fire` or the simulation timer loop. Factory and pose failures retire the
visual request without changing weapon operation. Failed detach remains
retryable; successful detach must clear the stable pointer slot.

Each producer must call `TryGetSingleplayerWeaponPresentationRuntime()` before
using the runtime. This rechecks the existing fail-closed SP gate and verified
mission state on every entry. The render driver performs the same check for
cleanup. Do not bypass it with a cached enabled flag.

The existing mission seam is currently qualified for GOG only. This additional
gate also keeps the bridge inactive on Steam until that seam has its own
released-build qualification; the SP predicate alone does not enable it.

## Ownership and teardown

`BeginSceneTeardown` retires bindings before the original engine call. Nested
`clearScene -> destroyAllMovableObjects` does not discard records at the inner
return. The outer completion forgets destroyed **presentation poses** and
removes only renderer slots already cleared by detach or native destruction.

**An Ogre scene teardown is not proof that native ParticleRender objects have
been destroyed.** A non-null native back-reference slot remains allocated even
after the outer return. A later native destructor can still safely clear it.
This is why `InvalidateResources` is not called from the Ogre hooks. Use that
stronger operation only after proving native back-references have ended.

Mission departure and hook reset queue cleanup without assuming the scene was
destroyed. Leaving singleplayer invalidates binding epochs; returning to SP
cannot revive old tokens. Rebinding a shared node waits for its previous visual
restoration, unless scene destruction has already removed that presentation.
Slots still held by failed detach count toward the binding cap; refusing new
cosmetic bindings is safer than freeing pointer storage still held by the engine.
The shared recoil table has its own cap: failed visual restorations can outlive
their weapon records. A binding that needs a new controller is refused when
that table is full; successful restoration or scene loss reclaims its capacity.

At coordinator destruction, an outstanding native pointer slot is deliberately
retained rather than freed. Normal teardown should detach or observe native
expiry first. Never unload the backend while it can receive cleanup retries.

## Verification

Performed in a Linux workspace using GCC 13.3:

~~~sh
cmake -S tests -B build/weapon-presentation-tests
cmake --build build/weapon-presentation-tests --parallel 4
ctest --test-dir build/weapon-presentation-tests --output-on-failure
~~~

All **58** host tests passed after merging current main, including
new presentation and native policy tests, existing convergence,
patch registration, resolve-table and shared-document checks. The new portable
source/tests also compile with `-Wall -Wextra -Werror`.

AddressSanitizer and UndefinedBehaviorSanitizer pass for the new tests with
`ASAN_OPTIONS=detect_leaks=0`. LeakSanitizer cannot inspect processes in this
execution environment; its leak sweep is not claimed as passed.

The fake native renderer retains the exact pointer-slot address, including
table growth, partial creation, failed detach, self-expiry, nested scene loss and
a native back-reference that outlives the Ogre scene. Other tests cover opt-in
and session gates, inherited/invalid configuration, bounded mesh lookup,
logical-shot deduplication, rapid-fire deadlines, delayed rendering, rotated
axes, shared-slot recovery, pose restoration retries and stale binding tokens.
The capacity regression retains a full table of failed recoil restorations
after releasing every weapon, then verifies refusal and eventual reclamation.

Static qualification can be reproduced with the private executable and the
public `reverse_engineering/qualify_weapon_presentation_static.py` script:

~~~sh
python qualify_weapon_presentation_static.py <private-stock-exe> --report <private-evidence>/static_report.json
~~~

It checks executable identity, fourteen unique mapped-image signatures,
three original call destinations, five complete stolen instruction ranges
and eleven native callee cleanup sizes. Its output explicitly records
`evidence_kind=static_only`, no PID and `activation_qualified=false`.

Windows plugin compilation and the actual assembly bridges are checked by the
draft PR's CI. Deployed-game visibility, Ogre update order, asset loading and
in-game lifetime tests remain separate gates. Do not describe this milestone
as a working in-game feature.
