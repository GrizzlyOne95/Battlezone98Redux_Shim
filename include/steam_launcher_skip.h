#pragma once

namespace BZROpenShim
{
    // Makes <game>\Launcher\d3d9.dll match [Steam] SkipRebellionLauncher.
    //
    // Writes or refreshes the proxy only on the Steam build, outside Wine, with
    // the toggle on and Launcher\BZLauncher.exe present. Otherwise (GOG
    // included) it removes the file, but only a copy OpenShim wrote. Never
    // replaces a d3d9.dll it did not write. A copy the running launcher holds
    // is renamed aside and deleted on a later start.
    //
    // Returns false when a write or removal it needed failed.
    bool SyncSteamLauncherProxy();
}
