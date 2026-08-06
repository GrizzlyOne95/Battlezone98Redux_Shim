// Input-binding UI replacement + OpenShim settings screen (options-shell
// sub-pages injected over cUI_OptionsInput / cUI_OptionsParent). Split out of
// bzr_hooks.cpp; the shared engine-binding surface (resolved fn pointers,
// inline-detour machinery, openshim.ini helpers, live feature re-apply) is
// declared in bzr_options_ui.h and implemented by bzr_hooks.cpp.
#include "bzr_options_ui.h"

#include "bzr_hooks.h"
#include "openshim_ini.h"
#include "patcher.h"
#include "shim_log.h"

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
#include <vector>

namespace BZROpenShim
{
    void* __fastcall OptionsInputPopulateUiHook(void* thisPtr, void* /*edx*/);
    bool __fastcall OptionsInputKeyReleasedHook(void* thisPtr, void* /*edx*/, uint32_t key, uint32_t keyCode);
    void* __fastcall OptionsParentCtorHook(void* thisPtr, void* /*edx*/);
    void __fastcall OptionsInputDtorHook(void* thisPtr, void* /*edx*/);
    void __fastcall OptionsParentDtorHook(void* thisPtr, void* /*edx*/);

    namespace
    {
        // The shipped GOG PDB public-symbol addresses for cUI_OptionsInput methods
        // are not reliable function-entry hooks against the current Redux binary.
        // The stock input screen constructor was recovered from string xrefs instead.
        constexpr uintptr_t kOptionsInputCtorAddr = 0x007B25B0;
        constexpr uintptr_t kOptionsInputKeyReleasedAddr = 0x007B48C0;
        constexpr uintptr_t kOptionsInputScreenFactoryCallerAddr = 0x007C8600;
        constexpr uintptr_t kOptionsInputBackClickAddr = 0x007B2210;
        constexpr uintptr_t kOptionsInputDefaultsClickAddr = 0x007B2230;
        // Stock "Joystick" button click thunk (cUI_OptionsInput ctor wires it
        // via SetOnClick 0x007C23E0; see FUN_007b25b0 decomp). The Default and
        // Joystick buttons are ctor locals, not screen members, so they are
        // located at runtime by matching this thunk in the +0x154 click slot.
        constexpr uintptr_t kOptionsInputJoystickClickAddr = 0x007B2220;
        constexpr size_t kUiViewChildBeginOffset = 0x12C;
        constexpr size_t kUiViewChildEndOffset = 0x130;
        constexpr size_t kUiButtonOnHoverOffset = 0x150;
        constexpr size_t kUiButtonOnClickOffset = 0x154;
        // cUI_View debug name: char[0xC8] copied by the view ctor (0x007D1CC0)
        // from its first argument. cUI_Button installs vtable 0x008A0470 over
        // the cUI_View vtable 0x008A0B94, which is how a node is identified as
        // a button when walking a screen's child tree.
        constexpr size_t kUiViewNameOffset = 0x20;
        constexpr uintptr_t kUiButtonVtableAddr = 0x008A0470;
        // cUI_OptionsParent constructor on the live GOG/Steam 2.2.301 exe,
        // recovered from the Redux decompile corpus (FUN_007b61a0: builds the
        // esc_center.png overlay plus the Play/Graphic/Audio/Input buttons) and
        // byte-verified against the installed exe (SEH prologue
        // 55 8B EC 6A FF 68 60 13 86 00). Singleton stored at 0x009455C4.
        constexpr uintptr_t kOptionsParentCtorAddr = 0x007B61A0;
        constexpr size_t kOptionsParentCtorDetourLen = 10;
        constexpr uintptr_t kOptionsParentSingletonAddr = 0x009455C4;
        // Stock cUI_OptionsParent "Input" click thunk: loads the parent
        // singleton and asks the options shell (this+0x138) to switch to screen
        // id 0x15 (the input options page) via the switch fn at 0x007C7930.
        // The OpenShim settings button reuses this exact navigation path.
        constexpr uintptr_t kOptionsParentInputClickThunkAddr = 0x007B6100;
        // cUI_OptionsInput singleton (DAT_009455B8); non-null while the stock
        // input screen object is alive inside the current options shell.
        constexpr uintptr_t kOptionsInputSingletonAddr = 0x009455B8;
        // Inner (non-deleting) destructors of the two hooked screens, recovered
        // from the live GOG exe: the ctor at 0x007B25B0 installs vtable
        // 0x0089F930 whose slot 0 (scalar deleting dtor 0x007B4840) calls
        // 0x007B4870; the parent ctor 0x007B61A0 installs vtable 0x0089FC34 ->
        // slot 0 0x007B6820 -> 0x007B6850. Hooking the inner dtor catches every
        // destruction path, which is what invalidates our cached child views.
        constexpr uintptr_t kOptionsInputDtorAddr = 0x007B4870;
        constexpr uintptr_t kOptionsParentDtorAddr = 0x007B6850;
        constexpr size_t kOptionsScreenDtorDetourLen = 10;
        constexpr size_t kOptionsInputCtorDetourLen = 10;
        constexpr size_t kOptionsInputKeyReleasedDetourLen = 9;
        constexpr size_t kOptionsInputKeyConfigOffset = 0x188;

        constexpr uintptr_t kGogReadMappingTableAddr = 0x00620010;

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

        constexpr size_t kInputBindingUiColumnCount = 2;
        constexpr size_t kInputBindingUiRowsPerColumn = 10;
        constexpr size_t kInputBindingUiVisibleRowCount =
            kInputBindingUiColumnCount * kInputBindingUiRowsPerColumn;

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
        static void* g_InputBindingUiBackdrop = nullptr;
        static void* g_InputBindingUiFrame = nullptr;
        static void* g_InputBindingUiTopMask = nullptr;
        static void* g_InputBindingUiContentMask = nullptr;
        static void* g_InputBindingUiHeaderBackdrop = nullptr;
        static std::array<void*, kInputBindingUiVisibleRowCount> g_InputBindingUiRowBackdrops = {};
        static void* g_InputBindingUiHeaderLabel = nullptr;
        static void* g_InputBindingUiStatusLabel = nullptr;
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

        // --- OpenShim settings screen (options-shell sub-page) ------------------
        // A native "OpenShim" button is appended to the stock Options screen; it
        // navigates to the (already hooked) input options screen with a mode flag
        // set, and the constructor hook renders a settings page there instead of
        // the key-binding list. Settings edit openshim.ini losslessly and apply
        // live through each feature's existing baseline/refresh machinery.
        constexpr size_t kShimSettingsUiColumnCount = 2;
        constexpr size_t kShimSettingsUiRowsPerColumn = 8;
        constexpr size_t kShimSettingsUiVisibleRowCount =
            kShimSettingsUiColumnCount * kShimSettingsUiRowsPerColumn;

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
        // Set by the OpenShim button click; consumed when the input screen is
        // (re)constructed or when it already exists and can be restyled directly.
        // The request expires so a click that never reached a construction cannot
        // hijack an unrelated later visit to the stock input page.
        static bool g_ShimSettingsPageRequested = false;
        static ULONGLONG g_ShimSettingsPageRequestTick = 0;
        static ULONGLONG g_ShimSettingsNavigationTick = 0;
        constexpr ULONGLONG kShimSettingsPageRequestTtlMs = 3000;
        constexpr ULONGLONG kShimSettingsNavigationDebounceMs = 350;
        // True while the settings page owns the hooked input screen's visuals.
        static bool g_ShimSettingsPageActive = false;
        static void* g_ShimSettingsUiBackdrop = nullptr;
        static void* g_ShimSettingsUiFrame = nullptr;
        static void* g_ShimSettingsUiTopMask = nullptr;
        static void* g_ShimSettingsUiContentMask = nullptr;
        static void* g_ShimSettingsUiHeaderBackdrop = nullptr;
        static std::array<void*, kShimSettingsUiVisibleRowCount> g_ShimSettingsUiRowBackdrops = {};
        static void* g_ShimSettingsUiHeaderLabel = nullptr;
        static void* g_ShimSettingsUiStatusLabel = nullptr;
        static void* g_ShimSettingsUiFooterLabel = nullptr;
        static void* g_ShimSettingsUiBackButton = nullptr;
        static std::array<void*, kShimSettingsUiVisibleRowCount> g_ShimSettingsUiRowLabels = {};
        static std::array<void*, kShimSettingsUiVisibleRowCount> g_ShimSettingsUiRowButtons = {};
        static void* g_ShimSettingsUiPageLabel = nullptr;
        static void* g_ShimSettingsUiPrevPageButton = nullptr;
        static void* g_ShimSettingsUiNextPageButton = nullptr;
        static size_t g_ShimSettingsUiPageStart = 0;
        static std::string g_ShimSettingsUiStatusText = {};
        static void OnShimSettingsMenuClicked();
        static void OnShimSettingsBackClicked();
        static void OnShimSettingsRowClicked(size_t rowIndex);
        static void OnShimSettingsRowHovered(size_t rowIndex);
        static void OnShimSettingsPageStepClicked(int direction);
        static void ResetShimSettingsUiVisuals();
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

        static void __cdecl ShimSettingsBackClick()
        {
            OnShimSettingsBackClicked();
        }

