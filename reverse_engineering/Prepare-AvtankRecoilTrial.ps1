<#
.SYNOPSIS
Creates a reversible loose avtank ODF override for the stock gatstab trial.
.DESCRIPTION
No model or weapon gameplay data is rewritten. AGR11BGA is avtank's world
barrel geometry, independently read with the shared Toolbox VDF reader.
Use -RestoreReceipt to remove this override or restore the original file.
The DLL trial additionally needs OPENSHIM_TRIAL_ODF_RECOIL=1 at launch.
#>
[CmdletBinding(DefaultParameterSetName = 'Prepare')]
param(
    [Parameter(ParameterSetName = 'Prepare')]
    [string]$GameRoot = 'C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux',
    [Parameter(ParameterSetName = 'Prepare')]
    [string]$SourceOdf,
    [Parameter(ParameterSetName = 'Prepare')]
    [switch]$Install,
    [Parameter(Mandatory, ParameterSetName = 'Restore')]
    [string]$RestoreReceipt
)
$ErrorActionPreference = 'Stop'
if ($PSCmdlet.ParameterSetName -eq 'Restore') {
    $receipt = Get-Content -LiteralPath $RestoreReceipt -Raw | ConvertFrom-Json
    $target = [IO.Path]::GetFullPath($receipt.target)
    if (Test-Path -LiteralPath $target) {
        if ((Get-FileHash -LiteralPath $target -Algorithm SHA256).Hash -ne $receipt.generatedHash) {
            throw "Refusing to overwrite a changed ODF: $target"
        }
    }
    if ($receipt.originalExisted -or $receipt.originalBase64) {
        [IO.File]::WriteAllBytes($target, [Convert]::FromBase64String($receipt.originalBase64))
    } elseif (Test-Path -LiteralPath $target) {
        Remove-Item -LiteralPath $target
    }
    Write-Output "Restored $target"
    return
}
$GameRoot = [IO.Path]::GetFullPath($GameRoot)
$target = Join-Path $GameRoot 'addon\avtank.odf'
if (-not $SourceOdf) {
    $SourceOdf = if (Test-Path -LiteralPath $target) { $target } else { Join-Path $GameRoot 'StockODFFiles\avtank.odf' }
}
$text = [IO.File]::ReadAllText($SourceOdf)
if ($text -notmatch '(?im)^weaponName1\s*=\s*"gatstab"') {
    throw 'The first weapon is not gatstab; refusing to replace a different tank configuration.'
}
if ($text -match '(?im)^recoil(?:Animation|Name|Distance|Return|PlaybackRate|Cockpit)1\s*=') {
    throw 'The source already authors slot-one recoil; preserve that configuration instead.'
}
$section = [regex]::Matches($text, '(?im)^\[CraftClass\]\s*\r?$')
if ($section.Count -ne 1) { throw 'Expected exactly one CraftClass section.' }
$settings = "`r`n// OpenShim opt-in avtank/gatstab recoil trial (slot 1).`r`nrecoilName1 = `"AGR11BGA`"`r`nrecoilDistance1 = 0.30`r`nrecoilReturn1 = 2.5`r`n"
$text = $text.Insert($section[0].Index + $section[0].Length, $settings)
$scratch = Join-Path ([IO.Path]::GetTempPath()) ('openshim-avtank-recoil-' + [guid]::NewGuid().ToString('N'))
[IO.Directory]::CreateDirectory($scratch) | Out-Null
$preview = Join-Path $scratch 'avtank.odf'
[IO.File]::WriteAllText($preview, $text, [Text.Encoding]::ASCII)
if (-not $Install) {
    Write-Output "Prepared $preview (game unchanged; pass -Install to install with a receipt)."
    return
}
$original = if (Test-Path -LiteralPath $target) { [Convert]::ToBase64String([IO.File]::ReadAllBytes($target)) } else { $null }
$receipt = [ordered]@{
    target = $target
    originalExisted = (Test-Path -LiteralPath $target)
    originalBase64 = $original
    generatedHash = (Get-FileHash -LiteralPath $preview -Algorithm SHA256).Hash
    source = [IO.Path]::GetFullPath($SourceOdf)
    barrel = 'AGR11BGA'
    weapon = 'gatstab'
}
$receiptPath = Join-Path $scratch 'receipt.json'
$receipt | ConvertTo-Json | Set-Content -LiteralPath $receiptPath -Encoding UTF8
[IO.Directory]::CreateDirectory((Split-Path -Parent $target)) | Out-Null
Copy-Item -LiteralPath $preview -Destination $target
Write-Output "Installed $target; restore receipt: $receiptPath"
