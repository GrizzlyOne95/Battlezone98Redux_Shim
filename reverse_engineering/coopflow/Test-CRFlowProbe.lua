-- Offline checks for CRFlowProbe.lua with a mocked engine and in-memory bzfile.
-- Run: lua reverse_engineering/coopflow/Test-CRFlowProbe.lua
-- Covers probe logic only; native loading, bzfile and replication need a live run.
local here = (arg and arg[0] or ""):match("^(.*)[\\/]") or "."
package.path = here .. "/?.lua;" .. package.path

local checks = 0
local function check(v, msg) assert(v, msg); checks = checks + 1 end

local files, printed, t = {}, {}, 0
local function H(name) return setmetatable({ name = name }, { __tostring = function() return "h:" .. name end }) end
-- Handles must be userdata for the probe; wrap a proxy userdata per name.
local handles, objects = {}, {}
local function handle(name, o)
    local u = handles[name]
    if not u then
        u = (newproxy and newproxy(true)) or io.tmpfile()
        handles[name] = u
        objects[u] = o or { odf = name, team = 1, alive = true, hp = 1, x = 0, y = 0, z = 0, isLocal = true }
    end
    return u
end

package.loaded.bzfile = {
    GetWorkingDirectory = function() return "C:\\inst\\" end,
    MakeDirectory = function() return true end,
    Exists = function(p) return files[p] ~= nil end,
    Open = function(p, mode)
        if mode == "r" then
            if not files[p] then return nil end
            return { Dump = function() return files[p] .. "\0\0" end, Close = function() end }
        end
        local buf = {}
        return { Write = function(_, s) buf[#buf + 1] = s end,
                 Close = function() files[p] = table.concat(buf) end }
    end,
}

_G.print = function(s) printed[#printed + 1] = s end
_G.GetTime = function() return t end
_G.IsNetGame = function() return true end
_G.IsHosting = function() return true end
_G.IsValid = function(h) return objects[h] ~= nil end
_G.IsAlive = function(h) return objects[h] ~= nil and objects[h].alive end
_G.IsLocal = function(h) return objects[h].isLocal end
_G.GetOdf = function(h) return objects[h].odf end
_G.GetLabel = function(h) return objects[h].odf end
_G.GetTeamNum = function(h) return objects[h].team end
_G.GetHealth = function(h) return objects[h].hp end
_G.GetMaxHealth = function() return 1000 end
_G.SetCurHealth = function(h, v) objects[h].hp = v / 1000 end
_G.GetPosition = function(h) local o = objects[h]; return { x = o.x, y = o.y, z = o.z } end
_G.GetPositionNear = function(p, a) return { x = p.x + a, y = p.y, z = p.z } end
_G.SetPosition = function(h, p) local o = objects[h]; o.x, o.y, o.z = p.x, p.y, p.z end
_G.GetDistance = function(a, b) local A, B = objects[a], objects[b]; return math.abs(A.x - B.x) + math.abs(A.z - B.z) end
_G.Damage = function(h) objects[h].alive = false end
_G.GetHandle = function(label) return handles[label] end
_G.AllCraft = function()
    local list = {}
    for _, u in pairs(handles) do if objects[u].alive then list[#list + 1] = u end end
    local i = 0
    return function() i = i + 1; return list[i] end
end

local me = handle("player", { odf = "avtank", team = 1, alive = true, hp = 1, x = 0, y = 0, z = 0, isLocal = true })
_G.GetPlayerHandle = function() return me end
local launch = handle("launch_pad", { odf = "ablpad", team = 1, alive = true, hp = 1, x = 500, y = 0, z = 500, isLocal = true })
local enemyNear = handle("svtank1", { odf = "svtank", team = 5, alive = true, hp = 1, x = 10, y = 0, z = 0, isLocal = true })
local enemyFar = handle("svtank2", { odf = "svtank", team = 5, alive = true, hp = 1, x = 4000, y = 0, z = 0, isLocal = true })

local M = { start_done = false, launch = launch, movie_time = 100, other_time = 50, solar_list = { true } }
local updates = 0
function Update() updates = updates + 1 end
local nativeCalls = {}
local native = {
    AddObjective = function(...) nativeCalls[#nativeCalls + 1] = { "AddObjective", ... } end,
    SetObjectiveName = function() end,
    CameraPath = function() end,
    CameraReady = function() end,
}
local CRCoop = {
    IsAuthority = function() return true end, GetLocalTeam = function() return 1 end,
    GetLocalPlayerId = function() return 1 end, GetMissionPhase = function() return 1 end,
    IsSessionReady = function() return true end, HasLateJoiners = function() return false end,
    HasLeaderDeparted = function() return false end,
    GetPlayers = function() return { [1] = { name = "BZRCoop1", team = 1, handle = me } } end,
}
local events = { 1, 2, 3 }

local probe = require("CRFlowProbe")
check(probe.Attach({ mission = "misn03", getM = function() return M end, CRCoop = CRCoop,
    native = native, getLocals = function() return { events = #events } end }), "attach returns true")

local function lines(kind)
    local out = {}
    for _, s in ipairs(printed) do
        if s:find('"k":"' .. kind .. '"', 1, true) then out[#out + 1] = s end
    end
    return out
end
check(#lines("attach") == 1, "attach event printed")
check(printed[1]:match("^%[CRFLOW%] {.*} #END$"), "event line format")

-- The wrapped Update still runs the mission's Update.
Update(); check(updates == 1, "mission Update still called")
check(#lines("role") == 1, "role event once player id is known")
check(#lines("snap") == 1, "first frame snapshots")
check(files["C:\\inst\\crflow\\state.json"]:find('"mission":"misn03"', 1, true), "state.json written")
check(files["C:\\inst\\crflow\\state.json"]:find('"events":3', 1, true), "locals included")

-- Flag transitions.
M.start_done = true; t = 1; Update()
local flags = lines("flag")
check(flags[#flags]:find('"key":"start_done"', 1, true) and flags[#flags]:find('"to":true', 1, true), "flag change emitted")
local n = #lines("flag"); t = 1.6; Update(); check(#lines("flag") == n, "unchanged flag not repeated")

-- Presentation hook: logged, then the real native runs.
native.AddObjective("misn0301.otf", "white")
check(#nativeCalls == 1, "native AddObjective still runs")
check(lines("op")[1]:find('"op":"AddObjective"', 1, true) and lines("op")[1]:find("misn0301.otf", 1, true), "op logged")
native.SetObjectiveName(launch, "Command Tower: 55%")
check(#lines("op") == 1, "health-name refresh is noise")
native.CameraPath("movie_path", 1, 1, launch); native.CameraPath("movie_path", 1, 1, launch)
check(#lines("op") == 2, "CameraPath logged once per path")

-- Commands.
local function send(seq, code) files["C:\\inst\\crflow\\cmd.txt"] = "seq=" .. seq .. "\n" .. code end
local function out() return files["C:\\inst\\crflow\\out.txt"] end
send(1, "return M.start_done, L().events"); t = 2; Update()
check(out():find("^seq=1\nok=true\n%[true,3%]\n#END\n$"), "multi-value result encoded: " .. tostring(out()))
send(1, "return 'again'"); t = 2.5; Update()
check(not out():find("again"), "same seq is not re-run")
send(2, "x = 41"); t = 3; Update()
send(3, "return x + 1"); t = 3.5; Update()
check(out():find("\n42\n", 1, true), "command variables persist")
check(rawget(_G, "x") == nil, "command variables stay out of _G")
send(4, "error('boom')"); t = 4; Update()
check(out():find("ok=false", 1, true) and out():find("boom", 1, true), "errors are reported")
check(updates > 0, "mission keeps running after a failing command")
send(5, "return ff('movie')"); t = 4.5; Update()
check(M.movie_time == 4.5 and M.other_time == 50, "ff pulls only matching timers")
send(6, "return tp('launch_pad', 20)"); t = 5; Update()
check(objects[me].x == 520, "tp moves own craft near the label")
objects[me].x, objects[me].z = 0, 0
send(7, "return clearAroundPlayers(5, '^sv', 500)"); t = 5.5; Update()
check(not objects[enemyNear].alive, "nearby enemy killed")
check(objects[enemyFar].alive, "far enemy untouched")
check(out():find("\n1\n", 1, true), "clear count returned")

-- Recurring tasks: runs until it returns true; errors cancel it.
send(8, "count = 0; every('heal', 1, function() count = count + 1; return count >= 2 end)"); t = 6; Update()
t = 7.1; Update(); t = 8.2; Update()
send(9, "return count, #tasks()"); t = 8.5; Update()
check(out():find("%[2,0%]"), "task ran twice then finished: " .. out())
send(10, "every('bad', 1, function() error('task boom') end)"); t = 9; Update(); t = 10.1; Update()
check(#lines("error") >= 1 and lines("error")[#lines("error")]:find("task boom", 1, true), "task error reported")

-- Handles serialize as comparable descriptors.
send(11, "return describe('launch_pad')"); t = 11; Update()
check(out():find('"odf":"ablpad"', 1, true) and out():find('"pos":[500,0,500]', 1, true), "handle descriptor")

-- A failing tick (getM throws) is contained.
M = nil
local okTick = pcall(function() t = 20; Update() end)
check(okTick, "probe failure does not break Update")

print = function(...) io.stdout:write(table.concat({ ... }, "\t"), "\n") end
print(string.format("Test-CRFlowProbe: %d checks passed (%s)", checks, _VERSION))
