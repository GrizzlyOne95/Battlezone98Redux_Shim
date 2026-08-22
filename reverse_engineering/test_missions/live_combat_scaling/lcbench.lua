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
    satellite = true,
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

-- Satellite (view 3) visibility fixture. Separate from the benchmark
-- scenarios: it spawns one group per case the OpenShim satellite visibility
-- fix has to get right, keeps every group on its own team so the shim's
-- [SATVISCHK] capture can score them apart, and drives the whole timeline off
-- one clock so the PowerShell runner can trigger view changes from log cues
-- rather than guessing at wall time.
--
--   friendly    team 1, near   -> illuminated, visible in satellite
--   detected    team 6, near   -> illuminated, visible in satellite
--   undetected  team 7, far    -> not illuminated, hidden in satellite
--   preHide     team 8, near   -> illuminated but its Ogre entity was hidden
--                                 before satellite; must stay hidden
--   reveal      team 9, far    -> starts hidden, teleported next to the player
--                                 mid-view so it must turn visible without
--                                 leaving view 3
--
-- Two further lifecycle cases are driven inside the view: one unit is created
-- while satellite is open and one is destroyed while it is open.
local SAT_DEFAULT_TEAMS = {
    friendly = 1,
    detected = 6,
    undetected = 7,
    preHide = 8,
    reveal = 9,
}

-- Cue times in seconds from Start(). The gaps are deliberate: detection has to
-- settle before the first entry, and each transition needs at least two
-- [SATVISCHK] samples (one per second) to be scoreable.
local SAT_DEFAULT_SCHEDULE = {
    { at = 6.0,  cue = "enter-satellite" },
    { at = 12.0, cue = "reveal" },
    { at = 15.0, cue = "spawn-in-satellite" },
    { at = 17.0, cue = "remove-in-satellite" },
    { at = 20.0, cue = "exit-satellite" },
    { at = 25.0, cue = "enter-satellite-2" },
    { at = 31.0, cue = "exit-satellite-2" },
    { at = 35.0, cue = "done" },
}

-- OpenODF is only safe after LuaMission startup has entered Start(). Keep
-- inert defaults during module loading, then replace them from lcbcfg.odf.
local BENCH_SCENARIO = "idle"
local BENCH_UNIT_ODF = "avtank"
local BENCH_COUNT = 20
local BENCH_DISTANCE = 50.0
local BENCH_ORIENTATION = "facing"
local BENCH_WARMUP_SECONDS = 4.0
local BENCH_MEASURE_SECONDS = 8.0

local SAT_TEAMS = {}
local SAT_GROUP_COUNT = 3
local SAT_NEAR_DISTANCE = 60.0
local SAT_FAR_DISTANCE = 1400.0
local SAT_RECYCLER_ODF = "avrecy"

local units = {}
local opponents = {}
local moveTargets = {}
local elapsed = 0.0
local measurementStarted = false
local benchmarkEnded = false

local satGroups = {}
local satNextCue = 1
local satPlayer = nil

local function readSatelliteConfig()
    local config = OpenODF("lcbcfg")

    local function team(key, fallback)
        local value = GetODFInt(config, "Satellite", key, fallback)
        value = math.floor(value or fallback)
        -- Team 0 is neutral and teams above 15 do not exist; either would make
        -- the [SATVISCHK] rows unreadable, so refuse a malformed edit rather
        -- than silently scoring the wrong group.
        if value < 1 or value > 15 then
            value = fallback
        end
        return value
    end

    SAT_TEAMS = {
        friendly = team("friendlyTeam", SAT_DEFAULT_TEAMS.friendly),
        detected = team("detectedTeam", SAT_DEFAULT_TEAMS.detected),
        undetected = team("undetectedTeam", SAT_DEFAULT_TEAMS.undetected),
        preHide = team("preHideTeam", SAT_DEFAULT_TEAMS.preHide),
        reveal = team("revealTeam", SAT_DEFAULT_TEAMS.reveal),
    }

    SAT_GROUP_COUNT = math.max(
        1, math.min(20, math.floor(GetODFInt(config, "Satellite", "groupCount", 3) or 3)))
    SAT_NEAR_DISTANCE = math.max(
        20.0, math.min(400.0, GetODFFloat(config, "Satellite", "nearDistance", 60.0) or 60.0))
    SAT_FAR_DISTANCE = math.max(
        SAT_NEAR_DISTANCE + 200.0,
        math.min(4000.0, GetODFFloat(config, "Satellite", "farDistance", 1400.0) or 1400.0))

    -- Which recycler enables the satellite depends on the player's race, so it
    -- stays configurable rather than hard-coded to the NSDF one.
    SAT_RECYCLER_ODF = GetODFString(config, "Satellite", "recyclerOdf", "avrecy")
    if type(SAT_RECYCLER_ODF) ~= "string" or SAT_RECYCLER_ODF == "" then
        SAT_RECYCLER_ODF = "avrecy"
    end
