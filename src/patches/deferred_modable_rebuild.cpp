// deferred_modable_rebuild.cpp
// BZR Open Shim - menu transitions without a Modable rebuild.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// See include/deferred_modable_rebuild.h for what and why.
//
// The four shell mount setters share one shape (GOG Redux 2.2.301):
//
//     cmp  dword [eax+8Ch], N ; jne +5 ; jmp <epilogue>   stock same-mode guard
//     mov  ecx, [ebp-..]                                   this
//     mov  dword [ecx+8Ch], N   <- Store site, 10 bytes
//     call 0x00434420           (pre: stop music, drop caches)
//     ... unmount, remount through Redux's file system ...
//     push "Modable"            <- Gate site, 5 bytes
//     ... std::string, getSingleton, call [clearResourceGroup]
//     ... std::string, getSingleton, call [initialiseResourceGroup]
//     call 0x00434440           <- skip target (post: reload font, music)
//
//   setter      mode  Store       Gate        clear/init/skip (from Gate)
//   0x0076A030  4     0x0076A07D  0x0076A16D  +0x20 / +0x55 / +0x6A
//   0x0076A430  1     0x0076A47D  0x0076A564  +0x20 / +0x55 / +0x6A
//   0x0076A240  2     0x0076A28D  0x0076A392  +0x20 / +0x55 / +0x6A
//   0x0076AB20  3     0x0076AB79  0x0076ADBF  +0x1D / +0x52 / +0x67
//   0x0076AE60  0     0x0076AEDC  0x0076B29A  +0x23 / +0x5B / +0x70  (campaign, optional)
//
// The two std::string temporaries are built and destroyed between Gate and the
// skip target, so the stack and the SEH state byte are the same at both ends:
// jumping over the block is stack-neutral and leaves nothing half built.
//
// Which content Ogre holds is tracked in s_state.held. Mode 0 (a mission or
// campaign mount, setters A 0x0076A600, B 0x0076AE60, C 0x0076B350) is never
// deferred inside the mission mount: A and C are not hooked and always rebuild,
// so a mount that was in mode 0 means the group holds mission content and the
// next shell setter rebuilds as stock. A shell setter skips only when the mode
// it replaces is a shell mode (1-4) and the group holds the base set (4).
// Going back to the main menu then costs nothing; going to IA/MP/list leaves a
// pending catch-up, flushed by the two call-site wrappers before anything
// renders mod content. The decisions live in include/deferred_modable_policy.h.
//
// Campaign enter (setter B, 0x0076AE60). Its two callers are the screen factory
// 0x007C7AD0 case 0x25 (campaign Launch -> briefing, return 0x007C7FFB) and
// the mission mount 0x0076E6C0 (0x0076E9E3). B's guard is same mode AND same
// path. The Mission Mount Call wrapper sets inMissionMount, so:
//   - factory call (flag clear): the Gate is skipped, the group keeps what it
//     held, pendingMission is set ("campaign enter: Modable rebuild deferred");
//   - mission mount: the Mission Mount Call wrapper sees pendingMission and
//     runs pre/clear/init/post BEFORE calling the mount ("mission mount:
//     forced deferred Modable rebuild"), i.e. at the point stock had already
//     rebuilt on enter. The mount then runs exactly as stock: B with the same
//     mode+path returns at its guard; a different path rebuilds again, as
//     stock would;
//   - back-out to a shell screen with pendingMission set: the enter rebuild
//     never ran, so the shell rule applies as if coming from a shell mode
//     ("campaign back: rebuild skipped (enter was deferred)").
// B's two sites are optional: OPENSHIM_DISABLE_DEFER_CAMPAIGN_MOUNT drops only
// them, and a byte mismatch stands only them down (B stays stock).

#include "deferred_modable_rebuild.h"
#include "deferred_modable_policy.h"

#include <windows.h>

#include <cstring>

#include "shim_log.h"

namespace BZROpenShim
{
    namespace DeferredModableRebuild
    {
        namespace
        {
            constexpr const char* kComponent = "DeferredModableRebuild";

