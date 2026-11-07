// d3d_compile_cache.cpp
// BZR Open Shim - content-addressed DXBC cache and live window for D3DCompile
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Why: on mission load Ogre's Direct3D11 render system compiles ~200 HLSL
// programs synchronously on the main thread through D3DCompile (~0.4 s each).
// That is an 80 s freeze during which the thread never reads its message
// queue, so Windows ghosts the window as "Not responding". Ogre's microcode
// cache is dropped whenever the shader-source fingerprint changes (every
// OpenShim or mod update), so the full recompile repeated after each update.
//
// What: RenderSystem_Direct3D11.dll's import of D3DCompile is redirected.
// The source is run through D3DPreprocess (same defines and include handler
// the caller passed), and the output plus entry point, target and flags key a
// DXBC file under <game root>/shader_cache/dxbc. A hit returns the stored
// blob. A miss runs the real D3DCompile on a worker thread while the calling
// thread pumps its message queue (PM_NOREMOVE, as terrain_native_hd does),
// then stores the result. If the worker hits any exception, the compile is
// redone inline so C++ exceptions reach Ogre as on the stock path.
//
// The worker compiles the PREPROCESSED text (no defines, no include handler).
// Ogre's include handler opens resources under the ResourceGroupManager lock,
// which the calling thread already holds when it compiles during resource
// group initialisation (OpenShim's EnsureEnhancedResourceGroup); calling it
// from the worker deadlocked the game at startup on any cache miss. Compiling
// the preprocessed text also makes the stored blob match its cache key.
//
// Fail closed: any unresolved export or failed preprocess leaves the stock
// compile path. OPENSHIM_DISABLE_DXBC_CACHE (or the existing
// OPENSHIM_DISABLE_SHADER_CACHE / BZR_DISABLE_SHADER_CACHE) leaves the
// renderer stock. A failed cache write latches the cache off.
#include "d3d_compile_cache.h"
#include "dxbc_cache_policy.h"
#include "iat_patch.h"
#include "ogre_shader_cache.h"
#include "shim_log.h"

#include <Windows.h>
#include <d3dcommon.h>

#include <atomic>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <mutex>
#include <string>
#include <vector>

namespace BZROpenShim
{
    namespace
    {
        constexpr char kComponent[] = "shadercache";
        constexpr DWORD kPumpIntervalMs = 50;
        constexpr ULONGLONG kSlowCompileMs = 500;
        constexpr uint32_t kSummaryEvery = 50;
        constexpr int kMaxInstallFaults = 5;

        using FnD3DCompile = HRESULT(WINAPI*)(
            LPCVOID, SIZE_T, LPCSTR, const D3D_SHADER_MACRO*, ID3DInclude*,
            LPCSTR, LPCSTR, UINT, UINT, ID3DBlob**, ID3DBlob**);
        using FnD3DPreprocess = HRESULT(WINAPI*)(
            LPCVOID, SIZE_T, LPCSTR, const D3D_SHADER_MACRO*, ID3DInclude*,
            ID3DBlob**, ID3DBlob**);
        using FnD3DCreateBlob = HRESULT(WINAPI*)(SIZE_T, ID3DBlob**);

        // Set once under the install mutex, before the IAT patch exists.
        FnD3DCompile g_RealD3DCompile = nullptr;
        FnD3DPreprocess g_Preprocess = nullptr;
        FnD3DCreateBlob g_CreateBlob = nullptr;
        std::wstring g_CacheDir;

        std::atomic<uint32_t> g_Hits{ 0 };
        std::atomic<uint32_t> g_Misses{ 0 };
        std::atomic<uint32_t> g_Passthrough{ 0 };
        std::atomic<uint32_t> g_Writes{ 0 };
        std::atomic<bool> g_CacheOff{ false };   // a cache write failed: pass straight through
        std::atomic<bool> g_WorkerFaultLogged{ false };
        std::atomic<bool> g_InstallDone{ false };

