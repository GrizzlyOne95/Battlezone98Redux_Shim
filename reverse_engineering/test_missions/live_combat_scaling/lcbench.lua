-- Deterministic live-unit scaling benchmark for GOG BZR 2.2.301 profiling.
-- The matching lcbench.bzn intentionally contains only the player so every
-- additional craft and every workload transition is owned by this script.

local VALID_SCENARIOS = {
    quiet = true,
    idle = true,
    movement = true,
    firing = true,
    flight = true,
    ai_idle = true,
    combat = true,
}

local VALID_UNIT_ODFS = {
    svtank = true,
    svfigh = true,
    avtank = true,
    avfigh = true,
    avrckt = true,
    avartl = true,
    avapc = true,
    avwalk = true,
    avmine = true,
    avturr = true,
    aspilo = true,
    svapc = true,
    svwalk = true,
    svmine = true,
    svturr = true,
    sspilo = true,
}

local function readConfig()
    local config = OpenODF("lcbcfg")
    local scenario = GetODFString(config, "Benchmark", "scenario", "idle")
    local unitOdf = GetODFString(config, "Benchmark", "unitOdf", "avtank")
    local count = GetODFInt(config, "Benchmark", "count", 20)
    local distance = GetODFFloat(config, "Benchmark", "distance", 50.0)
    local orientation = GetODFString(
        config, "Benchmark", "orientation", "facing")
    local warmup = GetODFFloat(
        config, "Benchmark", "warmupSeconds", 4.0)
    local measure = GetODFFloat(
        config, "Benchmark", "measureSeconds", 8.0)

    -- Clamp malformed manual edits before they can create an accidental load
    -- spike or a modulo-by-zero firing pair in the deterministic mission.
    if not VALID_SCENARIOS[scenario] then
        scenario = "idle"
    end
    if not VALID_UNIT_ODFS[unitOdf] then
        unitOdf = "avtank"
    end
    count = math.max(0, math.min(200, math.floor(count or 20)))
    if scenario == "quiet" then
        count = 0
    elseif (scenario == "firing" or scenario == "flight" or
            scenario == "combat") and count < 2 then
        count = 2
    end
    distance = math.max(20.0, math.min(2000.0, distance or 50.0))
    if orientation ~= "away" then
        orientation = "facing"
    end
    warmup = math.max(1.0, math.min(60.0, warmup or 4.0))
    measure = math.max(1.0, math.min(300.0, measure or 8.0))
    return scenario, unitOdf, count, distance, orientation, warmup, measure
end

-- OpenODF is only safe after LuaMission startup has entered Start(). Keep
-- inert defaults during module loading, then replace them from lcbcfg.odf.
local BENCH_SCENARIO = "idle"
local BENCH_UNIT_ODF = "avtank"
local BENCH_COUNT = 20
local BENCH_DISTANCE = 50.0
local BENCH_ORIENTATION = "facing"
local BENCH_WARMUP_SECONDS = 4.0
local BENCH_MEASURE_SECONDS = 8.0

local units = {}
local opponents = {}
local moveTargets = {}
local elapsed = 0.0
local measurementStarted = false
local benchmarkEnded = false

local function trace(message)
    print(string.format(
        "[LIVE_COMBAT_BENCH] t=%.3f scenario=%s odf=%s count=%d distance=%.1f orientation=%s %s",
        elapsed,
        BENCH_SCENARIO,
        BENCH_UNIT_ODF,
        BENCH_COUNT,
        BENCH_DISTANCE,
        BENCH_ORIENTATION,
        message))
end

