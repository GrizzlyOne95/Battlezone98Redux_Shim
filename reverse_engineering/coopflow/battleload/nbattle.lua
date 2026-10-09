-- Private multiplayer workload. The host owns both AI armies; native weapons
-- cause damage/deaths/scrap. No scripted kills or health/ammo replenishment.
local RequireFix = require("RequireFix")
RequireFix.Initialize({"campaignReimagined", "3686673790"})
local exu = require("exu")
if IsNetGame() then
    assert(exu.DisableStartingRecycler and exu.GetMyNetID, "EXU network APIs required")
    exu.DisableStartingRecycler()
end
local CRCoop = require("CRCoop")
local M
local units, nextSpawn, nextOrder, nextCensus = {}, 0, 0, 0
local scrapSeen = {}

local function alliances()
    CRCoop.ApplyCoopAlliances()
    -- Humans are observers. The two reserved AI teams fight each other only.
    for human = 1, 4 do
        for ai = 5, 6 do Ally(human, ai); Ally(ai, human) end
    end
    UnAlly(5, 6); UnAlly(6, 5)
end

local function census()
    local counts = {army5 = 0, army6 = 0, scrap = 0}
    for h in AllCraft() do
        if IsAlive(h) then
            local team = GetTeamNum(h)
            if team == 5 then counts.army5 = counts.army5 + 1 end
            if team == 6 then counts.army6 = counts.army6 + 1 end
        end
    end
    for h in AllObjects() do
        if GetClassLabel(h) == "scrap" then
            local p = GetPosition(h)
            -- Only battlefield debris, excluding incidental observer scrap.
            if (p.x - 2560)^2 + (p.z - 2740)^2 < 600^2 then
            counts.scrap = counts.scrap + 1
            if M.measuring and not scrapSeen[h] then
                scrapSeen[h] = true; M.scrapObserved = M.scrapObserved + 1
            end
            end
        end
    end
    M.army5, M.army6, M.scrap = counts.army5, counts.army6, counts.scrap
    if M.measuring then
        M.peakAI = math.max(M.peakAI, counts.army5 + counts.army6)
        M.peakArmy5 = math.max(M.peakArmy5, counts.army5)
        M.peakArmy6 = math.max(M.peakArmy6, counts.army6)
        M.peakScrap = math.max(M.peakScrap, counts.scrap)
    end
end

