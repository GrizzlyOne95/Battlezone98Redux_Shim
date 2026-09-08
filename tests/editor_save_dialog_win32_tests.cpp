// Exercise the production dialog/IAT hook with real Win32 files and a scripted
// native dialog/MessageBox. No game process, renderer or user map is touched.
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace
{
    std::filesystem::path g_fixture;
    std::string g_selection;
    std::wstring g_prompt;
    int g_answer = IDCANCEL;
    int g_prompts = 0;
    int g_failures = 0;
    bool g_dialogResult = true;
    bool g_abiOk = false;

    DWORD WINAPI TestModuleFileName(HMODULE, LPWSTR out, DWORD count)
    {
        const auto name = (g_fixture / L"editor-test.exe").wstring();
        if (name.size() >= count) return count;
        wcscpy_s(out, count, name.c_str());
        return static_cast<DWORD>(name.size());
    }

    int WINAPI TestMessageBox(HWND, LPCWSTR text, LPCWSTR, UINT flags)
    {
        ++g_prompts;
        g_prompt = text;
        if ((flags & MB_TYPEMASK) == MB_OKCANCEL && (flags & MB_DEFMASK) != MB_DEFBUTTON2)
            ++g_failures;
        return g_answer;
    }
}

#define GetModuleFileNameW TestModuleFileName
#define MessageBoxW TestMessageBox
#include "../src/patches/file_io_hooks.cpp"
#undef GetModuleFileNameW
#undef MessageBoxW

// Unrelated services used by the same production translation unit.
namespace BZROpenShim
{
    void Log(const wchar_t*, ...) {}
    std::string GetGameLogPath(const char* path) { return path; }
    void OgreShaderCacheOnProgramScriptOpen() {}
    // The CreateFile hooks report mission files to the .bzn load diagnostics;
    // this test is about the save dialog, so the reporter is stubbed out. Its
    // own analysis is covered by bzn_analysis_tests.
    void BznLoadTraceOnOpen(const wchar_t*, uint32_t) noexcept {}
    void BznLoadTraceOnOpenA(const char*, uint32_t) noexcept {}
}
namespace BZROpenShim::UiPerf
{
    bool IsEnabled() noexcept { return false; }
    void RecordShaderCache(uint32_t, uint32_t, double) noexcept {}
}
namespace HookEngine
{
    void* ResolveRelCallTarget(uint32_t) { return nullptr; }
    uint32_t ResolveNamedAddress(const char*) { return 0; }
}

namespace
{
    void Check(bool condition, const char* message)
    {
        if (!condition) { ++g_failures; std::cerr << "FAIL: " << message << '\n'; }
    }

    bool __fastcall NativeSelection(void* self, void*, char* filename, bool missionSave)
    {
        g_abiOk = self == reinterpret_cast<void*>(0x1234) && missionSave;
        if (g_dialogResult)
            strcpy_s(filename, 4096, g_selection.c_str());
        return g_dialogResult;
    }

    void Put(const std::filesystem::path& path, const char* contents = "original")
    {
        std::filesystem::create_directories(path.parent_path());
        std::ofstream(path, std::ios::binary) << contents;
    }

    std::string Read(const std::filesystem::path& path)
    {
        std::ifstream file(path, std::ios::binary);
        return {std::istreambuf_iterator<char>(file), {}};
    }

    void Observe(const std::filesystem::path& path, bool ansi)
    {
        using namespace BZROpenShim;
        const auto handle = ansi
            ? Hooked_CreateFileA(path.string().c_str(), GENERIC_READ, FILE_SHARE_READ,
                nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr)
            : Hooked_CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ,
                nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        Check(handle != INVALID_HANDLE_VALUE, "source file opened through production hook");
        if (handle != INVALID_HANDLE_VALUE) CloseHandle(handle);
    }

    bool Select(const std::filesystem::path& requested, std::string& chosen)
    {
        using namespace BZROpenShim;
        g_selection = requested.string();
        g_prompt.clear();
        g_prompts = 0;
        char filename[4096] = "unchanged";
        // Invoke as the game's thiscall CALL site does: ECX=self, two stack args.
        const auto hook = reinterpret_cast<EditorSaveDialog>(Hooked_EditorSaveDialog);
        const bool result = hook(reinterpret_cast<void*>(0x1234), filename, true);
        chosen = filename;
        Check(g_abiOk, "this pointer, filename and bool survive thiscall/fastcall adapter");
        return result;
    }
}

