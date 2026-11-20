// sp_player_paint.cpp
// BZR Open Shim - single-player player paint (Docs/SP_PLAYER_PAINT.md).
//
// [SinglePlayer] PlayerPaint picks a row of SpPlayerPaint::kVariants. At each
// frame start the local player's ship Entity is resolved from the player
// handle. Each SubEntity whose stock material has a mask
// (include/sp_player_paint_masks.inc) gets a clone named
// <current>@ospaint_<variant>: its en-high passes bind the mask on their
// teamMap unit and set the teamPaint uniform, and the clone is assigned to
// that SubEntity only. The ship's previous materials come back when the
// player leaves it, the setting changes, or the mission ends; the clones are
// removed from the MaterialManager at mission end and world teardown.
//
// Masks: OpenShim's own en-high programs (TEAM_PAINT_ENABLED +
// OSE_TEAM_MASK_R) read the BC4 openshim_paint_*.dds weight from .r. A pass
// that also binds actMap runs a Campaign Reimagined program that reads the
// weight from alpha, so it gets CR's own crteam mask, taken from CR's
// <material>_tm twin.
//
// GPU skinning clones skeletal craft materials. Painting such a SubEntity
// clones the skinned material (same vertex programs) and hands the change to
// OpenShimAdoptSurfaceVariant so GPU skinning keeps it.
//
// Render only: never in network games, no gameplay, sim or network state.
#include "sp_player_paint.h"
#include "sp_player_paint_policy.h"

#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "gpu_skinning.h"
#include "ogre_entity_liveness.h"
#include "render_profile_runtime.h"
#include "shim_log.h"

#include <Windows.h>

#include <atomic>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

extern "C" int __cdecl OpenShimAdoptSurfaceVariant(
    void* entity, unsigned int index, const char* before, const char* after);

namespace BZROpenShim
{
    namespace
    {
        using Hooks::ResolveOgreProc;
        namespace Policy = SpPlayerPaint;

        constexpr const char* kComponent = "sp-paint";
        constexpr uint32_t kProveIntervalFrames = 15;
        constexpr uint32_t kPruneIntervalFrames = 300;
        constexpr uint32_t kAwaitTeardownFrameLimit = 300;
        constexpr unsigned kMaxSubEntities = 64;
        constexpr uint16_t kMaxTechniques = 128;
        constexpr uint16_t kMaxPasses = 32;
        constexpr uint16_t kMaxUnits = 32;
        constexpr int kTexType2D = 2;  // Ogre::TEX_TYPE_2D
        constexpr size_t kSharedPtrUseCountOffset = 0x14;

        // Ogre::SharedPtr<T> as laid out by the shipping OgreMain.dll.
        struct SharedPtr
        {
            void* rep = nullptr;
            void* info = nullptr;
        };

        using FnSingleton = void* (__cdecl*)();
        using FnAddListener = void(__thiscall*)(void*, void*);
        using FnGetByName = SharedPtr* (__thiscall*)(void*, SharedPtr*, const std::string&, const std::string&);
        using FnRemove = void(__thiscall*)(void*, const std::string&);
        using FnClone = SharedPtr* (__thiscall*)(void*, SharedPtr*, const std::string&, bool, const std::string&);
        using FnStringRef = const std::string* (__thiscall*)(void*);
        using FnU16 = uint16_t(__thiscall*)(void*);
        using FnPtrAt16 = void* (__thiscall*)(void*, uint16_t);
        using FnU32 = uint32_t(__thiscall*)(void*);
        using FnPtrAt32 = void* (__thiscall*)(void*, uint32_t);
        using FnSharedRef = const SharedPtr* (__thiscall*)(void*);
        using FnSetMaterial = void(__thiscall*)(void*, const SharedPtr&);
        using FnSetTexture = void(__thiscall*)(void*, const std::string&, int);
        using FnBool = bool(__thiscall*)(void*);
        using FnSharedByValue = SharedPtr* (__thiscall*)(void*, SharedPtr*);
        using FnFindConstant = const void* (__thiscall*)(void*, const std::string&, bool);
        using FnSetVector4 = void(__thiscall*)(void*, const std::string&, const float*);

