#include "scene_depth_facts.h"

namespace BZROpenShim::SceneDepth
{
    bool IsDepthCandidate(uint32_t bindFlags)
    {
        return (bindFlags & Native::kBindDepthStencil) != 0u;
    }

    bool IsShaderReadable(uint32_t bindFlags)
    {
        return (bindFlags & Native::kBindShaderResource) != 0u;
    }

    bool IsMultisampled(const TextureFacts& facts)
    {
        return facts.sampleCount > 1u;
    }

    bool SameResourceShape(const TextureFacts& a, const TextureFacts& b)
    {
        // Everything that is fixed for the life of a texture. Deliberately not
        // the address, which is the thing being disambiguated, and deliberately
        // every dimension rather than just width/height: a shadow atlas and a
        // main depth surface can share a resolution, and an array slice count
        // is the cheapest thing that tells them apart.
        return a.width == b.width
            && a.height == b.height
            && a.format == b.format
            && a.sampleCount == b.sampleCount
            && a.sampleQuality == b.sampleQuality
            && a.bindFlags == b.bindFlags
            && a.miscFlags == b.miscFlags
            && a.arraySize == b.arraySize
            && a.mipLevels == b.mipLevels
            && a.usage == b.usage;
    }

    const char* FormatName(uint32_t format)
    {
        switch (format)
        {
        case Native::kFormatUnknown:        return "UNKNOWN";
        case Native::kFormatR32Typeless:    return "R32_TYPELESS";
        case Native::kFormatD32Float:       return "D32_FLOAT";
        case Native::kFormatR32Float:       return "R32_FLOAT";
        case Native::kFormatR24G8Typeless:  return "R24G8_TYPELESS";
        case Native::kFormatD24UnormS8Uint: return "D24_UNORM_S8_UINT";
        case Native::kFormatR16Typeless:    return "R16_TYPELESS";
        case Native::kFormatD16Unorm:       return "D16_UNORM";
        default:                            return nullptr;
        }
    }

    const char* DsvDimensionName(uint32_t dimension)
    {
        switch (dimension)
        {
        case Native::kDsvDimensionTexture2D:   return "TEXTURE2D";
        case Native::kDsvDimensionTexture2DMs: return "TEXTURE2DMS";
        default:                               return nullptr;
        }
    }

    Observation* Registry::FindMutable(uint64_t resource)
    {
        if (resource == 0)
            return nullptr;

        for (size_t i = 0; i < m_count; ++i)
        {
            if (m_entries[i].facts.resource == resource)
                return &m_entries[i];
        }
        return nullptr;
    }

    const Observation* Registry::Find(uint64_t resource) const
    {
        return const_cast<Registry*>(this)->FindMutable(resource);
    }

    const Observation* Registry::At(size_t index) const
    {
        return index < m_count ? &m_entries[index] : nullptr;
    }

    Registry::Event Registry::Observe(const TextureFacts& facts, uint32_t* outSerial)
    {
        if (!IsDepthCandidate(facts.bindFlags) || facts.resource == 0)
            return Event::Ignored;

        if (Observation* existing = FindMutable(facts.resource))
        {
            if (SameResourceShape(existing->facts, facts))
            {
                // The same surface described twice. Nothing has changed, and in
                // particular the serial must not move: downstream captures key
                // off it to follow one surface across a whole session.
                if (outSerial)
                    *outSerial = existing->serial;
                return Event::Known;
            }

            // The address is being reused for a different surface, which is
            // what a mission change or a resize looks like from here. Start a
            // fresh serial and reset everything observed about the old one;
            // carrying a bind count across a recreate would make a surface that
            // is used once look like one that is used every frame.
            existing->facts = facts;
            existing->serial = m_nextSerial++;
            existing->generation += 1;
            existing->dsvCount = 0;
            existing->dsvFormat = Native::kFormatUnknown;
            existing->dsvDimension = 0;
            existing->bindCount = 0;
            existing->lastRtWidth = 0;
            existing->lastRtHeight = 0;
            existing->lastRtCount = 0;
            existing->everBoundWithRenderTarget = false;
            existing->inUse = true;
            if (outSerial)
                *outSerial = existing->serial;
            return Event::Recreated;
        }

        if (m_count >= kCapacity)
        {
            m_overflowed = true;
            return Event::Overflow;
        }

        Observation& entry = m_entries[m_count++];
        entry = Observation{};
        entry.facts = facts;
        entry.serial = m_nextSerial++;
        entry.generation = 0;
        entry.inUse = true;
        if (outSerial)
            *outSerial = entry.serial;
        return Event::Added;
    }

    bool Registry::NoteDepthStencilView(uint64_t resource, uint32_t dsvFormat, uint32_t dsvDimension)
    {
        Observation* entry = FindMutable(resource);
        if (!entry)
            return false;

        entry->dsvCount += 1;
        entry->dsvFormat = dsvFormat;
        entry->dsvDimension = dsvDimension;
        return true;
    }

    bool Registry::NoteBind(uint64_t resource, uint32_t rtWidth, uint32_t rtHeight, uint32_t rtCount)
    {
        Observation* entry = FindMutable(resource);
        if (!entry)
            return false;

        entry->bindCount += 1;
        entry->lastRtCount = rtCount;
        if (rtCount > 0 && rtWidth > 0 && rtHeight > 0)
        {
            entry->lastRtWidth = rtWidth;
            entry->lastRtHeight = rtHeight;
            entry->everBoundWithRenderTarget = true;
        }
        return true;
    }

    void Registry::Clear()
    {
        for (size_t i = 0; i < kCapacity; ++i)
            m_entries[i] = Observation{};
        m_count = 0;
        m_nextSerial = 1;
        m_overflowed = false;
    }
}
