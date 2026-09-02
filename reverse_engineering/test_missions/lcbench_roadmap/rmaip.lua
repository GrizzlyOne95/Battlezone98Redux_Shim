-- lcbench AIP mixed stock/custom producer qualification overlay.
--
-- Each process runs one arm of the producer/unit-origin matrix. The arm
-- selects which producer ODFs are spawned for the AI team and which .aip is
-- installed; everything else is held constant. Scrap is force-fed every poll
-- so that a missing build can never be explained by budget.
--
-- "svfigh" is the stock unit. "mxfigh" is a value-identical clone of it that
-- differs only in ODF identity, so a preference for one over the other cannot
-- be explained by cost, build time, health, or role.

local AI_TEAM = 2

-- Strategic AI is startup-only configuration and must be set during root
-- initialization. The engine sets strategic AI up shortly after this chunk
-- runs, so calling it later (from Start) is too late to start the AI and can
-- crash the game.
SetAIControl(AI_TEAM, true)

-- arm -> { producers, label }
local ARMS = {
    sps  = { producers = {"svrecy"},          label = "stock producer / stock unit only" },
    spc  = { producers = {"svrecy"},          label = "stock producer / custom unit only" },
    spms = { producers = {"svrecy"},          label = "stock producer / mixed, stock first" },
    spmc = { producers = {"svrecy"},          label = "stock producer / mixed, custom first" },
    cps  = { producers = {"mxrecy"},          label = "custom producer / stock unit only" },
    cpc  = { producers = {"mxrecy"},          label = "custom producer / custom unit only" },
    cpms = { producers = {"mxrecy"},          label = "custom producer / mixed, stock first" },
    cpmc = { producers = {"mxrecy"},          label = "custom producer / mixed, custom first" },
    mp2  = { producers = {"svrecy", "mxrecy"}, label = "two producers / mixed, stock first" },
    ss2  = { producers = {"svrecy"},          label = "CONTROL: two STOCK units in one account" },
    cc2  = { producers = {"svrecy"},          label = "CONTROL: two CUSTOM units in one account" },
    ccak = { producers = {"svrecy"},           label = "CONTROL: shipped ccatank.aip verbatim" },
}

local elapsed = 0.0
local nextPoll = 0.0
local stage = 0
local selectedCase = "cpms"
local fixtureCommit = "unknown"
local arm = nil

local player = nil
local recycler = nil
local producers = {}
local tracked = {}
local seen = {}
local buildEvents = 0

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
    return GetPositionNear(base, 4.0, 10.0)
end

local function ValidText(h)
    return tostring(h ~= nil and IsValid(h))
end

-- Count only AI-team units of the two units under test. Anything else the
-- scheduler decides to build is reported separately as "other" rather than
-- being silently folded into either bucket.
-- Counted by IsOdf rather than by comparing GetOdf strings: GetOdf can return
-- hidden trailing null bytes, which silently breaks equality tests.
local TRACKED_ODFS = { "svfigh", "mxfigh", "svturr", "mxturr", "svscav", "svcnst" }

local function Census()
    local counts = { other = 0 }
    local i, j
    for i = 1, #TRACKED_ODFS do
        counts[TRACKED_ODFS[i]] = 0
    end
    for i = 1, #tracked do
        local h = tracked[i]
        if h ~= nil and IsValid(h) and GetTeamNum(h) == AI_TEAM then
            local matched = false
            for j = 1, #TRACKED_ODFS do
                if IsOdf(h, TRACKED_ODFS[j]) then
                    counts[TRACKED_ODFS[j]] = counts[TRACKED_ODFS[j]] + 1
                    matched = true
                    break
                end
            end
            if not matched then
                counts.other = counts.other + 1
            end
        end
    end
    return counts
end

-- stock=/custom= stay pinned to svfigh/mxfigh so existing parsing keeps
-- working; the same-origin pair arms are read from svturr=/mxturr=.
local function CountsText(c)
    return string.format(
        "stock=%d custom=%d svturr=%d mxturr=%d svscav=%d svcnst=%d other=%d",
        c.svfigh, c.mxfigh, c.svturr, c.mxturr, c.svscav, c.svcnst, c.other)
end

-- Hold the AI's budget open. Both caps must be raised first: SetScrap and
-- SetPilot are clamped to the team maximum, which is why an unraised cap
-- silently pins scrap at 40 and starves production of pilots.
local function Supply()
    SetMaxScrap(AI_TEAM, 400)
    SetScrap(AI_TEAM, 400)
    SetMaxPilot(AI_TEAM, 50)
    SetPilot(AI_TEAM, 50)
end

local function DeployedText(h)
    if h == nil or not IsValid(h) then
        return "invalid"
    end
    return tostring(IsDeployed(h))
end

-- A recycler is a mobile deployable building. BuildObject spawns it
-- undeployed, and an undeployed producer cannot run a construction program,
-- so deployment is re-asserted until it takes.
-- Deploy takes timeDeploy (5s) to complete. Re-issuing it every frame
-- restarts that animation and it never finishes, so retries are throttled
-- well clear of the deploy time.
local nextDeployAttempt = 0.0
local nextSupply = 0.0

local function EnsureDeployed()
    if elapsed < nextDeployAttempt then
        return
    end
    nextDeployAttempt = elapsed + 15.0
    local i
    for i = 1, #producers do
        local h = producers[i]
        if h ~= nil and IsValid(h) and not IsDeployed(h) then
            Deploy(h)
            print(string.format("[LCROAD][AIP] DEPLOY issued T+%.3f slot=%d", elapsed, i))
        end
    end
end

