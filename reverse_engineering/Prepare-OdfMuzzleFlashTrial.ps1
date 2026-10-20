<#
.SYNOPSIS
Prepares weapon ODF mesh/render effects; optionally installs a reversible override.
.DESCRIPTION
Requires mesh/material or render definitions supplied by the mod. Defaults to the stock
gatstab weapon. Preview is the default; -Install writes addon/<weapon>.odf.
#>
[CmdletBinding(DefaultParameterSetName = 'Prepare')]
param(
    [Parameter(ParameterSetName = 'Prepare')]
    [string]$GameRoot = 'C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux',
    [Parameter(ParameterSetName = 'Prepare')]
    [ValidatePattern('^[A-Za-z0-9_]{1,8}$')][string]$Weapon = 'gatstab',
    [Parameter(ParameterSetName = 'Prepare')]
    [ValidateLength(1,127)][string]$Mesh = '',
    [Parameter(ParameterSetName = 'Prepare')][string]$Material = '',
    [Parameter(ParameterSetName = 'Prepare')][float]$Duration = 0.08,
    [Parameter(ParameterSetName = 'Prepare')][float]$Scale = 1,
    [Parameter(ParameterSetName = 'Prepare')][float]$EndScale = 1,
    [Parameter(ParameterSetName = 'Prepare')][float[]]$Offset = @(0,0,0),
    [Parameter(ParameterSetName = 'Prepare')][float]$Roll = 0,
    [Parameter(ParameterSetName = 'Prepare')][string]$MuzzleRender = '',
    [Parameter(ParameterSetName = 'Prepare')][float]$MuzzleRenderDuration = 0.08,
    [Parameter(ParameterSetName = 'Prepare')][float[]]$MuzzleRenderOffset,
    [Parameter(ParameterSetName = 'Prepare')][string]$SourceOdf,
    [Parameter(ParameterSetName = 'Prepare')][switch]$Install,
    [Parameter(Mandatory, ParameterSetName = 'Restore')][string]$RestoreReceipt
)
$ErrorActionPreference = 'Stop'
if ($PSCmdlet.ParameterSetName -eq 'Restore') {
    # Same receipt contract as the recoil helper, including hash-safe restore.
    & (Join-Path $PSScriptRoot 'Prepare-AvtankRecoilTrial.ps1') -RestoreReceipt $RestoreReceipt
    return
}
foreach ($name in @($Mesh,$Material)) {
    if ($name.Length -gt 127 -or $name -match '[^\x20-\x7e]|"') { throw 'Resource names must be printable ASCII without quotes, at most 127 characters.' }
}
if (-not $Mesh -and -not $MuzzleRender) { throw 'Supply -Mesh, -MuzzleRender, or both; no generic effects are generated.' }
if ($Offset.Count -ne 3) { throw 'Offset requires right/up/forward values.' }
if (-not $MuzzleRenderOffset) { $MuzzleRenderOffset = $Offset }
if ($MuzzleRenderOffset.Count -ne 3) { throw 'MuzzleRenderOffset requires right/up/forward values.' }
if ($MuzzleRender.Length -gt 63 -or $MuzzleRender -match '[^\x21-\x7e]|"') { throw 'MuzzleRender requires a printable effect name without spaces/quotes, at most 63 characters.' }
$numbers = @($Duration,$Scale,$EndScale,$Roll,$MuzzleRenderDuration) + $Offset + $MuzzleRenderOffset
foreach ($number in $numbers) {
    if ([float]::IsNaN($number) -or [float]::IsInfinity($number)) { throw 'Flash settings must be finite.' }
}
if ($Duration -lt 0.005 -or $Duration -gt 5 -or $Scale -lt 0 -or $Scale -gt 100 -or
    $EndScale -lt 0 -or $EndScale -gt 100 -or ($Scale -eq 0 -and $EndScale -eq 0) -or [Math]::Abs($Roll) -gt 360 -or
    @($Offset | Where-Object { [Math]::Abs($_) -gt 20 }).Count -or
    $MuzzleRenderDuration -lt 0.005 -or $MuzzleRenderDuration -gt 5 -or
    @($MuzzleRenderOffset | Where-Object { [Math]::Abs($_) -gt 20 }).Count) { throw 'Flash/render values exceed the documented bounds.' }
