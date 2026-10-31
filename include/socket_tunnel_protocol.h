#pragma once
#include <cstdint>
#include <cstring>
#include <deque>
#include <vector>

namespace BZROpenShim::SocketTunnel
{
    constexpr size_t kPayloadMax = 60000;
    constexpr size_t kQueueMax = 256 * 1024;
    constexpr uint64_t kIdleMs = 15000;
    enum class Kind : uint8_t { Hello = 1, Welcome, Ping, Ack, Open, Data, Close, Reset, Datagram };
    struct Frame
    {
        Kind kind = Kind::Ping;
        uint64_t session = 0;
        uint32_t sequence = 0;
        uint32_t stream = 0;
        uint16_t port = 0;   // server destination/source port
        uint16_t source = 0; // original game's UDP source port (not destination port)
        std::vector<uint8_t> data;
    };
    inline bool Reliable(Kind k) { return k >= Kind::Open && k <= Kind::Reset; }
    inline bool GameUdp(uint16_t port) { return port >= 1338 && port <= 1369; }
    inline void Put(std::vector<uint8_t>& b, uint64_t n, unsigned count)
    { for (unsigned i = 0; i < count; ++i) b.push_back(uint8_t(n >> (i * 8))); }
    inline uint64_t Get(const uint8_t* b, unsigned count)
    { uint64_t n = 0; for (unsigned i = 0; i < count; ++i) n |= uint64_t(b[i]) << (i * 8); return n; }
    // Explicit little-endian v1 wire format. No packed structs or native ABI.
    inline bool Valid(const Frame& f)
    {
        if (!f.session || f.data.size() > kPayloadMax) return false;
        if (Reliable(f.kind))
        {
            if (!f.sequence || !f.stream || f.source) return false;
            if (f.kind == Kind::Open) return f.port == 1337 && f.data.empty();
            if (f.port) return false;
            return f.kind == Kind::Data ? !f.data.empty() && f.data.size() <= 1024 : f.data.empty();
        }
        if (f.kind == Kind::Datagram) return GameUdp(f.port) && f.source && !f.stream && !f.sequence;
        if (f.stream || f.port || f.source || !f.data.empty()) return false;
        if (f.kind == Kind::Ack) return f.sequence != 0;
        return (f.kind == Kind::Hello || f.kind == Kind::Welcome || f.kind == Kind::Ping) && !f.sequence;
    }
    inline std::vector<uint8_t> Encode(const Frame& f)
    {
        std::vector<uint8_t> b{'B','Z','T',1, uint8_t(f.kind), 0};
        Put(b, f.data.size(), 2); Put(b, f.session, 8); Put(b, f.sequence, 4);
        Put(b, f.stream, 4); Put(b, f.port, 2); Put(b, f.source, 2);
        b.insert(b.end(), f.data.begin(), f.data.end()); return b;
    }
    inline bool Decode(const uint8_t* b, size_t n, Frame& f)
    {
        if (n < 28 || std::memcmp(b, "BZT\1", 4) || b[5] || Get(b + 6, 2) != n - 28) return false;
        f.kind = Kind(b[4]); f.session = Get(b + 8, 8); f.sequence = uint32_t(Get(b + 16, 4));
        f.stream = uint32_t(Get(b + 20, 4)); f.port = uint16_t(Get(b + 24, 2));
        f.source = uint16_t(Get(b + 26, 2)); f.data.assign(b + 28, b + n); return Valid(f);
    }
    // M1 plain UDP reliability adapter: bounded stop-and-wait, duplicate ACKs,
    // retransmission and ordered delivery. Steam's reliable messages replace
    // this adapter in M2; OPEN/DATA/CLOSE/RESET and UDP semantics stay the same.
    struct ReliableQueue
    {
        std::deque<Frame> pending;
        size_t bytes = 0;
        uint32_t next = 1, received = 0;
        uint64_t sentAt = 0, startedAt = 0;
        bool Push(Frame f)
        {
            if (!next || bytes + f.data.size() + 28 > kQueueMax || pending.size() >= 512) return false;
            f.sequence = next++; bytes += f.data.size() + 28; pending.push_back(std::move(f)); return true;
        }
        bool Ack(uint32_t seq)
        {
            if (pending.empty() || pending.front().sequence != seq) return false;
            bytes -= pending.front().data.size() + 28; pending.pop_front(); sentAt = startedAt = 0; return true;
        }
        bool Due(uint64_t now) const { return !pending.empty() && (!sentAt || now - sentAt >= 100); }
        bool Expired(uint64_t now) const { return startedAt && now - startedAt >= 10000; }
        void Sent(uint64_t now) { sentAt = now; if (!startedAt) startedAt = now; }
    };
}
