#include "bzrnet_protocol.h"
#include "json_escape.h"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include "test_check.h"

using OpenShimTest::Check;

using namespace BZROpenShim;

namespace
{
    std::vector<uint8_t> Bytes(const std::string& text)
    {
        return std::vector<uint8_t>(text.begin(), text.end());
    }

    // One frame; `mask` of nullptr sends it unmasked.
    std::vector<uint8_t> Frame(bool fin, uint8_t opcode, const std::string& payload, const uint8_t* mask = nullptr)
    {
        std::vector<uint8_t> frame;
        frame.push_back(static_cast<uint8_t>((fin ? 0x80u : 0u) | opcode));
        const uint8_t maskBit = mask ? 0x80u : 0u;
        const size_t length = payload.size();
        if (length < 126)
        {
            frame.push_back(static_cast<uint8_t>(maskBit | length));
        }
        else if (length <= 0xFFFF)
        {
            frame.push_back(static_cast<uint8_t>(maskBit | 126));
            frame.push_back(static_cast<uint8_t>(length >> 8));
            frame.push_back(static_cast<uint8_t>(length & 0xFF));
        }
        else
        {
            frame.push_back(static_cast<uint8_t>(maskBit | 127));
            for (int shift = 56; shift >= 0; shift -= 8)
                frame.push_back(static_cast<uint8_t>((static_cast<uint64_t>(length) >> shift) & 0xFF));
        }
        if (mask)
            frame.insert(frame.end(), mask, mask + 4);
        for (size_t i = 0; i < length; ++i)
        {
            const uint8_t byte = static_cast<uint8_t>(payload[i]);
            frame.push_back(mask ? static_cast<uint8_t>(byte ^ mask[i % 4]) : byte);
        }
        return frame;
    }

    std::string Text(const WebSocketMessage& message)
    {
        return std::string(message.payload.begin(), message.payload.end());
    }

