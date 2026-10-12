// OpenShimSetup.exe -- double-clickable wrapper around the tested PowerShell
// installer. It carries scripts\install_windows.ps1 and scripts\uninstall_windows.ps1
// (and, in a release build, OpenShim-Suite.zip plus its SHA-256) as resources,
// unpacks them to a private temp directory and runs the script with the
// console inherited. All install logic stays in the scripts.
//
//   OpenShimSetup.exe              install (offline when a suite is embedded)
//   OpenShimSetup.exe --uninstall  run uninstall_windows.ps1 instead
//   --no-pause                     do not wait for Enter at the end
//
// Any other argument is handed to the script unchanged, and the environment
// the scripts understand (OPENSHIM_GAME_PATH, OPENSHIM_RESET_INI, ...) is
// inherited unchanged.

#include <windows.h>
#include <bcrypt.h>
#include <shellapi.h>

#include <cstdio>
#include <string>
#include <vector>

namespace {

constexpr WORD kResInstall = 1;
constexpr WORD kResUninstall = 2;
constexpr WORD kResSuiteZip = 3;
constexpr WORD kResSuiteSha = 4;

struct Blob {
    const unsigned char* data = nullptr;
    DWORD size = 0;
};

Blob FindBlob(WORD id) {
    Blob b;
    HRSRC r = FindResourceW(nullptr, MAKEINTRESOURCEW(id), RT_RCDATA);
    if (!r) return b;
    HGLOBAL h = LoadResource(nullptr, r);
    if (!h) return b;
    b.data = static_cast<const unsigned char*>(LockResource(h));
    b.size = SizeofResource(nullptr, r);
    if (!b.data) b.size = 0;
    return b;
}

bool Sha256Hex(const Blob& b, std::string& out) {
    BCRYPT_ALG_HANDLE alg = nullptr;
    if (BCryptOpenAlgorithmProvider(&alg, BCRYPT_SHA256_ALGORITHM, nullptr, 0) < 0) return false;
    BCRYPT_HASH_HANDLE hash = nullptr;
    bool ok = false;
    unsigned char digest[32];
    if (BCryptCreateHash(alg, &hash, nullptr, 0, nullptr, 0, 0) >= 0) {
        // BCryptHashData takes a ULONG; feed in chunks so the size is never truncated.
        ok = true;
        for (DWORD off = 0; ok && off < b.size;) {
            DWORD n = (b.size - off > (1u << 24)) ? (1u << 24) : (b.size - off);
            ok = BCryptHashData(hash, const_cast<PUCHAR>(b.data + off), n, 0) >= 0;
            off += n;
        }
        ok = ok && BCryptFinishHash(hash, digest, sizeof digest, 0) >= 0;
        BCryptDestroyHash(hash);
    }
    BCryptCloseAlgorithmProvider(alg, 0);
    if (!ok) return false;
    static const char* hex = "0123456789abcdef";
    out.clear();
    for (unsigned char c : digest) {
        out.push_back(hex[c >> 4]);
        out.push_back(hex[c & 15]);
    }
    return true;
}

bool WriteBlob(const std::wstring& path, const Blob& b) {
    HANDLE f = CreateFileW(path.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (f == INVALID_HANDLE_VALUE) return false;
    bool ok = true;
    for (DWORD off = 0; ok && off < b.size;) {
        DWORD wrote = 0;
        ok = WriteFile(f, b.data + off, b.size - off, &wrote, nullptr) && wrote != 0;
        off += wrote;
    }
    ok = CloseHandle(f) && ok;
    return ok;
}

// A fresh, unpredictable directory under %TEMP%. CreateDirectory fails if the
// name already exists, so an attacker-planted directory is never reused.
bool MakeWorkDir(std::wstring& dir) {
    wchar_t tmp[MAX_PATH + 1];
    DWORD n = GetTempPathW(MAX_PATH, tmp);
    if (n == 0 || n > MAX_PATH) return false;
    unsigned char rnd[8];
    if (BCryptGenRandom(nullptr, rnd, sizeof rnd, BCRYPT_USE_SYSTEM_PREFERRED_RNG) < 0) return false;
    std::wstring name = L"OpenShimSetup-";
    static const wchar_t* hex = L"0123456789abcdef";
    for (unsigned char c : rnd) {
        name.push_back(hex[c >> 4]);
        name.push_back(hex[c & 15]);
    }
    dir = std::wstring(tmp) + name;
    return CreateDirectoryW(dir.c_str(), nullptr) != FALSE;
}

std::wstring PowerShellPath() {
    wchar_t win[MAX_PATH + 1];
    UINT n = GetWindowsDirectoryW(win, MAX_PATH);
    // Only the system copy: a bare "powershell.exe" would be searched for in
    // this exe's own folder first (often Downloads), where anything can sit.
    if (n == 0 || n > MAX_PATH) return std::wstring();
    const std::wstring tail = L"\\System32\\WindowsPowerShell\\v1.0\\powershell.exe";
    // This is a 32-bit process. Under WOW64 prefer the 64-bit PowerShell
    // (Sysnative) so the script sees the native registry and Program Files.
    std::wstring native = std::wstring(win) + L"\\Sysnative\\WindowsPowerShell\\v1.0\\powershell.exe";
    if (GetFileAttributesW(native.c_str()) != INVALID_FILE_ATTRIBUTES) return native;
    std::wstring plain = std::wstring(win) + tail;
    if (GetFileAttributesW(plain.c_str()) != INVALID_FILE_ATTRIBUTES) return plain;
    return std::wstring();
}

// Standard Windows argv quoting (the inverse of CommandLineToArgvW).
std::wstring Quote(const std::wstring& a) {
    if (!a.empty() && a.find_first_of(L" \t\n\v\"") == std::wstring::npos) return a;
    std::wstring r = L"\"";
    for (size_t i = 0;; ++i) {
        size_t bs = 0;
        while (i < a.size() && a[i] == L'\\') { ++bs; ++i; }
        if (i == a.size()) { r.append(bs * 2, L'\\'); break; }
        if (a[i] == L'"') { r.append(bs * 2 + 1, L'\\'); r.push_back(L'"'); }
        else { r.append(bs, L'\\'); r.push_back(a[i]); }
    }
    r.push_back(L'"');
    return r;
}

void Pause() {
    DWORD mode;
    if (!GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode)) return;  // not interactive
    std::printf("\nPress Enter to close...");
    std::fflush(stdout);
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    int c;
    while ((c = std::getchar()) != '\n' && c != EOF) {}
}

}  // namespace

