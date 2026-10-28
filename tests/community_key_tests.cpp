#include "community_key.h"

#include <cstdio>
#include <string>
#include <vector>

using namespace BZROpenShim;

namespace
{
    int g_failures = 0;

    void Check(bool condition, const char* what)
    {
        if (!condition)
        {
            std::printf("FAIL: %s\n", what);
            ++g_failures;
        }
    }

    std::string Hmac(const std::vector<unsigned char>& key, const std::string& message)
    {
        const auto mac = HmacSha256(key.data(), key.size(), message.data(), message.size());
        return HexLower(mac.data(), mac.size());
    }

    void HmacMatchesRfc4231()
    {
        Check(Hmac(std::vector<unsigned char>(20, 0x0b), "Hi There") ==
                  "b0344c61d8db38535ca8afceaf0bf12b881dc200c9833da726e9376c2e32cff7",
              "RFC 4231 case 1");
        const std::string jefe = "Jefe";
        Check(Hmac(std::vector<unsigned char>(jefe.begin(), jefe.end()), "what do ya want for nothing?") ==
                  "5bdcc146bf60754e6a042426089575c75a003f089d2739839dec58b964ec3843",
              "RFC 4231 case 2");
        Check(Hmac(std::vector<unsigned char>(131, 0xaa), "Test Using Larger Than Block-Size Key - Hash Key First") ==
                  "60e431591ee0b67f0d8a26aacbf5b77f8e0bc6213728c5140546040f0ee37f54",
              "RFC 4231 case 6 (key longer than a block)");
    }

    void Sha256HexStillMatches()
    {
        Sha256 empty;
        Check(empty.Finish() == "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
              "Sha256 of empty input");
    }

    void CanonicalizesHosts()
    {
        Check(CanonicalCommunityHost("ws://192.168.0.44:1337/") == "192.168.0.44:1337", "launch option form");
        Check(CanonicalCommunityHost("192.168.0.44") == "192.168.0.44:1337", "bare IP gets default port");
        Check(CanonicalCommunityHost("  Play.Example.COM.  ") == "play.example.com:1337", "case, dot, spaces");
        Check(CanonicalCommunityHost("wss://play.example.com:4000/lobby?x=1") == "play.example.com:4000", "path and query");
        Check(CanonicalCommunityHost("[::1]:1338") == "[::1]:1338", "bracketed IPv6");
        Check(CanonicalCommunityHost("[::1]") == "[::1]:1337", "bracketed IPv6 default port");
        Check(CanonicalCommunityHost("").empty(), "empty");
        Check(CanonicalCommunityHost("ws://").empty(), "scheme only");
        Check(CanonicalCommunityHost("::1").empty(), "unbracketed IPv6");
        Check(CanonicalCommunityHost("host:0").empty(), "port zero");
        Check(CanonicalCommunityHost("host:65536").empty(), "port too large");
        Check(CanonicalCommunityHost("host:12a").empty(), "non-numeric port");
        Check(CanonicalCommunityHost("ftp://host").empty(), "unknown scheme");
        Check(CanonicalCommunityHost("user@host").empty(), "userinfo");
        Check(CanonicalCommunityHost("ho st").empty(), "space inside host");
    }

    void DerivesPerServerKeys()
    {
        std::vector<unsigned char> secret(kCommunitySecretBytes);
        for (size_t index = 0; index < secret.size(); ++index)
            secret[index] = static_cast<unsigned char>(index);

        const std::string a = DeriveCommunityKey(secret.data(), secret.size(), "ws://192.168.0.44:1337/");
        Check(a.size() == 64, "key is 64 hex chars");
        Check(a == DeriveCommunityKey(secret.data(), secret.size(), "192.168.0.44"),
              "equivalent spellings give the same key");
        Check(a != DeriveCommunityKey(secret.data(), secret.size(), "192.168.0.45"), "different host, different key");
        Check(a != DeriveCommunityKey(secret.data(), secret.size(), "192.168.0.44:1340"), "different port, different key");
        Check(a == Hmac(secret, "192.168.0.44:1337"), "key is HMAC of the canonical host");
        Check(DeriveCommunityKey(secret.data(), 16, "192.168.0.44").empty(), "short secret refused");
        Check(DeriveCommunityKey(nullptr, 32, "192.168.0.44").empty(), "null secret refused");
        Check(DeriveCommunityKey(secret.data(), secret.size(), "::1").empty(), "unparseable host refused");
    }
}

int main()
{
    HmacMatchesRfc4231();
    Sha256HexStillMatches();
    CanonicalizesHosts();
    DerivesPerServerKeys();
    if (g_failures == 0)
        std::printf("community_key_tests: all passed\n");
    return g_failures == 0 ? 0 : 1;
}
