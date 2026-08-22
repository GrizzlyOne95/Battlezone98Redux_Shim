param(
    [string]$SnapshotRoot = (Join-Path $PSScriptRoot "snapshots\live_combat"),
    [string]$OutputCsv = "",
    [string]$PresentMonOutputCsv = ""
)

$ErrorActionPreference = "Stop"

if (-not $OutputCsv) {
    $OutputCsv = Join-Path $SnapshotRoot "results.csv"
}
if (-not $PresentMonOutputCsv) {
    $PresentMonOutputCsv = Join-Path $SnapshotRoot "presentmon_results.csv"
}

function Get-Number {
    param(
        [string]$Text,
        [string]$Name
    )

    # Profiler records are deliberately stable key/value text, so extracting by
    # key keeps this analyzer independent from incidental spacing and field order.
    $match = [regex]::Match(
        $Text,
        "(?:^|[ |])$([regex]::Escape($Name))=(?<value>-?[0-9]+(?:\.[0-9]+)?)")
    if (-not $match.Success) {
        return $null
    }

    return [double]::Parse(
        $match.Groups["value"].Value,
        [Globalization.CultureInfo]::InvariantCulture)
}

function Get-Average {
    param([object[]]$Values)

    # Missing backend-specific counters should stay blank rather than silently
    # becoming zero and looking like a measured result.
    $numbers = @($Values | Where-Object { $null -ne $_ })
    if ($numbers.Count -eq 0) {
        return $null
    }

    return ($numbers | Measure-Object -Average).Average
}

function Get-UtcMarker {
    param(
        [string]$LogText,
        [string]$Marker
    )

    # BZLogger uses local wall time while OpenShim uses UTC. Converting the
    # mission markers gives each run an exact profiler sampling window.
    $pattern = "(?m)^(?<stamp>[0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2}\.[0-9]{6}).*" +
        [regex]::Escape($Marker)
    $match = [regex]::Match($LogText, $pattern)
    if (-not $match.Success) {
        throw "Mission marker '$Marker' was not found"
    }

    $local = [datetime]::ParseExact(
        $match.Groups["stamp"].Value,
        "yyyy-MM-dd HH:mm:ss.ffffff",
        [Globalization.CultureInfo]::InvariantCulture,
        [Globalization.DateTimeStyles]::AssumeLocal)
    return $local.ToUniversalTime()
}

function Get-ProfileRecord {
    param([string]$Line)

    $match = [regex]::Match(
        $Line,
        "^\[(?<stamp>[0-9]{4}-[0-9]{2}-[0-9]{2}T[0-9]{2}:[0-9]{2}:[0-9]{2}\.[0-9]{3}Z)\]")
    if (-not $match.Success) {
        return $null
    }

    return [pscustomobject]@{
        StampText = $match.Groups["stamp"].Value
        Stamp = [datetime]::Parse(
            $match.Groups["stamp"].Value,
            [Globalization.CultureInfo]::InvariantCulture,
            [Globalization.DateTimeStyles]::AdjustToUniversal)
        Line = $Line
    }
}

$metadataFiles = @(Get-ChildItem -LiteralPath $SnapshotRoot -Filter metadata.json -File -Recurse)
if ($metadataFiles.Count -eq 0) {
    throw "No benchmark metadata found beneath $SnapshotRoot"
}

