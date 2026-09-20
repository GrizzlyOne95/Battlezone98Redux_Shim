// Generated export thunks for winmm.dll. See include/openshim_sdk_bridge.h.
//
// Every OpenShim* name winmm.def exports is defined exactly once, here, and
// forwards through the installed provider table. Bodies are expanded from
// include/openshim_sdk_exports.inc so a signature cannot drift from the table.

#include "openshim_sdk_bridge.h"
#include "winmm_proxy.h"

namespace
{
    // Reports the first time a given export is called with no provider behind
    // it, then stays quiet: an unavailable export can be called every frame and
    // must not be able to flood the log.
    void NoteUnavailable(const char* exportName, bool& alreadyLogged);
}

#define OPENSHIM_SDK_THUNK_BODY(ret, name, impl, args, unavail)              \
    {                                                                        \
        const OpenShimSdkProviderTable* table =                              \
            BZROpenShim::SdkBridge::Provider();                              \
        if (!table || !OPENSHIM_SDK_TABLE_HAS(table, impl))                  \
        {                                                                    \
            static bool s_logged = false;                                    \
            NoteUnavailable(#name, s_logged);                                \
            return unavail;                                                  \
        }                                                                    \
        return table->impl args;                                             \
    }

#define OPENSHIM_SDK_EXPORT(ret, cc, name, impl, params, args, unavail)      \
    extern "C" ret cc name params                                            \
    OPENSHIM_SDK_THUNK_BODY(ret, name, impl, args, unavail)

#define OPENSHIM_SDK_EXPORT_NS(ret, cc, name, impl, params, args, unavail)   \
    namespace BZROpenShim {                                                  \
    extern "C" BZRO_API ret cc name params                                   \
    OPENSHIM_SDK_THUNK_BODY(ret, name, impl, args, unavail)                  \
    }

#include "openshim_sdk_exports.inc"

#undef OPENSHIM_SDK_EXPORT
#undef OPENSHIM_SDK_EXPORT_NS
#undef OPENSHIM_SDK_THUNK_BODY

#include "shim_log.h"

namespace
{
    void NoteUnavailable(const char* exportName, bool& alreadyLogged)
    {
        BZROpenShim::SdkBridge::NoteUnavailableCall();
        if (alreadyLogged) return;
        alreadyLogged = true;
        BZROpenShim::LogShimA(
            BZROpenShim::LogLevel::Warn, "sdkbridge",
            "%s was called before the OpenShim provider was installed; "
            "returning the documented unavailable value",
            exportName ? exportName : "<null>");
    }
}
