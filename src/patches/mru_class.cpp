#include "mru_class.h"

#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "mru_class_policy.h"
#include "shim_log.h"
#include "tracked_vehicle_class.h"
#include "tracked_vehicle_physics.h"

#include <Windows.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <unordered_map>

// classLabel = "mru" (Docs/MRU_CLASS.md), plan steps 1-2 of
// Docs/NIGHTINGALE_RESEARCH.md: the HoverCraftClass alias, the [MruClass]
// key parse, and a log-only command-menu probe.
//
// An mru ODF is built by the stock HoverCraftClass (4CC 'HOVR' and rank
// kept, label stamped "mru"), exactly as tracked does; the label compare and
// the BuildClass/Build detours are the ones tracked_vehicle_class.cpp owns,
// which call in here. An object of an mru class whose ODF has an [MruClass]
// section gets an OpenShim copy of the HoverCraft vtable whose
// UpdateModeList slot (23, 0x004EBD60) runs the stock fill and then puts
// Drop Repair, Drop Ammo and Deploy in slots 7-9 (single player only).
// Every other slot is a jmp through the stock vtable entry, so the stock
// hover, APC, Minelayer and Tug vtables are never written and in-place
// rewrites of the stock table still apply. rts_commands.cpp relabels the
// three entries and logs (and consumes) their picks; nothing else happens
// yet: no pod, no deploy state, no order change.

namespace BZROpenShim
{
    namespace Hooks
    {
        bool VtableTypeNameMatches(uintptr_t vtableAddress, const char* expectedName);
        bool IsSinglePlayerSession();
    }

    namespace
    {
        namespace Policy = MruClassPolicy;

        constexpr char kMruClassLabel[] = "mru";
        constexpr char kHoverClassLabel[] = "hover";
        constexpr char kComponent[] = "MRU";
        constexpr char kKillSwitch[] = "OPENSHIM_DISABLE_MRU_CLASS";

        // GameObjectClass.
        constexpr size_t kClassLabelOffset = 0x18;
        constexpr size_t kClassPackedNameOffset = 0x30;
        // GameObject: class pointer, ModeList (GameObjectGetModeList row),
        // and the pending order `what` GameObject::SetCommand writes
        // (rts_commands.cpp kPendingOrderOffset + 4).
        constexpr size_t kObjClass = 0xF8;
        constexpr size_t kObjPendingWhat = 0xCC;
        constexpr size_t kObjModeList = 0x1A4;
        // ModeList: 11 ids, then the enabled mask.
        constexpr size_t kModeListEnabled = 0x2C;

        // HoverCraftVtable (0x0087ABE4) has 42 slots (tracked_vehicle_class.cpp);
        // slot 23 is UpdateModeList, __thiscall(this), no arguments.
        constexpr size_t kHoverVtableSlots = 42;
        constexpr size_t kUpdateModeListSlot = 23;
        constexpr size_t kThunkStride = 8;

        using FnThisVoid = void (__thiscall*)(void*);
        // ModeList::SetMode(slot, mode, enabled), thiscall ret 0xC.
        using FnSetMode = void (__thiscall*)(void*, int, int, int);
        using FnOpenScope = void* (__thiscall*)(void*, const char*);
        using FnRawGet = const char* (__thiscall*)(void*, uint32_t, uint32_t);
        using FnPopScope = void (__thiscall*)(void*);

        FnSetMode g_SetMode = nullptr;
        FnOpenScope g_OpenScope = nullptr;
        FnRawGet g_RawGet = nullptr;
        FnPopScope g_PopScope = nullptr;

        uintptr_t g_HoverVtable = 0;
        // [0] is the stock RTTI locator, so the copy still reads as
        // .?AVHoverCraft@@; an object's vptr points at [1].
        void* g_MruVtable[kHoverVtableSlots + 1] = {};
        uint8_t* g_Thunks = nullptr;
        bool g_Installed = false;
        bool g_GaveUp = false;
        bool g_KillSwitchLogged = false;

        thread_local bool g_MruBuildPending = false;