$externalResults = @()
$results = foreach ($metadataFile in $metadataFiles) {
    $runRoot = $metadataFile.DirectoryName
    $bzLogPath = Join-Path $runRoot "BZLogger.slice.txt"
    $shimLogPath = Join-Path $runRoot "openshim.log"
    if (-not (Test-Path -LiteralPath $bzLogPath) -or
        -not (Test-Path -LiteralPath $shimLogPath)) {
        Write-Warning "Skipping incomplete run $runRoot"
        continue
    }

    $metadata = Get-Content -LiteralPath $metadataFile.FullName -Raw | ConvertFrom-Json
    if (-not $metadata.completed) {
        continue
    }

    if (-not $metadata.profiler_enabled) {
        $presentMonPath = Join-Path $runRoot "presentmon.csv"
        if (-not (Test-Path -LiteralPath $presentMonPath)) {
            continue
        }
        $presentRows = @(Import-Csv -LiteralPath $presentMonPath)
        $frameTimes = @($presentRows |
            ForEach-Object { [double]$_.msBetweenPresents } |
            Where-Object { $_ -gt 0 } |
            Sort-Object)
        if ($frameTimes.Count -eq 0) {
            Write-Warning "Skipping $($metadata.run_id): PresentMon has no frame samples"
            continue
        }
        $gpuTimes = @($presentRows |
            ForEach-Object { [double]$_.msGPUActive } |
            Where-Object { $_ -ge 0 })
        $meanFrameTime = ($frameTimes | Measure-Object -Average).Average
        $externalResults += [pscustomobject][ordered]@{
            run_id = $metadata.run_id
            renderer = $metadata.renderer
            unit_odf = if ($metadata.PSObject.Properties.Name -contains "unit_odf") {
                $metadata.unit_odf
            } else {
                "svtank"
            }
            scenario = $metadata.scenario
            count = $metadata.count
            distance = $metadata.distance
            orientation = $metadata.orientation
            samples = $frameTimes.Count
            fps = 1000.0 / $meanFrameTime
            frame_mean_ms = $meanFrameTime
            frame_p95_ms = $frameTimes[[math]::Floor(($frameTimes.Count - 1) * 0.95)]
            frame_p99_ms = $frameTimes[[math]::Floor(($frameTimes.Count - 1) * 0.99)]
            frame_max_ms = $frameTimes[-1]
            gpu_active_ms = if ($gpuTimes.Count) {
                ($gpuTimes | Measure-Object -Average).Average
            } else {
                $null
            }
        }
        continue
    }

    try {
        $bzText = Get-Content -LiteralPath $bzLogPath -Raw
        $measureBegin = Get-UtcMarker -LogText $bzText -Marker "measure-begin"
        $measureEnd = Get-UtcMarker -LogText $bzText -Marker "measure-end benchmark-end"
    } catch {
        Write-Warning "Skipping $($metadata.run_id): $($_.Exception.Message)"
        continue
    }

    $records = @(Get-Content -LiteralPath $shimLogPath |
        ForEach-Object { Get-ProfileRecord -Line $_ } |
        Where-Object { $null -ne $_ -and $_.Stamp -ge $measureBegin -and $_.Stamp -le $measureEnd })

    # All category records from one report share a timestamp. Indexing them lets
    # duplicate totals be normalized by the corresponding interval's frame count.
    $main = @($records | Where-Object { $_.Line -match '\[OgreProfile\] fps=' })
    if ($main.Count -eq 0) {
        Write-Warning "Skipping $($metadata.run_id): no profiler samples in measurement window"
        continue
    }

    $skinByStamp = @{}
    $renderByStamp = @{}
    $dynamicByStamp = @{}
    $passesByStamp = @{}
    foreach ($record in $records) {
        if ($record.Line -match '\[OgreProfile\]\[SkinMeta\]') {
            $skinByStamp[$record.StampText] = $record.Line
        } elseif ($record.Line -match '\[OgreProfile\]\[Render\]') {
            $renderByStamp[$record.StampText] = $record.Line
        } elseif ($record.Line -match '\[OgreProfile\]\[DynamicGeometry\]') {
            $dynamicByStamp[$record.StampText] = $record.Line
        } elseif ($record.Line -match '\[OgreProfile\]\[Passes\]') {
            $passesByStamp[$record.StampText] = $record.Line
        }
    }

    $sampleRows = foreach ($sample in $main) {
        $fps = Get-Number $sample.Line "fps"
        $skinLine = $skinByStamp[$sample.StampText]
        $renderLine = $renderByStamp[$sample.StampText]
        $dynamicLine = $dynamicByStamp[$sample.StampText]
        $passesLine = $passesByStamp[$sample.StampText]
        $dupAnim = Get-Number $sample.Line "dupAnim"
        $dupSkin = Get-Number $sample.Line "dupSkin"
        $dupRenderQueue = Get-Number $skinLine "duplicateRenderQueue"

        [pscustomobject]@{
            fps = $fps
            frame_mean_ms = Get-Number $sample.Line "frameMean"
            frame_p95_ms = Get-Number $sample.Line "p95"
            frame_p99_ms = Get-Number $sample.Line "p99"
            frame_max_ms = Get-Number $sample.Line "max"
            anim_calls_per_frame = Get-Number $sample.Line "anim"
            anim_render_driven_percent = Get-Number $sample.Line "renderDriven"
            anim_external_per_frame = Get-Number $sample.Line "external"
            anim_cpu_ms_per_frame = Get-Number $sample.Line "animCPU"
            nonblend_cpu_ms_per_frame = Get-Number $sample.Line "nonBlend"
            skin_calls_per_frame = Get-Number $sample.Line "skin"
            skin_vertices_per_frame = Get-Number $sample.Line "verts"
            skin_cpu_ms_per_frame = Get-Number $sample.Line "swCPU"
            duplicate_anim_per_frame = if ($fps -gt 0) { $dupAnim / $fps } else { $null }
            duplicate_skin_per_frame = if ($fps -gt 0) { $dupSkin / $fps } else { $null }
            matrix_avg = Get-Number $skinLine "avg"
            matrix_max = Get-Number $skinLine "max"
            render_queue_calls_per_frame = Get-Number $skinLine "renderQueue"
            duplicate_render_queue_per_frame = if ($fps -gt 0) { $dupRenderQueue / $fps } else { $null }
            unique_animated_entities = Get-Number $skinLine "anim~"
            unique_skinned_entities = Get-Number $skinLine "skin~"
            unique_rendered_entities = Get-Number $skinLine "render~"
            ogre_submissions_per_frame = Get-Number $renderLine "OgreSubmit"
            ogre_submission_cpu_ms_per_frame = Get-Number $renderLine "cpu"
            draw_calls_per_frame = Get-Number $renderLine "Draw"
            indexed_draw_calls_per_frame = Get-Number $renderLine "DrawIndexed"
            dynamic_batches = Get-Number $dynamicLine "batchesAvg"
            dynamic_materials = Get-Number $dynamicLine "materials"
            dynamic_vertices = Get-Number $dynamicLine "vertices"
            dynamic_cpu_ms_per_frame = Get-Number $dynamicLine "cpu"
            scene_renders_per_frame = Get-Number $passesLine "scene"
            shadow_scene_renders_per_frame = Get-Number $passesLine "shadowScene"
            main_render_queue_per_frame = Get-Number $passesLine "rqMain"
            shadow_render_queue_per_frame = Get-Number $passesLine "rqShadow"
            main_animation_calls_per_frame = Get-Number $passesLine "animMain"
            shadow_animation_calls_per_frame = Get-Number $passesLine "animShadow"
            main_skin_calls_per_frame = Get-Number $passesLine "skinMain"
            shadow_skin_calls_per_frame = Get-Number $passesLine "skinShadow"
        }
    }

    $result = [ordered]@{
        run_id = $metadata.run_id
        renderer = $metadata.renderer
        unit_odf = if ($metadata.PSObject.Properties.Name -contains "unit_odf") {
            $metadata.unit_odf
        } else {
            "svtank"
        }
        scenario = $metadata.scenario
        count = $metadata.count
        distance = $metadata.distance
        orientation = $metadata.orientation
        samples = $sampleRows.Count
    }
    foreach ($property in $sampleRows[0].PSObject.Properties.Name) {
        $result[$property] = Get-Average @($sampleRows.$property)
    }
    [pscustomobject]$result
}

