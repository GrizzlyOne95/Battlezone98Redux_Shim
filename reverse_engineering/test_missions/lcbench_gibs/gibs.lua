-- lcbench SkinnedGibs live-test overlay (debug only; deployed by
-- run_lcgibs.ps1 as addon/lcbench/lcbench.lua and restored afterwards).
--
-- Spawns the four stock pilots in a row in front of the player, then kills
-- them one after another with Damage() so each death runs the real
-- Person-death path that SkinnedGibs hooks. Watch for the gibs (and their cut
-- faces) for a few seconds, or capture. Marker lines go to BZLogger.txt.
--
-- Needs [General] SkinnedGibs = 1 in openshim.ini. [Diagnostics]
-- TraceSkinnedGibs = 1 logs one line per gib and a render probe once a second.

local models = { "aspilo", "bspilo", "cspilo", "sspilo" }
local elapsed = 0.0
local stage = 0
local pilots = {}
local killed = 0

local function BuildPosition(i)
    local player = GetPlayerHandle()
    local origin = SetVector(0.0, 0.0, 0.0)
    if IsValid(player) then origin = GetPosition(player) end
    -- A row 14 m ahead of the player's start, 5 m apart.
    return SetVector(origin.x + (i - 2.5) * 5.0, origin.y, origin.z + 14.0)
end

function Start()
    elapsed = 0.0
    stage = 0
    print("[LCGIBS] START build=2.2.301 models=" .. table.concat(models, ","))
end

function Update(dt)
    elapsed = elapsed + (dt or 0.0)

    if stage == 0 and elapsed >= 1.0 then
        for i, odf in ipairs(models) do
            local ok, h = pcall(BuildObject, odf, 1, BuildPosition(i))
            print(string.format("[LCGIBS] T+%.2f BUILD odf=%s ok=%s handle=%s", elapsed, odf, tostring(ok), tostring(h)))
            if ok then pilots[#pilots + 1] = { odf = odf, handle = h } end
        end
        stage = 1
        return
    end

    -- One death every 2.5 s starting at T+4, so the effects do not stack.
    if stage == 1 then
        local due = 4.0 + killed * 2.5
        if killed < #pilots and elapsed >= due then
            killed = killed + 1
            local p = pilots[killed]
            if IsValid(p.handle) then
                local ok = pcall(Damage, p.handle, 100000.0)
                print(string.format("[LCGIBS] T+%.2f KILL odf=%s ok=%s", elapsed, p.odf, tostring(ok)))
            end
        elseif killed >= #pilots and elapsed >= 4.0 + #pilots * 2.5 + 20.0 then
            print(string.format("[LCGIBS] T+%.2f COMPLETE", elapsed))
            FailMission(GetTime() + 1.0)
            stage = 2
        end
    end
end

function CreateObject(h) end
function AddObject(h) end
function DeleteObject(h) end
function CreatePlayer(id, name, team) end
function AddPlayer(id, name, team) end
function DeletePlayer(id, name, team) end
