-- music.lua -- lcbench fixture for the OpenShim soundtrack exports.
--
-- Deploy as addon/lcbench/lcbench.lua over the live_combat_scaling world, then
-- launch `battlezone98redux.exe lcbench.bzn` (see run_lcmusic.ps1).
--
-- Drives OpenShimSetMusicTrack / OpenShimStopMusic through EXU's Lua wrappers,
-- the path a mission actually uses, and prints each return value. The harness
-- samples the engine's music globals alongside, so a TRUE here can be checked
-- against the track the engine really selected and whether it is playing.
--
--   SET07   SetMusicTrack(7)   -- expected true, 07.ogg starts
--   SAME07  SetMusicTrack(7)   -- expected true, keeps playing (no restart)
--   MISS98  SetMusicTrack(98)  -- expected false, 98.ogg does not exist;
--                                 07.ogg must keep playing
--   STOP    StopMusic()        -- expected true, music stops
--   STOP2   StopMusic()        -- expected true, idempotent
--   SET12   SetMusicTrack(12)  -- expected true, 12.ogg starts
--
-- Lua 5.1 (no goto, no io/os/debug).

local exu = require("exu")

local elapsed = 0.0
local stepIndex = 0
local finished = false

local steps = {
    { at = 6.0,  key = "SET07",  call = function() return exu.SetMusicTrack(7) end },
    { at = 14.0, key = "SAME07", call = function() return exu.SetMusicTrack(7) end },
    { at = 20.0, key = "MISS98", call = function() return exu.SetMusicTrack(98) end },
    { at = 26.0, key = "STOP",   call = function() return exu.StopMusic() end },
    { at = 32.0, key = "STOP2",  call = function() return exu.StopMusic() end },
    { at = 38.0, key = "SET12",  call = function() return exu.SetMusicTrack(12) end },
}
local DONE_AT = 46.0

local function Marker(text)
    print(string.format("[MUSICFIX] T+%.2f %s", elapsed, text))
end

function Start()
    Marker(string.format("START exu=%s SetMusicTrack=%s StopMusic=%s",
        tostring(exu ~= nil), tostring(exu and exu.SetMusicTrack ~= nil),
        tostring(exu and exu.StopMusic ~= nil)))
end

function Update(dt)
    elapsed = elapsed + (dt or 0.0)
    if finished then return end

    local nextStep = steps[stepIndex + 1]
    if nextStep ~= nil and elapsed >= nextStep.at then
        stepIndex = stepIndex + 1
        local ok, result = pcall(nextStep.call)
        Marker(string.format("STEP %s ok=%s result=%s", nextStep.key, tostring(ok), tostring(result)))
        return
    end

    if nextStep == nil and elapsed >= DONE_AT then
        finished = true
        Marker("DONE")
    end
end
