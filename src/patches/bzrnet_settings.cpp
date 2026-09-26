// bzrnet_settings.cpp
// BZR Open Shim - BZRNet route preference, UDP port and nickname, split out
// of bzr_hooks.cpp. Configured from there and used by the lobby UI; shared
// helpers come from bzr_hooks_internal.h.
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "net_optimizer.h"
#include "patcher.h"
#include "shim_log.h"

#include <Windows.h>

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>

namespace BZROpenShim
{
    namespace Hooks
    {
        // --- BZRNet route preference and UDP port ------------------------------
        // Redux has no LAN browser, offline lobby, or direct-IP join: peers meet
        // in a BZRNet lobby over an authenticated WebSocket, the service hands
        // each peer the others' LAN and WAN UDP endpoints, and only then do the
        // peers choose a gameplay path themselves (LAN UDP -> direct WAN UDP ->
        // relay). What IS genuinely user-controllable is which path they prefer
        // and which local UDP port they bind. Stock exposes both only as
        // command-line switches, so these two settings persist them instead.
        //
        // This changes route preference, NOT session discovery. Neither setting
        // creates a LAN or direct-IP mode; see
        // reverse_engineering/redux_tcpip_lan_multiplayer_investigation_20260713.md.
        //
        // Both globals were confirmed against the shipped GOG image (sha256
        // 8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413,
        // byte-identical to the decompile corpus) from the instruction encodings
        // that reference them, not from the advisory PDB. Each has exactly four
        // .text references and no others.

        // dword. /iprelay writes 1 at 0x007D5CB9, /ipdirect writes 0 at
        // 0x007D5CE1. Read at 0x0075F09F (the per-peer connect decision in
        // FUN_0075EEA0) and 0x0075DDC6, both as `cmp dword ptr [addr], 0` -- so
        // it is consulted per connection attempt and may be changed live.
        constexpr uintptr_t kBzrNetForceRelayFlagAddr = 0x00946708;
        // NB: the guard site is the INSTRUCTION address, which starts two bytes
        // before the disp32 operand that names the global (`83 3D` opcode +
        // modrm). Anchoring on the operand instead silently fails the guard.
        constexpr uintptr_t kBzrNetForceRelayReadSiteAddr = 0x0075F09D;
        constexpr uint8_t kBzrNetForceRelayReadSiteBytes[] =
            { 0x83, 0x3D, 0x08, 0x67, 0x94, 0x00, 0x00 }; // cmp dword [946708],0

        // WORD, not dword: /bzrnetport= stores it with `mov word ptr` at
        // 0x007D5DB9. FUN_006BE750 reads it as the REQUESTED port at 0x006BE7B8
        // and then overwrites it at 0x006BE7FF with the port Winsock actually
        // bound. So it must be written before the socket opens -- and after the
        // socket opens it reads back as the true bound port, which is what the
        // lobby readout reports.
        constexpr uintptr_t kBzrNetUdpPortAddr = 0x00945704;
        constexpr uintptr_t kBzrNetUdpPortReadSiteAddr = 0x006BE7B5; // instr, not operand
        constexpr uint8_t kBzrNetUdpPortReadSiteBytes[] =
            { 0x0F, 0xB7, 0x15, 0x04, 0x57, 0x94, 0x00 }; // movzx edx,word [945704]

        // char[0x80] multiplayer name override, the /nickname= destination
        // (strncpy at 0x007D5947, terminator guard written at 0x007D5974).
        // FUN_006C6E60 consumes it when it builds the BZRNet identity message:
        // 0x006C7D87 tests byte 0 and falls back to the platform "realname"
        // when it is NUL, otherwise 0x006C7DA4 passes the buffer to a
        // std::string ctor. Because it is read at identity time rather than
        // latched at startup, an edit only reaches the service on the next
        // connect -- see the note on the lobby entry.
        constexpr uintptr_t kBzrNetNicknameAddr = 0x009453E0;
        constexpr uintptr_t kBzrNetNicknameReadSiteAddr = 0x006C7D84; // instr, not operand
        constexpr uint8_t kBzrNetNicknameReadSiteBytes[] =
            { 0x0F, 0xBE, 0x91, 0xE0, 0x53, 0x94, 0x00 }; // movsx edx,byte [ecx+9453E0]

