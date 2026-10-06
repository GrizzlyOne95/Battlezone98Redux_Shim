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
        // The generated Scion hulls reach 11146 source vertices. Cgeom_Create
        // uses 14 bytes of temporary stack storage per vertex and ushort remap
        // indices; 16384 stays bounded and below the index format's limit.
        constexpr unsigned kMaxVertices = 16384;
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
        State g_state{}; // Explicit EXU selection overrides the global policy.
        constexpr unsigned kMaxVehicles = 128;
        constexpr DWORD kMaxCachedFaces = 500000;
        State g_vehicles[kMaxVehicles]{};
        unsigned long long g_used[kMaxVehicles]{};
        unsigned long long g_clock = 0;
        bool g_globalEnabled = false;
        DWORD g_cachedFaces = 0;
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
        void FreeCaches(State& state)
        {
            unsigned char proxy[0xa0]{};
            for (unsigned i = 0; i < state.count; ++i)
            {
                if (!state.nodes[i].cache) continue;
                Field<void*>(proxy, 0x9c) = state.nodes[i].cache;
                g_delete(proxy);
            }
            state = {};
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

        bool LiveOwner(const State& state)
        {
            void* owner = GameObjectFromHandleGog(static_cast<int>(state.handle));
            void* root = nullptr;
            return owner && owner == state.owner &&
                Hooks::TryGetGameObjectObj76(owner, root) && root == state.root;
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

        bool Build(State& state, DWORD handle)
        {
            void* owner = GameObjectFromHandleGog(static_cast<int>(handle));
            void* root = nullptr;
            if (!owner || !Hooks::TryGetGameObjectObj76(owner, root) || Field<int>(root, 0x84) != 1)
                return false;
            void* nodes[kMaxNodes]{};
            unsigned count = 0;
            if (!Collect(root, nodes, count)) return false;
            state.handle = handle;
            state.owner = owner;
            state.root = root;
            state.count = count;
            unsigned totalVertices = 0;
            const float identity[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
            for (unsigned i = 0; i < count; ++i)
            {
                Node& node = state.nodes[i];
                node.object = nodes[i];
                if (!Physical(node.object)) continue;
                if (!g_select(node.object, 0)) return false;
                node.geometry = Field<void*>(node.object, 0x64);
                if (!node.geometry) return false;
                const unsigned vertices = Field<unsigned>(node.geometry, 4);
                if (vertices <= 8 || vertices > kMaxVertices)
                {
                    LogShimA(LogLevel::Warn, "geometrycontact", "part=%.8s rejected: source vertices=%u limit=%u",
                        static_cast<char*>(node.object) + 8, vertices, kMaxVertices);
                    return false;
                }
                totalVertices += vertices;
                if (totalVertices > 65536) return false;
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
                ++state.parts;
                state.faces += Field<DWORD>(node.cache, 16);
                if (state.faces > 131072) return false;
            }
            return state.parts > 0;
        }

        bool SafeBuild(State& state, DWORD handle)
        {
            __try { return Build(state, handle); }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }

        bool Matches(const State& state, void* entity)
        {
            return Field<void*>(entity, 0) == state.root && Field<int>(entity, 0x24) == 1;
        }

        bool TreeUnchanged(const State& state)
        {
            void* nodes[kMaxNodes]{};
            unsigned count = 0;
            if (!Collect(state.root, nodes, count) || count != state.count) return false;
            for (unsigned i = 0; i < count; ++i)
                if (nodes[i] != state.nodes[i].object ||
                    (state.nodes[i].cache && Field<void*>(nodes[i], 0x64) != state.nodes[i].geometry))
                    return false;
            return true;
        }

        // Save/restore exact flags, cache pointer and bounds even if the engine
        // contact routine faults. No pointers to EXU or its Lua state are kept.
        int GeometryCall(State& state, void* source, void* target, float dt, void* outSource, void* outTarget)
        {
            unsigned attached = 0;
            int result = 0;
            __try
            {
                for (unsigned i = 0; i < state.count; ++i)
                {
                    Node& n = state.nodes[i];
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
                    Node& n = state.nodes[i];
                    Field<DWORD>(n.object, 0x14) = n.flags;
                    Field<void*>(n.object, 0x9c) = n.previousCache;
                    std::memcpy(static_cast<unsigned char*>(n.object) + 0xa0, n.previousBounds, sizeof(n.previousBounds));
                }
            }
            return result;
        }

        void Retire(unsigned index)
        {
            g_cachedFaces -= g_vehicles[index].faces;
            FreeCaches(g_vehicles[index]);
            g_used[index] = 0;
        }

        State* GlobalTarget(void* entity)
        {
            void* root = Field<void*>(entity, 0);
            if (!root || Field<int>(root, 0x84) != 1) return nullptr;
            void* owner = Field<void*>(root, 0x8c);
            int handle = 0;
            void* actualRoot = nullptr;
            if (!owner || !Hooks::TryGetGameObjectHandleValue(owner, handle) || !handle ||
                GameObjectFromHandleGog(handle) != owner ||
                !Hooks::TryGetGameObjectObj76(owner, actualRoot) || actualRoot != root) return nullptr;
            unsigned slot = kMaxVehicles;
            for (unsigned i = 0; i < kMaxVehicles; ++i)
            {
                State& state = g_vehicles[i];
                if (state.handle == static_cast<DWORD>(handle))
                {
                    if (state.owner == owner && state.root == root)
                    {
                        g_used[i] = ++g_clock;
                        return &state; // Includes rejected targets: no repeated native allocations.
                    }
                    Retire(i); // Handle/root reuse never inherits another craft's cache.
                }
                if (!g_vehicles[i].handle && slot == kMaxVehicles) slot = i;
            }
            if (slot == kMaxVehicles)
            {
                slot = static_cast<unsigned>(std::min_element(g_used, g_used + kMaxVehicles) - g_used);
                Retire(slot);
            }
            State& state = g_vehicles[slot];
            if (!SafeBuild(state, static_cast<DWORD>(handle)))
            {
                FreeCaches(state);
                state.handle = static_cast<DWORD>(handle);
                state.owner = owner; state.root = root;
                LogShimA(LogLevel::Warn, "geometrycontact", "global handle=%08X unsupported; stock contact retained", handle);
            }
            else
            {
                // Native caches have a bounded face budget as well as a bounded
                // entry count. Reclaim oldest other targets before publishing.
                while (g_cachedFaces + state.faces > kMaxCachedFaces)
                {
                    unsigned oldest = kMaxVehicles;
                    for (unsigned i = 0; i < kMaxVehicles; ++i)
                        if (i != slot && g_vehicles[i].faces &&
                            (oldest == kMaxVehicles || g_used[i] < g_used[oldest])) oldest = i;
                    if (oldest == kMaxVehicles) break;
                    Retire(oldest);
                }
                state.enabled = true;
                g_cachedFaces += state.faces;
                LogShimA(LogLevel::Info, "geometrycontact", "global handle=%08X parts=%lu faces=%lu", handle, state.parts, state.faces);
            }
            g_used[slot] = ++g_clock;
            return &state;
        }

        int __cdecl ContactHook(void* a, void* b, float dt, void* outA, void* outB)
        {
            // The simulation thread also owns the Lua API calls. Fail closed
            // online on every entry, including explicitly selected vehicles.
            if (!Hooks::IsSinglePlayerSession()) return g_original(a, b, dt, outA, outB);
            State* state = nullptr;
            bool selectedA = false, eligible = false;
            __try
            {
                if (g_state.handle && !LiveOwner(g_state)) FreeCaches(g_state);
                if (g_state.handle)
                {
                    selectedA = Matches(g_state, a);
                    if (selectedA || Matches(g_state, b)) state = &g_state;
                }
                eligible = Field<int>(a, 0x24) == 1 && Field<int>(b, 0x24) == 1 &&
                    Field<void*>(a, 0) != Field<void*>(b, 0);
                // Native argument B is the target when no EXU override exists.
                if (!state && eligible && g_globalEnabled) state = GlobalTarget(b);
                if (!state) return g_original(a, b, dt, outA, outB);
                if (eligible && state->enabled && !TreeUnchanged(*state))
                {
                    state->enabled = false;
                    eligible = false;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { eligible = false; }
            if (!eligible)
            {
                if (state) ++state->fallbacks;
                return g_original(a, b, dt, outA, outB);
            }
            ++state->checks;
            int result = 0;
            if (!state->enabled)
            {
                // Explicit BOX selections are intentional; rejected/changed
                // automatic targets count every stock fallback.
                if (state != &g_state) ++state->fallbacks;
                result = g_original(a, b, dt, outA, outB);
            }
            else
            {
                __try { result = selectedA ? GeometryCall(*state, b, a, dt, outB, outA) : GeometryCall(*state, a, b, dt, outA, outB); }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    state->enabled = false;
                    ++state->fallbacks;
                    LogShimA(LogLevel::Error, "geometrycontact", "native geometry call faulted; restored stock contact");
                    result = g_original(a, b, dt, outA, outB);
                }
            }
            if (result) ++state->hits;
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
            LogShimA(LogLevel::Info, "geometrycontact", "GOG vehicle contact test hook installed; inactive unless global mode or an explicit selection is enabled");
            return true;
        }
    }

    DWORD Capabilities() { return Resolve() ? 1u : 0u; }

    BOOL Set(DWORD handle, BOOL enabled)
    {
        HookEngine::CodePatchLock lock;
        if (!handle || !Install()) return FALSE;
        if (handle != g_state.handle || !LiveOwner(g_state))
        {
            FreeCaches(g_state);
            if (!SafeBuild(g_state, handle)) { FreeCaches(g_state); return FALSE; }
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
        if (g_delete)
        {
            FreeCaches(g_state);
            for (unsigned i = 0; i < kMaxVehicles; ++i) Retire(i);
        }
        g_clock = 0;
        return TRUE;
    }

    BOOL Stats(DWORD handle, DWORD* enabled, DWORD* parts, DWORD* faces, DWORD* checks, DWORD* hits, DWORD* fallbacks)
    {
        if (!enabled || !parts || !faces || !checks || !hits || !fallbacks) return FALSE;
        const State* state = handle == g_state.handle ? &g_state : nullptr;
        if (!state)
            for (const State& candidate : g_vehicles)
                if (candidate.handle == handle) { state = &candidate; break; }
        if (!handle || !state || !LiveOwner(*state)) return FALSE;
        *enabled = state->enabled && Hooks::IsSinglePlayerSession() ? 1u : 0u;
        *parts = state->parts; *faces = state->faces;
        *checks = state->checks; *hits = state->hits; *fallbacks = state->fallbacks;
        return TRUE;
    }

    void InitializeGlobal()
    {
        HookEngine::CodePatchLock lock;
        bool requested = false;
        TryGetUserConfigBool("SinglePlayer", "VehicleGeometryContact", requested);
        // Mission/scene seams own cache retirement on non-Lua missions too.
        g_globalEnabled = requested && Hooks::g_MissionSeamInstalled && Install();
        LogShimA(LogLevel::Info, "geometrycontact", "global vehicle geometry %s (requested=%u; single player only)",
            g_globalEnabled ? "ON" : "OFF", requested ? 1u : 0u);
    }

    void Tick()
    {
        if (!g_globalEnabled) return;
        // No hierarchy dereference until generation/root ownership has passed.
        for (unsigned i = 0; i < kMaxVehicles; ++i)
            if (g_vehicles[i].handle && !LiveOwner(g_vehicles[i])) Retire(i);
    }
}
