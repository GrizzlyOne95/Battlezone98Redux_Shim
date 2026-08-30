-- fpstock.lua
-- Lua 5.1 stock-animation qualification for exu.animation.TargetLocalFirstPerson.
-- Deploy as addon/lcbench/lcbench.lua (engine-visible basename remains <=8 chars).
-- No custom clips and no manual player-control input are used.

local elapsed = 0.0
local stage = 0
local pilot = nil
local fp = nil
local exu = nil
local exuReady = false

local function Result(ok, value)
    if not ok then return "error:" .. tostring(value) end
    return tostring(value)
end

local function InfoText(target, animation)
    local ok, info = pcall(function()
        return exu.animation.GetInfo(target, animation)
    end)
    if not ok then return "error:" .. tostring(info) end
    if info == nil then return "nil" end
    return string.format("en=%s loop=%s w=%.3f t=%.3f len=%.3f nrm=%.3f",
        tostring(info.enabled), tostring(info.loop), info.weight or 0.0,
        info.timePosition or 0.0, info.length or 0.0,
        info.normalizedTime or 0.0)
end

local function Snapshot(label, animation)
    local worldText = pilot and InfoText(pilot, animation) or "no-pilot"
    local fpText = fp and InfoText(fp, animation) or "no-fp-descriptor"
    print(string.format("[FPSTOCK] T+%.3f %s anim=%s WORLD{%s} FP{%s}",
        elapsed, label, animation, worldText, fpText))
end

local function Invoke(label, fn)
    local ok, value = pcall(fn)
    print(string.format("[FPSTOCK] T+%.3f %s ok=%s result=%s",
        elapsed, label, tostring(ok), Result(ok, value)))
    return ok and value
end

local function HalfTime(target, animation)
    local ok, info = pcall(function()
        return exu.animation.GetInfo(target, animation)
    end)
    if not ok or info == nil or not info.length or info.length <= 0 then
        return 0.25
    end
    return info.length * 0.5
end

local function HoldPose(target, animation)
    local half = HalfTime(target, animation)
    pcall(function()
        exu.animation.SetLoop(target, animation, true)
        exu.animation.SetWeight(target, animation, 1.0)
        exu.animation.SetEnabled(target, animation, true)
        exu.animation.Seek(target, animation, half)
    end)
end

function Start()
    elapsed = 0.0
    stage = 0
    local ok, loaded = pcall(require, "exu")
    exuReady = ok and loaded ~= nil and loaded.animation ~= nil
    exu = loaded
    print(string.format("[FPSTOCK] T+0.000 START exuReady=%s require=%s",
        tostring(exuReady), Result(ok, loaded)))
    if not exuReady then
        FailMission(GetTime() + 1.0)
        stage = 99
        return
    end

    fp = exu.animation.TargetLocalFirstPerson()
    local caps = exu.animation.GetCapabilities()
    print(string.format("[FPSTOCK] T+0.000 CAPS gameObject=%s fp=%s clock=%s native=%s status=%s",
        tostring(caps.gameObjectTarget), tostring(caps.localFirstPersonTarget),
        tostring(caps.managedClock), tostring(caps.nativeAdvancement),
        tostring(caps.firstPersonStatus)))

    -- lcbench starts in a vehicle. A missing FP entity must fail closed here.
    Invoke("MISSING_HAS", function() return exu.animation.Has(fp, "stand2Kneel") end)
    Invoke("MISSING_PLAY", function()
        return exu.animation.Play(fp, "stand2Kneel", {restart=true, loop=false, weight=1.0})
    end)
    local missingInfo = exu.animation.GetInfo(fp, "stand2Kneel")
    print(string.format("[FPSTOCK] T+0.000 MISSING_INFO nil=%s", tostring(missingInfo == nil)))
end

