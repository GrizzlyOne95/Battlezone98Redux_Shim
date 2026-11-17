// Tests for the classLabel=tracked contact model (include/tracked_vehicle_physics.h).
//
// Each scenario runs the pure step through a plain semi-implicit integrator
// with the orientation held fixed, which is enough to pin how the hull sits,
// drives, pivots and refuses to strafe without the engine.

#include "tracked_vehicle_physics.h"

#include <cmath>
#include <cstdio>
#include <cstring>
#include "test_check.h"

using OpenShimTest::Check;

namespace
{
    using namespace BZROpenShim::TrackedPhysics;

    struct Terrain
    {
        double slopeZ = 0.0;   // height = base + slopeZ * z + slopeX * x - crownZ * z^2
        double slopeX = 0.0;
        double crownZ = 0.0;
        double base = 0.0;
        double ceiling = 1.0e9; // sampling fails above |x| or |z| past this
    };

    bool FloorAt(void* context, double x, double /*y*/, double z, double& height, Vec3& normal)
    {
        const auto* terrain = static_cast<const Terrain*>(context);
        if (std::fabs(x) > terrain->ceiling || std::fabs(z) > terrain->ceiling)
            return false;
        height = terrain->base + terrain->slopeZ * z + terrain->slopeX * x - terrain->crownZ * z * z;
        normal = NormalizeOr({ static_cast<float>(-terrain->slopeX), 1.0f,
                               static_cast<float>(-(terrain->slopeZ - 2.0 * terrain->crownZ * z)) },
                             { 0.0f, 1.0f, 0.0f });
        return true;
    }

    void CheckNear(double actual, double expected, double tolerance, const char* message)
    {
        if (!(std::fabs(actual - expected) <= tolerance))
        {
            OpenShimTest::Fail("%s (actual=%.6f expected=%.6f)", message, actual, expected);
        }
    }

    struct Run
    {
        Body body;
        Result last;
        double minY = 1.0e9;
        double maxY = -1.0e9;
    };

    // Steps `seconds` of simulation; the y range is tracked over the final
    // `settleWindow` seconds only.
    Run Simulate(Body body, const Terrain& terrain, const Inputs& inputs, float dt, float seconds,
                 float settleWindow = 1.0f, Config config = Config{})
    {
        Run run;
        const Footprint footprint{};
        const Drive drive{};
        const int steps = static_cast<int>(std::lround(seconds / dt));
        const int windowStart = steps - static_cast<int>(std::lround(settleWindow / dt));
        for (int i = 0; i < steps; ++i)
        {
            run.last = Step(config, footprint, drive, body, inputs, dt, &FloorAt,
                            const_cast<Terrain*>(&terrain));
            body.veloc = Add(run.last.veloc, Scale(run.last.accel, dt));
            body.omega = Add(body.omega, Scale(run.last.alpha, dt));
            body.px += body.veloc.x * dt;
            body.py += body.veloc.y * dt;
            body.pz += body.veloc.z * dt;
            if (i >= windowStart)
            {
                if (body.py < run.minY) run.minY = body.py;
                if (body.py > run.maxY) run.maxY = body.py;
            }
        }
        run.body = body;
        return run;
    }

    void TestHashesMatchParameterDb()
    {
        static_assert(OdfHash("GameObjectClass") == 0xD3DD9CECu, "section hash");
        static_assert(OdfHash("classLabel") == 0x92D04727u, "key hash");
        static_assert(OdfHash("BuildingClass") == 0x91E9360Fu, "case folding");
        Check(OdfHash("TRACKEDCLASS") == OdfHash("TrackedClass"), "hash folds case");
    }

