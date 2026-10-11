# Builds a -ContentOverride folder from a Campaign Reimagined checkout's
# working tree: every file changed or added since the staged CR build's commit,
# flattened to the Workshop layout (Scripts\x.lua -> x.lua), plus any extra
# files (e.g. a freshly built exu.dll). Nothing in the checkout, the staged
# content or the live install is modified.
#
#   powershell -ExecutionPolicy Bypass -File reverse_engineering\New-CRFlowOverride.ps1 `
#       -Name coop-comms -Extra C:\Users\iestu\Documents\GIT\ExtraUtilities\Release\exu.dll
#
# Then: Run-BZRCoopMission.ps1 ... -ContentOverride coopflow\overrides\<Name>
# Windows PowerShell 5.1.

param(
    [Parameter(Mandatory)][ValidatePattern('^[a-zA-Z0-9][a-zA-Z0-9_-]*$')][string]$Name,
    [string]$CRRepo = 'C:\Users\iestu\Documents\GIT\Campaign-Reimagined',
    # Staged CR build the harness copies first; its commit is the diff base.
    [string]$StagedContent = 'C:\Users\iestu\Documents\GIT\CR-release\Local\Workshop\content',
    [string]$Base = '',
    [string[]]$Extra = @(),
    # Repository paths whose files ship flat in the Workshop content. New map
    # previews and root descriptions must accompany their INI/BZN/VXT files.
    [string[]]$Folders = @('Scripts', 'Missions', 'ODF', 'Config', 'Assets/Graphics', '*.des')
)

$ErrorActionPreference = 'Stop'
if (-not $Base) {
    $Base = (& git -C (Split-Path $StagedContent -Parent | Split-Path -Parent | Split-Path -Parent) rev-parse HEAD).Trim()
}
$overrideRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot 'coopflow\overrides'))
$out = [IO.Path]::GetFullPath((Join-Path $overrideRoot $Name))
if (-not $out.StartsWith($overrideRoot + [IO.Path]::DirectorySeparatorChar, [StringComparison]::OrdinalIgnoreCase)) {
    throw 'Override output must stay inside coopflow\overrides.'
}
if (Test-Path -LiteralPath $out) { Remove-Item -LiteralPath $out -Recurse -Force }
$null = New-Item -ItemType Directory -Force -Path $out

$changed = @(& git -C $CRRepo diff --name-only $Base -- $Folders) +
           @(& git -C $CRRepo ls-files --others --exclude-standard -- $Folders)
$copied = New-Object System.Collections.ArrayList
foreach ($rel in ($changed | Where-Object { $_ } | Sort-Object -Unique)) {
    $src = Join-Path $CRRepo $rel
    if (-not (Test-Path -LiteralPath $src -PathType Leaf)) { continue }   # deleted
    $leaf = Split-Path $rel -Leaf
    if (-not (Test-Path -LiteralPath (Join-Path $StagedContent $leaf)) -and $rel -notlike 'Scripts/*') {
        Write-Warning "$rel has no counterpart in the staged content; copied anyway"
    }
    Copy-Item -LiteralPath $src -Destination (Join-Path $out $leaf) -Force
    [void]$copied.Add($rel)
}
foreach ($e in $Extra) {
    Copy-Item -LiteralPath $e -Destination $out -Force
    [void]$copied.Add($e)
}
$branch = (& git -C $CRRepo rev-parse --abbrev-ref HEAD).Trim()
$head = (& git -C $CRRepo rev-parse --short HEAD).Trim()
@("Built $(Get-Date -Format s) from $CRRepo ($branch $head + working tree) against $Base.", '') + $copied |
    Set-Content -LiteralPath (Join-Path $out 'OVERRIDE.txt')
Write-Host "[override] $($copied.Count) files -> $out"
$copied | ForEach-Object { Write-Host "  $_" }
