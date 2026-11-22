#include "splinter_payload_local.h"

#include <cstdint>
#include "test_check.h"

namespace
{
    using namespace BZROpenShim::SplinterPayloadLocal;
    using OpenShimTest::Check;

    // GOG Redux 2.2.301 (scripts/patches.json fallbacks).
    constexpr uint32_t kBuildSite = 0x005DAB73;
    constexpr uint32_t kTerrainSite = 0x005DB444;
    constexpr uint32_t kObjectSite = 0x005DB7C6;
    constexpr uint32_t kOrdnanceFactory = 0x00586FF0;
    constexpr uint32_t kGetMyPlayerId = 0x00572D90;
    constexpr uint32_t kBounceTerrainSite = 0x0047E447;
    constexpr uint32_t kBounceObjectSite = 0x0047E7B8;
    constexpr uint32_t kSprayBombVtable = 0x008881C4;
    constexpr uint32_t kBounceBombVtable = 0x008765C4;
    constexpr uint32_t kBeamVtable = 0x00876474;
    constexpr uint32_t kCleanupSite = 0x0061847D;
    constexpr uint32_t kOrdnanceCleanup = 0x00584E60;
    constexpr uint32_t kPopperVtable = 0x00885D48;
    constexpr uint32_t kSniperShellVtable = 0x00887BB4;
    constexpr uint32_t kPopperStoreSite = 0x005A6A98;


    constexpr uint16_t kMe = 3;
    constexpr uint32_t kOwner = 0x0BAD0000; // creator obj76 at +0xD8


    // What the bounce compare sees for `bomb`, as ReportedIdForFrame decides it.
    uint16_t Reported(const PayloadRegistry& registry, uintptr_t bomb, uint16_t source, uint16_t ordId)
    {
        return ReportedPlayerId(kMe, registry.Contains(bomb, MakeKey(source, ordId), kOwner), source);
    }

    void TestRegistry()
    {
        PayloadRegistry registry;
        Check(registry.Size() == 0, "a new registry is empty");
        Check(registry.Add(0x1000, MakeKey(kMe, 7), kOwner), "a payload is recorded");
        Check(registry.Contains(0x1000, MakeKey(kMe, 7), kOwner), "the recorded payload is found");
        Check(!registry.Contains(0x1000, MakeKey(kMe, 8), kOwner), "the same address with another ordid is not");
        Check(!registry.Contains(0x1000, MakeKey(kMe + 1, 7), kOwner), "the same address with another source is not");
        Check(!registry.Contains(0x2000, MakeKey(kMe, 7), kOwner), "another address is not");

        Check(registry.Add(0x1000, MakeKey(kMe, 9), kOwner), "a reused address is re-recorded");
        Check(registry.Size() == 1, "re-recording does not grow the registry");
        Check(registry.Contains(0x1000, MakeKey(kMe, 9), kOwner), "the reused address carries its new key");
        Check(!registry.Contains(0x1000, MakeKey(kMe, 7), kOwner), "the old key no longer matches");

        registry.Remove(0x1000);
        Check(!registry.Contains(0x1000, MakeKey(kMe, 9), kOwner), "a destroyed payload is dropped");
        Check(registry.Size() == 0, "the registry is empty again");
        registry.Remove(0x1000);
        Check(registry.Size() == 0, "removing an absent bomb is harmless");

        Check(!registry.Add(0, MakeKey(kMe, 1), kOwner), "a null bomb is refused");
        Check(registry.Size() == 0, "a refused bomb is not stored");
    }

    void TestRegistryCap()
    {
        PayloadRegistry registry;
        for (uintptr_t i = 1; i <= kMaxPayloads; ++i)
            registry.Add(i * 0x10, MakeKey(kMe, static_cast<uint16_t>(i)), kOwner);
        Check(registry.Size() == kMaxPayloads, "the registry fills to its cap");
        Check(!registry.Add(0x7FFF0000, MakeKey(kMe, 1), kOwner), "a payload past the cap is refused");
        Check(!registry.Contains(0x7FFF0000, MakeKey(kMe, 1), kOwner), "a refused payload keeps the stock bounce");
        Check(registry.Add(0x10, MakeKey(kMe, 2), kOwner), "an address already recorded can still be re-keyed when full");
    }

    void TestLocalPayloadIsKeptLocal()
    {
        PayloadRegistry registry;
        registry.Add(0x1000, MakeKey(kMe, 7), kOwner);
        const uint16_t reported = Reported(registry, 0x1000, kMe, 7);
        Check(reported != kMe, "a recorded payload gets an id that cannot match its source");
        Check(reported == 2, "the reported id is the source with bit 0 flipped");
        Check(KeepsBounceLocal(kMe, true, kMe), "a recorded payload bounce stays local");
        Check(ReportedPlayerId(0, true, 0) == 1, "player id 0 flips to 1");
        Check(ReportedPlayerId(0xFFFF, true, 0xFFFF) == 0xFFFE, "the top id flips within 16 bits");
    }

