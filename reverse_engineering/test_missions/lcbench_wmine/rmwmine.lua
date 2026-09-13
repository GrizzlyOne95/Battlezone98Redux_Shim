-- rmwmine.lua -- lcbench Arc Mine (weaponmine) boarding-discharge fixture.
--
-- Deploy as addon/lcbench/lcbench.lua and launch
-- `battlezone98redux.exe lcbench.bzn` (bare basename: the engine truncates the
-- mission argument to 15 characters, so a path never survives).
--
-- What this reproduces
-- --------------------
-- A 2026-09-13 play01.bzn capture (no mission script, so engine behaviour only)
-- showed an Arc Mine belonging to the player's OWN team discharging a gmbolt at
-- the player on the exact frame the player boarded a craft -- twice, at capture
-- frames 689 and 1565, the same frames the weapon panel switched from the pilot
-- loadout to the craft loadout. No discharge on either hop-out. The craft took
-- no damage.
--
-- Traced predicate (1.5 `WeaponMine::Simulate` 0x0053F9CF, Redux 0x00612950;
-- semantically identical -- see scene_light_flip_and_arc_mine_boarding_20260913.md):
--
--   for craft in Craft::craftList:
--       if GameObject::FriendP(mine, craft):  continue        -- friendly, skip
--       ...nearest within searchRadius, optional terrain LOS...
--   GameObject::SetTarget(mine, best)
--   if best and (not losFlag or not MayHitFriends(mine, d, 0.3, 1.0)): FIRE
--
--   GameObject::FriendP(GameObject* o) -> o->vtbl[1]()   == ACTUAL team
--   Team::FriendP(n)                   -> n >= 1 and (dwAllies & (1 << n))
--
-- The mine in the capture was team 1, the same team as the player. For a team-1
-- mine to target a team-1 object, `FriendP` has to come back false, and the only
-- way that happens is if the TARGET's team reads something team 1 is not allied
-- with. `Team::FriendP` rejects `n < 1` outright, so a team that reads **0** for
-- even one tick is hostile to its own side's mines. That is what "the weapon
-- mine neutral bug" is naming.
--
-- `Person` is a `Craft` subclass (`Craft::BuildPilot` is declared
-- `Craft * BuildPilot(Craft *, GameObjectClass *)`), so a pilot on foot is in
-- `craftList` and is a candidate target in its own right. Either the pilot
-- being destroyed or the craft being taken over could be the object that reads
-- 0; this fixture is built to say which.
--
-- Arc Mine is `boltmine.odf`: classLabel "weaponmine", weaponName "gmbolt",
-- searchRadius 100.0, heightScale 2.0, maxAmmo 100. That is what the player's
-- own slot-3 "Arc Mine" lays, and gmbolt is the vertical lightning in the clip.
--
-- How the boarding transition is driven
-- -------------------------------------
-- Plain BZ has no Lua API for boarding, `input.map` has no "enter vehicle"
-- action at all (an on-foot pilot boards by walking into the craft), and
-- `exu.SetAsUser` is NOT reachable from an addon mission chunk -- exu.dll loads
-- but a sibling run logged `BOARD ok=false via=no-exu` on twenty consecutive
-- attempts. So the transition is driven through the AI instead:
--
--   spawn an AI craft -> HopOut(craft) -> the engine runs Craft::AbandonPilot,
--   which builds an AI pilot and leaves the craft unoccupied -> GetIn(pilot,
--   craft) issues CMD_GET_IN and the AI pilot walks over and boards.
--
-- That is the same `AbandonPilot`/board pair the player performs, minus the
-- userObject swap. `PersonGetIn::DoStateProlog` requires the target craft to
-- have no AI process, which is exactly what AbandonPilot leaves behind.
--
-- The player's own craft is left alone as a control: if only the AI boarding
-- fires the mine, the userObject swap is not required; if neither fires it,
-- the repro is not on this map.
--
-- Ammo is the witness. maxAmmo = 100 and the discharge is a weapon shot, so a
-- drop in `GetAmmo` names which mine fired on which tick -- a number, not a
-- sprite in a screenshot.
--
-- Lua 5.1 (no goto, no io/os/debug).

