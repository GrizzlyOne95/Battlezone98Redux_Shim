// mp_invite_password.cpp -- let a Steam invite (or Join Game) reach a
// password-protected lobby.
//
// ============================================================================
// THE DEFECT (Redux 2.2.301, exact GOG image)
// ============================================================================
//
// Accepting an invite, or Steam's Join Game, runs
// CNetGameLobby::OnGameLobbyJoinRequested, 0x007408C0 (__thiscall(this,
// lobbyId16*, password string*, friend), ret 0xC). In the shell it copies the
// invite's password (always empty: the Steam connect string carries none)
// into this+0xA4 and parks the 16-byte lobby id at this+0x40 (decomp
// FUN_007408c0 lines 65-69); in a mission it stores only the id
// (FUN_00765bb0) and leaves the mission.
//
// CNetGameLobby::RunCallbacks (FUN_00740be0 line 79) later joins the parked
// lobby through the virtual join-by-id, vtable slot +0x7C, passing this+0x40
// and this+0xA4. On BZRNet that slot is 0x0074B7C0 (BZRNetLobby vtable
// 0x0089ADDC): it parses the id and sends the join with that password, no
// client-side check (FUN_0074b7c0 lines 46-76). The server refuses the empty
// password (OnLobbyJoined success=false) and the invitee sits on "gathering
// information from the server". Live repro 2026-11-08: invitee log shows
// "RunCallbacks, requesting to join lobby B1001" and never enters it.
//
// JoinLobby 0x00741990 (the lobby-list path, with the password popup) and
// JoinLobbyFromLaunchInvite 0x00741840 reach the same slot (FUN_00741990
// line 52, FUN_00741840 line 56).
//
// ============================================================================
// THE FIX
// ============================================================================
//
//   1. OnGameLobbyJoinRequested detour (10 bytes): records the requested lobby
//      id, then runs the original.
//   2. BZRNet join-by-id detour (10 bytes): when the password is empty and the
//      id is the recorded invite (within 2 minutes), it looks the lobby up in
//      the client's own list with FindLobby 0x007470B0 (create = 0; returns
//      the entry or 0, disassembly 0x00747158-0x0074716A; 0x0056F900 calls it
//      the same way with ecx = this) and, if the entry is passworded
//      (entry+0xB2), sends the entry's password (entry+0x98, the string the
//      server sent with the lobby list). The record is consumed by the first
//      join for that lobby. Every other join is untouched.
//
// Only a player who was invited, or who can Join Game from the host's Steam
// presence, gets the password filled. The client already holds the password
// in the lobby list; the server still checks it.
//
// Not covered: GOG Galaxy lobbies use another class's slot (CGalaxyLobby); a
// lobby missing from the invitee's list joins with the empty password as
// before. UNVERIFIED: the launch-invite path (game started by the invite) has
// a populated list by the time it joins.

#include "mp_invite_password_install.h"

