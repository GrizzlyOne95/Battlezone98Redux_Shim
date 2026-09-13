# Constructor double-recycle leaves the losing rig permanently deployed

Reproduced live on 2026-09-13 against the GOG Redux install, with controls.
Root cause identified in the shipped-exe decompile: the unbuild state machine's
only exit condition is never met when the target building disappears from under
a second Constructor.

## Reproduction

```powershell
pwsh -File reverse_engineering/run_lcroad_recycle.ps1
```

The runner installs the `lcbench` world assets if they are absent, deploys
`rmrcyc.lua` as `addon/lcbench/lcbench.lua`, runs each arm, captures evidence,
and removes everything it laid down. Single arm, three repeats:

```powershell
pwsh -NoProfile -Command "& './reverse_engineering/run_lcroad_recycle.ps1' -Cases @('same') -Repeats 3"
```

Note the `@(...)` form: `pwsh -File ... -Cases same,stag` passes one string and
fails `ValidateSet`.

`rmrcyc.lua` spawns the rigs at mirrored lateral offsets from the building so
both travel the same distance, issues `SetCommand(rig, AiCommand.RECYCLE, 1,
building)`, polls `IsDeployed` / `GetCurrentCommand` / `GetCurrentWho` every
half second, and then — ten seconds after the building dies — pokes every
surviving rig with a `Goto`. The poke is what separates *wedged* from merely
*idle and deployed*.

## Result

| Arm | Rigs | Buildings | Deployed at end | Moved after poke | Stuck | Target down at |
|---|---|---|---|---|---|---|
| `solo` | 1 | 1 | 0 | 1 | 0 | T+13.01 |
| `pair` | 2 | 2, one each | 0 | 2 | 0 | T+13.02 |
| `same` | 2 | 1, shared | 1 | 1 | **1** | T+13.01 |
| `stag` | 2 | 1, shared, 2nd order +4s | 1 | 1 | **1** | T+13.01 |

`same` reproduced identically on both repeats. The two controls are what make
the reading safe: a lone rig and two rigs on two buildings both finish clean,
so "ends up deployed" is not simply what Constructors do.

The trace from `same_r01`, trimmed to the transition:

```
T+9.501  POLL        rig1{dep=true  cmd=18 who=FFE00002} rig2{dep=true  cmd=18 who=FFE00002} bld1{v=true}
T+13.008 TARGETDOWN  rig1{dep=true  cmd=18 who=FFE00002} rig2{dep=true  cmd=18 who=FFE00002} bld1{v=false}
T+13.502 POLL        rig1{dep=false cmd=18 who=FFE00002} rig2{dep=true  cmd=18 who=FFE00002} bld1{v=false}
T+23.008 POKE rig=1 dep=false cmd=18
T+23.008 POKE rig=2 dep=true  cmd=18
T+35.012 RIGRESULT rig=1 dep=false cmd=0 travelled=63.09
T+35.012 RIGRESULT rig=2 dep=true  cmd=3 travelled=0.00
```

Both rigs hold `cmd=18` (`CMD_RECYCLE`) on the same handle `FFE00002`. When the
building dies, rig1 undeploys within half a second. Rig2 never does. Twelve
seconds after being handed a `Goto` it still reads `dep=true`, and `travelled`
is exactly `0.00` — it **accepted** the order (`cmd=3`, `GO`) and could not act
on it. The loser is not idling deployed, it is wedged.

Two incidental findings fall out of the same table:

- `targetDownAt` is T+13.0 in every arm, `solo` included. The second rig's
  unbuild contributes nothing — each rig runs its own independent countdown and
  the first to reach zero deletes the building. Double-recycling is pure loss:
  no speed-up, one Constructor gone.
- The 4-second stagger in `stag` does not help. This is not a same-frame race;
  any second rig that has reached the unbuild loop before the winner finishes is
  lost.

## Root cause

From the shipped 1.5 exe decompile (`reverse_engineering/decompilation_from_1.5_exe-pdb/1.5`).
The unbuild loop lives in `UnBuild::DoNear` (`0x0041060b`):

```c
if (this->unbuildStage == 0) {
    ConstructionRig::StartUnbuild(rig, target);
    this->unbuildStage = 1;
}
if (this->unbuildStage == 1) {
    ConstructionRig::UpdateUnbuild(rig, TimeStep());
    if (((int *)rig)[0xd8] == 0) {      /* rig->unbuildHandle */
        this->unbuildStage = 2;
        (**(code **)(*(int *)rig + 0x60))();   /* undeploy */
        ...
    }
}
```

`rig->unbuildHandle == 0` is the **only** way out of stage 1, and therefore the
only thing that ever undeploys the rig.

`ConstructionRig::UpdateUnbuild` (`0x0048566d`) has two ways to end:

```c
local_8 = GameObjectHandle::GetObj(this->unbuildHandle);
if (local_8 == (GameObject *)0x0) {
    Producer::CancelBuild((Producer *)this);     /* <-- target vanished */
}
else {
    ...
    if (0.0 <= fVar1) { /* still counting down */ }
    else { FinishUnbuild(this, local_8); }       /* <-- we finished it */
}
```

- `FinishUnbuild` (`0x004853b0`) ends with `this->unbuildHandle = 0;` — the
  winner's rig exits stage 1 and undeploys. That is rig1 at T+13.502.
- The vanished-target branch calls `Producer::CancelBuild` (`0x004ab24f`), which
  operates on the **build** path: it returns `false` immediately when
  `buildClass == 0`, refunds build cost, and **never touches `unbuildHandle`**.

So the loser's `unbuildHandle` keeps pointing at the freed building forever.
`ConstructionRig::IsUnbuilding` (`0x0041034c`) is literally
`return this->unbuildHandle != 0;`, so the rig reports as unbuilding for the
rest of the mission, `DoNear` re-enters `UpdateUnbuild` every frame, that call
takes the null branch and no-ops every frame, and the undeploy at vtable `+0x60`
is never reached.

The function that was wanted is `ConstructionRig::CancelUnbuild` (`0x00485394`),
sitting right next to it and doing exactly the one thing needed:

```c
bool ConstructionRig::CancelUnbuild(ConstructionRig *this) {
    if (this->unbuildHandle == 0) return false;
    this->unbuildHandle = 0;
    this->_padding_ = 0;
    return true;
}
```

**The defect is a one-call substitution in `ConstructionRig::UpdateUnbuild`:
the vanished-target branch calls `Producer::CancelBuild` where it must call
`ConstructionRig::CancelUnbuild`.** The two are adjacent cancel routines for the
producer's two modes, and the build-side one was used on the unbuild path.

This is stock BZ 1.5 code, not a Redux regression — the same substitution is
present in the 1.5 decompile, and the live reproduction above is Redux
inheriting it.

## Notes toward a fix

The Redux addresses still need resolving; the legacy→Redux symbol map is not
currently present in the tree (`reverse_engineering/workshop/symbol_transfer/`
is gone), so the call site has to be located in the shipped Redux binary
directly. The anchor is small and distinctive: a `GameObjectHandle::GetObj` on
a field at rig `+0x360` (`[0xd8]` as dwords) whose null branch tail-calls the
producer's cancel-build routine.

Per `[[byte-guard-anchor-instruction-not-operand]]`, guard on the instruction,
not the operand. The minimal correction is to zero `unbuildHandle` on that
branch — a detour on `UpdateUnbuild` that checks the target handle first and
clears the field itself is enough, and does not require replacing the whole
function.

Worth checking at the same time whether the AI-driven recycle path can put two
of its own Constructors on one building, since the wedged rig is invisible to
the player as a *failure* — it just sits there looking deployed.
