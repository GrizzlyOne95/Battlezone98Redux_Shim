#include "mru_class.h"

#include "bzr_hooks_internal.h"
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

// classLabel = "mru" (Docs/MRU_CLASS.md), plan steps 1-6 of
// Docs/NIGHTINGALE_RESEARCH.md: the HoverCraftClass alias, the [MruClass]
// key parse, the command-menu entries, and (with [SinglePlayer] MruGameplay)
// pod drops, the deployed flag and the radius service tick.
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
// three entries and hands their picks here. The copy also wraps Simulate
// (slot 15: cooldown, queued pod drop, deploy hold, service tick) and the
// destructor (slot 0: drops the per-object state). The menu entries and the
// gameplay need [SinglePlayer] MruGameplay = 1 and a single-player session.

namespace BZROpenShim
{
    namespace
    {
        namespace Policy = MruClassPolicy;

        constexpr char kMruClassLabel[] = "mru";
        constexpr char kHoverClassLabel[] = "hover";
        constexpr char kComponent[] = "MRU";
        constexpr char kKillSwitch[] = "OPENSHIM_DISABLE_MRU_CLASS";
        constexpr char kGameplayKillSwitch[] = "OPENSHIM_DISABLE_MRU_GAMEPLAY";
        constexpr char kGameplayOption[] = "MruGameplay";

        // GameObjectClass. class_id at +0x1C (2 STRUCTURE1, 5 SIGN, 7 SCRAP
        // are the ones Dispenser::Simulate builds without the carrier's
        // velocity, FUN_004b5da0.c lines 64 and 80).
        constexpr size_t kClassLabelOffset = 0x18;
        constexpr size_t kClassPackedNameOffset = 0x30;
        constexpr size_t kClassId = 0x1C;
        // GameObject: obj76 (transform owner), class pointer, ModeList
        // (GameObjectGetModeList row), the current and pending order `what`
        // (GameObject::SetCommand writes +0xCC, FUN_004dbce0;
        // rts_commands.cpp kPendingOrderOffset + 4), the velocity
        // (GetVelocity 0x004624B0 / SetVelocity 0x0046FB20 use +0x12C) and
        // the team Craft::Simulate compares with the user's team
        // (FUN_004ab380.c lines 326-328).
        constexpr size_t kObjObj76 = 0xF4;
        constexpr size_t kObjClass = 0xF8;
        constexpr size_t kObjCurrentWhat = 0xAC;
        constexpr size_t kObjPendingWhat = 0xCC;
        constexpr size_t kObjVelocity = 0x12C;
        constexpr size_t kObjTeam = 0x174;
        constexpr size_t kObjModeList = 0x1A4;
        // ModeList: 11 ids, then the enabled mask.
        constexpr size_t kModeListEnabled = 0x2C;
        // obj76 + 0x20: the 64-byte MAT_3D GameObjectClass::Build takes
        // (right/up/front floats, pad, posit doubles at +0x28; Dispenser
        // copies 16 dwords of it, FUN_004b5da0.c lines 57-63).
        constexpr size_t kObj76Matrix = 0x20;
        constexpr size_t kMatrixBytes = 0x40;
        constexpr size_t kMatrixFront = 0x18;
        constexpr size_t kMatrixPosit = 0x28;

        // HoverCraftVtable (0x0087ABE4) has 42 slots (tracked_vehicle_class.cpp);
        // slot 23 is UpdateModeList, __thiscall(this), no arguments. Slot 15
        // is Simulate, __thiscall(this, float dt), ret 4 (GameObject::Simulate
        // 0x004DEEC0 calls vtable +0x3C, FUN_004deec0.c lines 71 and 103);
        // slot 0 the scalar deleting destructor 0x004E9EC0, __thiscall(this,
        // flags), ret 4. tracked wraps the same two slots in its own copy.
        constexpr size_t kHoverVtableSlots = 42;
        constexpr size_t kDestructorSlot = 0;
        constexpr size_t kSimulateSlot = 15;
        constexpr size_t kUpdateModeListSlot = 23;
        constexpr size_t kThunkStride = 8;

        using FnThisVoid = void (__thiscall*)(void*);
        using FnSimulate = void (__thiscall*)(void*, float);
        using FnDestructor = void* (__thiscall*)(void*, unsigned int);
        // ModeList::SetMode(slot, mode, enabled), thiscall ret 0xC.
        using FnSetMode = void (__thiscall*)(void*, int, int, int);
        using FnOpenScope = void* (__thiscall*)(void*, const char*);
        using FnRawGet = const char* (__thiscall*)(void*, uint32_t, uint32_t);
        using FnPopScope = void (__thiscall*)(void*);