        static void __cdecl ShimSettingsPrevPageClick()
        {
            OnShimSettingsPageStepClicked(-1);
        }

        static void __cdecl ShimSettingsNextPageClick()
        {
            OnShimSettingsPageStepClicked(1);
        }

#define BZR_SHIM_SETTINGS_ROW_CLICK_DECL(index) \
        static void __cdecl ShimSettingsRowClick##index() { OnShimSettingsRowClicked(index); }

        BZR_SHIM_SETTINGS_ROW_CLICK_DECL(0)
        BZR_SHIM_SETTINGS_ROW_CLICK_DECL(1)
        BZR_SHIM_SETTINGS_ROW_CLICK_DECL(2)
        BZR_SHIM_SETTINGS_ROW_CLICK_DECL(3)
        BZR_SHIM_SETTINGS_ROW_CLICK_DECL(4)
        BZR_SHIM_SETTINGS_ROW_CLICK_DECL(5)
        BZR_SHIM_SETTINGS_ROW_CLICK_DECL(6)
        BZR_SHIM_SETTINGS_ROW_CLICK_DECL(7)
        BZR_SHIM_SETTINGS_ROW_CLICK_DECL(8)
        BZR_SHIM_SETTINGS_ROW_CLICK_DECL(9)
        BZR_SHIM_SETTINGS_ROW_CLICK_DECL(10)
        BZR_SHIM_SETTINGS_ROW_CLICK_DECL(11)
        BZR_SHIM_SETTINGS_ROW_CLICK_DECL(12)
        BZR_SHIM_SETTINGS_ROW_CLICK_DECL(13)
        BZR_SHIM_SETTINGS_ROW_CLICK_DECL(14)
        BZR_SHIM_SETTINGS_ROW_CLICK_DECL(15)

#undef BZR_SHIM_SETTINGS_ROW_CLICK_DECL

// Hover thunks feed the row's setting description into the status label.
// Screens may invoke every child's hover slot in bulk when they open (see
// InputBindingUiButtonOnHoverNoop), so the handler is gated and label-only.
#define BZR_SHIM_SETTINGS_ROW_HOVER_DECL(index) \
        static void __cdecl ShimSettingsRowHover##index(void* /*param*/) { OnShimSettingsRowHovered(index); }

        BZR_SHIM_SETTINGS_ROW_HOVER_DECL(0)
        BZR_SHIM_SETTINGS_ROW_HOVER_DECL(1)
        BZR_SHIM_SETTINGS_ROW_HOVER_DECL(2)
        BZR_SHIM_SETTINGS_ROW_HOVER_DECL(3)
        BZR_SHIM_SETTINGS_ROW_HOVER_DECL(4)
        BZR_SHIM_SETTINGS_ROW_HOVER_DECL(5)
        BZR_SHIM_SETTINGS_ROW_HOVER_DECL(6)
        BZR_SHIM_SETTINGS_ROW_HOVER_DECL(7)
        BZR_SHIM_SETTINGS_ROW_HOVER_DECL(8)
        BZR_SHIM_SETTINGS_ROW_HOVER_DECL(9)
        BZR_SHIM_SETTINGS_ROW_HOVER_DECL(10)
        BZR_SHIM_SETTINGS_ROW_HOVER_DECL(11)
        BZR_SHIM_SETTINGS_ROW_HOVER_DECL(12)
        BZR_SHIM_SETTINGS_ROW_HOVER_DECL(13)
        BZR_SHIM_SETTINGS_ROW_HOVER_DECL(14)
        BZR_SHIM_SETTINGS_ROW_HOVER_DECL(15)

#undef BZR_SHIM_SETTINGS_ROW_HOVER_DECL

        static void* const kShimSettingsRowHoverCallbacks[kShimSettingsUiVisibleRowCount] =
        {
            reinterpret_cast<void*>(ShimSettingsRowHover0),
            reinterpret_cast<void*>(ShimSettingsRowHover1),
            reinterpret_cast<void*>(ShimSettingsRowHover2),
            reinterpret_cast<void*>(ShimSettingsRowHover3),
            reinterpret_cast<void*>(ShimSettingsRowHover4),
            reinterpret_cast<void*>(ShimSettingsRowHover5),
            reinterpret_cast<void*>(ShimSettingsRowHover6),
            reinterpret_cast<void*>(ShimSettingsRowHover7),
            reinterpret_cast<void*>(ShimSettingsRowHover8),
            reinterpret_cast<void*>(ShimSettingsRowHover9),
            reinterpret_cast<void*>(ShimSettingsRowHover10),
            reinterpret_cast<void*>(ShimSettingsRowHover11),
            reinterpret_cast<void*>(ShimSettingsRowHover12),
            reinterpret_cast<void*>(ShimSettingsRowHover13),
            reinterpret_cast<void*>(ShimSettingsRowHover14),
            reinterpret_cast<void*>(ShimSettingsRowHover15),
        };

        static void* const kShimSettingsRowClickCallbacks[kShimSettingsUiVisibleRowCount] =
        {
            reinterpret_cast<void*>(ShimSettingsRowClick0),
            reinterpret_cast<void*>(ShimSettingsRowClick1),
            reinterpret_cast<void*>(ShimSettingsRowClick2),
            reinterpret_cast<void*>(ShimSettingsRowClick3),
            reinterpret_cast<void*>(ShimSettingsRowClick4),
            reinterpret_cast<void*>(ShimSettingsRowClick5),
            reinterpret_cast<void*>(ShimSettingsRowClick6),
            reinterpret_cast<void*>(ShimSettingsRowClick7),
            reinterpret_cast<void*>(ShimSettingsRowClick8),
            reinterpret_cast<void*>(ShimSettingsRowClick9),
            reinterpret_cast<void*>(ShimSettingsRowClick10),
            reinterpret_cast<void*>(ShimSettingsRowClick11),
            reinterpret_cast<void*>(ShimSettingsRowClick12),
            reinterpret_cast<void*>(ShimSettingsRowClick13),
            reinterpret_cast<void*>(ShimSettingsRowClick14),
            reinterpret_cast<void*>(ShimSettingsRowClick15),
        };

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
                static_cast<uint32_t>(kOptionsInputCtorAddr),
                static_cast<uint32_t>(kOptionsInputScreenFactoryCallerAddr));
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
            ResetShimSettingsUiVisuals();
            g_InputScreenBinding.BindDecorated(nullptr);
            g_InputBindingUiMiddleOverlay = nullptr;
            g_InputBindingUiBackdrop = nullptr;
            g_InputBindingUiFrame = nullptr;
            g_InputBindingUiTopMask = nullptr;
            g_InputBindingUiContentMask = nullptr;
            g_InputBindingUiHeaderBackdrop = nullptr;
            g_InputBindingUiRowBackdrops.fill(nullptr);
            g_InputBindingUiHeaderLabel = nullptr;
            g_InputBindingUiStatusLabel = nullptr;
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
            if (!parent || !g_BzrFn_ButtonCtor || !g_BzrFn_AddChild)
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

                if (g_BzrFn_SetTextureOff) g_BzrFn_SetTextureOff(slot, "mpcron.png");
                if (g_BzrFn_SetTextureOver) g_BzrFn_SetTextureOver(slot, "mpcrclk.png");
                if (g_BzrFn_SetTextureOn) g_BzrFn_SetTextureOn(slot, "mpcrclk.png");
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

            if (g_BzrFn_SetTextureOff) g_BzrFn_SetTextureOff(slot, "mpcron.png");
            if (g_BzrFn_SetTextureOver) g_BzrFn_SetTextureOver(slot, "mpcron.png");
            if (g_BzrFn_SetTextureOn) g_BzrFn_SetTextureOn(slot, "mpcron.png");
            return true;
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
        constexpr uintptr_t kGogUiTextMeasureAddr = 0x00689AB0;    // cdecl (font, text, &w, &h)
        constexpr uintptr_t kGogUiFontContextPtrAddr = 0x0091552C; // global font the UI text uses
        constexpr uintptr_t kGogUiFontCharSizeXAddr = 0x02BF041C;  // global char-size floats read
        constexpr uintptr_t kGogUiFontCharSizeYAddr = 0x02BF0420;  // by the per-char advance calls

        typedef void(__cdecl* FnUiMeasureText)(void* font, const char* text,
                                               float* outWidth, float* outHeight);

