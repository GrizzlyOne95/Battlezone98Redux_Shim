// Pure decision core for the startup backend seam. See backend_selection.h
// for the ownership model and invariants; this file deliberately holds no
// Win32/Ogre/logging dependencies.

#include "backend_selection.h"

#include <algorithm>
#include <cstring>

namespace BZROpenShim::BackendSelection
{
    namespace
    {
        bool EqualsNoCaseAscii(std::string_view a, std::string_view b)
        {
            if (a.size() != b.size())
            {
                return false;
            }
            for (size_t i = 0; i < a.size(); ++i)
            {
                const char ca = a[i];
                const char cb = b[i];
                const char la = (ca >= 'A' && ca <= 'Z') ? static_cast<char>(ca - 'A' + 'a') : ca;
                const char lb = (cb >= 'A' && cb <= 'Z') ? static_cast<char>(cb - 'A' + 'a') : cb;
                if (la != lb)
                {
                    return false;
                }
            }
            return true;
        }

        constexpr std::string_view kDx9Subsystem = "Direct3D9 Rendering Subsystem";
        constexpr std::string_view kDx11Subsystem = "Direct3D11 Rendering Subsystem";
        constexpr std::string_view kGlSubsystem = "OpenGL Rendering Subsystem";
        constexpr std::string_view kRenderSystemKey = "Render System=";
    }

    RendererToken ClassifyRendererToken(std::string_view token)
    {
        if (EqualsNoCaseAscii(token, "dx9") || EqualsNoCaseAscii(token, "d3d9") ||
            EqualsNoCaseAscii(token, "directx9"))
        {
            return RendererToken::Dx9;
        }
        if (EqualsNoCaseAscii(token, "dx11") || EqualsNoCaseAscii(token, "d3d11") ||
            EqualsNoCaseAscii(token, "directx11"))
        {
            return RendererToken::Dx11;
        }
        if (EqualsNoCaseAscii(token, "gl") || EqualsNoCaseAscii(token, "opengl"))
        {
            return RendererToken::Gl;
        }
        return RendererToken::None;
    }

    namespace
    {
        // Advances past one command-line token's leading separator. Stock uses
        // strtok over whitespace and accepts '/', '-' or '+' as the option
        // introducer; we mirror that without mutating the input.
        bool TokenTextMatches(std::string_view candidate, std::string_view key,
                              std::string_view& outValue)
        {
            // candidate excludes the introducer character; expected form:
            //   renderer:VALUE | renderer=VALUE
            if (candidate.size() <= key.size())
            {
                return false;
            }
            if (!EqualsNoCaseAscii(candidate.substr(0, key.size()), key))
            {
                return false;
            }
            const char sep = candidate[key.size()];
            if (sep != ':' && sep != '=')
            {
                return false;
            }
            outValue = candidate.substr(key.size() + 1);
            return !outValue.empty();
        }
    }

    RendererToken FindCommandLineRendererOverride(std::string_view commandLine)
    {
        constexpr std::string_view kKey = "renderer";
        RendererToken result = RendererToken::None;

        size_t i = 0;
        while (i < commandLine.size())
        {
            // Split on whitespace without allocating.
            while (i < commandLine.size() &&
                   (commandLine[i] == ' ' || commandLine[i] == '\t'))
            {
                ++i;
            }
            const size_t start = i;
            while (i < commandLine.size() &&
                   commandLine[i] != ' ' && commandLine[i] != '\t')
            {
                ++i;
            }
            if (start == i)
            {
                break;
            }
            std::string_view token = commandLine.substr(start, i - start);
            char introducer = '\0';
            if (!token.empty() &&
                (token[0] == '/' || token[0] == '-' || token[0] == '+'))
            {
                introducer = token[0];
                token.remove_prefix(1);
            }
            if (introducer == '\0')
            {
                continue;
            }
            std::string_view value;
            if (TokenTextMatches(token, kKey, value))
            {
                // LAST occurrence wins, matching stock's sequential parse.
                const RendererToken parsed = ClassifyRendererToken(value);
                if (parsed != RendererToken::None)
                {
                    result = parsed;
                }
            }
        }
        return result;
    }

