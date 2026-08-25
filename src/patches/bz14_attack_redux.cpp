// ============================================================================
// bz14_attack_redux.cpp - SEH-guarded Redux AttackTask accessors.
// Offsets and call sequences are decompile/asm-proven; see the header.
// ============================================================================

#include "bz14_attack_redux.h"

#include <Windows.h>

namespace bz14
{
    FnDoSlide g_DoSlide = nullptr;
    FnSaC g_SaC = nullptr;
    FnGetTime g_GetTime = nullptr;

    bool SehReadTaskHead(const uint8_t* task, int& curState, int& nextState,
                         uint8_t*& craft, uint8_t*& him)
    {
        __try
        {
            curState =
                *reinterpret_cast<const volatile int*>(task + kTaskCurState);
            nextState =
                *reinterpret_cast<const volatile int*>(task + kTaskNextState);
            craft = *reinterpret_cast<uint8_t* const volatile*>(task + kTaskCraft);
            him = *reinterpret_cast<uint8_t* const volatile*>(task + kTaskHimObj);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    bool SehReadFloat(const uint8_t* base, size_t offset, float& out)
    {
        __try
        {
            out = *reinterpret_cast<const float*>(base + offset);
            return std::isfinite(out);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    bool SehWriteFloat(uint8_t* base, size_t offset, float value)
    {
        __try
        {
            *reinterpret_cast<float*>(base + offset) = value;
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    bool SehWriteNextState(uint8_t* task, int value)
    {
        __try
        {
            *reinterpret_cast<volatile int*>(task + kTaskNextState) = value;
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    bool SehReadAbleToHit(const uint8_t* task, bool& out)
    {
        __try
        {
            out = *reinterpret_cast<const volatile uint8_t*>(
                      task + kTaskAbleToHit) != 0;
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            out = false;
            return false;
        }
    }

    bool TryGetPosXZ(const uint8_t* obj, float& x, float& z)
    {
        if (!obj)
            return false;
        __try
        {
            const double px = *reinterpret_cast<const double*>(
                obj + kObjTransform + kMatPositX);
            const double pz = *reinterpret_cast<const double*>(
                obj + kObjTransform + kMatPositX + 0x10);
            x = static_cast<float>(px);
            z = static_cast<float>(pz);
            return std::isfinite(x) && std::isfinite(z);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    bool TryDistSqObjects(const uint8_t* craft, const uint8_t* him,
                          float& distSq)
    {
        float cx = 0.0f, cz = 0.0f, hx = 0.0f, hz = 0.0f;
        if (!TryGetPosXZ(craft, cx, cz) || !TryGetPosXZ(him, hx, hz))
            return false;
        const float dx = cx - hx;
        const float dz = cz - hz;
        distSq = dx * dx + dz * dz;
        return std::isfinite(distSq);
    }

    // Slot-12 self accessor on the embedded interface at obj+0x18; mirrors
    // stock: this = obj+0x18, callee = (*(obj+0x18))[12] (asm @0x478D58).
    static bool TrySlotSelf(uint8_t* obj, void*& out)
    {
        out = nullptr;
        if (!obj)
            return false;
        __try
        {
            void* iface = obj + kObjIface;
            void** vptr = *reinterpret_cast<void***>(iface);
            if (!vptr)
                return false;
            using Fn = void*(__thiscall*)(void*);
            const Fn fn = reinterpret_cast<Fn>(vptr[12]);
            out = fn(iface);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            out = nullptr;
            return false;
        }
    }

    bool TryEnemyActivityState(uint8_t* him, int& state)
    {
        state = -1;
        void* self = nullptr;
        if (!TrySlotSelf(him, self) || !self)
            return false;
        __try
        {
            state = *reinterpret_cast<const volatile int*>(
                reinterpret_cast<uint8_t*>(self) + 0x84);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            state = -1;
            return false;
        }
    }

    // Success and value are deliberately distinct: every failure path
    // returns false WITHOUT touching `value`, so callers can tell a genuine
    // false predicate from missing evidence (fail-closed requirement).
    bool TrySidewaysAndCloseValue(uint8_t* craft, uint8_t* him, bool& value)
    {
        if (!g_SaC)
            return false;
        void* craftSelf = nullptr;
        void* himSelf = nullptr;
        if (!TrySlotSelf(craft, craftSelf) || !TrySlotSelf(him, himSelf))
            return false;
        __try
        {
            // Stock pushes the him-result first, craft-result second
            // (cdecl right-to-left), i.e. SaC(craftSelf, himSelf).
            value = g_SaC(craftSelf, himSelf);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    bool TryRunDoSlide(uint8_t* task)
    {
        if (!g_DoSlide)
            return false;
        __try
        {
            g_DoSlide(task);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    float GameTime()
    {
        if (!g_GetTime)
            return 0.0f;
        __try
        {
            return g_GetTime();
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return 0.0f;
        }
    }

} // namespace bz14
