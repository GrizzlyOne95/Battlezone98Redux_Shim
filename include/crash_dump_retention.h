#pragma once
// Heap-free retention rule for the crash logger's minidumps
// (logs\openshim_crash_YYYYMMDD_HHMMSS.dmp). Runs inside a crash handler,
// so it uses fixed buffers only. The names carry the timestamp in a fixed
// layout, so the largest names are the newest files.

#include <cstddef>
#include <cstring>

namespace BZROpenShim
{
    namespace CrashDumpRetention
    {
        constexpr size_t kKeptDumps = 3;
        constexpr size_t kMaxName = 64;

        inline char LowerAscii(char c)
        {
            return (c >= 'A' && c <= 'Z') ? static_cast<char>(c - 'A' + 'a') : c;
        }

        // Exactly "openshim_crash_YYYYMMDD_HHMMSS.dmp" (the crash logger's
        // own layout), case-insensitive. Anything else in the folder, even a
        // renamed "openshim_crash_test.dmp", is never counted or deleted. A
        // FindFirstFile pattern can also match short (8.3) names, so every
        // candidate is checked again here before deletion.
        inline bool IsCrashDumpName(const char* name)
        {
            static const char kPrefix[] = "openshim_crash_";
            static const char kStamp[] = "dddddddd_dddddd"; // d = digit
            static const char kSuffix[] = ".dmp";
            if (!name)
                return false;
            const size_t prefixLength = sizeof(kPrefix) - 1;
            const size_t stampLength = sizeof(kStamp) - 1;
            const size_t suffixLength = sizeof(kSuffix) - 1;
            if (std::strlen(name) != prefixLength + stampLength + suffixLength)
                return false;
            for (size_t i = 0; i < prefixLength; ++i)
                if (LowerAscii(name[i]) != kPrefix[i])
                    return false;
            const char* stamp = name + prefixLength;
            for (size_t i = 0; i < stampLength; ++i)
            {
                const bool digit = stamp[i] >= '0' && stamp[i] <= '9';
                if (kStamp[i] == 'd' ? !digit : stamp[i] != kStamp[i])
                    return false;
            }
            const char* suffix = stamp + stampLength;
            for (size_t i = 0; i < suffixLength; ++i)
                if (LowerAscii(suffix[i]) != kSuffix[i])
                    return false;
            return true;
        }

        inline int CompareNames(const char* a, const char* b)
        {
            for (;; ++a, ++b)
            {
                const char ca = LowerAscii(*a);
                const char cb = LowerAscii(*b);
                if (ca != cb)
                    return ca < cb ? -1 : 1;
                if (!ca)
                    return 0;
            }
        }

        // Pass 1: Offer() every name in the folder. Pass 2: ShouldDelete()
        // each name again; true for a dump name that is not one of the
        // newest kKeptDumps. Protect() names a file that is never deleted
        // (the dump just written, even if the clock went back).
        struct NewestKeeper
        {
            char keep[kKeptDumps][kMaxName] = {};
            size_t count = 0;
            char protectedName[kMaxName] = {};

            void Protect(const char* name)
            {
                protectedName[0] = '\0';
                if (!IsCrashDumpName(name))
                    return;
                std::memcpy(protectedName, name, std::strlen(name) + 1);
            }

            void Offer(const char* name)
            {
                if (!IsCrashDumpName(name))
                    return;
                for (size_t i = 0; i < count; ++i)
                    if (CompareNames(keep[i], name) == 0)
                        return;
                size_t slot = count;
                if (count == kKeptDumps)
                {
                    // Replace the oldest kept name when this one is newer.
                    slot = 0;
                    for (size_t i = 1; i < count; ++i)
                        if (CompareNames(keep[i], keep[slot]) < 0)
                            slot = i;
                    if (CompareNames(name, keep[slot]) <= 0)
                        return;
                }
                else
                {
                    ++count;
                }
                const size_t length = std::strlen(name);
                std::memcpy(keep[slot], name, length + 1);
            }

            bool ShouldDelete(const char* name) const
            {
                if (!IsCrashDumpName(name))
                    return false;
                if (protectedName[0] && CompareNames(protectedName, name) == 0)
                    return false;
                for (size_t i = 0; i < count; ++i)
                    if (CompareNames(keep[i], name) == 0)
                        return false;
                return true;
            }
        };
    }
}
