#include "bzrnet_protocol.h"
#include "json_escape.h"

#include <cstdio>
#include <string>
#include <vector>

using namespace BZROpenShim;

namespace
{
    int g_Checks = 0;
    int g_Failures = 0;
    void Check(bool value, const char* name)
    {
        ++g_Checks;
        if (value) return;
        ++g_Failures;
        std::printf("FAIL %s\n", name);
    }

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

    std::printf("%d checks, %d failures\n", g_Checks, g_Failures);
    return g_Failures ? 1 : 0;
}
