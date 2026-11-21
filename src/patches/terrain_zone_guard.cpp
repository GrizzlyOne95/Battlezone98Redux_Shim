// terrain_zone_guard.cpp -- the terrain zone tables stay inside their bounds.
//
// GOG Redux 2.2.301 (FUN_0077e230.c, FUN_00784100.c, FUN_00786340.c).
//
// 1. Zone-table build 0x0077E230 (void __cdecl(void), 6-byte entry detour,
//    stolen 55 8B EC 83 EC 34). When every zone of the TRN area lies in
//    -24..103 the stock function runs unchanged. Otherwise the area would be
//    written outside heightTable 0x02CC5108 / materialTable 0x02CD99A0, so the
//    hook logs which TRN value is out of range and then:
//      a. sets width/depth to 0 and calls the stock function: every fill,
//         the 0x1000 engine rand() calls (MP determinism), the defaults and
//         the default zone pointer 0x02CC5104 run exactly as stock, and the
//         zone loop runs zero times;
//      b. restores width/depth, writes the in-range zones with the engine's
//         own 0x00785C00 / 0x00785C20 and the stock zone numbering;
//      c. writes the eight trailing bounds globals from the full area, as
//         stock does.
//    It also warns once per load when the .hg2 holds fewer zone blocks than
//    the TRN area needs (log only).
// 2. Height sampler 0x00784100 (uint16 __cdecl(uint x, uint z), replaced
//    outright behind a 6-byte detour, stolen 55 8B EC 83 EC 08). Same
//    arithmetic as stock, but the zone pointer it reads (table entry, or the
//    default pointer 0x02CC5104 for an index outside the table) must be the
//    default zone 0x02C119D0 or a whole zone block of the loaded .hg2;
//    anything else reads the default zone instead and is logged (budgeted).
//
// Every absolute address below is an operand inside the byte-guarded rows
// TerrainBuildZoneTables, TerrainHeightSample and TerrainZoneHeightPointer,
// except the .hg2 size 0x02C319DC (FUN_00786340.c line 96, FUN_00829130's
// size out-parameter next to the pointer 0x02C319D8) and the TRN path
// 0x02CC40C0 (FUN_00786340.c lines 39 and 87, the file every key is read from).

#include "terrain_zone_guard.h"
#include "terrain_zone_guard_install.h"

