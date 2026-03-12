#include "bzr_hooks.h"

#include <Windows.h>
#include <cstdio>
#include <cstring>
#include <new>

namespace BZROpenShim
{
    // ---------------------------------------------------------------------
    // Global state used by hooks/trampolines
    // ---------------------------------------------------------------------
    void* g_VehicleListContext = nullptr;
    void* g_VehicleListParam   = nullptr;

    void* g_BzrnetHostObj   = nullptr;
    void* g_BzrnetClientObj = nullptr;

    void* g_BanParentHost  = nullptr;
    void* g_BanParentClient = nullptr;
    void* g_BanButtonHost  = nullptr;
    void* g_BanButtonClient = nullptr;
    void* g_BanLabelHost   = nullptr;
    void* g_BanLabelClient = nullptr;

    uint32_t g_BanFlag = 0;
    float g_BanX = 0.0f;
    float g_BanY = 0.0f;

    void* g_BzrFn_VehicleFixPre = nullptr;
    void* g_BzrFn_VehicleFixOrig = nullptr;

    BzrString g_BzrnetLabel1 = {};
    BzrString g_BzrnetLabel2 = {};
    BzrString g_BzrnetLabel3 = {};
    BzrString g_BzrnetLabel4 = {};

    // ---------------------------------------------------------------------
    // BZR function pointers (GOG v2.2.301 addresses)
    // ---------------------------------------------------------------------
    using FnVehicleListSet = void(__thiscall*)(void* thisPtr, BzrString a, BzrString b);
    using FnVehicleListLoad = void(__thiscall*)(void* thisPtr, BzrString* name);
    using FnVehicleListStep = void(__thiscall*)(void* thisPtr);
    using FnVehicleListFinalize = void(__thiscall*)(void* thisPtr);

    using FnUiCtor = void* (__thiscall*)(void* self,
                                         const char* label,
                                         float x, float y, float w, float h,
                                         uint32_t flags, void* parent, int a, int b);
    using FnUiSetStr = void(__thiscall*)(void* self, const char* str);
    using FnUiSetInt = void(__thiscall*)(void* self, void* param);
    using FnUiSetCb  = void(__thiscall*)(void* self, void* cb);
    using FnUiAddChild = void(__thiscall*)(void* parent, void* child, int flags);

    using FnGetSelected = void* (__thiscall*)(void* list);
    using FnCommandHandler = void(__cdecl*)(uint16_t id, const char* cmd);

    static void** g_BzrPtr_945478 = nullptr;
    static void** g_BzrPtr_94548C = nullptr;
    static void** g_BzrPtr_94555C = nullptr;
    static void** g_BzrPtr_9456D0 = nullptr;
    static void** g_BzrPtr_94557C = nullptr;
    static uint8_t* g_BzrPtr_CurrentUser = nullptr;

    static FnVehicleListSet g_BzrFn_VehicleListSet = nullptr;      // 0x0076B7A0
    static FnVehicleListFinalize g_BzrFn_VehicleListFinalize = nullptr; // 0x0076BA00
    static FnVehicleListLoad g_BzrFn_VehicleListLoad = nullptr;    // 0x00766900
    static FnVehicleListStep g_BzrFn_VehicleListRefresh1 = nullptr; // 0x007A3F80
    static FnVehicleListStep g_BzrFn_VehicleListRefresh2 = nullptr; // 0x007A4070

    static FnUiCtor g_BzrFn_ButtonCtor = nullptr; // 0x007C2480
    static FnUiCtor g_BzrFn_LabelCtor  = nullptr; // 0x007CC390
    static FnUiSetStr g_BzrFn_SetTextureOff = nullptr; // 0x007D2870
    static FnUiSetStr g_BzrFn_SetTextureOver = nullptr; // 0x007C2F10
    static FnUiSetStr g_BzrFn_SetTextureOn = nullptr; // 0x007C2E80
    static FnUiSetStr g_BzrFn_SetButtonLabel = nullptr; // 0x007C2950
    static FnUiSetStr g_BzrFn_SetTooltip = nullptr; // 0x007CC660
    static FnUiSetInt g_BzrFn_LabelState = nullptr; // 0x007CC5C0
    static FnUiSetCb g_BzrFn_SetOnClick = nullptr; // 0x007C23E0
    static FnUiSetCb g_BzrFn_SetOnHover = nullptr; // 0x007C23C0
    static FnUiAddChild g_BzrFn_AddChild = nullptr; // 0x007D2110

