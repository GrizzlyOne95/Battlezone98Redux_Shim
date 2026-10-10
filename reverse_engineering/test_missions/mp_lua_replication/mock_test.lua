-- Run with Lua 5.1 from this directory: lua mock_test.lua
local clock, calls, logs, objects, packets = 0, {}, {}, {}, {}
local player = newproxy()
local function called(name, ...) calls[#calls + 1] = { name, ... } end
function GetTime() return clock end
function GetPlayerHandle() return player end
function IsHosting() return true end
function IsNetGame() return true end
function IsValid(h) return objects[h] ~= nil and objects[h].valid end
function IsLocal(h) return objects[h].owner end
function IsRemote(h) return not objects[h].owner end
function GetTeamNum(h) return objects[h].team end
function GetObjectiveName(h) return objects[h].name end
function GetLabel(h) return "probe" end
function GetPosition(h) return objects[h].position end
function GetCurrentCommand(h) return 0 end
function GetWeaponClass(h, slot) return objects[h].weapons[slot] end
function BuildObject(odf, team, where)
    called("BuildObject", odf, team, where)
    local h = newproxy()
    objects[h] = { valid = true, owner = true, team = team, name = odf,
                   position = { x = 1, y = 2, z = 3 }, weapons = {} }
    return h
end
function SetName(h, s) called("SetName"); objects[h].name = s end
function SetObjectiveName(h, s) called("SetObjectiveName"); objects[h].name = s end
function SetObjectiveOn(h) called("SetObjectiveOn") end
function SetObjectiveOff(h) called("SetObjectiveOff") end
function GiveWeapon(h, weapon, slot) called("GiveWeapon"); objects[h].weapons[slot] = weapon; return true end
function RemoveObject(h) called("RemoveObject"); objects[h].valid = false end
function SetPosition(h, p) called("SetPosition"); objects[h].position = p end
function SetVelocity(h, p) called("SetVelocity") end
function SetTeamNum(h, team) called("SetTeamNum"); objects[h].team = team end
function SetLocal(h) called("SetLocal"); objects[h].owner = true end
function AddObjective(...) called("AddObjective", ...) end
function UpdateObjective(...) called("UpdateObjective", ...) end
function RemoveObjective(...) called("RemoveObjective", ...) end
function Send(...)
    packets[#packets + 1] = { n = select("#", ...), ... }
    return true
end
local checks = 0
local function check(v) assert(v); checks = checks + 1 end
local function rejects(fn)
    local before = #calls
    check(not pcall(fn))
    check(#calls == before)
end
local module = dofile("mprep.lua")
local p = module.new({ log = function(s) logs[#logs + 1] = s end })
local h = p.Spawn("stock", "avtank", 1, "spawn")
check(IsValid(h))
rejects(function() p.Spawn("sync", "avtank", 1, "spawn") end)
rejects(function() p.Spawn("stock", "avtank", 1.5, "spawn") end)
rejects(function() p.Run("SetLocal", h) end)
rejects(function() p.Run("GiveWeapon", h, "gspstab", 5) end)
rejects(function() p.Run("GiveWeapon", h, "gspstab", -1) end)
rejects(function() p.Run("GiveWeapon", h, "gspstab", 1.5) end)
rejects(function() p.Run("SetTeamNum", h, 16) end)
rejects(function() p.Run("SetName", h, string.rep("x", 65)) end)
check(p.Run("GiveWeapon", h, "gspstab", 0))
check(objects[h].weapons[0] == "gspstab")
p.Run("SetName", h, "Renamed")
check(objects[h].name == "Renamed")
check(p.Payload(2, "nil_test", 3, nil, "end", nil))
local packet = packets[#packets]
check(packet.n == 10 and packet[7] == 3 and packet[8] == nil and packet[9] == "end" and packet[10] == nil)
local sent = #packets
rejects(function() p.Payload(2, "long", string.rep("x", 128)) end)
rejects(function() p.Payload(2, "large", string.rep("x", 100), string.rep("y", 100)) end)
rejects(function() p.Payload(2, "cycle", {}) end)
rejects(function() p.Payload(2, "nan", 0/0) end)
check(#packets == sent)
check(p.Payload(2, "boundary", string.rep("x", 127)))
check(p.Receive(2, "!", "MPRE1", "watch", "x", h) == false)
check(p.Receive(2, "~", "OTHER", "watch", "x", h) == false)
local before = #calls
p.Receive(2, "~", "MPRE1", "watch", "x", h)
check(p.watches.x == nil and #calls == before)
p.AllowPeer(2)
check(p.Receive(2, "~", "MPRE1", "watch", "x", h))
check(p.watches.x.h == h and #calls == before)
p.Receive(2, "~", "MPRE1", "watch", "pending", nil)
check(p.watches.pending.h == nil and #calls == before)
p.Receive(2, "~", "MPRE1", "watch", "bad", "not a handle")
check(p.watches.bad == nil and #calls == before)
p.DeletePlayer(2)
p.Receive(2, "~", "MPRE1", "watch", "deleted", h)
check(p.watches.deleted == nil)
rejects(function() p.Run("RemoveObject", player) end)
p.Objective("add", "one")
rejects(function() p.Objective("add", "two") end)
p.Objective("update", "updated")
p.Objective("remove")
rejects(function() p.Objective("update", "missing") end)
clock = 11
p.Update()
check(next(p.watches) == nil)
p.Run("RemoveObject", h)
check(not IsValid(h))
rejects(function() p.Run("SetName", h, "stale") end)
local q = module.new({ allowOwnershipClaim = true, log = function() end })
local other = q.Spawn("stock", "avtank", 1, "spawn")
objects[other].owner = false
q.Run("SetLocal", other)
check(IsLocal(other))
print("PASS: " .. checks .. " probe checks under " .. _VERSION)
