#pragma once

// How a write into a CPU-mirrored D3D11 buffer reaches the GPU copy.
//
// d3d11_buffer_restore.cpp keeps a CPU copy of every vertex and index buffer
// the D3D11 renderer owns. A lock hands the caller the mirror; the unlock
// sends the written range to the GPU buffer the same way Ogre's own unlock
// would have: UpdateSubresource for a default-usage buffer, a WRITE_DISCARD or
// WRITE_NO_OVERWRITE map for a dynamic one, and a plain WRITE map for a
// staging one. Kept free of Windows headers so the tests can drive it.

#include <cstddef>
#include <cstdint>

namespace BZROpenShim
{
namespace D3D11BufferMirror
{
    // Ogre::HardwareBuffer::LockOptions.
    enum LockOption : uint32_t
    {
        LockNormal = 0,
        LockDiscard = 1,
        LockReadOnly = 2,
        LockNoOverwrite = 3,
        LockWriteOnly = 4,
    };

    // D3D11_USAGE.
    enum Usage : uint32_t
    {
        UsageDefault = 0,
        UsageImmutable = 1,
        UsageDynamic = 2,
        UsageStaging = 3,
    };

    enum class UploadKind
    {
        None,               // nothing to send (a read, an empty range, an immutable buffer)
        UpdateSubresource,  // default usage: copy the range with a box
        MapDiscard,         // dynamic: WRITE_DISCARD, then copy the range
        MapNoOverwrite,     // dynamic: WRITE_NO_OVERWRITE, then copy the range
        MapWrite,           // staging: WRITE, then copy the range
    };

    struct UploadPlan
    {
        UploadKind kind;
        size_t offset;  // bytes from the start of the buffer
        size_t count;   // bytes to copy from the mirror at that offset
    };

    // Whether [offset, offset + length) lies inside a mirror of `size` bytes,
    // without overflowing.
    inline bool RangeFits(size_t offset, size_t length, size_t size)
    {
        return offset <= size && length <= size - offset;
    }

    inline UploadPlan PlanUpload(uint32_t usage, uint32_t lockOption, size_t offset, size_t length, size_t size)
    {
        if (lockOption == LockReadOnly || length == 0 || !RangeFits(offset, length, size))
            return {UploadKind::None, 0, 0};
        switch (usage)
        {
        case UsageDefault:
            return {UploadKind::UpdateSubresource, offset, length};
        case UsageDynamic:
            if (lockOption == LockNoOverwrite)
                return {UploadKind::MapNoOverwrite, offset, length};
            if (lockOption == LockDiscard)
                return {UploadKind::MapDiscard, offset, length};
            // A dynamic buffer can only be mapped with DISCARD or
            // NO_OVERWRITE. A normal or write-only lock promised the rest of
            // the buffer is kept, so the discard map gets all of it back.
            return {UploadKind::MapDiscard, 0, size};
        case UsageStaging:
            return {UploadKind::MapWrite, offset, length};
        default:
            return {UploadKind::None, 0, 0};
        }
    }
}
}
