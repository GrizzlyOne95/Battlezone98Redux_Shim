// Regression tests for player smart-reticle weapon convergence.
//
// These pin the coordinate-space contract that the ~45-degree misfire violated:
// the matrix convergence writes to weapon->obj+0x20 is mount-relative, and the
// direction it solves for must be measured from the *world* muzzle, not from the
// world origin. Both defects are reproduced explicitly below so a regression
// shows up as a named failure rather than as a vague angle error.

#include "weapon_convergence.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>

namespace
{
    using namespace BZROpenShim::WeaponConvergence;

    [[noreturn]] void Fail(const char* message)
    {
        std::fprintf(stderr, "weapon_convergence_tests: %s\n", message);
        std::exit(1);
    }

    void Require(bool condition, const char* message)
    {
        if (!condition)
            Fail(message);
    }

    void RequireNear(double actual, double expected, double tolerance, const char* message)
    {
        if (!(std::fabs(actual - expected) <= tolerance))
        {
            std::fprintf(stderr,
                "weapon_convergence_tests: %s (actual=%.6f expected=%.6f)\n",
                message, actual, expected);
            std::exit(1);
        }
    }

    Matrix MakeYawMatrix(float radians, double px, double py, double pz)
    {
        const float c = std::cos(radians);
        const float s = std::sin(radians);
        Matrix out = Identity();
        // Row-vector yaw about +Y: right and front rotate, up is untouched.
        out.rightX = c;
        out.rightZ = -s;
        out.frontX = s;
        out.frontZ = c;
        out.positionX = px;
        out.positionY = py;
        out.positionZ = pz;
        return out;
    }

    Matrix MakePitchMatrix(float radians)
    {
        const float c = std::cos(radians);
        const float s = std::sin(radians);
        Matrix out = Identity();
        out.upY = c;
        out.upZ = s;
        out.frontY = -s;
        out.frontZ = c;
        return out;
    }

    float AngleBetweenDegrees(const Vec3& lhs, const Vec3& rhs)
    {
        float cosine = Dot(lhs, rhs);
        if (cosine > 1.0f)
            cosine = 1.0f;
        if (cosine < -1.0f)
            cosine = -1.0f;
        return std::acos(cosine) * (180.0f / 3.14159265358979f);
    }

    // Fire direction as the engine's ordnance spawn computes it:
    // Matrix_Multiply(weapon->obj->mat, weapon->M).
    Vec3 FireDirection(const Matrix& mountLocal, const Matrix& mountWorld)
    {
        return Front(Multiply(mountLocal, mountWorld));
    }

    Vec3 FireOrigin(const Matrix& mountLocal, const Matrix& mountWorld)
    {
        return Position(Multiply(mountLocal, mountWorld));
    }

    // A target placed `range` metres down the barrel's own world front, then
    // nudged `lateral` metres across it. Building targets this way keeps every
    // case inside the deviation safety stop no matter how the craft is oriented,
    // so a skip can never quietly hollow out a test.
    Vec3 TargetOffBarrel(
        const Matrix& mountLocal,
        const Matrix& mountWorld,
        float range,
        float lateral,
        float vertical)
    {
        const Matrix world = Multiply(mountLocal, mountWorld);
        const Vec3 origin = Position(world);
        const Vec3 front = Front(world);
        Vec3 right = { world.rightX, world.rightY, world.rightZ };
        Vec3 up = { world.upX, world.upY, world.upZ };
        Require(Normalize(right) && Normalize(up), "barrel basis was degenerate");
        return {
            origin.x + front.x * range + right.x * lateral + up.x * vertical,
            origin.y + front.y * range + right.y * lateral + up.y * vertical,
            origin.z + front.z * range + right.z * lateral + up.z * vertical,
        };
    }

    void TestMultiplyMatchesEngineConvention()
    {
        // Row-vector: p * lhs * rhs. A child offset by +X inside a parent
        // yawed 90 degrees must land along the parent's rotated axis.
        Matrix child = Identity();
        child.positionX = 1.0;
        const Matrix parent = MakeYawMatrix(3.14159265358979f * 0.5f, 10.0, 0.0, 20.0);

        const Matrix world = Multiply(child, parent);
        RequireNear(world.positionX, 10.0, 1e-4, "multiply did not place the child through the parent");
        RequireNear(world.positionY, 0.0, 1e-4, "multiply leaked into Y");
        RequireNear(world.positionZ, 19.0, 1e-4, "multiply did not rotate the child offset");
    }

