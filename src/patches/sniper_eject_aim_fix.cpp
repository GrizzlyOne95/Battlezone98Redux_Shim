// sniper_eject_aim_fix.cpp
// BZR Open Shim - keep a pilot's shot on the reticle while the pilot body is
// tilted (ejected sideways, pitched or rolled).
//
// Root cause (see reverse_engineering/sniper_eject_misalignment.md):
//   Person::Simulate (GOG 0x0059D340) ends with
//     aimPitch(+0x280) = controls.pitch(+0xC8) * 0.5
//     [if the compensation gate holds] aimPitch -= bodyFront.y (entity+0x3C)
//   i.e. it cancels the body's tilt with sin(pitch) and ignores roll.
//   Person::UpdateWeaponAim (0x005A12A0) then builds each weapon node matrix
//   as inverse(hardpoint chain) * Rx(-aimPitch). The shot leaves along that
//   node composed with the body matrix, so a pilot that is pitched or rolled
//   by more than a few degrees shoots off the reticle.
//
// Fix: the one matrix multiply in UpdateWeaponAim that builds the node matrix
// (call at 0x005A14C7) is redirected. When the stock compensation gate holds
// and the body is tilted, the node matrix is rebuilt so the shot's world
// orientation is Rx(-pitchInput) composed with the body's YAW ONLY (full
// tilt, pitch and roll, removed). A level body gives the identical stock
// matrix, so nothing changes for a standing pilot.
//
// Only the local shooter's own shot orientation is touched; no sync field is
// written (Person+0x280 is left as stock computed it).
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "hook_engine.h"
#include "bzr_options_ui.h"
#include "patcher.h"
#include "shim_log.h"

#include <Windows.h>