        enum class BzrNetRoutePreference
        {
            Stock,   // leave the engine's own value alone
            Direct,  // /ipdirect  -- try LAN, then direct WAN, then relay
            Relay,   // /iprelay   -- skip both direct paths
        };

        static bool g_BzrNetConfigInitialized = false;
        static bool g_BzrNetGlobalsVerified = false;
        static bool g_BzrNetGlobalsChecked = false;
        static BzrNetRoutePreference g_BzrNetRoutePreference = BzrNetRoutePreference::Stock;
        static int g_BzrNetConfiguredUdpPort = -1; // <0 leaves the stock ephemeral bind

        // Guard the writes on the two read sites still carrying the exact
        // instruction encodings that name these addresses. A build whose layout
        // moved fails this and the feature stands down rather than writing into
        // whatever now lives at the old address.
        static bool VerifyBzrNetGlobals()
        {
            if (g_BzrNetGlobalsChecked)
                return g_BzrNetGlobalsVerified;
            g_BzrNetGlobalsChecked = true;

            const bool relayOk = ExpectedBytesMatchAt(
                kBzrNetForceRelayReadSiteAddr,
                kBzrNetForceRelayReadSiteBytes,
                sizeof(kBzrNetForceRelayReadSiteBytes));
            const bool portOk = ExpectedBytesMatchAt(
                kBzrNetUdpPortReadSiteAddr,
                kBzrNetUdpPortReadSiteBytes,
                sizeof(kBzrNetUdpPortReadSiteBytes));
            const bool nicknameOk = ExpectedBytesMatchAt(
                kBzrNetNicknameReadSiteAddr,
                kBzrNetNicknameReadSiteBytes,
                sizeof(kBzrNetNicknameReadSiteBytes));

            g_BzrNetGlobalsVerified = relayOk && portOk && nicknameOk;
            if (!g_BzrNetGlobalsVerified)
            {
                Log(L"[BZRNET] Globals failed byte guard (relay=%hs port=%hs nickname=%hs); "
                    L"settings stand down on this build\n",
                    relayOk ? "ok" : "mismatch",
                    portOk ? "ok" : "mismatch",
                    nicknameOk ? "ok" : "mismatch");
            }
            return g_BzrNetGlobalsVerified;
        }

        // Both sides of the nickname buffer, in functions free of unwindable
        // objects so they can use __try (C2712).
        bool ReadBzrNetNickname(char* out, size_t outSize)
        {
            if (!out || outSize == 0)
                return false;
            out[0] = '\0';
            if (!VerifyBzrNetGlobals())
                return false;
            __try
            {
                const char* const buffer = reinterpret_cast<const char*>(kBzrNetNicknameAddr);
                size_t i = 0;
                for (; i + 1 < outSize && i < kBzrNetNicknameCapacity && buffer[i] != '\0'; ++i)
                    out[i] = buffer[i];
                out[i] = '\0';
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                out[0] = '\0';
            }
            return false;
        }

        static bool WriteBzrNetNickname(const char* value)
        {
            if (!VerifyBzrNetGlobals())
                return false;
            __try
            {
                char* const buffer = reinterpret_cast<char*>(kBzrNetNicknameAddr);
                size_t i = 0;
                if (value)
                {
                    for (; i + 1 < kBzrNetNicknameCapacity && value[i] != '\0'; ++i)
                        buffer[i] = value[i];
                }
                // Clear the tail so a shorter name cannot leave the previous
                // one's suffix behind, and keep the engine's own guard byte NUL.
                for (; i < kBzrNetNicknameCapacity; ++i)
                    buffer[i] = '\0';
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[BZRNET] Failed to write nickname buffer\n");
            }
            return false;
        }

        // The service receives the nickname in Authorization. Recycling the
        // control connection lets Redux's qualified stock reconnect path build
        // and send that message; no private BZRNet send ABI is called here.
        constexpr uintptr_t kBzrNetLobbyVftable = 0x0089ADDC;
        constexpr uintptr_t kBzrNetGetLobbyAddr = 0x00764760;
        constexpr size_t kBzrNetLobbyClientOffset = 0xC8;
        constexpr size_t kBzrNetNativeClientBackPointerOffset = 0xC38;