local function removeUnexpectedCraft(player)
    -- A malformed/stale map copy must not silently contaminate a benchmark.
    -- The checked-in BZN contains only the player, so this is normally a no-op.
    local unexpected = {}
    for handle in AllCraft() do
        if handle ~= player then
            unexpected[#unexpected + 1] = handle
        end
    end
    for _, handle in ipairs(unexpected) do
        if IsValid(handle) then
            RemoveObject(handle)
        end
    end
    trace(string.format("unexpected-craft-removed=%d", #unexpected))
end

local function formationPosition(playerPos, transform, index, teamSide)
    local columns = 10
    local row = math.floor(index / columns)
    local column = index % columns
    local lateral = (column - (columns - 1) * 0.5) * 8.0
    if teamSide ~= 0 and BENCH_SCENARIO ~= "flight" then
        lateral = lateral + teamSide * 42.0
    end

    local orientationSign = BENCH_ORIENTATION == "away" and -1.0 or 1.0
    local forward = BENCH_DISTANCE + row * 10.0
    -- The flight phase keeps one formation near the selected view distance
    -- and places its opponent 400 m farther along the same sight line. A short
    -- measurement window therefore captures muzzle flashes and projectiles in
    -- flight with very few impacts, using the stock weapon and ordnance paths.
    if BENCH_SCENARIO == "flight" and teamSide > 0 then
        forward = forward + 400.0
    end
    forward = orientationSign * forward
    local frontX = transform.front_x or 0.0
    local frontZ = transform.front_z or 1.0
    local rightX = transform.right_x or 1.0
    local rightZ = transform.right_z or 0.0
    return SetVector(
        playerPos.x + frontX * forward + rightX * lateral,
        playerPos.y,
        playerPos.z + frontZ * forward + rightZ * lateral)
end

local function spawnUnits(player)
    if BENCH_COUNT <= 0 then
        trace("spawned=0")
        return
    end

    local transform = GetTransform(player)
    local playerPos = GetPosition(player)
    local splitTeams = BENCH_SCENARIO == "firing" or
        BENCH_SCENARIO == "flight" or
        BENCH_SCENARIO == "combat"

    for index = 0, BENCH_COUNT - 1 do
        local side = 0
        -- The AI-idle phase shares the player's team so it exercises native AI
        -- scheduling without accidentally turning the player into an enemy.
        local team = BENCH_SCENARIO == "ai_idle" and 1 or 2
        if splitTeams then
            side = index % 2 == 0 and -1 or 1
            team = side < 0 and 2 or 3
        end

        local position = formationPosition(playerPos, transform, index, side)
        local handle = BuildObject(BENCH_UNIT_ODF, team, position)
        if IsValid(handle) then
            units[#units + 1] = handle
            SetIndependence(handle, BENCH_SCENARIO == "ai_idle" and 1 or 0)
            Stop(handle, 1)
            local targetSide = index % 2 == 0 and 1 or -1
            moveTargets[#moveTargets + 1] = formationPosition(
                playerPos, transform, index, targetSide)
        end
    end

    if splitTeams then
        local team2 = {}
        local team3 = {}
        for _, handle in ipairs(units) do
            if GetTeamNum(handle) == 2 then
                team2[#team2 + 1] = handle
            else
                team3[#team3 + 1] = handle
            end
        end
        for index, handle in ipairs(team2) do
            opponents[handle] = team3[((index - 1) % #team3) + 1]
        end
        for index, handle in ipairs(team3) do
            opponents[handle] = team2[((index - 1) % #team2) + 1]
        end
    end

    trace(string.format("spawned=%d", #units))
end

local function beginWorkload()
    if BENCH_SCENARIO == "movement" then
        for index, handle in ipairs(units) do
            if IsValid(handle) then
                Goto(handle, moveTargets[index], 1)
            end
        end
    elseif BENCH_SCENARIO == "combat" then
        for _, handle in ipairs(units) do
            local target = opponents[handle]
            if IsValid(handle) and IsValid(target) then
                SetIndependence(handle, 1)
                Attack(handle, target, 1)
            end
        end
    elseif BENCH_SCENARIO == "ai_idle" then
        for _, handle in ipairs(units) do
            if IsValid(handle) then
                SetIndependence(handle, 1)
            end
        end
    end
    trace("workload-begin")
end

local function maintainFiringWorkload()
    for _, handle in ipairs(units) do
        local target = opponents[handle]
        if IsValid(handle) and IsValid(target) then
            -- FireAt is the supported direct-fire primitive. Restoring health
            -- and ammo preserves weapon effects and impacts without debris.
            SetCurHealth(handle, GetMaxHealth(handle))
            SetCurAmmo(handle, GetMaxAmmo(handle))
            FireAt(handle, target)
        end
    end
end

function Start()
    BENCH_SCENARIO, BENCH_UNIT_ODF, BENCH_COUNT, BENCH_DISTANCE,
        BENCH_ORIENTATION, BENCH_WARMUP_SECONDS,
        BENCH_MEASURE_SECONDS = readConfig()
    trace("start")
    local player = GetPlayerHandle()
    if not IsValid(player) then
        trace("ERROR player-handle-unavailable")
        benchmarkEnded = true
        return
    end

    SetIndependence(player, 0)
    Stop(player, 1)
    removeUnexpectedCraft(player)
    spawnUnits(player)
    beginWorkload()
    trace("warmup-begin")
end

function Update(dt)
    elapsed = elapsed + (dt or 0.0)

    if BENCH_SCENARIO == "firing" or BENCH_SCENARIO == "flight" then
        maintainFiringWorkload()
    end

    if not measurementStarted and elapsed >= BENCH_WARMUP_SECONDS then
        measurementStarted = true
        trace("measure-begin")
    end

    if not benchmarkEnded and
       elapsed >= BENCH_WARMUP_SECONDS + BENCH_MEASURE_SECONDS then
        benchmarkEnded = true
        trace("measure-end benchmark-end")
    end
end
