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
    -- Spatially dispersed firing clusters. Exists to test aggregate-batch
    -- culling and ordering: generic chunklets are produced in several clusters
    -- hundreds of metres apart, so only one cluster can be inside the frustum
    -- at a time and the rest are off-screen or behind the camera.
    dispersed = true,
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
    local clusterCount = GetODFInt(config, "Benchmark", "clusterCount", 4)
    local clusterRadius = GetODFFloat(
        config, "Benchmark", "clusterRadius", 300.0)
    local spinSeconds = GetODFFloat(config, "Benchmark", "spinSeconds", 0.0)

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
    clusterCount = math.max(1, math.min(8, math.floor(clusterCount or 4)))
    clusterRadius = math.max(50.0, math.min(1500.0, clusterRadius or 300.0))
    -- 0 disables rotation entirely, which is the static-camera control run.
    spinSeconds = math.max(0.0, math.min(60.0, spinSeconds or 0.0))
    if scenario == "dispersed" and count < 2 * clusterCount then
        count = 2 * clusterCount
    end
    return scenario, unitOdf, count, distance, orientation, warmup, measure,
        clusterCount, clusterRadius, spinSeconds
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
local BENCH_CLUSTER_COUNT = 4
local BENCH_CLUSTER_RADIUS = 300.0
local BENCH_SPIN_SECONDS = 0.0

local units = {}
local opponents = {}
local moveTargets = {}
local playerHandle = nil
local playerOrigin = nil
local playerBasis = nil
local nextSpinAt = nil
local spinIndex = 0
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

-- Dispersed layout.
--
-- Clusters sit on a ring of BENCH_CLUSTER_RADIUS around the player, evenly
-- spaced in bearing and measured from the player's own front vector. Cluster 0
-- is straight ahead, so with four clusters at a 300 m radius one cluster is
-- inside the frustum and the other three are roughly 90, 180 and 270 degrees
-- off the sight line -- two lateral, one directly behind. Firing pairs inside
-- each cluster face each other along the radial direction, so impacts and the
-- generic chunklets they spawn stay local to their own cluster and the whole
-- debris field spans about two cluster radii.
local function clusterBasis(transform, clusterIndex)
    local frontX = transform.front_x or 0.0
    local frontZ = transform.front_z or 1.0
    local rightX = transform.right_x or 1.0
    local rightZ = transform.right_z or 0.0
    local angle = (clusterIndex % BENCH_CLUSTER_COUNT) *
        (2.0 * math.pi / BENCH_CLUSTER_COUNT)
    local c = math.cos(angle)
    local s = math.sin(angle)
    -- Radial: outward toward the cluster. Tangent: perpendicular to it.
    local radialX = frontX * c + rightX * s
    local radialZ = frontZ * c + rightZ * s
    local tangentX = -frontX * s + rightX * c
    local tangentZ = -frontZ * s + rightZ * c
    return radialX, radialZ, tangentX, tangentZ
end

local function dispersedPosition(playerPos, transform, index)
    local perCluster = math.max(2, math.floor(BENCH_COUNT / BENCH_CLUSTER_COUNT))
    local clusterIndex = math.floor(index / perCluster)
    if clusterIndex >= BENCH_CLUSTER_COUNT then
        clusterIndex = BENCH_CLUSTER_COUNT - 1
    end
    local local_index = index - clusterIndex * perCluster
    local radialX, radialZ, tangentX, tangentZ =
        clusterBasis(transform, clusterIndex)

    -- Pairs straddle the cluster centre along the radial axis so they shoot
    -- each other; ranks spread along the tangent so the cluster has area.
    local rank = math.floor(local_index / 2)
    local lateral = (rank - 2) * 9.0
    local radialOffset = (local_index % 2 == 0) and -20.0 or 20.0

    local centreX = playerPos.x + radialX * BENCH_CLUSTER_RADIUS
    local centreZ = playerPos.z + radialZ * BENCH_CLUSTER_RADIUS
    return SetVector(
        centreX + radialX * radialOffset + tangentX * lateral,
        playerPos.y,
        centreZ + radialZ * radialOffset + tangentZ * lateral)
