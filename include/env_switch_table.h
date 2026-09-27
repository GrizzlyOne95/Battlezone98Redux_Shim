#pragma once

// A table of boolean switches read from pairs of environment variables.
//
// Most OpenShim switches come in two spellings, an OPENSHIM_* name and an
// older BZR_* alias, and are either a kill switch (on unless either name is
// set) or an opt-in (off unless either name is set). ResolveBzrHooks used to
// spell each one out as a two-line expression; a table keeps the names in one
// column where they can be read and tested.
//
// Header-only and free of Windows calls: the caller supplies the lookup, so
// the tests can drive it with a fake environment.

#include <cstddef>

namespace BZROpenShim::EnvSwitches
{
    enum class Kind
    {
        KillSwitch, // true unless either name is set
        OptIn,      // false unless either name is set
    };

    struct EnvSwitch
    {
        bool* flag;
        Kind kind;
        const char* primaryName;
        const char* aliasName;
    };

    // Evaluates each row in order. The second name is not looked up when the
    // first is set, which is what the replaced `a || b` expressions did.
    template <typename Lookup, size_t N>
    void Apply(const EnvSwitch (&rows)[N], Lookup&& isSet)
    {
        for (const EnvSwitch& row : rows)
        {
            const bool named = isSet(row.primaryName) || isSet(row.aliasName);
            *row.flag = (row.kind == Kind::KillSwitch) ? !named : named;
        }
    }
}
