// shell_screens.cpp
// BZR Open Shim - OpenShim's own shell screens: a detour on the shell's
// screen factory that builds registered screens the way stock screens are
// built, plus a small widget kit over the stock cUI constructors.
//
// HOW A STOCK SCREEN IS BUILT (GOG 2.2.301, ShellScreenFactory 0x007C7AD0)
//
//   factory(manager, id):
//     ShellFactoryTick()                 bump the screen-creation counter
//     manager+0x18 = 0
//     screen = new cUI_X                 every one derives from cUI_View and
//                                        starts with the Top Screen ctor
//                                        (UiTopScreenCtor 0x007D0FA0): stock
//                                        background + four border views
//     screen+0x138 = manager             (0x005DF1F0)
//     if alert pending && id != 0x1D:    attach the GameAlert dialog
//        manager+0x24 = manager+0x28 = 0; ShellShowPendingAlert(screen, manager)
//
// The shell later deletes the screen through vtable slot 0 and updates it
// every frame through slot 13 (+0x34, which calls slot 13 on each child).
// cUI_View already implements every slot, so an OpenShim screen is a plain
// 0x144-byte cUI_View with its own copy of the cUI_View vtable in which only
// four slots differ:
//   slot 0  deleting dtor: tells the registered screen it is closing, then
//           runs cUI_View's
//   slot 2  char dispatcher (0x007D2420): offers a typed character to the
//           screen's onChar first, then runs cUI_View's
//   slot 5  OnKey: the stock handler cUI_OptionsParent and cUI_Load share
//           (UiScreenEscBackKey 0x00788E70), which runs Back on Esc
//   slot 13 per-frame update (0x007D37F0): runs cUI_View's, then the
//           screen's tick
//
// Navigation is the stock pair the shell's own buttons use, both __thiscall
// on the manager each screen stores at +0x138: ShellRequestScreen(id) pushes
// id on the history vector, ShellBackScreen() pops it. An OpenShim id on the
// history stack is rebuilt by this detour whenever the shell comes back to
// it, so Back from a stock screen opened over an OpenShim one works too.

#include "shell_screens.h"

#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "patcher.h"

#include <windows.h>

#include <cstring>
#include <filesystem>

namespace BZROpenShim
{
    namespace Hooks
    {
        bool VtableTypeNameMatches(uintptr_t vtableAddress, const char* expectedName);
    }
}

namespace BZROpenShim::ShellScreens
{
    const ButtonSkin kSkinTopCorner = { "topcorner.png", "topcrnhv.png", "topcrnck.png" };
    const ButtonSkin kSkinToMainMenu = { "tomnoff.png", "tomnon.png", "tomnclk.png" };

    namespace
    {
        constexpr size_t kUiViewVtableSlots = 15;
        constexpr size_t kVtableSlotDeletingDtor = 0;
        constexpr size_t kVtableSlotChar = 2;
        constexpr size_t kVtableSlotOnKey = 5;
        constexpr size_t kVtableSlotUpdate = 13;
        constexpr size_t kScreenManagerOffset = 0x138;
        constexpr size_t kManagerCreatingFlagOffset = 0x18;
        constexpr size_t kManagerAlertByteA = 0x24;
        constexpr size_t kManagerAlertByteB = 0x28;
        constexpr int kAlertDialogScreenId = 0x1D;  // cUI_AlertDlgBox never gets the pending alert
        constexpr size_t kFactoryDetourLen = 10;    // push ebp; mov ebp,esp; push -1; push imm32
        constexpr size_t kMaxScreens = 32;

