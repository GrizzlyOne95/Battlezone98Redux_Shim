// troubleshooting_bundle.h
// BZR Open Shim - the Options "Build Troubleshooting Bundle" action.
//
// Packs the logs, settings and newest crash dump a bug report needs into one
// zip beside the game logs, so a player can send a single file. Game-folder
// files come from a fixed allowlist, so the chat log, ban and mute lists and
// the community key secret never enter it; logs\ is taken by extension and
// its network traces keep player names and addresses.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <string>
#include <vector>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

namespace BZROpenShim
{
    uint32_t Crc32Update(uint32_t crc, const void* data, size_t length);

    // Minimal zip writer: stored (uncompressed) entries, no zip64, so the
    // whole archive must stay under 4 GB. Each entry's header is patched
    // after its data is streamed, so no data descriptors are needed.
    class StoreZipWriter
    {
    public:
        StoreZipWriter() = default;
        StoreZipWriter(const StoreZipWriter&) = delete;
        StoreZipWriter& operator=(const StoreZipWriter&) = delete;
        ~StoreZipWriter();

        bool Open(const std::wstring& path);
        bool AddBytes(const std::string& name, const void* data, size_t length);
        // Copies at most maxBytes from the END of source (a runaway log keeps
        // its newest lines). Returns false when the source cannot be opened.
        // copiedBytes/sourceBytes report what happened.
        bool AddFile(const std::string& name, const std::wstring& source, uint64_t maxBytes,
                     uint64_t& copiedBytes, uint64_t& sourceBytes);
        bool Close();
        uint64_t BytesWritten() const { return m_offset; }
        bool Failed() const { return m_failed; }

    private:
        struct Entry
        {
            std::string name;
            uint32_t crc = 0;
            uint32_t size = 0;
            uint32_t offset = 0;
        };

        bool Write(const void* data, size_t length);
        bool BeginEntry(const std::string& name, Entry& entry);
        bool FinishEntry(Entry& entry);

        HANDLE m_file = INVALID_HANDLE_VALUE;
        uint64_t m_offset = 0;
        uint16_t m_dosTime = 0;
        uint16_t m_dosDate = 0;
        bool m_failed = false;
        std::vector<Entry> m_entries;
    };

    struct TroubleshootingBundleResult
    {
        bool ok = false;
        std::wstring zipPath;
        size_t fileCount = 0;
        uint64_t zipBytes = 0;
        std::string error;
    };

    // Builds logs\OpenShim_Troubleshooting_<stamp>.zip next to the game exe.
    // Synchronous: copies up to a few hundred MB on the calling thread.
    TroubleshootingBundleResult BuildTroubleshootingBundle();

    // True under Wine/Proton (ntdll exports wine_get_version).
    bool RunningUnderWine();

    // Under Wine/Proton, the host (Linux) path of a Windows path, for showing
    // the player where the file really is; empty on Windows or on failure.
    std::string HostPathForDisplay(const std::wstring& path);

    // Opens Explorer with the bundle selected. Does nothing under Wine/Proton,
    // where Explorer is a window inside the prefix, not the player's file manager.
    void RevealTroubleshootingBundle(const std::wstring& zipPath);
}
