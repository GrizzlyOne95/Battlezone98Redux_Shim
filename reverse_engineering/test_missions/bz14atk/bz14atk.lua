-- Controlled attack-behavior validation + live AI task census mission.
-- Spawns attacker/target pairs, issues the configured command, and prints
-- one telemetry line per second so native-side censuses (bz14_task_census.js)
-- and stock-vs-experimental runs can be compared quantitatively.
--
-- Lua 5.1 only; no external libraries; print() only. Avoids ObjectiveObjects()
-- (broken iterator). ODF names are <= 8 characters.

local attackers = {}
local targets = {}
local playerHandle = nil

local elapsed = 0.0
local ordered = false
local finished = false
local lastTelemetry = -1.0
local lastMove = 0.0
local firstHitTime = nil
local targetStartHealth = nil

local CFG_COUNT = 1
local CFG_DISTANCE = 80.0
local CFG_ENGAGE_DISTANCE = 45.0
local CFG_TARGET_MOVE = "none"
local CFG_COMMAND = "attack"
local CFG_RUN_SECONDS = 40.0
local CFG_UNIT_ODF = "avtank"
local CFG_TARGET_ODF = "ivtank"

local function readConfig()
    local ok, config = pcall(OpenODF, "bz14cfg")
    if not ok or not config then
        print("[BZ14ATK] no bz14cfg.odf; using defaults")
        return
    end
    CFG_COUNT = GetODFInt(config, "Bz14Attack", "count", CFG_COUNT)
    CFG_DISTANCE = GetODFFloat(config, "Bz14Attack", "distance", CFG_DISTANCE)
    CFG_ENGAGE_DISTANCE =
        GetODFFloat(config, "Bz14Attack", "engageDistance", CFG_ENGAGE_DISTANCE)
    CFG_TARGET_MOVE =
        GetODFString(config, "Bz14Attack", "targetMove", CFG_TARGET_MOVE)
    CFG_COMMAND = GetODFString(config, "Bz14Attack", "command", CFG_COMMAND)
    CFG_RUN_SECONDS =
        GetODFFloat(config, "Bz14Attack", "runSeconds", CFG_RUN_SECONDS)
    CFG_UNIT_ODF = GetODFString(config, "Bz14Attack", "unitOdf", CFG_UNIT_ODF)
    CFG_TARGET_ODF =
        GetODFString(config, "Bz14Attack", "targetOdf", CFG_TARGET_ODF)
end

local function trace(message)
    print(string.format("[BZ14ATK] t=%.2f %s", elapsed, message))
end

local function getXZ(handle)
    local p = GetPosition(handle)
    return p.x, p.y, p.z
end

local function tryCmd(fn)
    -- One bad native binding must not kill the whole census run.
    local ok, err = pcall(fn)
    if not ok then
        trace("command error: " .. tostring(err))
    end
    return ok
end

local function issueCommand(a, tgt)
    if CFG_COMMAND == "attack" then
        Attack(a, tgt)
        SetIndependence(a, 1)
    elseif CFG_COMMAND == "hunt" then
        Hunt(a)
        SetIndependence(a, 1)
    elseif CFG_COMMAND == "follow" then
        Follow(a, playerHandle)
    elseif CFG_COMMAND == "defend2" then
        Defend2(a, playerHandle)
    elseif CFG_COMMAND == "formation" then
        -- Shared reference documents Formation(me, him); some builds bind
        -- argument 2 as a number. Try the documented shape first, fall back.
        if not tryCmd(function() Formation(a, playerHandle) end) then
            tryCmd(function() Formation(a, 1) end)
        end
    elseif CFG_COMMAND == "auto" then
        -- No order at all: autonomous retaliation/engagement only.
        Stop(a)
        SetIndependence(a, 1)
    else -- "none"
        Stop(a)
        SetIndependence(a, 0)
    end
end

