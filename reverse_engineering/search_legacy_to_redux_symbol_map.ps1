param(
    [Parameter(Mandatory = $true)]
    [string]$Pattern,
    [string]$MapPath = "",
    [string[]]$Confidence = @(),
    [int]$Limit = 50
)

if ([string]::IsNullOrWhiteSpace($MapPath)) {
    $MapPath = Join-Path $PSScriptRoot "workshop\symbol_transfer\legacy_to_redux\legacy_to_redux_symbol_map.csv"
}

if (-not (Test-Path $MapPath)) {
    throw "Missing symbol map: $MapPath. Run build_legacy_to_redux_symbol_map.py first."
}

$wantedConfidence = @{}
foreach ($item in $Confidence) {
    if (-not [string]::IsNullOrWhiteSpace($item)) {
        $wantedConfidence[$item.ToLowerInvariant()] = $true
    }
}

$regex = [regex]::new($Pattern, [System.Text.RegularExpressions.RegexOptions]::IgnoreCase)
$confidenceRank = @{
    "very_high" = 4
    "high" = 3
    "medium" = 2
    "low" = 1
}

Import-Csv -LiteralPath $MapPath |
    Where-Object {
        if ($wantedConfidence.Count -gt 0 -and -not $wantedConfidence.ContainsKey($_.confidence.ToLowerInvariant())) {
            return $false
        }
        $haystack = @(
            $_.legacy_name,
            $_.legacy_namespace,
            $_.legacy_signature,
            $_.redux_current_name,
            $_.redux_entry_rva,
            $_.methods,
            $_.shared_strings,
            $_.shared_constants
        ) -join " "
        return $regex.IsMatch($haystack)
    } |
    Sort-Object `
        @{ Expression = { $confidenceRank[$_.confidence] }; Descending = $true }, `
        @{ Expression = { [double]$_.score }; Descending = $true }, `
        @{ Expression = { [double]$_.margin }; Descending = $true } |
    Select-Object -First $Limit `
        confidence,
        score,
        margin,
        legacy_name,
        redux_entry_rva,
        redux_static_prologue,
        redux_current_name,
        methods,
        shared_strings,
        redux_decomp |
    Format-Table -AutoSize
