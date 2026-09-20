#pragma once

namespace BZROpenShim::SdkProvider
{
    // Installs the built-in OpenShim provider table into the export bridge.
    // Pointer store only: no allocation, no loader work, safe from DllMain.
    // Disappears when the provider moves into plugins/openshim.dll.
    bool InstallBuiltIn();
}
