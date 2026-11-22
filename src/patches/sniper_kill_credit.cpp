// sniper_kill_credit.cpp -- credit sniper kills on craft the shooter's
// machine owns (network games only).
//
// Mechanism: the E8 at 0x005D6FF7 in SniperShell::Hit (0x005D6E00) calls
// DistributedObject::IsLocal (0x004B9860, ecx = victim+0x18). It is redirected
// to a naked thunk that also passes the shell (Hit keeps `this` at [ebp-0xA0],
// stored at 0x005D6E15) to a cdecl helper. The helper returns the stock
// IsLocal result unchanged; the caller only consumes al (movzx edx,al at
// 0x005D6FFC) and reloads ecx, so eax/ecx/edx may be clobbered.
//
// For a local victim in a network game the helper does what the snipe
// receive handler (0x00573AE0) does on the victim owner's machine for a
// remote victim: test/set record flag 4, NetPlayer::RecordDeath(victimTeam,
// shooterTeam) (what DistributedObject::RecordDeath 0x004B9BA0 forwards to),
// then KillMessage(victimTeam, shooterTeam, 'S', victim == userObject). Hit
// has already called the victim's Snipe vfunc (+0x78), so it is not called
// again. Hit only runs on the shell owner's machine in a network game, which
// for a local victim is also the victim owner: no peer runs the receive
// handler for this kill (SendSnipe is skipped for local victims), so the
// credit happens exactly once.

#include "sniper_kill_credit.h"
#include "sniper_kill_credit_install.h"

#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "env_switch_table.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cstdint>

namespace BZROpenShim
{
    namespace SniperKillCredit
    {
        namespace
        {
            constexpr const char* kComponent = "SNIPECREDIT";

            using FnIsLocal = bool(__fastcall*)(void* distributedObject);
            using FnVirtualInt = int(__fastcall*)(void* self);
            using FnVirtualPtr = void*(__fastcall*)(void* self);
            using FnRecordDeath = void(__cdecl*)(int victimTeam, int killerTeam);
            using FnKillMessage = void(__cdecl*)(char victimTeam, char killerTeam, char type, char victimIsUser);

            std::atomic<bool> g_Done{ false };
            volatile long g_LogBudget = 32;

            FnIsLocal g_IsLocal = nullptr;
            FnRecordDeath g_RecordDeath = nullptr;
            FnKillMessage g_KillMessage = nullptr;
            const volatile uint8_t* g_IsNetGame = nullptr;
            void* const volatile* g_UserObject = nullptr;

            struct Snapshot
            {
                uint8_t* record = nullptr;
                int victimTeam = 0;
                int shooterTeam = 0;
                bool victimIsUser = false;
            };

            template <typename Fn>
            Fn VirtualAt(void* self, uint32_t offset)
            {
                const uintptr_t vtbl = *reinterpret_cast<const volatile uintptr_t*>(self);
                return reinterpret_cast<Fn>(*reinterpret_cast<const volatile uintptr_t*>(vtbl + offset));
            }

