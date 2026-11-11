// Predicate tests for the fog-distance submission cull (include/fog_distance_cull.h).
//
// The behaviour worth pinning is fail-closed: every input the hook could not
// verify must keep the object, and only a linear-fog main-camera main/glow pass
// with a finite box wholly past fogEnd + nearClip + margin may cull.

#include "fog_distance_cull.h"

#include <cmath>
#include <cstdio>
#include <limits>
#include "test_check.h"

using OpenShimTest::Check;

namespace
{
    using namespace openshim::fogcull;

    // A view looking down world -Z from the origin: view z == world z, so the
    // nearest depth of a box is -(box max z).
    constexpr float kLookDownMinusZ[4] = { 0.0f, 0.0f, 1.0f, 0.0f };

    Inputs Cullable()
    {
        Inputs in;
        in.featureEnabled = true;
        in.shadowPass = false;
        in.isMainCamera = true;
        in.passAllowed = true;
        in.viewModeAllowed = true;
        in.projectionType = kProjectionPerspective;
        in.fogMode = kFogModeLinear;
        in.fogStart = 100.0f;
        in.fogEnd = 375.0f;
        in.nearClip = 1.0f;
        in.extent = kExtentFinite;
        in.nearestDepth = 1000.0f;
        return in;
    }

    void TestDepth()
    {
        const float boxMin[3] = { -5.0f, -5.0f, -420.0f };
        const float boxMax[3] = { 5.0f, 5.0f, -400.0f };
        Check(NearestViewDepthOfAabb(kLookDownMinusZ, boxMin, boxMax) == 400.0f,
              "nearest depth of a box ahead is its near face");

        // Camera at z=+50 (view z = world z - 50): translation in column 3.
        const float shifted[4] = { 0.0f, 0.0f, 1.0f, -50.0f };
        Check(NearestViewDepthOfAabb(shifted, boxMin, boxMax) == 450.0f,
              "translation moves the nearest depth");

        // A box straddling the camera plane has a negative nearest depth.
        const float straddleMin[3] = { -1.0f, -1.0f, -10.0f };
        const float straddleMax[3] = { 1.0f, 1.0f, 10.0f };
        Check(NearestViewDepthOfAabb(kLookDownMinusZ, straddleMin, straddleMax) == -10.0f,
              "box around the camera is never far");

        // Rotated view (looking down -X): row2 = (1,0,0,0).
        const float lookMinusX[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
        const float sideMin[3] = { -600.0f, -1.0f, -1.0f };
        const float sideMax[3] = { -500.0f, 1.0f, 1.0f };
        Check(NearestViewDepthOfAabb(lookMinusX, sideMin, sideMax) == 500.0f,
              "rotated view picks the right corner");
    }

    void TestCullsOnlyPastThreshold()
    {
        Inputs in = Cullable();
        Check(DecideGeometry(in) == Decision::Cull, "baseline far object culls");

        const float threshold = CullDepth(in.fogEnd, in.nearClip);
        Check(threshold == 375.0f + 1.0f + kMarginMetres, "threshold is fogEnd + near + margin");

        in.nearestDepth = threshold;
        Check(DecideGeometry(in) == Decision::KeepInsideFog, "exactly at the threshold keeps");
        in.nearestDepth = threshold - 0.5f;
        Check(DecideGeometry(in) == Decision::KeepInsideFog, "inside the margin keeps");
        in.nearestDepth = in.fogEnd + 1.0f;
        Check(DecideGeometry(in) == Decision::KeepInsideFog, "just past fog end but inside margin keeps");
        in.nearestDepth = threshold + 0.5f;
        Check(DecideGeometry(in) == Decision::Cull, "just outside the margin culls");
        in.nearestDepth = -5.0f;
        Check(DecideGeometry(in) == Decision::KeepInsideFog, "behind/around camera keeps");
        in.nearestDepth = std::numeric_limits<float>::quiet_NaN();
        Check(DecideGeometry(in) == Decision::KeepInsideFog, "NaN depth keeps");
    }

    void TestFogStates()
    {
        Inputs in = Cullable();
        in.fogMode = 0;
        Check(DecideGeometry(in) == Decision::KeepFogNotLinear, "fog off keeps");
        in.fogMode = 1;
        Check(DecideGeometry(in) == Decision::KeepFogNotLinear, "exp fog keeps");
        in.fogMode = 2;
        Check(DecideGeometry(in) == Decision::KeepFogNotLinear, "exp2 fog keeps");

        in = Cullable();
        in.fogEnd = in.fogStart;
        Check(DecideGeometry(in) == Decision::KeepFogInvalid, "zero-width fog keeps");
        in = Cullable();
        in.fogEnd = 0.0f;
        in.fogStart = -10.0f;
        Check(DecideGeometry(in) == Decision::KeepFogInvalid, "fog end at zero keeps");
        in = Cullable();
        in.fogEnd = std::numeric_limits<float>::infinity();
        Check(DecideGeometry(in) == Decision::KeepFogInvalid, "infinite fog end keeps");
        in = Cullable();
        in.nearClip = std::numeric_limits<float>::quiet_NaN();
        Check(DecideGeometry(in) == Decision::KeepFogInvalid, "NaN near clip keeps");
    }

    void TestBounds()
    {
        Inputs in = Cullable();
        in.extent = 0u;
        Check(DecideGeometry(in) == Decision::KeepNoFiniteBounds, "null (missing) bounds keep");
        in.extent = 2u;
        Check(DecideGeometry(in) == Decision::KeepNoFiniteBounds, "infinite bounds keep");
        in.extent = 7u;
        Check(DecideGeometry(in) == Decision::KeepNoFiniteBounds, "garbage extent keeps");
    }

    void TestPassIdentity()
    {
        Inputs in = Cullable();
        in.featureEnabled = false;
        Check(DecideGeometry(in) == Decision::KeepDisabled, "feature off keeps");

        in = Cullable();
        in.shadowPass = true;
        Check(DecideGeometry(in) == Decision::KeepShadowPass, "shadow caster pass keeps");

        in = Cullable();
        in.isMainCamera = false;
        Check(DecideGeometry(in) == Decision::KeepNotMainCamera, "sniper/PiP/other camera keeps");

        in = Cullable();
        in.passAllowed = false;
        Check(DecideGeometry(in) == Decision::KeepPassNotAllowed,
              "extra viewport (mirror, RTT) with the main camera keeps");

        in = Cullable();
        in.projectionType = 0;
        Check(DecideGeometry(in) == Decision::KeepNotPerspective, "orthographic keeps");
        in.projectionType = -1;
        Check(DecideGeometry(in) == Decision::KeepNotPerspective, "unknown projection keeps");
    }

    void TestViewModes()
    {
        Check(IsAllowedViewMode(0) && IsAllowedViewMode(1) && IsAllowedViewMode(7),
              "cockpit/external/chase allowed");
        Check(!IsAllowedViewMode(2), "binocular zoom excluded");
        Check(!IsAllowedViewMode(3), "satellite excluded");
        Check(!IsAllowedViewMode(4) && !IsAllowedViewMode(6) && !IsAllowedViewMode(8),
              "padlock, free eye and missile camera excluded");
        Check(!IsAllowedViewMode(5), "cinematic excluded");
        Check(!IsAllowedViewMode(9) && !IsAllowedViewMode(10), "2D/editor excluded");
        Check(!IsAllowedViewMode(-1) && !IsAllowedViewMode(42), "unknown excluded");

        Inputs in = Cullable();
        in.viewModeAllowed = false;
        Check(DecideGeometry(in) == Decision::KeepViewMode, "disallowed view mode keeps");
    }

    void TestMaterial()
    {
        Check(ApplyMaterial(Decision::Cull, true) == Decision::KeepFogOverride,
              "fog_override pass keeps");
        Check(ApplyMaterial(Decision::Cull, false) == Decision::Cull,
              "normal fogged material culls");
        Check(ApplyMaterial(Decision::KeepInsideFog, false) == Decision::KeepInsideFog,
              "material check never turns keep into cull");
    }
}

int main()
{
    TestDepth();
    TestCullsOnlyPastThreshold();
    TestFogStates();
    TestBounds();
    TestPassIdentity();
    TestViewModes();
    TestMaterial();

    if (OpenShimTest::FailureCount() != 0)
    {
        std::fprintf(stderr, "fog_distance_cull_tests: %d failure(s)\n", OpenShimTest::FailureCount());
        return 1;
    }
    std::printf("fog_distance_cull_tests passed\n");
    return 0;
}
