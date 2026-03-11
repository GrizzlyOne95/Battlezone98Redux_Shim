[CmdletBinding()]
param(
    [string]$SteamCmdExe = "C:\steamcmd\steamcmd.exe",
    [string]$WorkshopItemId = "3362534335",
    [int]$AppId = 301650,
    [string]$SteamUser = "anonymous",
    [string]$SteamPassword = "",
    [string]$SteamGuardCode = "",
    [string]$WorkspaceRoot = ""
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

$repoRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path
if ([string]::IsNullOrWhiteSpace($WorkspaceRoot)) {
    $WorkspaceRoot = Join-Path $repoRoot (Join-Path "reverse_engineering\workshop" $WorkshopItemId)
}

if (-not (Test-Path -LiteralPath $SteamCmdExe)) {
    throw "steamcmd.exe not found at '$SteamCmdExe'"
}

$steamCmdRoot = Split-Path -Parent $SteamCmdExe
$steamWorkshopPath = Join-Path $steamCmdRoot (Join-Path "steamapps\workshop\content\$AppId" $WorkshopItemId)

$args = @()
if ($SteamUser -eq "anonymous") {
    $args += @("+login", "anonymous")
}
else {
    if ([string]::IsNullOrWhiteSpace($SteamPassword)) {
        throw "SteamPassword is required when SteamUser is not anonymous."
    }

    $args += @("+login", $SteamUser, $SteamPassword)

    if (-not [string]::IsNullOrWhiteSpace($SteamGuardCode)) {
        $args += $SteamGuardCode
    }
}

$args += @("+workshop_download_item", $AppId, $WorkshopItemId, "+quit")

Write-Host "Downloading workshop item $WorkshopItemId (appid $AppId) with SteamCMD..."
& $SteamCmdExe @args

if ($LASTEXITCODE -ne 0) {
    throw "SteamCMD exited with code $LASTEXITCODE"
}

if (-not (Test-Path -LiteralPath $steamWorkshopPath)) {
    throw "Workshop item path was not created: $steamWorkshopPath"
}

$timestamp = Get-Date -Format "yyyyMMdd-HHmmss"
$snapshotRoot = Join-Path $WorkspaceRoot "snapshots"
$snapshotPath = Join-Path $snapshotRoot $timestamp
$latestPath = Join-Path $WorkspaceRoot "latest"
$manifestPath = Join-Path $snapshotPath "manifest.sha256.txt"

New-Item -ItemType Directory -Path $snapshotPath -Force | Out-Null
Copy-Item -Path (Join-Path $steamWorkshopPath "*") -Destination $snapshotPath -Recurse -Force

if (Test-Path -LiteralPath $latestPath) {
    Remove-Item -LiteralPath $latestPath -Recurse -Force
}

New-Item -ItemType Directory -Path $latestPath -Force | Out-Null
Copy-Item -Path (Join-Path $snapshotPath "*") -Destination $latestPath -Recurse -Force

$hashLines = Get-ChildItem -Path $snapshotPath -Recurse -File |
    Sort-Object FullName |
    ForEach-Object {
        $relative = $_.FullName.Substring($snapshotPath.Length + 1).Replace("\", "/")
        $hash = (Get-FileHash -Path $_.FullName -Algorithm SHA256).Hash.ToLowerInvariant()
        "$hash *$relative"
    }

$hashLines | Set-Content -Path $manifestPath -Encoding ASCII

Write-Host ""
Write-Host "Steam cache path : $steamWorkshopPath"
Write-Host "Snapshot path    : $snapshotPath"
Write-Host "Latest path      : $latestPath"
Write-Host "Manifest         : $manifestPath"
