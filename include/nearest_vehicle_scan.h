// The body of UnitTask::NearestVehicle (GOG 0x00463FC0), written once so the
// shim's replacement and its unit test run the same code.
//
// Every step below mirrors the GOG disassembly, in the same order, with the
// same engine calls; reverse_engineering/ai_nearest_vehicle_fast_20261111.md
// cites each address. The only things it drops are the stock helpers that do
// no work: the vector iterator calls (plain pointer copies and compares,
// 0x0041FBD0 .. 0x00421F70), the cargo getter (one byte read, 0x0045BBC0),
// and the by-value Vector copies and stack-cookie frames of Dist3D_Squared
// (0x004620B0) and Vector subtract (0x004401A0).
//
// Engine is a policy type with:
//   Item* const* Begin()      -- the list's first slot, read once (0x00463FE9)
//   Item* const* End()        -- the list's end slot, read every pass (0x00464005)
//   bool  IsCargo(Item*)      -- byte [obj+0x9C] != 0 (0x0045BBCA)
//   uint32_t ClassSig(Item*)  -- obj class (vtbl[0]) +0x14
//   uint32_t ClassLabel(Item*)-- obj class (vtbl[0]) +0x1C, a second vtbl[0] call
//   const Vec3* Position(Item*) -- vtbl[3]
// Each accessor that is a virtual call in stock must make exactly that one
// call, so the engine sees the same calls in the same order.
#pragma once

#include <cstdint>
#include <xmmintrin.h>

namespace BZROpenShim
{
    namespace NearestVehicleScan
    {
        // Class signatures compared at 0x0046405C, 0x00464075 and 0x004640B7.
        constexpr uint32_t kSigTug = 0x54554700u;      // "\0GUT"
        constexpr uint32_t kSigRecycler = 0x52435943u; // "CYCR"
        constexpr uint32_t kSigTorpedo = 0x544F5250u;  // "PROT"

        // Starting best distance, the float at 0x008A2EB0 (0x7149F2CA).
        constexpr float kNoneYet = 1e30f;

        struct Vec3
        {
            float x;
            float y;
            float z;
        };

        // Dist3D_Squared(a, b) at 0x004620B0: Vector subtract (0x004401A0)
        // computes a - b one subss per axis, then (dx*dx + dy*dy) + dz*dz,
        // one SSE single op each (0x0046211B..0x0046213D). The intrinsics pin
        // that order and precision: the shim builds with /arch:IA32, where
        // plain float code would use x87 registers.
        inline float DistSquared(const Vec3& a, const Vec3& b)
        {
            const __m128 dx = _mm_sub_ss(_mm_load_ss(&a.x), _mm_load_ss(&b.x));
            const __m128 dy = _mm_sub_ss(_mm_load_ss(&a.y), _mm_load_ss(&b.y));
            const __m128 dz = _mm_sub_ss(_mm_load_ss(&a.z), _mm_load_ss(&b.z));
            __m128 sum = _mm_add_ss(_mm_mul_ss(dx, dx), _mm_mul_ss(dy, dy));
            sum = _mm_add_ss(sum, _mm_mul_ss(dz, dz));
            float out;
            _mm_store_ss(&out, sum);
            return out;
        }

        // comiss best, d; jbe skip (0x00464113): take d only when best > d,
        // ordered, so the first minimum in list order wins and a NaN never
        // does.
        inline bool Closer(float best, float d)
        {
            return _mm_comigt_ss(_mm_set_ss(best), _mm_set_ss(d)) != 0;
        }

        template <class Engine, class Item>
        Item* Scan(Engine& engine, Item* craft, const Vec3* position)
        {
            float best = kNoneYet;
            Item* result = nullptr;
            for (Item* const* it = engine.Begin(); it != engine.End(); ++it)
            {
                Item* const obj = *it;
                if (obj == craft) // 0x0046402E
                    continue;
                if (engine.IsCargo(obj)) // 0x00464038
                    continue;
                const uint32_t sig = engine.ClassSig(obj); // 0x00464054
                if (sig == kSigTug && engine.ClassSig(craft) == kSigRecycler) // 0x00464063..0x0046407C
                    continue;
                const uint32_t label = engine.ClassLabel(obj); // 0x00464091
                if (label == 5 || label == 7 || label == 2 || label == 10) // 0x00464099..0x004640AF
                    continue;
                if (label == 3 && sig != kSigTorpedo) // 0x004640B1..0x004640BE
                    continue;
                const Vec3* const where = engine.Position(obj); // 0x004640D4
                // The craft position is copied fresh on every pass (0x004640EB).
                const float d = DistSquared(*position, *where); // 0x00464103
                if (Closer(best, d))
                {
                    best = d;
                    result = obj;
                }
            }
            return result;
        }
    }
}