    void TestRestsOnFlatGroundWithoutBobbing()
    {
        const Terrain flat{};
        const float steps[] = { 0.1f, 1.0f / 30.0f, 1.0f / 60.0f };
        for (float dt : steps)
        {
            Body body;
            body.py = 1.0;  // dropped from a metre
            const Run run = Simulate(body, flat, Inputs{}, dt, 4.0f);
            const double expectedSink = kGravity / Config{}.stiffness;
            CheckNear(run.body.py, -expectedSink, 0.01, "settles at the spring's static sink");
            Check(run.maxY - run.minY < 0.005, "no bob once settled");
            CheckNear(run.body.veloc.y, 0.0, 0.01, "no vertical drift at rest");
            Check(run.last.groundedContacts == 6, "all six default contacts touch flat ground");
        }
    }

    void TestAirborneFallsFreely()
    {
        const Terrain flat{};
        Body body;
        body.py = 50.0;
        const Result r = Step(Config{}, Footprint{}, Drive{}, body, Inputs{ 1.0f, 1.0f }, 0.1f,
                              &FloorAt, const_cast<Terrain*>(&flat));
        Check(r.groundedContacts == 0, "no contact in the air");
        CheckNear(r.accel.y, -kGravity, 1e-5, "gravity only in the air");
        CheckNear(r.accel.x, 0.0, 1e-6, "no thrust in the air");
        CheckNear(r.accel.z, 0.0, 1e-6, "no thrust in the air");
    }

    void TestUnsampledTerrainIsAirborne()
    {
        Terrain edge{};
        edge.ceiling = 0.5;  // every contact lies outside the sampled area
        Body body;
        const Result r = Step(Config{}, Footprint{}, Drive{}, body, Inputs{}, 0.1f,
                              &FloorAt, &edge);
        Check(r.groundedContacts == 0, "unsampled terrain has no contact");
        CheckNear(r.accel.y, -kGravity, 1e-5, "unsampled terrain falls");
    }

    void TestDrivesForwardAndReverse()
    {
        const Terrain flat{};
        Body body;
        Run run = Simulate(body, flat, Inputs{ 1.0f, 0.0f }, 0.1f, 5.0f);
        CheckNear(run.body.veloc.z, Drive{}.velocForward, 0.05, "full throttle reaches velocForward");
        CheckNear(run.body.veloc.x, 0.0, 1e-4, "straight drive has no sideways speed");

        run = Simulate(body, flat, Inputs{ -1.0f, 0.0f }, 0.1f, 5.0f);
        CheckNear(run.body.veloc.z, -Drive{}.velocReverse, 0.05, "full reverse reaches velocReverse");
    }

    void TestThrustIsRateLimited()
    {
        const Terrain flat{};
        Body body;
        body.py = -kGravity / Config{}.stiffness;
        const Result r = Step(Config{}, Footprint{}, Drive{}, body, Inputs{ 1.0f, 0.0f }, 0.1f,
                              &FloorAt, const_cast<Terrain*>(&flat));
        CheckNear(r.accel.z, Drive{}.accelThrust, 1e-3, "pulling away is capped by accelThrust");
    }

    void TestPivotsAtStandstill()
    {
        const Terrain flat{};
        Body body;
        const Run run = Simulate(body, flat, Inputs{ 0.0f, 1.0f }, 0.1f, 3.0f);
        CheckNear(run.body.omega.y, Drive{}.omegaSpin, 0.01, "pivot spins at omegaSpin");
        CheckNear(Length(run.body.veloc), 0.0, 0.05, "pivot does not translate");
        Check(run.last.leftTread < 0.0f && run.last.rightTread > 0.0f, "treads counter-rotate in a pivot");
        CheckNear(run.last.leftTread, -run.last.rightTread, 1e-4, "pivot treads are equal and opposite");
    }

    void TestNeverStrafes()
    {
        const Terrain flat{};
        Body body;
        body.veloc = { 6.0f, 0.0f, 0.0f };  // shoved sideways
        const Run run = Simulate(body, flat, Inputs{ 0.0f, 0.0f }, 0.1f, 3.0f);
        CheckNear(run.body.veloc.x, 0.0, 0.01, "lateral friction kills sideways speed");

        Config slippery{};
        slippery.lateralFriction = 0.0f;
        const Run slide = Simulate(body, flat, Inputs{ 0.0f, 0.0f }, 0.1f, 1.0f, 1.0f, slippery);
        CheckNear(slide.body.veloc.x, 6.0, 0.01, "zero lateral friction lets it slide");
    }

