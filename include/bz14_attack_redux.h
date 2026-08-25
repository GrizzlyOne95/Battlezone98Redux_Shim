#pragma once

// ============================================================================
// bz14_attack_redux.h - SEH-guarded readers/writers for the Redux AttackTask
// cluster, shared by the legacy-1.4 attack policy hook. Offsets are
// decompile-proven (see reverse_engineering/bz14_attacktask_recovery_20260824.md):
//
//   AttackTask: curState +0x08 i32 | nextState +0x0C i32 | craft +0x10 ptr |
//               himObj +0x18 ptr | forceVec +0x4C f32x3 | rangeSq +0xA0 f32 |
//               ableToHit +0xC4 u8 | stateEntryTime +0x100 f32
//   OBJ76:      iface vptr at +0x18 (slot 12 = self accessor) |
//               MAT_3D at +0x20 (doubles posit_x/y/z at block+0x28/+0x30/+0x38) |
//               lastDamageTime +0x1E8 f32
// ============================================================================

#include <cmath>
#include <cstddef>
#include <cstdint>

namespace bz14
{
    // ---- Redux AttackTask field offsets (decompile-proven) ----------------
    constexpr size_t kTaskCurState = 0x08;
    constexpr size_t kTaskNextState = 0x0C;
    constexpr size_t kTaskCraft = 0x10;
    constexpr size_t kTaskHimObj = 0x18;
    constexpr size_t kTaskForceVec = 0x4C;
    constexpr size_t kTaskRangeSq = 0xA0;
    constexpr size_t kTaskAbleToHit = 0xC4;
    constexpr size_t kTaskStateEntry = 0x100;

    constexpr size_t kObjTransform = 0x20;
    constexpr size_t kMatPositX = 0x28; // double, y +0x30, z +0x38
    constexpr size_t kCraftLastDamageTime = 0x1E8;
    constexpr size_t kObjIface = 0x18;

    bool SehReadTaskHead(const uint8_t* task, int& curState, int& nextState,
                         uint8_t*& craft, uint8_t*& him);
    bool SehReadFloat(const uint8_t* base, size_t offset, float& out);
    bool SehWriteFloat(uint8_t* base, size_t offset, float value);
    bool SehWriteNextState(uint8_t* task, int value);
    bool SehReadAbleToHit(const uint8_t* task, bool& out);

    bool TryDistSqObjects(const uint8_t* craft, const uint8_t* him,
                          float& distSq);
    bool TryEnemyActivityState(uint8_t* him, int& state);

    // Reads the game's SidewaysAndClose with success and value kept
    // DISTINCT: returns false when the evidence is unavailable (helpers
    // unbound, interface slot unreadable, SEH fault) and only then leaves
    // `value` untouched. Callers must gate any override on the return
    // value - a false predicate is evidence, a failed read is not.
    bool TrySidewaysAndCloseValue(uint8_t* craft, uint8_t* him, bool& value);

    // Game-address-backed operations; bound by the .cpp at install time.
    using FnDoSlide = void(__thiscall*)(void* task);
    using FnSaC = bool(__cdecl*)(void* craftSelf, void* himSelf);
    using FnGetTime = float(__cdecl*)();

    extern FnDoSlide g_DoSlide;
    extern FnSaC g_SaC;
    extern FnGetTime g_GetTime;

    bool TrySidewaysAndClose(uint8_t* craft, uint8_t* him);
    bool TryRunDoSlide(uint8_t* task);
    float GameTime();

} // namespace bz14
