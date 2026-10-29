#define _CRT_RAND_S
#include "lan_no_auth.h"
#include "lan_no_auth_policy.h"
#include "bzr_options_ui.h"
#include "bzr_hooks.h"
#include "hook_engine.h"
#include "net_optimizer.h"
#include "patcher.h"
#include <windows.h>
#include <atomic>
#include <cstdlib>
#include <cstring>
#include <mutex>

namespace BZROpenShim::Hooks
{
    bool RedirectCallTarget(uintptr_t,uintptr_t,uintptr_t);
}
namespace BZROpenShim::LanNoAuth
{
namespace
{
    std::atomic<bool> requested{false}, selected{false}, installed{false};
    std::mutex selectionLock;
    std::string selectedEndpoint;
    uint64_t localValue = 0; // generated once before installed is published
    InlineDetour32 readyDetour;
    using ReadyFn = int(__cdecl*)();
    using EmptyFn = bool(__thiscall*)(void*);
    using LobbyFn = void*(__cdecl*)();
    struct NativeId { uint32_t kind=0, opaque=0; uint64_t value=0; };
    using LocalIdFn = NativeId*(__thiscall*)(void*,NativeId*);
    ReadyFn originalReady=nullptr, authOk=nullptr;
    EmptyFn originalEmpty=nullptr;
    LobbyFn getLobby=nullptr;
    LocalIdFn getLocal=nullptr;
    using ConnectFn = void(__thiscall*)(void*,void*);
    ConnectFn connectClient=nullptr;
    uintptr_t holderAddress=0,relayAddress=0;
    uint32_t lobbyVtable=0;
    std::atomic<unsigned> generation{0};