    void TestLauncherSentBombIsStock()
    {
        // The launcher's own thrown SprayBomb: source == me, and Ordnance_Sent
        // has already dropped its bSend from 2 to 0. It was never built by a
        // SprayBuilding, so it is not in the registry and must still resync.
        PayloadRegistry registry;
        registry.Add(0x1000, MakeKey(kMe, 7), kOwner); // an unrelated payload
        Check(Reported(registry, 0x2000, kMe, 8) == kMe, "the launcher's sent bomb (bSend 0) gets the real id");
        Check(!KeepsBounceLocal(kMe, registry.Contains(0x2000, MakeKey(kMe, 8), kOwner), kMe),
              "the launcher's sent bomb is NOT kept local");

        // After a payload dies without its destructor being seen, a thrown bomb
        // reusing that address has a new ordid and still resyncs.
        Check(Reported(registry, 0x1000, kMe, 11) == kMe, "a thrown bomb at a stale payload address is stock");
    }

    void TestRecordedPayloadClasses()
    {
        Check(IsRecordedPayloadClass(kSprayBombVtable, kSprayBombVtable, kBounceBombVtable, kPopperVtable),
              "a SprayBomb payload is recorded");
        Check(IsRecordedPayloadClass(kBounceBombVtable, kSprayBombVtable, kBounceBombVtable, kPopperVtable),
              "a BounceBomb payload is recorded");
        Check(IsRecordedPayloadClass(kPopperVtable, kSprayBombVtable, kBounceBombVtable, kPopperVtable),
              "a Popper payload is recorded");
        Check(!IsRecordedPayloadClass(kBeamVtable, kSprayBombVtable, kBounceBombVtable, kPopperVtable),
              "a Beam payload is not recorded");
        Check(!IsRecordedPayloadClass(kSniperShellVtable, kSprayBombVtable, kBounceBombVtable, kPopperVtable),
              "a SniperShell payload is not recorded");
        Check(!IsRecordedPayloadClass(0, 0, 0, 0), "an unbound vtable never matches");

        // A BounceBomb payload shares the registry and the decision.
        PayloadRegistry registry;
        registry.Add(0x5000, MakeKey(kMe, 4), kOwner);
        Check(Reported(registry, 0x5000, kMe, 4) != kMe, "a recorded BounceBomb payload bounce stays local");
        Check(Reported(registry, 0x6000, kMe, 5) == kMe, "the launcher's own BounceBomb keeps its resync");
    }

    void TestOwnerMustMatch()
    {
        // A pooled bomb reused for another creator, at the same address and
        // (after a u16 ordid wrap) the same key, is not the recorded payload.
        PayloadRegistry registry;
        registry.Add(0x1000, MakeKey(kMe, 7), kOwner);
        Check(registry.Contains(0x1000, MakeKey(kMe, 7), kOwner), "same address, key and owner matches");
        Check(!registry.Contains(0x1000, MakeKey(kMe, 7), kOwner + 4), "another owner does not match");
        Check(!registry.Contains(0x1000, MakeKey(kMe, 7), 0), "an ownerless bomb does not match");
        Check(!KeepsBounceLocal(kMe, registry.Contains(0x1000, MakeKey(kMe, 7), kOwner + 4), kMe),
              "a reused bomb with another owner keeps its stock resync");
        Check(registry.Add(0x1000, MakeKey(kMe, 7), kOwner + 4), "re-recording takes the new owner");
        Check(!registry.Contains(0x1000, MakeKey(kMe, 7), kOwner), "the old owner no longer matches");
    }

