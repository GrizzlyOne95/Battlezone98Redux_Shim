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
--   T+26   BOARD        -- the craft is parked in front of the pilot and
--                          driven into them with SetVelocity until they board
--   forever HEARTBEAT   -- never fails the mission, so the runner owns the
--                          process lifetime and can stop it cleanly
--
-- The board leg matters as much as the hop-out: the shim's [PILOTTEAM] probe
-- watches the pilot object ACROSS the boarding call, which is the only moment
-- GameObject::SetAsNotUser can be caught resetting the pilot's team. An earlier
-- revision tried to board through exu.SetAsUser, which is not reachable from an
-- addon mission chunk, so the leg silently never ran and the probe only ever
-- sampled the pilot standing around. See the boarding helpers below.
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
local parked = false
local nextHeartbeat = 0.0

local HOP_AT = 8.0
local BOARD_AT = 26.0

local function Marker(text)
    print(string.format("[PLIGHT] T+%.2f %s", elapsed, text))
end

-- Boarding, without any API for boarding.
--
-- `exu.SetAsUser` is NOT reachable from an addon mission chunk: exu.dll loads
-- but this fixture logged `BOARD ok=false via=no-exu` on twenty consecutive
-- attempts, and every heartbeat afterwards still read onFoot=true. `input.map`
-- has no enter-vehicle action either -- an on-foot pilot boards by walking into
-- the craft. So the boarding leg used to be a no-op, which is why the first
-- [PILOTTEAM] run measured the pilot standing around and never the transition.
--
-- Instead: park the player's own abandoned craft just in front of the pilot and
-- drive it into them with SetVelocity. The collision is the same one walking
-- into it produces, and the craft is genuinely empty because the player just
-- hopped out of it -- which also means it is carrying the perceivedTeam = 0
-- that Craft::AbandonPilot writes, exactly as in the reported repro.
--
-- Speed is deliberately low. Craft::ExplodePilot exists and plays squish.wav,
-- so a tank driven hard into a pilot may kill them rather than be boarded; the
-- outcome check below tells the two apart instead of assuming.
local NUDGE_SPEED = 4.0
local PARK_DISTANCE = 8.0

local function Vec(x, y, z)
    local v = nil
    pcall(function() v = SetVector(x, y, z) end)
    return v
end

-- Push `craftHandle` toward `targetHandle` at NUDGE_SPEED. Returns the
-- separation so the caller can log the approach.
local function NudgeToward(craftHandle, targetHandle)
    local cp, tp = nil, nil
    if not pcall(function() cp = GetPosition(craftHandle) end) or cp == nil then return nil end
    if not pcall(function() tp = GetPosition(targetHandle) end) or tp == nil then return nil end
    local dx, dz = tp.x - cp.x, tp.z - cp.z
    local flat = math.sqrt(dx * dx + dz * dz)
    if flat < 0.001 then return flat end
    local v = Vec(dx / flat * NUDGE_SPEED, 0.0, dz / flat * NUDGE_SPEED)
    if v ~= nil then pcall(SetVelocity, craftHandle, v) end
    return flat
end

-- Put the craft a short way in front of the pilot before nudging, so the run
-- does not depend on wherever HopOut happened to leave it.
local function ParkInFrontOf(craftHandle, targetHandle)
    local tp = nil
    if not pcall(function() tp = GetPosition(targetHandle) end) or tp == nil then return false end
    local where = Vec(tp.x + PARK_DISTANCE, tp.y, tp.z)
    if where == nil then return false end
    local ok = pcall(SetPosition, craftHandle, where)
    return ok
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
    parked = false
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

    if pilotReady and not boarded and elapsed >= BOARD_AT then
        local pilot = GetPlayerHandle()
        if craft == nil or not IsValid(craft) then
            Marker("BOARD abandoned: the craft handle is gone")
            boarded = true
        elseif pilot == nil or not IsValid(pilot) or not IsPilot(pilot) then
            -- The player stopped being a Person: either they boarded, or the
            -- craft squashed them. Craft::ExplodePilot plays squish.wav, so
            -- these are genuinely different outcomes and the run must say which.
            boarded = true
            local nowCraft = (pilot ~= nil and IsValid(pilot))
            Marker(string.format("BOARD_RESULT playerValid=%s -> %s",
                tostring(nowCraft),
                nowCraft and "BOARDED (player object is a craft again)"
                          or "PILOT GONE (killed, not boarded)"))
        else
            if not parked then
                parked = true
                Marker(string.format("PARK ok=%s -- craft placed %.1f m from the pilot",
                    tostring(ParkInFrontOf(craft, pilot)), PARK_DISTANCE))
            end
            local gap = NudgeToward(craft, pilot)
            boardAttempts = boardAttempts + 1
            if gap ~= nil and boardAttempts % 15 == 1 then
                Marker(string.format("NUDGE attempt=%d gap=%.2f m", boardAttempts, gap))
            end
            if boardAttempts > 900 then
                boarded = true
                Marker("BOARD gave up: the craft never reached the pilot")
            end
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