int main()
{
    using namespace BZROpenShim;
    wchar_t temp[MAX_PATH] = {};
    GetTempPathW(MAX_PATH, temp);
    // The production hook records a source path via GetFinalPathNameByHandleW,
    // which reports the volume's canonical form: 8.3 components are expanded
    // and symlinks resolved. Build the fixture from the canonical temp
    // directory so the paths this test constructs are the same spelling the
    // hook will hand back. Without this the expectations below fail anywhere
    // TEMP holds a short name -- GitHub's Windows runners use
    // C:\Users\RUNNER~1\AppData\Local\Temp -- while passing on a developer
    // box, which says nothing about the routing under test.
    std::error_code canonicalError;
    const std::filesystem::path tempRoot =
        std::filesystem::canonical(std::filesystem::path(temp), canonicalError);
    if (canonicalError)
        return EXIT_FAILURE;
    g_fixture = tempRoot /
        (L"bzr-editor-save-" + std::to_wstring(GetCurrentProcessId()) + L"-" + std::to_wstring(GetTickCount64()));
    if (std::filesystem::exists(g_fixture))
        return EXIT_FAILURE;
    const auto addon = g_fixture / L"addon";
    const auto source = addon / L"pilot" / L"pilot.bzn";
    const auto trn = addon / L"pilot" / L"pilot.trn";
    SetEnvironmentVariableA("BZR_BZN_SAVE_SOURCE", "1");
    g_RealCreateFileA = ::CreateFileA;
    g_RealCreateFileW = ::CreateFileW;
    g_OriginalEditorSaveDialog = reinterpret_cast<EditorSaveDialog>(NativeSelection);
    Put(source); Put(trn); Put(addon / L"pilot" / L"pilot.hg2"); Put(addon / L"pilot" / L"pilot.mat");
    Observe(source, false); Observe(trn, true);

    std::string chosen;
    Check(!Select(addon / L"pilot.bzn", chosen), "Cancel rejects BZN save");
    Check(g_prompts == 1 && g_prompt.find(source.wstring()) != std::wstring::npos,
        "confirmation names actual BZN target");
    Check(g_prompt.find(trn.wstring()) != std::wstring::npos &&
        g_prompt.find((addon / L"pilot" / L"pilot.hg2").wstring()) != std::wstring::npos &&
        g_prompt.find((addon / L"pilot" / L"pilot.mat").wstring()) != std::wstring::npos,
        "confirmation includes terrain companions");
    Check(Read(source) == "original" && Read(trn) == "original" &&
        !std::filesystem::exists(addon / L"pilot.bzn"), "Cancel leaves files untouched");

    g_answer = IDOK;
    Check(Select(addon / L"pilot.bzn", chosen) && chosen == source.string(),
        "OK returns source BZN path to native serializer");
    Check(Select(addon / L"pilot.trn", chosen) && chosen == trn.string(),
        "OK returns source TRN path to native serializer");
    Check(g_prompt.find(L"pilot.bzn") == std::wstring::npos,
        "TRN-only confirmation does not claim a BZN overwrite");

    g_answer = IDCANCEL;
    Check(!Select(addon / L"pilot.trn", chosen), "Cancel rejects entire TRN save");
    g_dialogResult = false;
    Check(!Select(addon / L"pilot.bzn", chosen) && g_prompts == 0,
        "native filename-dialog Cancel shows no additional prompt");
    g_dialogResult = true;

    g_answer = IDOK;
    Check(Select(addon / L"fresh.bzn", chosen) && chosen == (addon / L"fresh.bzn").string() && g_prompts == 0,
        "new Save As name keeps requested destination with no overwrite prompt");
    Put(addon / L"other" / L"pilot.bzn");
    Check(Select(addon / L"other" / L"pilot.bzn", chosen) && chosen == (addon / L"other" / L"pilot.bzn").string(),
        "explicit other directory stays explicit and still confirms overwrite");

    SetFileAttributesW(trn.c_str(), FILE_ATTRIBUTE_READONLY);
    Check(!Select(addon / L"pilot.bzn", chosen), "read-only companion cancels before any native writes");
    SetFileAttributesW(trn.c_str(), FILE_ATTRIBUTE_NORMAL);
    Check(Read(source) == "original" && Read(trn) == "original", "blocked save preserves source files");

    // Exercise the production hook repeatedly to expose an incorrect RET/ABI.
    for (int i = 0; i < 100; ++i)
        Check(Select(addon / L"pilot.trn", chosen), "repeated thiscall saves preserve stack");

    // The only recursive cleanup target is this run's own temporary fixture.
    if (std::filesystem::canonical(g_fixture).parent_path() != tempRoot ||
        g_fixture.filename().wstring().find(L"bzr-editor-save-") != 0)
        return EXIT_FAILURE;
    std::filesystem::remove_all(g_fixture);
    std::cout << "editor_save_dialog_win32_tests: " << (g_failures ? "FAIL" : "PASS") << '\n';
    return g_failures ? EXIT_FAILURE : EXIT_SUCCESS;
}
