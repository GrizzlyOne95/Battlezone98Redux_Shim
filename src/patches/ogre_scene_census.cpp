// SPDX-License-Identifier: MIT
//
// LOCAL DIAGNOSTIC (scene leak hunt, 2026-11-10). Not for main.
//
// OPENSHIM_SCENE_CENSUS=1: once per second, from the render thread, walk the
// Ogre scene graph and the SceneManager's per-type MovableObject collections
// and log what exists. Also counts processVisibleObject visits per pass type.
// Every Ogre read is SEH-guarded; a fault skips that tick.
#include "ogre_scene_census.h"

#include <Windows.h>

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>

#include "ogre_runtime.h"
#include "shim_log.h"

#ifndef register
#define OPENSHIM_OGRE_RESTORE_REGISTER
#define register
#endif
#include "OgreEntity.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreMesh.h"
#include "OgreAnimationState.h"
#ifdef OPENSHIM_OGRE_RESTORE_REGISTER
#undef register
#undef OPENSHIM_OGRE_RESTORE_REGISTER
#endif

namespace BZROpenShim
{
    namespace Hooks
    {
        void* GetOgreSceneManagerRuntime();
        const char* TryGetRttiClassName(const void* object, char* buffer, size_t bufferSize);
    }
}

namespace
{
    using namespace BZROpenShim;

    struct AnimSetAccess : Ogre::AnimationStateSet
    {
        using Ogre::AnimationStateSet::mEnabledAnimationStates;
        using Ogre::AnimationStateSet::mAnimationStates;
    };

    using FnEntityGetMesh = const Ogre::MeshPtr&(__thiscall*)(void*);
    using FnEntityHasSkeleton = bool(__thiscall*)(void*);
    using FnEntityGetAllAnimationStates = void*(__thiscall*)(void*);
    using FnParticleSystemGetNumParticles = size_t(__thiscall*)(void*);

    FnEntityGetMesh g_GetMesh = nullptr;
    FnEntityHasSkeleton g_HasSkeleton = nullptr;
    FnEntityGetAllAnimationStates g_GetAnims = nullptr;
    FnParticleSystemGetNumParticles g_GetNumParticles = nullptr;
    int g_Enabled = -1;
    bool g_Resolved = false;
    DWORD g_LastTick = 0;
    uint32_t g_TickIndex = 0;

    // Per-pass visits (render thread only).
    uint64_t g_VisitsMain = 0, g_VisitsShadow = 0, g_Passes = 0;
    const void* g_LastCamera = nullptr;
    bool g_LastShadow = false;
    struct VisitType { const void* vptr; uint64_t main; uint64_t shadow; };
    VisitType g_VisitTypes[24] = {};
    uint64_t g_VisitTypeOverflow = 0;

    void* FindOne(const char* token)
    {
        const auto m = OgreRuntime::FindExportsContaining(token);
        return m.size() == 1 ? m[0].address : nullptr;
    }

    // ---- Census tables (POD only, filled under SEH) ----
    constexpr int kTypes = 12;
    const char* const kTypeNames[kTypes] = {
        "Entity", "Light", "ParticleSystem", "BillboardSet", "BillboardChain", "RibbonTrail",
        "ManualObject", "InstancedEntity", "StaticGeometry", "Camera", "MovablePlane", "Rectangle2D" };

    struct MeshRow
    {
        const void* mesh;
        char name[48];
        uint32_t total, attached, visible, skeleton, animEnabled, animStates;
    };
    constexpr int kMeshRows = 768;
    MeshRow g_Mesh[kMeshRows];
    int g_MeshUsed = 0;
    uint32_t g_MeshOverflow = 0;

    struct RttiRow { const void* vptr; uint32_t count; };
    RttiRow g_GraphTypes[32];
    int g_GraphTypesUsed = 0;

    struct Census
    {
        bool ok;
        uint32_t graphNodes, graphNodesEmpty, graphObjects, graphMaxDepth;
        uint32_t factoryTotal[kTypes];
        uint32_t entityInvisible, entityDetached, entitySkeleton, entityAnimEnabled, enabledStates;
        uint32_t particlesActive;
    };

    void CountGraphType(const void* obj)
    {
        const void* vptr = *reinterpret_cast<const void* const*>(obj);
        for (int i = 0; i < g_GraphTypesUsed; ++i)
            if (g_GraphTypes[i].vptr == vptr) { ++g_GraphTypes[i].count; return; }
        if (g_GraphTypesUsed < 32)
            g_GraphTypes[g_GraphTypesUsed++] = { vptr, 1 };
    }

