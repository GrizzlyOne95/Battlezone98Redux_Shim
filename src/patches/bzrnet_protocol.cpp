#include "bzrnet_protocol.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <charconv>
#include <mutex>
#include <string>
#include <unordered_map>
#include <utility>

namespace BZROpenShim
{
namespace
{
    constexpr std::array<BzrNetMessageInfo, 41> kMessages = {{
        {"Authorization", BzrNetMessageDirection::ClientToServer, BzrNetEvidence::BinaryConfirmed, "content"},
        {"DoEnterLounge", BzrNetMessageDirection::ClientToServer, BzrNetEvidence::BinaryConfirmed, "content"},
        {"DoExitLounge", BzrNetMessageDirection::ClientToServer, BzrNetEvidence::BinaryConfirmed, "content"},
        {"CreateLobby", BzrNetMessageDirection::ClientToServer, BzrNetEvidence::BinaryConfirmed, "content"},
        {"CreateGame", BzrNetMessageDirection::ClientToServer, BzrNetEvidence::BinaryConfirmed, "content"},
        {"DoJoinLobby", BzrNetMessageDirection::ClientToServer, BzrNetEvidence::BinaryConfirmed, "content"},
        {"DoExitLobby", BzrNetMessageDirection::ClientToServer, BzrNetEvidence::BinaryConfirmed, "content"},
        {"DoSetLobbyOwner", BzrNetMessageDirection::ClientToServer, BzrNetEvidence::BinaryConfirmed, "content"},
        {"SetLobbyData", BzrNetMessageDirection::ClientToServer, BzrNetEvidence::BinaryConfirmed, "content"},
        {"SetPlayerData", BzrNetMessageDirection::ClientToServer, BzrNetEvidence::BinaryConfirmed, "content"},
        {"DeleteLobbyData", BzrNetMessageDirection::ClientToServer, BzrNetEvidence::BinaryConfirmed, "content"},
        {"LockLobby", BzrNetMessageDirection::ClientToServer, BzrNetEvidence::BinaryConfirmed, "content"},
        {"SetLobbyMemberLimit", BzrNetMessageDirection::ClientToServer, BzrNetEvidence::BinaryConfirmed, "content"},
        {"DoSendChat", BzrNetMessageDirection::ClientToServer, BzrNetEvidence::BinaryConfirmed, "content"},
        {"DoP2PConnect", BzrNetMessageDirection::ClientToServer, BzrNetEvidence::BinaryConfirmed, "content"},
        {"DoP2PRoute", BzrNetMessageDirection::ClientToServer, BzrNetEvidence::BinaryConfirmed, "content"},
        {"DoUpdateWAN", BzrNetMessageDirection::ClientToServer, BzrNetEvidence::BinaryConfirmed, "content"},
        {"DoUpdateLAN", BzrNetMessageDirection::ClientToServer, BzrNetEvidence::BinaryConfirmed, "content"},
        {"Ping", BzrNetMessageDirection::ClientToServer, BzrNetEvidence::Inferred, "content"},
        {"DoPing", BzrNetMessageDirection::ClientToServer, BzrNetEvidence::Inferred, "content"},
        {"DoKickUser", BzrNetMessageDirection::ClientToServer, BzrNetEvidence::Inferred, "content"},
        {"OnAuthorization", BzrNetMessageDirection::ServerToClient, BzrNetEvidence::BinaryConfirmed, "data"},
        {"OnChatMessage", BzrNetMessageDirection::ServerToClient, BzrNetEvidence::BinaryConfirmed, "data"},
        {"OnHeartbeat", BzrNetMessageDirection::ServerToClient, BzrNetEvidence::BinaryConfirmed, "data"},
        {"OnWANUpdated", BzrNetMessageDirection::ServerToClient, BzrNetEvidence::BinaryConfirmed, "data"},
        {"OnLANUpdated", BzrNetMessageDirection::ServerToClient, BzrNetEvidence::BinaryConfirmed, "data"},
        {"OnLobbyMemberListChanged", BzrNetMessageDirection::ServerToClient, BzrNetEvidence::BinaryConfirmed, "data"},
        {"OnLobbyDataChanged", BzrNetMessageDirection::ServerToClient, BzrNetEvidence::BinaryConfirmed, "data"},
        {"OnUserDataChanged", BzrNetMessageDirection::ServerToClient, BzrNetEvidence::BinaryConfirmed, "data"},
        {"OnLobbyListChanged", BzrNetMessageDirection::ServerToClient, BzrNetEvidence::BinaryConfirmed, "data"},
        {"OnLobbyChanged", BzrNetMessageDirection::ServerToClient, BzrNetEvidence::BinaryConfirmed, "data"},
        {"OnLobbyCreated", BzrNetMessageDirection::ServerToClient, BzrNetEvidence::BinaryConfirmed, "data"},
        {"OnLobbyRemoved", BzrNetMessageDirection::ServerToClient, BzrNetEvidence::BinaryConfirmed, "data"},
        {"OnLobbyJoined", BzrNetMessageDirection::ServerToClient, BzrNetEvidence::BinaryConfirmed, "data"},
        {"OnDoExitLobby", BzrNetMessageDirection::ServerToClient, BzrNetEvidence::BinaryConfirmed, "data"},
        {"OnDoExitLounge", BzrNetMessageDirection::ServerToClient, BzrNetEvidence::BinaryConfirmed, "data"},
        {"OnFailure", BzrNetMessageDirection::ServerToClient, BzrNetEvidence::BinaryConfirmed, "data"},
        {"OnWhitelistUpdated", BzrNetMessageDirection::ServerToClient, BzrNetEvidence::BinaryConfirmed, "data"},
        {"OnLobbyMemberP2PConnect", BzrNetMessageDirection::ServerToClient, BzrNetEvidence::BinaryConfirmed, "data"},
        {"OnP2PRoute", BzrNetMessageDirection::ServerToClient, BzrNetEvidence::BinaryConfirmed, "data"},
        {"OnServerShutdown", BzrNetMessageDirection::ServerToClient, BzrNetEvidence::BinaryConfirmed, "data"},
    }};

