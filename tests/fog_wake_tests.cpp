#include "fog_wake.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <limits>

using namespace BZROpenShim::FogWake;
namespace {
    int failures = 0;
    void Check(bool value, const char* message) {
        if (!value) { std::fprintf(stderr, "FAIL: %s\n", message); ++failures; }
    }
    bool Near(double a, double b) { return std::abs(a-b) < 1e-5; }
}
int main()
{
    Field f;
    Check(!f.Stamp({}, {}, 2, 1), "unconfigured field refuses work");
    Config c;
    c.width=32; c.height=24; c.origin={-16,-12};
    Check(f.Configure(c), "configure fixed world region");
    Check(f.Stamp({-10.5,0.5},{10.5,0.5},2,1), "stamp a fast vehicle sweep");
    for (int x=-10; x<=10; ++x)
        Check(Near(f.Sample({x+0.5,0.5}),1), "continuous corridor without endpoint gaps");
    Check(Near(f.Sample({0.5,1.5}),0.5), "soft capsule edge");
    Check(f.Sample({0.5,3.5})==0, "fog outside corridor unchanged");
    auto original=f.Clearance();
    f.Stamp({-10.5,0.5},{10.5,0.5},2,1);
    Check(f.Clearance()==original, "repeated stamps do not increase strength");
    Check(!f.Stamp({0,0},{100,0},2,1), "teleports cannot carve long trails");
    Check(f.Clearance()==original, "rejected teleport leaves field unchanged");
    const double nan=std::numeric_limits<double>::quiet_NaN();
    Check(!f.Stamp({nan,0},{0,0},2,1), "NaN vehicle positions rejected");
    Check(!f.Advance(-1,{}), "negative timestep rejected");
    Check(!f.Advance(1,{nan,0}), "NaN wind rejected");
    Config bad=c; bad.width=0;
    Check(!f.Configure(bad) && f.Clearance()==original, "bad config preserves region");
    Check(f.Advance(4,{}), "refill update");
    Check(Near(f.Sample({0.5,0.5}),std::exp(-1.0)), "specified recovery time is exponential");
    Field split; split.Configure(c); split.Stamp({-10.5,0.5},{10.5,0.5},2,1);
    for(int i=0;i<40;++i) split.Advance(0.1,{});
    Check(Near(f.Sample({0.5,0.5}),split.Sample({0.5,0.5})), "refill independent of timestep partition");
    f.Reset();
    f.Stamp({0.5,0.5},{0.5,0.5},0.75,1);
    f.Advance(1,{2,0});
    Check(Near(f.Sample({2.5,0.5}),std::exp(-0.25)), "wind carries wake in correct world direction");
    Check(f.Sample({0.5,0.5})==0, "wind vacates original cell");
    f.Reset(); f.Stamp({-16,0.5},{-10,0.5},2,1);
    Check(f.Sample({-15.5,0.5})>0, "partially outside stamps clipped correctly");
    f.Advance(1,{-100,0});
    Check(std::all_of(f.Clearance().begin(),f.Clearance().end(),[](float v){return v==0;}),
        "outflow leaves region without wraparound");
    f.Stamp({1e8,1e8},{1e8,1e8},2,1);
    Check(f.Sample({0,0})==0, "distant stamp does not alias grid");
    f.Stamp({0.5,0.5},{0.5,0.5},3,2);
    f.Advance(0.3,{0.37,-0.29});
    Check(std::all_of(f.Clearance().begin(),f.Clearance().end(),[](float v){
        return std::isfinite(v)&&v>=0&&v<=1;}), "fractional transport stays finite and bounded");
    f.Reset();
    Check(f.Sample({0.5,0.5})==0, "session reset clears all history");
    if (!failures) std::puts("fog wake tests passed");
    return failures ? 1 : 0;
}
