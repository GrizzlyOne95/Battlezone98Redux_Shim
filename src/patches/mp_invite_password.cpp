// mp_invite_password.cpp -- let a Steam invite (or Join Game) reach a
// password-protected lobby.
//
// ============================================================================
// THE DEFECT (Redux 2.2.301, exact GOG image)
// ============================================================================
//
// Accepting an invite, or Steam's Join Game, runs
// CNetGameLobby::OnGameLobbyJoinRequested, 0x007408C0 (__thiscall(this,
// lobbyId16*, password string*, friend), ret 0xC). In the shell it parks the
// 16-byte lobby id at this+0x40 (decomp FUN_007408c0 lines 66-69); in a
// mission it stores only the id (FUN_00765bb0) and leaves the mission. The
// lobby list refresh later finds the parked lobby and calls JoinLobby with a
// freshly constructed empty string (FUN_007a11e0 lines 242-246).
//
// JoinLobby, 0x00741990 (__thiscall(this, entry*, password string*), ret 8),
// refuses before sending anything when the entry is passworded and the string
// differs from the entry's password (FUN_00741990 lines 24-28: entry+0xB2 is
// the flag, entry+0x98 the std::string the server sent with the lobby list).
// So an invited friend never reaches a passworded lobby; the join fails
// silently on their machine.
//
// ============================================================================
// THE FIX
// ============================================================================
//
//   1. OnGameLobbyJoinRequested detour (10 bytes): records the requested lobby
//      id, then runs the original.
//   2. JoinLobby detour (10 bytes): when the password is empty, the entry is
//      passworded, and the entry id (entry+0x10, the id JoinLobby itself sends,
//      FUN_00741990 line 51) is the recorded invite, the original runs with the
//      entry's own password. The record is consumed by the first JoinLobby for
//      that lobby, within 2 minutes. Every other join is untouched, so the password popup still
//      guards joins from the lobby list. JoinLobby only reads the string: it
//      compares it (line 25), copies it into this+0xA4 (line 33; 0x00741A37
//      calls operator= 0x0041F710) and passes it on (line 52); its caller owns
//      and destroys the temporary, so passing the entry's string is safe.
//
// Only a player who was invited, or who can Join Game from the host's Steam
// presence, gets the password filled. The client already holds the password
// in the lobby list; the server still checks it.
//
// Not covered: a game launched by the invite (FUN_00741840) joins straight
// from the command line without a list entry. UNVERIFIED whether that path
// fails for passworded lobbies.

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

            constexpr uintptr_t kEntryIdOffset = 0x10;
            constexpr uintptr_t kEntryPasswordOffset = 0x98;
            constexpr uintptr_t kEntryHasPasswordOffset = 0xB2;
            constexpr size_t kLobbyIdBytes = 16;
            // MSVC std::string (x86): 16-byte buffer/pointer, then size.
            constexpr uintptr_t kStringSizeOffset = 0x10;

            using FnJoinRequested = void(__fastcall*)(void* self, void* edx, const void* lobbyId, void* password,
                                                      uint32_t friendArg);
            using FnJoinLobby = uint8_t(__fastcall*)(void* self, void* edx, void* entry, void* password);

            // push ebp / mov ebp,esp / push -1 / push imm32 (absolute SEH handler).
            constexpr uint8_t kJoinRequestedStolen[10] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF, 0x68, 0x3B, 0x0B, 0x85, 0x00 };
            constexpr uint8_t kJoinLobbyStolen[10] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF, 0x68, 0xFB, 0x0D, 0x85, 0x00 };

            bool g_Done = false;
            InlineDetour32 g_JoinRequestedDetour = {};
            InlineDetour32 g_JoinLobbyDetour = {};
            void* volatile g_JoinRequestedOriginal = nullptr;
            void* volatile g_JoinLobbyOriginal = nullptr;

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

            void __fastcall JoinRequestedHook(void* self, void* edx, const void* lobbyId, void* password,
                                              uint32_t friendArg)
            {
                if (lobbyId && SafeCopy(g_PendingId, reinterpret_cast<uintptr_t>(lobbyId), kLobbyIdBytes))
                {
                    g_HavePending = true;
                    g_PendingAt = GetTickCount64();
                }
                const FnJoinRequested original = reinterpret_cast<FnJoinRequested>(g_JoinRequestedOriginal);
                if (original)
                    original(self, edx, lobbyId, password, friendArg);
            }

            uint8_t __fastcall JoinLobbyHook(void* self, void* edx, void* entry, void* password)
            {
                const FnJoinLobby original = reinterpret_cast<FnJoinLobby>(g_JoinLobbyOriginal);
                if (!original)
                    return 0;
                const uintptr_t e = reinterpret_cast<uintptr_t>(entry);
                uint8_t entryId[kLobbyIdBytes] = {};
                if (g_HavePending && GetTickCount64() - g_PendingAt > kPendingMs)
                    g_HavePending = false;
                if (!g_HavePending || !e || !SafeCopy(entryId, e + kEntryIdOffset, kLobbyIdBytes) ||
                    std::memcmp(entryId, g_PendingId, kLobbyIdBytes) != 0)
                    return original(self, edx, entry, password);

                g_HavePending = false;  // one join per invite
                uint8_t hasPassword = 0;
                uint32_t typedLength = 0;
                if (!password || !SafeCopy(&hasPassword, e + kEntryHasPasswordOffset, 1) || !hasPassword ||
                    !SafeCopy(&typedLength, reinterpret_cast<uintptr_t>(password) + kStringSizeOffset,
                              sizeof(typedLength)) ||
                    typedLength != 0)
                    return original(self, edx, entry, password);

                LogShimA(LogLevel::Info, kComponent, "invited join to a passworded lobby: using the lobby's password");
                return original(self, edx, entry, reinterpret_cast<void*>(e + kEntryPasswordOffset));
            }

            void RollBack()
            {
                if (g_JoinRequestedDetour.target)
                    HookEngine::WriteMemory(static_cast<uint32_t>(g_JoinRequestedDetour.target),
                                            g_JoinRequestedDetour.original.data(), g_JoinRequestedDetour.patchLen);
            }

            bool DoInstall()
            {
                uint32_t requestedAddr = 0, joinAddr = 0;
                // Literal names so patch_registration_tests can check them
                // against scripts/patches.json.
                const HookEngine::EngineRow rows[] = {
                    { "LobbyOnJoinRequested", &requestedAddr },
                    { "LobbyJoinLobby", &joinAddr },
                };
                if (!HookEngine::BindEngineRows("InvitePassword", rows))
                {
                    LogShimA(LogLevel::Warn, kComponent, "an address did not resolve; invite password fix not installed");
                    return false;
                }
                if (!InstallInlineDetour32(g_JoinRequestedDetour, requestedAddr,
                                           reinterpret_cast<void*>(JoinRequestedHook), sizeof(kJoinRequestedStolen),
                                           kJoinRequestedStolen, sizeof(kJoinRequestedStolen),
                                           &g_JoinRequestedOriginal))
                {
                    LogShimA(LogLevel::Warn, kComponent, "OnGameLobbyJoinRequested failed its byte guard; not installed");
                    g_JoinRequestedDetour = {};
                    return false;
                }
                if (!InstallInlineDetour32(g_JoinLobbyDetour, joinAddr, reinterpret_cast<void*>(JoinLobbyHook),
                                           sizeof(kJoinLobbyStolen), kJoinLobbyStolen, sizeof(kJoinLobbyStolen),
                                           &g_JoinLobbyOriginal))
                {
                    LogShimA(LogLevel::Warn, kComponent, "JoinLobby failed its byte guard; not installed");
                    g_JoinLobbyDetour = {};
                    RollBack();
                    return false;
                }
                LogShimA(LogLevel::Info, kComponent, "installed: OnGameLobbyJoinRequested 0x%08X, JoinLobby 0x%08X",
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