            constexpr const char* kMainStore = "Deferred Modable Rebuild Main Store";
            constexpr const char* kMainGate  = "Deferred Modable Rebuild Main Gate";
            constexpr const char* kIaStore   = "Deferred Modable Rebuild IA Store";
            constexpr const char* kIaGate    = "Deferred Modable Rebuild IA Gate";
            constexpr const char* kMpStore   = "Deferred Modable Rebuild MP Store";
            constexpr const char* kMpGate    = "Deferred Modable Rebuild MP Gate";
            constexpr const char* kListStore = "Deferred Modable Rebuild List Store";
            constexpr const char* kListGate  = "Deferred Modable Rebuild List Gate";
            constexpr const char* kCampStore = "Deferred Modable Rebuild Campaign Store";
            constexpr const char* kCampGate  = "Deferred Modable Rebuild Campaign Gate";
            constexpr const char* kMissionCall = "Deferred Modable Rebuild Mission Mount Call";
            constexpr const char* kMpRoomCall  = "Deferred Modable Rebuild MP Room Mount Call";

            using namespace DeferredModablePolicy;
            constexpr uint32_t kModeOffset = 0x8C;

            constexpr const char* kClearImport =
                "?clearResourceGroup@ResourceGroupManager@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z";
            constexpr const char* kInitImport =
                "?initialiseResourceGroup@ResourceGroupManager@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z";
            constexpr const char* kGetSingletonImport = "?getSingleton@ResourceGroupManager@Ogre@@SAAAV12@XZ";

            struct GateLayout
            {
                uint32_t clearCall;
                uint32_t initCall;
                uint32_t skip;
            };
            constexpr GateLayout kWideGateLayout = {0x20, 0x55, 0x6A};  // main, IA, MP
            constexpr GateLayout kListGateLayout = {0x1D, 0x52, 0x67};
            constexpr GateLayout kCampGateLayout = {0x23, 0x5B, 0x70};
            // Inside the main gate block: the string ctor call, getSingleton
            // and the string dtor call that follows clearResourceGroup.
            constexpr uint32_t kGateCtorCall = 0x08;
            constexpr uint32_t kGateSingletonCall = 0x18;
            constexpr uint32_t kGateDtorCall = 0x30;
            // The campaign gate block is shifted: string ctor, getSingleton, dtor.
            constexpr uint32_t kCampCtorCall = 0x0B;
            constexpr uint32_t kCampSingletonCall = 0x1B;
            constexpr uint32_t kCampDtorCall = 0x33;

            struct StoreSite
            {
                uint32_t address = 0;
                uint32_t resume = 0;
            };
            struct GateSite
            {
                uint32_t address = 0;
                uint32_t resume = 0;
                uint32_t skip = 0;
                uint32_t pushImm = 0;
            };

            // Written once at patch time, before any detour exists.
            StoreSite s_mainStore, s_iaStore, s_mpStore, s_listStore, s_campStore;
            GateSite s_mainGate, s_iaGate, s_mpGate, s_listGate, s_campGate;
            uint32_t s_missionCallSite = 0;
            uint32_t s_mpRoomCallSite = 0;

            using MissionMountFn = int(__thiscall*)(void* self, int a, int b);
            using SetterFn = void(__thiscall*)(void* self);
            using StrCtorFn = void*(__thiscall*)(void* str, const char* text);
            using StrDtorFn = void(__thiscall*)(void* str);
            using GetSingletonFn = void*(__cdecl*)();
            using GroupFn = void(__thiscall*)(void* rgm, const void* name);
            using VoidFn = void(__cdecl*)();

            MissionMountFn s_missionMount = nullptr;
            SetterFn s_mpSetter = nullptr;
            StrCtorFn s_strCtor = nullptr;
            StrDtorFn s_strDtor = nullptr;
            VoidFn s_preRebuild = nullptr;
            VoidFn s_postRebuild = nullptr;
            uint32_t s_singletonSlot = 0;
            uint32_t s_clearSlot = 0;
            uint32_t s_initSlot = 0;
            const char* s_literal = nullptr;

            // UI thread only: the shell and the mission mount run on it.
            State s_state;              // held / pending / pendingMission, see the policy header
            int s_gateDecision = 0;     // scratch between the call and popad

            const char* ModeName(int mode)
            {
                switch (mode)
                {
                case kModeMission: return "mission";
                case kModeIa: return "instant action";
                case kModeMp: return "multiplayer";
                case kModeList: return "campaign list";
                case kModeMain: return "main";
                default: return "unknown";
                }
            }

