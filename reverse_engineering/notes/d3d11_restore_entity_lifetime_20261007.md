# D3D11 restore: cached entity animation ownership

## Evidence and diagnosis

Run: `cr-misn05-win-Overridemisn05-coop-Skipperhost-4p-20261007-193930`
under `C:\BZRCoop\runs`. Client2's dump is
`client2\logs\openshim_crash_20261007_194245.dmp` (76,997,564 bytes).
Client0's zero-byte dump cannot provide additional object evidence.

Client2 logged device loss at 19:42:41 and restoration at 19:42:45 on
2026-10-07, America/Chicago. The fatal AV followed restoration. The external
cause of the device loss is not established by this investigation. A display
change or GPU reset remains a trigger hypothesis, not the defect being fixed.

`0x00681AAF` is the return address of a virtual call, not a texture/material
dereference. Released GOG code in the containing function reads the part's
`+0xC8` field, tests it for null, and calls vtable `+0x20`,
`Node::setOrientation(float,float,float,float)`. The analogous `+0xCC` field
is updated later. The renderer's construction/binding code retains skeleton,
bone and animation-state pointers in its render records and part hierarchy.
In particular, the released binding helpers at `0x0067E260` and `0x0067E430`
store bones at those two part offsets.
Refreshing just this one part pointer would leave other dangling references.

At the fatal call the part was `0x38D156A0`, its `+0xC8` pointer was
`0x397F4708`, and its still-recognizable Node vtable was `0x54427A50`.
The float overload constructs a quaternion and calls vtable `+0x24`.
`Node::needUpdate` clears its `mChildrenToUpdate` set at `+0x28`, whose tree head
was `0x2B42D350`. That head's dumped contents violate the tree invariants; the
set-clear implementation subsequently dereferenced node value 1 and read
`0x0000000E`. This is consistent
with a destroyed/reused bone allocation, not a valid node with a missing
material. The minidump does not preserve sufficient heap metadata to attribute
the reuse to a particular allocator call.

The shipped D3D11 `handleDeviceLost` body invokes
`MeshManager::getSingleton` and ResourceManager's reload virtual with flag 4
(`LF_PRESERVE_STATE`) before restoring scene hardware resources and emitting
`DeviceRestored`. Ogre's entity render path detects a mesh state-count change
and forces `_initialise(true)`. That method calls `_deinitialise`, which frees
the entity's SkeletonInstance (and its bones), AnimationStateSet, frame marker
and bone matrices. BZR's cached pointers are not rebound by that path.
This establishes a stock lifetime failure compatible with the dump. The exact
destruction/reuse sequence still needs a controlled live restore trace.

