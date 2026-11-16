#pragma once
// mode_stress_plan.h
// BZR Open Shim - the plan-file parser of the mode-transition stress driver
// (src/patches/mode_stress_driver.cpp). Pure C++17 so the Linux test lane
// builds it (tests/mode_stress_plan_tests.cpp).
//
// One step per line; '#' starts a comment; blank lines are skipped:
//
//   mission <file.bzn> <seconds> [campaign]  ; campaign-mode load (optional
//                                             ; campaign id, e.g. cr_campaign)
//   ia <file.bzn> <seconds>                  ; Instant Action load
//   mp_host <file.bzn> <seconds>             ; host a one-player LAN game in this
//                                            ; process (OpenShim no-sign-in host)
//   shell <seconds>                          ; idle on the main menu
//   loop <n>                                 ; run the whole list n times
//
// <seconds> counts from "ready" (the sim loop running) for mission/ia, and
// from the main menu for shell. Fail-closed: any bad line rejects the plan.

#include <cstdint>
#include <cstdlib>
#include <string>
#include <string_view>
#include <vector>

namespace BZROpenShim
{
namespace ModeStress
{
    enum class StepKind
    {
        Mission,
        InstantAction,
        MpHost,
        Shell,
    };

    struct Step
    {
        StepKind kind = StepKind::Shell;
        std::string arg;       // bzn name; empty for shell
        std::string campaign;  // mission only; empty = leave the current one
        uint32_t seconds = 0;
        int line = 0;
    };

    struct Plan
    {
        std::vector<Step> steps;
        uint32_t loops = 1;
    };

    struct ParseResult
    {
        bool ok = false;
        Plan plan;
        int errorLine = 0;
        std::string error;
    };

    // The engine's queued mission-name buffer holds 16 chars with the
    // terminator (scripts/patches.json QueuedLoadNameBuffer).
    inline constexpr size_t kMaxBznChars = 15;
    inline constexpr size_t kMaxCampaignChars = 63;
    inline constexpr uint32_t kMaxSeconds = 3600;
    inline constexpr uint32_t kMaxLoops = 100;
    inline constexpr size_t kMaxSteps = 64;

    inline const char* KindName(StepKind kind)
    {
        switch (kind)
        {
        case StepKind::Mission: return "mission";
        case StepKind::InstantAction: return "ia";
        case StepKind::MpHost: return "mp_host";
        case StepKind::Shell: return "shell";
        }
        return "?";
    }

    namespace PlanDetail
    {
        inline bool IsSpace(char c) { return c == ' ' || c == '\t' || c == '\r' || c == '\v' || c == '\f'; }

        inline std::vector<std::string_view> Tokens(std::string_view line)
        {
            std::vector<std::string_view> out;
            size_t i = 0;
            while (i < line.size())
            {
                while (i < line.size() && IsSpace(line[i]))
                    ++i;
                const size_t start = i;
                while (i < line.size() && !IsSpace(line[i]))
                    ++i;
                if (i > start)
                    out.push_back(line.substr(start, i - start));
            }
            return out;
        }

        inline bool ParseUnsigned(std::string_view text, uint32_t minValue, uint32_t maxValue, uint32_t& out)
        {
            if (text.empty() || text.size() > 9)
                return false;
            uint32_t value = 0;
            for (const char c : text)
            {
                if (c < '0' || c > '9')
                    return false;
                value = value * 10u + static_cast<uint32_t>(c - '0');
            }
            if (value < minValue || value > maxValue)
                return false;
            out = value;
            return true;
        }

        inline bool IsNameChar(char c)
        {
            return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') ||
                   c == '_' || c == '-';
        }

        inline bool ValidBzn(std::string_view text)
        {
            if (text.size() < 5 || text.size() > kMaxBznChars)
                return false;
            const std::string_view ext = text.substr(text.size() - 4);
            if (ext[0] != '.' || (ext[1] | 0x20) != 'b' || (ext[2] | 0x20) != 'z' || (ext[3] | 0x20) != 'n')
                return false;
            for (size_t i = 0; i + 4 < text.size(); ++i)
            {
                if (!IsNameChar(text[i]))
                    return false;
            }
            return true;
        }

