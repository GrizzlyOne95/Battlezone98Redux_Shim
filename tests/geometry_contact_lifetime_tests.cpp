// Exercise the production cache/contact implementation with a fake engine.
// The geometry solver itself still requires released-game qualification.
#include <Windows.h>
#undef small
#include "../src/patches/geometry_contact_test.cpp"
#include <array>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <unordered_map>

namespace GC = BZROpenShim::GeometryContactTest;
namespace
{
    struct Fixture
    {
        int handle;
        std::array<unsigned char, 0xc8> root{}, part{};
        std::array<unsigned char, 32> geo{};
        std::array<unsigned char, 40> entity{};
        std::array<float, 27> positions{};
        explicit Fixture(int id) : handle(id)
        {
            GC::Field<int>(root.data(), 0x84) = 1;
            GC::Field<void*>(root.data(), 0x8c) = this;
            GC::Field<void*>(root.data(), 0x80) = part.data();
            std::memcpy(part.data() + 8, "ABC11abc", 8);
            GC::Field<int>(part.data(), 0x84) = 60;
            GC::Field<void*>(part.data(), 0x64) = geo.data();
            GC::Field<DWORD>(part.data(), 0x14) = 0x4000;
            GC::Field<unsigned>(geo.data(), 4) = 9;
            GC::Field<const float*>(geo.data(), 0x0c) = positions.data();
            GC::Field<void*>(entity.data(), 0) = root.data();
            GC::Field<int>(entity.data(), 0x24) = 1;
        }
    };
    std::unordered_map<int, Fixture*> live;
    bool singlePlayer = true, fault = false, requested = false;
    unsigned allocations = 0, deletions = 0, stockCalls = 0, geometryCalls = 0;
    DWORD facesPerPart = 10;
    int failures = 0;
    void Check(bool ok, const char* why)
    {
        if (!ok) { ++failures; std::printf("FAIL: %s\n", why); }
    }
    void* __cdecl Create(void*, const float*)
    {
        auto* p = new unsigned char[32]{};
        GC::Field<DWORD>(p, 16) = facesPerPart;
        ++allocations;
        return p;
    }
    void __cdecl Delete(void* proxy)
    {
        delete[] GC::Field<unsigned char*>(proxy, 0x9c);
        ++deletions;
    }
    bool __cdecl Select(void*, int) { return true; }
    void* __cdecl Properties(void* output, void*)
    {
        std::memset(output, 0x42, 72);
        return output;
    }
    int __cdecl Stock(void*, void*, float, void*, void*) { ++stockCalls; return 1; }
    int __cdecl Hierarchy(void*, void* target, float, void* outA, void* outB)
    {
        ++geometryCalls;
        auto* root = GC::Field<void*>(target, 0);
        auto* part = GC::Field<void*>(root, 0x80);
        Check(GC::Field<void*>(part, 0x9c) != nullptr, "target cache attached during call");
        Check((GC::Field<DWORD>(part, 0x14) & 0xf000u) == 0x3000, "target geometry flags attached");
        if (fault) RaiseException(EXCEPTION_ACCESS_VIOLATION, 0, 0, nullptr);
        GC::Field<DWORD>(outA, 0) = GC::Field<DWORD>(outB, 0) = 1;
        return 1;
    }
    void Contact(Fixture& a, Fixture& b)
    {
        unsigned char outA[120]{}, outB[120]{};
        GC::ContactHook(a.entity.data(), b.entity.data(), 0.1f, outA, outB);
        Check(GC::Field<void*>(b.part.data(), 0x9c) == nullptr, "cache restored after contact");
        Check(GC::Field<DWORD>(b.part.data(), 0x14) == 0x4000, "flags restored after contact");
    }
}

