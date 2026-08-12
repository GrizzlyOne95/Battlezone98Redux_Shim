#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

// OpenShim historically used process environment variables for many developer
// and feature gates. Force-including this header redirects those reads through
// openshim.ini first while retaining the real process environment as a
// compatibility fallback. Windows.h is included before the macro so Win32's
// own declarations are never rewritten. NOMINMAX is defined here because this
// header is force-included before all translation units; leaking Win32's min/max
// macros would otherwise break normal std::min/std::max use elsewhere.
DWORD WINAPI OpenShimGetEnvironmentVariableA(LPCSTR name, LPSTR buffer, DWORD size);

#define GetEnvironmentVariableA OpenShimGetEnvironmentVariableA
