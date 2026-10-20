#pragma once

namespace BZROpenShim
{
    // Experimental hardware skinning for skeletal craft on Direct3D 11.
    //
    // Off unless [Experimental] GpuSkinning = 1 (or OPENSHIM_GPU_SKINNING).
    // The setting is read when a mission starts, so a change applies on the
    // next mission load. Each eligible entity gets runtime clones of its
    // materials whose vertex programs (and shadow caster program) are
    // hardware-skinned twins of the installed ones; anything the transform
    // cannot prove compatible stays on Ogre's CPU path. Any fault disables the
    // feature for the rest of the process.
    //
    // Output is not bit-identical to the CPU path: shader float math reorders
    // the blend, so silhouettes can move by sub-pixel amounts.
    // See reverse_engineering/gpu_skinning_investigation_20261020.md.

    void GpuSkinningNotifyMissionRunStateChanged(bool running);

    // Called from the render queue hook on the render thread. Installs the
    // frame listener that does the work at frame start; otherwise one load.
    void GpuSkinningRenderFrameTick();
}
