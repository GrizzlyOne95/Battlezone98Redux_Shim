// rts_placement.cpp
// BZR Open Shim - RTS placement aids, local visuals for the local player:
//
//  * [Gameplay] RtsBuildGhost (default off): while the stock placement quad
//    shows (ConstructionDisplay, the ground.G/.Y/.R sprite), a see-through
//    copy of the picked building's own mesh at the rig's drop matrix
//    (ConstructionRig +0x378), tinted like the quad: green valid, yellow no
//    power, red blocked. While the Go To Nav submenu is open and Build at Nav
//    is active with a picked rig selected, a neutral ghost at every listed
//    nav, facing the player's heading on the terrain.
//  * [Gameplay] RtsPendingBuildGhost (default off): a dim neutral ghost at the
//    drop matrix of each of the local player's rigs with a BUILD order whose
//    construction has not started (its BuildGoto task, process +0x38), at
//    most eight.
//  * [Gameplay] RtsPowerRange (default off): while the stock preview or a nav
//    ghost shows a COMM/TURR/SHLD class, a ground ring of each allied power
//    plant's powerRadius (rings drawn by rts_markers.cpp).
//  * [Gameplay] RtsWaypointLines (default off): the command-record reader for
//    the waypoint lines rts_markers.cpp draws.
//
// The preview is read, never driven: a pass-through post-hook on
// ConstructionRig::GetCommand (vtable 0x00877994 slot 12, 0x0049D230; the
// reticle hover's only route in, the slot is its only reference in the image)
// records {rig, class, drop matrix, result, sprite, tick} after the stock
// call. Build at Nav's own validation call is skipped (SuppressRtsGhostRecord).
// The ghosts are shim-owned Ogre entities of the class's own mesh with one of
// four generated materials (rts_markers_assets.h) set on the entity; the
// mesh's materials are never touched. One cached entity per class for the
// cursor ghost (one visible at a time), ten for the nav ghosts, eight for
// the pending build ghosts (all Neutral). A mesh that
// fails to load is remembered and never retried.
//
// Rows: scripts/patches.json "Rts*" (and the ConstructionRig rows Build at Nav
// shares), bound once each on the patch thread; every engine read and call
// runs under SEH. Driver: TickRtsPlacement from the RTS marker tick
// (rts_markers.cpp). Docs/RTS_MARKERS.md.
#include "rts_placement.h"

#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "engine_globals.h"
#include "hook_engine.h"
#include "rts_markers_assets.h"
#include "rts_placement_policy.h"
#include "shell_casing_physics.h"
#include "shim_log.h"

#include <Windows.h>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <string>

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error RtsPlacement reads the GOG x86 engine layout
#endif

namespace BZROpenShim
{
    namespace Hooks
    {
        namespace
        {
            namespace RP = RtsPlacement;
            namespace SC = ShellCasings;
            using Vec3 = SC::Vec3;

            constexpr const char* kComponent = "rtsplacement";
            constexpr int kMaxInstallAttempts = 40;

            // ---- Layout (pinned by the rows named) ---------------------------
            constexpr size_t kGetCommandSlot = 12;           // ConstructionRigGetCommandPos identity
            constexpr size_t kRigDropClassOffset = 0x370;    // RtsGhostTowerSigCheck
            constexpr size_t kRigDropMatrixOffset = 0x378;   // RtsGhostDisplaySetBox +0x04
            constexpr size_t kDisplayGlobalOperand = 0x0E;   // RtsGhostDisplaySetBox: mov ecx, imm32
            constexpr size_t kDisplaySpriteOffset = 0x68;    // RtsGhostDisplayInit / Render
            constexpr size_t kDisplayGreenOffset = 0x6C;     // RtsGhostDisplayInit
            constexpr size_t kDisplayYellowOffset = 0x70;
            constexpr size_t kDisplayRedOffset = 0x74;
            constexpr size_t kAltPassOperand = 0x18;         // RtsGhostDisplayRender: cmp [imm32], 0
            constexpr size_t kClassSigOffset = 0x14;         // RtsGhostTowerSigCheck
            constexpr size_t kClassBaseNameOffset = 0x28;    // RtsGhostMeshName
            constexpr size_t kPanelOpenMenuOffset = 0x117C;  // RtsNavSubmenuOpen
            constexpr size_t kNavMenuIdOperand = 0x0E;       // RtsNavSubmenuOpen: cmp edx, [imm32]
            constexpr size_t kUserTeamOperand = 0x04;        // RtsUserTeam: mov eax, [imm32]
            constexpr size_t kObjectMatrixBlockOffset = 0xF4; // RtsUserFront
            constexpr size_t kMatrixBlockFrontOffset = 0x38;
            constexpr size_t kPlantVectorOperand = 0x03;     // RtsPowerPlantList: mov [ebp-44h], imm32
            constexpr size_t kPowerRadiusOffset = 0x160;     // RtsPowerRadius
            constexpr size_t kOwnershipOffset = 0x80;        // == 2: network replica (rts_commands.cpp)
            constexpr uint8_t kReplicaOwnership = 2;
            constexpr size_t kObjectProcessOffset = 0xFC;    // GetAIProcess 0x0045BDF0 (ai_native_orders.cpp)
            constexpr size_t kProcessTaskOffset = 0x38;      // RtsPendingBuildTask
            constexpr size_t kTaskStateOffset = 0x08;        // RtsPendingBuildStage
            constexpr size_t kTaskResultOffset = 0x0C;
            constexpr size_t kTaskOwnerOffset = 0x10;        // RtsPendingBuildStage
            constexpr size_t kTaskStageOffset = 0x14C;       // RtsPendingBuildGotoCtor / Stage
            constexpr size_t kTaskClassOffset = 0x150;       // RtsPendingBuildGotoCtor
            constexpr size_t kObj76FlagsOffset = 0x14;       // as laser_sight.cpp: 0x200 = dead
            constexpr uint32_t kObj76DeadFlag = 0x200;
            constexpr size_t kMaxObjects = 4096;             // as rts_commands.cpp

            // MAT_3D (bzr_hooks_internal.h LegacyMat3): right, up, front
            // floats, a pad, then the position as doubles.
            struct DropMatrix
            {
                float right[3];
                float up[3];
                float front[3];
                uint32_t pad;
                double posit[3];
            };
            static_assert(sizeof(DropMatrix) == 64, "MAT_3D is 64 bytes");

            // ---- Config ------------------------------------------------------
            bool g_ConfigLoaded = false;
            bool g_GhostOn = false;
            bool g_PowerOn = false;
            bool g_LinesOn = false;
            bool g_PendingOn = false;

            void LoadConfig()
            {
                bool value = false;
                g_GhostOn = TryGetUserConfigBool("Gameplay", "RtsBuildGhost", value) ? value : false;
                value = false;
                g_PowerOn = TryGetUserConfigBool("Gameplay", "RtsPowerRange", value) ? value : false;
                value = false;
                g_LinesOn = TryGetUserConfigBool("Gameplay", "RtsWaypointLines", value) ? value : false;
                value = false;
                g_PendingOn = TryGetUserConfigBool("Gameplay", "RtsPendingBuildGhost", value) ? value : false;
                g_ConfigLoaded = true;
                LogShimA(LogLevel::Info, kComponent,
                         "[RTSPLACE] config buildGhost=%d powerRange=%d waypointLines=%d pendingBuildGhost=%d",
                         g_GhostOn ? 1 : 0, g_PowerOn ? 1 : 0, g_LinesOn ? 1 : 0, g_PendingOn ? 1 : 0);
            }

