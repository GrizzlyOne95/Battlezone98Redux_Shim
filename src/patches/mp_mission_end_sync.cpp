// mp_mission_end_sync.cpp -- carry "the mission is over" from the host to the
// guests of a multiplayer session.
//
// ============================================================================
// THE DEFECT (Redux 2.2.301, exact GOG image)
// ============================================================================
//
// The Lua SucceedMission / FailMission callers (0x0045BE60 / 0x0045BE30) both
// funnel into AiMission::End, 0x0045DAF0:
//
//   __thiscall(AiMission* this, float shutdownTime, const char* name,
//              char failed), ret 0xC
//     sets this+0x10 done = 1, this+0x14 shutdownTime, this+0x18 failed and
//     copies name into this+0x19 (13 bytes).
//
// No network message carries any of that. A mission script runs on every peer,
// but missions commonly decide success or failure from host-only state, so only
// the host's End ever runs: the guests keep playing a finished mission forever.
//
// ============================================================================
// THE FIX
// ============================================================================
//
// Two inline detours (both or neither):
//
//   AiMission::End 0x0045DAF0 (host side). Run the original first, then, when
//     this call is not itself a remote application, a session is in game
//     (*(int*)(*(0x00917F48) + 8) == 4) and IsHost() (0x00572A60) is true,
//     broadcast through 0x00575890(buf, 21, 1, 1) -- the arguments the Lua Send
//     binding uses for a reliable broadcast:
//
//         'M' 'E'  version=1  failed  float shutdownTime  char name[13]
//
//   Net dispatcher 0x00570500 (guest side), shared with the other OpenShim
//     messages through net_tag_dispatch.cpp, which owns the one detour. The
//     tag is the first two payload bytes as a little-endian ushort, 0x454D.
//     A well-formed message (len >= 21, version 1) is consumed by the
//     registered handler and never reaches the stock switch; anything else
//     calls the original unchanged. Stock treats an unknown tag as a silent
//     fall-through, so an unpatched peer simply ignores the packet.
//
// A received message is applied only when it comes from the host
// (0x0056FC40, the check the stock 'PP' / 'GA' cases use), not from this
// machine's own player id (0x00572D90), and the current mission
// (*0x00915694) exists and is not already done. It then calls the original
// End with a re-entrancy guard set, so the host-side hook does not echo it.
//
// Every address is a named row in scripts/patches.json with a byte guard.

#include "mp_mission_end_sync_install.h"

