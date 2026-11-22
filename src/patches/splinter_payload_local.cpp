// splinter_payload_local.cpp -- keep a splinter's payload ordnance (SprayBomb,
// BounceBomb, Popper) local to each peer, so a Splinter whose payload is itself
// a SprayBomb does not multiply in multiplayer ("Splinception").
//
// ============================================================================
// THE DEFECT (Redux 2.2.301, exact GOG image; Docs/MPAUTH_SPLINTER_STATIC_ANALYSIS.md)
// ============================================================================
//
// SprayBuilding::Simulate (0x005DA6E0) builds its payload ordnance locally on
// every peer (OrdnanceClass factory call at 0x005DAB73) and sets the payload's
// bSend dword (+0x80) to 0, so it is never sent. Ordnance::Init gives it
// source (u16 at +0x7C) = Net_GetMyPlayerID on every peer. Both bounce
// branches of SprayBomb::Hit (0x005DB080; terrain bounce at speed >= 5, object
// bounce at speed >= 1) then do
//
//     if (Net_IsNetGame() && (short)bomb->source == Net_GetMyPlayerID())
//         { quantize the matrix; ...; bomb->bSend = 1; }
//
// A nested payload SprayBomb has source == me on every peer, so every peer
// resends its own copy at its first bounce under its own (me, ordid) key. No
// receiver knows that key, so Ordnance_Receive builds a new SprayBomb on each.
// Every copy deploys another SprayBuilding, which fires more payloads: the
// count grows by the number of peers each generation.
//
// The payload can be any ordnance class: SprayBuildingClass looks its payload
// up by name with the generic OrdnanceClass::Find (0x00586C60, no class
// filter) and Simulate builds it through the generic factory. BounceBomb::Hit
// (0x0047E250, BounceBombVtable slot 5) has the same two compares (terrain
// call 0x0047E447, object call 0x0047E7B8, bSend = 1 at 0x0047E5E7 and
// 0x0047E958), so a BounceBomb payload is resent from every peer too. It does
// not deploy anything, so it duplicates (one copy per peer) instead of growing.
//
// Popper::Control (0x005A6460, PopperVtable slot 3) builds its child ordnance
// when `!Net_IsNetGame() || source == me` (compare call 0x005A6990), copies the
// Popper's source and ordid+1 into the child and sets the child's bSend = 1
// (0x005A6A98). A payload Popper has source == me on every peer, so every peer
// sends its own child: one copy per peer, and growth when the child is a
// SprayBomb.
//
// Checked and left stock:
//   - SniperShell (FUN_005D6E00, compare call 0x005D6E38): on a hit with
//     source == me it applies the snipe to the target and sends a 'sn' message
//     to the target's owner (FUN_00573BB0). It builds no ordnance and the
//     effect is idempotent, so N peers converge; gating it would make a payload
//     SniperShell a dud.
//   - Ordnance_ControlAll (FUN_00583F30, compare call 0x00583FF5): batches a
//     removal message only for dead ordnance with source != me. A payload has
//     source == me, so it already takes the local path.
//   - Beam::Simulate (FUN_0047B030, compare call 0x0047B53A): once the beam
//     loses its anchor, the owner broadcasts an 'io' end message for its key.
//     It never sets bSend and receivers only update existing ordnance, so a
//     payload Beam's unknown key builds nothing.
//
// ============================================================================
// THE FIX
// ============================================================================
//
// bSend cannot identify the payload: Ordnance_Sent (0x00584530) sets a sent
// bomb's bSend from 2 back to 0, so the launcher's own thrown SprayBomb also
// reads source == me, bSend 0 by the time it bounces, and its bounce resync
// must stay. The payload is marked positively instead:
//
// 1. The payload factory call at 0x005DAB73 is retargeted to PayloadBuildHook,
//    which runs the factory and, in a network game only, records the result
//    when its vtable is the SprayBomb, BounceBomb or Popper vtable, keyed by
//    address, (source, ordid) and owner (+0xD8). Payloads built before a
//    mid-mission install are not recorded and behave as stock.
// 2. Ordnance is pooled: Ordnance remove (0x00585560) puts a dead bomb on its
//    class free list and the factory reuses it with Init only, so the SprayBomb
//    destructor rarely runs and records go stale. Within a mission the key
//    still protects a reused address, because Init gives it a new ordid. The
//    ordnance cleanup at mission teardown (0x00584E60, one caller at 0x0061847D)
//    resets the ordid counter (u16 0x00918130 = 0), so after it a stale
//    (me, n) record could match the launcher's own reused bomb. Its call is
//    retargeted to OrdnanceCleanupHook, which runs it and then clears the
//    registry. SprayBomb vtable slot 0 (scalar deleting destructor 0x005DB030)
//    still drops a record as a backstop for a bomb that really is deleted.
//    Known limit: within one mission the u16 ordid counter can wrap after
//    65536 ordnance, and a stale record whose address, key and owner all come
//    round again would read as a payload (its bounce stays local, its deploy is not
//    synced). Not worth more machinery at that rate.
// 3. The four Net_GetMyPlayerID calls in the bounce compares (two in each Hit)
//    are retargeted to SprayBombIdThunk / BounceBombIdThunk. Each calls the
//    original and, for a recorded payload whose source is me, returns the
//    source with bit 0 flipped, so the stock compare fails and the bounce
//    stays local. Every other bomb, the launcher's own thrown splinter
//    included, gets the real id. The decision and the registry are in
//    include/splinter_payload_local.h.
// 4. Popper::Control's child bSend store (0x005A6A98) is replaced by a call to
//    PopperChildSendThunk. For a recorded Popper the child gets bSend = 0 (it
//    stays local, like every other payload) and is itself recorded when it is
//    a SprayBomb, BounceBomb or Popper; every other Popper's child gets the
//    stock bSend = 1.
//
// Entry contract at the payload build call (0x005DAB73):
//   mov edx,[ebp-0x1D0] / mov eax,[edx+0xF4] / push eax      ; owner obj76
//   lea ecx,[ebp-0x44] / push ecx                            ; matrix
//   mov ecx,[ebp-0x1D8]                                      ; OrdnanceClass
//   call 0x00586FF0     <- here: __thiscall(cls, matrix, obj76), ret 8, EAX
//   mov [ebp-0x1D4],eax / ... / mov dword [edx+0x80],0       ; bSend = 0
// PayloadBuildHook is __fastcall with the same two stack arguments, so ECX
// carries the class and the callee pops 8, exactly as the factory does.
//
// Entry contract at the ordnance cleanup call (0x0061847D, in the mission
// teardown FUN_00618370): one of a run of argument-less `call`s; nothing is
// passed in registers or on the stack and the result is unused. 0x00584E60
// sets ECX itself and ends in a plain `ret`; OrdnanceCleanupHook is a cdecl
// void() that calls it, so the caller's view is unchanged.
//
// Entry contract at the SprayBomb bounce sites (bytes verified on GOG 2.2.301):
//
//   site A (terrain bounce)            site B (object bounce)
//   test eax,eax / jz ...              test eax,eax / jz ...   ; Net_IsNetGame
//   mov eax,[ebp-0x1B0]                mov edx,[ebp-0x1B0]     ; the bomb
//   movzx esi,word [eax+0x7C]          movzx esi,word [edx+0x7C]
//   call Net_GetMyPlayerID   <- here   call Net_GetMyPlayerID   <- here
//   movzx ecx,ax / cmp esi,ecx / jne   movzx eax,ax / cmp esi,eax / jne
//
// The BounceBomb sites (0x0047E447 terrain, 0x0047E7B8 object) are byte for
// byte the same shape as site A, with the bomb at [ebp-0x100] (BounceBomb::Hit
// stores its `this` there at entry, 0x0047E265); after the jne both reload ECX
// and EDX from the frame before use.
//
// EBP is the Hit function's frame. Only AX of the result is read; ESI must
// survive (the thunk's callee is a normal cdecl function, which preserves
// ESI/EDI/EBX/EBP). ECX and EDX are dead after the call (the compiler assumes
// a cdecl call clobbers them; site B's following `push ecx` only reserves a
// float argument slot). Only the five CALL bytes are rewritten at each site;
// nothing branches into them.
//
// Entry contract at the Popper child store (0x005A6A98, in Popper::Control):
//   mov eax,[ebp-0xD4] / mov [eax+0x7E],dx                   ; child ordid
//   mov ecx,[ebp-0xD4]                                       ; the child
//   mov dword [ecx+0x80],1   <- here (10 bytes: CALL + 5-byte NOP)
//   mov edx,[ebp-0xD0] / mov eax,[edx+0x14] / mov ecx,[eax+0x14] ...
// The Popper is at [ebp-0xD0] (stored from ECX at entry, 0x005A6475). The
// following code reloads EDX, EAX and ECX before use and reads no flags, so
// the thunk may clobber them; nothing branches into the ten bytes.
//
// The vtable slot, all six call sites and the Popper store are installed or
// none, under one CodePatchLock; if a rollback write fails, the hooks delegate
// to stock because g_Active stays false.
//
// Multiplayer note: nested splinter trees stay per-peer, which is the stock
// design for payload ordnance. SplinterSync still syncs only the top-level
// deploy (mp_splinter_sync.cpp asks IsLocalPayload and skips the rest). A peer
// without this fix still resends its own payload copies, which a patched peer
// will still build; the growth stops fully only when every peer has the fix.
//
// Every engine address is a named row in scripts/patches.json.

