<#
.SYNOPSIS
    Names the functions behind "module+0xRVA" crash addresses.

.DESCRIPTION
    Looks up the PDB that scripts\Deploy-OpenShim.ps1 archived for the DLL
    currently deployed (keyed by its SHA256), then runs llvm-symbolizer on
    each address. Pass addresses as written in openshim_crash*.log, for
    example "openshim.dll+0x0014DEC9", or bare RVAs with -Module.

.EXAMPLE
    .\Resolve-CrashAddress.ps1 openshim.dll+0x0014DEC9 openshim.dll+0x0020D05E

.EXAMPLE
    Select-String "$game\logs\openshim_crash.log" -Pattern 'openshim\.dll\+0x[0-9A-F]+' -AllMatches |
        ForEach-Object { $_.Matches.Value } | Sort-Object -Unique | .\Resolve-CrashAddress.ps1
#>
[CmdletBinding(PositionalBinding = $false)]
param(
    [Parameter(Mandatory, Position = 0, ValueFromPipeline, ValueFromRemainingArguments)]
    [string[]]$Address,
    [string]$GameDir = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [string]$Module = 'openshim.dll'
)
begin {
    $ErrorActionPreference = 'Stop'
    $symbolRoot = if ($env:BZR_SYMBOL_STORE) { $env:BZR_SYMBOL_STORE } else { Join-Path $env:LOCALAPPDATA 'BZRSymbols' }
    $deployed = @{
        'openshim.dll' = Join-Path $GameDir 'plugins\openshim.dll'
        'bzloader.dll' = Join-Path $GameDir 'bzloader.dll'
        'winmm.dll'    = Join-Path $GameDir 'winmm.dll'
    }
    $symbolizer = (Get-Command llvm-symbolizer -ErrorAction SilentlyContinue).Source
    $vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
    if (-not $symbolizer -and (Test-Path -LiteralPath $vswhere)) {
        $vs = & $vswhere -latest -property installationPath
        $candidate = Join-Path $vs 'VC\Tools\Llvm\bin\llvm-symbolizer.exe'
        if (Test-Path -LiteralPath $candidate) { $symbolizer = $candidate }
    }
    if (-not $symbolizer) { throw 'llvm-symbolizer not found (install the VS "C++ Clang tools" component).' }
    $all = [Collections.Generic.List[string]]::new()
}
process { foreach ($a in $Address) { $all.Add($a) } }
end {
    foreach ($group in $all | Group-Object { if ($_ -match '^(.+?)\+') { $Matches[1].ToLower() } else { $Module.ToLower() } }) {
        $dll = $deployed[$group.Name]
        if (-not $dll -or -not (Test-Path -LiteralPath $dll)) { Write-Warning "No deployed $($group.Name)"; continue }
        $hash = (Get-FileHash -Algorithm SHA256 -LiteralPath $dll).Hash
        $dir = Join-Path $symbolRoot ("{0}\{1}" -f [IO.Path]::GetFileNameWithoutExtension($group.Name), $hash)
        $archived = Join-Path $dir $group.Name
        if (-not (Test-Path -LiteralPath $archived)) {
            Write-Warning "No archived symbols for deployed $($group.Name) ($($hash.Substring(0,12))); it was not deployed with scripts\Deploy-OpenShim.ps1. Rebuild its commit to symbolize."
            continue
        }
        $commit = Get-Content -LiteralPath (Join-Path $dir 'commit.txt') -ErrorAction SilentlyContinue
        Write-Host "$($group.Name) $($hash.Substring(0,12)) commit $commit"
        foreach ($entry in $group.Group) {
            $rva = [Convert]::ToUInt32((($entry -split '\+')[-1] -replace '^0x', ''), 16)
            # Every BZR DLL links at the default 0x10000000 base.
            $va = '0x{0:X8}' -f (0x10000000 + $rva)
            # Native stderr must not become a terminating error under 'Stop' (Windows PowerShell 5.1).
            $ErrorActionPreference = 'Continue'
            $lines = & $symbolizer --obj=$archived --functions=linkage --inlining $va 2>&1 | ForEach-Object { "$_" } | Where-Object { $_ }
            $ErrorActionPreference = 'Stop'
            if ($lines -and $lines[0] -eq '??') { Write-Warning "$entry did not resolve: the PDB did not load or the address is outside the image." }
            Write-Host ("{0}`n    {1}" -f $entry, ($lines -join "`n    "))
        }
    }
}
