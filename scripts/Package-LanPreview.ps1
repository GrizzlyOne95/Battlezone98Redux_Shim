<#
.SYNOPSIS
Package the built OpenShim DLL set, resources and a verified LAN helper.
.DESCRIPTION
Creates a local preview overlay only. It neither deploys to a game install nor
publishes a release. The archive omits active INIs to preserve player settings.
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory)][string]$HelperDirectory,
    [string]$OutputDirectory = (Join-Path (Split-Path -Parent $PSScriptRoot) 'build\deliverables')
)
$ErrorActionPreference = 'Stop'
$repo = Split-Path -Parent $PSScriptRoot
$revision = (& git -C $repo rev-parse HEAD).Trim()
if ($LASTEXITCODE -or $revision -notmatch '^[0-9a-f]{40}$') { throw 'Cannot determine source revision.' }
$dirty = (& git -C $repo status --porcelain --untracked-files=normal)
if ($LASTEXITCODE -or $dirty) { throw 'Commit the preview source before packaging.' }
$name = 'OpenShim-LAN-' + $revision.Substring(0, 9) + '-' + (Get-Date -Format 'yyyyMMdd-HHmmss')
$output = [IO.Path]::GetFullPath($OutputDirectory)
$payload = Join-Path $output $name
if (Test-Path -LiteralPath $payload) { throw "Preview folder already exists: $payload" }
New-Item -ItemType Directory -Path $payload -Force | Out-Null
& (Join-Path $PSScriptRoot 'Deploy-OpenShim.ps1') -GameDir $payload -Configuration Release
& (Join-Path $PSScriptRoot 'Stage-LanHelper.ps1') -HelperDirectory $HelperDirectory -DestinationRoot $payload
Copy-Item -LiteralPath (Join-Path $repo 'openshim.ini.example') -Destination $payload
Copy-Item -LiteralPath (Join-Path $repo 'LICENSE') -Destination $payload
Copy-Item -LiteralPath (Join-Path $repo 'Docs\LAN_MULTIPLAYER.md') -Destination $payload
@'
OpenShim LAN development preview

Back up your current OpenShim DLLs and scripts/patches.json before trying this
overlay. Extract its complete folder layout into a Battlezone 98 Redux install;
keep your existing openshim.ini and net.ini. This archive includes only the
example INI, so it does not replace active preferences.

Multiplayer setup > LAN... > Host LAN, then Continue and Create Game in the
normal lobby. Other players choose LAN... > Refresh, select the host, Continue,
then join its game. Use address is the manual IP fallback. Steam/Galaxy sign-in
and matching game/mod versions are still required. Allow the helper and game
through the private-network firewall if prompted. Stop Host disconnects users.

This is a preview. Native menu, physical two-PC gameplay and Steam/GOG/
Proton/Wine acceptance are not established. It has not been merged or released.
See LAN_MULTIPLAYER.md for the implementation, tests and remaining gates.

preview_manifest.json identifies both source revisions and every payload hash.
'@ | Set-Content -LiteralPath (Join-Path $payload 'README-LAN.txt') -Encoding utf8
$files = @{}
Get-ChildItem -LiteralPath $payload -File -Recurse | ForEach-Object {
    $relative = [IO.Path]::GetRelativePath($payload, $_.FullName).Replace('\', '/')
    $files[$relative] = (Get-FileHash -LiteralPath $_.FullName -Algorithm SHA256).Hash.ToLowerInvariant()
}
$helper = Get-Content -LiteralPath (Join-Path $payload 'tools\lan\manifest.json') -Raw | ConvertFrom-Json
[ordered]@{
    format = 1; sourceRevision = $revision; helperRevision = $helper.revision
    status = 'development-preview'; nativeGameplayValidated = $false; sha256 = $files
} | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath (Join-Path $payload 'preview_manifest.json') -Encoding utf8
$zip = Join-Path $output ($name + '.zip')
Add-Type -AssemblyName System.IO.Compression.FileSystem
[IO.Compression.ZipFile]::CreateFromDirectory($payload, $zip)
Write-Host "Preview: $zip"
# Deploy's optional mod-shadow advisory returns 2 for a staging tree without
# a game/mod. Reaching this point means every payload check and zip succeeded.
$global:LASTEXITCODE = 0