    void TestWebSocketStream()
    {
        const size_t kMax = 1024 * 1024;
        const std::string handshake = "GET /ws HTTP/1.1\r\nUpgrade: websocket\r\n\r\n";

        // Handshake, then an unmasked text frame and a masked binary frame in one read.
        {
            WebSocketStreamState state;
            std::vector<uint8_t> input = Bytes(handshake);
            const auto text = Frame(true, 0x1, R"({"type":"Ping"})");
            const uint8_t mask[4] = { 0x11, 0x22, 0x33, 0x44 };
            const auto binary = Frame(true, 0x2, "abc", mask);
            input.insert(input.end(), text.begin(), text.end());
            input.insert(input.end(), binary.begin(), binary.end());
            std::vector<WebSocketMessage> out;
            FeedWebSocketStream(state, input.data(), input.size(), kMax, out);
            Check(state.handshakeComplete, "ws handshake skipped");
            Check(out.size() == 2, "ws two messages");
            Check(out.size() == 2 && out[0].opcode == 0x1 && Text(out[0]) == R"({"type":"Ping"})", "ws text frame");
            Check(out.size() == 2 && out[1].opcode == 0x2 && Text(out[1]) == "abc", "ws masked binary frame");
            Check(state.pending.empty(), "ws nothing left over");
        }

        // A frame split across reads is held until complete.
        {
            WebSocketStreamState state;
            state.handshakeComplete = true;
            const auto frame = Frame(true, 0x1, "hello");
            std::vector<WebSocketMessage> out;
            FeedWebSocketStream(state, frame.data(), 3, kMax, out);
            Check(out.empty() && state.pending.size() == 3, "ws partial frame held");
            FeedWebSocketStream(state, frame.data() + 3, frame.size() - 3, kMax, out);
            Check(out.size() == 1 && Text(out[0]) == "hello", "ws partial frame completed");
        }

        // 16-bit and 64-bit extended lengths.
        {
            WebSocketStreamState state;
            state.handshakeComplete = true;
            const std::string medium(300, 'm');
            const std::string large(70000, 'L');
            auto input = Frame(true, 0x1, medium);
            const auto second = Frame(true, 0x2, large);
            input.insert(input.end(), second.begin(), second.end());
            std::vector<WebSocketMessage> out;
            FeedWebSocketStream(state, input.data(), input.size(), kMax, out);
            Check(out.size() == 2 && out[0].payload.size() == 300 && out[1].payload.size() == 70000, "ws extended lengths");
        }

        // Fragmented text with a ping interleaved; the ping is consumed silently.
        {
            WebSocketStreamState state;
            state.handshakeComplete = true;
            auto input = Frame(false, 0x1, "hel");
            const auto ping = Frame(true, 0x9, "");
            const auto tail = Frame(true, 0x0, "lo");
            input.insert(input.end(), ping.begin(), ping.end());
            input.insert(input.end(), tail.begin(), tail.end());
            std::vector<WebSocketMessage> out;
            FeedWebSocketStream(state, input.data(), input.size(), kMax, out);
            Check(out.size() == 1 && out[0].opcode == 0x1 && Text(out[0]) == "hello", "ws fragments joined");
            Check(state.fragmented.empty() && state.fragmentedOpcode == 0, "ws fragment state cleared");
        }

        // A continuation with no message in progress is dropped.
        {
            WebSocketStreamState state;
            state.handshakeComplete = true;
            const auto stray = Frame(true, 0x0, "orphan");
            std::vector<WebSocketMessage> out;
            FeedWebSocketStream(state, stray.data(), stray.size(), kMax, out);
            Check(out.empty(), "ws stray continuation dropped");
        }

        // Oversize: a declared length above the cap drops the buffered state.
        {
            WebSocketStreamState state;
            state.handshakeComplete = true;
            const auto frame = Frame(true, 0x1, std::string(200, 'x'));
            std::vector<WebSocketMessage> out;
            FeedWebSocketStream(state, frame.data(), 4, 100, out);
            Check(out.empty() && state.pending.empty(), "ws declared oversize resets");
            const auto big = Bytes(std::string(150, 'y'));
            FeedWebSocketStream(state, big.data(), big.size(), 100, out);
            Check(out.empty() && state.pending.empty(), "ws buffered oversize resets");
        }

        // No handshake terminator yet: bytes are held, nothing parsed.
        {
            WebSocketStreamState state;
            const auto partial = Bytes("GET /ws HTTP/1.1\r\nUpgrade: web");
            std::vector<WebSocketMessage> out;
            FeedWebSocketStream(state, partial.data(), partial.size(), kMax, out);
            Check(!state.handshakeComplete && out.empty(), "ws handshake pending");
            Check(FindHttpHeaderEnd(Bytes("a\r\n\r\nb")) == 5, "http header end offset");
            Check(FindHttpHeaderEnd(Bytes("a\r\nb")) == std::string::npos, "http header end missing");
        }
    }

    void TestJsonEscape()
    {
        Check(EscapeJsonString("plain") == "plain", "json plain");
        Check(EscapeJsonString("a\"b\\c") == "a\\\"b\\\\c", "json quote and backslash");
        Check(EscapeJsonString("\n\r\t\b\f") == "\\n\\r\\t\\b\\f", "json named escapes");
        Check(EscapeJsonString(std::string("\x01\x1f", 2)) == "\\u0001\\u001f", "json control bytes as \\u00XX");
        Check(EscapeJsonString(std::string("\0", 1)) == "\\u0000", "json NUL");
        Check(EscapeJsonString("caf\xc3\xa9") == "caf\xc3\xa9", "json UTF-8 passes through");
    }
}


namespace
{
    // Unmasked payload of the single frame in `frame`.
    std::string FramePayloadText(const std::vector<uint8_t>& frame)
    {
        const bool masked = (frame[1] & 0x80u) != 0;
        size_t offset = 2;
        uint64_t length = frame[1] & 0x7Fu;
        if (length == 126) { length = (static_cast<uint64_t>(frame[2]) << 8) | frame[3]; offset = 4; }
        uint8_t mask[4] = {};
        if (masked) { std::memcpy(mask, frame.data() + offset, 4); offset += 4; }
        std::string out;
        for (uint64_t i = 0; i < length; ++i)
            out.push_back(static_cast<char>(frame[offset + static_cast<size_t>(i)] ^ (masked ? mask[static_cast<size_t>(i) % 4] : 0)));
        return out;
    }

