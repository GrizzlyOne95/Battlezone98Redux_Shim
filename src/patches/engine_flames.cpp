// engine_flames.cpp
// BZR Open Shim - engine flames: runtime target resolution, the per-colour
// flame manager variants, faction jet flames and the three engine hook
// entry points (hovercraft emit, control, submit), split out of
// bzr_hooks.cpp.
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
    static FnExuGetTeamEngineFlameColor g_ExuFn_GetTeamEngineFlameColor = nullptr;

    static HMODULE g_ExuTeamEngineFlameColorModule = nullptr;

    namespace Hooks
    {
        constexpr size_t kEngineFlameFlamePtrOffset = 0x1228;

        constexpr size_t kEngineFlameFlameTextureOffset = 0x123C;

        constexpr size_t kEngineFlameControlVtableOffset = 0x18;

        constexpr size_t kEngineFlameSubmitVtableOffset = 0x20;

        constexpr size_t kCraftHandleLoOffset = 0x15C;

        constexpr size_t kCraftHandleHiOffset = 0x160;

        constexpr int kEngineFlameColorDefault = 0;

        constexpr int kEngineFlameColorBlue = 1;

        constexpr int kEngineFlameColorRed = 2;

        constexpr int kEngineFlameColorGreen = 3;

        // Faction-only colors. EXU's public per-team color ABI intentionally
        // remains the stock 0..3 range above; these values are selected only by
        // the local ODF-faction fallback when JetFlames is enabled.
        constexpr int kEngineFlameColorOrange = 4;

        constexpr int kEngineFlameColorBlackDog = 5;

        constexpr size_t kGameObjectClassOdfNameOffset = 0x30;

        static bool g_LoggedExuEngineFlameBridge = false;

        static bool g_LoggedExuEngineFlameBridgeMissing = false;

        alignas(16) static unsigned char g_EngineFlamePrimaryRed[kEngineFlameObjectSize] = {};

        alignas(16) static unsigned char g_EngineFlamePrimaryBlue[kEngineFlameObjectSize] = {};

        alignas(16) static unsigned char g_EngineFlamePrimaryGreen[kEngineFlameObjectSize] = {};

        alignas(16) static unsigned char g_EngineFlamePrimaryOrange[kEngineFlameObjectSize] = {};

        alignas(16) static unsigned char g_EngineFlamePrimaryBlackDog[kEngineFlameObjectSize] = {};

        alignas(16) static unsigned char g_EngineFlameSecondaryRed[kEngineFlameObjectSize] = {};

        alignas(16) static unsigned char g_EngineFlameSecondaryBlue[kEngineFlameObjectSize] = {};

        alignas(16) static unsigned char g_EngineFlameSecondaryGreen[kEngineFlameObjectSize] = {};

        alignas(16) static unsigned char g_EngineFlameSecondaryOrange[kEngineFlameObjectSize] = {};

        alignas(16) static unsigned char g_EngineFlameSecondaryBlackDog[kEngineFlameObjectSize] = {};

        static bool g_JetFlamesEnabled = kJetFlamesEnabledDefault;

        static void* GetEngineFlamePrimary()
        {
            return g_EngineFlamePrimaryManager;
        }

        static void* GetEngineFlameSecondary()
        {
            return g_EngineFlameSecondaryManager;
        }


        static void LogEngineFlameTargetFailure(const wchar_t* name)
        {
            if (!name || !name[0])
                return;

            if (!g_LoggedEngineFlameTargetFailure)
            {
                Log(L"[FLAME] Failed to resolve Steam runtime target: %ls\n", name);
                g_LoggedEngineFlameTargetFailure = true;
            }
        }

        void ResolveEngineFlameRuntimeTargets()
        {
            if (g_BzrFn_EngineFlameAddFlame &&
                g_BzrFn_EngineFlameResolveTexture &&
                g_BzrFn_GetTeamNum)
            {
                return;
            }

            // Signatures, anchors and known-good constants for these three
            // live in the "resolves" array of scripts/patches.json. Each
            // resolution logs its match count and whether the scanned address
            // agrees with the constant, so an ambiguous or drifted signature
            // shows up in the log before it shows up as a missing effect.
            if (!g_BzrFn_EngineFlameAddFlame)
            {
                if (const uint32_t addFlame =
                        HookEngine::ResolveNamedAddress("EngineFlame::AddFlame"))
                {
                    g_BzrFn_EngineFlameAddFlame =
                        reinterpret_cast<FnEngineFlameAddFlame>(addFlame);
                }
                else
                {
                    LogEngineFlameTargetFailure(L"EngineFlame::AddFlame");
                }
            }

            if (!g_BzrFn_GetTeamNum)
            {
                if (const uint32_t getTeamNum =
                        HookEngine::ResolveNamedAddress("GetTeamNum"))
                {
                    g_BzrFn_GetTeamNum = reinterpret_cast<FnGetTeamNum>(getTeamNum);
                }
                else
                {
                    LogEngineFlameTargetFailure(L"GetTeamNum");
                }
            }

            if (!g_BzrFn_EngineFlameResolveTexture)
            {
                // One function in two roles: the engine flame texture lookup
                // and the HUD sprite lookup are the same code.
                if (const uint32_t resolveTexture =
                        HookEngine::ResolveNamedAddress("EngineFlame::ResolveTexture"))
                {
                    g_BzrFn_EngineFlameResolveTexture =
                        reinterpret_cast<FnEngineFlameResolveTexture>(resolveTexture);
                    g_BzrFn_HudSpriteLookup =
                        reinterpret_cast<FnHudSpriteLookup>(resolveTexture);
                }
                else
                {
                    LogEngineFlameTargetFailure(L"ResolveTexture");
                }
            }
        }

        static void ObserveEngineFlameManager(void* manager)
        {
            if (!manager)
                return;

            if (!g_EngineFlamePrimaryManager)
            {
                g_EngineFlamePrimaryManager = manager;
                Log(L"[FLAME] Observed primary engine flame manager=0x%p\n", manager);
                return;
            }

            if (manager != g_EngineFlamePrimaryManager && !g_EngineFlameSecondaryManager)
            {
                g_EngineFlameSecondaryManager = manager;
                Log(L"[FLAME] Observed secondary engine flame manager=0x%p\n", manager);
            }
        }

        static void EnsureEngineFlameVtableHooksInstalled(void* manager)
        {
            if (!g_IsSteamExe || g_EngineFlameVtableHooksInstalled || !manager)
                return;

            auto** vtable = *reinterpret_cast<void***>(manager);
            if (!vtable)
                return;

            const uintptr_t controlSlot =
                reinterpret_cast<uintptr_t>(vtable) + kEngineFlameControlVtableOffset;
            const uintptr_t submitSlot =
                reinterpret_cast<uintptr_t>(vtable) + kEngineFlameSubmitVtableOffset;
            const size_t controlIndex = kEngineFlameControlVtableOffset / sizeof(void*);
            const size_t submitIndex = kEngineFlameSubmitVtableOffset / sizeof(void*);

            // The originals come from the verified engine address table. When
            // either failed its guard, the hooks stay out: copying the vtable
            // slot instead would bind an unverified value, and once the DWORD
            // vtable patch has run that slot holds our own hook, which would
            // then call itself.
            if (!g_BzrFn_EngineFlameControl || !g_BzrFn_EngineFlameSubmit)
                return;

            using EngineFlameControlHookFn = void (__fastcall*)(void*, void*);
            using EngineFlameSubmitHookFn = void (__fastcall*)(void*, void*, void*);
            auto* controlHook =
                reinterpret_cast<void*>(static_cast<EngineFlameControlHookFn>(EngineFlameControlHook));
            auto* submitHook =
                reinterpret_cast<void*>(static_cast<EngineFlameSubmitHookFn>(EngineFlameSubmitHook));
            const bool controlPatched =
                (vtable[controlIndex] == controlHook) ||
                WritePointerValue(controlSlot, controlHook);
            const bool submitPatched =
                (vtable[submitIndex] == submitHook) ||
                WritePointerValue(submitSlot, submitHook);

            g_EngineFlameVtableHooksInstalled = controlPatched && submitPatched;
            if (g_EngineFlameVtableHooksInstalled && !g_LoggedEngineFlameVtableHook)
            {
                Log(L"[FLAME] Patched Steam engine flame vtable control=0x%08X submit=0x%08X\n",
                    static_cast<uint32_t>(controlSlot),
                    static_cast<uint32_t>(submitSlot));
                g_LoggedEngineFlameVtableHook = true;
            }
        }

        static uint32_t ResolveCraftHandle(void* craftPtr)
        {
            if (!craftPtr)
                return 0;

            auto* bytes = reinterpret_cast<uint8_t*>(craftPtr);
            const uint32_t low = *reinterpret_cast<uint32_t*>(bytes + kCraftHandleLoOffset);
            if (low == 0)
                return 0;

            const uint32_t high = *reinterpret_cast<uint32_t*>(bytes + kCraftHandleHiOffset);
            return ((high & 0x0FFFu) << 20) | (low & 0x000FFFFFu);
        }

        static void ResetEngineFlameQueue(void* manager)
        {
            if (!manager)
                return;

            auto* bytes = reinterpret_cast<uint8_t*>(manager);
            *reinterpret_cast<uintptr_t*>(bytes + kEngineFlameFlamePtrOffset) =
                reinterpret_cast<uintptr_t>(bytes + 0x28);
        }

        static void SetEngineFlameTexture(void* manager, int textureHandle)
        {
            if (!manager)
                return;

            auto* bytes = reinterpret_cast<uint8_t*>(manager);
            *reinterpret_cast<int*>(bytes + kEngineFlameFlameTextureOffset) = textureHandle;
        }

        static FnExuGetTeamEngineFlameColor ResolveExuTeamEngineFlameColor()
        {
            // Asked once per craft per frame (SelectEngineFlameManager). The
            // module set only changes at load time, so re-probe once a second
            // and answer from the cache in between (null means not loaded).
            static ULONGLONG s_nextProbeTick = 0;
            const ULONGLONG now = GetTickCount64();
            if (now < s_nextProbeTick)
                return g_ExuFn_GetTeamEngineFlameColor;
            s_nextProbeTick = now + 1000;
            HMODULE exuModule = GetModuleHandleA("exu.dll");
            if (!exuModule)
                exuModule = GetModuleHandleA("ExtraUtilities.dll");

            if (!exuModule)
            {
                g_ExuFn_GetTeamEngineFlameColor = nullptr;
                g_ExuTeamEngineFlameColorModule = nullptr;
                if (!g_LoggedExuEngineFlameBridgeMissing)
                {
                    Log(L"[FLAME] EXU module not loaded; team engine flame colors default to stock blue\n");
                    g_LoggedExuEngineFlameBridgeMissing = true;
                }
                return nullptr;
            }

            if (g_ExuFn_GetTeamEngineFlameColor && g_ExuTeamEngineFlameColorModule == exuModule)
                return g_ExuFn_GetTeamEngineFlameColor;

            auto* proc = reinterpret_cast<FnExuGetTeamEngineFlameColor>(
                GetProcAddress(exuModule, "EXU_GetTeamEngineFlameColor"));
            if (!proc)
            {
                g_ExuFn_GetTeamEngineFlameColor = nullptr;
                g_ExuTeamEngineFlameColorModule = nullptr;
                if (!g_LoggedExuEngineFlameBridgeMissing)
                {
                    Log(L"[FLAME] EXU_GetTeamEngineFlameColor export missing; team engine flame colors disabled\n");
                    g_LoggedExuEngineFlameBridgeMissing = true;
                }
                return nullptr;
            }

            g_ExuFn_GetTeamEngineFlameColor = proc;
            g_ExuTeamEngineFlameColorModule = exuModule;
            g_LoggedExuEngineFlameBridgeMissing = false;
            if (!g_LoggedExuEngineFlameBridge)
            {
                Log(L"[FLAME] Connected EXU engine flame color bridge from module=0x%p\n", exuModule);
                g_LoggedExuEngineFlameBridge = true;
            }
            return g_ExuFn_GetTeamEngineFlameColor;
        }

        static int ResolveTeamEngineFlameColor(int team)
        {
            if (team <= 0)
                return kEngineFlameColorDefault;

            auto* exuGetColor = ResolveExuTeamEngineFlameColor();
            if (!exuGetColor)
                return kEngineFlameColorDefault;

            int color = kEngineFlameColorDefault;
            __try
            {
                color = exuGetColor(team);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                g_ExuFn_GetTeamEngineFlameColor = nullptr;
                g_ExuTeamEngineFlameColorModule = nullptr;
                if (!g_LoggedExuEngineFlameBridgeMissing)
                {
                    Log(L"[FLAME] EXU engine flame color bridge call faulted; disabling cached bridge and falling back to stock blue\n");
                    g_LoggedExuEngineFlameBridgeMissing = true;
                }
                return kEngineFlameColorDefault;
            }
            if (color < kEngineFlameColorDefault || color > kEngineFlameColorGreen)
                return kEngineFlameColorDefault;
            return color;
        }

        static int ResolveEngineFlameTextureHandle(const char* const* candidates, size_t count, const wchar_t* colorName)
        {
            if (!g_BzrFn_EngineFlameResolveTexture || !candidates || count == 0)
                return 0;

            for (size_t i = 0; i < count; ++i)
            {
                const char* candidate = candidates[i];
                if (!candidate || !candidate[0])
                    continue;

                BzrString textureName = {};
                BzrStringInitEmpty(&textureName);
                BzrStringAssign(&textureName, candidate, std::strlen(candidate));
                const int textureHandle = g_BzrFn_EngineFlameResolveTexture(&textureName);
                BzrStringFree(&textureName);

                if (textureHandle != 0)
                {
                    Log(L"[FLAME] Resolved %ls engine flame texture '%hs' => 0x%08X\n",
                        colorName ? colorName : L"unknown",
                        candidate,
                        textureHandle);
                    return textureHandle;
                }
            }

            Log(L"[FLAME] Failed to resolve any %ls engine flame texture candidate\n",
                colorName ? colorName : L"unknown");
            return 0;
        }

        static void CloneEngineFlameManager(void* destination, const void* source, int textureHandle)
        {
            if (!destination || !source || textureHandle == 0)
                return;

            std::memcpy(destination, source, kEngineFlameObjectSize);
            ResetEngineFlameQueue(destination);
            SetEngineFlameTexture(destination, textureHandle);
        }

        static void EnsureEngineFlameVariantsInitialized()
        {
            if (g_EngineFlameVariantsInitialized)
                return;

            if (g_IsSteamExe)
                ResolveEngineFlameRuntimeTargets();

            if (!GetEngineFlamePrimary() || !GetEngineFlameSecondary() || !g_BzrFn_EngineFlameResolveTexture)
                return;

            if (g_EngineFlameVariantsInitAttempted)
                return;

            g_EngineFlameVariantsInitAttempted = true;

            // Blue is a real stock asset: bzone.zfs carries "exhaust_b",
            // WITHOUT the ".0" suffix that "exhaust_r.0" has. Blue used to be
            // aliased to "leave the stock manager alone", which is why NSDF
            // craft kept the orange stock flame instead of a faction colour.
            static const char* const kBlueTextureCandidates[] =
            {
                "exhaust_b.0",
                "exhaust_b",
                "bflame.0",
                "bflame",
            };
            static const char* const kRedTextureCandidates[] =
            {
                "exhaust_r.0",
                "exhaust_r",
                "rflame.0",
                "rflame",
            };
            static const char* const kGreenTextureCandidates[] =
            {
                "exhaust_g.0",
                "exhaust_g",
                "gflame.0",
                "gflame",
            };
            // Campaign Reimagined supplies two palette-separated variants:
            // burnt orange keeps CCA distinct from Black Dog's blood red. The
            // generic aliases remain as fallbacks for compatible add-ons.
            static const char* const kOrangeTextureCandidates[] =
            {
                "cr_exhaust_cca.0",
                "cr_exhaust_cca",
                "exhaust_o.0",
                "exhaust_o",
                "oflame.0",
                "oflame",
            };
            static const char* const kBlackDogTextureCandidates[] =
            {
                "cr_exhaust_blackdog.0",
                "cr_exhaust_blackdog",
                "exhaust_bd.0",
                "exhaust_bd",
                "bdflame.0",
                "bdflame",
            };

            g_EngineFlamePrimaryBlueTexture =
                ResolveEngineFlameTextureHandle(kBlueTextureCandidates, _countof(kBlueTextureCandidates), L"blue");
            g_EngineFlamePrimaryRedTexture =
                ResolveEngineFlameTextureHandle(kRedTextureCandidates, _countof(kRedTextureCandidates), L"red");
            g_EngineFlamePrimaryGreenTexture =
                ResolveEngineFlameTextureHandle(kGreenTextureCandidates, _countof(kGreenTextureCandidates), L"green");
            g_EngineFlamePrimaryOrangeTexture =
                ResolveEngineFlameTextureHandle(kOrangeTextureCandidates, _countof(kOrangeTextureCandidates), L"orange");
            g_EngineFlamePrimaryBlackDogTexture =
                ResolveEngineFlameTextureHandle(kBlackDogTextureCandidates, _countof(kBlackDogTextureCandidates), L"Black Dog blood-red");

            void* primary = GetEngineFlamePrimary();
            void* secondary = GetEngineFlameSecondary();
            if (g_EngineFlamePrimaryRedTexture != 0)
            {
                CloneEngineFlameManager(g_EngineFlamePrimaryRed, primary, g_EngineFlamePrimaryRedTexture);
                CloneEngineFlameManager(g_EngineFlameSecondaryRed, secondary, g_EngineFlamePrimaryRedTexture);
            }

            if (g_EngineFlamePrimaryBlueTexture != 0)
            {
                CloneEngineFlameManager(g_EngineFlamePrimaryBlue, primary, g_EngineFlamePrimaryBlueTexture);
                CloneEngineFlameManager(g_EngineFlameSecondaryBlue, secondary, g_EngineFlamePrimaryBlueTexture);
            }

            if (g_EngineFlamePrimaryGreenTexture != 0)
            {
                CloneEngineFlameManager(g_EngineFlamePrimaryGreen, primary, g_EngineFlamePrimaryGreenTexture);
                CloneEngineFlameManager(g_EngineFlameSecondaryGreen, secondary, g_EngineFlamePrimaryGreenTexture);
            }

            if (g_EngineFlamePrimaryOrangeTexture != 0)
            {
                CloneEngineFlameManager(g_EngineFlamePrimaryOrange, primary, g_EngineFlamePrimaryOrangeTexture);
                CloneEngineFlameManager(g_EngineFlameSecondaryOrange, secondary, g_EngineFlamePrimaryOrangeTexture);
            }

            if (g_EngineFlamePrimaryBlackDogTexture != 0)
            {
                CloneEngineFlameManager(g_EngineFlamePrimaryBlackDog, primary, g_EngineFlamePrimaryBlackDogTexture);
                CloneEngineFlameManager(g_EngineFlameSecondaryBlackDog, secondary, g_EngineFlamePrimaryBlackDogTexture);
            }

            g_EngineFlameVariantsInitialized = true;
            Log(L"[FLAME] Engine flame variants initialized blue=%hs red=%hs green=%hs orange=%hs blackdog=%hs\n",
                g_EngineFlamePrimaryBlueTexture != 0 ? "yes" : "no",
                g_EngineFlamePrimaryRedTexture != 0 ? "yes" : "no",
                g_EngineFlamePrimaryGreenTexture != 0 ? "yes" : "no",
                g_EngineFlamePrimaryOrangeTexture != 0 ? "yes" : "no",
                g_EngineFlamePrimaryBlackDogTexture != 0 ? "yes" : "no");
        }

        // Walks GameObject -> GameObjectClass -> ODF label and returns the
        // lowercased first character (the faction code). Mirrors the engine's own
        // GetClassLabel chain; SEH-guarded so a malformed object can never fault
        // the render path. Build-independent (no hardcoded addresses), so it also
        // works on the Steam executable.
        bool TryGetCraftOdfName(void* craftPtr, char* out, size_t outSize)
        {
            if (out && outSize)
                out[0] = '\0';
            if (!craftPtr || !out || outSize == 0)
                return false;

            __try
            {
                auto* obj = reinterpret_cast<uint8_t*>(craftPtr);
                void* classSub = obj + kGameObjectClassSubObjOffset;
                auto** vtbl = *reinterpret_cast<void***>(classSub);
                if (!vtbl)
                    return false;

                using ClassGetter = void*(__thiscall*)(void*);
                auto getClass = reinterpret_cast<ClassGetter>(vtbl[0]);
                void* klass = getClass(classSub);
                if (!klass)
                    return false;

                // The ODF name is an inline char[8] at class+0x30 (read by
                // address, matching GetOdf); may be exactly 8 chars (unterminated).
                const char* name = reinterpret_cast<const char*>(
                    reinterpret_cast<uint8_t*>(klass) + kGameObjectClassOdfNameOffset);
                const size_t maxCopy =
                    (outSize - 1 < kGameObjectClassOdfNameMax) ? (outSize - 1)
                                                              : kGameObjectClassOdfNameMax;
                size_t i = 0;
                for (; i < maxCopy && name[i]; ++i)
                    out[i] = name[i];
                out[i] = '\0';
                return out[0] != '\0';
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                if (out && outSize)
                    out[0] = '\0';
                return false;
            }
        }

        static bool TryGetCraftFactionChar(void* craftPtr, char& outFaction)
        {
            outFaction = 0;
            char odf[16] = {};
            if (!TryGetCraftOdfName(craftPtr, odf, sizeof(odf)))
                return false;
            outFaction = static_cast<char>(
                std::tolower(static_cast<unsigned char>(odf[0])));
            return outFaction != 0;
        }

        // Faction -> flame color fallback used when JetFlames is enabled and no
        // EXU per-team color applies. a=NSDF blue, s=CCA orange, c=CRA green,
        // b=Black Dog blood red; anything else keeps stock (default).
        static int ResolveFactionEngineFlameColor(void* craftPtr)
        {
            char faction = 0;
            if (!TryGetCraftFactionChar(craftPtr, faction))
                return kEngineFlameColorDefault;

            switch (faction)
            {
            case 'a': return kEngineFlameColorBlue;
            case 's': return kEngineFlameColorOrange;
            case 'c': return kEngineFlameColorGreen;
            case 'b': return kEngineFlameColorBlackDog;
            default:  return kEngineFlameColorDefault;
            }
        }

        void InitializeJetFlamesConfig()
        {
            if (g_JetFlamesConfigInitialized)
                return;
            g_JetFlamesConfigInitialized = true;

            bool enabled = kJetFlamesEnabledDefault;
            bool cfg = false;
            if (TryGetUserConfigBool(kUserConfigDisplaySection, "JetFlames", cfg))
                enabled = cfg;

            if (EnvFlagEnabled("OPENSHIM_FACTION_JET_FLAMES") ||
                EnvFlagEnabled("BZR_FACTION_JET_FLAMES"))
                enabled = true;
            else if (EnvFlagEnabled("OPENSHIM_DISABLE_FACTION_JET_FLAMES") ||
                     EnvFlagEnabled("BZR_DISABLE_FACTION_JET_FLAMES"))
                enabled = false;

            g_JetFlamesEnabled = enabled;
            Log(L"[FLAME] Faction jet flames %hs (a=blue s=orange c=green b=blood-red; EXU per-team colors win)\n",
                enabled ? "enabled" : "disabled");
        }

        static bool ShouldTraceJetFlames()
        {
            static int s_cached = -1;
            if (s_cached < 0)
            {
                s_cached =
                    (EnvFlagEnabled("OPENSHIM_TRACE_JET_FLAMES") ||
                     EnvFlagEnabled("BZR_TRACE_JET_FLAMES")) ? 1 : 0;
            }
            return s_cached != 0;
        }

        // Every early return below leaves the craft on the stock manager, which
        // is indistinguishable from a working feature that picked the default
        // color. Name the reason so a "still blue" report costs one log line
        // instead of a round of guessing.
        static void TraceJetFlameBail(const wchar_t* reason, void* craftPtr)
        {
            if (!ShouldTraceJetFlames())
                return;
            static int s_bailBudget = 12;
            if (s_bailBudget <= 0)
                return;
            --s_bailBudget;
            char odf[16] = {};
            TryGetCraftOdfName(craftPtr, odf, sizeof(odf));
            Log(L"[FLAME] route bail reason=%ls craft=0x%p odf='%hs' getTeamNumFn=0x%p\n",
                reason, craftPtr, odf[0] ? odf : "<none>",
                reinterpret_cast<void*>(g_BzrFn_GetTeamNum));
        }

        static void* SelectEngineFlameManager(void* originalManager, void* craftPtr)
        {
            if (!originalManager || !craftPtr)
            {
                TraceJetFlameBail(L"null-manager-or-craft", craftPtr);
                return originalManager;
            }

            if (originalManager != GetEngineFlamePrimary() && originalManager != GetEngineFlameSecondary())
            {
                TraceJetFlameBail(L"manager-not-primary-or-secondary", craftPtr);
                return originalManager;
            }

            if (g_IsSteamExe)
                ResolveEngineFlameRuntimeTargets();

            if (!g_BzrFn_GetTeamNum)
            {
                TraceJetFlameBail(L"getteamnum-unresolved", craftPtr);
                return originalManager;
            }

            const uint32_t handle = ResolveCraftHandle(craftPtr);
            if (handle == 0)
            {
                TraceJetFlameBail(L"craft-handle-zero", craftPtr);
                return originalManager;
            }

            const int team = g_BzrFn_GetTeamNum(static_cast<int>(handle));
            // EXU per-team color wins; when it has no opinion (default) and the
            // faction jet flames preference is on, tint by the unit's faction.
            const int exuColor = ResolveTeamEngineFlameColor(team);
            int color = exuColor;
            char faction = 0;
            const bool haveFaction = TryGetCraftFactionChar(craftPtr, faction);
            if (color == kEngineFlameColorDefault && g_JetFlamesEnabled && haveFaction)
                color = ResolveFactionEngineFlameColor(craftPtr);

            // Diagnostics (opt-in via OPENSHIM_TRACE_JET_FLAMES): log the first
            // several routing decisions so a stock mission shows how the unit's
            // ODF name -> faction -> color -> texture resolved.
            if (ShouldTraceJetFlames())
            {
                // Diagnostics only, so none of this runs in normal play. Pull
                // the variants up first: the texture handles are the whole
                // point of the line below, and reading them before they are
                // initialised printed five zeroes that read as a texture bug.
                EnsureEngineFlameVariantsInitialized();

                char odf[16] = {};
                TryGetCraftOdfName(craftPtr, odf, sizeof(odf));

                // One line per distinct craft type. Budgeting by call count
                // instead spent all 24 entries on a single craft inside one
                // frame, and said nothing about the units under test.
                static char s_seenOdf[24][16] = {};
                static int s_seenCount = 0;
                bool alreadySeen = false;
                for (int i = 0; i < s_seenCount; ++i)
                {
                    if (strcmp(s_seenOdf[i], odf) == 0)
                    {
                        alreadySeen = true;
                        break;
                    }
                }

                if (!alreadySeen && s_seenCount < 24)
                {
                    strncpy_s(s_seenOdf[s_seenCount], odf, _TRUNCATE);
                    ++s_seenCount;
                    Log(L"[FLAME] route craft=0x%p handle=0x%08X team=%d odf='%hs' faction='%c' exuColor=%d final=%d tex(b=0x%08X r=0x%08X g=0x%08X o=0x%08X bd=0x%08X)\n",
                        craftPtr, handle, team,
                        odf[0] ? odf : "<none>",
                        haveFaction && faction ? faction : '?',
                        exuColor, color,
                        static_cast<uint32_t>(g_EngineFlamePrimaryBlueTexture),
                        static_cast<uint32_t>(g_EngineFlamePrimaryRedTexture),
                        static_cast<uint32_t>(g_EngineFlamePrimaryGreenTexture),
                        static_cast<uint32_t>(g_EngineFlamePrimaryOrangeTexture),
                        static_cast<uint32_t>(g_EngineFlamePrimaryBlackDogTexture));
                }
            }

            if (color == kEngineFlameColorDefault)
                return originalManager;

            EnsureEngineFlameVariantsInitialized();

            if (color == kEngineFlameColorBlue && g_EngineFlamePrimaryBlueTexture != 0)
            {
                return (originalManager == GetEngineFlamePrimary())
                    ? static_cast<void*>(g_EngineFlamePrimaryBlue)
                    : static_cast<void*>(g_EngineFlameSecondaryBlue);
            }

            if (color == kEngineFlameColorRed && g_EngineFlamePrimaryRedTexture != 0)
            {
                return (originalManager == GetEngineFlamePrimary())
                    ? static_cast<void*>(g_EngineFlamePrimaryRed)
                    : static_cast<void*>(g_EngineFlameSecondaryRed);
            }

            if (color == kEngineFlameColorGreen && g_EngineFlamePrimaryGreenTexture != 0)
            {
                return (originalManager == GetEngineFlamePrimary())
                    ? static_cast<void*>(g_EngineFlamePrimaryGreen)
                    : static_cast<void*>(g_EngineFlameSecondaryGreen);
            }

            if (color == kEngineFlameColorOrange && g_EngineFlamePrimaryOrangeTexture != 0)
            {
                return (originalManager == GetEngineFlamePrimary())
                    ? static_cast<void*>(g_EngineFlamePrimaryOrange)
                    : static_cast<void*>(g_EngineFlameSecondaryOrange);
            }

            if (color == kEngineFlameColorBlackDog && g_EngineFlamePrimaryBlackDogTexture != 0)
            {
                return (originalManager == GetEngineFlamePrimary())
                    ? static_cast<void*>(g_EngineFlamePrimaryBlackDog)
                    : static_cast<void*>(g_EngineFlameSecondaryBlackDog);
            }

            return originalManager;
        }
    }

    using namespace Hooks;

    void __cdecl EngineFlameHoverCraftEmitHook(
        void* managerPtr,
        const void* transform,
        uint32_t scaleBits,
        void* craftPtr)
    {
        if (ShouldTraceJetFlames())
        {
            static bool s_loggedEmit = false;
            if (!s_loggedEmit)
            {
                s_loggedEmit = true;
                Log(L"[FLAME] Emit hook invoked manager=0x%p transform=0x%p craft=0x%p addFlameFn=0x%p\n",
                    managerPtr, transform, craftPtr,
                    reinterpret_cast<void*>(g_BzrFn_EngineFlameAddFlame));
            }
        }

        if (g_IsSteamExe)
            ResolveEngineFlameRuntimeTargets();

        if (!g_BzrFn_EngineFlameAddFlame || !managerPtr || !transform)
            return;

        ApplyWeaponMaskCarrierBiasForCraft(craftPtr);

        // Interactive fog wakes: a hovercraft under power is exactly the emitter
        // that should carve ground fog. This only records a position -- the
        // simulation is advanced on its own cadence -- so it is safe here even
        // though this hook can run more than once per simulation step.
        if (craftPtr && FogWakeFeatureEnabled())
        {
            float craftPosition[3] = { 0.0f, 0.0f, 0.0f };
            if (TryGetGameObjectWorldPosition(craftPtr, craftPosition))
                FogWakeObserveEmitter(craftPtr, craftPosition[0], craftPosition[2]);
        }

        ObserveEngineFlameManager(managerPtr);
        EnsureEngineFlameVtableHooksInstalled(managerPtr);

        const float scale = *reinterpret_cast<const float*>(&scaleBits);
        void* selectedManager = SelectEngineFlameManager(managerPtr, craftPtr);
        g_BzrFn_EngineFlameAddFlame(selectedManager, transform, scale);
    }

    void __fastcall EngineFlameControlHook(void* thisPtr, void* /*edx*/)
    {
        if (!g_BzrFn_EngineFlameControl || !thisPtr)
            return;

        EnsureEngineFlameVariantsInitialized();
        g_BzrFn_EngineFlameControl(thisPtr);

        if (thisPtr == GetEngineFlamePrimary())
        {
            if (g_EngineFlamePrimaryBlueTexture != 0)
                g_BzrFn_EngineFlameControl(g_EngineFlamePrimaryBlue);
            if (g_EngineFlamePrimaryRedTexture != 0)
                g_BzrFn_EngineFlameControl(g_EngineFlamePrimaryRed);
            if (g_EngineFlamePrimaryGreenTexture != 0)
                g_BzrFn_EngineFlameControl(g_EngineFlamePrimaryGreen);
            if (g_EngineFlamePrimaryOrangeTexture != 0)
                g_BzrFn_EngineFlameControl(g_EngineFlamePrimaryOrange);
            if (g_EngineFlamePrimaryBlackDogTexture != 0)
                g_BzrFn_EngineFlameControl(g_EngineFlamePrimaryBlackDog);
            return;
        }

        if (thisPtr == GetEngineFlameSecondary())
        {
            if (g_EngineFlamePrimaryBlueTexture != 0)
                g_BzrFn_EngineFlameControl(g_EngineFlameSecondaryBlue);
            if (g_EngineFlamePrimaryRedTexture != 0)
                g_BzrFn_EngineFlameControl(g_EngineFlameSecondaryRed);
            if (g_EngineFlamePrimaryGreenTexture != 0)
                g_BzrFn_EngineFlameControl(g_EngineFlameSecondaryGreen);
            if (g_EngineFlamePrimaryOrangeTexture != 0)
                g_BzrFn_EngineFlameControl(g_EngineFlameSecondaryOrange);
            if (g_EngineFlamePrimaryBlackDogTexture != 0)
                g_BzrFn_EngineFlameControl(g_EngineFlameSecondaryBlackDog);
        }
    }

    void __fastcall EngineFlameSubmitHook(void* thisPtr, void* /*edx*/, void* camera)
    {
        if (!g_BzrFn_EngineFlameSubmit || !thisPtr)
            return;

        EnsureEngineFlameVariantsInitialized();
        g_BzrFn_EngineFlameSubmit(thisPtr, camera);
        TickChunkProxyDebug(camera, true);

        if (thisPtr == GetEngineFlamePrimary())
        {
            if (g_EngineFlamePrimaryBlueTexture != 0)
                g_BzrFn_EngineFlameSubmit(g_EngineFlamePrimaryBlue, camera);
            if (g_EngineFlamePrimaryRedTexture != 0)
                g_BzrFn_EngineFlameSubmit(g_EngineFlamePrimaryRed, camera);
            if (g_EngineFlamePrimaryGreenTexture != 0)
                g_BzrFn_EngineFlameSubmit(g_EngineFlamePrimaryGreen, camera);
            if (g_EngineFlamePrimaryOrangeTexture != 0)
                g_BzrFn_EngineFlameSubmit(g_EngineFlamePrimaryOrange, camera);
            if (g_EngineFlamePrimaryBlackDogTexture != 0)
                g_BzrFn_EngineFlameSubmit(g_EngineFlamePrimaryBlackDog, camera);
            return;
        }

        if (thisPtr == GetEngineFlameSecondary())
        {
            if (g_EngineFlamePrimaryBlueTexture != 0)
                g_BzrFn_EngineFlameSubmit(g_EngineFlameSecondaryBlue, camera);
            if (g_EngineFlamePrimaryRedTexture != 0)
                g_BzrFn_EngineFlameSubmit(g_EngineFlameSecondaryRed, camera);
            if (g_EngineFlamePrimaryGreenTexture != 0)
                g_BzrFn_EngineFlameSubmit(g_EngineFlameSecondaryGreen, camera);
            if (g_EngineFlamePrimaryOrangeTexture != 0)
                g_BzrFn_EngineFlameSubmit(g_EngineFlameSecondaryOrange, camera);
            if (g_EngineFlamePrimaryBlackDogTexture != 0)
                g_BzrFn_EngineFlameSubmit(g_EngineFlameSecondaryBlackDog, camera);
        }
    }
}
