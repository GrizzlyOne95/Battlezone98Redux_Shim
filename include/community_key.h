#pragma once

#include "streaming_sha256.h"

#include <array>
#include <cctype>
#include <cstddef>
#include <cstring>
#include <string>

namespace BZROpenShim
{
    // Per-server community identity key sent to non-official lobby servers.
    // key = HMAC-SHA256(master secret, canonical "host:port"), so each server
    // sees a different key and none can replay another's.
    constexpr unsigned kCommunityDefaultLobbyPort = 1337;
    constexpr size_t kCommunitySecretBytes = 32;

    // RFC 2104 HMAC over SHA-256.
    inline std::array<unsigned char, 32> HmacSha256(const void* key, size_t keyLength,
                                                    const void* message, size_t messageLength)
    {
        std::array<unsigned char, 64> block = {};
        if (keyLength > block.size())
        {
            Sha256 hashed;
            hashed.Update(key, keyLength);
            const std::array<unsigned char, 32> digest = hashed.FinishBytes();
            std::memcpy(block.data(), digest.data(), digest.size());
        }
        else if (keyLength > 0)
        {
            std::memcpy(block.data(), key, keyLength);
        }

        std::array<unsigned char, 64> pad = {};
        for (size_t index = 0; index < block.size(); ++index)
            pad[index] = static_cast<unsigned char>(block[index] ^ 0x36);
        Sha256 inner;
        inner.Update(pad.data(), pad.size());
        inner.Update(message, messageLength);
        const std::array<unsigned char, 32> innerDigest = inner.FinishBytes();

        for (size_t index = 0; index < block.size(); ++index)
            pad[index] = static_cast<unsigned char>(block[index] ^ 0x5c);
        Sha256 outer;
        outer.Update(pad.data(), pad.size());
        outer.Update(innerDigest.data(), innerDigest.size());
        return outer.FinishBytes();
    }

    inline std::string HexLower(const unsigned char* bytes, size_t length)
    {
        static const char digits[] = "0123456789abcdef";
        std::string hex;
        hex.reserve(length * 2);
        for (size_t index = 0; index < length; ++index)
        {
            hex.push_back(digits[bytes[index] >> 4]);
            hex.push_back(digits[bytes[index] & 0xF]);
        }
        return hex;
    }

    // Reduces "ws://Host.Example:1337/", "host", "host:1338", "[::1]:1337" and
    // the like to lowercase "host:port" (default port 1337). Returns "" for
    // anything it cannot parse, so callers can fail closed.
    inline std::string CanonicalCommunityHost(std::string text)
    {
        auto isSpace = [](char c) { return std::isspace(static_cast<unsigned char>(c)) != 0; };
        while (!text.empty() && isSpace(text.front()))
            text.erase(text.begin());
        while (!text.empty() && isSpace(text.back()))
            text.pop_back();
        for (char& c : text)
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));

        const size_t scheme = text.find("://");
        if (scheme != std::string::npos)
        {
            const std::string name = text.substr(0, scheme);
            if (name != "ws" && name != "wss" && name != "http" && name != "https")
                return {};
            text.erase(0, scheme + 3);
        }
        const size_t path = text.find_first_of("/?#");
        if (path != std::string::npos)
            text.erase(path);
        if (text.find('@') != std::string::npos)
            return {};

        std::string host;
        std::string port;
        if (!text.empty() && text.front() == '[')
        {
            const size_t close = text.find(']');
            if (close == std::string::npos)
                return {};
            host = text.substr(0, close + 1);
            const std::string rest = text.substr(close + 1);
            if (!rest.empty())
            {
                if (rest.front() != ':')
                    return {};
                port = rest.substr(1);
            }
        }
        else
        {
            const size_t colon = text.find(':');
            if (colon != std::string::npos)
            {
                if (text.find(':', colon + 1) != std::string::npos)
                    return {};  // bare IPv6 without brackets is ambiguous
                host = text.substr(0, colon);
                port = text.substr(colon + 1);
            }
            else
            {
                host = text;
            }
            while (!host.empty() && host.back() == '.')
                host.pop_back();
            for (const char c : host)
            {
                if (!std::isalnum(static_cast<unsigned char>(c)) && c != '-' && c != '.' && c != '_')
                    return {};
            }
        }
        if (host.empty() || host == "[]")
            return {};

        unsigned value = kCommunityDefaultLobbyPort;
        if (!port.empty())
        {
            if (port.size() > 5)
                return {};
            value = 0;
            for (const char c : port)
            {
                if (c < '0' || c > '9')
                    return {};
                value = value * 10 + static_cast<unsigned>(c - '0');
            }
            if (value == 0 || value > 65535)
                return {};
        }
        return host + ":" + std::to_string(value);
    }

    // 64 lowercase hex chars, or "" when the host does not canonicalize or the
    // secret is the wrong size.
    inline std::string DeriveCommunityKey(const unsigned char* secret, size_t secretLength,
                                          const std::string& server)
    {
        if (secret == nullptr || secretLength != kCommunitySecretBytes)
            return {};
        const std::string canonical = CanonicalCommunityHost(server);
        if (canonical.empty())
            return {};
        const std::array<unsigned char, 32> mac =
            HmacSha256(secret, secretLength, canonical.data(), canonical.size());
        return HexLower(mac.data(), mac.size());
    }
}
