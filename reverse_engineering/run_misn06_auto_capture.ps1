param(
    [string]$GameRoot = "C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux",
    [string]$PackagedModsRoot = "C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux\packaged_mods\3686673790",
    [string]$MissionArgs = "misn06.bzn /edit",
    [int[]]$SpaceDelaysMs = @(250, 500, 750, 1000),
    [int]$SpaceRetryIntervalMs = 400,
    [int]$SpaceRetryWindowSeconds = 12,
    [int[]]$ScreenshotOffsetsMs = @(),
    [switch]$ScreenshotRelativeToSpace,
    [int]$RunDurationSeconds = 45,
    [switch]$WaitForChunkActivity,
    [int]$PostChunkActivitySeconds = 12,
    [int]$MainWindowTimeoutSeconds = 20,
    [switch]$AttachFrida,
    [string]$FridaScript = "",
    [switch]$DeployShim,
    [switch]$KillExistingGame,
    [switch]$KeepGameOpen
)

$ErrorActionPreference = "Stop"

Add-Type @"
using System;
using System.Runtime.InteropServices;

public static class OpenShimAutomationInputNative
{
    public const int SW_RESTORE = 9;
    public const ushort VK_SPACE = 0x20;
    public const uint KEYEVENTF_KEYUP = 0x0002;
    public const uint INPUT_KEYBOARD = 1;

    [StructLayout(LayoutKind.Sequential)]
    public struct INPUT
    {
        public uint type;
        public InputUnion U;
    }

    [StructLayout(LayoutKind.Explicit)]
    public struct InputUnion
    {
        [FieldOffset(0)]
        public KEYBDINPUT ki;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct KEYBDINPUT
    {
        public ushort wVk;
        public ushort wScan;
        public uint dwFlags;
        public uint time;
        public IntPtr dwExtraInfo;
    }

    [DllImport("user32.dll")]
    public static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);

    [DllImport("user32.dll")]
    public static extern bool SetForegroundWindow(IntPtr hWnd);

    [DllImport("user32.dll")]
    public static extern bool BringWindowToTop(IntPtr hWnd);

    [DllImport("user32.dll", SetLastError = true)]
    private static extern uint SendInput(uint nInputs, INPUT[] pInputs, int cbSize);

    public static bool SendSpaceKey()
    {
        INPUT[] inputs = new INPUT[2];
        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].U.ki.wVk = VK_SPACE;

        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].U.ki.wVk = VK_SPACE;
        inputs[1].U.ki.dwFlags = KEYEVENTF_KEYUP;

        return SendInput((uint)inputs.Length, inputs, Marshal.SizeOf(typeof(INPUT))) == inputs.Length;
    }
}
"@

if ($ScreenshotOffsetsMs.Count -gt 0) {
    Add-Type -AssemblyName System.Windows.Forms
    Add-Type -AssemblyName System.Drawing
    Add-Type @"
using System;
using System.Runtime.InteropServices;

public static class OpenShimWindowCaptureNative
{
    [StructLayout(LayoutKind.Sequential)]
    public struct RECT
    {
        public int Left;
        public int Top;
        public int Right;
        public int Bottom;
    }

    [DllImport("user32.dll")]
    public static extern bool GetWindowRect(IntPtr hWnd, out RECT rect);
}
"@
}

$repoRoot = Split-Path -Parent $PSScriptRoot
$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$gameLog = Join-Path $GameRoot "openshim.log"
$bzLogger = Join-Path $GameRoot "BZLogger.txt"
$dumpRoot = "C:\BZDumps"
$snapshotRoot = Join-Path $PSScriptRoot "snapshots"
$stamp = Get-Date -Format "yyyyMMdd_HHmmss"
$seriesRoot = Join-Path $snapshotRoot "misn06_auto_$stamp"
$shimSourceDll = Join-Path $repoRoot "bin\Release\winmm.dll"
$shimSourcePdb = Join-Path $repoRoot "bin\Release\winmm.pdb"
$shimTargets = @(
    (Join-Path $GameRoot "winmm.dll"),
    (Join-Path $PackagedModsRoot "winmm.dll")
)
$pdbTargets = @(
    (Join-Path $GameRoot "winmm.pdb"),
    (Join-Path $PackagedModsRoot "winmm.pdb")
)

