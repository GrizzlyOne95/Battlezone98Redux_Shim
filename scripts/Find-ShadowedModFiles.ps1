<#
.SYNOPSIS
    Lists files in the active Redux mod that a higher-precedence location overrides.

.DESCRIPTION
    Redux resolves loose game files (ODF, GEO, SDF, BZN, TRN ...) through one
    flat, name-keyed index, not through directory paths. A stale copy of
    avtank.odf in addon\ silently replaced Campaign Reimagined's avtank.odf, so
    a new key in CR's copy never loaded and nothing logged it. This finds those
    copies before a test run does.

    The resolution rule below was read from the shipping GOG exe's decompile
    (FS init 0x00820F10, index build 0x008283E0, name lookup 0x00828850, loose
    open 0x00828DC0, cWorkshop::build*Resource 0x0076A030..0x0076B350). Details
    and confidence per claim: reverse_engineering/loose_file_resolution_rule.md.

      1. The key is the file's lower-cased name, truncated to 16 characters,
         extension included. Folder structure is not part of the key.
      2. One index per mission/session. Sources are added in this order and the
         lowest source index wins a name:
           a. addon\ root, loose files only (not its subfolders)
           b. enabled mod folders, in registration order (the lines of
              modEnabled.dat that match a discovered mod)
           c. the mission's own folder (for a CR campaign: mods\<id>)
           d. stock (the install root and the .zfs archives)
      3. An addon\<subfolder> is only a source if it is listed in
         modEnabled.dat, or the mission was launched from it. Every other
         subfolder is dormant, however many files it shares with the mod.
      4. Ogre resources (material, program, mesh, skeleton, textures ...) are
         separate: the Modable group is BZ_ASSETS plus the same enabled mod
         folders and mission folder as overlays. addon\ root is not an overlay
         there; files of those types in addon\ root are reported as a
         lower-confidence shadow rather than ignored.

    The script reports every file of the active mod that (a) a loose addon\ root
    file with the same key overrides, or (b) an enabled mod folder overrides.
    Each is marked SAME or DIFFERENT by content hash; only DIFFERENT ones fail
    the run. With -IncludeDormant it also lists same-key files in non-enabled
    addon subfolders, mods\ siblings and packaged_mods, which do not take effect
    now but will the moment that folder is enabled.

.PARAMETER GameDir
    Battlezone 98 Redux install directory. Defaults to the GOG test install.

.PARAMETER ModId
    Folder name under mods\ (or packaged_mods\) of the mod being checked.
    Defaults to Campaign Reimagined's Workshop id.

.PARAMETER Json
    Emit one JSON document on stdout and nothing else.

.PARAMETER IncludeDormant
    Also scan the rest of addon\, mods\ and packaged_mods\ for same-key files
    that are not currently enabled. Walks the whole addon tree (tens of
    thousands of files), so it is off by default.

.PARAMETER Quiet
    Print the summary line only (used by Deploy-OpenShim.ps1).

.OUTPUTS
    Exit code 0 when no differing shadow exists, 1 when at least one does,
    2 when the install or mod folder cannot be read.

.EXAMPLE
    .\Find-ShadowedModFiles.ps1

.EXAMPLE
    .\Find-ShadowedModFiles.ps1 -IncludeDormant -Json > shadows.json
#>
[CmdletBinding()]
param(
    [string]$GameDir = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [string]$ModId = '3686673790',
    [switch]$Json,
    [switch]$IncludeDormant,
    [switch]$Quiet
)

$ErrorActionPreference = 'Stop'

# Types the Ogre resource system loads (Modable group). Everything else is a
# loose file read through the engine file system.
$ogreExt = @('.material', '.program', '.mesh', '.skeleton', '.compositor', '.particle',
    '.overlay', '.fontdef', '.cg', '.hlsl', '.glsl', '.glsles', '.shader', '.dds',
    '.png', '.tga', '.jpg', '.jpeg', '.hdr')

function Get-FullPath([string]$Path) {
    if ([System.IO.Path]::IsPathRooted($Path)) { return [System.IO.Path]::GetFullPath($Path) }
    return [System.IO.Path]::GetFullPath((Join-Path (Get-Location).ProviderPath $Path))
}

function Get-FileClass([string]$Name) {
    if ($ogreExt -contains [System.IO.Path]::GetExtension($Name).ToLowerInvariant()) { return 'ogre' }
    return 'engine'
}

# Engine file names are cut to 16 characters on both index build and lookup;
# Ogre resource names are not.
function Get-Key([string]$Name) {
    $lower = $Name.ToLowerInvariant()
    if ($lower.Length -gt 16 -and (Get-FileClass $Name) -eq 'engine') { return $lower.Substring(0, 16) }
    return $lower
}

