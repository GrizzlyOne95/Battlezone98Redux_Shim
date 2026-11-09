// mp_any_nation.cpp -- "Any Nation" multiplayer lobby toggle (Battlezone 1.5 parity).
//
//   ON  (default) = the full Redux vehicle pool, today's behaviour.
//   OFF           = the pool restricted to the 1.5 netveh.odf set (see
//                   MpFactionRestrict::SetAnyNationRestrict).
//
// Mixed lobbies are accepted as-is. Any Nation OFF only restricts players
// running OpenShim; stock clients still see the full pool. The lobby stays
// compatible either way: the setting travels in its own lobby-data key
// ("anyNation", "0" = OFF, "1" or absent = ON) and is never appended to the
// positional "gameSettings" string that FUN_0073C450 parses strictly.
//
// Evidence (GOG Redux 2.2.301; decomp under Battlezone_Source/BZ1/Redux/
// openshim_re_corpus, prologue bytes re-read from the shipped exe):
//   FUN_0073D020  republishes "gameSettings" through lobby vtable +0x20 when
//                 it differs from vtable +0x2C's current value (decomp :48-:67).
//                 __fastcall(netService). Post-hooked to publish anyNation.
//   FUN_00743F40  PopulateLobbyFromData, __thiscall(netService, info, arg2) `ret 8`,
//                 reads "gameSettings" with vtable +0x2C at decomp :222-:248.
//                 Post-hooked to read anyNation and apply it.
//   FUN_00796880  cUI_Multiplayer_Create screen ctor, __thiscall(this, arg) `ret 4`. Builds
//                 AnyNationButton at :306 with an empty label and the nullsub
//                 callback FUN_00795D70, then hides it (:313). Post-hooked to
//                 show it (host only) and label it.
//   0x00797ACA    the two `push 0x795D70` callbacks of that button, re-pointed
//                 at AnyNationClick. Same shape as the sniper toggle
//                 (FUN_0079C620 -> FUN_0079B880): flip, persist to multi.ini,
//                 relabel, republish through FUN_0073D020.
//   FUN_007C44A0  widget SetText(std::string by value), `ret 0x18`.
//   FUN_0056F900  net service -> lobby record; lobby id at record+0x10.
//
// Host only: the button is shown only for the lobby owner (record+0xB0) and the click
// handler re-checks it. Clients take the host's value from the lobby.

#include "mp_any_nation.h"
#include "mp_faction_restrict.h"
#include "bool_token.h"
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <string>