    static FnGetSelected g_BzrFn_GetSelected = nullptr; // 0x007CB1A0
    static FnCommandHandler g_BzrFn_CommandHandler = nullptr; // 0x006247A0

    // ---------------------------------------------------------------------
    // Helpers
    // ---------------------------------------------------------------------
    void ResolveBzrHooks()
    {
        g_BzrPtr_945478 = reinterpret_cast<void**>(0x00945478);
        g_BzrPtr_94548C = reinterpret_cast<void**>(0x0094548C);
        g_BzrPtr_94555C = reinterpret_cast<void**>(0x0094555C);
        g_BzrPtr_9456D0 = reinterpret_cast<void**>(0x009456D0);
        g_BzrPtr_94557C = reinterpret_cast<void**>(0x0094557C);
        g_BzrPtr_CurrentUser = reinterpret_cast<uint8_t*>(0x009C8F60);

        g_BzrFn_VehicleListSet = reinterpret_cast<FnVehicleListSet>(0x0076B7A0);
        g_BzrFn_VehicleListFinalize = reinterpret_cast<FnVehicleListFinalize>(0x0076BA00);
        g_BzrFn_VehicleListLoad = reinterpret_cast<FnVehicleListLoad>(0x00766900);
        g_BzrFn_VehicleListRefresh1 = reinterpret_cast<FnVehicleListStep>(0x007A3F80);
        g_BzrFn_VehicleListRefresh2 = reinterpret_cast<FnVehicleListStep>(0x007A4070);

        g_BzrFn_ButtonCtor = reinterpret_cast<FnUiCtor>(0x007C2480);
        g_BzrFn_LabelCtor  = reinterpret_cast<FnUiCtor>(0x007CC390);
        g_BzrFn_SetTextureOff = reinterpret_cast<FnUiSetStr>(0x007D2870);
        g_BzrFn_SetTextureOver = reinterpret_cast<FnUiSetStr>(0x007C2F10);
        g_BzrFn_SetTextureOn = reinterpret_cast<FnUiSetStr>(0x007C2E80);
        g_BzrFn_SetButtonLabel = reinterpret_cast<FnUiSetStr>(0x007C2950);
        g_BzrFn_SetTooltip = reinterpret_cast<FnUiSetStr>(0x007CC660);
        g_BzrFn_LabelState = reinterpret_cast<FnUiSetInt>(0x007CC5C0);
        g_BzrFn_SetOnClick = reinterpret_cast<FnUiSetCb>(0x007C23E0);
        g_BzrFn_SetOnHover = reinterpret_cast<FnUiSetCb>(0x007C23C0);
        g_BzrFn_AddChild = reinterpret_cast<FnUiAddChild>(0x007D2110);

        g_BzrFn_GetSelected = reinterpret_cast<FnGetSelected>(0x007CB1A0);
        g_BzrFn_CommandHandler = reinterpret_cast<FnCommandHandler>(0x006247A0);

        g_BzrFn_VehicleFixPre = reinterpret_cast<void*>(0x00481EA0);
        g_BzrFn_VehicleFixOrig = reinterpret_cast<void*>(0x00481AF0);
    }

    void InitBzrHookStrings()
    {
        BzrStringInitEmpty(&g_BzrnetLabel1);
        BzrStringInitEmpty(&g_BzrnetLabel2);
        BzrStringInitEmpty(&g_BzrnetLabel3);
        BzrStringInitEmpty(&g_BzrnetLabel4);
    }

    static uint8_t* VehicleEntryAt(void* context, uint32_t index)
    {
        if (!context) return nullptr;
        auto table = *reinterpret_cast<uint8_t**>(reinterpret_cast<uint8_t*>(context) + 0x18);
        if (!table) return nullptr;
        uint32_t bucket = *reinterpret_cast<uint32_t*>(table + 0x0C);
        uint32_t mask = *reinterpret_cast<uint32_t*>(table + 0x08);
        if (mask == 0) return nullptr;
        mask -= 1;
        uint32_t base = *reinterpret_cast<uint32_t*>(table + 0x04);
        return *reinterpret_cast<uint8_t**>(base + ((bucket + index) & mask) * 4);
    }

