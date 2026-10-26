#include "lua_getindependence_guard.h"

#include <cstdint>
#include "test_check.h"

namespace
{
    using namespace BZROpenShim::LuaGetIndependence;

    // Fake engine: the object, its process field and the process vtable are
    // scripted; every native call and push is recorded.
    struct FakeEngine
    {
        int32_t handle = 0x1234;
        bool hasObject = true;
        bool processReadable = true;
        uintptr_t process = 0x02000000;
        bool vtableReadable = true;
        uintptr_t vtable = 0x00880000;
        bool gameClass = true;
        int32_t nativeValue = 1;
        int nativeCalls = 0;
        int pushes = 0;
        int32_t pushed = -99;
        int rejects = 0;
        Verdict lastReject = Verdict::Accept;
    };
    FakeEngine g;
    int g_object = 0;

    int32_t GetHandle(void*, int index) { return index == 1 ? g.handle : -1; }
    void PushInteger(void*, int32_t v)
    {
        ++g.pushes;
        g.pushed = v;
    }
    int32_t GetIndependence(int32_t)
    {
        ++g.nativeCalls;
        return g.nativeValue;
    }
    void* GetObject(int32_t) { return g.hasObject ? &g_object : nullptr; }
    bool ReadProcess(const void*, uintptr_t& p)
    {
        p = g.processReadable ? g.process : 0;
        return g.processReadable;
    }
    bool ReadVtable(uintptr_t, uintptr_t& v)
    {
        v = g.vtableReadable ? g.vtable : 0;
        return g.vtableReadable;
    }
    bool IsGameClass(uintptr_t) { return g.gameClass; }
    void OnReject(int32_t, uintptr_t, uintptr_t, Verdict verdict)
    {
        ++g.rejects;
        g.lastReject = verdict;
    }
    const Engine kEngine = { GetHandle, PushInteger, GetIndependence, GetObject,
                             ReadProcess, ReadVtable, IsGameClass, OnReject };

    // Runs the binding and checks the contract every case shares: one Lua
    // result, pushed exactly once.
    int32_t Call()
    {
        CHECK(Run(nullptr, kEngine) == 1);
        CHECK(g.pushes == 1);
        return g.pushed;
    }

    void TestRealProcessForwardsToStock()
    {
        g = FakeEngine();
        g.nativeValue = 1;
        CHECK(Call() == 1);
        CHECK(g.nativeCalls == 1);
        CHECK(g.rejects == 0);

        g = FakeEngine();
        g.nativeValue = 0;
        CHECK(Call() == 0);
        CHECK(g.nativeCalls == 1);
    }

    void TestLoadPlaceholdersReadZero()
    {
        // 1 is the missionSave placeholder, 2 the value in the 2026-10-26
        // misn02b crash; neither may reach the native read of [p+0x18].
        const uintptr_t placeholders[] = { 1, 2, 0x1A, kMinPointer - 1 };
        for (uintptr_t p : placeholders)
        {
            g = FakeEngine();
            g.process = p;
            CHECK(Call() == 0);
            CHECK(g.nativeCalls == 0);
            CHECK(g.rejects == 1);
            CHECK(g.lastReject == Verdict::Placeholder);
        }
    }

    void TestStockZeroCasesStayQuiet()
    {
        g = FakeEngine();
        g.hasObject = false;
        CHECK(Call() == 0);
        CHECK(g.nativeCalls == 0);
        CHECK(g.rejects == 0);

        g = FakeEngine();
        g.process = 0;
        CHECK(Call() == 0);
        CHECK(g.nativeCalls == 0);
        CHECK(g.rejects == 0);
    }

    void TestUnreadableOrForeignProcessReadsZero()
    {
        g = FakeEngine();
        g.processReadable = false;
        CHECK(Call() == 0);
        CHECK(g.nativeCalls == 0);
        CHECK(g.lastReject == Verdict::Unreadable);

        g = FakeEngine();
        g.vtableReadable = false;
        CHECK(Call() == 0);
        CHECK(g.nativeCalls == 0);
        CHECK(g.lastReject == Verdict::Unreadable);

        // A large stale value that happens to be readable but is not a game
        // object (no in-image RTTI vtable).
        g = FakeEngine();
        g.gameClass = false;
        CHECK(Call() == 0);
        CHECK(g.nativeCalls == 0);
        CHECK(g.lastReject == Verdict::ForeignVtable);
    }

    void TestBoundary()
    {
        g = FakeEngine();
        g.process = kMinPointer;
        CHECK(Call() == 1);
        CHECK(g.nativeCalls == 1);
    }
}

int main()
{
    TestRealProcessForwardsToStock();
    TestLoadPlaceholdersReadZero();
    TestStockZeroCasesStayQuiet();
    TestUnreadableOrForeignProcessReadsZero();
    TestBoundary();
    return OpenShimTest::ExitCode();
}
