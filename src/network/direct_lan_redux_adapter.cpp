#include "direct_lan_redux_adapter.h"
#include <algorithm>
#include <cstring>
#include <utility>

#if defined(_MSC_VER) && defined(_M_IX86)
#define LAN_QUERY_CALL __fastcall
#else
#define LAN_QUERY_CALL
#endif

namespace BZROpenShim::DirectLan::Redux
{
    bool Equal(const Identity& a, const Identity& b)
    { return a.discriminator == b.discriminator && a.word8 == b.word8 && a.word12 == b.word12; }
    bool DirectIdentity(const Identity& id)
    { return id.discriminator == 3 && (id.word8 || id.word12); }
    bool Less(const Identity& a, const Identity& b)
    {
        int32_t kindA, kindB;
        std::memcpy(&kindA, &a.discriminator, 4); std::memcpy(&kindB, &b.discriminator, 4);
        return kindA < kindB || (kindA == kindB && (a.word12 < b.word12 ||
            (a.word12 == b.word12 && a.word8 < b.word8)));
    }
    Identity* Copy(Identity* out, const Identity& id)
    {
        if (out) { out->discriminator = id.discriminator; out->word8 = id.word8; out->word12 = id.word12; }
        return out;
    }
    namespace
    {
        bool LocalAddress(uint32_t ip)
        { return (ip >> 24) == 10 || (ip >> 24) == 127 || (ip >> 20) == 0xAC1 ||
            (ip >> 16) == 0xC0A8 || (ip >> 16) == 0xA9FE; }
        Identity Token(const Id& id, uint8_t domain)
        {
            // Explicit deterministic mapping, not a cast/truncation or a
            // platform ID. Both directions are stored and collisions rejected.
            uint64_t value = 14695981039346656037ull;
            value = (value ^ domain) * 1099511628211ull;
            for (auto byte : id.bytes) value = (value ^ byte) * 1099511628211ull;
            if (!value) value = 1;
            return {3, {}, uint32_t(value), uint32_t(value >> 32)};
        }
        bool Before(const Peer& a, const Peer& b)
        { return Less(a.native, b.native); }
    }
    struct Adapter::Impl
    {
        struct Mapping { Id id; uint8_t domain; Identity native; };
        struct QueryObject
        {
            const uintptr_t* vtable = nullptr;
            std::array<uint8_t, 0x28 - sizeof(uintptr_t)> unused{};
            Identity currentLobby; // offset required by released owner predicate
            Impl* adapter = nullptr;
        } object;
        static_assert(offsetof(QueryObject, currentLobby) == 0x28);
        Id local, session;
        Identity localNative, ownerNative;
        std::vector<Peer> peers;
        std::vector<Mapping> mappings; // tombstones retained until Reset
        uint64_t revision = 0;
        Phase phase = Phase::Idle;
        std::string error;
        explicit Impl(Id id) : local(id)
        {
            object.vtable = Table().data(); object.adapter = this;
            if (!local.Empty()) localNative = Token(local, 2);
        }
        static Identity* LAN_QUERY_CALL QueryLocal(QueryObject* self, void*, Identity* out)
        { return Copy(out, self->adapter->localNative); }
        static Identity* LAN_QUERY_CALL QueryOwner(QueryObject* self, void*, Identity* out, const Identity* lobby)
        {
            return Copy(out, lobby && self->adapter->Matches(*lobby) ? self->adapter->ownerNative : Identity{});
        }
        static Identity* LAN_QUERY_CALL QueryMember(QueryObject* self, void*, Identity* out, const Identity* lobby, int32_t index)
        {
            const auto& s = *self->adapter;
            return Copy(out, lobby && s.Matches(*lobby) && index >= 0 && size_t(index) < s.peers.size()
                ? s.peers[size_t(index)].native : Identity{});
        }
        static uint32_t LAN_QUERY_CALL QueryCount(QueryObject* self, void*, const Identity* lobby)
        { return lobby && self->adapter->Matches(*lobby) ? uint32_t(self->adapter->peers.size()) : 0; }
        static const std::array<uintptr_t, 32>& Table()
        {
            static const auto table = []
            {
                std::array<uintptr_t, 32> entries{};
                entries[0x38 / 4] = reinterpret_cast<uintptr_t>(&QueryLocal);
                entries[0x44 / 4] = reinterpret_cast<uintptr_t>(&QueryCount);
                entries[0x48 / 4] = reinterpret_cast<uintptr_t>(&QueryMember);
                entries[0x68 / 4] = reinterpret_cast<uintptr_t>(&QueryOwner);
                return entries;
            }();
            return table;
        }
        bool Matches(const Identity& id) const
        { return !peers.empty() && Equal(id, object.currentLobby); }
        void Unpublish()
        { peers.clear(); ownerNative = {}; object.currentLobby = {}; }
        void Reset()
        { Unpublish(); mappings.clear(); session = {}; revision = 0; phase = Phase::Idle; error.clear(); }
        bool Fail(const char* why)
        { Unpublish(); error = why; return false; }
        bool Map(std::vector<Mapping>& candidate, Id id, uint8_t domain, Identity& out)
        {
            const auto old = std::find_if(candidate.begin(), candidate.end(), [&](const Mapping& m) { return m.id == id && m.domain == domain; });
            if (old != candidate.end()) { out = old->native; return true; }
            if (id.Empty() || candidate.size() >= 257) return false;
            const auto token = Token(id, domain);
            if (std::any_of(candidate.begin(), candidate.end(), [&](const Mapping& m) { return Equal(m.native, token); })) return false;
            candidate.push_back({id, domain, token}); out = token; return true;
        }
        bool Apply(const View& view)
        {
            error.clear();
            if (view.phase == Phase::Closed) { Unpublish(); phase = Phase::Closed; return true; }
            if (view.phase != Phase::Lobby && view.phase != Phase::Preparing && view.phase != Phase::Running)
                return Fail("No accepted LAN lobby snapshot");
            if (phase == Phase::Closed || (!session.Empty() && session != view.session)) return Fail("Reset adapter before a new session");
            if (local.Empty() || view.session.Empty() || view.owner.Empty() || !view.revision || view.revision < revision ||
                view.members.empty() || view.members.size() > kMaxMembers || view.config.capacity < view.members.size() ||
                view.config.capacity < 2 || view.config.capacity > kMaxMembers || view.members[0].id != view.owner || view.members[0].slot != 0)
                return Fail("Invalid LAN identity/roster snapshot");
            if (phase == Phase::Running && view.phase != Phase::Running) return Fail("Running session cannot return to a lobby");
            auto candidate = mappings;
            Identity lobby, owner, mine;
            if (!Map(candidate, view.session, 1, lobby)) return Fail("Native LAN identity collision or mapping limit");
            std::vector<Peer> next;
            bool foundLocal = false;
            for (const auto& member : view.members)
            {
                if (member.id.Empty() || member.slot >= kMaxMembers || !member.endpoint.gamePort || !LocalAddress(member.endpoint.ipv4) ||
                    std::any_of(next.begin(), next.end(), [&](const Peer& old)
                    { return old.local == member.id || old.slot == member.slot ||
                        (old.endpoint.ipv4 == member.endpoint.ipv4 && old.endpoint.gamePort == member.endpoint.gamePort); }))
                    return Fail("Invalid or duplicate native LAN peer");
                Identity native;
                if (!Map(candidate, member.id, 2, native)) return Fail("Native LAN identity collision or mapping limit");
                next.push_back({member.id, native, member.endpoint, member.slot});
                if (member.id == view.owner) owner = native;
                if (member.id == local) { mine = native; foundLocal = true; }
            }
            if (!foundLocal) return Fail("Local player absent from accepted roster");
            std::sort(next.begin(), next.end(), Before);
            mappings = std::move(candidate); peers = std::move(next); session = view.session;
            revision = view.revision; phase = view.phase;
            object.currentLobby = lobby; localNative = mine; ownerNative = owner;
            return true;
        }
    };
    Adapter::Adapter(Id id) : impl_(new Impl(id)) {}
    Adapter::~Adapter() = default;
    bool Adapter::Apply(const View& view) { return impl_->Apply(view); }
    void Adapter::Reset() { impl_->Reset(); }
    bool Adapter::HasLobby() const { return !impl_->peers.empty(); }
    Identity Adapter::Lobby() const { return impl_->object.currentLobby; }
    Identity* Adapter::Local(Identity* out) const { return Copy(out, impl_->localNative); }
    Identity* Adapter::Owner(Identity* out, const Identity& lobby) const
    { return Copy(out, impl_->Matches(lobby) ? impl_->ownerNative : Identity{}); }
    Identity* Adapter::Member(Identity* out, const Identity& lobby, int32_t index) const
    { return Copy(out, impl_->Matches(lobby) && index >= 0 && size_t(index) < impl_->peers.size() ? impl_->peers[size_t(index)].native : Identity{}); }
    const Peer* Adapter::Find(const Identity& id) const
    {
        const auto found = std::find_if(impl_->peers.begin(), impl_->peers.end(), [&](const Peer& p) { return Equal(p.native, id); });
        return found == impl_->peers.end() ? nullptr : &*found;
    }
    size_t Adapter::Members() const { return impl_->peers.size(); }
    uint32_t Adapter::Count(const Identity& lobby) const { return impl_->Matches(lobby) ? uint32_t(impl_->peers.size()) : 0; }
    const std::string& Adapter::Error() const { return impl_->error; }
#ifdef OPENSHIM_DIRECT_LAN_ABI_TEST
    void* Adapter::QualificationObject() { return impl_->local.Empty() ? nullptr : &impl_->object; }
#endif
}