    void TestInvertRoundTrips()
    {
        const Matrix m = Multiply(MakePitchMatrix(0.4f), MakeYawMatrix(1.1f, 123.0, 4.0, -56.0));
        const Matrix roundTrip = Multiply(m, Invert(m));

        RequireNear(roundTrip.rightX, 1.0, 1e-4, "inverse round trip lost right.x");
        RequireNear(roundTrip.upY, 1.0, 1e-4, "inverse round trip lost up.y");
        RequireNear(roundTrip.frontZ, 1.0, 1e-4, "inverse round trip lost front.z");
        RequireNear(roundTrip.positionX, 0.0, 1e-3, "inverse round trip left translation in X");
        RequireNear(roundTrip.positionY, 0.0, 1e-3, "inverse round trip left translation in Y");
        RequireNear(roundTrip.positionZ, 0.0, 1e-3, "inverse round trip left translation in Z");
    }

    void TestArcRotationCarriesFrontOntoTarget()
    {
        const Vec3 from = { 0.0f, 0.0f, 1.0f };
        Vec3 to = { 0.3f, 0.5f, 0.8f };
        Require(Normalize(to), "test target direction was degenerate");

        Matrix arc = {};
        Require(BuildArcRotation(from, to, { 0.0f, 1.0f, 0.0f }, arc),
            "arc rotation refused a well-formed pair");

        // Row-vector: from * arc == to.
        const Vec3 rotated = {
            from.x * arc.rightX + from.y * arc.upX + from.z * arc.frontX,
            from.x * arc.rightY + from.y * arc.upY + from.z * arc.frontY,
            from.x * arc.rightZ + from.y * arc.upZ + from.z * arc.frontZ,
        };
        // acos is ill-conditioned near zero: a float dot product one ulp below
        // 1.0 already reads as ~0.03 degrees, so compare the vectors directly
        // and keep the angular checks below at a 0.05-degree noise floor --
        // still three orders of magnitude under the ~45-degree defect.
        RequireNear(rotated.x, to.x, 1e-5, "arc rotation lost X");
        RequireNear(rotated.y, to.y, 1e-5, "arc rotation lost Y");
        RequireNear(rotated.z, to.z, 1e-5, "arc rotation lost Z");
        Require(IsRotationOrthonormal(arc), "arc rotation was not orthonormal");
    }

    void TestArcRotationHandlesAlignedAndReversed()
    {
        const Vec3 forward = { 0.0f, 0.0f, 1.0f };
        Matrix arc = {};

        Require(BuildArcRotation(forward, forward, { 0.0f, 1.0f, 0.0f }, arc),
            "aligned arc rotation failed");
        RequireNear(arc.rightX, 1.0, 1e-5, "aligned arc rotation was not identity");
        RequireNear(arc.frontZ, 1.0, 1e-5, "aligned arc rotation was not identity");

        const Vec3 backward = { 0.0f, 0.0f, -1.0f };
        Require(BuildArcRotation(forward, backward, { 0.0f, 1.0f, 0.0f }, arc),
            "reversed arc rotation failed");
        Require(IsRotationOrthonormal(arc), "reversed arc rotation was not orthonormal");
        const Vec3 rotated = {
            forward.x * arc.rightX + forward.y * arc.upX + forward.z * arc.frontX,
            forward.x * arc.rightY + forward.y * arc.upY + forward.z * arc.frontY,
            forward.x * arc.rightZ + forward.y * arc.upZ + forward.z * arc.frontZ,
        };
        RequireNear(AngleBetweenDegrees(rotated, backward), 0.0, 1e-2,
            "reversed arc rotation did not flip the front vector");
    }

    // The headline case: craft parked far from the world origin, rotated, with a
    // laterally offset hardpoint. This is the exact geometry from the reported
    // failure -- target (2560, 2.4, 2615) roughly 3659 m from the origin.
    void TestConvergenceAimsThroughTheReticleFromADistantRotatedCraft()
    {
        const Matrix mountWorld = MakeYawMatrix(0.9f, 2500.0, 6.0, 2500.0);
        Matrix mountLocal = Identity();
        mountLocal.positionX = 1.5;   // hardpoint offset out on the right wing
        mountLocal.positionY = 0.4;

        const Vec3 target = { 2560.0f, 2.4f, 2615.0f };

        Solution solution = {};
        Require(Solve(mountLocal, mountWorld, target, solution) == SolveResult::Converged,
            "convergence refused a normal distant target");

        const Vec3 origin = FireOrigin(solution.mountLocal, mountWorld);
        Vec3 toTarget = { target.x - origin.x, target.y - origin.y, target.z - origin.z };
        Require(Normalize(toTarget), "muzzle-to-target vector was degenerate");

        const Vec3 fired = FireDirection(solution.mountLocal, mountWorld);
        RequireNear(AngleBetweenDegrees(fired, toTarget), 0.0, 0.05,
            "fire direction did not pass through the reticle target");
        RequireNear(solution.residualDegrees, 0.0, 0.05,
            "reported residual disagreed with the recomposed fire direction");
    }