$GameRoot = [IO.Path]::GetFullPath($GameRoot)
$target = Join-Path $GameRoot "addon\$Weapon.odf"
if (-not $SourceOdf) {
    $SourceOdf = if (Test-Path -LiteralPath $target) { $target } else { Join-Path $GameRoot "StockODFFiles\$Weapon.odf" }
}
$sourceBytes = [IO.File]::ReadAllBytes($SourceOdf)
# Latin-1 is byte-preserving for unmarked CP1252/UTF8 ODFs. Honor Unicode
# BOMs so an existing mod's labels/format are not damaged by this insertion.
$sourceEncoding = [Text.Encoding]::GetEncoding(28591)
if ($sourceBytes.Length -ge 3 -and $sourceBytes[0] -eq 0xef -and $sourceBytes[1] -eq 0xbb -and $sourceBytes[2] -eq 0xbf) {
    $sourceEncoding = New-Object Text.UTF8Encoding($true)
} elseif ($sourceBytes.Length -ge 2 -and $sourceBytes[0] -eq 0xff -and $sourceBytes[1] -eq 0xfe) {
    $sourceEncoding = [Text.Encoding]::Unicode
} elseif ($sourceBytes.Length -ge 2 -and $sourceBytes[0] -eq 0xfe -and $sourceBytes[1] -eq 0xff) {
    $sourceEncoding = [Text.Encoding]::BigEndianUnicode
}
$text = [IO.File]::ReadAllText($SourceOdf, $sourceEncoding)
if ($text -match '(?im)^[ \t]*(?:flash(?:Mesh|Material|Duration|Scale|EndScale|Offset|Roll)|muzzleRender(?:Duration|Offset)?)\s*=') {
    throw 'The source already authors flash settings; edit those values rather than adding duplicate keys.'
}
$section = [regex]::Matches($text, '(?im)^\[WeaponClass\]\s*\r?$')
if ($section.Count -ne 1) { throw 'Expected exactly one WeaponClass section.' }
$culture = [Globalization.CultureInfo]::InvariantCulture
function Format-FlashNumber([float]$value) { $value.ToString('R',$culture) }
$offsetText = ($Offset | ForEach-Object { Format-FlashNumber $_ }) -join ' '
$settings = "`r`n`r`n// OpenShim opt-in muzzle effects. Resources are supplied by this mod.`r`n"
if ($Mesh) {
    $settings += @"
flashMesh = "$Mesh"
flashMaterial = "$Material"
flashDuration = $(Format-FlashNumber $Duration)
flashScale = $(Format-FlashNumber $Scale)
flashEndScale = $(Format-FlashNumber $EndScale)
flashOffset = "$offsetText"
flashRoll = $(Format-FlashNumber $Roll)

"@
}
if ($MuzzleRender) {
    $renderOffsetText = ($MuzzleRenderOffset | ForEach-Object { Format-FlashNumber $_ }) -join ' '
    $settings += @"
muzzleRender = "$MuzzleRender"
muzzleRenderDuration = $(Format-FlashNumber $MuzzleRenderDuration)
muzzleRenderOffset = "$renderOffsetText"

"@
}
$text = $text.Insert($section[0].Index + $section[0].Length, $settings)
$scratch = Join-Path ([IO.Path]::GetTempPath()) ('openshim-muzzle-flash-' + [guid]::NewGuid().ToString('N'))
[IO.Directory]::CreateDirectory($scratch) | Out-Null
$preview = Join-Path $scratch "$Weapon.odf"
[IO.File]::WriteAllText($preview, $text, $sourceEncoding)
if (-not $Install) { Write-Output "Prepared $preview (game unchanged)."; return }
$existed = Test-Path -LiteralPath $target
$original = if ($existed) { [Convert]::ToBase64String([IO.File]::ReadAllBytes($target)) } else { $null }
$receiptPath = Join-Path $scratch 'receipt.json'
[ordered]@{
    target = $target; originalExisted = $existed; originalBase64 = $original
    generatedHash = (Get-FileHash -LiteralPath $preview -Algorithm SHA256).Hash
    source = [IO.Path]::GetFullPath($SourceOdf)
} | ConvertTo-Json | Set-Content -LiteralPath $receiptPath -Encoding UTF8
[IO.Directory]::CreateDirectory((Split-Path -Parent $target)) | Out-Null
Copy-Item -LiteralPath $preview -Destination $target
Write-Output "Installed $target; restore receipt: $receiptPath"
