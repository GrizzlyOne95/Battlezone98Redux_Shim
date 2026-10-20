#pragma once
#include "frame_bridge_camera.h"
namespace BZROpenShim::FrameBridge
{
    // Read-only exported API observation on the game render thread. Returns a
    // candidate with no pass-identity guarantee. Missing APIs/faults fail closed.
    bool ObserveViewportCamera(CameraSnapshot& snapshot);
    // Qualified named-export observers; default off and process-lifetime hooks.
    bool InstallIdentityOverlayObserver(void(*notify)(bool));
    // Qualified exported bound-program observation; no object field offsets.
    bool ObserveBoundEffectProgram(void*& pixelShader, std::uint32_t& width, std::uint32_t& height);
}
