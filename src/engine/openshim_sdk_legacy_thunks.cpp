// openshim_sdk_legacy_thunks.cpp
// BZR Open Shim - the legacy v1 C++ API, forwarded like everything else.
//
// GetShimVersion, IsCompatibleGameVersion, IsPatchingComplete,
// GetAppliedPatchCount and GetBzrDistribution are exported from winmm.dll as
// mangled C++ symbols and were part of the surface long before SDK v2, so
// they keep working after the runtime moved to plugins/openshim.dll. The
// values themselves are runtime state, so they arrive through the same
// provider table the OpenShim* thunks use.
//
// Initialize and Shutdown are NOT here: those are genuinely bootstrap-owned
// and live in dllmain.cpp.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "openshim_sdk_bridge.h"

#include <cstddef>

namespace BZROpenShim
{
    namespace
    {
        // An absent provider means the runtime has not loaded yet (or at
        // all). Report the documented "nothing yet" value and count it,
        // rather than faulting or inventing a plausible answer.
        template <typename Member>
        const OpenShimSdkProviderTable* TableFor(Member member, size_t fieldEnd)
        {
            const OpenShimSdkProviderTable* table = SdkBridge::Provider();
            if (table == nullptr || table->structSize < fieldEnd ||
                (table->*member) == nullptr)
            {
                SdkBridge::NoteUnavailableCall();
                return nullptr;
            }
            return table;
        }

#define OPENSHIM_LEGACY_FIELD_END(field)                      \
    (offsetof(OpenShimSdkProviderTable, field) +              \
     sizeof(((OpenShimSdkProviderTable*)0)->field))
    }

    BZRO_API uint32_t GetShimVersion()
    {
        const auto* t = TableFor(&OpenShimSdkProviderTable::legacyGetShimVersion,
                                 OPENSHIM_LEGACY_FIELD_END(legacyGetShimVersion));
        return t != nullptr ? t->legacyGetShimVersion() : 0u;
    }

    BZRO_API bool IsCompatibleGameVersion()
    {
        const auto* t = TableFor(&OpenShimSdkProviderTable::legacyIsCompatibleGameVersion,
                                 OPENSHIM_LEGACY_FIELD_END(legacyIsCompatibleGameVersion));
        return t != nullptr ? t->legacyIsCompatibleGameVersion() != 0 : false;
    }

    BZRO_API bool IsPatchingComplete()
    {
        const auto* t = TableFor(&OpenShimSdkProviderTable::legacyIsPatchingComplete,
                                 OPENSHIM_LEGACY_FIELD_END(legacyIsPatchingComplete));
        return t != nullptr ? t->legacyIsPatchingComplete() != 0 : false;
    }

    BZRO_API uint32_t GetAppliedPatchCount()
    {
        const auto* t = TableFor(&OpenShimSdkProviderTable::legacyGetAppliedPatchCount,
                                 OPENSHIM_LEGACY_FIELD_END(legacyGetAppliedPatchCount));
        return t != nullptr ? t->legacyGetAppliedPatchCount() : 0u;
    }

    BZRO_API BzrDistribution GetBzrDistribution()
    {
        const auto* t = TableFor(&OpenShimSdkProviderTable::legacyGetBzrDistribution,
                                 OPENSHIM_LEGACY_FIELD_END(legacyGetBzrDistribution));
        return t != nullptr
                   ? static_cast<BzrDistribution>(t->legacyGetBzrDistribution())
                   : BzrDistribution::Unknown;
    }

#undef OPENSHIM_LEGACY_FIELD_END
}