    void TestConvergencePreservesTheHardpointPosition()
    {
        const Matrix mountWorld = MakeYawMatrix(-2.2f, -900.0, 12.0, 400.0);
        Matrix mountLocal = MakePitchMatrix(0.15f);
        mountLocal.positionX = -1.25;
        mountLocal.positionY = 0.75;
        mountLocal.positionZ = 2.0;

        Solution solution = {};
        const Vec3 target = TargetOffBarrel(mountLocal, mountWorld, 180.0f, 12.0f, -4.0f);
        Require(Solve(mountLocal, mountWorld, target, solution) == SolveResult::Converged,
            "convergence refused a normal target");

        RequireNear(solution.mountLocal.positionX, mountLocal.positionX, 1e-9,
            "convergence moved the hardpoint in X");
        RequireNear(solution.mountLocal.positionY, mountLocal.positionY, 1e-9,
            "convergence moved the hardpoint in Y");
        RequireNear(solution.mountLocal.positionZ, mountLocal.positionZ, 1e-9,
            "convergence moved the hardpoint in Z");
        Require(IsRotationOrthonormal(solution.mountLocal),
            "converged mount-local rotation was not orthonormal");
    }

    void TestMuzzleIsWorldSpaceNotMountLocal()
    {
        // The original defect read the muzzle straight out of obj+0x20, which is
        // (0,0,0) for a hardpoint-mounted weapon, and so measured the aim vector
        // from the world origin. Assert the solver reports the composed world
        // muzzle instead.
        const Matrix mountWorld = MakeYawMatrix(0.0f, 2500.0, 6.0, 2500.0);
        Matrix mountLocal = Identity();

        Solution solution = {};
        Require(Solve(mountLocal, mountWorld, { 2560.0f, 2.4f, 2615.0f }, solution) ==
                SolveResult::Converged,
            "convergence refused a normal target");

        RequireNear(solution.muzzle.x, 2500.0, 1e-3, "muzzle was not reported in world space");
        RequireNear(solution.muzzle.z, 2500.0, 1e-3, "muzzle was not reported in world space");
        Require(solution.muzzle.x > 1.0f,
            "muzzle collapsed to the world origin -- the mount-local read regressed");
    }

    // Reproduces the pre-fix behaviour and asserts it is genuinely wrong, so the
    // test would have caught the shipped defect.
    void TestPreFixBehaviourIsRejected()
    {
        const Matrix mountWorld = MakeYawMatrix(0.9f, 2500.0, 6.0, 2500.0);
        const Matrix mountLocal = Identity();
        const Vec3 target = { 2560.0f, 2.4f, 2615.0f };

        // Old code: direction = normalize(target - obj+0x20 position), written as
        // a world basis straight into the mount-local slot.
        Vec3 badDirection = { target.x, target.y, target.z };
        Require(Normalize(badDirection), "reference direction was degenerate");
        Matrix badLocal = Identity();
        badLocal.frontX = badDirection.x;
        badLocal.frontY = badDirection.y;
        badLocal.frontZ = badDirection.z;
        Vec3 badRight = Cross({ 0.0f, 1.0f, 0.0f }, badDirection);
        Require(Normalize(badRight), "reference right vector was degenerate");
        const Vec3 badUp = Cross(badDirection, badRight);
        badLocal.rightX = badRight.x; badLocal.rightY = badRight.y; badLocal.rightZ = badRight.z;
        badLocal.upX = badUp.x; badLocal.upY = badUp.y; badLocal.upZ = badUp.z;

        const Vec3 origin = FireOrigin(badLocal, mountWorld);
        Vec3 toTarget = { target.x - origin.x, target.y - origin.y, target.z - origin.z };
        Require(Normalize(toTarget), "muzzle-to-target vector was degenerate");
        const float badError = AngleBetweenDegrees(FireDirection(badLocal, mountWorld), toTarget);
        Require(badError > 20.0f,
            "the pre-fix construction no longer misaims, so this regression guard is meaningless");

        Solution solution = {};
        Require(Solve(mountLocal, mountWorld, target, solution) == SolveResult::Converged,
            "convergence refused the reference case");
        Require(solution.residualDegrees < 0.05f,
            "fixed convergence still misaims on the reference case");
    }