    MeshRow* MeshRowFor(const void* mesh)
    {
        for (int i = 0; i < g_MeshUsed; ++i)
            if (g_Mesh[i].mesh == mesh) return &g_Mesh[i];
        if (g_MeshUsed >= kMeshRows) { ++g_MeshOverflow; return nullptr; }
        MeshRow* r = &g_Mesh[g_MeshUsed++];
        std::memset(r, 0, sizeof(*r));
        r->mesh = mesh;
        return r;
    }

    Ogre::SceneNode* g_Stack[16384];
    uint32_t g_Depth[16384];

    bool WalkGraph(Ogre::SceneManager* sm, Census& c)
    {
        __try
        {
            Ogre::SceneNode* root = sm->getRootSceneNode();
            if (!root) return false;
            int sp = 0;
            g_Stack[sp] = root; g_Depth[sp] = 0; ++sp;
            while (sp > 0)
            {
                --sp;
                Ogre::SceneNode* n = g_Stack[sp];
                const uint32_t d = g_Depth[sp];
                if (d > c.graphMaxDepth) c.graphMaxDepth = d;
                ++c.graphNodes;
                uint32_t objs = 0;
                Ogre::SceneNode::ObjectIterator oi = n->getAttachedObjectIterator();
                while (oi.hasMoreElements())
                {
                    Ogre::MovableObject* mo = oi.getNext();
                    if (!mo) continue;
                    ++objs;
                    CountGraphType(mo);
                }
                c.graphObjects += objs;
                if (objs == 0) ++c.graphNodesEmpty;
                Ogre::Node::ChildNodeIterator ci = n->getChildIterator();
                while (ci.hasMoreElements())
                {
                    Ogre::Node* child = ci.getNext();
                    if (child && sp < 16384)
                    {
                        g_Stack[sp] = static_cast<Ogre::SceneNode*>(child);
                        g_Depth[sp] = d + 1;
                        ++sp;
                    }
                }
            }
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    void RecordEntity(Ogre::Entity* e, Census& c)
    {
        const bool attached = e->isAttached();
        const bool visible = e->isVisible();
        const bool skel = g_HasSkeleton ? g_HasSkeleton(e) : false;
        uint32_t enabled = 0, states = 0;
        if (g_GetAnims)
        {
            auto* set = static_cast<Ogre::AnimationStateSet*>(g_GetAnims(e));
            if (set)
            {
                enabled = static_cast<uint32_t>((set->*(&AnimSetAccess::mEnabledAnimationStates)).size());
                states = static_cast<uint32_t>((set->*(&AnimSetAccess::mAnimationStates)).size());
                if (enabled > 4096) enabled = 0;
                if (states > 4096) states = 0;
            }
        }
        if (!attached) ++c.entityDetached;
        if (!visible) ++c.entityInvisible;
        if (skel) ++c.entitySkeleton;
        if (enabled) { ++c.entityAnimEnabled; c.enabledStates += enabled; }

        const Ogre::Mesh* mesh = nullptr;
        if (g_GetMesh)
        {
            const Ogre::MeshPtr& mp = g_GetMesh(e);
            mesh = mp.get();
        }
        MeshRow* r = MeshRowFor(mesh);
        if (!r) return;
        if (!r->name[0])
        {
            if (mesh)
            {
                const char* s = mesh->getName().c_str();
                size_t i = 0;
                for (; i + 1 < sizeof(r->name) && s[i]; ++i) r->name[i] = s[i];
                r->name[i] = 0;
            }
            else
                std::strcpy(r->name, "(no mesh)");
        }
        ++r->total;
        if (attached) ++r->attached;
        if (visible) ++r->visible;
        if (skel) ++r->skeleton;
        if (enabled) ++r->animEnabled;
        r->animStates += states;
    }

    bool WalkFactory(Ogre::SceneManager* sm, const std::string& type, int typeIndex, Census& c)
    {
        __try
        {
            Ogre::SceneManager::MovableObjectIterator it = sm->getMovableObjectIterator(type);
            uint32_t n = 0;
            while (it.hasMoreElements())
            {
                Ogre::MovableObject* mo = it.getNext();
                if (!mo) continue;
                ++n;
                if (typeIndex == 0)
                    RecordEntity(static_cast<Ogre::Entity*>(mo), c);
                else if (typeIndex == 2 && g_GetNumParticles)
                    c.particlesActive += static_cast<uint32_t>(g_GetNumParticles(mo));
            }
            c.factoryTotal[typeIndex] = n;
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    bool SceneManagerLooksLive(void* sm)
    {
        if (!sm) return false;
        void* vptr = nullptr;
        __try { vptr = *reinterpret_cast<void**>(sm); }
        __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        HMODULE owner = nullptr;
        if (!vptr || !GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                                         GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                         reinterpret_cast<LPCSTR>(vptr), &owner))
            return false;
        return owner && owner == GetModuleHandleA("OgreMain.dll");
    }

    void RunCensus()
    {
        void* raw = Hooks::GetOgreSceneManagerRuntime();
        if (!SceneManagerLooksLive(raw))
            return;
        auto* sm = static_cast<Ogre::SceneManager*>(raw);

        Census c = {};
        g_MeshUsed = 0;
        g_MeshOverflow = 0;
        g_GraphTypesUsed = 0;
        const bool graphOk = WalkGraph(sm, c);
        bool factoryOk = true;
        for (int t = 0; t < kTypes; ++t)
        {
            // StaticGeometry, Camera, MovablePlane, Rectangle2D are not factory
            // types in 1.10; asking would create an empty collection. Skip.
            if (t >= 8) break;
            const std::string name(kTypeNames[t]);
            factoryOk = WalkFactory(sm, name, t, c) && factoryOk;
        }

        char line[1400];
        int len = std::snprintf(line, sizeof(line),
            "[SCENECENSUS] tick=%u graphOk=%d factoryOk=%d graphNodes=%u emptyNodes=%u graphObjects=%u maxDepth=%u "
            "Entity=%u Light=%u ParticleSystem=%u BillboardSet=%u BillboardChain=%u RibbonTrail=%u ManualObject=%u InstancedEntity=%u "
            "entDetached=%u entInvisible=%u entSkeleton=%u entAnimEnabled=%u enabledStates=%u particles=%u "
            "visitsMain=%llu visitsShadow=%llu passes=%llu meshes=%d meshOverflow=%u",
            g_TickIndex, graphOk ? 1 : 0, factoryOk ? 1 : 0, c.graphNodes, c.graphNodesEmpty, c.graphObjects,
            c.graphMaxDepth, c.factoryTotal[0], c.factoryTotal[1], c.factoryTotal[2], c.factoryTotal[3],
            c.factoryTotal[4], c.factoryTotal[5], c.factoryTotal[6], c.factoryTotal[7], c.entityDetached,
            c.entityInvisible, c.entitySkeleton, c.entityAnimEnabled, c.enabledStates, c.particlesActive,
            static_cast<unsigned long long>(g_VisitsMain), static_cast<unsigned long long>(g_VisitsShadow),
            static_cast<unsigned long long>(g_Passes), g_MeshUsed, g_MeshOverflow);
        (void)len;
        LogShimA(LogLevel::Info, "scenecensus", "%s", line);

        // Attached-in-graph objects by RTTI type.
        {
            int pos = std::snprintf(line, sizeof(line), "[SCENECENSUS-GRAPH] tick=%u", g_TickIndex);
            char rtti[96];
            for (int i = 0; i < g_GraphTypesUsed && pos < static_cast<int>(sizeof(line)) - 120; ++i)
            {
                Hooks::TryGetRttiClassName(&g_GraphTypes[i].vptr, rtti, sizeof(rtti));
                pos += std::snprintf(line + pos, sizeof(line) - pos, " %s=%u", rtti, g_GraphTypes[i].count);
            }
            LogShimA(LogLevel::Info, "scenecensus", "%s", line);
        }

        // Visits by RTTI type since the previous tick.
        {
            int pos = std::snprintf(line, sizeof(line), "[SCENECENSUS-VISITS] tick=%u", g_TickIndex);
            char rtti[96];
            for (int i = 0; i < 24 && g_VisitTypes[i].vptr && pos < static_cast<int>(sizeof(line)) - 120; ++i)
            {
                Hooks::TryGetRttiClassName(&g_VisitTypes[i].vptr, rtti, sizeof(rtti));
                pos += std::snprintf(line + pos, sizeof(line) - pos, " %s=%llu/%llu", rtti,
                    static_cast<unsigned long long>(g_VisitTypes[i].main),
                    static_cast<unsigned long long>(g_VisitTypes[i].shadow));
                g_VisitTypes[i].main = g_VisitTypes[i].shadow = 0;
            }
            LogShimA(LogLevel::Info, "scenecensus", "%s overflow=%llu", line,
                static_cast<unsigned long long>(g_VisitTypeOverflow));
            g_VisitTypeOverflow = 0;
        }

        // Top 25 meshes by entity count, every 5th tick.
        if (g_TickIndex % 5 == 0)
        {
            bool used[kMeshRows] = {};
            int pos = std::snprintf(line, sizeof(line), "[SCENECENSUS-MESH] tick=%u", g_TickIndex);
            for (int k = 0; k < 25; ++k)
            {
                int best = -1;
                for (int i = 0; i < g_MeshUsed; ++i)
                    if (!used[i] && (best < 0 || g_Mesh[i].total > g_Mesh[best].total)) best = i;
                if (best < 0) break;
                used[best] = true;
                const MeshRow& r = g_Mesh[best];
                // name=total/attached/visible/skeleton/animEnabled/animStates
                pos += std::snprintf(line + pos, sizeof(line) - pos, " %s=%u/%u/%u/%u/%u/%u",
                    r.name, r.total, r.attached, r.visible, r.skeleton, r.animEnabled, r.animStates);
                if (pos >= static_cast<int>(sizeof(line)) - 100) break;
            }
            LogShimA(LogLevel::Info, "scenecensus", "%s", line);
        }
        g_VisitsMain = g_VisitsShadow = g_Passes = 0;
    }
}

namespace BZROpenShim
{
    namespace Hooks
    {
        bool SceneCensusEnabled()
        {
            if (g_Enabled < 0)
            {
                char value[8] = {};
                g_Enabled = (GetEnvironmentVariableA("OPENSHIM_SCENE_CENSUS", value, sizeof(value)) > 0 &&
                             value[0] == '1') ? 1 : 0;
                if (g_Enabled)
                    LogShimA(LogLevel::Info, "scenecensus", "[SCENECENSUS] enabled");
            }
            return g_Enabled == 1;
        }

        void SceneCensusOnVisit(const void* movableObject, const void* camera, bool onlyShadowCasters)
        {
            if (camera != g_LastCamera || onlyShadowCasters != g_LastShadow)
            {
                ++g_Passes;
                g_LastCamera = camera;
                g_LastShadow = onlyShadowCasters;
            }
            ++(onlyShadowCasters ? g_VisitsShadow : g_VisitsMain);
            const void* vptr = nullptr;
            __try { vptr = *reinterpret_cast<const void* const*>(movableObject); }
            __except (EXCEPTION_EXECUTE_HANDLER) { return; }
            for (int i = 0; i < 24; ++i)
            {
                if (!g_VisitTypes[i].vptr) g_VisitTypes[i].vptr = vptr;
                if (g_VisitTypes[i].vptr == vptr)
                {
                    ++(onlyShadowCasters ? g_VisitTypes[i].shadow : g_VisitTypes[i].main);
                    return;
                }
            }
            ++g_VisitTypeOverflow;
        }

        void SceneCensusTick()
        {
            const DWORD now = GetTickCount();
            if (g_LastTick && now - g_LastTick < 1000)
                return;
            g_LastTick = now;
            if (!g_Resolved && OgreRuntime::IsLoaded())
            {
                g_Resolved = true;
                g_GetMesh = reinterpret_cast<FnEntityGetMesh>(FindOne("?getMesh@Entity@Ogre@@"));
                g_HasSkeleton = reinterpret_cast<FnEntityHasSkeleton>(FindOne("?hasSkeleton@Entity@Ogre@@"));
                g_GetAnims = reinterpret_cast<FnEntityGetAllAnimationStates>(FindOne("?getAllAnimationStates@Entity@Ogre@@"));
                g_GetNumParticles = reinterpret_cast<FnParticleSystemGetNumParticles>(FindOne("?getNumParticles@ParticleSystem@Ogre@@"));
                LogShimA(LogLevel::Info, "scenecensus",
                    "[SCENECENSUS] resolved getMesh=%p hasSkeleton=%p getAllAnimationStates=%p getNumParticles=%p",
                    g_GetMesh, g_HasSkeleton, g_GetAnims, g_GetNumParticles);
            }
            ++g_TickIndex;
            RunCensus();
        }
    }
}