int wmain() {
    // Our lines and PowerShell's share one console; keep them in order when piped.
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    int argc = 0;
    wchar_t** argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    bool uninstall = false;
    bool pause = true;
    std::vector<std::wstring> passthrough;
    for (int i = 1; argv && i < argc; ++i) {
        std::wstring a = argv[i];
        if (a == L"--uninstall") uninstall = true;
        else if (a == L"--no-pause") pause = false;
        else passthrough.push_back(a);
    }
    if (argv) LocalFree(argv);

    std::printf("OpenShim Setup %s\n\n", uninstall ? "(uninstall)" : "");

    const Blob script = FindBlob(uninstall ? kResUninstall : kResInstall);
    const Blob zip = FindBlob(kResSuiteZip);
    const Blob shaRes = FindBlob(kResSuiteSha);
    const bool embedded = zip.size != 0 && shaRes.size == 64;
    std::string expected(reinterpret_cast<const char*>(shaRes.data ? shaRes.data : zip.data), embedded ? 64 : 0);

    int exitCode = 1;
    std::wstring work;
    std::wstring scriptsDir;
    std::wstring scriptPath;
    std::wstring zipPath;

    if (!script.size) {
        std::printf("This copy of OpenShimSetup.exe is missing its installer script.\n");
        goto done;
    }

    if (embedded && !uninstall) {
        // Verify in memory first: a damaged or modified exe is refused before
        // anything touches the disk.
        std::string actual;
        if (!Sha256Hex(zip, actual)) {
            std::printf("Could not compute the SHA-256 of the embedded OpenShim bundle.\n");
            goto done;
        }
        if (actual != expected) {
            std::printf("The embedded OpenShim bundle failed its integrity check.\n"
                        "  expected %s\n  actual   %s\n"
                        "This download is damaged or has been modified. Nothing was installed.\n"
                        "Please download OpenShimSetup.exe again.\n",
                        expected.c_str(), actual.c_str());
            goto done;
        }
        std::printf("Embedded OpenShim bundle verified (sha256 %s).\n", actual.c_str());
    } else if (!uninstall) {
        std::printf("This is a development build with no embedded OpenShim release.\n"
                    "It will download the latest published release instead.\n");
    }

    if (!MakeWorkDir(work)) {
        std::printf("Could not create a temporary folder (error %lu).\n", GetLastError());
        goto done;
    }
    // Scripts sit one level below the work dir, like scripts\ in a checkout, so
    // the install script's "repo root" probes find nothing but our own files.
    scriptsDir = work + L"\\scripts";
    scriptPath = scriptsDir + (uninstall ? L"\\uninstall_windows.ps1" : L"\\install_windows.ps1");
    zipPath = work + L"\\OpenShim-Suite.zip";
    if (!CreateDirectoryW(scriptsDir.c_str(), nullptr) || !WriteBlob(scriptPath, script) ||
        (embedded && !uninstall && !WriteBlob(zipPath, zip))) {
        std::printf("Could not unpack the installer (error %lu).\n", GetLastError());
        goto done;
    }

    if (embedded && !uninstall) {
        SetEnvironmentVariableW(L"OPENSHIM_SUITE_ZIP", zipPath.c_str());
        SetEnvironmentVariableW(L"OPENSHIM_SUITE_SHA256", std::wstring(expected.begin(), expected.end()).c_str());
    } else {
        // Online path: a stray offline setting must not redirect it.
        SetEnvironmentVariableW(L"OPENSHIM_SUITE_ZIP", nullptr);
        SetEnvironmentVariableW(L"OPENSHIM_SUITE_SHA256", nullptr);
    }

    {
        const std::wstring powershell = PowerShellPath();
        if (powershell.empty()) {
            std::printf("Windows PowerShell was not found in the Windows folder.\n");
            goto done;
        }
        // Launched from PowerShell 7, the inherited PSModulePath points at its
        // modules and Windows PowerShell 5.1 then cannot load Get-FileHash.
        // Without the variable, 5.1 rebuilds its own default.
        SetEnvironmentVariableW(L"PSModulePath", nullptr);
        std::wstring cmd = Quote(powershell) + L" -NoProfile -ExecutionPolicy Bypass -File " + Quote(scriptPath);
        for (const auto& a : passthrough) cmd += L" " + Quote(a);

        STARTUPINFOW si{};
        si.cb = sizeof si;
        PROCESS_INFORMATION pi{};
        std::vector<wchar_t> buf(cmd.begin(), cmd.end());
        buf.push_back(L'\0');
        if (!CreateProcessW(powershell.c_str(), buf.data(), nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si, &pi)) {
            std::printf("Could not start PowerShell (error %lu).\n", GetLastError());
            goto done;
        }
        CloseHandle(pi.hThread);
        // Let Ctrl+C reach PowerShell without killing the cleanup below.
        SetConsoleCtrlHandler(nullptr, TRUE);
        WaitForSingleObject(pi.hProcess, INFINITE);
        DWORD code = 1;
        GetExitCodeProcess(pi.hProcess, &code);
        CloseHandle(pi.hProcess);
        exitCode = static_cast<int>(code);
    }

done:
    if (!work.empty()) {
        DeleteFileW(scriptPath.c_str());
        DeleteFileW(zipPath.c_str());
        RemoveDirectoryW(scriptsDir.c_str());
        RemoveDirectoryW(work.c_str());
    }
    std::printf("\n%s\n", exitCode == 0 ? "Done." : "Setup did not complete.");
    if (pause) Pause();
    return exitCode;
}