        // Build decisions, per class (change-only log).
        enum class BuildDecision : int
        {
            Unseen,
            MenuVtable,
            NoSection,
            VtableMismatch,
        };

        struct MruClassData
        {
            Policy::Config config;
            bool sectionPresent = false;
            BuildDecision lastBuild = BuildDecision::Unseen;
        };

        // Keyed by class pointer. Used only while the class still carries
        // the "mru" label pointer; a reused address is overwritten at
        // BuildClass (as tracked's g_ClassData).
        SRWLOCK g_ClassDataLock = SRWLOCK_INIT;
        std::unordered_map<uintptr_t, MruClassData> g_ClassData;

        // The menu-fill decision, process wide (change-only log): -1 unseen,
        // 0 off (network game), 1 on.
        volatile long g_MenuDecision = -1;
        volatile long g_PickLogBudget = 256;

        bool IsExecutableAddress(uintptr_t address)
        {
            MEMORY_BASIC_INFORMATION info = {};
            if (!address || VirtualQuery(reinterpret_cast<const void*>(address), &info, sizeof(info)) != sizeof(info))
                return false;
            if (info.State != MEM_COMMIT)
                return false;
            const DWORD protect = info.Protect & 0xFF;
            return protect == PAGE_EXECUTE || protect == PAGE_EXECUTE_READ ||
                protect == PAGE_EXECUTE_READWRITE || protect == PAGE_EXECUTE_WRITECOPY;
        }

