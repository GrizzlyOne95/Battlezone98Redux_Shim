-- lcbench turret attack-order live-test overlay (debug only; deployed by
-- run_lcturretattack.ps1 as addon/lcbench/lcbench.lua and restored afterwards).
--
-- Builds a friendly avturr 30 m from the player and an enemy svrecy (no weapon,
-- so it cannot fight back) EnemyGap m beyond it, on the heading whose terrain
-- line is clearest. At T+3 the avturr gets Attack(avturr, svrecy), the same
-- CMD_ATTACK the reticle and menu send. With [SinglePlayer] TurretAttackOrders
-- on, a target beyond weapon range should make the turret pack up, close in,
-- deploy and fire (openshim.log [TURRETATK] lines). Each drop in the svrecy's
-- health is logged as a HIT. Marker lines go to BZLogger.txt as [LCTATK].

local elapsed = 0.0
local stage = 0
local nextPoll = 0.0
local nextHitCheck = 0.0
local turret = nil
local enemy = nil
local enemyStartHealth = nil
local lastHealth = nil
local hits = 0
local firstHitTime = nil
local startDist = nil
local minDist = nil

local kSampleStep = 4.0
local kMuzzleHeight = 2.5
local kEndTime = 90.0

local function GroundY(x, z)
    local ok, y = pcall(GetTerrainHeightAndNormal, SetVector(x, 0.0, z))
    if ok and type(y) == "number" then return y end
    return nil
end

local function Ground(x, z, fallbackY)
    local ok, y = pcall(TerrainFindFloor, x, z)
    if ok and type(y) == "number" then return SetVector(x, y, z) end
    return SetVector(x, fallbackY, z)
end

local function LineClearance(ax, ay, az, bx, by, bz)
    local dx, dz = bx - ax, bz - az
    local len = math.sqrt(dx * dx + dz * dz)
    if len < 10.0 then return nil end
    local minClear = math.huge
    local d = 4.0
    while d <= len - 4.0 do
        local t = d / len
        local g = GroundY(ax + dx * t, az + dz * t)
        if g == nil then return nil end
        minClear = math.min(minClear, ay + (by - ay) * t - g)
        d = d + kSampleStep
    end
    return minClear
end

local function Distance(a, b)
    local p, q = GetPosition(a), GetPosition(b)
    local dx, dy, dz = p.x - q.x, p.y - q.y, p.z - q.z
    return math.sqrt(dx * dx + dy * dy + dz * dz)
end

function Start()
    elapsed = 0.0
    stage = 0
    print("[LCTATK] START")
end

function Update(dt)
    elapsed = elapsed + (dt or 0.0)

    if stage == 0 and elapsed >= 1.0 then
        local player = GetPlayerHandle()
        local origin = SetVector(0.0, 0.0, 0.0)
        local baseAngle = 0.0
        if IsValid(player) then
            origin = GetPosition(player)
            local ok, f = pcall(GetFront, player)
            if ok and f and (f.x * f.x + f.z * f.z) > 0.0001 then baseAngle = math.atan2(f.x, f.z) end
        end
        local gap = tonumber(EnemyGap) or 450.0

        local best = nil
        for step = 0, 23 do
            local a = baseAngle + math.rad(step * 15.0)
            local fx, fz = math.sin(a), math.cos(a)
            local tx, tz = origin.x + fx * 30.0, origin.z + fz * 30.0
            local ex, ez = origin.x + fx * (30.0 + gap), origin.z + fz * (30.0 + gap)
            local ty, ey = GroundY(tx, tz), GroundY(ex, ez)
            if ty and ey then
                local c = LineClearance(tx, ty + kMuzzleHeight, tz, ex, ey + kMuzzleHeight, ez)
                if c and (best == nil or c > best.clearance) then
                    best = { step = step, fx = fx, fz = fz, clearance = c }
                end
            end
        end
        if best == nil then best = { step = 0, fx = math.sin(baseAngle), fz = math.cos(baseAngle), clearance = -1.0 } end

        local t = Ground(origin.x + best.fx * 30.0, origin.z + best.fz * 30.0, origin.y)
        local e = Ground(origin.x + best.fx * (30.0 + gap), origin.z + best.fz * (30.0 + gap), origin.y)
        turret = BuildObject("avturr", 1, t)
        enemy = BuildObject("svrecy", 2, e)
        local built = IsValid(turret) and IsValid(enemy)
        startDist = built and Distance(turret, enemy) or -1.0
        minDist = startDist
        print(string.format("[LCTATK] T+%.2f BUILD turret=%s enemy=%s dist=%.1f heading=+%d clearance=%.2f",
            elapsed, tostring(turret), tostring(enemy), startDist, best.step * 15, best.clearance))
        stage = 1
        return
    end

    if stage == 1 and elapsed >= 3.0 then
        if IsValid(enemy) then enemyStartHealth = GetCurHealth(enemy) end
        lastHealth = enemyStartHealth
        local ok, err = pcall(Attack, turret, enemy, 1)
        print(string.format("[LCTATK] T+%.2f ATTACK ok=%s ret=%s enemyHealth=%s", elapsed,
            tostring(ok), tostring(err), tostring(enemyStartHealth)))
        stage = 2
        nextPoll = elapsed
        nextHitCheck = elapsed
        return
    end

    if stage == 2 then
        if elapsed >= nextHitCheck or not IsValid(enemy) then
            nextHitCheck = elapsed + 0.25
            local health = IsValid(enemy) and GetCurHealth(enemy) or 0
            if lastHealth ~= nil and health < lastHealth then
                hits = hits + 1
                if firstHitTime == nil then firstHitTime = elapsed end
                print(string.format("[LCTATK] T+%.2f HIT n=%d enemyHealth=%s->%s", elapsed, hits,
                    tostring(lastHealth), tostring(health)))
            end
            lastHealth = health
        end
        local d = (IsValid(turret) and IsValid(enemy)) and Distance(turret, enemy) or -1.0
        if d >= 0.0 and (minDist == nil or d < minDist) then minDist = d end
        if elapsed >= nextPoll then
            nextPoll = elapsed + 2.0
            local okc, cmd = pcall(GetCurrentCommand, turret)
            print(string.format("[LCTATK] T+%.2f POLL dist=%.1f cmd=%s enemyHealth=%s",
                elapsed, d, tostring(okc and cmd or "?"), tostring(lastHealth)))
        end
        if elapsed >= kEndTime or not IsValid(enemy) then
            local health = IsValid(enemy) and GetCurHealth(enemy) or 0
            print(string.format("[LCTATK] T+%.2f COMPLETE startDist=%.1f minDist=%.1f damaged=%s hits=%d firstHit=%s",
                elapsed, startDist or -1.0, minDist or -1.0,
                tostring(enemyStartHealth ~= nil and health < enemyStartHealth), hits,
                firstHitTime and string.format("T+%.2f", firstHitTime) or "none"))
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
