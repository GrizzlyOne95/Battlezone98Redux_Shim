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
    std::puts("weapon_presentation_native_policy_tests: all checks passed");
}
