#include "direct_lan_redux_peer.h"
#include <deque>
#include <utility>

#if defined(_MSC_VER) && defined(_M_IX86)
#define LAN_PEER_CALL __fastcall
#else
#define LAN_PEER_CALL
#endif

namespace BZROpenShim::DirectLan::Redux
{
    struct PeerBridge::Impl
    {
        struct Object
        {
            const uintptr_t* table = nullptr;
            // Qualified base send wrapper updates 1C/20; receive dispatch
            // updates 24/28. Padding has no inferred gameplay meaning. The
            // native registration map at 2C is NOT constructed here.
            std::array<uint8_t, 0x1C - sizeof(uintptr_t)> unused{};
            uint32_t sentPackets = 0, sentBytes = 0, receivedPackets = 0, receivedBytes = 0;
            std::array<uint8_t, 12> unboundRegistration{};
            Impl* bridge = nullptr;
        } object;
        static_assert(offsetof(Object, sentPackets) == 0x1C && offsetof(Object, receivedBytes) == 0x28 && offsetof(Object, bridge) == 0x38);
        struct Handler { PacketHandler fn = nullptr; void* context = nullptr; };
        Adapter& adapter;
        Mesh& mesh;
        std::array<Handler, 256> handlers{};
        Handler fallback;
        std::deque<PeerPacket> pending;
        size_t queued = 0;
        uint64_t generation = 0;
        bool pumping = false, closed = false;
        Impl(Adapter& a, Mesh& m) : adapter(a), mesh(m)
        { object.table = Table().data(); object.bridge = this; }
        static void* LAN_PEER_CALL Destroy(Object* self, void*, uint32_t)
        {
            // Shim owns storage. A native deletion flag must never cross its
            // allocator boundary. This only retires this bridge's callbacks.
            self->bridge->Clear(); self->bridge->closed = true; return self;
        }
        static void LAN_PEER_CALL Initialize(Object*, void*) {}
        static void LAN_PEER_CALL Tick(Object* self, void*) { self->bridge->Pump(); }
        static bool LAN_PEER_CALL Transmit(Object* self, void*, const Identity* target, const void* bytes, uint32_t count, int reliable)
        { return target && self->bridge->Send(*target, bytes, count, reliable != 0); }
        static const std::array<uintptr_t, 4>& Table()
        {
            static const std::array<uintptr_t, 4> table{
                reinterpret_cast<uintptr_t>(&Destroy), reinterpret_cast<uintptr_t>(&Initialize),
                reinterpret_cast<uintptr_t>(&Tick), reinterpret_cast<uintptr_t>(&Transmit)};
            return table;
        }
        void Clear()
        { ++generation; handlers.fill({}); fallback = {}; pending.clear(); queued = 0; mesh.TakeReceived(); }
        bool Send(const Identity& target, const void* bytes, uint32_t count, bool reliable)
        {
            const auto peer = adapter.Find(target);
            return !closed && peer && count && count <= 1152 && bytes &&
                mesh.Send(peer->local, static_cast<const uint8_t*>(bytes), count, reliable);
        }
        void Pump()
        {
            if (closed || pumping) return;
            struct Guard { bool& value; explicit Guard(bool& v) : value(v) { value = true; } ~Guard() { value = false; } } guard(pumping);
            mesh.Poll();
            for (auto& packet : mesh.TakeReceived())
            {
                if (pending.size() >= 1024 || queued + packet.bytes.size() > 1024 * 1024)
                { mesh.Close(); Clear(); closed = true; return; }
                queued += packet.bytes.size(); pending.push_back(std::move(packet));
            }
            const auto epoch = generation;
            for (size_t i = 0; i < 128 && !pending.empty() && generation == epoch; ++i)
            {
                auto packet = std::move(pending.front()); pending.pop_front(); queued -= packet.bytes.size();
                Identity sender;
                bool found = false;
                const auto lobby = adapter.Lobby();
                for (int32_t n = 0; size_t(n) < adapter.Members(); ++n)
                {
                    adapter.Member(&sender, lobby, n); const auto peer = adapter.Find(sender);
                    if (peer && peer->local == packet.sender) { found = true; break; }
                }
                if (!found || packet.bytes.empty()) continue;
                ++object.receivedPackets; object.receivedBytes += uint32_t(packet.bytes.size());
                if (packet.bytes.size() >= 2 && packet.bytes[0] == 0 && packet.bytes[1] == 0)
                { const uint8_t pong[] = {0, 1}; mesh.Send(packet.sender, pong, sizeof(pong), true); }
                auto handler = handlers[packet.bytes[0]];
                if (!handler.fn) handler = fallback;
                if (handler.fn) handler.fn(handler.context, &object, sender, packet.bytes.data(), uint32_t(packet.bytes.size()));
            }
        }
#if defined(_MSC_VER) && defined(_M_IX86)
        static void Native(void* context, void* peer, const Identity& sender, const uint8_t* bytes, uint32_t count)
        {
            auto table = *static_cast<uintptr_t**>(context);
            using Receive = void(__thiscall*)(void*, void*, const Identity*, const uint8_t*, uint32_t);
            reinterpret_cast<Receive>(table[1])(context, peer, &sender, bytes, count);
        }
#endif
    };
    PeerBridge::PeerBridge(Adapter& a, Mesh& m) : impl_(new Impl(a, m)) {}
    PeerBridge::~PeerBridge() = default;
    void PeerBridge::SetHandler(uint8_t kind, PacketHandler fn, void* context) { impl_->handlers[kind] = {fn, context}; }
    void PeerBridge::RemoveHandler(uint8_t kind, PacketHandler fn, void* context)
    { auto& handler = impl_->handlers[kind]; if (handler.fn == fn && handler.context == context) handler = {}; }
    void PeerBridge::SetDefaultHandler(PacketHandler fn, void* context) { impl_->fallback = {fn, context}; }
    void PeerBridge::ClearHandlers() { impl_->Clear(); }
    bool PeerBridge::Send(const Identity& peer, const void* data, uint32_t count, bool reliable) { return impl_->Send(peer, data, count, reliable); }
    void PeerBridge::Pump() { impl_->Pump(); }
#if defined(_MSC_VER) && defined(_M_IX86)
    void PeerBridge::SetNativeHandler(uint8_t kind, void* handler) { impl_->handlers[kind] = {handler ? &Impl::Native : nullptr, handler}; }
    void PeerBridge::RemoveNativeHandler(uint8_t kind, void* handler)
    { RemoveHandler(kind, &Impl::Native, handler); }
    void PeerBridge::SetNativeDefaultHandler(void* handler) { impl_->fallback = {handler ? &Impl::Native : nullptr, handler}; }
#endif
#ifdef OPENSHIM_DIRECT_LAN_ABI_TEST
    void* PeerBridge::QualificationObject() { return &impl_->object; }
#endif
}
