#pragma once

// Engine-independent authoring contract for an opt-in custom planet video.
#include <charconv>
#include <cmath>
#include <cstdint>
#include <string>
#include <string_view>

namespace BZROpenShim::PlanetVideo
{
    constexpr size_t kMaxConfigBytes = 16384;

    struct Config
    {
        double loopStartSeconds = 0.0;
        bool startAtLoop = false;
        std::string introSound;
    };

    inline std::string_view Trim(std::string_view s)
    {
        constexpr auto whitespace = " \t\r\n";
        const auto first = s.find_first_not_of(whitespace);
        if (first == std::string_view::npos) return {};
        return s.substr(first, s.find_last_not_of(whitespace) - first + 1);
    }

    inline bool EqualAscii(std::string_view a, std::string_view b)
    {
        if (a.size() != b.size()) return false;
        for (size_t i = 0; i < a.size(); ++i)
        {
            const auto lower = [](char c) { return c >= 'A' && c <= 'Z' ? c + ('a' - 'A') : c; };
            if (lower(a[i]) != lower(b[i])) return false;
        }
        return true;
    }

    // Flat resource names avoid OS paths and work with the game's mounted VFS.
    inline bool IsResourceName(std::string_view s, std::string_view extension)
    {
        if (s.size() <= extension.size() || s.size() > 63 ||
            !EqualAscii(s.substr(s.size() - extension.size()), extension)) return false;
        for (char c : s.substr(0, s.size() - extension.size()))
            if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
                  (c >= '0' && c <= '9') || c == '_' || c == '-')) return false;
        return true;
    }

    inline std::string SidecarName(std::string_view video)
    {
        if (!IsResourceName(video, ".ogv")) return {};
        return std::string(video.substr(0, video.size() - 4)) + ".pvi";
    }

    // Atomic parse: an invalid file must never partially enable playback changes.
    inline bool Parse(std::string_view text, Config& out, std::string& error)
    {
        error.clear();
        const auto fail = [&](const char* why) { error = why; return false; };
        if (text.empty() || text.size() > kMaxConfigBytes || text.find('\0') != text.npos)
            return fail("empty, oversized, or binary sidecar");
        if (text.substr(0, 3) == "\xEF\xBB\xBF") text.remove_prefix(3);
        Config parsed;
        bool inSection = false, sectionSeen = false;
        unsigned keys = 0;
        while (!text.empty())
        {
            const auto end = text.find('\n');
            auto line = Trim(text.substr(0, end));
            if (end == text.npos) text = {};
            else text.remove_prefix(end + 1);
            if (line.empty() || line.front() == ';' || line.front() == '#') continue;
            if (line.front() == '[')
            {
                if (line.back() != ']') return fail("malformed section");
                inSection = EqualAscii(Trim(line.substr(1, line.size() - 2)), "PlanetVideo");
                if (inSection && sectionSeen) return fail("duplicate PlanetVideo section");
                sectionSeen = sectionSeen || inSection;
                continue;
            }
            if (!inSection) continue;
            const auto equals = line.find('=');
            if (equals == line.npos) return fail("expected key=value");
            const auto key = Trim(line.substr(0, equals));
            auto value = Trim(line.substr(equals + 1));
            const auto comment = value.find_first_of(";#");
            if (comment != value.npos) value = Trim(value.substr(0, comment));
            if (value.size() >= 2 && value.front() == '"' && value.back() == '"')
                value = value.substr(1, value.size() - 2);
            unsigned flag = 0;
            if (EqualAscii(key, "LoopStartSeconds"))
            {
                flag = 1;
                double seconds = 0;
                const auto result = std::from_chars(value.data(), value.data() + value.size(), seconds);
                if (result.ec != std::errc{} || result.ptr != value.data() + value.size() ||
                    !std::isfinite(seconds) || seconds < 0 || seconds > 86400)
                    return fail("invalid LoopStartSeconds");
                parsed.loopStartSeconds = seconds;
            }
            else if (EqualAscii(key, "StartAtLoop"))
            {
                flag = 2;
                if (value != "0" && value != "1") return fail("StartAtLoop must be 0 or 1");
                parsed.startAtLoop = value == "1";
            }
            else if (EqualAscii(key, "IntroSound"))
            {
                flag = 4;
                if (!value.empty() && !IsResourceName(value, ".wav")) return fail("IntroSound must be a flat WAV resource name");
                parsed.introSound = std::string(value);
            }
            else return fail("unknown PlanetVideo key");
            if (keys & flag) return fail("duplicate PlanetVideo key");
            keys |= flag;
        }
        if (!sectionSeen || !(keys & 1)) return fail("PlanetVideo/LoopStartSeconds is required");
        out = parsed;
        return true;
    }

    inline bool LoopFrame(const Config& config, double fps, int frameCount, int& out)
    {
        if (!std::isfinite(fps) || fps <= 0 || frameCount <= 0 ||
            !std::isfinite(config.loopStartSeconds) || config.loopStartSeconds < 0) return false;
        const double frame = std::floor(config.loopStartSeconds * fps + 0.5);
        if (!std::isfinite(frame) || frame >= frameCount) return false;
        out = static_cast<int>(frame);
        return true;
    }
}
