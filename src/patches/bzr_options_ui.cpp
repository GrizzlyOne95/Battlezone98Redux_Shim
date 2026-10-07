// Input-binding UI replacement + OpenShim settings screen (options-shell
// sub-pages injected over cUI_OptionsInput / cUI_OptionsParent). Split out of
// bzr_hooks.cpp; the shared engine-binding surface (resolved fn pointers,
// inline-detour machinery, openshim.ini helpers, live feature re-apply) is
// declared in bzr_options_ui.h and implemented by bzr_hooks.cpp and the
// helper files split out of it.
#include "bzr_options_ui.h"
#include "shell_screens.h"
#include "hook_engine.h"
#include "bool_token.h"

#include "autosave.h"
#include "bzr_hooks.h"
#include "native_ui.h"
#include "openshim_assets.h"
#include "openshim_ini.h"
#include "openshim_updater.h"
#include "patcher.h"
#include "shim_log.h"
#include "ui_decor.h"
#include "BZROpenShim.h"

#include <Windows.h>
#include <algorithm>
#include <array>
#include <cctype>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace BZROpenShim
{
    void* __fastcall OptionsInputPopulateUiHook(void* thisPtr, void* /*edx*/);
    bool __fastcall OptionsInputKeyReleasedHook(void* thisPtr, void* /*edx*/, uint32_t key, uint32_t keyCode);
    void* __fastcall OptionsParentCtorHook(void* thisPtr, void* /*edx*/);
    void __fastcall MainScreenCtorHook(void* thisPtr, void* /*edx*/, char phase);
    void __fastcall OptionsInputDtorHook(void* thisPtr, void* /*edx*/);
    void __fastcall OptionsParentDtorHook(void* thisPtr, void* /*edx*/);

    namespace Hooks
    {
        bool VtableTypeNameMatches(uintptr_t vtableAddress, const char* expectedName);
    }

    namespace
    {
        // UI texture availability probe for DLL-only bootstrap.
        // The Settings page that reports missing assets itself uses OpenShim-owned
        // CustomWidgets tiles (uiline.png, uiplate.png, uibtn.png, uibtnhv.png).
        // Stock BZR + winmm.dll + configs + NO assets must still produce a readable
        // Settings page. This probe checks the filesystem for the expected tile
        // at its deployed locations and, if absent, skips the custom texture so
        // the page falls back to stock widget appearance / text-only.
        static bool IsUiTextureFileAvailable(const char* textureName)
        {
            if (!textureName || !*textureName)
                return false;
            char modPath[MAX_PATH] = {};
            DWORD len = GetModuleFileNameA(nullptr, modPath, MAX_PATH);
            if (len == 0 || len >= MAX_PATH)
                return false;
            std::filesystem::path gameDir = std::filesystem::path(modPath).parent_path();
            std::filesystem::path candidates[] = {
                gameDir / "BZ_ASSETS_CORE" / "common" / "ui" / "CustomWidgets" / textureName,
                gameDir / "BZ_ASSETS" / "common" / "ui" / textureName,
                gameDir / "resources" / "ui" / "custom_widgets" / textureName,
                gameDir / textureName,
            };
            std::error_code ec;
            for (auto &cand : candidates)
            {
                if (std::filesystem::exists(cand, ec) && !ec)
                    return true;
            }
            // Also consider blackui.png and other stock textures that may live in
            // the game's data archives, not on loose filesystem. If we cannot
            // prove it exists on disk, we still try to set it once and rely on
            // Ogre's missing-resource handling (which is non-crashing). This
            // keeps stock installs working even when loose files are packed in
            // archives. For CustomWidgets tiles, the loose file *is* the
            // deployment, so missing loose file means missing tile.
            // Treat CustomWidgets tiles as unavailable when loose file missing;
            // other textures (blackui, mpcron) are assumed available via stock
            // archives and we return true to attempt the set.
            std::string lower = textureName;
            std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c){ return (char)std::tolower(c); });
            if (lower == "uiline.png" || lower == "uiplate.png" || lower == "uibtn.png" || lower == "uibtnhv.png")
                return false;
            return true;
        }

        // The shipped GOG PDB public-symbol addresses for cUI_OptionsInput methods
        // are not reliable function-entry hooks against the current Redux binary.
        // The stock input screen constructor was recovered from string xrefs instead.
        uint32_t g_OptionsInputCtorAddr = 0;
        uint32_t g_OptionsInputKeyReleasedAddr = 0;
        uint32_t g_OptionsInputScreenFactoryCallerAddr = 0;
        uint32_t g_OptionsInputBackClickAddr = 0;
        uint32_t g_OptionsInputDefaultsClickAddr = 0;
        // Stock "Joystick" button click thunk (cUI_OptionsInput ctor wires it
        // via SetOnClick 0x007C23E0; see FUN_007b25b0 decomp). The Default and
        // Joystick buttons are ctor locals, not screen members, so they are
        // located at runtime by matching this thunk in the +0x154 click slot.
        uint32_t g_OptionsInputJoystickClickAddr = 0;
        constexpr size_t kUiViewChildBeginOffset = 0x12C;
        constexpr size_t kUiViewChildEndOffset = 0x130;
        constexpr size_t kUiButtonOnHoverOffset = 0x150;
        constexpr size_t kUiButtonOnClickOffset = 0x154;
        // cUI_View debug name: char[0xC8] copied by the view ctor (0x007D1CC0)
        // from its first argument. cUI_Button installs vtable 0x008A0470 over
        // the cUI_View vtable 0x008A0B94, which is how a node is identified as
        // a button when walking a screen's child tree.
        constexpr size_t kUiViewNameOffset = 0x20;
        uint32_t g_UiButtonVtableAddr = 0;
        // cUI_OptionsParent constructor on the live GOG/Steam 2.2.301 exe,
        // recovered from the Redux decompile corpus (FUN_007b61a0: builds the
        // esc_center.png overlay plus the Play/Graphic/Audio/Input buttons) and
        // byte-verified against the installed exe (SEH prologue
        // 55 8B EC 6A FF 68 60 13 86 00). Singleton stored at 0x009455C4.
        uint32_t g_OptionsParentCtorAddr = 0;
        // cUI_MainScreen menu setup, void __thiscall(this, char).
        //
        // NOT the constructor. Hooking the constructor (0x0078E670) was tried
        // first and is too early: at its return the screen is still the splash
        // phase -- measured live as name "Top Screen", +0x158 null, single
        // child "Splash_Overlay1" -- because the title menu is built by a later
        // call to this routine. This is the function that creates
        // SinglePlayer_MainScreen and friends with *(this + 0x158) as parent,
        // so at its return the overlay exists.
        //
        // It is called for more than one phase, and the char argument selects
        // between them. Rather than depend on the meaning of that argument, the
        // resolver simply fails on any pass where MainScreen_Overlay is not
        // present and succeeds on the one where it is.
        //
        // Prologue read from the shipped GOG 2.2.301 image:
        //   55 8B EC 6A FF 68 12 EC 85 00
        uint32_t g_MainScreenCtorAddr = 0;
        constexpr size_t kMainScreenCtorDetourLen = 10;
        constexpr size_t kOptionsParentCtorDetourLen = 10;
        // Stock cUI_OptionsParent "Input" click thunk: loads the parent
        // singleton and asks the options shell (this+0x138) to switch to screen
        // id 0x15 (the input options page) via the switch fn at 0x007C7930.
        // The OpenShim settings button reuses this exact navigation path.
        uint32_t g_OptionsParentInputClickThunkAddr = 0;
        // cUI_OptionsInput singleton (DAT_009455B8); non-null while the stock
        // input screen object is alive inside the current options shell.
        uint32_t g_OptionsInputSingletonAddr = 0;
        // Inner (non-deleting) destructors of the two hooked screens, recovered
        // from the live GOG exe: the ctor at 0x007B25B0 installs vtable
        // 0x0089F930 whose slot 0 (scalar deleting dtor 0x007B4840) calls
        // 0x007B4870; the parent ctor 0x007B61A0 installs vtable 0x0089FC34 ->
        // slot 0 0x007B6820 -> 0x007B6850. Hooking the inner dtor catches every
        // destruction path, which is what invalidates our cached child views.
        uint32_t g_OptionsInputDtorAddr = 0;
        uint32_t g_OptionsParentDtorAddr = 0;
        constexpr size_t kOptionsScreenDtorDetourLen = 10;
        constexpr size_t kOptionsInputCtorDetourLen = 10;
        constexpr size_t kOptionsInputKeyReleasedDetourLen = 9;
        constexpr size_t kOptionsInputKeyConfigOffset = 0x188;

        uint32_t g_ReadMappingTableAddr = 0;

        enum class InputBindingMapFamily
        {
            Input,
            GameKey,
        };

        // One raw "+/- <source> <token>" line inside a command block, addressed by
        // its index in the owning document so edits can be made in place.
        struct InputBindingLineRef
        {
            size_t lineIndex = SIZE_MAX;
            bool positive = false;
            std::string source;
            std::string token;
        };

        struct InputBindingCommandBlock
        {
            std::string command;
            std::string section;
            std::string comment;
            size_t headerLineIndex = SIZE_MAX;
            size_t closeLineIndex = SIZE_MAX;
            std::vector<InputBindingLineRef> bindingLines;
            std::vector<std::string> positiveKeyboardTokens;
            std::vector<std::string> positiveNonKeyboardTokens;
            bool hasPositiveNonKeyboard = false;
        };

        // Lossless copy of a map file: every line verbatim, so structure-preserving
        // rewrites only touch the specific lines an edit targets.
        struct InputBindingDocument
        {
            std::vector<std::string> lines;
            bool loaded = false;
        };

        struct InputBindingInventoryStats
        {
            size_t uniqueCommandBlocks = 0;
            size_t simpleKeyboardBlocks = 0;
            size_t keyboardChordBlocks = 0;
            size_t mixedBlocks = 0;
            size_t uniqueGameKeyActions = 0;
            size_t gameKeyChords = 0;
            size_t firstPassInputRows = 0;
            size_t firstPassGameKeyRows = 0;
        };

        struct GameKeyBindingAction
        {
            std::string action;
            std::vector<std::string> chords;
            std::vector<size_t> chordLineIndices;
        };

        struct InputBindingRowSeed
        {
            const char* command = nullptr;
            const char* labelKey = nullptr;
            const char* displayText = nullptr;
        };

        struct InputBindingUiRow
        {
            InputBindingMapFamily family = InputBindingMapFamily::Input;
            std::string command;
            std::string sectionName;
            std::string displayLabelKey;
            std::string displayText;
            std::string currentBindingText;
            bool reserved = false;
            bool foundInMap = false;
            size_t matchingBlockCount = 0;
        };

        // Toolbar captions stop this far short of their button so the caption
        // never touches the button's own border art.
        constexpr float kUiToolbarCaptionPadding = 16.0f;

        constexpr size_t kInputBindingUiColumnCount = 2;
        constexpr size_t kInputBindingUiRowsPerColumn = 10;
        constexpr size_t kInputBindingUiVisibleRowCount =
            kInputBindingUiColumnCount * kInputBindingUiRowsPerColumn;

        // Toolbar: Back, Reset Controls, Controls, RTS Actions | Prev, Next,
        // Refresh. Widths are the caption's own width plus padding; the four
        // leading entries pack from the left inset and the three paging entries
        // pack flush to the right inset (LayoutUiToolbarRow).
        constexpr size_t kInputBindingUiToolbarSlotCount = 7;
        constexpr size_t kInputBindingUiToolbarRightGroup = 4;
        constexpr float kInputBindingUiToolbarWidths[kInputBindingUiToolbarSlotCount] =
        {
            120.0f, 190.0f, 150.0f, 160.0f, 90.0f, 90.0f, 120.0f
        };

        // Painted mode: with osh_keys_center.png deployed, the editor swaps the
        // Input screen's centre panel for it and places its widgets over the
        // panel's painted slots instead of building flat masks and plates. The
        // geometry is the layout contract with KEYS_LAYOUT in
        // resources/ui/custom_widgets/mkscreens.py.
        constexpr const char* kInputBindingPanelTexture = "osh_keys_center.png";
        static bool g_InputBindingUiPainted = false;

        static UiOptionsPageLayout BuildKeysPanelLayout()
        {
            UiOptionsPageLayout layout = {};
            constexpr float kColumnX[2] = { 228.0f, 736.0f };
            constexpr float kColumnW = 476.0f;
            constexpr float kColumnY = 316.0f;
            constexpr float kRowTop = 10.0f;
            constexpr float kPad = 16.0f;
            constexpr float kValueW = 196.0f;
            constexpr float kLabelInset = 28.0f;
            constexpr float kInfoX = 228.0f, kInfoY = 702.0f, kInfoW = 984.0f, kInfoH = 116.0f;

            layout.title = { 470.0f, 132.0f, 500.0f, 56.0f };
            const float textX = kInfoX + 24.0f;
            const float textW = kInfoW - 48.0f;
            layout.headerTextWidth = textW;
            layout.statusLine1 = { textX, kInfoY + 14.0f, textW, 30.0f };
            layout.statusLine2 = { textX, kInfoY + 46.0f, textW, 30.0f };
            layout.contextLine1 = { textX, kInfoY + kInfoH - 42.0f, textW, 30.0f };

            layout.toolbarY = 264.0f;
            layout.toolbarHeight = 40.0f;
            layout.toolbarLeftX = 228.0f;
            layout.toolbarRightX = 1212.0f;
            layout.toolbarGap = 10.0f;

            layout.rowLeftX = kColumnX[0] + kLabelInset;
            layout.rowRightX = kColumnX[1] + kLabelInset;
            layout.rowStartY = kColumnY + kRowTop;
            layout.rowPitch = 36.0f;
            layout.rowHeight = 30.0f;
            layout.rowLabelYInset = 2.0f;
            layout.rowValueOffsetX = kColumnW - kPad - kValueW - kLabelInset;
            layout.rowValueWidth = kValueW;
            layout.rowValueTextWidth = kValueW - 20.0f;
            layout.rowLabelWidth = layout.rowValueOffsetX - 22.0f;
            layout.rowLabelTextWidth = layout.rowLabelWidth - 30.0f;
            return layout;
        }

        static UiOptionsPageLayout GetInputBindingUiLayout()
        {
            return g_InputBindingUiPainted ? BuildKeysPanelLayout()
                                           : BuildUiOptionsPageLayout(kInputBindingUiRowsPerColumn);
        }

        // Button skins for painted mode: hover and press only, so the button
        // rests on its painted slot like the stock option buttons.
        struct InputBindingUiSkin
        {
            const char* over;
            const char* on;
        };
        static const InputBindingUiSkin* g_InputBindingUiSkin = nullptr;

        static InlineDetour32 g_OptionsInputPopulateUiDetour = {};
        static InlineDetour32 g_OptionsInputKeyReleasedDetour = {};

        static FnOptionsInputCtor g_BzrFn_OptionsInputCtor = nullptr;
        static FnOptionsInputKeyReleased g_BzrFn_OptionsInputKeyReleased = nullptr;

        static bool g_InputBindingUiScaffoldInitialized = false;
        static bool g_InputBindingUiScaffoldLogged = false;
        static bool g_InputBindingUiPopulateHookInstalled = false;
        static bool g_InputBindingUiKeyReleasedHookInstalled = false;
        static bool g_InputBindingUiPopulateHookMismatchLogged = false;
        static std::filesystem::path g_InputBindingInstallDirectory = {};
        static InputBindingInventoryStats g_InputBindingInventory = {};
        static InputBindingDocument g_InputMapDocument = {};
        static InputBindingDocument g_GameKeyMapDocument = {};
        static std::vector<InputBindingCommandBlock> g_InputBindingCommandBlocks = {};
        static std::vector<GameKeyBindingAction> g_GameKeyBindingActions = {};
        static bool g_InputMapLiveReloadChecked = false;
        static bool g_InputMapLiveReloadAvailable = false;
        static std::vector<InputBindingUiRow> g_InputBindingUiRows = {};

        // Tracks one engine screen this code decorates. The engine recycles
        // screen heap addresses (see the 2026-07-16 dump 2692 post-mortem), so
        // a bare pointer comparison cannot prove identity across destroy/
        // reconstruct cycles. Two roles are tracked separately: `constructed`
        // is the screen the stock constructor last produced (owned until the
        // dtor hook fires) and `decorated` is the screen currently carrying
        // our injected child widgets. Every mutation bumps the generation so
        // destroy/reconstruct cycles stay visible in the log, and the fast
        // restyle path only trusts a screen both roles agree on (IsLive).
        struct ScreenBinding
        {
            void* constructed = nullptr;
            void* decorated = nullptr;
            uint32_t generation = 0;

            void BindConstructed(void* screen)
            {
                constructed = screen;
                decorated = screen;
                ++generation;
            }
            void BindDecorated(void* screen)
            {
                decorated = screen;
                ++generation;
            }
            void Unbind()
            {
                constructed = nullptr;
                decorated = nullptr;
                ++generation;
            }
            bool Owns(const void* screen) const
            {
                return screen && (screen == constructed || screen == decorated);
            }
            bool IsLive(const void* screen) const
            {
                return screen && screen == constructed && screen == decorated;
            }
        };

        static ScreenBinding g_InputScreenBinding = {};
        static void* g_InputBindingUiMiddleOverlay = nullptr;
        static void* g_InputBindingUiTopMask = nullptr;
        static void* g_InputBindingUiContentMask = nullptr;
        static std::array<void*, kUiDecorMaxOptionsPagePieces> g_InputBindingUiDecor = {};
        static std::array<void*, kInputBindingUiVisibleRowCount> g_InputBindingUiRowBackdrops = {};
        static void* g_InputBindingUiHeaderLabel = nullptr;
        static void* g_InputBindingUiStatusLabel = nullptr;
        static void* g_InputBindingUiStatusDetailLabel = nullptr;
        static void* g_InputBindingUiPageLabel = nullptr;
        static void* g_InputBindingUiBackButton = nullptr;
        static void* g_InputBindingUiDefaultsButton = nullptr;
        static void* g_InputBindingUiInputFamilyButton = nullptr;
        static void* g_InputBindingUiGameKeyFamilyButton = nullptr;
        static void* g_InputBindingUiPrevPageButton = nullptr;
        static void* g_InputBindingUiNextPageButton = nullptr;
        static void* g_InputBindingUiRefreshButton = nullptr;
        static std::array<void*, kInputBindingUiVisibleRowCount> g_InputBindingUiRowLabels = {};
        static std::array<void*, kInputBindingUiVisibleRowCount> g_InputBindingUiRowButtons = {};
        static std::array<int, kInputBindingUiVisibleRowCount> g_InputBindingUiVisibleRowIndices = {};
        static InputBindingMapFamily g_InputBindingUiActiveFamily = InputBindingMapFamily::Input;
        static size_t g_InputBindingUiPageStart = 0;
        static InputBindingMapFamily g_InputBindingUiPendingFamily = InputBindingMapFamily::Input;
        static std::string g_InputBindingUiPendingCommand = {};
        static std::string g_InputBindingUiPendingDisplayText = {};
        static std::string g_InputBindingUiStatusText = {};
        static void InitializeInputBindingUiScaffold();
        static bool TryLiveReloadInputMapTables();
        static void OnInputBindingBackClicked();
        static void OnInputBindingDefaultsClicked();
        static void OnInputBindingRowButtonClicked(size_t visibleSlot);
        static void OnInputBindingFamilyButtonClicked(InputBindingMapFamily family);
        static void OnInputBindingPageStepClicked(int direction);
        static void OnInputBindingRefreshClicked();

#define BZR_INPUT_BINDING_ROW_CLICK_DECL(index) \
        static void __cdecl InputBindingRowClick##index() { OnInputBindingRowButtonClicked(index); }

        BZR_INPUT_BINDING_ROW_CLICK_DECL(0)
        BZR_INPUT_BINDING_ROW_CLICK_DECL(1)
        BZR_INPUT_BINDING_ROW_CLICK_DECL(2)
        BZR_INPUT_BINDING_ROW_CLICK_DECL(3)
        BZR_INPUT_BINDING_ROW_CLICK_DECL(4)
        BZR_INPUT_BINDING_ROW_CLICK_DECL(5)
        BZR_INPUT_BINDING_ROW_CLICK_DECL(6)
        BZR_INPUT_BINDING_ROW_CLICK_DECL(7)
        BZR_INPUT_BINDING_ROW_CLICK_DECL(8)
        BZR_INPUT_BINDING_ROW_CLICK_DECL(9)
        BZR_INPUT_BINDING_ROW_CLICK_DECL(10)
        BZR_INPUT_BINDING_ROW_CLICK_DECL(11)
        BZR_INPUT_BINDING_ROW_CLICK_DECL(12)
        BZR_INPUT_BINDING_ROW_CLICK_DECL(13)
        BZR_INPUT_BINDING_ROW_CLICK_DECL(14)
        BZR_INPUT_BINDING_ROW_CLICK_DECL(15)
        BZR_INPUT_BINDING_ROW_CLICK_DECL(16)
        BZR_INPUT_BINDING_ROW_CLICK_DECL(17)
        BZR_INPUT_BINDING_ROW_CLICK_DECL(18)
        BZR_INPUT_BINDING_ROW_CLICK_DECL(19)

