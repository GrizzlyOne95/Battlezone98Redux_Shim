#pragma once
// build_overlay.h
// BZR Open Shim - which battlezone98redux.exe build scripts/patches.json is for.
//
// Every address in patches.json belongs to one exact build of the game. The
// file names that build in a top-level "build" block, and may carry
// "build_overlays" for other builds: per-entry replacements produced by
// reverse_engineering/build_port/port_patches.py when BZR ships a patch.
// Steam players get a game update the day it ships while GOG players may not,
// so one OpenShim release has to serve both builds at once.
//
//   "build": { "label": "2.2.301", "time_date_stamps": ["0x58D9D6CC"] },
//   "build_overlays": [
//     { "build": { "label": "2.2.302", "time_date_stamps": ["0x...."] },
//       "entries": {
//         "engine_addresses/GAS_SetMaxVoices": { "address": "0x...", "expected": "..." },
//         "patches/HUD 2D Depth Floor Margin": null,
//         ...
//       } }
//   ]
//
// The running exe is identified by its PE link timestamp. Selecting the base
// build leaves the document as it is. Selecting an overlay merges each listed
// entry's fields over the base entry and drops every entry the overlay does not
// list, or lists as null: an address nobody carried across to that build must
// read as missing, so the feature built on it stands down, rather than fall
// through to the base build's value. An exe the file does not name at all gets
// every address entry dropped. Parsed here, away from <Windows.h>, so it is
// testable on the host.
#include <cstdint>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

namespace BZROpenShim::BuildOverlay
{
    enum class Match : uint8_t
    {
        Base,        // the exe is the build the top-level entries describe
        Overlay,     // the exe is described by one of "build_overlays"
        Unknown,     // the file names builds, and this exe is none of them
        Unversioned, // the file has no "build" block (older patches.json)
    };

    struct Selection
    {
        Match match = Match::Unversioned;
        std::string label;              // label of the selected build
        std::vector<std::string> known; // every build label the file names
        size_t replaced = 0;            // overlay: entries given new values
        size_t dropped = 0;             // overlay: entries with no value for this build
        std::string error;              // malformed build blocks, if any
    };

    // Rewrites doc in place to what applies to an exe linked at exeStamp, and
    // removes "build_overlays" from it. Never throws.
    Selection Apply(nlohmann::json& doc, uint32_t exeStamp);

    const char* MatchName(Match match);
}
