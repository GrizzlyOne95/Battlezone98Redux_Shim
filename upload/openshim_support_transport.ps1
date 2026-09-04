# OpenShim support telemetry transport helper (Windows PowerShell 5.1 compatible)
#
# This file deliberately contains transport only. Process supervision, log
# preservation, crash survival, bundling and outbox behavior remain owned by
# openshim_wrap.ps1 from PR #116.

Set-StrictMode -Version 2

function Get-OpenShimSupportEndpoint {
    param([string]$ConfFile)

    if ($env:OPENSHIM_SUPPORT_ENDPOINT) {
        return $env:OPENSHIM_SUPPORT_ENDPOINT.TrimEnd('/')
    }

    if ($ConfFile -and (Test-Path -LiteralPath $ConfFile)) {
        foreach ($line in (Get-Content -LiteralPath $ConfFile -ErrorAction SilentlyContinue)) {
            if ($line -match '^\s*OPENSHIM_SUPPORT_ENDPOINT\s*=\s*(.*)$') {
                $value = $Matches[1].Trim().Trim("'").Trim('"')
                if ($value) { return $value.TrimEnd('/') }
            }
        }
    }

    return ""
}

function Protect-OpenShimSupportText {
    param([AllowNull()][string]$Text)
    if ($null -eq $Text) { return "" }

    $safe = $Text

    # Never let an accidentally logged Discord webhook escape through the new
    # transport path. This also covers legacy PR #116 configuration mistakes.
    $safe = [regex]::Replace(
        $safe,
        'https://discord(?:app)?\.com/api/webhooks/[A-Za-z0-9_./-]+',
        '<DISCORD_WEBHOOK_REDACTED>',
        [System.Text.RegularExpressions.RegexOptions]::IgnoreCase)

    # Routine support mode does not need peer IP addresses. A later explicit
    # network-diagnostic mode can opt out of this redaction if required.
    $safe = [regex]::Replace(
        $safe,
        '(?<![0-9])(?:25[0-5]|2[0-4][0-9]|1?[0-9]{1,2})(?:\.(?:25[0-5]|2[0-4][0-9]|1?[0-9]{1,2})){3}(?![0-9])',
        '<IPV4_REDACTED>')

    # Remove the local Windows account name from absolute user-profile paths.
    $safe = [regex]::Replace(
        $safe,
        '(?i)([A-Z]:\\Users\\)[^\\\s]+',
        '$1<USER>')

    return $safe
}

function Convert-OpenShimSupportLogLine {
    param([Parameter(Mandatory = $true)][string]$Line)

    # Current shim_log.cpp format:
    # [2026-09-04T20:04:31.118Z] [pid:123 tid:456] [INFO] [hooks] message
    $pattern = '^\[([^\]]+)\]\s+\[pid:(\d+)\s+tid:(\d+)\]\s+\[([^\]]+)\]\s+\[([^\]]+)\]\s?(.*)$'
    if ($Line -match $pattern) {
        return [ordered]@{
            dt        = $Matches[1]
            pid       = [int64]$Matches[2]
            tid       = [int64]$Matches[3]
            level     = $Matches[4]
            component = $Matches[5]
            message   = Protect-OpenShimSupportText $Matches[6]
        }
    }

    return [ordered]@{
        dt        = [DateTime]::UtcNow.ToString('o')
        level     = 'INFO'
        component = 'raw'
        message   = Protect-OpenShimSupportText $Line
    }
}

function New-OpenShimSupportHttpClient {
    param([int]$TimeoutSeconds = 15)

    Add-Type -AssemblyName System.Net.Http -ErrorAction SilentlyContinue
    $client = New-Object System.Net.Http.HttpClient
    $client.Timeout = [TimeSpan]::FromSeconds($TimeoutSeconds)
    return $client
}

function Invoke-OpenShimSupportJsonPost {
    param(
        [Parameter(Mandatory = $true)][string]$Uri,
        [Parameter(Mandatory = $true)]$Body,
        [string]$BearerToken = "",
        [int]$TimeoutSeconds = 15
    )

    $client = $null
    try {
        $client = New-OpenShimSupportHttpClient -TimeoutSeconds $TimeoutSeconds
        if ($BearerToken) {
            $client.DefaultRequestHeaders.Authorization =
                New-Object System.Net.Http.Headers.AuthenticationHeaderValue('Bearer', $BearerToken)
        }

        $json = $Body | ConvertTo-Json -Depth 8 -Compress
        $content = New-Object System.Net.Http.StringContent(
            $json,
            [System.Text.Encoding]::UTF8,
            'application/json')

        $response = $client.PostAsync($Uri, $content).GetAwaiter().GetResult()
        $responseText = $response.Content.ReadAsStringAsync().GetAwaiter().GetResult()
        if (-not $response.IsSuccessStatusCode) {
            return [pscustomobject]@{
                Ok         = $false
                StatusCode = [int]$response.StatusCode
                Body       = $responseText
                Value      = $null
            }
        }

        $value = $null
        if ($responseText) {
            try { $value = $responseText | ConvertFrom-Json } catch { }
        }
        return [pscustomobject]@{
            Ok         = $true
            StatusCode = [int]$response.StatusCode
            Body       = $responseText
            Value      = $value
        }
    } catch {
        return [pscustomobject]@{
            Ok         = $false
            StatusCode = 0
            Body       = $_.Exception.Message
            Value      = $null
        }
    } finally {
        if ($client) { $client.Dispose() }
    }
}

