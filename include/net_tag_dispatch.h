#pragma once

#include <cstdint>

namespace BZROpenShim
{
    // One shared detour on Net::Receive (0x00570500) for every OpenShim
    // network message. Net::Receive's prologue can be inline-detoured only
    // once (a second detour fails its byte guard), so features register a
    // handler for their own two-byte tag instead of detouring it themselves.
    namespace NetTagDispatch
    {
        // Called on the thread that runs Net::Receive. `buf` holds at least
        // the two tag bytes (len >= 2). Return true if the message was
        // consumed; false hands it, untouched, to the original dispatcher.
        using Handler = bool (*)(unsigned senderId, const unsigned char* buf, unsigned len);

        // `tag` is the first two payload bytes read as a little-endian ushort
        // (for example 'M','E' is 0x454D). Installs the Net::Receive detour on
        // the first call. Returns false if the detour cannot be installed
        // (byte guard, unresolved row), the table is full or the tag is taken.
        bool RegisterNetTagHandler(uint16_t tag, Handler handler);
    }
}
