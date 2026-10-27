// mp_host_leave.cpp -- keep a multiplayer match alive, and the departed host's
// AI with it, when the host leaves.
//
// ============================================================================
// THE DEFECT (Redux 2.2.301, exact GOG image)
// ============================================================================
//
// The NetPlayer destructor, 0x00575BF0 (__thiscall(NetPlayer* this), plain
// ret; this+0x28 = u16 player id, this+0x68 = team byte), first zeroes the
// session host id (*(u16*)(*(u32*)0x00917F48 + 4)) when it equals the leaver,
// then loops every game object. Per object it calls the Distributed owner
// accessor 0x004B9800 (__thiscall, u16 owner from Distributed+0x62) at
// 0x00575CDC, compares the owner with the leaver id and, on a match, flags a
// dynamic object destroyed (0x00575D78) or SetLocals the rest (0x00575D86).
// In co-op every AI unit is owned by the host, so all of them vanish on every
// peer the moment the host leaves.
//
// NotifyNowHost, 0x00578760 (__cdecl, no arguments), runs on the newly elected
// host and is meant to take the leaver's objects over:
//   if (host id != 0) { TakeOwnership(0); TakeOwnership(hostId); }
// (0x00578867 / 0x0057887A -> 0x004BAAD0, cdecl, one int argument). The
// destructor zeroed the host id first, so the branch never runs.
//
// With two players the survivor is then alone, and Net::Execute (0x005715D0)
// sees 0x00577D50 ("exactly one player with lives left") at 0x0057191A and
// puts every guest on dialog 11 (Game Over) half a second later.
//
// ============================================================================
// THE FIX
// ============================================================================
//
// Five parts, installed together or not at all:
//
//   1. NetPlayer destructor detour (0x00575BF0, 10 bytes). Notes that a player
//      left; when the leaver is the session host it records the id and team
//      byte as the previous host, then runs the original.
//   2. The owner call at 0x00575CDC goes through a wrapper that returns 0 for
//      objects owned by the leaving host, so the stock compare fails and the
//      object is neither destroyed nor localized. It stays a remote copy.
//   3. NotifyNowHost detour (0x00578760, 11 bytes). Runs the original; then,
//      if a previous host was recorded and this machine is now the host, runs
//      the takeover the stock code skipped: TakeOwnership(0) and
//      TakeOwnership(previous host).
//   4. TakeOwnership looks the player up through 0x005771B0 at 0x004BAB2A. The
//      NetPlayer is already destroyed, so during that takeover the call is
//      answered with a stand-in carrying the id (+0x28) and the team byte
//      (+0x68). TakeOwnership then destroys the leaver's own-team dynamic
//      objects and keeps and re-owns the rest (the AI teams).
//   5. The last-player check at 0x0057191A goes through a wrapper that hides a
//      lone-player state caused by a leave. A real last-man-standing on lives
//      still ends the match: the suppression ends as soon as 2+ players have
//      lives again.
//
// If NotifyNowHost runs before the destructor, stock already works and no
// previous host is recorded. Every address is a named row in
// scripts/patches.json with a byte guard.

#include "mp_host_leave_install.h"

