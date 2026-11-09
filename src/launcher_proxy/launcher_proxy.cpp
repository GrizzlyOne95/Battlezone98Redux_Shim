// Launcher\d3d9.dll: skips Rebellion's BZLauncher.exe on Steam.
//
// BZLauncher.exe imports d3d9.dll, so Windows loads this file from the
// launcher's own folder before the system copy. DllMain patches the
// launcher's entry point (loader lock is held, so it does nothing else). When
// the entry point runs, the hook puts the original bytes back and decides:
//
//   skip  -> start ..\battlezone98redux.exe with the launcher's arguments,
//            wait for it, and exit with its code (Steam keeps tracking the
//            launcher process, as it does for the stock launcher).
//   show  -> jump to the original entry point; the launcher runs as stock and
//            Direct3DCreate9 is forwarded to the system d3d9.dll.
//
// It shows the launcher when Shift is held, [Steam] SkipRebellionLauncher in
// openshim.ini is not on, Ogre.cfg does not exist yet (first run), the game
// exe is missing, or it runs under Wine/Proton. plugins\openshim.dll deploys
// and removes this file (src/patches/steam_launcher_skip.cpp).

#include <windows.h>

#include <string>

#include "launcher_proxy_logic.h"

namespace
{
    BYTE* g_entry = nullptr;
    BYTE g_savedEntry[5] = {};

    std::wstring ModuleDirectory(HMODULE module)
    {
        wchar_t path[MAX_PATH] = {};
        const DWORD length = GetModuleFileNameW(module, path, MAX_PATH);
        if (length == 0 || length >= MAX_PATH)
            return {};
        std::wstring dir(path, length);
        const size_t slash = dir.find_last_of(L"\\/");
        return slash == std::wstring::npos ? std::wstring() : dir.substr(0, slash);
    }

    bool FileExists(const std::wstring& path)
    {
        const DWORD attributes = GetFileAttributesW(path.c_str());
        return attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
    }

    bool RunningUnderWine()
    {
        const HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
        return ntdll && GetProcAddress(ntdll, "wine_get_version") != nullptr;
    }

    bool ToggleOn(const std::wstring& gameRoot)
    {
        wchar_t value[32] = {};
        GetPrivateProfileStringW(L"Steam", L"SkipRebellionLauncher", L"", value, 32,
                                 (gameRoot + L"\\openshim.ini").c_str());
        return BZROpenShim::LauncherProxy::ParseToggle(value);
    }

    // Starts the game and waits for it. False (nothing started) shows the
    // launcher instead.
    bool RunGame(const std::wstring& gameRoot, DWORD& exitCode)
    {
        const std::wstring exe = gameRoot + L"\\battlezone98redux.exe";
        if (!FileExists(exe))
            return false;

        std::wstring commandLine = L"\"" + exe + L"\"";
        const wchar_t* args = BZROpenShim::LauncherProxy::CommandLineTail(GetCommandLineW());
        if (*args != L'\0')
            commandLine += L" " + std::wstring(args);

        STARTUPINFOW startup = {};
        startup.cb = sizeof(startup);
        PROCESS_INFORMATION process = {};
        if (!CreateProcessW(exe.c_str(), commandLine.data(), nullptr, nullptr, FALSE, 0, nullptr,
                            gameRoot.c_str(), &startup, &process))
            return false;

        CloseHandle(process.hThread);
        WaitForSingleObject(process.hProcess, INFINITE);
        exitCode = 0;
        GetExitCodeProcess(process.hProcess, &exitCode);
        CloseHandle(process.hProcess);
        return true;
    }

    void RestoreEntry()
    {
        DWORD oldProtect = 0;
        if (VirtualProtect(g_entry, sizeof(g_savedEntry), PAGE_EXECUTE_READWRITE, &oldProtect))
        {
            memcpy(g_entry, g_savedEntry, sizeof(g_savedEntry));
            VirtualProtect(g_entry, sizeof(g_savedEntry), oldProtect, &oldProtect);
        }
        FlushInstructionCache(GetCurrentProcess(), g_entry, sizeof(g_savedEntry));
    }

