#include "pond_class_label.h"

#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>
#include <unordered_set>

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

        // Redux 2.2.301 Building compatibility anchors. These are deliberately
        // fail-closed below: both constructor entry points must still have the
        // settled MSVC SEH prologue, and ParameterDB::Get(int) must still have
        // a normal function prologue, before any tuggability hook is installed.
        constexpr uintptr_t kBuildingCtorAddress = 0x0047E9C0u;
        constexpr uintptr_t kBuildingClassCtorAddress = 0x0047FFD0u;
        constexpr uintptr_t kParameterDbGetIntAddress = 0x005896C0u;
        constexpr size_t kTuggableCtorDetourLength = 5;

        // ParameterDB hashes are FNV-1a/32 over lowercase names. BuildingClass
        // is already proven in the shipped constructor as 0x91E9360F.
        constexpr uint32_t kBuildingClassSectionHash = 0x91E9360Fu;
        constexpr uint32_t kTuggableKeyHash = 0x93392C60u; // "tuggable"

        constexpr size_t kGameObjectClassPackedNameOffset = 0x30;
        constexpr size_t kGameObjectHandleOffset = 0xDC;
        constexpr size_t kBuildingTuggableHandleOffset = 0x220;

        constexpr char kBuildingClassLabel[] = "i76building";
        constexpr char kPondClassLabel[] = "pond";

        using FnStricmp = int (__cdecl*)(const char*, const char*);
        using FnBuildingBuildClass = void* (__thiscall*)(void*, uint32_t, uint32_t);
        using FnBuildingGetRank = float (__thiscall*)(void*, float, float);
        using FnGetObjectClass = void* (__thiscall*)(void*);
        using FnParameterDbGetInt = int (__cdecl*)(uint32_t, uint32_t, int*, int);
        using FnBuildingClassCtor = void* (__thiscall*)(void*, void*, uint32_t, uint32_t);
        using FnBuildingCtor = void* (__thiscall*)(void*, void*, void*);

        InlineDetour32 g_BuildClassDetour;
        InlineDetour32 g_GetRankDetour;
        InlineDetour32 g_BuildingClassCtorDetour;
        InlineDetour32 g_BuildingCtorDetour;
        FnStricmp g_OriginalStricmp = nullptr;
        FnBuildingBuildClass g_OriginalBuildClass = nullptr;
        FnBuildingGetRank g_OriginalGetRank = nullptr;
        FnParameterDbGetInt g_ParameterDbGetInt = nullptr;
        FnBuildingClassCtor g_OriginalBuildingClassCtor = nullptr;
        FnBuildingCtor g_OriginalBuildingCtor = nullptr;
        bool g_LabelCompareCallPatched = false;
        bool g_InstallFailureLogged = false;
        bool g_TuggableInstallLogged = false;

        // The class cache is keyed by the engine's own packed eight-character
        // ODF name rather than native class pointers. That avoids retaining a
        // stale pointer across mission teardown and exactly matches the name
        // identity Redux uses for the legacy `abstor` special case.
        SRWLOCK g_TuggableNamesLock = SRWLOCK_INIT;
        std::unordered_set<uint64_t> g_TuggableBuildingNames;

        uint64_t PackOdfName(uint32_t lo, uint32_t hi)
        {
            return static_cast<uint64_t>(lo) |
                (static_cast<uint64_t>(hi) << 32);
        }

        void FormatPackedOdfName(uint32_t lo, uint32_t hi, char (&out)[9])
        {
            std::memset(out, 0, sizeof(out));
            std::memcpy(out, &lo, sizeof(lo));
            std::memcpy(out + sizeof(lo), &hi, sizeof(hi));
        }

        void SetOdfTuggable(uint32_t lo, uint32_t hi, bool enabled)
        {
            const uint64_t packed = PackOdfName(lo, hi);
            AcquireSRWLockExclusive(&g_TuggableNamesLock);
            if (enabled)
                g_TuggableBuildingNames.insert(packed);
            else
                g_TuggableBuildingNames.erase(packed);
            ReleaseSRWLockExclusive(&g_TuggableNamesLock);
        }

        bool IsOdfTuggable(uint32_t lo, uint32_t hi)
        {
            const uint64_t packed = PackOdfName(lo, hi);
            AcquireSRWLockShared(&g_TuggableNamesLock);
            const bool found = g_TuggableBuildingNames.find(packed) !=
                g_TuggableBuildingNames.end();
            ReleaseSRWLockShared(&g_TuggableNamesLock);
            return found;
        }

        // The class constructor runs while Redux's ParameterDB still points at
        // the ODF being built. Reading the key here therefore inherits the
        // engine's own addon search, section hashing, and baseName resolution
        // instead of opening the file a second time in OpenShim.
        void* __fastcall TuggableBuildingClassCtorHook(void* thisPtr,
                                                       void* /*edx*/,
                                                       void* parentClass,
                                                       uint32_t odfNameLo,
                                                       uint32_t odfNameHi)
        {
            int enabled = 0;
            const bool found = g_ParameterDbGetInt &&
                g_ParameterDbGetInt(kBuildingClassSectionHash,
                                    kTuggableKeyHash,
                                    &enabled,
                                    0) != 0;

            void* result = g_OriginalBuildingClassCtor
                ? g_OriginalBuildingClassCtor(thisPtr, parentClass,
                                              odfNameLo, odfNameHi)
                : nullptr;

            // Missing/zero removes any stale process-lifetime name entry. This
            // matters when two addons shadow the same ODF name in successive
            // missions with different tuggability settings.
            SetOdfTuggable(odfNameLo, odfNameHi, found && enabled != 0);

            if (found && enabled != 0)
            {
                char odfName[9] = {};
                FormatPackedOdfName(odfNameLo, odfNameHi, odfName);
                LogShimA(LogLevel::Info, "TUGODF",
                    "ODF %.8s opted into Building tugging", odfName);
            }

            return result;
        }

        // Stock Building::Building sets +0x220 to GetHandle() only when the
        // packed class name is exactly `abstor`. For opted-in ODFs, reproduce
        // that one assignment after the stock constructor has initialized the
        // handle at +0xDC. Tug's existing dying/attached checks remain stock.
        void* __fastcall TuggableBuildingCtorHook(void* thisPtr,
                                                  void* /*edx*/,
                                                  void* objectArg,
                                                  void* objectClass)
        {
            void* result = g_OriginalBuildingCtor
                ? g_OriginalBuildingCtor(thisPtr, objectArg, objectClass)
                : nullptr;
            if (!result || !objectClass)
                return result;

            __try
            {
                const auto* classBytes =
                    reinterpret_cast<const uint8_t*>(objectClass);
                uint32_t odfNameLo = 0;
                uint32_t odfNameHi = 0;
                std::memcpy(&odfNameLo,
                            classBytes + kGameObjectClassPackedNameOffset,
                            sizeof(odfNameLo));
                std::memcpy(&odfNameHi,
                            classBytes + kGameObjectClassPackedNameOffset + 4,
                            sizeof(odfNameHi));

                if (IsOdfTuggable(odfNameLo, odfNameHi))
                {
                    auto* objectBytes = reinterpret_cast<uint8_t*>(result);
                    const uint32_t handle = *reinterpret_cast<const uint32_t*>(
                        objectBytes + kGameObjectHandleOffset);
                    *reinterpret_cast<uint32_t*>(
                        objectBytes + kBuildingTuggableHandleOffset) = handle;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                LogShimA(LogLevel::Warn, "TUGODF",
                    "could not apply tuggable Building flag to constructed object");
            }

            return result;
        }

        bool InstallTuggableBuildingSupportIfPossible()
        {
            if (g_BuildingClassCtorDetour.trampoline &&
                g_BuildingCtorDetour.trampoline)
            {
                return true;
            }

            static const uint8_t ctorPrologue[kTuggableCtorDetourLength] =
                { 0x55, 0x8B, 0xEC, 0x6A, 0xFF };
            static const uint8_t parameterDbPrologue[] =
                { 0x55, 0x8B, 0xEC };

            uint8_t parameterDbBytes[sizeof(parameterDbPrologue)] = {};
            if (!HookEngine::ReadMemory(
                    static_cast<uint32_t>(kParameterDbGetIntAddress),
                    parameterDbBytes, sizeof(parameterDbBytes)) ||
                std::memcmp(parameterDbBytes, parameterDbPrologue,
                            sizeof(parameterDbPrologue)) != 0)
            {
                return false;
            }
            g_ParameterDbGetInt = reinterpret_cast<FnParameterDbGetInt>(
                kParameterDbGetIntAddress);

            if (!g_BuildingClassCtorDetour.trampoline &&
                !InstallInlineDetour32(
                    g_BuildingClassCtorDetour,
                    kBuildingClassCtorAddress,
                    reinterpret_cast<void*>(&TuggableBuildingClassCtorHook),
                    kTuggableCtorDetourLength,
                    ctorPrologue,
                    sizeof(ctorPrologue)))
            {
                return false;
            }
            g_OriginalBuildingClassCtor = reinterpret_cast<FnBuildingClassCtor>(
                g_BuildingClassCtorDetour.trampoline);

            if (!g_BuildingCtorDetour.trampoline &&
                !InstallInlineDetour32(
                    g_BuildingCtorDetour,
                    kBuildingCtorAddress,
                    reinterpret_cast<void*>(&TuggableBuildingCtorHook),
                    kTuggableCtorDetourLength,
                    ctorPrologue,
                    sizeof(ctorPrologue)))
            {
                return false;
            }
            g_OriginalBuildingCtor = reinterpret_cast<FnBuildingCtor>(
                g_BuildingCtorDetour.trampoline);

            if (!g_TuggableInstallLogged)
            {
                LogShimA(LogLevel::Info, "TUGODF",
                    "installed [BuildingClass] tuggable=1 compatibility support; "
                    "stock abstor behavior remains unchanged");
                g_TuggableInstallLogged = true;
            }
            return true;
        }

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
        // This module already owns the shared Building compatibility seam, so
        // install the independent tuggable-building extension from the same
        // deferred retry path. It remains useful even when pond itself cannot
        // be installed on a future executable build.
        InstallTuggableBuildingSupportIfPossible();

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
