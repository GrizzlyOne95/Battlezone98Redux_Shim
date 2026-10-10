#pragma once

// Matchmaking server selection: the pure parsing and validation behind the
// pre-lobby's Rebellion / Custom choice. Header-only and free of Windows and
// engine calls so the tests can include it.
//
//   openshim.ini [Network] Server       = Rebellion | Custom   (absent: no override)
//   openshim.ini [Network] CustomServer = <host or IP>[:1337]
//
// Only the host is switchable. The scheme (ws) and port (1337) are the same
// for the official and custom servers, so a CustomServer value carries
// neither; a trailing ":1337" is accepted and dropped, any other port is
// refused.

#include <cstddef>
#include <string>
#include <string_view>

namespace BZROpenShim
{
namespace MatchmakingServer
{
    inline constexpr const char kRebellionHost[] = "battlezone98mp.webdev.rebellion.co.uk";
    inline constexpr unsigned kPort = 1337;
    inline constexpr size_t kMaxHostLength = 253;

    enum class Mode
    {
        None,       // no saved choice: stock behaviour (/bzrserver or the official host)
        Rebellion,
        Custom,
    };

    enum class HostStatus
    {
        Ok,
        Empty,
        Invalid,          // scheme, path, whitespace, bad characters
        UnsupportedPort,  // a well-formed port other than 1337
    };

    namespace Detail
    {
        inline bool IsSpace(char c)
        {
            return c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f';
        }

        inline char Lower(char c)
        {
            return (c >= 'A' && c <= 'Z') ? static_cast<char>(c - 'A' + 'a') : c;
        }

        inline std::string_view Trim(std::string_view text)
        {
            while (!text.empty() && IsSpace(text.front()))
                text.remove_prefix(1);
            while (!text.empty() && IsSpace(text.back()))
                text.remove_suffix(1);
            return text;
        }

        inline bool IsHostChar(char c)
        {
            return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
                   (c >= '0' && c <= '9') || c == '-' || c == '.' || c == '_';
        }
    }

    inline bool EqualsNoCase(std::string_view a, std::string_view b)
    {
        if (a.size() != b.size())
            return false;
        for (size_t i = 0; i < a.size(); ++i)
        {
            if (Detail::Lower(a[i]) != Detail::Lower(b[i]))
                return false;
        }
        return true;
    }

    // The [Network] Server value. Empty or absent is Mode::None and parses.
    // False (mode None) for anything else that is not Rebellion or Custom.
    inline bool ParseMode(std::string_view text, Mode& mode)
    {
        mode = Mode::None;
        text = Detail::Trim(text);
        if (text.empty())
            return true;
        if (EqualsNoCase(text, "Rebellion"))
        {
            mode = Mode::Rebellion;
            return true;
        }
        if (EqualsNoCase(text, "Custom"))
        {
            mode = Mode::Custom;
            return true;
        }
        return false;
    }

    inline const char* ModeName(Mode mode)
    {
        switch (mode)
        {
        case Mode::Rebellion: return "Rebellion";
        case Mode::Custom: return "Custom";
        default: return "";
        }
    }

    // Validates a typed or saved CustomServer value and returns the bare host
    // (":1337" stripped, case kept). `host` is cleared unless the result is Ok.
    inline HostStatus ValidateCustomHost(std::string_view input, std::string& host)
    {
        host.clear();
        input = Detail::Trim(input);
        if (input.empty())
            return HostStatus::Empty;

        for (char c : input)
        {
            if (Detail::IsSpace(c) || c == '/' || c == '\\' || c == '?' || c == '#' || c == '@')
                return HostStatus::Invalid;
        }

        std::string_view name = input;
        const size_t colon = input.find(':');
        if (colon != std::string_view::npos)
        {
            if (input.find(':', colon + 1) != std::string_view::npos)
                return HostStatus::Invalid;  // a second colon: a scheme or IPv6
            const std::string_view port = input.substr(colon + 1);
            if (port.empty() || port.size() > 5)
                return HostStatus::Invalid;
            unsigned value = 0;
            for (char c : port)
            {
                if (c < '0' || c > '9')
                    return HostStatus::Invalid;
                value = value * 10 + static_cast<unsigned>(c - '0');
            }
            name = input.substr(0, colon);
            if (name.empty())
                return HostStatus::Invalid;
            if (value != kPort)
                return HostStatus::UnsupportedPort;
        }

        if (name.size() > kMaxHostLength || name.front() == '.' || name.back() == '.' ||
            name.front() == '-' || name.find("..") != std::string_view::npos)
        {
            return HostStatus::Invalid;
        }
        for (char c : name)
        {
            if (!Detail::IsHostChar(c))
                return HostStatus::Invalid;
        }

        host.assign(name.data(), name.size());
        return HostStatus::Ok;
    }

