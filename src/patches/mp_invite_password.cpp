// mp_invite_password.cpp -- make a Steam invite to a password-protected lobby
// carry the password, so the invited friend gets in.
//
// ============================================================================
// THE DEFECT (Redux 2.2.301, exact GOG image)
// ============================================================================
//
// Every invite sender builds the Steam connect string from the CNetGameLobby
// singleton ([0x00945470], FUN_00764760): "-connect-galaxy-lobby=" + lobby id,
// then, only when the std::string at this+0xA4 is not empty, "," + that string
// (FUN_007582e0 lines 41-58, the in-game invite; FUN_00755110 lines 74-93, the
// overlay invite). The invitee's handler FUN_00757e00 (lines 33-45) splits the
// id from the text after ',' and hands both to OnGameLobbyJoinRequested
// 0x007408C0, which stores the password in its own this+0xA4; RunCallbacks
// then joins by id with it (FUN_00740be0 line 79).
//
// The host never fills this+0xA4. CreateLobby 0x007426E0 (logs
// "CNetGameLobby::CreateLobby called, creating game"; __thiscall(this, bool
// private, string* password, string* name), ret 0xC at 0x007427E7) copies the
// password to this+0x64 and the name to this+0x88 and nothing to this+0xA4.
// Live 2026-11-08 (PC 1 hosting private lobby B1001 with a password, read
// with ReadProcessMemory): +0x64 holds the password, +0xA4 is empty. So every
// invite goes out with no password and the server refuses the join
// (Battlezone98Redux_DedicatedServer server.py: JOIN_FAIL_BAD_PASSWORD), and
// the invitee sits on "gathering information from the server".
//
// The client cannot recover the password itself: the lobby list the server
// sends carries none (list entry +0x98 empty, live 2026-11-08 on PC 2).
//
// ============================================================================
// THE FIX
// ============================================================================
//
// A CreateLobby detour (10 bytes: push ebp / mov ebp,esp / push -1 / push
// imm32 SEH handler; absolute operand only) runs the original, then assigns
// this+0xA4 = this+0x64 with the engine's own std::string operator=
// 0x0041F710 (__thiscall(dst, const string* src), ret 4 at 0x0041F781), so
// the engine's CRT owns the buffer. A lobby with no password assigns an empty
// string, which also clears one left by an earlier lobby. The stock senders
// and the stock invitee parser then do the rest; the server still checks the
// password.
//
// Side effect, stock behaviour: the rich-presence writers (FUN_00755710 lines
// 44-75, FUN_00758470) publish "connect" only while this+0xA4 is empty, so a
// passworded lobby shows no Steam "Join Game"; friends join it by invite.
//
// UNVERIFIED: GOG Galaxy invites were not tested. UNVERIFIED: a guest's this+0xA4 keeps
// the last hosted lobby's password until the next CreateLobby (harmless to
// the server, which checks only passworded lobbies; it can hide the guest's
// own "Join Game" presence).

#include "mp_invite_password_install.h"

#include "bzr_options_ui.h"
#include "env_switch_table.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>
#include <cstdint>

namespace BZROpenShim
{
    namespace InvitePassword
    {
        namespace
        {
            constexpr const char* kComponent = "INVITEPW";

            constexpr uintptr_t kCreatePasswordOffset = 0x64;  // CreateLobby's copy of the password
            constexpr uintptr_t kInvitePasswordOffset = 0xA4;  // what every invite sender reads
            // MSVC std::string (x86): 16-byte buffer/pointer, then size.
            constexpr uintptr_t kStringSizeOffset = 0x10;

            using FnCreateLobby = void(__fastcall*)(void* self, void* edx, uint32_t isPrivate, void* password,
                                                    void* name);
            // __thiscall(dst, const string* src); called as fastcall with edx unused.
            using FnStringAssign = void*(__fastcall*)(void* dst, void* edx, const void* src);

            // push ebp / mov ebp,esp / push -1 / push 0x0084FCAB (SEH handler).
            constexpr uint8_t kCreateLobbyStolen[10] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF, 0x68, 0xAB, 0xFC, 0x84, 0x00 };

            bool g_Done = false;
            InlineDetour32 g_CreateLobbyDetour = {};
            void* volatile g_CreateLobbyOriginal = nullptr;
            FnStringAssign g_StringAssign = nullptr;

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

            uint32_t SafeStringSize(uintptr_t str)
            {
                __try
                {
                    return *reinterpret_cast<const uint32_t*>(str + kStringSizeOffset);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return 0xFFFFFFFFu;
                }
            }

            bool SafeAssign(uintptr_t dst, uintptr_t src)
            {
                __try
                {
                    g_StringAssign(reinterpret_cast<void*>(dst), nullptr, reinterpret_cast<const void*>(src));
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            void __fastcall CreateLobbyHook(void* self, void* edx, uint32_t isPrivate, void* password, void* name)
            {
                const FnCreateLobby original = reinterpret_cast<FnCreateLobby>(g_CreateLobbyOriginal);
                if (original)
                    original(self, edx, isPrivate, password, name);
                if (!self || !g_StringAssign)
                    return;
                const uintptr_t lobby = reinterpret_cast<uintptr_t>(self);
                const uint32_t length = SafeStringSize(lobby + kCreatePasswordOffset);
                if (length == 0xFFFFFFFFu)
                {
                    LogShimA(LogLevel::Warn, kComponent, "lobby password unreadable; invites unchanged");
                    return;
                }
                if (!SafeAssign(lobby + kInvitePasswordOffset, lobby + kCreatePasswordOffset))
                {
                    LogShimA(LogLevel::Warn, kComponent, "copying the lobby password faulted; invites unchanged");
                    return;
                }
                // Never log the password itself.
                LogShimA(LogLevel::Info, kComponent, "lobby created: invite password length %u",
                         SafeStringSize(lobby + kInvitePasswordOffset));
            }

            bool DoInstall()
            {
                uint32_t createAddr = 0, assignAddr = 0;
                // Literal names so patch_registration_tests can check them
                // against scripts/patches.json.
                const HookEngine::EngineRow rows[] = {
                    { "LobbyCreateLobby", &createAddr },
                    { "LobbyStringAssign", &assignAddr },
                };
                if (!HookEngine::BindEngineRows("InvitePassword", rows))
                {
                    LogShimA(LogLevel::Warn, kComponent, "an address did not resolve; invite password fix not installed");
                    return false;
                }
                g_StringAssign = reinterpret_cast<FnStringAssign>(static_cast<uintptr_t>(assignAddr));
                if (!InstallInlineDetour32(g_CreateLobbyDetour, createAddr, reinterpret_cast<void*>(CreateLobbyHook),
                                           sizeof(kCreateLobbyStolen), kCreateLobbyStolen, sizeof(kCreateLobbyStolen),
                                           &g_CreateLobbyOriginal))
                {
                    LogShimA(LogLevel::Warn, kComponent, "CreateLobby failed its byte guard; not installed");
                    g_CreateLobbyDetour = {};
                    g_StringAssign = nullptr;
                    return false;
                }
                LogShimA(LogLevel::Info, kComponent, "installed: CreateLobby 0x%08X, string assign 0x%08X",
                         createAddr, assignAddr);
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
