-- rmplight.lua -- lcbench pilot-flashlight scene-light A/B fixture.
--
-- Deploy as addon/lcbench/lcbench.lua and launch
-- `battlezone98redux.exe lcbench.bzn` (bare basename: the engine truncates the
-- mission argument to 15 characters, so a path never survives).
--
-- Why this fixture exists
-- -----------------------
-- A 2026-09-13 capture on play01.bzn showed the whole 3D scene stepping
-- between two light levels, exactly co-timed with boarding and leaving a
-- craft. Measured on a fixed terrain patch the two levels were 70.0 and 39.3
-- of 255 -- a ~2.4x step, with unchanged shading contrast, unchanged hue, pure
-- black preserved, and the sky dome bit-identical across the step. The HUD was
-- unaffected. The only thing whose lifetime matches every transition is the
-- shim's own pilot flashlight (`[SinglePlayer] PilotFlashlight`), which exists
-- while the player is on foot and is retired ~200 ms after boarding.
--
-- This fixture makes that transition happen on a timer with the view held
-- still, so the same frames can be captured with the feature ON and OFF and
-- compared numerically. The camera is never driven: an A/B is only meaningful
-- if both arms photograph the same geometry.
--
-- Timeline
--   T+0    START        -- in a craft, craft headlight owns the scene
--   T+8    HOP_OUT      -- on foot; the shim creates the pilot flashlight
--   T+26   BOARD        -- back in the craft via exu.SetAsUser, if EXU is
--                          present; the flashlight is retired
--   forever HEARTBEAT   -- never fails the mission, so the runner owns the
--                          process lifetime and can stop it cleanly
--
-- The board leg is a bonus, not a gate. Plain BZ has no Lua API for entering a
-- craft, so it is pcall-guarded through ExtraUtilities and the fixture still
-- produces a usable A/B when EXU is absent -- the hop-out leg alone changes the
-- flashlight's existence, which is the variable under test.
--
-- Lua 5.1 (no goto, no io/os/debug). Markers use print(), like the sibling
-- harnesses in this folder.

local elapsed = 0.0
local craft = nil
local hopped = false
local hopAttempts = 0
local pilotReady = false
local boarded = false
local boardAttempts = 0
local nextHeartbeat = 0.0

local HOP_AT = 8.0
local BOARD_AT = 26.0

local function Marker(text)
    print(string.format("[PLIGHT] T+%.2f %s", elapsed, text))
end

-- ExtraUtilities exposes GameObject::SetAsUser as exu.SetAsUser
-- (src/luaexport.cpp:673). It is the only scripted route back into a craft.
-- Resolved lazily: `exu` may be registered after this chunk runs.
local function TrySetAsUser(handle)
    local mod = rawget(_G, "exu")
    if mod == nil then
        local ok, required = pcall(require, "exu")
        if ok then mod = required end
    end
    if mod == nil or mod.SetAsUser == nil then
        return false, "no-exu"
    end
    local ok = pcall(mod.SetAsUser, handle)
    return ok, "exu.SetAsUser"
end

local function IsPilot(handle)
    local result = false
    if handle ~= nil and IsValid(handle) then
        pcall(function() result = IsPerson(handle) end)
    end
    return result
end

function Start()
    elapsed = 0.0
    craft = nil
    hopped = false
    hopAttempts = 0
    pilotReady = false
    boarded = false
    boardAttempts = 0
    nextHeartbeat = 0.0
    Marker("START pilot-flashlight scene-light fixture")
end

function Update(dt)
    elapsed = elapsed + (dt or 0.0)

    -- Remember the craft before hopping out: HopOut replaces the player
    -- object, so GetPlayerHandle stops naming the craft immediately after.
    if craft == nil and not hopped then
        local h = GetPlayerHandle()
        if h ~= nil and IsValid(h) and not IsPilot(h) then
            craft = h
            Marker("CRAFT_CAPTURED")
        end
    end

    if not hopped and elapsed >= HOP_AT and hopAttempts < 20 then
        local h = GetPlayerHandle()
        if h ~= nil and IsValid(h) then
            hopAttempts = hopAttempts + 1
            local ok = pcall(HopOut, h)
            Marker(string.format("HOP_OUT attempt=%d ok=%s", hopAttempts, tostring(ok)))
            hopped = ok
        end
    end

    if hopped and not pilotReady then
        if IsPilot(GetPlayerHandle()) then
            pilotReady = true
            Marker("PILOT_READY on foot -- flashlight window opens here")
        end
    end

    if pilotReady and not boarded and elapsed >= BOARD_AT and boardAttempts < 20 then
        boardAttempts = boardAttempts + 1
        if craft ~= nil and IsValid(craft) then
            local ok, how = TrySetAsUser(craft)
            Marker(string.format("BOARD attempt=%d ok=%s via=%s",
                boardAttempts, tostring(ok), how))
            if ok then boarded = true end
        else
            Marker(string.format("BOARD attempt=%d skipped: craft handle is gone",
                boardAttempts))
            boarded = true
        end
    end

    if elapsed >= nextHeartbeat then
        nextHeartbeat = elapsed + 5.0
        local h = GetPlayerHandle()
        Marker(string.format("HEARTBEAT valid=%s onFoot=%s hopped=%s boarded=%s",
            tostring(h ~= nil and IsValid(h)), tostring(IsPilot(h)),
            tostring(hopped), tostring(boarded)))
    end
end

function CreateObject(h) end
function AddObject(h) end
function DeleteObject(h) end

function Save()
    return elapsed, hopped, pilotReady, boarded
end

function Load(a, b, c, d)
    elapsed = a or 0.0
    hopped = b or false
    pilotReady = c or false
    boarded = d or false
end