#include "bzr_options_ui.h"
#include "env_switch_table.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace TerrainZones
    {
        namespace
        {
            constexpr const char* kComponent = "TERRAINZONES";

            constexpr uintptr_t kMinXZones = 0x02CC40B0;
            constexpr uintptr_t kMinZZones = 0x02CC40AC;
            constexpr uintptr_t kWidthZones = 0x02CC40A8;
            constexpr uintptr_t kDepthZones = 0x02CC40B4;
            constexpr uintptr_t kTrnPath = 0x02CC40C0;
            constexpr size_t kTrnPathMax = 260;

            constexpr uintptr_t kHeightTable = 0x02CC5108;
            constexpr uintptr_t kMaterialTable = 0x02CD99A0;
            constexpr uintptr_t kDefaultZonePointer = 0x02CC5104;
            constexpr uintptr_t kDefaultZone = 0x02C119D0;
            constexpr uintptr_t kHg2Pointer = 0x02C319D8;
            constexpr uintptr_t kHg2Size = 0x02C319DC;
            constexpr uintptr_t kBoundsScale = 0x008A285C;  // 5.0f

            constexpr uintptr_t kMinXUnits = 0x02CE99C0;
            constexpr uintptr_t kMaxXUnits = 0x02CE99A0;
            constexpr uintptr_t kMinZUnits = 0x02CD9984;
            constexpr uintptr_t kMaxZUnits = 0x02CE99C4;
            constexpr uintptr_t kMinXMeters = 0x02CD912C;
            constexpr uintptr_t kMaxXMeters = 0x02CD9124;
            constexpr uintptr_t kMinZMeters = 0x02CD9130;
            constexpr uintptr_t kMaxZMeters = 0x02CD9128;

            const uint8_t kBuildPrologue[6] = { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x34 };
            const uint8_t kSamplePrologue[6] = { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x08 };

            template <typename T>
            T& At(uintptr_t address)
            {
                return *reinterpret_cast<T*>(address);
            }

            using FnBuild = void(__cdecl*)();
            using FnZonePointer = uintptr_t(__cdecl*)(int32_t n);

            std::atomic<bool> g_BuildDone{ false };
            std::atomic<bool> g_SampleDone{ false };
            InlineDetour32 g_BuildDetour = {};
            InlineDetour32 g_SampleDetour = {};
            FnBuild volatile g_OrigBuild = nullptr;
            FnZonePointer g_HeightZone = nullptr;
            FnZonePointer g_MaterialZone = nullptr;
            float g_Scale = 5.0f;
            volatile long g_SampleLogBudget = 8;

            void ReadTrnPath(char (&out)[kTrnPathMax])
            {
                out[0] = '\0';
                __try
                {
                    const volatile char* src = reinterpret_cast<const volatile char*>(kTrnPath);
                    size_t i = 0;
                    for (; i + 1 < kTrnPathMax && src[i] != '\0'; ++i)
                        out[i] = src[i];
                    out[i] = '\0';
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    out[0] = '\0';
                }
            }

            Layout ReadLayout()
            {
                Layout l;
                l.minX = At<int32_t>(kMinXZones);
                l.minZ = At<int32_t>(kMinZZones);
                l.width = At<int32_t>(kWidthZones);
                l.depth = At<int32_t>(kDepthZones);
                return l;
            }

            void LogOutOfRange(const Layout& l, uint32_t bits, const char* trn)
            {
                // Zones are 1280 m; the TRN keys are in metres.
                LogShimA(LogLevel::Warn, kComponent,
                         "%s: TRN area MinX=%d MinZ=%d Width=%d Depth=%d (zones of 1280 m; metres %d/%d/%d/%d) "
                         "puts zones outside %d..%d, which stock writes past the terrain zone tables. Out of "
                         "range:%s%s%s%s. Zones outside the table are skipped (they read as flat default "
                         "terrain); adjust MinX/MinZ (or Width/Depth) so every zone fits.",
                         trn[0] ? trn : "(unknown map)", l.minX, l.minZ, l.width, l.depth, l.minX * 1280,
                         l.minZ * 1280, l.width * 1280, l.depth * 1280, kMinZone, kMaxZone,
                         (bits & kMinXLow) ? " MinX too low" : "", (bits & kMaxXHigh) ? " MinX+Width too high" : "",
                         (bits & kMinZLow) ? " MinZ too low" : "", (bits & kMaxZHigh) ? " MinZ+Depth too high" : "");
            }

            void CheckHg2(const Layout& l, const char* trn)
            {
                const uintptr_t hg2 = At<uintptr_t>(kHg2Pointer);
                const uint32_t size = At<uint32_t>(kHg2Size);
                if (!Hg2Truncated(hg2, size, l))
                    return;
                LogShimA(LogLevel::Warn, kComponent,
                         "%s: the .hg2 holds %u bytes but the TRN area of %d x %d zones needs %llu; the zones "
                         "past the end point outside the file data (the height sample guard reads them as flat).",
                         trn[0] ? trn : "(unknown map)", size, l.width, l.depth,
                         static_cast<unsigned long long>(kHg2Header +
                                                         static_cast<uint64_t>(l.width) * l.depth * kHg2ZoneBytes));
            }

            void __cdecl BuildHook()
            {
                const Layout l = ReadLayout();
                const uint32_t bits = Check(l);
                char trn[kTrnPathMax];
                ReadTrnPath(trn);
                CheckHg2(l, trn);
                if (bits == 0)
                {
                    g_OrigBuild();
                    return;
                }
                LogOutOfRange(l, bits, trn);

                // a. Stock fills, rand() sequence and defaults; empty zone loop.
                At<int32_t>(kWidthZones) = 0;
                At<int32_t>(kDepthZones) = 0;
                g_OrigBuild();
                At<int32_t>(kWidthZones) = l.width;
                At<int32_t>(kDepthZones) = l.depth;

                // b. In-range zones only, stock numbering.
                uintptr_t* heights = reinterpret_cast<uintptr_t*>(kHeightTable);
                uintptr_t* materials = reinterpret_cast<uintptr_t*>(kMaterialTable);
                const uint32_t written = BuildBounded(l, [&](int32_t idx, int32_t n) {
                    heights[idx] = g_HeightZone(n);
                    materials[idx] = g_MaterialZone(n);
                });

                // c. Trailing bounds from the full area, as stock.
                const Bounds b = ComputeBounds(l, g_Scale);
                At<int32_t>(kMinXUnits) = b.minXUnits;
                At<int32_t>(kMaxXUnits) = b.maxXUnits;
                At<int32_t>(kMinZUnits) = b.minZUnits;
                At<int32_t>(kMaxZUnits) = b.maxZUnits;
                At<float>(kMinXMeters) = b.minXMeters;
                At<float>(kMaxXMeters) = b.maxXMeters;
                At<float>(kMinZMeters) = b.minZMeters;
                At<float>(kMaxZMeters) = b.maxZMeters;

                LogShimA(LogLevel::Warn, kComponent, "bounded build wrote %u of %lld zones", written,
                         static_cast<long long>(l.width) * l.depth);
            }

            void LogBadPointer(int32_t index, uintptr_t p)
            {
                if (InterlockedDecrement(&g_SampleLogBudget) < 0)
                    return;
                LogShimA(LogLevel::Warn, kComponent,
                         "height sample: zone pointer 0x%08X (%s, index %d) is neither the default zone nor a "
                         ".hg2 block; reading flat default terrain instead",
                         static_cast<unsigned>(p), (index >= 0 && index < kTableEntries) ? "table" : "default slot",
                         static_cast<int>(index));
            }

            // Stock returns the 12-bit height in eax (movzx, so the upper
            // bits are zero); return 32 bits to keep that.
            uint32_t __cdecl SampleHook(uint32_t x, uint32_t z)
            {
                const Sample s = Locate(x, z);
                uintptr_t p = s.inTable ? reinterpret_cast<const uintptr_t*>(kHeightTable)[s.index]
                                        : At<uintptr_t>(kDefaultZonePointer);
                if (!ZonePointerValid(p, kDefaultZone, At<uintptr_t>(kHg2Pointer), At<uint32_t>(kHg2Size)))
                {
                    LogBadPointer(s.index, p);
                    p = kDefaultZone;
                }
                return reinterpret_cast<const uint16_t*>(p)[s.offset] & 0xFFFu;
            }

            bool Fail(const char* what, const char* feature)
            {
                LogShimA(LogLevel::Warn, kComponent, "%s; leaving the stock %s", what, feature);
                return false;
            }

            bool Enabled(const char* env, const char* legacy)
            {
                bool enabled = true;
                const EnvSwitches::EnvSwitch rows[] = {
                    { &enabled, EnvSwitches::Kind::KillSwitch, env, legacy },
                };
                EnvSwitches::Apply(rows, EnvFlagEnabled);
                return enabled;
            }

            bool InstallBuild()
            {
                uint32_t build = 0, heightZone = 0, materialZone = 0;
                const HookEngine::EngineRow rows[] = {
                    { "TerrainBuildZoneTables", &build },
                    { "TerrainZoneHeightPointer", &heightZone },
                    { "TerrainZoneMaterialPointer", &materialZone },
                };
                if (!HookEngine::BindEngineRows("Terrain zone table guard", rows))
                    return Fail("an engine function failed its byte guard", "zone-table build");

                float scale = 0.0f;
                if (!HookEngine::ReadMemory(static_cast<uint32_t>(kBoundsScale), &scale, sizeof(scale)) ||
                    scale != 5.0f)
                    return Fail("the bounds scale constant is not 5.0f", "zone-table build");
                g_Scale = scale;
                g_HeightZone = reinterpret_cast<FnZonePointer>(static_cast<uintptr_t>(heightZone));
                g_MaterialZone = reinterpret_cast<FnZonePointer>(static_cast<uintptr_t>(materialZone));

                if (!InstallInlineDetour32(g_BuildDetour, build, reinterpret_cast<void*>(&BuildHook),
                                           sizeof(kBuildPrologue), kBuildPrologue, sizeof(kBuildPrologue),
                                           reinterpret_cast<void* volatile*>(&g_OrigBuild)))
                    return Fail("the build detour could not be installed", "zone-table build");

                LogShimA(LogLevel::Info, kComponent,
                         "zone table guard installed: build=0x%08X trampoline=0x%08X zones %d..%d", build,
                         static_cast<unsigned>(reinterpret_cast<uintptr_t>(g_OrigBuild)), kMinZone, kMaxZone);
                return true;
            }

            bool InstallSample()
            {
                uint32_t sample = 0;
                const HookEngine::EngineRow rows[] = {
                    { "TerrainHeightSample", &sample },
                };
                if (!HookEngine::BindEngineRows("Terrain height sample guard", rows))
                    return Fail("the height sampler failed its byte guard", "height sampler");

                if (!InstallInlineDetour32(g_SampleDetour, sample, reinterpret_cast<void*>(&SampleHook),
                                           sizeof(kSamplePrologue), kSamplePrologue, sizeof(kSamplePrologue)))
                    return Fail("the sampler detour could not be installed", "height sampler");

                LogShimA(LogLevel::Info, kComponent,
                         "height sample guard installed: sampler=0x%08X default zone=0x%08X", sample,
                         static_cast<unsigned>(kDefaultZone));
                return true;
            }
        }

        void InstallTerrainZoneTableGuardIfPossible()
        {
            if (g_BuildDone.exchange(true))
                return;
            if (!Enabled("OPENSHIM_DISABLE_TERRAIN_ZONE_TABLE_GUARD", "BZR_DISABLE_TERRAIN_ZONE_TABLE_GUARD"))
            {
                LogShimA(LogLevel::Info, kComponent, "zone table guard disabled ([Fixes] TerrainZoneTableGuard = 0)");
                return;
            }
            InstallBuild();
        }

        void InstallTerrainHeightSampleGuardIfPossible()
        {
            if (g_SampleDone.exchange(true))
                return;
            if (!Enabled("OPENSHIM_DISABLE_TERRAIN_HEIGHT_SAMPLE_GUARD", "BZR_DISABLE_TERRAIN_HEIGHT_SAMPLE_GUARD"))
            {
                LogShimA(LogLevel::Info, kComponent,
                         "height sample guard disabled ([Fixes] TerrainHeightSampleGuard = 0)");
                return;
            }
            InstallSample();
        }
    }
}