#include "bzr_options_ui.h"
#include "env_switch_table.h"
#include "hook_engine.h"
#include "net_tag_dispatch.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace MissionEndSync
    {
        namespace
        {
            constexpr const char* kComponent = "MISSIONEND";

            constexpr uint8_t kTag0 = 'M';
            constexpr uint8_t kTag1 = 'E';
            constexpr uint16_t kTag = 0x454D; // 'M','E' read little-endian
            constexpr uint8_t kVersion = 1;
            constexpr unsigned kNameLen = 13;
            constexpr unsigned kPacketLen = 2 + 1 + 1 + 4 + kNameLen; // 21
            constexpr int kSessionInGame = 4;
            constexpr uintptr_t kSessionStateOffset = 8;
            constexpr uintptr_t kMissionDoneOffset = 0x10;

            // thiscall: ecx = this, callee pops the rest.
            using FnEnd = void(__thiscall*)(void* mission, float shutdownTime, const char* name, char failed);
            using FnBroadcastSend = char(__cdecl*)(const void* buf, unsigned len, int p3, char p4);
            using FnIsHost = unsigned char(__cdecl*)();
            using FnIsPlayerHost = unsigned char(__cdecl*)(int playerId);
            using FnLocalPlayerId = uint16_t(__cdecl*)();

            // Prologues (whole instructions, no relative operands).
            constexpr uint8_t kEndStolen[9] = { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x14, 0x89, 0x4D, 0xF8 };

            std::atomic<bool> g_Done{ false };
            InlineDetour32 g_EndDetour = {};
            void* volatile g_EndOriginal = nullptr;

            FnBroadcastSend g_Send = nullptr;
            FnIsHost g_IsHost = nullptr;
            FnIsPlayerHost g_IsPlayerHost = nullptr;
            FnLocalPlayerId g_LocalPlayerId = nullptr;
            uintptr_t g_SessionPtrAddr = 0;
            uintptr_t g_MissionPtrAddr = 0;

            // Set while this thread is applying a received message.
            thread_local bool t_Applying = false;

            bool IsEnabled()
            {
                bool enabled = true;
                static const EnvSwitches::EnvSwitch rows[] = {
                    { &enabled, EnvSwitches::Kind::KillSwitch,
                      "OPENSHIM_DISABLE_MP_MISSION_END_SYNC", "BZR_DISABLE_MP_MISSION_END_SYNC" },
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

            bool SessionInGame()
            {
                uint32_t session = 0;
                uint32_t state = 0;
                return SafeReadU32(g_SessionPtrAddr, session) && session != 0 &&
                       SafeReadU32(session + kSessionStateOffset, state) &&
                       static_cast<int>(state) == kSessionInGame;
            }

            bool SafeIsHost()
            {
                __try
                {
                    return g_IsHost() != 0;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool SafeIsPlayerHost(unsigned id)
            {
                __try
                {
                    return g_IsPlayerHost(static_cast<int>(static_cast<short>(id))) != 0;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            char SafeSend(const uint8_t* packet)
            {
                __try
                {
                    return g_Send(packet, kPacketLen, 1, 1);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return 0;
                }
            }

            // Host side: AiMission::End.
            void __fastcall EndHook(void* mission, void* /*edx*/, float shutdownTime, const char* name, char failed)
            {
                const FnEnd original = reinterpret_cast<FnEnd>(g_EndOriginal);
                if (original)
                    original(mission, shutdownTime, name, failed);

                if (t_Applying || !SessionInGame() || !SafeIsHost())
                    return;

                uint8_t packet[kPacketLen] = {};
                packet[0] = kTag0;
                packet[1] = kTag1;
                packet[2] = kVersion;
                packet[3] = failed ? 1 : 0;
                std::memcpy(packet + 4, &shutdownTime, sizeof(float));
                if (name)
                {
                    // Bounded copy; the engine's own name field holds 13 bytes.
                    for (unsigned i = 0; i < kNameLen && name[i]; ++i)
                        packet[8 + i] = static_cast<uint8_t>(name[i]);
                }

                const char sent = SafeSend(packet);
                LogShimA(LogLevel::Info, kComponent,
                         // The send's return is not a delivery flag: live run
                         // mpbugs-me-fixed-2 got 0 and the guest applied it.
                         "host mission end broadcast: failed=%d time=%.2f name=\"%.13s\" sendRet=%d",
                         failed ? 1 : 0, static_cast<double>(shutdownTime),
                         reinterpret_cast<const char*>(packet + 8), static_cast<int>(sent));
            }

            // Guest side: apply a received mission-end message.
            void ApplyMessage(unsigned senderId, const unsigned char* buf)
            {
                const unsigned char failed = buf[3];
                float shutdownTime = 0.0f;
                std::memcpy(&shutdownTime, buf + 4, sizeof(float));
                char name[kNameLen + 1] = {};
                std::memcpy(name, buf + 8, kNameLen);
                name[kNameLen] = '\0';

                const uint16_t localId = g_LocalPlayerId ? g_LocalPlayerId() : 0;
                if ((senderId & 0xFFFF) == localId)
                {
                    LogShimA(LogLevel::Info, kComponent, "ignored mission end from own player id %u", senderId & 0xFFFF);
                    return;
                }
                if (!SafeIsPlayerHost(senderId))
                {
                    LogShimA(LogLevel::Info, kComponent, "ignored mission end from non-host player %u", senderId & 0xFFFF);
                    return;
                }
                uint32_t mission = 0;
                if (!SafeReadU32(g_MissionPtrAddr, mission) || mission == 0)
                {
                    LogShimA(LogLevel::Info, kComponent, "ignored mission end: no current mission");
                    return;
                }
                uint8_t done = 0;
                if (!SafeReadU8(mission + kMissionDoneOffset, done))
                {
                    LogShimA(LogLevel::Info, kComponent, "ignored mission end: mission 0x%08X unreadable", mission);
                    return;
                }
                if (done)
                {
                    LogShimA(LogLevel::Info, kComponent, "ignored mission end: mission already done");
                    return;
                }

                const FnEnd original = reinterpret_cast<FnEnd>(g_EndOriginal);
                if (!original)
                    return;
                t_Applying = true;
                original(reinterpret_cast<void*>(static_cast<uintptr_t>(mission)), shutdownTime, name,
                         failed ? 1 : 0);
                t_Applying = false;
                LogShimA(LogLevel::Info, kComponent,
                         "applied host mission end: failed=%d time=%.2f name=\"%s\" from player %u",
                         failed ? 1 : 0, static_cast<double>(shutdownTime), name, senderId & 0xFFFF);
            }

            // Registered with NetTagDispatch; true if the message was consumed.
            bool ReceiveHandler(unsigned senderId, const unsigned char* buf, unsigned len)
            {
                if (len >= kPacketLen && buf[2] == kVersion)
                {
                    ApplyMessage(senderId, buf);
                    return true;
                }
                return false;
            }

            bool DoInstall()
            {
                // Literal names so patch_registration_tests can check them
                // against scripts/patches.json.
                const uint32_t endAddr = HookEngine::ResolveNamedAddress("AiMission::End");
                const uint32_t sendAddr = HookEngine::ResolveNamedAddress("Net::BroadcastSend");
                const uint32_t sessionAddr = HookEngine::ResolveNamedAddress("Net::Session");
                const uint32_t isPlayerHostAddr = HookEngine::ResolveNamedAddress("Net::IsPlayerHost");
                const uint32_t localIdAddr = HookEngine::ResolveNamedAddress("GetLocalPlayerNetId");
                uint32_t isHostAddr = 0;
                uint32_t missionAddr = 0;
                const HookEngine::EngineRow rows[] = {
                    { "IsHost", &isHostAddr },
                    { "CurrentAiMission", &missionAddr },
                };
                if (!endAddr || !sendAddr || !sessionAddr || !isPlayerHostAddr || !localIdAddr ||
                    !HookEngine::BindEngineRows("MissionEndSync", rows))
                {
                    LogShimA(LogLevel::Warn, kComponent, "an address did not resolve; mission end sync not installed");
                    return false;
                }

                g_Send = reinterpret_cast<FnBroadcastSend>(sendAddr);
                g_IsHost = reinterpret_cast<FnIsHost>(isHostAddr);
                g_IsPlayerHost = reinterpret_cast<FnIsPlayerHost>(isPlayerHostAddr);
                g_LocalPlayerId = reinterpret_cast<FnLocalPlayerId>(localIdAddr);
                g_SessionPtrAddr = sessionAddr;
                g_MissionPtrAddr = missionAddr;

                if (!InstallInlineDetour32(g_EndDetour, endAddr, reinterpret_cast<void*>(EndHook),
                                           sizeof(kEndStolen), kEndStolen, sizeof(kEndStolen),
                                           &g_EndOriginal))
                {
                    LogShimA(LogLevel::Warn, kComponent,
                             "AiMission::End at 0x%08X failed its byte guard; mission end sync not installed", endAddr);
                    return false;
                }
                if (!NetTagDispatch::RegisterNetTagHandler(kTag, &ReceiveHandler))
                {
                    // Roll back the first detour: half the pair would send
                    // messages nobody here can read, or the reverse. The
                    // trampoline stays allocated for any thread still in it.
                    const bool restored = HookEngine::WriteMemory(static_cast<uint32_t>(g_EndDetour.target),
                                                                  g_EndDetour.original.data(), g_EndDetour.patchLen);
                    LogShimA(LogLevel::Warn, kComponent,
                             "Net::Receive handler not registered; mission end sync not installed (%s)",
                             restored ? "AiMission::End hook rolled back" : "ROLLBACK FAILED");
                    return false;
                }

                LogShimA(LogLevel::Info, kComponent,
                         "installed: AiMission::End 0x%08X, send 0x%08X, session ptr 0x%08X",
                         endAddr, sendAddr, sessionAddr);
                return true;
            }
        }

        void InstallMissionEndSyncIfPossible()
        {
            if (g_Done.exchange(true))
                return;
            if (!IsEnabled())
            {
                LogShimA(LogLevel::Info, kComponent, "disabled ([Fixes] MissionEndSync = 0)");
                return;
            }
            DoInstall();
        }
    }
}