        bool EnvFlagSet(const char* name)
        {
            char value[16] = {};
            const DWORD len = GetEnvironmentVariableA(name, value, sizeof(value));
            if (len == 0 || len >= sizeof(value))
                return len >= sizeof(value);
            return !(value[0] == '0' && value[1] == '\0');
        }

        std::filesystem::path GetGameRootDirectory()
        {
            wchar_t buffer[MAX_PATH] = {};
            const DWORD len = GetModuleFileNameW(nullptr, buffer, MAX_PATH);
            if (len == 0 || len >= MAX_PATH)
                return {};
            return std::filesystem::path(buffer).parent_path();
        }

        void PumpMessages()
        {
            MSG pending;
            PeekMessageW(&pending, nullptr, 0, 0, PM_NOREMOVE);
        }

        std::wstring EntryPath(uint64_t key)
        {
            char hex[17];
            DxbcCachePolicy::HexName(key, hex);
            std::wstring path = g_CacheDir;
            path += L'\\';
            for (const char* c = hex; *c; ++c)
                path += static_cast<wchar_t>(*c);
            path += L".dxbc";
            return path;
        }

        bool ReadEntry(uint64_t key, size_t preprocessedSize, std::vector<uint8_t>& blob)
        {
            const std::wstring path = EntryPath(key);
            HANDLE file = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr,
                                      OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
            if (file == INVALID_HANDLE_VALUE)
                return false;
            LARGE_INTEGER size{};
            std::vector<uint8_t> data;
            bool ok = GetFileSizeEx(file, &size) && size.QuadPart > 0 &&
                      size.QuadPart <= static_cast<LONGLONG>(DxbcCachePolicy::kMaxBlobBytes) + 64;
            if (ok)
            {
                data.resize(static_cast<size_t>(size.QuadPart));
                DWORD got = 0;
                ok = ReadFile(file, data.data(), static_cast<DWORD>(data.size()), &got, nullptr) &&
                     got == data.size();
            }
            CloseHandle(file);
            size_t offset = 0, blobSize = 0;
            if (!ok || !DxbcCachePolicy::ValidateEntry(data.data(), data.size(), key,
                                                       preprocessedSize, &offset, &blobSize))
                return false;
            blob.assign(data.begin() + offset, data.begin() + offset + blobSize);
            return true;
        }

        // False when the cache directory looks unusable (cannot create or
        // write the temp file, flush fails, rename fails).
        bool WriteEntry(uint64_t key, size_t preprocessedSize, const void* blob, size_t blobSize)
        {
            if (blobSize == 0 || blobSize > DxbcCachePolicy::kMaxBlobBytes)
                return true;
            const std::wstring path = EntryPath(key);
            const std::wstring temp = path + L"." + std::to_wstring(GetCurrentProcessId()) + L".tmp";
            HANDLE file = CreateFileW(temp.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS,
                                      FILE_ATTRIBUTE_NORMAL, nullptr);
            if (file == INVALID_HANDLE_VALUE)
                return false;
            const DxbcCachePolicy::EntryHeader header =
                DxbcCachePolicy::MakeHeader(key, preprocessedSize, blob, blobSize);
            DWORD wrote = 0;
            const bool ok = WriteFile(file, &header, sizeof(header), &wrote, nullptr) &&
                            wrote == sizeof(header) &&
                            WriteFile(file, blob, static_cast<DWORD>(blobSize), &wrote, nullptr) &&
                            wrote == blobSize &&
                            FlushFileBuffers(file);
            CloseHandle(file);
            if (!ok || !MoveFileExW(temp.c_str(), path.c_str(),
                                    MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH))
            {
                DeleteFileW(temp.c_str());
                return false;
            }
            ++g_Writes;
            return true;
        }

        struct CompileJob
        {
            LPCVOID src; SIZE_T srcSize; LPCSTR name;
            const D3D_SHADER_MACRO* defines; ID3DInclude* include;
            LPCSTR entry; LPCSTR target; UINT flags1; UINT flags2;
            ID3DBlob* code = nullptr;
            ID3DBlob* errors = nullptr;
            HRESULT hr = E_FAIL;
            bool ok = false;
        };

