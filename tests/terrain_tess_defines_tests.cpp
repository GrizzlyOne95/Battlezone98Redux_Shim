#include "terrain_tess_defines.h"
#include <iostream>
#include <stdexcept>
using namespace BZROpenShim;
static void check(bool ok, const char* message) { if (!ok) throw std::runtime_error(message); }
int main()
{
    try
    {
        const std::string source = "#if defined(SHADOWRECEIVER)\n#if defined(PSSM_ENABLED)\nfloat x = NUM_SPLITS;\n#ifdef FOG_EXP_X\n";
        check(TerrainTess::RelevantDefines("SHADOWRECEIVER=1,FOG_EXP=1,PSSM_ENABLED;NUM_SPLITS=3", source) ==
            "SHADOWRECEIVER=1,PSSM_ENABLED,NUM_SPLITS=3", "relevant defines not kept in order");
        check(TerrainTess::RelevantDefines("FOG_EXP=1, LIGHTMAP", source).empty(), "unmentioned defines kept");
        check(TerrainTess::RelevantDefines(" SHADOWRECEIVER = 1 ;;", source) == "SHADOWRECEIVER = 1", "blank tokens or padding mishandled");
        check(TerrainTess::RelevantDefines("", source).empty(), "empty defines not empty");
        check(!TerrainTess::MentionsIdentifier("XPSSM_ENABLED PSSM_ENABLEDX", "PSSM_ENABLED"), "partial identifier matched");
        check(TerrainTess::MentionsIdentifier("PSSM_ENABLED", "PSSM_ENABLED"), "whole source identifier missed");
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << "\n";
        return 1;
    }
    std::cout << "terrain_tess_defines_tests passed\n";
    return 0;
}