-- Follow-family commands need the threat next to the followed object, not
-- straight ahead of the attacker; place the target near the player instead.
local function targetAnchor(ax, az, fx, fz)
    if CFG_COMMAND == "follow" or CFG_COMMAND == "defend2" or
        CFG_COMMAND == "formation" then
        local pp = GetPosition(playerHandle)
        return pp.x + fx * CFG_ENGAGE_DISTANCE,
               pp.z + fz * CFG_ENGAGE_DISTANCE
    end
    return ax + fx * CFG_DISTANCE, az + fz * CFG_DISTANCE
end

function Start()
    readConfig()
    for handle in AllCraft() do
        if IsValid(handle) and GetTeamNum(handle) == 1 then
            playerHandle = handle
            break
        end
    end
    if not playerHandle then
        print("[BZ14ATK] FATAL: no player craft on team 1")
        return
    end

    local tp = GetTransform(playerHandle)
    local fx = tp.front_x or 0.0
    local fz = tp.front_z or 1.0
    local rx = tp.right_x or 1.0
    local rz = tp.right_z or 0.0
    local pp = GetPosition(playerHandle)

    for i = 0, CFG_COUNT - 1 do
        local lateral = (i - (CFG_COUNT - 1) * 0.5) * 25.0
        local ax = pp.x + fx * 20.0 + rx * lateral
        local az = pp.z + fz * 20.0 + rz * lateral
        local tx, tz = targetAnchor(ax, az, fx, fz)
        local a = BuildObject(CFG_UNIT_ODF, 1, SetVector(ax, pp.y, az))
        local t = BuildObject(CFG_TARGET_ODF, 2, SetVector(tx, pp.y, tz))
        trace(string.format(
            "spawn pair=%d a=%s t=%s at(%.1f,%.1f) tgt(%.1f,%.1f)",
            i - 1, tostring(a), tostring(t), ax, az, tx, tz))
        if a ~= 0 and t ~= 0 and IsValid(a) and IsValid(t) then
            attackers[#attackers + 1] = a
            targets[#targets + 1] = t
            Stop(a)
            Stop(t)
        else
            trace(string.format("spawn-failed pair=%d a=%s t=%s",
                                i - 1, tostring(a), tostring(t)))
        end
    end
    trace(string.format(
        "config count=%d dist=%.1f engage=%.1f move=%s command=%s " ..
            "unit=%s target=%s",
        CFG_COUNT, CFG_DISTANCE, CFG_ENGAGE_DISTANCE, CFG_TARGET_MOVE,
        CFG_COMMAND, CFG_UNIT_ODF, CFG_TARGET_ODF))
end

local function applyOrders()
    for i, a in ipairs(attackers) do
        if IsValid(a) then
            local tgt = targets[i]
            issueCommand(a, tgt)
            trace(string.format("ordered pair=%d cmd=%s att=%s tgt=%s",
                                i - 1, CFG_COMMAND, tostring(a),
                                tostring(tgt)))
        end
    end
    if targets[1] and IsValid(targets[1]) then
        targetStartHealth = GetCurHealth(targets[1])
    end
end

local function driveTargetMovement()
    if CFG_TARGET_MOVE == "none" then
        return
    end
    for i, t in ipairs(targets) do
        if IsValid(t) and IsValid(attackers[i]) then
            local tx, ty, tz = getXZ(t)
            local ax, ay, az = getXZ(attackers[i])
            local dx, dz = tx - ax, tz - az
            local len = math.sqrt(dx * dx + dz * dz)
            if len > 1.0 then
                dx, dz = dx / len, dz / len
                local mx, mz
                if CFG_TARGET_MOVE == "away" then
                    mx, mz = tx + dx * 60.0, tz + dz * 60.0
                elseif CFG_TARGET_MOVE == "toward" then
                    mx, mz = ax, az
                else -- perp: cross sideways relative to the attacker ray
                    mx, mz = tx - dz * 70.0, tz + dx * 70.0
                end
                Goto(t, SetVector(mx, ty, mz))
            end
        end
    end
end

local function checkFirstHit()
    if firstHitTime or not targetStartHealth then
        return
    end
    if targets[1] and IsValid(targets[1]) then
        local h = GetCurHealth(targets[1])
        if h < targetStartHealth then
            firstHitTime = elapsed
            trace(string.format("first-hit t=%.2f", firstHitTime))
        end
    end
end

local function telemetry()
    for i, a in ipairs(attackers) do
        if IsValid(a) then
            local ax, ay, az = getXZ(a)
            local cmd = GetCurrentCommand(a)
            local distTxt = "-"
            if targets[i] and IsValid(targets[i]) then
                local tx, _, tz = getXZ(targets[i])
                local ddx, ddz = ax - tx, az - tz
                distTxt = string.format("%.1f",
                    math.sqrt(ddx * ddx + ddz * ddz))
            end
            print(string.format(
                "[BZ14ATK] tel t=%.2f pair=%d odf=%s cls=%s team=%d " ..
                    "att(%0.1f,%0.1f) dist=%s cmd=%s who=%s alive=%s",
                elapsed, i - 1, GetOdf(a), GetClassLabel(a),
                GetTeamNum(a), ax, az, distTxt,
                tostring(cmd),
                tostring(GetCurrentWho(a)),
                tostring(IsAlive(a))))
        end
    end
end

local function respawnTargets()
    -- Continuous-engagement mode for kill-oriented commands: keep fresh
    -- targets coming so attack tasks stay live regardless of probe timing.
    if CFG_COMMAND ~= "attack" and CFG_COMMAND ~= "auto" and
        CFG_COMMAND ~= "hunt" then
        return
    end
    local anyAlive = false
    for i, t in ipairs(targets) do
        if IsValid(t) and IsAlive(t) ~= false then
            anyAlive = true
        elseif t and not IsValid(t) then
            targets[i] = nil
        end
    end
    if anyAlive then
        return
    end
    local pp = GetPosition(playerHandle)
    local tp = GetTransform(playerHandle)
    local fx = tp.front_x or 0.0
    local fz = tp.front_z or 1.0
    for i, a in ipairs(attackers) do
        if IsValid(a) then
            local ax, ay, az = getXZ(a)
            local t = BuildObject(CFG_TARGET_ODF, 2,
                SetVector(ax + fx * CFG_DISTANCE, ay,
                          az + fz * CFG_DISTANCE))
            if t and t ~= 0 then
                Stop(t)
                table.insert(targets, t)
                if CFG_COMMAND == "attack" then
                    Attack(a, t)
                elseif CFG_COMMAND == "hunt" then
                    Hunt(a)
                end
                trace(string.format("respawn target for pair=%d tgt=%s",
                                    i - 1, tostring(t)))
            end
        end
    end
    firstHitTime = nil
    if targets[1] and IsValid(targets[1]) then
        targetStartHealth = GetCurHealth(targets[1])
    end
end

function Update(dt)
    elapsed = elapsed + (dt or 0.0)

    if not ordered and elapsed >= 1.5 then
        ordered = true
        applyOrders()
    end

    if ordered then
        if CFG_TARGET_MOVE ~= "none" and (elapsed - lastMove) >= 0.5 then
            lastMove = elapsed
            driveTargetMovement()
        end
        checkFirstHit()
        respawnTargets()
    end

    if elapsed - lastTelemetry >= 1.0 then
        lastTelemetry = elapsed
        telemetry()
    end

    if not finished and elapsed >= CFG_RUN_SECONDS then
        finished = true
        local kills = 0
        for _, t in ipairs(targets) do
            if not IsValid(t) or IsAlive(t) == false then
                kills = kills + 1
            end
        end
        trace(string.format("summary kills=%d/%d firstHit=%s",
                            kills, #targets,
                            tostring(firstHitTime)))
    end
end
