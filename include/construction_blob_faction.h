#pragma once

// Per-faction construction blob render effects ([Display] FactionConstructionBlobs).
//
// The stock ConstructionBlob draws one cnstblob.odf sprite over every build in
// progress. This feature reads optional render keys from the same
// [ConstructionBlob] section: blobRender (any faction) and blobRenderA/S/C/B
// (first letter of the ODF being built). When the built object's faction has
// a render, that blob's stock sprite is suppressed and one pooled engine
// render (the muzzleRender kind, file.section) follows the blob instead.
// Absent, empty or unresolved keys keep the stock sprite.
//
// The same option also drives the portal blob (portblob.odf [PortalBlob]):
// blobRender (both sprites), blobInRender (replaces blobInTexture, rpuff) and
// blobOutRender (replaces blobOutTexture, bpuff), with a second pool.
//
// The pure helpers here (parser, pool) are unit tested; the hooks live in
// src/patches/construction_blob_faction.cpp. See
// Docs/FACTION_CONSTRUCTION_BLOBS.md.

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>

namespace BZROpenShim::ConstructionBlobFaction
{
    inline constexpr size_t kFactionCount = 4;
    // Key 0 is the default for every faction; keys 1..4 follow FactionSlot().
    inline constexpr size_t kKeyCount = 1 + kFactionCount;
    inline constexpr const char* kRenderKeys[kKeyCount] = {
        "blobrender", "blobrendera", "blobrenders", "blobrenderc", "blobrenderb" };
    // Same identifier limit as muzzleRender: 1..63 printable characters.
    inline constexpr size_t kMaxRenderName = 63;

    // a = American, s = Soviet, c = Chinese, b = Black Dog; -1 for anything else.
    inline int FactionSlot(char odfFirstLetter)
    {
        switch (odfFirstLetter)
        {
        case 'a': case 'A': return 0;
        case 's': case 'S': return 1;
        case 'c': case 'C': return 2;
        case 'b': case 'B': return 3;
        default: return -1;
        }
    }

    namespace Detail
    {
        inline std::string_view Trim(std::string_view text)
        {
            const auto first = text.find_first_not_of(" \t\r\n");
            if (first == text.npos)
                return {};
            return text.substr(first, text.find_last_not_of(" \t\r\n") - first + 1);
        }

        inline bool EqualLower(std::string_view a, std::string_view lower)
        {
            if (a.size() != lower.size())
                return false;
            for (size_t i = 0; i < a.size(); ++i)
            {
                char c = a[i];
                if (c >= 'A' && c <= 'Z')
                    c = static_cast<char>(c + ('a' - 'A'));
                if (c != lower[i])
                    return false;
            }
            return true;
        }

        inline bool ValidName(std::string_view name)
        {
            if (name.empty() || name.size() > kMaxRenderName)
                return false;
            for (char c : name)
                if (c <= ' ' || c > '~' || c == '"' || c == '\'')
                    return false;
            return true;
        }
    }

    // Parsed render keys: key 0 is the default, keys 1..N-1 are per slot.
    template<size_t N>
    struct RenderKeysN
    {
        std::array<std::string, N> value{};
        std::array<bool, N> present{};

        // Effective render name for a slot (-1 = no slot of its own): its
        // own key when present (even empty, which forces the stock sprite),
        // else the key-0 default. Empty = stock sprite.
        const std::string& For(int slot) const
        {
            if (slot >= 0 && slot < static_cast<int>(N) - 1 && present[1 + slot])
                return value[1 + slot];
            return value[0];
        }
    };
    using RenderKeys = RenderKeysN<kKeyCount>;

