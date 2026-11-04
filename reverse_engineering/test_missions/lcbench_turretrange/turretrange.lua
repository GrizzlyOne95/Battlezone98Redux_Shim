-- lcbench turret range and charge-release live-test overlay (debug only;
-- deployed by run_lcturret.ps1 as addon/lcbench/lcbench.lua and restored
-- afterwards).
--
-- Builds a friendly avturr 30 m from the player and an enemy svturr EnemyGap m
-- beyond it, on the heading (every 15 degrees) whose straight muzzle-to-muzzle
-- line clears the terrain by the most. Lua has no line-of-sight call, so the
-- check samples GetTerrainHeightAndNormal every 2 m along that line. At T+3 the
-- avturr gets a MAG cannon (gmaggun: charge1 reaches about 300 m, full charge
-- charge6 75 m/s * 2.5 s = 187.5 m) in its empty GC2 hardpoint. Each drop in
-- the svturr's health is logged as a HIT. Marker lines go to BZLogger.txt.

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

local kMuzzleHeight = 2.5   -- metres above the ground at each turret
local kSampleStep = 2.0
local kMinClearance = 1.0
local kEndTime = 63.0

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

-- Smallest height of the muzzle-to-muzzle line above the terrain between a
-- and b (excluding the 4 m at each end, under the turrets themselves).
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
        local lineY = ay + (by - ay) * t
        minClear = math.min(minClear, lineY - g)
        d = d + kSampleStep
    end
    return minClear
end

local function ClearanceBetween(a, b)
    local p, q = GetPosition(a), GetPosition(b)
    return LineClearance(p.x, p.y + kMuzzleHeight, p.z, q.x, q.y + kMuzzleHeight, q.z)
end

local function Distance(a, b)
    local p, q = GetPosition(a), GetPosition(b)
    local dx, dy, dz = p.x - q.x, p.y - q.y, p.z - q.z
    return math.sqrt(dx * dx + dy * dy + dz * dz)
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
        local baseAngle = 0.0
        if IsValid(player) then
            origin = GetPosition(player)
            local ok, f = pcall(GetFront, player)
            if ok and f and (f.x * f.x + f.z * f.z) > 0.0001 then baseAngle = math.atan2(f.x, f.z) end
        end
        local gap = tonumber(EnemyGap) or 170.0

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
        print(string.format("[LCTURR] T+%.2f LOS search heading=+%d deg clearance=%.2f ok=%s", elapsed,
            best.step * 15, best.clearance, tostring(best.clearance >= kMinClearance)))

        local t = Ground(origin.x + best.fx * 30.0, origin.z + best.fz * 30.0, origin.y)
        local e = Ground(origin.x + best.fx * (30.0 + gap), origin.z + best.fz * (30.0 + gap), origin.y)
        turret = BuildObject("avturr", 1, t)
        enemy = BuildObject("svturr", 2, e)
        local built = IsValid(turret) and IsValid(enemy)
        local c = built and ClearanceBetween(turret, enemy) or nil
        print(string.format("[LCTURR] T+%.2f BUILD turret=%s enemy=%s dist=%.1f LOS clearance=%s ok=%s", elapsed,
            tostring(turret), tostring(enemy), built and Distance(turret, enemy) or -1.0,
            c and string.format("%.2f", c) or "nil", tostring(c ~= nil and c >= kMinClearance)))
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
        lastHealth = enemyStartHealth
        print(string.format("[LCTURR] T+%.2f GIVE gmaggun ok=%s ret=%s weapons=%s enemyHealth=%s", elapsed,
            tostring(ok), tostring(err), table.concat(classes, ","), tostring(enemyStartHealth)))
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
                print(string.format("[LCTURR] T+%.2f HIT n=%d enemyHealth=%s->%s", elapsed, hits,
                    tostring(lastHealth), tostring(health)))
            end
            lastHealth = health
        end
        if elapsed >= nextPoll then
            nextPoll = elapsed + 2.0
            local target = IsValid(turret) and GetTarget(turret) or nil
            local c = (IsValid(turret) and IsValid(enemy)) and ClearanceBetween(turret, enemy) or nil
            print(string.format("[LCTURR] T+%.2f POLL target=%s targetIsEnemy=%s enemyAlive=%s enemyHealth=%s dist=%.1f LOS=%s",
                elapsed, tostring(target), tostring(target ~= nil and target == enemy), tostring(IsValid(enemy)),
                tostring(lastHealth), (IsValid(turret) and IsValid(enemy)) and Distance(turret, enemy) or -1.0,
                c and string.format("%.2f", c) or "nil"))
        end
        if elapsed >= kEndTime or not IsValid(enemy) then
            local health = IsValid(enemy) and GetCurHealth(enemy) or 0
            print(string.format("[LCTURR] T+%.2f COMPLETE enemyAlive=%s enemyHealth=%s start=%s damaged=%s hits=%d firstHit=%s",
                elapsed, tostring(IsValid(enemy)), tostring(health), tostring(enemyStartHealth),
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