function Update(dt)
    elapsed = elapsed + (dt or 0.0)
    if stage == 99 then return end

    if stage == 0 and elapsed >= 2.0 then
        local vehicle = GetPlayerHandle()
        local ok, value = pcall(HopOut, vehicle)
        print(string.format("[FPSTOCK] T+%.3f HOP_OUT vehicle=%s ok=%s result=%s",
            elapsed, tostring(vehicle), tostring(ok), Result(ok, value)))
        stage = 1
        return
    end

    if stage == 1 then
        local current = GetPlayerHandle()
        if IsValid(current) and IsPerson(current) then
            pilot = current
            print(string.format("[FPSTOCK] T+%.3f PILOT_ACQUIRED handle=%s", elapsed, tostring(pilot)))
            stage = 2
        elseif elapsed >= 7.0 then
            print(string.format("[FPSTOCK] T+%.3f FAIL no local Person after HopOut", elapsed))
            FailMission(GetTime() + 1.0)
            stage = 99
        end
        return
    end

    if stage == 2 and elapsed >= 4.0 then
        local names = {"idle", "stand2Kneel", "kneel2stand", "fireRecoilSniper", "jump", "runForward", "landParachute"}
        local i
        for i = 1, #names do
            local name = names[i]
            local worldHas = exu.animation.Has(pilot, name)
            local fpHas = exu.animation.Has(fp, name)
            print(string.format("[FPSTOCK] T+%.3f INVENTORY anim=%s world=%s fp=%s",
                elapsed, name, tostring(worldHas), tostring(fpHas)))
        end
        Snapshot("BASELINE", "stand2Kneel")
        stage = 3
        return
    end

    if stage == 3 and elapsed >= 5.0 then
        Invoke("FP_PLAY", function()
            return exu.animation.Play(fp, "stand2Kneel", {restart=true, loop=true, weight=1.0})
        end)
        local half = HalfTime(fp, "stand2Kneel")
        Invoke("FP_SEEK_HALF", function() return exu.animation.Seek(fp, "stand2Kneel", half) end)
        Snapshot("FP_IMMEDIATE", "stand2Kneel")
        print(string.format("[FPSTOCK] T+%.3f FP_VISIBLE_WINDOW_BEGIN", elapsed))
        stage = 4
        return
    end

    if stage == 4 then
        HoldPose(fp, "stand2Kneel")
        if elapsed >= 12.0 then
            Snapshot("FP_HELD_WORLD_UNTOUCHED", "stand2Kneel")
            Invoke("FP_STOP", function() return exu.animation.Stop(fp, "stand2Kneel", true) end)
            Snapshot("FP_STOPPED", "stand2Kneel")
            print(string.format("[FPSTOCK] T+%.3f FP_VISIBLE_WINDOW_END", elapsed))
            stage = 5
        end
        return
    end

    if stage == 5 and elapsed >= 13.0 then
        Invoke("WORLD_PLAY", function()
            return exu.animation.Play(pilot, "stand2Kneel", {restart=true, loop=true, weight=1.0})
        end)
        local half = HalfTime(pilot, "stand2Kneel")
        Invoke("WORLD_SEEK_HALF", function() return exu.animation.Seek(pilot, "stand2Kneel", half) end)
        Snapshot("WORLD_IMMEDIATE", "stand2Kneel")
        stage = 6
        return
    end

    if stage == 6 then
        HoldPose(pilot, "stand2Kneel")
        if elapsed >= 17.0 then
            Snapshot("WORLD_HELD_FP_UNTOUCHED", "stand2Kneel")
            Invoke("WORLD_STOP", function() return exu.animation.Stop(pilot, "stand2Kneel", true) end)
            Snapshot("WORLD_STOPPED", "stand2Kneel")
            stage = 7
        end
        return
    end

    if stage == 7 and elapsed >= 18.0 then
        Invoke("FP_RECOIL_PLAY", function()
            return exu.animation.Play(fp, "fireRecoilSniper", {restart=true, loop=false, weight=1.0})
        end)
        local half = HalfTime(fp, "fireRecoilSniper")
        Invoke("FP_RECOIL_SEEK_HALF", function() return exu.animation.Seek(fp, "fireRecoilSniper", half) end)
        Snapshot("FP_RECOIL_IMMEDIATE", "fireRecoilSniper")
        stage = 8
        return
    end

    if stage == 8 and elapsed >= 19.0 then
        Invoke("FP_RECOIL_STOP", function() return exu.animation.Stop(fp, "fireRecoilSniper", true) end)
        Snapshot("FP_RECOIL_STOPPED", "fireRecoilSniper")
        stage = 9
        return
    end

    if stage == 9 and elapsed >= 21.0 then
        -- No persistent override exists. Observe stock state after all controls stop.
        Snapshot("GAMEPLAY_REGAIN", "idle")
        Snapshot("GAMEPLAY_REGAIN", "stand2Kneel")
        print(string.format("[FPSTOCK] T+%.3f LIFETIME_FAILMISSION", elapsed))
        FailMission(GetTime() + 1.0)
        stage = 10
        return
    end
end

function CreateObject(h) end
function AddObject(h) end
function DeleteObject(h) end
function CreatePlayer(id, name, team) end
function AddPlayer(id, name, team) end
function DeletePlayer(id, name, team) end
