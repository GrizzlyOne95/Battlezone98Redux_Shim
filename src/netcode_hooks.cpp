// netcode_hooks.cpp
// BZR Open Shim - netcode socket buffer enhancement
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Strategy:
//   Intercept `WSASocketW` calls by walking BZR.exe's Import Address Table (IAT)
//   and replacing the pointer with our hook function. When the game creates
//   its P2P socket, our hook calls the real WSASocketW, then calls
//   setsockopt() to apply the enlarged send and receive buffer sizes.

#include "netcode_hooks.h"
#include "patcher.h"      // for Log()

#include <Windows.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <new>

// We need Winsock 2 for the constants, types, and setsockopt
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

namespace BZROpenShim
{
    // -----------------------------------------------------------------------
    // Signature for WSASocketW
    // -----------------------------------------------------------------------
    typedef SOCKET (WINAPI* PFN_WSASocketW)(
        int af, int type, int protocol,
        LPWSAPROTOCOL_INFOW lpProtocolInfo,
        GROUP g, DWORD dwFlags
    );

    static PFN_WSASocketW g_RealWSASocketW = nullptr;

    // Buffer sizes from manifest (defaults if missing)
    static uint32_t g_SendSize = 524288;   // 512 KB
    static uint32_t g_RecvSize = 524288;   // 512 KB

    // -----------------------------------------------------------------------
    // Our hook that gets called instead of the real WSASocketW
    // -----------------------------------------------------------------------
    static SOCKET WINAPI Hooked_WSASocketW(
        int af, int type, int protocol,
        LPWSAPROTOCOL_INFOW lpProtocolInfo,
        GROUP g, DWORD dwFlags
    )
    {
        // 1. Call the original function to create the socket
        SOCKET s = g_RealWSASocketW(af, type, protocol, lpProtocolInfo, g, dwFlags);

        if (s != INVALID_SOCKET)
        {
            // The game uses UDP (SOCK_DGRAM) or IPPROTO_UDP for its primary netcode
            // We increase the buffers whenever a datagram socket is opened.
            if (type == SOCK_DGRAM || protocol == IPPROTO_UDP)
            {
                // 2. Set the send buffer
                int sendVal = static_cast<int>(g_SendSize);
                if (setsockopt(s, SOL_SOCKET, SO_SNDBUF, (const char*)&sendVal, sizeof(sendVal)) == 0)
                {
                    Log(L"[NET]  Hooked socket %p: setsockopt(SO_SNDBUF, %u) OK\n", (void*)s, g_SendSize);
                }
                else
                {
                    Log(L"[NET]  Hooked socket %p: setsockopt(SO_SNDBUF, %u) FAILED. error=%d\n", (void*)s, g_SendSize, WSAGetLastError());
                }

                // 3. Set the receive buffer
                int recvVal = static_cast<int>(g_RecvSize);
                if (setsockopt(s, SOL_SOCKET, SO_RCVBUF, (const char*)&recvVal, sizeof(recvVal)) == 0)
                {
                    Log(L"[NET]  Hooked socket %p: setsockopt(SO_RCVBUF, %u) OK\n", (void*)s, g_RecvSize);
                }
                else
                {
                    Log(L"[NET]  Hooked socket %p: setsockopt(SO_RCVBUF, %u) FAILED. error=%d\n", (void*)s, g_RecvSize, WSAGetLastError());
                }

                // 4. Read back effective values for verification
                int sndRead = -1;
                int rcvRead = -1;
                int sndLen = sizeof(sndRead);
                int rcvLen = sizeof(rcvRead);
                if (getsockopt(s, SOL_SOCKET, SO_SNDBUF, (char*)&sndRead, &sndLen) == 0)
                {
                    Log(L"[NET]  Hooked socket %p: effective SO_SNDBUF=%d\n", (void*)s, sndRead);
                }
                else
                {
                    Log(L"[NET]  Hooked socket %p: getsockopt(SO_SNDBUF) FAILED. error=%d\n", (void*)s, WSAGetLastError());
                }

                if (getsockopt(s, SOL_SOCKET, SO_RCVBUF, (char*)&rcvRead, &rcvLen) == 0)
                {
                    Log(L"[NET]  Hooked socket %p: effective SO_RCVBUF=%d\n", (void*)s, rcvRead);
                }
                else
                {
                    Log(L"[NET]  Hooked socket %p: getsockopt(SO_RCVBUF) FAILED. error=%d\n", (void*)s, WSAGetLastError());
                }
            }
        }

        return s;
    }