        // Any exception on the worker (SEH or C++) ends the attempt; the caller
        // then recompiles inline so a C++ exception from Ogre's include handler
        // propagates to Ogre exactly as on the stock path.
        void RunCompileGuarded(CompileJob* job)
        {
            __try
            {
                job->hr = g_RealD3DCompile(job->src, job->srcSize, job->name, job->defines,
                                           job->include, job->entry, job->target, job->flags1,
                                           job->flags2, &job->code, &job->errors);
                job->ok = true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                job->ok = false;
                job->code = nullptr;
                job->errors = nullptr;
            }
        }

        DWORD WINAPI CompileThread(LPVOID param)
        {
            RunCompileGuarded(static_cast<CompileJob*>(param));
            return 0;
        }

        // Real compile on a worker while this thread keeps the window alive.
        // Returns false when the worker could not run to completion (thread
        // creation failed or it faulted); the caller must compile inline.
        bool CompileWhilePumping(CompileJob& job)
        {
            HANDLE worker = CreateThread(nullptr, 0, CompileThread, &job, 0, nullptr);
            if (!worker)
                return false;
            while (WaitForSingleObject(worker, kPumpIntervalMs) == WAIT_TIMEOUT)
                PumpMessages();
            CloseHandle(worker);
            if (!job.ok && !g_WorkerFaultLogged.exchange(true))
            {
                LogShimA(LogLevel::Warn, kComponent,
                    "[DXBC] compile worker faulted; compiling inline (logged once)");
            }
            return job.ok;
        }

        void LogSummaryIfDue()
        {
            const uint32_t total = g_Hits + g_Misses + g_Passthrough;
            if (total % kSummaryEvery != 0)
                return;
            LogShimA(LogLevel::Info, kComponent,
                "[DXBC] compiles=%u hits=%u misses=%u stored=%u passthrough=%u",
                total, g_Hits.load(), g_Misses.load(), g_Writes.load(), g_Passthrough.load());
        }

        // Preprocess under SEH: a faulting include handler must not take the
        // process down where the stock path would have survived. Kept apart
        // from the hook so no object needing unwinding shares its frame.
        HRESULT PreprocessGuarded(LPCVOID src, SIZE_T size, LPCSTR name,
                                  const D3D_SHADER_MACRO* defines, ID3DInclude* include,
                                  ID3DBlob** pre, ID3DBlob** errors)
        {
            __try
            {
                return g_Preprocess(src, size, name, defines, include, pre, errors);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                *pre = nullptr;
                *errors = nullptr;
                return E_FAIL;
            }
        }