        using FnFactory = void* (__thiscall*)(void* manager, int id);
        using FnRequest = void(__thiscall*)(void* manager, int id);
        using FnBack = void(__thiscall*)(void* manager);
        using FnTick = void(__cdecl*)();
        using FnShowAlert = void(__cdecl*)(void* screen, void* manager);
        using FnTopScreenCtor = void* (__thiscall*)(void* self);
        using FnDeletingDtor = void* (__thiscall*)(void* self, unsigned flags);
        using FnGameNew = void* (__cdecl*)(size_t size);
        using FnStockUpdate = void(__thiscall*)(void* self);
        using FnStockChar = uint8_t(__thiscall*)(void* self, uint8_t ch);

        uint32_t g_FactoryAddr = 0;
        uint32_t g_RequestAddr = 0;
        uint32_t g_BackAddr = 0;
        uint32_t g_TickAddr = 0;
        uint32_t g_ShowAlertAddr = 0;
        uint32_t g_TopScreenCtorAddr = 0;
        uint32_t g_EscBackKeyAddr = 0;
        uint32_t g_AlertCheckAddr = 0;
        uint32_t g_UiViewVtableAddr = 0;
        const uint8_t* g_AlertPendingFlag = nullptr;
        FnGameNew g_GameNew = nullptr;

        InlineDetour32 g_FactoryDetour = {};
        FnFactory g_FactoryOriginal = nullptr;
        FnDeletingDtor g_StockDeletingDtor = nullptr;
        FnStockUpdate g_StockUpdate = nullptr;
        FnStockChar g_StockChar = nullptr;
        bool g_TickFaultLogged = false;
        bool g_CharFaultLogged = false;

        // [0] is the RTTI locator copied from the stock table, so the screen
        // still identifies as cUI_View to anything that checks.
        uintptr_t g_ScreenVtable[1 + kUiViewVtableSlots] = {};

        ScreenDef g_Defs[kMaxScreens] = {};
        size_t g_DefCount = 0;

        struct LiveEntry
        {
            uint32_t id;
            void* screen;
        };
        LiveEntry g_Live[kMaxScreens] = {};

        bool g_Bound = false;
        bool g_BindAttempted = false;
        bool g_DetourInstalled = false;

        void* __fastcall CustomScreenDeletingDtor(void* self, void* /*edx*/, unsigned flags);
        void __fastcall CustomScreenUpdate(void* self, void* /*edx*/);
        uint8_t __fastcall CustomScreenChar(void* self, void* /*edx*/, uint8_t ch);
        void* __fastcall ShellFactoryHook(void* manager, void* /*edx*/, int id);

