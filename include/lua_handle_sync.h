#pragma once
// lua_handle_sync.h -- engine-independent logic behind the Lua handle label
// remap (src/patches/lua_handle_sync.cpp).
//
// Redux's Lua Send/Receive serialises a Handle as the 4-byte
// DistributedObject::dwLocalID of the object it names. dwLocalID is only
// assigned by DistributedObject::SetLocal (owner << 16 | counter), so objects
// that came out of the .bzn and were never networked (geysers, scenery,
// beacons) have id 0 and arrive on every receiver as nil. Labels, in contrast,
// resolve to the same object on every peer.
//
// The remap keeps the 4-byte payload and spends part of the id space on it:
//
//     reserved id = 0x80000000 | fnv1a32(label) & 0x7FFFFFFF
//
// Real ids are owner << 16 | counter, so a reserved id would need a network
// owner id of 0x8000 (32768) or more. The receiver additionally lets the
// stock lookup win for any id it recognises, so a real object is never
// shadowed by a label hash.
//
// This header holds the hash and the label index only, so it builds and is
// tested without the engine.

#include <cstddef>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <utility>

namespace BZROpenShim
{
    namespace LuaHandleSync
    {
        constexpr uint32_t kReservedBit = 0x80000000u;
        constexpr uint32_t kHashMask = 0x7FFFFFFFu;
        // Longest label the remap will carry. Labels beyond this are left to
        // the stock behaviour (nil) rather than hashed from a truncated copy.
        constexpr size_t kMaxLabelLength = 127;

        inline uint32_t Fnv1a32(const char* text)
        {
            uint32_t hash = 2166136261u;
            if (!text)
                return hash;
            for (const unsigned char* p = reinterpret_cast<const unsigned char*>(text); *p; ++p)
            {
                hash ^= *p;
                hash *= 16777619u;
            }
            return hash;
        }

        inline bool IsReservedId(uint32_t id)
        {
            return (id & kReservedBit) != 0;
        }

        inline uint32_t LabelHash31(const char* label)
        {
            return Fnv1a32(label) & kHashMask;
        }

        inline uint32_t MakeReservedId(const char* label)
        {
            return kReservedBit | LabelHash31(label);
        }

        // True for a label the remap is willing to carry.
        inline bool IsCarriableLabel(const char* label)
        {
            if (!label || !*label)
                return false;
            size_t length = 0;
            while (label[length])
            {
                if (++length > kMaxLabelLength)
                    return false;
            }
            return true;
        }

        // Index from label hash to the one object that carries it.
        //
        // Fail-closed rules, so a wrong object is never named:
        //   * two different labels with one hash   -> Collision (neither used)
        //   * two objects with the same label      -> Ambiguous (neither used)
        // Only a hash owned by exactly one object under exactly one label
        // resolves as Unique.
        class LabelIndex
        {
        public:
            enum class Status
            {
                Unknown,
                Unique,
                Ambiguous,
                Collision,
            };

            struct Result
            {
                Status status = Status::Unknown;
                uintptr_t tag = 0;
                std::string label;
            };

            void Clear()
            {
                entries_.clear();
                collisions_ = 0;
            }

            // `tag` identifies the object (the engine pointer in production).
            void Add(const char* label, uintptr_t tag)
            {
                if (!IsCarriableLabel(label))
                    return;
                const uint32_t hash = LabelHash31(label);
                auto found = entries_.find(hash);
                if (found == entries_.end())
                {
                    Entry entry;
                    entry.label = label;
                    entry.tag = tag;
                    entry.objects = 1;
                    entries_.emplace(hash, std::move(entry));
                    return;
                }
                Entry& entry = found->second;
                if (entry.label != label)
                {
                    if (!entry.collision)
                        ++collisions_;
                    entry.collision = true;
                    return;
                }
                if (entry.tag != tag)
                    ++entry.objects;
            }

            Result Lookup(uint32_t reservedIdOrHash) const
            {
                Result result;
                const auto found = entries_.find(reservedIdOrHash & kHashMask);
                if (found == entries_.end())
                    return result;
                const Entry& entry = found->second;
                result.label = entry.label;
                result.tag = entry.tag;
                if (entry.collision)
                    result.status = Status::Collision;
                else if (entry.objects > 1)
                    result.status = Status::Ambiguous;
                else
                    result.status = Status::Unique;
                return result;
            }

            // Status of the label itself, for the pack side: unique only when
            // this label's hash is owned by this label on exactly one object.
            Result LookupLabel(const char* label) const
            {
                if (!IsCarriableLabel(label))
                    return Result();
                Result result = Lookup(LabelHash31(label));
                if (result.status != Status::Unknown && result.label != label)
                    result.status = Status::Collision;
                return result;
            }

            size_t Size() const { return entries_.size(); }
            size_t CollisionCount() const { return collisions_; }

        private:
            struct Entry
            {
                std::string label;
                uintptr_t tag = 0;
                uint32_t objects = 0;
                bool collision = false;
            };

            std::unordered_map<uint32_t, Entry> entries_;
            size_t collisions_ = 0;
        };
    }
}