    void TestTurningKeepsTurnRateUnderTheTreadLimit()
    {
        Drive drive{};
        float v = 0.0f, w = 0.0f;
        TreadCommand(drive, 2.0f, 1.0f, 1.0f, drive.velocForward, v, w);
        CheckNear(w, drive.omegaTurn, 1e-5, "full speed uses omegaTurn");
        CheckNear(v + w * 2.0f, drive.velocForward, 1e-4, "outer tread is held at velocForward");

        drive.omegaSpin = 50.0f;
        TreadCommand(drive, 2.0f, 0.0f, 1.0f, 0.0f, v, w);
        CheckNear(w * 2.0f, drive.velocReverse, 1e-4, "pivot clamps to the slower tread limit");
        CheckNear(v, 0.0, 1e-6, "clamped pivot has no forward speed");
    }

    Body OnSlope(double degrees)
    {
        const float a = static_cast<float>(degrees * 3.14159265358979 / 180.0);
        Body body;
        body.front = { 0.0f, std::sin(a), std::cos(a) };
        body.up = { 0.0f, std::cos(a), -std::sin(a) };
        body.py = -0.05;
        return body;
    }

    void TestHoldsOnAClimbableSlope()
    {
        Terrain hill{};
        hill.slopeZ = std::tan(20.0 * 3.14159265358979 / 180.0);
        const Run run = Simulate(OnSlope(20.0), hill, Inputs{}, 0.1f, 4.0f);
        CheckNear(Length(run.body.veloc), 0.0, 0.02, "parked on 20 degrees it stays put");
        CheckNear(run.last.slopeDeg, 20.0, 0.1, "footprint reads the slope");
        Check(run.last.traction > 0.99f, "full traction below maxSlope");
    }

    // Live failure: on a crowned side slope only the middle contacts touch,
    // and grip scaled by the touching fraction let the hull slide sideways.
    void TestHoldsACrownedSideSlopeOnFewContacts()
    {
        Terrain hill{};
        const double a = 20.0 * 3.14159265358979 / 180.0;
        hill.slopeX = std::tan(a);
        hill.crownZ = 0.05;
        Body body;
        body.right = { static_cast<float>(std::cos(a)), static_cast<float>(std::sin(a)), 0.0f };
        body.up = { static_cast<float>(-std::sin(a)), static_cast<float>(std::cos(a)), 0.0f };
        body.py = 0.0;
        const Run run = Simulate(body, hill, Inputs{}, 1.0f / 60.0f, 4.0f);
        Check(run.last.groundedContacts > 0 && run.last.groundedContacts < 6, "only some contacts touch");
        Check(run.last.traction > 0.95f, "the supported hull keeps full grip");
        CheckNear(Length(run.body.veloc), 0.0, 0.05, "parked across 20 degrees it does not slide");
    }

    void TestSlidesOffASteepSlope()
    {
        Terrain cliff{};
        cliff.slopeZ = std::tan(60.0 * 3.14159265358979 / 180.0);
        const Run run = Simulate(OnSlope(60.0), cliff, Inputs{ 1.0f, 0.0f }, 0.1f, 2.0f);
        Check(run.last.traction == 0.0f, "no traction past maxSlope + fade");
        Check(run.body.veloc.z < -1.0f, "it slides back down a 60 degree face");
    }

    void TestAlignsPitchTowardTheGround()
    {
        const Terrain flat{};
        Body body = OnSlope(10.0);  // nose up on flat ground
        body.py = -0.2;
        const Result r = Step(Config{}, Footprint{}, Drive{}, body, Inputs{}, 0.1f,
                              &FloorAt, const_cast<Terrain*>(&flat));
        Check(r.groundedContacts > 0, "the low end is on the ground");
        Check(r.alpha.x < 0.0f, "nose-up on flat ground pitches the nose down");
        CheckNear(r.alpha.z, 0.0, 1e-5, "no roll without a sideways tilt");
    }