        bool BindShellRows()
        {
            if (g_BindAttempted)
                return g_Bound;
            g_BindAttempted = true;

            const HookEngine::EngineRow rows[] = {
                { "ShellScreenFactory", &g_FactoryAddr },
                { "ShellRequestScreen", &g_RequestAddr },
                { "ShellBackScreen", &g_BackAddr },
                { "ShellFactoryTick", &g_TickAddr },
                { "ShellShowPendingAlert", &g_ShowAlertAddr },
                { "ShellFactoryAlertCheck", &g_AlertCheckAddr },
                { "UiTopScreenCtor", &g_TopScreenCtorAddr },
                { "UiScreenEscBackKey", &g_EscBackKeyAddr },
                { "UiViewVtable", &g_UiViewVtableAddr },
            };
            if (!HookEngine::BindEngineRows("OpenShim shell screens", rows))
                return false;
            if (!Hooks::VtableTypeNameMatches(g_UiViewVtableAddr, ".?AVcUI_View@@"))
            {
                Log(L"[SHELLUI] cUI_View vtable RTTI mismatch; OpenShim screens stand down\n");
                return false;
            }

            // movzx edx, byte ptr [flag] -- the operand is the alert-pending byte.
            g_AlertPendingFlag = reinterpret_cast<const uint8_t*>(
                static_cast<uintptr_t>(*reinterpret_cast<const uint32_t*>(g_AlertCheckAddr + 3)));

            // Screens are freed by the shell with the game's operator delete,
            // so they are allocated with the game's operator new.
            HMODULE crt = GetModuleHandleW(L"MSVCR120.dll");
            g_GameNew = crt ? reinterpret_cast<FnGameNew>(GetProcAddress(crt, "??2@YAPAXI@Z")) : nullptr;
            if (!g_GameNew)
            {
                Log(L"[SHELLUI] game operator new not found; OpenShim screens stand down\n");
                return false;
            }

            const uintptr_t* stock = reinterpret_cast<const uintptr_t*>(static_cast<uintptr_t>(g_UiViewVtableAddr));
            g_ScreenVtable[0] = stock[-1];
            std::memcpy(&g_ScreenVtable[1], stock, sizeof(uintptr_t) * kUiViewVtableSlots);
            g_StockDeletingDtor = reinterpret_cast<FnDeletingDtor>(stock[kVtableSlotDeletingDtor]);
            g_ScreenVtable[1 + kVtableSlotDeletingDtor] = reinterpret_cast<uintptr_t>(&CustomScreenDeletingDtor);
            g_ScreenVtable[1 + kVtableSlotOnKey] = g_EscBackKeyAddr;
            g_StockUpdate = reinterpret_cast<FnStockUpdate>(stock[kVtableSlotUpdate]);
            g_StockChar = reinterpret_cast<FnStockChar>(stock[kVtableSlotChar]);
            g_ScreenVtable[1 + kVtableSlotUpdate] = reinterpret_cast<uintptr_t>(&CustomScreenUpdate);
            g_ScreenVtable[1 + kVtableSlotChar] = reinterpret_cast<uintptr_t>(&CustomScreenChar);

            g_Bound = g_BzrFn_OverlayCtor && g_BzrFn_LabelCtor && g_BzrFn_ButtonCtor &&
                      g_BzrFn_AddChild && g_BzrFn_SetOnClick && g_BzrFn_SetOnHover;
            if (!g_Bound)
                Log(L"[SHELLUI] stock widget bindings unavailable; OpenShim screens stand down\n");
            return g_Bound;
        }

        bool EnsureFactoryDetour()
        {
            if (g_DetourInstalled)
                return true;
            if (!BindShellRows())
                return false;

            // The row's guard has already verified these bytes.
            const uint8_t* live = reinterpret_cast<const uint8_t*>(static_cast<uintptr_t>(g_FactoryAddr));
            if (!InstallInlineDetour32(g_FactoryDetour, g_FactoryAddr,
                                       reinterpret_cast<void*>(&ShellFactoryHook),
                                       kFactoryDetourLen, live, kFactoryDetourLen))
            {
                Log(L"[SHELLUI] could not detour the screen factory at 0x%08X\n", g_FactoryAddr);
                return false;
            }
            g_FactoryOriginal = reinterpret_cast<FnFactory>(g_FactoryDetour.trampoline);
            g_DetourInstalled = g_FactoryOriginal != nullptr;
            Log(L"[SHELLUI] screen factory detoured at 0x%08X\n", g_FactoryAddr);
            return g_DetourInstalled;
        }

        const ScreenDef* FindDef(uint32_t id)
        {
            for (size_t i = 0; i < g_DefCount; ++i)
                if (g_Defs[i].id == id)
                    return &g_Defs[i];
            return nullptr;
        }

        void SetLive(uint32_t id, void* screen)
        {
            for (auto& entry : g_Live)
            {
                if (entry.id == id)
                {
                    entry.screen = screen;
                    return;
                }
            }
            for (auto& entry : g_Live)
            {
                if (entry.id == 0)
                {
                    entry = { id, screen };
                    return;
                }
            }
        }

        // The build runs under SEH so a fault in a screen's widget code
        // leaves the shell with a usable (if bare) screen instead of taking
        // the game down inside the factory.
        bool RunBuildGuarded(BuildFn build, void* screen, DWORD& faultCode)
        {
            faultCode = 0;
            __try
            {
                return build(screen);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                faultCode = GetExceptionCode();
                return false;
            }
        }