    // Runs at the launcher's entry point, outside the loader lock. Returns
    // only when the launcher should run as stock.
    void DecideAtEntry()
    {
        RestoreEntry();

        const bool shiftHeld = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
        const std::wstring launcherDir = ModuleDirectory(nullptr);
        const size_t slash = launcherDir.find_last_of(L"\\/");
        if (shiftHeld || slash == std::wstring::npos)
            return;
        const std::wstring gameRoot = launcherDir.substr(0, slash);

        if (!BZROpenShim::LauncherProxy::ShouldSkipLauncher(
                shiftHeld, ToggleOn(gameRoot), FileExists(gameRoot + L"\\Ogre.cfg"), RunningUnderWine()))
            return;

        DWORD exitCode = 0;
        if (RunGame(gameRoot, exitCode))
            ExitProcess(exitCode);
    }

    // Keeps the stack exactly as the loader left it, so the original entry
    // point runs as if never hooked.
    __declspec(naked) void EntryThunk()
    {
        __asm {
            call DecideAtEntry
            jmp dword ptr [g_entry]
        }
    }

    void HookEntryPoint()
    {
        const auto base = reinterpret_cast<BYTE*>(GetModuleHandleW(nullptr));
        if (!base)
            return;
        const auto dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(base);
        const auto nt = reinterpret_cast<const IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
        if (dos->e_magic != IMAGE_DOS_SIGNATURE || nt->Signature != IMAGE_NT_SIGNATURE ||
            nt->OptionalHeader.AddressOfEntryPoint == 0)
            return;

        // Only Rebellion's launcher; any other exe that loads this file runs untouched.
        wchar_t exePath[MAX_PATH] = {};
        const DWORD exeLength = GetModuleFileNameW(nullptr, exePath, MAX_PATH);
        if (exeLength == 0 || exeLength >= MAX_PATH)
            return;
        const wchar_t* exeName = exePath;
        for (const wchar_t* p = exePath; *p != L'\0'; ++p)
        {
            if (*p == L'\\' || *p == L'/')
                exeName = p + 1;
        }
        if (_wcsicmp(exeName, L"BZLauncher.exe") != 0)
            return;

        BYTE* entry = base + nt->OptionalHeader.AddressOfEntryPoint;
        DWORD oldProtect = 0;
        if (!VirtualProtect(entry, sizeof(g_savedEntry), PAGE_EXECUTE_READWRITE, &oldProtect))
            return;
        memcpy(g_savedEntry, entry, sizeof(g_savedEntry));
        g_entry = entry;
        const auto rel = static_cast<INT32>(reinterpret_cast<BYTE*>(&EntryThunk) - (entry + 5));
        entry[0] = 0xE9;
        memcpy(entry + 1, &rel, sizeof(rel));
        VirtualProtect(entry, sizeof(g_savedEntry), oldProtect, &oldProtect);
        FlushInstructionCache(GetCurrentProcess(), entry, sizeof(g_savedEntry));
    }

    using Direct3DCreate9Fn = void*(WINAPI*)(UINT);

    Direct3DCreate9Fn SystemDirect3DCreate9()
    {
        static Direct3DCreate9Fn fn = []() -> Direct3DCreate9Fn {
            wchar_t path[MAX_PATH] = {};
            const UINT length = GetSystemDirectoryW(path, MAX_PATH);
            if (length == 0 || length >= MAX_PATH)
                return nullptr;
            const HMODULE system = LoadLibraryW((std::wstring(path, length) + L"\\d3d9.dll").c_str());
            return system ? reinterpret_cast<Direct3DCreate9Fn>(GetProcAddress(system, "Direct3DCreate9")) : nullptr;
        }();
        return fn;
    }
}

// Exported as Direct3DCreate9 (launcher_proxy.def).
extern "C" void* WINAPI OpenShimDirect3DCreate9(UINT sdkVersion)
{
    const Direct3DCreate9Fn fn = SystemDirect3DCreate9();
    return fn ? fn(sdkVersion) : nullptr;
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(module);
        HookEntryPoint();
    }
    return TRUE;
}
