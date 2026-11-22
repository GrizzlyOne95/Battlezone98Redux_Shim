// splinter_payload_local.h -- pure, host-testable half of the Splinter payload
// fix. splinter_payload_local.cpp owns the code and vtable rewrites; this
// header owns the payload registry, the decisions and the byte-level facts of
// the sites.
//
// A SprayBuilding builds its payload on every peer with source == that peer and
// never sends it. The payload can be any ordnance class (OrdnanceClass::Find
// has no class filter). Three classes then re-send or spawn sent ordnance from
// every peer, because their owner-only branch tests source == me:
//   - SprayBomb::Hit and BounceBomb::Hit: both bounce branches compare the
//     bomb's source (u16 at +0x7C, zero-extended into ESI) with the low 16 bits
//     of Net_GetMyPlayerID and, in a network game, set bSend (+0x80) to 1 so
//     the bomb is resent.
//   - Popper::Control: builds its child ordnance and sets the child's bSend to
//     1, so every peer sends its own child.
// Other classes with such a test were checked and left alone (see the .cpp).
//
// bSend cannot tell a payload apart: Ordnance_Sent (GOG 0x00584530) drops a
// launcher's own bomb from 2 back to 0 once it has gone out, so a thrown bomb
// also reads source == me and bSend 0. Payloads are therefore marked
// positively: the payload build call in SprayBuilding::Simulate records every
// SprayBomb, BounceBomb or Popper it returns, and a recorded Popper's children
// of those classes are recorded too. Ordnance is pooled (a dead bomb goes back
// on its class free list and is reused with Init only), so records mostly go
// stale rather than being destroyed. A record matches only on the same address,
// (source, ordid) and owner (+0xD8), and the registry is cleared when the
// mission teardown resets the ordid counter. The SprayBomb destructor drops a
// record as a backstop. Only network games record anything, and payloads
// built before a mid-mission install are not recorded and behave as stock.

#pragma once

#include <cstddef>
#include <cstdint>
#include <unordered_map>

namespace BZROpenShim
{
    namespace SplinterPayloadLocal
    {
        // Frame slots holding the ordnance: SprayBomb::Hit EBP - 0x1B0,
        // BounceBomb::Hit EBP - 0x100, Popper::Control EBP - 0xD0 (the Popper;
        // its new child is in ECX at the patched store).
        constexpr intptr_t kSprayBombFrameOffset = -0x1B0;
        constexpr intptr_t kBounceBombFrameOffset = -0x100;
        constexpr intptr_t kPopperFrameOffset = -0xD0;

        // Ordnance fields.
        constexpr uintptr_t kOrdnanceSourceOffset = 0x7C;
        constexpr uintptr_t kOrdnanceOrdIdOffset = 0x7E;
        constexpr uintptr_t kOrdnanceSendOffset = 0x80;
        constexpr uintptr_t kOrdnanceOwnerOffset = 0xD8; // creator obj76 (Ordnance::Init)

        // The five bytes at each call site start with a rel32 CALL.
        constexpr size_t kCallLength = 5;
        constexpr uint8_t kCallOpcode = 0xE8;

        // Popper::Control's `mov dword [ecx+0x80], 1` (the child's bSend),
        // rewritten as a CALL plus a 5-byte NOP.
        constexpr size_t kPopperStoreLength = 10;
        constexpr uint8_t kPopperStoreStock[kPopperStoreLength] = { 0xC7, 0x81, 0x80, 0x00, 0x00,
                                                                    0x00, 0x01, 0x00, 0x00, 0x00 };
        constexpr uint8_t kNop5[5] = { 0x0F, 0x1F, 0x44, 0x00, 0x00 };

        // More payload bombs alive at once than any real game makes. A bomb
        // that does not fit is not recorded and keeps the stock behaviour.
        constexpr size_t kMaxPayloads = 4096;

        // The payload classes whose owner-only branch re-sends: SprayBomb,
        // BounceBomb and Popper. A zero vtable never matches.
        inline bool IsRecordedPayloadClass(uint32_t vtable, uint32_t sprayBombVtable, uint32_t bounceBombVtable,
                                           uint32_t popperVtable)
        {
            return vtable != 0 && (vtable == sprayBombVtable || vtable == bounceBombVtable || vtable == popperVtable);
        }

