#pragma once

#include "bool_token.h"
#include <cstdint>
#include <initializer_list>

namespace BZROpenShim::ShellCasings
{
    // The INI redirect inverts ShellCasings into these legacy DISABLE aliases.
    // Require an explicit false value to opt in; either true value vetoes it.
    // Absence, blank and malformed values keep the presentation feature off.
    template <typename Reader>
    bool EnabledByEnvironment(const Reader& read)
    {
        bool enabled = false;
        for (const char* name : {"OPENSHIM_DISABLE_SHELL_CASINGS", "BZR_DISABLE_SHELL_CASINGS"})
        {
            char value[32] = {};
            const uint32_t length = read(name, value, static_cast<uint32_t>(sizeof(value)));
            bool disabled = true;
            if (length == 0)
                continue;
            if (length >= sizeof(value) || !BoolToken::TryParse(value, length, disabled) || disabled)
                return false;
            enabled = true;
        }
        return enabled;
    }
}
