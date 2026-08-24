param(
    [string]$SnapshotRoot = (Join-Path $PSScriptRoot "snapshots\live_combat"),
    [string]$OutputCsv = "",
    [string]$PresentMonOutputCsv = "",
    [string]$ContributorOutputCsv = ""
)

$ErrorActionPreference = "Stop"

if (-not $OutputCsv) {
    $OutputCsv = Join-Path $SnapshotRoot "results.csv"
}
if (-not $PresentMonOutputCsv) {
    $PresentMonOutputCsv = Join-Path $SnapshotRoot "presentmon_results.csv"
}
if (-not $ContributorOutputCsv) {
    $ContributorOutputCsv = Join-Path $SnapshotRoot "render_contributors.csv"
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

function Get-TextValue {
    param(
        [string]$Text,
        [string]$Name
    )

    $match = [regex]::Match(
        $Text,
        "(?:^|[ ])$([regex]::Escape($Name))=(?<value>[^ ]+)")
    if (-not $match.Success) {
        return $null
    }
    return $match.Groups["value"].Value
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
$contributorResults = @()
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

    $contributorRows = @($records |
        Where-Object { $_.Line -match '\[OgreProfile\]\[RenderContributorTop\]' } |
        ForEach-Object {
            [pscustomobject]@{
                type = Get-TextValue $_.Line "type"
                owner_sample = Get-TextValue $_.Line "ownerSample"
                mesh = Get-TextValue $_.Line "mesh"
                material = Get-TextValue $_.Line "material"
                technique = Get-TextValue $_.Line "technique"
                scheme = Get-TextValue $_.Line "scheme"
                lod = Get-Number $_.Line "lod"
                pass = Get-TextValue $_.Line "pass"
                camera = Get-TextValue $_.Line "camera"
                rank = Get-Number $_.Line "rank"
                main_per_frame = Get-Number $_.Line "main"
                shadow_per_frame = Get-Number $_.Line "shadow"
                render_calls_per_frame = Get-Number $_.Line "renderCalls"
                ogre_submissions_per_frame = Get-Number $_.Line "OgreSubmit"
                operation_vertices_per_frame = Get-Number $_.Line "opVerts"
                operation_indices_per_frame = Get-Number $_.Line "opIndices"
                draw_per_frame = Get-Number $_.Line "Draw"
                indexed_draw_per_frame = Get-Number $_.Line "DrawIndexed"
                drawn_vertices_per_frame = Get-Number $_.Line "drawnVerts"
                drawn_indices_per_frame = Get-Number $_.Line "drawnIndices"
                no_draw_per_frame = Get-Number $_.Line "noDraw"
                empty_vertex_per_frame = Get-Number $_.Line "emptyVerts"
                zero_prim_per_frame = Get-Number $_.Line "zeroPrim"
                unobserved_per_frame = Get-Number $_.Line "unobserved"
                cpu_ms_per_frame = Get-Number $_.Line "cpu"
            }
        })
    foreach ($group in @($contributorRows | Group-Object `
            type, mesh, material, technique, scheme, lod, pass, camera)) {
        $first = $group.Group[0]
        $contributorResults += [pscustomobject][ordered]@{
            run_id = $metadata.run_id
            renderer = $metadata.renderer
            unit_odf = $metadata.unit_odf
            scenario = $metadata.scenario
            count = $metadata.count
            distance = $metadata.distance
            orientation = $metadata.orientation
            type = $first.type
            owner_sample = $first.owner_sample
            mesh = $first.mesh
            material = $first.material
            technique = $first.technique
            scheme = $first.scheme
            lod = $first.lod
            pass = $first.pass
            camera = $first.camera
            samples = $group.Count
            rank_mean = Get-Average @($group.Group.rank)
            main_per_frame = Get-Average @($group.Group.main_per_frame)
            shadow_per_frame = Get-Average @($group.Group.shadow_per_frame)
            render_calls_per_frame = Get-Average @($group.Group.render_calls_per_frame)
            ogre_submissions_per_frame = Get-Average @($group.Group.ogre_submissions_per_frame)
            operation_vertices_per_frame = Get-Average @($group.Group.operation_vertices_per_frame)
            operation_indices_per_frame = Get-Average @($group.Group.operation_indices_per_frame)
            draw_per_frame = Get-Average @($group.Group.draw_per_frame)
            indexed_draw_per_frame = Get-Average @($group.Group.indexed_draw_per_frame)
            drawn_vertices_per_frame = Get-Average @($group.Group.drawn_vertices_per_frame)
            drawn_indices_per_frame = Get-Average @($group.Group.drawn_indices_per_frame)
            no_draw_per_frame = Get-Average @($group.Group.no_draw_per_frame)
            empty_vertex_per_frame = Get-Average @($group.Group.empty_vertex_per_frame)
            zero_prim_per_frame = Get-Average @($group.Group.zero_prim_per_frame)
            unobserved_per_frame = Get-Average @($group.Group.unobserved_per_frame)
            cpu_ms_per_frame = Get-Average @($group.Group.cpu_ms_per_frame)
        }
    }

    # All category records from one report share a timestamp. Indexing them lets
    # duplicate totals be normalized by the corresponding interval's frame count.
    $main = @($records | Where-Object { $_.Line -match '\[OgreProfile\] fps=' })
    if ($main.Count -eq 0) {
        Write-Warning "Skipping $($metadata.run_id): no profiler samples in measurement window"
        continue
    }

    $skinByStamp = @{}
    $renderByStamp = @{}
    $contributorSummaryByStamp = @{}
    $d3d9ByStamp = @{}
    $skinSourceByStamp = @{}
    $dynamicByStamp = @{}
    $passesByStamp = @{}
    foreach ($record in $records) {
        if ($record.Line -match '\[OgreProfile\]\[SkinMeta\]') {
            $skinByStamp[$record.StampText] = $record.Line
        } elseif ($record.Line -match '\[OgreProfile\]\[Render\]') {
            $renderByStamp[$record.StampText] = $record.Line
        } elseif ($record.Line -match '\[OgreProfile\]\[RenderContributorSummary\]') {
            $contributorSummaryByStamp[$record.StampText] = $record.Line
        } elseif ($record.Line -match '\[OgreProfile\]\[D3D9\]') {
            $d3d9ByStamp[$record.StampText] = $record.Line
        } elseif ($record.Line -match '\[OgreProfile\]\[DX11SkinSourceShadow\]') {
            $skinSourceByStamp[$record.StampText] = $record.Line
        } elseif ($record.Line -match '\[OgreProfile\]\[DynamicGeometry\]') {
            $dynamicByStamp[$record.StampText] = $record.Line
        } elseif ($record.Line -match '\[OgreProfile\]\[Passes\]') {
            $passesByStamp[$record.StampText] = $record.Line
        }
    }

    $d3d9Lines = @($records |
        Where-Object { $_.Line -match '\[OgreProfile\]\[D3D9\]' })
    $skinSourceLines = @($records |
        Where-Object { $_.Line -match '\[OgreProfile\]\[DX11SkinSourceShadow\]' })
    $contributorSummaryLines = @($records |
        Where-Object { $_.Line -match '\[OgreProfile\]\[RenderContributorSummary\]' })
    $sampleRows = for ($sampleOrdinal = 0; $sampleOrdinal -lt $main.Count; $sampleOrdinal++) {
        $sample = $main[$sampleOrdinal]
        $fps = Get-Number $sample.Line "fps"
        $skinLine = $skinByStamp[$sample.StampText]
        $renderLine = $renderByStamp[$sample.StampText]
        $contributorSummaryLine = $contributorSummaryByStamp[$sample.StampText]
        if (-not $contributorSummaryLine -and
            $sampleOrdinal -lt $contributorSummaryLines.Count) {
            # The contributor summary is emitted later in the same report block
            # and can cross the logger's millisecond boundary, exactly like the
            # D3D9 record below. Fall back to interval order rather than dropping
            # the submission-to-draw accounting for that interval.
            $contributorSummaryLine = $contributorSummaryLines[$sampleOrdinal].Line
        }
        $d3d9Line = $d3d9ByStamp[$sample.StampText]
        if (-not $d3d9Line -and $sampleOrdinal -lt $d3d9Lines.Count) {
            # D3D9 is emitted at the end of the same report block and can cross
            # the logger's millisecond boundary. Preserve interval order as the
            # fallback instead of dropping otherwise valid backend counters.
            $d3d9Line = $d3d9Lines[$sampleOrdinal].Line
        }
        $skinSourceLine = $skinSourceByStamp[$sample.StampText]
        if (-not $skinSourceLine -and $sampleOrdinal -lt $skinSourceLines.Count) {
            $skinSourceLine = $skinSourceLines[$sampleOrdinal].Line
        }
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
            instanced_draw_calls_per_frame = Get-Number $renderLine "DrawInstanced"
            indexed_instanced_draw_calls_per_frame = Get-Number $renderLine "DrawIndexedInstanced"
            context_vtable_refreshes = Get-Number $renderLine "contextRefresh"
            # Submission-to-draw accounting. An Ogre submission is not an API
            # draw: these say how many submissions issued none, and why.
            no_draw_submissions_per_frame = Get-Number $contributorSummaryLine "noDraw"
            empty_vertex_submissions_per_frame = Get-Number $contributorSummaryLine "emptyVerts"
            zero_prim_submissions_per_frame = Get-Number $contributorSummaryLine "zeroPrim"
            multi_draw_submissions_per_frame = Get-Number $contributorSummaryLine "multiDraw"
            unobserved_submissions_per_frame = Get-Number $contributorSummaryLine "unobserved"
            contributor_coverage_percent = Get-Number $contributorSummaryLine "coverage"
            d3d9_render_state_per_frame = Get-Number $d3d9Line "renderState"
            d3d9_blend_state_per_frame = Get-Number $d3d9Line "blendState"
            d3d9_texture_per_frame = Get-Number $d3d9Line "texture"
            d3d9_texture_stage_per_frame = Get-Number $d3d9Line "textureStage"
            d3d9_sampler_per_frame = Get-Number $d3d9Line "sampler"
            d3d9_vertex_shader_per_frame = Get-Number $d3d9Line "vertexShader"
            d3d9_pixel_shader_per_frame = Get-Number $d3d9Line "pixelShader"
            skin_source_queries = Get-Number $skinSourceLine "queries"
            skin_source_repairs = Get-Number $skinSourceLine "repairs"
            skin_source_bytes = Get-Number $skinSourceLine "bytes"
            skin_source_failures = Get-Number $skinSourceLine "failures"
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

if ($contributorResults.Count) {
    $contributorResults = @($contributorResults | Sort-Object `
        renderer, unit_odf, scenario, count, distance, orientation,
        @{ Expression = "ogre_submissions_per_frame"; Descending = $true })
    $contributorDirectory = Split-Path -Parent $ContributorOutputCsv
    if ($contributorDirectory) {
        New-Item -ItemType Directory -Path $contributorDirectory -Force | Out-Null
    }
    $contributorResults | Export-Csv -LiteralPath $ContributorOutputCsv -NoTypeInformation
    Write-Host "Wrote $($contributorResults.Count) contributor group(s) to $ContributorOutputCsv"
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