    // The host the saved settings select: the official host for Rebellion, the
    // validated CustomServer for Custom, empty for no override (None, or a
    // Custom with an unusable address).
    inline std::string ResolveSavedHost(Mode mode, std::string_view customServer)
    {
        if (mode == Mode::Rebellion)
            return kRebellionHost;
        if (mode == Mode::Custom)
        {
            std::string host;
            if (ValidateCustomHost(customServer, host) == HostStatus::Ok)
                return host;
        }
        return std::string();
    }

    // The host of a /bzrserver=<url> launch switch (ws://host[:port]/...),
    // matched case-insensitively. False when the switch is absent or carries
    // no usable host. A bare "host" or "host:port" is accepted too.
    inline bool ExtractLaunchHost(std::wstring_view commandLine, std::string& host)
    {
        host.clear();

        static constexpr char kSwitch[] = "bzrserver=";
        constexpr size_t kSwitchLen = sizeof(kSwitch) - 1;

        size_t at = 0;
        size_t valueStart = std::wstring_view::npos;
        while (at < commandLine.size())
        {
            const wchar_t lead = commandLine[at];
            const bool boundary = at == 0 || commandLine[at - 1] == L' ' ||
                                  commandLine[at - 1] == L'\t' || commandLine[at - 1] == L'"';
            if ((lead == L'/' || lead == L'-') && boundary &&
                commandLine.size() - at > kSwitchLen)
            {
                bool match = true;
                for (size_t i = 0; i < kSwitchLen; ++i)
                {
                    const wchar_t w = commandLine[at + 1 + i];
                    if (w > 0x7F || Detail::Lower(static_cast<char>(w)) != kSwitch[i])
                    {
                        match = false;
                        break;
                    }
                }
                if (match)
                {
                    valueStart = at + 1 + kSwitchLen;
                    break;
                }
            }
            ++at;
        }
        if (valueStart == std::wstring_view::npos)
            return false;

        std::wstring_view value = commandLine.substr(valueStart);
        if (!value.empty() && value.front() == L'"')
        {
            value.remove_prefix(1);
            const size_t close = value.find(L'"');
            if (close != std::wstring_view::npos)
                value = value.substr(0, close);
        }
        else
        {
            size_t end = 0;
            while (end < value.size() && value[end] != L' ' && value[end] != L'\t')
                ++end;
            value = value.substr(0, end);
        }

        std::string url;
        for (wchar_t w : value)
        {
            if (w > 0x7F)
                return false;
            url.push_back(static_cast<char>(w));
        }

        std::string_view rest = url;
        const size_t scheme = rest.find("://");
        if (scheme != std::string_view::npos)
            rest.remove_prefix(scheme + 3);
        const size_t pathAt = rest.find_first_of("/?#");
        if (pathAt != std::string_view::npos)
            rest = rest.substr(0, pathAt);
        const size_t userAt = rest.rfind('@');
        if (userAt != std::string_view::npos)
            rest.remove_prefix(userAt + 1);

        std::string_view name;
        if (!rest.empty() && rest.front() == '[')
        {
            const size_t close = rest.find(']');
            if (close == std::string_view::npos)
                return false;
            name = rest.substr(1, close - 1);
        }
        else
        {
            name = rest.substr(0, rest.find(':'));
        }
        if (name.empty())
            return false;

        host.assign(name.data(), name.size());
        return true;
    }
}
}