function New-OpenShimSupportSession {
    param(
        [Parameter(Mandatory = $true)][string]$Endpoint,
        [string]$Platform = 'windows',
        [string]$Distribution = 'unknown',
        [string]$WrapperVersion = 'unknown',
        [string]$OpenShimVersion = '',
        [string]$OpenShimCommit = '',
        [string]$GameVersion = '',
        [string]$ExeSha256 = ''
    )

    $body = [ordered]@{
        protocol         = 1
        platform         = $Platform
        distribution     = $Distribution
        wrapper_version  = $WrapperVersion
    }
    if ($OpenShimVersion) { $body.openshim_version = $OpenShimVersion }
    if ($OpenShimCommit)  { $body.openshim_commit = $OpenShimCommit }
    if ($GameVersion)     { $body.game_version = $GameVersion }
    if ($ExeSha256)       { $body.exe_sha256 = $ExeSha256 }

    $response = Invoke-OpenShimSupportJsonPost -Uri ($Endpoint.TrimEnd('/') + '/v1/session') -Body $body
    if (-not $response.Ok -or -not $response.Value -or
        -not $response.Value.support_id -or -not $response.Value.session_token) {
        return [pscustomobject]@{
            Ok         = $false
            StatusCode = $response.StatusCode
            Error      = $response.Body
            SupportId  = ''
            Token      = ''
        }
    }

    return [pscustomobject]@{
        Ok         = $true
        StatusCode = $response.StatusCode
        Error      = ''
        SupportId  = [string]$response.Value.support_id
        Token      = [string]$response.Value.session_token
        ExpiresAt  = [string]$response.Value.expires_at
    }
}

function Send-OpenShimSupportLogBatch {
    param(
        [Parameter(Mandatory = $true)][string]$Endpoint,
        [Parameter(Mandatory = $true)][string]$SupportId,
        [Parameter(Mandatory = $true)][string]$Token,
        [Parameter(Mandatory = $true)][int64]$Sequence,
        [Parameter(Mandatory = $true)][object[]]$Events
    )

    if ($Events.Count -eq 0) { return $true }
    $body = [ordered]@{ sequence = $Sequence; events = $Events }
    $uri = '{0}/v1/session/{1}/logs' -f $Endpoint.TrimEnd('/'), $SupportId
    $response = Invoke-OpenShimSupportJsonPost -Uri $uri -Body $body -BearerToken $Token
    return [bool]$response.Ok
}

function Send-OpenShimSupportArtifact {
    param(
        [Parameter(Mandatory = $true)][string]$Endpoint,
        [Parameter(Mandatory = $true)][string]$SupportId,
        [Parameter(Mandatory = $true)][string]$Token,
        [Parameter(Mandatory = $true)][string]$FilePath,
        [string]$ArtifactName = ''
    )

    if (-not (Test-Path -LiteralPath $FilePath -PathType Leaf)) { return $false }
    if (-not $ArtifactName) { $ArtifactName = [System.IO.Path]::GetFileName($FilePath) }

    $client = $null
    $stream = $null
    try {
        $client = New-OpenShimSupportHttpClient -TimeoutSeconds 300
        $client.DefaultRequestHeaders.Authorization =
            New-Object System.Net.Http.Headers.AuthenticationHeaderValue('Bearer', $Token)
        $client.DefaultRequestHeaders.Add('X-Artifact-Name', $ArtifactName)

        $stream = [System.IO.File]::Open(
            $FilePath,
            [System.IO.FileMode]::Open,
            [System.IO.FileAccess]::Read,
            [System.IO.FileShare]::ReadWrite)
        $content = New-Object System.Net.Http.StreamContent($stream)
        $content.Headers.ContentType =
            New-Object System.Net.Http.Headers.MediaTypeHeaderValue('application/octet-stream')

        $uri = '{0}/v1/session/{1}/artifact' -f $Endpoint.TrimEnd('/'), $SupportId
        $response = $client.PostAsync($uri, $content).GetAwaiter().GetResult()
        return [bool]$response.IsSuccessStatusCode
    } catch {
        return $false
    } finally {
        if ($stream) { $stream.Dispose() }
        if ($client) { $client.Dispose() }
    }
}

function Complete-OpenShimSupportSession {
    param(
        [Parameter(Mandatory = $true)][string]$Endpoint,
        [Parameter(Mandatory = $true)][string]$SupportId,
        [Parameter(Mandatory = $true)][string]$Token,
        [int]$ExitCode = 0,
        [bool]$CleanExit = $false,
        [bool]$Crashed = $false,
        [int64]$FinalSequence = -1,
        [string[]]$Artifacts = @()
    )

    $body = [ordered]@{
        exit_code      = $ExitCode
        clean_exit     = $CleanExit
        crashed        = $Crashed
        final_sequence = $FinalSequence
        artifacts      = $Artifacts
    }
    $uri = '{0}/v1/session/{1}/finish' -f $Endpoint.TrimEnd('/'), $SupportId
    $response = Invoke-OpenShimSupportJsonPost -Uri $uri -Body $body -BearerToken $Token
    return [bool]$response.Ok
}
