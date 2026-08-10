<#
.SYNOPSIS
    Numeric RGB comparison of two terrain captures (or two capture directories).

.DESCRIPTION
    Reports different_pixels, max_channel_error, mean_absolute_error and RMSE
    for a pair of PNG captures, and optionally writes an amplified difference
    image so small errors are visible.

    This is a framebuffer comparison, not a proof of frame equality. Two runs of
    the game are two different frames: animation, particles, HUD, weather and
    time-of-day differences all count as "different pixels". Use -Region to
    restrict the comparison to terrain, and treat the metrics as evidence about
    that region only.

.PARAMETER Reference
    Reference PNG, or a directory of PNGs when -Candidate is also a directory.

.PARAMETER Candidate
    Candidate PNG or directory. Directory mode pairs files by name.

.PARAMETER OutputDirectory
    Where amplified difference images are written. Defaults to no image output.

.PARAMETER Amplify
    Multiplier applied to the absolute difference when writing the diff image.
    Default 8.

.PARAMETER Region
    Optional "left,top,width,height" crop applied to both images before
    comparison. Use this to exclude HUD and sky.

.PARAMETER Threshold
    A channel delta at or below this value is treated as identical when
    counting different_pixels. Default 0 (exact).
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)][string]$Reference,
    [Parameter(Mandatory = $true)][string]$Candidate,
    [string]$OutputDirectory = "",
    [int]$Amplify = 8,
    [string]$Region = "",
    [int]$Threshold = 0
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

Add-Type -AssemblyName System.Drawing

# The per-pixel loop runs over multi-megapixel captures; PowerShell is far too
# slow for that, so the inner loop is compiled.
Add-Type @"
using System;

public static class OpenShimCaptureDiff
{
    public struct Result
    {
        public long DifferentPixels;
        public int MaxChannelError;
        public double AbsoluteSum;
        public double SquaredSum;
        public long ChannelCount;
    }

    public static Result Compare(
        byte[] reference, byte[] candidate, byte[] diff,
        int stride, int width, int height, int amplify, int threshold)
    {
        Result result = new Result();
        for (int y = 0; y < height; y++)
        {
            int rowBase = y * stride;
            for (int x = 0; x < width; x++)
            {
                int offset = rowBase + (x * 4);
                bool pixelDiffers = false;
                for (int channel = 0; channel < 3; channel++)
                {
                    int delta = reference[offset + channel] - candidate[offset + channel];
                    if (delta < 0) delta = -delta;
                    if (delta > result.MaxChannelError) result.MaxChannelError = delta;
                    if (delta > threshold) pixelDiffers = true;
                    result.AbsoluteSum += delta;
                    result.SquaredSum += (double)delta * delta;
                    result.ChannelCount++;
                    if (diff != null)
                    {
                        int amplified = delta * amplify;
                        diff[offset + channel] = (byte)(amplified > 255 ? 255 : amplified);
                    }
                }
                if (diff != null) diff[offset + 3] = 255;
                if (pixelDiffers) result.DifferentPixels++;
            }
        }
        return result;
    }
}
"@

function Get-RegionRectangle {
    param([string]$Text, [int]$Width, [int]$Height)

    if (-not $Text) {
        return New-Object System.Drawing.Rectangle 0, 0, $Width, $Height
    }
    $parts = $Text.Split(",")
    if ($parts.Count -ne 4) {
        throw "Region must be 'left,top,width,height'"
    }
    $left = [int]$parts[0]
    $top = [int]$parts[1]
    $regionWidth = [int]$parts[2]
    $regionHeight = [int]$parts[3]
    if ($left -lt 0 -or $top -lt 0 -or
        ($left + $regionWidth) -gt $Width -or ($top + $regionHeight) -gt $Height) {
        throw "Region $Text does not fit inside ${Width}x${Height}"
    }
    return New-Object System.Drawing.Rectangle $left, $top, $regionWidth, $regionHeight
}

