#pragma once
#include "frame_bridge_camera.h"
namespace BZROpenShim::FrameBridge
{
    // Read-only exported API observation on the game render thread. Returns a
    // candidate with no pass-identity guarantee. Missing APIs/faults fail closed.
    bool ObserveViewportCamera(CameraSnapshot& snapshot);
}