    const char kClientHandshake[] =
        "GET /ws HTTP/1.1\r\nHost: x\r\nUpgrade: websocket\r\nConnection: Upgrade\r\n\r\n";

    WebSocketTicketScrubState ReadyState()
    {
        WebSocketTicketScrubState state;
        std::vector<uint8_t> hs = Bytes(kClientHandshake);
        std::vector<WebSocketTicketRewrite> none;
        Check(ScrubWebSocketTickets(state, hs.data(), hs.size(), none) == WebSocketScrubStatus::Unchanged,
            "handshake passes untouched");
        return state;
    }

    void TestTicketWithholding()
    {
        const uint8_t mask[4] = { 0x12, 0x34, 0x56, 0x78 };
        const std::string ticket(40, 'A');

        // steamAppTicket: rewritten in place, same length, valid JSON.
        {
            WebSocketTicketScrubState state = ReadyState();
            const std::string json = "{\"type\":\"Authorization\",\"steamAppTicket\":\"" + ticket + "\",\"name\":\"bob\"}";
            std::vector<uint8_t> frame = Frame(true, 0x1, json, mask);
            const std::vector<uint8_t> original = frame;
            std::vector<WebSocketTicketRewrite> rewrites;
            Check(ScrubWebSocketTickets(state, frame.data(), frame.size(), rewrites) == WebSocketScrubStatus::Rewritten,
                "steam ticket rewritten");
            Check(frame.size() == original.size(), "length preserved");
            Check(std::equal(frame.begin(), frame.begin() + 6, original.begin()), "header and mask key untouched");
            const std::string out = FramePayloadText(frame);
            Check(out.size() == json.size(), "payload length preserved");
            Check(out.find("\"steamAppTicket\":\"withheld\"") != std::string::npos, "marker present");
            Check(out.find(ticket) == std::string::npos, "ticket bytes gone");
            Check(out.find("\"name\":\"bob\"") != std::string::npos, "other fields intact");
            Check(out.find("\"type\":\"Authorization\"") != std::string::npos, "type intact");
            Check(rewrites.size() == 1 && std::string(rewrites[0].key) == "steamAppTicket" &&
                rewrites[0].length == ticket.size(), "rewrite report");
            // The padded gap must be whitespace only, directly after the closing quote.
            const size_t q = out.find("withheld\"") + 9;
            Check(out.substr(q, ticket.size() - 8).find_first_not_of(' ') == std::string::npos, "padding is spaces");
        }

        // gogAppTicket.
        {
            WebSocketTicketScrubState state = ReadyState();
            const std::string json = "{\"type\":\"Authorization\",\"gogAppTicket\":\"" + ticket + "\"}";
            std::vector<uint8_t> frame = Frame(true, 0x1, json, mask);
            std::vector<WebSocketTicketRewrite> rewrites;
            Check(ScrubWebSocketTickets(state, frame.data(), frame.size(), rewrites) == WebSocketScrubStatus::Rewritten,
                "gog ticket rewritten");
            Check(FramePayloadText(frame).find("\"gogAppTicket\":\"withheld\"") != std::string::npos, "gog marker present");
        }

        // 16-bit extended length frame.
        {
            WebSocketTicketScrubState state = ReadyState();
            const std::string longTicket(500, 'Z');
            const std::string json = "{\"type\":\"Authorization\",\"steamAppTicket\":\"" + longTicket + "\"}";
            std::vector<uint8_t> frame = Frame(true, 0x1, json, mask);
            Check(frame[1] == (0x80 | 126), "frame uses 16-bit length");
            const size_t before = frame.size();
            std::vector<WebSocketTicketRewrite> rewrites;
            Check(ScrubWebSocketTickets(state, frame.data(), frame.size(), rewrites) == WebSocketScrubStatus::Rewritten,
                "extended-length frame rewritten");
            Check(frame.size() == before, "extended length preserved");
            const std::string out = FramePayloadText(frame);
            Check(out.size() == json.size() && out.find("withheld") != std::string::npos &&
                out.find(longTicket) == std::string::npos, "extended payload rewritten");
        }

        // A value shorter than the marker becomes "".
        {
            WebSocketTicketScrubState state = ReadyState();
            const std::string json = "{\"steamAppTicket\":\"abc\",\"x\":1}";
            std::vector<uint8_t> frame = Frame(true, 0x1, json, mask);
            std::vector<WebSocketTicketRewrite> rewrites;
            Check(ScrubWebSocketTickets(state, frame.data(), frame.size(), rewrites) == WebSocketScrubStatus::Rewritten,
                "short ticket rewritten");
            const std::string out = FramePayloadText(frame);
            Check(out.size() == json.size() && out.find("\"steamAppTicket\":\"\"") != std::string::npos &&
                out.find("abc") == std::string::npos, "short ticket becomes empty string");
        }

        // Non-auth frame: untouched byte for byte; ping too.
        {
            WebSocketTicketScrubState state = ReadyState();
            std::vector<uint8_t> frame = Frame(true, 0x1, "{\"type\":\"DoChat\",\"text\":\"hi\"}", mask);
            std::vector<uint8_t> ping = Frame(true, 0x9, "pp", mask);
            frame.insert(frame.end(), ping.begin(), ping.end());
            const std::vector<uint8_t> original = frame;
            std::vector<WebSocketTicketRewrite> rewrites;
            Check(ScrubWebSocketTickets(state, frame.data(), frame.size(), rewrites) == WebSocketScrubStatus::Unchanged,
                "non-auth frame unchanged");
            Check(frame == original && rewrites.empty(), "non-auth bytes identical");
        }

        // Two frames in one call, ticket in the second; and a header/payload split
        // across calls is still handled when the payload arrives whole.
        {
            WebSocketTicketScrubState state = ReadyState();
            std::vector<uint8_t> a = Frame(true, 0x1, "{\"type\":\"DoPing\"}", mask);
            std::vector<uint8_t> b = Frame(true, 0x1, "{\"authTicket\":\"" + ticket + "\"}", mask);
            a.insert(a.end(), b.begin(), b.end());
            std::vector<WebSocketTicketRewrite> rewrites;
            Check(ScrubWebSocketTickets(state, a.data(), a.size(), rewrites) == WebSocketScrubStatus::Rewritten,
                "ticket in second frame rewritten");

            std::vector<uint8_t> c = Frame(true, 0x1, "{\"platformTicket\":\"" + ticket + "\"}", mask);
            std::vector<uint8_t> head(c.begin(), c.begin() + 3);
            std::vector<uint8_t> rest(c.begin() + 3, c.end());
            Check(ScrubWebSocketTickets(state, head.data(), head.size(), rewrites) == WebSocketScrubStatus::Unchanged,
                "split header passes");
            Check(ScrubWebSocketTickets(state, rest.data(), rest.size(), rewrites) == WebSocketScrubStatus::Rewritten,
                "payload after split header rewritten");
            Check(rewrites.size() == 2, "both rewrites reported");
        }

        // Fail closed: RSV1 (permessage-deflate).
        {
            WebSocketTicketScrubState state = ReadyState();
            std::vector<uint8_t> frame = Frame(true, 0x1, "{\"steamAppTicket\":\"" + ticket + "\"}", mask);
            frame[0] |= 0x40;
            std::vector<WebSocketTicketRewrite> rewrites;
            const char* reason = nullptr;
            Check(ScrubWebSocketTickets(state, frame.data(), frame.size(), rewrites, &reason) == WebSocketScrubStatus::Rejected &&
                reason != nullptr, "RSV1 frame rejected");
            std::vector<uint8_t> next = Frame(true, 0x1, "{}", mask);
            Check(ScrubWebSocketTickets(state, next.data(), next.size(), rewrites) == WebSocketScrubStatus::Rejected,
                "rejected state is sticky");
        }

        // Fail closed: truncated text frame (payload split across sends).
        {
            WebSocketTicketScrubState state = ReadyState();
            std::vector<uint8_t> frame = Frame(true, 0x1, "{\"steamAppTicket\":\"" + ticket + "\"}", mask);
            std::vector<WebSocketTicketRewrite> rewrites;
            Check(ScrubWebSocketTickets(state, frame.data(), frame.size() - 5, rewrites) == WebSocketScrubStatus::Rejected,
                "truncated frame rejected");
        }

        // Fail closed: fragmented text message and a stray continuation.
        {
            WebSocketTicketScrubState state = ReadyState();
            std::vector<uint8_t> frame = Frame(false, 0x1, "{\"steamAppTicket\":\"", mask);
            std::vector<WebSocketTicketRewrite> rewrites;
            Check(ScrubWebSocketTickets(state, frame.data(), frame.size(), rewrites) == WebSocketScrubStatus::Rejected,
                "fragmented text rejected");
            WebSocketTicketScrubState state2 = ReadyState();
            std::vector<uint8_t> cont = Frame(true, 0x0, ticket + "\"}", mask);
            Check(ScrubWebSocketTickets(state2, cont.data(), cont.size(), rewrites) == WebSocketScrubStatus::Rejected,
                "continuation rejected");
        }

        // Fail closed: a ticket key whose value is not a string.
        {
            WebSocketTicketScrubState state = ReadyState();
            std::vector<uint8_t> frame = Frame(true, 0x1, "{\"steamAppTicket\":12345}", mask);
            std::vector<WebSocketTicketRewrite> rewrites;
            Check(ScrubWebSocketTickets(state, frame.data(), frame.size(), rewrites) == WebSocketScrubStatus::Rejected,
                "non-string ticket value rejected");
        }

        // A non-websocket stream is passed through untouched.
        {
            WebSocketTicketScrubState state;
            std::vector<uint8_t> http = Bytes("POST /x HTTP/1.1\r\nHost: y\r\n\r\nsteamAppTicket");
            const std::vector<uint8_t> original = http;
            std::vector<WebSocketTicketRewrite> rewrites;
            Check(ScrubWebSocketTickets(state, http.data(), http.size(), rewrites) == WebSocketScrubStatus::Unchanged &&
                http == original, "non-websocket HTTP untouched");
        }
    }
}

