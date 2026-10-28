#include "weapon_presentation_native_policy.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace WP = BZROpenShim::WeaponPresentation;
namespace Policy = WP::NativePolicy;
namespace WC = BZROpenShim::WeaponConvergence;

static void Require(bool condition, const char* message)
{
    if (!condition) { std::fprintf(stderr, "%s\n", message); std::abort(); }
}

int main()
{
    Require(Policy::Hash("WeaponClass") == Policy::Hash("weaponclass"), "section case changed native hash");
    Require(Policy::Hash("soundAmbient") == 0xf1aad7dcu, "native key hash mismatch");
    Require(Policy::Name(" \t\"MyFlash.Sprite\" \t") == "MyFlash.Sprite", "effect case/quotes changed");
    Require(Policy::Name("\"\"")->empty(), "explicit empty name was not preserved");
    for (const auto value : { "\"bad", "bad\"", "bad\n", "\"a\"b\"" })
        Require(!Policy::Name(value), "malformed native name accepted");
    Require(Policy::Duration(" +1.25e-1 ") == 0.125f, "valid native duration rejected");
    for (const auto value : { "", " ", "0", "-1", "NaN", "inf", "1seconds", "1,25", "1e999" })
        Require(!std::isfinite(Policy::Duration(value)), "malformed present duration inherited");
    const WP::FlashConfig parent{ "Parent.Sprite", 0.2f };
    Require(!WP::ResolveFlashConfig(parent, std::nullopt, Policy::Duration("bad")).Valid(),
        "invalid duration did not disable inherited config");

    WP::Runtime runtime;
    runtime.Configure({ false, true }); runtime.SetSession(true, true);
    WP::BindRequest request;
    request.owner = { 1, 2 }; request.weapon = { 3, 4 };
    auto rest = WC::Identity(); rest.positionX = 5; rest.positionY = 7; rest.positionZ = 11;
    request.recoil = WP::RecoilBinding{ { 8, 9 }, rest };
    const auto token = runtime.Bind(request);
    Require(token.has_value(), "could not bind static node");
    Require(runtime.Fire(*token, 1, WC::Identity()).recoilReset, "shot did not reset recoil");
    auto input = rest;
    input.rightX = 0; input.rightZ = -1; input.frontX = 1; input.frontZ = 0;
    const auto original = input;
    Require(runtime.SetRecoilPose(request.owner, request.recoil->node, input), "live rotation refused");
    WP::Matrix visual;
    Require(runtime.TryGetVisualRecoilPose(request.owner, request.recoil->node, visual), "could not stage native pose");
    Require(std::abs(visual.positionX - 4.4) < 0.00001 && visual.positionZ == 11,
        "staged recoil used world axis or lost rest translation");
    Require(std::memcmp(&input, &original, sizeof(input)) == 0, "gameplay pose was changed");
    auto moved = input; moved.positionX += 1;
    Require(!runtime.SetRecoilPose(request.owner, request.recoil->node, moved), "animated translation accepted");
    runtime.SetSession(false, true);
    Require(!runtime.TryGetVisualRecoilPose(request.owner, request.recoil->node, visual), "MP produced staged recoil");
    // Cockpit twin rule, from real CR/stock VDF bands.
    auto id = [](const char* name) { return *WP::ParseMeshId(name); };
    Require(Policy::CockpitTwinMatches("AGR21bga", id("AGR11BGA")), "avtank cockpit barrel not matched");
    Require(Policy::CockpitTwinMatches("SCZ21BGB", id("SCZ11BGB")), "svtank cockpit barrel not matched");
    Require(Policy::CockpitTwinMatches("age21hed", id("age11hed")), "walker cockpit twin not matched");
    Require(!Policy::CockpitTwinMatches("AGR11BGA", id("AGR11BGA")), "hidden band-1 bone matched itself");
    Require(!Policy::CockpitTwinMatches("AGR21bgb", id("AGR11BGA")), "different slot matched");
    Require(!Policy::CockpitTwinMatches("AGR21bg", id("AGR11BGA")), "length mismatch matched");
    Require(!Policy::CockpitTwinMatches("AGR31bga", id("AGR21BGA")), "non band-1 node got a twin");
    Require(!Policy::CockpitTwinMatches("ab2", id("ab1")), "short name got a twin");
    Require(Policy::CockpitFlag(" 0 ") == false && Policy::CockpitFlag("true") == true &&
        !Policy::CockpitFlag("yes"), "recoilCockpit flag parse changed");
    {
        WP::Matrix restPose = WC::Identity(), kicked = WC::Identity();
        kicked.frontX = 0; kicked.frontY = 0; kicked.frontZ = 1;
        restPose.positionZ = 2; kicked.positionZ = 2 - 0.3;
        Require(std::abs(Policy::RecoilDisplacement(restPose, kicked) + 0.3f) < 1e-5f, "displacement sign/size wrong");
        kicked.positionZ = 2; kicked.positionY = 5; // off-axis motion is not recoil
        Require(Policy::RecoilDisplacement(restPose, kicked) == 0, "off-axis motion read as recoil");
        const auto p = Policy::CockpitRecoilPosition({ 0.349f, 2.136f, 1.604f }, {}, -0.3f);
        Require(p.x == 0.349f && p.y == 2.136f && std::abs(p.z - 1.304f) < 1e-5f, "identity bone did not slide back on +Z");
        // 90 degrees about Y: +Z becomes +X.
        const float s = std::sqrt(0.5f);
        const auto f = Policy::BoneForward({ s, 0, s, 0 });
        Require(std::abs(f.x - 1) < 1e-5f && std::abs(f.y) < 1e-5f && std::abs(f.z) < 1e-5f, "bone forward axis wrong");
    }
    {
        // baseName inheritance: player.odf -> avtank.odf
        const auto base = Policy::ParseOdfText(
            "\xEF\xBB\xBF[GameObjectClass]\r\nweaponHard1 = \"Gcannon\" // main\r\nweaponHard2 = gmortar\r\nweaponHard3 = gdual\r\n"
            "[CraftClass]\r\nflashOffset1 = \"0.20 0.10 2.41\" ; muzzle\r\nrecoilName1 = \"AGR11BGA\"\r\n"
            "flashOffset2 = \"0 0 1\"\r\nflashOffset3 = \"0 0 2\"\r\nFlashOffset1 = \"9 9 9\"\r\n");
        Require(*Policy::OdfValue(base, "craftclass", "FLASHOFFSET1") == "\"0.20 0.10 2.41\"", "comment/first-wins/case parse wrong");
        Require(Policy::OdfValue(base, "GameObjectClass", "weaponHard1") && *Policy::OdfValue(base, "GameObjectClass", "weaponHard1") == "\"Gcannon\"",
            "// comment not stripped");
        Require(!Policy::OdfValue(base, "GameObjectClass", "flashOffset1"), "section leaked");
        const auto player = Policy::ParseOdfText(
            "[GameObjectClass]\nbaseName = \"avtank\"\nweaponHard1 = GCANNON\nweaponHard2 = other\nweaponHard3 = gdual\n"
            "[CraftClass]\nflashOffset3 = \"1 1 1\"\n");
        std::array<std::string, Policy::kCraftSlots> hard;
        for (size_t i = 0; i < hard.size(); ++i)
            if (const auto* v = Policy::OdfValue(player, "GameObjectClass", "weaponHard" + std::to_string(i + 1))) hard[i] = *v;
        const unsigned own = 0b00100; // slot 3 has its own flashOffset3
        // slot 1 inherits (case-insens. match), 2 mismatched hardpoint, 3 has own key, 4/5 absent
        Require(Policy::InheritedCraftSlots(own, hard, base) == 0b00001, "inheritance mask wrong");
        Require(Policy::InheritedCraftSlots(0, std::array<std::string, Policy::kCraftSlots>{}, base) == 0,
            "missing own weaponHard inherited");
        Require(Policy::BaseOdfName("\"avtank\"", "player") == "avtank", "base name not extracted");
        Require(Policy::BaseOdfName("AVTANK", "avtank").empty(), "self baseName followed");
        Require(Policy::BaseOdfName("", "player").empty() && Policy::BaseOdfName("\"bad", "player").empty(), "bad baseName followed");
    }
    std::puts("weapon_presentation_native_policy_tests: all checks passed");
}
