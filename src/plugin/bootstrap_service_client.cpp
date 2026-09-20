// bootstrap_service_client.cpp
// BZR Open Shim - the plugin's side of the bootstrap services.
//
// These definitions carry the same names the runtime already calls, so no
// call site had to change when the runtime moved into its own module. Each
// one forwards through the bootstrap API table. Only the plugin compiles
// this; winmm.dll has the real implementations.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "bootstrap_file_io.h"
#include "cli_multiparam_parser.h"
#include "openshim_bootstrap_api.h"
#include "openshim_plugin_bootstrap.h"
#include "openshim_sdk_bridge.h"

namespace BZROpenShim::BootstrapFileIo
{
    bool InstallProvider(const Provider* provider)
    {
        const OpenShimBootstrapApiV1* api = Plugin::BootstrapApi();
        if (api == nullptr || api->installFileIoProvider == nullptr) return false;
        return api->installFileIoProvider(provider) != 0;
    }

    bool PatchIATByFuncName(HMODULE targetModule, const char* funcName,
                            void* newFunc, void** oldFunc)
    {
        const OpenShimBootstrapApiV1* api = Plugin::BootstrapApi();
        if (api == nullptr || api->patchIatByFuncName == nullptr) return false;
        return api->patchIatByFuncName(targetModule, funcName, newFunc, oldFunc) != 0;
    }

    int PatchCreateFileHooksForModule(HMODULE targetModule)
    {
        const OpenShimBootstrapApiV1* api = Plugin::BootstrapApi();
        if (api == nullptr || api->patchCreateFileHooksForModule == nullptr) return 0;
        return api->patchCreateFileHooksForModule(targetModule);
    }

    // The runtime never reads the seam's own state; it only installs policy.
    const Provider* GetProvider() { return nullptr; }
}

namespace BZROpenShim::SdkBridge
{
    bool InstallProvider(const OpenShimSdkProviderTable* table)
    {
        const OpenShimBootstrapApiV1* api = Plugin::BootstrapApi();
        if (api == nullptr || api->installSdkProvider == nullptr) return false;
        return api->installSdkProvider(table) != 0;
    }
}

namespace BZROpenShim
{
    void VerifyCliMultiParameterOptionFix()
    {
        const OpenShimBootstrapApiV1* api = Plugin::BootstrapApi();
        if (api != nullptr && api->verifyCliMultiParameterOptionFix != nullptr)
            api->verifyCliMultiParameterOptionFix();
    }
}
