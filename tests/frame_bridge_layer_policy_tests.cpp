#include "frame_bridge_layer_policy.h"
#include "test_check.h"
int main()
{
    using namespace BZROpenShim::FrameBridge;
    using OpenShimTest::Check;
    WorldEffectFacts f{};
    Check(!SuppressWorldEffectReference(f),"default off and unknown facts never suppress a draw");
    f.requested=f.qualifiedApis=f.effectProgram=f.boundShaderMatches=f.immediate=f.depthEnabled=f.blendEnabled=f.viewportMatches=f.targetMatches=true;
    f.identityOverlay=f.depthWrites=f.alphaToCoverage=false;
    f.sourceBlend=5; f.destinationBlend=6; f.blendOperation=1; f.colorWriteMask=15;
    Check(SuppressWorldEffectReference(f),"qualified world alpha effect selected for reference");
    auto g=f; g.destinationBlend=2; Check(SuppressWorldEffectReference(g),"qualified additive world effect selected");
    g=f; g.depthWrites=true; Check(!SuppressWorldEffectReference(g),"depth-writing terrain/glow blends remain");
    g=f; g.effectProgram=false; Check(!SuppressWorldEffectReference(g),"sky/terrain/unknown programs remain");
    g=f; g.identityOverlay=true; Check(!SuppressWorldEffectReference(g),"identity HUD effect remains");
    g=f; g.boundShaderMatches=false; Check(!SuppressWorldEffectReference(g),"stale engine program observation cannot suppress another shader");
    g=f; g.targetMatches=false; Check(!SuppressWorldEffectReference(g),"shadow and secondary targets remain");
    g=f; g.viewportMatches=false; Check(!SuppressWorldEffectReference(g),"partial viewport remains");
    g=f; g.qualifiedApis=false; Check(!SuppressWorldEffectReference(g),"unqualified DLL/API fails closed");
    g=f; g.depthEnabled=false; Check(!SuppressWorldEffectReference(g),"unqualified depth policy remains");
    g=f; g.alphaToCoverage=true; Check(!SuppressWorldEffectReference(g),"alpha coverage remains");
    g=f; g.destinationBlend=1; Check(!SuppressWorldEffectReference(g),"replace blend remains");
    g=f; g.colorWriteMask=7; Check(!SuppressWorldEffectReference(g),"partial color write remains");
    g=f; g.blendOperation=2; Check(!SuppressWorldEffectReference(g),"subtract blend remains");
    g=f; g.requested=false; Check(!SuppressWorldEffectReference(g),"ordinary gameplay never omits these effects");
    return OpenShimTest::ExitCode();
}
