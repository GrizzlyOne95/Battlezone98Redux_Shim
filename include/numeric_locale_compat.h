// numeric_locale_compat.h

#pragma once

#include <clocale>

namespace BZROpenShim
{
#if defined(_MSC_VER)
    using SetLocaleFunction = char* (__cdecl*)(int, const char*);
#else
    using SetLocaleFunction = char* (*)(int, const char*);
#endif

    // Use the owning CRT's setlocale function. Redux and OpenShim use
    // different CRTs, so the runtime hook must pass MSVCR120's function here.
    bool EnforceCNumericLocale(SetLocaleFunction setLocale);
}
