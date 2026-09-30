# Singleplayer weapon presentation implementation

Implementation milestone: 2026-09-30.

**Status: the runtime state and lifecycle bridge are implemented; native weapon
producers and the renderer backend are not connected. This branch does not yet
produce visible muzzle flash or recoil in the game.**

The scope is singleplayer muzzle flash and primary mesh recoil. Existing weapon
convergence remains the aiming implementation. The bridge uses the existing
`IsSinglePlayerSession()` predicate, including its unreadable-state rejection,
and requires the verified mission seam to report a running mission. There are
no multiplayer packets, SDK exports, Lua events or new user-facing INI options.

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
| Build integration | Both new source units compile in Plugin_OpenShim; the portable suite includes `weapon_presentation_tests` |

The first recoil binding contract supports static local translation with live
orientation updates. It rejects an animated/displaced translation instead of
recapturing it as rest. Animated-translation composition needs its own qualified
baseline writer before support is added.

## Native adapter contract

`RegisterQualifiedWeaponPresentationBackend` is an internal connection point,
not an installer or a claim of runtime qualification. There is deliberately no
caller yet. Stock content takes the null-runtime fast path through the existing
frame and lifecycle seams. Registration allocates only when a qualified adapter
explicitly connects an enabled setting.

The native adapter must:

1. Recover signatures, exact call instructions and ABI from the released
   executable and validate them against a settled live Windows PID. Register
   build-specific addresses in `scripts/patches.json` when they are known.
   Do not enable guessed decompiler declarations or generic-prologue resolves.
2. Read extension keys within the engine's active ParameterDB scope, copying
   strings and inherited values before that scope ends. ODF parsing and class
   invalidation are not supplied by this milestone.
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

All **57** host tests passed again after rebasing onto current main, including
new presentation, existing convergence,
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

Windows plugin compilation is checked by the draft PR's `Release Win32` lane.
Native hook bytes/ABI, deployed-game visibility, Ogre update order, asset
loading and in-game lifetime tests remain separate gates. Do not describe this
milestone as a working in-game feature.
