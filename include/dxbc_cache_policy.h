// dxbc_cache_policy.h
// BZR Open Shim - key hashing and entry header for the D3DCompile DXBC cache
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Engine-independent so it can be unit-tested. The entry is a fixed header
// followed by the compiled blob; the header repeats the key and the
// preprocessed length so a renamed, truncated or foreign file is rejected.
#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace DxbcCachePolicy
    {
        // Bump when the key recipe or the entry layout changes.
        constexpr char kFormatVersion[] = "dxbc-v1";
        constexpr uint32_t kMagic = 0x43425844u; // "DXBC"
        constexpr uint32_t kEntryVersion = 2;
        constexpr uint32_t kMaxBlobBytes = 64u * 1024u * 1024u;

        struct EntryHeader
        {
            uint32_t magic;
            uint32_t version;
            uint64_t key;
            uint32_t preprocessedLength;
            uint32_t blobSize;
            uint64_t blobHash; // FNV-1a 64 of the payload
        };
        static_assert(sizeof(EntryHeader) == 32, "EntryHeader layout is part of the file format");

        class Hasher
        {
        public:
            void Bytes(const void* data, size_t size)
            {
                const auto* p = static_cast<const uint8_t*>(data);
                for (size_t i = 0; i < size; ++i)
                {
                    m_hash ^= p[i];
                    m_hash *= 1099511628211ull;
                }
            }
            // Length-prefixed so adjacent fields cannot bleed into each other.
            void Field(const void* data, size_t size)
            {
                const uint64_t n = size;
                Bytes(&n, sizeof(n));
                Bytes(data, size);
            }
            void Text(const char* text)
            {
                if (!text)
                {
                    const uint64_t none = ~0ull;
                    Bytes(&none, sizeof(none));
                    return;
                }
                Field(text, std::strlen(text));
            }
            void U32(uint32_t v) { Bytes(&v, sizeof(v)); }
            uint64_t Value() const { return m_hash ? m_hash : 1ull; }
        private:
            uint64_t m_hash = 1469598103934665603ull;
        };

        // `preprocessed` is the D3DPreprocess output (includes and defines
        // already expanded).
        inline uint64_t ComputeKey(const void* preprocessed, size_t preprocessedSize,
                                   const char* entryPoint, const char* target,
                                   uint32_t flags1, uint32_t flags2)
        {
            Hasher h;
            h.Text(kFormatVersion);
            h.Field(preprocessed, preprocessedSize);
            h.Text(entryPoint);
            h.Text(target);
            h.U32(flags1);
            h.U32(flags2);
            return h.Value();
        }

        inline void HexName(uint64_t key, char (&out)[17])
        {
            static const char digits[] = "0123456789abcdef";
            for (int i = 0; i < 16; ++i)
                out[i] = digits[(key >> ((15 - i) * 4)) & 0xF];
            out[16] = '\0';
        }

        inline uint64_t HashBlob(const void* data, size_t size)
        {
            Hasher h;
            h.Bytes(data, size);
            return h.Value();
        }

        // A compiled shader starts with the "DXBC" fourcc and stores its own
        // total size as a uint32 at offset 24.
        inline bool LooksLikeDxbc(const void* blob, size_t size)
        {
            if (!blob || size < 32)
                return false;
            uint32_t total = 0;
            std::memcpy(&total, static_cast<const uint8_t*>(blob) + 24, sizeof(total));
            return std::memcmp(blob, "DXBC", 4) == 0 && total == size;
        }

        inline EntryHeader MakeHeader(uint64_t key, size_t preprocessedLength,
                                      const void* blob, size_t blobSize)
        {
            EntryHeader h{};
            h.magic = kMagic;
            h.version = kEntryVersion;
            h.key = key;
            h.preprocessedLength = static_cast<uint32_t>(preprocessedLength);
            h.blobSize = static_cast<uint32_t>(blobSize);
            h.blobHash = HashBlob(blob, blobSize);
            return h;
        }

        // Validates a whole file image; on success `*blobOffset`/`*blobSize`
        // locate the DXBC payload.
        inline bool ValidateEntry(const void* file, size_t fileSize, uint64_t key,
                                  size_t preprocessedLength,
                                  size_t* blobOffset, size_t* blobSize)
        {
            if (!file || fileSize < sizeof(EntryHeader))
                return false;
            EntryHeader h;
            std::memcpy(&h, file, sizeof(h));
            if (h.magic != kMagic || h.version != kEntryVersion || h.key != key ||
                h.preprocessedLength != static_cast<uint32_t>(preprocessedLength))
                return false;
            if (h.blobSize == 0 || h.blobSize > kMaxBlobBytes ||
                fileSize - sizeof(EntryHeader) != h.blobSize)
                return false;
            const uint8_t* payload = static_cast<const uint8_t*>(file) + sizeof(EntryHeader);
            if (!LooksLikeDxbc(payload, h.blobSize) || HashBlob(payload, h.blobSize) != h.blobHash)
                return false;
            if (blobOffset) *blobOffset = sizeof(EntryHeader);
            if (blobSize) *blobSize = h.blobSize;
            return true;
        }
    }
}
