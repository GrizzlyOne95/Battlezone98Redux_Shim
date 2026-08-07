#pragma once
// Internal surface between bzr_hooks.cpp (engine bindings, detour machinery,
// openshim.ini helpers, live feature re-apply) and bzr_options_ui.cpp (the
// injected input-binding + OpenShim settings pages). Not a public API.

#include <array>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <string>

namespace BZROpenShim
{
    // --- engine UI/ input-map binding types (RE'd Redux ABI) ---
    using FnUiButtonCtor = void* (__thiscall*)(void* self,
                                               const char* label,
                                               float x, float y, float w, float h,
                                               uint32_t flags, void* parent, int a, int b);
    // The label ctor only cleans 8 stack arguments in v2.2.301.
    using FnUiLabelCtor = void* (__thiscall*)(void* self,
                                              const char* label,
                                              float x, float y, float w, float h,
                                              uint32_t flags, void* parent, int a);
    using FnUiOverlayCtor = void* (__thiscall*)(void* self,
                                                const char* label,
                                                float x, float y, float w, float h,
                                                uint32_t flags, void* parent, int a);
    using FnUiSetStr = void(__thiscall*)(void* self, const char* str);
    using FnUiSetFloat = void(__thiscall*)(void* self, float value);
    using FnUiSetInt = void(__thiscall*)(void* self, void* param);
    using FnUiSetCb  = void(__thiscall*)(void* self, void* cb);
    using FnUiSetActive = void(__thiscall*)(void* self, uint8_t value);
    using FnUiAddChild = void(__thiscall*)(void* parent, void* child, int flags);
    using FnUiDialogAction = void(__thiscall*)(void* thisPtr, int value);
    using FnOptionsInputCtor = void* (__thiscall*)(void* thisPtr);
    using FnOptionsScreenDtor = void(__thiscall*)(void* thisPtr);
    using FnOptionsInputKeyReleased = bool(__thiscall*)(void* thisPtr, uint32_t key, uint32_t keyCode);
    using FnKeyConfigSetKey = int(__thiscall*)(void* thisPtr, const char* command, const char* keyName);
    using FnWriteInputMapKey = void(__cdecl*)(const char* command, const char* keyName);
    using FnMapKeyNameFromCode = void(__cdecl*)(uint32_t keyCode, char* outBuffer);
    using FnReloadGameKeyMap = void(__cdecl*)();

    // Resolved by ResolveUiHooks in bzr_hooks.cpp; null until then.
    extern FnUiButtonCtor g_BzrFn_ButtonCtor;
    extern FnUiLabelCtor g_BzrFn_LabelCtor;
    extern FnUiOverlayCtor g_BzrFn_OverlayCtor;
    extern FnUiSetStr g_BzrFn_SetTextureOff;
    extern FnUiSetStr g_BzrFn_SetTextureOver;
    extern FnUiSetStr g_BzrFn_SetTextureOn;
    extern FnUiSetStr g_BzrFn_SetButtonLabel;
    extern FnUiSetFloat g_BzrFn_SetButtonTextScale;
    extern FnUiSetStr g_BzrFn_SetTooltip;
    extern FnUiSetInt g_BzrFn_LabelState;
    extern FnUiSetCb g_BzrFn_SetOnClick;
    extern FnUiSetCb g_BzrFn_SetOnHover;
    extern FnUiSetActive g_BzrFn_UiSetActive;
    extern FnUiAddChild g_BzrFn_AddChild;
    extern FnKeyConfigSetKey g_BzrFn_KeyConfigSetKey;
    extern FnMapKeyNameFromCode g_BzrFn_MapKeyNameFromCode;
    extern FnReloadGameKeyMap g_BzrFn_ReloadGameKeyMap;

    // --- inline-detour machinery (implemented in bzr_hooks.cpp) ---
    inline constexpr size_t kInlineDetourMaxPatchLen = 16;

    struct InlineDetour32
    {
        uintptr_t target = 0;
        void* hook = nullptr;
        void* trampoline = nullptr;
        size_t patchLen = 0;
        std::array<uint8_t, kInlineDetourMaxPatchLen> original = {};
    };

    bool InstallInlineDetour32(InlineDetour32& detour,
                               uintptr_t target,
                               void* hook,
                               size_t patchLen,
                               const uint8_t* expectedBytes,
                               size_t expectedLen);
    bool ExpectedBytesMatchAt(uintptr_t address,
                              const uint8_t* expectedBytes,
                              size_t expectedLen);

    // --- openshim.ini / environment helpers (implemented in bzr_hooks.cpp) ---
    inline constexpr char kUserConfigFileName[] = "openshim.ini";
    bool EnvFlagEnabled(const char* name);
    std::filesystem::path GetMainModuleDirectory();
    std::filesystem::path GetUserConfigPath();
    bool TryGetUserConfigString(const char* section, const char* key, std::string& out);
    bool TryGetUserConfigBool(const char* section, const char* key, bool& out);
    std::string TrimAsciiCopy(const std::string& value);

    // How a settings row re-applies its feature live after the ini write.
    enum class ShimSettingApplyGroup
    {
        GlobalImprovement,  // InitializeGlobalImprovementConfig re-reads the ini (no latch)
        UnderAttackAlert,
        TargetReticle,
        JetFlames,
        UnitVo,
        GlobalTurbo,
        Headlights,         // InitializeHeadlightConfig re-reads the ini (no latch)
        AutoSave,           // ReloadAutoSaveConfig re-reads the ini and applies immediately
        RestartRequired,    // no live path; takes effect next launch
    };
    void ApplyShimSettingLive(ShimSettingApplyGroup group);

    // --- options-UI entry points (implemented in bzr_options_ui.cpp) ---
    void EnsureInputBindingPopulateHookScaffold();
    void EnsureOptionsParentCtorHookScaffold();
    void ResetOptionsUiResolvedState();
    void LogShimSettingsUiStatus();
}
