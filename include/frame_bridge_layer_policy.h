#pragma once
#include <cstdint>
namespace BZROpenShim::FrameBridge
{
    struct WorldEffectFacts
    {
        bool requested=false, qualifiedApis=false, effectProgram=false, boundShaderMatches=false;
        bool identityOverlay=true, immediate=false, depthEnabled=false, depthWrites=true;
        bool blendEnabled=false, alphaToCoverage=true, viewportMatches=false, targetMatches=false;
        std::uint32_t sourceBlend=0,destinationBlend=0,blendOperation=0,colorWriteMask=0;
    };
    // Reference-only draw omission, not an opacity mask or playable renderer.
    // Terrain/glow blends write depth; sky and HUD use other program/matrix
    // policies. Decline unknown programs, APIs, targets and blend modes.
    inline bool SuppressWorldEffectReference(const WorldEffectFacts& f)
    {
        return f.requested&&f.qualifiedApis&&f.effectProgram&&f.boundShaderMatches&&!f.identityOverlay&&f.immediate&&
            f.depthEnabled&&!f.depthWrites&&f.blendEnabled&&!f.alphaToCoverage&&f.viewportMatches&&f.targetMatches&&
            f.sourceBlend==5&&(f.destinationBlend==6||f.destinationBlend==2)&&f.blendOperation==1&&f.colorWriteMask==15;
    }
}
