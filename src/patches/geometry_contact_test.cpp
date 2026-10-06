#include "geometry_contact_test.h"
#include "bzr_hooks_internal.h"
#include "hook_engine.h"
#include "shim_log.h"
#include <algorithm>
#include <cmath>
#include <cstring>

namespace BZROpenShim::GeometryContactTest
{
    namespace
    {
        // Layout qualified against exact GOG 2.2.301, see Docs/GEOMETRY_CONTACT_TEST.md.
        // Native calls are cdecl; CarHierarchyCheck has five caller-cleaned args.
        using ContactFn = int(__cdecl*)(void*, void*, float, void*, void*);
        using CreateFn = void*(__cdecl*)(void*, const float*);
        using DeleteFn = void(__cdecl*)(void*);
        using SelectFn = bool(__cdecl*)(void*, int);
        using PropertiesFn = void*(__cdecl*)(void*, void*);
        constexpr unsigned kMaxNodes = 256;
        struct Node
        {
            void* object;
            void* geometry;
            void* cache;
            DWORD flags;
            void* previousCache;
            float previousBounds[10];
            float bounds[10]; // sphere xyz/r, box min xyz/max xyz
        };
        struct State
        {
            DWORD handle, parts, faces, checks, hits, fallbacks;
            void* owner;
            void* root;
            bool enabled;
            unsigned count;
            Node nodes[kMaxNodes];
        };
        State g_state{};
        InlineDetour32 g_detour;
        ContactFn g_original = nullptr;
        ContactFn g_hierarchy = nullptr;
        CreateFn g_create = nullptr;
        DeleteFn g_delete = nullptr;
        SelectFn g_select = nullptr;
        PropertiesFn g_properties = nullptr;

        template<class T> T& Field(void* object, unsigned offset)
        {
            return *reinterpret_cast<T*>(static_cast<unsigned char*>(object) + offset);
        }

        bool Resolve()
        {
            if (g_IsSteamExe || !g_GameObjectGetHandleAddr) return false;
            if (g_hierarchy && g_create && g_delete && g_select && g_properties) return true;
            g_hierarchy = reinterpret_cast<ContactFn>(HookEngine::ResolveNamedAddress("CollisionTest::CarHierarchyCheck"));
            g_create = reinterpret_cast<CreateFn>(HookEngine::ResolveNamedAddress("CollisionTest::CgeomCreate"));
            g_delete = reinterpret_cast<DeleteFn>(HookEngine::ResolveNamedAddress("CollisionTest::CgeomDelete"));
            g_select = reinterpret_cast<SelectFn>(HookEngine::ResolveNamedAddress("CollisionTest::SelectLOD"));
            g_properties = reinterpret_cast<PropertiesFn>(HookEngine::ResolveNamedAddress("CollisionTest::GetProperties"));
            return g_hierarchy && g_create && g_delete && g_select && g_properties &&
                HookEngine::ResolveNamedAddress("CollisionTest::CarEntityCheck") != 0;
        }

        // Cgeom_Delete only reads/frees/nulls +9C, using the engine's own CRT.
        // Our caches are never attached outside the synchronous contact call;
        // freeing them does not require dereferencing a dead craft or part.
        void FreeCaches()
        {
            unsigned char proxy[0xa0]{};
            for (unsigned i = 0; i < g_state.count; ++i)
            {
                if (!g_state.nodes[i].cache) continue;
                Field<void*>(proxy, 0x9c) = g_state.nodes[i].cache;
                g_delete(proxy);
            }
            g_state = {};
        }

        bool Collect(void* object, void** nodes, unsigned& count)
        {
            for (; object; object = Field<void*>(object, 0x7c))
            {
                if (count == kMaxNodes) return false;
                // Bound cycles as well as oversized trees.
                for (unsigned i = 0; i < count; ++i) if (nodes[i] == object) return false;
                nodes[count++] = object;
                if (!Collect(Field<void*>(object, 0x80), nodes, count)) return false;
            }
            return true;
        }

        bool LiveOwner()
        {
            void* owner = GameObjectFromHandleGog(static_cast<int>(g_state.handle));
            void* root = nullptr;
            return owner && owner == g_state.owner &&
                Hooks::TryGetGameObjectObj76(owner, root) && root == g_state.root;
        }

        bool Physical(void* object)
        {
            const int kind = Field<int>(object, 0x84);
            const char* name = static_cast<const char*>(object) + 8;
            // Both '1' digits select the exterior LOD0 group. Helpers, POV,
            // cockpit group, smoke and light/gun hardpoints are not surfaces.
            return name[3] == '1' && name[4] == '1' &&
                (kind == 60 || kind == 65 || kind == 66 || kind == 67 || kind == 68) &&
                !(Field<DWORD>(object, 0x14) & 1);
        }

