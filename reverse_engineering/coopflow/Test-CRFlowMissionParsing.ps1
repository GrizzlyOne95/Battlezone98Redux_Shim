# Compile complete privately instrumented mission chunks without executing them.
# This catches Lua 5.1's 200-local limit, which parsing the probe alone misses.
param(
    [Parameter(Mandatory)][string]$CampaignScripts,
    [string]$Lua = 'lua5.1',
    [string[]]$Missions = @('misn02b','misn03','misn04','misn07','misn08','misn12','misn13','misn14','misn15')
)
$ErrorActionPreference = 'Stop'
. (Join-Path (Split-Path $PSScriptRoot) 'BZRCoopMission.ps1')
$fixtureRoot = Join-Path ([IO.Path]::GetTempPath()) ('crflow-parse-' + [guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $fixtureRoot | Out-Null
try {
    foreach ($mission in $Missions) {
        $source = Join-Path $CampaignScripts ($mission + '.lua')
        $chunk = (Get-Content -LiteralPath $source -Raw) + "`r`n" + (Get-CRFlowStub $mission)
        $fixture = Join-Path $fixtureRoot ($mission + '.lua')
        [IO.File]::WriteAllText($fixture, $chunk, [Text.UTF8Encoding]::new($false))
        & $Lua -e "assert(loadfile([[$fixture]]))"
        if ($LASTEXITCODE -ne 0) { throw "Instrumented $mission failed Lua 5.1 compilation" }
        Write-Host "${mission}: complete instrumented Lua 5.1 chunk compiles"
    }
} finally {
    $safeTemp = [IO.Path]::GetFullPath([IO.Path]::GetTempPath()).TrimEnd('\') + '\'
    if (-not ([IO.Path]::GetFullPath($fixtureRoot)).StartsWith($safeTemp, [StringComparison]::OrdinalIgnoreCase)) { throw 'Unexpected fixture cleanup path' }
    Remove-Item -LiteralPath $fixtureRoot -Recurse -Force
}