        // Gameplay rows (scripts/patches.json, Docs/MRU_CLASS.md).
        using FnAddHealthByHandle = void (__cdecl*)(uint32_t, float);
        using FnAddAmmoByHandle = void (__cdecl*)(uint32_t, long);
        using FnGetCurHealthByHandle = float (__cdecl*)(uint32_t);
        using FnGetCurAmmoByHandle = long (__cdecl*)(uint32_t);
        using FnFindClassByName = void* (__cdecl*)(const char*);
        // GameObjectClass::Build(matrix, team, independent, seq, existing),
        // thiscall, callee pops 0x14 (call site 0x004B6017).
        using FnBuild = void* (__thiscall*)(void*, const void*, int, int, int, void*);
        using FnAiMissionGetCurrent = void* (__cdecl*)();
        // AiMission vtable +0x1C(GameObject*), thiscall (0x004B6086).
        using FnAiMissionAdd = void (__thiscall*)(void*, void*);
        using FnSetVelocity = void (__thiscall*)(void*, const void*);
        using FnSetOwner = void (__thiscall*)(void*, void*);
        using FnSetCommand = void (__thiscall*)(void*, int);
        using FnIsAlly = uint8_t (__thiscall*)(void*, void*);
        using FnGetHandle = uint32_t (__thiscall*)(void*);

        FnSetMode g_SetMode = nullptr;
        FnOpenScope g_OpenScope = nullptr;
        FnRawGet g_RawGet = nullptr;
        FnPopScope g_PopScope = nullptr;

        FnAddHealthByHandle g_AddHealth = nullptr;
        FnAddAmmoByHandle g_AddAmmo = nullptr;
        FnGetCurHealthByHandle g_GetCurHealth = nullptr;
        FnGetCurAmmoByHandle g_GetCurAmmo = nullptr;
        FnFindClassByName g_FindClass = nullptr;
        FnBuild g_Build = nullptr;
        FnAiMissionGetCurrent g_AiMissionGetCurrent = nullptr;
        FnSetVelocity g_SetVelocity = nullptr;
        FnSetOwner g_SetOwner = nullptr;
        FnSetCommand g_SetCommand = nullptr;
        FnIsAlly g_IsAlly = nullptr;
        FnGetHandle g_GetHandle = nullptr;
        uintptr_t g_ObjectListGlobal = 0;
        // [SinglePlayer] MruGameplay, every row bound, kill switch unset.
        bool g_GameplayOn = false;

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
            // Set once GameObjectClass lookup by name returned 0 for the
            // repair [0] / ammo [1] pod; that entry stays disabled.
            bool podFailed[2] = {};
        };

        // Keyed by class pointer. Used only while the class still carries
        // the "mru" label pointer; a reused address is overwritten at
        // BuildClass (as tracked's g_ClassData).
        SRWLOCK g_ClassDataLock = SRWLOCK_INIT;
        std::unordered_map<uintptr_t, MruClassData> g_ClassData;

        // Per MRU object (vtable copy), keyed by object pointer; erased in
        // the slot 0 destructor wrapper. Not saved: after a load an MRU is
        // undeployed with its cooldown ready.
        struct MruObjectState
        {
            bool deployed = false;
            bool sawIdleCurrent = false;
            float cooldownLeft = 0.0f;
            float serviceAccumulator = 0.0f;
            float drainCarry = 0.0f;
            Policy::Action pendingDrop = Policy::Action::None;
            // Change-only log state.
            bool serviceWasActive = false;
            bool gaugeWasEmpty = false;
        };

        SRWLOCK g_ObjectStateLock = SRWLOCK_INIT;
        std::unordered_map<uintptr_t, MruObjectState> g_ObjectStates;

        // The menu-fill decision, process wide (change-only log): -1 unseen,
        // 0 off (network game), 1 on.
        volatile long g_MenuDecision = -1;
        volatile long g_PickLogBudget = 256;
        volatile long g_DeployLogBudget = 256;
        volatile long g_DropLogBudget = 256;
        volatile long g_ServiceLogBudget = 256;

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

        // ---- the menu --------------------------------------------------------

        void LogMenuDecision(long decision, const void* object)
        {
            if (InterlockedExchange(&g_MenuDecision, decision) == decision)
                return;
            if (decision == 1)
            {
                LogShimA(LogLevel::Info, kComponent,
                    "menu on (single player): obj=%p slots 7/8/9 = Drop Repair (0x%X), Drop Ammo (0x%X), "
                    "Deploy (0x%X); drops enabled when ready",
                    object, Policy::kModeDropRepair, Policy::kModeDropAmmo, Policy::kModeDeploy);
            }
            else
            {
                LogShimA(LogLevel::Info, kComponent,
                    "menu and gameplay off (network game): obj=%p keeps the stock hover menu", object);
            }
        }

        bool ReadModeList(const void* object, int32_t (&modes)[Policy::kModeSlots], uint32_t& enabled);

        // ---- per-object state ------------------------------------------------

