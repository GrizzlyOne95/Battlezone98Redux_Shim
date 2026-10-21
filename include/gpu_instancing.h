#pragma once

namespace BZROpenShim
{
    // Experimental hardware instancing for GPU-skinned craft on Direct3D 11.
    //
    // Off unless [Experimental] GpuInstancing = 1 (or OPENSHIM_GPU_INSTANCING)
    // and GpuSkinning is active for the mission. Sub-entities that share a
    // mesh, a skinned material pass, a light list and a shadow role are drawn
    // as one instanced draw through the instanced twin of that pass (see
    // gpu_skinning.h); everything else renders exactly as before. Any fault
    // disables the feature for the rest of the process.
    // See reverse_engineering/gpu_instancing_design_20261021.md.

    void GpuInstancingNotifyMissionRunStateChanged(bool running);

    // Called from the render queue hook on the render thread, after
    // GpuSkinningRenderFrameTick. Installs the draw hooks once the skinning
    // layer has twins to offer; otherwise one load.
    void GpuInstancingRenderFrameTick();
}
