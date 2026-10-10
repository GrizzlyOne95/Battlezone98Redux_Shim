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
#include "test_check.h"

namespace
{
    // --- synthetic implementations -------------------------------------
    bool g_ClearAllCalled = false;
    DWORD g_LastThrottle = 0;
    struct { const char* name; int x, y, w, h; } g_LastRect = {};
    struct { void* object; DWORD handle; float multiplier; } g_LastDamage = {};
    BOOL WINAPI FakeSetDamage(void* object, DWORD handle, float multiplier)
    {
        g_LastDamage = {object, handle, multiplier};
        return TRUE;
    }

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

    DWORD WINAPI FakeNativeHudCapabilities() { return 3; }
    DWORD WINAPI FakeGeometryCapabilities() { return 1; }
    DWORD g_GeometryHandle = 0;
    BOOL g_GeometryEnabled = FALSE;
    BOOL WINAPI FakeSetGeometry(DWORD h, BOOL enabled)
    { g_GeometryHandle = h; g_GeometryEnabled = enabled; return TRUE; }
    BOOL WINAPI FakeGeometryStats(DWORD h, DWORD* enabled, DWORD* parts, DWORD* faces,
                                 DWORD* checks, DWORD* hits, DWORD* fallbacks)
    {
        if (h != g_GeometryHandle) return FALSE;
        *enabled = g_GeometryEnabled ? 1u : 0u; *parts = 9; *faces = 1200;
        *checks = 15; *hits = 3; *fallbacks = 2;
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
            .OpenShimImpl_GetNativeHudLayoutCapabilities = FakeNativeHudCapabilities,
            .OpenShimImpl_SetNativeHudMeterRect = FakeSetHudSpriteRect,
            .OpenShimImpl_HasNativeDamageResistance = FakeClearAll,
            .OpenShimImpl_SetUnitDamageMultiplier = FakeSetDamage,
            .OpenShimImpl_GetGeometryContactCapabilities = FakeGeometryCapabilities,
            .OpenShimImpl_SetGeometryContact = FakeSetGeometry,
            .OpenShimImpl_GetGeometryContactStats = FakeGeometryStats,
        };
        return t;
    }
}

int main()
{
    // ---- nothing installed: every export must fail safely --------------
    CHECK(BZROpenShim::SdkBridge::Provider() == nullptr);

    const uint64_t before = BZROpenShim::SdkBridge::UnavailableCallCount();
    CHECK(OpenShimGetNativeHudLayoutCapabilities() == 0);
    CHECK(OpenShimSetNativeHudMeterRect("hull", 1, 2, 3, 4) == FALSE);
    CHECK(OpenShimClearAllAiUnitTuning() == FALSE);
    CHECK(OpenShimGetRadarSizeScale() == 0.0f);
    CHECK(OpenShimSetUnitVoThrottle(123) == FALSE);
    CHECK(BZROpenShim::OpenShimGetApi(2) == nullptr);
    CHECK(BZROpenShim::SdkBridge::UnavailableCallCount() == before + 6);
    // Calling with no provider must not have reached anything.
    CHECK(!g_ClearAllCalled);
    CHECK(g_LastThrottle == 0);
    CHECK(OpenShimHasNativeDamageResistance() == FALSE);
    CHECK(OpenShimSetUnitDamageMultiplier(nullptr, 0, .75f) == FALSE);

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

    // Appended HUD entries forward without moving existing/legacy slots.
    CHECK(OpenShimGetNativeHudLayoutCapabilities() == 3);
    CHECK(OpenShimSetNativeHudMeterRect("hull", 11, 22, 33, 44) == TRUE);
    CHECK(std::strcmp(g_LastRect.name, "hull") == 0 && g_LastRect.x == 11 && g_LastRect.h == 44);
    CHECK(OpenShimHasNativeDamageResistance() == TRUE);
    auto* damageObject = reinterpret_cast<void*>(static_cast<uintptr_t>(0x12345678));
    CHECK(OpenShimSetUnitDamageMultiplier(damageObject, 0x123ABCD, .75f) == TRUE);
    CHECK(g_LastDamage.object == damageObject && g_LastDamage.handle == 0x123ABCD &&
        g_LastDamage.multiplier == .75f);
    // The immediately preceding HUD provider keeps all of its slots and fails
    // closed on this appended damage block.
    table.structSize = (uint32_t)offsetof(OpenShimSdkProviderTable, OpenShimImpl_HasNativeDamageResistance);
    CHECK(OpenShimHasNativeDamageResistance() == FALSE);
    CHECK(OpenShimSetUnitDamageMultiplier(damageObject, 7, .5f) == FALSE);
    CHECK(OpenShimGetNativeHudLayoutCapabilities() == 3);
    table.structSize = sizeof(table);

    // Geometry fields append after HUD; every output argument keeps its order.
    CHECK(OpenShimGetGeometryContactCapabilities() == 1);
    CHECK(OpenShimSetGeometryContact(0xABC01234u, TRUE) == TRUE);
    DWORD enabled = 0, parts = 0, faces = 0, checks = 0, hits = 0, fallbacks = 0;
    CHECK(OpenShimGetGeometryContactStats(0xABC01234u, &enabled, &parts, &faces, &checks, &hits, &fallbacks) == TRUE);
    CHECK(enabled == 1 && parts == 9 && faces == 1200 && checks == 15 && hits == 3 && fallbacks == 2);
    table.structSize = (uint32_t)offsetof(OpenShimSdkProviderTable, OpenShimImpl_GetGeometryContactCapabilities);
    CHECK(OpenShimGetGeometryContactCapabilities() == 0);
    CHECK(OpenShimSetGeometryContact(0x123u, TRUE) == FALSE);
    CHECK(OpenShimGetGeometryContactStats(0x123u, &enabled, &parts, &faces, &checks, &hits, &fallbacks) == FALSE);
    CHECK(OpenShimGetNativeHudLayoutCapabilities() == 3);
    table.structSize = sizeof(table);

    // A previous-version provider ends immediately after its legacy block.
    // New slots fail closed, while every previous slot remains at its offset.
    table.structSize = (uint32_t)offsetof(OpenShimSdkProviderTable, OpenShimImpl_GetNativeHudLayoutCapabilities);
    CHECK(OpenShimGetNativeHudLayoutCapabilities() == 0);
    CHECK(OpenShimSetNativeHudMeterRect("hull", 1, 2, 3, 4) == FALSE);
    CHECK(OpenShimSetHudSpriteRect("radar", 1, 2, 3, 4) == TRUE);
    table.structSize = sizeof(table);

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

    if (OpenShimTest::FailureCount() != 0)
    {
        std::printf("openshim sdk thunk tests FAILED (%d)\n", OpenShimTest::FailureCount());
        return 1;
    }
    std::printf("openshim sdk thunk tests passed\n");
    return 0;
}