#include "bzr_options_ui.h"
#include "env_switch_table.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace InvitePassword
    {
        namespace
        {
            constexpr const char* kComponent = "INVITEPW";

            constexpr uintptr_t kEntryPasswordOffset = 0x98;
            constexpr uintptr_t kEntryHasPasswordOffset = 0xB2;
            constexpr size_t kLobbyIdBytes = 16;
            // MSVC std::string (x86): 16-byte buffer/pointer, then size.
            constexpr uintptr_t kStringSizeOffset = 0x10;

            using FnJoinRequested = void(__fastcall*)(void* self, void* edx, const void* lobbyId, void* password,
                                                      uint32_t friendArg);
            using FnJoinById = void(__fastcall*)(void* self, void* edx, const void* lobbyId, void* password);
            using FnFindLobby = void*(__fastcall*)(void* self, void* edx, const void* lobbyId, uint32_t create);

            // push ebp / mov ebp,esp / push -1 / push imm32 (absolute SEH handler).
            constexpr uint8_t kJoinRequestedStolen[10] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF, 0x68, 0x3B, 0x0B, 0x85, 0x00 };
            constexpr uint8_t kJoinByIdStolen[10] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF, 0x68, 0x58, 0xBC, 0x85, 0x00 };

            bool g_Done = false;
            InlineDetour32 g_JoinRequestedDetour = {};
            InlineDetour32 g_JoinByIdDetour = {};
            void* volatile g_JoinRequestedOriginal = nullptr;
            void* volatile g_JoinByIdOriginal = nullptr;
            FnFindLobby g_FindLobby = nullptr;

            // Game thread only.
            bool g_HavePending = false;
            uint64_t g_PendingAt = 0;  // a stale invite must not fill a later manual join
            constexpr uint64_t kPendingMs = 120000;
            uint8_t g_PendingId[kLobbyIdBytes] = {};

            bool IsEnabled()
            {
                bool enabled = true;
                static const EnvSwitches::EnvSwitch rows[] = {
                    { &enabled, EnvSwitches::Kind::KillSwitch,
                      "OPENSHIM_DISABLE_MP_INVITE_PASSWORD", "BZR_DISABLE_MP_INVITE_PASSWORD" },
                };
                EnvSwitches::Apply(rows, EnvFlagEnabled);
                return enabled;
            }

            bool SafeCopy(void* dst, uintptr_t src, size_t len)
            {
                __try
                {
                    std::memcpy(dst, reinterpret_cast<const void*>(src), len);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            void* SafeFindLobby(void* self, const void* lobbyId)
            {
                __try
                {
                    return g_FindLobby(self, nullptr, lobbyId, 0);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return nullptr;
                }
            }

            // 16 id bytes as hex, for the diagnostic lines.
            void HexId(const uint8_t* id, char (&out)[kLobbyIdBytes * 2 + 1])
            {
                static const char digits[] = "0123456789abcdef";
                for (size_t i = 0; i < kLobbyIdBytes; ++i)
                {
                    out[i * 2] = digits[id[i] >> 4];
                    out[i * 2 + 1] = digits[id[i] & 0xF];
                }
                out[kLobbyIdBytes * 2] = 0;
            }

            uint32_t StringSize(const void* str)
            {
                uint32_t size = 0xFFFFFFFFu;
                if (str)
                    SafeCopy(&size, reinterpret_cast<uintptr_t>(str) + kStringSizeOffset, sizeof(size));
                return size;
            }

            void __fastcall JoinRequestedHook(void* self, void* edx, const void* lobbyId, void* password,
                                              uint32_t friendArg)
            {
                if (lobbyId && SafeCopy(g_PendingId, reinterpret_cast<uintptr_t>(lobbyId), kLobbyIdBytes))
                {
                    g_HavePending = true;
                    g_PendingAt = GetTickCount64();
                    char hex[kLobbyIdBytes * 2 + 1];
                    HexId(g_PendingId, hex);
                    LogShimA(LogLevel::Info, kComponent, "join requested: id %s, invite password length %u", hex,
                             StringSize(password));
                }
                const FnJoinRequested original = reinterpret_cast<FnJoinRequested>(g_JoinRequestedOriginal);
                if (original)
                    original(self, edx, lobbyId, password, friendArg);
            }

            void __fastcall JoinByIdHook(void* self, void* edx, const void* lobbyId, void* password)
            {
                const FnJoinById original = reinterpret_cast<FnJoinById>(g_JoinByIdOriginal);
                if (!original)
                    return;
                uint8_t id[kLobbyIdBytes] = {};
                if (g_HavePending && GetTickCount64() - g_PendingAt > kPendingMs)
                    g_HavePending = false;
                const bool haveId = lobbyId && SafeCopy(id, reinterpret_cast<uintptr_t>(lobbyId), kLobbyIdBytes);
                const uint32_t typedLength = StringSize(password);
                char hex[kLobbyIdBytes * 2 + 1];
                HexId(id, hex);
                const bool matches = g_HavePending && haveId && std::memcmp(id, g_PendingId, kLobbyIdBytes) == 0;
                LogShimA(LogLevel::Info, kComponent, "join by id: id %s, password length %u, %s", hex, typedLength,
                         matches ? "the invited lobby" : (g_HavePending ? "not the invited lobby" : "no invite pending"));
                if (!matches)
                {
                    original(self, edx, lobbyId, password);
                    return;
                }

                g_HavePending = false;  // one join per invite
                if (typedLength != 0)
                {
                    original(self, edx, lobbyId, password);
                    return;
                }
                const uintptr_t entry = reinterpret_cast<uintptr_t>(SafeFindLobby(self, lobbyId));
                uint8_t hasPassword = 0;
                if (!entry)
                {
                    LogShimA(LogLevel::Info, kComponent, "invited lobby is not in the lobby list; joining without a password");
                    original(self, edx, lobbyId, password);
                    return;
                }
                if (!SafeCopy(&hasPassword, entry + kEntryHasPasswordOffset, 1) || !hasPassword)
                {
                    LogShimA(LogLevel::Info, kComponent, "invited lobby has no password; joining as is");
                    original(self, edx, lobbyId, password);
                    return;
                }
                LogShimA(LogLevel::Info, kComponent, "invited join to a passworded lobby: using the lobby's password");
                original(self, edx, lobbyId, reinterpret_cast<void*>(entry + kEntryPasswordOffset));
            }

            void RollBack()
            {
                if (g_JoinRequestedDetour.target)
                    HookEngine::WriteMemory(static_cast<uint32_t>(g_JoinRequestedDetour.target),
                                            g_JoinRequestedDetour.original.data(), g_JoinRequestedDetour.patchLen);
            }

            bool DoInstall()
            {
                uint32_t requestedAddr = 0, joinAddr = 0, findAddr = 0;
                // Literal names so patch_registration_tests can check them
                // against scripts/patches.json.
                const HookEngine::EngineRow rows[] = {
                    { "LobbyOnJoinRequested", &requestedAddr },
                    { "LobbyJoinById", &joinAddr },
                    { "LobbyFindLobby", &findAddr },
                };
                if (!HookEngine::BindEngineRows("InvitePassword", rows))
                {
                    LogShimA(LogLevel::Warn, kComponent, "an address did not resolve; invite password fix not installed");
                    return false;
                }
                g_FindLobby = reinterpret_cast<FnFindLobby>(static_cast<uintptr_t>(findAddr));
                if (!InstallInlineDetour32(g_JoinRequestedDetour, requestedAddr,
                                           reinterpret_cast<void*>(JoinRequestedHook), sizeof(kJoinRequestedStolen),
                                           kJoinRequestedStolen, sizeof(kJoinRequestedStolen),
                                           &g_JoinRequestedOriginal))
                {
                    LogShimA(LogLevel::Warn, kComponent, "OnGameLobbyJoinRequested failed its byte guard; not installed");
                    g_JoinRequestedDetour = {};
                    return false;
                }
                if (!InstallInlineDetour32(g_JoinByIdDetour, joinAddr, reinterpret_cast<void*>(JoinByIdHook),
                                           sizeof(kJoinByIdStolen), kJoinByIdStolen, sizeof(kJoinByIdStolen),
                                           &g_JoinByIdOriginal))
                {
                    LogShimA(LogLevel::Warn, kComponent, "join-by-id failed its byte guard; not installed");
                    g_JoinByIdDetour = {};
                    RollBack();
                    return false;
                }
                LogShimA(LogLevel::Info, kComponent, "installed: OnGameLobbyJoinRequested 0x%08X, join-by-id 0x%08X",
                         requestedAddr, joinAddr);
                return true;
            }
        }

        void InstallInvitePasswordIfPossible()
        {
            if (g_Done)
                return;
            g_Done = true;
            if (!IsEnabled())
            {
                LogShimA(LogLevel::Info, kComponent, "disabled ([Fixes] InvitePassword = 0)");
                return;
            }
            DoInstall();
        }
    }
}