        bool Build(DWORD handle)
        {
            void* owner = GameObjectFromHandleGog(static_cast<int>(handle));
            void* root = nullptr;
            if (!owner || !Hooks::TryGetGameObjectObj76(owner, root) || Field<int>(root, 0x84) != 1)
                return false;
            void* nodes[kMaxNodes]{};
            unsigned count = 0;
            if (!Collect(root, nodes, count)) return false;
            g_state.handle = handle;
            g_state.owner = owner;
            g_state.root = root;
            g_state.count = count;
            const float identity[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
            for (unsigned i = 0; i < count; ++i)
            {
                Node& node = g_state.nodes[i];
                node.object = nodes[i];
                if (!Physical(node.object)) continue;
                if (!g_select(node.object, 0)) return false;
                node.geometry = Field<void*>(node.object, 0x64);
                if (!node.geometry) return false;
                const unsigned vertices = Field<unsigned>(node.geometry, 4);
                if (vertices <= 8 || vertices > 8192) return false;
                const float* positions = Field<const float*>(node.geometry, 0x0c);
                if (!positions) return false;
                float lo[3] = {positions[0], positions[1], positions[2]};
                float hi[3] = {lo[0], lo[1], lo[2]};
                for (unsigned v = 0; v < vertices; ++v)
                    for (unsigned a = 0; a < 3; ++a)
                    {
                        const float x = positions[v * 3 + a];
                        if (!std::isfinite(x)) return false;
                        lo[a] = (std::min)(lo[a], x);
                        hi[a] = (std::max)(hi[a], x);
                    }
                for (unsigned a = 0; a < 3; ++a)
                {
                    node.bounds[a] = (lo[a] + hi[a]) * 0.5f;
                    node.bounds[4 + a] = lo[a];
                    node.bounds[7 + a] = hi[a];
                }
                float radius2 = 0;
                for (unsigned v = 0; v < vertices; ++v)
                {
                    float distance2 = 0;
                    for (unsigned a = 0; a < 3; ++a)
                    {
                        const float d = positions[v * 3 + a] - node.bounds[a];
                        distance2 += d * d;
                    }
                    radius2 = (std::max)(radius2, distance2);
                }
                node.bounds[3] = std::nextafter(std::sqrt(radius2), INFINITY);
                node.cache = g_create(node.object, identity);
                if (!node.cache || !Field<DWORD>(node.cache, 16)) return false;
                ++g_state.parts;
                g_state.faces += Field<DWORD>(node.cache, 16);
            }
            return g_state.parts > 0;
        }

        bool SafeBuild(DWORD handle)
        {
            __try { return Build(handle); }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }

        bool Matches(void* entity)
        {
            return Field<void*>(entity, 0) == g_state.root && Field<int>(entity, 0x24) == 1;
        }

        bool TreeUnchanged()
        {
            void* nodes[kMaxNodes]{};
            unsigned count = 0;
            if (!Collect(g_state.root, nodes, count) || count != g_state.count) return false;
            for (unsigned i = 0; i < count; ++i)
                if (nodes[i] != g_state.nodes[i].object ||
                    (g_state.nodes[i].cache && Field<void*>(nodes[i], 0x64) != g_state.nodes[i].geometry))
                    return false;
            return true;
        }

        // Save/restore exact flags, cache pointer and bounds even if the engine
        // contact routine faults. No pointers to EXU or its Lua state are kept.
        int GeometryCall(void* source, void* target, float dt, void* outSource, void* outTarget)
        {
            unsigned attached = 0;
            int result = 0;
            __try
            {
                for (unsigned i = 0; i < g_state.count; ++i)
                {
                    Node& n = g_state.nodes[i];
                    n.flags = Field<DWORD>(n.object, 0x14);
                    n.previousCache = Field<void*>(n.object, 0x9c);
                    std::memcpy(n.previousBounds, static_cast<unsigned char*>(n.object) + 0xa0, sizeof(n.previousBounds));
                    ++attached;
                    Field<DWORD>(n.object, 0x14) = (n.flags & ~0xf000u) | (n.cache ? 0x3000u : 0x1000u);
                    if (n.cache)
                    {
                        Field<void*>(n.object, 0x9c) = n.cache;
                        std::memcpy(static_cast<unsigned char*>(n.object) + 0xa0, n.bounds, sizeof(n.bounds));
                    }
                }
                result = g_hierarchy(source, target, dt, outSource, outTarget);
                if (result)
                {
                    // CLSN_INFO = collided, counterpart obj, 72-byte properties,
                    // time, point, relative velocity, normal (120 bytes total).
                    // BoxGeom fills properties from the leaf (default scenery
                    // values), but CheckPair subsequently replaces obj with the
                    // counterpart root. Match its root ownership here too: retain
                    // polygon time/point/normal, use each moving craft's actual
                    // mass, inertia and velocity. Output A describes target B.
                    if (Field<DWORD>(outSource, 0))
                        g_properties(static_cast<unsigned char*>(outSource) + 8, Field<void*>(target, 0));
                    if (Field<DWORD>(outTarget, 0))
                        g_properties(static_cast<unsigned char*>(outTarget) + 8, Field<void*>(source, 0));
                }
            }
            __finally
            {
                for (unsigned i = 0; i < attached; ++i)
                {
                    Node& n = g_state.nodes[i];
                    Field<DWORD>(n.object, 0x14) = n.flags;
                    Field<void*>(n.object, 0x9c) = n.previousCache;
                    std::memcpy(static_cast<unsigned char*>(n.object) + 0xa0, n.previousBounds, sizeof(n.previousBounds));
                }
            }
            return result;
        }

        int __cdecl ContactHook(void* a, void* b, float dt, void* outA, void* outB)
        {
            // The simulation thread also owns the Lua API calls. Resolve the
            // generation every time, before touching the remembered hierarchy.
            if (!g_state.handle || !LiveOwner()) return g_original(a, b, dt, outA, outB);
            bool selectedA = false, selectedB = false, eligible = false;
            __try
            {
                selectedA = Matches(a);
                selectedB = Matches(b);
                if (!selectedA && !selectedB) return g_original(a, b, dt, outA, outB);
                eligible = selectedA != selectedB && Field<int>(a, 0x24) == 1 && Field<int>(b, 0x24) == 1;
                if (eligible && g_state.enabled) eligible = TreeUnchanged();
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { eligible = false; }
            if (!eligible)
            {
                ++g_state.fallbacks;
                return g_original(a, b, dt, outA, outB);
            }
            ++g_state.checks;
            int result = 0;
            if (!g_state.enabled) result = g_original(a, b, dt, outA, outB);
            else
            {
                __try { result = selectedB ? GeometryCall(a, b, dt, outA, outB) : GeometryCall(b, a, dt, outB, outA); }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    g_state.enabled = false;
                    ++g_state.fallbacks;
                    LogShimA(LogLevel::Error, "geometrycontact", "native geometry call faulted; restored stock contact");
                    result = g_original(a, b, dt, outA, outB);
                }
            }
            if (result) ++g_state.hits;
            return result;
        }

        bool Install()
        {
            if (g_original) return true;
            if (!Resolve()) return false;
            const auto address = HookEngine::ResolveNamedAddress("CollisionTest::CarEntityCheck");
            // Three whole instructions; no relative operands in the trampoline.
            const unsigned char expected[] = {0x55,0x8b,0xec,0x83,0xec,0x08};
            if (!InstallInlineDetour32(g_detour, address, reinterpret_cast<void*>(ContactHook), sizeof(expected), expected, sizeof(expected))) return false;
            g_original = reinterpret_cast<ContactFn>(g_detour.trampoline);
            LogShimA(LogLevel::Info, "geometrycontact", "GOG vehicle contact test hook installed; inactive until explicitly selected");
            return true;
        }
    }

