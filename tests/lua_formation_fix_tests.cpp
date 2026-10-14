#include "lua_formation_fix.h"

#include <cstdint>
#include <vector>
#include "test_check.h"

namespace
{
    using namespace BZROpenShim::LuaFormation;

    // Fake engine: argument 2/3 types and values are scripted, every call is
    // recorded so the test can pin exactly what reached native Formation.
    struct FakeLua
    {
        int type2 = 7;               // LUA_TUSERDATA
        int32_t handle1 = 101;
        int32_t handle2 = 202;
        int32_t integer2 = 1;        // what luaL_optinteger(L, 2, 1) yields
        int32_t integer3 = 1;        // what luaL_optinteger(L, 3, 1) yields
        std::vector<int> handleIndices;
        std::vector<int> optIndices;
        int formationCalls = 0;
        int32_t me = -1, him = -1, priority = -1;
    };
    FakeLua g;

    int32_t GetHandle(void*, int i)
    {
        g.handleIndices.push_back(i);
        return i == 1 ? g.handle1 : g.handle2;
    }
    int LuaType(void*, int) { return g.type2; }
    int32_t OptInteger(void*, int i, int32_t def)
    {
        g.optIndices.push_back(i);
        if (def != 1)
            return 0x7FFFFFFF; // a default other than the documented 1 is a bug
        return i == 2 ? g.integer2 : g.integer3;
    }
    void Formation(int32_t a, int32_t b, int32_t c)
    {
        ++g.formationCalls;
        g.me = a;
        g.him = b;
        g.priority = c;
    }
    const Engine kEngine = { GetHandle, LuaType, OptInteger, Formation };

    int Call()
    {
        return Run(nullptr, kEngine);
    }

    void TestClassification()
    {
        CHECK(ClassifyArg2(kLuaTypeNone) == Arg2Kind::StockInteger);
        CHECK(ClassifyArg2(kLuaTypeNil) == Arg2Kind::StockInteger);
        CHECK(ClassifyArg2(kLuaTypeNumber) == Arg2Kind::StockInteger);
        CHECK(ClassifyArg2(1) == Arg2Kind::Handle);  // boolean: let the getter raise
        CHECK(ClassifyArg2(4) == Arg2Kind::Handle);  // string
        CHECK(ClassifyArg2(5) == Arg2Kind::Handle);  // table
        CHECK(ClassifyArg2(7) == Arg2Kind::Handle);  // BZHandle userdata
    }

    void TestHandleLeaderReachesNative()
    {
        g = FakeLua();
        g.type2 = 7;
        g.handle1 = 11;
        g.handle2 = 22;
        g.integer3 = 3;
        CHECK(Call() == 0);
        CHECK(g.formationCalls == 1);
        CHECK(g.me == 11);
        CHECK(g.him == 22);       // the leader handle, not an integer
        CHECK(g.priority == 3);   // argument 3 is honoured
        // Argument 2 must not be read as an integer at all (that is the bug).
        CHECK(g.optIndices == std::vector<int>({ 3 }));
        CHECK(g.handleIndices == std::vector<int>({ 1, 2 }));
    }

    void TestPriorityDefaultsToOne()
    {
        g = FakeLua();
        g.type2 = 7;
        CHECK(Call() == 0);
        CHECK(g.priority == 1);
    }

    void TestNumberKeepsStockReading()
    {
        g = FakeLua();
        g.type2 = kLuaTypeNumber;
        g.integer2 = 55;
        CHECK(Call() == 0);
        CHECK(g.formationCalls == 1);
        CHECK(g.him == 55);       // stock: the integer is the 'him' handle
        CHECK(g.handleIndices == std::vector<int>({ 1 }));
        CHECK(g.optIndices == std::vector<int>({ 2, 3 }));
    }

    void TestAbsentOrNilKeepsStockDefault()
    {
        for (int type : { kLuaTypeNone, kLuaTypeNil })
        {
            g = FakeLua();
            g.type2 = type;
            g.integer2 = 1; // luaL_optinteger default
            CHECK(Call() == 0);
            CHECK(g.formationCalls == 1);
            CHECK(g.him == 1);        // stock: Formation(unit) forms on handle 1
            CHECK(g.priority == 1);
        }
    }

    void TestNumberNowHonoursPriority()
    {
        g = FakeLua();
        g.type2 = kLuaTypeNumber;
        g.integer2 = 9;
        g.integer3 = 4;
        CHECK(Call() == 0);
        CHECK(g.him == 9);
        CHECK(g.priority == 4);   // stock hard-coded 1
    }

    void TestFirstArgumentReadFirst()
    {
        // The leader must be read after the unit so a bad unit argument still
        // raises "bad argument #1" exactly as stock does.
        g = FakeLua();
        g.type2 = 7;
        CHECK(Call() == 0);
        CHECK(g.handleIndices.size() == 2 && g.handleIndices[0] == 1 && g.handleIndices[1] == 2);
    }
}

int main()
{
    TestClassification();
    TestHandleLeaderReachesNative();
    TestPriorityDefaultsToOne();
    TestNumberKeepsStockReading();
    TestAbsentOrNilKeepsStockDefault();
    TestNumberNowHonoursPriority();
    TestFirstArgumentReadFirst();
    return OpenShimTest::ExitCode();
}