    void TestPopperChild()
    {
        Check(PopperChildSend(true) == 0, "a payload Popper's child stays local (bSend 0)");
        Check(PopperChildSend(false) == 1, "any other Popper's child gets the stock bSend 1");

        // Bytes at the shipped store, 0x005A6A98: mov dword [ecx+0x80], 1.
        const uint8_t store[kPopperStoreLength] = { 0xC7, 0x81, 0x80, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 };
        Check(PopperStoreIsStock(store), "the Popper child store is the stock bSend = 1");
        uint8_t hooked[kPopperStoreLength] = { 0xE8, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x1F, 0x44, 0x00, 0x00 };
        Check(!PopperStoreIsStock(hooked), "an already rewritten store refuses");
        uint8_t zero[kPopperStoreLength] = { 0xC7, 0x81, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
        Check(!PopperStoreIsStock(zero), "a store of another value refuses");
        Check(kPopperStoreLength == kCallLength + sizeof(kNop5), "CALL plus NOP fills the store exactly");
        Check(kPopperStoreSite + kCallLength + sizeof(kNop5) == 0x005A6AA2,
              "the rewrite ends at the next instruction");
    }

    void TestMissionCleanupClearsStaleRecords()
    {
        // Ordnance is pooled, so a payload's record outlives the bomb. The
        // mission-teardown cleanup resets the ordid counter, so in the next
        // mission the launcher's own thrown bomb can get the same address and
        // the same (me, n) key. The cleanup hook clears the registry first.
        PayloadRegistry registry;
        registry.Add(0x1000, MakeKey(kMe, 1), kOwner);
        registry.Add(0x2000, MakeKey(kMe, 2), kOwner);
        Check(Reported(registry, 0x1000, kMe, 1) != kMe, "before the clear the stale record still matches");
        registry.Clear();
        Check(registry.Size() == 0, "the cleanup empties the registry");
        Check(Reported(registry, 0x1000, kMe, 1) == kMe,
              "next mission: same address, same key after a clear is NOT reported local");
        Check(!KeepsBounceLocal(kMe, registry.Contains(0x2000, MakeKey(kMe, 2), kOwner), kMe),
              "next mission: the launcher's reused bomb keeps its bounce resync");
        Check(registry.Add(0x1000, MakeKey(kMe, 1), kOwner), "a new payload is recorded after the clear");
        Check(Reported(registry, 0x1000, kMe, 1) != kMe, "and is kept local again");
    }

    void TestReceivedBombIsStock()
    {
        // A received bomb carries its sender's id; the stock compare already fails.
        PayloadRegistry registry;
        Check(Reported(registry, 0x3000, 5, 1) == kMe, "a received bomb gets the real id");
        Check(ReportedPlayerId(kMe, true, 5) == kMe, "even if recorded, another source gets the real id");
        Check(ReportedPlayerId(kMe, true, 2) == kMe, "a source equal to me ^ 1 still gets the real id");
        Check(!KeepsBounceLocal(kMe, true, 5), "a received bomb is left to stock");
    }

    void TestUnreadableBombIsStock()
    {
        Check(ReportedPlayerId(kMe, false, kMe) == kMe, "an unrecorded or unread bomb: the real id");
        Check(!KeepsBounceLocal(kMe, false, kMe), "an unrecorded or unread bomb: stock");
    }

    void TestSiteIdentity()
    {
        // Bytes at the three shipped sites.
        const uint8_t build[kCallLength] = { 0xE8, 0x78, 0xC4, 0xFA, 0xFF };
        const uint8_t terrain[kCallLength] = { 0xE8, 0x47, 0x79, 0xF9, 0xFF };
        const uint8_t object[kCallLength] = { 0xE8, 0xC5, 0x75, 0xF9, 0xFF };
        Check(CallTarget(kBuildSite, build) == kOrdnanceFactory, "build site reaches the OrdnanceClass factory");
        Check(CallTarget(kTerrainSite, terrain) == kGetMyPlayerId, "terrain site reaches Net_GetMyPlayerID");
        Check(CallTarget(kObjectSite, object) == kGetMyPlayerId, "object site reaches Net_GetMyPlayerID");
        Check(SiteIsStockCall(kBuildSite, build, kOrdnanceFactory), "build site is the stock call");
        Check(SiteIsStockCall(kTerrainSite, terrain, kGetMyPlayerId), "terrain site is the stock call");
        Check(SiteIsStockCall(kObjectSite, object, kGetMyPlayerId), "object site is the stock call");

        Check(!SiteIsStockCall(kTerrainSite, terrain, 0), "an unresolved target refuses");
        Check(!SiteIsStockCall(kTerrainSite, terrain, kGetMyPlayerId + 1), "another target refuses");
        Check(!SiteIsStockCall(kObjectSite, terrain, kGetMyPlayerId), "the terrain bytes at the object site refuse");
        Check(!SiteIsStockCall(kBuildSite, build, kGetMyPlayerId), "the build site does not reach the id call");
        const uint8_t bounceTerrain[kCallLength] = { 0xE8, 0x44, 0x49, 0x0F, 0x00 };
        const uint8_t bounceObject[kCallLength] = { 0xE8, 0xD3, 0x45, 0x0F, 0x00 };
        Check(SiteIsStockCall(kBounceTerrainSite, bounceTerrain, kGetMyPlayerId),
              "BounceBomb terrain site reaches Net_GetMyPlayerID");
        Check(SiteIsStockCall(kBounceObjectSite, bounceObject, kGetMyPlayerId),
              "BounceBomb object site reaches Net_GetMyPlayerID");
        Check(!SiteIsStockCall(kBounceObjectSite, bounceTerrain, kGetMyPlayerId),
              "the BounceBomb terrain bytes at the object site refuse");
        const uint8_t cleanup[kCallLength] = { 0xE8, 0xDE, 0xC9, 0xF6, 0xFF };
        Check(SiteIsStockCall(kCleanupSite, cleanup, kOrdnanceCleanup), "cleanup site reaches the ordnance cleanup");
        const uint8_t jmp[kCallLength] = { 0xE9, 0x47, 0x79, 0xF9, 0xFF };
        Check(!SiteIsStockCall(kTerrainSite, jmp, kGetMyPlayerId), "a JMP (another hook) refuses");
    }
}

int main()
{
    TestRegistry();
    TestRegistryCap();
    TestLocalPayloadIsKeptLocal();
    TestLauncherSentBombIsStock();
    TestRecordedPayloadClasses();
    TestOwnerMustMatch();
    TestPopperChild();
    TestMissionCleanupClearsStaleRecords();
    TestReceivedBombIsStock();
    TestUnreadableBombIsStock();
    TestSiteIdentity();
    return OpenShimTest::ExitCode();
}
