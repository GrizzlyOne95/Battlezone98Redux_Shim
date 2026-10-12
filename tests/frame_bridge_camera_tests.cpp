#include "frame_bridge_protocol.h"
#include "test_check.h"
#include <limits>
#include <cstring>
#include <utility>

int main()
{
    using namespace BZROpenShim::FrameBridge;
    using OpenShimTest::Check;
    float uiView[16]{}, uiProjection[16]{};
    uiView[0] = uiView[5] = uiView[10] = uiView[15] = 1;
    std::memcpy(uiProjection, uiView, sizeof(uiView)); uiProjection[10] = uiProjection[11] = 0.5f;
    Check(IdentityOverlayMatrices(uiView, uiProjection), "observed Ogre D3D identity overlay pair");
    uiView[3] = 1;
    Check(!IdentityOverlayMatrices(uiView, uiProjection), "translated world view is not overlay");
    uiView[3] = 0; uiProjection[14] = -1;
    Check(!IdentityOverlayMatrices(uiView, uiProjection), "perspective view is not overlay");
    CameraSnapshot camera{};
    Check(!ValidCameraSnapshot(camera), "missing camera is not fabricated identity");
    camera.status = static_cast<std::uint32_t>(CameraStatus::Observed);
    camera.matrixSource = static_cast<std::uint32_t>(CameraMatrixSource::Synthetic);
    camera.width = 1600; camera.height = 900;
    camera.cameraIdentity = 1234; camera.observationQpc = 42;
    constexpr char fixtureName[] = "SyntheticCamera";
    std::memcpy(camera.name, fixtureName, sizeof(fixtureName));
    camera.view[0] = camera.view[5] = camera.view[10] = camera.view[15] = 1;
    camera.nearClip = 0.1f; camera.farClip = 100;
    const float q = camera.farClip / (camera.farClip - camera.nearClip);
    camera.projection[0] = 1.125f; camera.projection[5] = 2;
    camera.projection[10] = -q; camera.projection[11] = -q * camera.nearClip; camera.projection[14] = -1;
    Check(ValidCameraSnapshot(camera), "finite row-major camera observation");
    auto facts = InspectPerspective(camera);
    Check(facts.recognized && !facts.reversed && facts.forwardSign == -1 &&
        std::fabs(facts.aspect - 16.0 / 9.0) < 0.000001 && facts.verticalFovDegrees > 50 && facts.verticalFovDegrees < 55,
        "D3D right-handed perspective matches near/far device depth");
    auto changed = camera;
    changed.matrixSource = 0;
    Check(!ValidCameraSnapshot(changed), "unknown matrix convention is rejected");
    changed.matrixSource = 4;
    Check(!ValidCameraSnapshot(changed), "unsupported matrix convention is rejected");
    changed = camera;
    changed.matrixSource = static_cast<std::uint32_t>(CameraMatrixSource::CameraForShaders);
    Check(ValidCameraSnapshot(changed), "explicit shader camera convention");
    Check(std::strcmp(CameraMatrixSourceName(changed.matrixSource), "camera-for-shaders") == 0,
        "shader baseline retains convention in artifacts");
    changed = camera;
    changed.projection[10] *= -1; changed.projection[14] *= -1;
    facts = InspectPerspective(changed);
    Check(facts.recognized && facts.forwardSign == 1 && !facts.reversed, "recognize left-handed projection from positive clip w");
    changed = camera;
    changed.projection[10] = camera.nearClip / (camera.farClip - camera.nearClip);
    changed.projection[11] = q * camera.nearClip;
    Check(InspectPerspective(changed).recognized && InspectPerspective(changed).reversed, "recognize reversed depth from endpoints");
    changed = camera; changed.farClip = 0;
    changed.projection[10] = -1; changed.projection[11] = -changed.nearClip;
    Check(InspectPerspective(changed).recognized && !InspectPerspective(changed).reversed, "infinite far projection");
    changed.projection[10] = 0; changed.projection[11] = changed.nearClip;
    Check(InspectPerspective(changed).recognized && InspectPerspective(changed).reversed, "infinite reversed projection");
    changed = camera; std::swap(changed.projection[11], changed.projection[14]);
    Check(!InspectPerspective(changed).recognized, "reject transposed matrix convention");
    changed = camera; changed.projection[2] = 0.2f;
    Check(!InspectPerspective(changed).recognized, "asymmetric/oblique projection remains unqualified");
    changed = camera; changed.nearClip = 2;
    Check(!InspectPerspective(changed).recognized, "clip constants must match matrix endpoints");
    changed = camera; changed.farClip = changed.nearClip;
    Check(!ValidCameraSnapshot(changed), "invalid clip interval");
    changed = camera; changed.view[0] = std::numeric_limits<float>::quiet_NaN();
    Check(!ValidCameraSnapshot(changed), "reject nonfinite camera values");
    changed = camera; changed.view[0] = 0;
    Check(!ValidCameraSnapshot(changed), "singular camera transform");
    changed = camera;
    for (float& value : changed.projection) value = 0;
    Check(!ValidCameraSnapshot(changed), "reject uninitialized zero projection");
    changed = camera; changed.projection[0] = 0;
    Check(!ValidCameraSnapshot(changed), "reject singular projection with valid clip constants");
    changed = camera; changed.view[12] = 3;
    Check(!ValidCameraSnapshot(changed), "view is not row-major affine");
    changed = camera; changed.name[63] = 'X';
    Check(!ValidCameraSnapshot(changed), "wire name must terminate");
    changed = camera; changed.name[0] = '"';
    Check(!ValidCameraSnapshot(changed), "wire name sanitization");
    SharedFrame frame{};
    frame.width = camera.width; frame.height = camera.height;
    frame.captureQpc = camera.observationQpc;
    frame.depthTextureHandle = 1; frame.depthStatus = static_cast<std::uint32_t>(DepthStatus::Candidate);
    frame.depthSourceFormat = 45; frame.depthSourceSamples = 8;
    frame.depthCapturedOrdinal = 2; frame.depthMatchingClears = 3;
    frame.camera = camera; frame.camera.stage = 1; frame.camera.clearOrdinal = 2;
    Check(ValidCameraFrame(frame), "matched camera/depth dimensions and observation boundary");
    frame.sceneColorHandle = 7;
    frame.sceneColorStatus = static_cast<std::uint32_t>(SceneColorStatus::Candidate);
    frame.sceneColorCapturedOrdinal = 2;
    frame.sceneColorSource = static_cast<std::uint32_t>(SceneColorSource::BoundTarget);
    Check(ValidSceneColorFrame(frame), "scene color/depth/camera share pre-clear boundary");
    frame.sceneColorSource = 3;
    Check(!ValidSceneColorFrame(frame), "unknown scene color source invalid");
    frame.sceneColorSource = static_cast<std::uint32_t>(SceneColorSource::PresentBackbuffer);
    Check(ValidSceneColorFrame(frame), "explicit known present source");
    frame.sceneColorCapturedOrdinal = 3;
    Check(!ValidSceneColorFrame(frame), "scene color from another boundary is invalid");
    frame.sceneColorCapturedOrdinal = 2;
    frame.sceneColorStatus = static_cast<std::uint32_t>(SceneColorStatus::Missing);
    Check(!ValidSceneColorFrame(frame), "stale scene pixels cannot remain valid");
    ++frame.camera.observationQpc;
    Check(!ValidCameraFrame(frame), "camera observation cannot occur after its captured color frame");
    --frame.camera.observationQpc;
    frame.camera.clearOrdinal = 3;
    Check(!ValidCameraFrame(frame), "reject camera from different boundary");
    frame.camera.clearOrdinal = 2; frame.camera.width /= 2;
    Check(!ValidCameraFrame(frame), "reject satellite-sized camera for full-size depth");
    frame.camera.width = frame.width; frame.depthStatus = static_cast<std::uint32_t>(DepthStatus::Missing);
    Check(!ValidCameraFrame(frame), "missing depth invalidates paired camera");
    return OpenShimTest::ExitCode();
}
