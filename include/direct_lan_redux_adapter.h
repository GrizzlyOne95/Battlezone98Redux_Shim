#pragma once
#include "direct_lan_session.h"
#include <cstddef>
#include <memory>

namespace BZROpenShim::DirectLan::Redux
{
    // Released 2.2.301 identity operations read/write 0, 8 and 12. Offset 4
    // is deliberately unnamed and preserved by output operations. This is an
    // internal representation for the qualified query subset, not an SDK ABI.
    struct Identity
    {
        uint32_t discriminator = 0;
        std::array<uint8_t, 4> untouched{};
        uint32_t word8 = 0, word12 = 0;
    };
    static_assert(sizeof(Identity) == 16 && offsetof(Identity, word8) == 8 && offsetof(Identity, word12) == 12);
    bool Equal(const Identity&, const Identity&);
    bool Less(const Identity&, const Identity&);
    bool DirectIdentity(const Identity&); // discriminator 3, nonzero value
    Identity* Copy(Identity* output, const Identity&); // preserves offset 4

    struct Peer
    {
        Id local;
        Identity native;
        Endpoint endpoint;
        uint8_t slot = 0; // control slot; NOT Redux's uint16 gameplay player ID
    };

    // Projection from accepted session snapshots to Redux identity/roster
    // queries. No engine globals, allocations, hooks or callbacks are touched.
    // Only vtable +38/+48/+68 are implemented. This partial object MUST NOT
    // be installed as a game backend; lifecycle and gameplay are unqualified.
    class Adapter
    {
    public:
        explicit Adapter(Id local);
        ~Adapter();
        Adapter(const Adapter&) = delete;
        Adapter& operator=(const Adapter&) = delete;
        bool Apply(const View&);
        void Reset();
        bool HasLobby() const;
        Identity Lobby() const;
        Identity* Local(Identity*) const;
        Identity* Owner(Identity*, const Identity& lobby) const;
        Identity* Member(Identity*, const Identity& lobby, int32_t index) const;
        const Peer* Find(const Identity&) const; // borrowed until Apply/Reset; never lent to engine callbacks
        size_t Members() const;
        const std::string& Error() const;
#ifdef OPENSHIM_DIRECT_LAN_ABI_TEST
        // Test harness only: exposes the deliberately incomplete query object
        // to released-code predicates. There is no production install API.
        void* QualificationObject();
#endif
    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}