namespace
{
    void TestTicketWithholdingPerCall()
    {
        const uint8_t mask[4] = { 0x0A, 0x0B, 0x0C, 0x0D };
        const std::string ticket(60, 'T');
        std::vector<WebSocketTicketRewrite> rewrites;

        // The HTTP upgrade request passes untouched.
        {
            std::vector<uint8_t> req = Bytes(kClientHandshake);
            const std::vector<uint8_t> original = req;
            ByteSpan span{ req.data(), req.size() };
            Check(ScrubWebSocketTicketsPerCall(&span, 1, rewrites) == WebSocketScrubStatus::Unchanged && req == original,
                "per-call: upgrade request passes");
        }

        // Two complete frames in one call; only the ticket frame changes.
        {
            std::vector<uint8_t> a = Frame(true, 0x1, "{\"type\":\"DoPing\"}", mask);
            const std::vector<uint8_t> aOriginal = a;
            std::vector<uint8_t> b = Frame(true, 0x1, "{\"type\":\"Authorization\",\"steamAppTicket\":\"" + ticket + "\"}", mask);
            std::vector<uint8_t> both = a;
            both.insert(both.end(), b.begin(), b.end());
            const size_t size = both.size();
            ByteSpan span{ both.data(), both.size() };
            rewrites.clear();
            Check(ScrubWebSocketTicketsPerCall(&span, 1, rewrites) == WebSocketScrubStatus::Rewritten,
                "per-call: ticket frame rewritten");
            Check(both.size() == size && rewrites.size() == 1, "per-call: length kept, one rewrite");
            Check(std::equal(aOriginal.begin(), aOriginal.end(), both.begin()), "per-call: first frame untouched");
            std::vector<uint8_t> second(both.begin() + aOriginal.size(), both.end());
            const std::string out = FramePayloadText(second);
            Check(out.find("\"steamAppTicket\":\"withheld\"") != std::string::npos &&
                out.find(ticket) == std::string::npos, "per-call: second frame withheld");
        }

        // A frame split across two calls is refused (each call checked alone).
        {
            std::vector<uint8_t> frame = Frame(true, 0x1, "{\"steamAppTicket\":\"" + ticket + "\"}", mask);
            std::vector<uint8_t> head(frame.begin(), frame.begin() + 10);
            std::vector<uint8_t> tail(frame.begin() + 10, frame.end());
            ByteSpan h{ head.data(), head.size() };
            ByteSpan t{ tail.data(), tail.size() };
            Check(ScrubWebSocketTicketsPerCall(&h, 1, rewrites) == WebSocketScrubStatus::Rejected,
                "per-call: first half of a split frame rejected");
            Check(ScrubWebSocketTicketsPerCall(&t, 1, rewrites) == WebSocketScrubStatus::Rejected,
                "per-call: second half of a split frame rejected");
        }

        // Header and payload in separate WSABUF-style spans of ONE call.
        {
            std::vector<uint8_t> frame = Frame(true, 0x1, "{\"gogAppTicket\":\"" + ticket + "\"}", mask);
            const size_t headerSize = 2 + 4;
            std::vector<uint8_t> header(frame.begin(), frame.begin() + headerSize);
            std::vector<uint8_t> payload(frame.begin() + headerSize, frame.end());
            ByteSpan spans[2] = { { header.data(), header.size() }, { payload.data(), payload.size() } };
            rewrites.clear();
            Check(ScrubWebSocketTicketsPerCall(spans, 2, rewrites) == WebSocketScrubStatus::Rewritten,
                "scatter: two-buffer layout rewritten");
            std::vector<uint8_t> joined = header;
            joined.insert(joined.end(), payload.begin(), payload.end());
            const std::string out = FramePayloadText(joined);
            Check(joined.size() == frame.size() && out.find("\"gogAppTicket\":\"withheld\"") != std::string::npos &&
                out.find(ticket) == std::string::npos, "scatter: payload buffer holds the rewrite");
            Check(std::equal(header.begin(), header.end(), frame.begin()), "scatter: header buffer untouched");
        }

        // RSV1 and a call ending mid-frame are refused in per-call mode too.
        {
            std::vector<uint8_t> frame = Frame(true, 0x1, "{}", mask);
            frame[0] |= 0x40;
            ByteSpan span{ frame.data(), frame.size() };
            Check(ScrubWebSocketTicketsPerCall(&span, 1, rewrites) == WebSocketScrubStatus::Rejected,
                "per-call: RSV1 rejected");
            std::vector<uint8_t> ping = Frame(true, 0x9, "abcdef", mask);
            ByteSpan cut{ ping.data(), ping.size() - 2 };
            Check(ScrubWebSocketTicketsPerCall(&cut, 1, rewrites) == WebSocketScrubStatus::Rejected,
                "per-call: truncated control frame rejected");
        }
    }
}
int main()
{
    std::string type;
    Check(ExtractBzrNetMessageType(R"({"type":"Authorization","content":{"x":1}})", type) && type == "Authorization", "type extraction");
    Check(LookupBzrNetMessage("OnP2PRoute") && LookupBzrNetMessage("OnP2PRoute")->evidence == BzrNetEvidence::BinaryConfirmed, "registry evidence");

    int64_t reason = -1;
    Check(TryExtractBzrNetJsonInt(R"({"data":{"reasonCode":5}})", "reasonCode", reason) && reason == 5, "nested integer");
    bool success = true;
    Check(TryExtractBzrNetJsonBool(R"({"data":{"success":false}})", "success", success) && !success, "nested bool");

    ResetBzrNetSanitizationAliases();
    auto safe = SanitizeBzrNetJson(
        R"({"type":"Authorization","content":{"steamAppTicket":"SECRET","password":"pw","userId":"abc","name":"Alice","wanAddress":"1.2.3.4","lanAddresses":["10.0.0.1","10.0.0.2"]}})",
        false);
    Check(safe.authTicketRedacted && safe.authTicketLength == 6 && safe.json.find("SECRET") == std::string::npos, "auth ticket redaction");
    Check(safe.passwordRedacted && safe.passwordLength == 2 && safe.json.find("\"pw\"") == std::string::npos, "password redaction");
    Check(safe.json.find("abc") == std::string::npos && safe.json.find("Alice") == std::string::npos, "identity redaction");
    Check(safe.json.find("1.2.3.4") == std::string::npos && safe.json.find("10.0.0.2") == std::string::npos, "endpoint redaction");

    auto repeated = SanitizeBzrNetJson(
        R"({"users":[{"userId":"A","wanAddress":"8.8.8.8","lanAddresses":["10.1.1.1"]},{"userId":"B","wanAddress":"9.9.9.9","lanAddresses":["10.2.2.2"]}]})",
        false);
    Check(repeated.json.find("\"A\"") == std::string::npos && repeated.json.find("\"B\"") == std::string::npos, "all repeated identities redacted");
    Check(repeated.json.find("8.8.8.8") == std::string::npos && repeated.json.find("10.2.2.2") == std::string::npos, "all repeated endpoints redacted");

    auto repeatedSecrets = SanitizeBzrNetJson(
        R"({"type":"Unknown","content":{"steamAppTicket":"FIRST","nested":{"steamAppTicket":"SECOND","password":"one"},"password":"two"}})",
        true);
    Check(
        repeatedSecrets.authTicketRedacted &&
        repeatedSecrets.passwordRedacted &&
        repeatedSecrets.json.find("FIRST") == std::string::npos &&
        repeatedSecrets.json.find("SECOND") == std::string::npos &&
        repeatedSecrets.json.find("\"one\"") == std::string::npos &&
        repeatedSecrets.json.find("\"two\"") == std::string::npos,
        "all repeated secrets redacted");

    const uint8_t pp[] = {'P','P',1,0,0,0,2,0,0,0,3,0,0,0,4,0,0,0,5,0,0,0};
    const auto udp = DecodeBzrUdpControl(pp, sizeof(pp));
    Check(udp.recognized && udp.marker == "PP" && udp.fieldCount == 5 && udp.field4 == 5, "PP decoder");

    // PR (peer_ping_response) marker decodes a three-field payload.
    const uint8_t pr[] = {'P','R',10,0,0,0,20,0,0,0,30,0,0,0};
    const auto prUdp = DecodeBzrUdpControl(pr, sizeof(pr));
    Check(prUdp.recognized && prUdp.marker == "PR" && prUdp.fieldCount == 3 && prUdp.field0 == 10 && prUdp.field2 == 30, "PR decoder");

    // Unknown markers are reported as unrecognized rather than mis-decoded.
    const uint8_t xx[] = {'X','X',1,0,0,0};
    const auto xxUdp = DecodeBzrUdpControl(xx, sizeof(xx));
    Check(!xxUdp.recognized && xxUdp.marker == "XX", "unknown marker unrecognized");

    // Evidence/direction name helpers.
    Check(std::string(BzrNetEvidenceName(BzrNetEvidence::BinaryConfirmed)) == "binary_confirmed", "evidence name binary");
    Check(std::string(BzrNetEvidenceName(BzrNetEvidence::ReplacementOnly)) == "replacement_only", "evidence name replacement");
    Check(std::string(BzrNetEvidenceName(static_cast<BzrNetEvidence>(99))) == "unknown", "evidence name fallback");
    Check(std::string(BzrNetDirectionName(BzrNetMessageDirection::ServerToClient)) == "inbound", "direction name inbound");
    Check(std::string(BzrNetDirectionName(static_cast<BzrNetMessageDirection>(99))) == "unknown", "direction name fallback");

    // Unknown message types resolve to nullptr rather than a bogus entry.
    Check(LookupBzrNetMessage("NoSuchMessage") == nullptr, "unknown message returns null");

    // Standalone endpoint/identity sanitizers alias in shareable mode and are stable.
    ResetBzrNetSanitizationAliases();
    Check(SanitizeBzrNetIdentity("Alice", false) == "player_1", "identity alias assigned");
    Check(SanitizeBzrNetIdentity("Alice", false) == "player_1", "identity alias stable");
    Check(SanitizeBzrNetEndpoint("1.2.3.4", false) == "endpoint_1", "endpoint alias assigned");
    Check(SanitizeBzrNetEndpoint("1.2.3.4", true) == "1.2.3.4", "forensic endpoint passthrough");

    TestWebSocketStream();
    TestJsonEscape();
    TestTicketWithholding();
    TestTicketWithholdingPerCall();

    std::printf("%d checks, %d failures\n", OpenShimTest::CheckCount(), OpenShimTest::FailureCount());
    return OpenShimTest::ExitCode();
}
