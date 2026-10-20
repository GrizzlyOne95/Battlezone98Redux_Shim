-- Temporary perf harness (replaces crsetup.lua in the test install only; restored after the run).
local RequireFix = require("RequireFix")
RequireFix.Initialize({"campaignReimagined", "3686673790"})
local exu = require("exu")
local Environment = require("Environment")
local CRMarsWeather = require("CRMarsWeather")
local forced = false
local lastTime = nil

function Start()
    local p = GetPlayerHandle()
    if IsValid(p) then SetIndependence(p, 0) end
    if Environment and Environment.Init then Environment.Init() end
    CRMarsWeather.Init({ startLevel = 5, targetLevel = 5, windPush = false })
    if CRMarsWeather.SetAutomatic then CRMarsWeather.SetAutomatic(false) end
    print("[wxperf] harness start exu=" .. tostring(exu ~= nil))
end

function Update()
    local now = GetTime()
    local dt = lastTime and (now - lastTime) or 0.0
    lastTime = now
    if not forced and GetTime() > 3 then
        forced = true
        print("[wxperf] force severe " .. tostring(CRMarsWeather.ForceLevel(5, 86400, 2.0)))
    end
    CRMarsWeather.Update(dt)
    if Environment and Environment.Update then Environment.Update(dt) end
    local p = GetPlayerHandle()
    if IsValid(p) then SetCurHealth(p, GetMaxHealth(p)) end
end
