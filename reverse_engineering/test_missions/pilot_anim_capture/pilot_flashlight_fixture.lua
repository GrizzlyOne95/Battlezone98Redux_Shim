-- pilot_flashlight_fixture.lua
--
-- Minimal, endless on-foot fixture for the pilot flashlight siting probe.
-- Deploy as addon/lcbench/lcbench.lua (basename must match the .bzn), then
-- launch `battlezone98redux.exe addon/lcbench/lcbench.bzn`.
--
-- Unlike pilot_test.lua this drives no timeline and never fails the mission:
-- the probe needs a live pilot that stays alive long enough to attach Frida
-- and to observe the view being moved by hand.
--
-- Lua 5.1 (no goto, no io/os/debug). Markers use print(), like the sibling
-- harnesses in this folder.

local elapsed = 0.0
local hopped = false
local hopAttempts = 0
local announced = false
local nextHeartbeat = 0.0

local function Marker(text)
    print(string.format("[PFLFIX] T+%.2f %s", elapsed, text))
end

function Start()
    elapsed = 0.0
    hopped = false
    hopAttempts = 0
    announced = false
    nextHeartbeat = 0.0
    Marker("START endless pilot fixture")
end

function Update(dt)
    elapsed = elapsed + (dt or 0.0)

    if not hopped and elapsed >= 3.0 and hopAttempts < 20 then
        local h = GetPlayerHandle()
        if h ~= nil and IsValid(h) then
            hopAttempts = hopAttempts + 1
            local ok = pcall(HopOut, h)
            Marker(string.format("HOP_OUT attempt=%d ok=%s", hopAttempts, tostring(ok)))
            -- HopOut replaces the player object; confirm on a later frame.
            hopped = ok
        end
    end

    if hopped and not announced then
        local h = GetPlayerHandle()
        if h ~= nil and IsValid(h) then
            local isPerson = false
            pcall(function() isPerson = IsPerson(h) end)
            if isPerson then
                announced = true
                Marker("PILOT_READY -- probe may attach; move the view now")
            end
        end
    end

    if elapsed >= nextHeartbeat then
        nextHeartbeat = elapsed + 10.0
        local h = GetPlayerHandle()
        local valid = (h ~= nil and IsValid(h))
        local isPerson = false
        if valid then pcall(function() isPerson = IsPerson(h) end) end
        Marker(string.format("HEARTBEAT valid=%s isPerson=%s",
            tostring(valid), tostring(isPerson)))
    end
end

function CreateObject(h) end
function AddObject(h) end
function DeleteObject(h) end

function Save()
    return elapsed, hopped, announced
end

function Load(a, b, c)
    elapsed = a or 0.0
    hopped = b or false
    announced = c or false
end