    static void VehicleListModFix_Select(const BzrString* name)
    {
        if (!g_VehicleListContext || !name)
            return;

        auto ctx = reinterpret_cast<uint8_t*>(g_VehicleListContext);
        *reinterpret_cast<int*>(ctx + 0x38) = -1;

        uint8_t* match = nullptr;
        auto table = *reinterpret_cast<uint8_t**>(ctx + 0x18);
        if (table)
        {
            uint32_t count = *reinterpret_cast<uint32_t*>(table + 0x10);
            if (count)
            {
                uint32_t bucket = *reinterpret_cast<uint32_t*>(table + 0x0C);
                uint32_t mask = *reinterpret_cast<uint32_t*>(table + 0x08);
                uint32_t base = *reinterpret_cast<uint32_t*>(table + 0x04);
                if (mask)
                {
                    mask -= 1;
                    for (uint32_t i = 0; i < count; ++i)
                    {
                        auto entry = *reinterpret_cast<uint8_t**>(base + ((bucket + i) & mask) * 4);
                        if (!entry)
                            continue;
                        auto entryStr = reinterpret_cast<const BzrString*>(entry);
                        if (BzrStringEquals(entryStr, name))
                        {
                            match = entry;
                            *reinterpret_cast<uint32_t*>(ctx + 0x38) = i;
                            break;
                        }
                    }
                }
            }
        }

        BzrString title;
        BzrString subtitle;
        if (match)
        {
            BzrStringCopy(&title, reinterpret_cast<const BzrString*>(match));
            BzrStringCopy(&subtitle, reinterpret_cast<const BzrString*>(match + 0x3C));
        }
        else
        {
            BzrStringInitEmpty(&title);
            BzrStringInitEmpty(&subtitle);
        }

        void* listThis = (g_BzrPtr_945478 && *g_BzrPtr_945478) ? *g_BzrPtr_945478 : nullptr;
        if (g_BzrFn_VehicleListSet && listThis)
            g_BzrFn_VehicleListSet(listThis, title, subtitle);

        BzrString file;
        BzrStringCopy(&file, name);
        BzrStringAppend(&file, ".vxt", 4);

        void* mgrThis = (g_BzrPtr_94548C && *g_BzrPtr_94548C) ? *g_BzrPtr_94548C : nullptr;
        if (g_BzrFn_VehicleListLoad && mgrThis)
            g_BzrFn_VehicleListLoad(mgrThis, &file);

        if (g_BzrFn_VehicleListRefresh1 && g_VehicleListContext)
            g_BzrFn_VehicleListRefresh1(g_VehicleListContext);
        if (g_BzrFn_VehicleListRefresh2 && g_VehicleListContext)
            g_BzrFn_VehicleListRefresh2(g_VehicleListContext);
        if (g_BzrFn_VehicleListFinalize && listThis)
            g_BzrFn_VehicleListFinalize(listThis);

        BzrStringFree(&title);
        BzrStringFree(&subtitle);
        BzrStringFree(&file);
    }

    void __fastcall VehicleListModFix2(void* thisPtr, void* /*edx*/, BzrString* name)
    {
        g_VehicleListContext = thisPtr;
        VehicleListModFix_Select(name);
    }

    void VehicleListModFix4Helper()
    {
        if (!g_BzrPtr_94555C || !*g_BzrPtr_94555C)
            return;

        auto root = reinterpret_cast<uint8_t*>(*g_BzrPtr_94555C);
        g_VehicleListContext = *reinterpret_cast<void**>(root + 0x1C8);
        if (!g_VehicleListContext)
            return;

        auto ctx = reinterpret_cast<uint8_t*>(g_VehicleListContext);
        int index = *reinterpret_cast<int*>(ctx + 0x38);
        BzrString title;
        BzrString subtitle;

        if (index >= 0)
        {
            auto entry = VehicleEntryAt(g_VehicleListContext, static_cast<uint32_t>(index));
            if (entry)
            {
                BzrStringCopy(&title, reinterpret_cast<const BzrString*>(entry));
                BzrStringCopy(&subtitle, reinterpret_cast<const BzrString*>(entry + 0x3C));
            }
            else
            {
                BzrStringInitEmpty(&title);
                BzrStringInitEmpty(&subtitle);
            }
        }
        else
        {
            BzrStringInitEmpty(&title);
            BzrStringInitEmpty(&subtitle);
        }

        void* listThis = (g_BzrPtr_945478 && *g_BzrPtr_945478) ? *g_BzrPtr_945478 : nullptr;
        if (g_BzrFn_VehicleListSet && listThis)
            g_BzrFn_VehicleListSet(listThis, title, subtitle);

        void* mgrThis = (g_BzrPtr_94548C && *g_BzrPtr_94548C) ? *g_BzrPtr_94548C : nullptr;
        if (g_BzrFn_VehicleListLoad && mgrThis && g_VehicleListParam)
            g_BzrFn_VehicleListLoad(mgrThis, reinterpret_cast<BzrString*>(g_VehicleListParam));

        if (g_BzrFn_VehicleListFinalize && listThis)
            g_BzrFn_VehicleListFinalize(listThis);

        BzrStringFree(&title);
        BzrStringFree(&subtitle);
    }