        void* CreateCustomScreen(void* manager, const ScreenDef& def, int id)
        {
            reinterpret_cast<FnTick>(static_cast<uintptr_t>(g_TickAddr))();
            *(reinterpret_cast<uint8_t*>(manager) + kManagerCreatingFlagOffset) = 0;
            Log(L"[SHELLUI] creating screen %hs (id 0x%08X)\n", def.name, def.id);

            void* memory = g_GameNew(kUiViewSize);
            if (!memory)
                return nullptr;
            std::memset(memory, 0, kUiViewSize);
            void* screen = reinterpret_cast<FnTopScreenCtor>(static_cast<uintptr_t>(g_TopScreenCtorAddr))(memory);
            *reinterpret_cast<uintptr_t*>(screen) = reinterpret_cast<uintptr_t>(&g_ScreenVtable[1]);
            *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(screen) + kScreenManagerOffset) = manager;
            SetLive(def.id, screen);

            if (def.build)
            {
                DWORD fault = 0;
                if (!RunBuildGuarded(def.build, screen, fault))
                {
                    if (fault)
                        Log(L"[SHELLUI] %hs build faulted (0x%08X); screen left bare\n", def.name, fault);
                    else
                        Log(L"[SHELLUI] %hs build incomplete; screen left as built\n", def.name);
                }
            }

            if (*g_AlertPendingFlag && id != kAlertDialogScreenId)
            {
                *(reinterpret_cast<uint8_t*>(manager) + kManagerAlertByteA) = 0;
                *(reinterpret_cast<uint8_t*>(manager) + kManagerAlertByteB) = 0;
                reinterpret_cast<FnShowAlert>(static_cast<uintptr_t>(g_ShowAlertAddr))(screen, manager);
            }
            return screen;
        }

        void* __fastcall ShellFactoryHook(void* manager, void* /*edx*/, int id)
        {
            const ScreenDef* def = FindDef(static_cast<uint32_t>(id));
            if (!def)
                return g_FactoryOriginal(manager, id);
            return CreateCustomScreen(manager, *def, id);
        }

        const ScreenDef* DefForScreen(void* self)
        {
            for (const auto& entry : g_Live)
                if (entry.screen == self && entry.id != 0)
                    return FindDef(entry.id);
            return nullptr;
        }

        // The callbacks run under SEH, as the build does: a fault logs once
        // and the frame continues rather than taking the game down.
        bool RunTickGuarded(TickFn tick, void* screen, DWORD& faultCode)
        {
            faultCode = 0;
            __try
            {
                tick(screen);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                faultCode = GetExceptionCode();
                return false;
            }
        }

        bool RunCharGuarded(CharFn onChar, void* screen, uint8_t ch, bool& consumed, DWORD& faultCode)
        {
            faultCode = 0;
            consumed = false;
            __try
            {
                consumed = onChar(screen, ch);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                faultCode = GetExceptionCode();
                return false;
            }
        }

        void __fastcall CustomScreenUpdate(void* self, void* /*edx*/)
        {
            g_StockUpdate(self);
            const ScreenDef* def = DefForScreen(self);
            if (!def || !def->tick)
                return;
            DWORD fault = 0;
            if (!RunTickGuarded(def->tick, self, fault) && !g_TickFaultLogged)
            {
                g_TickFaultLogged = true;
                Log(L"[SHELLUI] %hs tick faulted (0x%08X); further faults are not logged
",
                    def->name, fault);
            }
        }

        uint8_t __fastcall CustomScreenChar(void* self, void* /*edx*/, uint8_t ch)
        {
            const ScreenDef* def = DefForScreen(self);
            if (def && def->onChar)
            {
                bool consumed = false;
                DWORD fault = 0;
                if (!RunCharGuarded(def->onChar, self, ch, consumed, fault))
                {
                    if (!g_CharFaultLogged)
                    {
                        g_CharFaultLogged = true;
                        Log(L"[SHELLUI] %hs char handler faulted (0x%08X); further faults are not logged
",
                            def->name, fault);
                    }
                }
                else if (consumed)
                    return 1;
            }
            return g_StockChar(self, ch);
        }

