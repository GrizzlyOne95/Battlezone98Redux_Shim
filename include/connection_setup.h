#pragma once
#include <cstdint>

namespace BZROpenShim::ConnectionSetup
{
    // The split is a UI preview until a complete native gameplay adapter is
    // qualified. It cannot turn network/auth readiness on or select a server.
    bool RegisterScreens();
    bool PreviewEnabled();
    uint32_t EntryScreen();
}
