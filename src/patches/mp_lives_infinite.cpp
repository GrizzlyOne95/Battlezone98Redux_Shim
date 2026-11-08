// mp_lives_infinite.cpp
// BZR Open Shim - "Infinite" as the sixth step of the multiplayer Lives button.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// See include/mp_lives_infinite.h. GOG Redux 2.2.301, static analysis only.
//
// Label sites: both detour a `call std::string::string(const char*)` (thiscall,
// ecx = destination, one stack argument). The thunk swaps the char* argument for
// "Infinite" when the lives value is 6, then tail-jumps to the original ctor.
//   host click   (generic cycle helper, also used by the player-limit button,
//                where 6 is a real value): [ebp-0x90] is the screen (saved at
//                0x0079BABB), [ebp+0xC] the button, [[ebp+8]] the value; only the
//                Lives button (screen+0x198) is relabelled.
//   lobby refresh (every frame, host and guests): [ebp-0x1D0] is the game info,
//                lives at +0x11C.
// The multi.ini write keeps the number "6" because it uses a different call.
//
// Launch site: replays `mov edx,[ebp+1Ch] / mov eax,[edx+58h]` and, for 6, stores
// 99 into eax and back into the launch block so the following re-read sees 99.

#include "mp_lives_infinite.h"

#include <windows.h>

#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace MpLivesInfinite
    {
        namespace
        {
            constexpr const char* kClickMax = "Infinite Lives Click Max";
            constexpr const char* kClamp = "Infinite Lives Config Clamp";
            constexpr const char* kHostLabel = "Infinite Lives Host Label";
            constexpr const char* kLobbyLabel = "Infinite Lives Lobby Label";
            constexpr const char* kLaunch = "Infinite Lives Launch Fill";

            // Static, never freed: the engine copies it into a std::string.
            const char kInfiniteText[] = "Infinite";

            uint32_t s_stringCtor = 0;
            uint32_t s_launchResume = 0;

            void __declspec(naked) HostLabelThunk()
            {
                __asm
                {
                    // Only the Lives button (screen+0x198); Player Limit (+0x19C)
                    // shares this helper and can legitimately read 6.
                    mov  eax, dword ptr [ebp - 0x90]
                    test eax, eax
                    jz   orig
                    mov  eax, dword ptr [eax + 0x198]
                    cmp  eax, dword ptr [ebp + 0x0C]
                    jne  orig
                    mov  eax, dword ptr [ebp + 8]
                    test eax, eax
                    jz   orig
                    cmp  dword ptr [eax], 6
                    jne  orig
                    mov  dword ptr [esp + 4], offset kInfiniteText
                orig:
                    jmp  dword ptr [s_stringCtor]
                }
            }

            void __declspec(naked) LobbyLabelThunk()
            {
                __asm
                {
                    mov  eax, dword ptr [ebp - 0x1D0]
                    test eax, eax
                    jz   orig
                    cmp  dword ptr [eax + 0x11C], 6
                    jne  orig
                    mov  dword ptr [esp + 4], offset kInfiniteText
                orig:
                    jmp  dword ptr [s_stringCtor]
                }
            }

            void __declspec(naked) LaunchThunk()
            {
                __asm
                {
                    mov  edx, dword ptr [ebp + 0x1C]
                    mov  eax, dword ptr [edx + 0x58]
                    cmp  eax, 6
                    jne  done
                    mov  eax, 99
                    mov  dword ptr [edx + 0x58], eax
                done:
                    jmp  dword ptr [s_launchResume]
                }
            }

            HookEngine::PatchDef* Find(std::vector<HookEngine::PatchDef>& patches, const char* name)
            {
                for (auto& p : patches)
                    if (p.name == name) return &p;
                return nullptr;
            }
        }

        bool IsPatchName(const char* name)
        {
            return name && strncmp(name, "Infinite Lives ", 15) == 0;
        }

        const char* Arm(std::vector<HookEngine::PatchDef>& patches, bool isSteam)
        {
            HookEngine::PatchDef* sites[kSiteCount] = {
                Find(patches, kClickMax), Find(patches, kClamp), Find(patches, kHostLabel),
                Find(patches, kLobbyLabel), Find(patches, kLaunch),
            };
            const char* reason = nullptr;
            for (auto* s : sites)
                if (!s) { reason = "a site is missing from the patch list"; break; }
            if (!reason)
                for (auto* s : sites)
                    if (!s->verified || s->address == 0) { reason = "a site did not verify against this build"; break; }
            if (!reason)
            {
                const uint32_t ctor = HookEngine::ResolveNamedAddress("MpLives::StdStringFromCStr");
                if (ctor == 0) reason = "std::string ctor did not resolve";
                for (int i = 2; i <= 3 && !reason; ++i)
                {
                    void* original = isSteam
                        ? HookEngine::ResolveRelCallTargetWithRetry(sites[i]->address - 1, 300, 10)
                        : HookEngine::ResolveRelCallTarget(sites[i]->address - 1);
                    if (!original || reinterpret_cast<uintptr_t>(original) != ctor)
                        reason = "a label call does not reach the std::string ctor";
                }
                if (!reason) s_stringCtor = ctor;
            }
            if (!reason)
            {
                s_launchResume = sites[4]->address + 6;
                const uint32_t host = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(HostLabelThunk));
                const uint32_t lobby = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(LobbyLabelThunk));
                const uint32_t launch = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(LaunchThunk));
                const int32_t relHost = static_cast<int32_t>(host) - static_cast<int32_t>(sites[2]->address + 4);
                const int32_t relLobby = static_cast<int32_t>(lobby) - static_cast<int32_t>(sites[3]->address + 4);
                sites[2]->payload.resize(4);
                memcpy(sites[2]->payload.data(), &relHost, 4);
                sites[3]->payload.resize(4);
                memcpy(sites[3]->payload.data(), &relLobby, 4);
                sites[4]->payload = HookEngine::MakeJmp5Payload(sites[4]->address, launch, 6);
                return nullptr;
            }
            // ApplyPatches does not read `verified`; an empty payload is what skips a site.
            for (auto* s : sites)
                if (s) { s->verified = false; s->payload.clear(); }
            return reason;
        }
    }
}
