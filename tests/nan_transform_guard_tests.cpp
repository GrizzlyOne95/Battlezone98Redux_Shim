#include "nan_transform_guard.h"

#include <cstdint>
#include <cstring>
#include <limits>
#include "test_check.h"

namespace
{
    using namespace BZROpenShim::NanTransform;

    struct Transform
    {
        float rot[9];
        float pad;
        double pos[3];
    };
    static_assert(sizeof(Transform) == kTransformBytes, "transform layout");

    Transform Good()
    {
        Transform t = {};
        const float r[9] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f };
        std::memcpy(t.rot, r, sizeof(r));
        t.pos[0] = 1200.5;
        t.pos[1] = 30.25;
        t.pos[2] = -800.0;
        return t;
    }

    uint8_t* Bytes(Transform& t) { return reinterpret_cast<uint8_t*>(&t); }

    const float kNanF = std::numeric_limits<float>::quiet_NaN();
    const float kInfF = std::numeric_limits<float>::infinity();
    const double kNanD = std::numeric_limits<double>::quiet_NaN();
    const double kInfD = std::numeric_limits<double>::infinity();

    bool IsIdentity(const Transform& t)
    {
        const float id[9] = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
        return std::memcmp(t.rot, id, sizeof(id)) == 0;
    }

    void TestBitTests()
    {
        CHECK(FiniteBits32(0x3F800000u));          // 1.0f
        CHECK(FiniteBits32(0x00000001u));          // denormal
        CHECK(!FiniteBits32(0x7F800000u));         // +inf
        CHECK(!FiniteBits32(0xFF800000u));         // -inf
        CHECK(!FiniteBits32(0x7FC00000u));         // NaN
        CHECK(FiniteBits64(0x3FF0000000000000ull));
        CHECK(!FiniteBits64(0x7FF0000000000000ull));
        CHECK(!FiniteBits64(0xFFF8000000000000ull));
    }

    void TestFiniteTransformUntouched()
    {
        Transform t = Good();
        Transform snap = Good();
        snap.pos[0] = 0.0;
        CHECK(RepairTransform(Bytes(t), Bytes(snap)) == Repair::None);
        CHECK(t.pos[0] == 1200.5);
        // Non-finite padding is not part of the transform.
        Transform p = Good();
        p.pad = kNanF;
        CHECK(TransformFinite(Bytes(p)));
    }

    void TestRotationNanRestoresSnapshot()
    {
        Transform snap = Good();
        Transform t = Good();
        t.rot[4] = kNanF;
        t.pos[1] = 99.0;
        CHECK(!RotationFinite(Bytes(t)));
        CHECK(RepairTransform(Bytes(t), Bytes(snap)) == Repair::RestoredSnapshot);
        CHECK(std::memcmp(&t, &snap, sizeof(t)) == 0);
    }

    void TestPositionInfRestoresSnapshot()
    {
        Transform snap = Good();
        Transform t = Good();
        t.pos[2] = -kInfD;
        CHECK(!PositionFinite(Bytes(t)));
        CHECK(RepairTransform(Bytes(t), Bytes(snap)) == Repair::RestoredSnapshot);
        CHECK(t.pos[2] == -800.0);
    }

    void TestSnapshotAlsoBad()
    {
        // Rotation bad, position fine, snapshot bad: identity, position kept.
        Transform snap = Good();
        snap.rot[0] = kInfF;
        Transform t = Good();
        t.rot[8] = kNanF;
        CHECK(RepairTransform(Bytes(t), Bytes(snap)) == Repair::IdentityRotation);
        CHECK(IsIdentity(t));
        CHECK(t.pos[0] == 1200.5);

        // Position bad and snapshot bad: rotation reset, position left as is.
        Transform t2 = Good();
        t2.rot[1] = kNanF;
        t2.pos[0] = kNanD;
        CHECK(RepairTransform(Bytes(t2), Bytes(snap)) == Repair::PositionNotFinite);
        CHECK(IsIdentity(t2));
        CHECK(t2.pos[0] != t2.pos[0]);

        // Only the position bad, snapshot bad: finite rotation is kept.
        Transform t3 = Good();
        t3.pos[1] = kInfD;
        const Transform before = t3;
        CHECK(RepairTransform(Bytes(t3), Bytes(snap)) == Repair::PositionNotFinite);
        CHECK(std::memcmp(t3.rot, before.rot, sizeof(t3.rot)) == 0);
    }

    void TestMotion()
    {
        uint8_t physics[kMotionEnd] = {};
        const float speed = 12.0f;
        const float v[3] = { 1.0f, -2.0f, 3.0f };
        const float w[3] = { 0.1f, 0.2f, 0.3f };
        std::memcpy(physics + kSpeedOffset, &speed, 4);
        std::memcpy(physics + kVelocityOffset, v, 12);
        std::memcpy(physics + kOmegaOffset, w, 12);
        CHECK(MotionFinite(physics));

        uint8_t bad[kMotionEnd];
        std::memcpy(bad, physics, sizeof(bad));
        std::memcpy(bad + kVelocityOffset + 4, &kNanF, 4);
        CHECK(!MotionFinite(bad));

        std::memcpy(bad, physics, sizeof(bad));
        std::memcpy(bad + kOmegaOffset + 8, &kInfF, 4);
        CHECK(!MotionFinite(bad));

        std::memcpy(bad, physics, sizeof(bad));
        std::memcpy(bad + kSpeedOffset, &kNanF, 4);
        CHECK(!MotionFinite(bad));

        ZeroMotion(bad);
        CHECK(MotionFinite(bad));
        float out[3] = { 9.0f, 9.0f, 9.0f };
        std::memcpy(out, bad + kVelocityOffset, 12);
        CHECK(out[0] == 0.0f && out[1] == 0.0f && out[2] == 0.0f);
    }
}

int main()
{
    TestBitTests();
    TestFiniteTransformUntouched();
    TestRotationNanRestoresSnapshot();
    TestPositionInfRestoresSnapshot();
    TestSnapshotAlsoBad();
    TestMotion();
    return OpenShimTest::ExitCode();
}