end

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

local function satTrace(message)
    print(string.format("[SATBENCH] t=%.3f %s", elapsed, message))
end

-- Places a group along the player's sight line at the requested range, spread
-- laterally so nothing spawns inside anything else.
local function satPlace(transform, playerPos, range, index)
    local lateral = (index - (SAT_GROUP_COUNT - 1) * 0.5) * 12.0
    local frontX = transform.front_x or 0.0
    local frontZ = transform.front_z or 1.0
    local rightX = transform.right_x or 1.0
    local rightZ = transform.right_z or 0.0
    return SetVector(
        playerPos.x + frontX * range + rightX * lateral,
        playerPos.y,
        playerPos.z + frontZ * range + rightZ * lateral)
end

local function satSpawnGroup(name, teamNum, range)
    local transform = GetTransform(satPlayer)
    local playerPos = GetPosition(satPlayer)
    local group = { team = teamNum, range = range, handles = {} }

    for index = 0, SAT_GROUP_COUNT - 1 do
        local handle = BuildObject(
            BENCH_UNIT_ODF, teamNum, satPlace(transform, playerPos, range, index))
        if IsValid(handle) then
            -- Independence 0 plus an explicit Stop keeps every group inert, so
            -- the only thing that changes across the run is what the fixture
            -- changes on purpose.
            SetIndependence(handle, 0)
            Stop(handle, 1)
            group.handles[#group.handles + 1] = handle
        end
    end

    satGroups[name] = group
    satTrace(string.format(
        "group=%s team=%d range=%.1f spawned=%d",
        name, teamNum, range, #group.handles))
end

local function satSpawnFixture()
    -- The satellite view is not a free camera: Apply_Satellite_View refuses
    -- unless ControlPanel_SatelliteEnabled(), which in normal play means the
    -- player's team owns a recycler. lcbench.bzn contains only the player, so
    -- without this the view key does nothing and the whole fixture measures
    -- first person.
    local transform = GetTransform(satPlayer)
    local playerPos = GetPosition(satPlayer)
    local recycler = BuildObject(
        SAT_RECYCLER_ODF, SAT_TEAMS.friendly,
        satPlace(transform, playerPos, SAT_NEAR_DISTANCE + 120.0, 0))
    if IsValid(recycler) then
        satGroups.recycler = { team = SAT_TEAMS.friendly, range = 0, handles = { recycler } }
        satTrace(string.format("recycler=%s team=%d", SAT_RECYCLER_ODF, SAT_TEAMS.friendly))
    else
        satTrace(string.format("ERROR recycler-build-failed odf=%s", SAT_RECYCLER_ODF))
    end

    satSpawnGroup("friendly", SAT_TEAMS.friendly, SAT_NEAR_DISTANCE)
    satSpawnGroup("detected", SAT_TEAMS.detected, SAT_NEAR_DISTANCE)
    satSpawnGroup("undetected", SAT_TEAMS.undetected, SAT_FAR_DISTANCE)
    -- Near, so its illumination is above zero and the only reason it can stay
    -- hidden in satellite is that its Ogre entity was hidden beforehand.
    satSpawnGroup("preHide", SAT_TEAMS.preHide, SAT_NEAR_DISTANCE)
    satSpawnGroup("reveal", SAT_TEAMS.reveal, SAT_FAR_DISTANCE)
end

local function satReveal()
    local group = satGroups.reveal
    if not group then
        satTrace("cue=reveal ERROR group-missing")
        return
    end
    local transform = GetTransform(satPlayer)
    local playerPos = GetPosition(satPlayer)
    local moved = 0
    for index, handle in ipairs(group.handles) do
        if IsValid(handle) then
            SetPosition(handle, satPlace(
                transform, playerPos, SAT_NEAR_DISTANCE, index - 1))
            moved = moved + 1
        end
    end
    satTrace(string.format("cue=reveal team=%d moved=%d", group.team, moved))
end

local function satSpawnInView()
    -- "Object created while already in satellite." Uses the detected team so
    -- its expected outcome (illuminated, therefore visible) is unambiguous.
    local transform = GetTransform(satPlayer)
    local playerPos = GetPosition(satPlayer)
    local handle = BuildObject(
        BENCH_UNIT_ODF, SAT_TEAMS.detected,
        satPlace(transform, playerPos, SAT_NEAR_DISTANCE, SAT_GROUP_COUNT + 1))
    if IsValid(handle) then
        SetIndependence(handle, 0)
        Stop(handle, 1)
        local group = satGroups.detected
        group.handles[#group.handles + 1] = handle
        satTrace(string.format(
            "cue=spawn-in-satellite team=%d total=%d",
            SAT_TEAMS.detected, #group.handles))
    else
        satTrace("cue=spawn-in-satellite ERROR build-failed")
    end
end

local function satRemoveInView()
    -- "Object destroyed while satellite is active." Taken from the undetected
    -- group, which is the one the fix is actively holding hidden, so the
    -- removal exercises the tracked-entry sweep rather than an untouched entry.
    local group = satGroups.undetected
    if not group then
        satTrace("cue=remove-in-satellite ERROR group-missing")
        return
    end
    for index = #group.handles, 1, -1 do
        local handle = group.handles[index]
        if IsValid(handle) then
            RemoveObject(handle)
            table.remove(group.handles, index)
            satTrace(string.format(
                "cue=remove-in-satellite team=%d remaining=%d",
                group.team, #group.handles))
            return
        end
        table.remove(group.handles, index)
    end
    satTrace("cue=remove-in-satellite ERROR nothing-live")
end

-- The runner watches for these cue lines and sends the matching view key, so
-- the view change is always ordered after the world change it is meant to
-- observe.
local function satRunCue(cue)
    if cue == "reveal" then
        satReveal()
    elseif cue == "spawn-in-satellite" then
        satSpawnInView()
    elseif cue == "remove-in-satellite" then
        satRemoveInView()
    elseif cue == "done" then
        satTrace("cue=done benchmark-end")
        benchmarkEnded = true
    else
        satTrace(string.format("cue=%s", cue))
    end
end

-- The hostile groups sit inside weapon range of the player and of each other,
-- and SetIndependence(0) does not reliably stop them engaging. Losses would
-- move units between the [SATVISCHK] rows mid-run and make the scoring
-- ambiguous, so hold every fixture unit at full health. Nothing here changes
-- illumination, visibility, or team.
local function satMaintainPopulation()
    for _, group in pairs(satGroups) do
        for _, handle in ipairs(group.handles) do
            if IsValid(handle) then
                SetCurHealth(handle, GetMaxHealth(handle))
            end
        end
    end
end

local function satUpdate()
    satMaintainPopulation()

    while satNextCue <= #SAT_DEFAULT_SCHEDULE do
        local entry = SAT_DEFAULT_SCHEDULE[satNextCue]
        if elapsed < entry.at then
            return
        end
        satNextCue = satNextCue + 1
        satRunCue(entry.cue)
    end
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

    if BENCH_SCENARIO == "satellite" then
        satPlayer = player
        readSatelliteConfig()
        satTrace(string.format(
            "start odf=%s groupCount=%d near=%.1f far=%.1f " ..
            "friendly=%d detected=%d undetected=%d preHide=%d reveal=%d",
            BENCH_UNIT_ODF, SAT_GROUP_COUNT, SAT_NEAR_DISTANCE, SAT_FAR_DISTANCE,
            SAT_TEAMS.friendly, SAT_TEAMS.detected, SAT_TEAMS.undetected,
            SAT_TEAMS.preHide, SAT_TEAMS.reveal))
        satSpawnFixture()
        satTrace("fixture-ready")
        return
    end

    spawnUnits(player)
    beginWorkload()
    trace("warmup-begin")
end

function Update(dt)
    elapsed = elapsed + (dt or 0.0)

    if BENCH_SCENARIO == "satellite" then
        if not benchmarkEnded then
            satUpdate()
        end
        return
    end

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
