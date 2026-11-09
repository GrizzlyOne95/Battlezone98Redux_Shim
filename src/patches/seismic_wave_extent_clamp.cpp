// seismic_wave_extent_clamp.cpp
// BZR Open Shim - SeismicWave extent clamp ([Fixes] SeismicWaveExtentClamp).
//
// Daywrecker's SeismicWave ordnance displaces terrain heights reversibly. All
// addresses and offsets are GOG 2.2.301 decompile (battlezone98redux.exe-6777ca):
//   - ctor FUN_005cef80 sizes the delta buffer at this+0xF4 as
//     side*side*2 bytes, side = (int)floor(r*2.0*0.2)+2, r = *(float*)(class+0x78).
//   - UpdateExtents FUN_005cf100 (__fastcall, ecx=this) stores
//     [this+0xE4]=floor((x-r)*gs), [+0xE8]=floor((z-r)*gs),
//     [+0xEC]=ceil((x+r)*gs), [+0xF0]=ceil((z+r)*gs), gs=1/Grid_Size.
//   - Restore FUN_005cf3f0 and the Simulate write loop (FUN_005cf510 L268-300)
//     walk z=E8..F0 and x=E4..EC inclusive, one buffer entry per cell. For an
//     unaligned position that is floor(D)+3 cells per axis against a buffer of
//     floor(D)+2, so every frame reads and writes one row/column past the heap
//     block; restore then subtracts garbage and leaves terrain spires/pits.
//   - Class ctor FUN_005cea80 L19-21: class+0x78 = r, class+0x7C = 1/r. The
//     write loop gives cells with normalised d^2 >= 1 a delta of 0, and the
//     max-edge cell ceil((x+r)/size) is always at least r away, so dropping it
//     discards only zero-delta cells. Clamping EC/F0 to the buffer is lossless
//     and changes no simulated height (safe in multiplayer).
// This post-hook calls the stock UpdateExtents, then clamps the two max edges.
#include "bzr_hooks.h"
#include "hook_engine.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "shim_log.h"

#include <cmath>
#include <cstdint>

namespace BZROpenShim
{
    namespace Hooks
    {
        // Released GOG 2.2.301 prologue (see patches.json SeismicWaveUpdateExtents):
        //   55 push ebp / 8B EC mov ebp,esp / 83 EC 24 sub esp,0x24 /
        //   89 4D FC mov [ebp-4],ecx  -- 9 bytes, whole instructions.
        static constexpr size_t kUpdateExtentsPatchLen = 9;
        static constexpr uint8_t kUpdateExtentsPrologue[kUpdateExtentsPatchLen] =
            { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x24, 0x89, 0x4D, 0xFC };

        typedef void(__fastcall* FnSeismicUpdateExtents)(void* self);

        static InlineDetour32 g_SeismicExtentsDetour;
        static FnSeismicUpdateExtents g_StockSeismicUpdateExtents = nullptr;
        static bool g_SeismicConfigInitialized = false;
        static bool g_SeismicClampLogged = false;
        static volatile long g_SeismicClampCount = 0;

        static void __fastcall SeismicUpdateExtentsHook(void* self)
        {
            g_StockSeismicUpdateExtents(self);

            uint8_t* t = static_cast<uint8_t*>(self);
            const uint8_t* cls = *reinterpret_cast<uint8_t* const*>(t + 0xC);
            if (!cls)
                return;
            const float r = *reinterpret_cast<const float*>(cls + 0x78);
            // Same expression order as the ctor FUN_005cef80.
            const int side = static_cast<int>(std::floor(static_cast<double>(r * 2.0f) * 0.2)) + 2;
            if (side < 1)
                return;

            const int e4 = *reinterpret_cast<int*>(t + 0xE4);
            const int e8 = *reinterpret_cast<int*>(t + 0xE8);
            int& ec = *reinterpret_cast<int*>(t + 0xEC);
            int& f0 = *reinterpret_cast<int*>(t + 0xF0);
            const int w = ec - e4 + 1;
            const int h = f0 - e8 + 1;
            bool clamped = false;
            if (w > side) { ec = e4 + side - 1; clamped = true; }
            if (h > side) { f0 = e8 + side - 1; clamped = true; }
            if (clamped)
            {
                ++g_SeismicClampCount;
                if (!g_SeismicClampLogged)
                {
                    g_SeismicClampLogged = true;
                    Log(L"[SEISMIC] clamped extents w=%d h=%d side=%d\n", w, h, side);
                }
            }
        }

        void InitializeSeismicWaveExtentClampConfig()
        {
            if (g_SeismicConfigInitialized)
                return;
            g_SeismicConfigInitialized = true;

            bool enabled = true;
            bool cfg = true;
            if (TryGetUserConfigBool(kUserConfigFixesSection, "SeismicWaveExtentClamp", cfg))
                enabled = cfg;
            if (!enabled)
            {
                Log(L"[SEISMIC] Extent clamp disabled by config\n");
                return;
            }

            uint32_t fn = 0;
            const HookEngine::EngineRow rows[] = {
                { "SeismicWaveUpdateExtents", &fn },
            };
            if (!HookEngine::BindEngineRows("SeismicWave extent clamp", rows))
                return;
            if (!ExpectedBytesMatchAt(fn, kUpdateExtentsPrologue, sizeof(kUpdateExtentsPrologue)))
            {
                Log(L"[SEISMIC] UpdateExtents prologue mismatch at 0x%08X; standing down\n", fn);
                return;
            }
            if (!InstallInlineDetour32(g_SeismicExtentsDetour, fn,
                                       reinterpret_cast<void*>(SeismicUpdateExtentsHook),
                                       kUpdateExtentsPatchLen,
                                       kUpdateExtentsPrologue, sizeof(kUpdateExtentsPrologue)))
            {
                Log(L"[SEISMIC] Failed installing UpdateExtents hook at 0x%08X\n", fn);
                return;
            }
            g_StockSeismicUpdateExtents =
                reinterpret_cast<FnSeismicUpdateExtents>(g_SeismicExtentsDetour.trampoline);
            Log(L"[SEISMIC] Extent clamp installed at 0x%08X\n", fn);
        }
    }
}