#undef BZR_INPUT_BINDING_ROW_CLICK_DECL

        static void* const kInputBindingRowClickCallbacks[kInputBindingUiVisibleRowCount] =
        {
            reinterpret_cast<void*>(InputBindingRowClick0),
            reinterpret_cast<void*>(InputBindingRowClick1),
            reinterpret_cast<void*>(InputBindingRowClick2),
            reinterpret_cast<void*>(InputBindingRowClick3),
            reinterpret_cast<void*>(InputBindingRowClick4),
            reinterpret_cast<void*>(InputBindingRowClick5),
            reinterpret_cast<void*>(InputBindingRowClick6),
            reinterpret_cast<void*>(InputBindingRowClick7),
            reinterpret_cast<void*>(InputBindingRowClick8),
            reinterpret_cast<void*>(InputBindingRowClick9),
            reinterpret_cast<void*>(InputBindingRowClick10),
            reinterpret_cast<void*>(InputBindingRowClick11),
            reinterpret_cast<void*>(InputBindingRowClick12),
            reinterpret_cast<void*>(InputBindingRowClick13),
            reinterpret_cast<void*>(InputBindingRowClick14),
            reinterpret_cast<void*>(InputBindingRowClick15),
            reinterpret_cast<void*>(InputBindingRowClick16),
            reinterpret_cast<void*>(InputBindingRowClick17),
            reinterpret_cast<void*>(InputBindingRowClick18),
            reinterpret_cast<void*>(InputBindingRowClick19),
        };

        static void __cdecl InputBindingFamilyInputClick()
        {
            OnInputBindingFamilyButtonClicked(InputBindingMapFamily::Input);
        }

        static void __cdecl InputBindingBackClick()
        {
            OnInputBindingBackClicked();
        }

        static void __cdecl InputBindingDefaultsClick()
        {
            OnInputBindingDefaultsClicked();
        }

        static void __cdecl InputBindingFamilyGameKeyClick()
        {
            OnInputBindingFamilyButtonClicked(InputBindingMapFamily::GameKey);
        }

        static void __cdecl InputBindingPrevPageClick()
        {
            OnInputBindingPageStepClicked(-1);
        }

        static void __cdecl InputBindingNextPageClick()
        {
            OnInputBindingPageStepClicked(1);
        }

        static void __cdecl InputBindingRefreshClick()
        {
            OnInputBindingRefreshClicked();
        }

        // --- OpenShim Options entry point ------------------------------------
        // An "OpenShim Options" button on the stock Options screen opens
        // OpenShim's own settings screens (see OPENSHIM OPTIONS SCREENS).
        static InlineDetour32 g_OptionsParentCtorDetour = {};
        static FnOptionsInputCtor g_BzrFn_OptionsParentCtor = nullptr;
        static bool g_OptionsParentHookInstalled = false;
        static bool g_OptionsParentHookMismatchLogged = false;
        // Destructor hooks that clear the cached screen/child pointers the
        // moment the engine tears a hooked screen down. Without them a click
        // arriving after a destroy-then-deferred-reconstruct navigation walks
        // freed child views (crash dump battlezone98redux.exe.2692:
        // SetInputBindingUiControlsVisible on a stale row backdrop).
        static InlineDetour32 g_OptionsInputDtorDetour = {};
        static FnOptionsScreenDtor g_BzrFn_OptionsInputDtorOriginal = nullptr;
        static bool g_OptionsInputDtorHookInstalled = false;
        static bool g_OptionsInputDtorHookAttempted = false;
        static InlineDetour32 g_OptionsParentDtorDetour = {};
        static FnOptionsScreenDtor g_BzrFn_OptionsParentDtorOriginal = nullptr;
        static bool g_OptionsParentDtorHookInstalled = false;
        static bool g_OptionsParentDtorHookAttempted = false;
        static ScreenBinding g_ParentScreenBinding = {};
        static void* g_ShimSettingsMenuButton = nullptr;
        static ULONGLONG g_ShimSettingsNavigationTick = 0;
        constexpr ULONGLONG kShimSettingsNavigationDebounceMs = 350;
        static UINT_PTR g_ShimSettingsUiUpdateTimer = 0;
        static uint64_t g_ShimSettingsUiUpdateGeneration = 0;
        static void OnShimSettingsMenuClicked();
        struct ShimSettingDescriptor;
        static void OnShimSettingsActionRowClicked(size_t settingIndex,
                                                   const ShimSettingDescriptor& setting);
        static bool EnsureShimSettingsUpdateTimer();
        static void EnsureInputBindingUiControls(void* screen);
        static void RefreshInputBindingUiControls();
        static void EnsureOptionsScreenDtorHook(uintptr_t dtorAddr,
                                                InlineDetour32& detour,
                                                void* hook,
                                                FnOptionsScreenDtor& original,
                                                bool& installed,
                                                bool& attempted,
                                                const wchar_t* logTag);

        static void __cdecl ShimSettingsMenuClick()
        {
            OnShimSettingsMenuClicked();
        }

        static constexpr InputBindingRowSeed kInputBindingFirstPassSeeds[] = {
            { "turbo", nullptr, "Turbo" },
            { "throttle_up", nullptr, "Throttle Forward" },
            { "throttle_down", nullptr, "Throttle Back" },
            { "steer_left", nullptr, "Steer Left" },
            { "steer_right", nullptr, "Steer Right" },
            { "pitch_up", nullptr, "Pitch Up" },
            { "pitch_down", nullptr, "Pitch Down" },
            { "strafe_left", nullptr, "Strafe Left" },
            { "strafe_right", nullptr, "Strafe Right" },
            { "jump", nullptr, "Jump" },
            { "weapon_fire", nullptr, "Fire" },
            { "weapon_cycle", nullptr, "Cycle Weapon" },
            { "weapon_link", nullptr, "Link Weapons" },
            { "eject", nullptr, "Eject" },
            { "abandon", nullptr, "Abandon Vehicle" },
            { "cloak", nullptr, "Cloak" },
            { "deploy", nullptr, "Deploy" },
            { "frontal_target", nullptr, "Target Ahead" },
            { "drop_beacon", nullptr, "Drop Beacon" },
            { "cycle_beacon", nullptr, "Cycle Beacon" },
            { "center_player", nullptr, "Center On Player" },
            { "center_recycler", nullptr, "Center On Recycler" },
            { "menu_up", nullptr, "Menu Up" },
            { "menu_down", nullptr, "Menu Down" },
            { "menu_back", nullptr, "Menu Back" },
            { "menu_press", nullptr, "Reticle Command" },
            { "group_select_0", nullptr, "Select Group 1" },
            { "group_select_1", nullptr, "Select Group 2" },
            { "group_select_2", nullptr, "Select Group 3" },
            { "group_select_3", nullptr, "Select Group 4" },
            { "group_select_4", nullptr, "Select Group 5" },
            { "group_select_5", nullptr, "Select Group 6" },
            { "group_select_6", nullptr, "Select Group 7" },
            { "weapon_select_0", nullptr, "Weapon Slot 1" },
            { "weapon_select_1", nullptr, "Weapon Slot 2" },
            { "weapon_select_2", nullptr, "Weapon Slot 3" },
            { "weapon_select_3", nullptr, "Weapon Slot 4" },
            { "weapon_select_4", nullptr, "Weapon Slot 5" },
            { "zoom_factor_plus", nullptr, "Zoom In" },
            { "zoom_factor_minus", nullptr, "Zoom Out" },
        };

        static std::string HumanizeInputBindingCommand(const std::string& command)
        {
            if (command.empty())
                return {};

            std::string text = command;
            for (char& ch : text)
            {
                if (ch == '_')
                    ch = ' ';
                else
                    ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
            }

            bool capitalizeNext = true;
            for (char& ch : text)
            {
                if (std::isspace(static_cast<unsigned char>(ch)))
                {
                    capitalizeNext = true;
                    continue;
                }

                if (capitalizeNext)
                {
                    ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
                    capitalizeNext = false;
                }
            }

            return text;
        }

        static bool IsInputBindingSectionHeading(const std::string& comment)
        {
            if (comment.empty())
                return false;

            if (_stricmp(comment.c_str(), "BATTLEZONE") == 0 ||
                _stricmp(comment.c_str(), "Input Mapping") == 0)
            {
                return false;
            }

            return comment.size() >= 8 &&
                   _stricmp(comment.c_str() + (comment.size() - 8), "CONTROLS") == 0;
        }

        static GameKeyBindingAction* FindGameKeyBindingAction(
            std::vector<GameKeyBindingAction>& actions,
            const std::string& action)
        {
            for (GameKeyBindingAction& entry : actions)
            {
                if (entry.action == action)
                    return &entry;
            }

            return nullptr;
        }

        static std::string JoinStrings(const std::vector<std::string>& parts, const char* separator)
        {
            if (parts.empty())
                return {};

            std::string combined;
            for (size_t index = 0; index < parts.size(); ++index)
            {
                if (index != 0 && separator)
                    combined += separator;
                combined += parts[index];
            }
            return combined;
        }

        static bool AppendUniqueString(std::vector<std::string>& values, const std::string& value)
        {
            if (value.empty())
                return false;

            if (std::find(values.begin(), values.end(), value) != values.end())
                return false;

            values.push_back(value);
            return true;
        }

        static std::filesystem::path ResolveInputBindingInstallDirectory()
        {
            const auto moduleDir = GetMainModuleDirectory();
            const auto hasInputMap = [](const std::filesystem::path& dir) -> bool
            {
                if (dir.empty())
                    return false;

                std::error_code error;
                return std::filesystem::exists(dir / "input.map", error);
            };

            if (hasInputMap(moduleDir))
                return moduleDir;

            char userProfile[MAX_PATH] = {};
            const DWORD userProfileLen =
                GetEnvironmentVariableA("USERPROFILE", userProfile, MAX_PATH);
            if (userProfileLen > 0 && userProfileLen < MAX_PATH)
            {
                const std::filesystem::path documentsInstall =
                    std::filesystem::path(userProfile) / "Documents" / "Battlezone 98 Redux";
                if (hasInputMap(documentsInstall))
                    return documentsInstall;
            }

            const std::filesystem::path gogInstall("<GAME_ROOT>");
            if (hasInputMap(gogInstall))
                return gogInstall;

            return moduleDir;
        }

        static bool LoadInputBindingDocument(const std::filesystem::path& path,
                                             InputBindingDocument& outDocument)
        {
            outDocument.lines.clear();
            outDocument.loaded = false;

            std::ifstream file(path);
            if (!file)
                return false;

            std::string line;
            while (std::getline(file, line))
            {
                if (!line.empty() && line.back() == '\r')
                    line.pop_back();
                outDocument.lines.push_back(line);
            }

            outDocument.loaded = true;
            return true;
        }

        static bool ParseInputBindingMapFile(
            const std::filesystem::path& inputMapPath,
            InputBindingDocument& outDocument,
            std::vector<InputBindingCommandBlock>& outBlocks,
            InputBindingInventoryStats& outInventory)
        {
            outBlocks.clear();
            outInventory = {};

            if (!LoadInputBindingDocument(inputMapPath, outDocument))
                return false;

            std::string pendingComment;
            std::string currentSection;
            bool inBlock = false;
            InputBindingCommandBlock currentBlock = {};

            auto finalizeBlock = [&](size_t closeLineIndex)
            {
                if (currentBlock.command.empty())
                    return;

                currentBlock.closeLineIndex = closeLineIndex;
                ++outInventory.uniqueCommandBlocks;
                if (currentBlock.hasPositiveNonKeyboard)
                    ++outInventory.mixedBlocks;
                else if (currentBlock.positiveKeyboardTokens.size() > 1)
                    ++outInventory.keyboardChordBlocks;
                else if (!currentBlock.positiveKeyboardTokens.empty())
                    ++outInventory.simpleKeyboardBlocks;

                outBlocks.push_back(currentBlock);
                currentBlock = {};
            };

            for (size_t lineIndex = 0; lineIndex < outDocument.lines.size(); ++lineIndex)
            {
                const std::string trimmed = TrimAsciiCopy(outDocument.lines[lineIndex]);
                if (!inBlock)
                {
                    if (trimmed.empty())
                        continue;

                    if (trimmed[0] == '#')
                    {
                        const std::string comment = TrimAsciiCopy(trimmed.substr(1));
                        if (!comment.empty())
                        {
                            if (IsInputBindingSectionHeading(comment))
                            {
                                currentSection = comment;
                                pendingComment.clear();
                            }
                            else
                            {
                                pendingComment = comment;
                            }
                        }
                        continue;
                    }

                    const size_t bracePos = trimmed.find('{');
                    if (bracePos == std::string::npos)
                    {
                        pendingComment.clear();
                        continue;
                    }

                    const std::string command = TrimAsciiCopy(trimmed.substr(0, bracePos));
                    if (command.empty())
                    {
                        pendingComment.clear();
                        continue;
                    }

                    currentBlock = {};
                    currentBlock.command = command;
                    currentBlock.section = currentSection;
                    currentBlock.comment = pendingComment;
                    currentBlock.headerLineIndex = lineIndex;
                    pendingComment.clear();
                    inBlock = true;
                    continue;
                }

                if (trimmed.empty() || trimmed[0] == '#')
                    continue;

                if (trimmed[0] == '}')
                {
                    finalizeBlock(lineIndex);
                    inBlock = false;
                    continue;
                }

                if (trimmed[0] != '+' && trimmed[0] != '-')
                    continue;

                size_t cursor = 1;
                while (cursor < trimmed.size() &&
                       std::isspace(static_cast<unsigned char>(trimmed[cursor])))
                {
                    ++cursor;
                }

                const size_t sourceStart = cursor;
                while (cursor < trimmed.size() &&
                       !std::isspace(static_cast<unsigned char>(trimmed[cursor])))
                {
                    ++cursor;
                }

                const std::string source = trimmed.substr(sourceStart, cursor - sourceStart);
                const std::string token = TrimAsciiCopy(trimmed.substr(cursor));
                if (source.empty() || token.empty())
                    continue;

                InputBindingLineRef lineRef = {};
                lineRef.lineIndex = lineIndex;
                lineRef.positive = trimmed[0] == '+';
                lineRef.source = source;
                lineRef.token = token;
                currentBlock.bindingLines.push_back(lineRef);

                if (trimmed[0] == '+')
                {
                    if (_stricmp(source.c_str(), "keyboard") == 0)
                        currentBlock.positiveKeyboardTokens.push_back(token);
                    else
                    {
                        currentBlock.hasPositiveNonKeyboard = true;
                        currentBlock.positiveNonKeyboardTokens.push_back(source + " " + token);
                    }
                }
            }

            if (inBlock)
                finalizeBlock(SIZE_MAX);

            return true;
        }

        static bool ParseGameKeyBindingMapFile(
            const std::filesystem::path& gameKeyMapPath,
            InputBindingDocument& outDocument,
            std::vector<GameKeyBindingAction>& outActions,
            InputBindingInventoryStats& outInventory)
        {
            outActions.clear();
            outInventory.uniqueGameKeyActions = 0;
            outInventory.gameKeyChords = 0;

            if (!LoadInputBindingDocument(gameKeyMapPath, outDocument))
                return false;

            for (size_t lineIndex = 0; lineIndex < outDocument.lines.size(); ++lineIndex)
            {
                const std::string trimmed = TrimAsciiCopy(outDocument.lines[lineIndex]);
                if (trimmed.empty() || trimmed[0] == '#')
                    continue;

                size_t cursor = 0;
                while (cursor < trimmed.size() &&
                       !std::isspace(static_cast<unsigned char>(trimmed[cursor])))
                {
                    ++cursor;
                }

                const std::string action = trimmed.substr(0, cursor);
                const std::string chord = TrimAsciiCopy(trimmed.substr(cursor));
                if (action.empty() || chord.empty())
                    continue;

                GameKeyBindingAction* existing = FindGameKeyBindingAction(outActions, action);
                if (!existing)
                {
                    GameKeyBindingAction created = {};
                    created.action = action;
                    outActions.push_back(std::move(created));
                    existing = &outActions.back();
                }

                if (AppendUniqueString(existing->chords, chord))
                {
                    existing->chordLineIndices.push_back(lineIndex);
                    ++outInventory.gameKeyChords;
                }
            }

            outInventory.uniqueGameKeyActions = outActions.size();
            return true;
        }

        static std::string DescribeLastWin32Error()
        {
            const DWORD error = GetLastError();
            char buffer[32] = {};
            _snprintf_s(buffer, _TRUNCATE, "win32 error %lu", static_cast<unsigned long>(error));
            return buffer;
        }

        // Writes a document to an adjacent temp file, keeps a .openshim.bak copy of
        // the pre-edit file, and prefers an atomic swap. Packaged GOG/Steam maps
        // may be read-only, so make the live file writable and retain a guarded
        // copy fallback for installations where ReplaceFile is unavailable.
        static bool WriteInputBindingDocumentAtomic(const std::filesystem::path& path,
                                                    const InputBindingDocument& document,
                                                    std::string& outError)
        {
            outError.clear();
            if (!document.loaded)
            {
                outError = "document was never loaded";
                return false;
            }

            const std::filesystem::path tempPath =
                std::filesystem::path(path.wstring() + L".openshim.tmp");
            const std::filesystem::path backupPath =
                std::filesystem::path(path.wstring() + L".openshim.bak");

            {
                std::ofstream file(tempPath, std::ios::trunc);
                if (!file)
                {
                    outError = "could not create temp file " + tempPath.string();
                    return false;
                }

                for (const std::string& line : document.lines)
                    file << line << "\n";

                file.flush();
                if (!file.good())
                {
                    outError = "write failed for temp file " + tempPath.string();
                    file.close();
                    std::error_code ignored;
                    std::filesystem::remove(tempPath, ignored);
                    return false;
                }
            }

            std::error_code existsError;
            const bool targetExists = std::filesystem::exists(path, existsError);
            if (targetExists)
            {
                const DWORD targetAttributes = GetFileAttributesW(path.c_str());
                const bool targetWasReadOnly =
                    targetAttributes != INVALID_FILE_ATTRIBUTES &&
                    (targetAttributes & FILE_ATTRIBUTE_READONLY) != 0;
                if (targetWasReadOnly &&
                    !SetFileAttributesW(path.c_str(), targetAttributes & ~FILE_ATTRIBUTE_READONLY))
                {
                    outError = "could not make the installed map writable (" +
                               DescribeLastWin32Error() + ")";
                    std::error_code ignored;
                    std::filesystem::remove(tempPath, ignored);
                    return false;
                }

                const DWORD backupAttributes = GetFileAttributesW(backupPath.c_str());
                if (backupAttributes != INVALID_FILE_ATTRIBUTES &&
                    (backupAttributes & FILE_ATTRIBUTE_READONLY) != 0)
                {
                    SetFileAttributesW(backupPath.c_str(),
                                       backupAttributes & ~FILE_ATTRIBUTE_READONLY);
                }
                if (!CopyFileW(path.c_str(), backupPath.c_str(), FALSE))
                {
                    Log(L"[INPUTUI] Backup copy failed for %hs (%hs); continuing with replace\n",
                        path.string().c_str(),
                        DescribeLastWin32Error().c_str());
                }

                bool replaced = ReplaceFileW(path.c_str(),
                                             tempPath.c_str(),
                                             nullptr,
                                             REPLACEFILE_IGNORE_MERGE_ERRORS,
                                             nullptr,
                                             nullptr) != FALSE;
                if (!replaced)
                {
                    replaced = MoveFileExW(tempPath.c_str(),
                                           path.c_str(),
                                           MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH) != FALSE;
                }
                if (!replaced && CopyFileW(tempPath.c_str(), path.c_str(), FALSE))
                {
                    std::error_code ignored;
                    std::filesystem::remove(tempPath, ignored);
                    replaced = true;
                    Log(L"[INPUTUI] Used guarded copy fallback for %hs\n",
                        path.string().c_str());
                }
                if (!replaced)
                {
                    outError = "atomic replace failed for " + path.string() +
                               " (" + DescribeLastWin32Error() + ")";
                    if (targetWasReadOnly)
                        SetFileAttributesW(path.c_str(), targetAttributes);
                    std::error_code ignored;
                    std::filesystem::remove(tempPath, ignored);
                    return false;
                }
            }
            else if (!MoveFileExW(tempPath.c_str(), path.c_str(), MOVEFILE_WRITE_THROUGH))
            {
                outError = "move into place failed for " + path.string() +
                           " (" + DescribeLastWin32Error() + ")";
                std::error_code ignored;
                std::filesystem::remove(tempPath, ignored);
                return false;
            }

            return true;
        }

        static const InputBindingCommandBlock* FindInputBindingCommandBlock(const std::string& command)
        {
            for (const InputBindingCommandBlock& block : g_InputBindingCommandBlocks)
            {
                if (block.command == command)
                    return &block;
            }
            return nullptr;
        }

        // Rewrites only the primary positive keyboard token of a command block; all
        // other lines (comments, mouse variants, negative guards, extra chords) are
        // preserved verbatim.
        static bool SetInputMapPrimaryKeyboardBinding(const std::string& command,
                                                      const std::string& keyName,
                                                      std::string& outError)
        {
            outError.clear();
            if (!g_InputMapDocument.loaded)
            {
                outError = "input.map is not loaded";
                return false;
            }

            const InputBindingCommandBlock* block = FindInputBindingCommandBlock(command);
            if (!block)
            {
                outError = "command " + command + " not found in input.map";
                return false;
            }

            const InputBindingLineRef* primary = nullptr;
            for (const InputBindingLineRef& lineRef : block->bindingLines)
            {
                if (lineRef.positive && _stricmp(lineRef.source.c_str(), "keyboard") == 0)
                {
                    primary = &lineRef;
                    break;
                }
            }

            InputBindingDocument edited = g_InputMapDocument;
            if (primary && primary->lineIndex < edited.lines.size())
            {
                const std::string& original = edited.lines[primary->lineIndex];
                const size_t signPos = original.find('+');
                const std::string prefix =
                    signPos == std::string::npos ? std::string("\t") : original.substr(0, signPos);
                edited.lines[primary->lineIndex] = prefix + "+ keyboard " + keyName;
            }
            else
            {
                size_t insertAt = SIZE_MAX;
                if (block->headerLineIndex != SIZE_MAX &&
                    block->headerLineIndex + 1 <= edited.lines.size())
                {
                    insertAt = block->headerLineIndex + 1;
                }
                else if (block->closeLineIndex != SIZE_MAX &&
                         block->closeLineIndex <= edited.lines.size())
                {
                    insertAt = block->closeLineIndex;
                }

                if (insertAt == SIZE_MAX)
                {
                    outError = "no insertion point for " + command + " in input.map";
                    return false;
                }

                edited.lines.insert(edited.lines.begin() + insertAt, "\t+ keyboard " + keyName);
            }

            const std::filesystem::path inputMapPath =
                g_InputBindingInstallDirectory / "input.map";
            return WriteInputBindingDocumentAtomic(inputMapPath, edited, outError);
        }

        // Rewrites only the first chord line of a gamekey.map action; additional
        // chord lines and every comment stay untouched.
        static bool SetGameKeyBindingPrimaryChord(const std::string& action,
                                                  const std::string& newChord,
                                                  std::string& outError)
        {
            outError.clear();
            if (!g_GameKeyMapDocument.loaded)
            {
                outError = "gamekey.map is not loaded";
                return false;
            }

            GameKeyBindingAction* entry =
                FindGameKeyBindingAction(g_GameKeyBindingActions, action);
            if (!entry)
            {
                outError = "action " + action + " not found in gamekey.map";
                return false;
            }

            InputBindingDocument edited = g_GameKeyMapDocument;
            if (!entry->chordLineIndices.empty() &&
                entry->chordLineIndices[0] < edited.lines.size())
            {
                const size_t lineIndex = entry->chordLineIndices[0];
                const std::string& original = edited.lines[lineIndex];

                size_t cursor = 0;
                while (cursor < original.size() &&
                       std::isspace(static_cast<unsigned char>(original[cursor])))
                {
                    ++cursor;
                }
                while (cursor < original.size() &&
                       !std::isspace(static_cast<unsigned char>(original[cursor])))
                {
                    ++cursor;
                }
                const size_t chordStart = original.find_first_not_of(" \t", cursor);
                if (chordStart == std::string::npos)
                {
                    outError = "could not locate chord column for " + action;
                    return false;
                }

                edited.lines[lineIndex] = original.substr(0, chordStart) + newChord;
            }
            else
            {
                edited.lines.push_back(action + "\t\t\t" + newChord);
            }

            const std::filesystem::path gameKeyMapPath =
                g_InputBindingInstallDirectory / "gamekey.map";
            return WriteInputBindingDocumentAtomic(gameKeyMapPath, edited, outError);
        }

        static std::string FormatInputBindingBlockValue(const InputBindingCommandBlock& block)
        {
            std::vector<std::string> parts = {};
            if (!block.positiveKeyboardTokens.empty())
                parts.push_back(JoinStrings(block.positiveKeyboardTokens, " + "));

            for (const std::string& token : block.positiveNonKeyboardTokens)
                AppendUniqueString(parts, token);

            return JoinStrings(parts, " | ");
        }

        static std::vector<InputBindingUiRow> BuildFirstPassInputBindingRows(
            const std::vector<InputBindingCommandBlock>& blocks)
        {
            std::vector<InputBindingUiRow> rows;
            rows.reserve(blocks.size());
            std::unordered_map<std::string, size_t> rowIndexByCommand = {};
            std::vector<std::string> encounteredCommands = {};
            encounteredCommands.reserve(blocks.size());
            std::vector<std::vector<std::string>> bindingValues = {};
            bindingValues.reserve(blocks.size());

            for (const InputBindingCommandBlock& block : blocks)
            {
                if (block.command.empty())
                    continue;

                size_t rowIndex = rows.size();
                const auto existing = rowIndexByCommand.find(block.command);
                if (existing == rowIndexByCommand.end())
                {
                    InputBindingUiRow row = {};
                    row.family = InputBindingMapFamily::Input;
                    row.command = block.command;
                    row.sectionName = block.section;
                    row.displayText =
                        !block.comment.empty() ? block.comment : HumanizeInputBindingCommand(block.command);
                    row.foundInMap = true;
                    rows.push_back(std::move(row));
                    encounteredCommands.push_back(block.command);
                    bindingValues.push_back({});
                    rowIndexByCommand.emplace(block.command, rowIndex);
                }
                else
                {
                    rowIndex = existing->second;
                }

                InputBindingUiRow& row = rows[rowIndex];
                row.foundInMap = true;
                ++row.matchingBlockCount;
                if (row.sectionName.empty() && !block.section.empty())
                    row.sectionName = block.section;
                if (row.displayText.empty() && !block.comment.empty())
                    row.displayText = block.comment;

                AppendUniqueString(bindingValues[rowIndex], FormatInputBindingBlockValue(block));
            }

            for (size_t index = 0; index < rows.size(); ++index)
            {
                InputBindingUiRow& row = rows[index];
                if (row.displayText.empty())
                    row.displayText = HumanizeInputBindingCommand(row.command);
                row.currentBindingText = JoinStrings(bindingValues[index], ", ");
                row.reserved = row.currentBindingText.empty();
            }

            std::vector<InputBindingUiRow> orderedRows = {};
            orderedRows.reserve(rows.size());
            std::unordered_set<std::string> usedCommands = {};

            const auto appendOrderedRow = [&](const std::string& command, const char* displayText)
            {
                const auto found = rowIndexByCommand.find(command);
                if (found == rowIndexByCommand.end())
                    return;

                InputBindingUiRow row = rows[found->second];
                if (displayText && *displayText)
                    row.displayText = displayText;

                orderedRows.push_back(std::move(row));
                usedCommands.insert(command);
            };

            for (const InputBindingRowSeed& seed : kInputBindingFirstPassSeeds)
            {
                if (!seed.command || !*seed.command)
                    continue;
                appendOrderedRow(seed.command, seed.displayText);
            }

            for (const std::string& command : encounteredCommands)
            {
                if (usedCommands.find(command) != usedCommands.end())
                    continue;
                appendOrderedRow(command, nullptr);
            }

            return orderedRows;
        }

        static std::vector<InputBindingUiRow> BuildFirstPassGameKeyBindingRows(
            const std::vector<GameKeyBindingAction>& actions)
        {
            std::vector<InputBindingUiRow> rows;
            rows.reserve(actions.size());

            for (const GameKeyBindingAction& action : actions)
            {
                InputBindingUiRow row = {};
                row.family = InputBindingMapFamily::GameKey;
                row.command = action.action;
                row.displayText = HumanizeInputBindingCommand(action.action);
                row.currentBindingText = JoinStrings(action.chords, ", ");
                row.foundInMap = true;
                row.reserved = row.currentBindingText.empty();
                row.matchingBlockCount = action.chords.size();
                rows.push_back(std::move(row));
            }

            return rows;
        }

        static void LogInputBindingUiScaffoldSummary()
        {
            if (g_InputBindingUiScaffoldLogged)
                return;
            g_InputBindingUiScaffoldLogged = true;

            const std::string installPath = g_InputBindingInstallDirectory.string();
            const std::string inputMapPath =
                (g_InputBindingInstallDirectory / "input.map").string();
            const std::string gameKeyMapPath =
                (g_InputBindingInstallDirectory / "gamekey.map").string();

            Log(L"[INPUTUI] Scaffold install=%hs input.map=%hs gamekey.map=%hs inputBlocks=%u simple=%u chord=%u mixed=%u gameActions=%u gameChords=%u firstPassInputRows=%u firstPassGameKeyRows=%u totalRows=%u\n",
                installPath.c_str(),
                inputMapPath.c_str(),
                gameKeyMapPath.c_str(),
                static_cast<unsigned>(g_InputBindingInventory.uniqueCommandBlocks),
                static_cast<unsigned>(g_InputBindingInventory.simpleKeyboardBlocks),
                static_cast<unsigned>(g_InputBindingInventory.keyboardChordBlocks),
                static_cast<unsigned>(g_InputBindingInventory.mixedBlocks),
                static_cast<unsigned>(g_InputBindingInventory.uniqueGameKeyActions),
                static_cast<unsigned>(g_InputBindingInventory.gameKeyChords),
                static_cast<unsigned>(g_InputBindingInventory.firstPassInputRows),
                static_cast<unsigned>(g_InputBindingInventory.firstPassGameKeyRows),
                static_cast<unsigned>(g_InputBindingUiRows.size()));

            const size_t previewCount = std::min<size_t>(g_InputBindingUiRows.size(), 10);
            for (size_t index = 0; index < previewCount; ++index)
            {
                const InputBindingUiRow& row = g_InputBindingUiRows[index];
                const char* familyText =
                    row.family == InputBindingMapFamily::GameKey ? "gamekey" : "input";
                Log(L"[INPUTUI]   row[%u] family=%hs cmd=%hs title=%hs value=%hs reserved=%hs blocks=%u\n",
                    static_cast<unsigned>(index),
                    familyText,
                    row.command.c_str(),
                    row.displayText.c_str(),
                    row.currentBindingText.empty() ? "<none>" : row.currentBindingText.c_str(),
                    row.reserved ? "yes" : "no",
                    static_cast<unsigned>(row.matchingBlockCount));
            }

            Log(L"[INPUTUI] Recovered stock constructor entry=0x%08X screenFactoryCall=0x%08X\n",
                static_cast<uint32_t>(g_OptionsInputCtorAddr),
                static_cast<uint32_t>(g_OptionsInputScreenFactoryCallerAddr));
        }

        static bool ShouldEnableInputBindingUiReplacement()
        {
            static int s_cached = -1;
            if (s_cached < 0)
            {
                bool enabled = true;
                bool configured = false;
                if (TryGetUserConfigBool("General", "CustomBindsUi", configured) ||
                    TryGetUserConfigBool("General", "CustomBindingUi", configured))
                {
                    enabled = configured;
                }
                const bool disabled =
                    EnvFlagEnabled("OPENSHIM_DISABLE_INPUT_BINDING_UI") ||
                    EnvFlagEnabled("OPENSHIM_DISABLE_INPUT_BINDING_UI_REPLACEMENT") ||
                    EnvFlagEnabled("BZR_DISABLE_INPUT_BINDING_UI");
                const bool forcedEnabled =
                    EnvFlagEnabled("OPENSHIM_ENABLE_INPUT_BINDING_UI") ||
                    EnvFlagEnabled("OPENSHIM_ENABLE_INPUT_BINDING_UI_REPLACEMENT") ||
                    EnvFlagEnabled("BZR_ENABLE_INPUT_BINDING_UI");
                s_cached = disabled ? 0 : ((forcedEnabled || enabled) ? 1 : 0);
            }
            return s_cached != 0;
        }

        static void ResetInputBindingUiVisuals()
        {
            g_InputScreenBinding.BindDecorated(nullptr);
            g_InputBindingUiMiddleOverlay = nullptr;
            g_InputBindingUiTopMask = nullptr;
            g_InputBindingUiContentMask = nullptr;
            g_InputBindingUiDecor.fill(nullptr);
            g_InputBindingUiRowBackdrops.fill(nullptr);
            g_InputBindingUiHeaderLabel = nullptr;
            g_InputBindingUiStatusLabel = nullptr;
            g_InputBindingUiStatusDetailLabel = nullptr;
            g_InputBindingUiPageLabel = nullptr;
            g_InputBindingUiBackButton = nullptr;
            g_InputBindingUiDefaultsButton = nullptr;
            g_InputBindingUiInputFamilyButton = nullptr;
            g_InputBindingUiGameKeyFamilyButton = nullptr;
            g_InputBindingUiPrevPageButton = nullptr;
            g_InputBindingUiNextPageButton = nullptr;
            g_InputBindingUiRefreshButton = nullptr;
            g_InputBindingUiRowLabels.fill(nullptr);
            g_InputBindingUiRowButtons.fill(nullptr);
            g_InputBindingUiVisibleRowIndices.fill(-1);
            g_InputBindingUiPendingCommand.clear();
            g_InputBindingUiPendingDisplayText.clear();
            g_InputBindingUiStatusText = "Click a binding button, then press a key. ESC cancels.";
        }

        // The stock input-options constructor assumes input.map exists and can
        // terminate the game before our constructor hook regains control. Repair
        // a missing file during OpenShim startup, preferring the last atomic-write
        // backup and then the GOG/Steam packaged mobile/default map.
        static bool RecoverMissingInputMap()
        {
            const std::filesystem::path inputMapPath =
                g_InputBindingInstallDirectory / "input.map";
            std::error_code error;
            if (std::filesystem::exists(inputMapPath, error))
                return true;

            const std::array<std::filesystem::path, 2> candidates =
            {
                g_InputBindingInstallDirectory / "input.map.openshim.bak",
                g_InputBindingInstallDirectory / "inputmbl.map"
            };

            for (const std::filesystem::path& candidate : candidates)
            {
                error.clear();
                if (!std::filesystem::is_regular_file(candidate, error))
                    continue;

                if (::CopyFileW(candidate.c_str(), inputMapPath.c_str(), TRUE))
                {
                    const DWORD recoveredAttributes = GetFileAttributesW(inputMapPath.c_str());
                    if (recoveredAttributes != INVALID_FILE_ATTRIBUTES &&
                        (recoveredAttributes & FILE_ATTRIBUTE_READONLY) != 0)
                    {
                        SetFileAttributesW(inputMapPath.c_str(),
                                           recoveredAttributes & ~FILE_ATTRIBUTE_READONLY);
                    }
                    Log(L"[INPUTUI] Recovered missing input.map from %ls\n",
                        candidate.c_str());
                    return true;
                }

                const DWORD copyError = GetLastError();
                if (copyError == ERROR_FILE_EXISTS || copyError == ERROR_ALREADY_EXISTS)
                    return true;

                Log(L"[INPUTUI] Could not recover input.map from %ls (Win32=%u)\n",
                    candidate.c_str(),
                    static_cast<unsigned>(copyError));
            }

            Log(L"[INPUTUI] input.map is missing and no recovery source was found\n");
            return false;
        }

        static bool ReloadInputBindingUiInventory(bool logFailures)
        {
            g_InputBindingInventory = {};
            g_InputMapDocument = {};
            g_GameKeyMapDocument = {};
            g_InputBindingCommandBlocks.clear();
            g_GameKeyBindingActions.clear();
            g_InputBindingUiRows.clear();

            const std::filesystem::path inputMapPath = g_InputBindingInstallDirectory / "input.map";
            if (!ParseInputBindingMapFile(inputMapPath,
                                          g_InputMapDocument,
                                          g_InputBindingCommandBlocks,
                                          g_InputBindingInventory))
            {
                if (logFailures)
                {
                    const std::string inputMapPathText = inputMapPath.string();
                    Log(L"[INPUTUI] Failed to parse input binding map at %hs\n",
                        inputMapPathText.c_str());
                }
                return false;
            }

            const std::filesystem::path gameKeyMapPath = g_InputBindingInstallDirectory / "gamekey.map";
            if (!ParseGameKeyBindingMapFile(gameKeyMapPath,
                                            g_GameKeyMapDocument,
                                            g_GameKeyBindingActions,
                                            g_InputBindingInventory) &&
                logFailures)
            {
                const std::string gameKeyMapPathText = gameKeyMapPath.string();
                Log(L"[INPUTUI] Failed to parse gamekey binding map at %hs\n",
                    gameKeyMapPathText.c_str());
            }

            std::vector<InputBindingUiRow> inputRows =
                BuildFirstPassInputBindingRows(g_InputBindingCommandBlocks);
            std::vector<InputBindingUiRow> gameKeyRows =
                BuildFirstPassGameKeyBindingRows(g_GameKeyBindingActions);
            g_InputBindingInventory.firstPassInputRows = inputRows.size();
            g_InputBindingInventory.firstPassGameKeyRows = gameKeyRows.size();

            g_InputBindingUiRows = std::move(inputRows);
            g_InputBindingUiRows.insert(
                g_InputBindingUiRows.end(),
                gameKeyRows.begin(),
                gameKeyRows.end());
            return true;
        }

        static size_t FindInputBindingUiRowIndex(InputBindingMapFamily family, const std::string& command)
        {
            for (size_t index = 0; index < g_InputBindingUiRows.size(); ++index)
            {
                const InputBindingUiRow& row = g_InputBindingUiRows[index];
                if (row.family == family && row.command == command)
                    return index;
            }
            return g_InputBindingUiRows.size();
        }

        static size_t GetInputBindingUiRowCountForFamily(InputBindingMapFamily family)
        {
            size_t count = 0;
            for (const InputBindingUiRow& row : g_InputBindingUiRows)
            {
                if (row.family == family)
                    ++count;
            }
            return count;
        }

        static size_t ClampInputBindingUiPageStart(InputBindingMapFamily family, size_t pageStart)
        {
            const size_t totalRows = GetInputBindingUiRowCountForFamily(family);
            if (totalRows <= kInputBindingUiVisibleRowCount)
                return 0;

            const size_t maxPageStart =
                ((totalRows - 1) / kInputBindingUiVisibleRowCount) * kInputBindingUiVisibleRowCount;
            return (std::min)(pageStart, maxPageStart);
        }

        static bool IsInputBindingUiPending(const InputBindingUiRow& row)
        {
            return !g_InputBindingUiPendingCommand.empty() &&
                   row.family == g_InputBindingUiPendingFamily &&
                   row.command == g_InputBindingUiPendingCommand;
        }

        static void SetInputBindingUiViewActive(void* view, bool active);

        static bool SetInputBindingUiLabelText(void* label, const char* text)
        {
            if (!label || !g_BzrFn_SetTooltip)
                return false;

            g_BzrFn_SetTooltip(label, text ? text : "");
            if (g_BzrFn_LabelState)
                g_BzrFn_LabelState(label, reinterpret_cast<void*>(1));
            return true;
        }

        static bool CreateInputBindingUiLabel(void*& slot,
                                              void* parent,
                                              const char* objectName,
                                              const char* text,
                                              float x,
                                              float y,
                                              float w,
                                              float h)
        {
            if (!parent || !g_BzrFn_LabelCtor || !g_BzrFn_AddChild)
                return false;

            if (slot)
            {
                const bool updated = SetInputBindingUiLabelText(slot, text);
                SetInputBindingUiViewActive(slot, true);
                return updated;
            }

            void* labelMem = ::operator new(0x930, std::nothrow);
            if (!labelMem)
                return false;

            std::memset(labelMem, 0, 0x930);
            const char* ctorLabel =
                (objectName && *objectName) ? objectName :
                ((text && *text) ? text : "OpenShimInputLabel");
            slot = g_BzrFn_LabelCtor(labelMem, ctorLabel, x, y, w, h, 0x20, parent, 0);
            if (!slot)
                return false;

            if (g_BzrFn_LabelState)
                g_BzrFn_LabelState(slot, reinterpret_cast<void*>(1));
            g_BzrFn_AddChild(parent, slot, 0);
            SetInputBindingUiLabelText(slot, text);
            SetInputBindingUiViewActive(slot, true);
            return true;
        }

        static bool CreateInputBindingUiOverlay(void*& slot,
                                                void* parent,
                                                const char* objectName,
                                                const char* textureName,
                                                float x,
                                                float y,
                                                float w,
                                                float h,
                                                uint32_t flags)
        {
            if (!parent || !g_BzrFn_OverlayCtor || !g_BzrFn_AddChild)
                return false;

            if (!slot)
            {
                void* overlayMem = ::operator new(0x144, std::nothrow);
                if (!overlayMem)
                    return false;

                std::memset(overlayMem, 0, 0x144);
                const char* ctorLabel =
                    (objectName && *objectName) ? objectName : "OpenShimInputOverlay";
                slot = g_BzrFn_OverlayCtor(overlayMem, ctorLabel, x, y, w, h, flags, parent, 0);
                if (!slot)
                    return false;

                g_BzrFn_AddChild(parent, slot, 0);
            }

            if (textureName && *textureName && g_BzrFn_SetTextureOff)
                g_BzrFn_SetTextureOff(slot, textureName);
            SetInputBindingUiViewActive(slot, true);
            return true;
        }

        // Keeps the +0x150 hover slot non-null on injected buttons. Screens that
        // walk dialog children invoke this slot; a null slot is a call through
        // NULL (see AutoSaveButtonOnHoverNoop for the same crash mechanism).
        static void __cdecl InputBindingUiButtonOnHoverNoop(void* /*param*/)
        {
        }

        static bool CreateInputBindingUiButton(void*& slot,
                                               void* parent,
                                               const char* objectName,
                                               const char* text,
                                               float x,
                                               float y,
                                               float w,
                                               float h,
                                               void* onClick,
                                               void* onHover = nullptr)
        {
            // The engine calls a child button's hover/click slots; a button
            // built without them crashes the screen.
            if (!parent || !g_BzrFn_ButtonCtor || !g_BzrFn_AddChild ||
                !g_BzrFn_SetOnClick || !g_BzrFn_SetOnHover)
                return false;

            if (!slot)
            {
                void* buttonMem = ::operator new(0x1EC, std::nothrow);
                if (!buttonMem)
                    return false;

                std::memset(buttonMem, 0, 0x1EC);
                const char* ctorLabel =
                    (objectName && *objectName) ? objectName :
                    ((text && *text) ? text : "OpenShimInputButton");
                slot = g_BzrFn_ButtonCtor(buttonMem,
                                          ctorLabel,
                                          x,
                                          y,
                                          w,
                                          h,
                                          0x20,
                                          parent,
                                          0,
                                          0);
                if (!slot)
                    return false;

                if (g_InputBindingUiSkin) {
                if (g_BzrFn_SetTextureOver) g_BzrFn_SetTextureOver(slot, g_InputBindingUiSkin->over);
                if (g_BzrFn_SetTextureOn) g_BzrFn_SetTextureOn(slot, g_InputBindingUiSkin->on);
            } else if (IsUiTextureFileAvailable("uibtn.png")) {
                if (g_BzrFn_SetTextureOff) g_BzrFn_SetTextureOff(slot, "uibtn.png");
                if (g_BzrFn_SetTextureOver) g_BzrFn_SetTextureOver(slot, "uibtnhv.png");
                if (g_BzrFn_SetTextureOn) g_BzrFn_SetTextureOn(slot, "uibtnhv.png");
            } else {
                // Fallback: use stock button texture if available, otherwise keep default
                if (g_BzrFn_SetTextureOff && IsUiTextureFileAvailable("mpcron.png"))
                    g_BzrFn_SetTextureOff(slot, "mpcron.png");
            }
                g_BzrFn_AddChild(parent, slot, 0);
            }

            if (g_BzrFn_SetOnClick && onClick)
                g_BzrFn_SetOnClick(slot, onClick);
            if (g_BzrFn_SetOnHover)
                g_BzrFn_SetOnHover(slot, onHover ? onHover
                                                 : reinterpret_cast<void*>(InputBindingUiButtonOnHoverNoop));
            if (g_BzrFn_SetButtonLabel)
                g_BzrFn_SetButtonLabel(slot, text ? text : "");
            if (g_BzrFn_SetButtonTextScale)
                g_BzrFn_SetButtonTextScale(slot, 0.85f);
            SetInputBindingUiViewActive(slot, true);
            return true;
        }

        // Decorative surface that follows the same parent-relative geometry as
        // the stock buttons. Overlay objects use a different coordinate path on
        // this screen and drift right when parented to the middle panel.
        //
        // The tile is a flat fill. The engine stretches a widget texture to the
        // widget rect, so the stock plate art ("mpcron.png") had its diagonal
        // highlight squashed underneath the value text; a flat fill cannot
        // distort. The label field is darker than the value button beside it,
        // which is what separates the two now that neither carries a border.
        static bool CreateInputBindingUiPlate(void*& slot,
                                              void* parent,
                                              const char* objectName,
                                              float x,
                                              float y,
                                              float w,
                                              float h)
        {
            if (!CreateInputBindingUiButton(slot, parent, objectName, "", x, y, w, h, nullptr))
                return false;

            if (IsUiTextureFileAvailable("uiplate.png")) {
                if (g_BzrFn_SetTextureOff) g_BzrFn_SetTextureOff(slot, "uiplate.png");
                if (g_BzrFn_SetTextureOver) g_BzrFn_SetTextureOver(slot, "uiplate.png");
                if (g_BzrFn_SetTextureOn) g_BzrFn_SetTextureOn(slot, "uiplate.png");
            } // else keep default plate appearance

            return true;
        }

        // A panel border bar. Same construction as a row plate -- a button with
        // no click handler -- but with one flat texture in every state, so
        // hovering the frame does not light it up.
        static bool CreateInputBindingUiDecorPiece(void*& slot,
                                                   void* parent,
                                                   const char* objectName,
                                                   const char* textureName,
                                                   float x,
                                                   float y,
                                                   float w,
                                                   float h)
        {
            if (!CreateInputBindingUiButton(slot, parent, objectName, "", x, y, w, h, nullptr))
                return false;

            const char* texture = (textureName && *textureName) ? textureName : "uiline.png";
            if (IsUiTextureFileAvailable(texture)) {
                if (g_BzrFn_SetTextureOff) g_BzrFn_SetTextureOff(slot, texture);
                if (g_BzrFn_SetTextureOver) g_BzrFn_SetTextureOver(slot, texture);
                if (g_BzrFn_SetTextureOn) g_BzrFn_SetTextureOn(slot, texture);
            } // else keep default decor appearance for DLL-only
            return true;
        }

        // Panel frames are plates on the control parent, not overlay views.
        // Overlays take a different coordinate path on this screen: a 2026-08-30
        // capture had all eleven frame textures load and then rasterize nothing
        // at the panel edges (sampled pure black), while plates land exactly on
        // their layout rect. Frames are created before every label and button on
        // the page, so they sit behind the controls, and they are outlines only,
        // so no decoration is laid across a rect that has to take a click.
        static void CreateInputBindingUiPageDecor(
            std::array<void*, kUiDecorMaxOptionsPagePieces>& slots,
            void* controlParent,
            const char* namePrefix,
            unsigned screenTag,
            const UiOptionsPageLayout& layout)
        {
            if (!controlParent || !namePrefix)
                return;

            UiDecorPanelDesc panels[kUiDecorPanelsPerOptionsPage] = {};
            const size_t panelCount =
                BuildUiOptionsPagePanels(layout, panels, kUiDecorPanelsPerOptionsPage);

            size_t requested = 0;
            size_t created = 0;
            for (size_t group = 0; group < panelCount; ++group)
            {
                UiDecorPiece pieces[kUiDecorMaxPanelPieces] = {};
                const size_t count =
                    BuildUiDecorPanel(panels[group], pieces, kUiDecorMaxPanelPieces);
                const size_t slotOffset = group * kUiDecorMaxPanelPieces;

                for (size_t index = 0; index < count; ++index)
                {
                    char controlName[96] = {};
                    std::snprintf(controlName,
                                  sizeof(controlName),
                                  "%s_%08X_%u_%02u",
                                  namePrefix,
                                  screenTag,
                                  static_cast<unsigned>(group),
                                  static_cast<unsigned>(index));
                    const UiDecorPiece& piece = pieces[index];
                    ++requested;
                    if (CreateInputBindingUiDecorPiece(slots[slotOffset + index],
                                                       controlParent,
                                                       controlName,
                                                       piece.texture,
                                                       piece.rect.x,
                                                       piece.rect.y,
                                                       piece.rect.width,
                                                       piece.rect.height))
                    {
                        ++created;
                    }
                }

                for (size_t index = count; index < kUiDecorMaxPanelPieces; ++index)
                    SetInputBindingUiViewActive(slots[slotOffset + index], false);
            }

            // An invisible frame is indistinguishable from one that was never
            // built, so record which of the two happened.
            Log(L"[INPUTUI] %hs decor panels=%u pieces=%u/%u\n",
                namePrefix,
                static_cast<unsigned>(panelCount),
                static_cast<unsigned>(created),
                static_cast<unsigned>(requested));
        }

        // Every OpenShim page draws the same stack: two masks that blank only
        // the bands the page actually writes into -- the header/toolbar band
        // and the row grid. Nothing full-bleed goes underneath them. The page
        // is parented to Middle_Overlay, which is the 4:3 centre of the screen
        // (measured 480,0,2880,2160 at 3840x2160), so a full-bleed blackout
        // here paints a black pillar over the middle three quarters of the
        // screen's own background art -- stock or a mod's custom background --
        // and leaves only the pillarboxes showing. Both masks are full-width
        // overlays on the screen itself; the panel frames go on the control
        // parent with the rest of the page. Both pages share this so their
        // backgrounds cannot drift apart.
        struct UiOptionsPageBackgroundSlots
        {
            void** topMask = nullptr;
            void** contentMask = nullptr;
        };

        static void CreateInputBindingUiPageBackground(
            const UiOptionsPageBackgroundSlots& slots,
            std::array<void*, kUiDecorMaxOptionsPagePieces>& decor,
            void* visualParent,
            void* controlParent,
            const char* namePrefix,
            unsigned screenTag,
            const UiOptionsPageLayout& layout)
        {
            if (!visualParent || !namePrefix)
                return;

            struct BackgroundLayer
            {
                void** slot;
                const char* suffix;
                const char* texture;
                UiDecorRect rect;
            };

            const BackgroundLayer layers[] =
            {
                { slots.topMask, "TopMask", "blackui.png", layout.topMask },
                { slots.contentMask, "ContentMask", "blackui.png", layout.contentMask },
            };
            // blackui.png is stock; if CustomWidgets tiles are missing we still want the
            // Settings page to be readable.

            char controlName[96] = {};
            for (const BackgroundLayer& layer : layers)
            {
                if (!layer.slot)
                    continue;
                std::snprintf(controlName, sizeof(controlName), "%s%s_%08X",
                              namePrefix, layer.suffix, screenTag);
                CreateInputBindingUiOverlay(*layer.slot,
                                            visualParent,
                                            controlName,
                                            layer.texture,
                                            layer.rect.x,
                                            layer.rect.y,
                                            layer.rect.width,
                                            layer.rect.height,
                                            0x60);
            }

            std::snprintf(controlName, sizeof(controlName), "%sDecor", namePrefix);
            CreateInputBindingUiPageDecor(decor, controlParent, controlName, screenTag, layout);
        }

        static bool SetInputBindingUiButtonText(void* button, const char* text)
        {
            if (!button || !g_BzrFn_SetButtonLabel)
                return false;

            g_BzrFn_SetButtonLabel(button, text ? text : "");
            return true;
        }

        // Injected text is not clipped by the engine: a string wider than its
        // widget spills over the neighbors. Labels get truncated with an
        // ellipsis; buttons first shrink their per-button text scale and only
        // then truncate. Widths come from the engine's own measure routine
        // when it verifies; the per-char estimates below remain the fallback
        // for byte drift or a not-yet-initialized font.
        constexpr float kInputBindingUiButtonCharWidth = 12.5f; // at text scale 1.0
        constexpr float kInputBindingUiLabelCharWidth = 11.0f;
        constexpr float kInputBindingUiButtonTextScale = 0.85f;
        constexpr float kInputBindingUiButtonTextMinScale = 0.60f;

        // Native text measurement, RE'd 2026-07-17 from the cUI_Text layout
        // path (SetText 0x7CC660 -> relayout 0x7CC750 -> text factory
        // 0x687DE0): 0x689AB0 walks the string against the global font
        // context, accumulating per-char advances at the current global char
        // size; the factory multiplies that char size by the per-text scale
        // before measuring and restores it afterwards, which is mirrored here.
        uint32_t g_UiTextMeasureAddr = 0;    // cdecl (font, text, &w, &h)
        uint32_t g_UiFontContextPtrAddr = 0; // global font the UI text uses
        uint32_t g_UiFontCharSizeXAddr = 0;  // global char-size floats read
        uint32_t g_UiFontCharSizeYAddr = 0;  // by the per-char advance calls

        typedef void(__cdecl* FnUiMeasureText)(void* font, const char* text,
                                               float* outWidth, float* outHeight);

        // POD-only for __try. Returns false whenever the native routine cannot
        // be trusted so callers fall back to the char-width estimates.
        static bool TryMeasureUiTextWidth(const char* text, float scale, float* outWidth)
        {
            static int s_measureState = 0; // 0=unchecked 1=usable -1=unavailable
            if (s_measureState == 0)
            {
                const HookEngine::EngineRow rows[] = {
                    { "UiTextMeasure", &g_UiTextMeasureAddr },
                    { "UiFontContext", &g_UiFontContextPtrAddr },
                    { "UiFontCharSizeX", &g_UiFontCharSizeXAddr },
                    { "UiFontCharSizeY", &g_UiFontCharSizeYAddr },
                };
                s_measureState = HookEngine::BindEngineRows("Native UI text measure", rows) ? 1 : -1;
                if (s_measureState < 0)
                    Log(L"[INPUTUI] Text measure rows do not bind; using char estimates\n");
            }
            if (s_measureState < 0 || !text || !outWidth || scale <= 0.0f)
                return false;

            float* const charSizeX = reinterpret_cast<float*>(g_UiFontCharSizeXAddr);
            float* const charSizeY = reinterpret_cast<float*>(g_UiFontCharSizeYAddr);
            float savedX = 0.0f;
            float savedY = 0.0f;
            bool scaled = false;
            __try
            {
                void* const font = *reinterpret_cast<void**>(g_UiFontContextPtrAddr);
                if (!font)
                    return false;

                savedX = *charSizeX;
                savedY = *charSizeY;
                if (savedX <= 0.0f || savedY <= 0.0f)
                    return false;
                *charSizeX = savedX * scale;
                *charSizeY = savedY * scale;
                scaled = true;
                float width = 0.0f;
                float height = 0.0f;
                reinterpret_cast<FnUiMeasureText>(g_UiTextMeasureAddr)(font, text, &width, &height);
                *charSizeX = savedX;
                *charSizeY = savedY;
                scaled = false;
                if (width < 0.0f || width > 65536.0f)
                    return false;
                // The engine measures with the global char sizes, which track
                // the render resolution (screen pixels), while every width this
                // file works in is the fixed 1080-tall logical UI space. At 4K
                // the raw measure comes back 2x the rendered logical width and
                // over-truncates ("Attack Al..."), verified in-game 2026-07-17.
                // Normalize by the display height; the game renders fullscreen.
                const int screenH = GetSystemMetrics(SM_CYSCREEN);
                if (screenH > 1080)
                    width = width * 1080.0f / static_cast<float>(screenH);
                *outWidth = width;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                // The globals live in .data; restoring them cannot fault even
                // though the measure call just did.
                if (scaled)
                {
                    *charSizeX = savedX;
                    *charSizeY = savedY;
                }
            }
            return false;
        }

        static std::string ClampInputBindingUiText(const char* text, size_t maxChars)
        {
            std::string value = text ? text : "";
            if (maxChars >= 4 && value.size() > maxChars)
            {
                value.resize(maxChars - 3);
                value += "...";
            }
            return value;
        }

        // Ellipsis-truncates using native measurement, or the historical
        // estimate when measurement is unavailable.
        static std::string FitUiTextToWidth(const char* text,
                                            float widthPx,
                                            float scale,
                                            float estimateCharWidth)
        {
            std::string value = text ? text : "";
            float width = 0.0f;
            if (!TryMeasureUiTextWidth(value.c_str(), scale, &width))
                return ClampInputBindingUiText(
                    text, static_cast<size_t>(widthPx / (estimateCharWidth * scale)));

            if (width <= widthPx || value.size() <= 4)
                return value;

            while (value.size() > 1)
            {
                value.pop_back();
                const std::string candidate = value + "...";
                if (!TryMeasureUiTextWidth(candidate.c_str(), scale, &width))
                    return candidate;
                if (width <= widthPx)
                    return candidate;
            }
            return value + "...";
        }

        static bool UiTextFitsWidth(const std::string& text,
                                    float widthPx,
                                    float scale,
                                    float estimateCharWidth)
        {
            float measuredWidth = 0.0f;
            if (TryMeasureUiTextWidth(text.c_str(), scale, &measuredWidth))
                return measuredWidth <= widthPx;
            return estimateCharWidth * scale * static_cast<float>(text.size()) <= widthPx;
        }

        static std::pair<std::string, std::string> WrapUiTextToTwoLines(const char* text,
                                                                        float widthPx)
        {
            std::string value = TrimAsciiCopy(text ? text : "");
            if (value.empty() || UiTextFitsWidth(value,
                                                widthPx,
                                                1.0f,
                                                kInputBindingUiLabelCharWidth))
            {
                return { value, {} };
            }

            size_t bestBreak = std::string::npos;
            for (size_t index = 0; index < value.size(); ++index)
            {
                if (value[index] != ' ' && value[index] != '\t')
                    continue;
                const std::string candidate = value.substr(0, index);
                if (!UiTextFitsWidth(candidate,
                                     widthPx,
                                     1.0f,
                                     kInputBindingUiLabelCharWidth))
                {
                    break;
                }
                bestBreak = index;
            }

            if (bestBreak == std::string::npos)
            {
                bestBreak = 1;
                while (bestBreak < value.size() &&
                       UiTextFitsWidth(value.substr(0, bestBreak + 1),
                                       widthPx,
                                       1.0f,
                                       kInputBindingUiLabelCharWidth))
                {
                    ++bestBreak;
                }
            }

            std::string first = TrimAsciiCopy(value.substr(0, bestBreak));
            std::string second = TrimAsciiCopy(value.substr(bestBreak));
            if (!UiTextFitsWidth(second,
                                 widthPx,
                                 1.0f,
                                 kInputBindingUiLabelCharWidth))
            {
                second = FitUiTextToWidth(second.c_str(),
                                          widthPx,
                                          1.0f,
                                          kInputBindingUiLabelCharWidth);
            }
            return { std::move(first), std::move(second) };
        }

        static bool SetInputBindingUiWrappedLabelText(void* firstLabel,
                                                      void* secondLabel,
                                                      const char* text,
                                                      float widthPx)
        {
            const auto lines = WrapUiTextToTwoLines(text, widthPx);
            const bool firstUpdated = SetInputBindingUiLabelText(firstLabel, lines.first.c_str());
            const bool secondUpdated = SetInputBindingUiLabelText(secondLabel, lines.second.c_str());
            return firstUpdated && secondUpdated;
        }

        static bool SetInputBindingUiLabelTextFitted(void* label, const char* text, float widthPx)
        {
            return SetInputBindingUiLabelText(
                label,
                FitUiTextToWidth(text, widthPx, 1.0f, kInputBindingUiLabelCharWidth).c_str());
        }

        static bool SetInputBindingUiButtonTextFitted(void* button, const char* text, float widthPx)
        {
            if (!button)
                return false;

            std::string value = text ? text : "";
            float scale = kInputBindingUiButtonTextScale;
            if (!value.empty())
            {
                float naturalWidth = 0.0f;
                if (TryMeasureUiTextWidth(value.c_str(), 1.0f, &naturalWidth) &&
                    naturalWidth > 0.0f)
                {
                    // Advance scales linearly with the global char size, so the
                    // width at scale s is naturalWidth * s.
                    const float fitScale = widthPx / naturalWidth;
                    scale = (std::min)(kInputBindingUiButtonTextScale, fitScale);
                    if (scale < kInputBindingUiButtonTextMinScale)
                    {
                        scale = kInputBindingUiButtonTextMinScale;
                        value = FitUiTextToWidth(value.c_str(), widthPx, scale,
                                                 kInputBindingUiButtonCharWidth);
                    }
                }
                else
                {
                    const float fitScale =
                        widthPx / (kInputBindingUiButtonCharWidth * static_cast<float>(value.size()));
                    scale = (std::min)(kInputBindingUiButtonTextScale, fitScale);
                    if (scale < kInputBindingUiButtonTextMinScale)
                    {
                        scale = kInputBindingUiButtonTextMinScale;
                        const size_t maxChars = static_cast<size_t>(
                            widthPx / (kInputBindingUiButtonCharWidth * scale));
                        value = ClampInputBindingUiText(value.c_str(), maxChars);
                    }
                }
            }

            if (!SetInputBindingUiButtonText(button, value.c_str()))
                return false;
            if (g_BzrFn_SetButtonTextScale)
                g_BzrFn_SetButtonTextScale(button, scale);
            return true;
        }

        static void* GetInputBindingUiViewParent(void* view)
        {
            if (!view)
                return nullptr;

            auto* viewBytes = reinterpret_cast<uint8_t*>(view);
            return *reinterpret_cast<void**>(viewBytes + 0x13C);
        }

        static void SetInputBindingUiViewActive(void* view, bool active)
        {
            if (!view || !g_BzrFn_UiSetActive)
                return;

            g_BzrFn_UiSetActive(view, active ? 1 : 0);
        }

        static void* ResolveStockOptionsInputMiddleOverlay(void* screen)
        {
            if (!screen)
                return nullptr;

            auto* screenWords = reinterpret_cast<void**>(screen);
            static constexpr size_t kDirectOverlayLabelOffsets[] = { 0x5D, 0x5E };
            for (size_t wordOffset : kDirectOverlayLabelOffsets)
            {
                void* const label = screenWords[wordOffset];
                void* const parent = GetInputBindingUiViewParent(label);
                if (parent)
                    return parent;
            }

            static constexpr size_t kKeyLabelOffsets[] =
            {
                0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C
            };
            for (size_t wordOffset : kKeyLabelOffsets)
            {
                void* const label = screenWords[wordOffset];
                void* const button = GetInputBindingUiViewParent(label);
                void* const parent = GetInputBindingUiViewParent(button);
                if (parent)
                    return parent;
            }

            return nullptr;
        }

        static void ReplaceInputBindingUiSubstring(std::string& text,
                                                   const char* oldText,
                                                   const char* newText)
        {
            if (!oldText || !*oldText)
                return;

            const std::string from(oldText);
            const std::string to = newText ? std::string(newText) : std::string();
            size_t position = 0;
            while ((position = text.find(from, position)) != std::string::npos)
            {
                text.replace(position, from.size(), to);
                position += to.size();
            }
        }

        static std::string CompactInputBindingUiValueText(std::string value)
        {
            ReplaceInputBindingUiSubstring(value, "program ", "");
            ReplaceInputBindingUiSubstring(value, "mouse ", "Mouse ");
            ReplaceInputBindingUiSubstring(value, "joystick ", "Joystick ");
            ReplaceInputBindingUiSubstring(value, "LeftBtn", "Left");
            ReplaceInputBindingUiSubstring(value, "RightBtn", "Right");
            ReplaceInputBindingUiSubstring(value, "MiddleBtn", "Middle");
            ReplaceInputBindingUiSubstring(value, "HorizPos", "X Axis");
            ReplaceInputBindingUiSubstring(value, "VertPos", "Y Axis");
            ReplaceInputBindingUiSubstring(value, "HorizVel", "X Delta");
            ReplaceInputBindingUiSubstring(value, "VertVel", "Y Delta");
            ReplaceInputBindingUiSubstring(value, "Mouse Left", "LMB");
            ReplaceInputBindingUiSubstring(value, "Mouse Right", "RMB");
            ReplaceInputBindingUiSubstring(value, "Mouse Middle", "MMB");
            ReplaceInputBindingUiSubstring(value, "KeypadEnter", "Num Enter");
            ReplaceInputBindingUiSubstring(value, "LeftControl", "Ctrl");
            ReplaceInputBindingUiSubstring(value, "RightControl", "Ctrl");
            ReplaceInputBindingUiSubstring(value, "LeftShift", "Shift");
            ReplaceInputBindingUiSubstring(value, "RightShift", "Shift");
            ReplaceInputBindingUiSubstring(value, ", ", " / ");
            return value;
        }

        static std::string GetInputBindingUiRowLabelText(const InputBindingUiRow& row)
        {
            std::string label =
                row.displayText.empty() ? HumanizeInputBindingCommand(row.command) : row.displayText;

            // The stock typeface is intentionally wide. Keep the uncommon debug
            // actions readable without letting their captions run into the value
            // buttons in the compact two-column layout.
            static const std::pair<const char*, const char*> kFriendlyLabels[] =
            {
                { "Toggle Netdebug", "Network Debug" },
                { "Mono Debug Toggle", "Debug Overlay" },
                { "Mono Debug Next Screen", "Debug: Next Screen" },
                { "Mono Debug Prev Screen", "Debug: Prev Screen" },
                { "Mono Debug Page Up", "Debug: Page Up" },
                { "Mono Debug Page Down", "Debug: Page Down" },
                { "Toggle Info Display", "Info Display" },
                { "Toggle Objectives Display", "Objectives Display" },
                { "Toggle Editmode", "Editor Mode" },
            };
            for (const auto& replacement : kFriendlyLabels)
            {
                if (_stricmp(label.c_str(), replacement.first) == 0)
                    return replacement.second;
            }
            return label;
        }

        static std::string GetInputBindingUiRowValueText(const InputBindingUiRow& row)
        {
            if (IsInputBindingUiPending(row))
                return "[Press key]";

            std::string value = row.currentBindingText.empty() ? "Unassigned" : row.currentBindingText;
            return CompactInputBindingUiValueText(std::move(value));
        }

        static void SuppressStockOptionsInputWidgets(void* screen)
        {
            if (!screen)
                return;

            static constexpr size_t kStockLabelWordOffsets[] =
            {
                0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E
            };

            auto* screenWords = reinterpret_cast<void**>(screen);
            for (size_t wordOffset : kStockLabelWordOffsets)
            {
                void* const label = screenWords[wordOffset];
                if (!label)
                    continue;

                SetInputBindingUiLabelText(label, "");
                SetInputBindingUiViewActive(label, false);

                if (wordOffset >= 0x51 && wordOffset <= 0x5C)
                {
                    void* const button = GetInputBindingUiViewParent(label);
                    if (button)
                    {
                        auto* buttonBytes = reinterpret_cast<uint8_t*>(button);
                        void* const buttonCaption = *reinterpret_cast<void**>(buttonBytes + 0x144);
                        SetInputBindingUiLabelText(buttonCaption, "");
                        SetInputBindingUiViewActive(buttonCaption, false);
                    }
                    SetInputBindingUiViewActive(button, false);
                }
            }
        }

        // The stock Default ("Reset Default") and Joystick buttons are ctor
        // locals of cUI_OptionsInput, not screen members, so they are found by
        // walking a view's child vector for the button whose +0x154 click slot
        // holds the known stock thunk. POD-only + SEH: the walk reads engine
        // heap structures that this code does not own.
        static void* FindStockOptionsInputButtonByClick(void* container, uintptr_t clickThunk)
        {
            __try
            {
                if (!container)
                    return nullptr;

                auto* const containerBytes = reinterpret_cast<uint8_t*>(container);
                void** const begin =
                    *reinterpret_cast<void***>(containerBytes + kUiViewChildBeginOffset);
                void** const end =
                    *reinterpret_cast<void***>(containerBytes + kUiViewChildEndOffset);
                if (!begin || !end || begin >= end || (end - begin) > 128)
                    return nullptr;

                for (void** child = begin; child != end; ++child)
                {
                    if (!*child)
                        continue;
                    auto* const childBytes = reinterpret_cast<uint8_t*>(*child);
                    const uintptr_t onClick =
                        *reinterpret_cast<uintptr_t*>(childBytes + kUiButtonOnClickOffset);
                    if (onClick == clickThunk)
                        return *child;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
            return nullptr;
        }

        static void* GetStockOptionsInputButtonCaption(void* button)
        {
            __try
            {
                if (!button)
                    return nullptr;
                return *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(button) + 0x144);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        // A button's caption label (+0x144) renders its text regardless of the
        // active flag (same reason SuppressStockOptionsInputWidgets blanks the
        // stock labels), so hiding blanks the caption and showing restores it.
        static void SetStockOptionsInputButtonActive(void* button, bool active, const char* restoreCaption)
        {
            if (!button)
                return;

            void* const caption = GetStockOptionsInputButtonCaption(button);
            if (!active)
                SetInputBindingUiLabelText(caption, "");
            else if (restoreCaption && g_BzrFn_SetButtonLabel)
                g_BzrFn_SetButtonLabel(button, restoreCaption);
            SetInputBindingUiViewActive(caption, active);
            SetInputBindingUiViewActive(button, active);
        }

        // Default duplicates our "Reset Controls" (and silently resets keybinds
        // if clicked from the settings page), so it hides on both pages. The
        // Joystick page has no replacement, so its button stays on the binding
        // page and only hides on the settings page.
        static void SetStockOptionsInputAccessoryVisibility(void* screen, bool showJoystick)
        {
            if (!screen)
                return;

            void* const overlay = ResolveStockOptionsInputMiddleOverlay(screen);
            void* defaultsButton =
                FindStockOptionsInputButtonByClick(overlay, g_OptionsInputDefaultsClickAddr);
            if (!defaultsButton)
                defaultsButton =
                    FindStockOptionsInputButtonByClick(screen, g_OptionsInputDefaultsClickAddr);
            SetStockOptionsInputButtonActive(defaultsButton, false, nullptr);

            void* joystickButton =
                FindStockOptionsInputButtonByClick(screen, g_OptionsInputJoystickClickAddr);
            if (!joystickButton)
                joystickButton =
                    FindStockOptionsInputButtonByClick(overlay, g_OptionsInputJoystickClickAddr);
            SetStockOptionsInputButtonActive(joystickButton, showJoystick, "Joystick");
        }

        static void RefreshInputBindingUiControls()
        {
            void* const decoratedScreen = g_InputScreenBinding.decorated;
            if (!decoratedScreen)
                return;

            g_InputBindingUiPageStart =
                ClampInputBindingUiPageStart(g_InputBindingUiActiveFamily, g_InputBindingUiPageStart);

            const size_t totalRows = GetInputBindingUiRowCountForFamily(g_InputBindingUiActiveFamily);
            const size_t pageNumber = (g_InputBindingUiPageStart / kInputBindingUiVisibleRowCount) + 1;
            const size_t pageCount =
                totalRows == 0 ? 1 : ((totalRows - 1) / kInputBindingUiVisibleRowCount) + 1;

            // Painted mode puts the header in the title plate, which holds a
            // short title; the active family shows on its toolbar button.
            const char* headerText =
                g_InputBindingUiPainted ? "KEY BINDINGS"
                : g_InputBindingUiActiveFamily == InputBindingMapFamily::GameKey
                    ? "RTS & Game Actions"
                    : "Movement & Vehicle Controls";

            const UiOptionsPageLayout layout = GetInputBindingUiLayout();

            SetInputBindingUiLabelTextFitted(g_InputBindingUiHeaderLabel, headerText,
                                             layout.headerTextWidth);
            SetInputBindingUiWrappedLabelText(g_InputBindingUiStatusLabel,
                                              g_InputBindingUiStatusDetailLabel,
                                              g_InputBindingUiStatusText.c_str(),
                                              layout.headerTextWidth);
            SuppressStockOptionsInputWidgets(decoratedScreen);
            SetStockOptionsInputAccessoryVisibility(decoratedScreen, true);

            SetInputBindingUiButtonTextFitted(
                g_InputBindingUiInputFamilyButton,
                g_InputBindingUiActiveFamily == InputBindingMapFamily::Input ? "> Controls <" : "Controls",
                kInputBindingUiToolbarWidths[2] - kUiToolbarCaptionPadding);
            SetInputBindingUiButtonTextFitted(
                g_InputBindingUiGameKeyFamilyButton,
                g_InputBindingUiActiveFamily == InputBindingMapFamily::GameKey ? "> RTS Actions <" : "RTS Actions",
                kInputBindingUiToolbarWidths[3] - kUiToolbarCaptionPadding);

            g_InputBindingUiVisibleRowIndices.fill(-1);
            size_t matchingIndex = 0;
            size_t visibleIndex = 0;
            for (size_t rowIndex = 0;
                 rowIndex < g_InputBindingUiRows.size() && visibleIndex < kInputBindingUiVisibleRowCount;
                 ++rowIndex)
            {
                const InputBindingUiRow& row = g_InputBindingUiRows[rowIndex];
                if (row.family != g_InputBindingUiActiveFamily)
                    continue;
                if (matchingIndex++ < g_InputBindingUiPageStart)
                    continue;

                g_InputBindingUiVisibleRowIndices[visibleIndex] = static_cast<int>(rowIndex);
                ++visibleIndex;
            }

            std::string sectionSummary;
            if (g_InputBindingUiActiveFamily == InputBindingMapFamily::Input)
            {
                std::string firstSection;
                std::string lastSection;
                for (size_t slot = 0; slot < visibleIndex; ++slot)
                {
                    const int rowIndex = g_InputBindingUiVisibleRowIndices[slot];
                    if (rowIndex < 0 || static_cast<size_t>(rowIndex) >= g_InputBindingUiRows.size())
                        continue;

                    const std::string& sectionName =
                        g_InputBindingUiRows[static_cast<size_t>(rowIndex)].sectionName;
                    if (sectionName.empty())
                        continue;

                    if (firstSection.empty())
                        firstSection = sectionName;
                    lastSection = sectionName;
                }

                if (!firstSection.empty())
                {
                    sectionSummary = firstSection;
                    if (_stricmp(firstSection.c_str(), lastSection.c_str()) != 0)
                    {
                        sectionSummary += " -> ";
                        sectionSummary += lastSection;
                    }
                }
            }

            char pageText[256] = {};
            if (!sectionSummary.empty())
            {
                std::snprintf(pageText,
                              sizeof(pageText),
                              "Page %u of %u  -  %u actions  -  %s",
                              static_cast<unsigned>(pageNumber),
                              static_cast<unsigned>(pageCount),
                              static_cast<unsigned>(totalRows),
                              sectionSummary.c_str());
            }
            else
            {
                std::snprintf(pageText,
                              sizeof(pageText),
                              "Page %u of %u  -  %u actions",
                              static_cast<unsigned>(pageNumber),
                              static_cast<unsigned>(pageCount),
                              static_cast<unsigned>(totalRows));
            }
            SetInputBindingUiLabelTextFitted(g_InputBindingUiPageLabel, pageText,
                                             layout.headerTextWidth);

            for (size_t slot = 0; slot < kInputBindingUiVisibleRowCount; ++slot)
            {
                const int rowIndex = g_InputBindingUiVisibleRowIndices[slot];
                if (rowIndex < 0 || static_cast<size_t>(rowIndex) >= g_InputBindingUiRows.size())
                {
                    SetInputBindingUiLabelText(g_InputBindingUiRowLabels[slot], "");
                    SetInputBindingUiButtonText(g_InputBindingUiRowButtons[slot], "");
                    SetInputBindingUiViewActive(g_InputBindingUiRowLabels[slot], false);
                    SetInputBindingUiViewActive(g_InputBindingUiRowButtons[slot], false);
                    SetInputBindingUiViewActive(g_InputBindingUiRowBackdrops[slot], false);
                    continue;
                }

                const InputBindingUiRow& row = g_InputBindingUiRows[static_cast<size_t>(rowIndex)];
                const std::string labelText = GetInputBindingUiRowLabelText(row);
                const std::string buttonText = GetInputBindingUiRowValueText(row);
                SetInputBindingUiLabelTextFitted(g_InputBindingUiRowLabels[slot], labelText.c_str(),
                                                 layout.rowLabelTextWidth);
                SetInputBindingUiButtonTextFitted(g_InputBindingUiRowButtons[slot], buttonText.c_str(),
                                                  layout.rowValueTextWidth);
                SetInputBindingUiViewActive(g_InputBindingUiRowLabels[slot], true);
                SetInputBindingUiViewActive(g_InputBindingUiRowButtons[slot], true);
                SetInputBindingUiViewActive(g_InputBindingUiRowBackdrops[slot], true);
            }
        }

        // --- OpenShim settings page implementation ------------------------------

        static bool ShouldEnableShimSettingsUi()
        {
            static int s_cached = -1;
            if (s_cached < 0)
            {
                bool enabled = true;
                bool configured = false;
                if (TryGetUserConfigBool("General", "SettingsUi", configured))
                    enabled = configured;
                const bool disabled =
                    EnvFlagEnabled("OPENSHIM_DISABLE_SETTINGS_UI") ||
                    EnvFlagEnabled("BZR_DISABLE_SETTINGS_UI");
                s_cached = (enabled && !disabled) ? 1 : 0;
            }
            return s_cached != 0;
        }

        // Lossless openshim.ini value write: only the matched "Key = value" line
        // changes; comments, blank lines, ordering, and unrelated keys survive
        // verbatim. Missing keys are appended at the end of their section and a
        // missing section (or file) is created. Same atomic temp/backup/replace
        // path as the input.map writer.
        static bool WriteUserConfigValueLossless(const char* section,
                                                 const char* key,
                                                 const char* const* altKeys,
                                                 size_t altKeyCount,
                                                 const char* value,
                                                 std::string& outError)
        {
            outError.clear();
            const auto path = GetUserConfigPath();
            if (path.empty())
            {
                outError = "config directory unavailable";
                return false;
            }

            // The lossless document-update logic lives in openshim_ini.cpp so
            // it can be unit-tested without the engine (tests/ini_writer_tests).
            InputBindingDocument document;
            document.loaded = true;
            document.lines = ReadTextFileLines(path);
            UpdateIniDocumentValueLossless(document.lines, section, key,
                                           altKeys, altKeyCount, value);

            if (!WriteInputBindingDocumentAtomic(path, document, outError))
                return false;

            Log(L"[SETTINGSUI] Wrote %hs [%hs] %hs = %hs\n",
                kUserConfigFileName, section, key, value);
            return true;
        }


        struct ShimSettingDescriptor
        {
            const char* label;         // row label in the UI
            const char* section;       // openshim.ini section
            const char* key;           // canonical ini key
            const char* const* altKeys;  // legacy key aliases replaced in-place
            size_t altKeyCount;
            const char* const* values;      // ini value written per option
            const char* const* valueLabels; // display text per option
            size_t valueCount;
            size_t defaultIndex;       // shown when the key is absent/invalid
            ShimSettingApplyGroup applyGroup;
            const char* description;   // one sentence shown in the status label on hover
        };

        static const char* const kShimSettingsOnOffValues[] = { "1", "0" };
        // Action-row "values" are confirmation states, not settings. Index 0 is
        // the resting cell, index 1 is what an armed row shows.
        static const char* const kShimSettingsActionValues[] = { "Reset", "Confirm?" };
        static const char* const kShimSettingsOnOffLabels[] = { "On", "Off" };
        static const char* const kShimSettingsAutoSaveIntervalValues[] = { "60", "120", "180", "300", "600" };
        static const char* const kShimSettingsAutoSaveIntervalLabels[] = { "1 min", "2 min", "3 min", "5 min", "10 min" };
        static const char* const kShimSettingsUnderAttackValues[] = { "Normal", "Minimal", "None" };
        static const char* const kShimSettingsUnitVoValues[] = { "Normal", "Reduced", "None" };
        static const char* const kShimSettingsTargetPolicyValues[] = { "Default", "NeutralOnly", "ExplicitOnly" };
        static const char* const kShimSettingsTargetPolicyLabels[] = { "Default", "Neutral Only", "Explicit Only" };
        static const char* const kShimSettingsScrapHudValues[] = { "Legacy", "Stock" };
        static const char* const kShimSettingsRadarScaleValues[] =
            { "1.0", "1.25", "1.5", "1.75", "2.0" };
        static const char* const kShimSettingsRadarScaleLabels[] =
            { "Stock", "125%", "150%", "175%", "200%" };
        static const char* const kShimSettingsSatelliteValues[] =
            { "1.0", "1.5", "2.0", "3.0" };
        static const char* const kShimSettingsSatelliteLabels[] =
            { "Stock", "1.5x", "2x", "3x" };
        static const char* const kShimSettingsHeadlightColorValues[] =
        {
            "Stock", "White", "Red", "Green", "Blue", "Yellow",
            "Cyan", "Magenta", "Orange", "Purple", "Teal", "Rainbow"
        };
        static const char* const kShimSettingsHeadlightBeamValues[] = { "Stock", "Focused", "Wide" };
        static const char* const kShimSettingsHeadlightBrightnessValues[] =
            { "0.50", "0.75", "1.00", "1.25", "1.50" };
        static const char* const kShimSettingsHeadlightBrightnessLabels[] =
            { "50%", "75%", "100%", "125%", "150%" };
        static const char* const kShimSettingsNetRouteValues[] = { "Stock", "Direct", "Relay" };
        static const char* const kShimSettingsGovernorTuningValues[] = { "OpenShim", "Stock" };
        static const char* const kShimSettingsNetRouteLabels[] = { "Stock", "Prefer Direct", "Force Relay" };
        static const char* const kShimSettingsTargetPolicyAltKeys[] = { "TargetReticle" };
        static const char* const kShimSettingsReticleConvAltKeys[] = { "SmartReticleConvergence" };
        static const char* const kShimSettingsScavengerAltKeys[] = { "ScavengerPathing" };
        static const char* const kShimSettingsBindsUiAltKeys[] = { "CustomBindingUi" };
        static const char* const kShimSettingsRenderProfileValues[] = { "Retro", "Redux", "Enhanced" };
        // 0 disables the override and leaves the stock engine limit alone; the
        // runtime clamps anything above 256, so 256 is the top of the ladder.
        static const char* const kShimSettingsSoundChannelValues[] = { "0", "64", "128", "192", "256" };
        static const char* const kShimSettingsSoundChannelLabels[] = { "Stock", "64", "128", "192", "256" };
        // Redux ships 200. The runtime accepts any finite value in 1..10000
        // from a hand-edited ini; these are the presets the page cycles.
        static const char* const kShimSettingsReticleRangeValues[] = { "200", "300", "400", "500" };
        static const char* const kShimSettingsReticleRangeLabels[] = { "Stock", "300", "400", "500" };

        static const ShimSettingDescriptor g_ShimSettingsRegistry[] =
        {
            // Deliberately NO Renderer (DX9/DX11) row: the runtime only parses
            // the [Graphics] Renderer preference and reports requested-vs-
            // effective divergence; it does not yet steer which render system
            // the game starts on. Exposing it as a restart-required selector
            // would promise a control that cannot deliver, so the row stays
            // hidden until startup renderer selection is actually implemented
            // (hand-edited openshim.ini values remain parsed and reported).
            { "Render Profile", "Graphics", "RenderProfile", nullptr, 0,
              kShimSettingsRenderProfileValues, kShimSettingsRenderProfileValues, 3, 1,
              ShimSettingApplyGroup::RenderProfile,
              "Visual rendering policy: Redux (stock baseline), Enhanced, or Retro. Applies live." },
            // [DX11Enhanced] is the experimental DX11 pipeline. Both rows fail
            // closed when the key is absent, which is what keeps an install
            // that never opted into this ini on the stock path; the shipped
            // openshim.ini opts in explicitly.
            { "DX11 FXAA", "DX11Enhanced", "FXAA", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
              ShimSettingApplyGroup::RestartRequired,
              "FXAA 3.11 anti-aliasing pass on the DX11 Enhanced pipeline. DX11 only. Restart required." },
            { "DX11 Local Lights", "DX11Enhanced", "EnhancedLightSelectionV2", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::RestartRequired,
              "Contribution-ranked per-object local-light ordering. DX11 only. Restart required." },
            { "Sun Flashbang", "Display", "SunFlashbang", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::LiveEngineToggle,
              "On is stock: looking near the sun paints a fullscreen white flash. Off suppresses only that flash." },
            { "Attack Alert", "Display", "UnderAttackAlert", nullptr, 0,
              kShimSettingsUnderAttackValues, kShimSettingsUnderAttackValues, 3, 0,
              ShimSettingApplyGroup::UnderAttackAlert,
              "Under-attack warning style: Normal, Minimal (quieter), or None." },
            { "Hop-Out Alert Fix", "General", "SuppressHopOutAttackAlert", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
              ShimSettingApplyGroup::LiveEngineToggle,
              "Suppress the stale under-attack growl that fires the instant you hop out. Audio only." },
            { "Target Popup", "Display", "TargetPolicy",
              kShimSettingsTargetPolicyAltKeys, 1,
              kShimSettingsTargetPolicyValues, kShimSettingsTargetPolicyLabels, 3, 0,
              ShimSettingApplyGroup::TargetReticle,
              "When the reticle target popup appears: always, neutral objects only, or explicit targets only." },
            { "Scrap/Pilot HUD", "Display", "ScrapPilotHud", nullptr, 0,
              kShimSettingsScrapHudValues, kShimSettingsScrapHudValues, 2, 0,
              ShimSettingApplyGroup::GlobalImprovement,
              "Legacy BZ98-style scrap and pilot readout, or the stock Redux HUD." },
            // Local HUD geometry, so this one is not single-player only.
            { "Radar Size", "Display", "RadarSizeScale", nullptr, 0,
              kShimSettingsRadarScaleValues, kShimSettingsRadarScaleLabels, 5, 0,
              ShimSettingApplyGroup::GlobalImprovement,
              "Scale the cockpit radar. The projection re-anchors to the backdrop so the "
              "mesh and its underlay stay concentric." },
            { "Satellite Zoom Out", "SinglePlayer", "SatelliteZoomOut", nullptr, 0,
              kShimSettingsSatelliteValues, kShimSettingsSatelliteLabels, 4, 0,
              ShimSettingApplyGroup::GlobalImprovement,
              "How much further than stock the satellite view can pull out. Single player only." },
            { "Satellite Pan Speed", "SinglePlayer", "SatellitePanSpeed", nullptr, 0,
              kShimSettingsSatelliteValues, kShimSettingsSatelliteLabels, 4, 0,
              ShimSettingApplyGroup::GlobalImprovement,
              "Satellite view pan speed, as a multiple of stock. Single player only." },
            { "Jet Flames", "Display", "JetFlames", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
              ShimSettingApplyGroup::JetFlames,
              "Faction-colored engine flames on jets and thrusters." },
            { "Empty Craft Lights", "Display", "EmptyCraftLights", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
              ShimSettingApplyGroup::LiveEngineToggle,
              "Keep emissive running lights lit on craft that have no pilot." },
            { "Emissive Pulse", "Display", "EmissivePulse", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
              ShimSettingApplyGroup::LiveEngineToggle,
              "Vary occupied-craft emissive brightness with asynchronous organic pulses." },
            { "Star Twinkle", "Display", "StarTwinkle", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
              ShimSettingApplyGroup::LiveEngineToggle,
              "Animate brightness variation in compatible star-sky materials." },
            { "Unit Voices", "Display", "UnitVoFeedback", nullptr, 0,
              kShimSettingsUnitVoValues, kShimSettingsUnitVoValues, 3, 0,
              ShimSettingApplyGroup::UnitVo,
              "Unit voice feedback: Normal, Reduced chatter, or None." },
            { "MP Vehicle Flags", "Display", "MultiplayerFlags", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
              ShimSettingApplyGroup::RestartRequired,
              "Multiplayer vehicle flags: the selection screen and the in-match renderer. "
              "Leave off for BZP/BZP-T; their waiting room is faction-only. Restart required." },
            { "Show Own MP Flag", "Display", "MultiplayerFlagShowOwnCraft", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
              ShimSettingApplyGroup::RestartRequired,
              "Also draw your own flag over your own craft; stock draws only other players'. Restart required." },
            { "Death Chunk Meshes", "General", "ChunkMeshes", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::RestartRequired,
              "Generate destruction pieces from the model's mesh and skeleton. Restart required." },
            { "Sound Channels", "General", "SoundChannels", nullptr, 0,
              kShimSettingsSoundChannelValues, kShimSettingsSoundChannelLabels, 5, 4,
              ShimSettingApplyGroup::RestartRequired,
              "Simultaneous sound objects. Stock leaves the engine limit alone; 256 is the ceiling. Restart required." },
            { "Background Music", "General", "MusicGlobalFocus", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::RestartRequired,
              "Keep the soundtrack playing and fed while the game is not the foreground window. Restart required." },
            { "Custom Keybinds", "General", "CustomBindsUi",
              kShimSettingsBindsUiAltKeys, 1,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::RestartRequired,
              "Key-binding editor on the Input options page. Restart required." },
            { "Raw Mouse Input", "General", "RawMouseInput", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
              ShimSettingApplyGroup::RestartRequired,
              "Reads the mouse as raw input, bypassing Windows pointer acceleration. Does not remove aim smoothing; see Unsmoothed Controls. Restart required." },
            { "Unsmoothed Controls", "General", "DisableControlSmoothing", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
              ShimSettingApplyGroup::RestartRequired,
              "Steer, aim, throttle and strafe follow input directly instead of easing toward it, like BZ2's Control Smoothing Off. Affects mouse, keys and joystick. Restart required." },
            { "Material Guard", "General", "OgreMaterialCollisionGuard", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::RestartRequired,
              "Survive duplicate Ogre material declarations that otherwise terminate the game. Restart required." },
            { "Map List Fixes", "General", "MapRefreshFixes", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::RestartRequired,
              "Multiplayer map-list refresh and selection-preservation fixes. Restart required." },
            { "Map Filters+", "General", "MapFilterExtras", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
              ShimSettingApplyGroup::RestartRequired,
              "Create Game map list: 5+ Players and Stock Maps filters, plus a search box. Restart required." },
            { "Editor Placement", "General", "EditorOverheadPlacementOrder", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::RestartRequired,
              "BZ 1.5 view order so object placement works in the running overhead view. Needs /edit. Restart required." },
            { "AutoSave", "AutoSave", "Enabled", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::AutoSave,
              "Rolling recovery save for single-player missions; manual saves remain your checkpoints." },
            { "AutoSave Interval", "AutoSave", "IntervalSeconds", nullptr, 0,
              kShimSettingsAutoSaveIntervalValues, kShimSettingsAutoSaveIntervalLabels, 5, 1,
              ShimSettingApplyGroup::AutoSave,
              "How often OpenShim refreshes the rolling AutoSave recovery slot." },
            { "Weapon Convergence", "SinglePlayer", "WeaponConvergence", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::GlobalImprovement,
              "Walker-style convergence on an explicitly targeted craft. Single player only." },
            { "Reticle Convergence", "SinglePlayer", "PlayerReticleConvergence",
              kShimSettingsReticleConvAltKeys, 1,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::GlobalImprovement,
              "Same convergence, but toward the smart-reticle world point; no target lock required. Single player only." },
            { "Reticle Range", "SinglePlayer", "SmartReticleRange", nullptr, 0,
              kShimSettingsReticleRangeValues, kShimSettingsReticleRangeLabels, 4, 3,
              ShimSettingApplyGroup::GlobalImprovement,
              "Smart-reticle targeting distance; Stock is Redux's 200. OpenShim's own "
              "value is single-player only. A mission that calls EXU SetReticleRange "
              "(BZP, Reloaded) is honored in network games too." },
            { "Smart Scavengers", "SinglePlayer", "SmartScavengerPathing",
              kShimSettingsScavengerAltKeys, 1,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::GlobalImprovement,
              "Smarter scavenger pathing to scrap. Single player only." },
            { "Turret AA Pitch", "SinglePlayer", "TurretAimPitch", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::GlobalImprovement,
              "Turrets pitch up to engage air targets. Single player only." },
            { "Jump-Snipe Crouch", "SinglePlayer", "JumpSnipeCrouch", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::GlobalImprovement,
              "Classic crouch while sniping mid-jump. Single player only." },
            // Ships off, so the default index is "Off" (1) -- what an absent
            // key does -- not what any preset happens to write.
            { "Ordnance Velocity", "SinglePlayer", "OrdnanceVelocityInheritance", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
              ShimSettingApplyGroup::GlobalImprovement,
              "Shots inherit the shooter's velocity, and cannon lead compensates for it. "
              "Single player only." },
            // AI behaviour switches that change stock content without any
            // mission script, so they belong on the page rather than staying
            // ini-only. Each default index is what an ABSENT key does, which
            // is not the same as what a preset happens to ship.
            { "Bomber AI Range", "SinglePlayer", "BomberAiRange", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
              ShimSettingApplyGroup::GlobalImprovement,
              "Bombers engage at the range their own weapon ODFs declare. Single player only." },
            { "AI Howitzer Volley", "SinglePlayer", "AiWeaponMaskArtillery", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
              ShimSettingApplyGroup::GlobalImprovement,
              "Artillery AI fires every fitted hardpoint as one volley instead of the first. "
              "A stock howitzer fires four rounds per cycle. Single player only." },
            { "AI Mine Volley", "SinglePlayer", "AiWeaponMaskMinelayer", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
              ShimSettingApplyGroup::GlobalImprovement,
              "Minelayer AI honours weaponMask instead of hard-coding hardpoint 0. "
              "Single player only." },
            // [Fixes] rather than [SinglePlayer], and it ships ON, so the
            // default index is "On" (0).
            { "AI Multi-Producer", "Fixes", "AiMultiProducerMakers", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::GlobalImprovement,
              "A built class gets every producer that can make it, not just the first one found." },
            { "Neutral Attack Orders", "Gameplay", "AllowNeutralAttackOrders", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
              ShimSettingApplyGroup::GlobalImprovement,
              "Allow explicit player attack orders against team-0 neutral objects. "
              "Diplomacy and autonomous targeting remain stock." },
            { "Global Turbo", "SinglePlayer", "Turbo", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
              ShimSettingApplyGroup::GlobalTurbo,
              "Turbo available on all drivable units. Single player only." },
            { "Satellite Fog Of War", "SinglePlayer", "SatelliteVisibilityFix", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::LiveEngineToggle,
              "Restore the BZ 1.5 satellite gate so unilluminated enemies stay hidden. Single player only." },
            { "Player Headlight", "SinglePlayer", "Headlights", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::Headlights,
              "Headlight on your vehicle. Single player only." },
            { "Headlight Brightness", "SinglePlayer", "HeadlightBrightness", nullptr, 0,
              kShimSettingsHeadlightBrightnessValues, kShimSettingsHeadlightBrightnessLabels, 5, 2,
              ShimSettingApplyGroup::Headlights,
              "Player-vehicle headlight intensity relative to stock. Applies live; single player only." },
            { "AI Headlights", "SinglePlayer", "OtherHeadlights", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
              ShimSettingApplyGroup::Headlights,
              "AI vehicles run headlights too. Single player only." },
            { "Headlight Color", "SinglePlayer", "HeadlightColor", nullptr, 0,
              kShimSettingsHeadlightColorValues, kShimSettingsHeadlightColorValues, 12, 0,
              ShimSettingApplyGroup::Headlights,
              "Headlight beam color; Rainbow cycles through colors." },
            { "Headlight Beam", "SinglePlayer", "HeadlightBeam", nullptr, 0,
              kShimSettingsHeadlightBeamValues, kShimSettingsHeadlightBeamValues, 3, 0,
              ShimSettingApplyGroup::Headlights,
              "Headlight beam shape: Stock, Focused (narrow), or Wide." },
            // Pilot flashlight. Not a stock light: no pilot skeleton has an
            // hlgt bone, so OpenShim creates this one on the pilot's own scene
            // node and destroys it when the player boards or the world ends.
            // Default off, so the default index is "Off" (1), matching what an
            // absent key does.
            { "Pilot Flashlight", "SinglePlayer", "PilotFlashlight", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
              ShimSettingApplyGroup::PilotFlashlight,
              "Flashlight on your pilot while on foot. Single player only." },
            { "Pilot Light Color", "SinglePlayer", "PilotFlashlightColor", nullptr, 0,
              kShimSettingsHeadlightColorValues, kShimSettingsHeadlightColorValues, 12, 0,
              ShimSettingApplyGroup::PilotFlashlight,
              "Pilot flashlight color; Rainbow cycles through colors." },
            { "Pilot Light Beam", "SinglePlayer", "PilotFlashlightBeam", nullptr, 0,
              kShimSettingsHeadlightBeamValues, kShimSettingsHeadlightBeamValues, 3, 0,
              ShimSettingApplyGroup::PilotFlashlight,
              "Pilot flashlight beam shape: Stock, Focused (narrow), or Wide." },
            // [Fixes]: confirmed Redux engine defects. All seven default ON and
            // normal single-player play wants them on -- they are switches so a
            // suspected regression is bisectable. Each one changes simulation
            // behaviour and none is negotiated with peers, so all seven stand
            // down for the duration of a network game and a mixed OpenShim /
            // stock lobby stays behaviourally identical.
            { "APC Allied Deploy", "Fixes", "ApcAlliedTargetDeploy", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::RestartRequired,
              "Let APC AI accept allied deploy targets. Single player only. Restart required." },
            { "Splinter Undead Fix", "Fixes", "SplinterUndead", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::RestartRequired,
              "Stop a destroyed splinter from spawning payload ordnance. Single player only. Restart required." },
            { "Howitzer Deploy Fix", "Fixes", "HowitzerUndeployedRetaliation", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::RestartRequired,
              "Stop an undeployed howitzer counter-sniping its attacker. Single player only. Restart required." },
            { "Tug Cargo Deploy", "Fixes", "TugCargoPostLoad", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::RestartRequired,
              "Arm the stock deploy transition after a tug loads cargo. Single player only. Restart required." },
            { "Recycle Release Fix", "Fixes", "ConstructorRecycleStaleTarget", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::RestartRequired,
              "Free a constructor left deployed when another recycles its target first. Single player only. Restart required." },
            { "Constructor Cleanup", "Fixes", "ConstructorRemoteBuild", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::RestartRequired,
              "Clear a dead constructor's remote build state. Single player only. Restart required." },
            { "Net Route", "Network", "RoutePreference", nullptr, 0,
              kShimSettingsNetRouteValues, kShimSettingsNetRouteLabels, 3, 0,
              ShimSettingApplyGroup::BzrNetRoute,
              "Preferred peer path: try LAN then direct WAN, or force the BZRNet relay. "
              "Does not add LAN or direct-IP hosting." },
            { "Net Improvements", "Network", "NetImprovements", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::RestartRequired,
              "OpenShim's socket layer as a whole. Off gives stock networking; "
              "turn it off to rule the shim out of a connection problem." },
            { "Net Tuning", "Network", "GovernorTuning", nullptr, 0,
              kShimSettingsGovernorTuningValues, kShimSettingsGovernorTuningValues, 2, 0,
              ShimSettingApplyGroup::RestartRequired,
              "Bandwidth governor and host auto-kick. Stock matches players who "
              "are not running OpenShim; net.ini still overrides per value." },
            // defaultIndex 1 selects "0", which is what an absent key does.
            // RestartRequired here means "no live apply step": the hook re-reads
            // the ini every time the multiplayer vehicle list is built, so the
            // change lands on the next list load without a relaunch.
            { "Stock Factions", "Network", "StockFactionsOnly", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
              ShimSettingApplyGroup::RestartRequired,
              "Restrict multiplayer starting vehicles to NSDF and CCA, as 1.5 did with "
              "Any Nation off. Local only, and it never adds craft the map withheld. "
              "Applies next time a vehicle list loads." },
            { "Lobby Ban Button", "Network", "LobbyBanButton", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
              ShimSettingApplyGroup::RestartRequired,
              "Ban User button on the multiplayer waiting room. Off leaves BZP/BZP-T's "
              "faction picker alone; /ban still works. Restart required." },
            // defaultIndex 0 selects "1": an absent key persists, which is what
            // the feature did before it had a key at all.
            { "Persistent Mutes", "Network", "PersistentPlayerMute", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::ReadOnNextUse,
              "Remember muted players across sessions, by stable identity, so a rename "
              "or reconnect does not undo it. Off is stock: the mute lasts the session. "
              "Local only; /mute works either way and your mute list is kept." },
            { "Lobby Readouts", "Network", "LobbyReadouts", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::RestartRequired,
              "Nickname field and route readout in the waiting-room left column. "
              "Does not cover BZP's faction picker. Restart required." },
            // Re-read on every nickname apply; no process restart is required
            // for the next OK / /nickname to take the new value.
            { "Live Nickname", "Network", "ReauthOnNicknameChange", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
              ShimSettingApplyGroup::ReadOnNextUse,
              "Experimental: recycle the lounge BZRNet connection after a nickname "
              "edit so stock reconnects and authorizes the new name. Expect a brief "
              "lounge drop / possible Not Ready flicker. In-match remains persist-only." },
            // defaultIndex 0 selects "1", which is what an absent key does: the
            // native tracker has always run, and turning the row off must be a
            // deliberate choice rather than the effect of a missing ini key.
            { "Career Stats", "Career", "StatsTracking", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::RestartRequired,
              "Record kills, deaths and missions played to career_stats.cfg across "
              "single player and multiplayer. Local file only; nothing is uploaded, "
              "and no mission script is required." },
            // Action row: no ini key, no cycling. Section/key stay null so the
            // settings reader and the lossless ini writer never touch it.
            { "Reset Career Stats", nullptr, nullptr, nullptr, 0,
              kShimSettingsActionValues, kShimSettingsActionValues, 2, 0,
              ShimSettingApplyGroup::CareerStatsReset,
              "Clear every recorded kill, death and mission play. Takes two clicks, "
              "and keeps the previous record as career_stats.cfg.openshim.bak. "
              "Does not turn tracking off." },
        };
        // The screens list registry rows by category (kShimSettingsCategories).
        constexpr size_t kShimSettingsRegistryCount =
            sizeof(g_ShimSettingsRegistry) / sizeof(g_ShimSettingsRegistry[0]);

        // An action row runs something on click instead of cycling an ini
        // value. It has no section/key, so nothing in the read/write path may
        // treat it as a setting.
        static bool IsShimSettingActionRow(const ShimSettingDescriptor& setting)
        {
            return setting.applyGroup == ShimSettingApplyGroup::CareerStatsReset;
        }

        // Which action row, if any, is one click away from firing. Registry
        // index, or kShimSettingsRegistryCount for "none". A destructive action
        // must never happen on a single click of a row the player was only
        // trying to read, so the first click arms and the second commits.
        static size_t g_ShimSettingsArmedActionIndex = kShimSettingsRegistryCount;

        static void DisarmShimSettingsAction()
        {
            g_ShimSettingsArmedActionIndex = kShimSettingsRegistryCount;
        }

        // The UI shows the ini baseline: the value the key currently resolves to
        // in openshim.ini (or the setting's default when absent/unrecognized).
        static size_t GetShimSettingCurrentIndex(const ShimSettingDescriptor& setting)
        {
            if (IsShimSettingActionRow(setting))
            {
                // Index 0 is the resting label, index 1 the armed one.
                const size_t index =
                    static_cast<size_t>(&setting - &g_ShimSettingsRegistry[0]);
                return (g_ShimSettingsArmedActionIndex == index) ? 1u : 0u;
            }

            std::string value;
            bool found = TryGetUserConfigString(setting.section, setting.key, value);
            for (size_t alt = 0; !found && alt < setting.altKeyCount; ++alt)
                found = TryGetUserConfigString(setting.section, setting.altKeys[alt], value);
            if (!found)
                return setting.defaultIndex;

            // Normalize like the feature parsers: case-insensitive, ignore
            // spaces/underscores/hyphens so NeutralOnly == neutral-only.
            std::string normalized;
            normalized.reserve(value.size());
            for (char ch : value)
            {
                if (ch == ' ' || ch == '\t' || ch == '_' || ch == '-')
                    continue;
                normalized.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
            }

            for (size_t index = 0; index < setting.valueCount; ++index)
            {
                std::string candidate;
                for (const char* cursor = setting.values[index]; *cursor; ++cursor)
                {
                    if (*cursor == ' ' || *cursor == '_' || *cursor == '-')
                        continue;
                    candidate.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(*cursor))));
                }
                if (normalized == candidate)
                    return index;
            }

            // Boolean rows also accept the parser's synonym set.
            bool token = false;
            if (setting.values == kShimSettingsOnOffValues && BZROpenShim::BoolToken::TryParse(normalized, token))
                return token ? 0 : 1;
            if (setting.values == kShimSettingsUnitVoValues && BZROpenShim::BoolToken::TryParse(normalized, token))
                return token ? 0 : 2;

            return setting.defaultIndex;
        }


        // ====================================================================
        // OPENSHIM OPTIONS SCREENS
        // ====================================================================
        //
        // The settings are their own shell screens (see shell_screens.h): the
        // stock Options screen gains an "OpenShim Options" button that opens a
        // hub, and each hub tile opens one category screen. They are built
        // like stock screens -- the stock Top Screen, one painted centre panel
        // (mkscreens.py), and stock widgets placed over the painted slots -- so
        // they fade, stack, and answer Esc like the screens around them.
        //
        // Every setting still comes from g_ShimSettingsRegistry; a category
        // lists registry rows by label, in display order. The coordinates
        // below are the layout contract with HUB_LAYOUT / CATEGORY_LAYOUT in
        // resources/ui/custom_widgets/mkscreens.py.
        namespace Shell = BZROpenShim::ShellScreens;

        constexpr const char* kShimHubPanelTexture = "osh_hub_center.png";
        constexpr const char* kShimCategoryPanelTexture = "osh_category_center.png";

        // Rows that are not openshim.ini settings: they run something.
        constexpr const char* kShimRowUpdateCheck = "OpenShim Updates";
        constexpr const char* kShimRowKeyBindings = "Key Bindings";
        constexpr size_t kShimPseudoRowUpdateCheck = kShimSettingsRegistryCount + 0;
        constexpr size_t kShimPseudoRowKeyBindings = kShimSettingsRegistryCount + 1;
        constexpr size_t kShimNoRow = kShimSettingsRegistryCount + 2;
        // Stock cUI_OptionsInput (key bindings), as the stock Input button uses.
        constexpr uint32_t kStockOptionsInputScreenId = 0x15;

        constexpr size_t kShimCategoryRowsPerColumn = 8;
        constexpr size_t kShimCategoryMaxRows = 2 * kShimCategoryRowsPerColumn;

        static const char* const kShimCategoryVideo[] = {
            "Render Profile", "DX11 FXAA", "DX11 Local Lights", "Sun Flashbang", "Jet Flames",
            "Empty Craft Lights", "Emissive Pulse", "Star Twinkle", "Death Chunk Meshes" };
        static const char* const kShimCategoryLighting[] = {
            "Player Headlight", "Headlight Brightness", "Headlight Color", "Headlight Beam",
            "AI Headlights", "Pilot Flashlight", "Pilot Light Color", "Pilot Light Beam" };
        static const char* const kShimCategoryAudio[] = {
            "Sound Channels", "Background Music", "Unit Voices", "Attack Alert", "Hop-Out Alert Fix" };
        static const char* const kShimCategoryHud[] = {
            "Scrap/Pilot HUD", "Radar Size", "Target Popup", "MP Vehicle Flags", "Show Own MP Flag" };
        static const char* const kShimCategoryControls[] = {
            kShimRowKeyBindings, "Custom Keybinds", "Raw Mouse Input", "Unsmoothed Controls",
            "Satellite Zoom Out", "Satellite Pan Speed", "Editor Placement" };
        static const char* const kShimCategoryGameplay[] = {
            "Weapon Convergence", "Reticle Convergence", "Reticle Range", "Ordnance Velocity",
            "Jump-Snipe Crouch", "Global Turbo", "Satellite Fog Of War", "Neutral Attack Orders",
            "Smart Scavengers", "Turret AA Pitch", "Bomber AI Range", "AI Howitzer Volley",
            "AI Mine Volley", "AutoSave", "AutoSave Interval" };
        static const char* const kShimCategoryFixes[] = {
            "AI Multi-Producer", "APC Allied Deploy", "Splinter Undead Fix", "Howitzer Deploy Fix",
            "Tug Cargo Deploy", "Recycle Release Fix", "Constructor Cleanup", "Material Guard" };
        static const char* const kShimCategoryNetwork[] = {
            "Net Route", "Net Improvements", "Net Tuning", "Stock Factions", "Map List Fixes",
            "Map Filters+", "Lobby Ban Button", "Lobby Readouts", "Persistent Mutes", "Live Nickname" };
        static const char* const kShimCategorySystem[] = {
            kShimRowUpdateCheck, "Career Stats", "Reset Career Stats" };

        struct ShimSettingsCategory
        {
            const char* name;   // tile caption
            const char* title;  // screen title
            const char* blurb;  // hub hover text
            const char* const* rows;
            size_t rowCount;
        };