    void TestDeterministic()
    {
        Terrain hill{};
        hill.slopeZ = 0.2;
        Body body = OnSlope(5.0);
        body.py = 2.0;
        const Run a = Simulate(body, hill, Inputs{ 0.7f, -0.3f }, 1.0f / 60.0f, 3.0f);
        const Run b = Simulate(body, hill, Inputs{ 0.7f, -0.3f }, 1.0f / 60.0f, 3.0f);
        Check(std::memcmp(&a.body, &b.body, sizeof(Body)) == 0, "identical inputs give identical state");
    }

    void TestConfigAndFootprintAreSanitized()
    {
        Config c{};
        c.contactsPerSide = 1;
        c.stiffness = -5.0f;
        c.maxSlopeDeg = std::nanf("");
        const Config s = Sanitize(c);
        Check(s.contactsPerSide == 2, "at least two contacts per side");
        Check(s.stiffness >= 10.0f, "stiffness floor");
        CheckNear(s.maxSlopeDeg, Config{}.maxSlopeDeg, 1e-6, "non-finite slope keeps the default");
        c.contactsPerSide = 40;
        Check(Sanitize(c).contactsPerSide == kMaxContactsPerSide, "contacts per side capped");

        const Footprint bad = FootprintFromBox({ 0.0f, 0.0f, 0.0f }, { 0.1f, 0.1f, 0.1f });
        CheckNear(bad.halfWidth, Footprint{}.halfWidth, 1e-6, "tiny box keeps the default footprint");
        const Footprint box = FootprintFromBox({ -2.0f, -0.5f, -4.0f }, { 2.0f, 1.5f, 4.0f });
        CheckNear(box.halfWidth, 1.7, 1e-5, "treads at 85% of the half width");
        CheckNear(box.backZ, -3.2, 1e-5, "rows inset 10% from the back");
        CheckNear(box.frontZ, 3.2, 1e-5, "rows inset 10% from the front");
        CheckNear(box.bottomY, -0.5, 1e-6, "contacts on the box bottom");
    }

    // The live failure: the engine held the hull in place while its
    // velocity kept growing. Pinning the position each step must not let
    // the velocity build up.
    void TestPinnedHullDoesNotAccumulateVelocity()
    {
        const Terrain flat{};
        const float dt = 1.0f / 30.0f;
        Body body;
        body.py = -0.01;
        Result r{};
        for (int i = 0; i < 300; ++i)
        {
            r = Step(Config{}, Footprint{}, Drive{}, body, Inputs{}, dt, &FloorAt, const_cast<Terrain*>(&flat));
            body.veloc = Add(r.veloc, Scale(r.accel, dt));
            // position not integrated: the engine clamp holds it
        }
        Check(r.groundedContacts == 6, "pinned hull stays grounded");
        Check(Length(body.veloc) < 0.5f, "velocity does not grow while the hull is held");
    }

    void TestIntoGroundVelocityRemovedAndCapped()
    {
        const Terrain flat{};
        Body body;
        body.py = -0.01;
        body.veloc = { 3.0f, -30.0f, 0.0f };
        const Result grounded = Step(Config{}, Footprint{}, Drive{}, body, Inputs{}, 0.1f,
                                     &FloorAt, const_cast<Terrain*>(&flat));
        Check(grounded.groundedContacts > 0, "hull touches the ground");
        CheckNear(grounded.veloc.y, 0.0, 1e-5, "no velocity into the ground while grounded");
        CheckNear(grounded.veloc.x, 3.0, 1e-5, "velocity along the ground is kept");

        body.py = 50.0;
        body.veloc = { 0.0f, -200.0f, 0.0f };
        const Result falling = Step(Config{}, Footprint{}, Drive{}, body, Inputs{}, 0.1f,
                                    &FloorAt, const_cast<Terrain*>(&flat));
        Check(falling.groundedContacts == 0, "airborne");
        CheckNear(falling.veloc.y, -kMaxFallSpeed, 1e-4, "fall speed capped");

        body.veloc = { 400.0f, 0.0f, 0.0f };
        const Result fast = Step(Config{}, Footprint{}, Drive{}, body, Inputs{}, 0.1f,
                                 &FloorAt, const_cast<Terrain*>(&flat));
        CheckNear(Length(fast.veloc), kMaxSpeed, 1e-3, "total speed capped");

        body.veloc = { std::nanf(""), 0.0f, 0.0f };
        const Result bad = Step(Config{}, Footprint{}, Drive{}, body, Inputs{}, 0.1f,
                                &FloorAt, const_cast<Terrain*>(&flat));
        Check(Finite(bad.veloc) && Length(bad.veloc) == 0.0f, "non-finite velocity resets to zero");
    }

