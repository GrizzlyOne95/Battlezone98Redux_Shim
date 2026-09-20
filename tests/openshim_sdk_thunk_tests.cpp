// Runtime behaviour of the winmm.dll export thunks.
//
// Links the real generated thunks and the real bridge, then drives them with a
// synthetic provider. What matters is that calling an exported name behaves
// exactly as calling the implementation used to: same arguments, same return
// value, and a documented value rather than a crash when nothing is installed.
//
// Signatures here are picked to cover the shapes that can go wrong: no-arg,
// scalar-arg, multi-arg ordering, a float return (returned in st0/xmm0 rather
// than eax), and one of the five __cdecl exports declared inside namespace
// BZROpenShim.

#include "openshim_sdk_bridge.h"

#include <cstdio>
#include <cstring>

namespace
{
    int g_Failures = 0;

    void Check(bool condition, const char* what, int line)
    {
        if (condition) return;
        std::printf("FAIL line %d: %s\n", line, what);
        ++g_Failures;
    }

#define CHECK(c) Check((c), #c, __LINE__)

    // --- synthetic implementations -------------------------------------
    bool g_ClearAllCalled = false;
    DWORD g_LastThrottle = 0;
    struct { const char* name; int x, y, w, h; } g_LastRect = {};

    BOOL WINAPI FakeClearAll()
    {
        g_ClearAllCalled = true;
        return TRUE;
    }

    BOOL WINAPI FakeSetUnitVoThrottle(DWORD ms)
    {
        g_LastThrottle = ms;
        return TRUE;
    }

    float WINAPI FakeGetRadarSizeScale() { return 2.5f; }

    BOOL WINAPI FakeSetHudSpriteRect(LPCSTR name, int x, int y, int w, int h)
    {
        g_LastRect = {name, x, y, w, h};
        return TRUE;
    }

    const BZROpenShim::OpenShimApiV2* g_FakeApi =
        reinterpret_cast<const BZROpenShim::OpenShimApiV2*>(
            static_cast<uintptr_t>(0xABCD0000u));

    const BZROpenShim::OpenShimApiV2* __cdecl FakeGetApi(uint32_t requested)
    {
        return requested == 2u ? g_FakeApi : nullptr;
    }

    BOOL WINAPI FakeSupportsRenderProfile(DWORD) { return TRUE; }

    // Designated initializers must appear in declaration order, which is the
    // order of include/openshim_sdk_exports.inc. Anything omitted stays null,
    // which is exactly the "provider does not implement this export" case.
    OpenShimSdkProviderTable MakeTable()
    {
        OpenShimSdkProviderTable t = {
            .structSize = sizeof(OpenShimSdkProviderTable),
            .OpenShimImpl_ClearAllAiUnitTuning = FakeClearAll,
            .OpenShimImpl_GetApi = FakeGetApi,
            .OpenShimImpl_GetRadarSizeScale = FakeGetRadarSizeScale,
            .OpenShimImpl_SetHudSpriteRect = FakeSetHudSpriteRect,
            .OpenShimImpl_SetUnitVoThrottle = FakeSetUnitVoThrottle,
            .OpenShimImpl_SupportsRenderProfile = FakeSupportsRenderProfile,
        };
        return t;
    }
}

int main()
{
    // ---- nothing installed: every export must fail safely --------------
    CHECK(BZROpenShim::SdkBridge::Provider() == nullptr);

    const uint64_t before = BZROpenShim::SdkBridge::UnavailableCallCount();
    CHECK(OpenShimClearAllAiUnitTuning() == FALSE);
    CHECK(OpenShimGetRadarSizeScale() == 0.0f);
    CHECK(OpenShimSetUnitVoThrottle(123) == FALSE);
    CHECK(BZROpenShim::OpenShimGetApi(2) == nullptr);
    CHECK(BZROpenShim::SdkBridge::UnavailableCallCount() == before + 4);
    // Calling with no provider must not have reached anything.
    CHECK(!g_ClearAllCalled);
    CHECK(g_LastThrottle == 0);

    // ---- provider installed: calls forward unchanged -------------------
    OpenShimSdkProviderTable table = MakeTable();
    CHECK(BZROpenShim::SdkBridge::InstallProvider(&table));
    CHECK(BZROpenShim::SdkBridge::Provider() == &table);

    CHECK(OpenShimClearAllAiUnitTuning() == TRUE);
    CHECK(g_ClearAllCalled);

    CHECK(OpenShimSetUnitVoThrottle(4242) == TRUE);
    CHECK(g_LastThrottle == 4242);

    // Float returns travel in a different register than integers; a thunk that
    // got the return type wrong would still compile.
    CHECK(OpenShimGetRadarSizeScale() == 2.5f);

    // Argument order and count, including the LPCSTR.
    CHECK(OpenShimSetHudSpriteRect("radar", 10, 20, 30, 40) == TRUE);
    CHECK(g_LastRect.name != nullptr && std::strcmp(g_LastRect.name, "radar") == 0);
    CHECK(g_LastRect.x == 10 && g_LastRect.y == 20);
    CHECK(g_LastRect.w == 30 && g_LastRect.h == 40);

    // __cdecl, declared inside namespace BZROpenShim, pointer return.
    CHECK(BZROpenShim::OpenShimGetApi(2) == g_FakeApi);
    CHECK(BZROpenShim::OpenShimGetApi(99) == nullptr);

    // ---- a slot the provider left unimplemented ------------------------
    const uint64_t beforeMissing = BZROpenShim::SdkBridge::UnavailableCallCount();
    CHECK(OpenShimGetUnitVoMuted() == FALSE);
    CHECK(BZROpenShim::SdkBridge::UnavailableCallCount() == beforeMissing + 1);

    // ---- append-only truncation ----------------------------------------
    // An older provider reports a smaller table. Fields past its end must read
    // as unavailable even though this build's struct has them, and fields
    // inside it must keep working.
    OpenShimSdkProviderTable truncated = MakeTable();
    truncated.structSize =
        (uint32_t)(offsetof(OpenShimSdkProviderTable, OpenShimImpl_SupportsRenderProfile));
    CHECK(BZROpenShim::SdkBridge::InstallProvider(&truncated));
    CHECK(OpenShimSupportsRenderProfile(1) == FALSE);
    CHECK(OpenShimClearAllAiUnitTuning() == TRUE);

    // A table too small to even carry structSize is refused outright.
    OpenShimSdkProviderTable degenerate = MakeTable();
    degenerate.structSize = 0;
    CHECK(!BZROpenShim::SdkBridge::InstallProvider(&degenerate));
    CHECK(!BZROpenShim::SdkBridge::InstallProvider(nullptr));

    if (g_Failures != 0)
    {
        std::printf("openshim sdk thunk tests FAILED (%d)\n", g_Failures);
        return 1;
    }
    std::printf("openshim sdk thunk tests passed\n");
    return 0;
}
