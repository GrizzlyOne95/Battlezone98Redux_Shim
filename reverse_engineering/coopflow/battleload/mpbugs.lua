-- Private multiplayer bug pack: reproductions of stock multiplayer defects.
-- The mission stays stock on purpose: it never replicates a mission result or
-- reacts to the host leaving, so the scenarios see what the engine alone does.
-- CRCoop supplies only the roster and readiness the harness waits on. The
-- entry points below are called through CRFlowProbe by the
-- coopflow\scenarios\mpbugs-*.ps1 scenarios.
local RequireFix = require("RequireFix")
RequireFix.Initialize({"campaignReimagined", "3686673790"})
local exu = require("exu")
if IsNetGame() then
    assert(exu.DisableStartingRecycler and exu.GetMyNetID, "EXU network APIs required")
    exu.DisableStartingRecycler()
end
local CRCoop = require("CRCoop")
-- Results go through this table so CRFlowProbe records each call as an op.
local native = {SucceedMission = SucceedMission, FailMission = FailMission}
local M
local units = {}
-- Explosive objects this peer has seen, one record per handle lifetime:
-- Daywreckers (apwrck) and deployed Splinters (splintb2).
local EXPLOSIVES = {apwrck = "daywrecker", splintb2 = "splinter"}
local tracked, lifetimes = {}, {}
-- The Armory deploys, builds, then takes its Dropoff one update after Build;
-- the Splinter shooter fires until its ammunition drops.
local pendingLaunch, pendingFire
local WITNESS_TEAM = 7

-- Humans are observers; the two AI teams fight each other only.
local function alliances()
    CRCoop.ApplyCoopAlliances()
    for human = 1, 4 do
        for ai = 5, 6 do Ally(human, ai); Ally(ai, human) end
    end
    UnAlly(5, 6); UnAlly(6, 5)
end

local function round(v, places)
    local m = 10 ^ (places or 1)
    return math.floor(v * m + 0.5) / m
end

local function explosiveKind(h)
    local odf = string.lower(GetOdf(h) or ""):gsub("%.odf$", "")
    return EXPLOSIVES[odf]
end

