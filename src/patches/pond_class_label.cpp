#include "pond_class_label.h"

#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "shim_log.h"
#include "legacy_tug_odf.inl"

#include <Windows.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>

namespace BZROpenShim
{
    namespace
    {
        constexpr uint32_t kPondSignature = 0x504F4E44u; // 'POND'
        constexpr uint32_t kPondClassRank = 5;
        constexpr size_t kClassSignatureOffset = 0x14;
        constexpr size_t kClassLabelOffset = 0x18;
        constexpr size_t kClassRankOffset = 0x1C;
        constexpr size_t kBuildClassDetourLength = 5;
        constexpr size_t kBuildingGetRankDetourLength = 6;

        constexpr char kBuildingClassLabel[] = "i76building";
        constexpr char kPondClassLabel[] = "pond";

        using FnStricmp = int (__cdecl*)(const char*, const char*);
        using FnBuildingBuildClass = void* (__thiscall*)(void*, uint32_t, uint32_t);
        using FnBuildingGetRank = float (__thiscall*)(void*, float, float);
        using FnGetObjectClass = void* (__thiscall*)(void*);

        InlineDetour32 g_BuildClassDetour;
        InlineDetour32 g_GetRankDetour;
        FnStricmp g_OriginalStricmp = nullptr;
        FnBuildingBuildClass g_OriginalBuildClass = nullptr;
        FnBuildingGetRank g_OriginalGetRank = nullptr;
        bool g_LabelCompareCallPatched = false;
        bool g_InstallFailureLogged = false;

        // The class-label comparison and the immediately following virtual
        // BuildClass call are synchronous. Clear this before entering stock
        // BuildingClass construction so recursive baseName lookups remain
        // ordinary building lookups.
        thread_local bool g_PondBuildPending = false;