            bool ReadMode(void* self, int& mode)
            {
                __try
                {
                    mode = *reinterpret_cast<const int*>(static_cast<const uint8_t*>(self) + kModeOffset);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            void __cdecl OnModeStore(void* self, int target)
            {
                int before = -1;
                if (!ReadMode(self, before)) before = -1;
                s_state.storeTarget = target;
                s_state.storeBefore = before;
            }

            // Returns 1 to jump over the clear+initialise block.
            int __cdecl DecideGate(int target)
            {
                const GateResult r = DecideShellGate(s_state, target);
                switch (r.reason)
                {
                case GateReason::CampaignBack:
                    LogShimA(LogLevel::Info, kComponent, "campaign back: rebuild skipped (enter was deferred) -> %s%s",
                             ModeName(target), s_state.pending ? ", catch-up pending" : "");
                    break;
                case GateReason::ShellSkipped:
                case GateReason::ShellDeferred:
                    LogShimA(LogLevel::Info, kComponent, "%s -> %s: Modable rebuild %s (group holds the main set)",
                             ModeName(r.before), ModeName(target), s_state.pending ? "deferred" : "skipped");
                    break;
                default:
                    LogShimA(LogLevel::Info, kComponent, "%s -> %s: Modable rebuild kept (group held %s)",
                             ModeName(r.before), ModeName(target), ModeName(r.held));
                    break;
                }
                return r.skip ? 1 : 0;
            }

            // Campaign setter B (mode 0). Returns 1 to jump over the block.
            int __cdecl DecideCampaignGateCall()
            {
                const GateResult r = DecideCampaignGate(s_state);
                if (r.skip)
                    LogShimA(LogLevel::Info, kComponent, "campaign enter: Modable rebuild deferred (group holds %s)",
                             ModeName(r.held));
                else
                    LogShimA(LogLevel::Info, kComponent, "mission mount: campaign setter rebuilds Modable (group held %s)",
                             ModeName(r.held));
                return r.skip ? 1 : 0;
            }

            void RunGroupCall(uint32_t slot)
            {
                alignas(8) uint8_t name[32] = {};
                s_strCtor(name, s_literal);
                void* rgm = reinterpret_cast<GetSingletonFn>(*reinterpret_cast<void**>(s_singletonSlot))();
                reinterpret_cast<GroupFn>(*reinterpret_cast<void**>(slot))(rgm, name);
                s_strDtor(name);
            }

            void RebuildNow()
            {
                s_preRebuild();
                RunGroupCall(s_clearSlot);
                RunGroupCall(s_initSlot);
                s_postRebuild();
            }

            // Same order as the setters: pre, clear, initialise, post.
            void Flush(void* self, const char* where)
            {
                if (!s_state.pending) return;
                s_state.pending = false;
                int mode = -1;
                if (!ReadMode(self, mode))
                {
                    s_state.held = kHeldUnknown;
                    return;
                }
                if (mode == kModeMission)
                {
                    // A mission setter ran its own (stock) rebuild.
                    s_state.held = kModeMission;
                    LogShimA(LogLevel::Info, kComponent, "%s: mission mount rebuilt the group itself", where);
                    return;
                }
                if (mode == s_state.held) return;
                const ULONGLONG start = GetTickCount64();
                RebuildNow();
                LogShimA(LogLevel::Info, kComponent, "%s: deferred Modable rebuild for %s (held %s) took %llu ms",
                         where, ModeName(mode), ModeName(s_state.held), GetTickCount64() - start);
                s_state.held = mode;
            }

            // Replaces `call 0x0076E6C0` (thiscall, 2 args, ret 8) in 0x007647C0.
            int __fastcall MissionMountHook(void* self, void* /*edx*/, int a, int b)
            {
                if (BeginMissionMount(s_state))
                {
                    const ULONGLONG start = GetTickCount64();
                    RebuildNow();
                    LogShimA(LogLevel::Info, kComponent, "mission mount: forced deferred Modable rebuild took %llu ms",
                             GetTickCount64() - start);
                }
                const int result = s_missionMount(self, a, b);
                FinishMissionMount(s_state);
                Flush(self, "mission mount");
                return result;
            }

            // Replaces `call 0x0076A240` (thiscall, plain ret) in the screen
            // factory's case 0xF. The lounge (0xE) already set mode 2, so the
            // setter usually returns at its guard; the room's vehicle preview
            // needs the multiplayer set built.
            void __fastcall MpRoomMountHook(void* self, void* /*edx*/)
            {
                s_mpSetter(self);
                Flush(self, "MP game room");
            }

            // ECX is `this` at every store site (loaded by the preceding mov).
#define DMR_STORE_STUB(Fn, Mode, Site)                \
            void __declspec(naked) Fn()               \
            {                                         \
                __asm pushfd                          \
                __asm pushad                          \
                __asm push Mode                       \
                __asm push ecx                        \
                __asm call OnModeStore                \
                __asm add esp, 8                      \
                __asm popad                           \
                __asm popfd                           \
                __asm mov dword ptr [ecx + 0x8C], Mode \
                __asm jmp dword ptr [Site.resume]     \
            }
            DMR_STORE_STUB(MainStoreStub, 4, s_mainStore)
            DMR_STORE_STUB(IaStoreStub, 1, s_iaStore)
            DMR_STORE_STUB(MpStoreStub, 2, s_mpStore)
            DMR_STORE_STUB(ListStoreStub, 3, s_listStore)
            DMR_STORE_STUB(CampStoreStub, 0, s_campStore)
#undef DMR_STORE_STUB

            // Flags are dead at both destinations: site+5 is `lea ecx; call`
            // and the skip target is a call, so the cmp after popfd is safe.
            void __declspec(naked) MainGateStub()
            {
                __asm
                {
                    pushfd
                    pushad
                    push 4
                    call DecideGate
                    add  esp, 4
                    mov  dword ptr [s_gateDecision], eax
                    popad
                    popfd
                    cmp  dword ptr [s_gateDecision], 0
                    jne  skip_block
                    push dword ptr [s_mainGate.pushImm]   // replay push "Modable"
                    jmp  dword ptr [s_mainGate.resume]
                skip_block:
                    jmp  dword ptr [s_mainGate.skip]
                }
            }

            void __declspec(naked) IaGateStub()
            {
                __asm
                {
                    pushfd
                    pushad
                    push 1
                    call DecideGate
                    add  esp, 4
                    mov  dword ptr [s_gateDecision], eax
                    popad
                    popfd
                    cmp  dword ptr [s_gateDecision], 0
                    jne  skip_block
                    push dword ptr [s_iaGate.pushImm]
                    jmp  dword ptr [s_iaGate.resume]
                skip_block:
                    jmp  dword ptr [s_iaGate.skip]
                }
            }

            void __declspec(naked) MpGateStub()
            {
                __asm
                {
                    pushfd
                    pushad
                    push 2
                    call DecideGate
                    add  esp, 4
                    mov  dword ptr [s_gateDecision], eax
                    popad
                    popfd
                    cmp  dword ptr [s_gateDecision], 0
                    jne  skip_block
                    push dword ptr [s_mpGate.pushImm]
                    jmp  dword ptr [s_mpGate.resume]
                skip_block:
                    jmp  dword ptr [s_mpGate.skip]
                }
            }

            void __declspec(naked) ListGateStub()
            {
                __asm
                {
                    pushfd
                    pushad
                    push 3
                    call DecideGate
                    add  esp, 4
                    mov  dword ptr [s_gateDecision], eax
                    popad
                    popfd
                    cmp  dword ptr [s_gateDecision], 0
                    jne  skip_block
                    push dword ptr [s_listGate.pushImm]
                    jmp  dword ptr [s_listGate.resume]
                skip_block:
                    jmp  dword ptr [s_listGate.skip]
                }
            }

            void __declspec(naked) CampGateStub()
            {
                __asm
                {
                    pushfd
                    pushad
                    call DecideCampaignGateCall
                    mov  dword ptr [s_gateDecision], eax
                    popad
                    popfd
                    cmp  dword ptr [s_gateDecision], 0
                    jne  skip_block
                    push dword ptr [s_campGate.pushImm]
                    jmp  dword ptr [s_campGate.resume]
                skip_block:
                    jmp  dword ptr [s_campGate.skip]
                }
            }

            bool ReadBytes(uint32_t address, void* out, size_t len)
            {
                __try
                {
                    memcpy(out, reinterpret_cast<const void*>(static_cast<uintptr_t>(address)), len);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool ReadU32(uint32_t address, uint32_t& out) { return ReadBytes(address, &out, sizeof(out)); }

            // Target of the E8 call at `address`, or 0.
            uint32_t CallTarget(uint32_t address)
            {
                uint8_t op = 0;
                uint32_t rel = 0;
                if (!ReadBytes(address, &op, 1) || op != 0xE8 || !ReadU32(address + 1, rel)) return 0;
                return address + 5 + rel;
            }

            // Finds the exe's IAT slot for OgreMain.dll!importName by walking its
            // import directory by name. That proves which function a `call [slot]`
            // reaches without trusting the loader's bound value.
            uint32_t FindOgreImportSlot(const char* importName)
            {
                __try
                {
                    auto* base = reinterpret_cast<const uint8_t*>(GetModuleHandleA(nullptr));
                    if (!base) return 0;
                    auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(base);
                    if (dos->e_magic != IMAGE_DOS_SIGNATURE) return 0;
                    auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS32*>(base + dos->e_lfanew);
                    if (nt->Signature != IMAGE_NT_SIGNATURE) return 0;
                    const IMAGE_DATA_DIRECTORY& dir = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
                    if (!dir.VirtualAddress) return 0;
                    for (auto* d = reinterpret_cast<const IMAGE_IMPORT_DESCRIPTOR*>(base + dir.VirtualAddress); d->Name; ++d)
                    {
                        if (_stricmp(reinterpret_cast<const char*>(base + d->Name), "OgreMain.dll") != 0) continue;
                        if (!d->OriginalFirstThunk || !d->FirstThunk) return 0;
                        auto* names = reinterpret_cast<const IMAGE_THUNK_DATA32*>(base + d->OriginalFirstThunk);
                        for (uint32_t i = 0; names[i].u1.AddressOfData; ++i)
                        {
                            if (IMAGE_SNAP_BY_ORDINAL32(names[i].u1.Ordinal)) continue;
                            auto* byName = reinterpret_cast<const IMAGE_IMPORT_BY_NAME*>(base + names[i].u1.AddressOfData);
                            if (strcmp(reinterpret_cast<const char*>(byName->Name), importName) == 0)
                                return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(base) + d->FirstThunk + i * sizeof(IMAGE_THUNK_DATA32));
                        }
                        return 0;
                    }
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                }
                return 0;
            }

            bool CheckIndirectCall(uint32_t address, uint32_t expectedSlot)
            {
                uint8_t op[2] = {};
                uint32_t slot = 0;
                return expectedSlot && ReadBytes(address, op, 2) && op[0] == 0xFF && op[1] == 0x15 &&
                       ReadU32(address + 2, slot) && slot == expectedSlot;
            }

            void* PrepareStore(const std::string& name, uint32_t address, int mode, StoreSite& site, void* stub,
                               size_t& stolenLen)
            {
                const uint8_t expected[10] = {0xC7, 0x81, 0x8C, 0x00, 0x00, 0x00, static_cast<uint8_t>(mode), 0x00, 0x00, 0x00};
                uint8_t actual[10] = {};
                if (!ReadBytes(address, actual, sizeof(actual)) || memcmp(actual, expected, sizeof(actual)) != 0)
                {
                    LogShimA(LogLevel::Warn, kComponent, "%s: 0x%08X is not mov [ecx+8Ch],%d; standing down",
                             name.c_str(), address, mode);
                    return nullptr;
                }
                site.address = address;
                site.resume = address + 10;
                stolenLen = 10;
                return stub;
            }

            void* PrepareGate(const std::string& name, uint32_t address, const GateLayout& layout, GateSite& site,
                              void* stub, size_t& stolenLen)
            {
                uint8_t push = 0;
                uint32_t imm = 0;
                char literal[8] = {};
                const char* why = nullptr;
                if (!ReadBytes(address, &push, 1) || push != 0x68 || !ReadU32(address + 1, imm))
                    why = "site is not push imm32";
                else if (!ReadBytes(imm, literal, sizeof(literal)) || memcmp(literal, "Modable", 8) != 0)
                    why = "pushed literal is not \"Modable\"";
                else if (!CheckIndirectCall(address + layout.clearCall, FindOgreImportSlot(kClearImport)))
                    why = "clear call is not OgreMain clearResourceGroup";
                else if (!CheckIndirectCall(address + layout.initCall, FindOgreImportSlot(kInitImport)))
                    why = "initialise call is not OgreMain initialiseResourceGroup";
                else if (!CallTarget(address + layout.skip))
                    why = "skip target is not a call";
                if (why)
                {
                    LogShimA(LogLevel::Warn, kComponent, "%s: 0x%08X %s; standing down", name.c_str(), address, why);
                    return nullptr;
                }
                site.address = address;
                site.resume = address + 5;
                site.skip = address + layout.skip;
                site.pushImm = imm;
                stolenLen = 5;
                return stub;
            }

            // REL32 sites: `address` is the call's rel32 operand.
            void* PrepareCall(const std::string& name, uint32_t address, uint32_t& site, void* hook, size_t& stolenLen)
            {
                if (!CallTarget(address - 1))
                {
                    LogShimA(LogLevel::Warn, kComponent, "%s: 0x%08X is not a rel32 call; standing down", name.c_str(),
                             address - 1);
                    return nullptr;
                }
                site = address - 1;
                stolenLen = 4;
                return hook;
            }
        }

        bool IsCampaignPatchName(const char* name)
        {
            return name && (strcmp(name, kCampStore) == 0 || strcmp(name, kCampGate) == 0);
        }

        bool IsPatchName(const char* name)
        {
            if (!name) return false;
            for (const char* n : {kMainStore, kMainGate, kIaStore, kIaGate, kMpStore, kMpGate, kListStore, kListGate,
                                  kMissionCall, kMpRoomCall})
                if (strcmp(name, n) == 0) return true;
            return false;
        }

        void* PrepareSite(const std::string& name, uint32_t address, size_t& stolenLen)
        {
            stolenLen = 0;
            if (name == kMainStore) return PrepareStore(name, address, kModeMain, s_mainStore, (void*)MainStoreStub, stolenLen);
            if (name == kIaStore) return PrepareStore(name, address, kModeIa, s_iaStore, (void*)IaStoreStub, stolenLen);
            if (name == kMpStore) return PrepareStore(name, address, kModeMp, s_mpStore, (void*)MpStoreStub, stolenLen);
            if (name == kListStore) return PrepareStore(name, address, kModeList, s_listStore, (void*)ListStoreStub, stolenLen);
            if (name == kMainGate) return PrepareGate(name, address, kWideGateLayout, s_mainGate, (void*)MainGateStub, stolenLen);
            if (name == kIaGate) return PrepareGate(name, address, kWideGateLayout, s_iaGate, (void*)IaGateStub, stolenLen);
            if (name == kMpGate) return PrepareGate(name, address, kWideGateLayout, s_mpGate, (void*)MpGateStub, stolenLen);
            if (name == kListGate) return PrepareGate(name, address, kListGateLayout, s_listGate, (void*)ListGateStub, stolenLen);
            if (name == kCampStore) return PrepareStore(name, address, kModeMission, s_campStore, (void*)CampStoreStub, stolenLen);
            if (name == kCampGate) return PrepareGate(name, address, kCampGateLayout, s_campGate, (void*)CampGateStub, stolenLen);
            if (name == kMissionCall) return PrepareCall(name, address, s_missionCallSite, (void*)MissionMountHook, stolenLen);
            if (name == kMpRoomCall) return PrepareCall(name, address, s_mpRoomCallSite, (void*)MpRoomMountHook, stolenLen);
            return nullptr;
        }

        bool FinalizeCampaignSites()
        {
            const char* why = nullptr;
            if (!s_campStore.address || !s_campGate.address || s_campGate.address <= s_campStore.address ||
                s_campGate.address - s_campStore.address > 0x500)
                why = "the campaign gate is not inside its store's setter";
            else if (CallTarget(s_campGate.skip) != reinterpret_cast<uintptr_t>(s_postRebuild))
                why = "the campaign gate skips to a different post-rebuild helper";
            else if (CallTarget(s_campGate.address + kCampCtorCall) != reinterpret_cast<uintptr_t>(s_strCtor) ||
                     CallTarget(s_campGate.address + kCampDtorCall) != reinterpret_cast<uintptr_t>(s_strDtor))
                why = "the campaign gate uses different string helpers";
            else if (!CheckIndirectCall(s_campGate.address + kCampSingletonCall, s_singletonSlot))
                why = "the campaign gate does not call ResourceGroupManager::getSingleton";
            if (why)
            {
                LogShimA(LogLevel::Warn, kComponent, "%s; campaign enter keeps the stock rebuild", why);
                return false;
            }
            return true;
        }

        bool FinalizeSites()
        {
            const char* why = nullptr;
            const StoreSite* stores[] = {&s_mainStore, &s_iaStore, &s_mpStore, &s_listStore};
            const GateSite* gates[] = {&s_mainGate, &s_iaGate, &s_mpGate, &s_listGate};
            for (int i = 0; i < 4 && !why; ++i)
            {
                // A gate must sit after its own store, inside the same setter.
                if (!stores[i]->address || !gates[i]->address || gates[i]->address <= stores[i]->address ||
                    gates[i]->address - stores[i]->address > 0x300)
                    why = "a gate is not inside its store's setter";
            }
            const uint32_t missionMount = s_missionCallSite ? CallTarget(s_missionCallSite) : 0;
            const uint32_t mpSetter = s_mpRoomCallSite ? CallTarget(s_mpRoomCallSite) : 0;
            if (!why && !missionMount)
                why = "mission mount call unresolved";
            // The MP setter's store sits 0x4D into it on GOG 2.2.301.
            if (!why && (!mpSetter || mpSetter >= s_mpStore.address || s_mpStore.address - mpSetter > 0x80))
                why = "MP room call does not reach the multiplayer mount setter";
            const uint32_t pre = CallTarget(s_mainStore.resume);
            const uint32_t post = CallTarget(s_mainGate.skip);
            const uint32_t ctor = CallTarget(s_mainGate.address + kGateCtorCall);
            const uint32_t dtor = CallTarget(s_mainGate.address + kGateDtorCall);
            const uint32_t singleton = FindOgreImportSlot(kGetSingletonImport);
            if (!why && (!pre || !post || !ctor || !dtor))
                why = "rebuild helpers (pre/post, string ctor/dtor) unresolved";
            if (!why && !CheckIndirectCall(s_mainGate.address + kGateSingletonCall, singleton))
                why = "main gate does not call ResourceGroupManager::getSingleton";
            // Every gate calls the same pre/post pair and string helpers.
            for (int i = 1; i < 4 && !why; ++i)
                if (CallTarget(gates[i]->skip) != post || CallTarget(gates[i]->address + kGateCtorCall) != ctor)
                    why = "gates disagree on the post-rebuild or string helpers";
            if (why)
            {
                LogShimA(LogLevel::Warn, kComponent, "%s; standing down", why);
                return false;
            }
            s_missionMount = reinterpret_cast<MissionMountFn>(static_cast<uintptr_t>(missionMount));
            s_mpSetter = reinterpret_cast<SetterFn>(static_cast<uintptr_t>(mpSetter));
            s_preRebuild = reinterpret_cast<VoidFn>(static_cast<uintptr_t>(pre));
            s_postRebuild = reinterpret_cast<VoidFn>(static_cast<uintptr_t>(post));
            s_strCtor = reinterpret_cast<StrCtorFn>(static_cast<uintptr_t>(ctor));
            s_strDtor = reinterpret_cast<StrDtorFn>(static_cast<uintptr_t>(dtor));
            s_singletonSlot = singleton;
            s_clearSlot = FindOgreImportSlot(kClearImport);
            s_initSlot = FindOgreImportSlot(kInitImport);
            s_literal = reinterpret_cast<const char*>(static_cast<uintptr_t>(s_mainGate.pushImm));
            LogShimA(LogLevel::Info, kComponent,
                     "armed: mission mount 0x%08X, MP setter 0x%08X, pre 0x%08X, post 0x%08X", missionMount, mpSetter,
                     pre, post);
            return true;
        }
    }
}
