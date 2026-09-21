# Set-BznIdentity: make a renamed .bzn agree with its own filename.
#
# Dot-source this; it defines one function and does nothing else.
#
#     . (Join-Path $PSScriptRoot "BznIdentity.ps1")
#     Set-BznIdentity -Path "...\lcbveg.bzn" -Basename "lcbveg"
#
# A .bzn names itself TWICE, in `msn_filename` and `TerrainName`. Copying
# lcbench.bzn to another name leaves both pointing at lcbench, so the engine
# looks for lcbench.trn / .hg2 / .mat / .lgt beside the new mission, does not
# find them, and the mission does not launch. Renaming the file is not enough.
#
# Rewritten as bytes, and verified afterwards, because the .bzn is ASCII with
# CRLF line endings and a single bare LF picked up along the way passes
# `git status` clean and then kills the ASCII parser mid-object.
#
# Lives here rather than inside one installer because two of them need it, and
# a subtle byte-level routine is exactly the kind that goes stale when copied.

function Set-BznIdentity {
    param(
        [Parameter(Mandatory)][string]$Path,
        [Parameter(Mandatory)][string]$Basename
    )

    $bytes = [System.IO.File]::ReadAllBytes($Path)
    $text = [System.Text.Encoding]::ASCII.GetString($bytes)

    $text = [regex]::Replace($text, '(?m)^msn_filename = \S+', "msn_filename = $Basename.bzn")
    $text = [regex]::Replace($text, '(?m)^TerrainName = \S+', "TerrainName = $Basename")

    $rewritten = [System.Text.Encoding]::ASCII.GetBytes($text)
    [System.IO.File]::WriteAllBytes($Path, $rewritten)

    # Prove both fields took, and that nothing acquired a bare LF.
    $check = [System.Text.Encoding]::ASCII.GetString(
        [System.IO.File]::ReadAllBytes($Path))
    if ($check -notmatch [regex]::Escape("msn_filename = $Basename.bzn") -or
        $check -notmatch [regex]::Escape("TerrainName = $Basename")) {
        throw "BZN identity rewrite did not take for $Basename"
    }
    $bareLf = ([regex]::Matches($check, "(?<!`r)`n")).Count
    if ($bareLf -gt 0) {
        throw "BZN $Basename gained $bareLf bare LF line ending(s)"
    }
}
