#pragma once

namespace BZROpenShim
{
    // Installs the BzE-compatible custom `classLabel = "pond"` support once
    // the settled Redux executable bytes are available. Safe to call from the
    // normal deferred-hook retry loop.
    void InstallPondClassLabelSupportIfPossible();
    bool IsPondClassLabelSupportInstalled();
}
