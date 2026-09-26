-- rmtug.lua -- lcbench fixture for the OpenShim [BuildingClass] tuggable = 1 key.
--
-- Deploy as addon/lcbench/lcbench.lua next to tugpow.odf and tugctl.odf, then
-- launch `battlezone98redux.exe lcbench.bzn` (see run_lctug.ps1).
--
-- tugpow, tugzro and tugctl are AbsoZero's battery PowerPlant (addon/AbsoZero/
-- abstor.odf, minus its 10 s lifespan) under their own names. tugpow adds
-- `tuggable = 1`, tugzro adds `tuggable = 0`, and tugctl has no key. Stock
-- `abstor` is the positive control: Building::Building hard-codes it
-- tuggable by filename.
--
-- Four phases run in order, each with a freshly spawned Tug so a Tug left
-- stuck on a refused pickup cannot fail the next phase. HasCargo/GetCargo are
-- the witness:
--   POW  Pickup(tug, tugpow)  -- expected: picked up (the extension works)
--   ZRO  Pickup(tug, tugzro)  -- expected: never picked up (explicit 0)
--   CTL  Pickup(tug, tugctl)  -- expected: never picked up (no key, no effect)
--   STK  Pickup(tug, abstor)  -- expected: picked up (stock behaviour intact)
-- A phase ends as soon as cargo appears or after PHASE_TIMEOUT seconds; a
-- picked-up building is dropped off before the next phase starts. TICK lines
-- carry the Tug-to-target distance and command, so a timeout can be told apart
-- from a Tug that never reached its target.
--
-- Lua 5.1 (no goto, no io/os/debug).

local TUG_ODF = "avhaul"
local MY_TEAM = 1
local PHASE_TIMEOUT = 35.0
local DROP_SETTLE = 25.0

local elapsed = 0.0
local tug = nil
local targets = {}
local phases = {
    { key = "POW", odf = "tugpow", expect = true },
    { key = "ZRO", odf = "tugzro", expect = false },
    { key = "CTL", odf = "tugctl", expect = false },
    { key = "STK", odf = "abstor", expect = true },
}
local phaseIndex = 0
local phaseStart = 0.0
local phaseState = "idle"   -- idle | ordered | dropping
local spawned = false
local finished = false
local nextHeartbeat = 0.0

local function Marker(text)
    print(string.format("[TUGFIX] T+%.2f %s", elapsed, text))
end

local function Safe(fn, ...)
    local ok, value = pcall(fn, ...)
    if ok then return value end
    return nil
end

local function OdfOf(handle)
    if handle == nil or not IsValid(handle) then return "<none>" end
    return tostring(Safe(GetOdf, handle))
end

local function AnchorPosition()
    local player = GetPlayerHandle()
    if player ~= nil and IsValid(player) then
        local where = Safe(GetPosition, player)
        if where ~= nil then return where end
    end
    return SetVector(0, 0, 0)
end

local function Spawn(odf, distance, label)
    local where = Safe(GetPositionNear, AnchorPosition(), distance, distance + 6)
    if where == nil then
        Marker(string.format("SPAWN_%s FAILED: no position", label))
        return nil
    end
    local handle = Safe(BuildObject, odf, MY_TEAM, where)
    if handle == nil or not IsValid(handle) then
        Marker(string.format("SPAWN_%s FAILED: BuildObject(%s) returned nothing", label, odf))
        return nil
    end
    Marker(string.format("SPAWN_%s odf=%s class=%s", label, OdfOf(handle),
        tostring(Safe(GetClassLabel, handle))))
    return handle
end

local function Cargo()
    if tug == nil or not IsValid(tug) then return nil end
    if not Safe(HasCargo, tug) then return nil end
    return Safe(GetCargo, tug)
end

local function StartPhase(index)
    phaseIndex = index
    phaseStart = elapsed
    local phase = phases[index]
    if phase == nil then
        finished = true
        Marker("DONE")
        return
    end
    local target = targets[phase.odf]
    if target == nil or not IsValid(target) then
        Marker(string.format("RESULT %s odf=%s SKIPPED: target missing", phase.key, phase.odf))
        StartPhase(index + 1)
        return
    end
    tug = Spawn(TUG_ODF, 20.0, "TUG_" .. phase.key)
    if tug == nil then
        Marker(string.format("RESULT %s odf=%s SKIPPED: no tug", phase.key, phase.odf))
        StartPhase(index + 1)
        return
    end
    local ok = pcall(Pickup, tug, target, 1)
    phaseState = "ordered"
    Marker(string.format("ORDER %s Pickup(tug, %s) ok=%s", phase.key, phase.odf, tostring(ok)))
end

function Start()
    Marker("START tuggable building fixture")
end

function Update(dt)
    elapsed = elapsed + (dt or 0.0)
    if finished then return end

    if not spawned and elapsed >= 2.0 then
        spawned = true
        targets.tugpow = Spawn("tugpow", 45.0, "TUGPOW")
        targets.tugzro = Spawn("tugzro", 60.0, "TUGZRO")
        targets.tugctl = Spawn("tugctl", 75.0, "TUGCTL")
        targets.abstor = Spawn("abstor", 95.0, "ABSTOR")
        return
    end

    if spawned and phaseIndex == 0 and elapsed >= 4.0 then
        StartPhase(1)
        return
    end

    local phase = phases[phaseIndex]
    if phase == nil then return end

    if phaseState == "ordered" then
        local cargo = Cargo()
        if cargo ~= nil then
            local got = OdfOf(cargo)
            local verdict = phase.expect and "PASS" or "FAIL"
            Marker(string.format("RESULT %s odf=%s picked_up=true cargo=%s after=%.1fs %s",
                phase.key, phase.odf, got, elapsed - phaseStart, verdict))
            pcall(Dropoff, tug, GetPositionNear(AnchorPosition(), 30.0, 40.0), 1)
            phaseState = "dropping"
            phaseStart = elapsed
        elseif elapsed - phaseStart >= PHASE_TIMEOUT then
            local verdict = phase.expect and "FAIL" or "PASS"
            Marker(string.format("RESULT %s odf=%s picked_up=false after=%.1fs %s",
                phase.key, phase.odf, elapsed - phaseStart, verdict))
            pcall(Stop, tug, 1)
            StartPhase(phaseIndex + 1)
        end
    elseif phaseState == "dropping" then
        if Cargo() == nil or elapsed - phaseStart >= DROP_SETTLE then
            Marker(string.format("DROPPED %s cargo_left=%s", phase.key, tostring(Cargo() == nil)))
            StartPhase(phaseIndex + 1)
        end
    end

    if elapsed >= nextHeartbeat then
        nextHeartbeat = elapsed + 5.0
        local target = targets[phase.odf]
        local dist = -1
        if tug ~= nil and IsValid(tug) and target ~= nil and IsValid(target) then
            dist = Safe(GetDistance, tug, target) or -1
        end
        local cmd = tug ~= nil and IsValid(tug) and Safe(GetCurrentCommand, tug) or nil
        Marker(string.format("TICK phase=%s state=%s cargo=%s dist=%.1f cmd=%s",
            phase.key, phaseState, OdfOf(Cargo()), dist, tostring(cmd)))
    end
end
