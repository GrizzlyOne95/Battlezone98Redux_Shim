-- lcbench neutral-team Attack command qualification overlay.
-- Each process tests one directed order while logging command state, target,
-- health, ammo, and shot attribution. UI orders remain a separate manual gate.

local elapsed = 0.0
local nextPoll = 0.0
local stage = 0
local selectedCase = "n2p"
local fixtureCommit = "unknown"
local player = nil
local ally = nil
local neutral = nil
local enemy = nil

local function Place(range, lateral)
    local transform = GetTransform(player)
    local origin = GetPosition(player)
    local frontX = transform.front_x or 0.0
    local frontZ = transform.front_z or 1.0
    local rightX = transform.right_x or 1.0
    local rightZ = transform.right_z or 0.0
    local base = SetVector(
        origin.x + frontX * range + rightX * lateral,
        origin.y,
        origin.z + frontZ * range + rightZ * lateral)
    return GetPositionNear(base, 2.0, 4.0)
end

local function ValidText(h)
    return tostring(h ~= nil and IsValid(h))
end

local function Num(h, fn, fallback)
    if h ~= nil and IsValid(h) then return fn(h) end
    return fallback
end

local function Snapshot(label)
    print(string.format(
        "[LCROAD][NEUT] T+%.3f %s " ..
        "ally{v=%s team=%d cmd=%s who=%s hp=%.3f ammo=%.3f shot=%s} " ..
        "neutral{v=%s team=%d cmd=%s who=%s hp=%.3f ammo=%.3f shot=%s} " ..
        "enemy{v=%s team=%d cmd=%s who=%s hp=%.3f ammo=%.3f shot=%s} " ..
        "player{hp=%.3f shot=%s}",
        elapsed, label,
        ValidText(ally), Num(ally, GetTeamNum, -1), tostring(Num(ally, GetCurrentCommand, -1)),
        tostring(Num(ally, GetCurrentWho, 0)), Num(ally, GetHealth, -1.0),
        Num(ally, GetAmmo, -1.0), tostring(Num(ally, GetWhoShotMe, 0)),
        ValidText(neutral), Num(neutral, GetTeamNum, -1), tostring(Num(neutral, GetCurrentCommand, -1)),
        tostring(Num(neutral, GetCurrentWho, 0)), Num(neutral, GetHealth, -1.0),
        Num(neutral, GetAmmo, -1.0), tostring(Num(neutral, GetWhoShotMe, 0)),
        ValidText(enemy), Num(enemy, GetTeamNum, -1), tostring(Num(enemy, GetCurrentCommand, -1)),
        tostring(Num(enemy, GetCurrentWho, 0)), Num(enemy, GetHealth, -1.0),
        Num(enemy, GetAmmo, -1.0), tostring(Num(enemy, GetWhoShotMe, 0)),
        Num(player, GetHealth, -1.0), tostring(Num(player, GetWhoShotMe, 0))))
end

function Start()
    elapsed = 0.0
    nextPoll = 0.0
    stage = 0
    local config = OpenODF("rmncfg")
    selectedCase = GetODFString(config, "Roadmap", "case", "n2p")
    fixtureCommit = GetODFString(config, "Roadmap", "commit", "unknown")
    player = GetPlayerHandle()
    print(string.format("[LCROAD][NEUT] START build=2.2.301 case=%s commit=%s player=%s",
        tostring(selectedCase), tostring(fixtureCommit), tostring(player)))

    ally = BuildObject("avfigh", 1, Place(35.0, -15.0))
    neutral = BuildObject("svfigh", 0, Place(55.0, 0.0))
    enemy = BuildObject("svfigh", 2, Place(75.0, 15.0))
    local handles = {ally, neutral, enemy}
    local i
    for i = 1, #handles do
        if IsValid(handles[i]) then
            SetIndependence(handles[i], 0)
            Stop(handles[i], 1)
        end
    end
    Snapshot("SPAWNED")
end

function Update(dt)
    elapsed = elapsed + (dt or 0.0)

    if stage == 0 and elapsed >= 1.0 then
        if selectedCase == "n2p" then
            print("[LCROAD][NEUT] ISSUE attacker=neutral target=player priority=1")
            Attack(neutral, player, 1)
        elseif selectedCase == "a2n" then
            print("[LCROAD][NEUT] ISSUE attacker=ally target=neutral priority=1")
            Attack(ally, neutral, 1)
        elseif selectedCase == "a2e" then
            print("[LCROAD][NEUT] ISSUE attacker=ally target=enemy priority=1")
            Attack(ally, enemy, 1)
        elseif selectedCase == "a2f" then
            print("[LCROAD][NEUT] ISSUE attacker=ally target=player priority=0")
            Attack(ally, player, 0)
        end
        Snapshot("ISSUED")
        nextPoll = elapsed + 0.5
        stage = 1
    end

    if stage == 1 and elapsed >= nextPoll then
        Snapshot("POLL")
        nextPoll = nextPoll + 0.5
    end

    if stage == 1 and elapsed >= 8.0 then
        Snapshot("RESULT")
        print(string.format("[LCROAD][NEUT] T+%.3f COMPLETE", elapsed))
        FailMission(GetTime() + 1.0)
        stage = 2
    end
end

function CreateObject(h) end
function AddObject(h) end
function DeleteObject(h) end
function CreatePlayer(id, name, team) end
function AddPlayer(id, name, team) end
function DeletePlayer(id, name, team) end

