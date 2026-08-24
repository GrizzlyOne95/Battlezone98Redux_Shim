// numeric_locale_compat.cpp

#include "numeric_locale_compat.h"

#include <cstring>

namespace BZROpenShim
{
    bool EnforceCNumericLocale(SetLocaleFunction setLocale)
    {
        if (!setLocale || !setLocale(LC_NUMERIC, "C"))
            return false;
        const char* selected = setLocale(LC_NUMERIC, nullptr);
        return selected && std::strcmp(selected, "C") == 0;
    }
}