if (-not (Test-Path $gameExe)) {
    throw "Game executable not found: $gameExe"
}

if (-not (Test-Path $snapshotRoot)) {
    New-Item -ItemType Directory -Path $snapshotRoot -Force | Out-Null
}
New-Item -ItemType Directory -Path $seriesRoot -Force | Out-Null

if (-not $FridaScript) {
    $FridaScript = Join-Path $repoRoot "reverse_engineering\redux_chunk_trace.js"
}

function Get-HashOrNull {
    param([string]$Path)
    if (-not (Test-Path $Path)) {
        return $null
    }
    try {
        return (Get-FileHash -Algorithm SHA256 -LiteralPath $Path).Hash
    } catch {
        $tempCopy = Join-Path $env:TEMP ("openshim_hash_" + [System.Guid]::NewGuid().ToString("N"))
        try {
            Copy-Item -LiteralPath $Path -Destination $tempCopy -Force
            return (Get-FileHash -Algorithm SHA256 -LiteralPath $tempCopy).Hash
        } catch {
            return $null
        } finally {
            Remove-Item -LiteralPath $tempCopy -Force -ErrorAction SilentlyContinue
        }
    }
}

function Stop-ProcessByNameIfPresent {
    param([string]$Name)
    Get-Process -Name $Name -ErrorAction SilentlyContinue | Stop-Process -Force
}

function Get-FileLengthOrZero {
    param([string]$Path)
    if (-not (Test-Path $Path)) {
        return 0L
    }
    try {
        return (Get-Item -LiteralPath $Path).Length
    } catch {
        return 0L
    }
}

function Get-LinesAfterOffset {
    param(
        [string]$Path,
        [long]$StartOffset
    )
    if (-not (Test-Path $Path)) {
        return @()
    }
    try {
        $fileInfo = Get-Item -LiteralPath $Path
        if ($StartOffset -lt 0 -or $StartOffset -gt $fileInfo.Length) {
            $StartOffset = 0L
        }

        $fileStream = [System.IO.File]::Open($Path, [System.IO.FileMode]::Open, [System.IO.FileAccess]::Read, [System.IO.FileShare]::ReadWrite)
        try {
            $skipFirstPartialLine = $false
            if ($StartOffset -gt 0) {
                [void]$fileStream.Seek($StartOffset - 1, [System.IO.SeekOrigin]::Begin)
                $previousByte = $fileStream.ReadByte()
                $skipFirstPartialLine = ($previousByte -ne 10 -and $previousByte -ne 13)
            }
            [void]$fileStream.Seek($StartOffset, [System.IO.SeekOrigin]::Begin)
            $reader = New-Object System.IO.StreamReader($fileStream, [System.Text.Encoding]::UTF8, $true, 4096, $true)
            try {
                if ($skipFirstPartialLine -and -not $reader.EndOfStream) {
                    [void]$reader.ReadLine()
                }
                $lines = New-Object System.Collections.Generic.List[string]
                while (-not $reader.EndOfStream) {
                    $lines.Add($reader.ReadLine())
                }
                return $lines.ToArray()
            } finally {
                $reader.Dispose()
            }
        } finally {
            $fileStream.Dispose()
        }
    } catch {
        return @()
    }
}

function Try-ActivateProcessWindow {
    param([System.Diagnostics.Process]$Process)

    if (-not $Process) {
        return $false
    }

    try {
        $Process.Refresh()
        if ($Process.HasExited -or $Process.MainWindowHandle -eq 0) {
            return $false
        }

        [void][OpenShimAutomationInputNative]::ShowWindow($Process.MainWindowHandle, [OpenShimAutomationInputNative]::SW_RESTORE)
        [void][OpenShimAutomationInputNative]::BringWindowToTop($Process.MainWindowHandle)
        [void][OpenShimAutomationInputNative]::SetForegroundWindow($Process.MainWindowHandle)

        $shell = New-Object -ComObject WScript.Shell
        [void]$shell.AppActivate($Process.Id)
        Start-Sleep -Milliseconds 100
        return $true
    } catch {
        return $false
    }
}

