-- lcbench turret range-refresh live-test overlay (debug only; deployed by
-- run_lcturret.ps1 as addon/lcbench/lcbench.lua and restored afterwards).
--
-- Builds a friendly avturr 30 m in front of the player and an enemy svturr
-- 170 m beyond it: inside the avturr's 200 m rangeScan and the full-charge MAG
-- reach (charge6: 75 m/s * 2.5 s = 187.5 m), outside its stock minigun reach
-- (bullet5: 120 m/s * 1.3 s = 156 m). At T+3 the avturr gets a
-- MAG cannon (gmaggun, about 300 m) in its empty GC2 hardpoint. The turret
-- caches its range only at Init/PostLoad, so without the OpenShim refresh it
-- keeps the 156 m range and never engages; with it, it fires on the svturr.
-- Marker lines go to BZLogger.txt.

local elapsed = 0.0
local stage = 0
local nextPoll = 0.0
local turret = nil
local enemy = nil
local enemyStartHealth = nil

local function Ground(x, z, fallbackY)
    local ok, y = pcall(TerrainFindFloor, x, z)
    if ok and type(y) == "number" then return SetVector(x, y, z) end
    return SetVector(x, fallbackY, z)
end

local function Distance(a, b)
    local p, q = GetPosition(a), GetPosition(b)
    local dx, dz = p.x - q.x, p.z - q.z
    return math.sqrt(dx * dx + dz * dz)
end

function Start()
    elapsed = 0.0
    stage = 0
    print("[LCTURR] START")
end

function Update(dt)
    elapsed = elapsed + (dt or 0.0)

    if stage == 0 and elapsed >= 1.0 then
        local player = GetPlayerHandle()
        local origin = SetVector(0.0, 0.0, 0.0)
        local front = SetVector(0.0, 0.0, 1.0)
        if IsValid(player) then
            origin = GetPosition(player)
            local ok, f = pcall(GetFront, player)
            if ok and f then front = f end
        end
        local len = math.sqrt(front.x * front.x + front.z * front.z)
        if len < 0.01 then front = SetVector(0.0, 0.0, 1.0) else front = SetVector(front.x / len, 0.0, front.z / len) end
        local t = Ground(origin.x + front.x * 30.0, origin.z + front.z * 30.0, origin.y)
        local gap = tonumber(EnemyGap) or 170.0
        local e = Ground(origin.x + front.x * (30.0 + gap), origin.z + front.z * (30.0 + gap), origin.y)
        turret = BuildObject("avturr", 1, t)
        enemy = BuildObject("svturr", 2, e)
        print(string.format("[LCTURR] T+%.2f BUILD turret=%s enemy=%s dist=%.1f", elapsed, tostring(turret), tostring(enemy),
            (IsValid(turret) and IsValid(enemy)) and Distance(turret, enemy) or -1.0))
        stage = 1
        return
    end

    if stage == 1 and elapsed >= 3.0 then
        local ok, err = pcall(GiveWeapon, turret, "gmaggun", 1)
        local classes = {}
        for slot = 0, 4 do
            local cok, c = pcall(GetWeaponClass, turret, slot)
            classes[#classes + 1] = tostring(slot) .. "=" .. tostring(cok and c or "?")
        end
        if IsValid(enemy) then enemyStartHealth = GetCurHealth(enemy) end
        print(string.format("[LCTURR] T+%.2f GIVE gmaggun ok=%s ret=%s weapons=%s enemyHealth=%s", elapsed,
            tostring(ok), tostring(err), table.concat(classes, ","), tostring(enemyStartHealth)))
        stage = 2
        nextPoll = elapsed
        return
    end

    if stage == 2 then
        if elapsed >= nextPoll then
            nextPoll = elapsed + 2.0
            local target = IsValid(turret) and GetTarget(turret) or nil
            local health = IsValid(enemy) and GetCurHealth(enemy) or -1
            print(string.format("[LCTURR] T+%.2f POLL target=%s targetIsEnemy=%s enemyAlive=%s enemyHealth=%s dist=%.1f",
                elapsed, tostring(target), tostring(target ~= nil and target == enemy), tostring(IsValid(enemy)), tostring(health),
                (IsValid(turret) and IsValid(enemy)) and Distance(turret, enemy) or -1.0))
        end
        if elapsed >= 33.0 then
            local health = IsValid(enemy) and GetCurHealth(enemy) or 0
            print(string.format("[LCTURR] T+%.2f COMPLETE enemyAlive=%s enemyHealth=%s start=%s damaged=%s", elapsed,
                tostring(IsValid(enemy)), tostring(health), tostring(enemyStartHealth),
                tostring(enemyStartHealth ~= nil and health < enemyStartHealth)))
            FailMission(GetTime() + 1.0)
            stage = 3
        end
    end
end

function CreateObject(h) end
function AddObject(h) end
function DeleteObject(h) end
function CreatePlayer(id, name, team) end
function AddPlayer(id, name, team) end
function DeletePlayer(id, name, team) end
