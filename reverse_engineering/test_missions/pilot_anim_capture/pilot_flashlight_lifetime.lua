-- pilot_flashlight_lifetime.lua
--
-- Exercises the pilot flashlight's *destroy* path, which the endless fixture
-- never reaches. Deploy as addon/lcbench/lcbench.lua and launch
-- `battlezone98redux.exe lcbench.bzn`.
--
-- Timeline:
--   T+3   HopOut  -> the shim creates the light on the pilot's scene node
--   T+15  DeleteObject(player) -> the local player object stops being a Person,
--         so RefreshPilotFlashlightState calls DestroyPilotFlashlight while the
--         scene manager is still live. This is the only route that actually
--         calls Ogre's SceneManager::destroyLight; a mission exit only reaches
--         the forget path.
--   T+22  FailMission -> mission teardown after the light is already gone.
--
-- Lua 5.1 (no goto, no io/os/debug).

-- The mission callback `DeleteObject(h)` at the bottom of this file is a
-- global assignment, so by the time Update runs it has REPLACED the engine's
-- DeleteObject API of the same name. Capture the real one here, while the
-- chunk is still executing top to bottom. (pilot_test.lua does not do this,
-- which is why its LIFETIME_DESTROY step silently called its own no-op.)
local EngineDeleteObject = DeleteObject
-- Redux's Lua removal API is RemoveObject; DeleteObject is only a mission
-- callback name, so the captured global above is normally nil and calling it
-- fails (observed: DELETE_PILOT ok=false). Prefer RemoveObject.
local EngineRemoveObject = RemoveObject

local elapsed = 0.0
local hopped = false
local deleted = false
local failed = false

local function Marker(text)
    print(string.format("[PFLLIFE] T+%.2f %s", elapsed, text))
end

function Start()
    elapsed = 0.0
    hopped = false
    deleted = false
    failed = false
    Marker("START lifetime fixture")
end

function Update(dt)
    elapsed = elapsed + (dt or 0.0)

    if not hopped and elapsed >= 3.0 then
        local h = GetPlayerHandle()
        if h ~= nil and IsValid(h) then
            hopped = pcall(HopOut, h)
            Marker(string.format("HOP_OUT ok=%s", tostring(hopped)))
        end
    end

    if hopped and not deleted and elapsed >= 15.0 then
        local h = GetPlayerHandle()
        local isPerson = false
        if h ~= nil and IsValid(h) then
            pcall(function() isPerson = IsPerson(h) end)
        end
        Marker(string.format("PRE_DELETE isPerson=%s", tostring(isPerson)))
        if h ~= nil and IsValid(h) then
            local remover = EngineRemoveObject or EngineDeleteObject
            local ok = false
            if remover ~= nil then ok = pcall(remover, h) end
            Marker(string.format("DELETE_PILOT ok=%s api=%s", tostring(ok),
                EngineRemoveObject ~= nil and "RemoveObject" or "DeleteObject"))
        end
        deleted = true
    end

    if deleted and not failed and elapsed >= 22.0 then
        failed = true
        Marker("FAIL_MISSION -- teardown after destroy")
        pcall(FailMission, GetTime() + 1.0)
    end
end

function CreateObject(h) end
function AddObject(h) end
function DeleteObject(h) end

function Save()
    return elapsed, hopped, deleted, failed
end

function Load(a, b, c, d)
    elapsed = a or 0.0
    hopped = b or false
    deleted = c or false
    failed = d or false
end
