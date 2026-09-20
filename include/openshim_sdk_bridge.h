#pragma once

// OpenShim SDK forwarding bridge.
//
// docs/OPENSHIM_SDK_V2.md tells companion DLLs to find OpenShim with
// GetModuleHandleA("winmm.dll") + GetProcAddress. That makes the *module name*
// part of the published ABI, not just the symbol names, so winmm.dll has to
// keep exporting every OpenShim* name even once the implementations live in
// plugins/openshim.dll.
//
// So winmm.dll exports thunks. Each one reads a provider table that the module
// owning the runtime installs, and calls through. The thunks never load
// anything: a thunk running before the provider is installed returns the
// documented unavailable value instead of touching the loader. That keeps
// export calls off the loader lock entirely, which matters because an export
// can be called from any thread at any time, including during module load.

#include "BZROpenShim.h"
#include "render_effect_intent.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <cstddef>
#include <cstdint>

// The provider table. Append-only, on the same terms as the BZLoader plugin
// ABI: structSize says which fields are really there, fields are only ever
// added at the end, and a reader guards every access. A provider built before
// an export existed simply reports a smaller table.
struct OpenShimSdkProviderTable
{
    uint32_t structSize;

#define OPENSHIM_SDK_EXPORT(ret, cc, name, impl, params, args, unavail) \
    ret(cc* impl) params;
#include "openshim_sdk_exports.inc"
#undef OPENSHIM_SDK_EXPORT

    // Appended: the legacy v1 C++ API. winmm.dll exports these as mangled
    // C++ symbols and has done since long before SDK v2, so they keep
    // working -- but the values are runtime state, so they come from the
    // plugin like everything else here. Guarded by structSize as usual.
    uint32_t(__cdecl* legacyGetShimVersion)(void);
    int32_t(__cdecl* legacyIsCompatibleGameVersion)(void);
    int32_t(__cdecl* legacyIsPatchingComplete)(void);
    uint32_t(__cdecl* legacyGetAppliedPatchCount)(void);
    uint32_t(__cdecl* legacyGetBzrDistribution)(void);
};

#define OPENSHIM_SDK_TABLE_HAS(tablePtr, field) \
    ((tablePtr)->structSize >= \
         (uint32_t)(offsetof(OpenShimSdkProviderTable, field) + \
                    sizeof(((OpenShimSdkProviderTable*)0)->field)) && \
     (tablePtr)->field != nullptr)

namespace BZROpenShim::SdkBridge
{
    // Installed once by whichever module owns the OpenShim runtime. Storing
    // the pointer is all this does -- no allocation, no loader work -- so it
    // is safe to call from DllMain while the provider is still built into
    // winmm.dll.
    bool InstallProvider(const OpenShimSdkProviderTable* table);

    // The post-extraction path: one GetProcAddress against an already-loaded
    // plugins/openshim.dll for "OpenShimSdkProvider_GetTable", then install
    // what it returns. All 71 pointers arrive in that single call, so no
    // export ever resolves itself. Never calls LoadLibrary.
    bool InstallProviderFromModule(HMODULE pluginModule);

    const OpenShimSdkProviderTable* Provider();

    // Number of export calls that found no provider or no table slot. Stays
    // zero on a healthy install; non-zero means a consumer called across a
    // boundary that was not ready.
    uint64_t UnavailableCallCount();

    // Called by an export thunk that found nothing to forward to.
    void NoteUnavailableCall();
}

// Declarations for every OpenShim* name winmm.dll exports. These had no
// declarations at all while the bodies lived in winmm_proxy.cpp; the thunks in
// openshim_sdk_thunks.cpp define them, and anything that wants to call one
// in-process (the thunk tests, for instance) declares them from here. The five
// namespaced entries are also declared in BZROpenShim.h, identically.
#define OPENSHIM_SDK_EXPORT(ret, cc, name, impl, params, args, unavail)     extern "C" ret cc name params;
#define OPENSHIM_SDK_EXPORT_NS(ret, cc, name, impl, params, args, unavail)     namespace BZROpenShim { extern "C" BZRO_API ret cc name params; }
#include "openshim_sdk_exports.inc"
#undef OPENSHIM_SDK_EXPORT
#undef OPENSHIM_SDK_EXPORT_NS

// The entry point plugins/openshim.dll exports so the bootstrap can fetch the
// table in one call.
extern "C" __declspec(dllexport) const OpenShimSdkProviderTable* __cdecl
OpenShimSdkProvider_GetTable(void);
