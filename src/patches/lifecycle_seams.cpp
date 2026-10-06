// lifecycle_seams.cpp
// BZR Open Shim - process and mission lifecycle seams: the Ogre scene
// teardown forget hooks, the SetRunning mission transition seam (with the
// EXU lifecycle notify) and the D3D11 module pin for shutdown ordering,
// split out of bzr_hooks.cpp.
#include "native_hud_runtime.h"
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
#include "weapon_presentation_hooks.h"
#include "geometry_contact_test.h"
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
#include "bzn_load_trace.h"
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
    namespace Hooks
    {
        // ---- Scene teardown observation --------------------------------
        // Loading a save (and any mission teardown) clears the Ogre scene,
        // destroying the chunk proxies' billboard set, scene nodes, and
        // entities while our slot table still points at them; the loading
        // screen renders a few frames in that window and the manual submit
        // path then touched freed entities (crash dump 35064). Hook both
        // teardown entry points -- clearScene calls destroyAllMovableObjects
        // internally, but each is also reachable on its own -- and forget all
        // chunk Ogre references before the objects die.
        using FnOgreSceneManagerVoidMethod = void(__thiscall*)(void*);

        static InlineDetour32 g_SceneClearSceneDetour = {};
        static InlineDetour32 g_SceneDestroyAllMovablesDetour = {};
        static FnOgreSceneManagerVoidMethod g_OgreFn_ClearSceneOriginal = nullptr;
        static FnOgreSceneManagerVoidMethod g_OgreFn_DestroyAllMovablesOriginal = nullptr;
        static bool g_SceneTeardownHooksInstalled = false;
        static bool g_SceneTeardownHookFailureLogged = false;

        static void __fastcall SceneManagerClearSceneHook(void* sceneManager, void* /*unusedEdx*/)
        {
            GeometryContactTest::Clear();
            if (g_OgreFn_ClearSceneOriginal)
                WeaponPresentationSceneTeardownBegin();
            TerrainProxySceneTeardownBegin(sceneManager, true);
            ForgetAllChunkProxySceneResources(L"clearScene");
            ForgetSkinnedGibSceneResources(L"clearScene");
            ForgetShellCasingSceneResources(L"clearScene");
            ForgetPilotFlashlight(L"clearScene");
            ForgetMultiplayerFlagSceneResources(L"clearScene");
            if (g_OgreFn_ClearSceneOriginal)
                g_OgreFn_ClearSceneOriginal(sceneManager);
            TerrainProxySceneTeardownComplete(sceneManager, true);
            if (g_OgreFn_ClearSceneOriginal)
                WeaponPresentationSceneTeardownComplete();
        }

        static void __fastcall SceneManagerDestroyAllMovablesHook(void* sceneManager, void* /*unusedEdx*/)
        {
            GeometryContactTest::Clear();
            if (g_OgreFn_DestroyAllMovablesOriginal)
                WeaponPresentationSceneTeardownBegin();
            TerrainProxySceneTeardownBegin(sceneManager, false);
            ForgetAllChunkProxySceneResources(L"destroyAllMovableObjects");
            ForgetSkinnedGibSceneResources(L"destroyAllMovableObjects");
            ForgetShellCasingSceneResources(L"destroyAllMovableObjects");
            ForgetPilotFlashlight(L"destroyAllMovableObjects");
            ForgetMultiplayerFlagSceneResources(L"destroyAllMovableObjects");
            if (g_OgreFn_DestroyAllMovablesOriginal)
                g_OgreFn_DestroyAllMovablesOriginal(sceneManager);
            TerrainProxySceneTeardownComplete(sceneManager, false);
            if (g_OgreFn_DestroyAllMovablesOriginal)
                WeaponPresentationSceneTeardownComplete();
        }

        void InstallSceneTeardownForgetHooksIfPossible()
        {
            if (g_SceneTeardownHooksInstalled)
                return;

            HMODULE ogreMain = GetModuleHandleA("OgreMain.dll");
            if (!ogreMain)
                return;

            const auto resolveExportBody = [ogreMain](const char* exportName) -> uint8_t*
            {
                auto* proc = reinterpret_cast<uint8_t*>(GetProcAddress(ogreMain, exportName));
                if (!proc)
                    return nullptr;

                // Incremental-link export thunks are `jmp rel32`; follow to
                // the body so internal callers hit the detour too.
                if (proc[0] == 0xE9)
                {
                    int32_t rel = 0;
                    memcpy(&rel, proc + 1, sizeof(rel));
                    proc = proc + 5 + rel;
                }
                return proc;
            };

            uint8_t* clearSceneBody =
                resolveExportBody("?clearScene@SceneManager@Ogre@@UAEXXZ");
            uint8_t* destroyAllMovablesBody =
                resolveExportBody("?destroyAllMovableObjects@SceneManager@Ogre@@UAEXXZ");
            if (!clearSceneBody || !destroyAllMovablesBody)
            {
                if (!g_SceneTeardownHookFailureLogged)
                {
                    Log(L"[CHUNKPROXY] scene teardown hooks: OgreMain exports unresolved\n");
                    g_SceneTeardownHookFailureLogged = true;
                }
                return;
            }

            // push ebp; mov ebp,esp; sub esp,8 -- 3 whole instructions, 6 bytes.
            static const uint8_t kExpectedClearSceneBytes[] =
            {
                0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x08
            };
            // push ebp; mov ebp,esp; push -1 (EH prologue start), 5 bytes.
            static const uint8_t kExpectedDestroyAllMovablesBytes[] =
            {
                0x55, 0x8B, 0xEC, 0x6A, 0xFF
            };

            bool anyFailed = false;
            if (!InstallInlineDetour32(g_SceneClearSceneDetour,
                                       reinterpret_cast<uintptr_t>(clearSceneBody),
                                       reinterpret_cast<void*>(SceneManagerClearSceneHook),
                                       sizeof(kExpectedClearSceneBytes),
                                       kExpectedClearSceneBytes,
                                       sizeof(kExpectedClearSceneBytes)))
            {
                anyFailed = true;
            }
            else
            {
                g_OgreFn_ClearSceneOriginal =
                    reinterpret_cast<FnOgreSceneManagerVoidMethod>(g_SceneClearSceneDetour.trampoline);
            }

            if (!InstallInlineDetour32(g_SceneDestroyAllMovablesDetour,
                                       reinterpret_cast<uintptr_t>(destroyAllMovablesBody),
                                       reinterpret_cast<void*>(SceneManagerDestroyAllMovablesHook),
                                       sizeof(kExpectedDestroyAllMovablesBytes),
                                       kExpectedDestroyAllMovablesBytes,
                                       sizeof(kExpectedDestroyAllMovablesBytes)))
            {
                anyFailed = true;
            }
            else
            {
                g_OgreFn_DestroyAllMovablesOriginal =
                    reinterpret_cast<FnOgreSceneManagerVoidMethod>(g_SceneDestroyAllMovablesDetour.trampoline);
            }

            if (anyFailed)
            {
                if (!g_SceneTeardownHookFailureLogged)
                {
                    Log(L"[CHUNKPROXY] scene teardown hook install failed clearScene=0x%08X destroyAllMovables=0x%08X (installed=%d/%d)\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(clearSceneBody)),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(destroyAllMovablesBody)),
                        g_OgreFn_ClearSceneOriginal ? 1 : 0,
                        g_OgreFn_DestroyAllMovablesOriginal ? 1 : 0);
                    g_SceneTeardownHookFailureLogged = true;
                }
                // Keep whatever half installed; retry cannot help once bytes
                // mismatch, so mark installed to avoid rescanning every call.
            }
            else
            {
                Log(L"[CHUNKPROXY] Installed scene teardown forget hooks clearScene=0x%08X destroyAllMovables=0x%08X\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(clearSceneBody)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(destroyAllMovablesBody)));
            }

            g_SceneTeardownHooksInstalled = true;
        }

        // --- mission lifetime seam -------------------------------------------
        //
        // The scene teardown hooks above never fire at a mission change. The
        // shipped executable contains no call to Ogre::SceneManager::clearScene
        // or destroyAllMovableObjects -- it creates one SceneManager and keeps
        // it for the life of the process, and a mission change is torn down by
        // the terrain zone destructor destroying only the objects it created.
        //
        // They DO fire at process exit, and they must stay. Redux shuts Ogre
        // down cleanly, and the SceneManager destructor calls clearScene, which
        // calls destroyAllMovableObjects: a GOG boot-and-exit on 2026-09-27
        // logged both hooks, twice each, on the main thread. That is where
        // they drop our chunk proxy, pilot light, flag and terrain proxy
        // references before Ogre frees those objects. Do not remove them as
        // dead code (the 2026-09-25 audit listed them as such; it was wrong).
        //
        // For mission changes, then, the forget paths that hang off those two
        // hooks never run, which is how chunk proxy
        // slots kept entities from a previous mission: on the next mission the
        // manual submit path called getSubEntity on freed memory, the
        // __try/__except swallowed the access violation, and the render loop
        // retried it every frame -- a 100% CPU freeze rather than a crash
        // (captured in C:\BZDumps\hang_7700.dmp).
        //
        // The one mission boundary Redux does cross in-process is
        // SetRunning (FUN_00434170) leaving RUN_STARTED. The scene is still
        // fully alive at that point, so it is a safe place to drop references.
        constexpr uintptr_t kBzrSetRunningAddr = 0x00434170;
        constexpr uintptr_t kBzrRunStateAddr = 0x008E706C;
        constexpr uintptr_t kBzrRunStateNameTableAddr = 0x00871690;
        constexpr int kBzrRunStateWasQuit = 2;

        using FnBzrSetRunning = void(__cdecl*)(int);
        static InlineDetour32 g_BzrSetRunningDetour = {};
        static FnBzrSetRunning g_BzrFn_SetRunningOriginal = nullptr;
        bool g_MissionSeamInstalled = false;
        static bool g_MissionSeamFailureLogged = false;
        static uint32_t g_MissionTransitionCount = 0;


        bool TryReadBzrRunState(int& value)
        {
            __try
            {
                value = *reinterpret_cast<const int*>(kBzrRunStateAddr);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static const char* BzrRunStateName(int state)
        {
            if (state < 0 || state >= 11)
                return "<out-of-range>";
            __try
            {
                const char* const* const table =
                    reinterpret_cast<const char* const*>(kBzrRunStateNameTableAddr);
                const char* const name = table[state];
                return name ? name : "<null>";
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return "<unreadable>";
            }
        }

        static bool BzrRunStateNameMatches(int state, const char* expected)
        {
            __try
            {
                const char* const* const table =
                    reinterpret_cast<const char* const*>(kBzrRunStateNameTableAddr);
                const char* const name = table[state];
                if (!name)
                    return false;
                for (size_t index = 0;; ++index)
                {
                    if (name[index] != expected[index])
                        return false;
                    if (expected[index] == '\0')
                        return true;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static void NotifyExuMissionSimulationState(bool active)
        {
            using FnNotifyMissionSimulationState = void(__cdecl*)(int);
            const HMODULE exu = GetModuleHandleW(L"exu.dll");
            if (!exu)
                return;

            const auto notify = reinterpret_cast<FnNotifyMissionSimulationState>(
                GetProcAddress(exu, "ExuNotifyMissionSimulationState"));
            if (!notify)
                return;

            __try
            {
                notify(active ? 1 : 0);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[MISSION] EXU overlay lifecycle notification faulted active=%d code=0x%08X\n",
                    active ? 1 : 0,
                    static_cast<uint32_t>(GetExceptionCode()));
            }
        }

        static void __cdecl BzrSetRunningHook(int state)
        {
            int previous = kBzrRunStateUnknown;
            const bool readPrevious = TryReadBzrRunState(previous);
            if (g_BzrFn_SetRunningOriginal)
                g_BzrFn_SetRunningOriginal(state);
            // The init-time pin runs ~5 s before Ogre loads its render system
            // plugins on GOG, and the deferred retry only recurs from Lua
            // bridges, so the guard used to never engage. Every SetRunning,
            // including RUN_WAS_EXITED ahead of Ogre's plugin unload, is
            // after plugin load. Latched per module: a no-op once pinned.
            PinDirect3DModulesForShutdown();
            // Re-read instead of trusting the argument: SetRunning refuses every
            // change once the state is RUN_WAS_EXITED.
            int current = kBzrRunStateUnknown;
            if (!readPrevious || !TryReadBzrRunState(current) || current == previous)
                return;

            if (previous == kBzrRunStateStarted && current != kBzrRunStateStarted)
            {
                ++g_MissionTransitionCount;
                Log(L"[MISSION] Mission left simulation: was %hs(%d) now %hs(%d) transitions=%u\n",
                    BzrRunStateName(previous), previous,
                    BzrRunStateName(current), current,
                    g_MissionTransitionCount);
                if (current == kBzrRunStateWasQuit)
                    BznLoadTraceOnMissionQuit();
                // clearScene / destroyAllMovableObjects never fire for this
                // in-process transition. Deactivate chunk proxies now, while
                // setVisible and node updates are still safe; otherwise Ogre's
                // own scene traversal can reach an attached proxy after Modable
                // unloads its SubMesh, before the manual-submit stale checks get
                // a chance to run. Do not apply the old pointer-forget path to
                // multiplayer flags here: that path previously recreated over
                // still-live Ogre objects and aborted in RenderMultiplayerFlags
                // (battlezone98redux.exe.35108.dmp).
                DeactivateAllChunkProxySceneResources(L"left simulation");
                DeactivateSkinnedGibs(L"left simulation");
                DeactivateShellCasings(L"left simulation");

                ResetPathBlockState(L"left simulation");
                HeadlightNotifyMissionRunStateChanged(false);
                WeaponPresentationMissionRunStateChanged(false);
                GeometryContactTest::Clear();
                PilotFlashlightNotifyMissionRunStateChanged(false);
                FogWakeNotifyMissionRunStateChanged(false);
                NotifyExuMissionSimulationState(false);
                NativeHud::Runtime::ResetMission();
            }
            else if (previous != kBzrRunStateStarted && current == kBzrRunStateStarted)
            {
                HeadlightNotifyMissionRunStateChanged(true);
                WeaponPresentationMissionRunStateChanged(true);
                FogWakeNotifyMissionRunStateChanged(true);
                PilotFlashlightNotifyMissionRunStateChanged(true);
                ApplyTerrainTileBlendForCurrentMission();
                NotifyExuMissionSimulationState(true);
            }
            TerrainProxyMissionRunStateChanged(previous, current);
        }

        void InstallMissionTransitionSeamIfPossible()
        {
            if (g_MissionSeamInstalled || g_MissionSeamFailureLogged)
                return;
            // GOG-only absolute addresses, and the stolen prologue carries an
            // absolute operand, so require the pinned image at its fixed base.
            if (g_IsSteamExe ||
                reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr)) != 0x00400000)
            {
                Log(L"[MISSION] Mission transition seam unavailable (%hs)\n",
                    g_IsSteamExe ? "Steam executable" : "executable relocated");
                g_MissionSeamFailureLogged = true;
                return;
            }

            // push ebp; mov ebp,esp; cmp dword ptr [runState],9
            static const uint8_t kExpectedSetRunningBytes[] =
            {
                0x55, 0x8B, 0xEC, 0x83, 0x3D, 0x6C, 0x70, 0x8E, 0x00, 0x09
            };
            if (!ExpectedBytesMatchAt(kBzrSetRunningAddr,
                                      kExpectedSetRunningBytes,
                                      sizeof(kExpectedSetRunningBytes)) ||
                !BzrRunStateNameMatches(kBzrRunStateStarted, "RUN_STARTED"))
            {
                Log(L"[MISSION] SetRunning signature mismatch at 0x%08X (index %d reads \"%hs\"); mission transition seam unavailable\n",
                    static_cast<uint32_t>(kBzrSetRunningAddr),
                    kBzrRunStateStarted,
                    BzrRunStateName(kBzrRunStateStarted));
                g_MissionSeamFailureLogged = true;
                return;
            }

            if (!InstallInlineDetour32(g_BzrSetRunningDetour,
                                       kBzrSetRunningAddr,
                                       reinterpret_cast<void*>(BzrSetRunningHook),
                                       sizeof(kExpectedSetRunningBytes),
                                       kExpectedSetRunningBytes,
                                       sizeof(kExpectedSetRunningBytes)))
            {
                Log(L"[MISSION] Mission transition seam install failed at 0x%08X\n",
                    static_cast<uint32_t>(kBzrSetRunningAddr));
                g_MissionSeamFailureLogged = true;
                return;
            }
            g_BzrFn_SetRunningOriginal =
                reinterpret_cast<FnBzrSetRunning>(g_BzrSetRunningDetour.trampoline);
            g_MissionSeamInstalled = true;
            int initial = kBzrRunStateUnknown;
            TryReadBzrRunState(initial);
            if (initial != kBzrRunStateUnknown)
                NotifyExuMissionSimulationState(initial == kBzrRunStateStarted);
            Log(L"[MISSION] Installed mission transition seam SetRunning=0x%08X initialState=%hs(%d)\n",
                static_cast<uint32_t>(kBzrSetRunningAddr),
                BzrRunStateName(initial), initial);
        }

        // --- D3D11 shutdown unload-order guard ---------------------------------
        //
        // The D3D11 render system is an Ogre plugin. When Root unloads plugins
        // at exit, FreeLibrary on RenderSystem_Direct3D11.dll drops its
        // reference to d3d11.dll, and if that was the last one the module
        // unmaps. A driver/worker thread whose callback is still pending then
        // jumps into unmapped memory. Crash dump
        // C:\BZDumps\battlezone98redux.exe.35596.dmp is exactly that:
        // <Unloaded_d3d11.dll>+0xa9f10 on thread 40, while the main thread was
        // still inside Ogre scene destruction.
        //
        // Ogre's teardown assumes the module outlives the render system but
        // does not enforce it. Take a process-lifetime reference on the D3D
        // modules and the plugin so their code stays mapped until the OS tears
        // the process down, which supplies the missing ordering guarantee.
        //
        // Note this extends module lifetime; it does not change when the device
        // is released. A late callback now runs real code instead of faulting
        // on unmapped memory, which is what the shutdown path already assumed.
        static bool g_D3D11ModulesPinned[3] = { false, false, false };

        void PinDirect3DModulesForShutdown()
        {
            static const wchar_t* const kModules[] =
            {
                L"d3d11.dll",
                L"dxgi.dll",
                L"RenderSystem_Direct3D11.dll"
            };
            static_assert(
                sizeof(kModules) / sizeof(kModules[0]) ==
                sizeof(g_D3D11ModulesPinned) / sizeof(g_D3D11ModulesPinned[0]),
                "pin bookkeeping must cover every module");

            for (size_t index = 0; index < sizeof(kModules) / sizeof(kModules[0]); ++index)
            {
                if (g_D3D11ModulesPinned[index])
                    continue;

                HMODULE module = nullptr;
                if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_PIN, kModules[index], &module) ||
                    module == nullptr)
                {
                    // Not loaded yet: the init-time call precedes Ogre's
                    // plugin load. BzrSetRunningHook retries on every run
                    // state change, which is what actually pins on GOG.
                    continue;
                }

                g_D3D11ModulesPinned[index] = true;
                Log(L"[D3D11] Pinned %ls at 0x%08X for process lifetime (shutdown unload-order guard)\n",
                    kModules[index],
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(module)));
            }
        }
    }

}