Upstream [Ogre 1.10 Entity source](https://github.com/OGRECave/ogre/blob/v1.10.0/OgreMain/src/OgreEntity.cpp)
and [D3D11 restore source](https://github.com/OGRECave/ogre/blob/v1.10.0/RenderSystems/Direct3D11/src/OgreD3D11RenderSystem.cpp)
explain this mechanism. They are semantic references; all offsets and ABI
decisions below were independently checked in the released Ogre binary.

## OpenShim involvement

The earlier guarded AV at OgreMain `+0xE7D61` is in the released
`BillboardSet::getRenderOperation`. At that instruction its `mVertexData`
pointer is null. Before the fault the getter writes that null pointer to the
probe's local RenderOperation; its first write through the null vertex data
then faults at `+0x10`. In this captured path there is no successful write to
the billboard's vertex data before the fault. `GuardedReadRenderableInputs`
catches the AV and declines the compatibility probe. This is a real access to
a resource absent in the restore window, but does not explain deletion of the
cached bone. This patch does not claim to eliminate that first-chance AV.

`CaptureChunkBridgeSnapshot` performs reads with SEH guards; it does not destroy
nodes or entities. Chunk mesh proxies were enabled, while both the placeholder
proxy and terrain proxy were disabled in client2's recorded configuration.
The surviving and crashing clients do not establish that all proxy-owned GPU
resources recover correctly. This change addresses the identified CPU pointer
lifetime failure, not every possible device-restore problem.

## Patch and ownership contract

`InstallEntityReloadLifetimeHookIfPossible` detours the real exported
`Entity::_initialise` body, following bounded incremental-link thunks. It is
registered in both initial and deferred installation. It requires the exact
shipped OgreMain SHA-256 plus live signatures for the hook/deinit prologues and
the layout-defining getters. It declines jumps outside OgreMain and unknown
builds. No executable-address patch or named EXE resolve is introduced, so no
new `scripts/patches.json` site is required (same export-hook convention as the
existing scene-teardown and particle-dedupe guards).

For a rebuilding entity with complete, independent CPU ownership, the hook:

1. Temporarily removes the skeleton, AnimationStateSet, frame marker and bone
   matrix pointers from the entity.
2. Runs the original rebuild. Ogre still destroys/recreates subentities,
   temporary vertex data and render resources and records the new mesh state.
3. Destroys the newly allocated CPU animation state through Ogre's destructors
   and allocators, then restores the original CPU ownership and invalidates the
   bone/animation update markers. BZR's cached bones and AnimationStates retain
   their identity, pose, enabled state and manually edited hierarchy.

The transaction also restores ownership during C++ exception unwinding and a
deferred-load return. It does not suppress AVs from a half-completed rebuild.
A subsequent non-forced initialization with retained ownership can retry the
transaction. Ordinary initialization, non-skeletal entities and normal
destruction retain the stock behavior.

Preservation requires the same master skeleton resource and matching nonzero
master/instance/matrix bone counts. Shared skeletons and entities with attached
TagPoints are excluded: the original deinitializer needs a live skeleton to
detach those objects. These are explicit limits, logged on a bounded budget;
this patch is not a general repair for arbitrary skeleton topology changes,
shared ownership or attachment graphs. The GOG executable imports no
`shareSkeletonInstanceWith` function. That absence is not proof that other
native plugins never use sharing.

`OPENSHIM_DISABLE_ENTITY_RELOAD_FIX=1` disables installation for comparison.
`[ENTITY-RELOAD]` logs report installation, rejected ABI/ownership gates and
sampled successful preservation counts. The hook is renderer-independent:
the qualified Ogre ABI, not a store path or host-specific D3D object, controls
installation. Steam/Proton/Wine execution remains unverified.

## Released ABI qualification

| Field | Offset | Released-code evidence |
|---|---:|---|
| Entity mesh SharedPtr object | `0xD4` | `_initialise` loads/calls the mesh |
| Entity AnimationStateSet | `0xEC` | getter and unconditional deinit cleanup |
| Bone world matrices | `0x158` | aligned deallocation in deinit |
| Bone matrices | `0x15C` | aligned allocation and deallocation |
| Number of bone matrices | `0x160` | WORD store of skeleton bone count |
| Frame animation last updated | `0x164` | constructor/update-animation field |
| Frame bones last updated pointer | `0x168` | 4-byte allocation, deinit free |
| Shared skeleton entity set | `0x16C` | sharing getter and deinit branch |
| SkeletonInstance | `0x1BC` | getter, constructor assignment and deinit delete |
| Initialised flag | `0x1C0` | getter and init/deinit gates |
| Attached-object map count | `0x20C` | attach/detach map at `0x208` |
| SkeletonInstance master SharedPtr | `0x138` | master-delegating getters |
| Mesh skeleton SharedPtr | `0x14C` | mesh skeleton getter |

Ogre's exported ordinary `AllocatedObject` delete routes to the same CRT free
used by `_deinitialise`. AlignedMemory's exported deallocator is used for both
matrix arrays. AnimationStateSet's destructor is nonvirtual and is called
explicitly before Ogre delete, matching stock behavior. No foreign CRT free
or replacement Ogre runtime is used.

Build identities (SHA-256):

- GOG EXE: `8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413`
- OgreMain, GOG install, Steam install and Instance2:
  `E5E693960B95AD0D60733A3B688464A6C6CBA234E86950698F9C2BEA4ACFEB45`
- D3D11 render plugin:
  `78A1D8E13C8BD71983B09A39A3DCF7783E6C34DDE577DE3B9202460DB500AAE0`

Dump module base: OgreMain `0x53D60000`. Real `_initialise` RVA `0x1793C0`,
`_deinitialise` RVA `0x179020`, skeleton getter RVA `0x849B0`, animation getter
RVA `0x17D610`. The dump's live init/deinit byte windows agree with the local
released file after ASLR relocation. No new process was launched for these
reads; this is saved crash-time memory, not a controlled live test.

Tools: `bzr-cdb32.cmd -z <client2-dump> -c <commands>` for registers, code and
object memory; pefile/Capstone for shipped PE exports and instruction decoding.
Useful repeatable dump commands: `.ecxr`, `u 00681a50 00681acf`,
`dd 38d156a0+c8 L4`, `dd 397f4708 L20`, `dps 54427a50 Ld`,
`u 53ed93ef L8`, `u 53ed910f L22`, `u 53e47d50 L14`.
Raw debugger/decompiler output and helper scratch are deliberately not tracked.

## Validation and remaining acceptance

- Release Win32 ownership tests cover cached-pointer survival, replacement
  allocation cleanup, normal teardown, C++ exception propagation, partial
  allocation cleanup, deferred retries, repeated restore attempts and rejection
  of unsafe ownership/topology cases.
- Full Release Win32 CTest: 79/79 passed, including patch registration.
- The expanded ownership test also passed under Ubuntu 24.04 GCC with C++17
  and `-Wall -Wextra -Werror`. This checks the portable transaction, not Wine
  or Proton's execution of the native hook.
- Native Release Win32 solution build passed; `winmm.dll` and
  `plugins/openshim.dll` were produced in this worktree's `bin/Release`.
- Offline PE qualification matched all seven installer ABI/body signatures and
  all four ownership exports in the GOG, Steam and Instance2 OgreMain files.
- No deployment, game clients, GPU-reset test, push or publication was performed.

Before release, obtain authorization for a serialized GOG DX11 mission-load
restore test, verify preservation diagnostics and absence of fatal cached-bone
AVs, and check pose/animation continuity and normal teardown across repeated
restores. Qualify Steam and the applicable Proton/Wine lanes separately.
Shared-skeleton/TagPoint exclusions and other device-owned proxy resources need
their own acceptance coverage if those features are enabled.
