// campaign_list_light_mount.cpp
// BZR Open Shim - Custom Campaigns list without a Modable rebuild.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// See include/campaign_list_light_mount.h for what and why.
//
// Both mount setters share one shape (GOG Redux 2.2.301):
//
//     cmp  dword [eax+8Ch], N ; jne +5 ; jmp <epilogue>   stock same-mode guard
//     mov  ecx, [ebp-..]                                   this
//     mov  dword [ecx+8Ch], N   <- Store site, 10 bytes
//     ... unmount, remount through Redux's file system ...
//     push "Modable"            <- Gate site, 5 bytes
//     ... std::string, getSingleton, call [clearResourceGroup]
//     ... std::string, getSingleton, call [initialiseResourceGroup]
//     call 0x00434440           <- skip target (Gate +0x67 / +0x6A)
//
// The two std::string temporaries are built and destroyed between Gate and the
// skip target, so the stack and the SEH state byte are the same at both ends
// (0 in the list setter, -1 in the main one): jumping over the block is
// stack-neutral and leaves nothing half built.
//
// Store stubs replay the mode store after recording the mode it replaces. Gate
// stubs either replay `push "Modable"` and resume, or jump to the skip target.
// Each gate consumes only its own flag, armed by its own store, so a gate never
// skips on a decision made for another setter.

#include "campaign_list_light_mount.h"

#include <windows.h>

#include <cstring>

#include "shim_log.h"

namespace BZROpenShim
{
    namespace CampaignListLightMount
    {
        namespace
        {
            constexpr const char* kListStore = "Campaign List Light Mount List Store";
            constexpr const char* kListGate  = "Campaign List Light Mount List Gate";
            constexpr const char* kMainStore = "Campaign List Light Mount Main Store";
            constexpr const char* kMainGate  = "Campaign List Light Mount Main Gate";

            constexpr int kModeList = 3;
            constexpr int kModeMain = 4;
            constexpr uint32_t kModeOffset = 0x8C;

            constexpr const char* kClearImport =
                "?clearResourceGroup@ResourceGroupManager@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z";
            constexpr const char* kInitImport =
                "?initialiseResourceGroup@ResourceGroupManager@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z";

            // Per-setter gate layout: offsets of the two `call [imp]` and of the
            // skip target, relative to the Gate site.
            struct GateLayout
            {
                uint32_t clearCall;
                uint32_t initCall;
                uint32_t skip;
            };
            constexpr GateLayout kListGateLayout = {0x1D, 0x52, 0x67};
            constexpr GateLayout kMainGateLayout = {0x20, 0x55, 0x6A};

            // Resume/skip addresses and the replayed push immediates. Written once
            // at patch time, before any detour exists.
            uint32_t s_listStoreResume = 0;
            uint32_t s_mainStoreResume = 0;
            uint32_t s_listGateResume = 0;
            uint32_t s_listGateSkip = 0;
            uint32_t s_listGatePush = 0;
            uint32_t s_mainGateResume = 0;
            uint32_t s_mainGateSkip = 0;
            uint32_t s_mainGatePush = 0;

            // UI thread only: the shell runs both setters from its frame.
            bool s_listSkipArmed = false;
            bool s_mainSkipArmed = false;
            bool s_lightActive = false;    // the list mount is up with a stale group
            void* s_lightOwner = nullptr;  // resource manager that took the light mount
            int s_lightFromMode = -1;      // mode it replaced
            int s_gateDecision = 0;        // scratch between the call and popad

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
                const bool readable = ReadMode(self, before);
                if (target == kModeList)
                {
                    // Entering the list: keep whatever the group holds, from any
                    // mode. The campaign's own setter (mode 0) still rebuilds.
                    s_listSkipArmed = readable;
                    s_lightActive = readable;
                    s_lightOwner = self;
                    s_lightFromMode = before;
                    LogShimA(LogLevel::Info, "CampaignListLightMount",
                             "list mount: mode %d -> 3, Modable rebuild %s", before,
                             readable ? "skipped" : "kept (mode unreadable)");
                    return;
                }
                if (target == kModeMain)
                {
                    // Back to the main mount: the group is still the main set
                    // only if the list was entered from mode 4 and nothing has
                    // rebuilt it since (any other setter moves the mode off 3).
                    const bool skip = readable && s_lightActive && s_lightOwner == self &&
                                      before == kModeList && s_lightFromMode == kModeMain;
                    s_mainSkipArmed = skip;
                    if (s_lightActive || skip)
                        LogShimA(LogLevel::Info, "CampaignListLightMount",
                                 "main mount: mode %d -> 4 (list entered from %d), Modable rebuild %s",
                                 before, s_lightFromMode, skip ? "skipped" : "kept");
                    s_lightActive = false;
                    s_lightOwner = nullptr;
                    s_lightFromMode = -1;
                }
            }

            int __cdecl ConsumeListSkip()
            {
                const bool skip = s_listSkipArmed;
                s_listSkipArmed = false;
                return skip ? 1 : 0;
            }