function Send-SpaceToProcess {
    param([System.Diagnostics.Process]$Process)

    $activated = Try-ActivateProcessWindow -Process $Process
    $sent = $false

    try {
        $sent = [OpenShimAutomationInputNative]::SendSpaceKey()
    } catch {
        $sent = $false
    }

    if (-not $sent) {
        try {
            $shell = New-Object -ComObject WScript.Shell
            if (-not $activated) {
                [void]$shell.AppActivate($Process.Id)
                Start-Sleep -Milliseconds 100
            }
            $shell.SendKeys(" ")
            $sent = $true
        } catch {
            $sent = $false
        }
    }

    return $sent
}

function Wait-ForMainWindow {
    param(
        [System.Diagnostics.Process]$Process,
        [int]$TimeoutSeconds
    )
    $deadline = (Get-Date).AddSeconds($TimeoutSeconds)
    while ((Get-Date) -lt $deadline) {
        if ($Process.HasExited) {
            return $false
        }
        $Process.Refresh()
        if ($Process.MainWindowHandle -ne 0) {
            return $true
        }
        Start-Sleep -Milliseconds 200
    }
    return $false
}

function Capture-DesktopScreenshot {
    param(
        [string]$OutPath,
        [int]$ProcessId = 0
    )

    if ($ProcessId -gt 0) {
        try {
            $shell = New-Object -ComObject WScript.Shell
            [void]$shell.AppActivate($ProcessId)
            Start-Sleep -Milliseconds 150
        } catch {
        }
    }

    $bounds = $null
    if ($ProcessId -gt 0) {
        try {
            $proc = Get-Process -Id $ProcessId -ErrorAction Stop
            if ($proc.MainWindowHandle -ne 0) {
                $rect = New-Object OpenShimWindowCaptureNative+RECT
                if ([OpenShimWindowCaptureNative]::GetWindowRect($proc.MainWindowHandle, [ref]$rect)) {
                    $width = [Math]::Max(1, $rect.Right - $rect.Left)
                    $height = [Math]::Max(1, $rect.Bottom - $rect.Top)
                    $bounds = [pscustomobject]@{
                        Left = $rect.Left
                        Top = $rect.Top
                        Width = $width
                        Height = $height
                    }
                }
            }
        } catch {
        }
    }

    if (-not $bounds) {
        $virtualScreen = [System.Windows.Forms.SystemInformation]::VirtualScreen
        $bounds = [pscustomobject]@{
            Left = $virtualScreen.Left
            Top = $virtualScreen.Top
            Width = $virtualScreen.Width
            Height = $virtualScreen.Height
        }
    }

    $bitmap = New-Object System.Drawing.Bitmap $bounds.Width, $bounds.Height
    $graphics = [System.Drawing.Graphics]::FromImage($bitmap)
    try {
        $graphics.CopyFromScreen($bounds.Left, $bounds.Top, 0, 0, $bitmap.Size)
        $bitmap.Save($OutPath, [System.Drawing.Imaging.ImageFormat]::Png)
    } finally {
        $graphics.Dispose()
        $bitmap.Dispose()
    }
}

function Get-RemainingRunMilliseconds {
    param([datetime]$Deadline)
    $remaining = [int][Math]::Floor(($Deadline - (Get-Date)).TotalMilliseconds)
    if ($remaining -lt 0) {
        return 0
    }
    return $remaining
}

function Start-FridaTrace {
    param(
        [int]$TargetPid,
        [string]$ScriptPath,
        [string]$OutPath,
        [string]$ErrPath
    )
    $quotedScript = '"' + $ScriptPath + '"'
    $cmdLine = "bzr-frida.cmd -p $TargetPid -q -t inf -l $quotedScript 1>`"$OutPath`" 2>`"$ErrPath`""
    return Start-Process -FilePath "cmd.exe" -ArgumentList "/c $cmdLine" -WorkingDirectory $repoRoot -PassThru -WindowStyle Hidden
}

