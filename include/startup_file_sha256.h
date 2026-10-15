#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include "streaming_sha256.h"
#include <utility>

namespace BZROpenShim
{
    // Early startup workers run concurrently with Steam DLL initialization.
    // Opening a CNG provider here can take BCrypt's provider lock, then wait
    // for the loader lock while Steam holds the latter and requests randomness.
    // Use the existing software SHA-256 core: keep the exact-image gate without
    // loading a crypto DLL/provider or relying on startup timing or store type.
    inline bool TryHashStartupFile(const wchar_t* path, std::string& hex, uint64_t& size)
    {
        hex.clear();
        size = 0;
        struct File
        {
            HANDLE handle;
            ~File() { if (handle != INVALID_HANDLE_VALUE) CloseHandle(handle); }
        } file{ CreateFileW(path, GENERIC_READ,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
            nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr) };
        if (file.handle == INVALID_HANDLE_VALUE)
            return false;
        LARGE_INTEGER originalSize = {};
        if (!GetFileSizeEx(file.handle, &originalSize) || originalSize.QuadPart < 0)
            return false;

        Sha256 hash;
        std::array<unsigned char, 64 * 1024> buffer;
        uint64_t total = 0;
        for (;;)
        {
            DWORD read = 0;
            if (!ReadFile(file.handle, buffer.data(), static_cast<DWORD>(buffer.size()), &read, nullptr))
                return false;
            if (read == 0)
                break;
            hash.Update(buffer.data(), read);
            total += read;
        }
        LARGE_INTEGER finalSize = {};
        if (!GetFileSizeEx(file.handle, &finalSize) ||
            finalSize.QuadPart != originalSize.QuadPart ||
            total != static_cast<uint64_t>(originalSize.QuadPart))
            return false;

        auto digest = hash.Finish();
        for (char& c : digest)
            if (c >= 'a' && c <= 'f') c = static_cast<char>(c - 'a' + 'A');
        hex = std::move(digest);
        size = total;
        return true;
    }
}