        HRESULT WINAPI HookedD3DCompile(
            LPCVOID pSrcData, SIZE_T SrcDataSize, LPCSTR pSourceName,
            const D3D_SHADER_MACRO* pDefines, ID3DInclude* pInclude,
            LPCSTR pEntrypoint, LPCSTR pTarget, UINT Flags1, UINT Flags2,
            ID3DBlob** ppCode, ID3DBlob** ppErrorMsgs)
        {
            const auto passthrough = [&]() {
                ++g_Passthrough;
                return g_RealD3DCompile(pSrcData, SrcDataSize, pSourceName, pDefines, pInclude,
                                        pEntrypoint, pTarget, Flags1, Flags2, ppCode, ppErrorMsgs);
            };
            if (!ppCode || !pSrcData || !g_Preprocess || !g_CreateBlob ||
                g_CacheOff.load(std::memory_order_relaxed))
                return passthrough();

            ID3DBlob* pre = nullptr;
            ID3DBlob* preErrors = nullptr;
            const HRESULT preHr = PreprocessGuarded(pSrcData, SrcDataSize, pSourceName,
                                                    pDefines, pInclude, &pre, &preErrors);
            if (preErrors)
                preErrors->Release();
            if (FAILED(preHr) || !pre)
            {
                if (pre)
                    pre->Release();
                return passthrough();
            }

            const size_t preSize = pre->GetBufferSize();
            const uint64_t key = DxbcCachePolicy::ComputeKey(
                pre->GetBufferPointer(), preSize, pEntrypoint, pTarget, Flags1, Flags2);

            std::vector<uint8_t> blob;
            if (ReadEntry(key, preSize, blob))
            {
                ID3DBlob* out = nullptr;
                if (SUCCEEDED(g_CreateBlob(blob.size(), &out)) && out)
                {
                    std::memcpy(out->GetBufferPointer(), blob.data(), blob.size());
                    *ppCode = out;
                    if (ppErrorMsgs)
                        *ppErrorMsgs = nullptr;
                    pre->Release();
                    ++g_Hits;
                    LogSummaryIfDue();
                    return S_OK;
                }
            }

            ++g_Misses;
            // Preprocessed text: the worker must never call the caller's include
            // handler (see the header comment), and defines are already expanded.
            CompileJob job{ pre->GetBufferPointer(), preSize, pSourceName, nullptr, nullptr,
                            pEntrypoint, pTarget, Flags1, Flags2 };
            // OPENSHIM_DXBC_DUMP_SLOW=1: keep the source of slow compiles for offline timing.
            static const bool dumpSlow = EnvFlagSet("OPENSHIM_DXBC_DUMP_SLOW");
            std::string dumpText;
            if (dumpSlow)
                dumpText.assign(static_cast<const char*>(pre->GetBufferPointer()), preSize);
            const ULONGLONG t0 = GetTickCount64();
            const bool workerOk = CompileWhilePumping(job);
            pre->Release();
            if (!workerOk)
            {
                // Unguarded, like the stock path: exceptions reach Ogre.
                return g_RealD3DCompile(pSrcData, SrcDataSize, pSourceName, pDefines, pInclude,
                                        pEntrypoint, pTarget, Flags1, Flags2, ppCode, ppErrorMsgs);
            }
            const HRESULT hr = job.hr;
            const ULONGLONG ms = GetTickCount64() - t0;

            *ppCode = job.code;
            if (ppErrorMsgs)
                *ppErrorMsgs = job.errors;
            else if (job.errors)
                job.errors->Release();

            if (SUCCEEDED(hr) && job.code &&
                !WriteEntry(key, preSize, job.code->GetBufferPointer(), job.code->GetBufferSize()) &&
                !g_CacheOff.exchange(true))
            {
                LogShimA(LogLevel::Warn, kComponent,
                    "[DXBC] cache write failed (err=%lu); cache latched off",
                    static_cast<unsigned long>(GetLastError()));
            }

            if (ms > kSlowCompileMs)
            {
                LogShimA(LogLevel::Info, kComponent,
                    "[UIPERF][SHADER] dxbc_compile elapsed=%.2fms entry=%s target=%s hr=0x%08lx",
                    static_cast<double>(ms), pEntrypoint ? pEntrypoint : "", pTarget ? pTarget : "",
                    static_cast<unsigned long>(hr));
                if (dumpSlow)
                {
                    char hex[17];
                    DxbcCachePolicy::HexName(key, hex);
                    std::error_code ec;
                    const std::filesystem::path dir = std::filesystem::path(g_CacheDir).parent_path() / L"slow";
                    std::filesystem::create_directories(dir, ec);
                    char name[128];
                    sprintf_s(name, "%06llu_%s_%s_f%08x.hlsl", ms, pEntrypoint ? pEntrypoint : "", hex, Flags1);
                    FILE* f = nullptr;
                    if (_wfopen_s(&f, (dir / name).c_str(), L"wb") == 0 && f)
                    {
                        fwrite(dumpText.data(), 1, dumpText.size(), f);
                        fclose(f);
                    }
                }
            }
            LogSummaryIfDue();

            // Keep Ogre's microcode cache saving progress during a long cold
            // load. Ogre calls D3DCompile from program load, never from inside
            // OgreShaderCacheTick's own critical section (that only loads and
            // saves the cache), so the mutex is free here.
            OgreShaderCacheTick();
            return hr;
        }
    }