function Score-Run {
    param(
        [string[]]$ShimLines,
        [string[]]$FridaLines,
        [string[]]$KnownGeoTokens,
        [bool]$Crashed
    )
    $createChunk = @($ShimLines | Where-Object { $_ -match '\[CHUNKSPAWN\] CreateChunk ' }).Count
    $createChunklet = @($ShimLines | Where-Object { $_ -match '\[CHUNKSPAWN\] CreateChunklet ' }).Count
    $fragFlush = @($ShimLines | Where-Object { $_ -match '\[CHUNKFRAG\] flush ' }).Count
    $fridaCreateChunk = @($FridaLines | Where-Object { $_ -match '\[CreateChunk\]' }).Count
    $geoHits = 0
    foreach ($token in $KnownGeoTokens) {
        if ($ShimLines -match [regex]::Escape($token)) {
            $geoHits++
        }
        if ($FridaLines -match [regex]::Escape($token)) {
            $geoHits++
        }
    }
    $score = ($createChunk * 50) + ($fridaCreateChunk * 60) + ($fragFlush * 30) + ($geoHits * 10) - ($createChunklet) - ($(if ($Crashed) { 200 } else { 0 }))
    return [ordered]@{
        create_chunk = $createChunk
        create_chunklet = $createChunklet
        chunkfrag_flush = $fragFlush
        frida_create_chunk = $fridaCreateChunk
        geo_hit_score = $geoHits
        score = $score
    }
}

$knownGeoTokens = @(
    "ARA11BDA","ARA11Gc1","ARA11Gc2","ARA11Gr1","ARA11Gs1","ARA11LGT","ARA11NRL","ARA11NRR","ARA11POV","ARA11ROR","ARA11RORL","ARA11RORT",
    "AGR11BDA","AGR11BDAT","AGR11BGA","AGR11GC1","AGR11Gc2","AGR11GM1","AGR11GS1","AGR11LGT","Agr11nrl","Agr11nrr","AGR11POV","AGR11ROR","AGR11TUR",
    "SFL11BDA","SFL11BDB","SFL11GC1","SFL11Gc2","SFL11GR1","SFL11Gs1","SFL11LGT","SFL11NFL","SFL11NFR","SFL11POV","SFL11ROR","SFL11RORp","SFL11RORt",
    "SCZ11BGA","SCZ11BGB","SCZ11GC1","SCZ11GC2","SCZ11GM1","SCZ11GS1","SCZ11LGT","SCZ11MOR","SCZ11POV","SCZ11RAD","scz11wgl","scz11wgr"
)

if ($KillExistingGame) {
    Stop-ProcessByNameIfPresent -Name "battlezone98redux"
    Stop-ProcessByNameIfPresent -Name "frida"
    Start-Sleep -Seconds 2
}

$deployment = [ordered]@{
    source_dll = $shimSourceDll
    source_pdb = $shimSourcePdb
    source_hash = Get-HashOrNull -Path $shimSourceDll
    deployed = @()
}

if ($DeployShim) {
    foreach ($target in $shimTargets) {
        Copy-Item -LiteralPath $shimSourceDll -Destination $target -Force
        $deployment.deployed += [pscustomobject]@{
            path = $target
            hash = Get-HashOrNull -Path $target
        }
    }
    foreach ($target in $pdbTargets) {
        if (Test-Path $shimSourcePdb) {
            Copy-Item -LiteralPath $shimSourcePdb -Destination $target -Force
        }
    }
}

$runs = @()