        MruObjectState LoadState(const void* object)
        {
            MruObjectState state;
            AcquireSRWLockShared(&g_ObjectStateLock);
            const auto it = g_ObjectStates.find(reinterpret_cast<uintptr_t>(object));
            if (it != g_ObjectStates.end())
                state = it->second;
            ReleaseSRWLockShared(&g_ObjectStateLock);
            return state;
        }

        void StoreState(const void* object, const MruObjectState& state)
        {
            AcquireSRWLockExclusive(&g_ObjectStateLock);
            try
            {
                g_ObjectStates[reinterpret_cast<uintptr_t>(object)] = state;
            }
            catch (...)
            {
                // Out of memory: the object runs without state this frame.
            }
            ReleaseSRWLockExclusive(&g_ObjectStateLock);
        }

        void EraseState(const void* object)
        {
            AcquireSRWLockExclusive(&g_ObjectStateLock);
            g_ObjectStates.erase(reinterpret_cast<uintptr_t>(object));
            ReleaseSRWLockExclusive(&g_ObjectStateLock);
        }

        // ---- engine calls (each under SEH, no C++ objects inside) -------------

        bool ReadClassPointer(const void* object, void*& objectClass)
        {
            __try
            {
                objectClass = *reinterpret_cast<void* const*>(static_cast<const uint8_t*>(object) + kObjClass);
                return objectClass != nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool LookupClassData(const void* object, MruClassData& data, void*& objectClass)
        {
            if (!ReadClassPointer(object, objectClass))
                return false;
            bool found = false;
            AcquireSRWLockShared(&g_ClassDataLock);
            const auto it = g_ClassData.find(reinterpret_cast<uintptr_t>(objectClass));
            if (it != g_ClassData.end())
            {
                data = it->second;
                found = true;
            }
            ReleaseSRWLockShared(&g_ClassDataLock);
            return found;
        }

        uint32_t SafeGetHandle(void* object)
        {
            if (!g_GetHandle || !object)
                return 0;
            __try
            {
                return g_GetHandle(object);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return 0;
            }
        }

        // -1 when the handle is dead or the call faults.
        long SafeGetCurAmmo(uint32_t handle)
        {
            if (!handle)
                return -1;
            __try
            {
                return g_GetCurAmmo(handle);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return -1;
            }
        }

        // -1 when the handle is dead or the call faults (the engine returns
        // -1234 for a dead handle).
        float SafeGetCurHealth(uint32_t handle)
        {
            if (!handle)
                return -1.0f;
            __try
            {
                return g_GetCurHealth(handle);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return -1.0f;
            }
        }

        void SafeAddHealth(uint32_t handle, float amount)
        {
            __try
            {
                g_AddHealth(handle, amount);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        void SafeAddAmmo(uint32_t handle, long amount)
        {
            __try
            {
                g_AddAmmo(handle, amount);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        bool SafeSetCommand(void* object, int what)
        {
            __try
            {
                g_SetCommand(object, what);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool ReadWhats(const void* object, int& pendingWhat, int& currentWhat)
        {
            __try
            {
                const auto* p = static_cast<const uint8_t*>(object);
                std::memcpy(&pendingWhat, p + kObjPendingWhat, sizeof(pendingWhat));
                std::memcpy(&currentWhat, p + kObjCurrentWhat, sizeof(currentWhat));
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // What the service scan and the drop read off one object.
        struct ObjectInfo
        {
            int classId;
            int team;
            double posit[3];
        };

        bool ReadObjectInfo(const void* object, ObjectInfo& info)
        {
            __try
            {
                const auto* p = static_cast<const uint8_t*>(object);
                const auto* objectClass = *reinterpret_cast<const uint8_t* const*>(p + kObjClass);
                const auto* obj76 = *reinterpret_cast<const uint8_t* const*>(p + kObjObj76);
                if (!objectClass || !obj76)
                    return false;
                std::memcpy(&info.classId, objectClass + kClassId, sizeof(info.classId));
                std::memcpy(&info.team, p + kObjTeam, sizeof(info.team));
                std::memcpy(info.posit, obj76 + kObj76Matrix + kMatrixPosit, sizeof(info.posit));
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool ReadMatrix(const void* object, uint8_t (&matrix)[kMatrixBytes])
        {
            __try
            {
                const auto* obj76 = *reinterpret_cast<const uint8_t* const*>(
                    static_cast<const uint8_t*>(object) + kObjObj76);
                if (!obj76)
                    return false;
                std::memcpy(matrix, obj76 + kObj76Matrix, sizeof(matrix));
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool SafeIsAlly(void* object, void* other)
        {
            __try
            {
                return g_IsAlly(object, other) != 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void* SafeFindClass(const char* name)
        {
            __try
            {
                return g_FindClass(name);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        // Dispenser::Simulate's build sequence (FUN_004b5da0.c lines 79-89):
        // Build, the carrier's velocity for a non-structure pod, hand it to
        // the AiMission, SetOwner(carrier). Dispenser's SetTarget (line 88,
        // the carrier's target) is left out: a pod has nothing to aim at.
        // False when a call faulted; `pod` is whatever Build returned.
        bool SafeBuildPod(void* podClass, const uint8_t (&matrix)[kMatrixBytes], int team, void* mru, void*& pod)
        {
            pod = nullptr;
            __try
            {
                pod = g_Build(podClass, matrix, team, 0, -1, nullptr);
                if (!pod)
                    return true;
                int classId = 0;
                std::memcpy(&classId, static_cast<const uint8_t*>(podClass) + kClassId, sizeof(classId));
                if (classId != 2 && classId != 7 && classId != 5)
                    g_SetVelocity(pod, static_cast<const uint8_t*>(mru) + kObjVelocity);
                void* mission = g_AiMissionGetCurrent();
                if (mission)
                {
                    const auto add = reinterpret_cast<FnAiMissionAdd>(
                        (*reinterpret_cast<void* const* const*>(mission))[7]);
                    add(mission, pod);
                }
                g_SetOwner(pod, mru);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                // Whatever was built stays; the caller logs the fault.
                return false;
            }
            return true;
        }

        // The engine's object vector (GameObject::objectList: _Myfirst +0,
        // _Mylast +4), as rts_commands.cpp SnapshotObjects.
        constexpr size_t kMaxObjects = 4096;
        void* g_ObjectScratch[kMaxObjects] = {};

        size_t SnapshotObjects(void** out, size_t capacity)
        {
            if (!g_ObjectListGlobal)
                return 0;
            size_t count = 0;
            __try
            {
                const uint8_t* vec = *reinterpret_cast<uint8_t* const*>(g_ObjectListGlobal);
                if (!vec)
                    return 0;
                void* const* first = *reinterpret_cast<void* const* const*>(vec);
                void* const* last = *reinterpret_cast<void* const* const*>(vec + 4);
                if (!first || last < first)
                    return 0;
                const size_t available = static_cast<size_t>(last - first);
                if (available > kMaxObjects)
                    return 0;
                for (size_t i = 0; i < available && count < capacity; ++i)
                {
                    if (first[i])
                        out[count++] = first[i];
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return 0;
            }
            return count;
        }

        // ---- gameplay ---------------------------------------------------------

        bool BudgetLeft(volatile long& budget)
        {
            return InterlockedDecrement(&budget) >= 0;
        }

        int PodIndex(Policy::Action action)
        {
            return action == Policy::Action::DropAmmo ? 1 : 0;
        }

        long GaugeOf(void* object)
        {
            const long gauge = SafeGetCurAmmo(SafeGetHandle(object));
            return gauge > 0 ? gauge : 0;
        }

        void DeployMru(void* object, MruObjectState& state, const char* why)
        {
            state.deployed = true;
            state.sawIdleCurrent = false;
            const bool stopped = SafeSetCommand(object, Policy::kWhatStop);
            if (BudgetLeft(g_DeployLogBudget))
            {
                LogShimA(LogLevel::Info, kComponent, "obj=%p deployed (%s); Stop order %s", object, why,
                    stopped ? "given" : "faulted");
            }
        }

        void PackMru(void* object, MruObjectState& state, const char* why)
        {
            state.deployed = false;
            state.sawIdleCurrent = false;
            if (BudgetLeft(g_DeployLogBudget))
                LogShimA(LogLevel::Info, kComponent, "obj=%p undeployed (%s)", object, why);
        }

        void MarkPodFailed(void* objectClass, int index, const char* name)
        {
            bool first = false;
            AcquireSRWLockExclusive(&g_ClassDataLock);
            const auto it = g_ClassData.find(reinterpret_cast<uintptr_t>(objectClass));
            if (it != g_ClassData.end() && !it->second.podFailed[index])
            {
                it->second.podFailed[index] = true;
                first = true;
            }
            ReleaseSRWLockExclusive(&g_ClassDataLock);
            if (first)
            {
                LogShimA(LogLevel::Warn, kComponent,
                    "class %p: pod class \"%s\" not found; Drop %s stays disabled", objectClass, name,
                    index == 0 ? "Repair" : "Ammo");
            }
        }

        // Builds the pod behind the MRU and charges the gauge. True when a
        // pod was built (the cooldown then restarts).
        bool DropPod(void* object, void* objectClass, const Policy::Config& c, Policy::Action action)
        {
            const char* name = Policy::PodClass(c, action);
            void* podClass = SafeFindClass(name);
            if (!podClass)
            {
                MarkPodFailed(objectClass, PodIndex(action), name);
                return false;
            }
            uint8_t matrix[kMatrixBytes] = {};
            ObjectInfo self{};
            if (!ReadMatrix(object, matrix) || !ReadObjectInfo(object, self))
                return false;
            double posit[3] = {};
            float front[3] = {};
            std::memcpy(posit, matrix + kMatrixPosit, sizeof(posit));
            std::memcpy(front, matrix + kMatrixFront, sizeof(front));
            double dropAt[3] = {};
            Policy::DropPosition(posit, front, Policy::kPodDropBackOffset, dropAt);
            std::memcpy(matrix + kMatrixPosit, dropAt, sizeof(dropAt));

            void* pod = nullptr;
            const bool clean = SafeBuildPod(podClass, matrix, self.team, object, pod);
            // A pod that exists is charged and starts the cooldown, even if
            // a later step (velocity, mission, owner) faulted.
            const bool built = pod != nullptr;
            const long cost = Policy::PodCost(c, action);
            if (built && cost > 0)
                SafeAddAmmo(SafeGetHandle(object), -cost);
            if (BudgetLeft(g_DropLogBudget))
            {
                LogShimA(built && clean ? LogLevel::Info : LogLevel::Warn, kComponent,
                    "obj=%p %s: pod \"%s\" %s team=%d at (%.1f, %.1f, %.1f) cost=%ld",
                    object, Policy::ActionName(action), name,
                    !built ? (clean ? "Build returned null" : "Build faulted")
                           : (clean ? "built" : "built, a follow-up call faulted"),
                    self.team, dropAt[0], dropAt[1], dropAt[2], built ? cost : 0L);
            }
            return built;
        }

        // Hook point for an AI deploy rule. No rule is built: the research
        // only proposed "AI auto-deploy" and the user has not chosen one
        // (Docs/MRU_CLASS.md "AI deploy"). A rule must leave player-team
        // MRUs alone (the user's team is [0x00917B00], FUN_004ab380.c lines
        // 326-328) and must hold its own order still: the deploy hold packs
        // an MRU whose pending or current order moves.
        enum class AiDeployRequest : int
        {
            None,
            Deploy,
            Pack,
        };

        AiDeployRequest AiDeployHook(void* /*object*/, const MruObjectState& /*state*/,
                                     const Policy::Config& /*config*/)
        {
            return AiDeployRequest::None;
        }

        // One service tick: every friendly helicopter/vehicle inside the
        // radius (any order, moving or not), at most kMaxServiceTargets.
        void ServiceTick(void* object, const Policy::Config& c, MruObjectState& state)
        {
            ObjectInfo self{};
            if (!ReadObjectInfo(object, self))
                return;
            const uint32_t selfHandle = SafeGetHandle(object);
            long gauge = SafeGetCurAmmo(selfHandle);
            if (gauge < 0)
                gauge = 0;
            const size_t n = SnapshotObjects(g_ObjectScratch, kMaxObjects);
            int targets = 0;
            float healed = 0.0f;
            long reloaded = 0;
            long drained = 0;
            for (size_t i = 0; i < n && targets < Policy::kMaxServiceTargets; ++i)
            {
                void* const other = g_ObjectScratch[i];
                const bool isSelf = other == object;
                if (isSelf && !c.serviceSelf)
                    continue;
                ObjectInfo t{};
                if (!ReadObjectInfo(other, t) || !Policy::IsServiceClassId(t.classId))
                    continue;
                const bool ally = t.team > 0 && t.team != self.team && SafeIsAlly(object, other);
                if (!Policy::IsFriendlyTeam(self.team, t.team, ally))
                    continue;
                if (!Policy::InRadius(t.posit[0] - self.posit[0], t.posit[1] - self.posit[1],
                                      t.posit[2] - self.posit[2], c.serviceRadius))
                    continue;
                const uint32_t handle = isSelf ? selfHandle : SafeGetHandle(other);
                const float before = SafeGetCurHealth(handle);
                if (!(before > 0.0f))
                    continue;
                ++targets;

                const float repair = Policy::RepairGrant(c.repairPerTick, c.ammoPerRepair,
                                                         static_cast<float>(gauge) - state.drainCarry);
                if (repair > 0.0f)
                {
                    SafeAddHealth(handle, repair);
                    const float served = SafeGetCurHealth(handle) - before;
                    if (served > 0.0f)
                    {
                        healed += served;
                        const long d = Policy::TakeDrain(state.drainCarry, served, c.ammoPerRepair, gauge);
                        if (d > 0)
                        {
                            SafeAddAmmo(selfHandle, -d);
                            gauge -= d;
                            drained += d;
                        }
                    }
                }

                // Reloading itself from its own gauge would only move ammo
                // in a circle.
                if (isSelf)
                    continue;
                const long reload = Policy::ReloadGrant(c.reloadPerTick, c.ammoPerReload,
                                                        static_cast<float>(gauge) - state.drainCarry);
                if (reload <= 0)
                    continue;
                const long ammoBefore = SafeGetCurAmmo(handle);
                if (ammoBefore < 0)
                    continue;
                SafeAddAmmo(handle, reload);
                const long served = SafeGetCurAmmo(handle) - ammoBefore;
                if (served > 0)
                {
                    reloaded += served;
                    const long d = Policy::TakeDrain(state.drainCarry, static_cast<float>(served),
                                                     c.ammoPerReload, gauge);
                    if (d > 0)
                    {
                        SafeAddAmmo(selfHandle, -d);
                        gauge -= d;
                        drained += d;
                    }
                }
            }

            const bool costed = c.ammoPerRepair > 0.0f || c.ammoPerReload > 0.0f;
            const bool empty = costed && gauge <= 0;
            if (empty != state.gaugeWasEmpty)
            {
                state.gaugeWasEmpty = empty;
                LogShimA(LogLevel::Info, kComponent, "obj=%p gauge %s", object,
                    empty ? "empty: costed service stops (free service continues)" : "refilled: costed service resumes");
            }
            if ((healed > 0.0f || reloaded > 0) && BudgetLeft(g_ServiceLogBudget))
            {
                LogShimA(LogLevel::Info, kComponent,
                    "obj=%p service tick: %d unit(s) in range, healed=%.0f reloaded=%ld drained=%ld gauge=%ld",
                    object, targets, healed, reloaded, drained, gauge);
            }
        }

        // Slot 15 work after the stock Simulate: cooldown, the queued drop,
        // the deploy hold, the AI hook point, the service tick.
        void MruTick(void* object, float dt)
        {
            MruClassData data;
            void* objectClass = nullptr;
            if (!LookupClassData(object, data, objectClass))
                return;
            const Policy::Config& c = data.config;
            MruObjectState state = LoadState(object);
            state.cooldownLeft = Policy::TickCooldown(state.cooldownLeft, dt);

            if (state.pendingDrop != Policy::Action::None)
            {
                const Policy::Action action = state.pendingDrop;
                state.pendingDrop = Policy::Action::None;
                const Policy::DropBlock block = Policy::WhyNoDrop(
                    c, action, state.cooldownLeft, GaugeOf(object), data.podFailed[PodIndex(action)]);
                if (block == Policy::DropBlock::None)
                {
                    if (DropPod(object, objectClass, c, action))
                        state.cooldownLeft = c.podCooldown;
                }
                else if (BudgetLeft(g_DropLogBudget))
                {
                    LogShimA(LogLevel::Info, kComponent, "obj=%p %s refused at drop time: %s", object,
                        Policy::ActionName(action), Policy::DropBlockName(block));
                }
            }

            if (state.deployed)
            {
                int pendingWhat = 0;
                int currentWhat = 0;
                if (ReadWhats(object, pendingWhat, currentWhat) &&
                    !Policy::KeepsDeploy(pendingWhat, currentWhat, state.sawIdleCurrent))
                {
                    PackMru(object, state, "given a move order");
                }
            }

            switch (AiDeployHook(object, state, c))
            {
            case AiDeployRequest::Deploy:
                if (!state.deployed)
                    DeployMru(object, state, "AI rule");
                break;
            case AiDeployRequest::Pack:
                if (state.deployed)
                    PackMru(object, state, "AI rule");
                break;
            default:
                break;
            }

            const bool active = Policy::ServiceActive(c, state.deployed);
            if (active != state.serviceWasActive)
            {
                state.serviceWasActive = active;
                state.serviceAccumulator = 0.0f;
                LogShimA(LogLevel::Info, kComponent, "obj=%p service %s (radius %.1f, %s)", object,
                    active ? "on" : "off", c.serviceRadius,
                    c.serviceRadius <= 0.0f ? "serviceRadius 0"
                    : c.serviceDeployed     ? (state.deployed ? "deployed" : "not deployed")
                                            : "serviceDeployed 0");
            }
            if (active && Policy::ConsumeTick(state.serviceAccumulator, dt, c.serviceInterval))
                ServiceTick(object, c, state);

            StoreState(object, state);
        }

        // Slot 15 of the MRU vtable copy.
        void __fastcall MruSimulateHook(void* self, void* /*edx*/, float dt)
        {
            reinterpret_cast<FnSimulate>(g_Thunks + kSimulateSlot * kThunkStride)(self, dt);
            if (!g_GameplayOn || !Hooks::IsSinglePlayerSession())
                return;
            MruTick(self, dt);
        }

        // Slot 0 of the MRU vtable copy.
        void* __fastcall MruDestructorHook(void* self, void* /*edx*/, unsigned int flags)
        {
            EraseState(self);
            return reinterpret_cast<FnDestructor>(g_Thunks + kDestructorSlot * kThunkStride)(self, flags);
        }

        // Enabled bits for slots 7-9: a drop when it could go now, Deploy
        // (or Undeploy) always.
        void MenuEnables(void* object, int (&enables)[Policy::kMenuEntryCount])
        {
            for (int i = 0; i < Policy::kMenuEntryCount; ++i)
                enables[i] = 1;
            MruClassData data;
            void* objectClass = nullptr;
            if (!LookupClassData(object, data, objectClass))
                return;
            const MruObjectState state = LoadState(object);
            const long gauge = GaugeOf(object);
            for (int i = 0; i < Policy::kMenuEntryCount; ++i)
            {
                const Policy::Action action = Policy::kMenuEntries[i].action;
                if (Policy::IsPodAction(action))
                {
                    enables[i] = Policy::CanDrop(data.config, action, state.cooldownLeft, gauge,
                                                 data.podFailed[PodIndex(action)]) ? 1 : 0;
                }
            }
        }

        // Stock Cloak/Decloak (FUN_004aefa0(7) in HoverCraft::UpdateModeList) owns slot 7 on a
        // cloak-capable craft; leave it there so a cloaked MRU can still decloak.
        constexpr int32_t kModeCloak = 0x18;
        constexpr int32_t kModeDecloak = 0x19;
        bool g_CloakSkipLogged = false;

        void FillMruMenu(void* self, const int (&enables)[Policy::kMenuEntryCount])
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
                g_SetMode(modeList, e.slot, e.mode, enables[i]);
            }
        }

        // Slot 23 of the MRU vtable copy. Craft::Simulate calls it every
        // frame for a unit on the user's team (FUN_004ab380.c lines
        // 326-328), so the enabled bits follow the cooldown and gauge.
        void __fastcall MruUpdateModeListHook(void* self, void* /*edx*/)
        {
            reinterpret_cast<FnThisVoid>(g_Thunks + kUpdateModeListSlot * kThunkStride)(self);
            if (!g_GameplayOn)
                return;
            const bool on = Hooks::IsSinglePlayerSession();
            LogMenuDecision(on ? 1 : 0, self);
            if (!on)
                return;
            int enables[Policy::kMenuEntryCount] = {};
            MenuEnables(self, enables);
            __try
            {
                FillMruMenu(self, enables);
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
            g_MruVtable[1 + kSimulateSlot] = reinterpret_cast<void*>(&MruSimulateHook);
            g_MruVtable[1 + kDestructorSlot] = reinterpret_cast<void*>(&MruDestructorHook);
            return true;
        }

        void GiveUp(const char* what)
        {
            g_GaveUp = true;
            LogShimA(LogLevel::Warn, kComponent, "classLabel=mru not installed: %s", what);
        }

        // [SinglePlayer] MruGameplay (default off, read once) and its rows.
        // Off, missing rows or the kill switch leave the class a plain hover
        // with the `mru` label: no menu entries, no service.
        bool BindGameplay()
        {
            bool option = false;
            if (!TryGetUserConfigBool(Hooks::kUserConfigSinglePlayerSection, kGameplayOption, option))
                option = false;
            if (!option)
            {
                LogShimA(LogLevel::Info, kComponent, "gameplay off ([SinglePlayer] %s = 0)", kGameplayOption);
                return false;
            }
            if (EnvFlagEnabled(kGameplayKillSwitch))
            {
                LogShimA(LogLevel::Info, kComponent, "gameplay off (%s set)", kGameplayKillSwitch);
                return false;
            }
            uint32_t addHealth = 0, addAmmo = 0, getHealth = 0, getAmmo = 0, findClass = 0, aiMission = 0;
            uint32_t setVelocity = 0, setOwner = 0, setCommand = 0, isAlly = 0;
            const HookEngine::EngineRow rows[] = {
                { "MruAddHealthByHandle", &addHealth },
                { "MruAddAmmoByHandle", &addAmmo },
                { "MruGetCurHealthByHandle", &getHealth },
                { "MruGetCurAmmoByHandle", &getAmmo },
                { "GameObjectClassFindByName", &findClass },
                { "AiMissionGetCurrent", &aiMission },
                { "GameObjectSetVelocity", &setVelocity },
                { "GameObjectSetOwner", &setOwner },
                { "GameObjectSetCommand", &setCommand },
                { "RtsPowerIsAlly", &isAlly },
            };
            if (!HookEngine::BindEngineRows("MRU gameplay", rows))
            {
                LogShimA(LogLevel::Warn, kComponent, "gameplay off: an engine row did not bind");
                return false;
            }
            const uintptr_t build = HookEngine::ResolveNamedAddress("GameObjectClass::Build");
            const uintptr_t objectList = HookEngine::ResolveNamedAddress("GameObject::objectList");
            if (!build || !objectList || !g_GameObjectGetHandleAddr)
            {
                LogShimA(LogLevel::Warn, kComponent,
                    "gameplay off: GameObjectClass::Build, GameObject::objectList or GameObject::GetHandle unresolved");
                return false;
            }
            g_AddHealth = reinterpret_cast<FnAddHealthByHandle>(addHealth);
            g_AddAmmo = reinterpret_cast<FnAddAmmoByHandle>(addAmmo);
            g_GetCurHealth = reinterpret_cast<FnGetCurHealthByHandle>(getHealth);
            g_GetCurAmmo = reinterpret_cast<FnGetCurAmmoByHandle>(getAmmo);
            g_FindClass = reinterpret_cast<FnFindClassByName>(findClass);
            g_AiMissionGetCurrent = reinterpret_cast<FnAiMissionGetCurrent>(aiMission);
            g_SetVelocity = reinterpret_cast<FnSetVelocity>(setVelocity);
            g_SetOwner = reinterpret_cast<FnSetOwner>(setOwner);
            g_SetCommand = reinterpret_cast<FnSetCommand>(setCommand);
            g_IsAlly = reinterpret_cast<FnIsAlly>(isAlly);
            g_Build = reinterpret_cast<FnBuild>(build);
            g_ObjectListGlobal = objectList;
            g_GetHandle = reinterpret_cast<FnGetHandle>(g_GameObjectGetHandleAddr);
            return true;
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
            "ammoPerAmmoPod=%.1f (used only with [SinglePlayer] %s = 1: %s)",
            odfName, objectClass, data.sectionPresent ? "present" : "absent (plain hover menu)",
            c.serviceRadius, c.serviceInterval, c.repairPerTick, c.reloadPerTick, c.ammoPerRepair,
            c.ammoPerReload, c.serviceSelf ? 1 : 0, c.serviceDeployed ? 1 : 0, c.podCooldown,
            c.repairPodClass[0] ? c.repairPodClass : "-", c.ammoPodClass[0] ? c.ammoPodClass : "-",
            c.ammoPerRepairPod, c.ammoPerAmmoPod, kGameplayOption, g_GameplayOn ? "on" : "off");
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
        return g_Installed && g_GameplayOn && HasMruVtable(object) && Hooks::IsSinglePlayerSession();
    }

    bool IsMruDeployed(void* object)
    {
        return IsMruMenuObject(object) && LoadState(object).deployed;
    }

    bool NoteMruMenuPick(void* object, uint32_t handle, int mode, bool packAll)
    {
        if (!IsMruMenuObject(object))
            return false;

        int32_t modes[Policy::kModeSlots] = {};
        uint32_t enabled = 0;
        const bool listRead = ReadModeList(object, modes, enabled);
        const Policy::Action action = Policy::ActionForMode(mode);
        // An MRU entry is consumed whenever it sits in its slot, even when
        // disabled: its reused id must never reach the stock dispatch.
        const bool consumed = listRead && action != Policy::Action::None &&
            Policy::EntryInItsSlot(modes, mode);
        int pendingWhat = -1;
        ReadPendingWhat(object, pendingWhat);

        const char* result = "stock dispatch";
        if (consumed)
        {
            MruClassData data;
            void* objectClass = nullptr;
            MruObjectState state = LoadState(object);
            if (action == Policy::Action::Deploy)
            {
                if (packAll)
                {
                    if (state.deployed)
                        PackMru(object, state, "menu");
                    result = "undeployed";
                }
                else if (!state.deployed)
                {
                    DeployMru(object, state, "menu");
                    result = "deployed";
                }
                else
                {
                    result = "already deployed";
                }
                StoreState(object, state);
            }
            else if (!LookupClassData(object, data, objectClass))
            {
                result = "no class data, ignored";
            }
            else
            {
                const Policy::DropBlock block = Policy::WhyNoDrop(data.config, action, state.cooldownLeft,
                    GaugeOf(object), data.podFailed[PodIndex(action)]);
                if (block == Policy::DropBlock::None)
                {
                    // Dropped in the next Simulate, as Dispenser::Trigger
                    // arms and Dispenser::Simulate builds.
                    state.pendingDrop = action;
                    StoreState(object, state);
                    result = "drop queued for the next Simulate";
                }
                else
                {
                    result = Policy::DropBlockName(block);
                }
            }
        }

        if (InterlockedDecrement(&g_PickLogBudget) >= 0)
        {
            LogShimA(LogLevel::Info, kComponent,
                "menu pick mode=0x%X (%s) on mru obj=%p handle=0x%08X pendingWhat=%d: %s%s",
                mode, consumed ? Policy::ActionName(action) : "stock entry", object, handle, pendingWhat,
                consumed ? "consumed, " : "", result);
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
        g_GameplayOn = BindGameplay();
        g_Installed = true;
        LogShimA(LogLevel::Info, kComponent,
            "installed classLabel=mru (HoverCraftClass alias; vtable copy slots %u UpdateModeList, %u Simulate, "
            "%u destructor; kill switch %s); gameplay %s",
            static_cast<unsigned>(kUpdateModeListSlot), static_cast<unsigned>(kSimulateSlot),
            static_cast<unsigned>(kDestructorSlot), kKillSwitch,
            g_GameplayOn ? "on (menu slots 7/8/9, pods, deploy, service; single player)"
                         : "off (plain hover menu, no service)");
    }

    bool IsMruClassInstalled()
    {
        return g_Installed;
    }
}