    // -----------------------------------------------------------------------
    // Generic IAT Hooker
    // Finds 'moduleName' (e.g., "ws2_32.dll") and 'funcName' (e.g. "WSASocketW")
    // in the import table of 'targetModule'. Replaces it with 'newFunc'.
    // -----------------------------------------------------------------------
    static bool PatchIAT(HMODULE targetModule, const char* moduleName, const char* funcName, void* newFunc, void** oldFunc)
    {
        if (!targetModule) return false;

        auto dos = reinterpret_cast<IMAGE_DOS_HEADER*>(targetModule);
        if (dos->e_magic != IMAGE_DOS_SIGNATURE) return false;

        auto nt = reinterpret_cast<IMAGE_NT_HEADERS*>(
            reinterpret_cast<uint8_t*>(targetModule) + dos->e_lfanew);
        if (nt->Signature != IMAGE_NT_SIGNATURE) return false;

        DWORD importRVA = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
        if (importRVA == 0) return false;

        auto importDesc = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(
            reinterpret_cast<uint8_t*>(targetModule) + importRVA);

        // Walk through all DLLs the targetModule imports
        while (importDesc->Name)
        {
            const char* currModuleName = reinterpret_cast<const char*>(targetModule) + importDesc->Name;
            
            if (_stricmp(currModuleName, moduleName) == 0)
            {
                // Found the correct DLL import block. Now find the function.
                auto originalFirstThunk = reinterpret_cast<IMAGE_THUNK_DATA*>(
                    reinterpret_cast<uint8_t*>(targetModule) + (importDesc->OriginalFirstThunk ? importDesc->OriginalFirstThunk : importDesc->FirstThunk));
                auto firstThunk = reinterpret_cast<IMAGE_THUNK_DATA*>(
                    reinterpret_cast<uint8_t*>(targetModule) + importDesc->FirstThunk);

                while (originalFirstThunk->u1.AddressOfData)
                {
                    if (IMAGE_SNAP_BY_ORDINAL(originalFirstThunk->u1.Ordinal))
                    {
                        // We do not support hooking by ordinal here.
                    }
                    else
                    {
                        auto importByName = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(
                            reinterpret_cast<uint8_t*>(targetModule) + originalFirstThunk->u1.AddressOfData);

                        if (strcmp(importByName->Name, funcName) == 0)
                        {
                            // Found the function! Modify the IAT entry.
                            DWORD oldProtect;
                            void** iatEntry = reinterpret_cast<void**>(&firstThunk->u1.Function);
                            
                            if (VirtualProtect(iatEntry, sizeof(void*), PAGE_READWRITE, &oldProtect))
                            {
                                if (oldFunc) *oldFunc = *iatEntry;
                                *iatEntry = newFunc;
                                VirtualProtect(iatEntry, sizeof(void*), oldProtect, &oldProtect);
                                return true;
                            }
                        }
                    }

                    ++originalFirstThunk;
                    ++firstThunk;
                }
                
                break; // Checked the right DLL, didn't find the func.
            }
            ++importDesc;
        }

        return false;
    }

    // -----------------------------------------------------------------------
    // Read buffer sizes from the "profile" object in the manifest JSON.
    // -----------------------------------------------------------------------
    static bool ParseProfile(const wchar_t* path, uint32_t& outSend, uint32_t& outRecv)
    {
        FILE* f = nullptr;
        _wfopen_s(&f, path, L"r");
        if (!f) return false;

        fseek(f, 0, SEEK_END);
        long size = ftell(f);
        fseek(f, 0, SEEK_SET);

        if (size <= 0 || size > 64 * 1024)
        {
            fclose(f);
            return false;
        }

        char* buf = new (std::nothrow) char[size + 1];
        if (!buf) { fclose(f); return false; }

        size_t bytesRead = fread(buf, 1, static_cast<size_t>(size), f);
        fclose(f);
        buf[bytesRead] = '\0';

        bool found = false;
        
        const char* profileStart = strstr(buf, "\"profile\"");
        if (profileStart)
        {
            auto extractInt = [](const char* start, const char* key) -> uint32_t {
                const char* pos = strstr(start, key);
                if (!pos) return 0;
                pos += strlen(key);
                while (*pos && (*pos == ':' || *pos == ' ' || *pos == '\t' || *pos == '\n' || *pos == '\r' || *pos == '"')) ++pos;
                return static_cast<uint32_t>(strtoul(pos, nullptr, 10));
            };

            uint32_t s = extractInt(profileStart, "\"send_buffer_bytes\"");
            uint32_t r = extractInt(profileStart, "\"receive_buffer_bytes\"");

            if (s > 0) outSend = s;
            if (r > 0) outRecv = r;
            
            if (s > 0 || r > 0) found = true;
        }

        delete[] buf;
        return found;
    }

    // -----------------------------------------------------------------------
    // ApplyNetcodeHooks — main entry point
    // -----------------------------------------------------------------------
    void ApplyNetcodeHooks()
    {
        Log(L"=========== NETCODE PATCHES ===========\n");

        HMODULE hMain = GetModuleHandleW(nullptr);
        if (!hMain) return;

        wchar_t dllPath[MAX_PATH] = {};
        GetModuleFileNameW(nullptr, dllPath, MAX_PATH);

        wchar_t* lastSlash = wcsrchr(dllPath, L'\\');
        if (lastSlash) *(lastSlash + 1) = L'\0';

        wchar_t manifestPath[MAX_PATH] = {};
        _snwprintf_s(manifestPath, MAX_PATH, L"%snetcode_manifest.json", dllPath);

        if (ParseProfile(manifestPath, g_SendSize, g_RecvSize))
        {
            Log(L"[NET]  Loaded sizes from manifest: send=%u, recv=%u\n", g_SendSize, g_RecvSize);
        }
        else
        {
            Log(L"[NET]  Could not read profile from manifest — using defaults (send=%u, recv=%u)\n", g_SendSize, g_RecvSize);
        }

        // Apply hook to WSASocketW into battlezone98redux.exe's IAT
        bool hooked = PatchIAT(hMain, "ws2_32.dll", "WSASocketW", 
            (void*)Hooked_WSASocketW, 
            (void**)&g_RealWSASocketW);

        if (hooked)
        {
            Log(L"[NET]  IAT hook successfully installed for WSASocketW. Sockets will be resized.\n");
        }
        else
        {
            Log(L"[NET]  WARNING: Failed to install IAT hook for WSASocketW!\n");
        }
    }

} // namespace BZROpenShim