#define BZR_SHIM_CATEGORY(name, title, blurb, rows) \
            { name, title, blurb, rows, sizeof(rows) / sizeof(rows[0]) }
        static const ShimSettingsCategory kShimSettingsCategories[] =
        {
            BZR_SHIM_CATEGORY("Video", "VIDEO",
                "Render profile, the DX11 Enhanced passes, and visual effects.", kShimCategoryVideo),
            BZR_SHIM_CATEGORY("Lighting", "LIGHTING",
                "Vehicle headlights and the pilot flashlight.", kShimCategoryLighting),
            BZR_SHIM_CATEGORY("Audio", "AUDIO",
                "Sound channels, background music, unit voices and alerts.", kShimCategoryAudio),
            BZR_SHIM_CATEGORY("HUD", "HUD",
                "Scrap and pilot readout, radar size, target popup and vehicle flags.", kShimCategoryHud),
            BZR_SHIM_CATEGORY("Controls", "CONTROLS",
                "Key bindings, raw mouse input, control smoothing and the satellite view.",
                kShimCategoryControls),
            BZR_SHIM_CATEGORY("Gameplay", "GAMEPLAY",
                "Single-player aiming, AI behaviour, turbo and AutoSave.", kShimCategoryGameplay),
            BZR_SHIM_CATEGORY("Fixes", "FIXES",
                "Switches for confirmed Redux engine defects. Leave these on unless "
                "you are chasing a regression.", kShimCategoryFixes),
            BZR_SHIM_CATEGORY("Network", "NETWORK",
                "Connection route, the socket layer, lobby features and map lists.",
                kShimCategoryNetwork),
            BZR_SHIM_CATEGORY("System", "SYSTEM",
                "OpenShim updates and career statistics.", kShimCategorySystem),
        };
