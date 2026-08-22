param(
    [Parameter(Mandatory = $true)]
    [string[]]$RunDirectory,
    [double]$WindowStartSeconds = 3.0,
    [double]$WindowEndSeconds = 18.0
)

$ErrorActionPreference = "Stop"

function Get-AverageValue {
    param(
        [object[]]$Records,
        [string]$Property
    )

    $values = @($Records | ForEach-Object { $_.$Property } | Where-Object { $null -ne $_ })
    if ($values.Count -eq 0) {
        return $null
    }
    return [Math]::Round(($values | Measure-Object -Average).Average, 3)
}

foreach ($directory in $RunDirectory) {
    $resolved = (Resolve-Path -LiteralPath $directory).Path
    $bzLog = Join-Path $resolved "BZLogger.slice.txt"
    $shimLog = Join-Path $resolved "openshim.slice.log"
    if (-not (Test-Path -LiteralPath $bzLog) -or -not (Test-Path -LiteralPath $shimLog)) {
        throw "Missing capture logs in $resolved"
    }

    $destroyLine = Get-Content -LiteralPath $bzLog | Where-Object {
        $_ -match '\[STOCK_CHUNK_TAIL\].*destroy-begin'
    } | Select-Object -First 1
    if (-not $destroyLine -or $destroyLine -notmatch '^(?<time>\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\.\d+)') {
        throw "No synthetic destruction marker found in $bzLog"
    }

    $destroyLocal = [datetime]::ParseExact(
        $Matches.time,
        "yyyy-MM-dd HH:mm:ss.ffffff",
        [Globalization.CultureInfo]::InvariantCulture,
        [Globalization.DateTimeStyles]::AssumeLocal)
    $windowStart = $destroyLocal.ToUniversalTime().AddSeconds($WindowStartSeconds)
    $windowEnd = $destroyLocal.ToUniversalTime().AddSeconds($WindowEndSeconds)

    $byTimestamp = @{}
    foreach ($line in Get-Content -LiteralPath $shimLog) {
        if ($line -notmatch '^\[(?<time>\d{4}-\d{2}-\d{2}T[^\]]+Z)\].*\[ogre-profile\] (?<message>.*)$') {
            continue
        }

        $timestamp = [datetime]::Parse(
            $Matches.time,
            [Globalization.CultureInfo]::InvariantCulture,
            [Globalization.DateTimeStyles]::AdjustToUniversal)
        if ($timestamp -lt $windowStart -or $timestamp -gt $windowEnd) {
            continue
        }

        $key = $timestamp.ToString("O")
        if (-not $byTimestamp.ContainsKey($key)) {
            $byTimestamp[$key] = [ordered]@{ timestamp = $timestamp }
        }
        $record = $byTimestamp[$key]
        $message = $Matches.message

        if ($message -match '^\[OgreProfile\] fps=(?<fps>[\d.]+) frameMean=(?<mean>[\d.]+).*p95=(?<p95>[\d.]+) p99=(?<p99>[\d.]+)') {
            $record.fps = [double]$Matches.fps
            $record.mean_ms = [double]$Matches.mean
            $record.p95_ms = [double]$Matches.p95
            $record.p99_ms = [double]$Matches.p99
        } elseif ($message -match '^\[OgreProfile\]\[Chunk\] activeAvg=(?<active>[\d.]+).*simCPU=(?<cpu>[\d.]+)ms/f') {
            $record.chunk_active = [double]$Matches.active
            $record.chunk_sim_cpu_ms = [double]$Matches.cpu
        } elseif ($message -match '^\[OgreProfile\]\[DynamicGeometry\].*batchesAvg=(?<batches>[\d.]+).*blended=(?<blended>[\d.]+)/call.*cpu=(?<cpu>[\d.]+)ms/f') {
            $record.dynamic_batches = [double]$Matches.batches
            $record.dynamic_blended = [double]$Matches.blended
            $record.dynamic_cpu_ms = [double]$Matches.cpu
        } elseif ($message -match '^\[OgreProfile\]\[Render\] OgreSubmit=(?<submit>[\d.]+)/f cpu=(?<cpu>[\d.]+)ms/f') {
            $record.ogre_submissions = [double]$Matches.submit
            $record.ogre_submission_cpu_ms = [double]$Matches.cpu
        } elseif ($message -match '^\[OgreProfile\]\[ChunkEntitySummary\] namedEntities=(?<entities>\d+) shadows=(?<shadows>\d+) renderQueue=(?<queue>[\d.]+)/f') {
            $record.chunk_entities = [double]$Matches.entities
            $record.chunk_shadows = [double]$Matches.shadows
            $record.chunk_render_queue = [double]$Matches.queue
        } elseif ($message -match '^\[OgreProfile\]\[D3D9\] DrawPrimitive=(?<draw>[\d.]+)/f DrawIndexedPrimitive=(?<indexed>[\d.]+)/f renderState=(?<render>[\d.]+)/f blendState=(?<blend>[\d.]+)/f texture=(?<texture>[\d.]+)/f textureStage=(?<stage>[\d.]+)/f sampler=(?<sampler>[\d.]+)/f vertexShader=(?<vs>[\d.]+)/f pixelShader=(?<ps>[\d.]+)/f') {
            $record.d3d9_draw = [double]$Matches.draw
            $record.d3d9_draw_indexed = [double]$Matches.indexed
            $record.d3d9_render_state = [double]$Matches.render
            $record.d3d9_blend_state = [double]$Matches.blend
            $record.d3d9_texture = [double]$Matches.texture
            $record.d3d9_texture_stage = [double]$Matches.stage
            $record.d3d9_sampler = [double]$Matches.sampler
            $record.d3d9_vertex_shader = [double]$Matches.vs
            $record.d3d9_pixel_shader = [double]$Matches.ps
        }
    }

    $records = @($byTimestamp.Values | ForEach-Object { [pscustomobject]$_ } |
        Where-Object { $null -ne $_.fps } | Sort-Object timestamp)
    if ($records.Count -eq 0) {
        throw "No profiler intervals found in the requested window for $resolved"
    }

    [pscustomobject][ordered]@{
        run = $resolved
        intervals = $records.Count
        window_start_seconds = $WindowStartSeconds
        window_end_seconds = $WindowEndSeconds
        fps = Get-AverageValue $records "fps"
        mean_ms = Get-AverageValue $records "mean_ms"
        p95_ms = Get-AverageValue $records "p95_ms"
        p99_ms = Get-AverageValue $records "p99_ms"
        ogre_submissions_per_frame = Get-AverageValue $records "ogre_submissions"
        ogre_submission_cpu_ms_per_frame = Get-AverageValue $records "ogre_submission_cpu_ms"
        chunk_active = Get-AverageValue $records "chunk_active"
        chunk_sim_cpu_ms_per_frame = Get-AverageValue $records "chunk_sim_cpu_ms"
        dynamic_batches_per_call = Get-AverageValue $records "dynamic_batches"
        dynamic_blended_batches_per_call = Get-AverageValue $records "dynamic_blended"
        dynamic_cpu_ms_per_frame = Get-AverageValue $records "dynamic_cpu_ms"
        chunk_entities = Get-AverageValue $records "chunk_entities"
        chunk_entities_with_shadows = Get-AverageValue $records "chunk_shadows"
        chunk_render_queue_per_frame = Get-AverageValue $records "chunk_render_queue"
        d3d9_draw_per_frame = Get-AverageValue $records "d3d9_draw"
        d3d9_draw_indexed_per_frame = Get-AverageValue $records "d3d9_draw_indexed"
        d3d9_render_state_per_frame = Get-AverageValue $records "d3d9_render_state"
        d3d9_blend_state_per_frame = Get-AverageValue $records "d3d9_blend_state"
        d3d9_texture_per_frame = Get-AverageValue $records "d3d9_texture"
        d3d9_texture_stage_per_frame = Get-AverageValue $records "d3d9_texture_stage"
        d3d9_sampler_per_frame = Get-AverageValue $records "d3d9_sampler"
        d3d9_vertex_shader_per_frame = Get-AverageValue $records "d3d9_vertex_shader"
        d3d9_pixel_shader_per_frame = Get-AverageValue $records "d3d9_pixel_shader"
    }
}