        struct OgreApi
        {
            FnSingleton rootSingleton = nullptr;
            FnAddListener addFrameListener = nullptr;
            FnSingleton materialManager = nullptr;
            FnGetByName getByName = nullptr;
            FnRemove removeResource = nullptr;
            FnClone cloneMaterial = nullptr;
            FnStringRef resourceName = nullptr;
            FnStringRef activeScheme = nullptr;  // optional, diagnostics only
            FnU16 techniqueCount = nullptr;
            FnPtrAt16 techniqueAt = nullptr;
            FnStringRef schemeName = nullptr;
            FnU16 passCount = nullptr;
            FnPtrAt16 passAt = nullptr;
            FnU16 unitCount = nullptr;
            FnPtrAt16 unitAt = nullptr;
            FnStringRef unitName = nullptr;
            FnStringRef unitTextureName = nullptr;
            FnSetTexture setUnitTexture = nullptr;
            FnBool hasFragmentProgram = nullptr;
            FnSharedByValue fragmentParameters = nullptr;
            FnFindConstant findConstant = nullptr;
            FnSetVector4 setVector4 = nullptr;
            FnU32 subEntityCount = nullptr;
            FnPtrAt32 subEntityAt = nullptr;
            FnSharedRef subEntityMaterial = nullptr;
            FnSetMaterial setSubEntityMaterial = nullptr;
        };
        OgreApi g_ogre;
        bool g_apiResolved = false;
        bool g_apiAvailable = false;

        // ---- State (render thread; RequestReload is the only cross-thread entry)
        std::atomic<bool> g_reloadRequested{false};
        std::atomic<bool> g_active{false};
        std::atomic<bool> g_failed{false};
        const Policy::Variant* g_variant = nullptr;
        bool g_missionEvaluated = false;
        bool g_teardownSeam = false;
        bool g_awaitTeardown = false;
        uint32_t g_awaitStartedFrames = 0;
        void* g_listenerRoot = nullptr;
        uint32_t g_frame = 0;
        const char* g_stage = "idle";
        char g_faultDetail[96] = {};
        OgreEntityLiveness::RootEntityCache g_rootProbes;

        // The clones this feature owns, by name (our SharedPtr reference).
        std::unordered_map<std::string, SharedPtr> g_clones;
        // CR team mask per stock material (from <material>_tm), "" = none.
        std::unordered_map<std::string, std::string> g_crMasks;
        // Current materials that cannot be painted this mission (logged once).
        std::unordered_set<std::string> g_unpaintable;

        struct Slot
        {
            unsigned index = 0;
            std::string original;  // material before paint
            std::string clone;
            unsigned repaints = 0;  // re-applied after something reverted it
        };
        struct Painted
        {
            void* entity = nullptr;
            std::vector<Slot> slots;
        };
        Painted g_painted;

        // ---- Change-only decision log ---------------------------------------
        enum DecisionSlot
        {
            kDecisionMission,
            kDecisionScheme,
            kDecisionCount
        };
        std::string g_lastDecision[kDecisionCount];

        void Decide(DecisionSlot slot, const char* format, ...)
        {
            char text[256];
            va_list args;
            va_start(args, format);
            _vsnprintf_s(text, sizeof(text), _TRUNCATE, format, args);
            va_end(args);
            if (g_lastDecision[slot] == text)
                return;
            g_lastDecision[slot] = text;
            LogShimA(LogLevel::Info, kComponent, "%s", text);
        }

        // Once per material per mission.
        void Unpaintable(const std::string& material, const char* why)
        {
            if (g_unpaintable.insert(material).second)
                LogShimA(LogLevel::Info, kComponent, "[PAINT] %s: %s; stock paint", material.c_str(), why);
        }

        // ---- Settings ----------------------------------------------------------
        const Policy::Variant* ReadVariant()
        {
            std::string value;
            if (!TryGetUserConfigString(Hooks::kUserConfigSinglePlayerSection, "PlayerPaint", value))
                return nullptr;
            return Policy::FindVariant(value);
        }

        bool GatePasses()
        {
            return RenderProfiles::Exports::GetActiveBackend() ==
                       static_cast<uint32_t>(RenderProfiles::ActiveBackend::DX11) &&
                   RenderProfiles::Exports::GetEffectiveRenderProfile() == RenderProfiles::Abi::kProfileEnhanced &&
                   RenderProfiles::IdentifyActiveRenderSystem() == 1;
        }