        inline uint32_t MakeKey(uint16_t source, uint16_t ordId)
        {
            return (static_cast<uint32_t>(source) << 16) | ordId;
        }

        // Payload ordnance alive on this peer, by address, each with the
        // (source, ordid) key and owner it was built with. Key and owner guard
        // against a stale record: a pooled bomb reused by the factory carries a
        // new ordid and its own creator, so it does not read as a payload.
        // After a u16 ordid wrap the owner check only narrows a stale match; a
        // reused bomb with the same address, key and owner still matches.
        // Clear() must run whenever the ordid counter restarts. Not
        // thread-safe; the caller locks.
        class PayloadRegistry
        {
        public:
            // False when the registry is full (the bomb stays stock).
            bool Add(uintptr_t bomb, uint32_t key, uint32_t owner)
            {
                if (!bomb)
                    return false;
                const auto it = m_ByBomb.find(bomb);
                if (it != m_ByBomb.end())
                {
                    it->second = Entry{ key, owner };
                    return true;
                }
                if (m_ByBomb.size() >= kMaxPayloads)
                    return false;
                m_ByBomb.emplace(bomb, Entry{ key, owner });
                return true;
            }

            void Remove(uintptr_t bomb) { m_ByBomb.erase(bomb); }

            void Clear() { m_ByBomb.clear(); }

            bool Contains(uintptr_t bomb, uint32_t key, uint32_t owner) const
            {
                const auto it = m_ByBomb.find(bomb);
                return it != m_ByBomb.end() && it->second.key == key && it->second.owner == owner;
            }

            size_t Size() const { return m_ByBomb.size(); }

        private:
            struct Entry
            {
                uint32_t key;
                uint32_t owner;
            };
            std::unordered_map<uintptr_t, Entry> m_ByBomb;
        };

        // What the rewritten my-id call returns to the stock compare. For a
        // recorded payload whose source is this peer, the source with bit 0
        // flipped, so the compare fails and the bounce stays local. Every other
        // bomb (the launcher's own thrown one, whatever its bSend; a received
        // one) gets the real id back.
        inline uint16_t ReportedPlayerId(uint16_t myId, bool isLocalPayload, uint16_t source)
        {
            if (isLocalPayload && source == myId)
                return static_cast<uint16_t>(source ^ 1u);
            return myId;
        }

        inline bool KeepsBounceLocal(uint16_t myId, bool isLocalPayload, uint16_t source)
        {
            return ReportedPlayerId(myId, isLocalPayload, source) != myId;
        }

        // The bSend a Popper's new child gets: stock 1 (sent), or 0 (local) when
        // the Popper is itself a recorded payload.
        inline uint32_t PopperChildSend(bool popperIsLocalPayload)
        {
            return popperIsLocalPayload ? 0u : 1u;
        }

        // Absolute target of the rel32 CALL whose first byte is at `site`.
        inline uint32_t CallTarget(uint32_t site, const uint8_t (&bytes)[kCallLength])
        {
            const uint32_t rel = static_cast<uint32_t>(bytes[1]) | (static_cast<uint32_t>(bytes[2]) << 8) |
                                 (static_cast<uint32_t>(bytes[3]) << 16) | (static_cast<uint32_t>(bytes[4]) << 24);
            return site + static_cast<uint32_t>(kCallLength) + rel;
        }

        // A site may be rewritten only while it is still the stock call: the
        // opcode is a rel32 CALL and it reaches `expected`.
        inline bool SiteIsStockCall(uint32_t site, const uint8_t (&bytes)[kCallLength], uint32_t expected)
        {
            return expected != 0 && bytes[0] == kCallOpcode && CallTarget(site, bytes) == expected;
        }

        inline bool PopperStoreIsStock(const uint8_t (&bytes)[kPopperStoreLength])
        {
            for (size_t i = 0; i < kPopperStoreLength; ++i)
            {
                if (bytes[i] != kPopperStoreStock[i])
                    return false;
            }
            return true;
        }
    }
}
