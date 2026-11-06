// Optional per-manifest campaign IDs. Unannotated campaigns keep their
// original directory identity and existing progress. Resource paths stay stock.
#include "campaign_manifest_id.h"
#include "bzr_string.h"
#include "hook_engine.h"
#include "patcher.h"

#include <windows.h>
#include <cstring>

namespace BZROpenShim::CampaignManifestId
{
    namespace
    {
        using AssignString = void* (__thiscall*)(void*, const BzrString*);
        AssignString originalAssign = nullptr;

        void* __stdcall AssignKey(void* destination, const BzrString* stockKey,
                                  const char* manifestPath)
        {
            // The caller owns a 1024-byte terminated copy of the exact INI
            // being parsed. Win32 profile reads also work under Wine/Proton.
            char id[66] = {};
            const DWORD size = GetPrivateProfileStringA(
                "WORKSHOP", "campaignID", "", id, sizeof(id), manifestPath);
            if (!ValidId(id, size))
            {
                if (size) Log(L"[CAMPAIGN-ID] invalid campaignID in %hs; retaining folder identity\n", manifestPath);
                return originalAssign(destination, stockKey);
            }

            // Borrow the bytes only for the original engine assignment. That
            // routine allocates/copies using the game's own CRT. No shim heap
            // pointer or destructor is transferred into an engine object.
            BzrString borrowed = {};
            borrowed.size = size;
            borrowed.capacity = size <= 15 ? 15 : size;
            if (size <= 15) std::memcpy(borrowed.small, id, size + 1);
            else borrowed.heap = id;
            void* result = originalAssign(destination, &borrowed);
            Log(L"[CAMPAIGN-ID] %hs: %hs -> %hs\n", manifestPath, BzrStringData(stockKey), id);
            return result;
        }

        // Replaces one thiscall string assignment in the campaign-only parser
        // branch. ECX is the destination and [ESP+4] is the stock key. The
        // guarded caller frame keeps the current INI path at EBP-0x410.
        __declspec(naked) void AssignKeyBridge()
        {
            __asm
            {
                lea eax, [ebp - 0410h]
                push eax
                push dword ptr [esp + 8]
                push ecx
                call AssignKey
                ret 4
            }
        }
    }

    void* PrepareThunk(std::uint32_t callSite)
    {
        const auto expected = HookEngine::ResolveNamedAddress("Campaign Manifest ID String Assignment");
        void* target = HookEngine::ResolveRelCallTarget(callSite);
        // The complete surrounding sequence pins both EBP-relative string
        // objects, not just a common std::string assignment CALL.
        static const unsigned char before[] = {
            0x8D,0x95,0x98,0xE9,0xFF,0xFF,0x52,0x8D,0x8D,0x98,0xE6,0xFF,0xFF
        };
        static const unsigned char after[] = {
            0x8D,0x85,0xB0,0xE9,0xFF,0xFF,0x50,0x8D,0x8D,0xB0,0xE6,0xFF,0xFF
        };
        bool matches = false;
        __try
        {
            matches = callSite >= sizeof(before) && expected &&
                reinterpret_cast<std::uintptr_t>(target) == expected &&
                std::memcmp(reinterpret_cast<const void*>(callSite - sizeof(before)), before, sizeof(before)) == 0 &&
                std::memcmp(reinterpret_cast<const void*>(callSite + 5), after, sizeof(after)) == 0;
        }
        __except (EXCEPTION_EXECUTE_HANDLER) { matches = false; }
        if (!matches)
        {
            Log(L"[CAMPAIGN-ID] caller identity failed; retaining stock campaign registry\n");
            return nullptr;
        }
        originalAssign = reinterpret_cast<AssignString>(target);
        Log(L"[CAMPAIGN-ID] guarded manifest identity hook prepared; absent campaignID retains stock behavior\n");
        return reinterpret_cast<void*>(&AssignKeyBridge);
    }
}
