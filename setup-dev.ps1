<#
.SYNOPSIS
    One-time developer environment setup for BZR OpenShim.

.DESCRIPTION
    Performs a sparse checkout of the upstream Ogre 1.10.0 headers used as
    compile-time reference declarations by OpenShim renderer/Ogre work.

    The headers are placed under:
        third_party\ogre-1.10.0-bzr\_work

    OpenShim does NOT build or load a replacement OgreMain.dll. Runtime code
    continues to operate against Battlezone 98 Redux's already-loaded
    OgreMain.dll through validated exports, module-relative offsets, and hooks.

    The shipped BZR Ogre binary is known to contain ABI drift from pristine
    upstream Ogre 1.10.0. Treat these headers as a source/API reference, not as
    proof that an arbitrary upstream class layout or exported signature is safe.

.NOTES
    - The _work/ directory is gitignored.
    - The pinned commit matches the Ogre 1.10.0 source reference already used
      by ExtraUtilities.
    - Run this script again safely; it is idempotent once the headers exist.
#>

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

$ogreCommit     = "f1f1937fd6cbad05a4b9170b9882da91f42f53a5"
$ogreDir        = Join-Path $PSScriptRoot "third_party\ogre-1.10.0-bzr\_work"
$headerSentinel = Join-Path $ogreDir "OgreMain\include\OgreEntity.h"

if (Test-Path $headerSentinel) {
    Write-Host "Ogre reference headers already present at: $ogreDir"
    Write-Host "Setup complete."
    exit 0
}

Write-Host "Fetching Ogre 1.10.0 reference headers (sparse checkout)..."
Write-Host "Pinned commit: $ogreCommit"
Write-Host "Target: $ogreDir"

if (-not (Get-Command git -ErrorAction SilentlyContinue)) {
    throw "git.exe was not found on PATH"
}

if (-not (Test-Path $ogreDir)) {
    New-Item -ItemType Directory -Path $ogreDir | Out-Null
}

if (-not (Test-Path (Join-Path $ogreDir ".git"))) {
    git -C $ogreDir init
    if ($LASTEXITCODE -ne 0) { throw "git init failed" }

    git -C $ogreDir remote add origin https://github.com/OGRECave/ogre.git
    if ($LASTEXITCODE -ne 0) { throw "git remote add failed" }
}

git -C $ogreDir sparse-checkout init --cone
if ($LASTEXITCODE -ne 0) { throw "sparse-checkout init failed" }

git -C $ogreDir sparse-checkout set OgreMain/include Components/Overlay/include
if ($LASTEXITCODE -ne 0) { throw "sparse-checkout set failed" }

git -C $ogreDir fetch --filter=blob:none --depth 1 origin $ogreCommit
if ($LASTEXITCODE -ne 0) { throw "git fetch failed" }

git -C $ogreDir checkout $ogreCommit
if ($LASTEXITCODE -ne 0) { throw "git checkout failed" }

Write-Host ""
Write-Host "Done. Ogre reference headers are ready at: $ogreDir"
Write-Host "Open BZROpenShim.sln and build Release | Win32."