        // ---- Ogre ------------------------------------------------------------
#define OS_STR "?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@"
        bool ResolveApi()
        {
            if (g_apiResolved)
                return g_apiAvailable;
            g_apiResolved = true;
            OgreApi& o = g_ogre;
            o.rootSingleton = ResolveOgreProc<FnSingleton>("?getSingletonPtr@Root@Ogre@@SAPAV12@XZ");
            o.addFrameListener = ResolveOgreProc<FnAddListener>("?addFrameListener@Root@Ogre@@QAEXPAVFrameListener@2@@Z");
            o.materialManager = ResolveOgreProc<FnSingleton>("?getSingletonPtr@MaterialManager@Ogre@@SAPAV12@XZ");
            o.getByName = ResolveOgreProc<FnGetByName>(
                "?getByName@MaterialManager@Ogre@@QAE?AV?$SharedPtr@VMaterial@Ogre@@@2@ABV" OS_STR "0@Z");
            o.removeResource = ResolveOgreProc<FnRemove>("?remove@ResourceManager@Ogre@@UAEXABV" OS_STR "@Z");
            o.cloneMaterial = ResolveOgreProc<FnClone>(
                "?clone@Material@Ogre@@QBE?AV?$SharedPtr@VMaterial@Ogre@@@2@ABV" OS_STR "_N0@Z");
            o.resourceName = ResolveOgreProc<FnStringRef>("?getName@Resource@Ogre@@UBEABV" OS_STR "XZ");
            o.activeScheme = ResolveOgreProc<FnStringRef>("?getActiveScheme@MaterialManager@Ogre@@UBEABV" OS_STR "XZ");
            o.techniqueCount = ResolveOgreProc<FnU16>("?getNumTechniques@Material@Ogre@@QBEGXZ");
            o.techniqueAt = ResolveOgreProc<FnPtrAt16>("?getTechnique@Material@Ogre@@QAEPAVTechnique@2@G@Z");
            o.schemeName = ResolveOgreProc<FnStringRef>("?getSchemeName@Technique@Ogre@@QBEABV" OS_STR "XZ");
            o.passCount = ResolveOgreProc<FnU16>("?getNumPasses@Technique@Ogre@@QBEGXZ");
            o.passAt = ResolveOgreProc<FnPtrAt16>("?getPass@Technique@Ogre@@QAEPAVPass@2@G@Z");
            o.unitCount = ResolveOgreProc<FnU16>("?getNumTextureUnitStates@Pass@Ogre@@QBEGXZ");
            o.unitAt = ResolveOgreProc<FnPtrAt16>("?getTextureUnitState@Pass@Ogre@@QAEPAVTextureUnitState@2@G@Z");
            o.unitName = ResolveOgreProc<FnStringRef>("?getName@TextureUnitState@Ogre@@QBEABV" OS_STR "XZ");
            o.unitTextureName = ResolveOgreProc<FnStringRef>("?getTextureName@TextureUnitState@Ogre@@QBEABV" OS_STR "XZ");
            o.setUnitTexture = ResolveOgreProc<FnSetTexture>(
                "?setTextureName@TextureUnitState@Ogre@@QAEXABV" OS_STR "W4TextureType@2@@Z");
            o.hasFragmentProgram = ResolveOgreProc<FnBool>("?hasFragmentProgram@Pass@Ogre@@QBE_NXZ");
            o.fragmentParameters = ResolveOgreProc<FnSharedByValue>(
                "?getFragmentProgramParameters@Pass@Ogre@@QBE?AV?$SharedPtr@VGpuProgramParameters@Ogre@@@2@XZ");
            o.findConstant = ResolveOgreProc<FnFindConstant>(
                "?_findNamedConstantDefinition@GpuProgramParameters@Ogre@@QBEPBUGpuConstantDefinition@2@ABV" OS_STR "_N@Z");
            o.setVector4 = ResolveOgreProc<FnSetVector4>(
                "?setNamedConstant@GpuProgramParameters@Ogre@@QAEXABV" OS_STR "ABVVector4@2@@Z");
            o.subEntityCount = ResolveOgreProc<FnU32>("?getNumSubEntities@Entity@Ogre@@QBEIXZ");
            o.subEntityAt = ResolveOgreProc<FnPtrAt32>("?getSubEntity@Entity@Ogre@@QBEPAVSubEntity@2@I@Z");
            o.subEntityMaterial = ResolveOgreProc<FnSharedRef>(
                "?getMaterial@SubEntity@Ogre@@UBEABV?$SharedPtr@VMaterial@Ogre@@@2@XZ");
            o.setSubEntityMaterial = ResolveOgreProc<FnSetMaterial>(
                "?setMaterial@SubEntity@Ogre@@QAEXABV?$SharedPtr@VMaterial@Ogre@@@2@@Z");
            g_apiAvailable = o.rootSingleton && o.addFrameListener && o.materialManager && o.getByName &&
                             o.removeResource && o.cloneMaterial && o.resourceName && o.techniqueCount &&
                             o.techniqueAt && o.schemeName && o.passCount && o.passAt && o.unitCount &&
                             o.unitAt && o.unitName && o.unitTextureName && o.setUnitTexture &&
                             o.hasFragmentProgram && o.fragmentParameters && o.findConstant && o.setVector4 &&
                             o.subEntityCount && o.subEntityAt && o.subEntityMaterial &&
                             o.setSubEntityMaterial && OgreEntityLiveness::Available();
            return g_apiAvailable;
        }
#undef OS_STR