    std::mutex g_AliasMutex;
    std::unordered_map<std::string, std::string> g_IdentityAliases;
    std::unordered_map<std::string, std::string> g_EndpointAliases;

    bool IsWs(char c)
    {
        return c == ' ' || c == '\t' || c == '\r' || c == '\n';
    }

    size_t SkipWs(std::string_view text, size_t pos)
    {
        while (pos < text.size() && IsWs(text[pos]))
            ++pos;
        return pos;
    }

    bool ParseJsonString(std::string_view text, size_t quotePos, size_t& outEnd, std::string* decoded)
    {
        if (quotePos >= text.size() || text[quotePos] != '"')
            return false;
        std::string value;
        for (size_t i = quotePos + 1; i < text.size(); ++i)
        {
            const char c = text[i];
            if (c == '"')
            {
                outEnd = i + 1;
                if (decoded)
                    *decoded = std::move(value);
                return true;
            }
            if (c == '\\')
            {
                if (++i >= text.size())
                    return false;
                const char esc = text[i];
                switch (esc)
                {
                    case '"': value.push_back('"'); break;
                    case '\\': value.push_back('\\'); break;
                    case '/': value.push_back('/'); break;
                    case 'b': value.push_back('\b'); break;
                    case 'f': value.push_back('\f'); break;
                    case 'n': value.push_back('\n'); break;
                    case 'r': value.push_back('\r'); break;
                    case 't': value.push_back('\t'); break;
                    case 'u':
                        if (i + 4 >= text.size()) return false;
                        value.append("\\u");
                        value.append(text.substr(i + 1, 4));
                        i += 4;
                        break;
                    default: return false;
                }
            }
            else
            {
                value.push_back(c);
            }
        }
        return false;
    }

    std::string JsonQuote(std::string_view value)
    {
        std::string out;
        out.reserve(value.size() + 2);
        out.push_back('"');
        for (const char c : value)
        {
            switch (c)
            {
                case '"': out += "\\\""; break;
                case '\\': out += "\\\\"; break;
                case '\b': out += "\\b"; break;
                case '\f': out += "\\f"; break;
                case '\n': out += "\\n"; break;
                case '\r': out += "\\r"; break;
                case '\t': out += "\\t"; break;
                default:
                    if (static_cast<unsigned char>(c) < 0x20)
                        out += '?';
                    else
                        out.push_back(c);
                    break;
            }
        }
        out.push_back('"');
        return out;
    }

    bool FindMemberValue(std::string_view json, std::string_view wantedKey, size_t& valueStart, size_t& valueEnd, std::string* stringValue)
    {
        size_t pos = 0;
        while (pos < json.size())
        {
            pos = json.find('"', pos);
            if (pos == std::string_view::npos)
                return false;
            size_t keyEnd = 0;
            std::string key;
            if (!ParseJsonString(json, pos, keyEnd, &key))
                return false;
            size_t colon = SkipWs(json, keyEnd);
            if (colon >= json.size() || json[colon] != ':')
            {
                pos = keyEnd;
                continue;
            }
            size_t start = SkipWs(json, colon + 1);
            if (start >= json.size())
                return false;

            size_t end = start;
            std::string decoded;
            if (json[start] == '"')
            {
                if (!ParseJsonString(json, start, end, &decoded))
                    return false;
            }
            else if (json[start] == '[' || json[start] == '{')
            {
                const char open = json[start];
                const char close = open == '[' ? ']' : '}';
                int depth = 0;
                bool inString = false;
                bool escaped = false;
                for (size_t i = start; i < json.size(); ++i)
                {
                    const char c = json[i];
                    if (inString)
                    {
                        if (escaped) escaped = false;
                        else if (c == '\\') escaped = true;
                        else if (c == '"') inString = false;
                        continue;
                    }
                    if (c == '"') { inString = true; continue; }
                    if (c == open) ++depth;
                    else if (c == close && --depth == 0) { end = i + 1; break; }
                }
                if (end == start)
                    return false;
            }
            else
            {
                end = start;
                while (end < json.size() && json[end] != ',' && json[end] != '}' && json[end] != ']')
                    ++end;
                while (end > start && IsWs(json[end - 1]))
                    --end;
            }

            if (key == wantedKey)
            {
                valueStart = start;
                valueEnd = end;
                if (stringValue)
                    *stringValue = std::move(decoded);
                return true;
            }
            pos = keyEnd;
        }
        return false;
    }

