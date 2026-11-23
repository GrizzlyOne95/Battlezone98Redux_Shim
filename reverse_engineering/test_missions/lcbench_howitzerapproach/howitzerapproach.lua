-- lcbench howitzer attack-approach live-test overlay (debug only; deployed by
-- run_lchowapproach.ps1 as addon/lcbench/lcbench.lua and restored afterwards).
--
-- Builds a friendly avartl 30 m from the player, an enemy svrecy (no weapon)
-- EnemyGap m beyond it on the heading whose terrain is flattest, and an
-- unarmed enemy svscav decoy beside the path, DecoyAlong m out and DecoySide m
-- to the side. At T+3 the avartl gets Attack(avartl, svrecy), the same
-- CMD_ATTACK the reticle and menu send. With [SinglePlayer]
-- HowitzerAttackApproach on, the howitzer should pack up, drive, deploy in
-- reach and fire at the svrecy, never switching to the decoy (openshim.log
-- [HOWAPPR] lines). Off, stock says "out of range" and it never moves.
-- Marker lines go to BZLogger.txt as [LCHOWA].

local elapsed = 0.0
local stage = 0
local nextPoll = 0.0
local nextHitCheck = 0.0
local howitzer = nil
local enemy = nil
local decoy = nil
local enemyStartHealth = nil
local decoyStartHealth = nil
local lastHealth = nil
local hits = 0
local firstHitTime = nil
local startDist = nil
local minDist = nil
local minDecoyDist = nil
local lastCmd = nil
local lastWho = nil
local whoChanges = 0
local whoOther = 0
local startPos = nil
local maxMoved = 0.0
local loadedAt = nil      -- elapsed when a save was loaded (not saved)
local stopSent = false

local kSampleStep = 8.0
local kEndTime = 130.0
local kDecoyAlong = 200.0
local kDecoySide = 35.0

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

-- Largest height step between samples along the line: a drivable, flat-ish
-- heading keeps the test about the feature, not about pathing over cliffs.
local function LineRoughness(ax, az, bx, bz)
    local dx, dz = bx - ax, bz - az
    local len = math.sqrt(dx * dx + dz * dz)
    local prev = GroundY(ax, az)
    if prev == nil then return nil end
    local worst = 0.0
    local d = kSampleStep
    while d <= len do
        local t = d / len
        local g = GroundY(ax + dx * t, az + dz * t)
        if g == nil then return nil end
        worst = math.max(worst, math.abs(g - prev))
        prev = g
        d = d + kSampleStep
    end
    return worst
end

local function Distance(a, b)
    local p, q = GetPosition(a), GetPosition(b)
    local dx, dy, dz = p.x - q.x, p.y - q.y, p.z - q.z
    return math.sqrt(dx * dx + dy * dy + dz * dz)
end