foreach ($delayMs in $SpaceDelaysMs) {
    Stop-ProcessByNameIfPresent -Name "frida"
    if ($KillExistingGame) {
        Stop-ProcessByNameIfPresent -Name "battlezone98redux"
        Start-Sleep -Seconds 1
    }

    $runRoot = Join-Path $seriesRoot ("delay_" + $delayMs.ToString("0000") + "ms")
    New-Item -ItemType Directory -Path $runRoot -Force | Out-Null
    $screenshotPaths = @()

    $preShimOffset = Get-FileLengthOrZero -Path $gameLog
    $preBzOffset = Get-FileLengthOrZero -Path $bzLogger
    $preDumpNames = @()
    if (Test-Path $dumpRoot) {
        $preDumpNames = @(Get-ChildItem -LiteralPath $dumpRoot -File | Select-Object -ExpandProperty Name)
    }

    $runStartedAt = Get-Date
    $runDeadline = $runStartedAt.AddSeconds($RunDurationSeconds)
    $tailDeadline = $runDeadline
    $chunkActivityDetected = $false
    $chunkActivityDetectedAt = $null
    $liveShimOffset = $preShimOffset
    $liveBzOffset = $preBzOffset

    $gameProc = Start-Process -FilePath $gameExe -ArgumentList $MissionArgs -WorkingDirectory $GameRoot -PassThru
    $windowWaitSeconds = [Math]::Min(
        $MainWindowTimeoutSeconds,
        [Math]::Max(0, [int][Math]::Ceiling(($runDeadline - (Get-Date)).TotalSeconds)))
    $windowReady = $false
    if ($windowWaitSeconds -gt 0) {
        $windowReady = Wait-ForMainWindow -Process $gameProc -TimeoutSeconds $windowWaitSeconds
    }
    $spaceSent = $false
    $spaceSentAt = $null
    $spaceAttemptCount = 0
    $waitingForVoObserved = $false
    $spaceSkipObserved = $false
    $voiceCompleteObserved = $false

    if ($windowReady) {
        $remainingBeforeSpace = Get-RemainingRunMilliseconds -Deadline $runDeadline
        if ($remainingBeforeSpace -gt 0) {
            Start-Sleep -Milliseconds ([Math]::Min($delayMs, $remainingBeforeSpace))
        }

        $spaceRetryDeadline = $null
        $nextSpaceAttemptAt = Get-Date

        while (-not $gameProc.HasExited -and
               -not $spaceSkipObserved -and
               -not $voiceCompleteObserved) {
            $remainingBeforeInput = Get-RemainingRunMilliseconds -Deadline $runDeadline
            if ($remainingBeforeInput -le 0) {
                break
            }

            $currentBzLength = Get-FileLengthOrZero -Path $bzLogger
            $liveBzLines = Get-LinesAfterOffset -Path $bzLogger -StartOffset $liveBzOffset
            $liveBzOffset = $currentBzLength

            foreach ($line in $liveBzLines) {
                if ($line -match 'Sim Startup: Waiting For VO') {
                    $waitingForVoObserved = $true
                    if (-not $spaceRetryDeadline) {
                        $spaceRetryDeadline = (Get-Date).AddSeconds($SpaceRetryWindowSeconds)
                        $nextSpaceAttemptAt = Get-Date
                    }
                }
                if ($line -match 'Stopping load voice due to space keypress') {
                    $spaceSkipObserved = $true
                }
                if ($line -match 'Sim Startup: VO complete' -or
                    $line -match 'Sim Startup: First Frame after' -or
                    $line -match 'Game Simulation Initialized after') {
                    $voiceCompleteObserved = $true
                }
            }

            if ($spaceSkipObserved -or $voiceCompleteObserved) {
                break
            }

            if ($waitingForVoObserved -and
                ((-not $spaceRetryDeadline) -or (Get-Date) -lt $spaceRetryDeadline) -and
                (Get-Date) -ge $nextSpaceAttemptAt) {
                if (Send-SpaceToProcess -Process $gameProc) {
                    ++$spaceAttemptCount
                    if (-not $spaceSent) {
                        $spaceSent = $true
                        $spaceSentAt = Get-Date
                    }
                }
                $nextSpaceAttemptAt = (Get-Date).AddMilliseconds($SpaceRetryIntervalMs)
            }

            $sleepUntilNextAttemptMs = [int][Math]::Floor(($nextSpaceAttemptAt - (Get-Date)).TotalMilliseconds)
            $loopSleepMs = 100
            if ($waitingForVoObserved) {
                $loopSleepMs = [Math]::Max(25, [Math]::Min(100, $sleepUntilNextAttemptMs))
            }
            Start-Sleep -Milliseconds ([Math]::Min($loopSleepMs, $remainingBeforeInput))
        }

        if (-not $spaceSkipObserved -and -not $voiceCompleteObserved) {
            $currentBzLength = Get-FileLengthOrZero -Path $bzLogger
            $liveBzLines = Get-LinesAfterOffset -Path $bzLogger -StartOffset $liveBzOffset
            $liveBzOffset = $currentBzLength
            foreach ($line in $liveBzLines) {
                if ($line -match 'Sim Startup: Waiting For VO') {
                    $waitingForVoObserved = $true
                }
                if ($line -match 'Stopping load voice due to space keypress') {
                    $spaceSkipObserved = $true
                }
                if ($line -match 'Sim Startup: VO complete' -or
                    $line -match 'Sim Startup: First Frame after' -or
                    $line -match 'Game Simulation Initialized after') {
                    $voiceCompleteObserved = $true
                }
            }
        }
    }

    $fridaLog = Join-Path $runRoot "frida.log"
    $fridaErr = Join-Path $runRoot "frida.err.log"
    $fridaProc = $null
    if ($AttachFrida -and -not $gameProc.HasExited) {
        $fridaProc = Start-FridaTrace -TargetPid $gameProc.Id -ScriptPath $FridaScript -OutPath $fridaLog -ErrPath $fridaErr
        $remainingAfterFrida = Get-RemainingRunMilliseconds -Deadline $runDeadline
        if ($remainingAfterFrida -gt 0) {
            Start-Sleep -Milliseconds ([Math]::Min(1000, $remainingAfterFrida))
        }
    }

    $captureSchedule = @($ScreenshotOffsetsMs | Sort-Object)
    foreach ($offsetMs in $captureSchedule) {
        $captureBaseTime = $runStartedAt
        if ($ScreenshotRelativeToSpace -and $spaceSentAt) {
            $captureBaseTime = $spaceSentAt
        }
        $targetTime = $captureBaseTime.AddMilliseconds($offsetMs)
        $remainingUntilCapture = [int][Math]::Floor(($targetTime - (Get-Date)).TotalMilliseconds)
        if ($remainingUntilCapture -gt 0) {
            $remainingBudget = Get-RemainingRunMilliseconds -Deadline $runDeadline
            if ($remainingBudget -le 0) {
                break
            }
            Start-Sleep -Milliseconds ([Math]::Min($remainingUntilCapture, $remainingBudget))
        }
        if ($gameProc.HasExited) {
            break
        }
        $shotPrefix = if ($ScreenshotRelativeToSpace) { "screen_space_" } else { "screen_" }
        $shotPath = Join-Path $runRoot ($shotPrefix + $offsetMs.ToString("00000") + "ms.png")
        try {
            Capture-DesktopScreenshot -OutPath $shotPath -ProcessId $gameProc.Id
            $screenshotPaths += $shotPath
        } catch {
        }
    }

    while ($true) {
        $remainingRunMs = Get-RemainingRunMilliseconds -Deadline $tailDeadline
        if ($remainingRunMs -le 0) {
            break
        }

        if ($WaitForChunkActivity -and -not $chunkActivityDetected -and -not $gameProc.HasExited) {
            $currentShimLength = Get-FileLengthOrZero -Path $gameLog
            $liveShimLines = Get-LinesAfterOffset -Path $gameLog -StartOffset $liveShimOffset
            $liveShimOffset = $currentShimLength
            $chunkActivityLines = @($liveShimLines | Where-Object {
                    $_ -match '\[CHUNKSPAWN\] CreateChunk ' -or
                    $_ -match '\[CHUNKMESH\] assigned '
                })
            if ($chunkActivityLines.Count -gt 0) {
                $chunkActivityDetected = $true
                $chunkActivityDetectedAt = Get-Date
                $tailDeadline = [DateTime]::Max($tailDeadline, $chunkActivityDetectedAt.AddSeconds($PostChunkActivitySeconds))
                continue
            }

            Start-Sleep -Milliseconds ([Math]::Min(500, $remainingRunMs))
            continue
        }

        Start-Sleep -Milliseconds $remainingRunMs
        break
    }

    $exitCode = $null
    $exitedNaturally = $false
    $gameProc.Refresh()
    if ($gameProc.HasExited) {
        $exitCode = $gameProc.ExitCode
        $exitedNaturally = $true
    } elseif (-not $KeepGameOpen) {
        Stop-Process -Id $gameProc.Id -Force
        Start-Sleep -Milliseconds 250
    }

    if ($fridaProc) {
        try {
            if (-not $fridaProc.HasExited) {
                Stop-Process -Id $fridaProc.Id -Force
            }
        } catch {
        }
    }

    Start-Sleep -Milliseconds 250

    $shimLines = Get-LinesAfterOffset -Path $gameLog -StartOffset $preShimOffset
    $bzLines = Get-LinesAfterOffset -Path $bzLogger -StartOffset $preBzOffset
    $fridaLines = @()
    if (Test-Path $fridaLog) {
        $fridaLines = Get-Content -LiteralPath $fridaLog
    }

    $newDumpNames = @()
    if (Test-Path $dumpRoot) {
        $newDumpNames = @(Get-ChildItem -LiteralPath $dumpRoot -File |
            Where-Object { $preDumpNames -notcontains $_.Name } |
            Sort-Object LastWriteTime |
            Select-Object -ExpandProperty Name)
    }

    $shimSlicePath = Join-Path $runRoot "openshim.slice.log"
    $bzSlicePath = Join-Path $runRoot "BZLogger.slice.txt"
    $summaryPath = Join-Path $runRoot "summary.json"
    [System.IO.File]::WriteAllText($shimSlicePath, (@($shimLines) -join [Environment]::NewLine), [System.Text.Encoding]::UTF8)
    [System.IO.File]::WriteAllText($bzSlicePath, (@($bzLines) -join [Environment]::NewLine), [System.Text.Encoding]::UTF8)

    $score = Score-Run -ShimLines $shimLines -FridaLines $fridaLines -KnownGeoTokens $knownGeoTokens -Crashed ($newDumpNames.Count -gt 0)
    $run = [ordered]@{
        delay_ms = $delayMs
        pid = $gameProc.Id
        window_ready = $windowReady
        space_sent = $spaceSent
        space_sent_at = if ($spaceSentAt) { $spaceSentAt.ToString("o") } else { $null }
        space_attempt_count = $spaceAttemptCount
        waiting_for_vo_observed = $waitingForVoObserved
        space_skip_observed = $spaceSkipObserved
        voice_complete_observed = $voiceCompleteObserved
        wait_for_chunk_activity = [bool]$WaitForChunkActivity
        chunk_activity_detected = $chunkActivityDetected
        chunk_activity_detected_at = if ($chunkActivityDetectedAt) { $chunkActivityDetectedAt.ToString("o") } else { $null }
        post_chunk_activity_seconds = $PostChunkActivitySeconds
        attach_frida = [bool]$AttachFrida
        frida_script = if ($AttachFrida) { $FridaScript } else { $null }
        exited_naturally = $exitedNaturally
        exit_code = $exitCode
        new_dumps = $newDumpNames
        output_dir = $runRoot
        shim_slice = $shimSlicePath
        bz_slice = $bzSlicePath
        frida_log = if ($AttachFrida) { $fridaLog } else { $null }
        frida_err = if ($AttachFrida) { $fridaErr } else { $null }
        screenshots = $screenshotPaths
    }
    foreach ($key in $score.Keys) {
        $run[$key] = $score[$key]
    }

    $run | ConvertTo-Json -Depth 5 | Set-Content -LiteralPath $summaryPath -Encoding ASCII
    $runs += [pscustomobject]$run
}