function Test-SameContent([string]$A, [string]$B) {
    $fa = New-Object System.IO.FileInfo $A
    $fb = New-Object System.IO.FileInfo $B
    if ($fa.Length -ne $fb.Length) { return $false }
    return (Get-FileHash -Algorithm SHA256 -LiteralPath $A).Hash -eq
           (Get-FileHash -Algorithm SHA256 -LiteralPath $B).Hash
}

function New-Hit($ModFile, $Other, $Tier, $Basis) {
    $om = New-Object System.IO.FileInfo $Other
    $mm = New-Object System.IO.FileInfo $ModFile
    [pscustomobject]@{
        ModFile       = $ModFile
        ShadowedBy    = $Other
        Tier          = $Tier
        Basis         = $Basis
        Class         = Get-FileClass $mm.Name
        NameMatch     = $(if ($mm.Name -ieq $om.Name) { 'exact' } else { 'prefix16' })
        ModSize       = $mm.Length
        ModMTime      = $mm.LastWriteTime.ToString('yyyy-MM-dd HH:mm:ss')
        ShadowSize    = $om.Length
        ShadowMTime   = $om.LastWriteTime.ToString('yyyy-MM-dd HH:mm:ss')
        SameHash      = (Test-SameContent $ModFile $Other)
    }
}