            // ---- Engine bindings (patch thread, then read-only) --------------
            using FnRigGetCommand = int(__thiscall*)(void* rig, const float* pos);
            using FnIsAlly = bool(__thiscall*)(void* self, void* other);
            using FnTerrainHeightAt = double(__cdecl*)(double x, double z);

            bool g_CoreBound = false;
            bool g_SlotInstalled = false;
            // Each row group is bound once (BindEngineRows logs every refusal);
            // only the slot write is retried, and its refusal is logged once.
            bool g_CoreTried = false;
            bool g_NavTried = false;
            bool g_PowerTried = false;
            bool g_LinesTried = false;
            bool g_PendingTried = false;
            bool g_SlotRefusalLogged = false;
            bool g_NavBound = false;
            bool g_PowerBound = false;
            bool g_LinesBound = false;
            bool g_PendingBound = false;
            uint32_t g_RigVtable = 0;
            uint32_t g_BuildGotoVtable = 0;
            uintptr_t g_ObjectListGlobal = 0;
            uint32_t g_GetCommandAddr = 0;
            uintptr_t g_Display = 0;
            uintptr_t g_AltPassFlag = 0;
            uintptr_t g_Panel = 0;
            uintptr_t g_NavMenuIdAddr = 0;
            uintptr_t g_UserTeamGlobal = 0;
            uintptr_t g_PlantVector = 0;
            FnRigGetCommand g_OrigGetCommand = nullptr;
            FnIsAlly g_FnIsAlly = nullptr;
            FnTerrainHeightAt g_HeightAt = nullptr;

            bool GhostReady()
            {
                return g_CoreBound && g_SlotInstalled;
            }

