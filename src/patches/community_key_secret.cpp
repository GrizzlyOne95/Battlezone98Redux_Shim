#include "community_key_secret.h"

#include <windows.h>

#include <string>

namespace BZROpenShim
{
    namespace
    {
        // RtlGenRandom, looked up at call time: no new static import, and never
        // touched under the loader lock (this only runs on a lobby login).
        bool FillRandom(unsigned char* buffer, ULONG length)
        {
            using RtlGenRandomFn = BOOLEAN(WINAPI*)(PVOID, ULONG);
            HMODULE advapi = LoadLibraryW(L"advapi32.dll");
            if (advapi == nullptr)
                return false;
            const auto generate =
                reinterpret_cast<RtlGenRandomFn>(GetProcAddress(advapi, "SystemFunction036"));
            const bool ok = generate != nullptr && generate(buffer, length) != FALSE;
            FreeLibrary(advapi);
            return ok;
        }

        bool ReadExact(const std::filesystem::path& path, unsigned char* buffer, DWORD length)
        {
            HANDLE file = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr,
                                      OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
            if (file == INVALID_HANDLE_VALUE)
                return false;
            LARGE_INTEGER size = {};
            DWORD read = 0;
            const bool ok = GetFileSizeEx(file, &size) && size.QuadPart == length &&
                            ReadFile(file, buffer, length, &read, nullptr) && read == length;
            CloseHandle(file);
            return ok;
        }

        bool WriteNew(const std::filesystem::path& path, const unsigned char* buffer, DWORD length)
        {
            HANDLE file = CreateFileW(path.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_NEW,
                                      FILE_ATTRIBUTE_NORMAL, nullptr);
            if (file == INVALID_HANDLE_VALUE)
                return false;
            DWORD written = 0;
            const bool ok = WriteFile(file, buffer, length, &written, nullptr) && written == length &&
                            FlushFileBuffers(file);
            CloseHandle(file);
            if (!ok)
                DeleteFileW(path.c_str());
            return ok;
        }
    }

    bool LoadOrCreateCommunitySecret(const std::filesystem::path& path,
                                     std::array<unsigned char, kCommunitySecretBytes>& secret)
    {
        secret.fill(0);
        const DWORD length = static_cast<DWORD>(secret.size());
        if (ReadExact(path, secret.data(), length))
            return true;
        if (GetFileAttributesW(path.c_str()) != INVALID_FILE_ATTRIBUTES)
        {
            secret.fill(0);
            return false;  // exists but unreadable or the wrong size: never overwrite it
        }

        std::array<unsigned char, kCommunitySecretBytes> fresh = {};
        if (!FillRandom(fresh.data(), length))
            return false;
        std::filesystem::path temp = path;
        temp += L"." + std::to_wstring(GetCurrentProcessId()) + L"." +
                std::to_wstring(GetTickCount64()) + L".tmp";
        const bool written = WriteNew(temp, fresh.data(), length);
        SecureZeroMemory(fresh.data(), fresh.size());
        if (!written)
            return false;
        // No MOVEFILE_REPLACE_EXISTING: if another process won the race, keep
        // its file and read that instead.
        MoveFileExW(temp.c_str(), path.c_str(), MOVEFILE_WRITE_THROUGH);
        DeleteFileW(temp.c_str());
        if (ReadExact(path, secret.data(), length))
            return true;
        secret.fill(0);
        return false;
    }
}
