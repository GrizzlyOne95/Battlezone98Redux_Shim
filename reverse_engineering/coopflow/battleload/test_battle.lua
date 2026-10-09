-- Meaningful fixture checks: guest authority, bounded frame creation, native
-- activity/death accounting, zero-health scrap, and cleanup only after measure.
local mission = assert(arg[1], "pass nbattle.lua path")
local objects, time, authority, builds, attacks, removals = {}, 0, true, 0, 0, 0
local coop = {Initialize=function() end, ApplyCoopAlliances=function() end,
    Update=function() end, IsSessionReady=function() return true end,
    MarkMissionStarted=function() end, IsAuthority=function() return authority end}
package.preload.RequireFix = function() return {Initialize=function() end} end
package.preload.exu = function() return {GetMyNetID=function() return 1 end,
    DisableStartingRecycler=function() end} end
package.preload.CRCoop = function() return coop end
function IsNetGame() return true end
function Ally() end
function UnAlly() end
function GetTime() return time end
function SetVector(x,y,z) return {x=x,y=y,z=z} end
function BuildObject(odf,team,pos)
    builds = builds + 1
    local h = {odf=odf,team=team,pos=pos,health=100,ammo=100,class="craft",alive=true,valid=true}
    objects[#objects+1]=h; return h
end
function IsAlive(h) return h and h.alive end
function IsValid(h) return h and h.valid end
function IsLocal(h) return h and h.valid end
function GetTeamNum(h) return h.team end
function GetCurHealth(h) return h.health end
function GetCurAmmo(h) return h.ammo end
function GetClassLabel(h) return h.class end
function GetOdf(h) return h.odf or "" end
function GetPosition(h) return h.pos or {x=2560,y=0,z=2740} end
function SetIndependence() end
function Attack(h,target) attacks=attacks+1; h.target=target end
function RemoveObject(h) removals=removals+1; h.valid=false; h.alive=false end
local function iterator(craft)
    local i=0
    return function()
        repeat i=i+1 until not objects[i] or (objects[i].valid and (not craft or objects[i].class=="craft"))
        return objects[i]
    end
end
function AllCraft() return iterator(true) end
function AllObjects() return iterator(false) end
assert(loadfile(mission))()
Start()
authority=false
assert(not pcall(BattleBegin,20,15), "guest must not start")
Update(); assert(builds==0, "guest must not spawn")
authority=true
assert(not pcall(BattleBegin,21,15), "reject odd count")
BattleBegin(20,15)
Update(); assert(builds==4, "bounded creation per quarter-second")
Update(); assert(builds==4, "no creation twice in same time slice")
for i=1,8 do time=i*.25; Update() end
assert(builds==20 and attacks>0, "requested balanced population and attack orders")
objects[1].ammo=90; objects[2].health=70; Update()
assert(BattleSnapshot().damageEvents==1 and BattleSnapshot().ammoDrops==1)
objects[2].alive=false; objects[2].valid=false
objects[#objects+1]={class="scrap",health=0,alive=false,valid=true}
objects[#objects+1]={class="scrapsilo",health=100,alive=true,valid=true,team=7}
local ejectedPilot={odf="aspilo",class="craft",health=100,ammo=0,alive=true,valid=true,team=5}
local observer={odf="asuser",class="craft",health=100,ammo=0,alive=true,valid=true,team=1}
objects[#objects+1]=ejectedPilot; objects[#objects+1]=observer
time=3; Update()
local s=BattleSnapshot()
assert(s.deaths==1 and s.peakScrap==1 and s.scrapObserved==1, "natural death and exact zero-health scrap census")
assert(s.pilot5==1 and s.army5+s.army6<=20, "ejected pilots cannot inflate vehicle load")
Update(); assert(BattleSnapshot().deaths==1, "death counted once")
assert(not pcall(BattleCleanup) and removals==0, "no cleanup during measurement")
time=18; Update(); assert(BattleSnapshot().finished and not BattleSnapshot().measuring)
local frozen=BattleSnapshot().peakScrap
objects[#objects+1]={class="scrap",health=0,alive=false,valid=true}
time=19; Update(); assert(BattleSnapshot().peakScrap==frozen, "post-measurement scrap cannot alter measured peak")
local before=builds; Update(); assert(builds==before, "stop replacement after deadline")
BattleCleanup(); assert(removals>0)
assert(not ejectedPilot.valid and observer.valid, "cleanup removes natural AI pilots and preserves human observers")
objects, time, builds = {}, 0, 0
Start(); BattleBegin(160,300)
for i=0,39 do time=i*.25; Update() end
assert(builds==160 and BattleSnapshot().rampCompleted, "full requested population before measurement deadline")
local positions={}
for _,h in ipairs(objects) do
    local key=h.pos.x .. ":" .. h.pos.z
    assert(not positions[key], "no duplicate initial spawn positions at maximum count")
    positions[key]=true
end
for i=40,190 do
    for _,h in ipairs(objects) do h.alive=false; h.valid=false end
    time=i*.25; Update()
end
assert(builds==640 and BattleSnapshot().capHit, "cumulative churn is bounded even under rapid attrition")
objects, time, builds = {}, 0, 0
Start(); BattleBegin(80,60,8,32)
local previous=0
for i=0,39 do
    time=i*.25; Update()
    assert(builds-previous<=4, "AI and extra objects share the bounded frame budget")
    previous=builds
end
local mixed=BattleSnapshot()
assert(builds==120 and mixed.rampCompleted and mixed.extras.beaconsCreated==8 and mixed.extras.powerupsCreated==32)
assert(mixed.extras.beaconPeak==8 and mixed.extras.powerupPeak==32, "native extra object census")
local keys=0; for _ in pairs(mixed) do keys=keys+1 end
assert(keys<=48, "snapshot cannot exceed probe scalar field limit")
time=80; Update(); BattleCleanup()
for _,h in ipairs(objects) do assert(not h.valid, "mixed cleanup removes all AI actors and staged extras") end
print("PASS: authority, bounded spawning, 160 unique slots, 640 churn cap, native activity accounting, scrap census, phase cleanup")
