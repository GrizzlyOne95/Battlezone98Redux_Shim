#pragma once
#include "direct_lan_transport.h"

namespace BZROpenShim::DirectLan
{
    constexpr uint16_t kDiscoveryPort = 21338;
    constexpr size_t kDiscoveryQuerySize = 192;
    struct Advertisement
    {
        Id session;
        Address control; // source IP from the socket, port from the response
        Compatibility compatibility;
        std::string name;
        uint8_t members = 0, capacity = 0;
    };
    std::vector<uint8_t> DiscoveryQuery(Id nonce);
    bool DiscoveryReply(const std::vector<uint8_t>& query, const View&, uint16_t controlPort,
                        std::vector<uint8_t>& response);
    bool ReadAdvertisement(const uint8_t*, size_t, Id nonce, uint32_t observedSource,
                           Advertisement&);

    class DiscoveryHost
    {
    public:
        DiscoveryHost();
        ~DiscoveryHost();
        bool Open(uint32_t bindAddress, uint16_t port = kDiscoveryPort);
        void Poll(const View&, uint16_t controlPort);
        uint16_t Port() const;
    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
    class Browser
    {
    public:
        Browser();
        ~Browser();
        // Explicit targets support an isolated loopback test. Empty means
        // limited broadcast, per-interface directed broadcasts, and loopback.
        bool Start(uint16_t port = kDiscoveryPort, std::vector<uint32_t> targets = {});
        void Poll();
        bool Searching() const;
        const std::vector<Advertisement>& Results() const;
        const std::string& Error() const;
    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}