local MINE_ODF = "boltmine"
local CRAFT_ODF = "avtank"
local MY_TEAM = 1
local NEUTRAL_TEAM = 0

local SPAWN_CRAFT_AT = 2.0
local LAY_MINES_AT = 5.0
local HOP_AT = 9.0
local GETIN_AT = 14.0
local FAIL_AT = 52.0

local elapsed = 0.0
local aiCraft = nil
local aiPilot = nil
local mineFriendly = nil
local mineNeutral = nil
local spawnedCraft = false
local laidMines = false
local hopped = false
local hopAttempts = 0
local orderedGetIn = false
local boardedSeen = false
local failed = false
local nextHeartbeat = 0.0
local watchForPilot = false

local function Marker(text)
    print(string.format("[WMINE] T+%.2f %s", elapsed, text))
end

local function SafeTeam(handle)
    local team = -1
    if handle ~= nil and IsValid(handle) then
        pcall(function() team = GetTeamNum(handle) end)
    end
    return team
end

-- boltmine.odf has maxAmmo = 100 and the discharge is a weapon shot, so ammo is
-- a numeric, frame-accurate witness that a specific mine actually fired. That
-- is the difference between "a bolt appeared somewhere" and "this mine fired".
local function SafeAmmo(handle)
    local ammo = -1
    if handle ~= nil and IsValid(handle) then
        pcall(function() ammo = GetAmmo(handle) end)
    end
    return ammo
end

local function IsPilot(handle)
    local result = false
    if handle ~= nil and IsValid(handle) then
        pcall(function() result = IsPerson(handle) end)
    end
    return result
end

-- GetPositionNear takes a POSITION, not a handle. Passing the handle straight
-- in fails silently and every spawn in the run reports "no position", which
-- reads exactly like the mission never started. Match the sibling harnesses:
-- GetPosition(handle) first, SetVector(0,0,0) as the floor.
local function AnchorPosition()
    local player = GetPlayerHandle()
    if player ~= nil and IsValid(player) then
        local where = nil
        if pcall(function() where = GetPosition(player) end) and where ~= nil then
            return where
        end
    end
    local origin = nil
    pcall(function() origin = SetVector(0, 0, 0) end)
    return origin
end

local function Spawn(odf, team, distance, label)
    local anchor = AnchorPosition()
    if anchor == nil then
        Marker(string.format("SPAWN_%s FAILED: no anchor position", label))
        return nil
    end
    local where = nil
    local ok = pcall(function() where = GetPositionNear(anchor, distance, distance + 4) end)
    if not ok or where == nil then
        Marker(string.format("SPAWN_%s FAILED: no position", label))
        return nil
    end
    local handle = nil
    ok = pcall(function() handle = BuildObject(odf, team, where) end)
    if not ok or handle == nil or not IsValid(handle) then
        Marker(string.format("SPAWN_%s FAILED: BuildObject(%s, %d) returned nothing",
            label, odf, team))
        return nil
    end
    Marker(string.format("SPAWN_%s odf=%s askedTeam=%d actualTeam=%d ammo=%d dist=%.1f",
        label, odf, team, SafeTeam(handle), SafeAmmo(handle), distance))
    return handle
end

function Start()
    elapsed = 0.0
    aiCraft = nil
    aiPilot = nil
    mineFriendly = nil
    mineNeutral = nil
    spawnedCraft = false
    laidMines = false
    hopped = false
    hopAttempts = 0
    orderedGetIn = false
    boardedSeen = false
    failed = false
    nextHeartbeat = 0.0
    watchForPilot = false
    Marker("START weaponmine boarding fixture")
end