    void TestContactBottomKeepsTheEngineProbeAboveGround()
    {
        const Config config{};
        const float bottom = ContactBottom(-0.5f, 0.0f, config);
        Check(bottom < -0.5f, "contacts sit below the engine's collision-box bottom");
        CheckNear(ContactBottom(std::nanf(""), 0.2f, config), 0.2f + (bottom + 0.5f), 1e-5,
                  "non-finite engine bottom uses the fallback");
        CheckNear(ContactBottom(1.0e9f, 0.2f, config), ContactBottom(0.2f, 0.0f, config), 1e-6,
                  "implausible engine bottom uses the fallback");

        // Resting on flat ground, the engine probe (origin + engine bottom)
        // stays above the floor.
        const Terrain flat{};
        Footprint footprint{};
        footprint.bottomY = bottom;
        Body body;
        body.py = 1.0;
        const float dt = 1.0f / 60.0f;
        Result r{};
        for (int i = 0; i < 600; ++i)
        {
            r = Step(config, footprint, Drive{}, body, Inputs{}, dt, &FloorAt, const_cast<Terrain*>(&flat));
            body.veloc = Add(r.veloc, Scale(r.accel, dt));
            body.py += body.veloc.y * dt;
        }
        Check(r.groundedContacts == 6, "settled on its contacts");
        Check(body.py + -0.5 > 0.0, "engine probe above the floor at rest");
        Check(body.py + -0.5 < 0.05, "and close to it");
    }

    void TestPerformanceCurve()
    {
        CheckNear(PerformanceScale(1.0f), 1.0, 1e-6, "healthy");
        CheckNear(PerformanceScale(0.5f), 1.0, 1e-6, "half health still full");
        CheckNear(PerformanceScale(0.25f), 0.875, 1e-6, "quarter health");
        CheckNear(PerformanceScale(0.0f), 0.5, 1e-6, "no health");
        CheckNear(PerformanceScale(-1.0f), 0.0, 1e-6, "negative");
    }
}

int main()
{
    TestHashesMatchParameterDb();
    TestRestsOnFlatGroundWithoutBobbing();
    TestAirborneFallsFreely();
    TestUnsampledTerrainIsAirborne();
    TestDrivesForwardAndReverse();
    TestThrustIsRateLimited();
    TestPivotsAtStandstill();
    TestNeverStrafes();
    TestTurningKeepsTurnRateUnderTheTreadLimit();
    TestHoldsOnAClimbableSlope();
    TestHoldsACrownedSideSlopeOnFewContacts();
    TestSlidesOffASteepSlope();
    TestAlignsPitchTowardTheGround();
    TestDeterministic();
    TestConfigAndFootprintAreSanitized();
    TestPinnedHullDoesNotAccumulateVelocity();
    TestIntoGroundVelocityRemovedAndCapped();
    TestContactBottomKeepsTheEngineProbeAboveGround();
    TestPerformanceCurve();
    if (OpenShimTest::ExitCode() == 0)
        std::printf("tracked_vehicle_physics_tests: all checks passed\n");
    return OpenShimTest::ExitCode();
}
