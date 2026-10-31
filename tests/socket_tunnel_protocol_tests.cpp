#include "socket_tunnel_protocol.h"
#include <cstdlib>
#include <iostream>
using namespace BZROpenShim::SocketTunnel;
static void Check(bool ok) { if (!ok) { std::cerr << "tunnel protocol check failed\n"; std::exit(1); } }
int main()
{
    Frame f{Kind::Datagram, 0x123456789abcdef0, 0, 0, 1369, 54321, {0, 255, 42}}, out;
    auto bytes = Encode(f);
    Check(Decode(bytes.data(), bytes.size(), out));
    Check(out.session == f.session && out.source == 54321 && out.port == 1369 && out.data == f.data);
    for (size_t n = 0; n < bytes.size(); ++n) Check(!Decode(bytes.data(), n, out));
    for (unsigned index : {0u, 3u, 5u, 6u})
    { auto bad = bytes; bad[index] ^= 0x40; Check(!Decode(bad.data(), bad.size(), out)); }
    f.port = 8080; Check(!Valid(f)); f.port = 1337; Check(!Valid(f));
    f.port = 1338; f.data.resize(kPayloadMax + 1); Check(!Valid(f));
    f = Frame{Kind::Open, 1, 1, 7, 1337}; Check(Valid(f));
    f.port = 8080; Check(!Valid(f));
    f = Frame{Kind::Data, 1, 1, 7}; Check(!Valid(f));
    f.data.resize(1024); Check(Valid(f)); f.data.push_back(0); Check(!Valid(f));
    f = Frame{Kind::Ack, 1, 1}; Check(Valid(f)); f.stream = 7; Check(!Valid(f));
    f = Frame{Kind(255), 1}; Check(!Valid(f));

    ReliableQueue sender, receiver;
    for (unsigned i = 0; i < 3; ++i) Check(sender.Push(Frame{Kind::Data, 1, 0, 7, 0, 0, {uint8_t(i)}}));
    Check(sender.Due(1000)); sender.Sent(1000);
    Check(!sender.Due(1099) && sender.Due(1100)); // lost first packet
    Check(!sender.Ack(2) && sender.pending.size() == 3); // reordered/spurious ACK
    // Deliver each packet twice, with its first ACK lost. Exactly-once bytes.
    std::vector<uint8_t> delivered;
    while (!sender.pending.empty())
    {
        const auto packet = sender.pending.front();
        for (int duplicate = 0; duplicate < 2; ++duplicate)
        {
            if (packet.sequence == receiver.received + 1)
            { delivered.push_back(packet.data[0]); receiver.received = packet.sequence; }
        }
        Check(sender.Ack(receiver.received));
    }
    Check(delivered == std::vector<uint8_t>({0, 1, 2}) && sender.bytes == 0);
    Check(sender.Push(Frame{Kind::Close, 1, 0, 7})); sender.Sent(1000);
    Check(!sender.Expired(10999) && sender.Expired(11000));
    while (sender.Push(Frame{Kind::Data, 1, 0, 7, 0, 0, std::vector<uint8_t>(1024)})) {}
    Check(sender.bytes <= kQueueMax && sender.pending.size() <= 512);
    sender.next = 0; Check(!sender.Push(Frame{Kind::Close, 1, 0, 7}));
    std::cout << "socket tunnel framing, loss/duplicate ordering, caps and timeout checks passed\n";
}