    DWORD Capabilities() { return Resolve() ? 1u : 0u; }

    BOOL Set(DWORD handle, BOOL enabled)
    {
        HookEngine::CodePatchLock lock;
        if (!handle || !Install()) return FALSE;
        if (handle != g_state.handle || !LiveOwner())
        {
            FreeCaches();
            if (!SafeBuild(handle)) { FreeCaches(); return FALSE; }
        }
        g_state.enabled = enabled != FALSE;
        g_state.checks = g_state.hits = g_state.fallbacks = 0;
        LogShimA(LogLevel::Info, "geometrycontact", "handle=%08X mode=%s parts=%lu faces=%lu", handle,
            g_state.enabled ? "legacy-GEO target" : "stock COLP", g_state.parts, g_state.faces);
        return TRUE;
    }

    BOOL Clear()
    {
        HookEngine::CodePatchLock lock;
        if (g_delete) FreeCaches();
        return TRUE;
    }

    BOOL Stats(DWORD handle, DWORD* enabled, DWORD* parts, DWORD* faces, DWORD* checks, DWORD* hits, DWORD* fallbacks)
    {
        if (handle != g_state.handle || !LiveOwner() || !enabled || !parts || !faces || !checks || !hits || !fallbacks) return FALSE;
        *enabled = g_state.enabled ? 1u : 0u;
        *parts = g_state.parts; *faces = g_state.faces;
        *checks = g_state.checks; *hits = g_state.hits; *fallbacks = g_state.fallbacks;
        return TRUE;
    }
}