            int __cdecl ConsumeMainSkip()
            {
                const bool skip = s_mainSkipArmed;
                s_mainSkipArmed = false;
                return skip ? 1 : 0;
            }

            // ECX is `this` at both store sites (loaded by the preceding mov).
            void __declspec(naked) ListStoreStub()
            {
                __asm
                {
                    pushfd
                    pushad
                    push 3
                    push ecx
                    call OnModeStore
                    add  esp, 8
                    popad
                    popfd
                    mov  dword ptr [ecx + 0x8C], 3   // replay the stolen store
                    jmp  dword ptr [s_listStoreResume]
                }
            }

            void __declspec(naked) MainStoreStub()
            {
                __asm
                {
                    pushfd
                    pushad
                    push 4
                    push ecx
                    call OnModeStore
                    add  esp, 8
                    popad
                    popfd
                    mov  dword ptr [ecx + 0x8C], 4   // replay the stolen store
                    jmp  dword ptr [s_mainStoreResume]
                }
            }

            // Flags are dead at both destinations: site+5 is `lea ecx; call`
            // and the skip target is a call, so the cmp after popfd is safe.
            void __declspec(naked) ListGateStub()
            {
                __asm
                {
                    pushfd
                    pushad
                    call ConsumeListSkip
                    mov  dword ptr [s_gateDecision], eax
                    popad
                    popfd
                    cmp  dword ptr [s_gateDecision], 0
                    jne  skip_block
                    push dword ptr [s_listGatePush]   // replay push "Modable"
                    jmp  dword ptr [s_listGateResume]
                skip_block:
                    jmp  dword ptr [s_listGateSkip]
                }
            }

            void __declspec(naked) MainGateStub()
            {
                __asm
                {
                    pushfd
                    pushad
                    call ConsumeMainSkip
                    mov  dword ptr [s_gateDecision], eax
                    popad
                    popfd
                    cmp  dword ptr [s_gateDecision], 0
                    jne  skip_block
                    push dword ptr [s_mainGatePush]   // replay push "Modable"
                    jmp  dword ptr [s_mainGateResume]
                skip_block:
                    jmp  dword ptr [s_mainGateSkip]
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

            void* PrepareStore(const std::string& name, uint32_t address, int mode, uint32_t& resume, void* stub,
                               size_t& stolenLen)
            {
                const uint8_t expected[10] = {0xC7, 0x81, 0x8C, 0x00, 0x00, 0x00, static_cast<uint8_t>(mode), 0x00, 0x00, 0x00};
                uint8_t actual[10] = {};
                if (!ReadBytes(address, actual, sizeof(actual)) || memcmp(actual, expected, sizeof(actual)) != 0)
                {
                    LogShimA(LogLevel::Warn, "CampaignListLightMount", "%s: 0x%08X is not mov [ecx+8Ch],%d; standing down",
                             name.c_str(), address, mode);
                    return nullptr;
                }
                resume = address + 10;
                stolenLen = 10;
                return stub;
            }

            void* PrepareGate(const std::string& name, uint32_t address, const GateLayout& layout, uint32_t& resume,
                              uint32_t& skip, uint32_t& pushImm, void* stub, size_t& stolenLen)
            {
                uint8_t push = 0, skipOp = 0;
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
                else if (!ReadBytes(address + layout.skip, &skipOp, 1) || skipOp != 0xE8)
                    why = "skip target is not a call";
                if (why)
                {
                    LogShimA(LogLevel::Warn, "CampaignListLightMount", "%s: 0x%08X %s; standing down", name.c_str(),
                             address, why);
                    return nullptr;
                }
                resume = address + 5;
                skip = address + layout.skip;
                pushImm = imm;
                stolenLen = 5;
                return stub;
            }
        }

        bool IsPatchName(const char* name)
        {
            return name && (strcmp(name, kListStore) == 0 || strcmp(name, kListGate) == 0 ||
                            strcmp(name, kMainStore) == 0 || strcmp(name, kMainGate) == 0);
        }

        void* PrepareSite(const std::string& name, uint32_t address, size_t& stolenLen)
        {
            stolenLen = 0;
            if (name == kListStore)
                return PrepareStore(name, address, kModeList, s_listStoreResume, (void*)ListStoreStub, stolenLen);
            if (name == kMainStore)
                return PrepareStore(name, address, kModeMain, s_mainStoreResume, (void*)MainStoreStub, stolenLen);
            if (name == kListGate)
                return PrepareGate(name, address, kListGateLayout, s_listGateResume, s_listGateSkip, s_listGatePush,
                                   (void*)ListGateStub, stolenLen);
            if (name == kMainGate)
                return PrepareGate(name, address, kMainGateLayout, s_mainGateResume, s_mainGateSkip, s_mainGatePush,
                                   (void*)MainGateStub, stolenLen);
            return nullptr;
        }
    }
}
