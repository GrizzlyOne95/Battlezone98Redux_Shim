#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <cstdio>

namespace
{
void WriteMarker(const char* message)
{
    if (!message)
    {
        return;
    }

    FILE* file = nullptr;
    if (fopen_s(&file, "OpenShimOgreProbe.log", "a") == 0 && file)
    {
        std::fprintf(file, "%s\r\n", message);
        std::fclose(file);
    }

    ::OutputDebugStringA(message);
    ::OutputDebugStringA("\n");
}
}

extern "C" void __cdecl dllStartPlugin()
{
    WriteMarker("[OpenShimOgreProbe] dllStartPlugin called");
}

extern "C" void __cdecl dllStopPlugin()
{
    WriteMarker("[OpenShimOgreProbe] dllStopPlugin called");
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
    (void)reserved;

    if (reason == DLL_PROCESS_ATTACH)
    {
        ::DisableThreadLibraryCalls(module);
    }

    return TRUE;
}