if (@($results).Count -eq 0 -and $externalResults.Count -eq 0) {
    throw "No completed profiler or PresentMon runs could be analyzed"
}

# Stable sort order makes renderer/scenario/count comparisons easy to diff and
# keeps repeated benchmark sessions reproducible.
$results = @($results | Sort-Object renderer, unit_odf, scenario, distance, count, orientation)
$outputDirectory = Split-Path -Parent $OutputCsv
if ($outputDirectory) {
    New-Item -ItemType Directory -Path $outputDirectory -Force | Out-Null
}
if ($results.Count) {
    $results | Export-Csv -LiteralPath $OutputCsv -NoTypeInformation
    $results | Format-Table renderer, unit_odf, scenario, count, distance, orientation, samples,
        fps, frame_mean_ms, frame_p95_ms, anim_cpu_ms_per_frame,
        skin_cpu_ms_per_frame, duplicate_anim_per_frame, ogre_submissions_per_frame -AutoSize
    Write-Host "Wrote $($results.Count) profiler run(s) to $OutputCsv"
}

if ($externalResults.Count) {
    $externalResults = @($externalResults |
        Sort-Object renderer, unit_odf, scenario, distance, count, orientation)
    $presentMonDirectory = Split-Path -Parent $PresentMonOutputCsv
    if ($presentMonDirectory) {
        New-Item -ItemType Directory -Path $presentMonDirectory -Force | Out-Null
    }
    $externalResults | Export-Csv -LiteralPath $PresentMonOutputCsv -NoTypeInformation
    $externalResults | Format-Table renderer, unit_odf, scenario, count, samples,
        fps, frame_mean_ms, frame_p95_ms, frame_p99_ms, gpu_active_ms -AutoSize
    Write-Host "Wrote $($externalResults.Count) PresentMon run(s) to $PresentMonOutputCsv"
}
