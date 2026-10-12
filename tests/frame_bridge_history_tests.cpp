#include "frame_bridge_history.h"
#include "test_check.h"
#include <cstring>
#include <limits>

namespace
{
    using namespace BZROpenShim::FrameBridge;
    SharedFrame Fixture(std::uint64_t id, std::uint64_t qpc)
    {
        SharedFrame f{};
        f.magic = kMagic; f.version = kVersion; f.byteSize = sizeof(f); f.producerPid = 42;
        f.width = 100; f.height = 80; f.format = 28; f.textureHandle = 1; f.readyFenceHandle = 2;
        f.depthTextureHandle = 3; f.qpcFrequency = 1000; f.frameId = id; f.captureQpc = qpc;
        f.depthStatus = static_cast<std::uint32_t>(DepthStatus::Candidate); f.depthSourceFormat = 45; f.depthSourceSamples = 4;
        f.depthCapturedOrdinal = 2; f.depthMatchingClears = 3;
        auto& c = f.camera;
        c.status = static_cast<std::uint32_t>(CameraStatus::Observed);
        c.matrixSource = static_cast<std::uint32_t>(CameraMatrixSource::Synthetic);
        c.width = f.width; c.height = f.height; c.cameraIdentity = 7; c.observationQpc = qpc - 1;
        std::memcpy(c.name, "Fixture", 8);
        c.view[0] = c.view[5] = c.view[10] = c.view[15] = 1;
        c.nearClip = 0.1f; c.farClip = 100;
        c.projection[0] = 2; c.projection[5] = 2;
        c.projection[10] = -100.0f / 99.9f; c.projection[11] = c.projection[10] * c.nearClip;
        c.projection[14] = -1; c.stage = 1; c.clearOrdinal = 2;
        return f;
    }
}
int main()
{
    using OpenShimTest::Check;
    CameraHistory history;
    auto f = Fixture(1, 100);
    Check(history.Push(f).reason == HistoryReason::First, "first captured frame has no history");
    f = Fixture(2, 116);
    auto pair = history.Push(f);
    Check(pair.comparable && pair.previousFrame == 1 && pair.currentFrame == 2 &&
        std::fabs(pair.intervalSeconds - 0.016) < 1e-9, "owned consecutive captured pair");
    f.camera.view[3] = 99;
    Check(pair.current.view[3] == 0, "pair owns camera bytes");
    CameraReprojection motion;
    Check(motion.Prepare(pair), "prepare recognized perspective");
    const float z5 = pair.current.projection[11] / 5 - pair.current.projection[10];
    auto pixel = motion.Pixel(50, 40, z5);
    Check(pixel.valid == 1 && std::fabs(pixel.x) < 1e-5 && std::fabs(pixel.y) < 1e-5,
        "stationary camera gives zero motion at pixel centers");
    pair.current.view[3] = 1;
    Check(motion.Prepare(pair), "translated camera");
    pixel = motion.Pixel(50, 40, z5);
    Check(pixel.valid == 1 && std::fabs(pixel.x + 20) < 0.0001 && std::fabs(pixel.y) < 0.0001,
        "analytic lateral translation gives previous-minus-current pixel motion");
    pair.current.view[3] = 0; pair.current.view[7] = 1;
    Check(motion.Prepare(pair), "vertical camera translation");
    pixel = motion.Pixel(50, 40, z5);
    Check(pixel.valid == 1 && std::fabs(pixel.x) < 0.0001 && std::fabs(pixel.y - 16) < 0.0001,
        "top-down pixel Y differs from clip Y");
    Check(motion.Pixel(50, 40, 1).valid == 0, "clear background is invalid");
    Check(motion.Pixel(50, 40, -0.1f).valid == 0 &&
        motion.Pixel(50, 40, std::numeric_limits<float>::quiet_NaN()).valid == 0,
        "invalid depth cannot fabricate motion");
    Check(motion.Pixel(100, 40, z5).valid == 0, "reject coordinates outside capture");
    pair.current.view[7] = 100;
    Check(motion.Prepare(pair) && motion.Pixel(50, 40, z5).valid == 0, "offscreen prior projection invalid");
    pair.current.view[7] = 0; pair.previous.view[11] = 10;
    Check(motion.Prepare(pair) && motion.Pixel(50, 40, z5).valid == 0, "point behind previous camera invalid");
    pair.comparable = false;
    Check(!motion.Prepare(pair) && motion.Pixel(50, 40, z5).valid == 0, "failed preparation invalidates old transform");
    pair = {};
    pair.comparable = true; pair.previous = pair.current = Fixture(1, 100).camera;
    const double angle = 0.05, cosine = std::cos(angle), sine = std::sin(angle);
    pair.current.view[0] = pair.current.view[10] = static_cast<float>(cosine);
    pair.current.view[2] = static_cast<float>(sine); pair.current.view[8] = static_cast<float>(-sine);
    Check(motion.Prepare(pair), "rotated camera");
    pixel = motion.Pixel(50, 40, z5);
    const double cameraX = 0.01 * 5 / 2;
    const double worldX = cosine * cameraX + sine * 5;
    const double worldZ = sine * cameraX - cosine * 5;
    const double expectedX = (2 * worldX / -worldZ + 1) * 50 - 50.5;
    Check(pixel.valid == 1 && std::fabs(pixel.x - expectedX) < 0.0001, "rotation matches analytic ray reprojection");
    pair.previous = pair.current = Fixture(1, 100).camera;
    pair.previous.projection[10] = pair.current.projection[10] = 0.1f / 99.9f;
    pair.previous.projection[11] = pair.current.projection[11] = 10.0f / 99.9f;
    const float reversedZ = -pair.current.projection[10] + pair.current.projection[11] / 5;
    Check(motion.Prepare(pair) && motion.Pixel(50, 40, reversedZ).valid == 1 && motion.Pixel(50, 40, 0).valid == 0,
        "reversed depth excludes zero background");
    pair.previous = pair.current = Fixture(1, 100).camera;
    pair.previous.farClip = pair.current.farClip = 0;
    pair.previous.projection[10] = pair.current.projection[10] = -1;
    pair.previous.projection[11] = pair.current.projection[11] = -0.1f;
    Check(motion.Prepare(pair) && motion.Pixel(50, 40, 0.98f).valid == 1, "infinite far reprojection");
    pair.previous.matrixSource = pair.current.matrixSource = static_cast<std::uint32_t>(CameraMatrixSource::ViewportRS);
    Check(!motion.Prepare(pair), "old viewport convention is not a shader-motion baseline");
    pair.previous = pair.current = Fixture(1, 100).camera;
    ++pair.previous.width;
    Check(!motion.Prepare(pair), "mismatched extent cannot reproject");

    auto resetCase = [&](HistoryReason expected, auto mutate) {
        history.Clear(); auto first = Fixture(1, 100); history.Push(first);
        auto second = Fixture(2, 116); mutate(second);
        const auto result = history.Push(second);
        Check(!result.comparable && result.reason == expected, HistoryReasonName(expected));
    };
    resetCase(HistoryReason::Missing, [](auto& x) { x.depthStatus = static_cast<std::uint32_t>(DepthStatus::Missing); });
    resetCase(HistoryReason::Session, [](auto& x) { ++x.producerPid; });
    resetCase(HistoryReason::Session, [](auto& x) { ++x.textureHandle; });
    resetCase(HistoryReason::Session, [](auto& x) { ++x.depthTextureHandle; });
    resetCase(HistoryReason::Sequence, [](auto& x) { ++x.frameId; });
    resetCase(HistoryReason::Time, [](auto& x) { x.captureQpc = 100; x.camera.observationQpc = 99; });
    resetCase(HistoryReason::Time, [](auto& x) { x.captureQpc = 400; });
    resetCase(HistoryReason::Boundary, [](auto& x) { x.depthCapturedOrdinal = x.camera.clearOrdinal = 3; });
    resetCase(HistoryReason::Boundary, [](auto& x) { ++x.depthMatchingClears; });
    resetCase(HistoryReason::Convention, [](auto& x) { ++x.camera.cameraIdentity; });
    resetCase(HistoryReason::Convention, [](auto& x) { x.camera.name[0] = 'X'; });
    resetCase(HistoryReason::Convention, [](auto& x) { x.camera.projection[0] += 0.01f; });
    resetCase(HistoryReason::Convention, [](auto& x) { x.camera.matrixSource = static_cast<std::uint32_t>(CameraMatrixSource::CameraForShaders); });
    history.Clear(); history.Push(Fixture(1, 100));
    Check(history.Push(Fixture(2, 116), true).reason == HistoryReason::ExplicitReset, "explicit cut reset prevents pairing");
    auto missing = Fixture(3, 132); missing.camera = {};
    Check(history.Push(missing).reason == HistoryReason::Missing && history.Push(Fixture(4, 148)).reason == HistoryReason::First,
        "missing frame discards earlier camera history");
    return OpenShimTest::ExitCode();
}
