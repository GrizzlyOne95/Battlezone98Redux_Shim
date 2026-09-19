// Pure OpenShim Enhanced resource bootstrap policy. No Win32, no Ogre, no
// process state: deterministic functions of their inputs for unit tests.

#include "enhanced_resource_bootstrap.h"

#include <cstdio>

namespace BZROpenShim::RenderProfiles::EnhancedBootstrap
{
    const char* BootstrapStateName(BootstrapState state) noexcept
    {
        switch (state)
        {
        case BootstrapState::NotAttempted: return "not-attempted";
        case BootstrapState::Attempting: return "attempting";
        case BootstrapState::Ready: return "ready";
        case BootstrapState::Unavailable: return "unavailable";
        }
        return "unknown";
    }

    BootstrapState DecideBootstrapState(
        const BootstrapObservations& observations) noexcept
    {
        if (observations.probeResolvedDirectory && observations.ogreApiResolved &&
            observations.groupRegistered && observations.canonicalProgramResolved)
        {
            return BootstrapState::Ready;
        }
        return BootstrapState::Unavailable;
    }

    bool ShouldAttemptBootstrap(BootstrapState current) noexcept
    {
        return current == BootstrapState::NotAttempted;
    }

    bool IsEnhancedCapabilityAvailable(BootstrapState current) noexcept
    {
        return current == BootstrapState::Ready;
    }

    const char* ResourceGroupName() noexcept
    {
        return "OpenShimEnhanced";
    }

    const char* ResourceLocationType() noexcept
    {
        return "FileSystem";
    }

    const char* CanonicalProbeProgram() noexcept
    {
        // Declared by openshim_enhanced_base.program, present in every
        // shipped payload revision, and not an EN/IBL variant -- so this
        // verifies the base payload parsed rather than one optional family.
        return "OSE_BaseHighNoShadow_fragment";
    }

    std::string FormatBootstrapReadyLog(std::string_view resourceDir)
    {
        char buf[768] = {};
        std::snprintf(buf, sizeof(buf),
                      "[OSE] enhanced resource group ready group=%s type=%s "
                      "probe=%s dir=%.400s",
                      ResourceGroupName(), ResourceLocationType(),
                      CanonicalProbeProgram(),
                      resourceDir.empty()
                          ? "<unresolved>"
                          : std::string(resourceDir).c_str());
        return std::string(buf);
    }

    std::string FormatBootstrapFailedLog(
        const BootstrapObservations& observations, std::string_view detail)
    {
        char buf[768] = {};
        std::snprintf(buf, sizeof(buf),
                      "[OSE] enhanced resource group unavailable probe=%s abi=%s "
                      "group=%s program=%s; Enhanced/OSE synthesis disabled%s%.300s",
                      observations.probeResolvedDirectory ? "ok" : "MISSING",
                      observations.ogreApiResolved ? "ok" : "MISSING",
                      observations.groupRegistered ? "ok" : "MISSING",
                      observations.canonicalProgramResolved ? "ok" : "MISSING",
                      detail.empty() ? "" : " -- ",
                      detail.empty() ? "" : std::string(detail).c_str());
        return std::string(buf);
    }
} // namespace BZROpenShim::RenderProfiles::EnhancedBootstrap