    void TestTargetsAboveAndBelowThePlayer()
    {
        const Matrix mountWorld = MakeYawMatrix(0.35f, 1000.0, 20.0, -750.0);
        const Matrix mountLocal = MakePitchMatrix(0.08f);

        // Well above, well below, and level -- all inside the deviation stop, so
        // every one of them must actually solve.
        const float verticals[] = { 90.0f, -90.0f, 0.0f };
        for (const float vertical : verticals)
        {
            const Vec3 target = TargetOffBarrel(mountLocal, mountWorld, 220.0f, 5.0f, vertical);

            Solution solution = {};
            Require(Solve(mountLocal, mountWorld, target, solution) == SolveResult::Converged,
                "convergence refused a reachable vertical target");
            Require(solution.residualDegrees < 0.05f,
                "vertical target left a residual aim error");

            const Vec3 origin = FireOrigin(solution.mountLocal, mountWorld);
            Vec3 toTarget = { target.x - origin.x, target.y - origin.y, target.z - origin.z };
            Require(Normalize(toTarget), "muzzle-to-target vector was degenerate");
            RequireNear(AngleBetweenDegrees(FireDirection(solution.mountLocal, mountWorld), toTarget),
                0.0, 0.05, "vertical target was not fired through");
        }
    }

    void TestRotatingCraftKeepsConvergenceExact()
    {
        const Matrix mountLocal = MakePitchMatrix(-0.05f);

        for (int step = 0; step < 72; ++step)
        {
            const float yaw = static_cast<float>(step) * (3.14159265358979f / 36.0f);
            const Matrix mountWorld = MakeYawMatrix(yaw, 380.0, 10.0, 360.0);
            const Vec3 target = TargetOffBarrel(mountLocal, mountWorld, 250.0f, 18.0f, 9.0f);

            Solution solution = {};
            Require(Solve(mountLocal, mountWorld, target, solution) == SolveResult::Converged,
                "convergence refused a reachable target while the craft rotated");
            Require(solution.residualDegrees < 0.05f,
                "rotating the craft reintroduced an aim error");
        }
    }

    void TestSafetyStopsAndDegenerateInput()
    {
        const Matrix mountWorld = MakeYawMatrix(0.0f, 0.0, 0.0, 0.0);
        const Matrix mountLocal = Identity();

        Solution solution = {};
        Require(Solve(mountLocal, mountWorld, { 0.0f, 0.0f, 0.2f }, solution) ==
                SolveResult::TargetTooClose,
            "a target inside the muzzle was not rejected");

        Require(Solve(mountLocal, mountWorld, { 0.0f, 0.0f, -500.0f }, solution) ==
                SolveResult::ExceedsDeviationLimit,
            "a target directly behind the barrel was not rejected");

        Matrix broken = Identity();
        broken.rightX = 7.5f;  // not a rotation
        Require(Solve(mountLocal, broken, { 0.0f, 0.0f, 500.0f }, solution) ==
                SolveResult::DegenerateInput,
            "a non-orthonormal mount frame was accepted");

        Matrix notFinite = Identity();
        notFinite.frontZ = std::nanf("");
        Require(Solve(mountLocal, notFinite, { 0.0f, 0.0f, 500.0f }, solution) ==
                SolveResult::DegenerateInput,
            "a non-finite mount frame was accepted");
    }
}

int main()
{
    TestMultiplyMatchesEngineConvention();
    TestInvertRoundTrips();
    TestArcRotationCarriesFrontOntoTarget();
    TestArcRotationHandlesAlignedAndReversed();
    TestConvergenceAimsThroughTheReticleFromADistantRotatedCraft();
    TestConvergencePreservesTheHardpointPosition();
    TestMuzzleIsWorldSpaceNotMountLocal();
    TestPreFixBehaviourIsRejected();
    TestTargetsAboveAndBelowThePlayer();
    TestRotatingCraftKeepsConvergenceExact();
    TestSafetyStopsAndDegenerateInput();
    std::printf("weapon_convergence_tests: all checks passed\n");
    return 0;
}
