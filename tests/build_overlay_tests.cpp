// build_overlay_tests.cpp
// Host-side checks for selecting patches.json entries by exe build
// (build_overlay.h). The rule under test: an exe only ever sees addresses
// someone established for that exact build; everything else reads as missing.
#include "build_overlay.h"

#include <string>

#include "test_check.h"

using OpenShimTest::Check;
using namespace BZROpenShim;

namespace
{
    const char* kDoc = R"({
      "features": { "ogre_material_collision_guard": true },
      "build": { "label": "2.2.301", "time_date_stamps": ["0x58D9D6CC"] },
      "patches": [
        { "name": "P1", "pattern": "AA BB", "offset": 0, "fallback": "0x00401000" },
        { "name": "P2", "pattern": "CC DD", "offset": 1, "fallback": "0x00402000" }
      ],
      "engine_addresses": [
        { "name": "Fn", "address": "0x00403000", "expected": "55 8B EC" },
        { "name": "Glob", "address": "0x00915594", "kind": "data" }
      ],
      "static_pointers": [ { "name": "SP", "address": "0x00900000" } ],
      "audio_gas_pattern": { "pattern": "A3 ?? ?? ?? ??" },
      "build_overlays": [
        { "build": { "label": "2.2.302", "time_date_stamps": ["0x60000000", "0x60000001"] },
          "entries": {
            "patches/P1": { "pattern": "AA BB EE", "fallback": "0x00401100" },
            "patches/P2": null,
            "engine_addresses/Fn": { "address": "0x00403100", "expected": "55 8B EC 51" },
            "static_pointers/SP": { "address": "0x00900100" },
            "audio_gas_pattern": { "pattern": "A3 ?? ?? ?? ?? A3" }
          } }
      ]
    })";

    nlohmann::json Doc() { return nlohmann::json::parse(kDoc); }

    const nlohmann::json* Find(const nlohmann::json& doc, const char* section, const char* name)
    {
        if (!doc.contains(section)) return nullptr;
        for (const auto& e : doc[section])
            if (e["name"] == name) return &e;
        return nullptr;
    }

    void BaseBuildIsUntouched()
    {
        auto doc = Doc();
        const auto before = Doc();
        const auto sel = BuildOverlay::Apply(doc, 0x58D9D6CC);
        Check(sel.match == BuildOverlay::Match::Base, "base stamp selects the base build");
        Check(sel.label == "2.2.301", "base label reported");
        Check(sel.known.size() == 2, "both builds listed as known");
        Check(!doc.contains("build_overlays"), "overlays removed from the effective document");
        Check(doc["patches"] == before["patches"], "base patches unchanged");
        Check(doc["engine_addresses"] == before["engine_addresses"], "base engine addresses unchanged");
        Check(sel.error.empty(), "no errors for a well-formed file");
    }

    void OverlayReplacesAndDrops()
    {
        auto doc = Doc();
        const auto sel = BuildOverlay::Apply(doc, 0x60000001);
        Check(sel.match == BuildOverlay::Match::Overlay, "second overlay stamp selects the overlay");
        Check(sel.label == "2.2.302", "overlay label reported");
        const auto* p1 = Find(doc, "patches", "P1");
        Check(p1 && (*p1)["fallback"] == "0x00401100" && (*p1)["pattern"] == "AA BB EE",
              "listed patch takes the overlay's fields");
        Check(p1 && (*p1)["offset"] == 0, "fields the overlay omits keep the base value");
        Check(Find(doc, "patches", "P2") == nullptr, "null entry is dropped");
        const auto* fn = Find(doc, "engine_addresses", "Fn");
        Check(fn && (*fn)["address"] == "0x00403100" && (*fn)["expected"] == "55 8B EC 51",
              "engine address and its guard bytes replaced together");
        Check(Find(doc, "engine_addresses", "Glob") == nullptr,
              "entry the overlay does not list is dropped, not left at the base address");
        const auto* sp = Find(doc, "static_pointers", "SP");
        Check(sp && (*sp)["address"] == "0x00900100", "static pointer replaced");
        Check(doc["audio_gas_pattern"]["pattern"] == "A3 ?? ?? ?? ?? A3", "single object section replaced");
        Check(doc["features"]["ogre_material_collision_guard"] == true, "feature switches are not build data");
        Check(sel.replaced == 4 && sel.dropped == 2, "counts: P1, Fn, SP, audio replaced; P2, Glob dropped");
    }

    void UnknownBuildSeesNoAddresses()
    {
        auto doc = Doc();
        const auto sel = BuildOverlay::Apply(doc, 0x12345678);
        Check(sel.match == BuildOverlay::Match::Unknown, "unlisted stamp is unknown");
        Check(doc["patches"].empty() && doc["engine_addresses"].empty() && doc["static_pointers"].empty(),
              "unknown build gets no address entries at all");
        Check(!doc.contains("audio_gas_pattern"), "unknown build gets no audio pattern");
        Check(doc.contains("features"), "feature switches survive");
    }

    void UnversionedFileIsLeftForTheCaller()
    {
        auto doc = nlohmann::json::parse(R"({ "patches": [ { "name": "P1" } ] })");
        const auto sel = BuildOverlay::Apply(doc, 0x58D9D6CC);
        Check(sel.match == BuildOverlay::Match::Unversioned, "no build block is unversioned");
        Check(doc["patches"].size() == 1, "unversioned document unchanged");
    }

    void MalformedBlocksAreReportedNotTrusted()
    {
        auto doc = nlohmann::json::parse(R"({
          "build": { "label": "x", "time_date_stamps": ["58D9D6CC"] },
          "patches": [ { "name": "P1" } ] })");
        const auto sel = BuildOverlay::Apply(doc, 0x58D9D6CC);
        Check(sel.match == BuildOverlay::Match::Unknown, "a stamp without 0x never matches");
        Check(!sel.error.empty(), "malformed stamp is reported");
        Check(doc["patches"].empty(), "and nothing is trusted");

        auto doc2 = nlohmann::json::parse(R"({ "build": { "label": "y" }, "patches": [] })");
        const auto sel2 = BuildOverlay::Apply(doc2, 0x58D9D6CC);
        Check(sel2.match == BuildOverlay::Match::Unknown && !sel2.error.empty(), "missing stamps reported");
    }
}

int main()
{
    BaseBuildIsUntouched();
    OverlayReplacesAndDrops();
    UnknownBuildSeesNoAddresses();
    UnversionedFileIsLeftForTheCaller();
    MalformedBlocksAreReportedNotTrusted();
    return OpenShimTest::ExitCode();
}
