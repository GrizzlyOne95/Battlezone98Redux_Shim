#pragma once
// Client-owned Direct LAN control state. Independent of Steam/Galaxy/BZRNet,
// native object layouts and gameplay packets. Ids are session-local opaque
// values; they must never be presented as platform identities.
#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace BZROpenShim::DirectLan
{
    constexpr size_t kMaxMembers = 16;
    constexpr size_t kMaxFrame = 4096;
    using Connection = uint64_t; // local transport handle, never a remote claim
    using Time = uint64_t;       // monotonic milliseconds supplied by the caller
    struct Id
    {
        std::array<uint8_t, 16> bytes{};
        bool Empty() const;
        bool operator==(const Id& other) const { return bytes == other.bytes; }
        bool operator!=(const Id& other) const { return !(*this == other); }
    };
    struct Compatibility
    {
        std::string gameBuild;
        std::array<uint8_t, 32> content{};
        bool operator==(const Compatibility& other) const
        { return gameBuild == other.gameBuild && content == other.content; }
    };
    struct Endpoint
    {
        uint32_t ipv4 = 0; // host byte order, observed TCP source IP for a guest
        uint16_t gamePort = 0;
    };
    struct Config
    {
        Compatibility compatibility;
        std::string name, map;
        std::vector<uint8_t> settings; // opaque native-adapter settings, <=512
        uint8_t capacity = 8;
    };
    enum class Phase : uint8_t { Idle, Joining, Lobby, Preparing, Running, Closed };
    struct Member
    {
        Id id;
        uint8_t slot = 0;
        std::string name;
        Endpoint endpoint;
        bool ready = false, prepared = false;
    };
    struct View
    {
        Id session, owner;
        Config config;
        uint64_t revision = 0, launch = 0;
        Phase phase = Phase::Idle;
        std::vector<Member> members;
        std::string reason;
    };
    enum class Type : uint8_t
    { Hello = 1, Snapshot, Ready, Prepare, Prepared, Commit, Leave, Reject, Close, Ping, Pong };
    struct Packet
    {
        Type type = Type::Hello;
        Id session, sender;
        uint64_t serial = 0;
        std::vector<uint8_t> payload;
    };
    // Length-prefixed, versioned TCP frames. Never fed to native packet parsers.
    bool Encode(const Packet&, std::vector<uint8_t>& frame);
    class Decoder
    {
    public:
        bool Feed(const uint8_t*, size_t, std::vector<Packet>&);
        bool Failed() const { return failed_; }
    private:
        std::vector<uint8_t> pending_;
        bool failed_ = false;
    };
    struct Outbound { Connection connection; Packet packet; bool closeAfter = false; };
    enum class EventType { Changed, Prepare, Started, Ended, Rejected };
    // Captured state matters: a departure can arrive in the same socket pump
    // after Commit. The adapter must see the exact committed launch roster.
    struct Event { EventType type; std::string reason; View state; };

    class Session
    {
    public:
        Session(Id local, std::string name, Compatibility, uint16_t gameplayPort);
        bool Host(Config, Id session, uint32_t localAddress, Time now);
        bool Join(Connection host, Id advertisedSession, Time now);
        void Receive(Connection, uint32_t observedAddress, const Packet&, Time now);
        void Disconnected(Connection, const std::string& reason = "Peer disconnected");
        void Tick(Time now);
        bool SetReady(bool);
        bool SetConfig(Config); // owner only; invalidates readiness
        bool RequestStart(Time now);
        bool Prepared(); // adapter calls only after native peer readiness
        void Leave();
        const View& State() const { return view_; }
        const Id& LocalId() const { return local_; }
        bool IsHost() const { return host_; }
        bool HasConnection(Connection) const;
        std::vector<Outbound> TakeOutbound();
        std::vector<Event> TakeEvents();
    private:
        struct Link { Connection connection; Id id; Time heard; uint64_t serial; };
        Id local_;
        std::string name_;
        Compatibility compatibility_;
        uint16_t gamePort_;
        View view_;
        bool host_ = false, valid_ = false;
        Connection hostConnection_ = 0;
        std::vector<Link> links_;
        std::vector<Outbound> outbound_;
        std::vector<Event> events_;
        uint64_t serial_ = 0, receivedSerial_ = 0;
        Time lastHeard_ = 0, lastPing_ = 0, prepareSince_ = 0;
        void Send(Connection, Type, std::vector<uint8_t> payload = {}, bool close = false);
        void Broadcast(Type, const std::vector<uint8_t>& payload = {});
        void Publish();
        void Changed(bool invalidate);
        void End(const std::string&, bool rejected = false);
        void CommitIfPrepared();
        void EventOut(EventType, const std::string& = "");
    };
}