    void InstallD3DCompileCacheIfPossible()
    {
        // Called from the patch thread (under CodePatchLock) and from the game
        // thread on every .program open: lock-free once finished, serialised
        // before that.
        if (g_InstallDone.load(std::memory_order_acquire))
            return;
        static std::mutex installMutex;
        static bool prepared = false;
        static void* original = nullptr;
        static int faults = 0;
        std::lock_guard<std::mutex> lock(installMutex);
        if (g_InstallDone.load(std::memory_order_relaxed))
            return;

        const auto finish = [] { g_InstallDone.store(true, std::memory_order_release); };

        HMODULE renderer = GetModuleHandleA("RenderSystem_Direct3D11.dll");
        if (!renderer)
            return;

        if (!prepared)
        {
            if (EnvFlagSet("OPENSHIM_DISABLE_DXBC_CACHE") ||
                EnvFlagSet("OPENSHIM_DISABLE_SHADER_CACHE") ||
                EnvFlagSet("BZR_DISABLE_SHADER_CACHE"))
            {
                finish();
                LogShimA(LogLevel::Info, kComponent, "[DXBC] disabled by environment kill switch");
                return;
            }

            HMODULE compiler = GetModuleHandleA("D3DCOMPILER_47.dll");
            if (!compiler)
                return; // the renderer imports it, so it appears with the renderer

            const FnD3DPreprocess preprocess = reinterpret_cast<FnD3DPreprocess>(
                GetProcAddress(compiler, "D3DPreprocess"));
            const FnD3DCreateBlob createBlob = reinterpret_cast<FnD3DCreateBlob>(
                GetProcAddress(compiler, "D3DCreateBlob"));
            original = reinterpret_cast<void*>(GetProcAddress(compiler, "D3DCompile"));
            if (!preprocess || !createBlob || !original)
            {
                finish();
                LogShimA(LogLevel::Warn, kComponent,
                    "[DXBC] D3DPreprocess/D3DCreateBlob/D3DCompile unavailable; left stock");
                return;
            }

            const std::filesystem::path root = GetGameRootDirectory();
            if (root.empty())
            {
                finish();
                LogShimA(LogLevel::Warn, kComponent, "[DXBC] game root unknown; D3DCompile left stock");
                return;
            }
            const std::filesystem::path dir = root / L"shader_cache" / L"dxbc";
            std::error_code ec;
            std::filesystem::create_directories(dir, ec);
            if (!std::filesystem::is_directory(dir, ec))
            {
                finish();
                LogShimA(LogLevel::Warn, kComponent,
                    "[DXBC] cannot create %s; D3DCompile left stock", dir.string().c_str());
                return;
            }

            // Everything the hook reads is set once, before the patch exists.
            g_CacheDir = dir.wstring();
            g_Preprocess = preprocess;
            g_CreateBlob = createBlob;
            g_RealD3DCompile = reinterpret_cast<FnD3DCompile>(original);
            prepared = true;
        }

        void* patchOriginal = original;
        const IatPatch::Result result = IatPatch::PatchImport(
            renderer, "D3DCOMPILER_47.dll", "D3DCompile",
            reinterpret_cast<void*>(&HookedD3DCompile), &patchOriginal);
        if (result == IatPatch::Result::Faulted && ++faults < kMaxInstallFaults)
            return; // loader may still be snapping imports; retry on next trigger

        finish();
        if (result != IatPatch::Result::Patched)
        {
            LogShimA(LogLevel::Warn, kComponent,
                "[DXBC] could not patch D3DCompile import (result=%d); left stock",
                static_cast<int>(result));
            return;
        }
        LogShimA(LogLevel::Info, kComponent,
            "[DXBC] installed: D3DCompile cached under %s",
            std::filesystem::path(g_CacheDir).string().c_str());
    }
}
