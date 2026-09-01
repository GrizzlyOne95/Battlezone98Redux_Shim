-- lcbench pilot-hardpoint ordering qualification overlay.
-- Deploy as lcbench.lua beside the existing lcbench world. The runner changes
-- only rmpcfg.odf between arms so each process constructs exactly one fixture.

local elapsed = 0.0
local stage = 0
local spawned = nil
local selectedCase = "pctl"
local fixtureCommit = "unknown"

local function BuildPosition()
    local player = GetPlayerHandle()
    if IsValid(player) then
        -- Do not overlap the player or any other matrix object.
        return GetPositionNear(GetPosition(player), 25.0, 35.0)
    end
    return GetPositionNear(SetVector(0.0, 0.0, 0.0), 25.0, 35.0)
end

function Start()
    elapsed = 0.0
    stage = 0
    local config = OpenODF("rmpcfg")
    selectedCase = GetODFString(config, "Roadmap", "case", "pctl")
    fixtureCommit = GetODFString(config, "Roadmap", "commit", "unknown")
    print(string.format("[LCROAD][PILOT] START build=2.2.301 case=%s commit=%s",
        tostring(selectedCase), tostring(fixtureCommit)))
end

function Update(dt)
    elapsed = elapsed + (dt or 0.0)

    if stage == 0 and elapsed >= 1.0 then
        local position = BuildPosition()
        print(string.format("[LCROAD][PILOT] T+%.3f BEFORE_BUILD odf=%s team=1",
            elapsed, tostring(selectedCase)))

        -- A native access violation will prevent the AFTER_BUILD marker. pcall
        -- still records ordinary Lua/ODF rejection without hiding native faults.
        local ok, value = pcall(BuildObject, selectedCase, 1, position)
        print(string.format("[LCROAD][PILOT] T+%.3f AFTER_BUILD odf=%s ok=%s handle=%s",
            elapsed, tostring(selectedCase), tostring(ok), tostring(value)))
        if ok then spawned = value end
        stage = 1
        return
    end

    if stage == 1 and elapsed >= 4.0 then
        local valid = spawned ~= nil and IsValid(spawned)
        local person = valid and IsPerson(spawned)
        print(string.format("[LCROAD][PILOT] T+%.3f RESULT valid=%s person=%s",
            elapsed, tostring(valid), tostring(person)))
        stage = 2
        return
    end

    if stage == 2 and elapsed >= 7.0 then
        print(string.format("[LCROAD][PILOT] T+%.3f COMPLETE", elapsed))
        FailMission(GetTime() + 1.0)
        stage = 3
    end
end

function CreateObject(h) end
function AddObject(h) end
function DeleteObject(h) end
function CreatePlayer(id, name, team) end
function AddPlayer(id, name, team) end
function DeletePlayer(id, name, team) end