        // `mov eax,[0x00945470]; ret` -- the global the lobby is published to on
        // construction and zeroed on teardown. Guarded on the instruction.
        static void* TryGetStockBzrNetLobby()
        {
            static constexpr uint8_t kExpectedBytes[] =
            {
                0x55, 0x8B, 0xEC, 0xA1, 0x70, 0x54, 0x94, 0x00, 0x5D, 0xC3
            };
            if (!ExpectedBytesMatchAt(
                    kBzrNetGetLobbyAddr, kExpectedBytes, sizeof(kExpectedBytes)))
                return nullptr;
            return reinterpret_cast<void* (__cdecl*)()>(kBzrNetGetLobbyAddr)();
        }

        // Experimental and default off until a two-client observer test proves
        // that the service publishes the new identity after stock reconnects.
        // In-match (netId != 0) never recycles the control connection.
        static bool ShouldReauthOnNicknameChange()
        {
            if (EnvFlagEnabled("OPENSHIM_DISABLE_BZRNET_REAUTH"))
                return false;
            bool enabled = false;
            if (TryGetUserConfigBool(
                    kUserConfigNetworkSection, "ReauthOnNicknameChange", enabled))
                return enabled;
            return false;
        }

        static bool ValidateBzrNetLobbyState(void* lobby)
        {
            if (!lobby)
                return false;
            __try
            {
                if (*reinterpret_cast<uintptr_t*>(lobby) != kBzrNetLobbyVftable)
                    return false;
                void* const client = *reinterpret_cast<void**>(
                    static_cast<uint8_t*>(lobby) + kBzrNetLobbyClientOffset);
                if (!client)
                    return false;
                // The native client owns a back-pointer to the lobby. Requiring
                // the pair to agree prevents calls through stale lobby memory.
                return *reinterpret_cast<void**>(
                    static_cast<uint8_t*>(client) + kBzrNetNativeClientBackPointerOffset) == lobby;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
            return false;
        }

        static bool IsValidBzrNetNickname(const std::string& value)
        {
            if (value.empty() || value.size() >= kBzrNetNicknameCapacity)
                return false;
            for (const unsigned char ch : value)
            {
                // Preserve printable UTF-8 bytes while rejecting ASCII control
                // characters that could corrupt chat/config presentation.
                if (ch < 0x20 || ch == 0x7F)
                    return false;
            }
            return true;
        }

        const char* BzrNetNicknameResultName(BzrNetNicknameResult result)
        {
            switch (result)
            {
            case BzrNetNicknameResult::NativeSendCompleted: return "native-send-completed";
            case BzrNetNicknameResult::StoredForNextConnection: return "stored-next-connect";
            case BzrNetNicknameResult::InvalidNickname: return "invalid";
            case BzrNetNicknameResult::UnsupportedBuild: return "unsupported-build";
            case BzrNetNicknameResult::NativeStateInvalid: return "native-state-invalid";
            case BzrNetNicknameResult::PersistenceFailed: return "persistence-failed";
            case BzrNetNicknameResult::LiveSendUnavailable: return "live-send-unavailable";
            case BzrNetNicknameResult::ReauthQueued: return "reauth-queued";
            default: return "unknown";
            }
        }

        bool IsAcceptedBzrNetNicknameResult(BzrNetNicknameResult result)
        {
            return result == BzrNetNicknameResult::NativeSendCompleted ||
                   result == BzrNetNicknameResult::StoredForNextConnection ||
                   result == BzrNetNicknameResult::UnsupportedBuild ||
                   result == BzrNetNicknameResult::NativeStateInvalid ||
                   result == BzrNetNicknameResult::LiveSendUnavailable ||
                   result == BzrNetNicknameResult::ReauthQueued;
        }

        static const char* CurrentNicknameSessionState(void* lobby, bool lobbyValid)
        {
            if (lobby)
                return lobbyValid ? "bzrnet-connected" : "bzrnet-state-invalid";
            return ReadLocalPlayerNetIdValue() != 0 ? "match-connected" : "pre-connect";
        }

        static std::string CurrentNicknameStableIdentity()
        {
            if (g_IsSteamExe)
            {
                uint64_t steam64 = 0;
                if (TryReadSteam64Value(steam64))
                    return "S" + std::to_string(steam64);
                return "steam-unavailable";
            }
            return "gog-unavailable";
        }

        BzrNetNicknameResult ApplyBzrNetNicknameAuthoritative(
            const char* requestedValue, const char* source)
        {
            const std::string nickname = TrimAsciiCopy(requestedValue ? requestedValue : "");
            if (!IsValidBzrNetNickname(nickname))
            {
                Log(L"[BZRNET] Nickname rejected (source=%hs reason=invalid)\n",
                    source ? source : "unknown");
                return BzrNetNicknameResult::InvalidNickname;
            }

            char oldNickname[128] = {};
            const bool oldNicknameReadable = ReadBzrNetNickname(
                oldNickname, sizeof(oldNickname));
            void* const lobby = TryGetStockBzrNetLobby();
            const bool lobbyValid = lobby && ValidateBzrNetLobbyState(lobby);
            const char* const sessionState = CurrentNicknameSessionState(lobby, lobbyValid);
            const char* const backend = g_IsSteamExe ? "steam" : "gog";
            const std::string stableIdentity = CurrentNicknameStableIdentity();
            const char* const operationSource = source ? source : "unknown";

            Log(L"[BZRNET] NicknameCommandAccepted backend=%hs session=%hs stable=%hs "
                L"old=\"%hs\" requested=\"%hs\" source=%hs\n",
                backend,
                sessionState,
                stableIdentity.c_str(),
                oldNicknameReadable ? oldNickname : "<unavailable>",
                nickname.c_str(),
                operationSource);

            // 0x009453E0 is read when the next Authorization body is built. It
            // is process state, not a live remote-player record.
            const bool localUpdated = WriteBzrNetNickname(nickname.c_str());
            Log(L"[BZRNET] NicknameLocalStateUpdated backend=%hs session=%hs stable=%hs "
                L"success=%hs old=\"%hs\" requested=\"%hs\" source=%hs\n",
                backend,
                sessionState,
                stableIdentity.c_str(),
                localUpdated ? "yes" : "no",
                oldNicknameReadable ? oldNickname : "<unavailable>",
                nickname.c_str(),
                operationSource);

            const bool persisted = WriteShimUserConfigValue(
                kUserConfigNetworkSection, "Nickname", nickname.c_str());
            Log(L"[BZRNET] NicknamePersisted backend=%hs session=%hs stable=%hs "
                L"success=%hs old=\"%hs\" requested=\"%hs\" source=%hs\n",
                backend,
                sessionState,
                stableIdentity.c_str(),
                persisted ? "yes" : "no",
                oldNicknameReadable ? oldNickname : "<unavailable>",
                nickname.c_str(),
                operationSource);

            if (!localUpdated)
            {
                Log(L"[BZRNET] NicknameNativeSendAttempt backend=%hs session=%hs stable=%hs "
                    L"attempted=no boundary=0x006C4F70 reason=local-state-update-failed\n",
                    backend, sessionState, stableIdentity.c_str());
                return persisted
                    ? BzrNetNicknameResult::UnsupportedBuild
                    : BzrNetNicknameResult::PersistenceFailed;
            }

            if (!persisted)
            {
                Log(L"[BZRNET] NicknameNativeSendAttempt backend=%hs session=%hs stable=%hs "
                    L"attempted=no boundary=0x006C4F70 reason=persistence-failed\n",
                    backend, sessionState, stableIdentity.c_str());
                return BzrNetNicknameResult::PersistenceFailed;
            }

            // Lounge/lobby only. Closing the live TCP session to port 1337
            // makes stock reconnect and SendAuthorization with the new
            // 0x009453E0 name. Calling SendAuthorization on an already-
            // authorized socket, SetPlayerData, and a mis-arity 0x006C6E60
            // call all failed to put a ~650-byte Authorization on the wire.
            if (lobby || ReadLocalPlayerNetIdValue() != 0)
            {
                if (lobby && lobbyValid && ReadLocalPlayerNetIdValue() == 0 &&
                    ShouldReauthOnNicknameChange())
                {
                    Log(L"[BZRNET] NicknameNativeSendAttempt backend=%hs session=%hs stable=%hs "
                        L"attempted=yes boundary=closesocket:1337 reason=ws-recycle source=%hs\n",
                        backend, sessionState, stableIdentity.c_str(), operationSource);

                    const bool recycled = RecycleBzrNetWebSocket();
                    Log(L"[BZRNET] NicknameNativeSendCompleted backend=%hs session=%hs stable=%hs "
                        L"entered=yes completed=%hs result=%hs reason=ws-recycle\n",
                        backend, sessionState, stableIdentity.c_str(),
                        recycled ? "yes" : "no",
                        recycled ? "reauth-queued" : "recycle-failed");

                    if (recycled)
                    {
                        Log(L"[BZRNET] Nickname result=%hs (source=%hs)\n",
                            BzrNetNicknameResultName(BzrNetNicknameResult::ReauthQueued),
                            operationSource);
                        return BzrNetNicknameResult::ReauthQueued;
                    }
                }
                Log(L"[BZRNET] NicknameNativeSendAttempt backend=%hs session=%hs stable=%hs "
                    L"attempted=no boundary=0x0074BF60 reason=runtime-name-mutation-unsupported\n",
                    backend, sessionState, stableIdentity.c_str());
                Log(L"[BZRNET] NicknameNativeSendCompleted backend=%hs session=%hs stable=%hs "
                    L"entered=no completed=no result=not-sent "
                    L"reason=runtime-name-mutation-unsupported\n",
                    backend, sessionState, stableIdentity.c_str());
                Log(L"[BZRNET] Nickname result=%hs (source=%hs)\n",
                    BzrNetNicknameResultName(BzrNetNicknameResult::LiveSendUnavailable),
                    operationSource);
                return BzrNetNicknameResult::LiveSendUnavailable;
            }

            Log(L"[BZRNET] NicknameNativeSendAttempt backend=%hs session=%hs stable=%hs "
                L"attempted=no boundary=0x006C4F70 reason=no-active-session\n",
                backend, sessionState, stableIdentity.c_str());
            Log(L"[BZRNET] NicknameNativeSendCompleted backend=%hs session=%hs stable=%hs "
                L"entered=no completed=no result=not-applicable reason=no-active-session\n",
                backend, sessionState, stableIdentity.c_str());
            Log(L"[BZRNET] Nickname result=%hs (source=%hs)\n",
                BzrNetNicknameResultName(BzrNetNicknameResult::StoredForNextConnection),
                operationSource);
            return BzrNetNicknameResult::StoredForNextConnection;
        }

        static const char* BzrNetRoutePreferenceName(BzrNetRoutePreference value)
        {
            switch (value)
            {
            case BzrNetRoutePreference::Direct: return "direct";
            case BzrNetRoutePreference::Relay:  return "relay";
            default:                            return "stock";
            }
        }

        static bool ParseBzrNetRoutePreference(const std::string& raw,
                                               BzrNetRoutePreference& out)
        {
            std::string token;
            token.reserve(raw.size());
            for (const char ch : ToLowerAscii(TrimAsciiCopy(raw)))
            {
                if (ch != ' ' && ch != '_' && ch != '-')
                    token.push_back(ch);
            }

            if (token.empty() || token == "stock" || token == "auto" || token == "default")
            {
                out = BzrNetRoutePreference::Stock;
                return true;
            }
            if (token == "direct" || token == "preferdirect" || token == "ipdirect")
            {
                out = BzrNetRoutePreference::Direct;
                return true;
            }
            if (token == "relay" || token == "forcerelay" || token == "iprelay")
            {
                out = BzrNetRoutePreference::Relay;
                return true;
            }
            return false;
        }

        // Reads back as the requested port before the socket opens and as the
        // actually bound port afterwards.
        int GetBzrNetUdpPort()
        {
            if (!VerifyBzrNetGlobals())
                return -1;
            __try
            {
                return static_cast<int>(*reinterpret_cast<volatile uint16_t*>(kBzrNetUdpPortAddr));
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return -1;
            }
        }

        bool IsBzrNetForceRelayActive()
        {
            if (!VerifyBzrNetGlobals())
                return false;
            __try
            {
                return *reinterpret_cast<volatile uint32_t*>(kBzrNetForceRelayFlagAddr) != 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static void ApplyBzrNetRoutePreference()
        {
            if (g_BzrNetRoutePreference == BzrNetRoutePreference::Stock)
                return;
            if (!VerifyBzrNetGlobals())
                return;

            const uint32_t value =
                (g_BzrNetRoutePreference == BzrNetRoutePreference::Relay) ? 1u : 0u;
            __try
            {
                *reinterpret_cast<volatile uint32_t*>(kBzrNetForceRelayFlagAddr) = value;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[BZRNET] Failed to write route preference flag\n");
            }
        }

        // Split out so InitializeBzrNetConfig can hold std::string locals: a
        // function using __try must not also require object unwinding (C2712).
        static void WriteBzrNetUdpPort(uint16_t port)
        {
            if (!VerifyBzrNetGlobals())
                return;
            __try
            {
                *reinterpret_cast<volatile uint16_t*>(kBzrNetUdpPortAddr) = port;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[BZRNET] Failed to write requested UDP port\n");
            }
        }

        void InitializeBzrNetConfig()
        {
            const bool firstRun = !g_BzrNetConfigInitialized;
            g_BzrNetConfigInitialized = true;

            std::string value;
            g_BzrNetRoutePreference = BzrNetRoutePreference::Stock;
            if (TryGetUserConfigString(kUserConfigNetworkSection, "RoutePreference", value) &&
                !ParseBzrNetRoutePreference(value, g_BzrNetRoutePreference))
            {
                Log(L"[BZRNET] Ignoring invalid RoutePreference=%hs\n", value.c_str());
                g_BzrNetRoutePreference = BzrNetRoutePreference::Stock;
            }
            ApplyBzrNetRoutePreference();

            // Applied on every pass, unlike the port: the engine reads the
            // nickname at identity time rather than latching it at startup, so
            // a later edit is still meaningful. An absent or blank key leaves
            // the buffer alone so the platform account name keeps winning.
            if (TryGetUserConfigString(kUserConfigNetworkSection, "Nickname", value))
            {
                const std::string nickname = TrimAsciiCopy(value);
                if (!nickname.empty())
                    WriteBzrNetNickname(nickname.c_str());
            }

            // The port is deliberately applied once, on the first pass. The
            // engine overwrites the same variable with the bound port, so a
            // later re-apply would either be ignored (socket already open) or
            // clobber the readout the lobby reports.
            if (!firstRun)
                return;

            g_BzrNetConfiguredUdpPort = -1;
            if (TryGetUserConfigString(kUserConfigNetworkSection, "UdpPort", value))
            {
                const std::string trimmed = TrimAsciiCopy(value);
                if (!trimmed.empty())
                {
                    char* end = nullptr;
                    const long parsed = std::strtol(trimmed.c_str(), &end, 10);
                    if (end && *end == '\0' && parsed >= 0 && parsed <= 65535)
                    {
                        g_BzrNetConfiguredUdpPort = static_cast<int>(parsed);
                    }
                    else
                    {
                        Log(L"[BZRNET] Ignoring invalid UdpPort=%hs (expected 0..65535)\n",
                            trimmed.c_str());
                    }
                }
            }

            if (g_BzrNetConfiguredUdpPort > 0)
                WriteBzrNetUdpPort(static_cast<uint16_t>(g_BzrNetConfiguredUdpPort));

            Log(L"[BZRNET] Route preference=%hs port=%hs guard=%hs "
                L"(preference only; Redux still has no LAN browser or direct-IP join)\n",
                BzrNetRoutePreferenceName(g_BzrNetRoutePreference),
                g_BzrNetConfiguredUdpPort > 0 ? std::to_string(g_BzrNetConfiguredUdpPort).c_str()
                                              : "ephemeral",
                g_BzrNetGlobalsVerified ? "ok" : "failed");
        }
    }
}
