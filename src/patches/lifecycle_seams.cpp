// lifecycle_seams.cpp
// BZR Open Shim - process and mission lifecycle seams: the Ogre scene
// teardown forget hooks, the SetRunning mission transition seam (with the
// EXU lifecycle notify) and the D3D11 module pin for shutdown ordering,
// split out of bzr_hooks.cpp.
#include "native_hud_runtime.h"
#include "hud_feedback.h"
#include "unit_damage.h"
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
#include "planet_environment.h"
#include "bzr_options_ui.h"
#include "remembered_mesh_bounds_table.h"
#include "patches.h"
#include "patcher.h"
#include "fog_wake_feature.h"
#include "gpu_instancing.h"
#include "gpu_skinning.h"
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
#include "mesh_impact.h"
#include "headlight_falloff.h"
#include "shadow_far_distance.h"
#include "sun_flash.h"
#include "chunk_batch_invalidation.h"
#include "ai_range_policy.h"
#include "lcbench_safety_policy.h"
#include "hook_engine.h"
#include "bool_token.h"
#include "iat_patch.h"
#include "ui_performance.h"
#include "openshim_events.h"
#include "player_kill_trace.h"
#include "bzn_load_trace.h"
#include "net_optimizer.h"
#include "pond_class_label.h"
#include "perf_telemetry.h"
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
            MeshImpact::Clear();
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
            MeshImpact::Clear();
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

        // ---- Mission-end entity teardown --------------------------------
        // Every mission end (and save load, and replay) runs stock
        // FUN_0067D0C0, which calls SceneManager::destroyAllEntities and then
        // destroyAllLights. That frees every Ogre Entity in the scene, mod
        // ones included, while leaving their owners' pointers set:
        //  - the sky dome / sky plane flags stay true, so the next frame's
        //    _queueSkiesForRendering walks freed entities (the Wine crash
        //    after a mission win, a save load or a replay; Windows got lucky);
        //  - the gib and shell casing pools keep their hidden entities for
        //    reuse in the next mission.
        // Ogre re-creates sky entities by name when the sky is re-enabled,
        // and a by-name destroy of a missing entity is a no-op, so clearing
        // the enabled flags is enough to make the next setSkyDome safe.
        static InlineDetour32 g_SceneDestroyAllEntitiesDetour = {};
        static FnOgreSceneManagerVoidMethod g_OgreFn_DestroyAllEntitiesOriginal = nullptr;
        // SceneManager offsets of mSkyDomeEnabled / mSkyPlaneEnabled, read
        // from the isSky*Enabled accessors; 0 = accessor not recognised.
        static uint32_t g_SkyDomeEnabledOffset = 0;
        static uint32_t g_SkyPlaneEnabledOffset = 0;

        static bool TryClearSceneFlagSeh(void* sceneManager, uint32_t offset)
        {
            __try
            {
                uint8_t* flag = static_cast<uint8_t*>(sceneManager) + offset;
                if (!*flag)
                    return false;
                *flag = 0;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static void __fastcall SceneManagerDestroyAllEntitiesHook(void* sceneManager, void* /*unusedEdx*/)
        {
            const bool domeCleared =
                g_SkyDomeEnabledOffset && TryClearSceneFlagSeh(sceneManager, g_SkyDomeEnabledOffset);
            const bool planeCleared =
                g_SkyPlaneEnabledOffset && TryClearSceneFlagSeh(sceneManager, g_SkyPlaneEnabledOffset);
            // Once per mission end, so a quiet teardown still shows it ran.
            Log(L"[SCENE] destroyAllEntities sm=0x%08X: disabled sky dome=%d plane=%d before its entities are freed\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sceneManager)),
                domeCleared ? 1 : 0,
                planeCleared ? 1 : 0);
            DestroySkinnedGibSceneObjects(sceneManager, L"destroyAllEntities");
            DestroyShellCasingSceneObjects(sceneManager, L"destroyAllEntities");
            if (g_OgreFn_DestroyAllEntitiesOriginal)
                g_OgreFn_DestroyAllEntitiesOriginal(sceneManager);
        }

        // `mov al, byte [ecx+disp32]; ret` -- the whole accessor.
        static uint32_t ReadBoolAccessorOffset(const uint8_t* body)
        {
            if (!body || body[0] != 0x8A || body[1] != 0x81 || body[6] != 0xC3)
                return 0;
            uint32_t offset = 0;
            memcpy(&offset, body + 2, sizeof(offset));
            return offset < 0x1000 ? offset : 0;
        }

        static void InstallDestroyAllEntitiesHook(HMODULE ogreMain, uint8_t* body, uint8_t* domeAccessor, uint8_t* planeAccessor)
        {
            static bool attempted = false;
            if (attempted)
                return;
            attempted = true;

            g_SkyDomeEnabledOffset = ReadBoolAccessorOffset(domeAccessor);
            g_SkyPlaneEnabledOffset = ReadBoolAccessorOffset(planeAccessor);

            // mov eax,[ecx]; push <static type-name String>; call [eax+0x494]
            // (destroyAllMovableObjectsByType). The push operand is an
            // absolute address that moves with OgreMain's load base, so the
            // first 7 bytes are checked by shape and the operand must point
            // inside OgreMain.
            static const uint8_t kCallByType[] = {0xFF, 0x90, 0x94, 0x04, 0x00, 0x00};
            bool shapeOk = body && body[0] == 0x8B && body[1] == 0x01 && body[2] == 0x68 &&
                           memcmp(body + 7, kCallByType, sizeof(kCallByType)) == 0;
            if (shapeOk)
            {
                const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(ogreMain);
                const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS32*>(
                    reinterpret_cast<const uint8_t*>(ogreMain) + dos->e_lfanew);
                const uintptr_t base = reinterpret_cast<uintptr_t>(ogreMain);
                uint32_t operand = 0;
                memcpy(&operand, body + 3, sizeof(operand));
                shapeOk = operand >= base && operand < base + nt->OptionalHeader.SizeOfImage;
            }

            uint8_t expected[7] = {};
            if (shapeOk)
                memcpy(expected, body, sizeof(expected));
            if (!shapeOk ||
                !InstallInlineDetour32(g_SceneDestroyAllEntitiesDetour,
                                       reinterpret_cast<uintptr_t>(body),
                                       reinterpret_cast<void*>(SceneManagerDestroyAllEntitiesHook),
                                       sizeof(expected),
                                       expected,
                                       sizeof(expected),
                                       reinterpret_cast<void* volatile*>(&g_OgreFn_DestroyAllEntitiesOriginal)))
            {
                Log(L"[SCENE] destroyAllEntities hook not installed body=0x%08X shape=%d\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(body)),
                    shapeOk ? 1 : 0);
                return;
            }

            // The trampoline was published before the jump went live.
            Log(L"[SCENE] Installed destroyAllEntities hook body=0x%08X skyDomeFlag=+0x%X skyPlaneFlag=+0x%X\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(body)),
                g_SkyDomeEnabledOffset,
                g_SkyPlaneEnabledOffset);
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

            // Independent of the two forget hooks below: it has its own log
            // line and fails closed on its own.
            InstallDestroyAllEntitiesHook(
                ogreMain,
                resolveExportBody("?destroyAllEntities@SceneManager@Ogre@@UAEXXZ"),
                resolveExportBody("?isSkyDomeEnabled@SceneManager@Ogre@@UBE_NXZ"),
                resolveExportBody("?isSkyPlaneEnabled@SceneManager@Ogre@@UBE_NXZ"));

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
        // The clearScene / destroyAllMovableObjects hooks above never fire at
        // a mission change. The shipped executable contains no call to either
        // -- it creates one SceneManager and keeps it for the life of the
        // process. A mission change is torn down by the terrain zone
        // destructor destroying its own objects and, last, by FUN_0067D0C0
        // calling destroyAllEntities and destroyAllLights, which free every
        // Entity and Light in the scene, ours included (caught with cdb on
        // 2026-10-28). The destroyAllEntities hook above covers the entities.
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
        //
        // SetRunning is the SetShellState row and opens with
        // `cmp dword [runState],9`, so the run state global is read from that
        // operand; the name table is a row checked by name before use.
        static uintptr_t g_BzrSetRunningAddr = 0;
        static uintptr_t g_BzrRunStateAddr = 0;
        static uintptr_t g_BzrRunStateNameTableAddr = 0;

        static bool BzrRunStateAddressesBound()
        {
            static const bool bound = [] {
                const HookEngine::EngineRow rows[] = {
                    { "SetShellState", &g_BzrSetRunningAddr },
                    { "RunStateNameTable", &g_BzrRunStateNameTableAddr },
                };
                if (!HookEngine::BindEngineRows("Lifecycle seams", rows))
                    return false;
                const auto* code = reinterpret_cast<const uint8_t*>(g_BzrSetRunningAddr);
                if (code[3] != 0x83 || code[4] != 0x3D)
                {
                    Log(L"[MISSION] SetRunning at 0x%08X does not open with cmp [runState]; lifecycle seams stand down\n",
                        static_cast<uint32_t>(g_BzrSetRunningAddr));
                    return false;
                }
                g_BzrRunStateAddr = *reinterpret_cast<const uint32_t*>(code + 5);
                return true;
            }();
            return bound;
        }

        // Shared with the terrain proxy. The mission seam detours SetRunning
        // once this has bound, so later readers must take these values rather
        // than bind the SetShellState row again (its guard no longer matches).
        bool GetBzrRunStateAddresses(uintptr_t& setRunning, uintptr_t& runState, uintptr_t& nameTable)
        {
            if (!BzrRunStateAddressesBound())
                return false;
            setRunning = g_BzrSetRunningAddr;
            runState = g_BzrRunStateAddr;
            nameTable = g_BzrRunStateNameTableAddr;
            return true;
        }
        constexpr int kBzrRunStateWasQuit = 2;

        using FnBzrSetRunning = void(__cdecl*)(int);
        static InlineDetour32 g_BzrSetRunningDetour = {};
        static FnBzrSetRunning g_BzrFn_SetRunningOriginal = nullptr;
        bool g_MissionSeamInstalled = false;
        static bool g_MissionSeamFailureLogged = false;
        static uint32_t g_MissionTransitionCount = 0;


        bool TryReadBzrRunState(int& value)
        {
            if (!BzrRunStateAddressesBound())
                return false;
            __try
            {
                value = *reinterpret_cast<const int*>(g_BzrRunStateAddr);
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
                    reinterpret_cast<const char* const*>(g_BzrRunStateNameTableAddr);
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
                    reinterpret_cast<const char* const*>(g_BzrRunStateNameTableAddr);
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
                ResetEngineFlameOdfColors();
                WeaponPresentationMissionRunStateChanged(false);
                GeometryContactTest::Clear();
                MeshImpact::Clear();
                PilotFlashlightNotifyMissionRunStateChanged(false);
                FogWakeNotifyMissionRunStateChanged(false);
                GpuInstancingNotifyMissionRunStateChanged(false);
                GpuSkinningNotifyMissionRunStateChanged(false);
                NotifyExuMissionSimulationState(false);
                NativeHud::Runtime::ResetMission();
                HudFeedback::ResetMission();
                UnitDamage::ResetMissionState();
                ResetUnderAttackAlertCooldown();
                ResetHopOutAttackAlertTracking();
            }
            else if (previous != kBzrRunStateStarted && current == kBzrRunStateStarted)
            {
                HeadlightNotifyMissionRunStateChanged(true);
                WeaponPresentationMissionRunStateChanged(true);
                FogWakeNotifyMissionRunStateChanged(true);
                GpuSkinningNotifyMissionRunStateChanged(true);
                PilotFlashlightNotifyMissionRunStateChanged(true);
                ApplyTerrainTileBlendForCurrentMission();
                ApplyPlanetEnvironmentForCurrentMission();
                NotifyExuMissionSimulationState(true);
            }
            TerrainProxyMissionRunStateChanged(previous, current);
            PerfTelemetryMissionRunStateChanged(previous, current);
        }

        void InstallMissionTransitionSeamIfPossible()
        {
            if (g_MissionSeamInstalled || g_MissionSeamFailureLogged)
                return;
            if (!BzrRunStateAddressesBound())
            {
                g_MissionSeamFailureLogged = true;
                return;
            }
            // The stolen prologue carries an absolute operand, so require the
            // image at its fixed base (Steam and GOG both load there).
            if (reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr)) != 0x00400000)
            {
                Log(L"[MISSION] Mission transition seam unavailable (executable relocated)\n");
                g_MissionSeamFailureLogged = true;
                return;
            }

            // push ebp; mov ebp,esp; cmp dword ptr [runState],9 -- read live
            // after the row's guard, since the operand is absolute.
            uint8_t kExpectedSetRunningBytes[10] = {};
            memcpy(kExpectedSetRunningBytes, reinterpret_cast<const void*>(g_BzrSetRunningAddr),
                   sizeof(kExpectedSetRunningBytes));
            if (!ExpectedBytesMatchAt(g_BzrSetRunningAddr,
                                      kExpectedSetRunningBytes,
                                      sizeof(kExpectedSetRunningBytes)) ||
                !BzrRunStateNameMatches(kBzrRunStateStarted, "RUN_STARTED"))
            {
                Log(L"[MISSION] SetRunning signature mismatch at 0x%08X (index %d reads \"%hs\"); mission transition seam unavailable\n",
                    static_cast<uint32_t>(g_BzrSetRunningAddr),
                    kBzrRunStateStarted,
                    BzrRunStateName(kBzrRunStateStarted));
                g_MissionSeamFailureLogged = true;
                return;
            }

            if (!InstallInlineDetour32(g_BzrSetRunningDetour,
                                       g_BzrSetRunningAddr,
                                       reinterpret_cast<void*>(BzrSetRunningHook),
                                       sizeof(kExpectedSetRunningBytes),
                                       kExpectedSetRunningBytes,
                                       sizeof(kExpectedSetRunningBytes)))
            {
                Log(L"[MISSION] Mission transition seam install failed at 0x%08X\n",
                    static_cast<uint32_t>(g_BzrSetRunningAddr));
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
                static_cast<uint32_t>(g_BzrSetRunningAddr),
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

        static void InstallRootDestructorExitSeam();

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
            InstallRootDestructorExitSeam();
        }

        // --- D3D11 exit teardown skip ------------------------------------------
        //
        // At exit Root::unloadPlugins -> dllStopPlugin -> Root::uninstallPlugin
        // -> D3D11Plugin::uninstall deletes the render system, whose shutdown
        // releases the device and context. The NVIDIA driver's own worker
        // thread can still be using a released object then: it faults at
        // nvwgf2um!NVAPI_Thunk+0x1a0cea (lock xadd on freed memory) while the
        // main thread waits in ID3D11DeviceContext::Flush inside
        // D3D11Device::ReleaseAll. The crash hit 6 of 8 exits in one batch and
        // 2 of 8 in another, with or without FXAA and the buffer mirrors.
        //
        // The same race can instead deadlock the main thread in that Flush.
        //
        // When the game calls Ogre::Root::~Root (its only Root, destroyed once
        // at exit; the run state is not a usable signal because quitting from a
        // finished mission never reaches RUN_WAS_EXITED), point the plugin's
        // uninstall vtable slot at a no-op, so the render system is leaked to
        // the OS instead of being torn down under the driver. The modules are
        // pinned above, and ExitProcess ends the driver's threads before any
        // DLL detach. The rest of ~Root and the game's exit tail still run.
        // OPENSHIM_KEEP_D3D11_EXIT_TEARDOWN=1 leaves the stock teardown.
        static bool g_D3D11ExitTeardownSkipDone = false;

        static void __fastcall SkipD3D11PluginUninstall(void* /*plugin*/, void* /*edx*/)
        {
            Log(L"[D3D11] Skipped render system teardown at exit (driver worker race guard)\n");
        }

        static void ArmD3D11ExitTeardownSkip()
        {
            if (g_D3D11ExitTeardownSkipDone)
                return;
            g_D3D11ExitTeardownSkipDone = true;

            char value[16] = {};
            const DWORD n = GetEnvironmentVariableA("OPENSHIM_KEEP_D3D11_EXIT_TEARDOWN", value,
                                                    static_cast<DWORD>(sizeof(value)));
            if (n > 0 && n < sizeof(value) && BoolToken::IsTruthy(value, n))
            {
                Log(L"[D3D11] Exit teardown skip disabled by OPENSHIM_KEEP_D3D11_EXIT_TEARDOWN\n");
                return;
            }

            const HMODULE renderer = GetModuleHandleW(L"RenderSystem_Direct3D11.dll");
            if (!renderer)
                return;  // DX9 or not loaded: nothing to guard.

            uint32_t thunk = 0, body = 0;
            const HookEngine::EngineRow rows[] = {
                {"D3D11PluginUninstallThunk", &thunk},
                {"D3D11PluginUninstall", &body},
            };
            if (!HookEngine::BindModuleRows("D3D11 exit teardown skip", renderer, rows))
                return;

            // The thunk must be the uninstall export and jump to the guarded
            // body, and slot 5 of the exported D3D11Plugin vtable must hold it.
            const auto exportAt = [renderer](const char* name) {
                return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(GetProcAddress(renderer, name)));
            };
            const uint32_t vtable = exportAt("??_7D3D11Plugin@Ogre@@6B@");
            const uint32_t slot = vtable ? vtable + 5 * sizeof(uint32_t) : 0;
            int32_t rel = 0;
            std::memcpy(&rel, reinterpret_cast<const void*>(thunk + 1), sizeof(rel));
            if (exportAt("?uninstall@D3D11Plugin@Ogre@@UAEXXZ") != thunk ||
                thunk + 5 + static_cast<uint32_t>(rel) != body ||
                !slot || *reinterpret_cast<const uint32_t*>(slot) != thunk)
            {
                Log(L"[D3D11] Exit teardown skip: rows do not match the renderer exports; left stock\n");
                return;
            }

            DWORD oldProtect = 0;
            if (!VirtualProtect(reinterpret_cast<void*>(slot), 4, PAGE_READWRITE, &oldProtect))
            {
                Log(L"[D3D11] Exit teardown skip: could not unprotect the uninstall slot; left stock\n");
                return;
            }
            const uint32_t skip = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&SkipD3D11PluginUninstall));
            const bool swapped = static_cast<uint32_t>(InterlockedCompareExchange(
                reinterpret_cast<volatile LONG*>(slot), static_cast<LONG>(skip), static_cast<LONG>(thunk))) == thunk;
            DWORD ignored = 0;
            VirtualProtect(reinterpret_cast<void*>(slot), 4, oldProtect, &ignored);
            Log(swapped
                    ? L"[D3D11] Armed exit teardown skip at D3D11Plugin vtable slot 0x%08X\n"
                    : L"[D3D11] Exit teardown skip: uninstall slot 0x%08X changed underneath; left as is\n",
                slot);
        }

        using RootDestructorFn = void(__thiscall*)(void* root);
        static void* g_RealRootDestructor = nullptr;
        static bool g_RootDestructorSeamInstalled = false;

        static void __fastcall RootDestructorExitSeam(void* root, void* /*edx*/)
        {
            __try
            {
                ArmD3D11ExitTeardownSkip();
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                // Never let the guard cost the game its exit path.
            }
            reinterpret_cast<RootDestructorFn>(g_RealRootDestructor)(root);
        }

        static void InstallRootDestructorExitSeam()
        {
            if (g_RootDestructorSeamInstalled)
                return;
            const IatPatch::Result result = IatPatch::PatchImport(
                GetModuleHandleW(nullptr), "OgreMain.dll", "??1Root@Ogre@@QAE@XZ",
                reinterpret_cast<void*>(&RootDestructorExitSeam), &g_RealRootDestructor);
            if (result == IatPatch::Result::Faulted)
                return;  // Retried on the next run state change.
            g_RootDestructorSeamInstalled = true;
            if (result == IatPatch::Result::Patched)
                Log(L"[D3D11] Installed Root destructor exit seam (exit teardown skip)\n");
            else
                Log(L"[D3D11] Root destructor import not found; exit teardown skip unavailable\n");
        }
    }

}
