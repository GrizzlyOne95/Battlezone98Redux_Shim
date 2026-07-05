// Minimal 32-bit load test for the deployed winmm.dll shim.
// Loads the DLL (runs DllMain), exercises a forwarded export (timeGetTime),
// and queries the OpenShim API export, to confirm the proxy loads + forwards.
#include <windows.h>
#include <cstdio>

int main(int argc, char** argv)
{
    if (argc < 2) { printf("usage: load_test <path-to-winmm.dll>\n"); return 2; }
    const char* dllPath = argv[1];

    HMODULE h = LoadLibraryA(dllPath);
    if (!h) { printf("FAIL: LoadLibrary('%s') err=%lu\n", dllPath, GetLastError()); return 1; }
    printf("PASS: LoadLibrary ok, base=0x%p\n", (void*)h);

    typedef DWORD (WINAPI *timeGetTime_t)(void);
    timeGetTime_t pTime = (timeGetTime_t)GetProcAddress(h, "timeGetTime");
    if (!pTime) { printf("FAIL: GetProcAddress(timeGetTime) err=%lu\n", GetLastError()); FreeLibrary(h); return 1; }
    DWORD t = pTime();
    printf("PASS: forwarded timeGetTime() = %lu\n", t);

    // OpenShim API export (decorated C++ name from dumpbin).
    typedef unsigned int (__cdecl *GetShimVersion_t)(void);
    GetShimVersion_t pVer = (GetShimVersion_t)GetProcAddress(h, "?GetShimVersion@BZROpenShim@@YAIXZ");
    if (pVer) printf("PASS: GetShimVersion() = %u\n", pVer());
    else      printf("INFO: GetShimVersion export not found (err=%lu)\n", GetLastError());

    FreeLibrary(h);
    printf("PASS: FreeLibrary ok\n");
    return 0;
}
