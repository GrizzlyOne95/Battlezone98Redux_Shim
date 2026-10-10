# Any mission: preview a camera path with several height/speed/target values
# and screenshot each, to tune a film without playing up to it. Runs the
# native camera on the host only (nothing is sent to the guest).
#
#   Run-BZRCoopMission.ps1 -Mission misn04 -Scenario film-preview -ScenarioArgs @{
#       Path = 'endcin'; Variants = @('100,200,M.avrec', '8000,9000,center') }
#
# A variant is "height,speed,target": height and speed in the units
# CameraPath takes (cm above the path, cm/s); target is a Lua expression for
# the handle to look at, or "center" for a camera pod placed on the ground at
# the middle of the path. Shots land in flow-shots\ (one step per sample).
param([int]$HostClient = 0,
      [Parameter(Mandatory)][string]$Path,
      [string[]]$Variants = @('100,200,center'),
      [int[]]$SampleSeconds = @(3, 8, 14, 19),
      # M fields healed every half second so an idle mission is not lost.
      [string[]]$Protect = @(),
      # x,z of the "center" target when the build has no GetPathPoints.
      [double[]]$Center = @())

$H = $HostClient
$script:CRFlowSkipParity = $true

Invoke-CRFlowStep 'probe attached; protect the mission and hide the PDA' {
    Wait-CRFlowEvent $H attach -TimeoutSeconds 120 | Out-Null
    $keep = ($Protect | ForEach-Object { "`"$_`"" }) -join ', '
    Invoke-CRFlow $H @"
every('protect', 0.5, function()
    for _, k in ipairs({ $keep }) do if M[k] then heal(M[k]) end end
    for h in AllCraft() do if GetTeamNum(h) <= 4 and GetTeamNum(h) > 0 then heal(h) end end
end)
local pc = package.loaded.PersistentConfig
if pc and pc._SettingsActions and pc._SettingsActions.SetWeaponStatsHudEnabled then
    pcall(pc._SettingsActions.SetWeaponStatsHudEnabled, false)
end
-- Middle of the path, on the ground, as a look-at target.
local pts = GetPathPoints and GetPathPoints('$Path')
local cx, cz, n = 0, 0, 0
if type(pts) == 'table' then for _, p in ipairs(pts) do cx, cz, n = cx + p.x, cz + p.z, n + 1 end end
$(if ($Center.Count -eq 2) { "cx, cz, n = $($Center[0]), $($Center[1]), 1" })
if n > 0 then
    cx, cz = cx / n, cz / n
    local y = GetTerrainHeightAndNormal(SetVector(cx, 0, cz))
    center = BuildObject('apcamr', 0, SetVector(cx, y, cz))
end
return { points = n, center = n > 0 and { cx, cz } or nil }
"@
}

foreach ($v in $Variants) {
    $height, $speed, $target = $v -split ',', 3
    Invoke-CRFlowStep "film $Path h=$height s=$speed look=$target start" {
        Invoke-CRFlow $H "filmTarget = $target; native.CameraReady(); every('film', 0, function() native.CameraPath('$Path', $height, $speed, filmTarget) end); return IsValid(filmTarget)"
    }
    $t0 = Get-Date
    foreach ($s in $SampleSeconds) {
        $wait = $s - ((Get-Date) - $t0).TotalSeconds
        if ($wait -gt 0) { Start-Sleep -Milliseconds ([int]($wait * 1000)) }
        Invoke-CRFlowStep "film $Path h=$height s=$speed look=$target t=${s}s" { "sample" }
    }
    Invoke-CRFlowStep "film $Path h=$height s=$speed look=$target end" {
        Invoke-CRFlow $H "cancel('film'); native.CameraFinish(); return true"
    }
}
