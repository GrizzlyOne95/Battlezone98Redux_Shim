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
    // cUI_TextEntry ctor 0x007CF410. The two leading flags are byte fields:
    // arg2 lands at +0x950 (mAllowEnter, 1 at every shipped call site) and arg1
    // at +0x960 (0 or 1 depending on screen). displayLength is 0x24 or 0x2A in
    // stock code and controls the rendered tail, not the total input length;
    // +0x964 is the optional total input limit. Derives from cUI_Text, whose
    // ctor it forwards args 4..10 to.
    using FnUiTextEntryCtor = void* (__thiscall*)(void* self,
                                                  int flagA, int allowEnter, int displayLength,
                                                  const char* name,
                                                  float x, float y, float w, float h,
                                                  uint32_t flags, void* parent);
    // cUI_Selectlist ctor 0x007C9DE0. onPageUp/onPageDown are installed as the
    // click callbacks of the two arrow buttons the ctor builds for itself at
    // +0x178/+0x17C -- they are NOT selection handlers; that is a separate
    // setter (0x007CB3E0). The ctor pre-creates as many row labels as fit the
    // requested height, so it is safe to construct with no items.
    using FnUiSelectlistCtor = void* (__thiscall*)(void* self,
                                                   const char* name,
                                                   float x, float y, float w, float h,
                                                   void* onPageUp, void* onPageDown,
                                                   uint32_t flags, void* parent,
                                                   uint32_t rowColour, float rowScale);
    // 0x007CABF0. Overwrites entry `index`, or appends when index == size(),
    // truncating the label to the list width and updating arrow visibility.
    using FnUiSelectlistSetItem = void(__thiscall*)(void* self,
                                                    const char* label, int index, int value);

    // Object sizes, taken from the `operator new` at every shipped call site of
    // each ctor rather than from the reference PDB -- that PDB is a different
    // build and reports cUI_TextEntry as 2400, eight bytes short of the 0x968
    // this build allocates (its ctor writes a field at +0x964).
    inline constexpr size_t kUiButtonSize = 0x1EC;
    inline constexpr size_t kUiTextSize = 0x930;
    inline constexpr size_t kUiViewSize = 0x144;
    inline constexpr size_t kUiTextEntrySize = 0x968;
    inline constexpr size_t kUiSelectlistSize = 0x180;

    // Field offsets confirmed against this build's ctor code, not the PDB.
    // cUI_View's input-active byte, set by its ctor and by SetActive
    // (0x007D3310, which also drives the Ogre element's visibility). While it
    // is set, cUI_View::MousePressed/MouseReleased report any click inside the
    // view's own rect as handled -- without a callback -- so a decorative
    // overlay silently blocks every widget the parent visits after it.
    inline constexpr size_t kUiViewInputActiveOffset = 0xE9;
    inline constexpr size_t kUiTextEntryTextOffset = 0x930;       // std::string
    inline constexpr size_t kUiTextEntryMaxLengthOffset = 0x948;  // rendered tail length
    inline constexpr size_t kUiTextEntryEnterCbOffset = 0x94C;
    inline constexpr size_t kUiTextEntryAllowEnterOffset = 0x950; // byte
    inline constexpr size_t kUiTextEntryInputLimitOffset = 0x964; // -1 means unlimited
    inline constexpr size_t kUiSelectlistSelectedOffset = 0x14C;  // -1 when none
    inline constexpr size_t kUiSelectlistScrollOffset = 0x150;
    inline constexpr size_t kUiSelectlistPageUpOffset = 0x178;
    inline constexpr size_t kUiSelectlistPageDownOffset = 0x17C;

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
    extern FnUiTextEntryCtor g_BzrFn_TextEntryCtor;
    extern FnUiSelectlistCtor g_BzrFn_SelectlistCtor;
    extern FnUiSelectlistSetItem g_BzrFn_SelectlistSetItem;
    extern FnUiSetCb g_BzrFn_TextEntrySetEnterCb;
    extern FnUiSetCb g_BzrFn_SelectlistSetOnSelect;
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
        BzrNetRoute,        // the engine re-reads the relay flag per connection attempt
        RenderProfile,      // RenderProfiles::ReloadRenderProfileConfig re-reads + reapplies live
        RestartRequired,    // no live path; takes effect next launch
    };
    void ApplyShimSettingLive(ShimSettingApplyGroup group);

    // Persist one openshim.ini key through the settings page's lossless writer
    // (comments, ordering and the .openshim.bak backup are preserved).
    bool WriteShimUserConfigValue(const char* section, const char* key, const char* value);

    // --- options-UI entry points (implemented in bzr_options_ui.cpp) ---
    void EnsureInputBindingPopulateHookScaffold();
    void EnsureOptionsParentCtorHookScaffold();
    void ResetOptionsUiResolvedState();
    void LogShimSettingsUiStatus();
}