function Update(dt)
    elapsed = elapsed + (dt or 0.0)

    if not spawnedCraft and elapsed >= SPAWN_CRAFT_AT then
        spawnedCraft = true
        aiCraft = Spawn(CRAFT_ODF, MY_TEAM, 40.0, "AICRAFT")
    end

    if not laidMines and elapsed >= LAY_MINES_AT then
        laidMines = true
        -- Same team as the player and as the AI craft. This is the mine the
        -- capture shows firing, so it is the one under test.
        mineFriendly = Spawn(MINE_ODF, MY_TEAM, 26.0, "MINE_TEAM1")
        -- Control. Team::FriendP rejects team 0, so a team-0 mine should be
        -- hostile to everything by construction and fire without any
        -- transition at all. If it never fires, the predicate reading is wrong.
        mineNeutral = Spawn(MINE_ODF, NEUTRAL_TEAM, 32.0, "MINE_TEAM0")
    end

    if laidMines and not hopped and elapsed >= HOP_AT and hopAttempts < 20 then
        if aiCraft ~= nil and IsValid(aiCraft) then
            hopAttempts = hopAttempts + 1
            watchForPilot = true
            local ok = pcall(HopOut, aiCraft)
            Marker(string.format("AI_HOP_OUT attempt=%d ok=%s craftTeam=%d",
                hopAttempts, tostring(ok), SafeTeam(aiCraft)))
            hopped = ok
        else
            Marker("AI_HOP_OUT skipped: no AI craft")
            hopped = true
        end
    end

    if hopped and not orderedGetIn and elapsed >= GETIN_AT then
        orderedGetIn = true
        local api = rawget(_G, "GetIn")
        if api == nil then
            Marker("GET_IN unavailable: no GetIn in _G")
        elseif aiPilot == nil or not IsValid(aiPilot) then
            Marker("GET_IN skipped: the AbandonPilot pilot was never seen by CreateObject")
        elseif aiCraft == nil or not IsValid(aiCraft) then
            Marker("GET_IN skipped: the AI craft is gone")
        else
            local ok = pcall(api, aiPilot, aiCraft, 1)
            Marker(string.format("GET_IN ok=%s pilotTeam=%d craftTeam=%d",
                tostring(ok), SafeTeam(aiPilot), SafeTeam(aiCraft)))
        end
    end

    if orderedGetIn and not boardedSeen and aiPilot ~= nil then
        if not IsValid(aiPilot) then
            boardedSeen = true
            Marker("BOARD_DETECTED the AI pilot object is gone -- it boarded")
        end
    end

    if not failed and elapsed >= FAIL_AT then
        failed = true
        Marker("FAIL_MISSION -- teardown")
        pcall(FailMission, GetTime() + 1.0)
    end

    -- Per tick, not per heartbeat: the discharge lands on a single frame, so a
    -- 5 s sample would step straight over the tick that carries the evidence.
    print(string.format(
        "[WMINE-T] T+%.3f pilot=%s pTeam=%d craftTeam=%d fTeam=%d fAmmo=%d nTeam=%d nAmmo=%d",
        elapsed, tostring(aiPilot ~= nil and IsValid(aiPilot)),
        SafeTeam(aiPilot), SafeTeam(aiCraft),
        SafeTeam(mineFriendly), SafeAmmo(mineFriendly),
        SafeTeam(mineNeutral), SafeAmmo(mineNeutral)))

    if elapsed >= nextHeartbeat then
        nextHeartbeat = elapsed + 5.0
        Marker(string.format("HEARTBEAT hopped=%s ordered=%s boarded=%s pilot=%s",
            tostring(hopped), tostring(orderedGetIn), tostring(boardedSeen),
            tostring(aiPilot ~= nil and IsValid(aiPilot))))
    end
end

-- Craft::AbandonPilot builds the pilot, so the only way to learn its handle is
-- the engine's own creation callback. Claim the first Person that appears after
-- the hop-out is ordered.
function CreateObject(h)
    if watchForPilot and aiPilot == nil and h ~= nil and IsValid(h) and IsPilot(h) then
        aiPilot = h
        watchForPilot = false
        Marker(string.format("AI_PILOT_SEEN team=%d", SafeTeam(h)))
    end
end

function AddObject(h) end
function DeleteObject(h) end

function Save()
    return elapsed, spawnedCraft, laidMines, hopped, orderedGetIn, boardedSeen
end

function Load(a, b, c, d, e, f)
    elapsed = a or 0.0
    spawnedCraft = b or false
    laidMines = c or false
    hopped = d or false
    orderedGetIn = e or false
    boardedSeen = f or false
end