function Start()
    elapsed = 0.0
    stage = 0
    print("[LCHOWA] START")
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
        local gap = tonumber(EnemyGap) or 800.0

        local best = nil
        for step = 0, 23 do
            local a = baseAngle + math.rad(step * 15.0)
            local fx, fz = math.sin(a), math.cos(a)
            local r = LineRoughness(origin.x + fx * 30.0, origin.z + fz * 30.0,
                origin.x + fx * (30.0 + gap), origin.z + fz * (30.0 + gap))
            if r and (best == nil or r < best.roughness) then
                best = { step = step, fx = fx, fz = fz, roughness = r }
            end
        end
        if best == nil then best = { step = 0, fx = math.sin(baseAngle), fz = math.cos(baseAngle), roughness = -1.0 } end

        local h = Ground(origin.x + best.fx * 30.0, origin.z + best.fz * 30.0, origin.y)
        local e = Ground(origin.x + best.fx * (30.0 + gap), origin.z + best.fz * (30.0 + gap), origin.y)
        -- Side vector (fz, -fx) is perpendicular to the path in XZ.
        local d = Ground(origin.x + best.fx * (30.0 + kDecoyAlong) + best.fz * kDecoySide,
            origin.z + best.fz * (30.0 + kDecoyAlong) - best.fx * kDecoySide, origin.y)
        howitzer = BuildObject("avartl", 1, h)
        enemy = BuildObject("svrecy", 2, e)
        decoy = BuildObject("svscav", 2, d)
        local built = IsValid(howitzer) and IsValid(enemy) and IsValid(decoy)
        startDist = built and Distance(howitzer, enemy) or -1.0
        minDist = startDist
        minDecoyDist = built and Distance(howitzer, decoy) or -1.0
        startPos = built and GetPosition(howitzer) or nil
        if IsValid(decoy) then decoyStartHealth = GetCurHealth(decoy) end
        print(string.format("[LCHOWA] T+%.2f BUILD howitzer=%s enemy=%s decoy=%s built=%s dist=%.1f decoyDist=%.1f heading=+%d roughness=%.2f",
            elapsed, tostring(howitzer), tostring(enemy), tostring(decoy), tostring(built), startDist,
            minDecoyDist, best.step * 15, best.roughness))
        stage = 1
        return
    end

    if stage == 1 and elapsed >= 3.0 then
        if IsValid(enemy) then enemyStartHealth = GetCurHealth(enemy) end
        lastHealth = enemyStartHealth
        local ok, err = pcall(Attack, howitzer, enemy, 1)
        print(string.format("[LCHOWA] T+%.2f ATTACK ok=%s ret=%s enemyHealth=%s", elapsed,
            tostring(ok), tostring(err), tostring(enemyStartHealth)))
        stage = 2
        nextPoll = elapsed
        nextHitCheck = elapsed
        return
    end

    if stage == 2 then
        -- StopAfterLoad (set by run_lchowapproach.ps1 -StopAfterLoad): order
        -- Stop that many seconds after a load, so the attack state ends while
        -- the approach is still driving.
        local stopAfter = tonumber(StopAfterLoad)
        if stopAfter and loadedAt and not stopSent and elapsed >= loadedAt + stopAfter then
            stopSent = true
            local ok, err = pcall(Stop, howitzer, 1)
            print(string.format("[LCHOWA] T+%.2f STOP ok=%s ret=%s", elapsed, tostring(ok), tostring(err)))
        end
        if elapsed >= nextHitCheck or not IsValid(enemy) then
            nextHitCheck = elapsed + 0.25
            local health = IsValid(enemy) and GetCurHealth(enemy) or 0
            if lastHealth ~= nil and health < lastHealth then
                hits = hits + 1
                if firstHitTime == nil then firstHitTime = elapsed end
                print(string.format("[LCHOWA] T+%.2f HIT n=%d enemyHealth=%s->%s", elapsed, hits,
                    tostring(lastHealth), tostring(health)))
            end
            lastHealth = health

            -- Command and target changes, logged when they change.
            local okc, cmd = pcall(GetCurrentCommand, howitzer)
            cmd = okc and cmd or "?"
            local okw, who = pcall(GetCurrentWho, howitzer)
            who = okw and who or nil
            if cmd ~= lastCmd or who ~= lastWho then
                local tag = (who == enemy) and "enemy" or ((who == decoy) and "DECOY" or tostring(who))
                if lastWho ~= nil and who ~= lastWho then whoChanges = whoChanges + 1 end
                if who ~= nil and who ~= enemy then whoOther = whoOther + 1 end
                print(string.format("[LCHOWA] T+%.2f ORDER cmd=%s who=%s", elapsed, tostring(cmd), tag))
                lastCmd = cmd
                lastWho = who
            end
        end
        local d = (IsValid(howitzer) and IsValid(enemy)) and Distance(howitzer, enemy) or -1.0
        if d >= 0.0 and (minDist == nil or d < minDist) then minDist = d end
        if IsValid(howitzer) and IsValid(decoy) then
            local dd = Distance(howitzer, decoy)
            if minDecoyDist == nil or dd < minDecoyDist then minDecoyDist = dd end
        end
        if IsValid(howitzer) and startPos then
            local p = GetPosition(howitzer)
            local mx, mz = p.x - startPos.x, p.z - startPos.z
            maxMoved = math.max(maxMoved, math.sqrt(mx * mx + mz * mz))
        end
        if elapsed >= nextPoll then
            nextPoll = elapsed + 4.0
            local okd, deployed = pcall(IsDeployed, howitzer)
            print(string.format("[LCHOWA] T+%.2f POLL dist=%.1f moved=%.1f deployed=%s enemyHealth=%s",
                elapsed, d, maxMoved, tostring(okd and deployed or "?"), tostring(lastHealth)))
        end
        if elapsed >= kEndTime or not IsValid(enemy) then
            local health = IsValid(enemy) and GetCurHealth(enemy) or 0
            local decoyHealth = IsValid(decoy) and GetCurHealth(decoy) or 0
            print(string.format("[LCHOWA] T+%.2f COMPLETE startDist=%.1f minDist=%.1f moved=%.1f damaged=%s hits=%d firstHit=%s minDecoyDist=%.1f decoyDamaged=%s whoChanges=%d whoOther=%d",
                elapsed, startDist or -1.0, minDist or -1.0, maxMoved,
                tostring(enemyStartHealth ~= nil and health < enemyStartHealth), hits,
                firstHitTime and string.format("T+%.2f", firstHitTime) or "none",
                minDecoyDist or -1.0,
                tostring(decoyStartHealth ~= nil and decoyHealth < decoyStartHealth),
                whoChanges, whoOther))
            FailMission(GetTime() + 1.0)
            stage = 3
        end
    end