-- A handle that leaves AllObjects closes its record; a new handle opens one,
-- so a consumed explosive rebuilt from network state shows as a second record.
local function trackExplosives()
    local now, seen = GetTime(), {}
    for h in AllObjects() do
        local kind = explosiveKind(h)
        if kind then
            seen[h] = true
            local p = GetPosition(h)
            local r = tracked[h]
            if not r then
                r = {kind = kind, first = now, mine = IsLocal(h), remote = IsRemote(h),
                     x = round(p.x), y = round(p.y), z = round(p.z)}
                tracked[h] = r
                lifetimes[#lifetimes + 1] = r
            end
            r.last, r.lastX, r.lastY, r.lastZ = now, round(p.x), round(p.y), round(p.z)
        end
    end
    for h, r in pairs(tracked) do
        if not seen[h] then r.gone = now; tracked[h] = nil end
    end
end

local function serviceLaunches()
    local l = pendingLaunch
    if l then
        if not IsAlive(l.armory) then
            M.launch.lost = GetTime(); pendingLaunch = nil
        elseif not l.built then
            -- A producer builds only once deployed; go ahead anyway after 15 s.
            if IsDeployed(l.armory) or GetTime() > l.deployDeadline then
                M.launch.deployed = IsDeployed(l.armory)
                Build(l.armory, "apwrck")
                M.launch.buildAt = GetTime()
                l.built = true
            end
        else
            Dropoff(l.armory, l.where)
            M.launch.dropoffAt = GetTime()
            pendingLaunch = nil
        end
    end
    if pendingFire then
        local f = pendingFire
        if not IsAlive(f.shooter) or GetTime() > f.deadline then
            M.fire.timedOut = true; pendingFire = nil
        elseif GetCurAmmo(f.shooter) < f.ammo then
            M.fire.firedAt = GetTime(); pendingFire = nil
        elseif IsAlive(f.target) then
            FireAt(f.shooter, f.target)
        end
    end
end

function Start()
    M = {coopMissionStarted = false, updates = 0, simulationTime = 0, ended = nil, spawned = 0,
         launch = {}, fire = {}}
    units, tracked, lifetimes = {}, {}, {}
    CRCoop.Initialize({getLocalPlayerId = function() return exu.GetMyNetID() end,
        leaderTeam = 1, humanTeamMin = 1, humanTeamMax = 4})
    alliances()
end

function CreatePlayer(id, name, team) CRCoop.CreatePlayer(id, name, team); alliances() end
function AddPlayer(id, name, team) CRCoop.AddPlayer(id, name, team); alliances() end
function DeletePlayer(id)
    M.deletedPlayers = (M.deletedPlayers or 0) + 1
    CRCoop.DeletePlayer(id)
end
function Receive(from, kind, ...) return CRCoop.Receive(from, kind, ...) end

function Update()
    CRCoop.Update()
    M.updates, M.simulationTime = M.updates + 1, GetTime()
    if not M.coopMissionStarted and CRCoop.IsSessionReady() then
        CRCoop.MarkMissionStarted(); M.coopMissionStarted = true
    end
    trackExplosives()
    serviceLaunches()
end

-- Ends the mission on this peer only, the way a stock script does: the
-- result is a local native call with no message to the other peers.
function BugEnd(kind, delay)
    local fn = kind == "fail" and native.FailMission or native.SucceedMission
    M.ended = {kind = kind == "fail" and "fail" or "succeed", at = GetTime()}
    fn(GetTime() + (delay or 3), "mpbugs.des")
    return M.ended
end

-- Host only: AI combat owned by this peer, so a guest can watch what happens
-- to objects whose owner has left.
function BugSpawnArmies(perTeam)
    assert(IsLocal(GetPlayerHandle()), "local player handle required")
    for i = 0, perTeam - 1 do
        for _, team in ipairs({5, 6}) do
            local x = 2440 + (i % 8) * 22
            local z = team == 5 and (2670 - math.floor(i / 8) * 22) or (2810 + math.floor(i / 8) * 22)
            local h = BuildObject(team == 5 and "avtank" or "svtank", team, SetVector(x, 0, z))
            assert(h and IsAlive(h), "bug pack unit failed to spawn")
            SetIndependence(h, 1)
            units[#units + 1] = h
            M.spawned = M.spawned + 1
        end
    end
    for _, h in ipairs(units) do
        local enemy = GetTeamNum(h) == 5 and 6 or 5
        for _, other in ipairs(units) do
            if GetTeamNum(other) == enemy and IsAlive(other) then Attack(h, other); break end
        end
    end
    return M.spawned
end

-- Per-peer census: every object by team, AI craft health and positions, and
-- how many of them this peer owns.
function BugState()
    local s = {time = GetTime(), updates = M.updates, ended = M.ended,
               deletedPlayers = M.deletedPlayers or 0, objects = 0, teams = {},
               craft = {[5] = 0, [6] = 0}, localCraft = 0, health = 0, posSum = 0}
    for h in AllObjects() do
        s.objects = s.objects + 1
        local team = GetTeamNum(h)
        s.teams[tostring(team)] = (s.teams[tostring(team)] or 0) + 1
        if (team == 5 or team == 6) and IsCraft(h) and IsAlive(h) then
            s.craft[team] = s.craft[team] + 1
            if IsLocal(h) then s.localCraft = s.localCraft + 1 end
            s.health = s.health + GetCurHealth(h)
            local p = GetPosition(h)
            s.posSum = s.posSum + p.x + p.z
        end
    end
    s.craft5, s.craft6, s.craft = s.craft[5], s.craft[6], nil
    local roster = 0
    for _ in pairs(CRCoop.GetPlayers()) do roster = roster + 1 end
    s.roster = roster
    s.leaderDeparted = CRCoop.HasLeaderDeparted()
    return s
end

-- Weapons case (coopflow\scenarios\mpbugs-weapons.ps1). Witness tanks on a
-- team nobody is allied with, owned by the peer that builds them: only an
-- owner applies damage to its own objects, so a peer that sees a doubled blast
-- shows it as doubled damage on its witnesses. BuildSyncObject keeps a
-- guest's witnesses replicated and its own.
function BugPlaceWitnesses(cx, cz, distances, angles)
    local placed = 0
    for _, d in ipairs(distances) do
        for _, a in ipairs(angles) do
            local r = math.rad(a)
            local h = exu.BuildSyncObject("avtank", WITNESS_TEAM, SetVector(cx + d * math.cos(r), 0, cz + d * math.sin(r)))
            assert(h and IsAlive(h), "witness failed to spawn")
            SetIndependence(h, 0)
            placed = placed + 1
        end
    end
    return placed
end

-- The launch the player makes: this peer's Armory builds a Daywrecker and
-- lobs it at (tx, tz). The Armory is on this peer's own team, so the
-- cross-team targeting defect stays out of the way.
function BugLaunchDaywrecker(tx, tz)
    local team = GetTeamNum(GetPlayerHandle())
    local p = GetPosition(GetPlayerHandle())
    local armory = exu.BuildSyncObject("avslf", team, SetVector(p.x + 40, 0, p.z + 60))
    assert(armory and IsAlive(armory), "armory failed to spawn")
    SetScrap(team, 100)
    Deploy(armory)
    pendingLaunch = {armory = armory, where = SetVector(tx, 0, tz), deployDeadline = GetTime() + 15}
    M.launch = {team = team, at = GetTime(), tx = tx, tz = tz}
    return M.launch
end

-- A tank on this peer's team fires one stock Splinter (gsplint, mortar slot)
-- at a witness-team target at (tx, tz).
function BugFireSplinter(tx, tz, range)
    local team = GetTeamNum(GetPlayerHandle())
    local target = exu.BuildSyncObject("avtank", WITNESS_TEAM, SetVector(tx, 0, tz))
    local shooter = exu.BuildSyncObject("avtank", team, SetVector(tx, 0, tz - (range or 100)))
    assert(target and shooter, "splinter shooter or target failed to spawn")
    SetIndependence(target, 0); SetIndependence(shooter, 0)
    GiveWeapon(shooter, "gsplint", 3)
    SetWeaponMask(shooter, 8)
    pendingFire = {shooter = shooter, target = target, ammo = GetCurAmmo(shooter), deadline = GetTime() + 30}
    M.fire = {team = team, at = GetTime(), weapon = GetWeaponClass(shooter, 3), ammo = pendingFire.ammo}
    return M.fire
end

-- One site on this peer: terrain heights and normals on a grid, every witness
-- craft in range with its owner and health, and the explosive lifetimes seen.
function BugSite(cx, cz, radius, half, step)
    radius, half, step = radius or 250, half or 30, step or 5
    local s = {time = GetTime(), launch = M.launch, fire = M.fire, heights = {}, normals = {},
               witnesses = {}, lifetimes = {}}
    for dz = -half, half, step do
        for dx = -half, half, step do
            local h, n = GetTerrainHeightAndNormal(SetVector(cx + dx, 0, cz + dz))
            s.heights[#s.heights + 1] = round(h, 3)
            s.normals[#s.normals + 1] = round(n.y, 4)
        end
    end
    -- Strings: the probe truncates arrays past 48 items.
    s.heights, s.normals = table.concat(s.heights, " "), table.concat(s.normals, " ")
    for h in AllObjects() do
        if GetTeamNum(h) == WITNESS_TEAM and IsCraft(h) and IsAlive(h) then
            local p = GetPosition(h)
            local d = math.sqrt((p.x - cx) ^ 2 + (p.z - cz) ^ 2)
            if d <= radius then
                s.witnesses[#s.witnesses + 1] = {id = tostring(h), x = round(p.x), z = round(p.z), health = round(GetCurHealth(h)),
                    mine = IsLocal(h), remote = IsRemote(h)}
            end
        end
    end
    for _, r in ipairs(lifetimes) do
        if math.sqrt((r.lastX - cx) ^ 2 + (r.lastZ - cz) ^ 2) <= radius then s.lifetimes[#s.lifetimes + 1] = r end
    end
    return s
end