namespace HookEngine
{
    CodePatchLock::CodePatchLock() {}
    CodePatchLock::~CodePatchLock() {}
    uint32_t ResolveNamedAddress(const char*) { return 0; }
}
namespace BZROpenShim
{
    bool g_IsSteamExe = false;
    uintptr_t g_GameObjectGetHandleAddr = 1;
    void LogShimA(LogLevel, const char*, const char*, ...) {}
    bool TryGetUserConfigBool(const char*, const char*, bool& out) { out = requested; return requested; }
    bool InstallInlineDetour32(InlineDetour32&, uintptr_t, void*, size_t, const uint8_t*, size_t) { return false; }
    void* __cdecl GameObjectFromHandleGog(int handle)
    {
        auto it = live.find(handle);
        return it == live.end() ? nullptr : it->second;
    }
    namespace Hooks
    {
        bool g_MissionSeamInstalled = true;
        bool IsSinglePlayerSession() { return singlePlayer; }
        bool TryGetGameObjectObj76(void* owner, void*& root)
        {
            root = static_cast<Fixture*>(owner)->root.data(); return true;
        }
        bool TryGetGameObjectHandleValue(void* owner, int& handle)
        {
            handle = static_cast<Fixture*>(owner)->handle; return true;
        }
    }
}

int main()
{
    GC::g_create = Create; GC::g_delete = Delete; GC::g_select = Select;
    GC::g_properties = Properties; GC::g_hierarchy = Hierarchy; GC::g_original = Stock;
    Fixture a(1), b(2), c(3);
    live = {{1, &a}, {2, &b}, {3, &c}};
    GC::InitializeGlobal();
    Contact(a, b);
    Check(allocations == 0 && stockCalls == 1, "absent setting preserves stock without allocating");
    requested = true;
    GC::InitializeGlobal();
    Contact(a, b); Contact(a, c); Contact(c, b);
    Check(allocations == 2 && geometryCalls == 3, "multiple targets reuse independent caches");
    DWORD enabled, parts, faces, checks, hits, fallbacks;
    Check(GC::Stats(2, &enabled, &parts, &faces, &checks, &hits, &fallbacks) &&
          enabled == 1 && checks == 2 && hits == 2, "automatic targets expose actual stats");
    GC::Set(2, FALSE);
    const unsigned before = geometryCalls;
    Contact(a, b); Contact(a, c);
    Check(geometryCalls == before + 1, "explicit BOX overrides global only for selected pair");
    GC::Clear();
    Check(allocations == deletions, "clear frees selected and automatic caches");
    Contact(a, b);
    Check(GC::g_globalEnabled, "mission clear retains configured global policy");
    live.erase(2); GC::Tick();
    Check(allocations == deletions, "removed target retired without dereferencing dead parts");
    Fixture recycled(2); live[2] = &recycled; Contact(a, recycled);
    Check(allocations == deletions + 1, "reused handle starts with fresh cache");
    GC::Field<void*>(recycled.part.data(), 0x64) = c.geo.data();
    Contact(a, recycled);
    Check(GC::Stats(2, &enabled, &parts, &faces, &checks, &hits, &fallbacks) &&
          enabled == 0 && fallbacks == 1, "model mutation disables stale geometry");
    GC::Clear();
    GC::Field<unsigned>(b.geo.data(), 4) = 8; live[2] = &b;
    const unsigned rejectedStart = allocations;
    Contact(a, b); Contact(a, b);
    Check(allocations == rejectedStart, "rejected tiny geometry cached without retry allocation");
    GC::Field<unsigned>(b.geo.data(), 4) = 9;
    GC::Clear(); singlePlayer = false;
    Contact(a, b);
    Check(allocations == rejectedStart, "network gate cannot allocate or activate geometry");
    singlePlayer = true; fault = true; Contact(a, b); fault = false;
    Check(GC::Stats(2, &enabled, &parts, &faces, &checks, &hits, &fallbacks) &&
          enabled == 0 && fallbacks == 1, "native fault restores fields and disables automatic target");
    GC::Clear();
    std::vector<std::unique_ptr<Fixture>> many;
    for (unsigned i = 0; i < GC::kMaxVehicles + 2; ++i)
    {
        many.push_back(std::make_unique<Fixture>(100 + static_cast<int>(i)));
        Fixture& target = *many.back(); live[target.handle] = &target; Contact(a, target);
    }
    Check(allocations - deletions == GC::kMaxVehicles, "entry limit evicts old native caches");
    GC::Clear(); facesPerPart = 100000;
    for (unsigned i = 0; i < 6; ++i) Contact(a, *many[i]);
    Check(GC::g_cachedFaces <= GC::kMaxCachedFaces && allocations - deletions == 5,
          "face budget evicts independent of entry limit");
    GC::Clear();
    Check(allocations == deletions, "all native allocations released at final teardown");
    std::printf("geometry contact lifetime failures: %d\n", failures);
    return failures ? 1 : 0;
}
