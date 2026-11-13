// autosave_restart.cpp
// BZR Open Shim - the AutoSave and QuickSave load buttons injected into the load screen
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
        // Injected load-screen slots below the ten stock ones: AutoSave is the
        // 11th row, QuickSave the 12th.
        constexpr float kInjectedLoadButtonX = 135.0f;

        constexpr float kInjectedLoadButtonFirstY = 180.0f + (10.0f * 68.0f);

        constexpr float kInjectedLoadButtonRowStep = 68.0f;

        constexpr float kInjectedLoadButtonW = 1100.0f;

        constexpr float kInjectedLoadButtonH = 58.0f;

        constexpr uint32_t kInjectedLoadButtonFlags = 0x22;

        constexpr int kRestartMissionState = 6;

        constexpr int kLoadSaveState = 8;

        // engine_addresses rows; the load button and restart handlers leave
        // stock behaviour alone when they do not bind.
        uint32_t g_LoadScreenSelectionFlagAddr = 0;

        uint32_t g_MissionSaveFlagAddr = 0;

        uint32_t g_OldMissionModeAddr = 0;

        uint32_t g_UiScreenTypeAddr = 0;

        static bool AutoSaveRestartAddressesBound()
        {
            static const bool bound = [] {
                const HookEngine::EngineRow bind[] = {
                    { "LoadScreenSelectionFlag", &g_LoadScreenSelectionFlagAddr },
                    { "MissionSaveFlag", &g_MissionSaveFlagAddr },
                    { "OldMissionMode", &g_OldMissionModeAddr },
                    { "UiCurrentScreenType", &g_UiScreenTypeAddr },
                };
                return HookEngine::BindEngineRows("AutoSave load/restart", bind) &&
                       QueuedLoadPathBufferAddr() != 0 && QueuedLoadNameBufferAddr() != 0;
            }();
            return bound;
        }

        // One injected load-screen slot: the save files it loads (first
        // existing stem wins), its fallback text and its row, plus the live
        // button it last built.
        struct InjectedLoadSlot
        {
            const char* const* stems;
            size_t stemCount;
            const char* fallbackLabel;
            const char* logName;
            float y;
            void(__cdecl* onClick)();
            void* parent;
            void* screen;
            void* button;
        };

        static bool TryGetSlotFilePathUtf8(const InjectedLoadSlot& slot, char (&outPath)[MAX_PATH])
        {
            outPath[0] = '\0';

            const auto moduleDir = GetMainModuleDirectory();
            if (moduleDir.empty())
                return false;

            for (size_t index = 0; index < slot.stemCount; ++index)
            {
                std::error_code error;
                const auto path = moduleDir / "Save" / (std::string(slot.stems[index]) + ".sav");
                if (std::filesystem::exists(path, error))
                {
                    const auto pathString = path.string();
                    return strncpy_s(outPath, pathString.c_str(), _TRUNCATE) == 0;
                }
            }

            return false;
        }

        static bool SlotFileExists(const InjectedLoadSlot& slot)
        {
            char path[MAX_PATH] = {};
            return TryGetSlotFilePathUtf8(slot, path);
        }

        static std::string GetSlotButtonLabel(const InjectedLoadSlot& slot)
        {
            char savePath[MAX_PATH] = {};
            if (!TryGetSlotFilePathUtf8(slot, savePath))
                return slot.fallbackLabel;

            std::filesystem::path labelPath(savePath);
            labelPath.replace_extension(".label.txt");

            std::ifstream input(labelPath, std::ios::binary);
            if (!input.is_open())
                return slot.fallbackLabel;

            std::string data((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
            if (!input.good() && !input.eof())
                return slot.fallbackLabel;

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
                return slot.fallbackLabel;

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

            if (!AutoSaveRestartAddressesBound())
                return;
            if (BZROpenShim::UiPerf::IsEnabled())
                BZROpenShim::UiPerf::NotifyShellRequest(0x17);
            *reinterpret_cast<uint8_t*>(g_LoadScreenSelectionFlagAddr) = 1;
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

            auto* queuedPath = reinterpret_cast<char*>(QueuedLoadPathBufferAddr());
            auto* queuedName = reinterpret_cast<char*>(QueuedLoadNameBufferAddr());
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
            auto* queuedPath = reinterpret_cast<char*>(QueuedLoadPathBufferAddr());
            auto* queuedName = reinterpret_cast<const char*>(QueuedLoadNameBufferAddr());
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

            if (!AutoSaveRestartAddressesBound())
                return;
            auto* missionSaveFlag = reinterpret_cast<uint8_t*>(g_MissionSaveFlagAddr);
            auto* oldMissionMode = reinterpret_cast<uint32_t*>(g_OldMissionModeAddr);
            auto* screenType = reinterpret_cast<uint32_t*>(g_UiScreenTypeAddr);
            auto* queuedPath = reinterpret_cast<const char*>(QueuedLoadPathBufferAddr());
            auto* queuedName = reinterpret_cast<const char*>(QueuedLoadNameBufferAddr());

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

    static void __cdecl QuickSaveButtonOnClickLoad();

    static const char* const kAutoSaveSlotStems[] = { "auto", "auto2" };
    static const char* const kQuickSaveSlotStems[] = { "quick" };

    static InjectedLoadSlot g_AutoSaveLoadSlot = {
        kAutoSaveSlotStems, 2, "AutoSave", "Auto-save",
        kInjectedLoadButtonFirstY, &AutoSaveButtonOnClickLoad, nullptr, nullptr, nullptr };
    static InjectedLoadSlot g_QuickSaveLoadSlot = {
        kQuickSaveSlotStems, 1, "QuickSave", "Quick-save",
        kInjectedLoadButtonFirstY + kInjectedLoadButtonRowStep, &QuickSaveButtonOnClickLoad,
        nullptr, nullptr, nullptr };

    static void LoadInjectedSlot(const InjectedLoadSlot& slot)
    {
        if (!g_BzrFn_SetShellState)
            return;

        char savePath[MAX_PATH] = {};
        if (!TryGetSlotFilePathUtf8(slot, savePath))
        {
            Log(L"[AUTOSAVE] %hs button clicked but no save file exists\n", slot.logName);
            return;
        }

        __try
        {
            PrepareLoadScreenForSelection(slot.screen);
            if (!QueueAutoSaveLoadPath(savePath))
            {
                Log(L"[AUTOSAVE] Failed to queue %hs load path=%hs\n", slot.logName, savePath);
                return;
            }

            auto* queuedPath = reinterpret_cast<char*>(QueuedLoadPathBufferAddr());
            Log(L"[AUTOSAVE] %hs queued for stock save-load state path=%hs\n",
                slot.logName, queuedPath);
            g_BzrFn_SetShellState(kLoadSaveState);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            Log(L"[AUTOSAVE] Direct %hs load raised an exception\n", slot.logName);
        }
    }

    void __cdecl AutoSaveButtonOnClickLoad()
    {
        LoadInjectedSlot(g_AutoSaveLoadSlot);
    }

    static void __cdecl QuickSaveButtonOnClickLoad()
    {
        LoadInjectedSlot(g_QuickSaveLoadSlot);
    }

    // POD-only helper so __try/__except is valid (no C++ objects with destructors).
    // Returns true if the button is still alive and was updated, false if it was
    // dangling (exception caught) so the caller should create a fresh button.
    static bool TryUpdateInjectedLoadButton(InjectedLoadSlot& slot, const char* label)
    {
        __try
        {
            if (g_BzrFn_SetButtonLabel)
                g_BzrFn_SetButtonLabel(slot.button, label);
            if (g_BzrFn_SetOnClick) g_BzrFn_SetOnClick(slot.button, reinterpret_cast<void*>(slot.onClick));
            if (g_BzrFn_SetOnHover) g_BzrFn_SetOnHover(slot.button, reinterpret_cast<void*>(AutoSaveButtonOnHoverNoop));
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            slot.button = nullptr;
            return false;
        }
        return true;
    }

    static void InjectedLoadButtonCreate(InjectedLoadSlot& slot, void* parent, void* screen)
    {
        if (!SlotFileExists(slot))
            return;

        const std::string label = GetSlotButtonLabel(slot);
        // Pointer equality alone cannot prove the cached button survived a
        // screen rebuild at a recycled address; require it to still be linked
        // into the live parent's child vector before updating it in place.
        if (slot.button && slot.parent == parent && slot.screen == screen &&
            IsWidgetLiveChildOfParent(parent, slot.button))
        {
            if (TryUpdateInjectedLoadButton(slot, label.c_str()))
                return;
        }

        slot.parent = parent;
        slot.screen = screen;
        slot.button = nullptr;

        void* buttonMem = ::operator new(0x1EC, std::nothrow);
        if (!buttonMem)
            return;

        std::memset(buttonMem, 0, 0x1EC);
        slot.button = g_BzrFn_ButtonCtor(
            buttonMem,
            label.c_str(),
            kInjectedLoadButtonX,
            slot.y,
            kInjectedLoadButtonW,
            kInjectedLoadButtonH,
            kInjectedLoadButtonFlags,
            parent,
            0,
            0);

        if (!slot.button)
            return;

        if (g_BzrFn_SetTextureOff) g_BzrFn_SetTextureOff(slot.button, "mpcron.png");
        if (g_BzrFn_SetTextureOver) g_BzrFn_SetTextureOver(slot.button, "mpcrclk.png");
        if (g_BzrFn_SetTextureOn) g_BzrFn_SetTextureOn(slot.button, "mpcrclk.png");
        if (g_BzrFn_SetButtonLabel) g_BzrFn_SetButtonLabel(slot.button, label.c_str());
        // 0x007CC660 is a label-style tooltip writer that stores text inline at
        // +0x144. Button objects use +0x150/+0x154 for hover/click callbacks,
        // so using it here corrupts the callback slot and crashes the load menu.
        if (g_BzrFn_SetOnClick) g_BzrFn_SetOnClick(slot.button, reinterpret_cast<void*>(slot.onClick));
        // Mirror the stock load-slot buttons by also populating the +0x150 slot.
        // Without this the load screen invokes a null callback on open and
        // crashes (call through NULL / EIP=0). See AutoSaveButtonOnHoverNoop.
        if (g_BzrFn_SetOnHover) g_BzrFn_SetOnHover(slot.button, reinterpret_cast<void*>(AutoSaveButtonOnHoverNoop));
        g_BzrFn_AddChild(parent, slot.button, 0);
    }

    static void AutoSaveLoadButtonCreate(void* parent, void* screen)
    {
        // The engine calls a child button's hover/click slots; a button built
        // without them crashes the dialog, so both setters are required.
        if (!parent || !screen || !g_BzrFn_ButtonCtor || !g_BzrFn_AddChild ||
            !g_BzrFn_SetOnClick || !g_BzrFn_SetOnHover)
            return;

        InjectedLoadButtonCreate(g_AutoSaveLoadSlot, parent, screen);
        InjectedLoadButtonCreate(g_QuickSaveLoadSlot, parent, screen);
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