$bestRun = $runs | Sort-Object @{ Expression = "score"; Descending = $true }, @{ Expression = "create_chunk"; Descending = $true }, @{ Expression = "geo_hit_score"; Descending = $true } | Select-Object -First 1
$seriesSummary = [ordered]@{
    captured_at = (Get-Date).ToString("o")
    game_root = $GameRoot
    mission_args = $MissionArgs
    deploy_shim = [bool]$DeployShim
    deployment = $deployment
    attach_frida = [bool]$AttachFrida
    frida_script = if ($AttachFrida) { $FridaScript } else { $null }
    run_duration_seconds = $RunDurationSeconds
    space_retry_interval_ms = $SpaceRetryIntervalMs
    space_retry_window_seconds = $SpaceRetryWindowSeconds
    wait_for_chunk_activity = [bool]$WaitForChunkActivity
    post_chunk_activity_seconds = $PostChunkActivitySeconds
    main_window_timeout_seconds = $MainWindowTimeoutSeconds
    space_delays_ms = $SpaceDelaysMs
    best_run = $bestRun
    runs = $runs
}

$seriesSummaryPath = Join-Path $seriesRoot "series_summary.json"
$seriesSummary | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath $seriesSummaryPath -Encoding ASCII
$seriesSummary | ConvertTo-Json -Depth 6
