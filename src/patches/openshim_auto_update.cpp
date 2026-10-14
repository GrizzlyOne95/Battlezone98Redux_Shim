#include "openshim_auto_update.h"

namespace BZROpenShim
{
    namespace
    {
        // PowerShell treats the typographic single quotes as quote
        // characters too, so a path containing one would end the literal.
        bool IsPowerShellSingleQuote(wchar_t ch)
        {
            return ch == L'\'' || ch == 0x2018 || ch == 0x2019 ||
                ch == 0x201A || ch == 0x201B;
        }

        bool IsAbsoluteWindowsPath(const std::wstring& path)
        {
            if (path.size() >= 3 && path[1] == L':' &&
                (path[2] == L'\\' || path[2] == L'/') &&
                ((path[0] >= L'A' && path[0] <= L'Z') || (path[0] >= L'a' && path[0] <= L'z')))
                return true;
            return path.size() >= 3 && path[0] == L'\\' && path[1] == L'\\' &&
                path[2] != L'\\';
        }
    }

    std::string FormatAutoStageNotice(const std::string& version)
    {
        return "OpenShim " + version + " is ready and will install when you quit the game.";
    }

    bool BuildUpdateRestartWatcherScript(const std::wstring& statusFile,
                                         const std::wstring& appId,
                                         unsigned timeoutSeconds,
                                         std::wstring& script)
    {
        script.clear();
        if (!IsAbsoluteWindowsPath(statusFile) || appId.empty() || timeoutSeconds == 0)
            return false;
        for (const wchar_t ch : appId)
        {
            if (ch < L'0' || ch > L'9')
                return false;
        }
        std::wstring literal;
        for (const wchar_t ch : statusFile)
        {
            if (ch < 0x20 || ch == 0x7F)
                return false;
            literal.push_back(ch);
            if (IsPowerShellSingleQuote(ch))
                literal.push_back(ch);
        }

        script = L"$p='" + literal + L"';"
            L"$e=(Get-Date).AddSeconds(" + std::to_wstring(timeoutSeconds) + L");"
            L"while((Get-Date) -lt $e){"
            L"$t='';"
            L"if(Test-Path -LiteralPath $p){"
            L"$t=[string](Get-Content -LiteralPath $p -Raw -ErrorAction SilentlyContinue)};"
            L"if($t -match '(?m)^state=complete\\s*$'){"
            L"Start-Process 'steam://rungameid/" + appId + L"';break};"
            L"if($t -match '(?m)^state=failed\\s*$'){break};"
            L"Start-Sleep -Milliseconds 500}";
        return true;
    }
}
