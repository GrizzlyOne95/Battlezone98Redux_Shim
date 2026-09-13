-- lcbench Constructor double-recycle qualification overlay.
--
-- Two Constructors are placed at equal range from one building and both are
-- ordered to recycle it. One of them wins the race and removes the building;
-- the report under test is that the loser is left permanently deployed.
--
-- Every arm is a variation on that race, with two controls that must stay
-- clean so a "stuck deployed" reading cannot simply mean "Constructors always
-- finish deployed".
--
--   same  two rigs, one building, both orders on the same frame
--   stag  two rigs, one building, the second order issued later
--   solo  CONTROL: one rig, one building
--   pair  CONTROL: two rigs, one building each
--
-- After the building dies the fixture waits, then pokes each surviving rig
-- with a Goto. A rig that neither undeploys nor moves is wedged, not idle.

local TEAM = 1

local ARMS = {
    same = { rigs = 2, buildings = 1, stagger = 0.0,
             label = "two rigs / one building / simultaneous orders" },
    stag = { rigs = 2, buildings = 1, stagger = 4.0,
             label = "two rigs / one building / second order 4s late" },
    solo = { rigs = 1, buildings = 1, stagger = 0.0,
             label = "CONTROL: one rig / one building" },
    pair = { rigs = 2, buildings = 2, stagger = 0.0,
             label = "CONTROL: two rigs / one building each" },
}

local elapsed = 0.0
local nextPoll = 0.0
local stage = 0

local selectedCase = "same"
local fixtureCommit = "unknown"
local rigOdf = "avcnst"
local buildingOdf = "abcomm"
local arm = nil

local player = nil
local rigs = {}
local buildings = {}
local orderIssued = {}
local targetOf = {}

local firstDeathAt = -1.0
local pokeAt = -1.0
local pokePos = {}
local resultAt = -1.0

local POKE_DELAY = 10.0   -- seconds after the last building dies
local POKE_WINDOW = 12.0  -- seconds allowed for a poked rig to react
local HARD_CAP = 110.0    -- absolute ceiling regardless of what happens

local function Place(range, lateral)
    local transform = GetTransform(player)
    local origin = GetPosition(player)
    local frontX = transform.front_x or 0.0
    local frontZ = transform.front_z or 1.0
    local rightX = transform.right_x or 1.0
    local rightZ = transform.right_z or 0.0
    return SetVector(
        origin.x + frontX * range + rightX * lateral,
        origin.y,
        origin.z + frontZ * range + rightZ * lateral)
end

local function Live(h)
    return h ~= nil and IsValid(h)
end

local function Dist(a, b)
    if not Live(a) or not Live(b) then return -1.0 end
    local pa = GetPosition(a)
    local pb = GetPosition(b)
    local dx = pa.x - pb.x
    local dz = pa.z - pb.z
    return math.sqrt(dx * dx + dz * dz)
end

local function DistPos(h, p)
    if not Live(h) or p == nil then return -1.0 end
    local ph = GetPosition(h)
    local dx = ph.x - p.x
    local dz = ph.z - p.z
    return math.sqrt(dx * dx + dz * dz)
end

local function RigText(i)
    local h = rigs[i]
    if not Live(h) then
        return string.format("rig%d{v=false}", i)
    end
    return string.format(
        "rig%d{v=true dep=%s cmd=%s who=%s busy=%s hp=%.3f dTgt=%.2f dPoke=%.2f}",
        i,
        tostring(IsDeployed(h)),
        tostring(GetCurrentCommand(h)),
        tostring(GetCurrentWho(h)),
        tostring(IsBusy(h)),
        GetHealth(h),
        Dist(h, buildings[targetOf[i]]),
        DistPos(h, pokePos[i]))
end

local function BldText(i)
    return string.format("bld%d{v=%s}", i, tostring(Live(buildings[i])))
end

