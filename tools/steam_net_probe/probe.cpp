// Steam networking availability probe (32-bit). Loads the SHIPPED steam_api.dll
// (copied beside the exe, appid via steam_appid.txt), then asks the Steam client
// for the newer networking interfaces through the legacy ISteamClient generic
// accessor. Touches no game files. See docs/STEAM_NETWORKING_FEASIBILITY_20261028.md.
#include <windows.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <steam/steamnetworkingtypes.h>
#include <steam/isteamnetworkingsockets.h>
#include <steam/isteamnetworkingutils.h>
#include <steam/isteamnetworkingmessages.h>

typedef int (__cdecl *PFN_Init)();
typedef void (__cdecl *PFN_Void)();
typedef int (__cdecl *PFN_Handle)();
typedef void* (__cdecl *PFN_Client)();
typedef void* (__cdecl *PFN_Generic)(void* client, int hUser, int hPipe, const char* ver);

template <class T> static T Sym(HMODULE m, const char* n) { return (T)GetProcAddress(m, n); }

static void* g_client; static int g_user, g_pipe; static PFN_Generic g_generic;

static void* Probe(const char* name) {
    void* p = g_generic(g_client, g_user, g_pipe, name);
    printf("  %-36s -> %s\n", name, p ? "SERVED" : "null");
    return p;
}

int main() {
    HMODULE dll = LoadLibraryA("steam_api.dll");
    if (!dll) { printf("steam_api.dll load failed (%lu)\n", GetLastError()); return 2; }
    auto init = Sym<PFN_Init>(dll, "SteamAPI_Init");
    auto run = Sym<PFN_Void>(dll, "SteamAPI_RunCallbacks");
    auto shut = Sym<PFN_Void>(dll, "SteamAPI_Shutdown");
    auto getUser = Sym<PFN_Handle>(dll, "SteamAPI_GetHSteamUser");
    auto getPipe = Sym<PFN_Handle>(dll, "SteamAPI_GetHSteamPipe");
    auto client = Sym<PFN_Client>(dll, "SteamClient");
    g_generic = Sym<PFN_Generic>(dll, "SteamAPI_ISteamClient_GetISteamGenericInterface");
    if (!init || !run || !getUser || !getPipe || !client || !g_generic) { printf("missing exports\n"); return 2; }
    int ok = init() & 0xFF;
    printf("SteamAPI_Init: %d\n", ok);
    if (!ok) return 3;
    g_client = client(); g_user = getUser(); g_pipe = getPipe();
    printf("client=%p user=%d pipe=%d\n", g_client, g_user, g_pipe);

    printf("Interface probe (generic accessor):\n");
    const char* socks[] = {"SteamNetworkingSockets006","SteamNetworkingSockets008","SteamNetworkingSockets009",
        "SteamNetworkingSockets010","SteamNetworkingSockets011","SteamNetworkingSockets012","SteamNetworkingSockets013",
        STEAMNETWORKINGSOCKETS_INTERFACE_VERSION};
    const char* utils[] = {"SteamNetworkingUtils001","SteamNetworkingUtils002","SteamNetworkingUtils003","SteamNetworkingUtils004",
        STEAMNETWORKINGUTILS_INTERFACE_VERSION};
    const char* msgs[] = {"SteamNetworkingMessages001","SteamNetworkingMessages002", STEAMNETWORKINGMESSAGES_INTERFACE_VERSION};
    ISteamNetworkingSockets* sockets = nullptr; ISteamNetworkingUtils* u = nullptr; ISteamNetworkingMessages* m = nullptr;
    printf("header versions: %s %s %s\n", STEAMNETWORKINGSOCKETS_INTERFACE_VERSION, STEAMNETWORKINGUTILS_INTERFACE_VERSION, STEAMNETWORKINGMESSAGES_INTERFACE_VERSION);
    for (auto n : socks) { void* p = Probe(n); if (p && !strcmp(n, STEAMNETWORKINGSOCKETS_INTERFACE_VERSION)) sockets = (ISteamNetworkingSockets*)p; }
    for (auto n : utils) { void* p = Probe(n); if (p && !strcmp(n, STEAMNETWORKINGUTILS_INTERFACE_VERSION)) u = (ISteamNetworkingUtils*)p; }
    for (auto n : msgs) { void* p = Probe(n); if (p && !strcmp(n, STEAMNETWORKINGMESSAGES_INTERFACE_VERSION)) m = (ISteamNetworkingMessages*)p; }

    if (u) {
        u->InitRelayNetworkAccess();
        printf("InitRelayNetworkAccess called\n");
    }
    SteamNetworkingIdentity id{}; bool haveId = false;
    if (sockets) { haveId = sockets->GetIdentity(&id); if (haveId) printf("identity: type=%d steamid64=%llu\n", (int)id.m_eType, (unsigned long long)id.GetSteamID64()); }
    HSteamListenSocket listen = k_HSteamListenSocket_Invalid;
    if (sockets) { listen = sockets->CreateListenSocketP2P(0, 0, nullptr); printf("CreateListenSocketP2P(vport0) -> %u\n", (unsigned)listen); }

    DWORD t0 = GetTickCount(); int last = -1; bool pingPrinted = false;
    while (GetTickCount() - t0 < 25000) {
        run();
        if (u) {
            SteamRelayNetworkStatus_t st{};
            int a = u->GetRelayNetworkStatus(&st);
            int key = (int)st.m_eAvail * 100 + (int)st.m_eAvailNetworkConfig * 10 + (int)st.m_eAvailAnyRelay;
            if (key != last) {
                last = key;
                printf("[%5lums] relay: overall=%d netcfg=%d anyrelay=%d pingmeasurementInProgress=%d msg='%s'\n", GetTickCount() - t0,
                       a, (int)st.m_eAvailNetworkConfig, (int)st.m_eAvailAnyRelay, (int)st.m_bPingMeasurementInProgress, st.m_debugMsg);
            }
            if (!pingPrinted) {
                SteamNetworkPingLocation_t loc{};
                float age = u->GetLocalPingLocation(loc);
                if (age >= 0) {
                    char buf[k_cchMaxSteamNetworkingPingLocationString] = {};
                    u->ConvertPingLocationToString(loc, buf, sizeof(buf));
                    printf("[%5lums] ping location (age %.1fs): %s\n", GetTickCount() - t0, age, buf);
                    pingPrinted = true;
                }
            }
        }
        if (sockets) {
            SteamNetAuthenticationStatus_t as{}; sockets->GetAuthenticationStatus(&as);
            static int la = -1; if ((int)as.m_eAvail != la) { la = (int)as.m_eAvail; printf("auth status: %d '%s'\n", la, as.m_debugMsg); }
        }
        Sleep(200);
    }
    printf("messages iface: %s\n", m ? "present" : "absent");
    if (sockets && listen != k_HSteamListenSocket_Invalid) sockets->CloseListenSocket(listen);
    shut();
    printf("done\n");
    return 0;
}
