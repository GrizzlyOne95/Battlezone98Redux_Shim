#pragma once

namespace BZROpenShim
{
    // Called only from OpenShim's existing patch worker, never from DllMain.
    bool InitializeBZLoader();
    void ShutdownBZLoader();
}
