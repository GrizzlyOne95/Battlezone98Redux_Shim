param(
    [string]$TargetPath = "",
    [string]$OutputRoot = "",
    [int]$DefaultTimeoutSeconds = 60,
    [int]$CapaTimeoutSeconds = 180,
    [int]$FlossTimeoutSeconds = 180,
    [string]$YaraRules = "",
    [switch]$SkipCapa,
    [switch]$SkipFloss
)

$ErrorActionPreference = "Stop"

function Resolve-RepoRoot {
    return (Split-Path -Parent $PSScriptRoot)
}

function Resolve-DefaultTarget {
    $candidates = @(
        [Environment]::GetEnvironmentVariable("BZR_GAME_EXE", "Process"),
        [Environment]::GetEnvironmentVariable("BZR_GAME_EXE", "User"),
        [Environment]::GetEnvironmentVariable("BZR_REDUX_EXE", "Process"),
        [Environment]::GetEnvironmentVariable("BZR_REDUX_EXE", "User"),
        (Join-Path $env:USERPROFILE "Documents\Battlezone 98 Redux\battlezone98redux.exe"),
        "C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux\battlezone98redux.exe"
    )

    foreach ($candidate in $candidates) {
        if ($candidate -and (Test-Path -LiteralPath $candidate)) {
            return (Resolve-Path -LiteralPath $candidate).Path
        }
    }

    throw "Could not locate a default Battlezone executable. Pass -TargetPath explicitly."
}

function Resolve-Tool([string]$Name) {
    $command = Get-Command $Name -ErrorAction SilentlyContinue
    if ($command) {
        return $command.Source
    }
    return ""
}

function Add-ReportSection([System.Collections.Generic.List[string]]$Lines, [string]$Title, [string[]]$Body) {
    $Lines.Add("")
    $Lines.Add("## $Title")
    foreach ($line in $Body) {
        $Lines.Add($line)
    }
}

function Invoke-CapturedTool {
    param(
        [string]$Name,
        [string]$CommandPath,
        [string[]]$Arguments,
        [string]$RawDirectory,
        [int]$TimeoutSeconds
    )

    $safeName = $Name -replace "[^A-Za-z0-9_.-]", "_"
    $stdoutPath = Join-Path $RawDirectory "$safeName.stdout.txt"
    $stderrPath = Join-Path $RawDirectory "$safeName.stderr.txt"

    $result = [ordered]@{
        name = $Name
        command = $CommandPath
        arguments = $Arguments
        stdout = $stdoutPath
        stderr = $stderrPath
        exit_code = $null
        timed_out = $false
        skipped = $false
        error = ""
    }

    if (-not $CommandPath -or -not (Test-Path -LiteralPath $CommandPath)) {
        $result.skipped = $true
        $result.error = "Tool not found on PATH."
        return $result
    }

    $psi = [System.Diagnostics.ProcessStartInfo]::new()
    $psi.FileName = $CommandPath
    $psi.UseShellExecute = $false
    $psi.RedirectStandardOutput = $true
    $psi.RedirectStandardError = $true
    $psi.CreateNoWindow = $true
    foreach ($argument in $Arguments) {
        [void]$psi.ArgumentList.Add($argument)
    }

    $process = [System.Diagnostics.Process]::new()
    $process.StartInfo = $psi

    try {
        [void]$process.Start()
        $stdoutTask = $process.StandardOutput.ReadToEndAsync()
        $stderrTask = $process.StandardError.ReadToEndAsync()
        $finished = $process.WaitForExit($TimeoutSeconds * 1000)
        if (-not $finished) {
            $result.timed_out = $true
            try {
                $process.Kill($true)
            } catch {
            }
        }

        $stdout = $stdoutTask.GetAwaiter().GetResult()
        $stderr = $stderrTask.GetAwaiter().GetResult()
        Set-Content -LiteralPath $stdoutPath -Value $stdout -Encoding ASCII
        Set-Content -LiteralPath $stderrPath -Value $stderr -Encoding ASCII

        if ($process.HasExited) {
            $result.exit_code = $process.ExitCode
        }
    } catch {
        $result.error = $_.Exception.Message
        Set-Content -LiteralPath $stdoutPath -Value "" -Encoding ASCII
        Set-Content -LiteralPath $stderrPath -Value $result.error -Encoding ASCII
    } finally {
        $process.Dispose()
    }

    return $result
}

function Get-PreviewLines([string]$Path, [int]$LineCount = 40) {
    if (-not (Test-Path -LiteralPath $Path)) {
        return @("_No output file._")
    }

    $lines = @(Get-Content -LiteralPath $Path -ErrorAction SilentlyContinue | Select-Object -First $LineCount)
    if ($lines.Count -eq 0) {
        return @("_No stdout._")
    }

    return @("``````text") + $lines + @("``````")
}

$repoRoot = Resolve-RepoRoot
if (-not $TargetPath) {
    $TargetPath = Resolve-DefaultTarget
}
$TargetPath = (Resolve-Path -LiteralPath $TargetPath).Path

if (-not $OutputRoot) {
    $OutputRoot = Join-Path $PSScriptRoot "tooling_smoke"
}

$timestamp = Get-Date -Format "yyyyMMdd_HHmmss"
$targetBaseName = [System.IO.Path]::GetFileNameWithoutExtension($TargetPath)
$outputDir = Join-Path $OutputRoot "$($timestamp)_$targetBaseName"
$rawDir = Join-Path $outputDir "raw"
New-Item -ItemType Directory -Path $rawDir -Force | Out-Null

$reportPath = Join-Path $outputDir "report.md"
$summaryJsonPath = Join-Path $outputDir "summary.json"

