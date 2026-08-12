<#
.SYNOPSIS
    Creates numbered PNG tiles and a Phase 3B terrain-HD manifest.

.DESCRIPTION
    OutputDirectory must be an Ogre resource directory used by the active mod.
    Every generated image has identical dimensions and a unique, asymmetric
    pattern so tile selection and orientation errors are obvious. ManifestPath
    may live anywhere; set TerrainHdManifest to its absolute path or copy it
    beside battlezone98redux.exe.

.EXAMPLE
    .\New-TerrainHdSmokeTiles.ps1 `
        -OutputDirectory 'C:\path\to\active-mod' `
        -ManifestPath 'C:\path\to\game\terrain_hd_tiles.json' `
        -Material MA_DETAIL_ATLAS -Force
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory)]
    [string]$OutputDirectory,

    [Parameter(Mandatory)]
    [string]$ManifestPath,

    [string]$Material = '*',

    [ValidateRange(1, 256)]
    [int]$SliceCount = 256,

    [ValidateRange(64, 2048)]
    [int]$TileSize = 256,

    [switch]$Force
)

$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing

$output = [System.IO.Path]::GetFullPath($OutputDirectory)
$manifest = [System.IO.Path]::GetFullPath($ManifestPath)
if (($TileSize -band ($TileSize - 1)) -ne 0) {
    throw 'TileSize must be a power of two.'
}

if (Test-Path -LiteralPath $output) {
    $existing = @(Get-ChildItem -LiteralPath $output -Filter 'openshim_hd_smoke_*.png')
    if ($existing.Count -ne 0 -and -not $Force) {
        throw "Smoke tiles already exist in '$output'. Pass -Force to replace them."
    }
} else {
    New-Item -ItemType Directory -Path $output | Out-Null
}

$manifestParent = Split-Path -Parent $manifest
if ($manifestParent -and -not (Test-Path -LiteralPath $manifestParent)) {
    New-Item -ItemType Directory -Path $manifestParent | Out-Null
}
if ((Test-Path -LiteralPath $manifest) -and -not $Force) {
    throw "Manifest '$manifest' already exists. Pass -Force to replace it."
}

function New-SmokeTile {
    param(
        [Parameter(Mandatory)][string]$Path,
        [Parameter(Mandatory)][int]$Index,
        [Parameter(Mandatory)][int]$Size,
        [switch]$Fallback
    )

    $bitmap = [System.Drawing.Bitmap]::new(
        $Size, $Size, [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
    $graphics = [System.Drawing.Graphics]::FromImage($bitmap)
    try {
        $graphics.SmoothingMode = [System.Drawing.Drawing2D.SmoothingMode]::AntiAlias
        if ($Fallback) {
            $base = [System.Drawing.Color]::FromArgb(255, 255, 0, 255)
        } else {
            $red = (53 * $Index + 37) % 224 + 24
            $green = (97 * $Index + 71) % 224 + 24
            $blue = (193 * $Index + 19) % 224 + 24
            $base = [System.Drawing.Color]::FromArgb(255, $red, $green, $blue)
        }
        $graphics.Clear($base)

        $gridPen = [System.Drawing.Pen]::new(
            [System.Drawing.Color]::FromArgb(150, 0, 0, 0),
            [Math]::Max(1, [int]($Size / 64)))
        $topBrush = [System.Drawing.SolidBrush]::new(
            [System.Drawing.Color]::FromArgb(230, 255, 64, 64))
        $leftBrush = [System.Drawing.SolidBrush]::new(
            [System.Drawing.Color]::FromArgb(230, 64, 255, 64))
        $cornerBrush = [System.Drawing.SolidBrush]::new(
            [System.Drawing.Color]::FromArgb(255, 255, 255, 255))
        $textBrush = [System.Drawing.SolidBrush]::new(
            [System.Drawing.Color]::FromArgb(255, 255, 255, 255))
        $shadowBrush = [System.Drawing.SolidBrush]::new(
            [System.Drawing.Color]::FromArgb(210, 0, 0, 0))
        $font = [System.Drawing.Font]::new(
            [System.Drawing.FontFamily]::GenericSansSerif,
            [Math]::Max(16.0, $Size * 0.22),
            [System.Drawing.FontStyle]::Bold,
            [System.Drawing.GraphicsUnit]::Pixel)
        try {
            $step = [Math]::Max(8, [int]($Size / 8))
            for ($position = $step; $position -lt $Size; $position += $step) {
                $graphics.DrawLine($gridPen, $position, 0, $position, $Size)
                $graphics.DrawLine($gridPen, 0, $position, $Size, $position)
            }
            $bar = [Math]::Max(4, [int]($Size / 20))
            $graphics.FillRectangle($topBrush, 0, 0, $Size, $bar)
            $graphics.FillRectangle($leftBrush, 0, 0, $bar, $Size)
            $corner = [Math]::Max(8, [int]($Size / 10))
            $graphics.FillEllipse($cornerBrush, $Size - $corner - 2, 2, $corner, $corner)

            $label = if ($Fallback) { 'FALLBACK' } else { '{0:D3}' -f $Index }
            $measured = $graphics.MeasureString($label, $font)
            $x = ($Size - $measured.Width) / 2
            $y = ($Size - $measured.Height) / 2
            $graphics.DrawString($label, $font, $shadowBrush, $x + 3, $y + 3)
            $graphics.DrawString($label, $font, $textBrush, $x, $y)
        }
        finally {
            $font.Dispose()
            $shadowBrush.Dispose()
            $textBrush.Dispose()
            $cornerBrush.Dispose()
            $leftBrush.Dispose()
            $topBrush.Dispose()
            $gridPen.Dispose()
        }
        $bitmap.Save($Path, [System.Drawing.Imaging.ImageFormat]::Png)
    }
    finally {
        $graphics.Dispose()
        $bitmap.Dispose()
    }
}

$fallbackName = 'openshim_hd_smoke_fallback.png'
New-SmokeTile -Path (Join-Path $output $fallbackName) `
    -Index 0 -Size $TileSize -Fallback

$tiles = [ordered]@{}
for ($index = 0; $index -lt $SliceCount; ++$index) {
    $name = 'openshim_hd_smoke_{0:D3}.png' -f $index
    New-SmokeTile -Path (Join-Path $output $name) `
        -Index $index -Size $TileSize
    $tiles["$index"] = $name
}

$binding = [ordered]@{
    sliceCount = $SliceCount
    fallback = $fallbackName
    tiles = $tiles
}
$materials = [ordered]@{}
$materials[$Material] = $binding
$document = [ordered]@{
    schema = 'bzr-openshim-terrain-hd-v1'
    materials = $materials
}
$document | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath $manifest -Encoding utf8

[pscustomobject]@{
    OutputDirectory = $output
    ManifestPath = $manifest
    Material = $Material
    SliceCount = $SliceCount
    TileSize = $TileSize
}
