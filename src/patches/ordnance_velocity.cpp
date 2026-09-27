// ordnance_velocity.cpp
// BZR Open Shim - ordnance velocity inheritance (constants, state, detours
// and reconcile), split out of bzr_hooks.cpp. Configured from its shared
// initializer; shared helpers come from bzr_hooks_internal.h.
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "patcher.h"
#include "shim_log.h"

#include <Windows.h>

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace BZROpenShim
{
    namespace Hooks
    {
        // --- Ordnance velocity inheritance -----------------------------------
        //
        // Stock Redux gives every projectile exactly the muzzle velocity its
        // ordnance class declares and nothing else. A shot fired from a craft
        // doing 40 m/s leaves the barrel at the same world velocity as one
        // fired from a standstill, so ordnance appears to fall behind a moving
        // shooter, and the cannon's own lead solution is computed against a
        // target velocity that never accounts for the shooter's motion.
        //
        // Traced statically against the shipped GOG v2.2.301 executable
        // (battlezone98redux.exe, ImageBase 0x00400000). Three sites:
        //
        //   Ordnance::Init (0x00480340, __thiscall, this stored to [ebp-0x20]
        //   by the prologue at 0x00480350):
        //     0x004803BD  the spawn velocity vec3 is built into the frame
        //                 locals [ebp-0x10] / [ebp-0x0C] / [ebp-0x08]
        //     0x004803CE  eax := this + 0x30  (kOrdnanceVelocityOffset)
        //     0x004803D4  mov ecx,[ebp-0x10]        <-- 8-byte detour site
        //                 mov [eax],ecx
        //                 mov edx,[ebp-0x0C]
        //     0x004803DC  ...the rest of the vec3 store
        //     0x004803E8  nominal speed [+0x20] is then taken from the ordnance
        //                 CLASS field [class+0x54] -- NOT from the vector we
        //                 just changed -- and [+0x24] is its reciprocal. Both
        //                 must therefore be left alone here, unlike the magnet
        //                 mine and shield tower paths further down this file,
        //                 which recompute them because they change velocity
        //                 after the object is fully built.
        //
        //   Cannon lead/TLI solve (0x0048F5E0, __thiscall, this at [ebp-0x20]):
        //     0x0048F62D  movss xmm0,[ebp-0x44]         target speed
        //     0x0048F632  comiss xmm0,[0x008A2538]      the constant is 0.1f
        //     0x0048F639  jbe <bail>                <-- 6-byte NOP site
        //     0x0048F642  call ...                      returns target velocity
        //     0x0048F647  ...copied into [ebp-0x1C] / [ebp-0x18] / [ebp-0x14]
        //     0x0048F658  mov eax,[ebp-0x20]        <-- 6-byte detour site
        //                 mov ecx,[eax+0x0C]
        //
        // The shooter chain used by the spawn site was read out of the ordnance
        // neighbourhood itself (0x0047F000..0x00482000), where [ordnance+0xD8]
        // is dereferenced thirteen times -- at 0x00480720 and 0x004808CC it is
        // pushed as the owner pointer alongside the ordnance transform, which
        // is the shape of an obj76 being handed to the effect and damage calls
        // -- and [ordnance+0xCC] is never touched at all:
        //
        //     Ordnance*  + 0xD8   -> shooter obj76
        //     obj76      + 0x8C   -> GameObject* shooter (kObj76GameObjectOffset)
        //     GameObject + 0x12C  -> shooter world velocity vec3
        //
        // The lead-tolerance NOP matters because the stock gate skips the whole
        // lead solve for a target moving slower than 0.1 m/s. Once the
        // shooter's own velocity is subtracted from the target velocity a
        // stationary target still needs a lead solution, so the gate has to
        // come out for the compensation to be observable at all. It is only
        // ever applied while the compensation is actually running: on its own
        // it would make a moving shooter's aim worse, not better.
        constexpr uintptr_t kOrdnanceSpawnVelocityAddr = 0x004803D4;
        constexpr size_t kOrdnanceSpawnVelocityPatchLen = 8;
        // mov ecx,[ebp-0x10] ; mov [eax],ecx ; mov edx,[ebp-0x0C]
        constexpr uint8_t kOrdnanceSpawnVelocityExpected[kOrdnanceSpawnVelocityPatchLen] =
        {
            0x8B, 0x4D, 0xF0, 0x89, 0x08, 0x8B, 0x55, 0xF4
        };

        constexpr uintptr_t kCannonLeadVelocityAddr = 0x0048F658;
        constexpr size_t kCannonLeadVelocityPatchLen = 6;
        // mov eax,[ebp-0x20] ; mov ecx,[eax+0x0C]
        constexpr uint8_t kCannonLeadVelocityExpected[kCannonLeadVelocityPatchLen] =
        {
            0x8B, 0x45, 0xE0, 0x8B, 0x48, 0x0C
        };

        constexpr uintptr_t kCannonLeadToleranceAddr = 0x0048F639;
        constexpr size_t kCannonLeadTolerancePatchLen = 6;
        // jbe 0x0048F82F -- the "target is barely moving, skip the lead solve"
        // branch guarded by the 0.1f at 0x008A2538.
        constexpr uint8_t kCannonLeadToleranceExpected[kCannonLeadTolerancePatchLen] =
        {
            0x0F, 0x86, 0xF0, 0x01, 0x00, 0x00
        };
        constexpr uint8_t kCannonLeadTolerancePatched[kCannonLeadTolerancePatchLen] =
        {
            0x90, 0x90, 0x90, 0x90, 0x90, 0x90
        };

        // Host frame offsets. Both sites are entered by a JMP written over
        // whole instructions, so EBP still addresses the host frame.
        constexpr long kOrdnanceSpawnThisFrameOffset = -0x20;
        constexpr long kOrdnanceSpawnVelocityFrameOffset = -0x10;
        constexpr long kCannonLeadThisFrameOffset = -0x20;
        constexpr long kCannonLeadVelocityFrameOffset = -0x1C;

        // Ordnance::Init stores its creator obj76 at +0xD8; both the team-filter
        // and velocity-inheritance paths use the shared constant above.
        // Unlike the ordnance chain, this offset could NOT be corroborated
        // statically -- the only +0x18 dereferences in the lead function are on
        // an argument ([ebp+0x0C]), and every +0x8C access in
        // 0x0048E000..0x00492000 is a float rather than a pointer hop. It is
        // therefore proven at runtime by ValidateCannonOwnerChain below instead
        // of being trusted.
        constexpr size_t kCannonOwnerObjOffset = 0x18;

        // Runtime verdict on kCannonOwnerObjOffset.
        constexpr long kCannonOwnerChainUnprobed = -1;
        constexpr long kCannonOwnerChainRejected = 0;
        constexpr long kCannonOwnerChainAccepted = 1;
        // The reconcile tick retries installation; Steam decrypts .text in
        // stages, so an early attempt can legitimately match nothing.
        constexpr int kOrdnanceVelocityDetourMaxAttempts = 200;

        // Ordnance velocity inheritance. Desired state starts from the INI
        // baseline; the refresh gate keeps it out of multiplayer.
        bool g_OrdnanceVelocityInheritanceEnabled = false;
        bool g_OrdnanceVelocityInheritanceBaselineEnabled = false;
        // Sampled by the two naked thunks on every shot. The detours stay
        // installed for the process lifetime and simply do nothing while this
        // is 0, so the multiplayer gate never has to rewrite .text on a hot
        // path -- only the lead-tolerance NOP is written and reverted.
        static volatile long g_OrdnanceVelocityInheritanceActive = 0;
        static InlineDetour32 g_OrdnanceSpawnVelocityDetour = {};
        static InlineDetour32 g_CannonLeadVelocityDetour = {};
        // Resume targets read by the thunks. Held separately from the detour
        // records so the tail JMP is one indirect load that clobbers nothing.
        static void* g_OrdnanceSpawnVelocityResume = nullptr;
        static void* g_CannonLeadVelocityResume = nullptr;
        static bool g_OrdnanceSpawnVelocityDetourInstalled = false;
        static bool g_CannonLeadVelocityDetourInstalled = false;
        static bool g_OrdnanceVelocityDetourFailureLogged = false;
        static int g_OrdnanceVelocityDetourAttempts = 0;
        static bool g_CannonLeadTolerancePatchActive = false;
        static volatile long g_CannonOwnerChainState = kCannonOwnerChainUnprobed;
        // Set by the sim thread when the chain fails validation, consumed by
        // the next reconcile tick. The thunk must not touch page protection.
        static volatile long g_CannonOwnerChainRejectPending = 0;
        // What each arm actually did. A zero here after a session spent
        // shooting means the arm never engaged, not that it made no difference.
        static volatile long g_OrdnanceSpawnVelocityAppliedCount = 0;
        static volatile long g_CannonLeadVelocityAppliedCount = 0;

        // --- Ordnance velocity inheritance ------------------------------------
        // See the site trace next to kOrdnanceSpawnVelocityAddr above.

        // Defined further down this file; both thunk helpers need it.

        static bool WriteCannonLeadToleranceBytes(const uint8_t* bytes)
        {
            auto* target = reinterpret_cast<uint8_t*>(kCannonLeadToleranceAddr);
            DWORD oldProtect = 0;
            if (!VirtualProtect(target,
                                kCannonLeadTolerancePatchLen,
                                PAGE_EXECUTE_READWRITE,
                                &oldProtect))
            {
                Log(L"[ORDVEL] Lead-tolerance VirtualProtect failed at 0x%08X\n",
                    static_cast<uint32_t>(kCannonLeadToleranceAddr));
                return false;
            }

            memcpy(target, bytes, kCannonLeadTolerancePatchLen);
            FlushInstructionCache(GetCurrentProcess(), target, kCannonLeadTolerancePatchLen);

            DWORD restoreProtect = 0;
            VirtualProtect(target, kCannonLeadTolerancePatchLen, oldProtect, &restoreProtect);
            return true;
        }

        // Reconciles the lead-tolerance NOP with the desired state. Guarded by
        // the exact expected/patched bytes so it no-ops on any build that does
        // not match (for example Steam, which relocates these functions).
        static void ApplyCannonLeadTolerancePatch(bool wantActive)
        {
            if (wantActive == g_CannonLeadTolerancePatchActive)
                return;

            if (wantActive)
            {
                if (!ExpectedBytesMatchAt(kCannonLeadToleranceAddr,
                                          kCannonLeadToleranceExpected,
                                          sizeof(kCannonLeadToleranceExpected)))
                {
                    return;
                }
                if (WriteCannonLeadToleranceBytes(kCannonLeadTolerancePatched))
                {
                    g_CannonLeadTolerancePatchActive = true;
                    Log(L"[ORDVEL] Applied lead-tolerance bypass at 0x%08X (SP-only)\n",
                        static_cast<uint32_t>(kCannonLeadToleranceAddr));
                }
            }
            else
            {
                if (ExpectedBytesMatchAt(kCannonLeadToleranceAddr,
                                         kCannonLeadTolerancePatched,
                                         sizeof(kCannonLeadTolerancePatched)))
                {
                    if (WriteCannonLeadToleranceBytes(kCannonLeadToleranceExpected))
                    {
                        g_CannonLeadTolerancePatchActive = false;
                        Log(L"[ORDVEL] Reverted lead-tolerance bypass at 0x%08X\n",
                            static_cast<uint32_t>(kCannonLeadToleranceAddr));
                    }
                }
                else
                {
                    // Bytes are not ours; treat as inactive without writing.
                    g_CannonLeadTolerancePatchActive = false;
                }
            }
        }

        // Called from the sim thread the first time the cannon chain does not
        // hold up. Only records the verdict -- pulling the NOP needs page
        // protection changes, which the reconcile tick does instead.
        static void RejectCannonOwnerChain()
        {
            if (InterlockedExchange(&g_CannonOwnerChainState, kCannonOwnerChainRejected) ==
                kCannonOwnerChainRejected)
            {
                return;
            }
            InterlockedExchange(&g_CannonOwnerChainRejectPending, 1);
        }

        // Walks Cannon+0x18 -> obj76+0x8C and requires the endpoint to pass
        // TryGetGameObjectFieldBase, which proves identity by checking the
        // object's vtable slot really resolves to GameObject::GetTeam rather
        // than merely pointing at committed memory. Run once; the offset is
        // either right for this build or it is not.
        static bool ValidateCannonOwnerChain(void* cannon, uint8_t*& outShooterBase)
        {
            outShooterBase = nullptr;
            if (!cannon)
                return false;

            void* ownerObj76 = nullptr;
            __try
            {
                ownerObj76 = *reinterpret_cast<void* const*>(
                    reinterpret_cast<const uint8_t*>(cannon) + kCannonOwnerObjOffset);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }

            void* owner = nullptr;
            if (!TryGetGameObjectFromObj76(ownerObj76, owner))
                return false;

            return TryGetGameObjectFieldBase(owner, outShooterBase);
        }

        // Spawn site helper. The ordnance -> obj76 -> GameObject chain here is
        // the one the engine itself walks throughout this neighbourhood, so
        // SEH around the loads is the same guard TryGetOrdnanceOwner relies on;
        // no per-shot VirtualQuery is warranted.
        static void __cdecl ApplyOrdnanceSpawnVelocity(uint8_t* frame)
        {
            if (!frame || g_OrdnanceVelocityInheritanceActive == 0)
                return;

            __try
            {
                void* ordnance = *reinterpret_cast<void* const*>(
                    frame + kOrdnanceSpawnThisFrameOffset);
                if (!ordnance)
                    return;

                void* shooterObj76 = *reinterpret_cast<void* const*>(
                    reinterpret_cast<const uint8_t*>(ordnance) + kOrdnanceOwnerObjOffset);
                void* shooter = nullptr;
                if (!TryGetGameObjectFromObj76(shooterObj76, shooter))
                    return;

                const auto* shooterVelocity = reinterpret_cast<const float*>(
                    reinterpret_cast<const uint8_t*>(shooter) + kGameObjectVelocityOffset);
                auto* spawnVelocity = reinterpret_cast<float*>(
                    frame + kOrdnanceSpawnVelocityFrameOffset);

                // Compute all three before storing any, so a non-finite
                // component cannot leave the vector half-updated.
                float inherited[3];
                for (int i = 0; i < 3; ++i)
                {
                    inherited[i] = spawnVelocity[i] + shooterVelocity[i];
                    if (!std::isfinite(inherited[i]))
                        return;
                }

                // Nominal speed [+0x20] and its reciprocal [+0x24] are written
                // from the ordnance class at 0x004803E8, two instructions after
                // this store, and are deliberately not touched here.
                memcpy(spawnVelocity, inherited, sizeof(inherited));
                InterlockedIncrement(&g_OrdnanceSpawnVelocityAppliedCount);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        // Cannon lead helper. Subtracts the shooter's own velocity from the
        // target velocity the solver is about to use, which is what keeps a
        // moving shooter's lead correct now that its shots carry that velocity.
        static void __cdecl ApplyCannonLeadVelocity(uint8_t* frame)
        {
            if (!frame || g_OrdnanceVelocityInheritanceActive == 0)
                return;
            if (g_CannonOwnerChainState == kCannonOwnerChainRejected)
                return;

            __try
            {
                void* cannon = *reinterpret_cast<void* const*>(
                    frame + kCannonLeadThisFrameOffset);
                if (!cannon)
                    return;

                uint8_t* shooterBase = nullptr;
                if (g_CannonOwnerChainState == kCannonOwnerChainUnprobed)
                {
                    if (!ValidateCannonOwnerChain(cannon, shooterBase))
                    {
                        RejectCannonOwnerChain();
                        return;
                    }
                    InterlockedExchange(&g_CannonOwnerChainState, kCannonOwnerChainAccepted);
                }
                else
                {
                    // Layout already proven for this build; take the cheap path.
                    void* ownerObj76 = *reinterpret_cast<void* const*>(
                        reinterpret_cast<const uint8_t*>(cannon) + kCannonOwnerObjOffset);
                    void* owner = nullptr;
                    if (!TryGetGameObjectFromObj76(ownerObj76, owner))
                        return;
                    shooterBase = reinterpret_cast<uint8_t*>(owner);
                }

                const auto* shooterVelocity = reinterpret_cast<const float*>(
                    shooterBase + kGameObjectVelocityOffset);
                auto* targetVelocity = reinterpret_cast<float*>(
                    frame + kCannonLeadVelocityFrameOffset);

                float relative[3];
                for (int i = 0; i < 3; ++i)
                {
                    relative[i] = targetVelocity[i] - shooterVelocity[i];
                    if (!std::isfinite(relative[i]))
                        return;
                }

                memcpy(targetVelocity, relative, sizeof(relative));
                InterlockedIncrement(&g_CannonLeadVelocityAppliedCount);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                RejectCannonOwnerChain();
            }
        }

        // Both detour sites are entered by a 5-byte JMP written over whole
        // instructions, so no prologue of ours has run: EBP still addresses the
        // host frame and every value the helper needs hangs off it.
        //
        // PUSHAD/PUSHFD covers the integer set and flags. XMM0-7 need no saving
        // here: the x86 cdecl ABI already makes them caller-saved, and at both
        // sites the nearest preceding instruction that could have set one is a
        // CALL (0x004803B5 and 0x0048F642 respectively) followed by nothing but
        // integer moves, so the host cannot have live XMM state across us. The
        // x87 stack is untouched because the helpers are ordinary C++.
        static __declspec(naked) void OrdnanceSpawnVelocityThunk()
        {
            __asm
            {
                pushad
                pushfd
                push ebp
                call ApplyOrdnanceSpawnVelocity
                add  esp, 4
                popfd
                popad
                jmp  dword ptr [g_OrdnanceSpawnVelocityResume]
            }
        }

        static __declspec(naked) void CannonLeadVelocityThunk()
        {
            __asm
            {
                pushad
                pushfd
                push ebp
                call ApplyCannonLeadVelocity
                add  esp, 4
                popfd
                popad
                jmp  dword ptr [g_CannonLeadVelocityResume]
            }
        }

        // Installs the two inline detours. Retried by the reconcile tick until
        // it succeeds: on Steam the .text bytes are decrypted in stages, so a
        // first attempt during startup can legitimately find nothing to match.
        static void EnsureOrdnanceVelocityDetours()
        {
            if (g_OrdnanceSpawnVelocityDetourInstalled && g_CannonLeadVelocityDetourInstalled)
                return;
            if (g_OrdnanceVelocityDetourAttempts >= kOrdnanceVelocityDetourMaxAttempts)
                return;
            ++g_OrdnanceVelocityDetourAttempts;

            if (!g_OrdnanceSpawnVelocityDetourInstalled &&
                InstallInlineDetour32(g_OrdnanceSpawnVelocityDetour,
                                      kOrdnanceSpawnVelocityAddr,
                                      reinterpret_cast<void*>(&OrdnanceSpawnVelocityThunk),
                                      kOrdnanceSpawnVelocityPatchLen,
                                      kOrdnanceSpawnVelocityExpected,
                                      sizeof(kOrdnanceSpawnVelocityExpected)))
            {
                g_OrdnanceSpawnVelocityResume = g_OrdnanceSpawnVelocityDetour.trampoline;
                g_OrdnanceSpawnVelocityDetourInstalled = true;
                Log(L"[ORDVEL] Installed spawn-velocity detour at 0x%08X trampoline=0x%08X\n",
                    static_cast<uint32_t>(kOrdnanceSpawnVelocityAddr),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_OrdnanceSpawnVelocityResume)));
            }

            if (!g_CannonLeadVelocityDetourInstalled &&
                InstallInlineDetour32(g_CannonLeadVelocityDetour,
                                      kCannonLeadVelocityAddr,
                                      reinterpret_cast<void*>(&CannonLeadVelocityThunk),
                                      kCannonLeadVelocityPatchLen,
                                      kCannonLeadVelocityExpected,
                                      sizeof(kCannonLeadVelocityExpected)))
            {
                g_CannonLeadVelocityResume = g_CannonLeadVelocityDetour.trampoline;
                g_CannonLeadVelocityDetourInstalled = true;
                Log(L"[ORDVEL] Installed cannon-lead detour at 0x%08X trampoline=0x%08X\n",
                    static_cast<uint32_t>(kCannonLeadVelocityAddr),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_CannonLeadVelocityResume)));
            }

            // Say which arm gave up. A half-installed feature that stays quiet
            // reads as "the setting does nothing" rather than as a build
            // mismatch, so name the site that never matched.
            if (g_OrdnanceVelocityDetourAttempts >= kOrdnanceVelocityDetourMaxAttempts &&
                !g_OrdnanceVelocityDetourFailureLogged &&
                !(g_OrdnanceSpawnVelocityDetourInstalled && g_CannonLeadVelocityDetourInstalled))
            {
                g_OrdnanceVelocityDetourFailureLogged = true;
                if (!g_OrdnanceSpawnVelocityDetourInstalled)
                {
                    Log(L"[ORDVEL] Spawn-velocity site at 0x%08X never matched after %d "
                        L"attempts; ordnance velocity inheritance unavailable on this build\n",
                        static_cast<uint32_t>(kOrdnanceSpawnVelocityAddr),
                        g_OrdnanceVelocityDetourAttempts);
                }
                else
                {
                    Log(L"[ORDVEL] Cannon-lead site at 0x%08X never matched after %d "
                        L"attempts; spawn inheritance is active but lead compensation "
                        L"and its tolerance bypass stay off\n",
                        static_cast<uint32_t>(kCannonLeadVelocityAddr),
                        g_OrdnanceVelocityDetourAttempts);
                }
            }
        }

        // Reconciles the live state. The feature is applied only when the user
        // enabled it AND we are not in a network game (net id 0). Inheritance
        // rides on the spawn detour; the cannon compensation and its tolerance
        // bypass additionally require the cannon owner chain to have survived
        // validation, so a build whose Cannon layout differs degrades to
        // spawn-velocity inheritance instead of feeding the weapon solver a
        // pointer it cannot trust.
        void RefreshOrdnanceVelocityInheritanceState()
        {
            const bool wantActive =
                g_OrdnanceVelocityInheritanceEnabled && IsSinglePlayerSession();

            if (wantActive)
                EnsureOrdnanceVelocityDetours();

            const bool active = wantActive && g_OrdnanceSpawnVelocityDetourInstalled;
            InterlockedExchange(&g_OrdnanceVelocityInheritanceActive, active ? 1 : 0);

            if (InterlockedExchange(&g_CannonOwnerChainRejectPending, 0) != 0)
            {
                Log(L"[ORDVEL] Cannon owner chain at +0x%02X failed validation; "
                    L"lead compensation stood down. Spawn inheritance still active "
                    L"(applied=%ld).\n",
                    static_cast<unsigned>(kCannonOwnerObjOffset),
                    g_OrdnanceSpawnVelocityAppliedCount);
            }

            const bool wantTolerance =
                active &&
                g_CannonLeadVelocityDetourInstalled &&
                g_CannonOwnerChainState != kCannonOwnerChainRejected;
            ApplyCannonLeadTolerancePatch(wantTolerance);
        }

        // Mission-end resting state: drop any scripted enable back to the INI
        // baseline, then reconcile (which also re-applies the multiplayer gate).
        void RevertOrdnanceVelocityInheritanceToBaseline()
        {
            g_OrdnanceVelocityInheritanceEnabled = g_OrdnanceVelocityInheritanceBaselineEnabled;
            RefreshOrdnanceVelocityInheritanceState();
        }
    }
}
