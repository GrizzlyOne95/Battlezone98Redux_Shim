-- rmwmine.lua -- lcbench Arc Mine (weaponmine) boarding-discharge fixture.
--
-- Deploy as addon/lcbench/lcbench.lua and launch
-- `battlezone98redux.exe lcbench.bzn` (bare basename: the engine truncates the
-- mission argument to 15 characters, so a path never survives).
--
-- What this reproduces
-- --------------------
-- A 2026-09-13 play01.bzn capture (no mission script, so engine behaviour only)
-- showed an allied Arc Mine field discharging a gmbolt at the player, on the
-- exact frame the player boarded a craft -- twice, at capture frames 689 and
-- 1565, the same frames the weapon panel switched from the pilot loadout to the
-- craft loadout. No discharge on either hop-out. The craft took no damage: the
-- hull bar is flat across the whole capture.
--
-- Traced predicate (1.5 `WeaponMine::Simulate` 0x0053F9CF, Redux 0x00612950;
-- semantically identical, see weaponmine_hop_friendly_fire_root_cause_20260817.md):
--
--   for craft in Craft::craftList:
--       if GameObject::FriendP(mine, craft):  continue        -- friendly, skip
--       ...nearest within searchRadius, optional terrain LOS...
--   GameObject::SetTarget(mine, best)
--   if best and (not losFlag or not MayHitFriends(mine, d, 0.3, 1.0)): FIRE
--
--   GameObject::FriendP(GameObject*)  -> target->vtbl[1]() == ACTUAL team
--   GameObject::FriendP(int n)        -> n >= 0 and Team::FriendP(teamList, n)
--   Team::FriendP(n)                  -> n >= 1 and (dwAllies & (1 << n))
--
-- So `Team::FriendP` rejects team 0 outright: **any object whose actual team
-- reads 0 is hostile to every weapon mine, including its own side's mines.**
-- `Person` is a `Craft` subclass (`Craft::BuildPilot` returns `Craft *`), so
-- pilots on foot are in `craftList` and are themselves candidate targets.
--
-- The open question this fixture answers is *which* object reads team 0 during
-- the boarding transition -- the pilot being destroyed, or the craft being
-- taken over -- and whether the friendly mine is the shooter at all.
--
-- Arc Mine is `boltmine.odf`: classLabel "weaponmine", weaponName "gmbolt",
-- searchRadius 100.0, heightScale 2.0. That is the object the player's own
-- slot-3 "Arc Mine" lays, and gmbolt is the vertical lightning the capture shows.
--
-- Timeline
--   T+2    lay a friendly (team 1) Arc Mine ~30 m off, inside searchRadius
--   T+4    lay a team-0 Arc Mine beside it: control for "a neutral mine is
--          hostile to everyone", which the predicate above predicts outright
--   T+10   HOP_OUT
--   T+24   BOARD via exu.SetAsUser -- the transition under test
--   every tick: TEAMS line with the player's actual team, whether it is a
--          Person, and both mines' teams, so a one-tick team-0 read is visible
--          in the log rather than inferred
--
-- Lua 5.1 (no goto, no io/os/debug).

local MINE_ODF = "boltmine"
local FRIENDLY_TEAM = 1
local NEUTRAL_TEAM = 0

local elapsed = 0.0
local craft = nil
local mineFriendly = nil
local mineNeutral = nil
local laidFriendly = false
local laidNeutral = false
local hopped = false
local hopAttempts = 0
local pilotReady = false
local boarded = false
local boardAttempts = 0
local nextHeartbeat = 0.0

local LAY_FRIENDLY_AT = 2.0
local LAY_NEUTRAL_AT = 4.0
local HOP_AT = 10.0
local BOARD_AT = 24.0

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

-- boltmine.odf has maxAmmo = 100 and the discharge is a weapon shot, so ammo
-- is a numeric, frame-accurate witness that the mine actually fired. That
-- removes any need to recognise the gmbolt sprite in a screenshot, and it is
-- the difference between "a bolt appeared somewhere" and "this mine fired".
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

-- ExtraUtilities exposes GameObject::SetAsUser as exu.SetAsUser
-- (src/luaexport.cpp:673). Plain BZ has no Lua API for boarding a craft, so
-- this is the only scripted route into the transition under test.
local function TrySetAsUser(handle)
    local mod = rawget(_G, "exu")
    if mod == nil then
        local ok, required = pcall(require, "exu")
        if ok then mod = required end
    end
    if mod == nil or mod.SetAsUser == nil then
        return false, "no-exu"
    end
    local ok = pcall(mod.SetAsUser, handle)
    return ok, "exu.SetAsUser"
end