local function spawnOne(team)
    M.spawned = M.spawned + 1
    local used = {}
    for _, u in ipairs(units) do if u.team == team then used[u.slot] = true end end
    local slot = 0
    while used[slot] do slot = slot + 1 end
    assert(slot < 80, "no free battle spawn slot")
    local x = 2420 + (slot % 10) * 22
    local z = team == 5 and (2670 - math.floor(slot / 10) * 22) or (2810 + math.floor(slot / 10) * 22)
    local odf = team == 5 and "avtank" or "svtank"
    if slot % 3 == 0 then odf = team == 5 and "avfigh" or "svfigh" end
    local h = BuildObject(odf, team, SetVector(x, 0, z))
    assert(h and IsAlive(h), "battle unit failed to spawn")
    SetIndependence(h, 1)
    units[#units + 1] = {h = h, team = team, slot = slot, health = GetCurHealth(h), ammo = GetCurAmmo(h)}
end

function Start()
    M = {coopMissionStarted = false, running = false, finished = false,
         target = 0, spawned = 0, deaths = 0, damageEvents = 0, ammoDrops = 0,
         scrapObserved = 0, peakAI = 0, peakArmy5 = 0, peakArmy6 = 0,
         peakScrap = 0, army5 = 0, army6 = 0, measuring = false, baselineScrap = 0,
         capHit = false, scrap = 0, updates = 0, orders = 0, simulationTime = 0}
    units, scrapSeen = {}, {}
    nextSpawn, nextOrder, nextCensus = 0, 0, 0
    CRCoop.Initialize({getLocalPlayerId = function() return exu.GetMyNetID() end,
        leaderTeam = 1, humanTeamMin = 1, humanTeamMax = 4})
    alliances()
end

function CreatePlayer(id, name, team) CRCoop.CreatePlayer(id, name, team); alliances() end
function AddPlayer(id, name, team) CRCoop.AddPlayer(id, name, team); alliances() end
function DeletePlayer(id) CRCoop.DeletePlayer(id) end
function Receive(from, kind, ...) return CRCoop.Receive(from, kind, ...) end

-- Called through CRFlowProbe, after all four real clients have joined.
function BattleObserveBegin()
    census()
    M.baselineScrap = M.scrap
    -- Baseline pieces cannot count as combat-created salvage.
    for h in AllObjects() do if GetClassLabel(h) == "scrap" then scrapSeen[h] = true end end
    M.measuring = true
    return true
end

function BattleObserveEnd()
    assert(not CRCoop.IsAuthority(), "host measurement ends with the workload")
    M.measuring = false
    return true
end

function BattleBegin(count, seconds)
    assert(CRCoop.IsAuthority(), "only host can start battle")
    assert(not M.running and not M.finished, "one workload per mission")
    assert(count >= 4 and count <= 160 and count % 2 == 0, "even AI count 4..160 required")
    assert(seconds >= 15 and seconds <= 300, "duration 15..300 seconds required")
    M.target, M.started, M.duration = count, GetTime(), seconds
    M.rampDeadline, M.rampFailed = GetTime() + 30, false
    BattleObserveBegin()
    M.running = true
    return true
end

function BattleSnapshot()
    local out = {}
    for k, v in pairs(M) do out[k] = v end
    return out
end

function BattleCleanup()
    assert(CRCoop.IsAuthority() and M.finished, "cleanup requires finished host workload")
    for _, u in ipairs(units) do if IsValid(u.h) then RemoveObject(u.h) end end
    units = {}
    return true
end

function Update()
    CRCoop.Update()
    M.updates, M.simulationTime = M.updates + 1, GetTime()
    if not M.coopMissionStarted and CRCoop.IsSessionReady() then
        CRCoop.MarkMissionStarted(); M.coopMissionStarted = true
    end
    local now = GetTime()
    if now >= nextCensus then nextCensus = now + 1; census() end
    if not CRCoop.IsAuthority() or not M.running then return end
    local living, byTeam = {}, {[5] = {}, [6] = {}}
    for _, u in ipairs(units) do
        if IsAlive(u.h) then
            local health, ammo = GetCurHealth(u.h), GetCurAmmo(u.h)
            if health < u.health then M.damageEvents = M.damageEvents + 1 end
            if ammo < u.ammo then M.ammoDrops = M.ammoDrops + 1 end
            u.health, u.ammo = health, ammo
            living[#living + 1] = u
            byTeam[u.team][#byTeam[u.team] + 1] = u
        else
            M.deaths = M.deaths + 1
        end
    end
    units = living
    if (M.ends and now >= M.ends) or (not M.ends and now >= M.rampDeadline) then
        census()
        M.running, M.finished, M.measuring = false, true, false
        M.rampFailed = M.ends == nil
        M.finalAI = #units
        return
    end
    -- Four creations per quarter second, rather than a startup-frame burst.
    -- Hard cumulative cap prevents unbounded debris/object churn on a slow run.
    if now >= nextSpawn then
        nextSpawn = now + 0.25
        for _ = 1, math.min(4, M.target - #units, 640 - M.spawned) do
            local team = #byTeam[5] <= #byTeam[6] and 5 or 6
            spawnOne(team)
            byTeam[team][#byTeam[team] + 1] = units[#units]
        end
        if M.spawned >= 640 and not M.capHit then M.capHit, M.capHitTime = true, now end
        if not M.rampCompleted and #units >= M.target then
            M.rampCompleted, M.ends = now, now + M.duration
        end
    end
    -- Give native AI one attack order; retarget only when its victim dies.
    if now >= nextOrder then
        nextOrder = now + 1
        for i, u in ipairs(units) do
            if not u.target or not IsAlive(u.target) then
                local enemies = byTeam[u.team == 5 and 6 or 5]
                if #enemies > 0 then
                    u.target = enemies[(i - 1) % #enemies + 1].h
                    Attack(u.h, u.target, 1); M.orders = M.orders + 1
                end
            end
        end
    end
end
