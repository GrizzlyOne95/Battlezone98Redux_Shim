// ogre_dedupe_crash_fixes.cpp
// BZR Open Shim - two Ogre crash fixes: the ParticleSystemManager::
// createTemplate dedupe detour and the UI "Top Screen" ManualObject orphan
// dedupe detour, split out of bzr_hooks.cpp.
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
#include "render_queue_trace.h"
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
    namespace Hooks
    {
        static InlineDetour32 g_ParticleCreateTemplateDetour = {};

        static bool g_ParticleTemplateDedupeHookInstalled = false;

        static bool g_ParticleTemplateDedupeFailureLogged = false;

        static InlineDetour32 g_UiManualObjectEnsureDetour = {};

        static bool g_UiManualObjectDedupeHookInstalled = false;

        static bool g_UiManualObjectDedupeFailureLogged = false;

        static bool g_UiManualObjectDedupeTestInjected = false;

        // Ogre particle templates are process-global, but the game re-parses
        // every mod resource group's .particle scripts when resource groups are
        // re-initialised (e.g. leaving a multiplayer lobby back to the main
        // menu). Stock ParticleSystemManager::createTemplate throws
        // ItemIdentityException on the duplicate name, and the exception is
        // never caught -> terminate/abort (dump battlezone98redux.exe.30808:
        // "ParticleSystem template with name 'Weather/Rain/Heavy' already
        // exists."). Detour createTemplate to drop the stale template first so
        // the parser rebuilds it cleanly.
        using FnOgreParticleCreateTemplate = void*(__thiscall*)(void*, const std::string&, const std::string&);
        using FnOgreParticleGetTemplate = void*(__thiscall*)(void*, const std::string&);
        using FnOgreParticleRemoveTemplate = void(__thiscall*)(void*, const std::string&, bool);

        static FnOgreParticleCreateTemplate g_OgreFn_ParticleCreateTemplateOriginal = nullptr;
        static FnOgreParticleGetTemplate g_OgreFn_ParticleGetTemplate = nullptr;
        static FnOgreParticleRemoveTemplate g_OgreFn_ParticleRemoveTemplate = nullptr;

        void* __fastcall ParticleCreateTemplateDedupeHook(void* thisPtr,
                                                          void* /*edx*/,
                                                          const std::string& name,
                                                          const std::string& resourceGroup)
        {
            if (thisPtr &&
                g_OgreFn_ParticleGetTemplate &&
                g_OgreFn_ParticleRemoveTemplate &&
                g_OgreFn_ParticleGetTemplate(thisPtr, name) != nullptr)
            {
                Log(L"[PARTICLE] Removing stale particle template '%hs' before re-create\n",
                    name.c_str());
                g_OgreFn_ParticleRemoveTemplate(thisPtr, name, true);
            }

            if (!g_OgreFn_ParticleCreateTemplateOriginal)
                return nullptr;

            return g_OgreFn_ParticleCreateTemplateOriginal(thisPtr, name, resourceGroup);
        }

        void InstallParticleTemplateDedupeHookIfPossible()
        {
            if (g_ParticleTemplateDedupeHookInstalled)
                return;

            HMODULE ogreMain = GetModuleHandleA("OgreMain.dll");
            if (!ogreMain)
                return;

            const auto resolveExportBody = [ogreMain](const char* exportName) -> uint8_t*
            {
                auto* proc = reinterpret_cast<uint8_t*>(GetProcAddress(ogreMain, exportName));
                if (!proc)
                    return nullptr;

                // The shipped OgreMain.dll is incrementally linked: exports
                // land on a `jmp rel32` thunk. Follow it so the detour patches
                // the real function body every internal call site reaches.
                if (proc[0] == 0xE9)
                {
                    int32_t rel = 0;
                    memcpy(&rel, proc + 1, sizeof(rel));
                    proc = proc + 5 + rel;
                }
                return proc;
            };

            uint8_t* createTemplateBody = resolveExportBody(
                "?createTemplate@ParticleSystemManager@Ogre@@QAEPAVParticleSystem@2@"
                "ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
            g_OgreFn_ParticleGetTemplate = ResolveOgreProc<FnOgreParticleGetTemplate>(
                "?getTemplate@ParticleSystemManager@Ogre@@QAEPAVParticleSystem@2@"
                "ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
            g_OgreFn_ParticleRemoveTemplate = ResolveOgreProc<FnOgreParticleRemoveTemplate>(
                "?removeTemplate@ParticleSystemManager@Ogre@@QAEXABV?$basic_string@"
                "DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");

            if (!createTemplateBody ||
                !g_OgreFn_ParticleGetTemplate ||
                !g_OgreFn_ParticleRemoveTemplate)
            {
                if (!g_ParticleTemplateDedupeFailureLogged)
                {
                    Log(L"[PARTICLE] createTemplate dedupe hook: OgreMain exports unresolved\n");
                    g_ParticleTemplateDedupeFailureLogged = true;
                }
                return;
            }

            static const uint8_t kExpectedCreateTemplateBytes[] =
            {
                0x55, 0x8B, 0xEC, 0x6A, 0xFF // push ebp; mov ebp,esp; push -1
            };

            if (!ExpectedBytesMatchAt(reinterpret_cast<uintptr_t>(createTemplateBody),
                                      kExpectedCreateTemplateBytes,
                                      sizeof(kExpectedCreateTemplateBytes)))
            {
                if (!g_ParticleTemplateDedupeFailureLogged)
                {
                    Log(L"[PARTICLE] createTemplate prologue mismatch at 0x%08X; dedupe hook skipped\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(createTemplateBody)));
                    g_ParticleTemplateDedupeFailureLogged = true;
                }
                return;
            }

            if (!InstallInlineDetour32(g_ParticleCreateTemplateDetour,
                                       reinterpret_cast<uintptr_t>(createTemplateBody),
                                       reinterpret_cast<void*>(ParticleCreateTemplateDedupeHook),
                                       sizeof(kExpectedCreateTemplateBytes),
                                       kExpectedCreateTemplateBytes,
                                       sizeof(kExpectedCreateTemplateBytes)))
            {
                if (!g_ParticleTemplateDedupeFailureLogged)
                {
                    Log(L"[PARTICLE] Failed installing createTemplate dedupe hook at 0x%08X\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(createTemplateBody)));
                    g_ParticleTemplateDedupeFailureLogged = true;
                }
                return;
            }

            g_OgreFn_ParticleCreateTemplateOriginal =
                reinterpret_cast<FnOgreParticleCreateTemplate>(g_ParticleCreateTemplateDetour.trampoline);
            g_ParticleTemplateDedupeHookInstalled = true;
            Log(L"[PARTICLE] Installed ParticleSystemManager::createTemplate dedupe hook body=0x%08X trampoline=0x%08X\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(createTemplateBody)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_ParticleCreateTemplateDetour.trampoline)));
        }

        // Redux UI widgets lazily create a named ManualObject in FUN_007D2B70.
        // Dump 29188 proved that the widget's cached pointer can be null while
        // SceneManager still owns the old "Top Screen" object. Stock then
        // calls createManualObject with the duplicate name; Ogre throws an
        // ItemIdentityException which escapes the main loop and terminates the
        // process. Remove only this verified orphan immediately before the
        // stock widget rebuild. ManualObject destruction detaches it from its
        // old SceneNode, and Redux creates/attaches a fresh object normally.
        constexpr uintptr_t kUiEnsureManualObjectAddr = 0x007D2B70;
        constexpr size_t kUiManualObjectPtrOffset = 0x120;
        constexpr size_t kUiWidgetNameOffset = 0x20;

        struct UiOgreSharedPtr
        {
            void* rep;
            void* info;
        };
        static_assert(sizeof(UiOgreSharedPtr) == 8, "Redux Ogre SharedPtr ABI changed");

        // FUN_007D2B70 receives an Ogre SharedPtr by value in two stack
        // dwords and returns with `ret 8`; preserving that hidden-looking
        // argument is mandatory even though the best-effort decompiler omits
        // it from the prototype.
        using FnUiEnsureManualObject = void(__thiscall*)(void*, UiOgreSharedPtr);
        using FnOgreHasManualObject = bool(__thiscall*)(void*, const std::string&);
        using FnOgreDestroyManualObject = void(__thiscall*)(void*, const std::string&);

        static FnUiEnsureManualObject g_BzrFn_UiEnsureManualObjectOriginal = nullptr;
        static FnOgreHasManualObject g_OgreFn_HasManualObject = nullptr;
        static FnOgreDestroyManualObject g_OgreFn_DestroyManualObject = nullptr;

        static bool ShouldEnableUiManualObjectDedupe()
        {
            return !(EnvFlagEnabled("OPENSHIM_DISABLE_UI_MANUAL_OBJECT_DEDUPE") ||
                     EnvFlagEnabled("BZR_DISABLE_UI_MANUAL_OBJECT_DEDUPE"));
        }

        static bool ShouldInjectUiManualObjectOrphanTest()
        {
            return EnvFlagEnabled("OPENSHIM_TEST_UI_MANUAL_OBJECT_ORPHAN");
        }

        static void __fastcall UiEnsureManualObjectDedupeHook(
            void* widget, void* /*unusedEdx*/, UiOgreSharedPtr resource)
        {
            if (widget && g_OgreFn_HasManualObject && g_OgreFn_DestroyManualObject)
            {
                try
                {
                    auto* bytes = reinterpret_cast<uint8_t*>(widget);
                    void** cachedManualObjectSlot =
                        reinterpret_cast<void**>(bytes + kUiManualObjectPtrOffset);
                    void* cachedManualObject = *cachedManualObjectSlot;
                    const std::string& name =
                        *reinterpret_cast<const std::string*>(bytes + kUiWidgetNameOffset);
                    if (name == "Top Screen")
                    {
                        auto* const renderGlobalsSlot =
                            reinterpret_cast<void**>(EngineGlobals::RenderGlobals());
                        void* sceneRoot = renderGlobalsSlot ? *renderGlobalsSlot : nullptr;
                        void* sceneManager = sceneRoot
                            ? *reinterpret_cast<void**>(
                                reinterpret_cast<uint8_t*>(sceneRoot) + 8)
                            : nullptr;
                        const bool registered = sceneManager &&
                            g_OgreFn_HasManualObject(sceneManager, name);

                        // Deterministic regression path for dump 29188. The
                        // inherited environment flag is test-only and off by
                        // default; when set, manufacture the exact proven
                        // state once (null widget cache, still-registered Ogre
                        // object) and immediately exercise normal recovery.
                        if (cachedManualObject && registered &&
                            !g_UiManualObjectDedupeTestInjected &&
                            ShouldInjectUiManualObjectOrphanTest())
                        {
                            g_UiManualObjectDedupeTestInjected = true;
                            *cachedManualObjectSlot = nullptr;
                            cachedManualObject = nullptr;
                            Log(L"[UI-DEDUPE] TEST injected orphan ManualObject '%hs'\n",
                                name.c_str());
                        }

                        if (!cachedManualObject && registered)
                        {
                            Log(L"[UI-DEDUPE] Removing orphan ManualObject '%hs' before stock rebuild (dump 29188)\n",
                                name.c_str());
                            g_OgreFn_DestroyManualObject(sceneManager, name);
                        }
                    }
                }
                catch (...)
                {
                    if (!g_UiManualObjectDedupeFailureLogged)
                    {
                        Log(L"[UI-DEDUPE] Orphan lookup/removal threw; stock UI path retained\n");
                        g_UiManualObjectDedupeFailureLogged = true;
                    }
                }
            }

            if (g_BzrFn_UiEnsureManualObjectOriginal)
                g_BzrFn_UiEnsureManualObjectOriginal(widget, resource);
        }

        void InstallUiManualObjectDedupeHookIfPossible()
        {
            if (!ShouldEnableUiManualObjectDedupe() ||
                g_UiManualObjectDedupeHookInstalled)
                return;

            HMODULE ogreMain = GetModuleHandleA("OgreMain.dll");
            if (!ogreMain)
                return;

            g_OgreFn_HasManualObject = ResolveOgreProc<FnOgreHasManualObject>(
                "?hasManualObject@SceneManager@Ogre@@UBE_NABV?$basic_string@"
                "DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
            g_OgreFn_DestroyManualObject = ResolveOgreProc<FnOgreDestroyManualObject>(
                "?destroyManualObject@SceneManager@Ogre@@UAEXABV?$basic_string@"
                "DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
            if (!g_OgreFn_HasManualObject || !g_OgreFn_DestroyManualObject)
            {
                if (!g_UiManualObjectDedupeFailureLogged)
                {
                    Log(L"[UI-DEDUPE] Ogre ManualObject exports unresolved; recovery skipped\n");
                    g_UiManualObjectDedupeFailureLogged = true;
                }
                return;
            }

            static const uint8_t kExpectedBytes[] =
            {
                0x55, 0x8B, 0xEC, 0x6A, 0xFF
            };
            if (!ExpectedBytesMatchAt(kUiEnsureManualObjectAddr,
                                      kExpectedBytes,
                                      sizeof(kExpectedBytes)))
            {
                if (!g_UiManualObjectDedupeFailureLogged)
                {
                    Log(L"[UI-DEDUPE] FUN_007D2B70 entry mismatch; recovery skipped\n");
                    g_UiManualObjectDedupeFailureLogged = true;
                }
                return;
            }

            if (!InstallInlineDetour32(g_UiManualObjectEnsureDetour,
                                       kUiEnsureManualObjectAddr,
                                       reinterpret_cast<void*>(UiEnsureManualObjectDedupeHook),
                                       sizeof(kExpectedBytes),
                                       kExpectedBytes,
                                       sizeof(kExpectedBytes)))
            {
                if (!g_UiManualObjectDedupeFailureLogged)
                {
                    Log(L"[UI-DEDUPE] Failed installing FUN_007D2B70 recovery hook\n");
                    g_UiManualObjectDedupeFailureLogged = true;
                }
                return;
            }

            g_BzrFn_UiEnsureManualObjectOriginal =
                reinterpret_cast<FnUiEnsureManualObject>(
                    g_UiManualObjectEnsureDetour.trampoline);
            g_UiManualObjectDedupeHookInstalled =
                g_BzrFn_UiEnsureManualObjectOriginal != nullptr;
            if (g_UiManualObjectDedupeHookInstalled)
            {
                Log(L"[UI-DEDUPE] Installed Top Screen ManualObject orphan recovery entry=0x%08X trampoline=0x%08X\n",
                    static_cast<uint32_t>(kUiEnsureManualObjectAddr),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(
                        g_UiManualObjectEnsureDetour.trampoline)));
            }
        }
    }
}
