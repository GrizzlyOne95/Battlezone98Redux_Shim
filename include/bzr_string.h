#pragma once

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <cstdlib>

namespace BZROpenShim
{
    // BZR std::string (SSO) layout as observed in the reference patch.
    struct BzrString
    {
        union
        {
            char  small[16];
            char* heap;
        };
        uint32_t size;
        uint32_t capacity;
    };

    inline bool BzrStringIsHeap(const BzrString* s)
    {
        return s && s->capacity > 0xF;
    }

    inline const char* BzrStringData(const BzrString* s)
    {
        if (!s) return "";
        return BzrStringIsHeap(s) ? (s->heap ? s->heap : "") : s->small;
    }

    inline void BzrStringInitEmpty(BzrString* s)
    {
        if (!s) return;
        std::memset(s, 0, sizeof(*s));
        s->capacity = 0xF;
        s->small[0] = '\0';
    }

    inline void BzrStringFree(BzrString* s)
    {
        if (!s) return;
        if (BzrStringIsHeap(s) && s->heap)
        {
            std::free(s->heap);
        }
        BzrStringInitEmpty(s);
    }

    inline void BzrStringAssign(BzrString* s, const char* data, size_t len)
    {
        if (!s) return;
        BzrStringFree(s);
        if (!data)
        {
            BzrStringInitEmpty(s);
            return;
        }

        if (len <= 0xF)
        {
            std::memcpy(s->small, data, len);
            s->small[len] = '\0';
            s->size = static_cast<uint32_t>(len);
            s->capacity = 0xF;
            return;
        }

        size_t cap = len | 0xF;
        if (cap < 0x10) cap = 0x10;
        char* buf = static_cast<char*>(std::malloc(cap + 1));
        if (!buf)
        {
            BzrStringInitEmpty(s);
            return;
        }
        std::memcpy(buf, data, len);
        buf[len] = '\0';
        s->heap = buf;
        s->size = static_cast<uint32_t>(len);
        s->capacity = static_cast<uint32_t>(cap);
    }

    inline void BzrStringCopy(BzrString* dst, const BzrString* src)
    {
        if (!dst)
            return;
        if (!src)
        {
            BzrStringInitEmpty(dst);
            return;
        }
        BzrStringAssign(dst, BzrStringData(src), src->size);
    }

    inline void BzrStringAppend(BzrString* s, const char* data, size_t len)
    {
        if (!s || !data || len == 0)
            return;

        const size_t cur_len = s->size;
        const size_t new_len = cur_len + len;

        if (new_len <= 0xF)
        {
            const char* cur = BzrStringData(s);
            if (cur != s->small && cur_len)
                std::memcpy(s->small, cur, cur_len);
            std::memcpy(s->small + cur_len, data, len);
            s->small[new_len] = '\0';
            s->size = static_cast<uint32_t>(new_len);
            s->capacity = 0xF;
            return;
        }

        size_t cap = s->capacity;
        if (cap <= 0xF || cap < new_len)
        {
            cap = new_len | 0xF;
            if (cap < 0x10) cap = 0x10;
        }

        char* buf = static_cast<char*>(std::malloc(cap + 1));
        if (!buf)
            return;

        const char* cur = BzrStringData(s);
        if (cur_len)
            std::memcpy(buf, cur, cur_len);
        std::memcpy(buf + cur_len, data, len);
        buf[new_len] = '\0';

        if (BzrStringIsHeap(s) && s->heap)
            std::free(s->heap);

        s->heap = buf;
        s->size = static_cast<uint32_t>(new_len);
        s->capacity = static_cast<uint32_t>(cap);
    }

    inline bool BzrStringEquals(const BzrString* a, const BzrString* b)
    {
        if (!a || !b) return false;
        if (a->size != b->size) return false;
        if (a->size == 0) return true;
        return std::memcmp(BzrStringData(a), BzrStringData(b), a->size) == 0;
    }
}
