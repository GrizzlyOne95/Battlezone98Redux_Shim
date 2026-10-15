#include "streaming_sha256.h"
#include <cstdio>
#include <cstdlib>
#include <string>

#ifdef _WIN32
#include "startup_file_sha256.h"
#include <filesystem>
#include <fstream>
#endif

using BZROpenShim::Sha256;
static void Check(bool ok, const char* message)
{
    if (!ok) { std::fprintf(stderr, "%s\n", message); std::exit(1); }
}

static void TestVectors()
{
    const struct { const char* text; const char* digest; } vectors[] = {
        { "", "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855" },
        { "abc", "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad" },
        { "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1" }
    };
    for (const auto& v : vectors)
    {
        const std::string text(v.text);
        for (size_t chunk : { size_t(1), size_t(7), size_t(64), size_t(65536) })
        {
            Sha256 hash;
            for (size_t at = 0; at < text.size(); at += chunk)
                hash.Update(text.data() + at, (std::min)(chunk, text.size() - at));
            Check(hash.Finish() == v.digest, "SHA-256 known vector/chunking mismatch");
        }
    }
    const std::string million(1000000, 'a');
    Sha256 hash;
    hash.Update(million.data(), million.size());
    Check(hash.Finish() == "cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0", "million-a vector mismatch");
}

#ifdef _WIN32
static HANDLE readyEvent, workEvent, doneEvent;
static std::wstring probePath;
static bool control = false, completedInsideLoader = false, workerOk = false;

extern "C" __declspec(dllexport) void __cdecl StartupHashLoaderLockProbe()
{
    SetEvent(workEvent);
    completedInsideLoader = WaitForSingleObject(doneEvent, 1500) == WAIT_OBJECT_0;
}

static DWORD WINAPI HashWorker(void*)
{
    SetEvent(readyEvent);
    if (WaitForSingleObject(workEvent, 5000) != WAIT_OBJECT_0) return 1;
    if (control)
    {
        HMODULE dll = LoadLibraryW(L"version.dll");
        if (!dll) return 2;
        FreeLibrary(dll);
    }
    std::string hex;
    uint64_t size = 0;
    workerOk = BZROpenShim::TryHashStartupFile(probePath.c_str(), hex, size) &&
        size == 3 && hex == "BA7816BF8F01CFEA414140DE5DAE2223B00361A396177A9CB410FF61F20015AD";
    SetEvent(doneEvent);
    return 0;
}

static void TestFilesAndLoaderLock(const char* fixture)
{
    namespace fs = std::filesystem;
    const auto dir = fs::temp_directory_path() / (L"openshim-hash-\u00e9-" + std::to_wstring(GetCurrentProcessId()));
    fs::create_directory(dir);
    const auto path = dir / L"\u6708.bin";
    for (size_t length : { size_t(0), size_t(55), size_t(56), size_t(63), size_t(64), size_t(65), size_t(65535), size_t(65536), size_t(65537) })
    {
        std::string bytes(length, '\0');
        for (size_t i = 0; i < length; ++i) bytes[i] = static_cast<char>(i % 251);
        { std::ofstream out(path, std::ios::binary); out.write(bytes.data(), bytes.size()); }
        Sha256 oracle;
        oracle.Update(bytes.data(), bytes.size());
        auto expected = oracle.Finish();
        for (char& c : expected) if (c >= 'a' && c <= 'f') c = static_cast<char>(c - 'a' + 'A');
        std::string actual = "stale";
        uint64_t size = 99;
        Check(BZROpenShim::TryHashStartupFile(path.c_str(), actual, size), "hash file failed");
        Check(actual == expected && size == length, "streamed file digest/size mismatch");
    }
    std::string hex = "stale";
    uint64_t size = 99;
    Check(!BZROpenShim::TryHashStartupFile((dir / "missing").c_str(), hex, size) && hex.empty() && size == 0, "missing file must clear outputs and fail closed");
    Check(!BZROpenShim::TryHashStartupFile(dir.c_str(), hex, size), "directory must fail closed");
    { std::ofstream out(path, std::ios::binary); out << "abc"; }
    probePath = path.wstring();
    readyEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    workEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    doneEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    Check(readyEvent && workEvent && doneEvent, "probe event creation failed");
    HANDLE worker = CreateThread(nullptr, 0, HashWorker, nullptr, 0, nullptr);
    Check(worker && WaitForSingleObject(readyEvent, 5000) == WAIT_OBJECT_0, "hash worker did not start");
    HMODULE dll = LoadLibraryA(fixture);
    Check(dll != nullptr, "loader-lock fixture load failed");
    Check(WaitForSingleObject(worker, 5000) == WAIT_OBJECT_0 && workerOk, "hash worker did not finish");
    Check(completedInsideLoader != control, "hashing blocked on loader lock, or negative control failed to detect it");
    FreeLibrary(dll);
    for (HANDLE h : { worker, readyEvent, workEvent, doneEvent }) CloseHandle(h);
    fs::remove(path);
    fs::remove(dir);
}
#endif

int main(int argc, char** argv)
{
    TestVectors();
#ifdef _WIN32
    Check(argc >= 2, "loader-lock fixture path required");
    control = argc >= 3 && std::string(argv[2]) == "--loader-control";
    TestFilesAndLoaderLock(argv[1]);
#else
    (void)argc; (void)argv;
#endif
    std::puts("SHA-256 vectors, streaming and startup probe passed");
}