        void* __fastcall CustomScreenDeletingDtor(void* self, void* /*edx*/, unsigned flags)
        {
            for (auto& entry : g_Live)
            {
                if (entry.screen != self)
                    continue;
                entry.screen = nullptr;
                if (const ScreenDef* def = FindDef(entry.id))
                {
                    Log(L"[SHELLUI] closing screen %hs\n", def->name);
                    if (def->closed)
                        def->closed(self);
                }
            }
            return g_StockDeletingDtor(self, flags);
        }

        void* ScreenManager(void* screen)
        {
            if (!screen)
                return nullptr;
            return *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(screen) + kScreenManagerOffset);
        }

        void __cdecl ButtonHoverNoop(void* /*param*/)
        {
        }

        void* AllocWidget(size_t size)
        {
            void* memory = g_GameNew ? g_GameNew(size) : nullptr;
            if (memory)
                std::memset(memory, 0, size);
            return memory;
        }

        int FloatBits(float value)
        {
            int bits = 0;
            std::memcpy(&bits, &value, sizeof(bits));
            return bits;
        }
    }

    bool IsAvailable()
    {
        return BindShellRows();
    }

    bool RegisterScreen(const ScreenDef& def)
    {
        if (!EnsureFactoryDetour())
            return false;
        if (FindDef(def.id))
            return true;
        if (g_DefCount >= kMaxScreens || def.id < kCustomScreenIdBase)
        {
            Log(L"[SHELLUI] cannot register screen %hs (id 0x%08X): %ls\n", def.name, def.id,
                def.id < kCustomScreenIdBase ? L"id below the custom range" : L"screen table full");
            return false;
        }
        g_Defs[g_DefCount++] = def;
        Log(L"[SHELLUI] registered screen %hs (id 0x%08X)\n", def.name, def.id);
        return true;
    }

    bool RequestScreen(void* fromScreen, uint32_t id)
    {
        void* manager = ScreenManager(fromScreen);
        if (!g_Bound || !manager)
            return false;
        reinterpret_cast<FnRequest>(static_cast<uintptr_t>(g_RequestAddr))(manager, static_cast<int>(id));
        return true;
    }

    bool Back(void* fromScreen)
    {
        void* manager = ScreenManager(fromScreen);
        if (!g_Bound || !manager)
            return false;
        reinterpret_cast<FnBack>(static_cast<uintptr_t>(g_BackAddr))(manager);
        return true;
    }

    void* LiveScreen(uint32_t id)
    {
        for (const auto& entry : g_Live)
            if (entry.id == id)
                return entry.screen;
        return nullptr;
    }

    void* AddPanel(void* container, void* layoutParent, const char* name, const Rect& r,
                   const char* texture, uint32_t flags)
    {
        if (!container || !g_Bound)
            return nullptr;
        void* memory = AllocWidget(kUiViewSize);
        if (!memory)
            return nullptr;
        void* view = g_BzrFn_OverlayCtor(memory, name, r.x, r.y, r.w, r.h, flags, layoutParent, 0);
        if (!view)
            return nullptr;
        if (g_BzrFn_UiSetActive)
            g_BzrFn_UiSetActive(view, 1);
        if (texture && *texture && g_BzrFn_SetTextureOff)
            g_BzrFn_SetTextureOff(view, texture);
        g_BzrFn_AddChild(container, view, 0);
        return view;
    }

    void* AddLabel(void* container, void* layoutParent, const char* name, const Rect& r,
                   const char* text, uint32_t flags)
    {
        if (!container || !g_Bound)
            return nullptr;
        void* memory = AllocWidget(kUiTextSize);
        if (!memory)
            return nullptr;
        void* label = g_BzrFn_LabelCtor(memory, name, r.x, r.y, r.w, r.h, flags, layoutParent, 0);
        if (!label)
            return nullptr;
        g_BzrFn_AddChild(container, label, 0);
        SetLabelText(label, text);
        if (g_BzrFn_UiSetActive)
            g_BzrFn_UiSetActive(label, 1);
        return label;
    }

    void* AddButton(void* container, void* layoutParent, const char* name, const Rect& r,
                    const char* text, const ButtonSkin& skin, float textScale,
                    float textOffset, void(__cdecl* onClick)(), HoverFn onHover)
    {
        if (!container || !g_Bound)
            return nullptr;
        void* memory = AllocWidget(kUiButtonSize);
        if (!memory)
            return nullptr;
        void* button = g_BzrFn_ButtonCtor(memory, name, r.x, r.y, r.w, r.h, kControlFlags,
                                          layoutParent, FloatBits(textOffset), 0);
        if (!button)
            return nullptr;
        if (skin.off && g_BzrFn_SetTextureOff) g_BzrFn_SetTextureOff(button, skin.off);
        if (skin.over && g_BzrFn_SetTextureOver) g_BzrFn_SetTextureOver(button, skin.over);
        if (skin.on && g_BzrFn_SetTextureOn) g_BzrFn_SetTextureOn(button, skin.on);
        if (g_BzrFn_SetButtonLabel)
            g_BzrFn_SetButtonLabel(button, text ? text : "");
        if (g_BzrFn_SetButtonTextScale)
            g_BzrFn_SetButtonTextScale(button, textScale);
        // The shell calls a child button's hover and click slots unchecked.
        g_BzrFn_SetOnClick(button, reinterpret_cast<void*>(onClick));
        g_BzrFn_SetOnHover(button, onHover ? reinterpret_cast<void*>(onHover)
                                           : reinterpret_cast<void*>(&ButtonHoverNoop));
        g_BzrFn_AddChild(container, button, 0);
        // The ctor leaves the button input-inactive until SetActive runs, as
        // every injected button in this codebase has found.
        if (g_BzrFn_UiSetActive)
            g_BzrFn_UiSetActive(button, 1);
        return button;
    }

    bool CursorDesignPoint(float& x, float& y)
    {
        HWND window = GetForegroundWindow();
        POINT cursor = {};
        RECT client = {};
        if (!window || !GetCursorPos(&cursor) || !ScreenToClient(window, &cursor) ||
            !GetClientRect(window, &client) || client.bottom <= 0)
            return false;
        const float scale = static_cast<float>(client.bottom) / 1080.0f;
        const float offsetX = (static_cast<float>(client.right) - 1440.0f * scale) * 0.5f;
        x = (static_cast<float>(cursor.x) - offsetX) / scale;
        y = static_cast<float>(cursor.y) / scale;
        return true;
    }

    void SetLabelText(void* label, const char* text)
    {
        if (!label || !g_BzrFn_SetTooltip)
            return;
        g_BzrFn_SetTooltip(label, text ? text : "");
        if (g_BzrFn_LabelState)
            g_BzrFn_LabelState(label, reinterpret_cast<void*>(1));
    }

    bool IsTextureDeployed(const char* textureName)
    {
        if (!textureName || !*textureName)
            return false;
        wchar_t modulePath[MAX_PATH] = {};
        const DWORD length = GetModuleFileNameW(nullptr, modulePath, MAX_PATH);
        if (length == 0 || length >= MAX_PATH)
            return false;
        std::error_code ec;
        const std::filesystem::path path = std::filesystem::path(modulePath).parent_path() /
            "BZ_ASSETS_CORE" / "common" / "ui" / "CustomWidgets" / textureName;
        return std::filesystem::exists(path, ec) && !ec;
    }
}