#include "splinter_payload_local.h"
#include "splinter_payload_local_install.h"

#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "com_vtable_patch.h"
#include "env_switch_table.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace SplinterPayloadLocal
    {
        namespace
        {
            constexpr const char* kComponent = "SPLINTERPAYLOAD";
            constexpr long kLogBudget = 16;
            constexpr size_t kDtorSlot = 0;

            using FnLocalPlayerId = uint16_t(__cdecl*)();
            using FnOrdnanceFactory = void*(__thiscall*)(void* ordnanceClass, void* matrix, void* ownerObj76);
            using FnDtor = void*(__thiscall*)(void* self, int flags);
            using FnOrdnanceCleanup = void(__cdecl*)();

            std::atomic<bool> g_Done{ false };
            std::atomic<bool> g_Active{ false };
            FnLocalPlayerId g_LocalPlayerId = nullptr;
            FnOrdnanceFactory g_Factory = nullptr;
            FnDtor g_DtorOriginal = nullptr;
            FnOrdnanceCleanup g_Cleanup = nullptr;
            uint32_t g_SprayBombVtable = 0;
            uint32_t g_BounceBombVtable = 0;
            uint32_t g_PopperVtable = 0;
            uint32_t g_NetFlagAddr = 0;
            volatile long g_LogLeft = kLogBudget;
            volatile long g_FullLogLeft = 4;

            // Build, Hit, cleanup and the destructor all run on the game
            // thread; the lock only keeps a stray caller from racing the map.
            SRWLOCK g_Lock = SRWLOCK_INIT;
            PayloadRegistry g_Registry;

            struct ScopedLock
            {
                ScopedLock() { AcquireSRWLockExclusive(&g_Lock); }
                ~ScopedLock() { ReleaseSRWLockExclusive(&g_Lock); }
                ScopedLock(const ScopedLock&) = delete;
                ScopedLock& operator=(const ScopedLock&) = delete;
            };

            bool IsEnabled()
            {
                bool enabled = true;
                static const EnvSwitches::EnvSwitch rows[] = {
                    { &enabled, EnvSwitches::Kind::KillSwitch,
                      "OPENSHIM_DISABLE_SPLINTER_PAYLOAD_LOCAL", "BZR_DISABLE_SPLINTER_PAYLOAD_LOCAL" },
                };
                EnvSwitches::Apply(rows, EnvFlagEnabled);
                return enabled;
            }

            // --- SEH leaves --------------------------------------------------

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

            bool SafeWriteU32(uintptr_t address, uint32_t value)
            {
                __try
                {
                    *reinterpret_cast<uint32_t*>(address) = value;
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            // Source, ordid and owner (creator obj76 at +0xD8).
            bool ReadBombKey(const void* bomb, uint16_t& source, uint16_t& ordId, uint32_t& owner)
            {
                __try
                {
                    const uint8_t* p = static_cast<const uint8_t*>(bomb);
                    source = *reinterpret_cast<const uint16_t*>(p + kOrdnanceSourceOffset);
                    ordId = *reinterpret_cast<const uint16_t*>(p + kOrdnanceOrdIdOffset);
                    owner = *reinterpret_cast<const uint32_t*>(p + kOrdnanceOwnerOffset);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool IsNetGame()
            {
                uint8_t flag = 0;
                return g_NetFlagAddr && SafeReadU8(g_NetFlagAddr, flag) && flag != 0;
            }

            const void* ReadFrameBomb(const uint8_t* frame, intptr_t bombOffset)
            {
                __try
                {
                    return *reinterpret_cast<const void* const*>(frame + bombOffset);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return nullptr;
                }
            }

            // True when `bomb` is a recorded payload under its current key and
            // owner.
            bool IsRecorded(const void* bomb)
            {
                uint16_t source = 0, ordId = 0;
                uint32_t owner = 0;
                if (!bomb || !ReadBombKey(bomb, source, ordId, owner))
                    return false;
                ScopedLock lock;
                return g_Registry.Contains(reinterpret_cast<uintptr_t>(bomb), MakeKey(source, ordId), owner);
            }

            // Records `ordnance` when it is one of the payload classes.
            void RecordIfPayloadClass(void* ordnance)
            {
                uint32_t vtable = 0;
                uint16_t source = 0, ordId = 0;
                uint32_t owner = 0;
                if (!SafeReadU32(reinterpret_cast<uintptr_t>(ordnance), vtable) ||
                    !IsRecordedPayloadClass(vtable, g_SprayBombVtable, g_BounceBombVtable, g_PopperVtable) ||
                    !ReadBombKey(ordnance, source, ordId, owner))
                    return;
                bool added = false;
                {
                    ScopedLock lock;
                    added = g_Registry.Add(reinterpret_cast<uintptr_t>(ordnance), MakeKey(source, ordId), owner);
                }
                if (!added && InterlockedDecrement(&g_FullLogLeft) >= 0)
                    LogShimA(LogLevel::Warn, kComponent,
                             "payload registry full (%u); payload %u/%u stays stock",
                             static_cast<unsigned>(kMaxPayloads), source, ordId);
            }

            // --- hooks -------------------------------------------------------

            // Replaces the OrdnanceClass factory call in SprayBuilding::Simulate.
            // In a network game, records SprayBomb, BounceBomb and Popper
            // payloads, the classes whose owner-only branch re-sends.
            void* __fastcall PayloadBuildHook(void* ordnanceClass, void* /*edx*/, void* matrix,
                                              void* ownerObj76)
            {
                void* payload = g_Factory(ordnanceClass, matrix, ownerObj76);
                // Off the net the owner-only branches send nothing.
                if (payload && IsNetGame())
                    RecordIfPayloadClass(payload);
                return payload;
            }

            void* __fastcall SprayBombDtorHook(void* self, void* /*edx*/, int flags)
            {
                {
                    ScopedLock lock;
                    g_Registry.Remove(reinterpret_cast<uintptr_t>(self));
                }
                return g_DtorOriginal(self, flags);
            }

            // Replaces the ordnance cleanup call in the mission teardown. Every
            // record is stale after it: the ordid counter restarts at 0.
            void __cdecl OrdnanceCleanupHook()
            {
                g_Cleanup();
                size_t dropped = 0;
                {
                    ScopedLock lock;
                    dropped = g_Registry.Size();
                    g_Registry.Clear();
                }
                if (dropped && InterlockedDecrement(&g_LogLeft) >= 0)
                    LogShimA(LogLevel::Info, kComponent, "ordnance cleanup: dropped %u payload records",
                             static_cast<unsigned>(dropped));
            }

            // Called by a thunk with the Hit function's EBP. Returns the id the
            // stock compare sees (only the low 16 bits are read).
            uint32_t ReportedIdForFrame(const uint8_t* frame, intptr_t bombOffset)
            {
                const uint16_t me = g_LocalPlayerId();
                // A degraded install (rollback failed) stays fully stock.
                if (!g_Active.load(std::memory_order_acquire))
                    return me;
                const void* bomb = frame ? ReadFrameBomb(frame, bombOffset) : nullptr;
                uint16_t source = 0, ordId = 0;
                uint32_t owner = 0;
                const bool isPayload = bomb && ReadBombKey(bomb, source, ordId, owner) && IsRecorded(bomb);
                const uint16_t reported = ReportedPlayerId(me, isPayload, source);
                if (reported != me && InterlockedDecrement(&g_LogLeft) >= 0)
                    LogShimA(LogLevel::Info, kComponent,
                             "kept payload bounce local: source %u ordid %u", source, ordId);
                return reported;
            }

            uint32_t __cdecl SprayBombIdForFrame(const uint8_t* frame)
            {
                return ReportedIdForFrame(frame, kSprayBombFrameOffset);
            }

            uint32_t __cdecl BounceBombIdForFrame(const uint8_t* frame)
            {
                return ReportedIdForFrame(frame, kBounceBombFrameOffset);
            }

            __declspec(naked) void SprayBombIdThunk()
            {
                __asm
                {
                    push ebp                    // SprayBomb::Hit's frame
                    call SprayBombIdForFrame
                    add esp, 4
                    ret
                }
            }

            __declspec(naked) void BounceBombIdThunk()
            {
                __asm
                {
                    push ebp                    // BounceBomb::Hit's frame
                    call BounceBombIdForFrame
                    add esp, 4
                    ret
                }
            }

            // Called by PopperChildSendThunk in place of the stock
            // `mov dword [child+0x80], 1`.
            void __cdecl PopperChildSendFor(const uint8_t* frame, uint8_t* child)
            {
                if (!child)
                    return;
                bool popperIsPayload = false;
                // A degraded install (rollback failed) stays fully stock.
                if (g_Active.load(std::memory_order_acquire) && frame)
                    popperIsPayload = IsRecorded(ReadFrameBomb(frame, kPopperFrameOffset));
                SafeWriteU32(reinterpret_cast<uintptr_t>(child) + kOrdnanceSendOffset,
                             PopperChildSend(popperIsPayload));
                if (!popperIsPayload)
                    return;
                RecordIfPayloadClass(child);
                if (InterlockedDecrement(&g_LogLeft) >= 0)
                    LogShimA(LogLevel::Info, kComponent, "kept payload Popper child 0x%08X local",
                             static_cast<unsigned>(reinterpret_cast<uintptr_t>(child)));
            }

            __declspec(naked) void PopperChildSendThunk()
            {
                __asm
                {
                    push ecx                    // the child
                    push ebp                    // Popper::Control's frame
                    call PopperChildSendFor
                    add esp, 8
                    ret
                }
            }

            // --- install -----------------------------------------------------

            bool PatchCallSite(uint32_t site, const void* replacement, const uint8_t (&original)[kCallLength])
            {
                HookEngine::PatchDef def;
                def.address = site;
                def.type = HookEngine::PatchType::REL32;
                def.name = "SplinterPayloadLocal::CallSite";
                def.verified = true;
                def.expected_original.assign(original, original + kCallLength);

                const int32_t rel =
                    static_cast<int32_t>(reinterpret_cast<uintptr_t>(replacement)) -
                    static_cast<int32_t>(site + kCallLength);
                def.payload.assign(kCallLength, 0);
                def.payload[0] = kCallOpcode;
                std::memcpy(def.payload.data() + 1, &rel, sizeof(rel));
                return HookEngine::ApplyPatch(def);
            }

            // Popper child store: CALL PopperChildSendThunk + 5-byte NOP.
            // The 10-byte write is not atomic. That matters only if the fix
            // installs mid-mission while a Popper executes this store at that
            // instant.
            bool PatchPopperStore(uint32_t site, const uint8_t (&original)[kPopperStoreLength])
            {
                HookEngine::PatchDef def;
                def.address = site;
                def.type = HookEngine::PatchType::BYTES;
                def.name = "SplinterPayloadLocal::PopperStore";
                def.verified = true;
                def.expected_original.assign(original, original + kPopperStoreLength);

                const int32_t rel =
                    static_cast<int32_t>(reinterpret_cast<uintptr_t>(&PopperChildSendThunk)) -
                    static_cast<int32_t>(site + kCallLength);
                def.payload.assign(kPopperStoreLength, 0);
                def.payload[0] = kCallOpcode;
                std::memcpy(def.payload.data() + 1, &rel, sizeof(rel));
                std::memcpy(def.payload.data() + kCallLength, kNop5, sizeof(kNop5));
                return HookEngine::ApplyPatch(def);
            }

            struct CallSite
            {
                const char* what;
                uint32_t address;
                uint32_t expectedTarget;
                const void* replacement;
                uint8_t original[kCallLength];
            };

            void DoInstall()
            {
                // Literal names so patch_registration_tests can check them
                // against scripts/patches.json.
                const uint32_t buildSite =
                    HookEngine::ResolveNamedAddress("SprayBuilding::Simulate payload build call");
                const uint32_t cleanupSite =
                    HookEngine::ResolveNamedAddress("Mission teardown ordnance cleanup call");
                const uint32_t terrainSite =
                    HookEngine::ResolveNamedAddress("SprayBomb::Hit terrain bounce my-id call");
                const uint32_t objectSite = HookEngine::ResolveNamedAddress("SprayBomb::Hit object bounce my-id call");
                const uint32_t bounceTerrainSite =
                    HookEngine::ResolveNamedAddress("BounceBomb::Hit terrain bounce my-id call");
                const uint32_t bounceObjectSite =
                    HookEngine::ResolveNamedAddress("BounceBomb::Hit object bounce my-id call");
                const uint32_t popperStoreSite =
                    HookEngine::ResolveNamedAddress("Popper::Control child bSend store");
                const uint32_t localIdAddr = HookEngine::ResolveNamedAddress("GetLocalPlayerNetId");
                const uint32_t factoryAddr = HookEngine::ResolveNamedAddress("WeaponPresentation::OrdnanceFactory");
                uint32_t dtorAddr = 0;
                uint32_t cleanupAddr = 0;
                uint32_t netFlagAddr = 0;
                const HookEngine::EngineRow rows[] = {
                    { "SprayBombVtable", &g_SprayBombVtable },
                    { "BounceBombVtable", &g_BounceBombVtable },
                    { "PopperVtable", &g_PopperVtable },
                    { "SprayBombDtor", &dtorAddr },
                    { "OrdnanceCleanup", &cleanupAddr },
                    { "IsNetGameFlag", &netFlagAddr },
                };
                if (!buildSite || !cleanupSite || !terrainSite || !objectSite || !bounceTerrainSite ||
                    !bounceObjectSite || !popperStoreSite || !localIdAddr || !factoryAddr ||
                    !HookEngine::BindEngineRows("SplinterPayloadLocal", rows))
                {
                    LogShimA(LogLevel::Warn, kComponent, "an address did not resolve; fix not installed");
                    return;
                }
                if (!Hooks::VtableTypeNameMatches(g_SprayBombVtable, ".?AVSprayBomb@@") ||
                    !Hooks::VtableTypeNameMatches(g_BounceBombVtable, ".?AVBounceBomb@@") ||
                    !Hooks::VtableTypeNameMatches(g_PopperVtable, ".?AVPopper@@"))
                {
                    LogShimA(LogLevel::Warn, kComponent,
                             "vtable 0x%08X / 0x%08X / 0x%08X is not SprayBomb / BounceBomb / Popper; "
                             "fix not installed",
                             g_SprayBombVtable, g_BounceBombVtable, g_PopperVtable);
                    return;
                }
                const uint32_t slotAddr = g_SprayBombVtable + static_cast<uint32_t>(kDtorSlot * sizeof(void*));
                uint32_t slot0 = 0;
                if (!SafeReadU32(slotAddr, slot0) || slot0 != dtorAddr)
                {
                    LogShimA(LogLevel::Warn, kComponent,
                             "SprayBomb vtable slot 0 is 0x%08X, expected 0x%08X; fix not installed", slot0, dtorAddr);
                    return;
                }

                CallSite sites[] = {
                    { "ordnance cleanup", cleanupSite, cleanupAddr,
                      reinterpret_cast<const void*>(&OrdnanceCleanupHook), {} },
                    { "payload build", buildSite, factoryAddr, reinterpret_cast<const void*>(&PayloadBuildHook), {} },
                    { "SprayBomb terrain bounce", terrainSite, localIdAddr,
                      reinterpret_cast<const void*>(&SprayBombIdThunk), {} },
                    { "SprayBomb object bounce", objectSite, localIdAddr,
                      reinterpret_cast<const void*>(&SprayBombIdThunk), {} },
                    { "BounceBomb terrain bounce", bounceTerrainSite, localIdAddr,
                      reinterpret_cast<const void*>(&BounceBombIdThunk), {} },
                    { "BounceBomb object bounce", bounceObjectSite, localIdAddr,
                      reinterpret_cast<const void*>(&BounceBombIdThunk), {} },
                };
                // Signature uniqueness is not identity: each site must still be
                // the stock call to the routine it was written against.
                for (CallSite& site : sites)
                {
                    if (!HookEngine::ReadMemory(site.address, site.original, kCallLength) ||
                        !SiteIsStockCall(site.address, site.original, site.expectedTarget))
                    {
                        LogShimA(LogLevel::Warn, kComponent,
                                 "%s call 0x%08X does not reach 0x%08X; fix not installed", site.what, site.address,
                                 site.expectedTarget);
                        return;
                    }
                }
                uint8_t popperStoreOriginal[kPopperStoreLength] = {};
                if (!HookEngine::ReadMemory(popperStoreSite, popperStoreOriginal, kPopperStoreLength) ||
                    !PopperStoreIsStock(popperStoreOriginal))
                {
                    LogShimA(LogLevel::Warn, kComponent,
                             "Popper child store 0x%08X is not the stock bSend = 1; fix not installed",
                             popperStoreSite);
                    return;
                }

                g_NetFlagAddr = netFlagAddr;
                g_LocalPlayerId = reinterpret_cast<FnLocalPlayerId>(static_cast<uintptr_t>(localIdAddr));
                g_Factory = reinterpret_cast<FnOrdnanceFactory>(static_cast<uintptr_t>(factoryAddr));
                g_Cleanup = reinterpret_cast<FnOrdnanceCleanup>(static_cast<uintptr_t>(cleanupAddr));

                // One lock over every write and its rollback, so no other
                // installer sees a half-installed set.
                HookEngine::CodePatchLock patchLock;

                void* vtableHolder = &g_SprayBombVtable;
                // Known before the write, so the hook never sees a null
                // original and Refuse can detect a foreign wrapper.
                void* dtorOriginal = reinterpret_cast<void*>(static_cast<uintptr_t>(dtorAddr));
                g_DtorOriginal = reinterpret_cast<FnDtor>(dtorOriginal);
                const ComVtablePatch::Result patched = ComVtablePatch::PatchEntry(
                    vtableHolder, kDtorSlot, reinterpret_cast<void*>(&SprayBombDtorHook), dtorOriginal,
                    ComVtablePatch::OnForeignWrapper::Refuse);
                if (!ComVtablePatch::Succeeded(patched) ||
                    reinterpret_cast<uintptr_t>(dtorOriginal) != dtorAddr)
                {
                    LogShimA(LogLevel::Warn, kComponent,
                             "SprayBomb destructor slot not patched (%d); fix not installed",
                             static_cast<int>(patched));
                    return;
                }

                const size_t siteCount = sizeof(sites) / sizeof(sites[0]);
                size_t written = 0;
                for (; written < siteCount; ++written)
                {
                    if (!PatchCallSite(sites[written].address, sites[written].replacement, sites[written].original))
                        break;
                }
                if (written != siteCount || !PatchPopperStore(popperStoreSite, popperStoreOriginal))
                {
                    // Put back what was written, newest first. WriteMemory
                    // takes the same (recursive) CodePatchLock as ApplyPatch.
                    bool restored = true;
                    for (size_t i = written; i-- > 0;)
                        restored =
                            HookEngine::WriteMemory(sites[i].address, sites[i].original, kCallLength) && restored;
                    const uint32_t dtorValue = dtorAddr;
                    restored = HookEngine::WriteMemory(slotAddr, &dtorValue, sizeof(dtorValue)) && restored;
                    const char* what = written != siteCount ? sites[written].what : "Popper child store";
                    const uint32_t where = written != siteCount ? sites[written].address : popperStoreSite;
                    LogShimA(LogLevel::Warn, kComponent,
                             "%s 0x%08X could not be rewritten; fix not installed (earlier writes %s)", what,
                             where, restored ? "restored" : "restore FAILED, the hooks still delegate");
                    return;
                }

                g_Active.store(true, std::memory_order_release);
                LogShimA(LogLevel::Info, kComponent,
                         "installed: cleanup 0x%08X, payload build 0x%08X, SprayBomb bounces 0x%08X/0x%08X, "
                         "BounceBomb bounces 0x%08X/0x%08X, Popper child store 0x%08X, "
                         "SprayBomb vtable 0x%08X dtor 0x%08X",
                         cleanupSite, buildSite, terrainSite, objectSite, bounceTerrainSite, bounceObjectSite,
                         popperStoreSite, g_SprayBombVtable, dtorAddr);
            }
        }

        void InstallSplinterPayloadLocalIfPossible()
        {
            if (g_Done.exchange(true))
                return;
            if (!IsEnabled())
            {
                LogShimA(LogLevel::Info, kComponent, "disabled ([Fixes] SplinterPayloadLocal = 0)");
                return;
            }
            DoInstall();
        }

        bool IsLocalPayload(const void* bomb)
        {
            if (!g_Active.load(std::memory_order_acquire) || !bomb)
                return false;
            return IsRecorded(bomb);
        }
    }
}