            // ---- Fault-safe access (no C++ objects in these frames) ----------
            bool CopySeh(uintptr_t address, void* out, size_t size)
            {
                if (address < 0x10000)
                    return false;
                __try
                {
                    std::memcpy(out, reinterpret_cast<const void*>(address), size);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool ReadU32(uintptr_t address, uint32_t& out)
            {
                return CopySeh(address, &out, sizeof(out));
            }

            bool ReadI32(uintptr_t address, int32_t& out)
            {
                return CopySeh(address, &out, sizeof(out));
            }

            bool SafeIsAlly(void* self, void* other)
            {
                if (!g_FnIsAlly || !self || !other)
                    return false;
                __try
                {
                    return g_FnIsAlly(self, other);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool TerrainHeightSeh(double x, double z, double& out)
            {
                if (!g_HeightAt)
                    return false;
                __try
                {
                    out = g_HeightAt(x, z);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
                return std::isfinite(out) && std::fabs(out) < 1.0e6;
            }

            // ---- Preview record (GetCommand post-hook, game thread) ----------
            struct PreviewRecord
            {
                bool valid = false;
                void* rig = nullptr;
                uint32_t buildClass = 0;
                DropMatrix matrix = {};
                int result = 0;
                RP::Tint tint = RP::Tint::None;
                uint32_t serial = 0;
            };
            PreviewRecord g_Record;
            uint32_t g_Serial = 0;
            bool g_SuppressRecord = false;
            volatile long g_RecordLogBudget = 8;

            // After the stock call: what the stock quad will show this frame.
            void RecordPreviewSeh(void* rig, int result)
            {
                if (result != RP::kResultValid && result != RP::kResultRefused)
                    return;
                __try
                {
                    const uintptr_t base = reinterpret_cast<uintptr_t>(rig);
                    const uintptr_t display = g_Display;
                    const RP::Tint tint = RP::TintFor(
                        result, *reinterpret_cast<const uintptr_t*>(display + kDisplaySpriteOffset),
                        *reinterpret_cast<const uintptr_t*>(display + kDisplayGreenOffset),
                        *reinterpret_cast<const uintptr_t*>(display + kDisplayYellowOffset),
                        *reinterpret_cast<const uintptr_t*>(display + kDisplayRedOffset));
                    if (tint == RP::Tint::None)
                        return;
                    const uint32_t buildClass = *reinterpret_cast<const uint32_t*>(base + kRigDropClassOffset);
                    if (buildClass < 0x10000)
                        return;
                    std::memcpy(&g_Record.matrix, reinterpret_cast<const void*>(base + kRigDropMatrixOffset),
                                sizeof(DropMatrix));
                    g_Record.rig = rig;
                    g_Record.buildClass = buildClass;
                    g_Record.result = result;
                    g_Record.tint = tint;
                    g_Record.serial = g_Serial;
                    g_Record.valid = true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    g_Record.valid = false;
                }
            }

            // ConstructionRig::GetCommand(const VECTOR_3D*): thiscall, ret 4.
            int __fastcall RigGetCommandHook(void* rig, void* /*edx*/, const float* pos)
            {
                const int result = g_OrigGetCommand(rig, pos);
                if (!g_SuppressRecord && (g_GhostOn || g_PowerOn) && rig)
                {
                    RecordPreviewSeh(rig, result);
                    if (g_Record.valid && g_Record.serial == g_Serial && InterlockedDecrement(&g_RecordLogBudget) >= 0)
                        LogShimA(LogLevel::Info, kComponent, "[RTSPLACE] preview result=%d tint=%d class=0x%08X",
                                 result, static_cast<int>(g_Record.tint), g_Record.buildClass);
                }
                return result;
            }

            // ---- Ogre --------------------------------------------------------
            using FnSetCastShadows = void(__thiscall*)(void*, bool);
            using FnSetMaterialName = void(__thiscall*)(void*, const std::string&, const std::string&);
            using FnDestroyEntity = void(__thiscall*)(void*, void*);

            struct GhostOgre
            {
                FnOgreGetRootSceneNode getRootSceneNode = nullptr;
                FnOgreCreateChildSceneNode createChildSceneNode = nullptr;
                FnOgreCreateEntity createEntity = nullptr;
                FnDestroyEntity destroyEntity = nullptr;
                FnOgreAttachObject attachObject = nullptr;
                FnSetMaterialName setMaterialName = nullptr;
                FnSetCastShadows setCastShadows = nullptr;
                FnOgreSetVisible setVisible = nullptr;
                FnOgreSetNodePosition setPosition = nullptr;
                FnOgreSetNodeOrientation setOrientation = nullptr;
                bool usable = false;
            };

            const GhostOgre& GetOgre()
            {
                static GhostOgre api;
                static bool resolved = false;
                if (resolved)
                    return api;
                resolved = true;
                api.getRootSceneNode =
                    ResolveOgreProc<FnOgreGetRootSceneNode>("?getRootSceneNode@SceneManager@Ogre@@UAEPAVSceneNode@2@XZ");
                api.createChildSceneNode = ResolveOgreProc<FnOgreCreateChildSceneNode>(
                    "?createChildSceneNode@SceneNode@Ogre@@UAEPAV12@ABVVector3@2@ABVQuaternion@2@@Z");
                api.createEntity = ResolveOgreProc<FnOgreCreateEntity>(
                    "?createEntity@SceneManager@Ogre@@UAEPAVEntity@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$"
                    "allocator@D@2@@std@@@Z");
                api.destroyEntity = ResolveOgreProc<FnDestroyEntity>("?destroyEntity@SceneManager@Ogre@@UAEXPAVEntity@2@@Z");
                api.attachObject =
                    ResolveOgreProc<FnOgreAttachObject>("?attachObject@SceneNode@Ogre@@UAEXPAVMovableObject@2@@Z");
                api.setMaterialName = ResolveOgreProc<FnSetMaterialName>(
                    "?setMaterialName@Entity@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@"
                    "std@@0@Z");
                api.setCastShadows = ResolveOgreProc<FnSetCastShadows>("?setCastShadows@MovableObject@Ogre@@QAEX_N@Z");
                api.setVisible = ResolveOgreProc<FnOgreSetVisible>("?setVisible@MovableObject@Ogre@@UAEX_N@Z");
                api.setPosition = ResolveOgreProc<FnOgreSetNodePosition>("?setPosition@Node@Ogre@@UAEXMMM@Z");
                api.setOrientation = ResolveOgreProc<FnOgreSetNodeOrientation>("?setOrientation@Node@Ogre@@UAEXMMMM@Z");
                api.usable = api.getRootSceneNode && api.createChildSceneNode && api.createEntity && api.destroyEntity &&
                             api.attachObject && api.setMaterialName && api.setCastShadows && api.setVisible &&
                             api.setPosition && api.setOrientation;
                if (!api.usable)
                    LogShimA(LogLevel::Warn, kComponent, "[RTSPLACE] Ogre exports unresolved; no build ghost");
                return api;
            }

            // Ogre takes these by const reference; kept alive for the process
            // so the SEH frames below hold no C++ objects.
            const std::string& MaterialGroup()
            {
                static const std::string group = kChunkPayloadResourceRootName;
                return group;
            }

            const std::string* MaterialNameFor(RP::Tint tint)
            {
                static const std::string names[] = {RP::kGhostMaterialValid, RP::kGhostMaterialNoPower,
                                                    RP::kGhostMaterialBlocked, RP::kGhostMaterialNeutral};
                switch (tint)
                {
                case RP::Tint::Valid:
                    return &names[0];
                case RP::Tint::NoPower:
                    return &names[1];
                case RP::Tint::Blocked:
                    return &names[2];
                case RP::Tint::Neutral:
                    return &names[3];
                case RP::Tint::None:
                default:
                    return nullptr;
                }
            }

            struct GhostSlot
            {
                uint32_t buildClass = 0; // the class whose mesh the entity shows
                void* node = nullptr;
                void* entity = nullptr;
                RP::Tint tint = RP::Tint::None;
                bool visible = false;
                uint32_t lastUsed = 0;
            };

            constexpr size_t kCursorCache = 8;
            GhostSlot g_CursorGhosts[kCursorCache];
            GhostSlot g_NavGhosts[RP::kMaxNavGhosts];
            GhostSlot g_PendingGhosts[RP::kMaxPendingGhosts];
            void* g_SceneManager = nullptr;
            bool g_SceneFailed = false; // node creation failed in this scene; not retried until it changes

            // Classes whose mesh did not load (process lifetime; a missing
            // mesh stays missing). A full list overwrites its oldest entry.
            constexpr size_t kFailedClassCapacity = 64;
            uint32_t g_FailedClasses[kFailedClassCapacity] = {};
            size_t g_FailedCount = 0;
            size_t g_FailedNext = 0;

            bool ClassFailed(uint32_t buildClass)
            {
                for (size_t i = 0; i < g_FailedCount; ++i)
                    if (g_FailedClasses[i] == buildClass)
                        return true;
                return false;
            }

            void ClearFailedClasses()
            {
                g_FailedCount = 0;
                g_FailedNext = 0;
            }

            void RememberFailedClass(uint32_t buildClass)
            {
                g_FailedClasses[g_FailedNext] = buildClass;
                g_FailedNext = (g_FailedNext + 1) % kFailedClassCapacity;
                if (g_FailedCount < kFailedClassCapacity)
                    ++g_FailedCount;
            }

            bool CreateNodeCpp(const GhostOgre& api, void* sceneManager, GhostSlot& slot)
            {
                try
                {
                    void* root = api.getRootSceneNode(sceneManager);
                    if (!root)
                        return false;
                    const OgreVector3 origin = {0.0f, 0.0f, 0.0f};
                    const OgreQuaternion identity = {1.0f, 0.0f, 0.0f, 0.0f};
                    slot.node = api.createChildSceneNode(root, origin, identity);
                    return slot.node != nullptr;
                }
                catch (...)
                {
                    return false;
                }
            }

            bool CreateNodeSeh(const GhostOgre& api, void* sceneManager, GhostSlot& slot)
            {
                __try
                {
                    return CreateNodeCpp(api, sceneManager, slot);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            // A missing mesh throws (Ogre FileNotFoundException): caught here.
            // An entity made before a later call throws is destroyed again.
            bool CreateEntityCpp(const GhostOgre& api, void* sceneManager, const std::string& mesh, GhostSlot& slot)
            {
                void* entity = nullptr;
                try
                {
                    entity = api.createEntity(sceneManager, mesh);
                    if (!entity)
                        return false;
                    api.attachObject(slot.node, entity);
                    api.setCastShadows(entity, false);
                    api.setVisible(entity, false);
                    slot.entity = entity;
                    return true;
                }
                catch (...)
                {
                    if (entity)
                    {
                        try
                        {
                            api.destroyEntity(sceneManager, entity);
                        }
                        catch (...)
                        {
                        }
                    }
                    return false;
                }
            }

            bool CreateEntitySeh(const GhostOgre& api, void* sceneManager, const std::string& mesh, GhostSlot& slot)
            {
                __try
                {
                    return CreateEntityCpp(api, sceneManager, mesh, slot);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            // destroyEntity detaches it from the node (MovableObject dtor).
            void DestroyEntityCpp(const GhostOgre& api, void* sceneManager, void* entity)
            {
                try
                {
                    api.destroyEntity(sceneManager, entity);
                }
                catch (...)
                {
                }
            }

            void DestroyEntitySeh(const GhostOgre& api, void* sceneManager, void* entity)
            {
                __try
                {
                    DestroyEntityCpp(api, sceneManager, entity);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                }
            }

            // Ogre 1.10 SubEntity::setMaterialName falls back to BaseWhite
            // without throwing, so a missing ghost material would draw an
            // opaque white building: all four must exist before any ghost.
            using FnMaterialManager = void* (*)();
            using FnResourceExists = bool(__thiscall*)(void*, const std::string&);

            bool MaterialExistsSeh(FnMaterialManager getManager, FnResourceExists exists, const std::string& name)
            {
                __try
                {
                    void* const manager = getManager();
                    return manager && exists(manager, name);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool g_MaterialsChecked = false; // per scene; ForgetGhosts / the entity drop reset it
            bool g_MaterialsPresent = false;
            bool g_MaterialsMissingLogged = false;

            bool GhostMaterialsPresent()
            {
                if (g_MaterialsChecked)
                    return g_MaterialsPresent;
                static const FnMaterialManager getManager =
                    ResolveOgreProc<FnMaterialManager>("?getSingletonPtr@MaterialManager@Ogre@@SAPAV12@XZ");
                static const FnResourceExists exists = ResolveOgreProc<FnResourceExists>(
                    "?resourceExists@ResourceManager@Ogre@@UAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$"
                    "allocator@D@2@@std@@@Z");
                g_MaterialsChecked = true;
                g_MaterialsPresent = getManager && exists;
                const char* missing = getManager && exists ? nullptr : "(MaterialManager exports unresolved)";
                const RP::Tint tints[] = {RP::Tint::Valid, RP::Tint::NoPower, RP::Tint::Blocked, RP::Tint::Neutral};
                for (size_t i = 0; g_MaterialsPresent && i < sizeof(tints) / sizeof(tints[0]); ++i)
                {
                    const std::string* name = MaterialNameFor(tints[i]);
                    if (!name || !MaterialExistsSeh(getManager, exists, *name))
                    {
                        g_MaterialsPresent = false;
                        missing = RP::MaterialFor(tints[i]);
                    }
                }
                if (!g_MaterialsPresent && !g_MaterialsMissingLogged)
                {
                    g_MaterialsMissingLogged = true;
                    LogShimA(LogLevel::Warn, kComponent, "[RTSPLACE] ghost material %s missing; no build ghost",
                             missing ? missing : "?");
                }
                return g_MaterialsPresent;
            }

            bool SetMaterialCpp(const GhostOgre& api, void* entity, const std::string& name)
            {
                try
                {
                    api.setMaterialName(entity, name, MaterialGroup());
                    return true;
                }
                catch (...)
                {
                    return false;
                }
            }

            bool SetMaterialSeh(const GhostOgre& api, void* entity, const std::string& name)
            {
                __try
                {
                    return SetMaterialCpp(api, entity, name);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool SetVisibleSeh(const GhostOgre& api, void* entity, bool visible)
            {
                __try
                {
                    api.setVisible(entity, visible);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool PlaceNodeSeh(const GhostOgre& api, void* node, const Vec3& position, const SC::Quat& q)
            {
                __try
                {
                    api.setPosition(node, position.x, position.y, position.z);
                    api.setOrientation(node, q.w, q.x, q.y, q.z);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            void HideSlot(GhostSlot& slot)
            {
                if (slot.visible && slot.entity)
                    SetVisibleSeh(GetOgre(), slot.entity, false);
                slot.visible = false;
            }

            void HideGhosts(GhostSlot* slots, size_t count)
            {
                for (size_t i = 0; i < count; ++i)
                    HideSlot(slots[i]);
            }

            void HideAllGhosts()
            {
                HideGhosts(g_CursorGhosts, kCursorCache);
                HideGhosts(g_NavGhosts, RP::kMaxNavGhosts);
                HideGhosts(g_PendingGhosts, RP::kMaxPendingGhosts);
            }

            void ForgetGhosts(const wchar_t* reason)
            {
                size_t held = 0;
                for (GhostSlot& slot : g_CursorGhosts)
                {
                    if (slot.node || slot.entity)
                        ++held;
                    slot = GhostSlot{};
                }
                for (GhostSlot& slot : g_NavGhosts)
                {
                    if (slot.node || slot.entity)
                        ++held;
                    slot = GhostSlot{};
                }
                for (GhostSlot& slot : g_PendingGhosts)
                {
                    if (slot.node || slot.entity)
                        ++held;
                    slot = GhostSlot{};
                }
                g_SceneManager = nullptr;
                g_SceneFailed = false;
                g_MaterialsChecked = false;
                if (held)
                    LogShimW(LogLevel::Info, kComponent, L"[RTSPLACE] forgot %zu ghost(s) (%ls)", held,
                             reason ? reason : L"unspecified");
            }

            // The class's mesh name from GameObjectClass +0x28 (char[8]).
            std::string MeshNameOf(uint32_t buildClass)
            {
                char base[RP::kMeshBaseLength] = {};
                if (!CopySeh(static_cast<uintptr_t>(buildClass) + kClassBaseNameOffset, base, sizeof(base)))
                    return std::string();
                return RP::MeshNameFor(base);
            }

            // Gives `slot` an entity of `buildClass` (destroying another
            // class's entity first). False when the mesh does not load (the
            // class is remembered) or Ogre is unusable in this scene.
            bool EnsureSlotEntity(const GhostOgre& api, void* sceneManager, GhostSlot& slot, uint32_t buildClass)
            {
                if (slot.entity && slot.buildClass == buildClass)
                    return true;
                if (g_SceneFailed || ClassFailed(buildClass))
                    return false;
                // The ghost materials live in the chunk payload group.
                if (!EnsureSkinnedGibResourceLocations() || !GhostMaterialsPresent())
                {
                    g_SceneFailed = true;
                    return false;
                }
                if (slot.entity)
                {
                    HideSlot(slot);
                    DestroyEntitySeh(api, sceneManager, slot.entity);
                    slot.entity = nullptr;
                    slot.buildClass = 0;
                    slot.tint = RP::Tint::None;
                }
                if (!slot.node && !CreateNodeSeh(api, sceneManager, slot))
                {
                    g_SceneFailed = true;
                    LogShimA(LogLevel::Warn, kComponent, "[RTSPLACE] ghost node creation failed; ghosts off for this scene");
                    return false;
                }
                const std::string mesh = MeshNameOf(buildClass);
                if (mesh.empty() || !CreateEntitySeh(api, sceneManager, mesh, slot))
                {
                    RememberFailedClass(buildClass);
                    LogShimA(LogLevel::Warn, kComponent, "[RTSPLACE] no ghost for class 0x%08X: mesh '%s' did not load",
                             buildClass, mesh.c_str());
                    return false;
                }
                slot.buildClass = buildClass;
                slot.tint = RP::Tint::None;
                LogShimA(LogLevel::Info, kComponent, "[RTSPLACE] ghost entity for %s (class 0x%08X)", mesh.c_str(),
                         buildClass);
                return true;
            }

            bool ShowSlot(const GhostOgre& api, GhostSlot& slot, RP::Tint tint, const Vec3& renderPos, const SC::Quat& q)
            {
                if (slot.tint != tint)
                {
                    const std::string* material = MaterialNameFor(tint);
                    if (!material || !SetMaterialSeh(api, slot.entity, *material))
                        return false;
                    slot.tint = tint;
                }
                if (!PlaceNodeSeh(api, slot.node, renderPos, q))
                    return false;
                if (!slot.visible)
                {
                    if (!SetVisibleSeh(api, slot.entity, true))
                        return false;
                    slot.visible = true;
                }
                slot.lastUsed = g_Serial;
                return true;
            }

            bool RenderPose(const float right[3], const float up[3], const float front[3], const double posit[3],
                            const Vec3& origin, Vec3& renderPos, SC::Quat& q)
            {
                RP::Axes axes{};
                if (!RP::RenderAxesFromSimBasis(right, up, front, axes) || !std::isfinite(posit[0]) ||
                    !std::isfinite(posit[1]) || !std::isfinite(posit[2]))
                    return false;
                q = SC::QuatFromAxes({axes.x[0], axes.x[1], axes.x[2]}, {axes.y[0], axes.y[1], axes.y[2]},
                                     {axes.z[0], axes.z[1], axes.z[2]});
                renderPos = SC::SimToRenderPoint(
                    {static_cast<float>(posit[0]), static_cast<float>(posit[1]), static_cast<float>(posit[2])}, origin);
                return SC::Finite(renderPos);
            }

            // The cursor ghost: the cached entity of the record's class, the
            // only visible one.
            void ShowCursorGhost(const GhostOgre& api, void* sceneManager, const Vec3& origin)
            {
                const PreviewRecord& rec = g_Record;
                Vec3 renderPos{};
                SC::Quat q{};
                if (!RenderPose(rec.matrix.right, rec.matrix.up, rec.matrix.front, rec.matrix.posit, origin, renderPos, q))
                {
                    HideGhosts(g_CursorGhosts, kCursorCache);
                    return;
                }
                size_t pick = kCursorCache;
                for (size_t i = 0; i < kCursorCache; ++i)
                    if (g_CursorGhosts[i].entity && g_CursorGhosts[i].buildClass == rec.buildClass)
                        pick = i;
                if (pick == kCursorCache)
                {
                    // An empty slot, else the least recently shown.
                    pick = 0;
                    for (size_t i = 0; i < kCursorCache; ++i)
                    {
                        if (!g_CursorGhosts[i].entity)
                        {
                            pick = i;
                            break;
                        }
                        if (static_cast<uint32_t>(g_Serial - g_CursorGhosts[i].lastUsed) >
                            static_cast<uint32_t>(g_Serial - g_CursorGhosts[pick].lastUsed))
                            pick = i;
                    }
                }
                for (size_t i = 0; i < kCursorCache; ++i)
                    if (i != pick)
                        HideSlot(g_CursorGhosts[i]);
                GhostSlot& slot = g_CursorGhosts[pick];
                if (!EnsureSlotEntity(api, sceneManager, slot, rec.buildClass) ||
                    !ShowSlot(api, slot, rec.tint, renderPos, q))
                    HideSlot(slot);
            }

            // ---- Nav ghosts --------------------------------------------------
            struct NavSpot
            {
                float pos[3];
            };

            bool NavSubmenuOpen()
            {
                int32_t open = -1, navMenu = -2;
                return g_NavBound && ReadI32(g_Panel + kPanelOpenMenuOffset, open) &&
                       ReadI32(g_NavMenuIdAddr, navMenu) && open == navMenu;
            }

            // The beacons the submenu lists: user team slots 0x23..0x2C.
            size_t GatherNavs(NavSpot (&out)[RP::kMaxNavGhosts])
            {
                uint32_t team = 0;
                if (!ReadU32(g_UserTeamGlobal, team) || team < 0x10000)
                    return 0;
                size_t n = 0;
                for (int slot = RP::kFirstNavSlot; slot <= RP::kLastNavSlot && n < RP::kMaxNavGhosts; ++slot)
                {
                    uint32_t nav = 0;
                    if (!ReadU32(static_cast<uintptr_t>(team) + 4u * static_cast<uint32_t>(slot), nav) || nav < 0x10000)
                        continue;
                    float pos[3] = {};
                    if (!TryGetGameObjectWorldPosition(reinterpret_cast<void*>(static_cast<uintptr_t>(nav)), pos))
                        continue;
                    double ground = pos[1];
                    if (TerrainHeightSeh(pos[0], pos[2], ground))
                        pos[1] = static_cast<float>(ground);
                    std::memcpy(out[n].pos, pos, sizeof(pos));
                    ++n;
                }
                return n;
            }

            // The player's heading: GameObject +0xF4 matrix block, front at
            // +0x38 (RtsUserFront). Sim +Z when unreadable.
            void UserFront(float front[3])
            {
                front[0] = 0.0f;
                front[1] = 0.0f;
                front[2] = 1.0f;
                const uintptr_t slot = EngineGlobals::UserObjectSlot();
                uint32_t user = 0, block = 0;
                float f[3] = {};
                if (!slot || !ReadU32(slot, user) || user < 0x10000 ||
                    !ReadU32(static_cast<uintptr_t>(user) + kObjectMatrixBlockOffset, block) || block < 0x10000 ||
                    !CopySeh(static_cast<uintptr_t>(block) + kMatrixBlockFrontOffset, f, sizeof(f)))
                    return;
                if (std::isfinite(f[0]) && std::isfinite(f[1]) && std::isfinite(f[2]))
                    std::memcpy(front, f, sizeof(f));
            }

            void ShowNavGhosts(const GhostOgre& api, void* sceneManager, const Vec3& origin, uint32_t buildClass,
                               const NavSpot* navs, size_t count)
            {
                float heading[3], right[3], up[3], front[3];
                UserFront(heading);
                if (!RP::YawBasis(heading, right, up, front))
                {
                    right[0] = 1.0f, right[1] = 0.0f, right[2] = 0.0f;
                    up[0] = 0.0f, up[1] = 1.0f, up[2] = 0.0f;
                    front[0] = 0.0f, front[1] = 0.0f, front[2] = 1.0f;
                }
                for (size_t i = 0; i < RP::kMaxNavGhosts; ++i)
                {
                    GhostSlot& slot = g_NavGhosts[i];
                    if (i >= count)
                    {
                        HideSlot(slot);
                        continue;
                    }
                    const double posit[3] = {navs[i].pos[0], navs[i].pos[1], navs[i].pos[2]};
                    Vec3 renderPos{};
                    SC::Quat q{};
                    if (!RenderPose(right, up, front, posit, origin, renderPos, q) ||
                        !EnsureSlotEntity(api, sceneManager, slot, buildClass) ||
                        !ShowSlot(api, slot, RP::Tint::Neutral, renderPos, q))
                        HideSlot(slot);
                }
            }


            // ---- Pending build ghosts ----------------------------------------
            struct PendingBuild
            {
                void* rig;
                uint32_t buildClass;
                DropMatrix matrix;
            };

            size_t g_PendingShownLast = 0;

            // The engine's object vector (GameObject::objectList: _Myfirst at
            // +0, _Mylast at +4; lua_handle_sync.cpp SnapshotObjects).
            size_t SnapshotObjects(uint32_t* out, size_t capacity)
            {
                size_t count = 0;
                __try
                {
                    const uint8_t* vec = *reinterpret_cast<uint8_t* const*>(g_ObjectListGlobal);
                    if (!vec)
                        return 0;
                    const uint32_t* first = *reinterpret_cast<const uint32_t* const*>(vec);
                    const uint32_t* last = *reinterpret_cast<const uint32_t* const*>(vec + 4);
                    if (!first || last < first || static_cast<size_t>(last - first) > kMaxObjects)
                        return 0;
                    const size_t available = static_cast<size_t>(last - first);
                    for (size_t i = 0; i < available && count < capacity; ++i)
                        if (first[i] >= 0x10000)
                            out[count++] = first[i];
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return 0;
                }
                return count;
            }

            // One object: a live, local Construction Rig on `userTeam` whose
            // AI process (+0xFC) runs a BuildGoto task (process +0x38, vtable
            // checked) of its own (task +0x10) that has not started building.
            bool ReadPendingBuildSeh(uint32_t object, int32_t userTeam, PendingBuild& out)
            {
                __try
                {
                    const uint8_t* const obj = reinterpret_cast<const uint8_t*>(static_cast<uintptr_t>(object));
                    if (*reinterpret_cast<const uint32_t*>(obj) != g_RigVtable ||
                        *reinterpret_cast<const int32_t*>(obj + kGameObjectActualTeamOffset) != userTeam ||
                        obj[kOwnershipOffset] == kReplicaOwnership)
                        return false;
                    const uint8_t* const obj76 = *reinterpret_cast<const uint8_t* const*>(obj + kGameObjectObjOffset);
                    if (obj76 && (*reinterpret_cast<const uint32_t*>(obj76 + kObj76FlagsOffset) & kObj76DeadFlag))
                        return false;
                    const uint8_t* const proc = *reinterpret_cast<const uint8_t* const*>(obj + kObjectProcessOffset);
                    if (reinterpret_cast<uintptr_t>(proc) < 0x10000)
                        return false;
                    const uint8_t* const task = *reinterpret_cast<const uint8_t* const*>(proc + kProcessTaskOffset);
                    if (reinterpret_cast<uintptr_t>(task) < 0x10000 ||
                        *reinterpret_cast<const uint32_t*>(task) != g_BuildGotoVtable ||
                        *reinterpret_cast<const uint8_t* const*>(task + kTaskOwnerOffset) != obj ||
                        !RP::PendingBuildShows(*reinterpret_cast<const int32_t*>(task + kTaskStateOffset),
                                               *reinterpret_cast<const int32_t*>(task + kTaskResultOffset),
                                               *reinterpret_cast<const int32_t*>(task + kTaskStageOffset)))
                        return false;
                    const uint32_t buildClass = *reinterpret_cast<const uint32_t*>(task + kTaskClassOffset);
                    if (buildClass < 0x10000)
                        return false;
                    out.rig = const_cast<uint8_t*>(obj);
                    out.buildClass = buildClass;
                    std::memcpy(&out.matrix, obj + kRigDropMatrixOffset, sizeof(DropMatrix));
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            // At most kMaxPendingGhosts, in object-list order; `skipRig` (the
            // rig the cursor ghost is previewing) is left out. `found` counts
            // the rigs with a pending order before that skip.
            size_t GatherPendingBuilds(PendingBuild (&out)[RP::kMaxPendingGhosts], const void* skipRig,
                                       size_t& found)
            {
                found = 0;
                static uint32_t objects[kMaxObjects];
                const uintptr_t slot = EngineGlobals::UserObjectSlot();
                uint32_t user = 0;
                int32_t userTeam = -1;
                if (!slot || !ReadU32(slot, user) || user < 0x10000 ||
                    !ReadI32(static_cast<uintptr_t>(user) + kGameObjectActualTeamOffset, userTeam))
                    return 0;
                const size_t count = SnapshotObjects(objects, kMaxObjects);
                size_t n = 0;
                for (size_t i = 0; i < count && found < RP::kMaxPendingGhosts; ++i)
                {
                    if (!ReadPendingBuildSeh(objects[i], userTeam, out[n]))
                        continue;
                    ++found;
                    if (out[n].rig != skipRig)
                        ++n;
                }
                return n;
            }

            // A slot already holding the class keeps it (no entity churn
            // while the same orders stand); the rest take the free slots.
            void ShowPendingGhosts(const GhostOgre& api, void* sceneManager, const Vec3& origin,
                                   const PendingBuild* builds, size_t count)
            {
                bool taken[RP::kMaxPendingGhosts] = {};
                bool placed[RP::kMaxPendingGhosts] = {};
                size_t assign[RP::kMaxPendingGhosts] = {};
                for (size_t b = 0; b < count; ++b)
                {
                    for (size_t s = 0; s < RP::kMaxPendingGhosts && !placed[b]; ++s)
                    {
                        if (!taken[s] && g_PendingGhosts[s].entity &&
                            g_PendingGhosts[s].buildClass == builds[b].buildClass)
                        {
                            taken[s] = placed[b] = true;
                            assign[b] = s;
                        }
                    }
                }
                // Empty slots before ones caching another class's entity.
                for (int pass = 0; pass < 2; ++pass)
                {
                    for (size_t b = 0; b < count; ++b)
                    {
                        for (size_t s = 0; s < RP::kMaxPendingGhosts && !placed[b]; ++s)
                        {
                            if (!taken[s] && (pass == 1 || !g_PendingGhosts[s].entity))
                            {
                                taken[s] = placed[b] = true;
                                assign[b] = s;
                            }
                        }
                    }
                }
                for (size_t s = 0; s < RP::kMaxPendingGhosts; ++s)
                    if (!taken[s])
                        HideSlot(g_PendingGhosts[s]);
                for (size_t b = 0; b < count; ++b)
                {
                    GhostSlot& slot = g_PendingGhosts[assign[b]];
                    const DropMatrix& m = builds[b].matrix;
                    Vec3 renderPos{};
                    SC::Quat q{};
                    if (!RenderPose(m.right, m.up, m.front, m.posit, origin, renderPos, q) ||
                        !EnsureSlotEntity(api, sceneManager, slot, builds[b].buildClass) ||
                        !ShowSlot(api, slot, RP::Tint::Neutral, renderPos, q))
                        HideSlot(slot);
                }
            }

            // ---- Power rings -------------------------------------------------
            RtsPowerRing g_PowerRings[RP::kMaxPowerRings];
            size_t g_PowerRingCount = 0;
            volatile long g_PowerLogBudget = 4;

            bool ClassNeedsPower(uint32_t buildClass)
            {
                uint32_t sig = 0;
                return buildClass >= 0x10000 &&
                       ReadU32(static_cast<uintptr_t>(buildClass) + kClassSigOffset, sig) && RP::NeedsPower(sig);
            }

            void GatherPowerRings(void* rig, float focusX, float focusZ)
            {
                static uint32_t plants[RP::kMaxPlantEntries];
                static RP::PlantCandidate candidates[RP::kMaxPlantEntries];
                uint32_t vec[2] = {};
                size_t count = 0;
                if (!CopySeh(g_PlantVector, vec, sizeof(vec)) || !RP::PlantVectorSane(vec[0], vec[1], count))
                {
                    if (InterlockedDecrement(&g_PowerLogBudget) >= 0)
                        LogShimA(LogLevel::Warn, kComponent, "[RTSPLACE] power plant list unreadable (0x%08X..0x%08X)",
                                 vec[0], vec[1]);
                    return;
                }
                if (count == 0 || !CopySeh(vec[0], plants, count * sizeof(uint32_t)))
                    return;
                for (size_t i = 0; i < count; ++i)
                {
                    RP::PlantCandidate& c = candidates[i];
                    c = RP::PlantCandidate{};
                    void* const plant = reinterpret_cast<void*>(static_cast<uintptr_t>(plants[i]));
                    if (plants[i] < 0x10000 || !SafeIsAlly(rig, plant))
                        continue;
                    uint32_t plantClass = 0;
                    float radius = 0.0f;
                    if (!ReadU32(plants[i] + kGameObjectClassOffset, plantClass) || plantClass < 0x10000 ||
                        !CopySeh(static_cast<uintptr_t>(plantClass) + kPowerRadiusOffset, &radius, sizeof(radius)) ||
                        !TryGetGameObjectWorldPosition(plant, c.pos))
                        continue;
                    c.radius = radius;
                    c.ally = true;
                }
                size_t chosen[RP::kMaxPowerRings] = {};
                const size_t n =
                    RP::SelectPowerRings(candidates, count, focusX, focusZ, RP::kMaxPowerRings, chosen);
                for (size_t i = 0; i < n; ++i)
                {
                    std::memcpy(g_PowerRings[i].centre, candidates[chosen[i]].pos, sizeof(g_PowerRings[i].centre));
                    g_PowerRings[i].radius = candidates[chosen[i]].radius;
                }
                g_PowerRingCount = n;
            }

            // ---- Install -----------------------------------------------------
            bool ReadOperand(uint32_t site, size_t offset, uintptr_t& out)
            {
                uint32_t value = 0;
                if (!site || !HookEngine::ReadMemory(site + static_cast<uint32_t>(offset), &value, sizeof(value)) ||
                    value < 0x10000)
                    return false;
                out = value;
                return true;
            }

            void BindRows()
            {
                if (!g_CoreTried)
                {
                    g_CoreTried = true;
                    uint32_t setBox = 0, init = 0, render = 0, results = 0, meshName = 0, panel = 0;
                    const HookEngine::EngineRow rows[] = {
                        {"ConstructionRigVtable", &g_RigVtable},
                        {"ConstructionRigGetCommandPos", &g_GetCommandAddr},
                        {"RtsGhostDisplaySetBox", &setBox},
                        {"RtsGhostDisplayInit", &init},
                        {"RtsGhostDisplayRender", &render},
                        {"RtsGhostPreviewResults", &results},
                        {"RtsGhostMeshName", &meshName},
                        {"ControlPanelGlobal", &panel},
                    };
                    if (HookEngine::BindEngineRows("RTS build ghost", rows) &&
                        ReadOperand(setBox, kDisplayGlobalOperand, g_Display) &&
                        ReadOperand(render, kAltPassOperand, g_AltPassFlag))
                    {
                        if (VtableTypeNameMatches(g_RigVtable, ".?AVConstructionRig@@"))
                        {
                            g_Panel = panel;
                            g_OrigGetCommand = reinterpret_cast<FnRigGetCommand>(static_cast<uintptr_t>(g_GetCommandAddr));
                            g_CoreBound = true;
                        }
                        else
                        {
                            LogShimA(LogLevel::Warn, kComponent,
                                     "[RTSPLACE] ConstructionRigVtable RTTI mismatch; no build ghost");
                        }
                    }
                }
                if (g_CoreBound && !g_NavTried)
                {
                    g_NavTried = true;
                    uint32_t open = 0, loop = 0, team = 0, slot = 0, front = 0;
                    const HookEngine::EngineRow rows[] = {
                        {"RtsNavSubmenuOpen", &open}, {"RtsNavSlotLoop", &loop}, {"RtsUserTeam", &team},
                        {"RtsTeamGetSlot", &slot},    {"RtsUserFront", &front},
                    };
                    const uint32_t heightAt = HookEngine::ResolveNamedAddress("Terrain::HeightAt");
                    if (HookEngine::BindEngineRows("RTS build ghost navs", rows) && heightAt &&
                        ReadOperand(open, kNavMenuIdOperand, g_NavMenuIdAddr) &&
                        ReadOperand(team, kUserTeamOperand, g_UserTeamGlobal))
                    {
                        g_HeightAt = reinterpret_cast<FnTerrainHeightAt>(static_cast<uintptr_t>(heightAt));
                        g_NavBound = true;
                    }
                }
                if (g_CoreBound && !g_PowerTried)
                {
                    g_PowerTried = true;
                    uint32_t sigCheck = 0, list = 0, isAlly = 0, radius = 0;
                    const HookEngine::EngineRow rows[] = {
                        {"RtsGhostTowerSigCheck", &sigCheck},
                        {"RtsPowerPlantList", &list},
                        {"RtsPowerIsAlly", &isAlly},
                        {"RtsPowerRadius", &radius},
                    };
                    if (HookEngine::BindEngineRows("RTS power range", rows) &&
                        ReadOperand(list, kPlantVectorOperand, g_PlantVector))
                    {
                        g_FnIsAlly = reinterpret_cast<FnIsAlly>(static_cast<uintptr_t>(isAlly));
                        g_PowerBound = true;
                    }
                }
                if (g_CoreBound && !g_PendingTried)
                {
                    g_PendingTried = true;
                    uint32_t task = 0, ctor = 0, stage = 0;
                    const HookEngine::EngineRow rows[] = {
                        {"BuildGotoVtable", &g_BuildGotoVtable},
                        {"RtsPendingBuildTask", &task},
                        {"RtsPendingBuildGotoCtor", &ctor},
                        {"RtsPendingBuildStage", &stage},
                    };
                    const uint32_t objectList = HookEngine::ResolveNamedAddress("GameObject::objectList");
                    if (HookEngine::BindEngineRows("RTS pending build ghost", rows) && objectList)
                    {
                        if (VtableTypeNameMatches(g_BuildGotoVtable, ".?AVBuildGoto@@"))
                        {
                            g_ObjectListGlobal = objectList;
                            g_PendingBound = true;
                        }
                        else
                        {
                            LogShimA(LogLevel::Warn, kComponent,
                                     "[RTSPLACE] BuildGotoVtable RTTI mismatch; no pending build ghost");
                        }
                    }
                }
                if (!g_LinesTried)
                {
                    g_LinesTried = true;
                    uint32_t promote = 0, path = 0;
                    const HookEngine::EngineRow rows[] = {
                        {"RtsCommandPromote", &promote},
                        {"RtsAiPathCtor", &path},
                    };
                    g_LinesBound = HookEngine::BindEngineRows("RTS waypoint lines", rows);
                }
            }

            // Vtable slot 12, as turret_attack_orders.cpp: RTTI, then the
            // slot must hold the stock function (or our hook already).
            bool InstallSlot()
            {
                const uintptr_t slotAddress = g_RigVtable + kGetCommandSlot * sizeof(void*);
                void* const hook = reinterpret_cast<void*>(&RigGetCommandHook);
                if (!VtableTypeNameMatches(g_RigVtable, ".?AVConstructionRig@@"))
                    return false;
                uint32_t current = 0;
                if (!HookEngine::ReadMemory(static_cast<uint32_t>(slotAddress), &current, sizeof(current)))
                    return false;
                if (current == static_cast<uint32_t>(reinterpret_cast<uintptr_t>(hook)))
                    return true;
                if (current != g_GetCommandAddr)
                {
                    if (g_SlotRefusalLogged)
                        return false;
                    g_SlotRefusalLogged = true;
                    LogShimA(LogLevel::Warn, kComponent,
                             "[RTSPLACE] GetCommand slot 0x%08X holds 0x%08X, expected 0x%08X; no build ghost",
                             static_cast<uint32_t>(slotAddress), current, g_GetCommandAddr);
                    return false;
                }
                if (!WritePointerValue(slotAddress, hook))
                {
                    if (g_SlotRefusalLogged)
                        return false;
                    g_SlotRefusalLogged = true;
                    LogShimA(LogLevel::Warn, kComponent, "[RTSPLACE] GetCommand slot write failed; no build ghost");
                    return false;
                }
                LogShimA(LogLevel::Info, kComponent, "[RTSPLACE] ConstructionRig::GetCommand post-hook installed slot=0x%08X",
                         static_cast<uint32_t>(slotAddress));
                return true;
            }

            void MarkOptions()
            {
                struct Mark
                {
                    const char* key;
                    bool ready;
                    const char* reason;
                };
                const Mark marks[] = {
                    {"RtsBuildGhost", GhostReady(),
                     "Unavailable: Build Ghost did not hook on this game build (see openshim.log)."},
                    {"RtsPowerRange", GhostReady() && g_PowerBound,
                     "Unavailable: Power Range did not hook on this game build (see openshim.log)."},
                    {"RtsWaypointLines", g_LinesBound,
                     "Unavailable: Waypoint Lines did not bind on this game build (see openshim.log)."},
                    {"RtsPendingBuildGhost", GhostReady() && g_PendingBound,
                     "Unavailable: Pending Build Ghost did not hook on this game build (see openshim.log)."},
                };
                for (const Mark& m : marks)
                {
                    if (m.ready)
                        ClearOptionHookFailed(m.key);
                    else
                        MarkOptionHookFailed(m.key, m.reason);
                }
            }
        }

        void InstallRtsPlacementIfPossible()
        {
            static bool s_done = false;
            static int s_attempts = 0;
            if (s_done)
                return;
            if (!g_ConfigLoaded)
                LoadConfig();
            ++s_attempts;
            BindRows();
            if (g_CoreBound && !g_SlotInstalled)
                g_SlotInstalled = InstallSlot();
            MarkOptions();
            const bool all = GhostReady() && g_NavBound && g_PowerBound && g_LinesBound && g_PendingBound;
            if (all || s_attempts >= kMaxInstallAttempts)
            {
                s_done = true;
                LogShimA(LogLevel::Info, kComponent,
                         "[RTSPLACE] install %s after %d attempt(s): ghost %s, nav ghosts %s, power %s, lines %s, "
                         "pending %s",
                         all ? "complete" : "gave up", s_attempts, GhostReady() ? "yes" : "no",
                         g_NavBound ? "yes" : "no", g_PowerBound ? "yes" : "no", g_LinesBound ? "yes" : "no",
                         g_PendingBound ? "yes" : "no");
            }
        }

        void ReloadRtsPlacementConfig()
        {
            // Applied on the next tick (game thread), which hides what is off.
            LoadConfig();
        }

        void SuppressRtsGhostRecord(bool suppress)
        {
            g_SuppressRecord = suppress;
        }

        bool RtsPlacementAnyEnabled()
        {
            if (!g_ConfigLoaded)
                LoadConfig();
            return g_GhostOn || g_PowerOn || g_LinesOn || g_PendingOn;
        }

        bool RtsWaypointLinesEnabled()
        {
            if (!g_ConfigLoaded)
                LoadConfig();
            return g_LinesOn && g_LinesBound;
        }

        void TickRtsPlacement(void* sceneManager, const float renderOrigin[3])
        {
            if (!g_ConfigLoaded)
                LoadConfig();
            ++g_Serial;
            g_PowerRingCount = 0;
            if (!GhostReady() || (!g_GhostOn && !g_PowerOn && !g_PendingOn) || !sceneManager || !renderOrigin)
            {
                HideAllGhosts();
                return;
            }
            if (g_SceneManager != sceneManager)
            {
                if (g_SceneManager)
                    ForgetGhosts(L"scene manager changed");
                g_SceneManager = sceneManager;
            }
            const Vec3 origin = {renderOrigin[0], renderOrigin[1], renderOrigin[2]};

            int32_t altPass = 0;
            if (!ReadI32(g_AltPassFlag, altPass))
                altPass = 1;
            // The hook stamps g_Serial as it stood since the previous tick,
            // and this tick has already incremented it: records made since the
            // previous tick carry g_Serial - 1, so that is "this tick" for
            // GhostVisible, and the tick before is the record one older.
            const uint32_t recordTick = g_Serial - 1u;
            const bool cursor = RP::GhostVisible(true, false, g_Record.valid, g_Record.serial, recordTick,
                                                 altPass != 0, g_Record.tint);

            void* navRig = nullptr;
            uint32_t navClass = 0;
            NavSpot navs[RP::kMaxNavGhosts] = {};
            size_t navCount = 0;
            if (g_NavBound && NavSubmenuOpen() && RtsBuildAtNavPickedRig(navRig, navClass) &&
                RP::NavGhostsWanted(true, false, true, 0, 0, navClass))
                navCount = GatherNavs(navs);

            const GhostOgre& api = GetOgre();
            if (g_GhostOn && cursor && api.usable)
                ShowCursorGhost(api, sceneManager, origin);
            else
                HideGhosts(g_CursorGhosts, kCursorCache);
            if (g_GhostOn && navCount && api.usable)
                ShowNavGhosts(api, sceneManager, origin, navClass, navs, navCount);
            else
                HideGhosts(g_NavGhosts, RP::kMaxNavGhosts);

            // The rig the cursor ghost is previewing shows that instead.
            PendingBuild pending[RP::kMaxPendingGhosts];
            size_t pendingCount = 0, pendingFound = 0;
            if (g_PendingOn && g_PendingBound && api.usable)
                pendingCount =
                    GatherPendingBuilds(pending, g_GhostOn && cursor ? g_Record.rig : nullptr, pendingFound);
            if (pendingCount)
                ShowPendingGhosts(api, sceneManager, origin, pending, pendingCount);
            else
                HideGhosts(g_PendingGhosts, RP::kMaxPendingGhosts);
            if (pendingFound != g_PendingShownLast)
            {
                LogShimA(LogLevel::Info, kComponent, "[RTSPLACE] rigs with a pending build %zu -> %zu",
                         g_PendingShownLast, pendingFound);
                g_PendingShownLast = pendingFound;
            }

            if (g_PowerOn && g_PowerBound)
            {
                if (cursor && ClassNeedsPower(g_Record.buildClass))
                    GatherPowerRings(g_Record.rig, static_cast<float>(g_Record.matrix.posit[0]),
                                     static_cast<float>(g_Record.matrix.posit[2]));
                else if (navCount && ClassNeedsPower(navClass))
                    GatherPowerRings(navRig, navs[0].pos[0], navs[0].pos[2]);
            }
        }

        void HideRtsPlacement()
        {
            HideAllGhosts();
            g_PowerRingCount = 0;
        }

        void ForgetRtsPlacementSceneResources(const wchar_t* reason)
        {
            ForgetGhosts(reason);
            g_PowerRingCount = 0;
        }

        void DestroyRtsPlacementSceneObjects(void* sceneManager, const wchar_t* reason)
        {
            // destroyAllEntities frees every entity of this scene manager,
            // ours included: destroy them first and keep the nodes.
            if (!sceneManager || sceneManager != g_SceneManager)
                return;
            const GhostOgre& api = GetOgre();
            size_t destroyed = 0;
            const auto drop = [&](GhostSlot& slot) {
                if (slot.entity)
                {
                    if (api.usable)
                        DestroyEntitySeh(api, sceneManager, slot.entity);
                    ++destroyed;
                }
                slot.entity = nullptr;
                slot.buildClass = 0;
                slot.tint = RP::Tint::None;
                slot.visible = false;
            };
            for (GhostSlot& slot : g_CursorGhosts)
                drop(slot);
            for (GhostSlot& slot : g_NavGhosts)
                drop(slot);
            for (GhostSlot& slot : g_PendingGhosts)
                drop(slot);
            ClearFailedClasses();
            g_SceneFailed = false;
            g_MaterialsChecked = false;
            g_PowerRingCount = 0;
            if (destroyed)
                LogShimW(LogLevel::Info, kComponent, L"[RTSPLACE] destroyed %zu ghost entit%ls (%ls)", destroyed,
                         destroyed == 1 ? L"y" : L"ies", reason ? reason : L"unspecified");
        }

        void DeactivateRtsPlacement(const wchar_t* /*reason*/)
        {
            HideAllGhosts();
            ClearFailedClasses();
            g_Record = PreviewRecord{};
            g_PendingShownLast = 0;
            g_PowerRingCount = 0;
            g_SceneFailed = false;
            g_RecordLogBudget = 8;
            g_PowerLogBudget = 4;
        }

        size_t RtsPowerRingsThisTick(RtsPowerRing* out, size_t capacity)
        {
            if (!out)
                return 0;
            const size_t n = g_PowerRingCount < capacity ? g_PowerRingCount : capacity;
            for (size_t i = 0; i < n; ++i)
                out[i] = g_PowerRings[i];
            return n;
        }

        bool ReadRtsCommandDestination(void* gameObject, bool pending, int& what, float& x, float& z)
        {
            what = 0;
            if (!g_LinesBound || !gameObject)
                return false;
            const auto read = [](uintptr_t address, void* out, size_t size) { return CopySeh(address, out, size); };
            return RP::CommandDestination(read, reinterpret_cast<uintptr_t>(gameObject),
                                          pending ? RP::kPendingRecordOffset : RP::kCurrentRecordOffset, what, x, z);
        }

        bool ReadRtsCommandTarget(void* gameObject, bool pending, int& what, uint32_t& who)
        {
            what = 0;
            who = 0;
            if (!g_LinesBound || !gameObject)
                return false;
            const auto read = [](uintptr_t address, void* out, size_t size) { return CopySeh(address, out, size); };
            return RP::CommandTarget(read, reinterpret_cast<uintptr_t>(gameObject),
                                     pending ? RP::kPendingRecordOffset : RP::kCurrentRecordOffset, what, who);
        }
    }
}
