// autosave_restart.cpp
// BZR Open Shim - the AutoSave load button injected into the load screen
// and the restart-mission hooks (pause menu and failure screen), split out
// of bzr_hooks.cpp.
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
    void* g_AutoSaveLoadParent = nullptr;

    void* g_AutoSaveLoadScreen = nullptr;

    void* g_AutoSaveLoadButton = nullptr;

    namespace Hooks
    {
        constexpr float kAutoSaveLoadButtonX = 135.0f;

        constexpr float kAutoSaveLoadButtonY = 180.0f + (10.0f * 68.0f);

        constexpr float kAutoSaveLoadButtonW = 1100.0f;

        constexpr float kAutoSaveLoadButtonH = 58.0f;

        constexpr uint32_t kAutoSaveLoadButtonFlags = 0x22;

        constexpr int kRestartMissionState = 6;

        constexpr int kLoadSaveState = 8;

        constexpr uintptr_t kLoadScreenSelectionFlagAddr = 0x00918133;

        constexpr uintptr_t kMissionSaveFlagAddr = 0x009173B7;

        constexpr uintptr_t kOldMissionModeAddr = 0x00918314;

        constexpr uintptr_t kUiScreenTypeAddr = 0x00918328;

        static bool AutoSaveFileExists()
        {
            const auto moduleDir = GetMainModuleDirectory();
            if (moduleDir.empty())
                return false;

            std::error_code error;
            return std::filesystem::exists(moduleDir / "Save" / "auto.sav", error) ||
                std::filesystem::exists(moduleDir / "Save" / "auto2.sav", error);
        }

        static bool TryGetAutoSaveFilePathUtf8(char (&outPath)[MAX_PATH])
        {
            outPath[0] = '\0';

            const auto moduleDir = GetMainModuleDirectory();
            if (moduleDir.empty())
                return false;

            std::error_code error;
            const auto primaryPath = moduleDir / "Save" / "auto.sav";
            if (std::filesystem::exists(primaryPath, error))
            {
                const auto primaryString = primaryPath.string();
                return strncpy_s(outPath, primaryString.c_str(), _TRUNCATE) == 0;
            }

            error.clear();
            const auto secondaryPath = moduleDir / "Save" / "auto2.sav";
            if (std::filesystem::exists(secondaryPath, error))
            {
                const auto secondaryString = secondaryPath.string();
                return strncpy_s(outPath, secondaryString.c_str(), _TRUNCATE) == 0;
            }

            return false;
        }

        static std::string GetAutoSaveButtonLabel()
        {
            char autoSavePath[MAX_PATH] = {};
            if (!TryGetAutoSaveFilePathUtf8(autoSavePath))
                return "AutoSave";

            std::filesystem::path labelPath(autoSavePath);
            labelPath.replace_extension(".label.txt");

            std::ifstream input(labelPath, std::ios::binary);
            if (!input.is_open())
                return "AutoSave";

            std::string data((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
            if (!input.good() && !input.eof())
                return "AutoSave";

            data.erase(std::remove(data.begin(), data.end(), '\0'), data.end());
            data.erase(std::remove(data.begin(), data.end(), '\r'), data.end());
            data.erase(std::remove(data.begin(), data.end(), '\n'), data.end());

            const auto trimPred = [](unsigned char ch)
            {
                return std::isspace(ch) != 0;
            };
            data.erase(data.begin(), std::find_if(data.begin(), data.end(), [&](char ch)
            {
                return !trimPred(static_cast<unsigned char>(ch));
            }));
            data.erase(std::find_if(data.rbegin(), data.rend(), [&](char ch)
            {
                return !trimPred(static_cast<unsigned char>(ch));
            }).base(), data.end());

            if (data.empty())
                return "AutoSave";

            constexpr size_t kMaxButtonLabelChars = 96;
            if (data.size() > kMaxButtonLabelChars)
                data.resize(kMaxButtonLabelChars);

            return data;
        }

        static void PrepareLoadScreenForSelection(void* screen)
        {
            if (!screen)
                return;

            auto* screenBytes = reinterpret_cast<uint8_t*>(screen);
            void* dialog = *reinterpret_cast<void**>(screenBytes + 0x138);
            if (!dialog || !g_BzrFn_UiDialogSetEnabled || !g_BzrFn_UiDialogAdvance ||
                !g_BzrFn_LoadScreenPrep || !g_BzrFn_BzrStringCtorFromCStr ||
                !g_BzrFn_BzrStringDtor || !g_BzrFn_LoadScreenClearSelection)
            {
                return;
            }

            if (BZROpenShim::UiPerf::IsEnabled())
                BZROpenShim::UiPerf::NotifyShellRequest(0x17);
            *reinterpret_cast<uint8_t*>(kLoadScreenSelectionFlagAddr) = 1;
            g_BzrFn_UiDialogSetEnabled(dialog, 0);
            g_BzrFn_LoadScreenPrep();
            g_BzrFn_UiDialogAdvance(dialog, 0x17);

            BzrString emptyText = {};
            g_BzrFn_BzrStringCtorFromCStr(&emptyText, "");
            g_BzrFn_LoadScreenClearSelection(&emptyText);
            g_BzrFn_BzrStringDtor(&emptyText);
        }

        static bool QueueAutoSaveLoadPath(const char* autoSavePath)
        {
            if (!autoSavePath || !autoSavePath[0])
                return false;

            auto* queuedPath = reinterpret_cast<char*>(kQueuedLoadPathBufferAddr);
            auto* queuedName = reinterpret_cast<char*>(kQueuedLoadNameBufferAddr);
            if (!queuedPath || !queuedName)
                return false;

            // Blanking the name is deliberate -- it makes the load screen use the
            // explicit path below rather than re-deriving one -- but it is also
            // the moment the mission identity is lost, so keep a copy first.
            RememberQueuedMissionName(queuedName);
            queuedName[0] = '\0';
            return strncpy_s(queuedPath, MAX_PATH, autoSavePath, _TRUNCATE) == 0;
        }

        static bool RefreshQueuedPathFromMissionName()
        {
            auto* queuedPath = reinterpret_cast<char*>(kQueuedLoadPathBufferAddr);
            auto* queuedName = reinterpret_cast<const char*>(kQueuedLoadNameBufferAddr);
            if (!queuedPath || !queuedName || !queuedName[0])
                return false;

            return strncpy_s(queuedPath, MAX_PATH, queuedName, _TRUNCATE) == 0;
        }

        static void ForceFreshRestartMissionState(void* screenThis, const char* sourceTag)
        {
            if (!screenThis)
            {
                Log(L"[RESTART] %hs missing screen context\n", sourceTag ? sourceTag : "unknown");
                return;
            }

            auto* screenBytes = reinterpret_cast<uint8_t*>(screenThis);
            void* dialog = *reinterpret_cast<void**>(screenBytes + 0x138);
            if (!dialog || !g_BzrFn_UiDialogSetEnabled || !g_BzrFn_UiDialogAdvance ||
                !g_BzrFn_LoadScreenPrep || !g_BzrFn_BzrStringCtorFromCStr ||
                !g_BzrFn_BzrStringDtor || !g_BzrFn_LoadScreenClearSelection ||
                !g_BzrFn_SetShellState)
            {
                Log(L"[RESTART] %hs missing restart helpers dialog=0x%p setEnabled=0x%p advance=0x%p prep=0x%p strCtor=0x%p strDtor=0x%p clearSelection=0x%p setState=0x%p\n",
                    sourceTag ? sourceTag : "unknown",
                    dialog,
                    g_BzrFn_UiDialogSetEnabled,
                    g_BzrFn_UiDialogAdvance,
                    g_BzrFn_LoadScreenPrep,
                    g_BzrFn_BzrStringCtorFromCStr,
                    g_BzrFn_BzrStringDtor,
                    g_BzrFn_LoadScreenClearSelection,
                    g_BzrFn_SetShellState);
                return;
            }

            auto* missionSaveFlag = reinterpret_cast<uint8_t*>(kMissionSaveFlagAddr);
            auto* oldMissionMode = reinterpret_cast<uint32_t*>(kOldMissionModeAddr);
            auto* screenType = reinterpret_cast<uint32_t*>(kUiScreenTypeAddr);
            auto* queuedPath = reinterpret_cast<const char*>(kQueuedLoadPathBufferAddr);
            auto* queuedName = reinterpret_cast<const char*>(kQueuedLoadNameBufferAddr);

            const uint8_t previousMissionSave = *missionSaveFlag;
            const uint32_t previousMissionMode = *oldMissionMode;
            char previousQueuedPath[MAX_PATH] = {};
            strncpy_s(previousQueuedPath, queuedPath ? queuedPath : "", _TRUNCATE);

            // Restart state 6 skips parts of normal mission teardown. Drop all
            // shim-owned Ogre scene references before asking the shell to enter
            // that path; otherwise the render hook can submit a freed SubEntity
            // while the loading screen is still drawing frames.
            ForgetAllChunkProxySceneResources(L"restart mission");

            *missionSaveFlag = 0;
            *oldMissionMode = 0;
            const bool refreshedQueuedPath = RefreshQueuedPathFromMissionName();
            PrepareLoadScreenForSelection(screenThis);
            g_BzrFn_SetShellState(kRestartMissionState);
            *screenType = 0;

            Log(L"[RESTART] %hs forcing restart mission reload state=%d missionSave=%u->%u oldMissionMode=%u->%u queuedName=%hs queuedPath=%hs refreshedQueuedPath=%hs previousQueuedPath=%hs\n",
                sourceTag ? sourceTag : "unknown",
                kRestartMissionState,
                previousMissionSave,
                *missionSaveFlag,
                previousMissionMode,
                *oldMissionMode,
                queuedName,
                queuedPath,
                refreshedQueuedPath ? "true" : "false",
                previousQueuedPath);
        }
    }

    using namespace Hooks;

    // The native load screen sets BOTH callback slots on every load-slot button:
    // +0x150 (via 0x007C23C0, "SetOnHover") and +0x154 (via 0x007C23E0,
    // "SetOnClick"). When the screen is opened it walks every dialog child and
    // invokes each child's +0x150 slot, so any child that leaves +0x150 null
    // causes a call-through-null (EIP=0) crash. Our injected AutoSave button
    // only set the click slot, leaving +0x150 null -> deterministic crash on
    // opening Load/Save whenever an auto.sav exists. This benign no-op keeps the
    // hover slot non-null (matching the stock slot buttons) without triggering
    // the load path on hover/refresh.
    void __cdecl AutoSaveButtonOnHoverNoop(void* /*param*/)
    {
    }

    void __cdecl AutoSaveButtonOnClickLoad()
    {
        if (!g_BzrFn_SetShellState)
            return;

        char autoSavePath[MAX_PATH] = {};
        if (!TryGetAutoSaveFilePathUtf8(autoSavePath))
        {
            Log(L"[AUTOSAVE] AutoSave button clicked but no auto-save file exists\n");
            return;
        }

        __try
        {
            PrepareLoadScreenForSelection(g_AutoSaveLoadScreen);
            if (!QueueAutoSaveLoadPath(autoSavePath))
            {
                Log(L"[AUTOSAVE] Failed to queue auto-save load path=%hs\n", autoSavePath);
                return;
            }

            auto* queuedPath = reinterpret_cast<char*>(kQueuedLoadPathBufferAddr);
            Log(L"[AUTOSAVE] Auto-save queued for stock save-load state path=%hs\n",
                queuedPath);
            g_BzrFn_SetShellState(kLoadSaveState);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            Log(L"[AUTOSAVE] Direct auto-save load raised an exception\n");
        }
    }

    // POD-only helper so __try/__except is valid (no C++ objects with destructors).
    // Returns true if the button is still alive and was updated, false if it was
    // dangling (exception caught) so the caller should create a fresh button.
    static bool TryUpdateAutoSaveLoadButton(const char* label)
    {
        __try
        {
            if (g_BzrFn_SetButtonLabel)
                g_BzrFn_SetButtonLabel(g_AutoSaveLoadButton, label);
            if (g_BzrFn_SetOnClick) g_BzrFn_SetOnClick(g_AutoSaveLoadButton, reinterpret_cast<void*>(AutoSaveButtonOnClickLoad));
            if (g_BzrFn_SetOnHover) g_BzrFn_SetOnHover(g_AutoSaveLoadButton, reinterpret_cast<void*>(AutoSaveButtonOnHoverNoop));
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            g_AutoSaveLoadButton = nullptr;
            return false;
        }
        return true;
    }

    static void AutoSaveLoadButtonCreate(void* parent, void* screen)
    {
        // The engine calls a child button's hover/click slots; a button built
        // without them crashes the dialog, so both setters are required.
        if (!parent || !screen || !g_BzrFn_ButtonCtor || !g_BzrFn_AddChild ||
            !g_BzrFn_SetOnClick || !g_BzrFn_SetOnHover)
            return;

        if (!AutoSaveFileExists())
            return;

        const std::string autoSaveLabel = GetAutoSaveButtonLabel();
        // Pointer equality alone cannot prove the cached button survived a
        // screen rebuild at a recycled address; require it to still be linked
        // into the live parent's child vector before updating it in place.
        if (g_AutoSaveLoadButton && g_AutoSaveLoadParent == parent && g_AutoSaveLoadScreen == screen &&
            IsWidgetLiveChildOfParent(parent, g_AutoSaveLoadButton))
        {
            if (TryUpdateAutoSaveLoadButton(autoSaveLabel.c_str()))
                return;
        }

        g_AutoSaveLoadParent = parent;
        g_AutoSaveLoadScreen = screen;
        g_AutoSaveLoadButton = nullptr;

        void* buttonMem = ::operator new(0x1EC, std::nothrow);
        if (!buttonMem)
            return;

        std::memset(buttonMem, 0, 0x1EC);
        g_AutoSaveLoadButton = g_BzrFn_ButtonCtor(
            buttonMem,
            autoSaveLabel.c_str(),
            kAutoSaveLoadButtonX,
            kAutoSaveLoadButtonY,
            kAutoSaveLoadButtonW,
            kAutoSaveLoadButtonH,
            kAutoSaveLoadButtonFlags,
            parent,
            0,
            0);

        if (!g_AutoSaveLoadButton)
            return;

        if (g_BzrFn_SetTextureOff) g_BzrFn_SetTextureOff(g_AutoSaveLoadButton, "mpcron.png");
        if (g_BzrFn_SetTextureOver) g_BzrFn_SetTextureOver(g_AutoSaveLoadButton, "mpcrclk.png");
        if (g_BzrFn_SetTextureOn) g_BzrFn_SetTextureOn(g_AutoSaveLoadButton, "mpcrclk.png");
        if (g_BzrFn_SetButtonLabel) g_BzrFn_SetButtonLabel(g_AutoSaveLoadButton, autoSaveLabel.c_str());
        // 0x007CC660 is a label-style tooltip writer that stores text inline at
        // +0x144. Button objects use +0x150/+0x154 for hover/click callbacks,
        // so using it here corrupts the callback slot and crashes the load menu.
        if (g_BzrFn_SetOnClick) g_BzrFn_SetOnClick(g_AutoSaveLoadButton, reinterpret_cast<void*>(AutoSaveButtonOnClickLoad));
        // Mirror the stock load-slot buttons by also populating the +0x150 slot.
        // Without this the load screen invokes a null callback on open and
        // crashes (call through NULL / EIP=0). See AutoSaveButtonOnHoverNoop.
        if (g_BzrFn_SetOnHover) g_BzrFn_SetOnHover(g_AutoSaveLoadButton, reinterpret_cast<void*>(AutoSaveButtonOnHoverNoop));
        g_BzrFn_AddChild(parent, g_AutoSaveLoadButton, 0);
    }

    void AutoSaveLoadButtonCreateFromFrame(void* frameBase)
    {
        if (!frameBase)
            return;

        __try
        {
            auto* frame = reinterpret_cast<uint8_t*>(frameBase);
            void* parent = *reinterpret_cast<void**>(frame - 0x184);
            void* screen = *reinterpret_cast<void**>(frame - 0x178);
            AutoSaveLoadButtonCreate(parent, screen);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            Log(L"[AUTOSAVE] Failed to inspect load screen frame for AutoSave button injection\n");
        }
    }

    void __fastcall RestartMissionPauseHook(void* thisPtr)
    {
        ForceFreshRestartMissionState(thisPtr, "pause");
    }

    void __fastcall RestartMissionFailureHook(void* thisPtr)
    {
        ForceFreshRestartMissionState(thisPtr, "failure");
    }
}