local function Snapshot(label)
    local parts = {}
    local i
    for i = 1, arm.rigs do parts[#parts + 1] = RigText(i) end
    for i = 1, arm.buildings do parts[#parts + 1] = BldText(i) end
    print(string.format("[LCROAD][RCYC] T+%.3f %s %s",
        elapsed, label, table.concat(parts, " ")))
end

local function IssueRecycle(i)
    local rig = rigs[i]
    local target = buildings[targetOf[i]]
    if not Live(rig) or not Live(target) then
        print(string.format("[LCROAD][RCYC] T+%.3f ISSUE-SKIP rig=%d rigLive=%s tgtLive=%s",
            elapsed, i, tostring(Live(rig)), tostring(Live(target))))
        return
    end
    print(string.format("[LCROAD][RCYC] T+%.3f ISSUE rig=%d target=bld%d handle=%s",
        elapsed, i, targetOf[i], tostring(target)))
    SetCommand(rig, AiCommand.RECYCLE, 1, target)
    orderIssued[i] = true
end

function Start()
    elapsed = 0.0
    nextPoll = 0.0
    stage = 0

    local config = OpenODF("rmrcfg")
    selectedCase = GetODFString(config, "Roadmap", "case", "same")
    fixtureCommit = GetODFString(config, "Roadmap", "commit", "unknown")
    rigOdf = GetODFString(config, "Roadmap", "rig", "avcnst")
    buildingOdf = GetODFString(config, "Roadmap", "building", "abcomm")

    arm = ARMS[selectedCase]
    if arm == nil then
        selectedCase = "same"
        arm = ARMS.same
    end

    player = GetPlayerHandle()
    print(string.format(
        "[LCROAD][RCYC] START case=%s label=%q commit=%s rigOdf=%s bldOdf=%s rigs=%d buildings=%d stagger=%.1f",
        selectedCase, arm.label, tostring(fixtureCommit),
        rigOdf, buildingOdf, arm.rigs, arm.buildings, arm.stagger))

    -- Buildings sit on the player's front axis, spaced apart so two rigs on
    -- the two-building control never contend for the same structure.
    local i
    for i = 1, arm.buildings do
        local lateral = 0.0
        if arm.buildings > 1 then lateral = (i - 1.5) * 120.0 end
        buildings[i] = BuildObject(buildingOdf, TEAM, Place(90.0, lateral))
    end

    -- Rigs are placed at mirrored lateral offsets from their target, so both
    -- travel the same distance and start unbuilding within a frame or two of
    -- each other. That equal start is the whole point of the "same" arm.
    for i = 1, arm.rigs do
        if arm.buildings > 1 then
            targetOf[i] = i
        else
            targetOf[i] = 1
        end
        local base = 0.0
        if arm.buildings > 1 then base = (targetOf[i] - 1.5) * 120.0 end
        local side = 30.0
        if i % 2 == 1 then side = -30.0 end
        if arm.buildings > 1 then side = -30.0 end
        rigs[i] = BuildObject(rigOdf, TEAM, Place(90.0, base + side))
        orderIssued[i] = false
        if Live(rigs[i]) then
            SetIndependence(rigs[i], 0)
            Stop(rigs[i], 1)
        end
    end

    Snapshot("SPAWNED")
end

function Update(dt)
    elapsed = elapsed + (dt or 0.0)

    -- stage 0: settle, then issue the first order(s)
    if stage == 0 and elapsed >= 3.0 then
        IssueRecycle(1)
        if arm.rigs > 1 and arm.stagger <= 0.0 then
            IssueRecycle(2)
        end
        Snapshot("ISSUED")
        nextPoll = elapsed + 0.5
        stage = 1
    end

    -- staggered second order
    if stage == 1 and arm.rigs > 1 and arm.stagger > 0.0
       and not orderIssued[2] and elapsed >= 3.0 + arm.stagger then
        IssueRecycle(2)
        Snapshot("ISSUED2")
    end

    if stage >= 1 and stage <= 2 and elapsed >= nextPoll then
        Snapshot("POLL")
        nextPoll = nextPoll + 0.5
    end

    -- detect the moment every target building is gone
    if stage == 1 then
        local allDown = true
        local i
        for i = 1, arm.buildings do
            if Live(buildings[i]) then allDown = false end
        end
        if allDown then
            firstDeathAt = elapsed
            pokeAt = elapsed + POKE_DELAY
            resultAt = pokeAt + POKE_WINDOW
            Snapshot("TARGETDOWN")
            print(string.format("[LCROAD][RCYC] T+%.3f TARGETDOWN pokeAt=%.3f",
                elapsed, pokeAt))
            stage = 2
        elseif elapsed >= HARD_CAP - 20.0 then
            -- nothing ever got recycled; report it rather than timing out mute
            firstDeathAt = -1.0
            pokeAt = elapsed
            resultAt = elapsed + POKE_WINDOW
            Snapshot("NOTARGETDOWN")
            stage = 2
        end
    end

    -- poke: a rig that is merely idle-deployed will undeploy and drive away
    if stage == 2 and elapsed >= pokeAt then
        local i
        for i = 1, arm.rigs do
            if Live(rigs[i]) then
                pokePos[i] = GetPosition(rigs[i])
                print(string.format("[LCROAD][RCYC] T+%.3f POKE rig=%d dep=%s cmd=%s",
                    elapsed, i, tostring(IsDeployed(rigs[i])),
                    tostring(GetCurrentCommand(rigs[i]))))
                Goto(rigs[i], Place(30.0, (i - 1.5) * 40.0), 1)
            end
        end
        Snapshot("POKED")
        stage = 3
        nextPoll = elapsed + 0.5
    end

    if stage == 3 and elapsed >= nextPoll then
        Snapshot("POLL")
        nextPoll = nextPoll + 0.5
    end

    if stage == 3 and (elapsed >= resultAt or elapsed >= HARD_CAP) then
        Snapshot("RESULT")
        local stuck = 0
        local moved = 0
        local deployed = 0
        local i
        for i = 1, arm.rigs do
            if Live(rigs[i]) then
                local isDep = IsDeployed(rigs[i])
                local travelled = DistPos(rigs[i], pokePos[i])
                if isDep then deployed = deployed + 1 end
                if travelled > 5.0 then moved = moved + 1 end
                -- wedged: still deployed and it ignored the Goto entirely
                if isDep and travelled >= 0.0 and travelled <= 5.0 then
                    stuck = stuck + 1
                end
                print(string.format(
                    "[LCROAD][RCYC] T+%.3f RIGRESULT rig=%d dep=%s cmd=%s travelled=%.2f",
                    elapsed, i, tostring(isDep),
                    tostring(GetCurrentCommand(rigs[i])), travelled))
            else
                print(string.format("[LCROAD][RCYC] T+%.3f RIGRESULT rig=%d GONE",
                    elapsed, i))
            end
        end
        print(string.format(
            "[LCROAD][RCYC] T+%.3f COMPLETE case=%s rigs=%d deployed=%d moved=%d stuck=%d targetDownAt=%.3f",
            elapsed, selectedCase, arm.rigs, deployed, moved, stuck, firstDeathAt))
        FailMission(GetTime() + 1.0)
        stage = 4
    end
end

function CreateObject(h) end
function AddObject(h) end
function DeleteObject(h) end
function CreatePlayer(id, name, team) end
function AddPlayer(id, name, team) end
function DeletePlayer(id, name, team) end