local function LayMine(team, distance, label)
    local anchor = GetPlayerHandle()
    if anchor == nil or not IsValid(anchor) then return nil end
    local where = nil
    local ok = pcall(function() where = GetPositionNear(anchor, distance, distance + 4) end)
    if not ok or where == nil then
        Marker(string.format("LAY_%s failed: no position", label))
        return nil
    end
    local handle = nil
    ok = pcall(function() handle = BuildObject(MINE_ODF, team, where) end)
    if not ok or handle == nil or not IsValid(handle) then
        Marker(string.format("LAY_%s failed: BuildObject(%s, %d) returned nothing",
            label, MINE_ODF, team))
        return nil
    end
    Marker(string.format("LAY_%s odf=%s askedTeam=%d actualTeam=%d dist=%.1f",
        label, MINE_ODF, team, SafeTeam(handle), distance))
    return handle
end

function Start()
    elapsed = 0.0
    craft = nil
    mineFriendly = nil
    mineNeutral = nil
    laidFriendly = false
    laidNeutral = false
    hopped = false
    hopAttempts = 0
    pilotReady = false
    boarded = false
    boardAttempts = 0
    nextHeartbeat = 0.0
    Marker("START weaponmine boarding fixture")
end

function Update(dt)
    elapsed = elapsed + (dt or 0.0)

    if craft == nil and not hopped then
        local h = GetPlayerHandle()
        if h ~= nil and IsValid(h) and not IsPilot(h) then
            craft = h
            Marker(string.format("CRAFT_CAPTURED team=%d", SafeTeam(h)))
        end
    end

    if not laidFriendly and elapsed >= LAY_FRIENDLY_AT then
        laidFriendly = true
        mineFriendly = LayMine(FRIENDLY_TEAM, 30.0, "FRIENDLY")
    end

    if not laidNeutral and elapsed >= LAY_NEUTRAL_AT then
        laidNeutral = true
        mineNeutral = LayMine(NEUTRAL_TEAM, 34.0, "NEUTRAL")
    end

    if not hopped and elapsed >= HOP_AT and hopAttempts < 20 then
        local h = GetPlayerHandle()
        if h ~= nil and IsValid(h) then
            hopAttempts = hopAttempts + 1
            local ok = pcall(HopOut, h)
            Marker(string.format("HOP_OUT attempt=%d ok=%s", hopAttempts, tostring(ok)))
            hopped = ok
        end
    end

    if hopped and not pilotReady then
        local h = GetPlayerHandle()
        if IsPilot(h) then
            pilotReady = true
            Marker(string.format("PILOT_READY team=%d", SafeTeam(h)))
        end
    end

    if pilotReady and not boarded and elapsed >= BOARD_AT and boardAttempts < 20 then
        boardAttempts = boardAttempts + 1
        if craft ~= nil and IsValid(craft) then
            Marker(string.format("PRE_BOARD pilotTeam=%d craftTeam=%d",
                SafeTeam(GetPlayerHandle()), SafeTeam(craft)))
            local ok, how = TrySetAsUser(craft)
            Marker(string.format("BOARD attempt=%d ok=%s via=%s", boardAttempts, tostring(ok), how))
            if ok then boarded = true end
        else
            Marker("BOARD skipped: craft handle is gone")
            boarded = true
        end
    end

    -- Per-tick, not per-heartbeat: the discharge lands on a single frame, so a
    -- 5 s sample would miss the one tick where a team reads 0.
    local player = GetPlayerHandle()
    print(string.format(
        "[WMINE-T] T+%.3f onFoot=%s pTeam=%d craftTeam=%d fTeam=%d fAmmo=%d nTeam=%d nAmmo=%d",
        elapsed, tostring(IsPilot(player)),
        SafeTeam(player), SafeTeam(craft),
        SafeTeam(mineFriendly), SafeAmmo(mineFriendly),
        SafeTeam(mineNeutral), SafeAmmo(mineNeutral)))

    if elapsed >= nextHeartbeat then
        nextHeartbeat = elapsed + 5.0
        Marker(string.format("HEARTBEAT hopped=%s boarded=%s fMine=%s nMine=%s",
            tostring(hopped), tostring(boarded),
            tostring(mineFriendly ~= nil and IsValid(mineFriendly)),
            tostring(mineNeutral ~= nil and IsValid(mineNeutral))))
    end
end

function CreateObject(h) end
function AddObject(h) end
function DeleteObject(h) end

function Save()
    return elapsed, hopped, pilotReady, boarded, laidFriendly, laidNeutral
end

function Load(a, b, c, d, e, f)
    elapsed = a or 0.0
    hopped = b or false
    pilotReady = c or false
    boarded = d or false
    laidFriendly = e or false
    laidNeutral = f or false
end
