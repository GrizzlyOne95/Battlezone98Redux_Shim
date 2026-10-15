#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cstring>

BOOL WINAPI DllMain(HINSTANCE, DWORD reason, LPVOID)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        // Deliberately hold the real loader lock while an already-running
        // worker hashes a file. The callback has a bounded wait, so the old
        // provider/load-library behavior fails the test without wedging it.
        FARPROC address = GetProcAddress(GetModuleHandleW(nullptr), "StartupHashLoaderLockProbe");
        if (!address)
            address = GetProcAddress(GetModuleHandleW(nullptr), "_StartupHashLoaderLockProbe");
        if (!address) return FALSE;
        void (__cdecl* probe)() = nullptr;
        static_assert(sizeof(probe) == sizeof(address), "function pointer size");
        std::memcpy(&probe, &address, sizeof(probe));
        probe();
    }
    return TRUE;
}