        // Drops our reference without ever freeing: the use count is only
        // decremented while another owner holds one (as gpu_skinning.cpp).
        void Release(SharedPtr& pointer)
        {
            if (pointer.rep && pointer.info)
            {
                auto* count = reinterpret_cast<volatile LONG*>(
                    static_cast<uint8_t*>(pointer.info) + kSharedPtrUseCountOffset);
                if (InterlockedCompareExchange(count, 0, 0) > 1)
                    InterlockedDecrement(count);
            }
            pointer = {};
        }

        // A by-value SharedPtr from an Ogre call, released on scope exit.
        struct Held
        {
            SharedPtr ptr;
            Held() = default;
            Held(const Held&) = delete;
            Held& operator=(const Held&) = delete;
            ~Held() { Release(ptr); }
        };

        const std::string kAutodetect = "Autodetect";
        const std::string kTeamPaint = "teamPaint";

        void LookupMaterial(const std::string& name, Held& out)
        {
            void* const manager = g_ogre.materialManager();
            if (manager)
                g_ogre.getByName(manager, &out.ptr, name, kAutodetect);
        }

        const std::string& NameOf(void* resource)
        {
            return *g_ogre.resourceName(resource);
        }

        // CR's mask for a stock material: the texture its <material>_tm twin
        // binds on an en-high teamMap unit. "" when CR is not loaded.
        const std::string& CrMask(const std::string& key)
        {
            auto found = g_crMasks.find(key);
            if (found != g_crMasks.end())
                return found->second;
            std::string mask;
            Held twin;
            LookupMaterial(key + "_tm", twin);
            if (twin.ptr.rep)
            {
                const uint16_t techniques = g_ogre.techniqueCount(twin.ptr.rep);
                for (uint16_t t = 0; t < techniques && t < kMaxTechniques && mask.empty(); ++t)
                {
                    void* const technique = g_ogre.techniqueAt(twin.ptr.rep, t);
                    if (!technique || !Policy::IsPaintScheme(*g_ogre.schemeName(technique)))
                        continue;
                    const uint16_t passes = g_ogre.passCount(technique);
                    for (uint16_t p = 0; p < passes && p < kMaxPasses && mask.empty(); ++p)
                    {
                        void* const pass = g_ogre.passAt(technique, p);
                        const uint16_t units = pass ? g_ogre.unitCount(pass) : 0;
                        for (uint16_t u = 0; u < units && u < kMaxUnits; ++u)
                        {
                            void* const unit = g_ogre.unitAt(pass, u);
                            if (unit && *g_ogre.unitName(unit) == "teamMap")
                            {
                                mask = *g_ogre.unitTextureName(unit);
                                break;
                            }
                        }
                    }
                }
            }
            return g_crMasks.emplace(key, mask).first->second;
        }

