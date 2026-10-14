#include "planet_video_policy.h"
#include <cstdio>
#include <cstdlib>
#include <limits>

using namespace BZROpenShim::PlanetVideo;
static void Check(bool ok, const char* message)
{
    if (!ok) { std::fprintf(stderr, "%s\n", message); std::exit(1); }
}

int main()
{
    Config config;
    std::string error;
    Check(Parse("\xEF\xBB\xBF[PlanetVideo]\r\nLoopStartSeconds=6.4 ; Moon\r\nIntroSound=\"emspin.wav\"\r\nStartAtLoop=0", config, error), "Moon sidecar rejected");
    Check(config.introSound == "emspin.wav" && !config.startAtLoop, "intro settings not preserved");
    int frame = -1;
    Check(LoopFrame(config, 15, 155, frame) && frame == 96, "stock Moon timing wrong");
    Check(LoopFrame(config, 30, 310, frame) && frame == 192, "30 fps Moon timing wrong");
    Check(LoopFrame(config, 60, 620, frame) && frame == 384, "60 fps Moon timing wrong");
    Check(LoopFrame(config, 30000.0 / 1001, 310, frame) && frame == 192, "fractional FPS rounding wrong");
    Check(!LoopFrame(config, 15, 96, frame), "EOF loop accepted");
    Check(!LoopFrame(config, 0, 155, frame), "zero FPS accepted");
    Check(!LoopFrame(config, std::numeric_limits<double>::infinity(), 155, frame), "infinite FPS accepted");
    Check(!LoopFrame(config, 15, 0, frame), "empty video accepted");

    for (const char* bad : {
        "[PlanetVideo]\nLoopStartSeconds=-1", "[PlanetVideo]\nLoopStartSeconds=nan",
        "[PlanetVideo]\nLoopStartSeconds=inf", "[PlanetVideo]\nLoopStartSeconds=1e9999",
        "[PlanetVideo]\nLoopStartSeconds=6.4junk", "[PlanetVideo]\nLoopStartSeconds=6,4",
        "[PlanetVideo]\nLoopStartSeconds=", "[PlanetVideo]\nLoopStartSeconds=1\nStartAtLoop=yes",
        "[PlanetVideo]\nLoopStartSeconds=1\nIntroSound=../outside.wav",
        "[PlanetVideo]\nLoopStartSeconds=1\nIntroSound=C:/outside.wav",
        "[PlanetVideo]\nLoopStartSeconds=1\nIntroSound=audio.ogg",
        "[PlanetVideo]\nLoopStartSeconds=1\nLoopStartSeconds=2",
        "[PlanetVideo]\nLoopStartSeconds=1\n[PlanetVideo]\nStartAtLoop=1",
        "[PlanetVideo]\nLoopStartSeconds=1\nTypo=2", "[PlanetVideo]\nStartAtLoop=1",
        "[Other]\nLoopStartSeconds=1", "[PlanetVideo\nLoopStartSeconds=1" })
    {
        const auto oldSeconds = config.loopStartSeconds;
        Check(!Parse(bad, config, error) && !error.empty(), bad);
        Check(config.loopStartSeconds == oldSeconds && config.introSound == "emspin.wav", "invalid parse changed output");
    }
    Check(!Parse(std::string(kMaxConfigBytes + 1, 'x'), config, error), "oversized file accepted");
    Check(!Parse(std::string("[PlanetVideo]\nLoopStartSeconds=0\0", 33), config, error), "binary file accepted");
    Check(Parse("[Other]\nUnrelated=ok\n[planetvideo]\nloopstartseconds=0\nstartatloop=1\nintrosound=\"\"", config, error), "case-insensitive minimal loop rejected");
    Check(config.startAtLoop && config.introSound.empty() && LoopFrame(config, 60, 120, frame) && frame == 0, "spin-only loop wrong");
    Check(SidecarName("crmoon.ogv") == "crmoon.pvi", "sidecar derivation wrong");
    Check(SidecarName("crMoon.OGV") == "crMoon.pvi", "sidecar case not preserved");
    for (const char* bad : {"../moon.ogv", "path/moon.ogv", "C:\\moon.ogv", "moon.mp4", ".ogv", "moon..ogv"})
        Check(SidecarName(bad).empty(), "non-flat video resource accepted");
    std::puts("planet video policy tests passed");
}