    bool EffectiveSelection()
    {
        if (!selected.load() || !installed.load()) return false;
        std::string endpoint, canonical; bool official = true;
        if (!GetBzrNetEffectiveEndpoint(endpoint,official) || official ||
            !PrivateEndpoint(endpoint,canonical)) return false;
        std::lock_guard<std::mutex> lock(selectionLock);
        return canonical == selectedEndpoint;
    }
    bool ReadNativeReady()
    {
        __try
        {
            if (!authOk || !authOk() || !getLobby || !getLocal) return false;
            void* lobby = getLobby(); if (!lobby) return false;
            NativeId id{}; getLocal(lobby,&id);
            return NativeIdentityMatches(id.kind,id.value,localValue);
        }
        __except(EXCEPTION_EXECUTE_HANDLER) { return false; }
    }
    int __cdecl LocalReady()
    {
        // Online provider flags are never altered. Offline readiness requires
        // the actual local admission reply and the exact locally generated ID.
        return Requested() ? (Ready() ? 1 : 0) : originalReady();
    }
    bool __fastcall LocalCredentialEmpty(void* text,void*)
    {
        if (Requested()) return !Available();
        return originalEmpty(text);
    }
    uint32_t CallTarget(uint32_t site)
    {
        uint8_t bytes[5]{}; int32_t relative = 0;
        if (!HookEngine::ReadMemory(site,bytes,sizeof(bytes)) || bytes[0] != 0xE8) return 0;
        std::memcpy(&relative,bytes+1,sizeof(relative));
        return site+5+uint32_t(relative);
    }
}
bool Enabled()
{
    bool enabled = false;
    TryGetUserConfigBool("Network","NoAuthLan",enabled);
    return enabled;
}
bool Requested() { return requested.load(); }
bool Available() { return selected.load() && installed.load(); }
void SelectEndpoint(const char* endpoint, bool lanSelection)
{
    const bool want = Enabled() && lanSelection;
    std::string canonical;
    char redirect[256]{};
    const bool valid = want && endpoint && PrivateEndpoint(endpoint,canonical) &&
        !GetMatchmakingRedirectTarget(redirect,sizeof(redirect));
    selected = false;
    { std::lock_guard<std::mutex> lock(selectionLock); selectedEndpoint=valid ? canonical : ""; }
    requested=want; selected=valid;
    generation.fetch_add(1);
    if (want) Log(L"[LAN-NOAUTH] selection %hs; platform credentials unchanged\n",valid ? canonical.c_str() : "blocked: private numeric LAN address required, with no test redirect");
}
bool Ready() { return EffectiveSelection() && ReadNativeReady(); }
uintptr_t PlatformReadyCode(uintptr_t site)
{
    return originalReady ? reinterpret_cast<uintptr_t>(originalReady) : site;
}
void PumpMainThread()
{
    // The provider normally supplies the first credential callback. Explicit
    // LAN has no provider callback, so start the same native asynchronous
    // connection once; its stock reconnect timer owns subsequent retries.
    static void* started=nullptr;
    static unsigned lastGeneration=0;
    static bool routeSaved=false;
    static uint32_t previousRoute=0;
    __try
    {
        const bool active=Available() && Requested();
        if (relayAddress)
        {
            auto& relay=*reinterpret_cast<volatile uint32_t*>(relayAddress);
            if (active) { if (!routeSaved) {previousRoute=relay;routeSaved=true;} relay=0; }
            else if (routeSaved) {relay=previousRoute;routeSaved=false;}
        }
        if (!active) {started=nullptr;return;}
        const auto current=generation.load();
        if (lastGeneration!=current) {started=nullptr;lastGeneration=current;}
        void* holder=*reinterpret_cast<void**>(holderAddress);
        if (!holder) return;
        void* client=*reinterpret_cast<void**>(holder);
        void* lobby=getLobby();
        if (!client || !lobby || *reinterpret_cast<uint32_t*>(lobby)!=lobbyVtable ||
            *reinterpret_cast<void**>(static_cast<uint8_t*>(lobby)+0xC8)!=client ||
            *reinterpret_cast<void**>(static_cast<uint8_t*>(client)+0xC38)!=lobby ||
            *reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(client)+4)!=0 || started==client) return;
        started=client;
        uint32_t error[2]{};
        connectClient(client,error);
        Log(L"[LAN-NOAUTH] starting native LAN connection without a platform credential callback\n");
    }
    __except(EXCEPTION_EXECUTE_HANDLER) { /* unavailable native state fails closed */ }
}
bool Identity(std::string& id,std::string& name)
{
    if (!Requested() || !EffectiveSelection()) return false;
    id="B"+std::to_string(localValue);
    if (!TryGetUserConfigString("Network","Nickname",name) || name.empty()) name="LAN Player";
    name=TrimAsciiCopy(name);
    if (name.empty() || name.size()>127) name="LAN Player";
    for (auto& ch : name) if (static_cast<unsigned char>(ch)<32 || ch==127) ch=' ';
    return true;
}
void InstallIfPossible(bool authorizationHookReady)
{
    if (installed.load() || !Enabled() || !authorizationHookReady) return;
    uint32_t nameSite=0,ticketSite=0,readySite=0,emptySite=0,authSite=0,lobbySite=0,localSite=0;
    uint32_t connectSite=0,stateSite=0,relaySite=0;
    const HookEngine::EngineRow rows[] = {
        {"LanNoAuthNameEmptyCall",&nameSite},{"LanNoAuthTicketEmptyCall",&ticketSite},
        {"PlatformReady",&readySite},{"LanNoAuthStringEmpty",&emptySite},
        {"PlatformBzrNetAuthOk",&authSite},{"BzrNetGetLobby",&lobbySite},
        {"LanNoAuthGetLocalId",&localSite},
        {"LanNoAuthConnect",&connectSite},{"BzrNetClientState",&stateSite},
        {"BzrNetLobbyVtable",&lobbyVtable},{"BzrNetForceRelayRead",&relaySite},
    };
    if (!HookEngine::BindEngineRows("LAN local identity",rows) ||
        CallTarget(nameSite)!=emptySite || CallTarget(ticketSite)!=emptySite) return;
    unsigned random[2]{};
    if (rand_s(&random[0]) || rand_s(&random[1])) return;
    localValue=(uint64_t(random[0])<<32)|random[1]; if (!localValue) return;
    originalEmpty=reinterpret_cast<EmptyFn>(emptySite);
    std::memcpy(&holderAddress,reinterpret_cast<void*>(authSite+5),sizeof(uint32_t));
    std::memcpy(&relayAddress,reinterpret_cast<void*>(relaySite+2),sizeof(uint32_t));
    connectClient=reinterpret_cast<ConnectFn>(connectSite);
    authOk=reinterpret_cast<ReadyFn>(authSite); getLobby=reinterpret_cast<LobbyFn>(lobbySite);
    getLocal=reinterpret_cast<LocalIdFn>(localSite);
    uint8_t original[10]{};
    if (!HookEngine::ReadMemory(readySite,original,sizeof(original))) return;
    if (!InstallInlineDetour32(readyDetour,readySite,reinterpret_cast<void*>(&LocalReady),
            sizeof(original),original,sizeof(original),reinterpret_cast<void* volatile*>(&originalReady))) return;
    // A partial installation stays fail-closed for requested LAN mode: neither
    // readiness nor credential-empty hooks can admit a partial local identity.
    if (!Hooks::RedirectCallTarget(nameSite,emptySite,reinterpret_cast<uintptr_t>(&LocalCredentialEmpty)) ||
        !Hooks::RedirectCallTarget(ticketSite,emptySite,reinterpret_cast<uintptr_t>(&LocalCredentialEmpty)))
    { Log(L"[LAN-NOAUTH] local identity installation incomplete; LAN unavailable\n"); return; }
    installed=true;
    Log(L"[LAN-NOAUTH] local B identity and admission readiness installed; no platform sign-in, helper or fake platform IDs\n");
}
}