local function Snapshot(label)
    local counts = Census()
    local factory = GetFactoryHandle(AI_TEAM)
    local prodDep = "none"
    if #producers >= 1 then
        prodDep = DeployedText(producers[1])
        if #producers >= 2 then
            prodDep = prodDep .. "/" .. DeployedText(producers[2])
        end
    end
    print(string.format(
        "[LCROAD][AIP] T+%.3f %s case=%s %s " ..
        "events=%d scrap=%d pilots=%d recycler=%s factory=%s recyDep=%s prodDep=%s",
        elapsed, label, tostring(selectedCase),
        CountsText(counts), buildEvents,
        GetScrap(AI_TEAM), GetPilot(AI_TEAM),
        ValidText(recycler), ValidText(factory),
        DeployedText(recycler), prodDep))
end

function Start()
    elapsed = 0.0
    nextPoll = 0.0
    stage = 0
    tracked = {}
    seen = {}
    buildEvents = 0

    local config = OpenODF("rmacfg")
    selectedCase = GetODFString(config, "Roadmap", "case", "cpms")
    fixtureCommit = GetODFString(config, "Roadmap", "commit", "unknown")
    arm = ARMS[selectedCase]
    if arm == nil then
        arm = ARMS.cpms
    end

    player = GetPlayerHandle()
    print(string.format(
        "[LCROAD][AIP] START build=2.2.301 case=%s commit=%s arm=%s player=%s",
        tostring(selectedCase), tostring(fixtureCommit),
        tostring(arm.label), tostring(player)))

    -- The producer under test IS the team recycler. Both the recycler and the
    -- munitions factory refuse to deploy anywhere except on a geyser, and an
    -- undeployed producer never runs a construction program. This map ships
    -- no geysers, so each producer is given one and spawned directly on it.
    local found = {}
    local h
    for h in ObjectsInRange(500.0, player) do
        if GetClassLabel(h) == "geyser" then
            table.insert(found, h)
        end
    end
    print(string.format("[LCROAD][AIP] GEYSERS onMap=%d needed=%d",
        #found, #arm.producers))

    local i
    for i = 1, #arm.producers do
        local odfName = arm.producers[i]
        local site = found[i]
        local origin = "map"
        if site == nil then
            site = BuildObject("eggeizr1", 0, Place(180.0, -60.0 + (i * 60.0)))
            origin = "created"
        end
        print(string.format(
            "[LCROAD][AIP] GEYSER slot=%d origin=%s valid=%s class=%s",
            i, origin, ValidText(site),
            tostring(site ~= nil and IsValid(site) and GetClassLabel(site))))

        local p = BuildObject(odfName, AI_TEAM, GetPosition(site))
        producers[i] = p
        print(string.format(
            "[LCROAD][AIP] PRODUCER slot=%d odf=%s handle=%s valid=%s dist=%.2f",
            i, odfName, tostring(p), ValidText(p),
            (p ~= nil and IsValid(p)) and GetDistance(p, site) or -1.0))
    end
    recycler = producers[1]

    Supply()
    EnsureDeployed()
    SetAIP(selectedCase .. ".aip", AI_TEAM)
    print(string.format("[LCROAD][AIP] AIP INSTALLED file=%s.aip team=%d aiControl=%s",
        tostring(selectedCase), AI_TEAM, tostring(GetAIControl(AI_TEAM))))
    Snapshot("SPAWNED")
end

function Update(dt)
    elapsed = elapsed + (dt or 0.0)

    -- Hold the budget open so a missing build is never a scrap or pilot
    -- shortage. Throttled: nothing here may run every frame, because
    -- re-issuing engine calls at frame rate stalls the affected unit.
    if elapsed >= nextSupply then
        nextSupply = elapsed + 2.0
        Supply()
    end
    if elapsed >= 1.0 then
        EnsureDeployed()
    end

    if stage == 0 and elapsed >= 1.0 then
        Snapshot("ARMED")
        nextPoll = elapsed + 2.0
        stage = 1
    end

    if stage == 1 and elapsed >= nextPoll then
        Snapshot("POLL")
        nextPoll = nextPoll + 2.0
    end

    if stage == 1 and elapsed >= 90.0 then
        local counts = Census()
        Snapshot("RESULT")
        print(string.format(
            "[LCROAD][AIP] T+%.3f COMPLETE case=%s %s events=%d",
            elapsed, tostring(selectedCase), CountsText(counts), buildEvents))
        FailMission(GetTime() + 1.0)
        stage = 2
    end
end

-- Production observer. Every object the engine creates after the AIP is
-- installed is recorded with its ODF identity and the time it appeared, so
-- the build ORDER is recoverable and not just the final tally.
local function Observe(h, source)
    if h == nil or not IsValid(h) then
        return
    end
    -- The engine fires BOTH CreateObject and AddObject for the same object,
    -- so without this every build is counted twice.
    if seen[h] then
        return
    end
    seen[h] = true
    table.insert(tracked, h)
    if GetTeamNum(h) == AI_TEAM and (IsOdf(h, "svfigh") or IsOdf(h, "mxfigh") or
                              IsOdf(h, "svturr") or IsOdf(h, "mxturr")) then
        buildEvents = buildEvents + 1
        print(string.format(
            "[LCROAD][AIP] BUILT T+%.3f n=%d odf=%s class=%s team=%d src=%s",
            elapsed, buildEvents, tostring(GetOdf(h)), tostring(GetClassLabel(h)),
            GetTeamNum(h), source))
    end
end

function CreateObject(h) Observe(h, "create") end
function AddObject(h) Observe(h, "add") end
function DeleteObject(h) end
function CreatePlayer(id, name, team) end
function AddPlayer(id, name, team) end
function DeletePlayer(id, name, team) end
