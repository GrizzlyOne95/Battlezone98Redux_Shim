#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>

namespace BZROpenShim
{
    enum class BzrNetEvidence : uint8_t
    {
        Unknown = 0,
        BinaryConfirmed,
        CaptureConfirmed,
        HighConfidence,
        Inferred,
        ReplacementOnly,
    };

    enum class BzrNetMessageDirection : uint8_t
    {
        Unknown = 0,
        ClientToServer,
        ServerToClient,
    };

    struct BzrNetMessageInfo
    {
        const char* name = nullptr;
        BzrNetMessageDirection direction = BzrNetMessageDirection::Unknown;
        BzrNetEvidence evidence = BzrNetEvidence::Unknown;
        const char* envelope = nullptr;
    };

    struct BzrNetSanitizedMessage
    {
        std::string json;
        bool authTicketRedacted = false;
        size_t authTicketLength = 0;
        bool passwordRedacted = false;
        size_t passwordLength = 0;
    };

    struct BzrUdpControlInfo
    {
        bool recognized = false;
        std::string marker;
        std::string likelyMeaning;
        BzrNetEvidence evidence = BzrNetEvidence::Unknown;
        uint32_t field0 = 0;
        uint32_t field1 = 0;
        uint32_t field2 = 0;
        uint32_t field3 = 0;
        uint32_t field4 = 0;
        uint32_t fieldCount = 0;
    };

    const BzrNetMessageInfo* LookupBzrNetMessage(std::string_view type);
    bool ExtractBzrNetMessageType(std::string_view json, std::string& outType);
    bool TryExtractBzrNetJsonInt(std::string_view json, std::string_view key, int64_t& outValue);
    bool TryExtractBzrNetJsonBool(std::string_view json, std::string_view key, bool& outValue);
    const char* BzrNetEvidenceName(BzrNetEvidence evidence);
    const char* BzrNetDirectionName(BzrNetMessageDirection direction);

    // Ordinary trace output always redacts authentication tickets and lobby
    // passwords. In sanitized mode, identity and endpoint fields are also
    // replaced with stable per-process aliases.
    BzrNetSanitizedMessage SanitizeBzrNetJson(std::string_view json, bool privateForensic);
    void ResetBzrNetSanitizationAliases();
    std::string SanitizeBzrNetEndpoint(std::string_view endpoint, bool privateForensic);
    std::string SanitizeBzrNetIdentity(std::string_view identity, bool privateForensic);

    // Read-only decoder for the known two-byte BZR UDP control markers. The
    // input may be either the marker payload itself or a common-header packet
    // whose payload begins with the marker; callers should pass the marker
    // offset they have already established.
    BzrUdpControlInfo DecodeBzrUdpControl(const uint8_t* data, size_t length);
}
