// shadow_far_distance_hook.cpp
// BZR Open Shim - shadow far distance correction: detours the game's
// shadow-apply routine and re-issues setShadowFarDistance with the PSSM
// outer split, split out of bzr_hooks.cpp.
#include "bzr_hooks.h"
#include "bzr_object_layout.h"
#include "bzr_hooks_internal.h"
#include "engine_globals.h"
#include "game_state.h"
#include "openshim_ini.h"
#include "openshim_preset_migration.h"
#include "openshim_assets.h"
#include "terrain_proxy.h"
#include "terrain_tile_blend.h"
#include "bzr_options_ui.h"
#include "remembered_mesh_bounds_table.h"
#include "patches.h"
#include "patcher.h"
#include "fog_wake_feature.h"
#include "mp_vehicle_preview_fix.h"
#include "shim_log.h"
#include "x86_length.h"
#include "ogre_shader_cache.h"
#include "ogre_enhanced_light_selection.h"
#include "render_effect_intent.h"
#include "render_profile_runtime.h"
#include "native_ui.h"
#include "../engine/native_ui_validation.h"
#include "ogre_animation_profiler.h"
#include "ogre_profiler_algorithms.h"
#include "weapon_convergence.h"
#include "headlight_falloff.h"
#include "shadow_far_distance.h"
#include "sun_flash.h"
#include "chunk_batch_invalidation.h"
#include "ai_range_policy.h"
#include "lcbench_safety_policy.h"
#include "hook_engine.h"
#include "ui_performance.h"
#include "openshim_events.h"
#include "player_kill_trace.h"
#include "net_optimizer.h"
#include "pond_class_label.h"
#include <Windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <array>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <intrin.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <exception>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <new>
#include <string>
#include <string_view>
#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace BZROpenShim
{
    using namespace Hooks;

    // --- Shadow far distance correction ------------------------------------
    // (on by default; OPENSHIM_SHADOW_FAR_DISTANCE=stock opts out)
    //
    // Root cause (reverse_engineering/shadow_cutoff_root_cause_20260825.md):
    // FUN_00680fe0 writes SceneManager::setShadowFarDistance(128.0) for every
    // shadow quality, while the PSSM receiver shaders trust cascade 3 out to
    // the 256 m outer split. Ogre's Focused/LiSPSM fit clips the cascade
    // intersection body at the shadow far distance, so cascade 3's fitted
    // coverage ends at ~128 m; receivers between 128-256 m sample outside the
    // shadow map (white border = fully lit). That is the reported hard shadow
    // terminator.
    //
    // This detours the game's own shadow-apply routine and, after every stock
    // apply, re-issues the game's own virtual setter with the corrected
    // distance. It is deliberately narrow:
    //   - defaults to the 256 m outer split; OPENSHIM_SHADOW_FAR_DISTANCE
    //     accepts another distance, or "stock"/"off"/"128" to opt out
    //     entirely, in which case nothing is installed and the game runs
    //     stock-exact;
    //   - applies only when the settings say PSSM and the stock value was
    //     observed (fail closed otherwise);
    //   - touches no material LOD, shader, split distance, or headlight state.
    namespace ShadowFarOverride
    {
        // FUN_00680fe0: shadow-texture/PSSM/viewport-scheme apply.
        constexpr uintptr_t kShadowApplyFnRva = 0x00280FE0;
        // DAT_0094672c -> settings struct; +0x25 shadow quality (sbyte).
        constexpr uintptr_t kShadowSettingsPtrRva = 0x0054672C;
        // 0x008ED0BC: per-quality mode bytes (0 = single map, 1 = PSSM).
        constexpr uintptr_t kShadowModeTableRva = 0x004ED0BC;
        // Validated GOG 2.2.301 module identities (exe SHA-256
        // 8D71F56C...; OgreMain SHA-256 E5E69396... — PE timestamp/size here,
        // full-hash checks exist in the features that write memory elsewhere).
        constexpr DWORD kExpectedExeTimestamp = 0x58D9D6CC;
        constexpr DWORD kExpectedExeImageSize = 0x0290F000;
        constexpr DWORD kExpectedOgreTimestamp = 0x5866BF6A;
        constexpr DWORD kExpectedOgreImageSize = 0x00A65000;
        // SceneManager vtable slots, confirmed two ways: FUN_00680fe0 calls
        // slot +0x394 with 128.0 between the shadow-texture and per-type-count
        // writes, and shipped Light::getShadowFarDistance (RVA 0x21F430)
        // forwards to slot +0x398 when the light has no own distance.
        constexpr SIZE_T kVtableSetSlot = 0x394 / sizeof(void*);
        constexpr SIZE_T kVtableGetSlot = 0x398 / sizeof(void*);
        constexpr float kStockFarDistance = 128.0f;
        constexpr int kMaxTelemetryLines = 16;

        using FnGetFarDistance = float(__thiscall*)(void*);
        using FnSetFarDistance = void(__thiscall*)(void*, float);

        InlineDetour32 g_ApplyDetour = {};
        float g_OverrideDistance = 0.0f;
        bool g_InstallAttempted = false;
        int g_TelemetryLines = 0;

        // The Win32 half only. What the string means lives in
        // include/shadow_far_distance.h, where it is unit-tested -- including
        // the case that matters most, which is what an absent setting does.
        float ReadOverrideDistance()
        {
            char buffer[32] = {};
            const DWORD length = GetEnvironmentVariableA(
                "OPENSHIM_SHADOW_FAR_DISTANCE", buffer, sizeof(buffer));
            const bool overlong = (length >= sizeof(buffer));
            const char* configured = (length == 0 || overlong) ? nullptr : buffer;

            const openshim::shadow::FarDistanceDecision decision =
                openshim::shadow::DecideFarDistance(configured);

            if (overlong || decision.source == openshim::shadow::FarDistanceSource::Rejected)
            {
                // Fail closed to stock rather than to the default: quietly
                // applying the fix after refusing what was asked for would
                // make the refusal invisible.
                LogShimA(LogLevel::Warn, "SHADOWFAR",
                    "rejected OPENSHIM_SHADOW_FAR_DISTANCE=%hs (want a finite "
                    "distance in [%.0f, %.0f], or stock/off to keep the stock "
                    "%.0f m clip); leaving shadow far distance alone",
                    overlong ? "<too long>" : buffer,
                    static_cast<double>(openshim::shadow::kMinFarDistance),
                    static_cast<double>(openshim::shadow::kMaxFarDistance),
                    static_cast<double>(kStockFarDistance));
                return 0.0f;
            }

            if (decision.source == openshim::shadow::FarDistanceSource::OptedOut)
            {
                LogShimA(LogLevel::Info, "SHADOWFAR",
                    "opted out; keeping the stock %.0f m shadow far distance",
                    static_cast<double>(kStockFarDistance));
                return 0.0f;
            }

            LogShimA(LogLevel::Info, "SHADOWFAR",
                "shadow far distance %.1f m (%hs); stock clips the cascade fit "
                "at %.0f m while the receiver selects cascade 3 to %.0f m",
                static_cast<double>(decision.distance),
                openshim::shadow::SourceName(decision.source),
                static_cast<double>(kStockFarDistance),
                static_cast<double>(openshim::shadow::kOuterSplitDistance));
            return decision.distance;
        }

        bool ModuleIdentityMatches(HMODULE module,
                                   DWORD expectedTimestamp,
                                   DWORD expectedImageSize)
        {
            if (!module)
                return false;
            __try
            {
                const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(module);
                if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                    return false;
                const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS*>(
                    reinterpret_cast<const uint8_t*>(module) + dos->e_lfanew);
                return nt->Signature == IMAGE_NT_SIGNATURE
                    && nt->FileHeader.TimeDateStamp == expectedTimestamp
                    && nt->OptionalHeader.SizeOfImage == expectedImageSize;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Telemetry field: which render system the game actually selected.
        // Both render-system DLLs are loaded at startup regardless of choice,
        // so module presence is meaningless here — parse Ogre.cfg instead,
        // exactly the signal the profiler's ReadConfiguredRenderer uses.
        const char* ActiveRendererName()
        {
            static char name[16] = "";
            static bool resolved = false;
            if (!resolved)
            {
                resolved = true;
                char path[MAX_PATH] = {};
                const DWORD length = GetModuleFileNameA(nullptr, path, MAX_PATH);
                char* slash = length ? std::strrchr(path, '\\') : nullptr;
                if (slash)
                {
                    strcpy_s(slash + 1,
                             MAX_PATH - static_cast<size_t>(slash + 1 - path),
                             "Ogre.cfg");
                    std::ifstream file(path);
                    std::string line;
                    while (std::getline(file, line))
                    {
                        if (line.compare(0, 14, "Render System=") == 0)
                        {
                            if (line.find("Direct3D11") != std::string::npos)
                                strcpy_s(name, "Direct3D11");
                            else if (line.find("Direct3D9") != std::string::npos)
                                strcpy_s(name, "Direct3D9");
                            break;
                        }
                    }
                }
            }
            return name[0] ? name : "unknown";
        }

        // g_TelemetryLines budgets only the log lines below. It must not gate
        // the functional re-apply: the stock game re-issues its own
        // setShadowFarDistance on every mission load and quality change, and
        // an override that stopped re-applying after sixteen of those would
        // silently hand the 128 m stock clip back mid-session.
        static bool TelemetryBudgetLeft()
        {
            return g_TelemetryLines < kMaxTelemetryLines;
        }

        void ApplyAfterStock()
        {
            if (g_OverrideDistance <= 0.0f)
                return;

            __try
            {
                const HMODULE exe = GetModuleHandleA(nullptr);
                auto* settingsPtr = *reinterpret_cast<uint8_t**>(
                    reinterpret_cast<uintptr_t>(exe) + kShadowSettingsPtrRva);
                int quality = -1;
                bool pssm = false;
                if (settingsPtr)
                {
                    quality = *reinterpret_cast<int8_t*>(settingsPtr + 0x25);
                    if (quality >= 0 && quality <= 4)
                    {
                        pssm = *reinterpret_cast<const int8_t*>(
                            reinterpret_cast<uintptr_t>(exe)
                            + kShadowModeTableRva + quality) != 0;
                    }
                }

                void* sceneManager = GetOgreSceneManagerRuntime();
                if (!sceneManager)
                {
                    if (TelemetryBudgetLeft())
                    {
                        LogShimA(LogLevel::Warn, "SHADOWFAR",
                            "no SceneManager runtime pointer; override not applied");
                        ++g_TelemetryLines;
                    }
                    return;
                }

                auto** vtable = *reinterpret_cast<FnGetFarDistance***>(sceneManager);
                const void* getFar = reinterpret_cast<const void*>(
                    vtable[kVtableGetSlot]);
                void* setFar = reinterpret_cast<void*>(vtable[kVtableSetSlot]);
                const HMODULE ogre = GetModuleHandleA("OgreMain.dll");
                const uintptr_t ogreBegin = reinterpret_cast<uintptr_t>(ogre);
                const uintptr_t ogreEnd = ogreBegin + kExpectedOgreImageSize;
                if (reinterpret_cast<uintptr_t>(getFar) < ogreBegin
                    || reinterpret_cast<uintptr_t>(getFar) >= ogreEnd
                    || reinterpret_cast<uintptr_t>(setFar) < ogreBegin
                    || reinterpret_cast<uintptr_t>(setFar) >= ogreEnd)
                {
                    if (TelemetryBudgetLeft())
                    {
                        LogShimA(LogLevel::Warn, "SHADOWFAR",
                            "vtable slots outside OgreMain; override not applied");
                        ++g_TelemetryLines;
                    }
                    return;
                }

                const float stock = reinterpret_cast<FnGetFarDistance>(
                    const_cast<void*>(getFar))(sceneManager);
                if (!pssm)
                {
                    // Command-line mission launches skip pilot-profile
                    // loading, so the settings struct legitimately still says
                    // -1 during early applies. Log the first two, then stay
                    // quiet so later applies (after a runtime quality change)
                    // keep telemetry budget.
                    if (TelemetryBudgetLeft())
                        ++g_TelemetryLines;
                    if (g_TelemetryLines <= 2)
                    {
                        LogShimA(LogLevel::Info, "SHADOWFAR",
                            "requested=%.2f stock=%.2f override=%.2f "
                            "applied=0 effective=%.2f renderer=%hs "
                            "quality=%d pssm=%hs action=skipped "
                            "reason=pssm-disabled",
                            static_cast<double>(stock),
                            static_cast<double>(stock),
                            static_cast<double>(g_OverrideDistance),
                            static_cast<double>(stock),
                            ActiveRendererName(), quality,
                            pssm ? "yes" : "no");
                    }
                    return;
                }
                if (stock != kStockFarDistance)
                {
                    if (TelemetryBudgetLeft())
                    {
                        LogShimA(LogLevel::Warn, "SHADOWFAR",
                            "requested=%.2f stock=%.2f override=%.2f applied=0 "
                            "effective=%.2f renderer=%hs quality=%d pssm=%hs "
                            "action=skipped reason=unexpected-stock-value",
                            static_cast<double>(stock),
                            static_cast<double>(stock),
                            static_cast<double>(g_OverrideDistance),
                            static_cast<double>(stock),
                            ActiveRendererName(), quality,
                            pssm ? "yes" : "no");
                        ++g_TelemetryLines;
                    }
                    return;
                }

                reinterpret_cast<FnSetFarDistance>(setFar)(
                    sceneManager, g_OverrideDistance);
                if (TelemetryBudgetLeft())
                {
                    const float effective = reinterpret_cast<FnGetFarDistance>(
                        const_cast<void*>(getFar))(sceneManager);
                    LogShimA(LogLevel::Info, "SHADOWFAR",
                        "requested=%.2f stock=%.2f override=%.2f applied=%.2f "
                        "effective=%.2f renderer=%hs quality=%d pssm=%hs "
                        "action=applied",
                        static_cast<double>(stock),
                        static_cast<double>(stock),
                        static_cast<double>(g_OverrideDistance),
                        static_cast<double>(g_OverrideDistance),
                        static_cast<double>(effective),
                        ActiveRendererName(), quality, pssm ? "yes" : "no");
                    ++g_TelemetryLines;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                if (TelemetryBudgetLeft())
                {
                    LogShimA(LogLevel::Warn, "SHADOWFAR",
                        "exception while applying override; stock state retained");
                    ++g_TelemetryLines;
                }
            }
        }

        void __cdecl ApplyHook()
        {
            // Stock behaviour first, exactly as the game wrote it.
            reinterpret_cast<void(__cdecl*)()>(g_ApplyDetour.trampoline)();
            ApplyAfterStock();
        }
    }

    void InstallShadowFarOverrideIfPossible()
    {
        using namespace ShadowFarOverride;
        if (g_InstallAttempted)
            return;

        // On by default. ReadOverrideDistance returns 0 only when the user
        // opted out or asked for something unusable, and 0 leaves the stock
        // clip and installs no detour at all.
        g_OverrideDistance = ReadOverrideDistance();
        g_InstallAttempted = true;
        if (g_OverrideDistance <= 0.0f)
            return;

        // The apply routine lives in the exe; OgreMain must be present for the
        // runtime vtable resolution, so retry until it loads.
        const HMODULE exe = GetModuleHandleA(nullptr);
        const HMODULE ogre = GetModuleHandleA("OgreMain.dll");
        if (!exe || !ogre)
        {
            g_InstallAttempted = false;
            return;
        }

        if (!ModuleIdentityMatches(exe, kExpectedExeTimestamp, kExpectedExeImageSize)
            || !ModuleIdentityMatches(ogre, kExpectedOgreTimestamp, kExpectedOgreImageSize))
        {
            LogShimA(LogLevel::Warn, "SHADOWFAR",
                "unsupported exe/OgreMain build; shadow-far override not installed");
            return;
        }

        // Prologue: push ebp; mov ebp,esp; sub esp,0x94 — three complete
        // instructions, so the verbatim-copy trampoline is instruction-safe.
        static const uint8_t expected[] =
            { 0x55, 0x8B, 0xEC, 0x81, 0xEC, 0x94, 0x00, 0x00, 0x00 };
        const uintptr_t target = reinterpret_cast<uintptr_t>(exe) + kShadowApplyFnRva;
        if (!InstallInlineDetour32(g_ApplyDetour, target,
                reinterpret_cast<void*>(&ApplyHook), sizeof(expected),
                expected, sizeof(expected)))
        {
            LogShimA(LogLevel::Warn, "SHADOWFAR",
                "apply-routine prologue mismatch; override failed closed");
            return;
        }

        LogShimA(LogLevel::Info, "SHADOWFAR",
            "installed override=%.2f applyRva=0x%08lX (stock %.2f reissued "
            "after each stock apply; stock-exact when the env var is unset)",
            static_cast<double>(g_OverrideDistance),
            static_cast<unsigned long>(kShadowApplyFnRva),
            static_cast<double>(kStockFarDistance));
    }
}
