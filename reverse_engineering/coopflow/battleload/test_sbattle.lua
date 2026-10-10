-- Strategy-mode fixture checks: team mapping, alliance matrix, warp detector
-- thresholds, owner-only spawning/orders/cleanup, and the unchanged old mode.
local mission = assert(arg[1], "pass nbattle.lua path")
local objects, time, builds, syncBuilds, attacks, removals = {}, 0, 0, 0, {}, 0
local relation = {}
local coop = {Initialize=function() end, ApplyCoopAlliances=function() end,
    Update=function() end, IsSessionReady=function() return true end,
    MarkMissionStarted=function() end, IsAuthority=function() return false end}
package.preload.RequireFix = function() return {Initialize=function() end} end
local function make(odf, team, pos)
    local h = {odf=odf,team=team,pos=pos,health=100,ammo=100,class="craft",alive=true,valid=true}
    objects[#objects+1]=h; return h
end
local exu = {GetMyNetID=function() return 3 end, DisableStartingRecycler=function() end,
    BuildSyncObject=function(odf, team, pos) syncBuilds = syncBuilds + 1; return make(odf, team, pos) end}
package.preload.exu = function() return exu end
package.preload.CRCoop = function() return coop end
function IsNetGame() return true end
function Ally(a, b) relation[a .. ">" .. b] = true end
function UnAlly(a, b) relation[a .. ">" .. b] = false end
function GetTime() return time end
function SetVector(x,y,z) return {x=x,y=y,z=z} end
function BuildObject(odf, team, pos) builds = builds + 1; return make(odf, team, pos) end
function IsAlive(h) return h and h.alive end
function IsValid(h) return h and h.valid end
function IsLocal(h) return h and h.valid end
function GetTeamNum(h) return h.team end
function GetCurHealth(h) return h.health end
function GetCurAmmo(h) return h.ammo end
function GetClassLabel(h) return h.class end
function GetOdf(h) return h.odf or "" end
function GetPosition(h) return h.pos end
function SetIndependence() end
function Attack(h, target) attacks[#attacks+1] = target; h.target = target end
function RemoveObject(h) removals = removals + 1; h.valid = false; h.alive = false end
local function iterator(craft)
    local i = 0
    return function()
        repeat i = i + 1 until not objects[i] or (objects[i].valid and (not craft or objects[i].class == "craft"))
        return objects[i]
    end
end
function AllCraft() return iterator(true) end
function AllObjects() return iterator(false) end
assert(loadfile(mission))()

-- Team mapping: human 1..4 -> army 5..8, sides 5+6 versus 7+8.
for human = 1, 4 do assert(ArmyTeamForHuman(human) == human + 4) end
assert(not pcall(ArmyTeamForHuman, 0) and not pcall(ArmyTeamForHuman, 5) and not pcall(ArmyTeamForHuman, 1.5))
assert(ArmySide(5) == 1 and ArmySide(6) == 1 and ArmySide(7) == 2 and ArmySide(8) == 2)

-- Old mode: no army key, snapshot unchanged, strategy entry points guarded.
Start()
assert(BattleSnapshot().army == nil, "old mode snapshot has no army block")
assert(relation["5>6"] == false and relation["6>5"] == false and relation["1>5"] and relation["5>1"])
assert(relation["7>8"] == nil, "old mode does not touch teams 7/8")
assert(not pcall(ArmyCleanup), "cleanup requires a started army")

-- Strategy mode: alliance matrix applied at ArmyBegin.
Start()
assert(not pcall(ArmyBegin, 41, 15, 3) and not pcall(ArmyBegin, 4, 5, 3) and not pcall(ArmyBegin, 4, 15, 0))
ArmyBegin(8, 15, 3)
local army = BattleSnapshot().army
assert(army.humanTeam == 3 and army.team == 7 and army.perClient == 8)
for human = 1, 4 do
    for t = 5, 8 do assert(relation[human .. ">" .. t] and relation[t .. ">" .. human], "observers ally every army") end
end
for a = 5, 8 do
    for b = 5, 8 do
        if a ~= b then
            local same = (a <= 6) == (b <= 6)
            assert(relation[a .. ">" .. b] == same, "alliance " .. a .. ">" .. b)
        end
    end
end
assert(not pcall(ArmyBegin, 8, 15, 3), "one workload per mission")

-- Warp detector thresholds on synthetic positions (dt = 0.25 s -> 30 m limit).
local prev, p = {}, function(x) return {x=x, y=0, z=0} end
local h = {}
local sampled, warp = WarpObserve(prev, h, p(0), 1, 1)
assert(sampled == false and warp == nil, "first sample after spawn is skipped")
sampled, warp = WarpObserve(prev, h, p(20), 1.25, 2)
assert(sampled and warp == nil, "20 m in 0.25 s is plausible")
sampled, warp = WarpObserve(prev, h, p(20 + 30), 1.5, 3)
assert(sampled and warp == nil, "exactly at 80 m/s * dt + 10 is not a warp")
sampled, warp = WarpObserve(prev, h, p(50 + 31), 1.75, 4)
assert(sampled and warp == 31, "31 m in 0.25 s is a warp")
sampled, warp = WarpObserve(prev, h, p(500), 2, 6)
assert(sampled == false, "object unseen last frame is re-baselined, not counted")
sampled, warp = WarpObserve(prev, h, p(500), 2, 7)
assert(sampled == false, "repeated timestamp is skipped")
sampled, warp = WarpObserve(prev, h, p(500 + 90), 4, 8)
assert(sampled and warp == nil, "90 m over 2 s is below the limit (170 m)")

-- Owner client simulation: team 7, remote team 5 (enemy) and team 8 (ally).
local enemy = make("svtank", 5, SetVector(2470, 0, 2715))
local allyRemote = make("svfigh", 8, SetVector(2650, 0, 2765))
enemy.odf, allyRemote.odf = "avtank", "svtank"
Update(); assert(syncBuilds == 2 and builds == 0, "two unit per tick via BuildSyncObject, never BuildObject")
Update(); assert(syncBuilds == 2, "no creation twice in same time slice")
local seen = {}
for i = 1, 20 do
    time = i * .25
    if i == 12 then enemy.pos = SetVector(2470 + 40, 0, 2715) end   -- 40 m jump > 30 m
    if i == 14 then enemy.pos = SetVector(2470 + 140, 0, 2715) end  -- 100 m jump
    if i == 16 then enemy.pos = SetVector(2470 + 145, 0, 2715) end  -- 5 m, fine
    if i == 15 then objects[3].pos = SetVector(objects[3].pos.x + 60, 0, objects[3].pos.z) end -- own unit jump
    Update()
end
assert(syncBuilds == 8, "per-client count reached and then capped")
army = BattleSnapshot().army
for _, o in ipairs(objects) do
    if o.team == 7 then
        assert(o.pos.x > 2560 and o.pos.z > 2740 - 80 and o.pos.z < 2740 + 80, "side 2 is east of centre")
    end
end
assert(army.rampCompleted and army.alive == 8 and army.spawned == 8 and army.localOwned == 8)
assert(army.a5 == 1 and army.a7 == 8 and army.a8 == 1 and army.a6 == 0 and army.p7 == 8)
assert(army.rWarps == 2 and army.rBig == 2 and army.rMax > 99 and army.rMax < 101 and army.rSamples > 0)
assert(army.lWarps == 1 and army.lSamples > 0, "own-unit jump counted as local")
assert(#attacks > 0, "owner issues attack orders")
for _, t in ipairs(attacks) do assert(t.team == 5 or t.team == 6, "attacks target enemy side only") end
assert(army.orders == #attacks)
objects[3].health = 80; objects[4].ammo = 90; Update()
army = BattleSnapshot().army
assert(army.damageEvents == 1 and army.ammoDrops == 1)
enemy.health = 10; enemy.ammo = 1; Update()
assert(BattleSnapshot().army.damageEvents == 1, "remote units are not counted as owned damage")
objects[3].alive = false; objects[3].valid = false; time = time + .25; Update()
army = BattleSnapshot().army
assert(army.deaths == 1, "own death counted once")
assert(not pcall(ArmyCleanup), "no cleanup during measurement")
local topKeys, armyKeys = 0, 0
for _ in pairs(BattleSnapshot()) do topKeys = topKeys + 1 end
for _ in pairs(army) do armyKeys = armyKeys + 1 end
assert(topKeys <= 48 and armyKeys <= 48, "snapshot cannot exceed probe field limit")
time = 40; Update(); assert(BattleSnapshot().army.finished and not BattleSnapshot().army.running)
local before = syncBuilds; time = 41; Update(); assert(syncBuilds == before, "no spawning after the deadline")
local pilot = make("aspilo", 7, SetVector(2600, 0, 2740))
ArmyCleanup()
assert(not pilot.valid, "own ejected pilot removed")
assert(enemy.valid and allyRemote.valid, "only the owner's craft are removed")
for _, o in ipairs(objects) do assert(o.team ~= 7 or not o.valid, "own army removed") end
assert(BattleSnapshot().army.cleaned and BattleSnapshot().army.alive == 0)
assert(removals > 0)

-- Ramp failure is reported rather than hanging (units never alive enough).
objects, time, syncBuilds = {}, 0, 0
Start()
ArmyBegin(4, 15, 1)
assert(BattleSnapshot().army.team == 5)
for i = 0, 130 do
    time = i * .25
    for _, o in ipairs(objects) do o.alive = false; o.valid = false end
    Update()
end
army = BattleSnapshot().army
assert(army.finished and army.rampFailed and army.spawned == 16, "cumulative churn cap respected under attrition")
print("PASS: strategy mapping, alliance matrix, warp thresholds, owner-only spawn/orders/cleanup, old mode unchanged")
