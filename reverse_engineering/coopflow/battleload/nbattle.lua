-- Private multiplayer workload. The host owns both AI armies; native weapons
-- cause damage/deaths/scrap. No scripted kills or health/ammo replenishment.
-- Strategy mode (ArmyBegin/ArmyCleanup) instead gives every client its own army.
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
local extras = {}
local vehicleOdfs = {avtank=true, svtank=true, avfigh=true, svfigh=true}

-- ===== Strategy mode: every client owns one AI army (teams 5..8) =====
-- Human team 1..4 (this client's own player craft team) owns army team 5..8.
-- Teams 5+6 (clients 0,1) fight 7+8 (clients 2,3). Units are created with
-- exu.BuildSyncObject so they replicate even from a guest (UNVERIFIED live).
-- Damage, orders and removal are applied only to units this client created.
local ARMY_FIRST_TEAM, ARMY_LAST_TEAM = 5, 8
local ARMY_CENTER_X, ARMY_CENTER_Z = 2560, 2740
local ARMY_SPAWN_PER_TICK = 2      -- per client per quarter second
local ARMY_CHURN_FACTOR = 4        -- cumulative spawn cap = factor * perClient
local ARMY_MAX_PER_CLIENT = 40
local WARP_MAX_SPEED = 80          -- m/s a unit may legitimately move
local WARP_SLACK = 10              -- m of tolerance on top of speed * dt
local WARP_BIG = 25                -- m; warps at least this long also counted
local armyUnits, warpPrev, warpFrame, armyNextSpawn, armyNextOrder = {}, {}, 0, 0, 0

function ArmyTeamForHuman(human)
    assert(human == math.floor(human) and human >= 1 and human <= 4, "human team 1..4 required")
    return human + 4
end

function ArmySide(team) return team <= 6 and 1 or 2 end

local function armyAlliances()
    for human = 1, 4 do
        for army = ARMY_FIRST_TEAM, ARMY_LAST_TEAM do Ally(human, army); Ally(army, human) end
    end
    for a = ARMY_FIRST_TEAM, ARMY_LAST_TEAM do
        for b = ARMY_FIRST_TEAM, ARMY_LAST_TEAM do
            if a ~= b then
                if ArmySide(a) == ArmySide(b) then Ally(a, b) else UnAlly(a, b) end
            end
        end
    end
end

-- Side 1 (teams 5,6) west of centre, side 2 (7,8) east, 180 m apart; the
-- first team of a side sits north, the second south, rows growing outward.
function ArmySlotPosition(team, slot)
    local side, second = ArmySide(team), (team - ARMY_FIRST_TEAM) % 2
    local sign = second == 0 and -1 or 1
    local x = ARMY_CENTER_X + (side == 1 and -90 or 90) + (slot % 8 - 3.5) * 14
    local z = ARMY_CENTER_Z + sign * 25 + sign * math.floor(slot / 8) * 14
    return SetVector(x, 0, z)
end

-- Returns sampled, warpDistance (nil when the jump is within plausible speed).
-- First sample, unseen-last-frame objects and repeated timestamps are skipped.
function WarpObserve(prev, h, p, now, frame)
    local e = prev[h]
    if not e then
        prev[h] = {x = p.x, y = p.y, z = p.z, t = now, frame = frame}
        return false
    end
    local contiguous = e.frame == frame - 1
    if contiguous and now <= e.t then e.frame = frame; return false end
    local sampled, warp = false, nil
    if contiguous then
        local dx, dy, dz = p.x - e.x, p.y - e.y, p.z - e.z
        local d = math.sqrt(dx * dx + dy * dy + dz * dz)
        sampled = true
        if d > WARP_MAX_SPEED * (now - e.t) + WARP_SLACK then warp = d end
    end
    e.x, e.y, e.z, e.t, e.frame = p.x, p.y, p.z, now, frame
    return sampled, warp
end

local function armyScan(now, wantEnemies)
    local a = M.army
    warpFrame = warpFrame + 1
    local alive, craft = {0, 0, 0, 0}, 0
    local enemies = wantEnemies and {} or nil
    for h in AllCraft() do
        if IsAlive(h) then
            local team = GetTeamNum(h)
            if team >= ARMY_FIRST_TEAM and team <= ARMY_LAST_TEAM then
                craft = craft + 1
                if vehicleOdfs[GetOdf(h)] then
                    alive[team - 4] = alive[team - 4] + 1
                    local own = team == a.team
                    local sampled, warp = WarpObserve(warpPrev, h, GetPosition(h), now, warpFrame)
                    if sampled then
                        local k = own and "l" or "r"
                        a[k .. "Samples"] = a[k .. "Samples"] + 1
                        if warp then
                            a[k .. "Warps"], a[k .. "Dist"] = a[k .. "Warps"] + 1, a[k .. "Dist"] + warp
                            a[k .. "Max"] = math.max(a[k .. "Max"], warp)
                            if warp >= WARP_BIG then a[k .. "Big"] = a[k .. "Big"] + 1 end
                        end
                    end
                    if enemies and ArmySide(team) ~= ArmySide(a.team) then enemies[#enemies + 1] = h end
                end
            end
        end
    end
    for k, e in pairs(warpPrev) do if e.frame ~= warpFrame then warpPrev[k] = nil end end
    for i = 1, 4 do
        a["a" .. (i + 4)] = alive[i]
        a["p" .. (i + 4)] = math.max(a["p" .. (i + 4)], alive[i])
    end
    a.craft = craft
    return enemies
end

local function armySpawn()
    local a = M.army
    local used = {}
    for _, u in ipairs(armyUnits) do used[u.slot] = true end
    local slot = 0
    while used[slot] do slot = slot + 1 end
    local odf = ArmySide(a.team) == 1 and "avtank" or "svtank"
    if slot % 3 == 0 then odf = ArmySide(a.team) == 1 and "avfigh" or "svfigh" end
    a.spawned = a.spawned + 1
    local h = exu.BuildSyncObject(odf, a.team, ArmySlotPosition(a.team, slot))
    if not h or not IsAlive(h) then a.spawnFailed = a.spawnFailed + 1; return end
    SetIndependence(h, 1)
    if IsLocal(h) then a.localOwned = a.localOwned + 1 end
    armyUnits[#armyUnits + 1] = {h = h, slot = slot, health = GetCurHealth(h), ammo = GetCurAmmo(h)}
end

local function armyUpdate(now)
    local a = M.army
    local wantOrders = a.running and now >= armyNextOrder
    local enemies = armyScan(now, wantOrders)
    local living = {}
    for _, u in ipairs(armyUnits) do
        if IsAlive(u.h) then
            local health, ammo = GetCurHealth(u.h), GetCurAmmo(u.h)
            if health < u.health then a.damageEvents = a.damageEvents + 1 end
            if ammo < u.ammo then a.ammoDrops = a.ammoDrops + 1 end
            u.health, u.ammo = health, ammo
            living[#living + 1] = u
        else
            a.deaths = a.deaths + 1
        end
    end
    armyUnits = living
    a.alive = #armyUnits
    if not a.running then return end
    if (a.ends and now >= a.ends) or (not a.ends and now >= a.rampDeadline) then
        a.running, a.finished = false, true
        a.rampFailed = a.ends == nil
        return
    end
    if now >= armyNextSpawn then
        armyNextSpawn = now + 0.25
        local additions = math.min(ARMY_SPAWN_PER_TICK, a.perClient - #armyUnits,
                                   ARMY_CHURN_FACTOR * a.perClient - a.spawned)
        for _ = 1, additions do armySpawn() end
        a.alive = #armyUnits
        if a.spawned >= ARMY_CHURN_FACTOR * a.perClient and not a.capHit then a.capHit = true end
        if not a.rampCompleted and #armyUnits >= a.perClient then
            a.rampCompleted, a.ends = now, now + a.duration
        end
    end
    if wantOrders then
        armyNextOrder = now + 1
        for i, u in ipairs(armyUnits) do
            if (not u.target or not IsAlive(u.target)) and #enemies > 0 then
                u.target = enemies[(i + a.team - 1) % #enemies + 1]
                Attack(u.h, u.target, 1); a.orders = a.orders + 1
            end
        end
    end
end

-- Called on every client (CRFlowProbe). humanTeam is optional: defaults to the
-- local player's own team (CRCoop.GetLocalTeam, else GetTeamNum(GetPlayerHandle())).
function ArmyBegin(perClient, seconds, humanTeam)
    assert(not M.army and not M.running and not M.finished, "one workload per mission")
    assert(perClient == math.floor(perClient) and perClient >= 1 and perClient <= ARMY_MAX_PER_CLIENT, "perClient 1..40 required")
    assert(seconds >= 15 and seconds <= 300, "duration 15..300 seconds required")
    assert(exu.BuildSyncObject, "exu.BuildSyncObject required")
    humanTeam = humanTeam or (CRCoop.GetLocalTeam and CRCoop.GetLocalTeam())
        or (GetPlayerHandle and GetTeamNum(GetPlayerHandle()))
    assert(humanTeam, "local human team unknown")
    local now = GetTime()
    M.army = {humanTeam = humanTeam, team = ArmyTeamForHuman(humanTeam), perClient = perClient,
        duration = seconds, started = now, rampDeadline = now + 30, running = true, finished = false,
        cleaned = false, rampFailed = false, capHit = false, spawned = 0, spawnFailed = 0, localOwned = 0,
        alive = 0, deaths = 0, damageEvents = 0, ammoDrops = 0, orders = 0, craft = 0,
        a5 = 0, a6 = 0, a7 = 0, a8 = 0, p5 = 0, p6 = 0, p7 = 0, p8 = 0,
        lSamples = 0, lWarps = 0, lDist = 0, lMax = 0, lBig = 0,
        rSamples = 0, rWarps = 0, rDist = 0, rMax = 0, rBig = 0}
    armyUnits, warpPrev, warpFrame, armyNextSpawn, armyNextOrder = {}, {}, 0, 0, 0
    armyAlliances()
    return true
end

function ArmyCleanup()
    assert(M.army and M.army.finished, "cleanup requires finished army workload")
    local remove, seen = {}, {}
    for h in AllCraft() do
        if GetTeamNum(h) == M.army.team and not seen[h] then remove[#remove + 1] = h; seen[h] = true end
    end
    for _, h in ipairs(remove) do if IsValid(h) then RemoveObject(h) end end
    armyUnits = {}
    M.army.cleaned, M.army.alive = true, 0
    return true
end

local function alliances()
    CRCoop.ApplyCoopAlliances()
    if M and M.army then armyAlliances(); return end
    -- Humans are observers. The two reserved AI teams fight each other only.
    for human = 1, 4 do
        for ai = 5, 6 do Ally(human, ai); Ally(ai, human) end
    end
    UnAlly(5, 6); UnAlly(6, 5)
end

local function census()
    local counts = {army5 = 0, army6 = 0, pilot5 = 0, pilot6 = 0, scrap = 0, beacons = 0, powerups = 0}
    for h in AllCraft() do
        if IsAlive(h) then
            local team = GetTeamNum(h)
            if team == 5 or team == 6 then
                local kind = vehicleOdfs[GetOdf(h)] and "army" or "pilot"
                counts[kind .. team] = counts[kind .. team] + 1
            end
        end
    end
    for h in AllObjects() do
        local odf = GetOdf(h)
        if odf == "apcamr" then counts.beacons = counts.beacons + 1 end
        if odf == "apammo" or odf == "aprepa" then counts.powerups = counts.powerups + 1 end
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
    M.pilot5, M.pilot6 = counts.pilot5, counts.pilot6
    M.extras.beacons, M.extras.powerups = counts.beacons, counts.powerups
    local gone = 0
    for _, e in ipairs(extras) do if e.powerup and not IsValid(e.h) then gone = gone + 1 end end
    M.extras.powerupsGone = gone -- disappearance, not proof of collection
    if M.measuring then
        M.peakAI = math.max(M.peakAI, counts.army5 + counts.army6)
        M.peakArmy5 = math.max(M.peakArmy5, counts.army5)
        M.peakArmy6 = math.max(M.peakArmy6, counts.army6)
        M.peakScrap = math.max(M.peakScrap, counts.scrap)
        M.peakPilots = math.max(M.peakPilots, counts.pilot5 + counts.pilot6)
        M.extras.beaconPeak = math.max(M.extras.beaconPeak, counts.beacons)
        M.extras.powerupPeak = math.max(M.extras.powerupPeak, counts.powerups)
    end
end

local function spawnExtraOne()
    local state = M.extras
    local odf, position, powerup
    if state.beaconsCreated < state.beaconTarget then
        local i = state.beaconsCreated
        state.beaconsCreated = i + 1
        odf, position = "apcamr", SetVector(2300 + (i % 8) * 40, 0, 2500 - math.floor(i / 8) * 30)
    elseif state.powerupsCreated < state.powerupTarget then
        local i = state.powerupsCreated
        state.powerupsCreated = i + 1
        odf = i % 2 == 0 and "apammo" or "aprepa"
        position, powerup = SetVector(2430 + (i % 10) * 20, 0, 2700 + math.floor(i / 10) * 16), true
    else return false end
    local h = BuildObject(odf, powerup and 0 or 1, position)
    assert(h and IsValid(h), "battle extra object failed to spawn")
    assert(IsLocal(h), "battle extra object must be owned by the creating host")
    extras[#extras + 1] = {h=h, powerup=powerup}
    return true
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
         capHit = false, scrap = 0, updates = 0, orders = 0, simulationTime = 0,
         pilot5 = 0, pilot6 = 0, peakPilots = 0, ammoRises = 0, healthRises = 0,
         extras = {beaconTarget=0, powerupTarget=0, beaconsCreated=0, powerupsCreated=0,
                   beacons=0, powerups=0, beaconPeak=0, powerupPeak=0, powerupsGone=0}}
    units, scrapSeen, extras = {}, {}, {}
    armyUnits, warpPrev, warpFrame, armyNextSpawn, armyNextOrder = {}, {}, 0, 0, 0
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

function BattleBegin(count, seconds, beacons, powerups)
    assert(CRCoop.IsAuthority(), "only host can start battle")
    assert(not M.running and not M.finished, "one workload per mission")
    assert(count >= 4 and count <= 160 and count % 2 == 0, "even AI count 4..160 required")
    assert(seconds >= 15 and seconds <= 300, "duration 15..300 seconds required")
    beacons, powerups = beacons or 0, powerups or 0
    assert(beacons >= 0 and beacons <= 16 and beacons % 1 == 0, "beacons 0..16 required")
    assert(powerups >= 0 and powerups <= 128 and powerups % 1 == 0, "powerups 0..128 required")
    M.extras.beaconTarget, M.extras.powerupTarget = beacons, powerups
    M.target, M.started, M.duration = count, GetTime(), seconds
    M.rampDeadline, M.rampFailed = GetTime() + 30, false
    BattleObserveBegin()
    M.running = true
    return true
end

function BattleSnapshot()
    local out = {}
    for k, v in pairs(M) do out[k] = v end
    if M.army then
        out.army = {}
        for k, v in pairs(M.army) do out.army[k] = v end
    end
    return out
end

function BattleCleanup()
    assert(CRCoop.IsAuthority() and M.finished, "cleanup requires finished host workload")
    -- Natural ejected pilots are not in units. Snapshot the reserved-team
    -- craft iterator before mutation, then remove all surviving AI actors.
    local remove, seen = {}, {}
    for h in AllCraft() do
        local team = GetTeamNum(h)
        if (team == 5 or team == 6) and not seen[h] then remove[#remove + 1] = h; seen[h] = true end
    end
    for _, e in ipairs(extras) do if IsValid(e.h) and not seen[e.h] then remove[#remove + 1] = e.h; seen[e.h] = true end end
    for _, h in ipairs(remove) do if IsValid(h) then RemoveObject(h) end end
    units, extras = {}, {}
    census()
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
    if M.army then armyUpdate(now) end
    if not CRCoop.IsAuthority() or not M.running then return end
    local living, byTeam = {}, {[5] = {}, [6] = {}}
    for _, u in ipairs(units) do
        if IsAlive(u.h) then
            local health, ammo = GetCurHealth(u.h), GetCurAmmo(u.h)
            if health < u.health then M.damageEvents = M.damageEvents + 1 end
            if ammo < u.ammo then M.ammoDrops = M.ammoDrops + 1 end
            if ammo > u.ammo then M.ammoRises = M.ammoRises + 1 end
            if health > u.health then M.healthRises = M.healthRises + 1 end
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
        local pendingExtras = M.extras.beaconsCreated < M.extras.beaconTarget or M.extras.powerupsCreated < M.extras.powerupTarget
        local budget = 4
        if pendingExtras and spawnExtraOne() then budget = budget - 1 end
        local additions = math.min(budget, M.target - #units, 640 - M.spawned)
        for _ = 1, additions do
            local team = #byTeam[5] <= #byTeam[6] and 5 or 6
            spawnOne(team)
            byTeam[team][#byTeam[team] + 1] = units[#units]
        end
        budget = budget - additions
        for _ = 1, budget do if not spawnExtraOne() then break end end
        if M.spawned >= 640 and not M.capHit then M.capHit, M.capHitTime = true, now end
        if not M.rampCompleted and #units >= M.target and
            M.extras.beaconsCreated >= M.extras.beaconTarget and M.extras.powerupsCreated >= M.extras.powerupTarget then
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