        // Binds the mask and sets teamPaint on every en-high pass of `material`
        // that has a teamMap unit and declares teamPaint. Returns the number
        // of passes painted; `why` names the reason when none was.
        int PaintMaterial(void* material, const std::string& key, const std::string& mask,
                          const Policy::Variant& variant, const char*& why)
        {
            int painted = 0;
            bool sawScheme = false;
            bool sawTeamUnit = false;
            bool crPassWithoutMask = false;
            const uint16_t techniques = g_ogre.techniqueCount(material);
            for (uint16_t t = 0; t < techniques && t < kMaxTechniques; ++t)
            {
                void* const technique = g_ogre.techniqueAt(material, t);
                if (!technique || !Policy::IsPaintScheme(*g_ogre.schemeName(technique)))
                    continue;
                sawScheme = true;
                const uint16_t passes = g_ogre.passCount(technique);
                for (uint16_t p = 0; p < passes && p < kMaxPasses; ++p)
                {
                    void* const pass = g_ogre.passAt(technique, p);
                    if (!pass)
                        continue;
                    void* teamUnit = nullptr;
                    bool actMap = false;
                    const uint16_t units = g_ogre.unitCount(pass);
                    for (uint16_t u = 0; u < units && u < kMaxUnits; ++u)
                    {
                        void* const unit = g_ogre.unitAt(pass, u);
                        if (!unit)
                            continue;
                        const std::string& name = *g_ogre.unitName(unit);
                        if (name == "teamMap")
                            teamUnit = unit;
                        else if (name == "actMap")
                            actMap = true;
                    }
                    if (!teamUnit || !g_ogre.hasFragmentProgram(pass))
                        continue;
                    sawTeamUnit = true;
                    Held parameters;
                    g_ogre.fragmentParameters(pass, &parameters.ptr);
                    if (!parameters.ptr.rep || !g_ogre.findConstant(parameters.ptr.rep, kTeamPaint, false))
                        continue;
                    // A CR program (it binds actMap) reads the weight from
                    // alpha: only CR's own mask fits it.
                    const std::string& texture = actMap ? CrMask(key) : mask;
                    if (texture.empty())
                    {
                        crPassWithoutMask = true;
                        continue;
                    }
                    g_ogre.setUnitTexture(teamUnit, texture, kTexType2D);
                    g_ogre.setVector4(parameters.ptr.rep, kTeamPaint, variant.rgba);
                    ++painted;
                }
            }
            if (!painted)
            {
                why = !sawScheme ? "no en-high technique"
                    : crPassWithoutMask ? "Campaign Reimagined program but no CR team mask (<material>_tm)"
                    : sawTeamUnit ? "en-high pass does not declare teamPaint"
                    : "no en-high pass with a teamMap unit";
            }
            return painted;
        }

        bool StartsWith(const std::string& text, const char* prefix)
        {
            return text.compare(0, std::strlen(prefix), prefix) == 0;
        }

        // The clone for `current` + the active variant: reused, adopted from a
        // leftover of the same name, or made now. Null when it cannot paint.
        const SharedPtr* EnsureClone(void* currentMaterial, const std::string& current,
                                     const std::string& key, const char* mask)
        {
            const std::string name = Policy::CloneName(current, *g_variant);
            auto found = g_clones.find(name);
            if (found != g_clones.end())
                return &found->second;
            SharedPtr made;
            {
                Held leftover;
                LookupMaterial(name, leftover);
                if (leftover.ptr.rep)
                    std::swap(made, leftover.ptr);
            }
            if (!made.rep)
            {
                g_stage = "clone";
                g_ogre.cloneMaterial(currentMaterial, &made, name, false, std::string());
                if (!made.rep)
                {
                    Unpaintable(current, "material clone failed");
                    return nullptr;
                }
                g_stage = "paint-material";
                const char* why = "";
                if (!PaintMaterial(made.rep, key, mask, *g_variant, why))
                {
                    Release(made);
                    g_ogre.removeResource(g_ogre.materialManager(), name);
                    Unpaintable(current, why);
                    return nullptr;
                }
            }
            return &g_clones.emplace(name, made).first->second;
        }