    BootRequest ResolveBootRequest(RenderProfiles::RendererBackend persistent,
                                   RendererToken cliToken)
    {
        // An explicit GL override is honored-but-unsupported: OpenShim cannot
        // transport GL, so this boot collapses to untouched stock selection
        // even when a transportable persistent preference exists (stock's own
        // /renderer:gl handling stays authoritative).
        if (cliToken == RendererToken::Dx9 || cliToken == RendererToken::Dx11)
        {
            BootRequest request;
            request.backend = cliToken == RendererToken::Dx11
                ? RenderProfiles::RendererBackend::DX11
                : RenderProfiles::RendererBackend::DX9;
            request.source = RequestSource::CliOverride;
            return request;
        }
        if (cliToken == RendererToken::Gl)
        {
            BootRequest stock;
            return stock;
        }
        if (persistent == RenderProfiles::RendererBackend::DX9 ||
            persistent == RenderProfiles::RendererBackend::DX11)
        {
            BootRequest request;
            request.backend = persistent;
            request.source = RequestSource::Persistent;
            return request;
        }
        // Auto preference or absent CLI collapse to stock selection.
        BootRequest stock;
        return stock;
    }

    const char* SubsystemNameFor(RenderProfiles::RendererBackend backend)
    {
        switch (backend)
        {
        case RenderProfiles::RendererBackend::DX9:
            return "Direct3D9 Rendering Subsystem";
        case RenderProfiles::RendererBackend::DX11:
            return "Direct3D11 Rendering Subsystem";
        default:
            return nullptr;
        }
    }

    bool BackendFromSubsystemName(std::string_view name,
                                  RenderProfiles::RendererBackend& out)
    {
        if (EqualsNoCaseAscii(name, kDx9Subsystem))
        {
            out = RenderProfiles::RendererBackend::DX9;
            return true;
        }
        if (EqualsNoCaseAscii(name, kDx11Subsystem))
        {
            out = RenderProfiles::RendererBackend::DX11;
            return true;
        }
        if (EqualsNoCaseAscii(name, kGlSubsystem))
        {
            // No GL representation in the resolver space; report absence and
            // let callers treat it as "not a transportable backend".
            return false;
        }
        return false;
    }

    std::string_view ExtractStockRenderSystemValue(std::string_view cfgText)
    {
        size_t pos = 0;
        while (pos < cfgText.size())
        {
            size_t eol = cfgText.find('\n', pos);
            const bool hasEol = eol != std::string_view::npos;
            if (!hasEol)
            {
                eol = cfgText.size();
            }
            std::string_view line = cfgText.substr(pos, eol - pos);
            // Trim trailing CR for CRLF text.
            while (!line.empty() && (line.back() == '\r' || line.back() == ' ' ||
                                     line.back() == '\t'))
            {
                line.remove_suffix(1);
            }
            // Trim leading whitespace.
            size_t lead = 0;
            while (lead < line.size() && (line[lead] == ' ' || line[lead] == '\t'))
            {
                ++lead;
            }
            line.remove_prefix(lead);
            if (line.size() > kRenderSystemKey.size() &&
                EqualsNoCaseAscii(line.substr(0, kRenderSystemKey.size()),
                                  kRenderSystemKey))
            {
                return line.substr(kRenderSystemKey.size());
            }
            pos = eol + 1;
        }
        return {};
    }

    bool ApplyTransportToConfigImage(std::string& cfgText,
                                     std::string_view subsystemName)
    {
        if (subsystemName.empty())
        {
            return false;
        }
        if (cfgText.empty())
        {
            return false;
        }
        for (const char c : cfgText)
        {
            const unsigned char uc = static_cast<unsigned char>(c);
            if (uc == '\0' || uc > 0x7Fu)
            {
                return false; // refuse-to-touch: not plain ASCII
            }
        }

        size_t pos = 0;
        while (pos < cfgText.size())
        {
            size_t eol = cfgText.find('\n', pos);
            const bool hasEol = eol != std::string_view::npos;
            if (!hasEol)
            {
                eol = cfgText.size();
            }
            // Locate the key span within [pos, eol) preserving EOL bytes.
            size_t lineEnd = eol;
            if (lineEnd > pos && cfgText[lineEnd - 1] == '\r')
            {
                --lineEnd;
            }
            size_t contentStart = pos;
            while (contentStart < lineEnd &&
                   (cfgText[contentStart] == ' ' || cfgText[contentStart] == '\t'))
            {
                ++contentStart;
            }
            const size_t contentLen = lineEnd - contentStart;
            if (contentLen > kRenderSystemKey.size() &&
                EqualsNoCaseAscii(
                    std::string_view(cfgText).substr(contentStart, kRenderSystemKey.size()),
                    kRenderSystemKey))
            {
                // Replace ONLY the value span; the "Render System=" key must
                // survive or the game's getSetting("Render System") read
                // returns empty and selection falls off the transport.
                const size_t valueStart = contentStart + kRenderSystemKey.size();
                cfgText.replace(valueStart, lineEnd - valueStart, subsystemName);
                return true;
            }
            pos = eol + 1;
        }

        // Line absent: prepend a minimal keyed line, keeping the existing
        // document intact behind it (stock writes this key first anyway).
        std::string replacement;
        replacement.reserve(kRenderSystemKey.size() + subsystemName.size() +
                            2 + cfgText.size());
        replacement.append(kRenderSystemKey);
        replacement.append(subsystemName);
        replacement.push_back('\r');
        replacement.push_back('\n');
        replacement.append(cfgText);
        cfgText.swap(replacement);
        return true;
    }