namespace BZROpenShim { namespace AnyNation {

namespace {

constexpr char kComponent[] = "anynation";

// Lobby-data key. "0" = Any Nation OFF; "1" or absent = ON.
constexpr char kKey[] = "anyNation";

// MSVC std::string as laid out in this build: char buf[16] | size | res.
struct RawStr
{
    char buf[16];
    uint32_t size;
    uint32_t res;
};

RawStr MakeRaw(const char* s)
{
    RawStr r = {};
    size_t n = std::strlen(s);
    if (n > 15) n = 15;
    std::memcpy(r.buf, s, n);
    r.size = static_cast<uint32_t>(n);
    r.res = 15;
    return r;
}

// The detours hand back whatever the original left in eax: the decompile shows
// void, but a caller may still read it.
using FnVoidSvc      = uintptr_t(__fastcall*)(void* svc, void* edx);
// 0x00743F40 ends in `ret 8` (two stack args, the first is the lobby info); 0x00796880 ends
// in `ret 4` (one stack arg). Both read from the shipped image 2026-11-09.
using FnReadDetour   = uintptr_t(__fastcall*)(void* svc, void* edx, void* info, void* arg2);
using FnCtor         = uintptr_t(__fastcall*)(void* self, void* edx, void* arg1);
using FnLobbyRecord  = void*(__fastcall*)(void* svc, void* edx);
using FnLobbyRead    = const char*(__fastcall*)(void* svc, void* edx, void* lobbyId, const RawStr* key);
using FnLobbyWrite   = uint32_t(__fastcall*)(void* svc, void* edx, void* lobbyId, const RawStr* key, const RawStr* value);
using FnSetText      = void(__fastcall*)(void* widget, void* edx, RawStr text);
using FnSetVisible   = void(__fastcall*)(void* widget, void* edx, int visible);

constexpr uint32_t kVtLobbyWrite    = 0x20;
constexpr uint32_t kVtLobbyRead     = 0x2C;
constexpr uint32_t kVtWidgetVisible = 0x24;
constexpr uint32_t kLobbyIdOffset   = 0x10;   // record+0x10 (FUN_0073D020:46)
constexpr uint32_t kScreenSvcOffset = 0x1BC;  // cUI_Multiplayer_Create+0x1BC (FUN_0079B880 disasm 0x79b8b8)
constexpr uint32_t kScreenAnyNationWidget = 0x1A0; // param_1[0x68] (FUN_00796880:308)
constexpr uint32_t kScreenSingleton = 0x0094555C;  // what the callback thunks load (0x795D70)

constexpr uint8_t kCallbackStock[10] = { 0x68, 0x70, 0x5D, 0x79, 0x00, 0x68, 0x70, 0x5D, 0x79, 0x00 };
constexpr uint8_t kPrologue[10] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF, 0x68 /* + imm32 */ };

std::atomic<bool> g_Installed{false};
std::atomic<bool> g_Local{true};       // host's own setting (persisted)
std::atomic<bool> g_Effective{true};   // what the list currently follows
std::atomic<int>  g_LastRead{-1};      // last value read from the lobby (-1 = none)
std::atomic<void*> g_HostScreen{nullptr}; // screen HostSync has already finished

uint32_t g_AddrRecord = 0, g_AddrSetText = 0, g_AddrPublish = 0;
uint32_t g_AddrRead = 0, g_AddrCtor = 0, g_AddrCallbacks = 0;

InlineDetour32 g_PublishDetour, g_ReadDetour, g_CtorDetour;
void* volatile g_PublishTramp = nullptr;
void* volatile g_ReadTramp = nullptr;
void* volatile g_CtorTramp = nullptr;

bool ReadShimBool(const char* name, bool defaultValue)
{
    char raw[64] = {};
    const DWORD len = GetEnvironmentVariableA(name, raw, sizeof(raw));
    if (len == 0 || len >= sizeof(raw))
        return defaultValue;
    bool value = defaultValue;
    return BZROpenShim::BoolToken::TryParse(raw, len, value) ? value : defaultValue;
}

std::string MultiIniPath()
{
    return (GetMainModuleDirectory() / "multi.ini").string();
}

bool LoadLocalSetting()
{
    return GetPrivateProfileIntA("multi", "anyNation", 1, MultiIniPath().c_str()) != 0;
}

void SaveLocalSetting(bool on)
{
    WritePrivateProfileStringA("multi", "anyNation", on ? "1" : "0", MultiIniPath().c_str());
}

// Lobby ownership: the lobby's owner id equals our own id. record+0xB0, CNetGameLobby::IsOwner
// (0x00742CF0) and Net::IsHost were each tried and read the same on host and guest here.
constexpr uint32_t kRecordOwnerFlag = 0xB0;
bool SafeIsHost(void* svc);

__declspec(noinline) void* SafeRecord(void* svc)
{
    __try { return reinterpret_cast<FnLobbyRecord>(g_AddrRecord)(svc, nullptr); }
    __except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
}

bool SafeIsHost(void* svc)
{
    if (!svc)
        return false;
    void* record = SafeRecord(svc);
    if (!record)
        return false;
    // Same two calls PopulateLobbyFromData makes (decomp :85 and :90):
    // vtable +0x68 GetLobbyOwner(out16*, lobbyId*) and vtable +0x38 GetMyID(out16*).
    uint32_t owner[8] = {}, me[8] = {};
    __try
    {
        void** vt = *reinterpret_cast<void***>(svc);
        reinterpret_cast<void(__fastcall*)(void*, void*, void*, void*)>(vt[0x68 / 4])(
            svc, nullptr, owner, static_cast<uint8_t*>(record) + kLobbyIdOffset);
        reinterpret_cast<void(__fastcall*)(void*, void*, void*)>(vt[0x38 / 4])(svc, nullptr, me);
    }
    __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
    const bool nonzero = owner[0] || owner[1] || owner[2] || owner[3];
    return nonzero && std::memcmp(owner, me, 16) == 0;
}

__declspec(noinline) bool SafeLobbyRead(void* svc, void* lobbyId, const RawStr* key, char* out, size_t outLen, bool* present)
{
    __try
    {
        void** vt = *reinterpret_cast<void***>(svc);
        const char* v = reinterpret_cast<FnLobbyRead>(vt[kVtLobbyRead / 4])(svc, nullptr, lobbyId, key);
        *present = v != nullptr;
        out[0] = 0;
        if (v)
        {
            strncpy_s(out, outLen, v, _TRUNCATE);
        }
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
}

__declspec(noinline) bool SafeLobbyWrite(void* svc, void* lobbyId, const RawStr* key, const RawStr* val)
{
    __try
    {
        void** vt = *reinterpret_cast<void***>(svc);
        reinterpret_cast<FnLobbyWrite>(vt[kVtLobbyWrite / 4])(svc, nullptr, lobbyId, key, val);
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
}

// A game lobby carries the positional "gameSettings" value; the lounge chat
// lobby ("~chat~pub~~default") does not. Only game lobbies are touched.
bool IsGameLobby(void* svc, void* lobbyId)
{
    const RawStr key = MakeRaw("gameSettings");
    char cur[8] = {};
    bool present = false;
    if (!SafeLobbyRead(svc, lobbyId, &key, cur, sizeof(cur), &present))
        return false;
    return present && cur[0] != 0;
}

__declspec(noinline) bool SafeWidgetCalls(void* widget, bool show, const char* label)
{
    __try
    {
        void** vt = *reinterpret_cast<void***>(widget);
        reinterpret_cast<FnSetText>(g_AddrSetText)(widget, nullptr, MakeRaw(label));
        reinterpret_cast<FnSetVisible>(vt[kVtWidgetVisible / 4])(widget, nullptr, show ? 1 : 0);
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
}

const char* LabelFor(bool on) { return on ? "Any Nation: On" : "Any Nation: Off"; }

void ApplyToList(bool on, const char* why)
{
    g_Effective.store(on);
    const bool wasRestricted = MpFactionRestrict::AnyNationRestrictActive();
    MpFactionRestrict::SetAnyNationRestrict(!on);
    LogShimA(LogLevel::Info, kComponent, "[ANYNATION] apply value=%u (%s) restrictWas=%u", on ? 1u : 0u, why,
             wasRestricted ? 1u : 0u);
    MpFactionRestrict::RebuildVehicleList(why);
}

// Host: publish anyNation next to gameSettings. OFF is always written; ON is
// only written to replace an earlier "0", so a lobby that never turned it OFF
// carries no new key at all (inert for stock peers).
void PublishFor(void* svc)
{
    if (!svc || !SafeIsHost(svc))
        return;
    void* record = SafeRecord(svc);
    if (!record)
        return;
    void* lobbyId = static_cast<uint8_t*>(record) + kLobbyIdOffset;
    if (!IsGameLobby(svc, lobbyId))
        return;
    const RawStr key = MakeRaw(kKey);
    char cur[16] = {};
    bool present = false;
    if (!SafeLobbyRead(svc, lobbyId, &key, cur, sizeof(cur), &present))
        return;
    if (present && cur[0] == 0)
        present = false; // empty value == no key
    const bool want = g_Local.load();
    const char* wantStr = want ? "1" : "0";
    if (present ? (std::strcmp(cur, wantStr) == 0) : want)
        return;
    const RawStr val = MakeRaw(wantStr);
    const bool ok = SafeLobbyWrite(svc, lobbyId, &key, &val);
    LogShimA(LogLevel::Info, kComponent, "[ANYNATION] publish value=%s (lobby had %s) %s", wantStr,
             present ? cur : "<absent>", ok ? "ok" : "FAILED (exception)");
}

void HostSync(void* svc);
void ReadAfter(void* svc, void* info);

uintptr_t __fastcall PublishDetour(void* svc, void* edx)
{
    const uintptr_t r = g_PublishTramp ? reinterpret_cast<FnVoidSvc>(g_PublishTramp)(svc, edx) : 0;
    PublishFor(svc);
    return r;
}

uintptr_t __fastcall ReadDetour(void* svc, void* edx, void* info, void* arg2)
{
    const uintptr_t r = g_ReadTramp ? reinterpret_cast<FnReadDetour>(g_ReadTramp)(svc, edx, info, arg2) : 0;
    ReadAfter(svc, info);
    return r;
}

// PopulateLobbyFromData's info must be the lobby we are in, not a browser entry.
bool IsCurrentLobby(void* svc, void* info)
{
    void* record = SafeRecord(svc);
    if (!record)
        return false;
    __try
    {
        return std::memcmp(static_cast<uint8_t*>(record) + kLobbyIdOffset,
                           static_cast<uint8_t*>(info) + kLobbyIdOffset, 16) == 0;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
}

// Staging-screen singleton fields, read under SEH (the screen may be gone).
void* SafeScreenField(void** outSvc, uint32_t widgetOffset, void** outWidget)
{
    __try
    {
        void* screen = *reinterpret_cast<void**>(kScreenSingleton);
        if (screen)
        {
            *outSvc = *reinterpret_cast<void**>(static_cast<uint8_t*>(screen) + kScreenSvcOffset);
            *outWidget = *reinterpret_cast<void**>(static_cast<uint8_t*>(screen) + widgetOffset);
        }
        return screen;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
}

void ReadAfter(void* svc, void* info)
{
    if (!svc || !info || !IsCurrentLobby(svc, info))
        return;
    if (!IsGameLobby(svc, static_cast<uint8_t*>(info) + kLobbyIdOffset))
        return;
    {
        static std::atomic<int> n{0};
        if (n.fetch_add(1) < 6)
            LogShimA(LogLevel::Info, kComponent, "[ANYNATION] lobby data seen: owner=%s", SafeIsHost(svc) ? "me" : "other");
    }
    if (SafeIsHost(svc))
    {
        HostSync(svc); // the host is authoritative for its own lobby
        return;
    }
    const RawStr key = MakeRaw(kKey);
    char cur[16] = {};
    bool present = false;
    if (!SafeLobbyRead(svc, static_cast<uint8_t*>(info) + kLobbyIdOffset, &key, cur, sizeof(cur), &present))
        return;
    if (present && cur[0] == 0)
        present = false; // an empty value is the same as no key
    const bool on = !(present && cur[0] == '0');
    const int asInt = on ? 1 : 0;
    if (g_LastRead.exchange(asInt) != asInt)
        LogShimA(LogLevel::Info, kComponent, "[ANYNATION] read value=%s (key %s)", on ? "1" : "0",
                 present ? "present" : "absent");
    if (on != g_Effective.load())
        ApplyToList(on, "lobby value changed");
}

// The staging screen is constructed BEFORE the lobby record exists (BZLogger:
// "Creating screen of type 15" precedes "OnLobbyCreated"), so lobby ownership
// cannot be decided here. The host side is finished from the first
// PopulateLobbyFromData that sees an owned lobby (HostSync).
uintptr_t __fastcall CtorDetour(void* self, void* edx, void* arg1)
{
    const uintptr_t r = g_CtorTramp ? reinterpret_cast<FnCtor>(g_CtorTramp)(self, edx, arg1) : 0;
    if (!self)
        return r;
    g_LastRead.store(-1);
    g_HostScreen.store(nullptr);
    LogShimA(LogLevel::Info, kComponent, "[ANYNATION] lobby screen built (screen=%p); owner decided at first lobby data", self);
    ApplyToList(true, "lobby screen built (ON until the lobby says otherwise)");
    return r;
}

// Host: show and label the button, apply the saved value to this machine's
// list and publish it, once per screen.
void HostSync(void* svc)
{
    void* screenSvc = nullptr;
    void* widget = nullptr;
    void* screen = SafeScreenField(&screenSvc, kScreenAnyNationWidget, &widget);
    if (!screen || g_HostScreen.load() == screen || screenSvc != svc)
        return;
    g_HostScreen.store(screen);
    const bool local = LoadLocalSetting();
    g_Local.store(local);
    const bool ok = widget && SafeWidgetCalls(widget, true, LabelFor(local));
    LogShimA(LogLevel::Info, kComponent, "[ANYNATION] host lobby ready: value=%u button %s", local ? 1u : 0u,
             ok ? "shown" : "NOT shown");
    ApplyToList(local, "host lobby ready");
    PublishFor(svc);
}

// cdecl void(): the engine calls the widget callback with no arguments.
void __cdecl AnyNationClick()
{
    void* svc = nullptr;
    void* widget = nullptr;
    void* screen = SafeScreenField(&svc, kScreenAnyNationWidget, &widget);
    if (!screen || !SafeIsHost(svc))
        return;
    const bool on = !g_Local.load();
    g_Local.store(on);
    SaveLocalSetting(on);
    if (widget)
        SafeWidgetCalls(widget, true, LabelFor(on));
    LogShimA(LogLevel::Info, kComponent, "[ANYNATION] host click: value=%u", on ? 1u : 0u);
    ApplyToList(on, "host toggle");
    if (g_AddrPublish)
    {
        // Through the detour: runs the stock republish, then anyNation.
        __try { reinterpret_cast<FnVoidSvc>(g_AddrPublish)(svc, nullptr); }
        __except (EXCEPTION_EXECUTE_HANDLER) {}
    }
}

} // namespace

bool IsEnabled()
{
    return ReadShimBool("OPENSHIM_ANY_NATION_TOGGLE", true);
}

void InstallAnyNationToggleIfPossible()
{
    if (g_Installed.load())
        return;
    if (!IsEnabled())
    {
        LogShimA(LogLevel::Info, kComponent, "[ANYNATION] disabled ([Fixes] AnyNationToggle = 0)");
        return;
    }
    if (!MpFactionRestrict::VehicleListHookReady())
    {
        LogShimA(LogLevel::Warn, kComponent, "[ANYNATION] vehicle-list hook not installed; Any Nation toggle stands down");
        return;
    }

    const HookEngine::EngineRow rows[] = {
        { "AnyNationLobbyRecord", &g_AddrRecord },
        { "AnyNationWidgetSetText", &g_AddrSetText },
        { "AnyNationLobbyPublish", &g_AddrPublish },
        { "AnyNationLobbyRead", &g_AddrRead },
        { "AnyNationScreenCtor", &g_AddrCtor },
        { "AnyNationButtonCallbacks", &g_AddrCallbacks },
    };
    if (!HookEngine::BindEngineRows("AnyNation", rows))
        return;

    // The callback site must still be the two nullsub pushes.
    if (!ExpectedBytesMatchAt(g_AddrCallbacks, kCallbackStock, sizeof(kCallbackStock)))
    {
        LogShimA(LogLevel::Warn, kComponent, "[ANYNATION] button callback bytes not stock at 0x%08X; standing down",
                 g_AddrCallbacks);
        return;
    }

    if (!InstallInlineDetour32(g_PublishDetour, g_AddrPublish, reinterpret_cast<void*>(&PublishDetour), 5,
                               kPrologue, 5, &g_PublishTramp) ||
        !InstallInlineDetour32(g_ReadDetour, g_AddrRead, reinterpret_cast<void*>(&ReadDetour), 5,
                               kPrologue, 5, &g_ReadTramp) ||
        !InstallInlineDetour32(g_CtorDetour, g_AddrCtor, reinterpret_cast<void*>(&CtorDetour), 5,
                               kPrologue, 5, &g_CtorTramp))
    {
        LogShimA(LogLevel::Warn, kComponent, "[ANYNATION] a detour failed to install; toggle partly installed, publish/read may be inert");
        return;
    }

    uint8_t patched[10] = {};
    const uint32_t fn = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&AnyNationClick));
    patched[0] = 0x68; std::memcpy(patched + 1, &fn, 4);
    patched[5] = 0x68; std::memcpy(patched + 6, &fn, 4);
    if (!Hooks::WritePatchBytes(g_AddrCallbacks, patched, sizeof(patched)))
    {
        LogShimA(LogLevel::Warn, kComponent, "[ANYNATION] could not re-point the button callbacks");
        return;
    }

    g_Local.store(LoadLocalSetting());
    g_Installed.store(true);
    LogShimA(LogLevel::Info, kComponent,
             "[ANYNATION] installed: publish=0x%08X read=0x%08X ctor=0x%08X callbacks=0x%08X local=%u",
             g_AddrPublish, g_AddrRead, g_AddrCtor, g_AddrCallbacks, g_Local.load() ? 1u : 0u);
}

}} // namespace BZROpenShim::AnyNation
