#pragma once

// State-version model for the generic chunk batch.
//
// The batch is a single Ogre ManualObject that is torn down and re-emitted
// inside RebuildAndSubmitGenericChunkBatch(). That function is reached from the
// game's own _updateRenderQueue override, which Ogre drives once per camera
// traversal per active material scheme -- measured at 3.02-3.03 times per
// rendered frame on lcbench. Every one of those calls re-transformed and
// re-emitted the entire vertex set even though the source state had not moved
// between them.
//
// Why the version is *derived* from the source rather than *declared* by its
// mutators. UpdateChunkProxySlotPosition() unconditionally clears
// genericBatchKind/genericBatchTransformReady at the top of every slot update
// and then re-sets them further down, so a slot that did not change still
// performs a clear-then-restore each simulation tick. Bumping a counter at each
// write site would therefore fire on every slot every tick and dedup nothing,
// and restructuring those writes into a single commit point risks missing an
// exit path -- which fails in the worst direction, leaving stale geometry on
// screen. Hashing the state the rebuild is about to consume cannot miss a
// mutation site, because it reads the same fields the rebuild reads, and it
// folds into the eligibility scan that function already performs. There is no
// additional pass over the slots.
//
// The version deliberately does not include the frame number: reuse is keyed on
// the source state, not on a once-per-frame gate. Chunks that legitimately move
// twice within one frame rebuild twice; debris that is unchanged across several
// frames rebuilds zero times.

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace BZROpenShim::ChunkBatchInvalidation
{
    // FNV-1a. 64 bits is chosen over 32 because a collision here does not
    // degrade quality gracefully -- it silently draws last frame's debris
    // positions -- and the cost difference is a single multiply per mix.
    inline constexpr std::uint64_t kOffsetBasis = 1469598103934665603ull;
    inline constexpr std::uint64_t kPrime = 1099511628211ull;

    // A version that has never been built. Distinct from any live version
    // because MixCount() always folds in at least the chunk count.
    inline constexpr std::uint64_t kUnbuiltVersion = 0ull;

    class SourceVersion
    {
    public:
        void MixBytes(const void* data, std::size_t size)
        {
            const auto* bytes = static_cast<const std::uint8_t*>(data);
            for (std::size_t i = 0; i < size; ++i)
            {
                hash_ ^= bytes[i];
                hash_ *= kPrime;
            }
        }

        void MixU32(std::uint32_t value) { MixBytes(&value, sizeof(value)); }

        // Floats are mixed by their exact bit pattern, not by value: two
        // transforms that differ only in the last mantissa bit produce
        // different vertices, so they must produce different versions. This
        // also means a NaN transform is stable rather than never-equal.
        void MixFloat(float value)
        {
            std::uint32_t bits = 0;
            std::memcpy(&bits, &value, sizeof(bits));
            // Normalise the two zeroes so a -0.0f transform does not force a
            // rebuild against an otherwise identical +0.0f one.
            if (bits == 0x80000000u)
                bits = 0u;
            MixU32(bits);
        }

        std::uint64_t Value() const
        {
            // Never hand back kUnbuiltVersion for real content: a legitimately
            // hashed state must not be mistaken for "nothing built yet".
            return hash_ == kUnbuiltVersion ? kPrime : hash_;
        }

    private:
        std::uint64_t hash_ = kOffsetBasis;
    };

    // Everything about one slot that changes the emitted geometry. Position,
    // orientation and scale all feed AppendGenericChunkBatchGeometry, and the
    // kind selects which vertex table is emitted, so all of it is in.
    struct SlotState
    {
        std::uint8_t kind = 0;
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        float qw = 1.0f;
        float qx = 0.0f;
        float qy = 0.0f;
        float qz = 0.0f;
        float sx = 1.0f;
        float sy = 1.0f;
        float sz = 1.0f;
    };

    inline void MixSlot(SourceVersion& version, std::uint32_t ordinal, const SlotState& slot)
    {
        // The ordinal is folded in so that two slots swapping content is not
        // mistaken for no change. Emission order determines index order, and a
        // reordered batch is a different batch even when the set is equal.
        version.MixU32(ordinal);
        version.MixU32(slot.kind);
        version.MixFloat(slot.x);
        version.MixFloat(slot.y);
        version.MixFloat(slot.z);
        version.MixFloat(slot.qw);
        version.MixFloat(slot.qx);
        version.MixFloat(slot.qy);
        version.MixFloat(slot.qz);
        version.MixFloat(slot.sx);
        version.MixFloat(slot.sy);
        version.MixFloat(slot.sz);
    }

    inline void MixCount(SourceVersion& version, std::uint32_t chunkCount)
    {
        version.MixU32(chunkCount);
    }

    // Why a rebuild happened, so the telemetry can say more than "it rebuilt".
    enum class Reason : std::uint8_t
    {
        None = 0,             // reused; no rebuild
        NeverBuilt,           // first build of this ManualObject
        SourceChanged,        // chunk membership or a transform moved
        ObjectRecreated,      // ManualObject/SceneManager changed under us
        SectionMissing,       // no section yet, so beginUpdate is not legal
        MaterialChanged,      // batch material identity changed
        ForcedByCaller,       // opt-out or diagnostics demanded a rebuild
    };

    inline const char* ReasonName(Reason reason)
    {
        switch (reason)
        {
        case Reason::None: return "reused";
        case Reason::NeverBuilt: return "never-built";
        case Reason::SourceChanged: return "source-changed";
        case Reason::ObjectRecreated: return "object-recreated";
        case Reason::SectionMissing: return "section-missing";
        case Reason::MaterialChanged: return "material-changed";
        case Reason::ForcedByCaller: return "forced";
        }
        return "unknown";
    }

    // Inputs the decision needs from the live batch. Kept as a plain struct so
    // the policy can be exercised without Ogre.
    struct BuiltState
    {
        std::uint64_t version = kUnbuiltVersion;
        bool objectAlive = false;
        bool sectionCreated = false;
        bool objectIdentityStable = true;
        bool materialStable = true;
    };

    // The whole reuse policy, in one place. Every uncertain input resolves
    // toward rebuilding: reuse requires an intact object, an existing section,
    // stable identity and material, and a byte-identical source version.
    inline Reason DecideRebuild(
        const BuiltState& built,
        std::uint64_t sourceVersion,
        bool forceRebuild)
    {
        if (forceRebuild)
            return Reason::ForcedByCaller;
        if (!built.objectAlive)
            return Reason::ObjectRecreated;
        if (!built.objectIdentityStable)
            return Reason::ObjectRecreated;
        if (!built.materialStable)
            return Reason::MaterialChanged;
        if (!built.sectionCreated)
            return Reason::SectionMissing;
        if (built.version == kUnbuiltVersion)
            return Reason::NeverBuilt;
        if (built.version != sourceVersion)
            return Reason::SourceChanged;
        return Reason::None;
    }

    inline bool ShouldRebuild(Reason reason) { return reason != Reason::None; }

    // Bounded telemetry. Fixed-size, no allocation, safe to read from the
    // render thread and print on an interval.
    inline constexpr std::size_t kMaxTrackedSchemes = 8;
    inline constexpr std::size_t kMaxSchemeNameLength = 31;

    struct SchemeCounters
    {
        char name[kMaxSchemeNameLength + 1] = {};
        std::uint64_t requests = 0;
        std::uint64_t rebuilds = 0;
    };

    struct Telemetry
    {
        std::uint64_t requests = 0;          // calls that reached the decision
        std::uint64_t rebuilds = 0;          // decisions that re-emitted geometry
        std::uint64_t reused = 0;            // decisions that re-submitted as-is
        std::uint64_t emptySkips = 0;        // no eligible chunks at all
        std::uint64_t verticesRebuilt = 0;
        std::uint64_t indicesRebuilt = 0;
        std::uint64_t rebuildNanoseconds = 0;
        std::uint64_t maxRebuildNanoseconds = 0;
        std::uint64_t reasonCounts[8] = {};
        SchemeCounters schemes[kMaxTrackedSchemes] = {};
        std::size_t schemeCount = 0;

        void NoteReason(Reason reason)
        {
            const auto index = static_cast<std::size_t>(reason);
            if (index < (sizeof(reasonCounts) / sizeof(reasonCounts[0])))
                ++reasonCounts[index];
        }

        // Attributes one request to a material scheme so the per-frame
        // multiplicity can be blamed on a specific pass. Unknown schemes past
        // the table limit are folded into the last slot rather than dropped, so
        // the totals still reconcile with `requests`.
        void NoteScheme(const char* schemeName, bool rebuilt)
        {
            const char* name = (schemeName && schemeName[0]) ? schemeName : "<none>";
            for (std::size_t i = 0; i < schemeCount; ++i)
            {
                if (std::strncmp(schemes[i].name, name, kMaxSchemeNameLength) == 0)
                {
                    ++schemes[i].requests;
                    if (rebuilt)
                        ++schemes[i].rebuilds;
                    return;
                }
            }
            if (schemeCount < kMaxTrackedSchemes)
            {
                SchemeCounters& entry = schemes[schemeCount++];
                // Hand-rolled bounded copy rather than strncpy: the tests
                // build with /W4 /WX, where strncpy is a deprecation error.
                std::size_t length = 0;
                while (length < kMaxSchemeNameLength && name[length] != 0)
                {
                    entry.name[length] = name[length];
                    ++length;
                }
                entry.name[length] = 0;
                entry.requests = 1;
                entry.rebuilds = rebuilt ? 1u : 0u;
                return;
            }
            SchemeCounters& overflow = schemes[kMaxTrackedSchemes - 1];
            ++overflow.requests;
            if (rebuilt)
                ++overflow.rebuilds;
        }
    };
}
