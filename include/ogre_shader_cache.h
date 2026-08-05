#pragma once

namespace BZROpenShim
{
    // Ogre GpuProgram microcode cache bridge. Fixes the ~30 second stall when
    // leaving a multiplayer game: every "Modable" resource-group reinit
    // (mission load AND leave-game back to shell) recompiles the mod's
    // enhanced-lighting ps_3_0 fragment shaders (MAX_LIGHTS=24 [unroll] plus
    // 4x4 PCF unrolls cost seconds of D3DXCompileShader each). With the
    // microcode cache enabled each unique program compiles at most once per
    // machine and is reloaded from disk on later launches.

    // Cheap trigger from the CreateFile hooks whenever any module opens an
    // Ogre *.program script: runs the one-time cache init (enable + load)
    // on the exact thread that is about to parse/compile, plus throttled
    // dirty saves afterwards.
    void OgreShaderCacheOnProgramScriptOpen();

    // Periodic trigger from the per-sim-tick hook (dirty save fallback).
    void OgreShaderCacheTick();
}