$toolNames = @(
    "bzr-diec.cmd",
    "bzr-rz-bin.cmd",
    "bzr-dumpbin.cmd",
    "bzr-capa.cmd",
    "bzr-floss.cmd",
    "bzr-entropy.cmd",
    "bzr-yara.cmd"
)
$tools = [ordered]@{}
foreach ($toolName in $toolNames) {
    $tools[$toolName] = Resolve-Tool $toolName
}

$fileInfo = Get-Item -LiteralPath $TargetPath
$hashes = [ordered]@{
    sha256 = (Get-FileHash -LiteralPath $TargetPath -Algorithm SHA256).Hash
    sha1 = (Get-FileHash -LiteralPath $TargetPath -Algorithm SHA1).Hash
    md5 = (Get-FileHash -LiteralPath $TargetPath -Algorithm MD5).Hash
}

$runs = [System.Collections.Generic.List[object]]::new()

$runs.Add((Invoke-CapturedTool "diec" $tools["bzr-diec.cmd"] @($TargetPath) $rawDir $DefaultTimeoutSeconds))
$runs.Add((Invoke-CapturedTool "rz-bin_info" $tools["bzr-rz-bin.cmd"] @("-I", $TargetPath) $rawDir $DefaultTimeoutSeconds))
$runs.Add((Invoke-CapturedTool "rz-bin_imports" $tools["bzr-rz-bin.cmd"] @("-i", $TargetPath) $rawDir $DefaultTimeoutSeconds))
$runs.Add((Invoke-CapturedTool "rz-bin_sections" $tools["bzr-rz-bin.cmd"] @("-S", $TargetPath) $rawDir $DefaultTimeoutSeconds))
$runs.Add((Invoke-CapturedTool "dumpbin_headers" $tools["bzr-dumpbin.cmd"] @("/headers", $TargetPath) $rawDir $DefaultTimeoutSeconds))
$runs.Add((Invoke-CapturedTool "dumpbin_imports" $tools["bzr-dumpbin.cmd"] @("/imports", $TargetPath) $rawDir $DefaultTimeoutSeconds))
$runs.Add((Invoke-CapturedTool "entropy" $tools["bzr-entropy.cmd"] @($TargetPath) $rawDir $DefaultTimeoutSeconds))

if (-not $SkipCapa) {
    $runs.Add((Invoke-CapturedTool "capa" $tools["bzr-capa.cmd"] @($TargetPath) $rawDir $CapaTimeoutSeconds))
}

if (-not $SkipFloss) {
    $runs.Add((Invoke-CapturedTool "floss" $tools["bzr-floss.cmd"] @($TargetPath) $rawDir $FlossTimeoutSeconds))
}

if ($YaraRules) {
    $resolvedRules = (Resolve-Path -LiteralPath $YaraRules).Path
    $runs.Add((Invoke-CapturedTool "yara" $tools["bzr-yara.cmd"] @("-r", $resolvedRules, $TargetPath) $rawDir $DefaultTimeoutSeconds))
}

$summary = [ordered]@{
    generated_at = (Get-Date).ToString("o")
    repo_root = $repoRoot
    target_path = $TargetPath
    output_dir = $outputDir
    raw_dir = $rawDir
    file = [ordered]@{
        name = $fileInfo.Name
        length = $fileInfo.Length
        last_write_time = $fileInfo.LastWriteTime.ToString("o")
        hashes = $hashes
    }
    tools = $tools
    runs = $runs
}
$summary | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath $summaryJsonPath -Encoding ASCII

$report = [System.Collections.Generic.List[string]]::new()
$report.Add("# Battlezone Tooling Smoke Report")
$report.Add("")
$report.Add("- Generated: $($summary.generated_at)")
$report.Add(('- Repo: `{0}`' -f $repoRoot))
$report.Add(('- Target: `{0}`' -f $TargetPath))
$report.Add("- Size: $($fileInfo.Length) bytes")
$report.Add(('- SHA256: `{0}`' -f $hashes.sha256))
$report.Add('- Raw outputs: `raw/`')

$availability = foreach ($toolName in $toolNames) {
    $path = $tools[$toolName]
    if ($path) {
        "- ``$toolName``: ``$path``"
    } else {
        "- ``$toolName``: missing"
    }
}
Add-ReportSection $report "Tool Availability" $availability

$runSummary = foreach ($run in $runs) {
    $status = "ok"
    if ($run.skipped) {
        $status = "skipped"
    } elseif ($run.timed_out) {
        $status = "timed out"
    } elseif ($run.exit_code -ne 0 -and $null -ne $run.exit_code) {
        $status = "exit $($run.exit_code)"
    } elseif ($run.error) {
        $status = "error"
    }
    "- ``$($run.name)``: $status"
}
Add-ReportSection $report "Run Summary" $runSummary

foreach ($run in $runs) {
    $body = @()
    $body += ('- Command: `{0}`' -f $run.command)
    $body += ('- Arguments: `{0}`' -f ($run.arguments -join ' '))
    $body += ('- Exit code: `{0}`' -f $run.exit_code)
    $body += ('- Timed out: `{0}`' -f $run.timed_out)
    if ($run.error) {
        $body += ('- Error: `{0}`' -f $run.error)
    }
    $body += ('- Stdout: `raw/{0}`' -f [System.IO.Path]::GetFileName($run.stdout))
    $body += ('- Stderr: `raw/{0}`' -f [System.IO.Path]::GetFileName($run.stderr))
    $body += ""
    $body += Get-PreviewLines $run.stdout 40
    Add-ReportSection $report $run.name $body
}

Set-Content -LiteralPath $reportPath -Value $report -Encoding ASCII

[ordered]@{
    output_dir = $outputDir
    report = $reportPath
    summary_json = $summaryJsonPath
} | ConvertTo-Json