function Get-Pixels {
    param([System.Drawing.Bitmap]$Bitmap, [System.Drawing.Rectangle]$Rectangle)

    $data = $Bitmap.LockBits(
        $Rectangle,
        [System.Drawing.Imaging.ImageLockMode]::ReadOnly,
        [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
    try {
        $byteCount = [Math]::Abs($data.Stride) * $Rectangle.Height
        $buffer = New-Object byte[] $byteCount
        [System.Runtime.InteropServices.Marshal]::Copy($data.Scan0, $buffer, 0, $byteCount)
        return [pscustomobject]@{
            Bytes  = $buffer
            Stride = $data.Stride
            Width  = $Rectangle.Width
            Height = $Rectangle.Height
        }
    }
    finally {
        $Bitmap.UnlockBits($data)
    }
}

function Compare-CapturePair {
    param(
        [string]$ReferencePath,
        [string]$CandidatePath,
        [string]$DiffPath
    )

    $referenceImage = [System.Drawing.Bitmap]::FromFile($ReferencePath)
    try {
        $candidateImage = [System.Drawing.Bitmap]::FromFile($CandidatePath)
        try {
            if ($referenceImage.Width -ne $candidateImage.Width -or
                $referenceImage.Height -ne $candidateImage.Height) {
                throw ("Size mismatch: {0} is {1}x{2}, {3} is {4}x{5}" -f `
                    $ReferencePath, $referenceImage.Width, $referenceImage.Height, `
                    $CandidatePath, $candidateImage.Width, $candidateImage.Height)
            }

            $rectangle = Get-RegionRectangle -Text $Region `
                -Width $referenceImage.Width -Height $referenceImage.Height
            $referencePixels = Get-Pixels -Bitmap $referenceImage -Rectangle $rectangle
            $candidatePixels = Get-Pixels -Bitmap $candidateImage -Rectangle $rectangle

            $diffImage = $null
            $diffBuffer = $null
            if ($DiffPath) {
                $diffImage = New-Object System.Drawing.Bitmap $rectangle.Width, $rectangle.Height,
                    ([System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
                $diffBuffer = New-Object byte[] ($referencePixels.Stride * $rectangle.Height)
            }

            $stats = [OpenShimCaptureDiff]::Compare(
                $referencePixels.Bytes, $candidatePixels.Bytes, $diffBuffer,
                $referencePixels.Stride, $rectangle.Width, $rectangle.Height,
                $Amplify, $Threshold)
            $differentPixels = $stats.DifferentPixels
            $maxChannelError = $stats.MaxChannelError
            $absoluteSum = $stats.AbsoluteSum
            $squaredSum = $stats.SquaredSum
            $channelCount = $stats.ChannelCount

            if ($diffImage) {
                $diffData = $diffImage.LockBits(
                    (New-Object System.Drawing.Rectangle 0, 0, $rectangle.Width, $rectangle.Height),
                    [System.Drawing.Imaging.ImageLockMode]::WriteOnly,
                    [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
                try {
                    [System.Runtime.InteropServices.Marshal]::Copy(
                        $diffBuffer, 0, $diffData.Scan0, $diffBuffer.Length)
                }
                finally {
                    $diffImage.UnlockBits($diffData)
                }
                $diffImage.Save($DiffPath, [System.Drawing.Imaging.ImageFormat]::Png)
                $diffImage.Dispose()
            }

            $totalPixels = [long]$rectangle.Width * [long]$rectangle.Height
            return [ordered]@{
                reference          = $ReferencePath
                candidate          = $CandidatePath
                region             = ("{0},{1},{2},{3}" -f $rectangle.Left, $rectangle.Top, $rectangle.Width, $rectangle.Height)
                total_pixels       = $totalPixels
                different_pixels   = $differentPixels
                different_fraction = if ($totalPixels -gt 0) { [Math]::Round($differentPixels / $totalPixels, 6) } else { 0 }
                max_channel_error  = $maxChannelError
                mean_absolute_error = [Math]::Round($absoluteSum / [Math]::Max(1, $channelCount), 6)
                rmse               = [Math]::Round([Math]::Sqrt($squaredSum / [Math]::Max(1, $channelCount)), 6)
                threshold          = $Threshold
                diff_image         = $DiffPath
            }
        }
        finally { $candidateImage.Dispose() }
    }
    finally { $referenceImage.Dispose() }
}

if ($OutputDirectory -and -not (Test-Path $OutputDirectory)) {
    New-Item -ItemType Directory -Path $OutputDirectory -Force | Out-Null
}

$results = @()
if ((Test-Path $Reference -PathType Container) -and (Test-Path $Candidate -PathType Container)) {
    $referenceFiles = Get-ChildItem -LiteralPath $Reference -Filter *.png | Sort-Object Name
    foreach ($file in $referenceFiles) {
        $candidateFile = Join-Path $Candidate $file.Name
        if (-not (Test-Path $candidateFile)) { continue }
        $diffPath = ""
        if ($OutputDirectory) {
            $diffPath = Join-Path $OutputDirectory ("diff_" + $file.Name)
        }
        $results += [pscustomobject](Compare-CapturePair `
            -ReferencePath $file.FullName -CandidatePath $candidateFile -DiffPath $diffPath)
    }
}
else {
    $diffPath = ""
    if ($OutputDirectory) {
        $diffPath = Join-Path $OutputDirectory ("diff_" + (Split-Path -Leaf $Candidate))
    }
    $results += [pscustomobject](Compare-CapturePair `
        -ReferencePath $Reference -CandidatePath $Candidate -DiffPath $diffPath)
}

$results | Format-Table -AutoSize reference, candidate, different_pixels, different_fraction, max_channel_error, mean_absolute_error, rmse
$results | ConvertTo-Json -Depth 4
