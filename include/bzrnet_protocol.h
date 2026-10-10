#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

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

    // Passive reassembly of one direction of a WebSocket connection, as seen
    // by the socket hooks. The HTTP upgrade exchange is skipped up to its
    // blank line; after that, frames are unmasked and fragmented messages
    // joined. Only text (0x1) and binary (0x2) messages are returned; control
    // frames are consumed silently. Anything larger than `maxBytes`, buffered
    // or declared, drops the direction's buffered state rather than growing.
    //
    // The relay capture in net_optimizer and the structured BZRNet trace each
    // had a copy of this parser (audit P2-3).
    struct WebSocketStreamState
    {
        bool handshakeComplete = false;
        uint8_t fragmentedOpcode = 0;
        std::vector<uint8_t> pending;
        std::vector<uint8_t> fragmented;
    };

    struct WebSocketMessage
    {
        uint8_t opcode = 0;
        std::vector<uint8_t> payload;
    };

    // Offset just past the first "\r\n\r\n", or std::string::npos.
    size_t FindHttpHeaderEnd(const std::vector<uint8_t>& data);

    // Appends every message completed by `bytes` to `out`, in order.
    void FeedWebSocketStream(
        WebSocketStreamState& state,
        const uint8_t* bytes,
        size_t length,
        size_t maxBytes,
        std::vector<WebSocketMessage>& out);

    // --- Outbound platform-ticket withholding (client -> custom server) ---
    //
    // Scrubs the Steam/GOG app ticket out of client-to-server WebSocket text
    // frames IN PLACE and without changing a byte count: the ticket string is
    // replaced by "withheld" (or "" when the value is shorter than the marker)
    // and the rest of the old value becomes JSON whitespace after the closing
    // quote. Frame header, length and mask key are untouched; the payload is
    // re-masked with the frame's own key.
    //
    // Fail-closed: anything that could carry a ticket but cannot be rewritten
    // safely (a text frame split across calls, a fragmented message, RSV bits
    // such as permessage-deflate, an oversized or unparseable frame) yields
    // Rejected, and the state stays rejected. The caller must not send the
    // bytes. Non-text frames, and text frames without a ticket key, pass
    // through untouched.
    constexpr size_t kTicketScrubMaxPayload = 256 * 1024;

    enum class WebSocketScrubStatus { Unchanged, Rewritten, Rejected };

    struct WebSocketTicketRewrite
    {
        const char* key = "";
        size_t length = 0;   // original value length in bytes; never the value
    };

    struct WebSocketTicketScrubState
    {
        enum class Phase : uint8_t { Handshake, FrameHeader, FramePayload, Passthrough };
        Phase phase = Phase::Handshake;
        bool rejected = false;
        std::vector<uint8_t> handshake;
        uint8_t header[14] = {};
        size_t headerLength = 0;
        uint8_t opcode = 0;
        uint8_t mask[4] = {};
        uint64_t payloadRemaining = 0;
    };

    // `data` is a private copy of the bytes about to be sent. `rewrites` is
    // appended to; `rejectReason` (optional) receives a static string.
    WebSocketScrubStatus ScrubWebSocketTickets(
        WebSocketTicketScrubState& state,
        uint8_t* data,
        size_t length,
        std::vector<WebSocketTicketRewrite>& rewrites,
        const char** rejectReason = nullptr);

    // Per-call, frame-aligned mode for IOCP-style senders that may re-issue a
    // partial tail, so no stream state can be trusted across calls. One call
    // (the spans are its scatter/gather buffers) must be either the HTTP
    // upgrade request ("GET " ... CRLF CRLF) or a whole number of complete
    // frames starting at a frame boundary; anything else is Rejected. A
    // rewrite is scattered back into the spans in place (length unchanged).
    struct ByteSpan
    {
        uint8_t* data = nullptr;
        size_t length = 0;
    };
    constexpr size_t kTicketScrubMaxCallBytes = 512 * 1024;

    WebSocketScrubStatus ScrubWebSocketTicketsPerCall(
        const ByteSpan* spans,
        size_t count,
        std::vector<WebSocketTicketRewrite>& rewrites,
        const char** rejectReason = nullptr);
}