try {
    $game = Get-FullPath $GameDir
    if (-not (Test-Path -LiteralPath $game -PathType Container)) { throw "GameDir not found: $game" }

    $modDir = $null
    foreach ($root in @('mods', 'packaged_mods')) {
        $candidate = Join-Path (Join-Path $game $root) $ModId
        if (Test-Path -LiteralPath $candidate -PathType Container) { $modDir = $candidate; break }
    }
    if (-not $modDir) { throw "Mod $ModId not found under $game\mods or $game\packaged_mods" }

    # Index the active mod once: key -> list of full paths.
    $modIndex = New-Object 'System.Collections.Generic.Dictionary[string,System.Collections.Generic.List[string]]'
    $modFileCount = 0
    foreach ($f in [System.IO.Directory]::EnumerateFiles($modDir, '*', [System.IO.SearchOption]::AllDirectories)) {
        $modFileCount++
        $k = Get-Key ([System.IO.Path]::GetFileName($f))
        $list = $null
        if (-not $modIndex.TryGetValue($k, [ref]$list)) {
            $list = New-Object 'System.Collections.Generic.List[string]'
            $modIndex[$k] = $list
        }
        $list.Add($f)
    }

    # Enabled mod folders, in modEnabled.dat order.
    $enabled = New-Object System.Collections.Generic.List[string]
    $activeModEnabled = $false
    $enabledFile = Join-Path $game 'modEnabled.dat'
    if (Test-Path -LiteralPath $enabledFile) {
        foreach ($line in [System.IO.File]::ReadAllLines($enabledFile)) {
            $p = $line.Trim()
            if (-not $p) { continue }
            if (-not (Test-Path -LiteralPath $p -PathType Container)) {
                # The file stores absolute paths; follow a moved install by leaf name.
                $leaf = Split-Path -Leaf $p
                $p = $null
                foreach ($root in @('addon', 'mods', 'packaged_mods')) {
                    $try = Join-Path (Join-Path $game $root) $leaf
                    if (Test-Path -LiteralPath $try -PathType Container) { $p = $try; break }
                }
            }
            if (-not $p) { continue }
            if ((Get-FullPath $p) -eq (Get-FullPath $modDir)) { $activeModEnabled = $true }
            else { $enabled.Add((Get-FullPath $p)) }
        }
    }

    $shadows = New-Object System.Collections.Generic.List[object]
    $reported = New-Object 'System.Collections.Generic.HashSet[string]'

    # Tier 1: addon\ root, loose files only.
    $addonDir = Join-Path $game 'addon'
    if (Test-Path -LiteralPath $addonDir -PathType Container) {
        foreach ($f in [System.IO.Directory]::EnumerateFiles($addonDir, '*', [System.IO.SearchOption]::TopDirectoryOnly)) {
            $list = $null
            if ($modIndex.TryGetValue((Get-Key ([System.IO.Path]::GetFileName($f))), [ref]$list)) {
                $basis = 'confirmed'
                if ((Get-FileClass $f) -eq 'ogre') { $basis = 'inferred (addon root is not an Ogre overlay; not proven inert)' }
                foreach ($m in $list) {
                    [void]$reported.Add("$m|$f")
                    $shadows.Add((New-Hit $m $f 'addon-root' $basis))
                }
            }
        }
    }

    # When the active mod is itself listed in modEnabled.dat its position among
    # the enabled mods decides who wins; that order is not proven, so say so.
    $enabledBasis = 'confirmed (engine files); inferred (Ogre overlay priority)'
    if ($activeModEnabled) { $enabledBasis = 'order against the active mod unverified (it is also in modEnabled.dat)' }

    # Tier 2: enabled mod folders (registered after addon root, before the mission folder).
    foreach ($dir in $enabled) {
        foreach ($f in [System.IO.Directory]::EnumerateFiles($dir, '*', [System.IO.SearchOption]::AllDirectories)) {
            $list = $null
            if ($modIndex.TryGetValue((Get-Key ([System.IO.Path]::GetFileName($f))), [ref]$list)) {
                foreach ($m in $list) {
                    if ($reported.Add("$m|$f")) {
                        $shadows.Add((New-Hit $m $f ('enabled-mod:' + (Split-Path -Leaf $dir)) $enabledBasis))
                    }
                }
            }
        }
    }

    # Dormant: same-key files in folders that are not sources right now.
    $dormant = New-Object System.Collections.Generic.List[object]
    if ($IncludeDormant) {
        $skip = New-Object 'System.Collections.Generic.HashSet[string]' ([System.StringComparer]::OrdinalIgnoreCase)
        [void]$skip.Add((Get-FullPath $modDir))
        foreach ($d in $enabled) { [void]$skip.Add($d) }
        $roots = New-Object System.Collections.Generic.List[string]
        foreach ($root in @('addon', 'mods', 'packaged_mods')) {
            $r = Join-Path $game $root
            if (-not (Test-Path -LiteralPath $r -PathType Container)) { continue }
            foreach ($sub in [System.IO.Directory]::EnumerateDirectories($r)) {
                if (-not $skip.Contains((Get-FullPath $sub))) { $roots.Add($sub) }
            }
        }
        foreach ($dir in $roots) {
            foreach ($f in [System.IO.Directory]::EnumerateFiles($dir, '*', [System.IO.SearchOption]::AllDirectories)) {
                $list = $null
                if ($modIndex.TryGetValue((Get-Key ([System.IO.Path]::GetFileName($f))), [ref]$list)) {
                    foreach ($m in $list) {
                        $h = New-Hit $m $f ('dormant:' + $dir.Substring($game.Length).TrimStart('\')) 'dormant until the folder is enabled or launched from'
                        $dormant.Add($h)
                    }
                }
            }
        }
    }

    # A prefix16-only match is real to the engine but only if it ever opens such a
    # long name; report it, do not fail on it.
    $differing = @($shadows.ToArray() | Where-Object { -not $_.SameHash -and $_.NameMatch -eq 'exact' })
    $result = [pscustomobject]@{
        GameDir        = $game
        ModId          = $ModId
        ModDir         = $modDir
        ModFiles       = $modFileCount
        ActiveModEnabled = $activeModEnabled
        EnabledMods    = $enabled.ToArray()
        ShadowCount    = $shadows.Count
        DifferingCount = $differing.Count
        Shadows        = $shadows.ToArray()
        DormantCount   = $dormant.Count
        DormantDiffering = @($dormant.ToArray() | Where-Object { -not $_.SameHash }).Count
        Dormant        = $dormant.ToArray()
    }

    if ($Json) {
        $result | ConvertTo-Json -Depth 6
    }
    else {
        $summary = "Shadow check for mod $ModId ($modFileCount files): $($shadows.Count) shadowed, $($differing.Count) differ."
        if ($IncludeDormant) { $summary += " Dormant same-key files: $($dormant.Count) ($($result.DormantDiffering) differ)." }
        if (-not $Quiet) {
            Write-Host ("Active mod:   {0}" -f $modDir)
            Write-Host ("Enabled mods: {0}" -f $(if ($enabled.Count) { ($enabled.ToArray() | ForEach-Object { Split-Path -Leaf $_ }) -join ', ' } else { '(none in modEnabled.dat)' }))
            foreach ($s in ($shadows.ToArray() | Sort-Object SameHash, Class, ModFile)) {
                $verdict = if ($s.SameHash) { 'SAME     ' } else { 'DIFFERENT' }
                Write-Host ("{0} [{1}] {2}" -f $verdict, $s.Tier, $s.ModFile.Substring($modDir.Length).TrimStart('\'))
                Write-Host ("          shadowed by {0}  ({1} B, {2}; mod copy {3} B, {4})" -f $s.ShadowedBy, $s.ShadowSize, $s.ShadowMTime, $s.ModSize, $s.ModMTime)
            }
            if ($IncludeDormant -and $dormant.Count) {
                Write-Host ""
                Write-Host "Dormant (not a source now), by folder:"
                $dormant.ToArray() | Group-Object Tier | Sort-Object Count -Descending | ForEach-Object {
                    $d = @($_.Group | Where-Object { -not $_.SameHash }).Count
                    Write-Host ("  {0,5} files ({1} differ)  {2}" -f $_.Count, $d, $_.Name.Substring(8))
                }
            }
        }
        Write-Host $summary
    }

    if ($differing.Count -gt 0) { exit 1 }
    exit 0
}
catch {
    [Console]::Error.WriteLine("Find-ShadowedModFiles: $($_.Exception.Message)")
    exit 2
}
