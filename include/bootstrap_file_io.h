// bootstrap_file_io.h
// BZR Open Shim - the permanent bootstrap file-I/O seam.
//
// The main executable's CreateFileA/W IAT entries point at the wrappers here
// for the whole life of the process. That is deliberate and permanent: the
// entries are patched once, before the CRT runs, and nothing ever re-points
// them. What changes over the process lifetime is not the hook, it is the
// *policy* behind it.
//
// Before OpenShim is loaded the wrappers still have a job to do -- the game
// creates BZLogger.txt and its Ogre log almost immediately, and those have to
// land in logs\. So the wrappers route the stock logs, call the real Win32
// function, preserve GetLastError, and do nothing else. Everything richer
// (terrain-atlas routing, TRN tracking, BZN source tracking and load tracing,
// shader-cache priming, UI-perf markers) is runtime policy that OpenShim
// supplies later by installing a Provider.
//
// This Provider is an internal seam between the bootstrap and OpenShim. It is
// intentionally NOT part of the BZLoader plugin ABI: third-party plugins have
// no business interposing on the game's file I/O yet, and nothing here is
// covered by the ABI v1 compatibility promise.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <cstdint>

namespace BZROpenShim::BootstrapFileIo
{
    // Runtime policy for the file-I/O seam. Append-only, guarded by
    // structSize, on the same terms as the other tables in this codebase.
    //
    // Every callback may be invoked on any thread, re-entrantly with respect
    // to unrelated file activity, and from the very first file the process
    // opens. A provider must not assume the game is initialised.
    struct Provider
    {
        uint32_t structSize;

        // Optional path rewrite, applied *after* the bootstrap's own log
        // routing, so the provider sees the path that would otherwise be
        // opened. Return nullptr to leave it alone, or a pointer that stays
        // valid until this thread calls back in again -- a thread_local
        // buffer on the provider side. Returning storage with any shorter
        // lifetime is a use-after-free.
        const wchar_t*(__cdecl* routePathW)(
            const wchar_t* path, DWORD desiredAccess, DWORD creationDisposition);
        const char*(__cdecl* routePathA)(
            const char* path, DWORD desiredAccess, DWORD creationDisposition);

        // Post-open notification, only on a successful open.
        //
        // `requested` is the name the caller passed; `routed` is what was
        // actually opened. Both are needed and they are not interchangeable:
        // the *.program shader-cache trigger and TRN write tracking key off
        // the caller's original name, while editor-source detection and BZN
        // load tracing follow the path that was really opened.
        void(__cdecl* onOpenedW)(
            HANDLE handle, const wchar_t* requested, const wchar_t* routed,
            DWORD desiredAccess, DWORD creationDisposition);
        void(__cdecl* onOpenedA)(
            HANDLE handle, const char* requested, const char* routed,
            DWORD desiredAccess, DWORD creationDisposition);
    };

    // Installs the runtime policy. A pointer store: no allocation, no loader
    // work, safe from DllMain. The table must outlive the process, because
    // the wrappers keep calling through it and there is no uninstall.
    bool InstallProvider(const Provider* provider);

    // Whatever is installed right now, or nullptr. A caller that is going to
    // use several fields must load this once and keep the result: the pointer
    // can change underneath a call that reads it twice.
    const Provider* GetProvider();

    // Installs the CreateFileA/W wrappers into a module's import table and
    // captures the originals. Idempotent: the real pointers are captured on
    // the first module and reused, so patching the CRT modules later does not
    // lose them. Returns how many entries were rewritten.
    int PatchCreateFileHooksForModule(HMODULE module);

    // The self-contained import-table patcher. Lives here because the seam
    // needs it before anything else exists, and is shared so the runtime does
    // not carry a second copy.
    bool PatchIATByFuncName(
        HMODULE targetModule, const char* funcName, void* newFunc, void** oldFunc);

    // Installs the main-executable CreateFile wrappers and rewrites the five
    // immediate log-path operands the statically linked runtime uses to
    // bypass the imports. Safe during process attach, before the game opens
    // its stock logger files.
    void ApplyEarlyGameLogHooks();
}