    static void AppendBanList(const char* id, const BzrString* name)
    {
        if (!id || !*id)
            return;
        FILE* f = nullptr;
        fopen_s(&f, "banlist.txt", "a");
        if (!f)
            return;

        if (name && name->size)
        {
            std::fprintf(f, "%s %.*s\n", id, static_cast<int>(name->size), BzrStringData(name));
        }
        else
        {
            std::fprintf(f, "%s\n", id);
        }
        std::fclose(f);
    }

    void __cdecl BanButtonOnClickHost()
    {
        if (!g_BzrPtr_9456D0 || !g_BzrFn_GetSelected)
            return;

        void* root = *g_BzrPtr_9456D0;
        if (!root)
            return;

        auto listObj = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(root) + 0x0C);
        auto selected = g_BzrFn_GetSelected(listObj);
        if (!selected)
            return;

        int type = *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(selected) + 0x08);
        if (type != 1 && type != 2)
            return;

        const char prefix = (type == 1) ? 'S' : 'G';
        uint64_t id = *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(selected) + 0x10);
        char idbuf[32] = {};
        std::snprintf(idbuf, sizeof(idbuf), "%c%llu", prefix, static_cast<unsigned long long>(id));

        BzrString name;
        BzrStringCopy(&name, reinterpret_cast<BzrString*>(reinterpret_cast<uint8_t*>(selected) + 0x2C));
        AppendBanList(idbuf, &name);
        BzrStringFree(&name);
    }

    void __cdecl BanButtonOnClickClient()
    {
        if (!g_BzrPtr_94557C || !g_BzrFn_GetSelected || !g_BzrFn_CommandHandler)
            return;

        void* root = *g_BzrPtr_94557C;
        if (!root)
            return;

        void* listObj = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(root) + 0x194);
        void* selected = g_BzrFn_GetSelected(listObj);
        if (!selected)
            return;

        if (g_BzrPtr_CurrentUser)
        {
            auto cur = g_BzrPtr_CurrentUser;
            if (*reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(selected) + 0x38) ==
                    *reinterpret_cast<uint32_t*>(cur + 8) &&
                *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(selected) + 0x3C) ==
                    *reinterpret_cast<uint32_t*>(cur + 0x0C))
                return;

            if (*reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(selected) + 0x30) ==
                *reinterpret_cast<uint32_t*>(cur))
                return;
        }

        uint16_t id = *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(selected) + 0x28);
        g_BzrFn_CommandHandler(id, "/ban");
        g_BzrFn_CommandHandler(id, "/kick");
    }

    void __cdecl BanButtonOnHoverHost(void* param)
    {
        if (g_BzrFn_LabelState && g_BanLabelHost)
            g_BzrFn_LabelState(g_BanLabelHost, param);
    }

    void __cdecl BanButtonOnHoverClient(void* param)
    {
        if (g_BzrFn_LabelState && g_BanLabelClient)
            g_BzrFn_LabelState(g_BanLabelClient, param);
    }

    void BanButtonCreateHost()
    {
        if (!g_BzrFn_ButtonCtor || !g_BzrFn_LabelCtor || !g_BzrFn_AddChild || !g_BanParentHost)
            return;

        void* parent = g_BanParentHost;

        void* buttonMem = ::operator new(0x1EC, std::nothrow);
        if (!buttonMem)
            return;
        std::memset(buttonMem, 0, 0x1EC);
        g_BanButtonHost = g_BzrFn_ButtonCtor(
            buttonMem,
            "Ban User",
            g_BanX - 48.0f,
            g_BanY + 96.0f,
            48.0f,
            48.0f,
            0x20,
            parent,
            0,
            0);

        if (g_BanButtonHost)
        {
            if (g_BzrFn_SetTextureOff) g_BzrFn_SetTextureOff(g_BanButtonHost, "MultiplayerModeButton_off.png");
            if (g_BzrFn_SetTextureOver) g_BzrFn_SetTextureOver(g_BanButtonHost, "MultiplayerModeButton_over.png");
            if (g_BzrFn_SetTextureOn) g_BzrFn_SetTextureOn(g_BanButtonHost, "MultiplayerModeButton_on.png");
            if (g_BzrFn_SetButtonLabel) g_BzrFn_SetButtonLabel(g_BanButtonHost, "B");
            if (g_BzrFn_SetOnClick) g_BzrFn_SetOnClick(g_BanButtonHost, reinterpret_cast<void*>(BanButtonOnClickHost));
            if (g_BzrFn_SetOnHover) g_BzrFn_SetOnHover(g_BanButtonHost, reinterpret_cast<void*>(BanButtonOnHoverHost));
            g_BzrFn_AddChild(parent, g_BanButtonHost, 0);
        }

        void* labelMem = ::operator new(0x930, std::nothrow);
        if (!labelMem)
            return;
        std::memset(labelMem, 0, 0x930);
        g_BanLabelHost = g_BzrFn_LabelCtor(
            labelMem,
            "Lobby",
            270.0f,
            980.0f,
            338.0f,
            43.0f,
            0x8020,
            parent,
            0,
            0);

        if (g_BanLabelHost)
        {
            if (g_BzrFn_SetTooltip) g_BzrFn_SetTooltip(g_BanLabelHost, "Ban highlighted player");
            if (g_BzrFn_LabelState) g_BzrFn_LabelState(g_BanLabelHost, nullptr);
            g_BzrFn_AddChild(parent, g_BanLabelHost, 0);
        }
    }

    void BanButtonCreateClient()
    {
        if (!g_BzrFn_ButtonCtor || !g_BzrFn_LabelCtor || !g_BzrFn_AddChild || !g_BanParentClient)
            return;

        void* parent = g_BanParentClient;

        void* buttonMem = ::operator new(0x1EC, std::nothrow);
        if (!buttonMem)
            return;
        std::memset(buttonMem, 0, 0x1EC);
        g_BanButtonClient = g_BzrFn_ButtonCtor(
            buttonMem,
            "Ban User",
            -33.0f,
            942.0f,
            48.0f,
            48.0f,
            0,
            parent,
            0,
            0);

        if (g_BanButtonClient)
        {
            if (g_BzrFn_SetTextureOff) g_BzrFn_SetTextureOff(g_BanButtonClient, "MultiplayerModeButton_off.png");
            if (g_BzrFn_SetTextureOver) g_BzrFn_SetTextureOver(g_BanButtonClient, "MultiplayerModeButton_over.png");
            if (g_BzrFn_SetTextureOn) g_BzrFn_SetTextureOn(g_BanButtonClient, "MultiplayerModeButton_on.png");
            if (g_BzrFn_SetButtonLabel) g_BzrFn_SetButtonLabel(g_BanButtonClient, "B");
            if (g_BzrFn_SetOnClick) g_BzrFn_SetOnClick(g_BanButtonClient, reinterpret_cast<void*>(BanButtonOnClickClient));
            if (g_BzrFn_SetOnHover) g_BzrFn_SetOnHover(g_BanButtonClient, reinterpret_cast<void*>(BanButtonOnHoverClient));
            g_BzrFn_AddChild(parent, g_BanButtonClient, 0);
        }

        void* labelMem = ::operator new(0x930, std::nothrow);
        if (!labelMem)
            return;
        std::memset(labelMem, 0, 0x930);
        g_BanLabelClient = g_BzrFn_LabelCtor(
            labelMem,
            "Lobby",
            270.0f,
            1000.0f,
            338.0f,
            43.0f,
            0x20,
            parent,
            0,
            0);

        if (g_BanLabelClient)
        {
            if (g_BzrFn_SetTooltip) g_BzrFn_SetTooltip(g_BanLabelClient, "Ban highlighted player");
            if (g_BzrFn_LabelState) g_BzrFn_LabelState(g_BanLabelClient, nullptr);
            g_BzrFn_AddChild(parent, g_BanLabelClient, 0);
        }
    }
}