        void PaintEntity(void* entity)
        {
            if (g_painted.entity != entity)
                g_painted = Painted{entity, {}};
            const uint32_t count = g_ogre.subEntityCount(entity);
            for (uint32_t i = 0; i < count && i < kMaxSubEntities; ++i)
            {
                g_stage = "sub-entity";
                void* const sub = g_ogre.subEntityAt(entity, i);
                const SharedPtr* const material = sub ? g_ogre.subEntityMaterial(sub) : nullptr;
                if (!material || !material->rep)
                    continue;
                const std::string current = NameOf(material->rep);
                if (Policy::PaintedWith(current, *g_variant) || g_unpaintable.count(current))
                    continue;
                const std::string key(Policy::SourceKey(current));
                const char* const mask = Policy::FindMask(key);
                if (!mask)
                {
                    Unpaintable(current, "no paint mask for this material");
                    continue;
                }
                const SharedPtr* const clone = EnsureClone(material->rep, current, key, mask);
                if (!clone)
                    continue;
                const std::string cloneName = Policy::CloneName(current, *g_variant);
                g_stage = "assign";
                if (StartsWith(current, kGpuSkinCloneRoot))
                {
                    // GPU skinning rejects a SubEntity on a clone it did not
                    // make unless the change is queued for adoption.
                    Held keep;
                    LookupMaterial(current, keep);
                    g_ogre.setSubEntityMaterial(sub, *clone);
                    if (!OpenShimAdoptSurfaceVariant(entity, i, current.c_str(), cloneName.c_str()))
                    {
                        if (keep.ptr.rep)
                            g_ogre.setSubEntityMaterial(sub, keep.ptr);
                        Unpaintable(current, "GPU skinning did not accept the painted clone");
                        continue;
                    }
                }
                else
                {
                    g_ogre.setSubEntityMaterial(sub, *clone);
                }
                // An unpainted material on a known slot means something (GPU
                // skinning dropping a queued variant, a new skin generation)
                // replaced ours: it is now the material to restore. Log the
                // first repaint per slot only, so a repeated revert cannot
                // spam the log every frame.
                Slot* known = nullptr;
                for (Slot& slot : g_painted.slots)
                {
                    if (slot.index == i)
                        known = &slot;
                }
                if (!known)
                {
                    g_painted.slots.push_back(Slot{i, current, cloneName});
                    LogShimA(LogLevel::Info, kComponent, "[PAINT] %s -> %s", current.c_str(), cloneName.c_str());
                }
                else
                {
                    known->original = current;
                    known->clone = cloneName;
                    if (known->repaints++ == 0)
                        LogShimA(LogLevel::Info, kComponent, "[PAINT] %s -> %s (repainted after a revert; further repaints not logged)",
                            current.c_str(), cloneName.c_str());
                }
            }
            if (g_ogre.activeScheme)
            {
                const std::string& scheme = *g_ogre.activeScheme(g_ogre.materialManager());
                if (Policy::IsPaintScheme(scheme))
                    Decide(kDecisionScheme, "[PAINT] active scheme %s: paint visible", scheme.c_str());
                else
                    Decide(kDecisionScheme, "[PAINT] active scheme %s is not en-high: ship keeps stock look",
                        scheme.empty() ? "(none)" : scheme.c_str());
            }
        }

        bool EntityLive(void* entity)
        {
            void* const sceneManager = Hooks::GetOgreSceneManagerRuntime();
            return entity && sceneManager && OgreEntityLiveness::IsOgreEntityObject(entity) &&
                   OgreEntityLiveness::EntityProvenLive(sceneManager, entity);
        }

        // Puts the pre-paint materials back on the last painted ship, if it
        // is still in the scene.
        void RestorePainted()
        {
            Painted painted = std::move(g_painted);
            g_painted = Painted{};
            if (!painted.entity || painted.slots.empty() || !EntityLive(painted.entity))
                return;
            g_stage = "restore";
            const uint32_t count = g_ogre.subEntityCount(painted.entity);
            for (const Slot& slot : painted.slots)
            {
                if (slot.index >= count)
                    continue;
                void* const sub = g_ogre.subEntityAt(painted.entity, slot.index);
                const SharedPtr* const material = sub ? g_ogre.subEntityMaterial(sub) : nullptr;
                if (!material || !material->rep)
                    continue;
                const std::string current = NameOf(material->rep);
                if (!Policy::IsPaintClone(current))
                    continue;
                std::string target(Policy::StripPaintSuffix(slot.original));
                Held original;
                LookupMaterial(target, original);
                if (!original.ptr.rep)
                {
                    // GPU skinning may have dropped its clone: the stock material.
                    target = std::string(Policy::SourceKey(slot.original));
                    LookupMaterial(target, original);
                }
                if (!original.ptr.rep)
                {
                    LogShimA(LogLevel::Warn, kComponent, "[PAINT] restore: %s not found; %s stays",
                        target.c_str(), current.c_str());
                    continue;
                }
                g_ogre.setSubEntityMaterial(sub, original.ptr);
                if (StartsWith(current, kGpuSkinCloneRoot) && StartsWith(target, kGpuSkinCloneRoot))
                    OpenShimAdoptSurfaceVariant(painted.entity, slot.index, current.c_str(), target.c_str());
            }
            LogShimA(LogLevel::Info, kComponent, "[PAINT] restored %u material(s) on the previous ship",
                static_cast<unsigned>(painted.slots.size()));
        }