end

-- Save/load (run_lchowapproach.ps1 -SaveLoad): the mission state survives a
-- save made mid-approach, so the loaded run carries on from the same stage.
function Save()
    return {
        elapsed = elapsed, stage = stage, nextPoll = nextPoll, nextHitCheck = nextHitCheck,
        howitzer = howitzer, enemy = enemy, decoy = decoy,
        enemyStartHealth = enemyStartHealth, decoyStartHealth = decoyStartHealth,
        lastHealth = lastHealth, hits = hits, firstHitTime = firstHitTime,
        startDist = startDist, minDist = minDist, minDecoyDist = minDecoyDist,
        whoChanges = whoChanges, whoOther = whoOther, maxMoved = maxMoved,
        startX = startPos and startPos.x or nil, startY = startPos and startPos.y or nil,
        startZ = startPos and startPos.z or nil,
    }
end

function Load(s)
    if type(s) ~= "table" then
        print("[LCHOWA] LOAD no state")
        return
    end
    elapsed = s.elapsed or 0.0
    stage = s.stage or 0
    nextPoll = s.nextPoll or 0.0
    nextHitCheck = s.nextHitCheck or 0.0
    howitzer, enemy, decoy = s.howitzer, s.enemy, s.decoy
    enemyStartHealth, decoyStartHealth = s.enemyStartHealth, s.decoyStartHealth
    lastHealth, hits, firstHitTime = s.lastHealth, s.hits or 0, s.firstHitTime
    startDist, minDist, minDecoyDist = s.startDist, s.minDist, s.minDecoyDist
    whoChanges, whoOther, maxMoved = s.whoChanges or 0, s.whoOther or 0, s.maxMoved or 0.0
    startPos = s.startX and SetVector(s.startX, s.startY, s.startZ) or nil
    -- Command/target are re-logged on the first poll after the load.
    lastCmd, lastWho = nil, nil
    loadedAt = elapsed
    local d = (IsValid(howitzer) and IsValid(enemy)) and Distance(howitzer, enemy) or -1.0
    print(string.format("[LCHOWA] T+%.2f LOADED stage=%d howitzer=%s enemy=%s dist=%.1f moved=%.1f",
        elapsed, stage, tostring(howitzer), tostring(enemy), d, maxMoved))
end

function CreateObject(h) end
function AddObject(h) end
function DeleteObject(h) end
function CreatePlayer(id, name, team) end
function AddPlayer(id, name, team) end
function DeletePlayer(id, name, team) end
