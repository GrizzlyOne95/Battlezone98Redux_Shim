// sp_player_paint_policy_tests.cpp
//
// Pins the pure policy of single-player player paint
// (include/sp_player_paint_policy.h, Docs/SP_PLAYER_PAINT.md): the variant
// table, the generated mask table, and the clone naming that keeps paint
// clones apart from GPU-skinning clones and CR team twins.

#include "sp_player_paint_policy.h"

#include <cstring>
#include "test_check.h"

using OpenShimTest::Check;
using namespace BZROpenShim::SpPlayerPaint;

namespace
{
    void Variants()
    {
        Check(FindVariant("stock") == nullptr && FindVariant("") == nullptr, "stock and empty: no paint");
        Check(FindVariant("host") == nullptr, "host camo is not offered (single-channel masks)");
        const Variant* red = FindVariant("T2");
        Check(red && std::strcmp(red->key, "t2") == 0 && red->rgba[0] == 0.80f && red->rgba[3] == 2.0f,
              "t2 is CR's red tint, case-insensitive");
        Check(FindVariant("t3") && FindVariant("t4") && !FindVariant("t5") && !FindVariant("t"), "t3/t4 only");
        for (const Variant& v : kVariants)
            Check(v.rgba[3] > 1.5f, "every variant turns the shader paint on (a > 1.5)");
    }

    void Masks()
    {
        Check(sizeof(kMasks) / sizeof(kMasks[0]) == 71, "71 stock materials have a mask");
        const char* apc = FindMask("avapc00");
        Check(apc && std::strcmp(apc, "openshim_paint_avapc.dds") == 0, "avapc00 -> openshim_paint_avapc.dds");
        Check(FindMask("AVAPC00") == apc, "lookup is case-insensitive");
        Check(FindMask("avapc0") == nullptr && FindMask("avapc00x") == nullptr, "exact names only");
        Check(FindMask("avcnst_nacjet") == nullptr, "CR-only materials are not in the table");
    }

    void Names()
    {
        const Variant& t2 = *FindVariant("t2");
        const Variant& t3 = *FindVariant("t3");
        Check(CloneName("avapc00", t2) == "avapc00@ospaint_t2", "plain clone name");
        Check(CloneName("avapc00@ospaint_t2", t3) == "avapc00@ospaint_t3", "repaint replaces the suffix");
        Check(CloneName("OpenShim/GpuSkin/3/w4/avapc00", t2) == "OpenShim/GpuSkin/3/w4/avapc00@ospaint_t2",
              "GPU-skinning clone keeps its path (same vertex programs)");
        Check(PaintedWith("OpenShim/GpuSkin/3/w4/avapc00@ospaint_t2", t2), "GPU skinning's clone of ours counts");
        Check(!PaintedWith("avapc00@ospaint_t2", t3) && !PaintedWith("avapc00", t2), "other variant or stock");
        Check(IsPaintClone("x@ospaint_t4") && !IsPaintClone("avapc00"), "clone tag");
        Check(SourceKey("avapc00") == "avapc00", "stock name");
        Check(SourceKey("OpenShim/GpuSkin/3/w4/avapc00@ospaint_t2") == "avapc00", "skin path and suffix dropped");
        Check(SourceKey("avapc00_tm") == "avapc00", "CR team twin suffix dropped");
        Check(StripPaintSuffix("OpenShim/GpuSkin/3/w4/avapc00@ospaint_t2") == "OpenShim/GpuSkin/3/w4/avapc00",
              "restore target keeps the skin path");
    }

    void Schemes()
    {
        Check(IsPaintScheme("en-high") && IsPaintScheme("en-high-pssm") && IsPaintScheme("en-high-noshadow"),
              "en-high family");
        Check(!IsPaintScheme("en-medium") && !IsPaintScheme("high-pssm") && !IsPaintScheme(""), "nothing else");
    }
}

int main()
{
    Variants();
    Masks();
    Names();
    Schemes();
    return OpenShimTest::ExitCode();
}