        void ReleaseClones()
        {
            g_stage = "release";
            void* const manager = g_ogre.materialManager ? g_ogre.materialManager() : nullptr;
            const size_t count = g_clones.size();
            for (auto& entry : g_clones)
            {
                Release(entry.second);
                if (manager)
                    g_ogre.removeResource(manager, entry.first);
            }
            g_clones.clear();
            g_crMasks.clear();
            g_unpaintable.clear();
            g_rootProbes.Clear();
            if (count)
                LogShimA(LogLevel::Info, kComponent, "[PAINT] removed %u clone material(s)", static_cast<unsigned>(count));
        }

        void RestoreAndRelease()
        {
            RestorePainted();
            ReleaseClones();
        }

        // World already destroyed: nothing to put back, only our references.
        void ForgetAndRelease()
        {
            g_painted = Painted{};
            ReleaseClones();
        }

        void* ResolvePlayerEntity()
        {
            if (!g_BzrFn_GetPlayerHandle)
                return nullptr;
            const int handle = g_BzrFn_GetPlayerHandle();
            void* const object = handle ? GameObjectFromHandleGog(handle) : nullptr;
            void* obj76 = nullptr;
            if (!object || !Hooks::TryGetGameObjectObj76(object, obj76) || !obj76)
                return nullptr;
            void* const sceneManager = Hooks::GetOgreSceneManagerRuntime();
            if (!sceneManager)
                return nullptr;
            const bool provePass = (g_frame % kProveIntervalFrames) == 0;
            void* directRoot = nullptr;
            void* ownerRoot = nullptr;
            OgreEntityLiveness::ReadBridgeRoots(static_cast<const uint8_t*>(obj76), directRoot, ownerRoot);
            void* const candidates[] = {
                g_rootProbes.Resolve(directRoot, g_frame, provePass),
                g_rootProbes.Resolve(ownerRoot, g_frame, provePass),
            };
            for (void* entity : candidates)
            {
                if (!entity || !OgreEntityLiveness::IsOgreEntityObject(entity))
                    continue;
                if ((entity == g_painted.entity && !provePass) ||
                    OgreEntityLiveness::EntityProvenLive(sceneManager, entity))
                    return entity;
            }
            return nullptr;
        }

        void RenderFrame()
        {
            ++g_frame;
            if ((g_frame % kPruneIntervalFrames) == 0)
                g_rootProbes.PruneUnseen(g_frame - 1);
            if (!g_variant)
                return;
            g_stage = "player";
            void* const entity = ResolvePlayerEntity();
            if (g_painted.entity && g_painted.entity != entity)
                RestorePainted();
            if (entity)
                PaintEntity(entity);
            g_stage = "idle";
        }

        // ---- Guards ------------------------------------------------------------
        bool RunCxx(void (*work)())
        {
            try
            {
                work();
                return true;
            }
            catch (...)
            {
                strcpy_s(g_faultDetail, "C++ exception");
                return false;
            }
        }

        int RecordSehFault(EXCEPTION_POINTERS* info)
        {
            const EXCEPTION_RECORD* const record = info ? info->ExceptionRecord : nullptr;
            _snprintf_s(g_faultDetail, sizeof(g_faultDetail), _TRUNCATE, "SEH 0x%08lX at 0x%08X",
                record ? record->ExceptionCode : 0ul,
                static_cast<unsigned>(reinterpret_cast<uintptr_t>(record ? record->ExceptionAddress : nullptr)));
            return EXCEPTION_EXECUTE_HANDLER;
        }

        // No destructible locals: SEH and C++ unwinding do not mix in one frame.
        bool RunSeh(void (*work)())
        {
            bool ok = false;
            g_faultDetail[0] = '\0';
            __try
            {
                ok = RunCxx(work);
            }
            __except (RecordSehFault(GetExceptionInformation()))
            {
                ok = false;
                if (GetExceptionCode() == EXCEPTION_STACK_OVERFLOW)
                    _resetstkoflw();
            }
            return ok;
        }

        void Disable(const char* why)
        {
            g_failed.store(true, std::memory_order_release);
            g_active.store(false, std::memory_order_release);
            LogShimA(LogLevel::Error, kComponent, "[PAINT] disabled for this session: %s", why);
            // Once only: a fault inside the cleanup itself is just logged.
            static bool s_cleaning = false;
            if (s_cleaning)
                return;
            s_cleaning = true;
            if (!RunSeh(RestoreAndRelease))
                LogShimA(LogLevel::Error, kComponent, "[PAINT] fault restoring on disable: %s", g_faultDetail);
        }