end

local function faceCluster(clusterIndex)
    if not playerHandle or not IsValid(playerHandle) then
        return false
    end
    if not playerOrigin or not playerBasis then
        return false
    end
    local radialX, radialZ = clusterBasis(playerBasis, clusterIndex)
    local heading = SetVector(radialX, 0.0, radialZ)
    local matrix = BuildDirectionalMatrix(playerOrigin, heading)
    SetTransform(playerHandle, matrix)
    trace(string.format(
        "spin cluster=%d heading=(%.3f,0,%.3f)",
        clusterIndex % BENCH_CLUSTER_COUNT, radialX, radialZ))
    return true
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
        BENCH_SCENARIO == "combat" or
        BENCH_SCENARIO == "dispersed"

    for index = 0, BENCH_COUNT - 1 do
        local side = 0
        -- The AI-idle phase shares the player's team so it exercises native AI
        -- scheduling without accidentally turning the player into an enemy.
        local team = BENCH_SCENARIO == "ai_idle" and 1 or 2
        if splitTeams then
            side = index % 2 == 0 and -1 or 1
            team = side < 0 and 2 or 3
        end

        local position
        if BENCH_SCENARIO == "dispersed" then
            position = dispersedPosition(playerPos, transform, index)
        else
            position = formationPosition(playerPos, transform, index, side)
        end
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

    if BENCH_SCENARIO == "dispersed" then
        -- Pair consecutive spawn indices. Within a cluster those two units sit
        -- 40 m apart on the radial axis facing each other, so every impact and
        -- every chunklet it spawns belongs to that cluster and nothing fires
        -- across the several hundred metres between clusters.
        for index = 1, #units, 2 do
            local a = units[index]
            local b = units[index + 1]
            if a and b then
                opponents[a] = b
                opponents[b] = a
            end
        end
    elseif splitTeams then
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
        BENCH_MEASURE_SECONDS, BENCH_CLUSTER_COUNT, BENCH_CLUSTER_RADIUS,
        BENCH_SPIN_SECONDS = readConfig()
    trace("start")
    local player = GetPlayerHandle()
    if not IsValid(player) then
        trace("ERROR player-handle-unavailable")
        benchmarkEnded = true
        return
    end

    SetIndependence(player, 0)
    Stop(player, 1)
    playerHandle = player
    playerOrigin = GetPosition(player)
    playerBasis = GetTransform(player)
    removeUnexpectedCraft(player)
    spawnUnits(player)
    beginWorkload()
    if BENCH_SCENARIO == "dispersed" then
        trace(string.format(
            "dispersed clusters=%d radius=%.1f spin=%.1f",
            BENCH_CLUSTER_COUNT, BENCH_CLUSTER_RADIUS, BENCH_SPIN_SECONDS))
        if BENCH_SPIN_SECONDS > 0.0 then
            -- First rotation lands inside the measurement window rather than
            -- during warmup, so every capture contains at least one transition.
            nextSpinAt = BENCH_WARMUP_SECONDS + BENCH_SPIN_SECONDS
        end
    end
    trace("warmup-begin")
end

function Update(dt)
    elapsed = elapsed + (dt or 0.0)

    if BENCH_SCENARIO == "firing" or BENCH_SCENARIO == "flight" or
       BENCH_SCENARIO == "dispersed" then
        maintainFiringWorkload()
    end

    -- Deterministic camera rotation between clusters. Each spin re-points the
    -- player craft at the next cluster on the ring, which is what moves debris
    -- clusters in and out of the frustum without any synthetic input.
    if BENCH_SCENARIO == "dispersed" and BENCH_SPIN_SECONDS > 0.0 and
       nextSpinAt and elapsed >= nextSpinAt then
        spinIndex = spinIndex + 1
        faceCluster(spinIndex)
        nextSpinAt = elapsed + BENCH_SPIN_SECONDS
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