    std::string AliasFor(std::unordered_map<std::string, std::string>& table, std::string_view raw, const char* prefix)
    {
        std::lock_guard<std::mutex> guard(g_AliasMutex);
        const std::string key(raw);
        const auto it = table.find(key);
        if (it != table.end())
            return it->second;
        const std::string alias = std::string(prefix) + std::to_string(table.size() + 1);
        table.emplace(key, alias);
        return alias;
    }

    bool ReplaceMember(std::string& json, std::string_view key, const std::string& replacement, size_t* originalStringLength)
    {
        size_t start = 0;
        size_t end = 0;
        std::string decoded;
        if (!FindMemberValue(json, key, start, end, &decoded))
            return false;
        if (originalStringLength)
            *originalStringLength = decoded.size();
        json.replace(start, end - start, replacement);
        return true;
    }

    void AliasStringMember(std::string& json, std::string_view key, std::unordered_map<std::string, std::string>& table, const char* prefix)
    {
        size_t start = 0;
        size_t end = 0;
        std::string decoded;
        if (!FindMemberValue(json, key, start, end, &decoded) || decoded.empty())
            return;
        json.replace(start, end - start, JsonQuote(AliasFor(table, decoded, prefix)));
    }

    uint32_t ReadU32Le(const uint8_t* p)
    {
        return static_cast<uint32_t>(p[0]) |
            (static_cast<uint32_t>(p[1]) << 8) |
            (static_cast<uint32_t>(p[2]) << 16) |
            (static_cast<uint32_t>(p[3]) << 24);
    }
}

const BzrNetMessageInfo* LookupBzrNetMessage(std::string_view type)
{
    for (const auto& message : kMessages)
    {
        if (type == message.name)
            return &message;
    }
    return nullptr;
}

bool ExtractBzrNetMessageType(std::string_view json, std::string& outType)
{
    size_t start = 0;
    size_t end = 0;
    std::string decoded;
    if (!FindMemberValue(json, "type", start, end, &decoded) || decoded.empty())
        return false;
    outType = std::move(decoded);
    return true;
}

bool TryExtractBzrNetJsonInt(std::string_view json, std::string_view key, int64_t& outValue)
{
    size_t start = 0;
    size_t end = 0;
    if (!FindMemberValue(json, key, start, end, nullptr) || start >= end || json[start] == '"')
        return false;
    const std::string_view token = json.substr(start, end - start);
    int64_t value = 0;
    const auto result = std::from_chars(token.data(), token.data() + token.size(), value);
    if (result.ec != std::errc{} || result.ptr != token.data() + token.size())
        return false;
    outValue = value;
    return true;
}

bool TryExtractBzrNetJsonBool(std::string_view json, std::string_view key, bool& outValue)
{
    size_t start = 0;
    size_t end = 0;
    if (!FindMemberValue(json, key, start, end, nullptr))
        return false;
    const auto token = json.substr(start, end - start);
    if (token == "true") { outValue = true; return true; }
    if (token == "false") { outValue = false; return true; }
    return false;
}

const char* BzrNetEvidenceName(BzrNetEvidence evidence)
{
    switch (evidence)
    {
        case BzrNetEvidence::BinaryConfirmed: return "binary_confirmed";
        case BzrNetEvidence::CaptureConfirmed: return "capture_confirmed";
        case BzrNetEvidence::HighConfidence: return "high_confidence";
        case BzrNetEvidence::Inferred: return "inferred";
        case BzrNetEvidence::ReplacementOnly: return "replacement_only";
        default: return "unknown";
    }
}

const char* BzrNetDirectionName(BzrNetMessageDirection direction)
{
    switch (direction)
    {
        case BzrNetMessageDirection::ClientToServer: return "outbound";
        case BzrNetMessageDirection::ServerToClient: return "inbound";
        default: return "unknown";
    }
}

BzrNetSanitizedMessage SanitizeBzrNetJson(std::string_view json, bool privateForensic)
{
    BzrNetSanitizedMessage result;
    result.json.assign(json.begin(), json.end());

    size_t ticketLength = 0;
    if (ReplaceMember(result.json, "steamAppTicket", JsonQuote("<REDACTED>"), &ticketLength))
    {
        result.authTicketRedacted = true;
        result.authTicketLength = ticketLength;
    }

    size_t passwordLength = 0;
    if (ReplaceMember(result.json, "password", JsonQuote("<REDACTED>"), &passwordLength))
    {
        result.passwordRedacted = true;
        result.passwordLength = passwordLength;
    }

    if (!privateForensic)
    {
        for (const auto key : {"userId", "player", "speakerId", "owner", "member"})
            AliasStringMember(result.json, key, g_IdentityAliases, "player_");
        for (const auto key : {"wanAddress"})
            AliasStringMember(result.json, key, g_EndpointAliases, "endpoint_");

        size_t start = 0;
        size_t end = 0;
        if (FindMemberValue(result.json, "lanAddresses", start, end, nullptr) &&
            start < end && result.json[start] == '[')
        {
            std::string replacement = "[";
            size_t pos = start + 1;
            bool first = true;
            while (pos < end)
            {
                pos = result.json.find('"', pos);
                if (pos == std::string::npos || pos >= end)
                    break;
                size_t stringEnd = 0;
                std::string decoded;
                if (!ParseJsonString(result.json, pos, stringEnd, &decoded) || stringEnd > end)
                    break;
                if (!first) replacement += ',';
                replacement += JsonQuote(AliasFor(g_EndpointAliases, decoded, "endpoint_"));
                first = false;
                pos = stringEnd;
            }
            replacement += ']';
            result.json.replace(start, end - start, replacement);
        }
    }

    return result;
}

void ResetBzrNetSanitizationAliases()
{
    std::lock_guard<std::mutex> guard(g_AliasMutex);
    g_IdentityAliases.clear();
    g_EndpointAliases.clear();
}

std::string SanitizeBzrNetEndpoint(std::string_view endpoint, bool privateForensic)
{
    if (privateForensic || endpoint.empty())
        return std::string(endpoint);
    return AliasFor(g_EndpointAliases, endpoint, "endpoint_");
}

std::string SanitizeBzrNetIdentity(std::string_view identity, bool privateForensic)
{
    if (privateForensic || identity.empty())
        return std::string(identity);
    return AliasFor(g_IdentityAliases, identity, "player_");
}

BzrUdpControlInfo DecodeBzrUdpControl(const uint8_t* data, size_t length)
{
    BzrUdpControlInfo info;
    if (!data || length < 2)
        return info;

    info.marker.assign(reinterpret_cast<const char*>(data), 2);
    if (info.marker == "PP")
    {
        info.recognized = true;
        info.likelyMeaning = "peer_ping_request";
        info.evidence = BzrNetEvidence::HighConfidence;
        if (length >= 22)
        {
            info.field0 = ReadU32Le(data + 2);
            info.field1 = ReadU32Le(data + 6);
            info.field2 = ReadU32Le(data + 10);
            info.field3 = ReadU32Le(data + 14);
            info.field4 = ReadU32Le(data + 18);
            info.fieldCount = 5;
        }
    }
    else if (info.marker == "PR")
    {
        info.recognized = true;
        info.likelyMeaning = "peer_ping_response";
        info.evidence = BzrNetEvidence::HighConfidence;
        if (length >= 14)
        {
            info.field0 = ReadU32Le(data + 2);
            info.field1 = ReadU32Le(data + 6);
            info.field2 = ReadU32Le(data + 10);
            info.fieldCount = 3;
        }
    }
    else if (info.marker == "PB")
    {
        info.recognized = true;
        info.likelyMeaning = "peer_timing_sideband";
        info.evidence = BzrNetEvidence::Inferred;
        if (length >= 10)
        {
            info.field0 = ReadU32Le(data + 2);
            info.field1 = ReadU32Le(data + 6);
            info.fieldCount = 2;
        }
    }
    else if (info.marker == "SS")
    {
        info.recognized = true;
        info.likelyMeaning = "peer_session_sync";
        info.evidence = BzrNetEvidence::HighConfidence;
    }
    else if (info.marker == "KA")
    {
        info.recognized = true;
        info.likelyMeaning = "peer_keepalive";
        info.evidence = BzrNetEvidence::HighConfidence;
    }
    else if (info.marker == "PO" || info.marker == "PZ")
    {
        info.recognized = true;
        info.likelyMeaning = info.marker == "PO" ? "peer_control_unknown_po" : "peer_control_unknown_pz";
        info.evidence = BzrNetEvidence::Inferred;
    }
    return info;
}
}
