$src = Join-Path $PSScriptRoot "..\bin\Release\winmm.dll"
$dst = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\winmm.dll"
Copy-Item -LiteralPath $src -Destination $dst -Force
$srcPdb = Join-Path $PSScriptRoot "..\bin\Release\winmm.pdb"
$dstPdb = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\winmm.pdb"
if (Test-Path -LiteralPath $srcPdb) { Copy-Item -LiteralPath $srcPdb -Destination $dstPdb -Force -ErrorAction SilentlyContinue }
Write-Output "deployed to $dst"
Get-FileHash -LiteralPath $dst -Algorithm SHA256 | Format-List