        // POD-only for __try. Returns false whenever the native routine cannot
        // be trusted so callers fall back to the char-width estimates.
        static bool TryMeasureUiTextWidth(const char* text, float scale, float* outWidth)
        {
            static int s_measureState = 0; // 0=unchecked 1=usable -1=unavailable
            if (s_measureState == 0)
            {
                static const uint8_t kExpectedMeasureBytes[] =
                {
                    0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x24, 0x83, 0x7D, 0x10, 0x00
                };
                s_measureState = ExpectedBytesMatchAt(kGogUiTextMeasureAddr,
                                                      kExpectedMeasureBytes,
                                                      sizeof(kExpectedMeasureBytes))
                                     ? 1
                                     : -1;
                if (s_measureState < 0)
                    Log(L"[INPUTUI] Text measure bytes mismatch at 0x%08X; using char estimates\n",
                        static_cast<uint32_t>(kGogUiTextMeasureAddr));
            }
            if (s_measureState < 0 || !text || !outWidth || scale <= 0.0f)
                return false;

            float* const charSizeX = reinterpret_cast<float*>(kGogUiFontCharSizeXAddr);
            float* const charSizeY = reinterpret_cast<float*>(kGogUiFontCharSizeYAddr);
            float savedX = 0.0f;
            float savedY = 0.0f;
            bool scaled = false;
            __try
            {
                void* const font = *reinterpret_cast<void**>(kGogUiFontContextPtrAddr);
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
                reinterpret_cast<FnUiMeasureText>(kGogUiTextMeasureAddr)(font, text, &width, &height);
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
                FindStockOptionsInputButtonByClick(overlay, kOptionsInputDefaultsClickAddr);
            if (!defaultsButton)
                defaultsButton =
                    FindStockOptionsInputButtonByClick(screen, kOptionsInputDefaultsClickAddr);
            SetStockOptionsInputButtonActive(defaultsButton, false, nullptr);

            void* joystickButton =
                FindStockOptionsInputButtonByClick(screen, kOptionsInputJoystickClickAddr);
            if (!joystickButton)
                joystickButton =
                    FindStockOptionsInputButtonByClick(overlay, kOptionsInputJoystickClickAddr);
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

            const char* headerText =
                g_InputBindingUiActiveFamily == InputBindingMapFamily::GameKey
                    ? "RTS & Game Actions"
                    : "Movement & Vehicle Controls";

            SetInputBindingUiLabelTextFitted(g_InputBindingUiHeaderLabel, headerText, 800.0f);
            SetInputBindingUiLabelTextFitted(g_InputBindingUiStatusLabel,
                                             g_InputBindingUiStatusText.c_str(), 800.0f);
            SuppressStockOptionsInputWidgets(decoratedScreen);
            SetStockOptionsInputAccessoryVisibility(decoratedScreen, true);

            SetInputBindingUiButtonTextFitted(
                g_InputBindingUiInputFamilyButton,
                g_InputBindingUiActiveFamily == InputBindingMapFamily::Input ? "> Controls <" : "Controls",
                150.0f);
            SetInputBindingUiButtonTextFitted(
                g_InputBindingUiGameKeyFamilyButton,
                g_InputBindingUiActiveFamily == InputBindingMapFamily::GameKey ? "> RTS Actions <" : "RTS Actions",
                150.0f);

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
            SetInputBindingUiLabelTextFitted(g_InputBindingUiPageLabel, pageText, 800.0f);

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
                SetInputBindingUiLabelTextFitted(g_InputBindingUiRowLabels[slot], labelText.c_str(), 275.0f);
                SetInputBindingUiButtonTextFitted(g_InputBindingUiRowButtons[slot], buttonText.c_str(), 165.0f);
                SetInputBindingUiViewActive(g_InputBindingUiRowLabels[slot], true);
                SetInputBindingUiViewActive(g_InputBindingUiRowButtons[slot], true);
                SetInputBindingUiViewActive(g_InputBindingUiRowBackdrops[slot], true);
            }
        }

        // --- OpenShim settings page implementation ------------------------------

