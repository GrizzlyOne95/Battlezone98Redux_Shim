-- Fake client for offline channel tests (Test-CRFlowChannel.ps1): runs the
-- real CRFlowProbe against a mocked engine, with real file I/O standing in for
-- bzfile and print() going to a BZLogger.txt, for a fixed number of seconds.
-- Usage: lua FakeClient.lua <instanceDir> <seconds> <authority:0|1>
local dir, seconds, authority = arg[1], tonumber(arg[2]) or 20, arg[3] == "1"
local here = (arg[0] or ""):match("^(.*)[\\/]") or "."
package.path = here .. "/?.lua;" .. package.path

local log = assert(io.open(dir .. "\\BZLogger.txt", "a"))
print = function(s) log:write(os.date("%Y-%m-%d %H:%M:%S "), tostring(s), "\n"); log:flush() end

package.loaded.bzfile = {
    GetWorkingDirectory = function() return dir end,
    MakeDirectory = function() return true end,
    Exists = function(p) local f = io.open(p, "rb"); if f then f:close() return true end return false end,
    Open = function(p, mode)
        local f = io.open(p, mode == "r" and "rb" or "wb")
        if not f then return nil end
        return { Dump = function() return f:read("a") end, Write = function(_, s) f:write(s) end,
                 Close = function() f:close() end }
    end,
}

local start = os.clock()
local objects = {}
local function handle(name, o) local u = io.tmpfile(); objects[u] = o; return u end
GetTime = function() return os.clock() - start end
IsNetGame = function() return true end
IsHosting = function() return authority end
IsValid = function(h) return objects[h] ~= nil end
IsAlive = function(h) return objects[h] ~= nil and objects[h].alive end
IsLocal = function() return true end
GetOdf = function(h) return objects[h].odf end
GetLabel = function(h) return objects[h].odf end
GetTeamNum = function(h) return objects[h].team end
GetHealth = function() return 1 end
GetPosition = function(h) return { x = objects[h].x, y = 0, z = 0 } end
GetPositionNear = function(p, d) return { x = p.x + d, y = 0, z = 0 } end
SetPosition = function(h, p) objects[h].x = p.x end
Damage = function(h) objects[h].alive = false end
AllCraft = function() local k; return function() k = next(objects, k); return k end end

local me = handle("me", { odf = "avtank", team = authority and 1 or 2, alive = true, x = 0 })
local launch = handle("launch", { odf = "ablpad", team = 1, alive = true, x = 500 })
GetPlayerHandle = function() return me end

local M = { start_done = false, launch = launch }
local native = { AddObjective = function() end }
local CRCoop = {
    IsAuthority = function() return authority end,
    GetLocalTeam = function() return authority and 1 or 2 end,
    GetLocalPlayerId = function() return authority and 1 or 2 end,
    GetMissionPhase = function() return M.start_done and 1 or 0 end,
    IsSessionReady = function() return true end,
    GetPlayers = function() return {} end,
}
local events, receivedEvent = {}, 0
function Update()
    if authority and GetTime() > 2 and not M.start_done then
        M.start_done = true
        native.AddObjective("misn0301.otf", "white")
    end
end

-- The same stub Install-CRFlowProbe appends (passed in by the test).
local stub = assert(io.open(dir .. "\\stub.lua", "rb")):read("a")
assert(load(stub, "=stub", "t", setmetatable({ M = M, CRCoop = CRCoop, native = native,
    events = events, receivedEvent = receivedEvent }, { __index = _G })))()

while GetTime() < seconds do
    Update()
    local t = os.clock() + 0.03
    while os.clock() < t do end
end
log:close()