    // Reads the given lower-case keys from one ODF section (lower-case name).
    // Values may be quoted; comments (; # //) outside quotes are ignored; the
    // first NUL ends the text. An invalid name (spaces, quotes, over 63
    // characters) counts as present but empty, so that slot keeps the stock
    // sprite rather than a guess.
    template<size_t N>
    inline RenderKeysN<N> ParseRenderKeys(std::string_view text, std::string_view sectionLower,
                                          const char* const (&keys)[N])
    {
        RenderKeysN<N> out;
        text = text.substr(0, text.find('\0'));
        bool inSection = false;
        while (!text.empty())
        {
            const auto end = text.find('\n');
            auto line = text.substr(0, end);
            text = end == text.npos ? std::string_view{} : text.substr(end + 1);
            char quote = 0;
            for (size_t i = 0; i < line.size(); ++i)
            {
                const char c = line[i];
                if (quote)
                {
                    if (c == quote)
                        quote = 0;
                }
                else if (c == '"' || c == '\'')
                    quote = c;
                else if (c == ';' || c == '#' ||
                         (c == '/' && i + 1 < line.size() && line[i + 1] == '/'))
                {
                    line = line.substr(0, i);
                    break;
                }
            }
            line = Detail::Trim(line);
            if (line.empty())
                continue;
            if (line.front() == '[')
            {
                inSection = line.back() == ']' &&
                    Detail::EqualLower(Detail::Trim(line.substr(1, line.size() - 2)), sectionLower);
                continue;
            }
            const auto equals = line.find('=');
            if (!inSection || equals == line.npos)
                continue;
            const auto key = Detail::Trim(line.substr(0, equals));
            auto value = Detail::Trim(line.substr(equals + 1));
            if (value.size() >= 2 && (value.front() == '"' || value.front() == '\'') &&
                value.back() == value.front())
                value = Detail::Trim(value.substr(1, value.size() - 2));
            for (size_t k = 0; k < N; ++k)
            {
                if (!Detail::EqualLower(key, keys[k]))
                    continue;
                out.present[k] = true;
                if (Detail::ValidName(value))
                    out.value[k].assign(value.data(), value.size());
                else
                    out.value[k].clear();
            }
        }
        return out;
    }

    // blobRender and blobRenderA/S/C/B from [ConstructionBlob] of cnstblob.odf.
    inline RenderKeys ParseOdf(std::string_view text)
    {
        return ParseRenderKeys(text, "constructionblob", kRenderKeys);
    }

    // Portal blob (portblob.odf [PortalBlob]): the stock emitter draws
    // blobInTexture (rpuff) for an inward blob and blobOutTexture (bpuff)
    // for an outward one. blobRender is the default for both;
    // blobInRender / blobOutRender replace one sprite each.
    inline constexpr size_t kPortalKeyCount = 3;
    inline constexpr const char* kPortalRenderKeys[kPortalKeyCount] = {
        "blobrender", "blobinrender", "bloboutrender" };
    using PortalRenderKeys = RenderKeysN<kPortalKeyCount>;

    // Slot for a portal blob entry's in flag (entry+0x14): 0 = in, 1 = out.
    inline int PortalSlot(bool in) { return in ? 0 : 1; }

    inline PortalRenderKeys ParsePortalOdf(std::string_view text)
    {
        return ParseRenderKeys(text, "portalblob", kPortalRenderKeys);
    }

    // Pooled render instances, one per active build (owner + target). Pure
    // bookkeeping over a backend, so it is unit tested and reusable by other
    // blob-like emitters (the portal blob uses a second pool). Storage slots live inside the
    // pool, which is a static object in the runtime: the engine keeps a
    // back-reference to each slot and nulls it when a render dies, so the
    // slot address must stay valid for the life of the process.
    struct BlobPose
    {
        float x, y, z;
    };

    struct BlobRenderBackend
    {
        // effect: caller-defined effect id (index into its resolved names).
        bool (*create)(void* context, int effect, const BlobPose& pose, void** storage);
        bool (*update)(void* context, void** storage, const BlobPose& pose);
        bool (*detach)(void* context, void** storage);
        void* context;
    };

    template<size_t Capacity>
    class BlobRenderPool
    {
    public:
        struct Slot
        {
            uintptr_t owner = 0;    // 0 = free (when storage is also null)
            uintptr_t target = 0;
            int effect = -1;
            void* storage = nullptr;
            bool touched = false;
            bool failed = false;    // create or update failed: stock sprite until released
        };