        inline bool ValidCampaign(std::string_view text)
        {
            if (text.empty() || text.size() > kMaxCampaignChars)
                return false;
            for (const char c : text)
            {
                if (!IsNameChar(c))
                    return false;
            }
            return true;
        }
    }

    inline ParseResult ParsePlan(std::string_view text)
    {
        using namespace PlanDetail;
        ParseResult result;
        bool sawLoop = false;
        int lineNumber = 0;
        auto fail = [&](const std::string& why) {
            result.ok = false;
            result.errorLine = lineNumber;
            result.error = why;
            result.plan = Plan{};
            return result;
        };

        size_t pos = 0;
        while (pos <= text.size())
        {
            const size_t end = text.find('\n', pos);
            std::string_view line = text.substr(pos, end == std::string_view::npos ? std::string_view::npos : end - pos);
            pos = end == std::string_view::npos ? text.size() + 1 : end + 1;
            ++lineNumber;

            const size_t hash = line.find('#');
            if (hash != std::string_view::npos)
                line = line.substr(0, hash);
            const std::vector<std::string_view> tok = Tokens(line);
            if (tok.empty())
                continue;

            const std::string_view kind = tok[0];
            Step step;
            step.line = lineNumber;
            if (kind == "loop")
            {
                if (sawLoop)
                    return fail("loop given twice");
                if (tok.size() != 2 || !ParseUnsigned(tok[1], 1, kMaxLoops, result.plan.loops))
                    return fail("loop takes one count 1-100");
                sawLoop = true;
                continue;
            }
            if (kind == "shell")
            {
                step.kind = StepKind::Shell;
                if (tok.size() != 2 || !ParseUnsigned(tok[1], 0, kMaxSeconds, step.seconds))
                    return fail("shell takes <seconds> 0-3600");
            }
            else if (kind == "mission" || kind == "ia")
            {
                const bool mission = kind == "mission";
                step.kind = mission ? StepKind::Mission : StepKind::InstantAction;
                const size_t maxTokens = mission ? 4 : 3;
                if (tok.size() < 3 || tok.size() > maxTokens)
                    return fail(mission ? "mission takes <file.bzn> <seconds> [campaign]"
                                        : "ia takes <file.bzn> <seconds>");
                if (!ValidBzn(tok[1]))
                    return fail("bad bzn name (letters, digits, _ or -, ending .bzn, at most 15 chars)");
                if (!ParseUnsigned(tok[2], 1, kMaxSeconds, step.seconds))
                    return fail("seconds must be 1-3600");
                step.arg.assign(tok[1].data(), tok[1].size());
                if (tok.size() == 4)
                {
                    if (!ValidCampaign(tok[3]))
                        return fail("bad campaign id (letters, digits, _ or -)");
                    step.campaign.assign(tok[3].data(), tok[3].size());
                }
            }
            else if (kind == "mp_host")
            {
                step.kind = StepKind::MpHost;
                if (tok.size() != 3)
                    return fail("mp_host takes <file.bzn> <seconds>");
                if (!ValidBzn(tok[1]))
                    return fail("bad bzn name (letters, digits, _ or -, ending .bzn, at most 15 chars)");
                if (!ParseUnsigned(tok[2], 1, kMaxSeconds, step.seconds))
                    return fail("seconds must be 1-3600");
                step.arg.assign(tok[1].data(), tok[1].size());
            }
            else
            {
                return fail("unknown step kind");
            }
            if (result.plan.steps.size() >= kMaxSteps)
                return fail("more than 64 steps");
            result.plan.steps.push_back(step);
        }
        lineNumber = 0;
        if (result.plan.steps.empty())
            return fail("plan has no steps");
        result.ok = true;
        return result;
    }
}
}