        bool IsMruClass(const void* objectClass)
        {
            if (!objectClass)
                return false;
            __try
            {
                return *reinterpret_cast<const char* const*>(
                    reinterpret_cast<const uint8_t*>(objectClass) + kClassLabelOffset) == kMruClassLabel;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // An object carrying the MRU vtable copy (only mru classes with an
        // [MruClass] section get it).
        bool HasMruVtable(const void* object)
        {
            if (!object)
                return false;
            __try
            {
                return *reinterpret_cast<const uintptr_t*>(object) ==
                    reinterpret_cast<uintptr_t>(&g_MruVtable[1]);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // ---- class construction --------------------------------------------

        constexpr size_t kRawValueBytes = 32;
        struct RawMruKeys
        {
            char values[Policy::kKeyCount][kRawValueBytes];
        };

        void CopyRaw(const char* value, char (&out)[kRawValueBytes])
        {
            out[0] = 0;
            if (!value)
                return;
            for (size_t i = 0; i + 1 < kRawValueBytes; ++i)
            {
                out[i] = value[i];
                if (!value[i])
                    return;
            }
            out[kRawValueBytes - 1] = 0;
        }

        // Opens the ODF's ParameterDB scope (a cache hit: GameObjectClass::Find
        // holds its own scope on the same file across BuildClass) and copies
        // the [MruClass] values out before popping it, as tracked does.
        bool ReadMruKeys(const char* odfFile, const uint32_t (&keyHashes)[Policy::kKeyCount], RawMruKeys& keys)
        {
            std::memset(&keys, 0, sizeof(keys));
            void* scope = nullptr;
            __try
            {
                g_OpenScope(&scope, odfFile);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
            if (!scope)
                return false;

            bool ok = true;
            __try
            {
                constexpr uint32_t section = TrackedPhysics::OdfHash("MruClass");
                for (int i = 0; i < Policy::kKeyCount; ++i)
                    CopyRaw(g_RawGet(&scope, section, keyHashes[i]), keys.values[i]);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                ok = false;
            }
            __try
            {
                g_PopScope(&scope);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                ok = false;
            }
            return ok;
        }

        bool StampMruClass(void* objectClass)
        {
            __try
            {
                *reinterpret_cast<const char**>(reinterpret_cast<uint8_t*>(objectClass) + kClassLabelOffset) =
                    kMruClassLabel;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool SwapToMruVtable(void* object)
        {
            __try
            {
                auto* vptr = reinterpret_cast<uintptr_t*>(object);
                if (*vptr != g_HoverVtable)
                    return false;
                *vptr = reinterpret_cast<uintptr_t>(&g_MruVtable[1]);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // ---- the menu probe --------------------------------------------------

        void LogMenuDecision(long decision, const void* object)
        {
            if (InterlockedExchange(&g_MenuDecision, decision) == decision)
                return;
            if (decision == 1)
            {
                LogShimA(LogLevel::Info, kComponent,
                    "menu probe on (single player): obj=%p slots 7/8/9 = Drop Repair (0x%X), Drop Ammo (0x%X), "
                    "Deploy (0x%X), all enabled",
                    object, Policy::kModeDropRepair, Policy::kModeDropAmmo, Policy::kModeDeploy);
            }
            else
            {
                LogShimA(LogLevel::Info, kComponent,
                    "menu probe off (network game): obj=%p keeps the stock hover menu", object);
            }
        }

        bool ReadModeList(const void* object, int32_t (&modes)[Policy::kModeSlots], uint32_t& enabled);

        // Stock Cloak/Decloak (FUN_004aefa0(7) in HoverCraft::UpdateModeList) owns slot 7 on a
        // cloak-capable craft; leave it there so a cloaked MRU can still decloak.
        constexpr int32_t kModeCloak = 0x18;
        constexpr int32_t kModeDecloak = 0x19;
        bool g_CloakSkipLogged = false;

        void FillMruMenu(void* self)
        {
            auto* modeList = static_cast<uint8_t*>(self) + kObjModeList;
            int32_t modes[Policy::kModeSlots] = {};
            uint32_t enabled = 0;
            const bool listRead = ReadModeList(self, modes, enabled);
            for (int i = 0; i < Policy::kMenuEntryCount; ++i)
            {
                const Policy::MenuEntry& e = Policy::kMenuEntries[i];
                if (listRead && (modes[e.slot] == kModeCloak || modes[e.slot] == kModeDecloak))
                {
                    if (!g_CloakSkipLogged)
                    {
                        g_CloakSkipLogged = true;
                        LogShimA(LogLevel::Info, kComponent,
                            "menu probe: obj=%p slot %d holds stock Cloak/Decloak (0x%X); MRU entry 0x%X skipped",
                            self, e.slot, modes[e.slot], e.mode);
                    }
                    continue;
                }
                g_SetMode(modeList, e.slot, e.mode, 1);
            }
        }

        // Slot 23 of the MRU vtable copy.
        void __fastcall MruUpdateModeListHook(void* self, void* /*edx*/)
        {
            reinterpret_cast<FnThisVoid>(g_Thunks + kUpdateModeListSlot * kThunkStride)(self);
            const bool on = Hooks::IsSinglePlayerSession();
            LogMenuDecision(on ? 1 : 0, self);
            if (!on)
                return;
            __try
            {
                FillMruMenu(self);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                // Fail closed: the stock fill above stands.
            }
        }

        bool ReadModeList(const void* object, int32_t (&modes)[Policy::kModeSlots], uint32_t& enabled)
        {
            __try
            {
                const auto* list = static_cast<const uint8_t*>(object) + kObjModeList;
                std::memcpy(modes, list, sizeof(modes));
                std::memcpy(&enabled, list + kModeListEnabled, sizeof(enabled));
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool ReadPendingWhat(const void* object, int& what)
        {
            __try
            {
                std::memcpy(&what, static_cast<const uint8_t*>(object) + kObjPendingWhat, sizeof(what));
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // ---- install ---------------------------------------------------------

        bool BuildMruVtable(uintptr_t stockVtable, uintptr_t stockUpdateModeList)
        {
            void* stock[kHoverVtableSlots + 2] = {};
            if (!HookEngine::ReadMemory(static_cast<uint32_t>(stockVtable - sizeof(void*)), stock, sizeof(stock)))
                return false;
            // stock[0] is the RTTI locator, stock[1 + i] slot i, and
            // stock[1 + 42] must not be code: that pins the slot count.
            for (size_t i = 0; i < kHoverVtableSlots; ++i)
            {
                if (!IsExecutableAddress(reinterpret_cast<uintptr_t>(stock[1 + i])))
                    return false;
            }
            if (IsExecutableAddress(reinterpret_cast<uintptr_t>(stock[1 + kHoverVtableSlots])))
                return false;
            if (reinterpret_cast<uintptr_t>(stock[1 + kUpdateModeListSlot]) != stockUpdateModeList)
                return false;

            if (!g_Thunks)
            {
                g_Thunks = static_cast<uint8_t*>(VirtualAlloc(nullptr, kHoverVtableSlots * kThunkStride,
                                                              MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));
                if (!g_Thunks)
                    return false;
                for (size_t i = 0; i < kHoverVtableSlots; ++i)
                {
                    // jmp dword ptr [stockVtable + 4*i]; int3; int3
                    uint8_t* thunk = g_Thunks + i * kThunkStride;
                    const uint32_t slotAddress = static_cast<uint32_t>(stockVtable + i * sizeof(void*));
                    thunk[0] = 0xFF;
                    thunk[1] = 0x25;
                    std::memcpy(thunk + 2, &slotAddress, sizeof(slotAddress));
                    thunk[6] = 0xCC;
                    thunk[7] = 0xCC;
                }
                DWORD oldProtect = 0;
                if (!VirtualProtect(g_Thunks, kHoverVtableSlots * kThunkStride, PAGE_EXECUTE_READ, &oldProtect))
                {
                    VirtualFree(g_Thunks, 0, MEM_RELEASE);
                    g_Thunks = nullptr;
                    return false;
                }
                FlushInstructionCache(GetCurrentProcess(), g_Thunks, kHoverVtableSlots * kThunkStride);
            }

            g_MruVtable[0] = stock[0];
            for (size_t i = 0; i < kHoverVtableSlots; ++i)
                g_MruVtable[1 + i] = g_Thunks + i * kThunkStride;
            g_MruVtable[1 + kUpdateModeListSlot] = reinterpret_cast<void*>(&MruUpdateModeListHook);
            return true;
        }

        void GiveUp(const char* what)
        {
            g_GaveUp = true;
            LogShimA(LogLevel::Warn, kComponent, "classLabel=mru not installed: %s", what);
        }
    }

    bool MatchMruClassLabel(const char* registeredLabel,
                            const char* odfLabel,
                            int (__cdecl* stricmp)(const char*, const char*))
    {
        if (!g_Installed || !registeredLabel || !odfLabel || !stricmp)
            return false;
        if (stricmp(registeredLabel, kHoverClassLabel) != 0 || stricmp(odfLabel, kMruClassLabel) != 0)
            return false;
        g_MruBuildPending = true;
        return true;
    }

    bool TakeMruBuildPending()
    {
        const bool pending = g_MruBuildPending;
        g_MruBuildPending = false;
        return pending;
    }

    void ConfigureMruClass(void* objectClass, uint32_t odfNameLo, uint32_t odfNameHi)
    {
        if (!g_Installed || !objectClass)
            return;
        if (!StampMruClass(objectClass))
        {
            LogShimA(LogLevel::Warn, kComponent, "HoverCraftClass returned an unreadable class object");
            return;
        }

        char odfName[9] = {};
        std::memcpy(odfName, &odfNameLo, sizeof(odfNameLo));
        std::memcpy(odfName + 4, &odfNameHi, sizeof(odfNameHi));
        char odfFile[16] = {};
        std::snprintf(odfFile, sizeof(odfFile), "%.8s.odf", odfName);

        uint32_t keyHashes[Policy::kKeyCount] = {};
        for (int i = 0; i < Policy::kKeyCount; ++i)
            keyHashes[i] = TrackedPhysics::OdfHash(Policy::KeyName(i));

        RawMruKeys keys{};
        Policy::RawKeys raw;
        const bool read = ReadMruKeys(odfFile, keyHashes, keys);
        if (read)
        {
            for (int i = 0; i < Policy::kKeyCount; ++i)
                raw.values[i] = keys.values[i];
        }
        else
        {
            LogShimA(LogLevel::Warn, kComponent,
                "ODF %.8s: [MruClass] could not be read; plain hover", odfName);
        }
        const Policy::ParseResult parsed = Policy::ParseConfig(raw);
        if (parsed.repairPodNameTooLong || parsed.ammoPodNameTooLong)
        {
            LogShimA(LogLevel::Warn, kComponent,
                "ODF %.8s: %s longer than %u characters; ignored", odfName,
                parsed.repairPodNameTooLong ? "repairPodClass" : "ammoPodClass",
                static_cast<unsigned>(Policy::kPodClassBytes - 1));
        }

        MruClassData data;
        data.config = parsed.config;
        data.sectionPresent = parsed.sectionPresent;
        AcquireSRWLockExclusive(&g_ClassDataLock);
        g_ClassData[reinterpret_cast<uintptr_t>(objectClass)] = data;
        ReleaseSRWLockExclusive(&g_ClassDataLock);

        const Policy::Config& c = data.config;
        LogShimA(LogLevel::Info, kComponent,
            "built ODF %.8s as mru class=%p [MruClass] %s: serviceRadius=%.1f serviceInterval=%.2f "
            "repairPerTick=%.1f reloadPerTick=%.1f ammoPerRepair=%.2f ammoPerReload=%.2f serviceSelf=%d "
            "serviceDeployed=%d podCooldown=%.1f repairPodClass=%s ammoPodClass=%s ammoPerRepairPod=%.1f "
            "ammoPerAmmoPod=%.1f (parsed only; nothing uses them yet)",
            odfName, objectClass, data.sectionPresent ? "present" : "absent (plain hover menu)",
            c.serviceRadius, c.serviceInterval, c.repairPerTick, c.reloadPerTick, c.ammoPerRepair,
            c.ammoPerReload, c.serviceSelf ? 1 : 0, c.serviceDeployed ? 1 : 0, c.podCooldown,
            c.repairPodClass[0] ? c.repairPodClass : "-", c.ammoPodClass[0] ? c.ammoPodClass : "-",
            c.ammoPerRepairPod, c.ammoPerAmmoPod);
    }

    void OnHoverObjectBuilt(void* objectClass, void* object)
    {
        if (!g_Installed || !object || !IsMruClass(objectClass))
            return;

        bool sectionPresent = false;
        BuildDecision last = BuildDecision::Unseen;
        AcquireSRWLockShared(&g_ClassDataLock);
        const auto it = g_ClassData.find(reinterpret_cast<uintptr_t>(objectClass));
        if (it != g_ClassData.end())
        {
            sectionPresent = it->second.sectionPresent;
            last = it->second.lastBuild;
        }
        ReleaseSRWLockShared(&g_ClassDataLock);

        BuildDecision decision = BuildDecision::NoSection;
        if (sectionPresent)
            decision = SwapToMruVtable(object) ? BuildDecision::MenuVtable : BuildDecision::VtableMismatch;
        if (decision == last)
            return;

        AcquireSRWLockExclusive(&g_ClassDataLock);
        const auto entry = g_ClassData.find(reinterpret_cast<uintptr_t>(objectClass));
        if (entry != g_ClassData.end())
            entry->second.lastBuild = decision;
        ReleaseSRWLockExclusive(&g_ClassDataLock);

        switch (decision)
        {
        case BuildDecision::MenuVtable:
            LogShimA(LogLevel::Info, kComponent,
                "class %p: objects get the MRU vtable copy (UpdateModeList slot %u), first obj=%p",
                objectClass, static_cast<unsigned>(kUpdateModeListSlot), object);
            break;
        case BuildDecision::NoSection:
            LogShimA(LogLevel::Info, kComponent,
                "class %p: no [MruClass] section; objects stay plain hover, first obj=%p", objectClass, object);
            break;
        default:
            LogShimA(LogLevel::Warn, kComponent,
                "class %p built object %p without the HoverCraft vtable; left as is", objectClass, object);
            break;
        }
    }

    bool IsMruMenuObject(void* object)
    {
        return g_Installed && HasMruVtable(object) && Hooks::IsSinglePlayerSession();
    }

    bool NoteMruMenuPick(void* object, uint32_t handle, int mode)
    {
        if (!IsMruMenuObject(object))
            return false;

        int32_t modes[Policy::kModeSlots] = {};
        uint32_t enabled = 0;
        const bool listRead = ReadModeList(object, modes, enabled);
        const Policy::Action action = Policy::ActionForMode(mode);
        const bool consumed = listRead && action != Policy::Action::None &&
            Policy::UnitOffersAction(modes, enabled, mode);
        int pendingWhat = -1;
        ReadPendingWhat(object, pendingWhat);

        if (InterlockedDecrement(&g_PickLogBudget) >= 0)
        {
            LogShimA(LogLevel::Info, kComponent,
                "menu pick mode=0x%X (%s) on mru obj=%p handle=0x%08X pendingWhat=%d: %s",
                mode, consumed ? Policy::ActionName(action) : "stock entry", object, handle, pendingWhat,
                consumed ? "probe only, consumed (no order, no stock dispatch)" : "stock dispatch");
        }
        return consumed;
    }

    void InstallMruClassIfPossible()
    {
        if (g_Installed || g_GaveUp)
            return;
        if (EnvFlagEnabled(kKillSwitch))
        {
            if (!g_KillSwitchLogged)
            {
                g_KillSwitchLogged = true;
                LogShimA(LogLevel::Info, kComponent, "classLabel=mru off (%s set)", kKillSwitch);
            }
            return;
        }
        // The alias rides on the Find label compare (pond) and the
        // HoverCraftClass BuildClass/Build detours (tracked).
        if (!IsTrackedVehicleClassInstalled())
            return;

        uint32_t updateModeList = 0;
        uint32_t setMode = 0;
        const HookEngine::EngineRow rows[] = {
            { "HoverCraftUpdateModeList", &updateModeList },
            { "ModeListSetMode", &setMode },
        };
        if (!HookEngine::BindEngineRows("MRU class", rows))
        {
            GiveUp("HoverCraftUpdateModeList or ModeListSetMode did not bind");
            return;
        }
        const uintptr_t openScope = HookEngine::ResolveNamedAddress("ParameterDB::OpenScope");
        const uintptr_t rawGet = HookEngine::ResolveNamedAddress("WeaponPresentation::RawGet");
        const uintptr_t popScope = HookEngine::ResolveNamedAddress("WeaponPresentation::PopScope");
        if (!openScope || !rawGet || !popScope)
        {
            GiveUp("ParameterDB resolves missing");
            return;
        }
        const uintptr_t hoverVtable = HookEngine::EngineAddress("HoverCraftVtable");
        if (!hoverVtable || !Hooks::VtableTypeNameMatches(hoverVtable, ".?AVHoverCraft@@"))
        {
            GiveUp("HoverCraftVtable row missing or not .?AVHoverCraft@@");
            return;
        }
        if (!BuildMruVtable(hoverVtable, updateModeList))
        {
            GiveUp("HoverCraftVtable is not the expected 42-slot table with UpdateModeList in slot 23");
            return;
        }

        g_SetMode = reinterpret_cast<FnSetMode>(setMode);
        g_OpenScope = reinterpret_cast<FnOpenScope>(openScope);
        g_RawGet = reinterpret_cast<FnRawGet>(rawGet);
        g_PopScope = reinterpret_cast<FnPopScope>(popScope);
        g_HoverVtable = hoverVtable;
        g_Installed = true;
        LogShimA(LogLevel::Info, kComponent,
            "installed classLabel=mru (HoverCraftClass alias; menu probe: UpdateModeList slot %u on a vtable "
            "copy, slots 7/8/9, single player; kill switch %s)",
            static_cast<unsigned>(kUpdateModeListSlot), kKillSwitch);
    }

    bool IsMruClassInstalled()
    {
        return g_Installed;
    }
}