        static void* ReadOptionsInputSingletonRaw()
        {
            __try
            {
                return *reinterpret_cast<void* const volatile*>(kOptionsInputSingletonAddr);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

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
        static const char* const kShimSettingsOnOffLabels[] = { "On", "Off" };
        static const char* const kShimSettingsUnderAttackValues[] = { "Normal", "Minimal", "None" };
        static const char* const kShimSettingsUnitVoValues[] = { "Normal", "Reduced", "None" };
        static const char* const kShimSettingsTargetPolicyValues[] = { "Default", "NeutralOnly", "ExplicitOnly" };
        static const char* const kShimSettingsTargetPolicyLabels[] = { "Default", "Neutral Only", "Explicit Only" };
        static const char* const kShimSettingsScrapHudValues[] = { "Legacy", "Stock" };
        static const char* const kShimSettingsHeadlightColorValues[] =
        {
            "Stock", "White", "Red", "Green", "Blue", "Yellow",
            "Cyan", "Magenta", "Orange", "Purple", "Teal", "Rainbow"
        };
        static const char* const kShimSettingsHeadlightBeamValues[] = { "Stock", "Focused", "Wide" };
        static const char* const kShimSettingsTargetPolicyAltKeys[] = { "TargetReticle" };
        static const char* const kShimSettingsReticleConvAltKeys[] = { "SmartReticleConvergence" };
        static const char* const kShimSettingsScavengerAltKeys[] = { "ScavengerPathing" };
        static const char* const kShimSettingsBindsUiAltKeys[] = { "CustomBindingUi" };

        static const ShimSettingDescriptor g_ShimSettingsRegistry[] =
        {
            { "Attack Alert", "Display", "UnderAttackAlert", nullptr, 0,
              kShimSettingsUnderAttackValues, kShimSettingsUnderAttackValues, 3, 0,
              ShimSettingApplyGroup::UnderAttackAlert,
              "Under-attack warning style: Normal, Minimal (quieter), or None." },
            { "Target Popup", "Display", "TargetPolicy",
              kShimSettingsTargetPolicyAltKeys, 1,
              kShimSettingsTargetPolicyValues, kShimSettingsTargetPolicyLabels, 3, 0,
              ShimSettingApplyGroup::TargetReticle,
              "When the reticle target popup appears: always, neutral objects only, or explicit targets only." },
            { "Scrap/Pilot HUD", "Display", "ScrapPilotHud", nullptr, 0,
              kShimSettingsScrapHudValues, kShimSettingsScrapHudValues, 2, 0,
              ShimSettingApplyGroup::GlobalImprovement,
              "Legacy BZ98-style scrap and pilot readout, or the stock Redux HUD." },
            { "Jet Flames", "Display", "JetFlames", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
              ShimSettingApplyGroup::JetFlames,
              "Faction-colored engine flames on jets and thrusters." },
            { "Unit Voices", "Display", "UnitVoFeedback", nullptr, 0,
              kShimSettingsUnitVoValues, kShimSettingsUnitVoValues, 3, 0,
              ShimSettingApplyGroup::UnitVo,
              "Unit voice feedback: Normal, Reduced chatter, or None." },
            { "Custom Keybinds", "General", "CustomBindsUi",
              kShimSettingsBindsUiAltKeys, 1,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::RestartRequired,
              "Key-binding editor on the Input options page. Restart required." },
            { "Weapon Convergence", "SinglePlayer", "WeaponConvergence", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::GlobalImprovement,
              "Fixed weapons converge on the reticle aim point. Single player only." },
            { "Reticle Convergence", "SinglePlayer", "PlayerReticleConvergence",
              kShimSettingsReticleConvAltKeys, 1,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::GlobalImprovement,
              "Player reticle tracks the weapon convergence point. Single player only." },
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
            { "Global Turbo", "SinglePlayer", "Turbo", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 1,
              ShimSettingApplyGroup::GlobalTurbo,
              "Turbo available on all drivable units. Single player only." },
            { "Player Headlight", "SinglePlayer", "Headlights", nullptr, 0,
              kShimSettingsOnOffValues, kShimSettingsOnOffLabels, 2, 0,
              ShimSettingApplyGroup::Headlights,
              "Headlight on your vehicle. Single player only." },
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
        };
        // The page count adapts to the registry (see the paging controls in
        // RefreshShimSettingsUiControls), so the registry may exceed the
        // per-page row slots.
        constexpr size_t kShimSettingsRegistryCount =
            sizeof(g_ShimSettingsRegistry) / sizeof(g_ShimSettingsRegistry[0]);

        static size_t ClampShimSettingsUiPageStart(size_t pageStart)
        {
            if constexpr (kShimSettingsRegistryCount <= kShimSettingsUiVisibleRowCount)
            {
                return 0;
            }
            else
            {
                constexpr size_t maxPageStart =
                    ((kShimSettingsRegistryCount - 1) / kShimSettingsUiVisibleRowCount) *
                    kShimSettingsUiVisibleRowCount;
                return (std::min)(pageStart, maxPageStart);
            }
        }

        // The UI shows the ini baseline: the value the key currently resolves to
        // in openshim.ini (or the setting's default when absent/unrecognized).
        static size_t GetShimSettingCurrentIndex(const ShimSettingDescriptor& setting)
        {
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
            if (setting.values == kShimSettingsOnOffValues)
            {
                if (normalized == "1" || normalized == "true" || normalized == "on" ||
                    normalized == "yes" || normalized == "enabled")
                    return 0;
                if (normalized == "0" || normalized == "false" || normalized == "off" ||
                    normalized == "no" || normalized == "disabled")
                    return 1;
            }
            else if (setting.values == kShimSettingsUnitVoValues)
            {
                if (normalized == "1" || normalized == "true" || normalized == "on" ||
                    normalized == "yes" || normalized == "enabled")
                    return 0;
                if (normalized == "0" || normalized == "false" || normalized == "off" ||
                    normalized == "no" || normalized == "disabled")
                    return 2;
            }

            return setting.defaultIndex;
        }


        static void ResetShimSettingsUiVisuals()
        {
            g_ShimSettingsUiBackdrop = nullptr;
            g_ShimSettingsUiFrame = nullptr;
            g_ShimSettingsUiTopMask = nullptr;
            g_ShimSettingsUiContentMask = nullptr;
            g_ShimSettingsUiHeaderBackdrop = nullptr;
            g_ShimSettingsUiRowBackdrops.fill(nullptr);
            g_ShimSettingsUiHeaderLabel = nullptr;
            g_ShimSettingsUiStatusLabel = nullptr;
            g_ShimSettingsUiFooterLabel = nullptr;
            g_ShimSettingsUiBackButton = nullptr;
            g_ShimSettingsUiPageLabel = nullptr;
            g_ShimSettingsUiPrevPageButton = nullptr;
            g_ShimSettingsUiNextPageButton = nullptr;
            g_ShimSettingsUiRowLabels.fill(nullptr);
            g_ShimSettingsUiRowButtons.fill(nullptr);
        }

        static void SetShimSettingsUiControlsVisible(bool visible)
        {
            SetInputBindingUiViewActive(g_ShimSettingsUiBackdrop, visible);
            SetInputBindingUiViewActive(g_ShimSettingsUiFrame, visible);
            SetInputBindingUiViewActive(g_ShimSettingsUiTopMask, visible);
            SetInputBindingUiViewActive(g_ShimSettingsUiContentMask, visible);
            SetInputBindingUiViewActive(g_ShimSettingsUiHeaderBackdrop, visible);
            for (void* backdrop : g_ShimSettingsUiRowBackdrops)
                SetInputBindingUiViewActive(backdrop, visible);
            SetInputBindingUiViewActive(g_ShimSettingsUiHeaderLabel, visible);
            SetInputBindingUiViewActive(g_ShimSettingsUiStatusLabel, visible);
            SetInputBindingUiViewActive(g_ShimSettingsUiFooterLabel, visible);
            SetInputBindingUiViewActive(g_ShimSettingsUiBackButton, visible);
            SetInputBindingUiViewActive(g_ShimSettingsUiPageLabel, visible);
            SetInputBindingUiViewActive(g_ShimSettingsUiPrevPageButton, visible);
            SetInputBindingUiViewActive(g_ShimSettingsUiNextPageButton, visible);
            for (void* label : g_ShimSettingsUiRowLabels)
                SetInputBindingUiViewActive(label, visible);
            for (void* button : g_ShimSettingsUiRowButtons)
                SetInputBindingUiViewActive(button, visible);
        }

        static void SetInputBindingUiControlsVisible(bool visible)
        {
            SetInputBindingUiViewActive(g_InputBindingUiBackdrop, visible);
            SetInputBindingUiViewActive(g_InputBindingUiFrame, visible);
            SetInputBindingUiViewActive(g_InputBindingUiTopMask, visible);
            SetInputBindingUiViewActive(g_InputBindingUiContentMask, visible);
            SetInputBindingUiViewActive(g_InputBindingUiHeaderBackdrop, visible);
            for (void* backdrop : g_InputBindingUiRowBackdrops)
                SetInputBindingUiViewActive(backdrop, visible);
            SetInputBindingUiViewActive(g_InputBindingUiHeaderLabel, visible);
            SetInputBindingUiViewActive(g_InputBindingUiStatusLabel, visible);
            SetInputBindingUiViewActive(g_InputBindingUiPageLabel, visible);
            SetInputBindingUiViewActive(g_InputBindingUiBackButton, visible);
            SetInputBindingUiViewActive(g_InputBindingUiDefaultsButton, visible);
            SetInputBindingUiViewActive(g_InputBindingUiInputFamilyButton, visible);
            SetInputBindingUiViewActive(g_InputBindingUiGameKeyFamilyButton, visible);
            SetInputBindingUiViewActive(g_InputBindingUiPrevPageButton, visible);
            SetInputBindingUiViewActive(g_InputBindingUiNextPageButton, visible);
            SetInputBindingUiViewActive(g_InputBindingUiRefreshButton, visible);
            for (void* label : g_InputBindingUiRowLabels)
                SetInputBindingUiViewActive(label, visible);
            for (void* button : g_InputBindingUiRowButtons)
                SetInputBindingUiViewActive(button, visible);
        }

        static void RefreshShimSettingsUiControls()
        {
            g_ShimSettingsUiPageStart = ClampShimSettingsUiPageStart(g_ShimSettingsUiPageStart);

            SetInputBindingUiLabelTextFitted(g_ShimSettingsUiHeaderLabel, "OpenShim Settings", 800.0f);
            SetInputBindingUiLabelTextFitted(g_ShimSettingsUiStatusLabel,
                                             g_ShimSettingsUiStatusText.c_str(), 800.0f);
            // Short enough to stay inside the header plate (ends at x=1135).
            SetInputBindingUiLabelTextFitted(
                g_ShimSettingsUiFooterLabel,
                "Click a value to cycle it. Never applies in MP. * = after restart.",
                900.0f);

            // Paging controls only appear once the registry outgrows one page;
            // blank the captions too, an inactive caption keeps drawing.
            const size_t pageCount =
                (kShimSettingsRegistryCount + kShimSettingsUiVisibleRowCount - 1) /
                kShimSettingsUiVisibleRowCount;
            const bool paged = pageCount > 1;
            if (paged)
            {
                char pageText[64] = {};
                std::snprintf(pageText, sizeof(pageText), "Page %u of %u",
                              static_cast<unsigned>(g_ShimSettingsUiPageStart /
                                                        kShimSettingsUiVisibleRowCount + 1),
                              static_cast<unsigned>(pageCount));
                SetInputBindingUiLabelTextFitted(g_ShimSettingsUiPageLabel, pageText, 105.0f);
                SetInputBindingUiButtonText(g_ShimSettingsUiPrevPageButton, "Prev");
                SetInputBindingUiButtonText(g_ShimSettingsUiNextPageButton, "Next");
            }
            else
            {
                SetInputBindingUiLabelText(g_ShimSettingsUiPageLabel, "");
                SetInputBindingUiButtonText(g_ShimSettingsUiPrevPageButton, "");
                SetInputBindingUiButtonText(g_ShimSettingsUiNextPageButton, "");
            }
            SetInputBindingUiViewActive(g_ShimSettingsUiPageLabel, paged);
            SetInputBindingUiViewActive(g_ShimSettingsUiPrevPageButton, paged);
            SetInputBindingUiViewActive(g_ShimSettingsUiNextPageButton, paged);

            for (size_t slot = 0; slot < kShimSettingsUiVisibleRowCount; ++slot)
            {
                const size_t index = g_ShimSettingsUiPageStart + slot;
                if (index >= kShimSettingsRegistryCount)
                {
                    SetInputBindingUiLabelText(g_ShimSettingsUiRowLabels[slot], "");
                    SetInputBindingUiButtonText(g_ShimSettingsUiRowButtons[slot], "");
                    SetInputBindingUiViewActive(g_ShimSettingsUiRowLabels[slot], false);
                    SetInputBindingUiViewActive(g_ShimSettingsUiRowButtons[slot], false);
                    SetInputBindingUiViewActive(g_ShimSettingsUiRowBackdrops[slot], false);
                    continue;
                }

                const ShimSettingDescriptor& setting = g_ShimSettingsRegistry[index];
                const size_t valueIndex = GetShimSettingCurrentIndex(setting);
                std::string valueText = setting.valueLabels[valueIndex];
                if (setting.applyGroup == ShimSettingApplyGroup::RestartRequired)
                    valueText += " *";
                SetInputBindingUiLabelTextFitted(g_ShimSettingsUiRowLabels[slot], setting.label, 275.0f);
                SetInputBindingUiButtonTextFitted(g_ShimSettingsUiRowButtons[slot],
                                                  valueText.c_str(), 165.0f);
                SetInputBindingUiViewActive(g_ShimSettingsUiRowLabels[slot], true);
                SetInputBindingUiViewActive(g_ShimSettingsUiRowButtons[slot], true);
                SetInputBindingUiViewActive(g_ShimSettingsUiRowBackdrops[slot], true);
            }
        }

        static void EnsureShimSettingsUiControls(void* screen)
        {
            if (!screen)
                return;

            void* const visualParent = screen;
            void* controlParent = ResolveStockOptionsInputMiddleOverlay(screen);
            if (!controlParent)
                controlParent = screen;

            static constexpr float kBackdropX = 0.0f;
            static constexpr float kBackdropY = 0.0f;
            static constexpr float kBackdropW = 1440.0f;
            static constexpr float kBackdropH = 1080.0f;
            static constexpr float kHeaderX = 320.0f;
            static constexpr float kHeaderY = 176.0f;
            static constexpr float kHeaderW = 800.0f;
            static constexpr float kHeaderH = 28.0f;
            static constexpr float kStatusX = 320.0f;
            static constexpr float kStatusY = 204.0f;
            static constexpr float kStatusW = 800.0f;
            static constexpr float kStatusH = 24.0f;
            static constexpr float kFooterX = 320.0f;
            static constexpr float kFooterY = 230.0f;
            static constexpr float kFooterW = 900.0f;
            static constexpr float kFooterH = 22.0f;
            static constexpr float kToolbarY = 256.0f;
            static constexpr float kToolbarW = 150.0f;
            static constexpr float kToolbarH = 34.0f;
            static constexpr float kTopMaskX = 220.0f;
            static constexpr float kTopMaskY = 122.0f;
            static constexpr float kTopMaskW = 1000.0f;
            // Runs down to the content mask seam so the Back button row is not
            // drawn over an unmasked strip of the stock page (122+174 > 292).
            static constexpr float kTopMaskH = 174.0f;
            // Same x/width as the top mask so the two stack into one flush
            // panel column instead of a stepped pair of rectangles.
            static constexpr float kContentMaskX = 220.0f;
            static constexpr float kContentMaskY = 292.0f;
            static constexpr float kContentMaskW = 1000.0f;
            static constexpr float kContentMaskH = 456.0f;
            // Labels get the wider share of each column: at the UI font size the
            // old 200px label box truncated even short names ("Jet Fl...").
            // Values are compact enums that shrink their own text scale, so they
            // read fine in a narrower box.
            static constexpr float kRowLeftBaseX = 258.0f;
            static constexpr float kRowRightBaseX = 740.0f;
            static constexpr float kRowY = 308.0f;
            static constexpr float kRowLabelW = 285.0f;
            static constexpr float kRowButtonH = 30.0f;
            // Matches the input page's row step so both pages read as one family.
            static constexpr float kRowStep = 38.0f;
            static constexpr float kRowButtonOffsetX = 292.0f;
            static constexpr float kRowButtonW = 175.0f;
            static constexpr float kPageLabelX = 790.0f;
            static constexpr float kPageLabelY = 262.0f;
            static constexpr float kPageLabelW = 105.0f;
            static constexpr float kPageLabelH = 22.0f;

            const unsigned screenTag = static_cast<unsigned>(reinterpret_cast<uintptr_t>(screen));
            char controlName[64] = {};

            std::snprintf(controlName, sizeof(controlName), "OpenShimSettingsBackdrop_%08X", screenTag);
            CreateInputBindingUiOverlay(g_ShimSettingsUiBackdrop, visualParent, controlName,
                                        "blackui.png", kBackdropX, kBackdropY, kBackdropW, kBackdropH, 0x60);
            std::snprintf(controlName, sizeof(controlName), "OpenShimSettingsFrame_%08X", screenTag);
            CreateInputBindingUiOverlay(g_ShimSettingsUiFrame, visualParent, controlName,
                                        "keyOptions_center.png", kBackdropX, kBackdropY, kBackdropW, kBackdropH, 0x60);
            std::snprintf(controlName, sizeof(controlName), "OpenShimSettingsTopMask_%08X", screenTag);
            CreateInputBindingUiOverlay(g_ShimSettingsUiTopMask, visualParent, controlName,
                                        "blackui.png", kTopMaskX, kTopMaskY, kTopMaskW, kTopMaskH, 0x60);
            std::snprintf(controlName, sizeof(controlName), "OpenShimSettingsContentMask_%08X", screenTag);
            CreateInputBindingUiOverlay(g_ShimSettingsUiContentMask, visualParent, controlName,
                                        "blackui.png", kContentMaskX, kContentMaskY, kContentMaskW, kContentMaskH, 0x60);
            std::snprintf(controlName, sizeof(controlName), "OpenShimSettingsHeaderPlate_%08X", screenTag);
            CreateInputBindingUiPlate(g_ShimSettingsUiHeaderBackdrop, controlParent, controlName,
                                      305.0f, 168.0f, 830.0f, 84.0f);

            std::snprintf(controlName, sizeof(controlName), "OpenShimSettingsHeader_%08X", screenTag);
            CreateInputBindingUiLabel(g_ShimSettingsUiHeaderLabel, controlParent, controlName, "",
                                      kHeaderX, kHeaderY, kHeaderW, kHeaderH);
            std::snprintf(controlName, sizeof(controlName), "OpenShimSettingsStatus_%08X", screenTag);
            CreateInputBindingUiLabel(g_ShimSettingsUiStatusLabel, controlParent, controlName, "",
                                      kStatusX, kStatusY, kStatusW, kStatusH);
            std::snprintf(controlName, sizeof(controlName), "OpenShimSettingsFooter_%08X", screenTag);
            CreateInputBindingUiLabel(g_ShimSettingsUiFooterLabel, controlParent, controlName, "",
                                      kFooterX, kFooterY, kFooterW, kFooterH);
            std::snprintf(controlName, sizeof(controlName), "OpenShimSettingsBack_%08X", screenTag);
            CreateInputBindingUiButton(g_ShimSettingsUiBackButton, controlParent, controlName, "Back",
                                       195.0f, kToolbarY, kToolbarW, kToolbarH,
                                       reinterpret_cast<void*>(ShimSettingsBackClick));
            // Prev/Next mirror the input page toolbar (905/1015, w100); refresh
            // hides all three while the registry still fits on one page.
            std::snprintf(controlName, sizeof(controlName), "OpenShimSettingsPage_%08X", screenTag);
            CreateInputBindingUiLabel(g_ShimSettingsUiPageLabel, controlParent, controlName, "",
                                      kPageLabelX, kPageLabelY, kPageLabelW, kPageLabelH);
            std::snprintf(controlName, sizeof(controlName), "OpenShimSettingsPrev_%08X", screenTag);
            CreateInputBindingUiButton(g_ShimSettingsUiPrevPageButton, controlParent, controlName, "Prev",
                                       905.0f, kToolbarY, 100.0f, kToolbarH,
                                       reinterpret_cast<void*>(ShimSettingsPrevPageClick));
            std::snprintf(controlName, sizeof(controlName), "OpenShimSettingsNext_%08X", screenTag);
            CreateInputBindingUiButton(g_ShimSettingsUiNextPageButton, controlParent, controlName, "Next",
                                       1015.0f, kToolbarY, 100.0f, kToolbarH,
                                       reinterpret_cast<void*>(ShimSettingsNextPageClick));

            for (size_t slot = 0; slot < kShimSettingsUiVisibleRowCount; ++slot)
            {
                const size_t column = slot / kShimSettingsUiRowsPerColumn;
                const size_t row = slot % kShimSettingsUiRowsPerColumn;
                const float baseX = (column == 0) ? kRowLeftBaseX : kRowRightBaseX;
                const float y = kRowY + (static_cast<float>(row) * kRowStep);
                std::snprintf(controlName, sizeof(controlName),
                              "OpenShimSettingsRowPlate_%08X_%02u", screenTag, static_cast<unsigned>(slot));
                CreateInputBindingUiPlate(g_ShimSettingsUiRowBackdrops[slot], controlParent, controlName,
                                          baseX - 8.0f, y, kRowButtonOffsetX + 8.0f,
                                          kRowButtonH);
                std::snprintf(controlName, sizeof(controlName),
                              "OpenShimSettingsRowLabel_%08X_%02u", screenTag, static_cast<unsigned>(slot));
                CreateInputBindingUiLabel(g_ShimSettingsUiRowLabels[slot], controlParent, controlName, "",
                                          baseX, y + 2.0f, kRowLabelW, kRowButtonH);
                std::snprintf(controlName, sizeof(controlName),
                              "OpenShimSettingsRowButton_%08X_%02u", screenTag, static_cast<unsigned>(slot));
                CreateInputBindingUiButton(g_ShimSettingsUiRowButtons[slot], controlParent, controlName, "",
                                           baseX + kRowButtonOffsetX, y, kRowButtonW, kRowButtonH,
                                           kShimSettingsRowClickCallbacks[slot],
                                           kShimSettingsRowHoverCallbacks[slot]);
            }
        }

        static void ActivateShimSettingsPage(void* screen)
        {
            if (!screen)
                return;

            if (g_InputScreenBinding.decorated != screen)
            {
                ResetInputBindingUiVisuals();
                g_InputScreenBinding.BindDecorated(screen);
            }

            g_ShimSettingsPageActive = true;
            SetInputBindingUiControlsVisible(false);
            SuppressStockOptionsInputWidgets(screen);
            SetStockOptionsInputAccessoryVisibility(screen, false);
            EnsureShimSettingsUiControls(screen);
            RefreshShimSettingsUiControls();
            Log(L"[SETTINGSUI] Settings page active screen=0x%08X rows=%u\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(screen)),
                static_cast<unsigned>(sizeof(g_ShimSettingsRegistry) / sizeof(g_ShimSettingsRegistry[0])));
        }

        static void OnShimSettingsRowClicked(size_t rowIndex)
        {
            const size_t settingIndex = g_ShimSettingsUiPageStart + rowIndex;
            if (settingIndex >= kShimSettingsRegistryCount || !g_ShimSettingsPageActive)
                return;

            const ShimSettingDescriptor& setting = g_ShimSettingsRegistry[settingIndex];
            const size_t nextIndex = (GetShimSettingCurrentIndex(setting) + 1) % setting.valueCount;
            const char* const newValue = setting.values[nextIndex];

            std::string error;
            if (!WriteUserConfigValueLossless(setting.section, setting.key,
                                              setting.altKeys, setting.altKeyCount,
                                              newValue, error))
            {
                g_ShimSettingsUiStatusText = "Save failed: " + error;
                Log(L"[SETTINGSUI] Save failed for %hs: %hs\n", setting.key, error.c_str());
                RefreshShimSettingsUiControls();
                return;
            }

            ApplyShimSettingLive(setting.applyGroup);

            g_ShimSettingsUiStatusText = std::string(setting.label) + " = " +
                setting.valueLabels[nextIndex] +
                (setting.applyGroup == ShimSettingApplyGroup::RestartRequired
                     ? "  (takes effect after restart)"
                     : "  (applied)");
            RefreshShimSettingsUiControls();
        }

        // The +0x150 slot fires on hover-state *changes* (verified in-game
        // 2026-07-17: sweeping row 3 -> row 0 invoked row 3's thunk while the
        // cursor already sat on row 0), so the thunk's own row index lags one
        // row behind the cursor. Resolve the row actually under the cursor by
        // reversing the UI transform: the 1440x1080 design space is uniformly
        // scaled by clientHeight/1080 and centered horizontally.
        static bool TryResolveHoveredShimSettingsSlot(size_t* outSlot)
        {
            HWND window = GetForegroundWindow();
            if (!window || !outSlot)
                return false;

            POINT cursor = {};
            RECT client = {};
            if (!GetCursorPos(&cursor) || !ScreenToClient(window, &cursor) ||
                !GetClientRect(window, &client) || client.bottom <= 0)
                return false;

            const float scale = static_cast<float>(client.bottom) / 1080.0f;
            const float offsetX = (static_cast<float>(client.right) - 1440.0f * scale) * 0.5f;
            const float logicalX = (static_cast<float>(cursor.x) - offsetX) / scale;
            const float logicalY = static_cast<float>(cursor.y) / scale;

            // Full row footprint (plate through value button) per column.
            constexpr float kRowSpanW = 292.0f + 175.0f + 8.0f;
            size_t column = 0;
            if (logicalX >= 258.0f - 8.0f && logicalX <= 258.0f + kRowSpanW - 8.0f)
                column = 0;
            else if (logicalX >= 740.0f - 8.0f && logicalX <= 740.0f + kRowSpanW - 8.0f)
                column = 1;
            else
                return false;

            const float rowOffset = logicalY - 308.0f;
            if (rowOffset < 0.0f)
                return false;
            const size_t row = static_cast<size_t>(rowOffset / 38.0f);
            if (row >= kShimSettingsUiRowsPerColumn ||
                (rowOffset - static_cast<float>(row) * 38.0f) > 30.0f)
                return false;

            *outSlot = column * kShimSettingsUiRowsPerColumn + row;
            return true;
        }

        // Writes the hovered row's description straight into the status label.
        // g_ShimSettingsUiStatusText is left alone so the next full refresh
        // restores the last click/apply status. Screens may invoke every hover
        // slot in bulk on open, hence the active-page gate.
        static void OnShimSettingsRowHovered(size_t rowIndex)
        {
            if (!g_ShimSettingsPageActive)
                return;

            size_t slot = rowIndex;
            if (!TryResolveHoveredShimSettingsSlot(&slot))
                slot = rowIndex; // cursor resolve unavailable: thunk index

            const size_t settingIndex = g_ShimSettingsUiPageStart + slot;
            if (settingIndex >= kShimSettingsRegistryCount)
                return;

            const char* description = g_ShimSettingsRegistry[settingIndex].description;
            if (description && *description)
                SetInputBindingUiLabelTextFitted(g_ShimSettingsUiStatusLabel, description, 800.0f);
        }

        static void OnShimSettingsPageStepClicked(int direction)
        {
            if (!g_ShimSettingsPageActive)
                return;

            const size_t current = g_ShimSettingsUiPageStart;
            if (direction < 0)
            {
                g_ShimSettingsUiPageStart =
                    current >= kShimSettingsUiVisibleRowCount ? current - kShimSettingsUiVisibleRowCount : 0;
            }
            else if (direction > 0)
            {
                g_ShimSettingsUiPageStart = current + kShimSettingsUiVisibleRowCount;
            }

            g_ShimSettingsUiPageStart = ClampShimSettingsUiPageStart(g_ShimSettingsUiPageStart);
            RefreshShimSettingsUiControls();
        }

        // Hide the settings page and hand the host screen back to the binding
        // UI (when enabled) so a later plain "Input" visit that does not
        // reconstruct the screen still shows the key-binding page.
        static void DeactivateShimSettingsPage()
        {
            if (!g_ShimSettingsPageActive)
                return;

            g_ShimSettingsPageActive = false;
            g_ShimSettingsUiStatusText.clear();
            SetShimSettingsUiControlsVisible(false);

            void* const hostScreen = g_InputScreenBinding.decorated;
            if (ShouldEnableInputBindingUiReplacement() && hostScreen)
            {
                EnsureInputBindingUiControls(hostScreen);
                RefreshInputBindingUiControls();
            }
        }

        static void OnShimSettingsBackClicked()
        {
            DeactivateShimSettingsPage();
            OnInputBindingBackClicked();
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
            g_ShimSettingsUiStatusText.clear();
            g_ShimSettingsPageRequested = true;
            g_ShimSettingsPageRequestTick = now;
            auto* const navigateToInputScreen =
                reinterpret_cast<void(__cdecl*)()>(kOptionsParentInputClickThunkAddr);
            navigateToInputScreen();

            // If the shell keeps a constructed input screen alive, the ctor hook
            // will not re-fire for this navigation; restyle the live screen now.
            // Pointer equality is only trustworthy while the dtor hook clears
            // the binding on destruction: without it, a destroy-then-deferred-
            // reconstruct navigation leaves the binding matching a freed
            // screen and this path walks dangling child views (dump 2692).
            void* const liveInputScreen = ReadOptionsInputSingletonRaw();
            if (g_OptionsInputDtorHookInstalled &&
                g_InputScreenBinding.IsLive(liveInputScreen))
            {
                g_ShimSettingsPageRequested = false;
                ActivateShimSettingsPage(liveInputScreen);
            }
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

            static constexpr float kBackdropX = 0.0f;
            static constexpr float kBackdropY = 0.0f;
            static constexpr float kBackdropW = 1440.0f;
            static constexpr float kBackdropH = 1080.0f;
            static constexpr float kHeaderX = 320.0f;
            static constexpr float kHeaderY = 176.0f;
            static constexpr float kHeaderW = 800.0f;
            static constexpr float kHeaderH = 28.0f;
            static constexpr float kStatusX = 320.0f;
            static constexpr float kStatusY = 204.0f;
            static constexpr float kStatusW = 800.0f;
            static constexpr float kStatusH = 24.0f;
            static constexpr float kPageX = 320.0f;
            static constexpr float kPageY = 230.0f;
            static constexpr float kPageW = 800.0f;
            static constexpr float kPageH = 22.0f;
            static constexpr float kToolbarY = 256.0f;
            static constexpr float kToolbarW = 150.0f;
            static constexpr float kToolbarH = 34.0f;
            static constexpr float kTopMaskX = 220.0f;
            static constexpr float kTopMaskY = 122.0f;
            static constexpr float kTopMaskW = 1000.0f;
            // Runs down to the content mask seam so the toolbar row is not
            // drawn over an unmasked strip of the stock page (122+174 > 292).
            static constexpr float kTopMaskH = 174.0f;
            // Same x/width as the top mask so the two stack into one flush
            // panel column instead of a stepped pair of rectangles.
            static constexpr float kContentMaskX = 220.0f;
            static constexpr float kContentMaskY = 292.0f;
            static constexpr float kContentMaskW = 1000.0f;
            static constexpr float kContentMaskH = 456.0f;
            // Same label/value split as the settings page: labels get the wide
            // box (the old 205px truncated "Throttle Forward"-length names),
            // value buttons shrink their own text scale in the narrow one.
            static constexpr float kRowLeftBaseX = 258.0f;
            static constexpr float kRowRightBaseX = 740.0f;
            static constexpr float kRowY = 308.0f;
            static constexpr float kRowLabelW = 285.0f;
            static constexpr float kRowButtonH = 30.0f;
            static constexpr float kRowStep = 38.0f;
            static constexpr float kRowButtonOffsetX = 292.0f;
            static constexpr float kRowCompactButtonW = 175.0f;

            const unsigned screenTag = static_cast<unsigned>(reinterpret_cast<uintptr_t>(screen));
            char controlName[64] = {};

            std::snprintf(controlName, sizeof(controlName), "OpenShimInputBackdrop_%08X", screenTag);
            CreateInputBindingUiOverlay(g_InputBindingUiBackdrop,
                                        visualParent,
                                        controlName,
                                        "blackui.png",
                                        kBackdropX,
                                        kBackdropY,
                                        kBackdropW,
                                        kBackdropH,
                                        0x60);
            std::snprintf(controlName, sizeof(controlName), "OpenShimInputFrame_%08X", screenTag);
            CreateInputBindingUiOverlay(g_InputBindingUiFrame,
                                        visualParent,
                                        controlName,
                                        "keyOptions_center.png",
                                        kBackdropX,
                                        kBackdropY,
                                        kBackdropW,
                                        kBackdropH,
                                        0x60);
            std::snprintf(controlName, sizeof(controlName), "OpenShimInputTopMask_%08X", screenTag);
            CreateInputBindingUiOverlay(g_InputBindingUiTopMask,
                                        visualParent,
                                        controlName,
                                        "blackui.png",
                                        kTopMaskX,
                                        kTopMaskY,
                                        kTopMaskW,
                                        kTopMaskH,
                                        0x60);
            std::snprintf(controlName, sizeof(controlName), "OpenShimInputContentMask_%08X", screenTag);
            CreateInputBindingUiOverlay(g_InputBindingUiContentMask,
                                        visualParent,
                                        controlName,
                                        "blackui.png",
                                        kContentMaskX,
                                        kContentMaskY,
                                        kContentMaskW,
                                        kContentMaskH,
                                        0x60);
            std::snprintf(controlName, sizeof(controlName), "OpenShimInputHeaderPlate_%08X", screenTag);
            CreateInputBindingUiPlate(g_InputBindingUiHeaderBackdrop,
                                      controlParent,
                                      controlName,
                                      305.0f,
                                      168.0f,
                                      830.0f,
                                      84.0f);

            std::snprintf(controlName, sizeof(controlName), "OpenShimInputHeader_%08X", screenTag);
            CreateInputBindingUiLabel(g_InputBindingUiHeaderLabel, controlParent, controlName, "", kHeaderX, kHeaderY, kHeaderW, kHeaderH);
            std::snprintf(controlName, sizeof(controlName), "OpenShimInputStatus_%08X", screenTag);
            CreateInputBindingUiLabel(g_InputBindingUiStatusLabel, controlParent, controlName, "", kStatusX, kStatusY, kStatusW, kStatusH);
            std::snprintf(controlName, sizeof(controlName), "OpenShimInputPage_%08X", screenTag);
            CreateInputBindingUiLabel(g_InputBindingUiPageLabel, controlParent, controlName, "", kPageX, kPageY, kPageW, kPageH);
            std::snprintf(controlName, sizeof(controlName), "OpenShimInputBack_%08X", screenTag);
            CreateInputBindingUiButton(g_InputBindingUiBackButton, controlParent, controlName, "Back", 195.0f, kToolbarY, kToolbarW, kToolbarH, reinterpret_cast<void*>(InputBindingBackClick));
            std::snprintf(controlName, sizeof(controlName), "OpenShimInputDefaults_%08X", screenTag);
            CreateInputBindingUiButton(g_InputBindingUiDefaultsButton, controlParent, controlName, "Reset Controls", 355.0f, kToolbarY, 210.0f, kToolbarH, reinterpret_cast<void*>(InputBindingDefaultsClick));
            std::snprintf(controlName, sizeof(controlName), "OpenShimInputFamily_%08X", screenTag);
            CreateInputBindingUiButton(g_InputBindingUiInputFamilyButton, controlParent, controlName, "Controls", 585.0f, kToolbarY, kToolbarW, kToolbarH, reinterpret_cast<void*>(InputBindingFamilyInputClick));
            std::snprintf(controlName, sizeof(controlName), "OpenShimGameKeyFamily_%08X", screenTag);
            CreateInputBindingUiButton(g_InputBindingUiGameKeyFamilyButton, controlParent, controlName, "RTS Actions", 745.0f, kToolbarY, kToolbarW, kToolbarH, reinterpret_cast<void*>(InputBindingFamilyGameKeyClick));
            // Prev/Next/Refresh stay inside the masked frame (right edge 1220);
            // the old 1155+90 Refresh spilled past it onto the stock page.
            std::snprintf(controlName, sizeof(controlName), "OpenShimInputPrev_%08X", screenTag);
            CreateInputBindingUiButton(g_InputBindingUiPrevPageButton, controlParent, controlName, "Prev", 905.0f, kToolbarY, 100.0f, kToolbarH, reinterpret_cast<void*>(InputBindingPrevPageClick));
            std::snprintf(controlName, sizeof(controlName), "OpenShimInputNext_%08X", screenTag);
            CreateInputBindingUiButton(g_InputBindingUiNextPageButton, controlParent, controlName, "Next", 1015.0f, kToolbarY, 100.0f, kToolbarH, reinterpret_cast<void*>(InputBindingNextPageClick));
            std::snprintf(controlName, sizeof(controlName), "OpenShimInputReload_%08X", screenTag);
            CreateInputBindingUiButton(g_InputBindingUiRefreshButton, controlParent, controlName, "Refresh", 1125.0f, kToolbarY, 90.0f, kToolbarH, reinterpret_cast<void*>(InputBindingRefreshClick));

            for (size_t slot = 0; slot < kInputBindingUiVisibleRowCount; ++slot)
            {
                const size_t column = slot / kInputBindingUiRowsPerColumn;
                const size_t row = slot % kInputBindingUiRowsPerColumn;
                const float baseX = (column == 0) ? kRowLeftBaseX : kRowRightBaseX;
                const float y = kRowY + (static_cast<float>(row) * kRowStep);
                std::snprintf(controlName, sizeof(controlName), "OpenShimInputRowPlate_%08X_%02u", screenTag, static_cast<unsigned>(slot));
                CreateInputBindingUiPlate(g_InputBindingUiRowBackdrops[slot], controlParent, controlName,
                                          baseX - 8.0f, y,
                                          kRowButtonOffsetX + 8.0f, kRowButtonH);
                std::snprintf(controlName, sizeof(controlName), "OpenShimInputRowLabel_%08X_%02u", screenTag, static_cast<unsigned>(slot));
                CreateInputBindingUiLabel(g_InputBindingUiRowLabels[slot], controlParent, controlName, "", baseX, y + 2.0f, kRowLabelW, kRowButtonH);
                std::snprintf(controlName, sizeof(controlName), "OpenShimInputRowButton_%08X_%02u", screenTag, static_cast<unsigned>(slot));
                CreateInputBindingUiButton(g_InputBindingUiRowButtons[slot], controlParent, controlName, "", baseX + kRowButtonOffsetX, y, kRowCompactButtonW, kRowButtonH, kInputBindingRowClickCallbacks[slot]);
            }
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
            auto* const backClick = reinterpret_cast<void(__cdecl*)()>(kOptionsInputBackClickAddr);
            if (backClick)
            {
                Log(L"[INPUTUI] Invoking stock Back callback\n");
                backClick();
            }
        }

        static void OnInputBindingDefaultsClicked()
        {
            auto* const defaultsClick = reinterpret_cast<void(__cdecl*)()>(kOptionsInputDefaultsClickAddr);
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
                static const uint8_t kExpectedReadMappingTableBytes[] =
                {
                    0x55, 0x8B, 0xEC, 0x81, 0xEC, 0xDC, 0x02, 0x00, 0x00
                };
                g_InputMapLiveReloadAvailable =
                    ExpectedBytesMatchAt(kGogReadMappingTableAddr,
                                         kExpectedReadMappingTableBytes,
                                         sizeof(kExpectedReadMappingTableBytes));
                Log(L"[INPUTUI] Live input.map reload %hs at 0x%08X\n",
                    g_InputMapLiveReloadAvailable ? "available" : "unavailable (bytes mismatch)",
                    static_cast<uint32_t>(kGogReadMappingTableAddr));
            }

            if (!g_InputMapLiveReloadAvailable)
                return false;

            auto* readMappingTable =
                reinterpret_cast<FnReloadGameKeyMap>(kGogReadMappingTableAddr);
            if (!CallReloadMappingTableGuarded(readMappingTable))
            {
                // The stock parser crashed mid-reload once (dump 30940, AV in a
                // msvcr120 copy reached from 0x00620010). Trading a stale table
                // for a crash-to-desktop: report failure and stop retrying.
                g_InputMapLiveReloadAvailable = false;
                Log(L"[INPUTUI] Live input.map reload faulted at 0x%08X; disabled for this session\n",
                    static_cast<uint32_t>(kGogReadMappingTableAddr));
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

            const bool requestFresh =
                g_ShimSettingsPageRequested &&
                (GetTickCount64() - g_ShimSettingsPageRequestTick) <= kShimSettingsPageRequestTtlMs;
            const bool settingsMode = requestFresh && ShouldEnableShimSettingsUi();
            g_ShimSettingsPageRequested = false;
            if (settingsMode)
            {
                ActivateShimSettingsPage(screen);
                return;
            }

            g_ShimSettingsPageActive = false;
            if (!ShouldEnableInputBindingUiReplacement())
                return;

            EnsureInputBindingUiControls(screen);
            SetShimSettingsUiControlsVisible(false);
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

            g_ShimSettingsPageActive = false;
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
                const bool isButton = (vtable == kUiButtonVtableAddr);

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

        // A shorter final row keeps the button inside the frame at 16:9 instead
        // of clipping off the bottom.
        static void EnsureShimSettingsMenuButton(void* parentScreen)
        {
            if (!parentScreen || !g_BzrFn_ButtonCtor || !g_BzrFn_AddChild)
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

            void* buttonMem = ::operator new(0x1EC, std::nothrow);
            if (!buttonMem)
                return;

            std::memset(buttonMem, 0, 0x1EC);
            void* const button = g_BzrFn_ButtonCtor(buttonMem,
                                                    "OpenShimSettingsMenuButton",
                                                    // Continue the stock options column with a compact fifth row.
                                                    // The shorter height keeps it above the lower frame at 16:9.
                                                    // x/w match the stock Play/Graphic/Audio/Input buttons because
                                                    // this shares their parent: the layout pass (0x007D14B0) adds
                                                    // Middle_Overlay's absolute origin on top of these design
                                                    // coordinates, so 508 lands the column-aligned 1496 at 4K.
                                                    508.0f,
                                                    882.0f,
                                                    422.0f,
                                                    58.0f,
                                                    0x20,
                                                    buttonParent,
                                                    0,
                                                    0);
            if (!button)
                return;

            if (g_BzrFn_SetTextureOff) g_BzrFn_SetTextureOff(button, "optionhv.png");
            if (g_BzrFn_SetTextureOver) g_BzrFn_SetTextureOver(button, "optionck.png");
            if (g_BzrFn_SetTextureOn) g_BzrFn_SetTextureOn(button, "optionck.png");
            if (g_BzrFn_SetButtonLabel) g_BzrFn_SetButtonLabel(button, "OpenShim Options");
            if (g_BzrFn_SetButtonTextScale) g_BzrFn_SetButtonTextScale(button, 0.85f);
            if (g_BzrFn_SetOnClick)
                g_BzrFn_SetOnClick(button, reinterpret_cast<void*>(ShimSettingsMenuClick));
            if (g_BzrFn_SetOnHover)
                g_BzrFn_SetOnHover(button, reinterpret_cast<void*>(InputBindingUiButtonOnHoverNoop));
            // Append as Middle_Overlay's sixth child, alongside Back and the four
            // stock option buttons. All six are leaf views, so they share the
            // dispatch pass and are tried in list order; Back stays at index 0
            // and keeps first refusal on the top-left clicks.
            g_BzrFn_AddChild(buttonParent, button, 0);
            g_ShimSettingsMenuButton = button;

            const auto* const buttonRect =
                reinterpret_cast<const float*>(reinterpret_cast<uint8_t*>(button) + 4);
            void** const parentBegin = *reinterpret_cast<void***>(
                reinterpret_cast<uint8_t*>(buttonParent) + kUiViewChildBeginOffset);
            void** const parentEnd = *reinterpret_cast<void***>(
                reinterpret_cast<uint8_t*>(buttonParent) + kUiViewChildEndOffset);
            Log(L"[SETTINGSUI] OpenShim button added to options screen=0x%08X parent=0x%08X "
                L"parentName=%hs parentChildren=%d rect=(%.1f,%.1f,%.1f,%.1f)\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(parentScreen)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(buttonParent)),
                ReadUiViewName(buttonParent),
                static_cast<int>(parentEnd - parentBegin),
                buttonRect[0], buttonRect[1], buttonRect[2], buttonRect[3]);
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



    }

    void EnsureInputBindingPopulateHookScaffold()
    {
        InitializeInputBindingUiScaffold();

        // The settings page reuses the hooked input screen as its host, so
        // the ctor/key hooks install when either feature is enabled.
        if (!ShouldEnableInputBindingUiReplacement() && !ShouldEnableShimSettingsUi())
            return;

        EnsureOptionsScreenDtorHook(kOptionsInputDtorAddr,
                                    g_OptionsInputDtorDetour,
                                    reinterpret_cast<void*>(OptionsInputDtorHook),
                                    g_BzrFn_OptionsInputDtorOriginal,
                                    g_OptionsInputDtorHookInstalled,
                                    g_OptionsInputDtorHookAttempted,
                                    L"INPUTUI");

        if (g_InputBindingUiPopulateHookInstalled && g_InputBindingUiKeyReleasedHookInstalled)
            return;

        const uint8_t kExpectedOptionsInputCtorBytes[kOptionsInputCtorDetourLen] =
        {
            0x55, 0x8B, 0xEC, 0x6A, 0xFF, 0x68, 0x73, 0x12, 0x86, 0x00
        };
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
            if (!ExpectedBytesMatchAt(kOptionsInputKeyReleasedAddr,
                                      kExpectedOptionsInputKeyReleasedBytes,
                                      sizeof(kExpectedOptionsInputKeyReleasedBytes)))
            {
                if (!g_InputBindingUiPopulateHookMismatchLogged)
                {
                    Log(L"[INPUTUI] KeyReleased entry bytes mismatch at 0x%08X; input UI replacement remains disabled\n",
                        static_cast<uint32_t>(kOptionsInputKeyReleasedAddr));
                    g_InputBindingUiPopulateHookMismatchLogged = true;
                }
                return;
            }

            if (!InstallInlineDetour32(g_OptionsInputKeyReleasedDetour,
                                       kOptionsInputKeyReleasedAddr,
                                       reinterpret_cast<void*>(OptionsInputKeyReleasedHook),
                                       kOptionsInputKeyReleasedDetourLen,
                                       kExpectedOptionsInputKeyReleasedBytes,
                                       sizeof(kExpectedOptionsInputKeyReleasedBytes)))
            {
                Log(L"[INPUTUI] Failed installing key-release hook at 0x%08X\n",
                    static_cast<uint32_t>(kOptionsInputKeyReleasedAddr));
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
            if (!ExpectedBytesMatchAt(kOptionsInputCtorAddr,
                                      kExpectedOptionsInputCtorBytes,
                                      sizeof(kExpectedOptionsInputCtorBytes)))
            {
                if (!g_InputBindingUiPopulateHookMismatchLogged)
                {
                    Log(L"[INPUTUI] Constructor entry bytes mismatch at 0x%08X; input UI replacement remains disabled\n",
                        static_cast<uint32_t>(kOptionsInputCtorAddr));
                    g_InputBindingUiPopulateHookMismatchLogged = true;
                }
                return;
            }

            if (!InstallInlineDetour32(g_OptionsInputPopulateUiDetour,
                                       kOptionsInputCtorAddr,
                                       reinterpret_cast<void*>(OptionsInputPopulateUiHook),
                                       kOptionsInputCtorDetourLen,
                                       kExpectedOptionsInputCtorBytes,
                                       sizeof(kExpectedOptionsInputCtorBytes)))
            {
                Log(L"[INPUTUI] Failed installing constructor hook at 0x%08X\n",
                    static_cast<uint32_t>(kOptionsInputCtorAddr));
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
            static_cast<uint32_t>(kOptionsInputCtorAddr),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_OptionsInputPopulateUiDetour.trampoline)),
            static_cast<uint32_t>(kOptionsInputKeyReleasedAddr));
    }

    void EnsureOptionsParentCtorHookScaffold()
    {
        if (!ShouldEnableShimSettingsUi())
            return;

        EnsureOptionsScreenDtorHook(kOptionsParentDtorAddr,
                                    g_OptionsParentDtorDetour,
                                    reinterpret_cast<void*>(OptionsParentDtorHook),
                                    g_BzrFn_OptionsParentDtorOriginal,
                                    g_OptionsParentDtorHookInstalled,
                                    g_OptionsParentDtorHookAttempted,
                                    L"SETTINGSUI");

        if (g_OptionsParentHookInstalled)
            return;

        const uint8_t kExpectedOptionsParentCtorBytes[kOptionsParentCtorDetourLen] =
        {
            0x55, 0x8B, 0xEC, 0x6A, 0xFF, 0x68, 0x60, 0x13, 0x86, 0x00
        };

        if (!ExpectedBytesMatchAt(kOptionsParentCtorAddr,
                                  kExpectedOptionsParentCtorBytes,
                                  sizeof(kExpectedOptionsParentCtorBytes)))
        {
            if (!g_OptionsParentHookMismatchLogged)
            {
                Log(L"[SETTINGSUI] Options ctor bytes mismatch at 0x%08X; settings UI disabled\n",
                    static_cast<uint32_t>(kOptionsParentCtorAddr));
                g_OptionsParentHookMismatchLogged = true;
            }
            return;
        }

        if (!InstallInlineDetour32(g_OptionsParentCtorDetour,
                                   kOptionsParentCtorAddr,
                                   reinterpret_cast<void*>(OptionsParentCtorHook),
                                   kOptionsParentCtorDetourLen,
                                   kExpectedOptionsParentCtorBytes,
                                   sizeof(kExpectedOptionsParentCtorBytes)))
        {
            Log(L"[SETTINGSUI] Failed installing options ctor hook at 0x%08X\n",
                static_cast<uint32_t>(kOptionsParentCtorAddr));
            return;
        }

        g_BzrFn_OptionsParentCtor =
            reinterpret_cast<FnOptionsInputCtor>(g_OptionsParentCtorDetour.trampoline);
        g_OptionsParentHookInstalled = (g_BzrFn_OptionsParentCtor != nullptr);
        if (g_OptionsParentHookInstalled)
        {
            Log(L"[SETTINGSUI] Installed options ctor hook entry=0x%08X trampoline=0x%08X\n",
                static_cast<uint32_t>(kOptionsParentCtorAddr),
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
        // A stock ESC backs out of the settings page without our Back button;
        // hand the host screen back to the binding UI before the stock handler
        // navigates away.
        if (g_ShimSettingsPageActive && key == VK_ESCAPE)
            DeactivateShimSettingsPage();

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