#undef BZR_SHIM_CATEGORY
        constexpr size_t kShimSettingsCategoryCount =
            sizeof(kShimSettingsCategories) / sizeof(kShimSettingsCategories[0]);
        static_assert(sizeof(kShimCategoryGameplay) / sizeof(kShimCategoryGameplay[0]) <= kShimCategoryMaxRows,
                      "a category screen shows at most 16 rows");

        // Hub geometry (HUB_LAYOUT).
        constexpr Shell::Rect kShimTitleRect = { 470.0f, 132.0f, 500.0f, 56.0f };
        constexpr Shell::Rect kShimBackRect = { 0.0f, 0.0f, 342.0f, 77.0f };
        constexpr float kShimBackTextOffset = 28.0f;
        constexpr size_t kShimHubColumns = 3;
        constexpr Shell::Rect kShimHubTile0 = { 240.0f, 252.0f, 300.0f, 100.0f };
        constexpr float kShimHubPitchX = 330.0f;
        constexpr float kShimHubPitchY = 124.0f;
        constexpr Shell::Rect kShimHubInfo = { 240.0f, 640.0f, 960.0f, 170.0f };
        // Category geometry (CATEGORY_LAYOUT).
        constexpr float kShimColumnX[2] = { 228.0f, 736.0f };
        constexpr float kShimColumnY = 236.0f;
        constexpr float kShimColumnW = 476.0f;
        constexpr float kShimRowTop = 14.0f;
        constexpr float kShimRowPitch = 52.0f;
        constexpr float kShimRowH = 42.0f;
        constexpr float kShimRowPad = 16.0f;
        constexpr float kShimValueW = 196.0f;
        constexpr Shell::Rect kShimCategoryInfo = { 228.0f, 690.0f, 984.0f, 120.0f };

        static Shell::Rect ShimHubTileRect(size_t index)
        {
            const float col = static_cast<float>(index % kShimHubColumns);
            const float row = static_cast<float>(index / kShimHubColumns);
            return { kShimHubTile0.x + col * kShimHubPitchX, kShimHubTile0.y + row * kShimHubPitchY,
                     kShimHubTile0.w, kShimHubTile0.h };
        }

        static Shell::Rect ShimValueRect(size_t slot)
        {
            const float x = kShimColumnX[slot / kShimCategoryRowsPerColumn] + kShimColumnW -
                            kShimRowPad - kShimValueW;
            const float y = kShimColumnY + kShimRowTop +
                            kShimRowPitch * static_cast<float>(slot % kShimCategoryRowsPerColumn);
            return { x, y, kShimValueW, kShimRowH };
        }

        static Shell::Rect ShimRowLabelRect(size_t slot)
        {
            const Shell::Rect value = ShimValueRect(slot);
            const float x = kShimColumnX[slot / kShimCategoryRowsPerColumn] + kShimRowPad + 12.0f;
            return { x, value.y, value.x - x - 22.0f, kShimRowH };
        }

        // Three text lines in an info box: two for a description, and one
        // under the painted divider for a standing note.
        static Shell::Rect ShimInfoLine(const Shell::Rect& box, size_t line)
        {
            const float x = box.x + 24.0f;
            const float w = box.w - 48.0f;
            if (line < 2)
                return { x, box.y + 14.0f + 32.0f * static_cast<float>(line), w, 30.0f };
            return { x, box.y + box.h - 42.0f, w, 30.0f };
        }

        static Shell::ButtonSkin ShimSlotSkin(const char* hover, const char* press)
        {
            // No resting texture: the slot is painted into the panel, as the
            // stock option buttons rest on esc_center.png's slots. Without
            // our art there is no painted slot, so rest on the stock art.
            if (Shell::IsTextureDeployed(hover) && Shell::IsTextureDeployed(press))
                return { nullptr, hover, press };
            return { "optionhv.png", "optionhv.png", "optionck.png" };
        }

        static size_t FindShimSettingByLabel(const char* label)
        {
            if (std::strcmp(label, kShimRowUpdateCheck) == 0)
                return kShimPseudoRowUpdateCheck;
            if (std::strcmp(label, kShimRowKeyBindings) == 0)
                return kShimPseudoRowKeyBindings;
            for (size_t index = 0; index < kShimSettingsRegistryCount; ++index)
            {
                if (std::strcmp(g_ShimSettingsRegistry[index].label, label) == 0)
                    return index;
            }
            return kShimNoRow;
        }

        // Logged once: a registry row no category lists cannot be reached from
        // the screens, and a category label that matches no row is a typo.
        static void CheckShimSettingsCategories()
        {
            static bool checked = false;
            if (checked)
                return;
            checked = true;
            std::array<bool, kShimSettingsRegistryCount> listed = {};
            for (const auto& category : kShimSettingsCategories)
            {
                for (size_t r = 0; r < category.rowCount; ++r)
                {
                    const size_t index = FindShimSettingByLabel(category.rows[r]);
                    if (index < kShimSettingsRegistryCount)
                        listed[index] = true;
                    else if (index == kShimNoRow)
                        Log(L"[SETTINGSUI] category %hs lists unknown row \"%hs\"\n",
                            category.name, category.rows[r]);
                }
            }
            for (size_t index = 0; index < kShimSettingsRegistryCount; ++index)
            {
                if (!listed[index])
                    Log(L"[SETTINGSUI] setting \"%hs\" is in no category; it is not on any screen\n",
                        g_ShimSettingsRegistry[index].label);
            }
        }

        // Null when the row can be used; otherwise why not.
        static const char* ShimSettingUnavailableReason(const ShimSettingDescriptor& setting)
        {
            const auto caps = Assets::GetAssetCapabilities();
            if (caps.state == Assets::AssetPackState::Unknown || !setting.section || !setting.key)
                return nullptr;
            // Native mesh extraction (ChunkMeshes) needs no external payload pack.
            if (std::strcmp(setting.section, "DX11Enhanced") == 0 &&
                (std::strcmp(setting.key, "FXAA") == 0 ||
                 std::strcmp(setting.key, "EnhancedLightSelectionV2") == 0) &&
                !Assets::IsAssetFeatureAvailable(Assets::AssetFeature::EnhancedRenderer))
            {
                return "Unavailable: Enhanced renderer resources were not detected.";
            }
            return nullptr;
        }

        // ---- shared state -------------------------------------------------
        // One hub and one category screen can be live at a time (the shell may
        // build the next screen before it frees the last, so every reset is
        // keyed to the screen that owns the state).
        struct ShimHubUi
        {
            void* screen = nullptr;
            void* info[3] = {};
        };
        struct ShimCategoryUi
        {
            void* screen = nullptr;
            size_t category = 0;
            size_t rowCount = 0;
            std::array<size_t, kShimCategoryMaxRows> rows = {};
            std::array<void*, kShimCategoryMaxRows> values = {};
            void* info[3] = {};
            std::string status;
        };
        static ShimHubUi g_ShimHubUi;
        static ShimCategoryUi g_ShimCategoryUi;

        static std::string ShimRuntimeLine()
        {
            const BZROpenShim::BzrDistribution dist = BZROpenShim::GetBzrDistribution();
            const char* distName = (dist == BZROpenShim::BzrDistribution::Steam) ? "Steam"
                                 : (dist == BZROpenShim::BzrDistribution::GOG)   ? "GOG"
                                                                                 : "Unknown";
            return "OpenShim " + std::to_string(GetShimVersion()) + "   Game: " + distName + " 2.2.301";
        }

        static void SetShimInfoText(void* const (&info)[3], const char* text, float width)
        {
            SetInputBindingUiWrappedLabelText(info[0], info[1], text ? text : "", width);
        }

        // ---- hub ----------------------------------------------------------
        static void ShowShimHubDefaultInfo()
        {
            if (!g_ShimHubUi.screen)
                return;
            const float width = ShimInfoLine(kShimHubInfo, 0).w;
            const auto caps = Assets::GetAssetCapabilities();
            std::string text = "Changes are saved to openshim.ini as you make them. ";
            text += Assets::FormatAssetStatusForUi(caps);
            SetShimInfoText(g_ShimHubUi.info, text.c_str(), width);
            SetInputBindingUiLabelTextFitted(g_ShimHubUi.info[2], ShimRuntimeLine().c_str(), width);
        }

        static void __cdecl OnShimHubHover(void* /*param*/)
        {
            if (!g_ShimHubUi.screen)
                return;
            float x = 0.0f, y = 0.0f;
            if (Shell::CursorDesignPoint(x, y))
            {
                for (size_t i = 0; i < kShimSettingsCategoryCount; ++i)
                {
                    if (Shell::Contains(ShimHubTileRect(i), x, y))
                    {
                        SetShimInfoText(g_ShimHubUi.info, kShimSettingsCategories[i].blurb,
                                        ShimInfoLine(kShimHubInfo, 0).w);
                        return;
                    }
                }
            }
            ShowShimHubDefaultInfo();
        }

        static void OnShimHubTileClicked(size_t category)
        {
            if (g_ShimHubUi.screen && category < kShimSettingsCategoryCount)
                Shell::RequestScreen(g_ShimHubUi.screen,
                                     Shell::kOptionsCategoryScreenIdBase + static_cast<uint32_t>(category));
        }

        template <size_t I>
        static void __cdecl ShimHubTileClick() { OnShimHubTileClicked(I); }

        template <size_t... I>
        static constexpr std::array<void(__cdecl*)(), sizeof...(I)> MakeShimHubTileClicks(std::index_sequence<I...>)
        {
            return { &ShimHubTileClick<I>... };
        }
        static constexpr auto kShimHubTileClicks =
            MakeShimHubTileClicks(std::make_index_sequence<kShimSettingsCategoryCount>{});

        static void __cdecl OnShimHubBack()
        {
            if (g_ShimHubUi.screen)
                Shell::Back(g_ShimHubUi.screen);
        }

        static bool BuildShimHubScreen(void* screen)
        {
            CheckShimSettingsCategories();
            Assets::RefreshAssetCapabilities();
            g_ShimHubUi = {};
            g_ShimHubUi.screen = screen;

            const char* texture =
                Shell::IsTextureDeployed(kShimHubPanelTexture) ? kShimHubPanelTexture : nullptr;
            void* panel = Shell::AddPanel(screen, nullptr, "OpenShimHub_Overlay",
                                          { 0.0f, 0.0f, 1440.0f, 1080.0f }, texture);
            if (!panel)
                return false;
            Shell::AddLabel(panel, panel, "OpenShimHub_Title", kShimTitleRect, "OPENSHIM OPTIONS",
                            Shell::kTitleLabelFlags);

            const Shell::ButtonSkin skin = ShimSlotSkin("osh_tile_hv.png", "osh_tile_ck.png");
            char name[64] = {};
            for (size_t i = 0; i < kShimSettingsCategoryCount; ++i)
            {
                _snprintf_s(name, _TRUNCATE, "OpenShimHub_%s", kShimSettingsCategories[i].name);
                Shell::AddButton(panel, panel, name, ShimHubTileRect(i), kShimSettingsCategories[i].name,
                                 skin, 1.3f, 0.0f, kShimHubTileClicks[i], &OnShimHubHover);
            }
            for (size_t line = 0; line < 3; ++line)
            {
                _snprintf_s(name, _TRUNCATE, "OpenShimHub_Info%zu", line);
                g_ShimHubUi.info[line] =
                    Shell::AddLabel(panel, panel, name, ShimInfoLine(kShimHubInfo, line), "");
            }
            ShowShimHubDefaultInfo();
            return Shell::AddButton(panel, nullptr, "OpenShimHub_Back", kShimBackRect, "Back",
                                    Shell::kSkinTopCorner, 1.0f, kShimBackTextOffset,
                                    &OnShimHubBack) != nullptr;
        }

        static void OnShimHubClosed(void* screen)
        {
            if (g_ShimHubUi.screen == screen)
                g_ShimHubUi = {};
        }

        // ---- category screens ---------------------------------------------
        static std::string ShimRowValueText(size_t row)
        {
            if (row == kShimPseudoRowUpdateCheck)
                return GetOpenShimUpdateSnapshot().busy ? "Checking..." : "Check now";
            if (row == kShimPseudoRowKeyBindings)
                return "Edit";
            const ShimSettingDescriptor& setting = g_ShimSettingsRegistry[row];
            if (ShimSettingUnavailableReason(setting))
                return "Unavailable";
            std::string text = setting.valueLabels[GetShimSettingCurrentIndex(setting)];
            if (setting.applyGroup == ShimSettingApplyGroup::RestartRequired)
                text += " *";
            return text;
        }

        static const char* ShimRowLabel(size_t row)
        {
            if (row == kShimPseudoRowUpdateCheck)
                return kShimRowUpdateCheck;
            if (row == kShimPseudoRowKeyBindings)
                return kShimRowKeyBindings;
            return g_ShimSettingsRegistry[row].label;
        }

        static const char* ShimRowDescription(size_t row)
        {
            if (row == kShimPseudoRowUpdateCheck)
                return "Check the Steam Workshop for a newer OpenShim and stage it for the next launch.";
            if (row == kShimPseudoRowKeyBindings)
                return "Open the key-binding editor for keyboard commands and game keys.";
            const ShimSettingDescriptor& setting = g_ShimSettingsRegistry[row];
            if (const char* reason = ShimSettingUnavailableReason(setting))
                return reason;
            return setting.description;
        }

        static void ShowShimCategoryDefaultInfo()
        {
            ShimCategoryUi& ui = g_ShimCategoryUi;
            if (!ui.screen)
                return;
            const float width = ShimInfoLine(kShimCategoryInfo, 0).w;
            SetShimInfoText(ui.info,
                            ui.status.empty()
                                ? "Click a value to change it. Point at a setting to read what it does."
                                : ui.status.c_str(),
                            width);
            bool anyRestart = false;
            for (size_t slot = 0; slot < ui.rowCount; ++slot)
            {
                const size_t row = ui.rows[slot];
                anyRestart |= row < kShimSettingsRegistryCount &&
                              g_ShimSettingsRegistry[row].applyGroup == ShimSettingApplyGroup::RestartRequired;
            }
            SetInputBindingUiLabelTextFitted(
                ui.info[2],
                anyRestart ? "* Takes effect after restarting Battlezone." : ShimRuntimeLine().c_str(),
                width);
        }

        static void RefreshShimCategoryValues()
        {
            ShimCategoryUi& ui = g_ShimCategoryUi;
            for (size_t slot = 0; slot < ui.rowCount; ++slot)
                SetInputBindingUiButtonTextFitted(ui.values[slot], ShimRowValueText(ui.rows[slot]).c_str(),
                                                  kShimValueW - 20.0f);
            ShowShimCategoryDefaultInfo();
        }

        static void __cdecl OnShimCategoryHover(void* /*param*/)
        {
            ShimCategoryUi& ui = g_ShimCategoryUi;
            if (!ui.screen)
                return;
            float x = 0.0f, y = 0.0f;
            if (Shell::CursorDesignPoint(x, y))
            {
                for (size_t slot = 0; slot < ui.rowCount; ++slot)
                {
                    if (!Shell::Contains(ShimValueRect(slot), x, y))
                        continue;
                    const size_t row = ui.rows[slot];
                    std::string text = ShimRowDescription(row) ? ShimRowDescription(row) : "";
                    if (row < kShimSettingsRegistryCount && !IsShimSettingActionRow(g_ShimSettingsRegistry[row]) &&
                        !ShimSettingUnavailableReason(g_ShimSettingsRegistry[row]))
                    {
                        const ShimSettingDescriptor& setting = g_ShimSettingsRegistry[row];
                        const size_t current = GetShimSettingCurrentIndex(setting);
                        text += "  Click for ";
                        text += setting.valueLabels[(current + 1) % setting.valueCount];
                        text += ".";
                    }
                    SetShimInfoText(ui.info, text.c_str(), ShimInfoLine(kShimCategoryInfo, 0).w);
                    return;
                }
            }
            ShowShimCategoryDefaultInfo();
        }

        static void StartShimUpdateCheck()
        {
            BeginOpenShimUpdateCheck();
            OpenShimUpdateSnapshot update = GetOpenShimUpdateSnapshot();
            if (update.busy && !EnsureShimSettingsUpdateTimer())
            {
                CancelOpenShimUpdateCheck(
                    "Update check failed: Battlezone could not schedule Workshop status checks.");
                update = GetOpenShimUpdateSnapshot();
            }
            g_ShimSettingsUiUpdateGeneration = update.generation;
            g_ShimCategoryUi.status = update.message;
        }

        // Cycles a setting to its next value, saves it, and applies it live
        // where the feature supports that.
        static void CycleShimSetting(size_t index)
        {
            const ShimSettingDescriptor& setting = g_ShimSettingsRegistry[index];
            std::string& status = g_ShimCategoryUi.status;
            if (const char* reason = ShimSettingUnavailableReason(setting))
            {
                status = reason;
                Log(L"[SETTINGSUI] Asset-backed setting blocked %hs: %hs\n", setting.key, reason);
                return;
            }
            if (IsShimSettingActionRow(setting))
            {
                OnShimSettingsActionRowClicked(index, setting);
                return;
            }
            // Clicking anything else abandons a pending confirmation rather
            // than leaving it armed behind the player's back.
            DisarmShimSettingsAction();

            const size_t nextIndex = (GetShimSettingCurrentIndex(setting) + 1) % setting.valueCount;
            std::string error;
            if (!WriteUserConfigValueLossless(setting.section, setting.key, setting.altKeys,
                                              setting.altKeyCount, setting.values[nextIndex], error))
            {
                status = "Save failed: " + error;
                Log(L"[SETTINGSUI] Save failed for %hs: %hs\n", setting.key, error.c_str());
                return;
            }

            bool liveApplyOk = true;
            if (setting.applyGroup == ShimSettingApplyGroup::AutoSave)
                liveApplyOk = ReloadAutoSaveConfig();
            else
                ApplyShimSettingLive(setting.applyGroup);

            status = std::string(setting.label) + " = " + setting.valueLabels[nextIndex];
            if (setting.applyGroup == ShimSettingApplyGroup::RestartRequired)
                status += "  (takes effect after restart)";
            else if (setting.applyGroup == ShimSettingApplyGroup::ReadOnNextUse)
                status += "  (takes effect the next time it is used)";
            else if (!liveApplyOk)
                status += "  (saved; runtime apply failed - see openshim.log)";
            else
                status += "  (applied)";
        }

        static void OnShimCategoryRowClicked(size_t slot)
        {
            ShimCategoryUi& ui = g_ShimCategoryUi;
            if (!ui.screen || slot >= ui.rowCount)
                return;
            const size_t row = ui.rows[slot];
            if (row == kShimPseudoRowKeyBindings)
            {
                DisarmShimSettingsAction();
                Shell::RequestScreen(ui.screen, kStockOptionsInputScreenId);
                return;
            }
            if (row == kShimPseudoRowUpdateCheck)
            {
                DisarmShimSettingsAction();
                StartShimUpdateCheck();
            }
            else
            {
                CycleShimSetting(row);
            }
            RefreshShimCategoryValues();
        }

        template <size_t I>
        static void __cdecl ShimCategoryRowClick() { OnShimCategoryRowClicked(I); }

        template <size_t... I>
        static constexpr std::array<void(__cdecl*)(), sizeof...(I)> MakeShimCategoryRowClicks(std::index_sequence<I...>)
        {
            return { &ShimCategoryRowClick<I>... };
        }
        static constexpr auto kShimCategoryRowClicks =
            MakeShimCategoryRowClicks(std::make_index_sequence<kShimCategoryMaxRows>{});

        static void __cdecl OnShimCategoryBack()
        {
            if (g_ShimCategoryUi.screen)
                Shell::Back(g_ShimCategoryUi.screen);
        }

        static bool BuildShimCategoryScreen(size_t category, void* screen)
        {
            const ShimSettingsCategory& def = kShimSettingsCategories[category];
            ShimCategoryUi& ui = g_ShimCategoryUi;
            ui = {};
            ui.screen = screen;
            ui.category = category;
            DisarmShimSettingsAction();
            if (GetOpenShimUpdateSnapshot().busy)
                EnsureShimSettingsUpdateTimer();

            const char* texture =
                Shell::IsTextureDeployed(kShimCategoryPanelTexture) ? kShimCategoryPanelTexture : nullptr;
            void* panel = Shell::AddPanel(screen, nullptr, "OpenShimCategory_Overlay",
                                          { 0.0f, 0.0f, 1440.0f, 1080.0f }, texture);
            if (!panel)
                return false;
            Shell::AddLabel(panel, panel, "OpenShimCategory_Title", kShimTitleRect, def.title,
                            Shell::kTitleLabelFlags);

            const Shell::ButtonSkin skin = ShimSlotSkin("osh_value_hv.png", "osh_value_ck.png");
            char name[64] = {};
            for (size_t r = 0; r < def.rowCount && ui.rowCount < kShimCategoryMaxRows; ++r)
            {
                const size_t row = FindShimSettingByLabel(def.rows[r]);
                if (row == kShimNoRow)
                    continue;
                const size_t slot = ui.rowCount++;
                ui.rows[slot] = row;
                _snprintf_s(name, _TRUNCATE, "OpenShimCategory_Label%zu", slot);
                void* label = Shell::AddLabel(panel, panel, name, ShimRowLabelRect(slot), "");
                // The text measure runs a little narrow for this font size, so
                // fit with a margin; the label rect itself stays the full well.
                SetInputBindingUiLabelTextFitted(label, ShimRowLabel(row), ShimRowLabelRect(slot).w - 34.0f);
                _snprintf_s(name, _TRUNCATE, "OpenShimCategory_Value%zu", slot);
                ui.values[slot] = Shell::AddButton(panel, panel, name, ShimValueRect(slot), "", skin, 1.0f,
                                                   0.0f, kShimCategoryRowClicks[slot], &OnShimCategoryHover);
            }
            for (size_t line = 0; line < 3; ++line)
            {
                _snprintf_s(name, _TRUNCATE, "OpenShimCategory_Info%zu", line);
                ui.info[line] = Shell::AddLabel(panel, panel, name, ShimInfoLine(kShimCategoryInfo, line), "");
            }
            RefreshShimCategoryValues();
            Log(L"[SETTINGSUI] %hs screen built: %u rows\n", def.name, static_cast<unsigned>(ui.rowCount));
            return Shell::AddButton(panel, nullptr, "OpenShimCategory_Back", kShimBackRect, "Back",
                                    Shell::kSkinTopCorner, 1.0f, kShimBackTextOffset,
                                    &OnShimCategoryBack) != nullptr;
        }

        template <size_t I>
        static bool BuildShimCategoryScreenAt(void* screen) { return BuildShimCategoryScreen(I, screen); }

        template <size_t... I>
        static constexpr std::array<Shell::BuildFn, sizeof...(I)> MakeShimCategoryBuilders(std::index_sequence<I...>)
        {
            return { &BuildShimCategoryScreenAt<I>... };
        }
        static constexpr auto kShimCategoryBuilders =
            MakeShimCategoryBuilders(std::make_index_sequence<kShimSettingsCategoryCount>{});

        static void OnShimCategoryClosed(void* screen)
        {
            if (g_ShimCategoryUi.screen != screen)
                return;
            DisarmShimSettingsAction();
            g_ShimCategoryUi = {};
        }

        static bool RegisterShimOptionsScreens()
        {
            static const bool registered = [] {
                if (!Shell::RegisterScreen({ Shell::kOptionsHubScreenId, "OpenShim Options",
                                             &BuildShimHubScreen, &OnShimHubClosed }))
                    return false;
                for (size_t i = 0; i < kShimSettingsCategoryCount; ++i)
                {
                    if (!Shell::RegisterScreen({ Shell::kOptionsCategoryScreenIdBase + static_cast<uint32_t>(i),
                                                 kShimSettingsCategories[i].name, kShimCategoryBuilders[i],
                                                 &OnShimCategoryClosed }))
                        return false;
                }
                return true;
            }();
            return registered;
        }

        // Two-click confirmation for a destructive row. The first click arms
        // it and repaints the value cell; the second runs it. Clicking any
        // other row or leaving the screen disarms.
        static void OnShimSettingsActionRowClicked(size_t settingIndex,
                                                   const ShimSettingDescriptor& setting)
        {
            std::string& status = g_ShimCategoryUi.status;
            if (g_ShimSettingsArmedActionIndex != settingIndex)
            {
                g_ShimSettingsArmedActionIndex = settingIndex;
                status = std::string(setting.label) + ": click again to confirm. This cannot be undone.";
                return;
            }

            DisarmShimSettingsAction();

            switch (setting.applyGroup)
            {
            case ShimSettingApplyGroup::CareerStatsReset:
                switch (ResetCareerStatsFromBridge())
                {
                case CareerStatsResetResult::Cleared:
                    status = "Career statistics cleared. The previous record was kept as "
                             "career_stats.cfg.openshim.bak";
                    break;
                case CareerStatsResetResult::AlreadyEmpty:
                    status = "Career statistics were already empty; nothing changed.";
                    break;
                case CareerStatsResetResult::Failed:
                    status = "Career reset failed; existing statistics were kept - see openshim.log";
                    break;
                }
                break;
            default:
                status = std::string(setting.label) + ": no action is wired up for this row.";
                break;
            }
        }

        static void StopShimSettingsUpdateTimer()
        {
            if (g_ShimSettingsUiUpdateTimer == 0)
                return;
            KillTimer(nullptr, g_ShimSettingsUiUpdateTimer);
            g_ShimSettingsUiUpdateTimer = 0;
        }

        // SetTimer was created by the button click on Battlezone's UI thread,
        // so SteamUGC polling stays on the same thread as the stock New Game
        // RefreshButton path. The hashing/staging phase remains on the updater
        // worker and only publishes an atomic snapshot back here.
        static void CALLBACK ShimSettingsUpdateTimerProc(HWND, UINT, UINT_PTR, DWORD)
        {
            PollOpenShimUpdateCheck();
            const OpenShimUpdateSnapshot update = GetOpenShimUpdateSnapshot();
            if (update.generation != g_ShimSettingsUiUpdateGeneration)
            {
                g_ShimSettingsUiUpdateGeneration = update.generation;
                if (g_ShimCategoryUi.screen)
                {
                    if (!update.message.empty())
                        g_ShimCategoryUi.status = update.message;
                    RefreshShimCategoryValues();
                }
            }
            if (!update.busy)
            {
                StopShimSettingsUpdateTimer();
                if (g_ShimCategoryUi.screen)
                    RefreshShimCategoryValues();
            }
        }

        static bool EnsureShimSettingsUpdateTimer()
        {
            if (g_ShimSettingsUiUpdateTimer != 0)
                return true;
            g_ShimSettingsUiUpdateTimer = SetTimer(
                nullptr, 0, 250, ShimSettingsUpdateTimerProc);
            return g_ShimSettingsUiUpdateTimer != 0;
        }

        static void OnShimSettingsMenuClicked()
        {
            const ULONGLONG now = GetTickCount64();
            if (g_ShimSettingsNavigationTick != 0 &&
                now - g_ShimSettingsNavigationTick < kShimSettingsNavigationDebounceMs)
            {
                return;
            }
            g_ShimSettingsNavigationTick = now;
            void* const optionsScreen = g_ParentScreenBinding.constructed;
            if (!optionsScreen || !Shell::RequestScreen(optionsScreen, Shell::kOptionsHubScreenId))
                Log(L"[SETTINGSUI] OpenShim Options: no live Options screen to navigate from\n");
        }

        static void EnsureInputBindingUiControls(void* screen)
        {
            if (!screen)
                return;

            if (g_InputScreenBinding.decorated != screen)
            {
                ResetInputBindingUiVisuals();
                g_InputScreenBinding.BindDecorated(screen);
            }

            if (!g_InputBindingUiMiddleOverlay)
                g_InputBindingUiMiddleOverlay = ResolveStockOptionsInputMiddleOverlay(screen);

            void* const visualParent = screen;
            void* const controlParent =
                g_InputBindingUiMiddleOverlay ? g_InputBindingUiMiddleOverlay : screen;

            // Painted mode needs the panel art, the overlay to put it on, and
            // the shell kit for the title label; otherwise the flat masks and
            // plates are built as before.
            g_InputBindingUiPainted =
                g_InputBindingUiMiddleOverlay && g_BzrFn_SetTextureOff &&
                ShellScreens::IsAvailable() &&
                ShellScreens::IsTextureDeployed(kInputBindingPanelTexture) &&
                ShellScreens::IsTextureDeployed("osh_key_hv.png") &&
                ShellScreens::IsTextureDeployed("osh_tool_hv.png");
            const UiOptionsPageLayout layout = GetInputBindingUiLayout();
            static const InputBindingUiSkin kKeySkin = { "osh_key_hv.png", "osh_key_ck.png" };
            static const InputBindingUiSkin kToolSkin = { "osh_tool_hv.png", "osh_tool_ck.png" };

            const unsigned screenTag = static_cast<unsigned>(reinterpret_cast<uintptr_t>(screen));
            char controlName[64] = {};

            std::snprintf(controlName, sizeof(controlName), "OpenShimInputHeader_%08X", screenTag);
            if (g_InputBindingUiPainted)
            {
                g_BzrFn_SetTextureOff(g_InputBindingUiMiddleOverlay, kInputBindingPanelTexture);
                if (!g_InputBindingUiHeaderLabel)
                    g_InputBindingUiHeaderLabel = ShellScreens::AddLabel(
                        controlParent, controlParent, controlName,
                        { layout.title.x, layout.title.y, layout.title.width, layout.title.height },
                        "", ShellScreens::kTitleLabelFlags);
            }
            else
            {
                UiOptionsPageBackgroundSlots background = {};
                background.topMask = &g_InputBindingUiTopMask;
                background.contentMask = &g_InputBindingUiContentMask;
                CreateInputBindingUiPageBackground(background,
                                                   g_InputBindingUiDecor,
                                                   visualParent,
                                                   controlParent,
                                                   "OpenShimInput",
                                                   screenTag,
                                                   layout);
                CreateInputBindingUiLabel(g_InputBindingUiHeaderLabel, controlParent, controlName, "",
                                          layout.title.x, layout.title.y,
                                          layout.title.width, layout.title.height);
            }
            std::snprintf(controlName, sizeof(controlName), "OpenShimInputStatus_%08X", screenTag);
            CreateInputBindingUiLabel(g_InputBindingUiStatusLabel, controlParent, controlName, "",
                                      layout.statusLine1.x, layout.statusLine1.y,
                                      layout.statusLine1.width, layout.statusLine1.height);
            std::snprintf(controlName, sizeof(controlName), "OpenShimInputStatus2_%08X", screenTag);
            CreateInputBindingUiLabel(g_InputBindingUiStatusDetailLabel, controlParent, controlName, "",
                                      layout.statusLine2.x, layout.statusLine2.y,
                                      layout.statusLine2.width, layout.statusLine2.height);
            std::snprintf(controlName, sizeof(controlName), "OpenShimInputPage_%08X", screenTag);
            CreateInputBindingUiLabel(g_InputBindingUiPageLabel, controlParent, controlName, "",
                                      layout.contextLine1.x, layout.contextLine1.y,
                                      layout.contextLine1.width, layout.contextLine1.height);
            UiDecorRect toolbar[kInputBindingUiToolbarSlotCount] = {};
            LayoutUiToolbarRow(layout,
                               kInputBindingUiToolbarWidths,
                               kInputBindingUiToolbarSlotCount,
                               kInputBindingUiToolbarRightGroup,
                               toolbar,
                               kInputBindingUiToolbarSlotCount);

            g_InputBindingUiSkin = g_InputBindingUiPainted ? &kToolSkin : nullptr;
            std::snprintf(controlName, sizeof(controlName), "OpenShimInputBack_%08X", screenTag);
            CreateInputBindingUiButton(g_InputBindingUiBackButton, controlParent, controlName, "Back",
                                       toolbar[0].x, toolbar[0].y, toolbar[0].width, toolbar[0].height,
                                       reinterpret_cast<void*>(InputBindingBackClick));
            std::snprintf(controlName, sizeof(controlName), "OpenShimInputDefaults_%08X", screenTag);
            CreateInputBindingUiButton(g_InputBindingUiDefaultsButton, controlParent, controlName,
                                       "Reset Controls",
                                       toolbar[1].x, toolbar[1].y, toolbar[1].width, toolbar[1].height,
                                       reinterpret_cast<void*>(InputBindingDefaultsClick));
            std::snprintf(controlName, sizeof(controlName), "OpenShimInputFamily_%08X", screenTag);
            CreateInputBindingUiButton(g_InputBindingUiInputFamilyButton, controlParent, controlName,
                                       "Controls",
                                       toolbar[2].x, toolbar[2].y, toolbar[2].width, toolbar[2].height,
                                       reinterpret_cast<void*>(InputBindingFamilyInputClick));
            std::snprintf(controlName, sizeof(controlName), "OpenShimGameKeyFamily_%08X", screenTag);
            CreateInputBindingUiButton(g_InputBindingUiGameKeyFamilyButton, controlParent, controlName,
                                       "RTS Actions",
                                       toolbar[3].x, toolbar[3].y, toolbar[3].width, toolbar[3].height,
                                       reinterpret_cast<void*>(InputBindingFamilyGameKeyClick));
            std::snprintf(controlName, sizeof(controlName), "OpenShimInputPrev_%08X", screenTag);
            CreateInputBindingUiButton(g_InputBindingUiPrevPageButton, controlParent, controlName,
                                       "Prev",
                                       toolbar[4].x, toolbar[4].y, toolbar[4].width, toolbar[4].height,
                                       reinterpret_cast<void*>(InputBindingPrevPageClick));
            std::snprintf(controlName, sizeof(controlName), "OpenShimInputNext_%08X", screenTag);
            CreateInputBindingUiButton(g_InputBindingUiNextPageButton, controlParent, controlName,
                                       "Next",
                                       toolbar[5].x, toolbar[5].y, toolbar[5].width, toolbar[5].height,
                                       reinterpret_cast<void*>(InputBindingNextPageClick));
            std::snprintf(controlName, sizeof(controlName), "OpenShimInputReload_%08X", screenTag);
            CreateInputBindingUiButton(g_InputBindingUiRefreshButton, controlParent, controlName,
                                       "Refresh",
                                       toolbar[6].x, toolbar[6].y, toolbar[6].width, toolbar[6].height,
                                       reinterpret_cast<void*>(InputBindingRefreshClick));

            g_InputBindingUiSkin = g_InputBindingUiPainted ? &kKeySkin : nullptr;
            for (size_t slot = 0; slot < kInputBindingUiVisibleRowCount; ++slot)
            {
                const size_t column = slot / kInputBindingUiRowsPerColumn;
                const size_t row = slot % kInputBindingUiRowsPerColumn;
                const float baseX = (column == 0) ? layout.rowLeftX : layout.rowRightX;
                const float y = layout.rowStartY + (static_cast<float>(row) * layout.rowPitch);
                std::snprintf(controlName, sizeof(controlName), "OpenShimInputRowPlate_%08X_%02u", screenTag, static_cast<unsigned>(slot));
                if (!g_InputBindingUiPainted)
                    CreateInputBindingUiPlate(g_InputBindingUiRowBackdrops[slot], controlParent, controlName,
                                          baseX - layout.rowPlateInsetX, y,
                                          layout.rowPlateWidth,
                                          layout.rowHeight);
                std::snprintf(controlName, sizeof(controlName), "OpenShimInputRowLabel_%08X_%02u", screenTag, static_cast<unsigned>(slot));
                CreateInputBindingUiLabel(g_InputBindingUiRowLabels[slot], controlParent, controlName, "",
                                          baseX, y + layout.rowLabelYInset,
                                          layout.rowLabelWidth,
                                          layout.rowHeight - layout.rowLabelYInset);
                std::snprintf(controlName, sizeof(controlName), "OpenShimInputRowButton_%08X_%02u", screenTag, static_cast<unsigned>(slot));
                CreateInputBindingUiButton(g_InputBindingUiRowButtons[slot], controlParent, controlName, "",
                                           baseX + layout.rowValueOffsetX, y,
                                           layout.rowValueWidth, layout.rowHeight,
                                           kInputBindingRowClickCallbacks[slot]);
            }
            g_InputBindingUiSkin = nullptr;
        }


        static std::string BuildInputBindingKeyNameFromCode(uint32_t keyCode)
        {
            if (!g_BzrFn_MapKeyNameFromCode)
                return {};

            char keyName[64] = {};
            g_BzrFn_MapKeyNameFromCode(keyCode, keyName);
            return TrimAsciiCopy(keyName);
        }

        static std::string BuildGameKeyTokenFromVk(uint32_t key, uint32_t keyCode)
        {
            switch (key)
            {
            case VK_BACK: return "BSP";
            case VK_TAB: return "TAB";
            case VK_RETURN: return "ENTER";
            case VK_ESCAPE: return "ESC";
            case VK_SPACE: return "SPACE";
            case VK_PAUSE: return "PAUSE";
            case VK_CAPITAL: return "CAPS";
            case VK_UP: return "GreyUpArrow";
            case VK_DOWN: return "GreyDownArrow";
            case VK_LEFT: return "GreyLeftArrow";
            case VK_RIGHT: return "GreyRightArrow";
            case VK_INSERT: return "Insert";
            case VK_DELETE: return "GreyDelete";
            case VK_HOME: return "Home";
            case VK_END: return "End";
            case VK_PRIOR: return "PageUp";
            case VK_NEXT: return "PageDown";
            default:
                break;
            }

            if ((key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9'))
                return std::string(1, static_cast<char>(key));
            if (key >= VK_F1 && key <= VK_F12)
                return "F" + std::to_string(static_cast<unsigned>(key - VK_F1 + 1));

            switch (key)
            {
            case VK_OEM_3: return "`";
            case VK_OEM_MINUS: return "-";
            case VK_OEM_PLUS: return "=";
            case VK_OEM_4: return "[";
            case VK_OEM_6: return "]";
            case VK_OEM_5: return "\\";
            case VK_OEM_1: return ";";
            case VK_OEM_7: return "'";
            case VK_OEM_COMMA: return ",";
            case VK_OEM_PERIOD: return ".";
            case VK_OEM_2: return "/";
            default:
                break;
            }

            std::string fallback = BuildInputBindingKeyNameFromCode(keyCode);
            if (_stricmp(fallback.c_str(), "Escape") == 0)
                return "ESC";
            if (_stricmp(fallback.c_str(), "Backspace") == 0)
                return "BSP";
            if (_stricmp(fallback.c_str(), "CapsLock") == 0 ||
                _stricmp(fallback.c_str(), "CAPSLock") == 0)
            {
                return "CAPS";
            }
            if (_stricmp(fallback.c_str(), "Enter") == 0 ||
                _stricmp(fallback.c_str(), "Return") == 0)
            {
                return "ENTER";
            }
            return fallback;
        }

        static bool BuildGameKeyChordFromKey(uint32_t key, uint32_t keyCode, std::string& outChord)
        {
            outChord.clear();
            if (key == VK_SHIFT || key == VK_CONTROL || key == VK_MENU)
                return false;

            const std::string token = BuildGameKeyTokenFromVk(key, keyCode);
            if (token.empty())
                return false;

            std::vector<std::string> parts;
            if ((GetKeyState(VK_CONTROL) & 0x8000) != 0)
                parts.push_back("CTRL");
            if ((GetKeyState(VK_SHIFT) & 0x8000) != 0)
                parts.push_back("SHIFT");
            if ((GetKeyState(VK_MENU) & 0x8000) != 0)
                parts.push_back("ALT");
            parts.push_back(token);
            outChord = JoinStrings(parts, "+");
            return true;
        }

        static bool AssignGameKeyBindingChord(const std::string& action,
                                              const std::string& newChord,
                                              std::string& outError)
        {
            outError.clear();
            if (action.empty() || newChord.empty())
            {
                outError = "empty action or chord";
                return false;
            }

            if (!SetGameKeyBindingPrimaryChord(action, newChord, outError))
                return false;

            if (g_BzrFn_ReloadGameKeyMap)
                g_BzrFn_ReloadGameKeyMap();
            return true;
        }

        static void OnInputBindingRowButtonClicked(size_t visibleSlot)
        {
            if (visibleSlot >= kInputBindingUiVisibleRowCount)
                return;

            const int rowIndex = g_InputBindingUiVisibleRowIndices[visibleSlot];
            if (rowIndex < 0 || static_cast<size_t>(rowIndex) >= g_InputBindingUiRows.size())
                return;

            const InputBindingUiRow& row = g_InputBindingUiRows[static_cast<size_t>(rowIndex)];
            const std::string displayText =
                row.displayText.empty() ? HumanizeInputBindingCommand(row.command) : row.displayText;
            g_InputBindingUiPendingFamily = row.family;
            g_InputBindingUiPendingCommand = row.command;
            g_InputBindingUiPendingDisplayText = displayText;
            g_InputBindingUiStatusText =
                "Press a key for " + g_InputBindingUiPendingDisplayText + ". ESC cancels.";
            Log(L"[INPUTUI] Pending capture family=%hs slot=%u command=%hs display=%hs\n",
                row.family == InputBindingMapFamily::GameKey ? "gamekey" : "input",
                static_cast<unsigned>(visibleSlot),
                row.command.c_str(),
                displayText.c_str());
            RefreshInputBindingUiControls();
        }

        static void OnInputBindingBackClicked()
        {
            auto* const backClick = reinterpret_cast<void(__cdecl*)()>(g_OptionsInputBackClickAddr);
            if (backClick)
            {
                Log(L"[INPUTUI] Invoking stock Back callback\n");
                backClick();
            }
        }

        static void OnInputBindingDefaultsClicked()
        {
            auto* const defaultsClick = reinterpret_cast<void(__cdecl*)()>(g_OptionsInputDefaultsClickAddr);
            if (defaultsClick)
            {
                Log(L"[INPUTUI] Invoking stock input default reset callback\n");
                defaultsClick();
            }

            TryLiveReloadInputMapTables();
            ReloadInputBindingUiInventory(true);
            g_InputBindingUiPageStart =
                ClampInputBindingUiPageStart(g_InputBindingUiActiveFamily, g_InputBindingUiPageStart);
            g_InputBindingUiPendingCommand.clear();
            g_InputBindingUiPendingDisplayText.clear();
            g_InputBindingUiStatusText = "Reset input.map defaults and reloaded key maps.";
            RefreshInputBindingUiControls();
        }

        static void OnInputBindingFamilyButtonClicked(InputBindingMapFamily family)
        {
            g_InputBindingUiActiveFamily = family;
            g_InputBindingUiPageStart = 0;
            RefreshInputBindingUiControls();
        }

        static void OnInputBindingPageStepClicked(int direction)
        {
            const size_t current = g_InputBindingUiPageStart;
            if (direction < 0)
            {
                g_InputBindingUiPageStart =
                    current >= kInputBindingUiVisibleRowCount ? current - kInputBindingUiVisibleRowCount : 0;
            }
            else if (direction > 0)
            {
                g_InputBindingUiPageStart = current + kInputBindingUiVisibleRowCount;
            }

            g_InputBindingUiPageStart =
                ClampInputBindingUiPageStart(g_InputBindingUiActiveFamily, g_InputBindingUiPageStart);
            RefreshInputBindingUiControls();
        }

        static void OnInputBindingRefreshClicked()
        {
            ReloadInputBindingUiInventory(true);
            g_InputBindingUiPageStart =
                ClampInputBindingUiPageStart(g_InputBindingUiActiveFamily, g_InputBindingUiPageStart);
            g_InputBindingUiStatusText = "Reloaded input.map and gamekey.map.";
            RefreshInputBindingUiControls();
        }

        // KeyConfig layout confirmed against the 1.5 PDB object model: nKeyCount at
        // +0, _KeyItem[100] at +4, each entry cKeyName[0x100] at +0,
        // cKeyFunction[0x100] at +0x100, nReserved at +0x200 (stride 0x204).
        struct KeyConfigEntryView
        {
            const char* keyName = nullptr;
            const char* function = nullptr;
            int reserved = 0;
        };

        static bool IsPrintableAsciiZ(const char* text, size_t maxLen)
        {
            for (size_t index = 0; index < maxLen; ++index)
            {
                const char ch = text[index];
                if (ch == '\0')
                    return true;
                if (ch < 0x20 || ch > 0x7E)
                    return false;
            }
            return false;
        }

        static bool TryFindKeyConfigEntry(void* keyConfig,
                                          const char* command,
                                          KeyConfigEntryView& outEntry,
                                          bool& outTableValid)
        {
            constexpr size_t kListOffset = 4;
            constexpr size_t kEntryStride = 0x204;
            constexpr size_t kFunctionOffset = 0x100;
            constexpr size_t kReservedOffset = 0x200;
            constexpr int kMaxEntries = 100;

            outEntry = {};
            outTableValid = false;
            if (!keyConfig || !command || !*command)
                return false;

            const int count = *reinterpret_cast<const int*>(keyConfig);
            if (count <= 0 || count > kMaxEntries)
                return false;

            const uint8_t* listBase = reinterpret_cast<const uint8_t*>(keyConfig) + kListOffset;
            const char* firstName = reinterpret_cast<const char*>(listBase);
            const char* firstFunction = reinterpret_cast<const char*>(listBase + kFunctionOffset);
            if (!IsPrintableAsciiZ(firstName, kFunctionOffset) ||
                !IsPrintableAsciiZ(firstFunction, kFunctionOffset) ||
                *firstFunction == '\0')
            {
                return false;
            }

            outTableValid = true;
            for (int index = 0; index < count; ++index)
            {
                const uint8_t* entry = listBase + static_cast<size_t>(index) * kEntryStride;
                const char* function = reinterpret_cast<const char*>(entry + kFunctionOffset);
                if (!IsPrintableAsciiZ(function, kFunctionOffset))
                    continue;
                if (_stricmp(function, command) != 0)
                    continue;

                outEntry.keyName = reinterpret_cast<const char*>(entry);
                outEntry.function = function;
                outEntry.reserved = *reinterpret_cast<const int*>(entry + kReservedOffset);
                return true;
            }
            return false;
        }

        // Mirrors the stock alreadyBound rule, but across every parsed block so
        // extended commands participate in conflict detection too.
        static const InputBindingCommandBlock* FindInputMapKeyOwner(
            const std::string& keyName,
            const std::string& excludeCommand)
        {
            for (const InputBindingCommandBlock& block : g_InputBindingCommandBlocks)
            {
                if (_stricmp(block.command.c_str(), excludeCommand.c_str()) == 0)
                    continue;
                for (const std::string& token : block.positiveKeyboardTokens)
                {
                    if (_stricmp(token.c_str(), keyName.c_str()) == 0)
                        return &block;
                }
            }
            return nullptr;
        }

        // Redux read_mapping_table (legacy 0x004BBD49) recovered at 0x00620010; it
        // fully re-reads input.map plus the giddi device templates into the live
        // tables. Byte-verified before first use so a drifted binary degrades to a
        // restart notice instead of a wild call.
        // POD-only helper so __try/__except is valid around the stock parser.
        static bool CallReloadMappingTableGuarded(FnReloadGameKeyMap readMappingTable)
        {
            __try
            {
                readMappingTable();
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool TryLiveReloadInputMapTables()
        {
            if (!g_InputMapLiveReloadChecked)
            {
                g_InputMapLiveReloadChecked = true;
                g_ReadMappingTableAddr = HookEngine::EngineAddress("ReadMappingTable");
                g_InputMapLiveReloadAvailable = g_ReadMappingTableAddr != 0;
                Log(L"[INPUTUI] Live input.map reload %hs at 0x%08X\n",
                    g_InputMapLiveReloadAvailable ? "available" : "unavailable (bytes mismatch)",
                    static_cast<uint32_t>(g_ReadMappingTableAddr));
            }

            if (!g_InputMapLiveReloadAvailable)
                return false;

            auto* readMappingTable =
                reinterpret_cast<FnReloadGameKeyMap>(g_ReadMappingTableAddr);
            if (!CallReloadMappingTableGuarded(readMappingTable))
            {
                // The stock parser crashed mid-reload once (dump 30940, AV in a
                // msvcr120 copy reached from 0x00620010). Trading a stale table
                // for a crash-to-desktop: report failure and stop retrying.
                g_InputMapLiveReloadAvailable = false;
                Log(L"[INPUTUI] Live input.map reload faulted at 0x%08X; disabled for this session\n",
                    static_cast<uint32_t>(g_ReadMappingTableAddr));
                return false;
            }
            return true;
        }

        static bool HandleCapturedInputBindingKey(void* screen, uint32_t key, uint32_t keyCode)
        {
            if (g_InputBindingUiPendingCommand.empty())
                return false;

            Log(L"[INPUTUI] Capture key family=%hs command=%hs vk=0x%02X keyCode=0x%02X screen=0x%08X\n",
                g_InputBindingUiPendingFamily == InputBindingMapFamily::GameKey ? "gamekey" : "input",
                g_InputBindingUiPendingCommand.c_str(),
                static_cast<unsigned>(key & 0xFFu),
                static_cast<unsigned>(keyCode & 0xFFu),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(screen)));

            if (key == VK_ESCAPE)
            {
                g_InputBindingUiPendingCommand.clear();
                g_InputBindingUiPendingDisplayText.clear();
                g_InputBindingUiStatusText = "Capture cancelled.";
                RefreshInputBindingUiControls();
                return true;
            }

            const size_t rowIndex =
                FindInputBindingUiRowIndex(g_InputBindingUiPendingFamily, g_InputBindingUiPendingCommand);
            if (rowIndex >= g_InputBindingUiRows.size())
            {
                g_InputBindingUiPendingCommand.clear();
                g_InputBindingUiPendingDisplayText.clear();
                g_InputBindingUiStatusText = "Pending binding row was no longer available.";
                RefreshInputBindingUiControls();
                return true;
            }

            // Copies, not references: ReloadInputBindingUiInventory rebuilds the row
            // vector before the success status is composed.
            const InputBindingMapFamily rowFamily = g_InputBindingUiRows[rowIndex].family;
            const std::string command = g_InputBindingUiRows[rowIndex].command;
            const std::string displayText = g_InputBindingUiRows[rowIndex].displayText.empty()
                ? HumanizeInputBindingCommand(command)
                : g_InputBindingUiRows[rowIndex].displayText;

            if (rowFamily == InputBindingMapFamily::Input)
            {
                std::string keyName = BuildInputBindingKeyNameFromCode(keyCode);
                // Some keyboard providers (including accessibility and remote-input
                // tools) supply a valid virtual key without the legacy scan-code
                // value expected by the stock mapper. Keep capture usable in that
                // case by falling back to the equivalent input.map token.
                if (keyName.empty())
                    keyName = BuildGameKeyTokenFromVk(key, keyCode);
                if (keyName.empty())
                {
                    g_InputBindingUiStatusText = "That key is not available for input.map bindings.";
                    Log(L"[INPUTUI] Capture rejected: no stock key name for keyCode=0x%02X\n",
                        static_cast<unsigned>(keyCode & 0xFFu));
                    RefreshInputBindingUiControls();
                    return true;
                }

                if (const InputBindingCommandBlock* owner = FindInputMapKeyOwner(keyName, command))
                {
                    const std::string ownerText = !owner->comment.empty()
                        ? owner->comment
                        : HumanizeInputBindingCommand(owner->command);
                    g_InputBindingUiStatusText =
                        keyName + " is already bound to " + ownerText + ".";
                    Log(L"[INPUTUI] Capture rejected: key=%hs already owned by command=%hs\n",
                        keyName.c_str(),
                        owner->command.c_str());
                    RefreshInputBindingUiControls();
                    return true;
                }

                void* keyConfig = nullptr;
                if (screen)
                {
                    auto* screenBytes = reinterpret_cast<uint8_t*>(screen);
                    keyConfig = *reinterpret_cast<void**>(screenBytes + kOptionsInputKeyConfigOffset);
                }

                // Stock-managed commands keep KeyConfig::set_key so the native table
                // stays consistent; extended commands are not in that table (set_key
                // would reject them) and go straight to the file writer.
                KeyConfigEntryView stockEntry = {};
                bool stockTableValid = false;
                const bool stockManaged =
                    TryFindKeyConfigEntry(keyConfig, command.c_str(), stockEntry, stockTableValid);
                if (keyConfig && !stockTableValid)
                {
                    Log(L"[INPUTUI] KeyConfig table at 0x%08X failed layout sanity check; treating %hs as extended\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(keyConfig)),
                        command.c_str());
                }

                if (stockManaged)
                {
                    if (stockEntry.reserved != 0)
                    {
                        g_InputBindingUiStatusText =
                            displayText + " is reserved by the game and cannot be rebound.";
                        Log(L"[INPUTUI] Capture rejected: command=%hs is reserved\n",
                            command.c_str());
                        RefreshInputBindingUiControls();
                        return true;
                    }

                    if (g_BzrFn_KeyConfigSetKey &&
                        g_BzrFn_KeyConfigSetKey(keyConfig, command.c_str(), keyName.c_str()) == 0)
                    {
                        g_InputBindingUiStatusText =
                            "Binding rejected for " + displayText +
                            ". The stock key table refused " + keyName + ".";
                        Log(L"[INPUTUI] Capture rejected by KeyConfig::set_key command=%hs key=%hs\n",
                            command.c_str(),
                            keyName.c_str());
                        RefreshInputBindingUiControls();
                        return true;
                    }
                }

                std::string writeError;
                if (!SetInputMapPrimaryKeyboardBinding(command, keyName, writeError))
                {
                    g_InputBindingUiStatusText =
                        "Could not save input.map. Check file permissions; details are in OpenShim.log.";
                    Log(L"[INPUTUI] input.map write failed command=%hs key=%hs error=%hs\n",
                        command.c_str(),
                        keyName.c_str(),
                        writeError.c_str());
                    RefreshInputBindingUiControls();
                    return true;
                }

                const bool liveReload = TryLiveReloadInputMapTables();
                ReloadInputBindingUiInventory(true);
                g_InputBindingUiPendingCommand.clear();
                g_InputBindingUiPendingDisplayText.clear();
                g_InputBindingUiStatusText = "Bound " + displayText + " to " + keyName +
                    (liveReload ? "." : ". Takes effect after restart.");
                Log(L"[INPUTUI] Bound input command=%hs key=%hs stockManaged=%hs liveReload=%hs\n",
                    command.c_str(),
                    keyName.c_str(),
                    stockManaged ? "yes" : "no",
                    liveReload ? "yes" : "no");
                RefreshInputBindingUiControls();
                return true;
            }

            std::string chord;
            if (!BuildGameKeyChordFromKey(key, keyCode, chord))
            {
                g_InputBindingUiStatusText =
                    "Press a non-modifier key for " + g_InputBindingUiPendingDisplayText + ".";
                Log(L"[INPUTUI] Capture rejected for gamekey command=%hs because chord build failed\n",
                    command.c_str());
                RefreshInputBindingUiControls();
                return true;
            }

            std::string assignError;
            if (!AssignGameKeyBindingChord(command, chord, assignError))
            {
                g_InputBindingUiStatusText =
                    "Could not save gamekey.map. Check file permissions; details are in OpenShim.log.";
                Log(L"[INPUTUI] Failed writing gamekey command=%hs chord=%hs error=%hs\n",
                    command.c_str(),
                    chord.c_str(),
                    assignError.c_str());
                RefreshInputBindingUiControls();
                return true;
            }

            ReloadInputBindingUiInventory(true);
            g_InputBindingUiPendingCommand.clear();
            g_InputBindingUiPendingDisplayText.clear();
            g_InputBindingUiStatusText = "Bound " + displayText + " to " + chord + ".";
            Log(L"[INPUTUI] Bound gamekey action=%hs chord=%hs\n",
                command.c_str(),
                chord.c_str());
            RefreshInputBindingUiControls();
            return true;
        }

        static void InitializeInputBindingUiScaffold()
        {
            if (g_InputBindingUiScaffoldInitialized)
                return;
            g_InputBindingUiScaffoldInitialized = true;

            g_InputBindingInstallDirectory = ResolveInputBindingInstallDirectory();
            g_InputScreenBinding.Unbind();
            g_InputBindingUiActiveFamily = InputBindingMapFamily::Input;
            g_InputBindingUiPageStart = 0;
            ResetInputBindingUiVisuals();
            RecoverMissingInputMap();
            ReloadInputBindingUiInventory(true);
            LogInputBindingUiScaffoldSummary();
        }


        static void OnOptionsInputPopulateUiScaffold(void* screen)
        {
            InitializeInputBindingUiScaffold();

            if (!screen)
                return;

            // This is called only after a fresh stock constructor. The shell can
            // recycle the same screen address, so pointer equality is not proof
            // that injected children are still alive. Always discard cached child
            // pointers before decorating the new instance.
            ResetInputBindingUiVisuals();
            g_InputScreenBinding.BindConstructed(screen);

            if (!ShouldEnableInputBindingUiReplacement())
                return;

            EnsureInputBindingUiControls(screen);
            RefreshInputBindingUiControls();
            Log(L"[INPUTUI] Constructor hook screen=0x%08X gen=%u rows=%u liveUi=%hs keyRelease=%hs\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(screen)),
                g_InputScreenBinding.generation,
                static_cast<unsigned>(g_InputBindingUiRows.size()),
                "yes",
                g_InputBindingUiKeyReleasedHookInstalled ? "yes" : "no");
        }

        // The engine is destroying a hooked input screen: every child view we
        // injected dies with it. Forget them all before the memory is freed so
        // no later click/refresh path can touch a dangling pointer.
        static void OnOptionsInputScreenDestroyed(void* screen)
        {
            if (!screen)
                return;

            if (!g_InputScreenBinding.Owns(screen))
                return;

            ResetInputBindingUiVisuals();
            g_InputScreenBinding.Unbind();
            Log(L"[INPUTUI] Input screen destroyed; binding cleared screen=0x%08X gen=%u\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(screen)),
                g_InputScreenBinding.generation);
        }

        static void OnOptionsParentScreenDestroyed(void* screen)
        {
            if (!g_ParentScreenBinding.Owns(screen))
                return;

            g_ParentScreenBinding.Unbind();
            g_ShimSettingsMenuButton = nullptr;
        }

        static void EnsureOptionsScreenDtorHook(uintptr_t dtorAddr,
                                                InlineDetour32& detour,
                                                void* hook,
                                                FnOptionsScreenDtor& original,
                                                bool& installed,
                                                bool& attempted,
                                                const wchar_t* logTag)
        {
            if (installed || attempted)
                return;
            attempted = true;

            // Shared MSVC dtor prologue: push ebp / mov ebp,esp / push ecx /
            // mov [ebp-4],ecx / mov eax,[ebp-4] (10 bytes, instruction aligned).
            static const uint8_t kExpectedOptionsScreenDtorBytes[kOptionsScreenDtorDetourLen] =
            {
                0x55, 0x8B, 0xEC, 0x51, 0x89, 0x4D, 0xFC, 0x8B, 0x45, 0xFC
            };

            if (!ExpectedBytesMatchAt(dtorAddr,
                                      kExpectedOptionsScreenDtorBytes,
                                      sizeof(kExpectedOptionsScreenDtorBytes)))
            {
                Log(L"[%ls] Screen dtor bytes mismatch at 0x%08X; lifetime tracking unavailable\n",
                    logTag, static_cast<uint32_t>(dtorAddr));
                return;
            }

            if (!InstallInlineDetour32(detour,
                                       dtorAddr,
                                       hook,
                                       kOptionsScreenDtorDetourLen,
                                       kExpectedOptionsScreenDtorBytes,
                                       sizeof(kExpectedOptionsScreenDtorBytes)))
            {
                Log(L"[%ls] Failed installing screen dtor hook at 0x%08X\n",
                    logTag, static_cast<uint32_t>(dtorAddr));
                return;
            }

            original = reinterpret_cast<FnOptionsScreenDtor>(detour.trampoline);
            installed = (original != nullptr);
            if (installed)
            {
                Log(L"[%ls] Installed screen dtor hook entry=0x%08X trampoline=0x%08X\n",
                    logTag,
                    static_cast<uint32_t>(dtorAddr),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(detour.trampoline)));
            }
        }

        // --- OpenShim button on the stock Options screen -------------------------

        // The stock options column lives inside "Middle_Overlay", the centered
        // 1440-wide panel the cUI_OptionsParent ctor (0x007B61A0) creates; the
        // Back button and the four option buttons are all its children.
        //
        // It is NOT the screen's first child. The screen is built with four
        // full-bleed frame views first, so the child list measured live on the
        // GOG 2.2.301 build is:
        //   [0] Border_Top    (0,0,3840,136)   [1] Border_Bot
        //   [2] Border_Left   [3] Border_Right [4] Middle_Overlay (480,0,2880,2160)
        // Taking begin[0] therefore landed the OpenShim button under Border_Top,
        // which is what killed the top-left Back button: cUI_View's mouse
        // dispatch (0x007D2570 down / 0x007D26C0 up) walks the child list in two
        // passes -- children that themselves have children first, then leaf
        // children -- taking the first that returns true, and a view whose own
        // rect is hit consumes the event after its children decline it. An empty
        // Border_Top is a leaf, so Middle_Overlay (5 children) was dispatched
        // first and Back got the click. Parenting one button to Border_Top
        // promoted that 3840x136 top strip into the first pass ahead of
        // Middle_Overlay, so it swallowed every click in the top 136px -- which
        // is where Back sits. Back's rect is 154px tall, so only the bottom
        // ~18px sliver still reached it: exactly the "sometimes needs a second
        // click" symptom, and a dead button for clicks aimed at its centre.
        //
        // Match the panel by the engine's own view name instead, falling back to
        // the child with the most children (the borders have none) so a renamed
        // view still resolves rather than silently re-breaking Back.
        static const char* ReadUiViewName(void* view);

        static void* ResolveOptionsParentMiddleOverlay(void* parentScreen)
        {
            if (!parentScreen)
                return nullptr;

            void* bestByChildCount = nullptr;
            ptrdiff_t bestChildCount = 0;
            ptrdiff_t bestIndex = -1;

            __try
            {
                auto* const screenBytes = reinterpret_cast<uint8_t*>(parentScreen);
                void** const begin =
                    *reinterpret_cast<void***>(screenBytes + kUiViewChildBeginOffset);
                void** const end =
                    *reinterpret_cast<void***>(screenBytes + kUiViewChildEndOffset);
                if (!begin || !end || begin >= end || (end - begin) >= 64)
                    return nullptr;

                for (void** slot = begin; slot != end; ++slot)
                {
                    void* const child = *slot;
                    if (!child)
                        continue;

                    auto* const childBytes = reinterpret_cast<uint8_t*>(child);
                    if (std::strncmp(reinterpret_cast<const char*>(childBytes + kUiViewNameOffset),
                                     "Middle_Overlay",
                                     sizeof("Middle_Overlay")) == 0)
                    {
                        Log(L"[SETTINGSUI] options parent resolved by name: index=%d "
                            L"view=0x%08X name=%hs\n",
                            static_cast<int>(slot - begin),
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(child)),
                            ReadUiViewName(child));
                        return child;
                    }

                    void** const childBegin =
                        *reinterpret_cast<void***>(childBytes + kUiViewChildBeginOffset);
                    void** const childEnd =
                        *reinterpret_cast<void***>(childBytes + kUiViewChildEndOffset);
                    if (!childBegin || !childEnd || childBegin > childEnd ||
                        (childEnd - childBegin) >= 256)
                    {
                        continue;
                    }

                    const ptrdiff_t childCount = childEnd - childBegin;
                    if (childCount > bestChildCount)
                    {
                        bestChildCount = childCount;
                        bestByChildCount = child;
                        bestIndex = slot - begin;
                    }
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }

            // The name match is the expected path. Reaching the fallback means the
            // screen layout moved, so say so loudly rather than silently adopting
            // whichever view happened to have the most children.
            Log(L"[SETTINGSUI] options parent NAME MATCH FAILED; fallback index=%d "
                L"view=0x%08X name=%hs children=%d\n",
                static_cast<int>(bestIndex),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(bestByChildCount)),
                ReadUiViewName(bestByChildCount),
                static_cast<int>(bestChildCount));

            return bestByChildCount;
        }

        // --- Options-screen tree instrumentation ---------------------------------
        //
        // The Back-button quirk (design doc UI #4) was root-caused from the
        // cUI_OptionsParent ctor decompile alone. Disassembling the dispatch
        // itself (2026-08-05) showed that model cannot produce the symptom:
        //   cUI_View::OnMouseDown 0x7D2570 / OnMouseUp 0x7D26C0 walk +0x12C in
        //   two passes -- children that themselves have children first, then
        //   leaf children -- taking the first that returns true, and finally
        //   consuming the event themselves if their own rect is hit. Buttons
        //   are leaves (the caption at +0x144 is not AddChild'd), Back is the
        //   overlay's child[0], so appending a sixth leaf cannot starve it.
        //
        // Rather than guess again, measure: dump the real tree once per Options
        // construction so the rects, flags, parents and click slots that the
        // dispatch actually sees are on the record.
        static const char* ReadUiViewName(void* view)
        {
            static char name[0xC8 + 1];
            name[0] = '\0';
            if (!view)
                return name;

            __try
            {
                const char* const raw = reinterpret_cast<const char*>(
                    reinterpret_cast<uint8_t*>(view) + kUiViewNameOffset);
                size_t index = 0;
                for (; index < 0xC8; ++index)
                {
                    const char ch = raw[index];
                    if (ch == '\0')
                        break;
                    name[index] = (ch >= 0x20 && ch <= 0x7E) ? ch : '?';
                }
                name[index] = '\0';
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                name[0] = '\0';
            }
            return name;
        }

        static void LogUiViewNode(const wchar_t* tag, void* view, unsigned depth)
        {
            if (!view || depth > 2)
                return;

            __try
            {
                auto* const bytes = reinterpret_cast<uint8_t*>(view);
                const auto* const rect = reinterpret_cast<const float*>(bytes + 4);
                void** const begin = *reinterpret_cast<void***>(bytes + kUiViewChildBeginOffset);
                void** const end = *reinterpret_cast<void***>(bytes + kUiViewChildEndOffset);
                const ptrdiff_t childCount =
                    (begin && end && begin <= end && (end - begin) < 256) ? (end - begin) : -1;
                const uintptr_t vtable = *reinterpret_cast<uintptr_t*>(bytes);
                const bool isButton = (vtable == g_UiButtonVtableAddr);

                Log(L"[SETTINGSUI] %ls depth=%u view=0x%08X vt=0x%08X name=%hs "
                    L"rect=(%.1f,%.1f,%.1f,%.1f) flags=0x%X vis=%u layer=%u "
                    L"parent=0x%08X shell=0x%08X children=%d%ls\n",
                    tag,
                    depth,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(view)),
                    static_cast<uint32_t>(vtable),
                    ReadUiViewName(view),
                    rect[0], rect[1], rect[2], rect[3],
                    *reinterpret_cast<uint32_t*>(bytes + 0x14),
                    static_cast<unsigned>(bytes[0xE9]),
                    static_cast<unsigned>(bytes[0xE8]),
                    static_cast<uint32_t>(*reinterpret_cast<uintptr_t*>(bytes + 0x13C)),
                    static_cast<uint32_t>(*reinterpret_cast<uintptr_t*>(bytes + 0x138)),
                    static_cast<int>(childCount),
                    isButton ? L" [button]" : L"");

                if (isButton)
                {
                    Log(L"[SETTINGSUI]   button enabled=%u onHover=0x%08X onClick=0x%08X\n",
                        static_cast<unsigned>(bytes[0x148]),
                        static_cast<uint32_t>(
                            *reinterpret_cast<uintptr_t*>(bytes + kUiButtonOnHoverOffset)),
                        static_cast<uint32_t>(
                            *reinterpret_cast<uintptr_t*>(bytes + kUiButtonOnClickOffset)));
                }

                for (ptrdiff_t index = 0; index < childCount; ++index)
                    LogUiViewNode(tag, begin[index], depth + 1);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[SETTINGSUI] %ls depth=%u view=0x%08X <faulted while reading>\n",
                    tag,
                    depth,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(view)));
            }
        }

        // The stock Options column (cUI_OptionsParent ctor 0x007B61A0): four
        // 422x130 buttons at x 508, y 208 / 386 / 564 / 741, resting on four
        // slots painted into esc_center.png. With OpenShim's panel art
        // deployed the column becomes five even slots (OPTIONS_LAYOUT in
        // mkscreens.py): the panel is swapped for osh_options_center.png and
        // the four stock buttons are moved onto its slots (design rect
        // rewritten, layout run again), with OpenShim Options as the fifth.
        // Without the art the
        // stock layout is left alone and the button squeezes in underneath.
        constexpr const char* kOptionsPanelTexture = "osh_options_center.png";
        constexpr float kOptionsColumnX = 508.0f;
        constexpr float kOptionsColumnW = 422.0f;
        constexpr float kOptionsSlotY0 = 180.0f;
        constexpr float kOptionsSlotH = 120.0f;
        constexpr float kOptionsSlotPitch = 150.0f;
        constexpr size_t kOptionsStockButtonCount = 4;
        // The stock option buttons' caption scale (FUN_007c30e0(1.3f)).
        constexpr float kOptionsButtonTextScale = 1.3f;

        // cUI_View keeps the ctor's design rect (1440x1080 space) at +0xEC and
        // the laid-out screen rect at +4; the ctor runs the layout
        // (UiWidgetLayout, 0x007D14B0) immediately, so moving a built widget
        // means rewriting the design rect and running the layout again, as
        // the map preview fix does.
        constexpr size_t kUiViewDesignRectOffset = 0xEC;
        using FnUiWidgetLayout = void(__thiscall*)(void* view, float x, float y, float w, float h);

        static FnUiWidgetLayout ResolveUiWidgetLayout()
        {
            static const FnUiWidgetLayout layout = [] {
                uint32_t address = 0;
                const HookEngine::EngineRow rows[] = { { "UiWidgetLayout", &address } };
                if (!HookEngine::BindEngineRows("Options column", rows))
                    return FnUiWidgetLayout{};
                return reinterpret_cast<FnUiWidgetLayout>(static_cast<uintptr_t>(address));
            }();
            return layout;
        }

        // Finds the four stock column buttons by their ctor design rect and
        // moves them onto the five-slot column. All or nothing: a column that
        // does not look stock is left exactly as built.
        static bool RespaceStockOptionsColumn(void* overlay)
        {
            const FnUiWidgetLayout layout = ResolveUiWidgetLayout();
            if (!layout)
                return false;
            std::array<uint8_t*, kOptionsStockButtonCount> buttons = {};
            size_t found = 0;
            __try
            {
                auto* const bytes = reinterpret_cast<uint8_t*>(overlay);
                void** const begin = *reinterpret_cast<void***>(bytes + kUiViewChildBeginOffset);
                void** const end = *reinterpret_cast<void***>(bytes + kUiViewChildEndOffset);
                if (!begin || !end || begin > end || (end - begin) >= 64)
                    return false;
                for (void** slot = begin; slot != end; ++slot)
                {
                    auto* const child = reinterpret_cast<uint8_t*>(*slot);
                    if (!child || *reinterpret_cast<uintptr_t*>(child) != g_UiButtonVtableAddr)
                        continue;
                    const auto* const design = reinterpret_cast<const float*>(child + kUiViewDesignRectOffset);
                    if (design[0] != kOptionsColumnX || design[2] != kOptionsColumnW || design[3] != 130.0f)
                        continue;
                    if (found == kOptionsStockButtonCount)
                        return false;
                    buttons[found++] = child;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            if (found != kOptionsStockButtonCount)
                return false;

            std::sort(buttons.begin(), buttons.end(), [](const uint8_t* a, const uint8_t* b) {
                return reinterpret_cast<const float*>(a + kUiViewDesignRectOffset)[1] <
                       reinterpret_cast<const float*>(b + kUiViewDesignRectOffset)[1];
            });
            for (size_t i = 0; i < kOptionsStockButtonCount; ++i)
            {
                auto* const design = reinterpret_cast<float*>(buttons[i] + kUiViewDesignRectOffset);
                const float newY = kOptionsSlotY0 + kOptionsSlotPitch * static_cast<float>(i);
                // The caption (+0x144) is its own text view, built by the
                // button ctor on the same layout parent at the button's rect
                // plus the caption offset; it moves with the button.
                auto* const caption = *reinterpret_cast<uint8_t**>(buttons[i] + 0x144);
                if (caption)
                {
                    auto* const captionDesign = reinterpret_cast<float*>(caption + kUiViewDesignRectOffset);
                    captionDesign[1] += newY - design[1];
                    captionDesign[3] = kOptionsSlotH;
                    layout(caption, captionDesign[0], captionDesign[1], captionDesign[2], captionDesign[3]);
                }
                design[1] = newY;
                design[3] = kOptionsSlotH;
                layout(buttons[i], design[0], design[1], design[2], design[3]);
                // A cUI_Text builds its glyphs when its text is set, so the
                // moved caption keeps drawing at the old place until the text
                // is set again. Its buffer is at +0x144 (2000 bytes).
                if (caption && g_BzrFn_SetButtonLabel)
                {
                    char text[256] = {};
                    strncpy_s(text, reinterpret_cast<const char*>(caption + 0x144), _TRUNCATE);
                    g_BzrFn_SetButtonLabel(buttons[i], text);
                }
            }
            return true;
        }

        static void EnsureShimSettingsMenuButton(void* parentScreen)
        {
            if (!parentScreen || !g_BzrFn_ButtonCtor || !g_BzrFn_AddChild ||
                !g_BzrFn_SetOnClick || !g_BzrFn_SetOnHover)
                return;

            if (g_ParentScreenBinding.constructed != parentScreen)
            {
                g_ParentScreenBinding.BindConstructed(parentScreen);
                g_ShimSettingsMenuButton = nullptr;
            }

            if (g_ShimSettingsMenuButton)
                return;

            // Middle_Overlay or nothing. Every other parent on this screen is a
            // full-bleed frame view, and giving any of them a child reorders the
            // screen's click dispatch and starves a stock button (the screen
            // itself is no better: Middle_Overlay spans the whole play area and
            // would then eat this button's own clicks, which is what the
            // 2026-07-17 "parent to screen root" attempt hit). A missing entry
            // point beats a dead Back button, so bail instead of guessing.
            void* const buttonParent = ResolveOptionsParentMiddleOverlay(parentScreen);
            if (!buttonParent)
            {
                Log(L"[SETTINGSUI] Middle_Overlay not found on options screen=0x%08X; "
                    L"skipping OpenShim button\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(parentScreen)));
                return;
            }

            const bool fiveSlots = ShellScreens::IsTextureDeployed(kOptionsPanelTexture) &&
                                   g_BzrFn_SetTextureOff && RespaceStockOptionsColumn(buttonParent);
            if (fiveSlots)
                g_BzrFn_SetTextureOff(buttonParent, kOptionsPanelTexture);
            else
                Log(L"[SETTINGSUI] Options column left stock (%hs); OpenShim button goes underneath\n",
                    ShellScreens::IsTextureDeployed(kOptionsPanelTexture) ? "column not recognised"
                                                                          : "panel art not deployed");

            void* buttonMem = ::operator new(0x1EC, std::nothrow);
            if (!buttonMem)
                return;

            std::memset(buttonMem, 0, 0x1EC);
            // Shares the stock buttons' parent: the layout pass (0x007D14B0)
            // adds Middle_Overlay's absolute origin on top of these design
            // coordinates, so the button lines up with the column at any size.
            const float y = fiveSlots ? kOptionsSlotY0 + kOptionsSlotPitch * kOptionsStockButtonCount : 882.0f;
            const float h = fiveSlots ? kOptionsSlotH : 58.0f;
            void* const button = g_BzrFn_ButtonCtor(buttonMem, "OpenShimSettingsMenuButton",
                                                    kOptionsColumnX, y, kOptionsColumnW, h,
                                                    0x20, buttonParent, 0, 0);
            if (!button)
                return;

            // Like the stock buttons: nothing at rest over a painted slot.
            if (!fiveSlots && g_BzrFn_SetTextureOff) g_BzrFn_SetTextureOff(button, "optionhv.png");
            if (g_BzrFn_SetTextureOver) g_BzrFn_SetTextureOver(button, "optionhv.png");
            if (g_BzrFn_SetTextureOn) g_BzrFn_SetTextureOn(button, "optionck.png");
            if (fiveSlots && g_BzrFn_SetButtonLabel)
            {
                g_BzrFn_SetButtonLabel(button, "OpenShim Options");
                if (g_BzrFn_SetButtonTextScale)
                    g_BzrFn_SetButtonTextScale(button, kOptionsButtonTextScale);
            }
            else
            {
                SetInputBindingUiButtonTextFitted(button, "OpenShim Options", 390.0f);
            }
            g_BzrFn_SetOnClick(button, reinterpret_cast<void*>(ShimSettingsMenuClick));
            g_BzrFn_SetOnHover(button, reinterpret_cast<void*>(InputBindingUiButtonOnHoverNoop));
            // Append as Middle_Overlay's sixth child, alongside Back and the four
            // stock option buttons. All six are leaf views, so they share the
            // dispatch pass and are tried in list order; Back stays at index 0
            // and keeps first refusal on the top-left clicks.
            g_BzrFn_AddChild(buttonParent, button, 0);
            g_ShimSettingsMenuButton = button;

            Log(L"[SETTINGSUI] OpenShim button added to options screen=0x%08X layout=%hs "
                L"rect=(%.1f,%.1f,%.1f,%.1f)\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(parentScreen)),
                fiveSlots ? "five-slot" : "stock+compact",
                kOptionsColumnX, y, kOptionsColumnW, h);
        }

        static void OnOptionsParentCtorScaffold(void* screen)
        {
            if (!screen || !ShouldEnableShimSettingsUi())
                return;

            // Like the input screen, the Options object can be reconstructed at
            // the same address. Never retain a child button across constructors.
            g_ParentScreenBinding.BindConstructed(screen);
            g_ShimSettingsMenuButton = nullptr;
            g_ShimSettingsNavigationTick = 0;
            // This dump is how the Back-button starvation was finally measured,
            // and it is the tool to reach for whenever a widget on this screen
            // stops receiving clicks. Dump the first Options construction of
            // every session unconditionally -- the whole reason this bug
            // survived two fix attempts is that reproducing it required a flag
            // nobody had set -- and let the env var force it on every open.
            static bool dumpedThisSession = false;
            const bool dumpTree =
                !dumpedThisSession || EnvFlagEnabled("OPENSHIM_LOG_OPTIONS_TREE");
            dumpedThisSession = true;

            if (dumpTree)
                LogUiViewNode(L"options-tree-before", screen, 0);
            EnsureShimSettingsMenuButton(screen);
            if (dumpTree)
                LogUiViewNode(L"options-tree-after", screen, 0);
        }




        // ====================================================================
        // MAIN-MENU CAREER PAGE
        // ====================================================================
        //
        // A CAREER button on the title screen, and a page behind it that shows
        // what career_stats.cfg has recorded.
        //
        // WHY IT IS BUILT THIS WAY
        //
        // Redux's screen factory is a compiled switch, not a registration
        // table, so there is no safe way to invent a CAREER screen id and hand
        // it to the stock factory. The documented direction
        // (docs/NATIVE_UI_FRAMEWORK.md) is instead to mount both the button and
        // the page under the existing cUI_MainScreen, hide the stock title
        // controls while the page is up, and restore them on Back. Redux does
        // the same thing itself: Credits and Replay Intro do not create a new
        // screen, they present a child overlay under the live MainScreen.
        //
        // TRIGGER. Injection runs from a detour on the cUI_MainScreen
        // constructor, which is the moment the stock title menu exists. A timer
        // poll was tried first and rejected: SetTimer callbacks only arrive on
        // a thread that pumps messages, and the patcher thread does not, so the
        // tick would simply never fire.
        //
        // The detour is the same shape the settings page already uses on the
        // cUI_OptionsParent constructor: a 10-byte SEH prologue
        // (55 8B EC 6A FF 68 <handler>), guarded by an exact byte match before
        // anything is written. The handler pointer differs per function, so the
        // guard identifies this constructor specifically. If the bytes do not
        // match, nothing is patched and the Career button simply does not
        // appear -- shell construction is never put at risk to add a button.
        //
        // GEOMETRY IS TAKEN FROM THE STOCK BUTTONS, NOT GUESSED. The stock
        // title menu builds its own controls through this very constructor
        // (0x007C2480) with literal coordinates:
        //
        //     ExitGame_MainScreen        (0,   0,   342, 77)
        //     SinglePlayer_MainScreen    (163, 151, 446, 189)
        //     MultiPlayer_MainScreen     (831, 151, 446, 189)
        //
        // Single Player starts at x=163 and Multi Player ends at 831+446=1277,
        // so the content is centred on x=720 in a 1440-wide design space. The
        // CAREER button is centred on that same 720 and sits in the empty band
        // between the top bar (height 77) and the button rows (y=151), which is
        // the gap visible on the title screen.
        //
        // The stock parent is MainScreen_Overlay, passed to the constructor as
        // argument 7. It is resolved by exact child name rather than through
        // the +0x158 field, matching the established rule that name discovery
        // is the contract and the offset is not.

        // Binary-confirmed cUI_MainScreen singleton for this GOG build; the
        // constructor stores it and the destructor clears it, so a null read
        // means "no title screen right now" rather than "not resolved yet".
        uint32_t g_MainScreenSingletonAddr = 0;

        // Matches the stock top-corner controls exactly: same 342x77 frame,
        // same art, clamped to the top edge. ExitGame_MainScreen and
        // openAchievements are both built as (x, 0, 342, 77) with the
        // topcorner texture set, so the Career button reads as one of the same
        // family rather than as a floating panel. Centred on x=720, which is
        // the middle of the 1440-wide content space the stock buttons use.
        // The stock "to main menu" control's art (tomnoff/tomnon/tomnclk),
        // sized to the texture's own 369x68 so it is not stretched. The corner
        // frame this used first is an asymmetric bracket meant for a screen
        // corner, which reads as out of place centred on the top edge; the
        // to-main-menu art is symmetric and made to sit centred.
        //
        // Centred on x=720: SinglePlayer_MainScreen starts at 163 and
        // MultiPlayer_MainScreen ends at 1277, so the menu's content centre is
        // 720 in this 1440-wide space. Vertically inset by half the difference
        // against the 77-tall corner controls so it sits level with Exit Game
        // rather than riding high in the same row.
        constexpr float kCareerButtonW = 369.0f;
        constexpr float kCareerButtonH = 68.0f;
        constexpr float kCareerButtonX = 720.0f - kCareerButtonW * 0.5f;
        constexpr float kCareerButtonY = (77.0f - kCareerButtonH) * 0.5f;

        static void* g_CareerUiMainScreen = nullptr;
        static void* g_CareerUiOverlay = nullptr;
        static void* g_CareerUiButton = nullptr;

        static void ResetCareerUiState();
        static void* ReadMainScreenSingleton();

        // Every address in this file is an engine_addresses row. The options/career
        // hooks bind them together (OptionsUiAddressesBound); the native text
        // measure and the live input.map reload each bind their own rows and
        // fall back (char estimates, restart-to-apply) when those do not bind.
        static bool OptionsUiAddressesBound()
        {
            static const bool bound = [] {
                const HookEngine::EngineRow rows[] = {
                    { "OptionsInputCtor", &g_OptionsInputCtorAddr },
                    { "OptionsInputKeyReleased", &g_OptionsInputKeyReleasedAddr },
                    { "OptionsInputScreenFactoryCaller", &g_OptionsInputScreenFactoryCallerAddr },
                    { "OptionsInputBackClick", &g_OptionsInputBackClickAddr },
                    { "OptionsInputDefaultsClick", &g_OptionsInputDefaultsClickAddr },
                    { "OptionsInputJoystickClick", &g_OptionsInputJoystickClickAddr },
                    { "UiPerfButtonVtable", &g_UiButtonVtableAddr },
                    { "OptionsParentCtor", &g_OptionsParentCtorAddr },
                    { "MainScreenMenuSetup", &g_MainScreenCtorAddr },
                    { "OptionsParentInputClick", &g_OptionsParentInputClickThunkAddr },
                    { "OptionsInputSingleton", &g_OptionsInputSingletonAddr },
                    { "OptionsInputDtor", &g_OptionsInputDtorAddr },
                    { "OptionsParentDtor", &g_OptionsParentDtorAddr },
                    { "UiPerfMainScreenGlobal", &g_MainScreenSingletonAddr },
                };
                if (!HookEngine::BindEngineRows("Shim options UI", rows))
                    return false;
                if (!Hooks::VtableTypeNameMatches(g_UiButtonVtableAddr, ".?AVcUI_Button@@"))
                {
                    Log(L"[INPUTUI] cUI_Button vtable RTTI mismatch; shim options UI stands down\n");
                    return false;
                }
                return true;
            }();
            return bound;
        }

        // Copies a prologue's live bytes into an expected-bytes buffer. Used for
        // SEH prologues whose `push offset handler` operand is absolute: the
        // row's guard has already checked them on the reference build and the
        // porter regenerates it for others, so the live bytes are the truth.
        static void CopyLivePrologue(uint32_t address, uint8_t* out, size_t length)
        {
            std::memcpy(out, reinterpret_cast<const void*>(static_cast<uintptr_t>(address)), length);
        }

        static InlineDetour32 g_MainScreenCtorDetour = {};
        using FnMainScreenSetup = void(__thiscall*)(void* thisPtr, char phase);
        static FnMainScreenSetup g_BzrFn_MainScreenCtorOriginal = nullptr;
        static bool g_MainScreenCtorHookInstalled = false;
        static bool g_MainScreenCtorHookAttempted = false;
        static bool g_MainScreenCtorMismatchLogged = false;

        static void* ReadMainScreenSingleton()
        {
            __try
            {
                return *reinterpret_cast<void* const*>(g_MainScreenSingletonAddr);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        // Field the stock setup routine passes as the parent when it builds
        // the title buttons: FUN_0078d000 creates every one of them with
        // *(mainScreen + 0x158) in the constructor's parent argument. The RE
        // map is explicit that this offset is build knowledge and not a
        // contract, so it is used as a candidate and then confirmed by name.
        constexpr size_t kMainScreenOverlayFieldOffset = 0x158;

        static bool MainScreenViewNameMatches(void* view, const char* expected)
        {
            if (!view)
                return false;
            __try
            {
                return std::strncmp(
                    reinterpret_cast<const char*>(
                        reinterpret_cast<uint8_t*>(view) + kUiViewNameOffset),
                    expected, std::strlen(expected)) == 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Bounded dump of what the title screen actually looks like at hook
        // time. The first attempt resolved nothing, and guessing a second
        // structure without looking is how injected UI work goes wrong. Capped
        // rather than one-shot because this routine runs for more than one
        // phase and the interesting pass is not the first one.
        static void LogMainScreenShape(void* mainScreen)
        {
            static int s_logged = 0;
            if (s_logged >= 3 || !mainScreen)
                return;
            ++s_logged;

            __try
            {
                auto* const bytes = reinterpret_cast<uint8_t*>(mainScreen);
                void* const field158 =
                    *reinterpret_cast<void* const*>(bytes + kMainScreenOverlayFieldOffset);
                // One name per Log call on purpose. ReadUiViewName returns a
                // single shared static buffer, so two calls in one format list
                // both print whichever ran last -- which is exactly how the
                // first live capture reported the overlay as "Top Screen".
                Log(L"[CAREERUI] screen=0x%08X name=%hs\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(mainScreen)),
                    ReadUiViewName(mainScreen));
                Log(L"[CAREERUI] +0x158=0x%08X name=%hs\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(field158)),
                    field158 ? ReadUiViewName(field158) : "<null>");

                void** const begin =
                    *reinterpret_cast<void***>(bytes + kUiViewChildBeginOffset);
                void** const end =
                    *reinterpret_cast<void***>(bytes + kUiViewChildEndOffset);
                Log(L"[CAREERUI] child vector begin=0x%08X end=0x%08X count=%d\n",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(begin)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(end)),
                    (begin && end && end >= begin) ? static_cast<int>(end - begin) : -1);
                if (begin && end && begin < end && (end - begin) < 64)
                {
                    int index = 0;
                    for (void** slot = begin; slot != end; ++slot, ++index)
                        Log(L"[CAREERUI]   child[%d]=0x%08X name=%hs\n",
                            index,
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(*slot)),
                            ReadUiViewName(*slot));
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[CAREERUI] shape dump faulted\n");
            }
        }

        // Prefer the field the stock code itself uses, confirmed by name; fall
        // back to a bounded child scan by name. Both paths must agree on the
        // name, so neither can silently adopt the wrong container.
        static void* ResolveMainScreenOverlay(void* mainScreen)
        {
            if (!mainScreen)
                return nullptr;

            LogMainScreenShape(mainScreen);

            __try
            {
                auto* const screenBytes = reinterpret_cast<uint8_t*>(mainScreen);

                void* const candidate =
                    *reinterpret_cast<void* const*>(screenBytes + kMainScreenOverlayFieldOffset);
                if (MainScreenViewNameMatches(candidate, "MainScreen_Overlay"))
                    return candidate;

                void** const begin =
                    *reinterpret_cast<void***>(screenBytes + kUiViewChildBeginOffset);
                void** const end =
                    *reinterpret_cast<void***>(screenBytes + kUiViewChildEndOffset);
                if (!begin || !end || begin >= end || (end - begin) >= 64)
                    return nullptr;

                for (void** slot = begin; slot != end; ++slot)
                {
                    if (MainScreenViewNameMatches(*slot, "MainScreen_Overlay"))
                        return *slot;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }

            return nullptr;
        }

        // The Career page is its own shell screen (career_screen.cpp); the
        // title-screen button only asks the shell to go there, the same way
        // the stock Single Player and Options buttons do.
        static void __cdecl CareerUiButtonClick()
        {
            if (!ShellScreens::RequestScreen(ReadMainScreenSingleton(), ShellScreens::kCareerScreenId))
                Log(L"[CAREERUI] could not request the Career screen\n");
        }

        // Drop every cached pointer. Called when the singleton changes or goes
        // away: MainScreen children do not survive a screen transition, and a
        // retained pointer into a destroyed tree is the documented way to turn
        // this kind of injection into a crash.
        static void ResetCareerUiState()
        {
            g_CareerUiMainScreen = nullptr;
            g_CareerUiOverlay = nullptr;
            g_CareerUiButton = nullptr;
        }

        // Runs from the MainScreen destructor detour after the engine's
        // destructor has returned: the singleton is already null and every
        // child is gone. Drops the cached pointers at the moment they die
        // rather than at the next setup pass, so a heap address recycled in
        // between can never be mistaken for one of them.
        static void OnMainScreenDestroyedForCareerUi(void* screen)
        {
            if (!g_CareerUiMainScreen)
                return;
            Log(L"[CAREERUI] title screen 0x%08X destroyed; dropping cached widgets\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(screen)));
            ResetCareerUiState();
        }

        // Is `child` still in `parent`'s child vector? The MainScreen singleton
        // outlives its own menu: navigating to Options and back rebuilds the
        // overlay's children while the screen pointer stays the same, so a
        // cached widget pointer can survive the widget itself. Identity of the
        // screen is not identity of what is on it.
        static bool UiViewHasChild(void* parent, void* child)
        {
            if (!parent || !child)
                return false;

            __try
            {
                auto* const bytes = reinterpret_cast<uint8_t*>(parent);
                void** const begin = *reinterpret_cast<void***>(bytes + kUiViewChildBeginOffset);
                void** const end = *reinterpret_cast<void***>(bytes + kUiViewChildEndOffset);
                if (!begin || !end || begin > end || (end - begin) >= 64)
                    return false;

                for (void** slot = begin; slot != end; ++slot)
                {
                    if (*slot == child)
                        return true;
                }
                return false;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static void EnsureCareerUiButton()
        {
            if (!g_CareerUiOverlay || g_CareerUiButton)
                return;

            if (!CreateInputBindingUiButton(g_CareerUiButton, g_CareerUiOverlay,
                                            "OpenShimCareer_MainScreen", "CAREER",
                                            kCareerButtonX, kCareerButtonY,
                                            kCareerButtonW, kCareerButtonH,
                                            reinterpret_cast<void*>(CareerUiButtonClick)))
            {
                Log(L"[CAREERUI] button creation failed\n");
                return;
            }

            // Caption size to match the stock corner controls. The shared
            // creator uses 0.85 for the settings page, which reads visibly
            // smaller than "Exit Game" sitting beside it.
            if (g_BzrFn_SetButtonTextScale)
                g_BzrFn_SetButtonTextScale(g_CareerUiButton, 1.0f);

            // The stock "to main menu" skin, not the settings-page one: base /
            // hover / click, same three states the corner controls use.
            if (g_BzrFn_SetTextureOff) g_BzrFn_SetTextureOff(g_CareerUiButton, "tomnoff.png");
            if (g_BzrFn_SetTextureOver) g_BzrFn_SetTextureOver(g_CareerUiButton, "tomnon.png");
            if (g_BzrFn_SetTextureOn) g_BzrFn_SetTextureOn(g_CareerUiButton, "tomnclk.png");

            Log(L"[CAREERUI] button injected overlay=0x%08X button=0x%08X\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_CareerUiOverlay)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_CareerUiButton)));
        }

        // Poll tick. Cheap by design: one guarded pointer read in the common
        // case, and real work only when the title screen appears or changes.
        static void TickCareerUi()
        {
            void* const mainScreen = ReadMainScreenSingleton();

            if (!mainScreen)
            {
                if (g_CareerUiMainScreen)
                {
                    Log(L"[CAREERUI] title screen gone; dropping cached widgets\n");
                    ResetCareerUiState();
                }
                return;
            }

            // The singleton is longer-lived than the title menu below it.
            // Resolve the named overlay on every constructor completion rather
            // than using MainScreen identity as a proxy for child-tree identity.
            void* const overlay = ResolveMainScreenOverlay(mainScreen);
            if (!overlay)
            {
                if (mainScreen != g_CareerUiMainScreen)
                {
                    // Expected on the splash pass. Deliberately does NOT cache
                    // the screen pointer: the same screen object builds its
                    // title menu on a later call, and caching here would make
                    // the change test skip that pass and never inject.
                    static int s_missingOverlayLogs = 0;
                    if (s_missingOverlayLogs < 3)
                    {
                        ++s_missingOverlayLogs;
                        Log(L"[CAREERUI] MainScreen_Overlay not present on this pass; waiting\n");
                    }
                }
                return;
            }

            const bool overlayChanged =
                mainScreen != g_CareerUiMainScreen || overlay != g_CareerUiOverlay;
            const bool childrenRebuilt =
                !overlayChanged && g_CareerUiButton &&
                !UiViewHasChild(overlay, g_CareerUiButton);
            if (overlayChanged || childrenRebuilt)
            {
                if (childrenRebuilt)
                {
                    Log(L"[CAREERUI] button 0x%08X detached from overlay 0x%08X; rebuilding tree\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_CareerUiButton)),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(overlay)));
                }

                // The old page controls belong to the old child tree. Clear
                // them, then immediately adopt the live screen/overlay so this
                // same setup pass can inject replacements.
                ResetCareerUiState();
                g_CareerUiMainScreen = mainScreen;
                g_CareerUiOverlay = overlay;
            }

            EnsureCareerUiButton();
        }
    }

    void EnsureInputBindingPopulateHookScaffold()
    {
        if (!OptionsUiAddressesBound()) return;
        InitializeInputBindingUiScaffold();

        // The settings page reuses the hooked input screen as its host, so
        // the ctor/key hooks install when either feature is enabled.
        if (!ShouldEnableInputBindingUiReplacement() && !ShouldEnableShimSettingsUi())
            return;

        EnsureOptionsScreenDtorHook(g_OptionsInputDtorAddr,
                                    g_OptionsInputDtorDetour,
                                    reinterpret_cast<void*>(OptionsInputDtorHook),
                                    g_BzrFn_OptionsInputDtorOriginal,
                                    g_OptionsInputDtorHookInstalled,
                                    g_OptionsInputDtorHookAttempted,
                                    L"INPUTUI");

        if (g_InputBindingUiPopulateHookInstalled && g_InputBindingUiKeyReleasedHookInstalled)
            return;

        // push ebp; mov ebp,esp; push -1; push offset SEH handler -- read live.
        uint8_t kExpectedOptionsInputCtorBytes[kOptionsInputCtorDetourLen] = {};
        CopyLivePrologue(g_OptionsInputCtorAddr, kExpectedOptionsInputCtorBytes, sizeof(kExpectedOptionsInputCtorBytes));
        const uint8_t kExpectedOptionsInputKeyReleasedBytes[kOptionsInputKeyReleasedDetourLen] =
        {
            0x55, 0x8B, 0xEC, 0x81, 0xEC, 0x54, 0x01, 0x00, 0x00
        };

        // The key-release hook is passive (forwards to stock while no capture is
        // pending), so it installs first. The constructor hook is what activates
        // the replacement UI and only installs once key capture is guaranteed.
        // A failure therefore never strands a replacement UI that cannot capture
        // keys, and a retry never re-validates bytes on an already-patched site.
        if (!g_InputBindingUiKeyReleasedHookInstalled)
        {
            if (!ExpectedBytesMatchAt(g_OptionsInputKeyReleasedAddr,
                                      kExpectedOptionsInputKeyReleasedBytes,
                                      sizeof(kExpectedOptionsInputKeyReleasedBytes)))
            {
                if (!g_InputBindingUiPopulateHookMismatchLogged)
                {
                    Log(L"[INPUTUI] KeyReleased entry bytes mismatch at 0x%08X; input UI replacement remains disabled\n",
                        static_cast<uint32_t>(g_OptionsInputKeyReleasedAddr));
                    g_InputBindingUiPopulateHookMismatchLogged = true;
                }
                return;
            }

            if (!InstallInlineDetour32(g_OptionsInputKeyReleasedDetour,
                                       g_OptionsInputKeyReleasedAddr,
                                       reinterpret_cast<void*>(OptionsInputKeyReleasedHook),
                                       kOptionsInputKeyReleasedDetourLen,
                                       kExpectedOptionsInputKeyReleasedBytes,
                                       sizeof(kExpectedOptionsInputKeyReleasedBytes)))
            {
                Log(L"[INPUTUI] Failed installing key-release hook at 0x%08X\n",
                    static_cast<uint32_t>(g_OptionsInputKeyReleasedAddr));
                return;
            }

            g_BzrFn_OptionsInputKeyReleased =
                reinterpret_cast<FnOptionsInputKeyReleased>(g_OptionsInputKeyReleasedDetour.trampoline);
            g_InputBindingUiKeyReleasedHookInstalled = (g_BzrFn_OptionsInputKeyReleased != nullptr);
            if (!g_InputBindingUiKeyReleasedHookInstalled)
                return;
        }

        if (!g_InputBindingUiPopulateHookInstalled)
        {
            if (!ExpectedBytesMatchAt(g_OptionsInputCtorAddr,
                                      kExpectedOptionsInputCtorBytes,
                                      sizeof(kExpectedOptionsInputCtorBytes)))
            {
                if (!g_InputBindingUiPopulateHookMismatchLogged)
                {
                    Log(L"[INPUTUI] Constructor entry bytes mismatch at 0x%08X; input UI replacement remains disabled\n",
                        static_cast<uint32_t>(g_OptionsInputCtorAddr));
                    g_InputBindingUiPopulateHookMismatchLogged = true;
                }
                return;
            }

            if (!InstallInlineDetour32(g_OptionsInputPopulateUiDetour,
                                       g_OptionsInputCtorAddr,
                                       reinterpret_cast<void*>(OptionsInputPopulateUiHook),
                                       kOptionsInputCtorDetourLen,
                                       kExpectedOptionsInputCtorBytes,
                                       sizeof(kExpectedOptionsInputCtorBytes)))
            {
                Log(L"[INPUTUI] Failed installing constructor hook at 0x%08X\n",
                    static_cast<uint32_t>(g_OptionsInputCtorAddr));
                return;
            }

            g_BzrFn_OptionsInputCtor =
                reinterpret_cast<FnOptionsInputCtor>(g_OptionsInputPopulateUiDetour.trampoline);
            g_InputBindingUiPopulateHookInstalled = (g_BzrFn_OptionsInputCtor != nullptr);
            if (!g_InputBindingUiPopulateHookInstalled)
                return;
        }

        g_InputBindingUiPopulateHookMismatchLogged = false;
        Log(L"[INPUTUI] Installed constructor hook entry=0x%08X trampoline=0x%08X keyRelease=0x%08X\n",
            static_cast<uint32_t>(g_OptionsInputCtorAddr),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_OptionsInputPopulateUiDetour.trampoline)),
            static_cast<uint32_t>(g_OptionsInputKeyReleasedAddr));
    }

    // Thin public wrapper so features outside the settings page (the lobby
    // nickname entry) can persist a single key through the same lossless
    // writer, keeping comments, ordering and the .openshim.bak backup intact.
    bool WriteShimUserConfigValue(const char* section, const char* key, const char* value)
    {
        if (!section || !key || !value)
            return false;

        std::string error;
        if (WriteUserConfigValueLossless(section, key, nullptr, 0, value, error))
            return true;

        Log(L"[SETTINGSUI] Failed to write [%hs] %hs: %hs\n",
            section, key, error.c_str());
        return false;
    }

    // Career button injection. Gated on the same switch as the settings page:
    // both are OpenShim shell UI, and a player who turned that off should not
    // get a new title-screen button either.
    void EnsureMainScreenCtorHookScaffold()
    {
        if (!ShouldEnableShimSettingsUi() || !OptionsUiAddressesBound())
            return;
        if (g_MainScreenCtorHookInstalled || g_MainScreenCtorHookAttempted)
            return;
        g_MainScreenCtorHookAttempted = true;

        // The button leads to the Career screen; without the screen there is
        // nothing to put on the title menu.
        if (!RegisterCareerScreen())
        {
            Log(L"[CAREERUI] Career screen unavailable on this build; no title-screen button\n");
            return;
        }

        // push ebp; mov ebp,esp; push -1; push offset SEH handler -- read live.
        uint8_t kExpectedMainScreenCtorBytes[kMainScreenCtorDetourLen] = {};
        CopyLivePrologue(g_MainScreenCtorAddr, kExpectedMainScreenCtorBytes, sizeof(kExpectedMainScreenCtorBytes));

        if (!ExpectedBytesMatchAt(g_MainScreenCtorAddr,
                                  kExpectedMainScreenCtorBytes,
                                  sizeof(kExpectedMainScreenCtorBytes)))
        {
            if (!g_MainScreenCtorMismatchLogged)
            {
                g_MainScreenCtorMismatchLogged = true;
                Log(L"[CAREERUI] MainScreen ctor bytes mismatch at 0x%08X; Career button disabled\n",
                    static_cast<uint32_t>(g_MainScreenCtorAddr));
            }
            return;
        }

        if (!InstallInlineDetour32(g_MainScreenCtorDetour,
                                   g_MainScreenCtorAddr,
                                   reinterpret_cast<void*>(MainScreenCtorHook),
                                   kMainScreenCtorDetourLen,
                                   kExpectedMainScreenCtorBytes,
                                   sizeof(kExpectedMainScreenCtorBytes)))
        {
            Log(L"[CAREERUI] Failed installing MainScreen ctor hook at 0x%08X\n",
                static_cast<uint32_t>(g_MainScreenCtorAddr));
            return;
        }

        g_BzrFn_MainScreenCtorOriginal =
            reinterpret_cast<FnMainScreenSetup>(g_MainScreenCtorDetour.trampoline);
        g_MainScreenCtorHookInstalled = (g_BzrFn_MainScreenCtorOriginal != nullptr);

        Log(L"[CAREERUI] MainScreen setup hook installed entry=0x%08X trampoline=0x%08X\n",
            static_cast<uint32_t>(g_MainScreenCtorAddr),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_MainScreenCtorDetour.trampoline)));

        // The cached widgets die with the screen; learn about it from the
        // destructor rather than from the next setup pass.
        if (EnsureMainScreenDestroyedHook() &&
            AddMainScreenDestroyedListener(&OnMainScreenDestroyedForCareerUi))
        {
            Log(L"[CAREERUI] MainScreen destructor listener registered\n");
        }
        else
        {
            Log(L"[CAREERUI] MainScreen destructor hook unavailable; cached widgets are "
                L"checked against the live singleton instead\n");
        }
    }

    void EnsureOptionsParentCtorHookScaffold()
    {
        if (!OptionsUiAddressesBound()) return;
        if (!ShouldEnableShimSettingsUi())
            return;

        EnsureMainScreenCtorHookScaffold();

        // The OpenShim button leads to OpenShim's own screens; a build that
        // cannot host them gets no button rather than a dead one.
        if (!RegisterShimOptionsScreens())
        {
            Log(L"[SETTINGSUI] OpenShim Options screens unavailable; Options left stock\n");
            return;
        }

        EnsureOptionsScreenDtorHook(g_OptionsParentDtorAddr,
                                    g_OptionsParentDtorDetour,
                                    reinterpret_cast<void*>(OptionsParentDtorHook),
                                    g_BzrFn_OptionsParentDtorOriginal,
                                    g_OptionsParentDtorHookInstalled,
                                    g_OptionsParentDtorHookAttempted,
                                    L"SETTINGSUI");

        if (g_OptionsParentHookInstalled)
            return;

        // push ebp; mov ebp,esp; push -1; push offset SEH handler -- read live.
        uint8_t kExpectedOptionsParentCtorBytes[kOptionsParentCtorDetourLen] = {};
        CopyLivePrologue(g_OptionsParentCtorAddr, kExpectedOptionsParentCtorBytes, sizeof(kExpectedOptionsParentCtorBytes));

        if (!ExpectedBytesMatchAt(g_OptionsParentCtorAddr,
                                  kExpectedOptionsParentCtorBytes,
                                  sizeof(kExpectedOptionsParentCtorBytes)))
        {
            if (!g_OptionsParentHookMismatchLogged)
            {
                Log(L"[SETTINGSUI] Options ctor bytes mismatch at 0x%08X; settings UI disabled\n",
                    static_cast<uint32_t>(g_OptionsParentCtorAddr));
                g_OptionsParentHookMismatchLogged = true;
            }
            return;
        }

        if (!InstallInlineDetour32(g_OptionsParentCtorDetour,
                                   g_OptionsParentCtorAddr,
                                   reinterpret_cast<void*>(OptionsParentCtorHook),
                                   kOptionsParentCtorDetourLen,
                                   kExpectedOptionsParentCtorBytes,
                                   sizeof(kExpectedOptionsParentCtorBytes)))
        {
            Log(L"[SETTINGSUI] Failed installing options ctor hook at 0x%08X\n",
                static_cast<uint32_t>(g_OptionsParentCtorAddr));
            return;
        }

        g_BzrFn_OptionsParentCtor =
            reinterpret_cast<FnOptionsInputCtor>(g_OptionsParentCtorDetour.trampoline);
        g_OptionsParentHookInstalled = (g_BzrFn_OptionsParentCtor != nullptr);
        if (g_OptionsParentHookInstalled)
        {
            Log(L"[SETTINGSUI] Installed options ctor hook entry=0x%08X trampoline=0x%08X\n",
                static_cast<uint32_t>(g_OptionsParentCtorAddr),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_OptionsParentCtorDetour.trampoline)));
        }
    }

    void* __fastcall OptionsInputPopulateUiHook(void* thisPtr, void* /*edx*/)
    {
        void* screen = thisPtr;

        if (g_BzrFn_OptionsInputCtor)
            screen = g_BzrFn_OptionsInputCtor(thisPtr);

        OnOptionsInputPopulateUiScaffold(screen);
        return screen;
    }

    bool __fastcall OptionsInputKeyReleasedHook(void* thisPtr,
                                                void* /*edx*/,
                                                uint32_t key,
                                                uint32_t keyCode)
    {
        if (HandleCapturedInputBindingKey(thisPtr, key, keyCode))
            return true;

        if (g_BzrFn_OptionsInputKeyReleased)
            return g_BzrFn_OptionsInputKeyReleased(thisPtr, key, keyCode);

        return false;
    }

    void* __fastcall OptionsParentCtorHook(void* thisPtr, void* /*edx*/)
    {
        void* screen = thisPtr;

        if (g_BzrFn_OptionsParentCtor)
            screen = g_BzrFn_OptionsParentCtor(thisPtr);

        OnOptionsParentCtorScaffold(screen);
        return screen;
    }

    // Runs once per title-screen construction. The stock constructor builds
    // the whole menu (including MainScreen_Overlay and the singleton the
    // resolver reads), so injection has to happen after it returns, not before.
    void __fastcall MainScreenCtorHook(void* thisPtr, void* /*edx*/, char phase)
    {
        if (g_BzrFn_MainScreenCtorOriginal)
            g_BzrFn_MainScreenCtorOriginal(thisPtr, phase);

        // Never let a failure in an injected button take the title screen with
        // it: the shell is already constructed and usable at this point.
        __try
        {
            TickCareerUi();
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            Log(L"[CAREERUI] injection faulted (0x%08X); title screen left stock\n",
                static_cast<uint32_t>(GetExceptionCode()));
            ResetCareerUiState();
        }
    }

    void __fastcall OptionsInputDtorHook(void* thisPtr, void* /*edx*/)
    {
        OnOptionsInputScreenDestroyed(thisPtr);
        if (g_BzrFn_OptionsInputDtorOriginal)
            g_BzrFn_OptionsInputDtorOriginal(thisPtr);
    }

    void __fastcall OptionsParentDtorHook(void* thisPtr, void* /*edx*/)
    {
        OnOptionsParentScreenDestroyed(thisPtr);
        if (g_BzrFn_OptionsParentDtorOriginal)
            g_BzrFn_OptionsParentDtorOriginal(thisPtr);
    }

    // ResolveBzrHooks (bzr_hooks.cpp) delegates the UI-owned re-resolve /
    // reset work here: trampoline-backed fn pointers survive, everything
    // keyed to a dead screen or a stale inventory is dropped.
    void ResetOptionsUiResolvedState()
    {
        g_BzrFn_OptionsInputCtor = g_OptionsInputPopulateUiDetour.trampoline
            ? reinterpret_cast<FnOptionsInputCtor>(g_OptionsInputPopulateUiDetour.trampoline)
            : nullptr;
        g_BzrFn_OptionsInputKeyReleased = g_OptionsInputKeyReleasedDetour.trampoline
            ? reinterpret_cast<FnOptionsInputKeyReleased>(g_OptionsInputKeyReleasedDetour.trampoline)
            : nullptr;
        g_BzrFn_OptionsParentCtor = g_OptionsParentCtorDetour.trampoline
            ? reinterpret_cast<FnOptionsInputCtor>(g_OptionsParentCtorDetour.trampoline)
            : nullptr;
        g_OptionsParentHookInstalled = (g_BzrFn_OptionsParentCtor != nullptr);
        g_InputBindingUiScaffoldInitialized = false;
        g_InputBindingUiScaffoldLogged = false;
        g_InputBindingUiPopulateHookInstalled =
            (g_OptionsInputPopulateUiDetour.trampoline != nullptr);
        g_InputBindingUiKeyReleasedHookInstalled =
            (g_OptionsInputKeyReleasedDetour.trampoline != nullptr);
        g_InputBindingUiPopulateHookMismatchLogged = false;
        g_InputBindingInstallDirectory.clear();
        g_InputBindingInventory = {};
        g_InputBindingCommandBlocks.clear();
        g_GameKeyBindingActions.clear();
        g_InputBindingUiRows.clear();
        g_InputScreenBinding.Unbind();
        g_ParentScreenBinding.Unbind();
        g_ShimSettingsMenuButton = nullptr;
        ResetInputBindingUiVisuals();
    }

    void LogShimSettingsUiStatus()
    {
        Log(L"[SETTINGSUI] Settings UI: %hs\n",
            ShouldEnableShimSettingsUi()
                ? (g_OptionsParentHookInstalled ? "enabled" : "enabled (hook pending)")
                : "disabled");
    }

    bool AreInputBindingUiHooksInstalled()
    {
        return g_InputBindingUiPopulateHookInstalled && g_InputBindingUiKeyReleasedHookInstalled;
    }
}