        // Called after the build appended its blob. Returns true while a
        // render stands for it (suppress the stock sprite), false to keep
        // the stock sprite. Creates at most once per build.
        bool Touch(const BlobRenderBackend& backend, uintptr_t owner, uintptr_t target, int effect,
                   const BlobPose& pose)
        {
            if (!owner || effect < 0)
                return false;
            Slot* slot = Find(owner, target);
            if (slot && slot->effect != effect)
            {
                Release(backend, *slot);
                slot = nullptr;
            }
            if (!slot)
            {
                slot = FreeSlot();
                if (!slot)
                    return false;  // capped: stock sprite
                slot->owner = owner;
                slot->target = target;
                slot->effect = effect;
                slot->failed = !backend.create(backend.context, effect, pose, &slot->storage) || !slot->storage;
                ++creates_;
                slot->touched = true;
                return !slot->failed;
            }
            slot->touched = true;
            if (slot->failed || !slot->storage)
                return false;  // failed, or the render ended itself: stock for the rest of this build
            if (!backend.update(backend.context, &slot->storage, pose))
            {
                // Detach but keep the build's slot, so it is not re-created
                // every pass; EndPass frees it when the build stops.
                Release(backend, *slot, false);
                slot->failed = true;
                slot->touched = true;
                return false;
            }
            return true;
        }

        // Once per simulation pass, before the builds re-add their blobs:
        // releases every build that added no blob since the previous pass
        // (finished, cancelled, or its owner is gone).
        void EndPass(const BlobRenderBackend& backend)
        {
            for (Slot& slot : slots_)
            {
                if (slot.owner && !slot.touched)
                    Release(backend, slot);
                slot.touched = false;
            }
        }

        // Scene teardown or mission load: release everything.
        void ReleaseAll(const BlobRenderBackend& backend)
        {
            for (Slot& slot : slots_)
                if (slot.owner || slot.storage)
                    Release(backend, slot);
        }

        // Mission load, after ReleaseAll: the previous world's render list
        // is gone, so drop every slot (including one whose detach failed)
        // without touching the engine again.
        void Forget()
        {
            slots_.fill(Slot{});
        }

        size_t Active() const
        {
            size_t n = 0;
            for (const Slot& slot : slots_)
                n += slot.storage ? 1 : 0;
            return n;
        }
        uint32_t Creates() const { return creates_; }
        const Slot& At(size_t i) const { return slots_[i]; }

    private:
        Slot* Find(uintptr_t owner, uintptr_t target)
        {
            for (Slot& slot : slots_)
                if (slot.owner == owner && slot.target == target)
                    return &slot;
            return nullptr;
        }

        // A slot whose detach failed keeps its storage (the engine still
        // points at it) and is never reused.
        Slot* FreeSlot()
        {
            for (Slot& slot : slots_)
                if (!slot.owner && !slot.storage)
                    return &slot;
            return nullptr;
        }

        void Release(const BlobRenderBackend& backend, Slot& slot, bool clearOwner = true)
        {
            if (slot.storage)
                backend.detach(backend.context, &slot.storage);
            if (clearOwner)
            {
                slot.owner = 0;
                slot.target = 0;
                slot.effect = -1;
                slot.failed = false;
            }
            slot.touched = false;
        }

        std::array<Slot, Capacity> slots_{};
        uint32_t creates_ = 0;
    };

    // --- runtime (src/patches/construction_blob_faction.cpp) ---

    // True for the "Construction Blob Faction ..." and "Portal Blob Render ..."
    // patch rows.
    bool IsPatchName(const char* name);
    // Reads [Display] FactionConstructionBlobs (default off) and binds the
    // engine rows and render helpers of each emitter (construction blob,
    // portal blob) on its own. False for a row keeps it out of the batch:
    // stock bytes stay. Logs each emitter's decision once per change.
    bool ShouldInstall();
    // True when the row's emitter was bound by the last ShouldInstall().
    bool ShouldInstallRow(const char* name);
    // Hook address for a DWORD vtable row, 0 for an unknown name.
    uint32_t DwordTarget(const char* name);
    // Hook address for a REL32 row once `original` (the call's current
    // target) matches the expected engine routine and `callSite` (address of
    // the E8) sits where its caller's frame contract was checked; 0 leaves
    // the stock call.
    uint32_t Rel32Target(const char* name, void* original, uint32_t callSite);
    // Scene teardown seam: detach every pooled render while the world exists.
    void SceneTeardown() noexcept;
}
