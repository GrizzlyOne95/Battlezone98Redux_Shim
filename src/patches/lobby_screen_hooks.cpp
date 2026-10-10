// lobby_screen_hooks.cpp
// BZR Open Shim - multiplayer lobby screen hooks: the cUI_TextEntry
// AppendChar detour behind the live nickname entry and the create-screen
// "Map Layout" preview overflow fix, split out of bzr_hooks.cpp.
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
    namespace Hooks
    {
        bool g_LobbyNicknameInputHookInstalled = false;

        static InlineDetour32 g_TextEntryAppendCharDetour = {};

        static FnUiTextEntryAppendChar g_BzrFn_TextEntryAppendCharOriginal = nullptr;

        static bool g_LobbyNicknameInputHookFailureLogged = false;

        static volatile long g_NicknameInputTraceBudget = 16;

        // Lobby screens route keyboard characters to their own stock chat
        // entries through cUI_TextEntry::AppendChar (0x007CFA70), but they do
        // not share one reliable screen-level OnChar target. Intercept the
        // common append operation instead. The detour is inert unless the
        // player explicitly activated our live nickname entry.
        static uint8_t __fastcall TextEntryAppendCharNicknameHook(
            void* thisPtr,
            void* /*unusedEdx*/,
            uint8_t character)
        {
            // The Create Game map search box, while it is being edited.
            uint8_t routed = 0;
            if (TryRouteMapSearchChar(character, g_BzrFn_TextEntryAppendCharOriginal, routed))
                return routed;

            void* const entry = g_ActiveNicknameEntry;
            void* const parent = g_ActiveNicknameParent;
            if (entry && parent && g_BzrFn_TextEntryAppendChar &&
                IsWidgetLiveChildOfParent(parent, entry))
            {
                // A click means "replace" when a configured nickname is
                // already displayed. Keep it visible until the first actual
                // edit so clicking and pressing Enter remains a no-op update.
                if (g_ReplaceNicknameOnNextInput && character != '\r' && character != '\n')
                {
                    if (g_BzrFn_TextEntryClear)
                        g_BzrFn_TextEntryClear(entry);
                    g_ReplaceNicknameOnNextInput = false;
                }
                if (InterlockedDecrement(&g_NicknameInputTraceBudget) >= 0)
                    Log(L"[BZRNET] Nickname input routed (char=0x%02X enter=%hs)\n",
                        static_cast<unsigned>(character),
                        (character == '\r' || character == '\n') ? "yes" : "no");
                const bool isEnter = (character == '\r' || character == '\n');
                if (isEnter)
                    g_NicknameEnterDispatchEntry = entry;
                const uint8_t result = g_BzrFn_TextEntryAppendCharOriginal
                    ? g_BzrFn_TextEntryAppendCharOriginal(entry, character)
                    : 0;
                if (isEnter)
                {
                    g_NicknameEnterDispatchEntry = nullptr;
                    // AppendChar rebuilds the rendered text after invoking its
                    // Enter callback. Paint confirmation only after it returns
                    // so the rebuild cannot immediately erase the message.
                    if (g_PendingNicknameConfirmationEntry == entry)
                    {
                        g_PendingNicknameConfirmationEntry = nullptr;
                        ShowNicknameApplyConfirmation(
                            entry, g_PendingNicknameConfirmationResult);
                    }
                }
                return result;
            }

            if (entry || parent)
            {
                // A rebuilt lobby invalidates injected children. Drop edit
                // mode before falling back so stale pointers receive no input.
                g_ActiveNicknameEntry = nullptr;
                g_ActiveNicknameParent = nullptr;
                g_NicknameEnterDispatchEntry = nullptr;
                g_ReplaceNicknameOnNextInput = false;
            }
            return g_BzrFn_TextEntryAppendCharOriginal
                ? g_BzrFn_TextEntryAppendCharOriginal(thisPtr, character)
                : 0;
        }

        void InstallNicknameTextEntryInputHookIfPossible()
        {
            if (g_LobbyNicknameInputHookInstalled)
                return;

            const uintptr_t kTextEntryAppendCharAddr = HookEngine::EngineAddress("TextEntryAppendChar");
            if (kTextEntryAppendCharAddr == 0)
                return;
            // push ebp; mov ebp,esp; push -1 -- complete instructions only.
            static constexpr uint8_t kExpectedBytes[] =
            {
                0x55, 0x8B, 0xEC, 0x6A, 0xFF
            };

            if (!InstallInlineDetour32(
                    g_TextEntryAppendCharDetour,
                    kTextEntryAppendCharAddr,
                    reinterpret_cast<void*>(TextEntryAppendCharNicknameHook),
                    sizeof(kExpectedBytes),
                    kExpectedBytes,
                    sizeof(kExpectedBytes)))
            {
                if (!g_LobbyNicknameInputHookFailureLogged)
                {
                    Log(L"[BZRNET] TextEntry AppendChar bytes mismatch at 0x%08X; nickname editing disabled\n",
                        static_cast<uint32_t>(kTextEntryAppendCharAddr));
                    g_LobbyNicknameInputHookFailureLogged = true;
                }
                return;
            }

            g_BzrFn_TextEntryAppendCharOriginal =
                reinterpret_cast<FnUiTextEntryAppendChar>(g_TextEntryAppendCharDetour.trampoline);
            g_LobbyNicknameInputHookInstalled =
                (g_BzrFn_TextEntryAppendCharOriginal != nullptr);
            if (g_LobbyNicknameInputHookInstalled)
                Log(L"[BZRNET] Installed TextEntry nickname input routing hook at 0x%08X\n",
                    static_cast<uint32_t>(kTextEntryAppendCharAddr));
        }

        // ---- Multiplayer create-screen "Map Layout" preview overflow fix ----
        //
        // cUI_Multiplayer_Create (ctor 0x00796880) builds the preview as a
        // 200x200 UI-unit image widget ("MapPreview", image ctor 0x007D1CC0),
        // but the first selection update rewrites the widget's design size to
        // the wire texture's pixel size (500x500), so the quad overflows the
        // "Map Layout" frame at every resolution. The quad geometry is built
        // only once (later texture changes just swap the Ogre material), so
        // the fix clamps the design size back to 200x200, re-runs the
        // engine's own layout pass, and rebuilds the quad using the same
        // beginUpdate/rebuild/end sequence the video-texture path uses
        // (0x7D3C92..0x7D3CEA). Driven from the screen's per-frame update
        // virtual (MultiplayerCreateVtable row, slot 13, live-verified as the
        // only per-frame slot), so only this screen ever dispatches the hook.
        // Both vtables are checked by RTTI name; the slot's stock target is
        // whatever the checked vtable holds at bind time.
        static uintptr_t g_MultiCreateUpdateVtblSlotAddr = 0;
        static uintptr_t g_MultiCreateUpdateFnAddr = 0;
        static uint32_t g_MultiMapComponentPtrAddr = 0;
        static uint32_t g_UiImageWidgetVftableAddr = 0;
        static uint32_t g_UiWidgetLayoutFnAddr = 0;
        static uint32_t g_UiImageRebuildGeometryFnAddr = 0;
        constexpr size_t kMultiCreateUpdateVtblIndex = 13;
        constexpr float kMultiMapPreviewDesignSize = 200.0f;

        using FnScreenUpdate = void(__thiscall*)(void*);
        using FnWidgetLayout = void(__thiscall*)(void*, float, float, float, float);
        using FnImageRebuildGeometry = void(__thiscall*)(void*);
        using FnManualObjectBeginUpdate = void(__thiscall*)(void*, uint32_t);
        using FnManualObjectEnd = void(__thiscall*)(void*);

        static FnScreenUpdate g_BzrFn_MultiCreateUpdateOriginal = nullptr;
        static bool g_MultiCreatePreviewHookInstalled = false;
        static bool g_MultiCreatePreviewHookFailureLogged = false;
        static bool g_MultiCreatePreviewClampLogged = false;

        static bool ShouldEnableMapPreviewFix()
        {
            static int s_cached = -1;
            if (s_cached < 0)
            {
                s_cached =
                    (EnvFlagEnabled("OPENSHIM_DISABLE_MAP_PREVIEW_FIX") ||
                     EnvFlagEnabled("BZR_DISABLE_MAP_PREVIEW_FIX")) ? 0 : 1;
            }
            return s_cached != 0;
        }

        static bool MultiCreatePreviewAddressesBound()
        {
            static const bool bound = [] {
                uint32_t screenVtable = 0;
                const HookEngine::EngineRow rows[] = {
                    { "MultiplayerCreateVtable", &screenVtable },
                    { "MultiplayerMapComponent", &g_MultiMapComponentPtrAddr },
                    { "UiPerfMainScreenOverlayVtable", &g_UiImageWidgetVftableAddr },
                    { "UiWidgetLayout", &g_UiWidgetLayoutFnAddr },
                    { "UiImageRebuildGeometry", &g_UiImageRebuildGeometryFnAddr },
                };
                if (!HookEngine::BindEngineRows("Map preview fix", rows))
                    return false;
                if (!VtableTypeNameMatches(screenVtable, ".?AVcUI_Multiplayer_Create@@") ||
                    !VtableTypeNameMatches(g_UiImageWidgetVftableAddr, ".?AVcUI_View@@"))
                {
                    Log(L"[MAPPREVIEW] vtable RTTI mismatch; map preview fix stands down\n");
                    return false;
                }
                g_MultiCreateUpdateVtblSlotAddr = screenVtable + kMultiCreateUpdateVtblIndex * sizeof(void*);
                g_MultiCreateUpdateFnAddr = *reinterpret_cast<const uintptr_t*>(g_MultiCreateUpdateVtblSlotAddr);
                return true;
            }();
            return bound;
        }

        static void ClampMultiCreateMapPreviewIfNeeded()
        {
            __try
            {
                uint8_t* component = *reinterpret_cast<uint8_t**>(g_MultiMapComponentPtrAddr);
                if (!component)
                    return;
                uint8_t* widget = *reinterpret_cast<uint8_t**>(component + 0x1C);
                if (!widget ||
                    *reinterpret_cast<uintptr_t*>(widget) != g_UiImageWidgetVftableAddr)
                    return;

                float* designW = reinterpret_cast<float*>(widget + 0xF4);
                float* designH = reinterpret_cast<float*>(widget + 0xF8);
                if (*designW == kMultiMapPreviewDesignSize &&
                    *designH == kMultiMapPreviewDesignSize)
                    return;

                if (!g_MultiCreatePreviewClampLogged)
                {
                    g_MultiCreatePreviewClampLogged = true;
                    Log(L"[MAPPREVIEW] clamping oversized map preview design %.0fx%.0f -> %.0fx%.0f\n",
                        static_cast<double>(*designW),
                        static_cast<double>(*designH),
                        static_cast<double>(kMultiMapPreviewDesignSize),
                        static_cast<double>(kMultiMapPreviewDesignSize));
                }

                *designW = kMultiMapPreviewDesignSize;
                *designH = kMultiMapPreviewDesignSize;
                const float designX = *reinterpret_cast<float*>(widget + 0xEC);
                const float designY = *reinterpret_cast<float*>(widget + 0xF0);
                reinterpret_cast<FnWidgetLayout>(g_UiWidgetLayoutFnAddr)(
                    widget,
                    designX,
                    designY,
                    kMultiMapPreviewDesignSize,
                    kMultiMapPreviewDesignSize);

                void* manualObject = *reinterpret_cast<void**>(widget + 0x120);
                if (manualObject)
                {
                    uintptr_t* vtbl = *reinterpret_cast<uintptr_t**>(manualObject);
                    reinterpret_cast<FnManualObjectBeginUpdate>(vtbl[0x118 / 4])(manualObject, 0);
                    reinterpret_cast<FnImageRebuildGeometry>(g_UiImageRebuildGeometryFnAddr)(widget);
                    reinterpret_cast<FnManualObjectEnd>(vtbl[0x16C / 4])(manualObject);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                if (!g_MultiCreatePreviewHookFailureLogged)
                {
                    g_MultiCreatePreviewHookFailureLogged = true;
                    Log(L"[MAPPREVIEW] clamp faulted code=0x%08X; leaving preview untouched\n",
                        static_cast<uint32_t>(GetExceptionCode()));
                }
            }
        }

        static void __fastcall MultiCreateUpdateHook(void* screen, void* /*unusedEdx*/)
        {
            if (g_BzrFn_MultiCreateUpdateOriginal)
                g_BzrFn_MultiCreateUpdateOriginal(screen);
            if (ShouldEnableMapPreviewFix())
                ClampMultiCreateMapPreviewIfNeeded();
        }

        void InstallMultiCreatePreviewFixIfPossible()
        {
            if (!ShouldEnableMapPreviewFix() || g_MultiCreatePreviewHookInstalled)
                return;
            if (!MultiCreatePreviewAddressesBound())
                return;

            __try
            {
                void* current = *reinterpret_cast<void**>(g_MultiCreateUpdateVtblSlotAddr);
                if (current == reinterpret_cast<void*>(MultiCreateUpdateHook))
                {
                    g_MultiCreatePreviewHookInstalled = true;
                    return;
                }
                if (current != reinterpret_cast<void*>(g_MultiCreateUpdateFnAddr))
                {
                    if (!g_MultiCreatePreviewHookFailureLogged)
                    {
                        Log(L"[MAPPREVIEW] update hook skipped: slot=0x%08X current=0x%08X expected=0x%08X\n",
                            static_cast<uint32_t>(g_MultiCreateUpdateVtblSlotAddr),
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)),
                            static_cast<uint32_t>(g_MultiCreateUpdateFnAddr));
                        g_MultiCreatePreviewHookFailureLogged = true;
                    }
                    return;
                }

                g_BzrFn_MultiCreateUpdateOriginal =
                    reinterpret_cast<FnScreenUpdate>(current);
                if (!WritePointerValue(
                        g_MultiCreateUpdateVtblSlotAddr,
                        reinterpret_cast<void*>(MultiCreateUpdateHook)))
                {
                    return;
                }
                g_MultiCreatePreviewHookInstalled = true;
                Log(L"[MAPPREVIEW] Installed multi-create map preview fix slot=0x%08X original=0x%08X\n",
                    static_cast<uint32_t>(g_MultiCreateUpdateVtblSlotAddr),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)));
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                if (!g_MultiCreatePreviewHookFailureLogged)
                {
                    Log(L"[MAPPREVIEW] update hook install fault code=0x%08X\n",
                        static_cast<uint32_t>(GetExceptionCode()));
                    g_MultiCreatePreviewHookFailureLogged = true;
                }
            }
        }
    }

}
