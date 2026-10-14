#pragma once

#include <string>

// Engine-independent halves of the automatic update staging: the go/no-go
// decision and the text handed to the "Restart now" watcher. The Win32 side
// lives in openshim_updater.cpp.
namespace BZROpenShim
{
    struct AutoStageInputs
    {
        bool configEnabled = true;       // [Updater] AutoStage (default on)
        bool steamBuild = false;         // only Steam has the Workshop manager
        bool inNetworkSession = false;   // never touch the network mid-match
        bool alreadyRanThisProcess = false;
    };

    inline bool ShouldAutoStageUpdate(const AutoStageInputs& in)
    {
        return in.configEnabled && in.steamBuild && !in.inNetworkSession &&
            !in.alreadyRanThisProcess;
    }

    // "OpenShim <version> is ready and will install when you quit the game."
    std::string FormatAutoStageNotice(const std::string& version);

    // PowerShell script for the detached restart watcher: wait up to
    // timeoutSeconds for `statusFile` to contain state=complete, then start
    // steam://rungameid/<appId>; do nothing on state=failed or timeout.
    // `statusFile` must be an absolute path without control characters and
    // `appId` must be decimal digits, otherwise false is returned and the
    // script is left empty. The path is embedded as a single-quoted
    // PowerShell literal (every quote character doubled), so it cannot end
    // the literal and inject code.
    bool BuildUpdateRestartWatcherScript(const std::wstring& statusFile,
                                         const std::wstring& appId,
                                         unsigned timeoutSeconds,
                                         std::wstring& script);
}
