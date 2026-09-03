#pragma once

#include <cstdint>

namespace BZROpenShim
{
    // Walker first-person cockpit jitter investigation instrument.
    //
    // Scope (see reverse_engineering/walker_jitter_expanded_result_20260902.md):
    // the expanded EXU bench proved only that the top-level vehicle world
    // transform is stable while stationary. It did NOT qualify the cockpit
    // ("_c") hierarchy, the POV node, or the camera path, and it did not
    // exercise real possessed motion. This instrument closes that gap.
    //
    // Design notes that matter:
    //  - Capture is frame-synchronous via a real Ogre::FrameListener registered
    //    on Root. A 60Hz polling thread reads the scene graph while the render
    //    thread mutates it, which manufactures false discontinuities -- exactly
    //    the artefact we are trying to measure. Do not "simplify" this back to
    //    a polling worker.
    //  - Entity identity is resolved by matching live SceneManager entity
    //    pointers against the fields of the local user GameObject, not by
    //    guessing "<odf>_c" mesh names. Name matching was what prevented the
    //    previous pass from resolving cockpit entities at all.
    //  - The visible defect is a per-frame discontinuity, so the reported
    //    statistic is jerk (the second difference of each transform), tracked
    //    per link of the chain. The first link whose jerk spikes is the first
    //    incorrect writer's output.
    void InitializeWalkerCockpitTrace();

    // Stops frame capture and unregisters the frame listener.
    void ShutdownWalkerCockpitTrace();
}