#include <cmath>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace Hooks
    {
        bool g_SniperEjectAimFixEnabled = true;
        bool g_SniperEjectAimFixInstalled = false;
        volatile long g_SniperEjectAimLogCount = 0;

        namespace
        {
            uint32_t g_UpdateWeaponAimAddr = 0;
            uint32_t g_AimMatrixMulCallAddr = 0;
            uint32_t g_AimMatrixMulAddr = 0;
            InlineDetour32 g_UpdateWeaponAimDetour;

            // Person being processed by the stock UpdateWeaponAim; set only
            // for the duration of that call (game simulation thread).
            void* g_CurrentPerson = nullptr;
            bool g_SelfCheckFailedLogged = false;

            using FnUpdateWeaponAim = void(__thiscall*)(void* person, uintptr_t stackArg);
            using FnMatrixMul = float*(__cdecl*)(float* out, const float* a, const float* b);
            FnUpdateWeaponAim g_UpdateWeaponAimOriginal = nullptr;

            constexpr uint32_t kProfileGlobal = 0x0094672C; // FUN_004e96a0: [0x94672C]+0x30 & 0x10

            template <typename T>
            bool ReadAt(uintptr_t address, T& out)
            {
                __try
                {
                    out = *reinterpret_cast<const volatile T*>(address);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            // Same predicate as the compensation at 0x005A09E6..0x005A0A2C
            // (FUN_0059d340:1116-1118).
            bool CompensationGateHolds(uintptr_t person, uintptr_t entity)
            {
                uint32_t entityFlags = 0;
                if (!ReadAt<uint32_t>(entity + 0x14, entityFlags))
                    return false;
                if ((entityFlags & 0x10u) != 0)
                {
                    uint32_t profile = 0, profileFlags = 0;
                    if (ReadAt<uint32_t>(kProfileGlobal, profile) && profile != 0 &&
                        ReadAt<uint32_t>(profile + 0x30, profileFlags) && (profileFlags & 0x10u) != 0)
                        return true;
                }
                uint8_t state = 0;
                uint32_t controls = 0, controlFlags = 0;
                return ReadAt<uint8_t>(person + 0x18 + 0x68, state) && state == 2 &&
                       ReadAt<uint32_t>(person + 0x230, controls) && controls != 0 &&
                       ReadAt<uint32_t>(controls + 0x114, controlFlags) && (controlFlags & 0x1000u) != 0;
            }

            // 3x3 row-major, row-vector convention (v' = v * M), matching the
            // engine's FUN_0081fe60.
            void Mul3(const float* a, const float* b, float* o)
            {
                for (int r = 0; r < 3; ++r)
                    for (int c = 0; c < 3; ++c)
                        o[r * 3 + c] = a[r * 3 + 0] * b[0 * 3 + c] +
                                       a[r * 3 + 1] * b[1 * 3 + c] +
                                       a[r * 3 + 2] * b[2 * 3 + c];
            }

            void Transpose3(const float* a, float* o)
            {
                for (int r = 0; r < 3; ++r)
                    for (int c = 0; c < 3; ++c)
                        o[c * 3 + r] = a[r * 3 + c];
            }

            // Rx(-p) exactly as FUN_0081ec40(-p) builds it (decomp 0081ec40:
            // rows (1,0,0) (0,cos p,-sin p) (0,sin p,cos p)).
            void RxNeg(float p, float* o)
            {
                const float c = std::cos(p), s = std::sin(p);
                o[0] = 1; o[1] = 0; o[2] = 0;
                o[3] = 0; o[4] = c; o[5] = -s;
                o[6] = 0; o[7] = s; o[8] = c;
            }

            // Yaw-only basis of `own` (rows = local axes in world space).
            bool LevelBasis(const float* own, float* level)
            {
                float fx = own[6], fz = own[8];
                float len = std::sqrt(fx * fx + fz * fz);
                if (len < 0.3f)
                {
                    // Nearly vertical body: the up axis carries the heading.
                    const float sign = own[7] > 0.0f ? -1.0f : 1.0f;
                    fx = sign * own[3 + 0];
                    fz = sign * own[3 + 2];
                    len = std::sqrt(fx * fx + fz * fz);
                }
                if (!(len > 1e-4f))
                    return false;
                fx /= len;
                fz /= len;
                level[0] = fz;  level[1] = 0.0f; level[2] = -fx; // right = up x front
                level[3] = 0.0f; level[4] = 1.0f; level[5] = 0.0f;
                level[6] = fx;  level[7] = 0.0f; level[8] = fz;
                return true;
            }

            // Replacement for the matrix multiply at 0x005A14C7:
            // out = a * b, a = inverse(hardpoint chain), b = Rx(-aimPitch).
            float* __cdecl AimMatrixMulHook(float* out, const float* a, const float* b)
            {
                float* result = reinterpret_cast<FnMatrixMul>(g_AimMatrixMulAddr)(out, a, b);
                void* personPtr = g_CurrentPerson;
                if (!g_SniperEjectAimFixEnabled || !personPtr)
                    return result;

                const uintptr_t person = reinterpret_cast<uintptr_t>(personPtr);
                uint32_t entityPtr = 0;
                float aimPitch = 0.0f, ownRaw[9] = {};
                if (!ReadAt<uint32_t>(person + 0xF4, entityPtr) || entityPtr == 0 ||
                    !ReadAt<float>(person + 0x280, aimPitch))
                    return result;
                for (int i = 0; i < 9; ++i)
                {
                    if (!ReadAt<float>(entityPtr + 0x20 + i * 4, ownRaw[i]))
                        return result;
                }
                if (!CompensationGateHolds(person, entityPtr))
                    return result;

                const float frontY = ownRaw[7];                 // entity+0x3C
                const float upY = ownRaw[4];
                if (std::fabs(frontY) < 1e-4f && std::fabs(upY - 1.0f) < 1e-4f)
                    return result;                              // level body: stock result is exact

                // Self-check: our Rx(-aimPitch) must reproduce b, else the
                // convention differs on this build and we stand down.
                float rx[9];
                RxNeg(aimPitch, rx);
                for (int i = 0; i < 9; ++i)
                {
                    if (std::fabs(rx[i] - b[i]) > 1e-3f)
                    {
                        if (!g_SelfCheckFailedLogged)
                        {
                            g_SelfCheckFailedLogged = true;
                            Log(L"[SNIPEJECT] Rx(-pitch) self-check failed; leaving stock aim\n");
                        }
                        return result;
                    }
                }

                float level[9];
                if (!LevelBasis(ownRaw, level))
                    return result;

                // Undo the stock sin(pitch) compensation: pitchInput = pitch + front.y.
                float rx0[9];
                RxNeg(aimPitch + frontY, rx0);

                // C = hardpoint chain rotation = transpose(a).
                // (C^T is `a` itself.)
                float chain[9];
                Transpose3(a, chain);

                // node' = a * Rx(-p0) * C * Level * Own^T * C^T
                float ownT[9], t1[9], t2[9], t3[9], t4[9], t5[9];
                Transpose3(ownRaw, ownT);
                Mul3(a, rx0, t1);
                Mul3(t1, chain, t2);
                Mul3(t2, level, t3);
                Mul3(t3, ownT, t4);
                Mul3(t4, a, t5);
                for (int i = 0; i < 9; ++i)
                {
                    if (!std::isfinite(t5[i]))
                        return result;
                }
                std::memcpy(result, t5, sizeof(t5)); // rotation floats 0..8 only

                const long n = InterlockedIncrement(&g_SniperEjectAimLogCount);
                if (n <= 6 || (n % 1024) == 0)
                {
                    Log(L"[SNIPEJECT] corrected aim for tilted pilot: front.y=%.3f up.y=%.3f pitchIn=%.3f (#%ld)\n",
                        frontY, upY, aimPitch + frontY, n);
                }
                return result;
            }

            void __fastcall UpdateWeaponAimHook(void* person, void* /*edx*/, uintptr_t stackArg)
            {
                void* previous = g_CurrentPerson;
                g_CurrentPerson = person;
                g_UpdateWeaponAimOriginal(person, stackArg);
                g_CurrentPerson = previous;
            }
        }

        void InstallSniperEjectAimFixIfPossible()
        {
            if (!g_SniperEjectAimFixEnabled || g_SniperEjectAimFixInstalled)
                return;
            static int s_bound = 0;
            if (s_bound < 0)
                return;
            if (s_bound == 0)
            {
                const HookEngine::EngineRow rows[] = {
                    { "PersonUpdateWeaponAim", &g_UpdateWeaponAimAddr },
                    { "PersonAimMatrixMulCall", &g_AimMatrixMulCallAddr },
                    { "PersonAimMatrixMul", &g_AimMatrixMulAddr },
                };
                s_bound = HookEngine::BindEngineRows("Sniper eject aim fix", rows) ? 1 : -1;
                if (s_bound < 0)
                {
                    Log(L"[SNIPEJECT] Unavailable: engine rows did not bind on this build\n");
                    return;
                }
            }

            static const uint8_t kExpectedEntry[9] = { 0x55, 0x8B, 0xEC, 0x81, 0xEC, 0x24, 0x03, 0x00, 0x00 };
            if (!InstallInlineDetour32(g_UpdateWeaponAimDetour,
                                       g_UpdateWeaponAimAddr,
                                       reinterpret_cast<void*>(UpdateWeaponAimHook),
                                       sizeof(kExpectedEntry),
                                       kExpectedEntry,
                                       sizeof(kExpectedEntry)))
            {
                s_bound = -1;
                return;
            }
            g_UpdateWeaponAimOriginal =
                reinterpret_cast<FnUpdateWeaponAim>(g_UpdateWeaponAimDetour.trampoline);

            if (!RedirectCallTarget(g_AimMatrixMulCallAddr,
                                    g_AimMatrixMulAddr,
                                    reinterpret_cast<uintptr_t>(AimMatrixMulHook)))
            {
                // The entry detour alone is harmless (it only records the
                // person); the fix stays inert without the call redirect.
                Log(L"[SNIPEJECT] Call at 0x%08X does not target 0x%08X; fix inert\n",
                    g_AimMatrixMulCallAddr, g_AimMatrixMulAddr);
                s_bound = -1;
                return;
            }

            g_SniperEjectAimFixInstalled = true;
            Log(L"[SNIPEJECT] Installed tilted-pilot aim fix entry=0x%08X mulCall=0x%08X\n",
                g_UpdateWeaponAimAddr, g_AimMatrixMulCallAddr);
        }
    }
}