        bool IsPondClassInterface(void* classInterface)
        {
            if (!classInterface)
                return false;

            __try
            {
                void** vtable = *reinterpret_cast<void***>(classInterface);
                if (!vtable || !vtable[0])
                    return false;

                void* objectClass =
                    reinterpret_cast<FnGetObjectClass>(vtable[0])(classInterface);
                return objectClass &&
                    *reinterpret_cast<const uint32_t*>(
                        reinterpret_cast<const uint8_t*>(objectClass) +
                        kClassSignatureOffset) == kPondSignature;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        int __cdecl PondClassLabelCompareHook(const char* registeredLabel,
                                               const char* odfLabel)
        {
            if (!g_OriginalStricmp)
                return 1;

            const int stockResult = g_OriginalStricmp(registeredLabel, odfLabel);
            if (stockResult == 0 || !registeredLabel || !odfLabel)
                return stockResult;

            if (g_OriginalStricmp(registeredLabel, kBuildingClassLabel) == 0 &&
                g_OriginalStricmp(odfLabel, kPondClassLabel) == 0)
            {
                g_PondBuildPending = true;
                return 0;
            }

            return stockResult;
        }

        void* __fastcall PondBuildingBuildClassHook(void* thisPtr,
                                                    void* /*edx*/,
                                                    uint32_t odfNameLo,
                                                    uint32_t odfNameHi)
        {
            const bool buildPond = g_PondBuildPending;
            g_PondBuildPending = false;

            void* objectClass = g_OriginalBuildClass
                ? g_OriginalBuildClass(thisPtr, odfNameLo, odfNameHi)
                : nullptr;
            if (!buildPond || !objectClass)
                return objectClass;

            __try
            {
                auto* bytes = reinterpret_cast<uint8_t*>(objectClass);
                *reinterpret_cast<uint32_t*>(bytes + kClassSignatureOffset) =
                    kPondSignature;
                *reinterpret_cast<const char**>(bytes + kClassLabelOffset) =
                    kPondClassLabel;
                *reinterpret_cast<uint32_t*>(bytes + kClassRankOffset) =
                    kPondClassRank;

                char odfName[9] = {};
                std::memcpy(odfName, &odfNameLo, sizeof(odfNameLo));
                std::memcpy(odfName + sizeof(odfNameLo),
                            &odfNameHi, sizeof(odfNameHi));
                LogShimA(LogLevel::Info, "POND",
                    "built ODF %.8s as POND class=%p rank=%u",
                    odfName,
                    objectClass,
                    static_cast<unsigned>(kPondClassRank));
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                LogShimA(LogLevel::Warn, "POND",
                    "BuildingClass returned an unreadable class object");
            }

            return objectClass;
        }

        float __fastcall PondBuildingGetRankHook(void* classInterface,
                                                 void* /*edx*/,
                                                 float y,
                                                 float distance)
        {
            // BzE's Pond override is a two-instruction leaf returning -1.0f.
            if (IsPondClassInterface(classInterface))
                return -1.0f;
            return g_OriginalGetRank
                ? g_OriginalGetRank(classInterface, y, distance)
                : -1.0f;
        }

        bool PatchClassLabelCompareCall(uintptr_t callSite)
        {
            uint8_t original[6] = {};
            if (!HookEngine::ReadMemory(
                    static_cast<uint32_t>(callSite), original, sizeof(original)) ||
                original[0] != 0xFF || original[1] != 0x15)
            {
                return false;
            }

            uint32_t iatSlot = 0;
            std::memcpy(&iatSlot, original + 2, sizeof(iatSlot));
            void* importedTarget = nullptr;
            if (!HookEngine::ReadMemory(
                    iatSlot, &importedTarget, sizeof(importedTarget)) ||
                !importedTarget)
            {
                return false;
            }

            const intptr_t displacement =
                reinterpret_cast<intptr_t>(&PondClassLabelCompareHook) -
                static_cast<intptr_t>(callSite + 5);
            if (displacement < std::numeric_limits<int32_t>::min() ||
                displacement > std::numeric_limits<int32_t>::max())
            {
                return false;
            }

            uint8_t patch[6] = { 0xE8, 0, 0, 0, 0, 0x90 };
            const int32_t rel32 = static_cast<int32_t>(displacement);
            std::memcpy(patch + 1, &rel32, sizeof(rel32));

            g_OriginalStricmp = reinterpret_cast<FnStricmp>(importedTarget);
            if (!HookEngine::WriteMemory(
                    static_cast<uint32_t>(callSite), patch, sizeof(patch)))
            {
                g_OriginalStricmp = nullptr;
                return false;
            }
            return true;
        }
    }

    void InstallPondClassLabelSupportIfPossible()
    {
        // The same deferred retry point also owns legacy ODF compatibility
        // hooks that must not run under DllMain. Keep this independent of
        // whether pond support has already finished installing.
        InstallTugOdfToggleIfPossible();

        if (IsPondClassLabelSupportInstalled())
            return;

        const uintptr_t buildClass = HookEngine::ResolveNamedAddress(
            "BuildingClass::BuildClass");
        const uintptr_t getRank = HookEngine::ResolveNamedAddress(
            "Building::GetRank");
        const uintptr_t labelCompareCall = HookEngine::ResolveNamedAddress(
            "GameObjectClass::Find class-label comparison");
        if (!buildClass || !getRank || !labelCompareCall)
            return;

        static const uint8_t buildClassPrologue[kBuildClassDetourLength] =
            { 0x55, 0x8B, 0xEC, 0x6A, 0xFF };
        if (!g_BuildClassDetour.trampoline &&
            !InstallInlineDetour32(
                g_BuildClassDetour,
                buildClass,
                reinterpret_cast<void*>(&PondBuildingBuildClassHook),
                kBuildClassDetourLength,
                buildClassPrologue,
                sizeof(buildClassPrologue)))
        {
            if (!g_InstallFailureLogged)
            {
                LogShimA(LogLevel::Warn, "POND",
                    "BuildingClass::BuildClass detour was not installed");
                g_InstallFailureLogged = true;
            }
            return;
        }
        g_OriginalBuildClass = reinterpret_cast<FnBuildingBuildClass>(
            g_BuildClassDetour.trampoline);

        static const uint8_t getRankPrologue[kBuildingGetRankDetourLength] =
            { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x10 };
        if (!g_GetRankDetour.trampoline &&
            !InstallInlineDetour32(
                g_GetRankDetour,
                getRank,
                reinterpret_cast<void*>(&PondBuildingGetRankHook),
                kBuildingGetRankDetourLength,
                getRankPrologue,
                sizeof(getRankPrologue)))
        {
            if (!g_InstallFailureLogged)
            {
                LogShimA(LogLevel::Warn, "POND",
                    "Building::GetRank detour was not installed");
                g_InstallFailureLogged = true;
            }
            return;
        }
        g_OriginalGetRank = reinterpret_cast<FnBuildingGetRank>(
            g_GetRankDetour.trampoline);

        if (!g_LabelCompareCallPatched)
            g_LabelCompareCallPatched = PatchClassLabelCompareCall(labelCompareCall);
        if (!g_LabelCompareCallPatched)
        {
            if (!g_InstallFailureLogged)
            {
                LogShimA(LogLevel::Warn, "POND",
                    "GameObjectClass::Find label comparison was not patched");
                g_InstallFailureLogged = true;
            }
            return;
        }

        LogShimA(LogLevel::Info, "POND",
            "installed BzE-compatible classLabel=pond support");
    }

    bool IsPondClassLabelSupportInstalled()
    {
        return g_BuildClassDetour.trampoline &&
            g_GetRankDetour.trampoline &&
            g_LabelCompareCallPatched;
    }
}