    std::string BuildMinimalConfigImage(std::string_view subsystemName)
    {
        if (subsystemName.empty())
        {
            return {};
        }
        std::string image;
        image.reserve(kRenderSystemKey.size() + subsystemName.size() + 2);
        image.append(kRenderSystemKey);
        image.append(subsystemName);
        image.push_back('\r');
        image.push_back('\n');
        return image;
    }

    std::string MakeTransportTempFileName(uint32_t processId)
    {
        // Fixed prefix/suffix keep the file recognizable and scoped next to
        // Ogre.cfg; the decimal PID makes concurrent game processes disjoint.
        std::string name;
        name.reserve(32);
        name.append("Ogre.cfg.openshim-");
        char digits[16] = {};
        size_t count = 0;
        do
        {
            digits[count++] = static_cast<char>('0' + processId % 10);
            processId /= 10;
        } while (processId != 0);
        while (count != 0)
        {
            name.push_back(digits[--count]);
        }
        name.append(".tmp");
        return name;
    }

    bool ParseTransportEnabled(std::string_view value)
    {
        while (!value.empty() &&
               (value.front() == ' ' || value.front() == '\t'))
        {
            value.remove_prefix(1);
        }
        while (!value.empty() &&
               (value.back() == ' ' || value.back() == '\t'))
        {
            value.remove_suffix(1);
        }
        if (EqualsNoCaseAscii(value, "0") || EqualsNoCaseAscii(value, "false") ||
            EqualsNoCaseAscii(value, "no") || EqualsNoCaseAscii(value, "off"))
        {
            return false;
        }
        return true;
    }

    bool IsStartupConfigFilename(std::string_view filename)
    {
        constexpr std::string_view kName = "Ogre.cfg";
        if (EqualsNoCaseAscii(filename, kName))
        {
            return true;
        }
        if (filename.size() <= kName.size())
        {
            return false;
        }
        const char separator = filename[filename.size() - kName.size() - 1];
        if (separator != '\\' && separator != '/')
        {
            return false;
        }
        return EqualsNoCaseAscii(filename.substr(filename.size() - kName.size()),
                                 kName);
    }

    const char* ReasonName(SelectionReason reason)
    {
        switch (reason)
        {
        case SelectionReason::None: return "none";
        case SelectionReason::CliOverride: return "cli-override";
        case SelectionReason::BackendUnavailable: return "backend-unavailable";
        case SelectionReason::UnresolvedMismatch: return "unresolved-mismatch";
        case SelectionReason::NoEstablishment: return "no-establishment";
        case SelectionReason::Stock: return "stock";
        default: return "unknown";
        }
    }

    SelectionReason ClassifyOutcome(const OutcomeInput& input)
    {
        if (!input.haveRequest)
        {
            return SelectionReason::Stock;
        }
        if (input.backendIdentified)
        {
            if (input.effective ==
                (input.requested == RenderProfiles::RendererBackend::DX11
                     ? RenderProfiles::ActiveBackend::DX11
                     : RenderProfiles::ActiveBackend::DX9))
            {
                return input.source == RequestSource::CliOverride
                           ? SelectionReason::CliOverride
                           : SelectionReason::None;
            }
            // Requested != effective: did stock burn the transport line?
            const auto requestedName = SubsystemNameFor(input.requested);
            if (requestedName == nullptr ||
                !EqualsNoCaseAscii(input.stockLineAfterBoot, requestedName))
            {
                return SelectionReason::BackendUnavailable;
            }
            return SelectionReason::UnresolvedMismatch;
        }
        return SelectionReason::NoEstablishment;
    }
}
