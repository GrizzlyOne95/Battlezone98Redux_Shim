# Per-craft native damage resistance

The appended SDK exports `OpenShimHasNativeDamageResistance`,
`OpenShimSetUnitDamageMultiplier(void* object, DWORD handle, float multiplier)`,
`OpenShimClearUnitDamageMultiplier(DWORD handle)` and
`OpenShimResetUnitDamageMultipliers` are forwarded through `winmm.dll` to the
OpenShim provider. Existing provider/legacy slots retain their offsets.

EXU owns the Lua binding. OpenShim owns native patching and the per-object
policy. Call the setter on the simulation thread with a live full GameObject
pointer, its matching full handle, and a finite multiplier in [0, 1]. The setter
validates a handle/object round trip. One clears an override; zero grants immunity.
Registrations include the allocation generation and reset when simulation ends,
as well as on EXU mission-VM attachment/teardown.

The implementation changes only the receiver-local effective damage in
`Craft::DamageAlloc`, after difficulty adjustment and before the zero-damage
branch, health subtraction and death flagging. The source DAMAGE record is
unchanged. Healing/direct health setters are untouched. Buildings and persons
use other damage implementations and are outside this hook's contract.

Qualification is currently Windows/GOG Redux 2.2.301 x86. The unique site and
independent identity evidence are in `scripts/patches.json` under
`Craft::EffectiveDamageResistanceSite`. Capability lazily installs the guarded
inline detour; mismatches return false. Steam, Proton and Wine remain unqualified.
The trampoline replays the stolen instruction; the bridge preserves flags,
integer registers, x87 and XMM state.

Validation on 2026-10-07 used the installed GOG executable with SHA256
`8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413`:

- Frida captured the unpatched site from live PID 41772 before building it.
- Native-only mission checks: 100-HP Lancer survived 120 damage at 10 HP;
  unshielded and cleared-override controls died; zero multiplier stayed at 100 HP;
  direct health edits stayed unchanged.
- One 120-damage explosion removed 90 HP from the shielded Lancer and still
  killed the 100-HP unshielded victim in the same radius query. The health sample
  was taken before secondary explosions from that control.
- Real enemy projectile hits drove the EXU hit callback and ISDFC shell/contact
  effects. Native-only runs exited normally.
- Policy, append-only SDK/thunk and registration checks passed. The complete
  applicable OpenShim CTest suite passed (77 tests).

Scratch decompilation, game binaries and runtime dumps stay outside this public
repository. The experimental Frida entry/continuation trace crashed the game;
it was removed from the qualification run. It is not behavioral evidence.
