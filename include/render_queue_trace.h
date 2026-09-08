#pragma once

namespace BZROpenShim
{
    // Diagnostic: records the render queue groups Ogre actually processes per
    // frame, and the invocation each belongs to.
    //
    // This exists to answer one question nothing in the repo could answer by
    // inspection: is there a point inside Ogre's scene render that comes after
    // the opaque world and before the cockpit and HUD? A compositor pass
    // (interactive fog, contract item 6 of Docs/INTERACTIVE_FOG_WAKES.md) needs
    // such a point, and the two render hooks OpenShim already owns are both on
    // the wrong side of it -- the world _updateRenderQueue hook runs during
    // visibility gathering, before any draw, and the Enhanced FXAA pass runs
    // immediately before Present, after everything including the HUD.
    //
    // Off unless [Diagnostics] TraceRenderQueues = 1 (or
    // OPENSHIM_TRACE_RENDER_QUEUES). Registers an Ogre RenderQueueListener,
    // logs a bounded number of frames, then deregisters itself.
    //
    // The caller supplies the scene manager because the qualified accessor for
    // it lives in bzr_hooks.cpp. Cheap and latched when the key is off.
    void RenderQueueTraceTick(void* sceneManager);

    // Deregisters the listener from the scene manager it was attached to.
    // Safe to call when nothing was ever registered.
    void RenderQueueTraceShutdown();
}