#include "bzr_options_ui.h"
#include "env_switch_table.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace HostLeave
    {
        namespace
        {
            constexpr const char* kComponent = "HOSTLEAVE";

            constexpr uintptr_t kPlayerIdOffset = 0x28;
            constexpr uintptr_t kPlayerTeamOffset = 0x68;
            constexpr uintptr_t kSessionHostIdOffset = 4;
            constexpr uintptr_t kSessionStateOffset = 8;
            constexpr uint32_t kSessionStateInGame = 4;
            constexpr uint16_t kNoOwner = 0xFFFF;

            using FnVoidFastcall = void(__fastcall*)(void* self, void* edx);
            using FnNotifyNowHost = void(__cdecl*)();
            using FnOwner = uint16_t(__thiscall*)(void* distributed);
            using FnTakeOwnership = void(__cdecl*)(int id);
            using FnFindPlayer = void*(__cdecl*)(int id);
            using FnOnePlayerLeft = unsigned char(__cdecl*)();
            using FnLocalPlayerId = uint16_t(__cdecl*)();

            // Whole instructions; the push imm32 / cmp operands are absolute.
            constexpr uint8_t kDtorStolen[10] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF, 0x68, 0x26, 0xB9, 0x84, 0x00 };
            constexpr uint8_t kNotifyStolen[11] = { 0x55, 0x8B, 0xEC, 0x56, 0x83, 0x3D, 0x48, 0x7F, 0x91, 0x00, 0x00 };

            bool g_Done = false;
            InlineDetour32 g_DtorDetour = {};
            InlineDetour32 g_NotifyDetour = {};
            void* volatile g_DtorOriginal = nullptr;
            void* volatile g_NotifyOriginal = nullptr;

            FnOwner g_Owner = nullptr;
            FnTakeOwnership g_TakeOwnership = nullptr;
            FnFindPlayer g_FindPlayer = nullptr;
            FnOnePlayerLeft g_OnePlayerLeft = nullptr;
            FnLocalPlayerId g_LocalPlayerId = nullptr;
            uintptr_t g_SessionPtrAddr = 0;

            // A patched call site, for rollback.
            struct CallSite
            {
                uintptr_t address = 0;
                uint8_t original[5] = {};
                bool patched = false;
            };
            CallSite g_OwnerSite;
            CallSite g_LookupSite;
            CallSite g_OnePlayerSite;

            // State; everything here runs on the game thread.
            bool g_LeaveHappened = false;
            uint16_t g_SkipOwner = kNoOwner;
            uint16_t g_PrevHost = 0;
            uint8_t g_PrevHostTeam = 0;
            unsigned g_Skipped = 0;
            bool g_SuppressLogged = false;
            bool g_InTakeover = false;
            uint16_t g_TakeoverId = 0;

            alignas(16) uint8_t g_FakePlayer[0x200] = {};

            bool IsEnabled()
            {
                bool enabled = true;
                static const EnvSwitches::EnvSwitch rows[] = {
                    { &enabled, EnvSwitches::Kind::KillSwitch,
                      "OPENSHIM_DISABLE_MP_HOST_LEAVE", "BZR_DISABLE_MP_HOST_LEAVE" },
                };
                EnvSwitches::Apply(rows, EnvFlagEnabled);
                return enabled;
            }

            bool SafeReadU32(uintptr_t address, uint32_t& out)
            {
                __try
                {
                    out = *reinterpret_cast<const uint32_t*>(address);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool SafeReadU16(uintptr_t address, uint16_t& out)
            {
                __try
                {
                    out = *reinterpret_cast<const uint16_t*>(address);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool SafeReadU8(uintptr_t address, uint8_t& out)
            {
                __try
                {
                    out = *reinterpret_cast<const uint8_t*>(address);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            // The session's host id; false when there is no session.
            bool ReadSessionHostId(uint16_t& out)
            {
                uint32_t session = 0;
                return SafeReadU32(g_SessionPtrAddr, session) && session != 0 &&
                       SafeReadU16(session + kSessionHostIdOffset, out);
            }

            // A leave only counts mid-match; NetPlayers freed at teardown or
            // in the lobby must not arm the Game Over suppression or a
            // takeover for a later match.
            bool SessionInGame()
            {
                uint32_t session = 0;
                uint32_t state = 0;
                return SafeReadU32(g_SessionPtrAddr, session) && session != 0 &&
                       SafeReadU32(session + kSessionStateOffset, state) && state == kSessionStateInGame;
            }

            // Runs the takeover; its own function because __try cannot share
            // a frame with objects that need unwinding.
            bool SafeTakeOwnership(int id)
            {
                __try
                {
                    g_TakeOwnership(id);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            // 1. NetPlayer destructor.
            void __fastcall DtorHook(void* player, void* edx)
            {
                g_SkipOwner = kNoOwner;
                g_Skipped = 0;
                if (!SessionInGame())
                {
                    g_LeaveHappened = false;
                    g_PrevHost = 0;
                    const FnVoidFastcall passthrough = reinterpret_cast<FnVoidFastcall>(g_DtorOriginal);
                    if (passthrough)
                        passthrough(player, edx);
                    return;
                }
                g_LeaveHappened = true;

                uint16_t id = 0;
                uint8_t team = 0;
                uint16_t hostId = 0;
                const uintptr_t p = reinterpret_cast<uintptr_t>(player);
                if (p && SafeReadU16(p + kPlayerIdOffset, id) && SafeReadU8(p + kPlayerTeamOffset, team) &&
                    id != 0 && ReadSessionHostId(hostId) && hostId == id)
                {
                    g_SkipOwner = id;
                    g_PrevHost = id;
                    g_PrevHostTeam = team;
                    LogShimA(LogLevel::Info, kComponent,
                             "host player %u (team %u) is leaving; its objects are kept as remote copies",
                             static_cast<unsigned>(id), static_cast<unsigned>(team));
                }

                const FnVoidFastcall original = reinterpret_cast<FnVoidFastcall>(g_DtorOriginal);
                if (original)
                    original(player, edx);

                if (g_SkipOwner != kNoOwner)
                {
                    LogShimA(LogLevel::Info, kComponent, "kept %u object(s) owned by leaving host %u",
                             g_Skipped, static_cast<unsigned>(g_SkipOwner));
                    g_SkipOwner = kNoOwner;
                }
            }

            // 2. Owner accessor call inside the destructor's object loop. The
            // caller reads AX; a zero owner never matches a real leaver.
            uint32_t __fastcall OwnerWrapper(void* distributed, void* /*edx*/)
            {
                const uint16_t owner = g_Owner(distributed);
                if (g_SkipOwner != kNoOwner && owner == g_SkipOwner)
                {
                    ++g_Skipped;
                    return 0;
                }
                return owner;
            }

            // 3. NotifyNowHost.
            void __cdecl NotifyHook()
            {
                // The kicked/exiting branch also ends with host = local; only a
                // machine that was not host before the call is a new host.
                uint16_t hostBefore = 0;
                const uint16_t localBefore = g_LocalPlayerId ? g_LocalPlayerId() : 0;
                const bool wasHost = ReadSessionHostId(hostBefore) && hostBefore != 0 && hostBefore == localBefore;

                const FnNotifyNowHost original = reinterpret_cast<FnNotifyNowHost>(g_NotifyOriginal);
                if (original)
                    original();

                if (g_PrevHost == 0)
                    return;
                if (wasHost || !SessionInGame())
                {
                    g_PrevHost = 0;
                    return;
                }

                uint16_t hostId = 0;
                const uint16_t localId = g_LocalPlayerId ? g_LocalPlayerId() : 0;
                if (!ReadSessionHostId(hostId) || hostId == 0 || hostId != localId)
                    return;

                const uint16_t prev = g_PrevHost;
                g_PrevHost = 0;
                g_TakeoverId = prev;
                g_InTakeover = true;
                const bool ok = SafeTakeOwnership(0) && SafeTakeOwnership(prev);
                g_InTakeover = false;
                if (ok)
                    LogShimA(LogLevel::Info, kComponent,
                             "this machine (player %u) is the new host; took over objects of departed host %u (team %u)",
                             static_cast<unsigned>(localId), static_cast<unsigned>(prev),
                             static_cast<unsigned>(g_PrevHostTeam));
                else
                    LogShimA(LogLevel::Warn, kComponent, "exception during takeover of departed host %u",
                             static_cast<unsigned>(prev));
            }

            // 4. NetPlayer lookup inside TakeOwnership.
            void* __cdecl LookupWrapper(int id)
            {
                if (g_InTakeover && (static_cast<unsigned>(id) & 0xFFFF) == g_TakeoverId && g_TakeoverId != 0)
                {
                    std::memset(g_FakePlayer, 0, sizeof(g_FakePlayer));
                    const uint16_t pid = g_TakeoverId;
                    std::memcpy(g_FakePlayer + kPlayerIdOffset, &pid, sizeof(pid));
                    g_FakePlayer[kPlayerTeamOffset] = g_PrevHostTeam;
                    return g_FakePlayer;
                }
                return g_FindPlayer(id);
            }

            // 5. Last-player-standing check in Net::Execute.
            unsigned char __cdecl OnePlayerWrapper()
            {
                const unsigned char r = g_OnePlayerLeft();
                if (!r || !SessionInGame())
                {
                    g_LeaveHappened = false;
                    g_SuppressLogged = false;
                    return 0;
                }
                if (g_LeaveHappened)
                {
                    if (!g_SuppressLogged)
                    {
                        g_SuppressLogged = true;
                        LogShimA(LogLevel::Info, kComponent, "lone player after a leave: Game Over suppressed");
                    }
                    return 0;
                }
                return r;
            }

            // Redirects the E8 call at `address`, which must currently reach
            // `expectedTarget`.
            bool PatchCall(CallSite& site, uintptr_t address, uintptr_t expectedTarget, void* replacement)
            {
                uint8_t cur[5] = {};
                __try
                {
                    std::memcpy(cur, reinterpret_cast<const void*>(address), sizeof(cur));
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
                if (cur[0] != 0xE8)
                    return false;
                int32_t rel = 0;
                std::memcpy(&rel, cur + 1, sizeof(rel));
                if (address + 5 + static_cast<uintptr_t>(rel) != expectedTarget)
                    return false;

                std::memcpy(site.original, cur, sizeof(cur));
                site.address = address;
                const int32_t newRel =
                    static_cast<int32_t>(reinterpret_cast<uintptr_t>(replacement) - (address + 5));
                uint8_t patch[5] = { 0xE8, 0, 0, 0, 0 };
                std::memcpy(patch + 1, &newRel, sizeof(newRel));
                site.patched = HookEngine::WriteMemory(static_cast<uint32_t>(address), patch, sizeof(patch));
                return site.patched;
            }

            void RestoreCall(CallSite& site)
            {
                if (site.patched)
                {
                    HookEngine::WriteMemory(static_cast<uint32_t>(site.address), site.original,
                                            sizeof(site.original));
                    site.patched = false;
                }
            }

            // Trampolines stay allocated for any thread still inside them.
            void RollBack()
            {
                RestoreCall(g_OnePlayerSite);
                RestoreCall(g_LookupSite);
                RestoreCall(g_OwnerSite);
                if (g_NotifyDetour.target)
                    HookEngine::WriteMemory(static_cast<uint32_t>(g_NotifyDetour.target),
                                            g_NotifyDetour.original.data(), g_NotifyDetour.patchLen);
                if (g_DtorDetour.target)
                    HookEngine::WriteMemory(static_cast<uint32_t>(g_DtorDetour.target),
                                            g_DtorDetour.original.data(), g_DtorDetour.patchLen);
            }

            bool DoInstall()
            {
                // Literal names so patch_registration_tests can check them
                // against scripts/patches.json.
                const uint32_t sessionAddr = HookEngine::ResolveNamedAddress("Net::Session");
                const uint32_t localIdAddr = HookEngine::ResolveNamedAddress("GetLocalPlayerNetId");
                uint32_t dtorAddr = 0, ownerCallAddr = 0, ownerAddr = 0, notifyAddr = 0, takeAddr = 0;
                uint32_t lookupCallAddr = 0, findAddr = 0, oneLeftAddr = 0, oneLeftCallAddr = 0;
                const HookEngine::EngineRow rows[] = {
                    { "NetPlayerDtor", &dtorAddr },
                    { "NetPlayerDtorOwnerCall", &ownerCallAddr },
                    { "NetDistributedOwner", &ownerAddr },
                    { "NetNotifyNowHost", &notifyAddr },
                    { "NetTakeOwnership", &takeAddr },
                    { "NetTakeOwnershipLookupCall", &lookupCallAddr },
                    { "NetFindPlayer", &findAddr },
                    { "NetOnePlayerLeftCheck", &oneLeftAddr },
                    { "NetExecuteOnePlayerCall", &oneLeftCallAddr },
                };
                if (!sessionAddr || !localIdAddr || !HookEngine::BindEngineRows("HostLeave", rows))
                {
                    LogShimA(LogLevel::Warn, kComponent, "an address did not resolve; host leave fix not installed");
                    return false;
                }

                g_Owner = reinterpret_cast<FnOwner>(ownerAddr);
                g_TakeOwnership = reinterpret_cast<FnTakeOwnership>(takeAddr);
                g_FindPlayer = reinterpret_cast<FnFindPlayer>(findAddr);
                g_OnePlayerLeft = reinterpret_cast<FnOnePlayerLeft>(oneLeftAddr);
                g_LocalPlayerId = reinterpret_cast<FnLocalPlayerId>(localIdAddr);
                g_SessionPtrAddr = sessionAddr;

                if (!InstallInlineDetour32(g_DtorDetour, dtorAddr, reinterpret_cast<void*>(DtorHook),
                                           sizeof(kDtorStolen), kDtorStolen, sizeof(kDtorStolen), &g_DtorOriginal))
                {
                    LogShimA(LogLevel::Warn, kComponent, "NetPlayer destructor failed its byte guard; not installed");
                    g_DtorDetour = {};
                    return false;
                }
                if (!InstallInlineDetour32(g_NotifyDetour, notifyAddr, reinterpret_cast<void*>(NotifyHook),
                                           sizeof(kNotifyStolen), kNotifyStolen, sizeof(kNotifyStolen),
                                           &g_NotifyOriginal))
                {
                    LogShimA(LogLevel::Warn, kComponent, "NotifyNowHost failed its byte guard; not installed");
                    g_NotifyDetour = {};
                    RollBack();
                    return false;
                }
                if (!PatchCall(g_OwnerSite, ownerCallAddr, ownerAddr, reinterpret_cast<void*>(OwnerWrapper)) ||
                    !PatchCall(g_LookupSite, lookupCallAddr, findAddr, reinterpret_cast<void*>(LookupWrapper)) ||
                    !PatchCall(g_OnePlayerSite, oneLeftCallAddr, oneLeftAddr,
                               reinterpret_cast<void*>(OnePlayerWrapper)))
                {
                    LogShimA(LogLevel::Warn, kComponent, "a call site did not match; host leave fix rolled back");
                    RollBack();
                    return false;
                }

                LogShimA(LogLevel::Info, kComponent,
                         "installed: NetPlayer dtor 0x%08X, NotifyNowHost 0x%08X, session ptr 0x%08X",
                         dtorAddr, notifyAddr, sessionAddr);
                return true;
            }
        }

        void InstallHostLeaveIfPossible()
        {
            if (g_Done)
                return;
            g_Done = true;
            if (!IsEnabled())
            {
                LogShimA(LogLevel::Info, kComponent, "disabled ([Fixes] HostLeave = 0)");
                return;
            }
            DoInstall();
        }
    }
}