            // Reads the shooter, the victim record and both teams with the
            // same vfuncs the receive handler calls (record at 0x00573B33,
            // GetTeam at 0x00573B90). Returns false when a read faults.
            bool ReadSnapshot(void* victimDo, void* shell, Inputs& in, Snapshot& snap)
            {
                __try
                {
                    uint8_t* const shellBytes = static_cast<uint8_t*>(shell);
                    uint8_t* const ownerObj =
                        *reinterpret_cast<uint8_t* const volatile*>(shellBytes + kShellOwnerObjOffset);
                    uint8_t* const shooter = ownerObj
                        ? *reinterpret_cast<uint8_t* const volatile*>(ownerObj + kObjGameObjectOffset)
                        : nullptr;
                    // Stock skips SendSnipe only for a null owner (0x005D6FC7);
                    // an owner with no GameObject is sent with killer team 0
                    // (0x00573BEA..0x00573C06): death counted, no kill.
                    in.haveShooter = ownerObj != nullptr;
                    if (!ownerObj)
                        return true;

                    if (shooter)
                    {
                        void* const shooterDo = shooter + kDistributedObjectOffset;
                        snap.shooterTeam = VirtualAt<FnVirtualInt>(shooterDo, kDoVtblGetTeam)(shooterDo);
                    }
                    snap.record =
                        static_cast<uint8_t*>(VirtualAt<FnVirtualPtr>(victimDo, kDoVtblGetRecord)(victimDo));
                    if (!snap.record)
                        return false;
                    in.recordFlags = *reinterpret_cast<const volatile uint32_t*>(snap.record + kRecordFlagsOffset);
                    snap.victimTeam = VirtualAt<FnVirtualInt>(victimDo, kDoVtblGetTeam)(victimDo);
                    void* const victimGo = static_cast<uint8_t*>(victimDo) - kDistributedObjectOffset;
                    snap.victimIsUser = victimGo == *g_UserObject;
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool MarkRecorded(uint8_t* record)
            {
                __try
                {
                    volatile uint32_t* flags = reinterpret_cast<volatile uint32_t*>(record + kRecordFlagsOffset);
                    *flags = *flags | kDeathRecordedFlag;
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool ReadNetGame()
            {
                __try
                {
                    return *g_IsNetGame != 0;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            int __cdecl IsLocalGate(void* victimDo, void* shell)
            {
                const bool local = g_IsLocal(victimDo);
                if (!local || !shell)
                    return local ? 1 : 0;

                Inputs in;
                in.victimLocal = true;
                in.netGame = ReadNetGame();
                Snapshot snap;
                if (in.netGame)
                    in.readOk = ReadSnapshot(victimDo, shell, in, snap);

                const Decision decision = Decide(in);
                if (decision == Decision::Credit)
                {
                    if (!MarkRecorded(snap.record))
                        return 1;
                    g_RecordDeath(snap.victimTeam, snap.shooterTeam);
                    g_KillMessage(static_cast<char>(snap.victimTeam), static_cast<char>(snap.shooterTeam),
                                  kSnipeKillType, snap.victimIsUser ? 1 : 0);
                }
                if (decision != Decision::NotNetGame && InterlockedDecrement(&g_LogBudget) >= 0)
                {
                    LogShimA(LogLevel::Info, kComponent,
                             "local snipe victim=%p team=%d shooterTeam=%d user=%d -> %s",
                             victimDo, snap.victimTeam, snap.shooterTeam, snap.victimIsUser ? 1 : 0,
                             DecisionName(decision));
                }
                return 1;
            }

            // Replaces `call IsLocal` at 0x005D6FF7: ecx = victim DO, the shell
            // is Hit's local at [ebp-0xA0]. Returns IsLocal's bool in eax.
            __declspec(naked) void IsLocalThunk()
            {
                __asm
                {
                    push dword ptr [ebp - 0xA0]
                    push ecx
                    call IsLocalGate
                    add esp, 8
                    ret
                }
            }

            bool Fail(const char* what)
            {
                LogShimA(LogLevel::Warn, kComponent, "%s; leaving stock SniperShell::Hit", what);
                return false;
            }

            bool IsEnabled()
            {
                bool enabled = true;
                static const EnvSwitches::EnvSwitch rows[] = {
                    { &enabled, EnvSwitches::Kind::KillSwitch,
                      "OPENSHIM_DISABLE_SNIPER_KILL_CREDIT", "BZR_DISABLE_SNIPER_KILL_CREDIT" },
                };
                EnvSwitches::Apply(rows, EnvFlagEnabled);
                return enabled;
            }

            bool DoInstall()
            {
                uint32_t shellLocal = 0, callSite = 0, isLocal = 0, recordDeath = 0, killMessage = 0, netGame = 0;
                const HookEngine::EngineRow rows[] = {
                    { "SniperShellHitShellLocal", &shellLocal },
                    { "SniperShellHitIsLocalCall", &callSite },
                    { "DistributedObjectIsLocal", &isLocal },
                    { "NetPlayerRecordDeath", &recordDeath },
                    { "KillMessage", &killMessage },
                    { "IsNetGameFlag", &netGame },
                };
                if (!HookEngine::BindEngineRows("Sniper kill credit", rows))
                    return Fail("an engine address failed its byte guard");
                const uint32_t userObject = HookEngine::ResolveNamedAddress("GameObject::userObject");
                if (userObject == 0)
                    return Fail("GameObject::userObject did not resolve");

                g_IsLocal = reinterpret_cast<FnIsLocal>(static_cast<uintptr_t>(isLocal));
                g_RecordDeath = reinterpret_cast<FnRecordDeath>(static_cast<uintptr_t>(recordDeath));
                g_KillMessage = reinterpret_cast<FnKillMessage>(static_cast<uintptr_t>(killMessage));
                g_IsNetGame = reinterpret_cast<const volatile uint8_t*>(static_cast<uintptr_t>(netGame));
                g_UserObject = reinterpret_cast<void* const volatile*>(static_cast<uintptr_t>(userObject));

                if (!Hooks::RedirectCallTarget(callSite, isLocal, reinterpret_cast<uintptr_t>(&IsLocalThunk)))
                    return Fail("the IsLocal call does not target DistributedObject::IsLocal");

                LogShimA(LogLevel::Info, kComponent,
                         "installed: call=0x%08X isLocal=0x%08X recordDeath=0x%08X killMessage=0x%08X",
                         callSite, isLocal, recordDeath, killMessage);
                return true;
            }
        }

        void InstallSniperKillCreditIfPossible()
        {
            if (g_Done.exchange(true))
                return;
            if (!IsEnabled())
            {
                LogShimA(LogLevel::Info, kComponent, "disabled ([Fixes] SniperKillCredit = 0)");
                return;
            }
            DoInstall();
        }
    }
}