        void RunGuarded(void (*work)(), const char* what)
        {
            if (RunSeh(work))
                return;
            LogShimA(LogLevel::Error, kComponent, "[PAINT] %s fault: stage=%s %s", what, g_stage,
                g_faultDetail[0] ? g_faultDetail : "(no detail)");
            Disable(what);
        }

        void RenderFrameGuarded()
        {
            RunGuarded(RenderFrame, "frame update");
        }

        // Ogre::FrameListener, laid out to its vtable: frameStarted,
        // frameRenderingQueued, frameEnded, virtual destructor.
        class FrameListener
        {
        public:
            virtual bool frameStarted(const void*)
            {
                if (g_active.load(std::memory_order_acquire) && !g_failed.load(std::memory_order_acquire))
                    RenderFrameGuarded();
                return true;
            }
            virtual bool frameRenderingQueued(const void*) { return true; }
            virtual bool frameEnded(const void*) { return true; }
            virtual ~FrameListener() = default;
        };
        FrameListener g_listener;

        const char* VariantKey()
        {
            return g_variant ? g_variant->key : "stock";
        }
    }

    namespace SpPlayerPaint
    {
        void RequestReload()
        {
            g_reloadRequested.store(true, std::memory_order_release);
        }
    }

    void SpPlayerPaintSetSceneTeardownSeam(bool installed)
    {
        g_teardownSeam = installed;
    }

    void SpPlayerPaintNotifySceneEntitiesDestroyed()
    {
        g_awaitTeardown = false;
        g_missionEvaluated = false;
        if (!g_active.exchange(false))
            return;
        RunGuarded(ForgetAndRelease, "scene teardown release");
    }

    void SpPlayerPaintNotifyMissionRunStateChanged(bool running)
    {
        if (!running)
        {
            g_missionEvaluated = false;
            if (!g_active.exchange(false))
                return;
            g_awaitTeardown = g_teardownSeam;
            g_awaitStartedFrames = 0;
            // The debrief still renders this world: put the stock paint back.
            RunGuarded(RestoreAndRelease, "mission-end restore");
            return;
        }

        g_missionEvaluated = true;
        g_variant = ReadVariant();
        if (g_failed.load(std::memory_order_acquire))
            return;
        if (Hooks::ReadLocalPlayerNetIdValue() != 0)
        {
            Decide(kDecisionMission, "[PAINT] network game: player paint off (co-op keeps its own team paint)");
            return;
        }
        if (!GatePasses())
        {
            Decide(kDecisionMission, "[PAINT] render profile is not DX11 Enhanced: player paint off");
            return;
        }
        if (!ResolveApi())
        {
            Decide(kDecisionMission, "[PAINT] Ogre exports missing: player paint off");
            return;
        }
        g_active.store(true, std::memory_order_release);
        Decide(kDecisionMission, "[PAINT] single player: paint %s", VariantKey());
    }

    namespace
    {
        // Render thread. A changed paint first puts the old one back; the
        // next frame paints the new one (or nothing for stock).
        void ApplyReload()
        {
            const Policy::Variant* const next = ReadVariant();
            if (next == g_variant)
                return;
            g_variant = next;
            if (g_active.load(std::memory_order_acquire))
            {
                RunGuarded(RestorePainted, "setting-change restore");
                Decide(kDecisionMission, "[PAINT] single player: paint %s", VariantKey());
            }
        }
    }

    void SpPlayerPaintRenderFrameTick()
    {
        if (g_reloadRequested.exchange(false, std::memory_order_acq_rel))
            ApplyReload();
        // Started at the first world render of a mission, as GPU skinning.
        if (g_awaitTeardown)
        {
            int state = Hooks::kBzrRunStateUnknown;
            if (Hooks::TryReadBzrRunState(state) && state == Hooks::kBzrRunStateStarted &&
                ++g_awaitStartedFrames >= kAwaitTeardownFrameLimit)
                g_awaitTeardown = false;
        }
        if (!g_missionEvaluated && !g_awaitTeardown)
            SpPlayerPaintNotifyMissionRunStateChanged(true);
        if (!g_active.load(std::memory_order_acquire) || g_failed.load(std::memory_order_acquire))
            return;
        void* const root = g_ogre.rootSingleton ? g_ogre.rootSingleton() : nullptr;
        if (!root)
        {
            Disable("Ogre Root unavailable");
            return;
        }
        if (root != g_listenerRoot)
        {
            g_listenerRoot = root;
            g_ogre.addFrameListener(root, &g_listener);
            LogShimA(LogLevel::Info, kComponent, "[PAINT] frame listener installed");
        }
    }
}
