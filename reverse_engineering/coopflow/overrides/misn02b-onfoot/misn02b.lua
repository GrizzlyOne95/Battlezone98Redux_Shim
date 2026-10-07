-- tran05.lua
-- Converted from Tran05Mission.cpp

-- Compatibility for 1.5 vs Redux naming
SetLabel = SetLabel or SetLabel

-- EXU Initialization
local RequireFix = require("RequireFix")
RequireFix.Initialize({"campaignReimagined", "3686673790"})
local exu = require("exu")
-- MultST native Init runs before Start; preserve the authored recycler only.
if type(IsNetGame) == "function" and IsNetGame() then
    assert(exu.DisableStartingRecycler and exu.GetMyNetID,
        "misn02b co-op requires the bundled EXU multiplayer hooks")
    exu.DisableStartingRecycler()
end
aiCore = require("aiCore")
local DiffUtils = require("DiffUtils")
local subtit = require("ScriptSubtitles")
local PersistentConfig = require("PersistentConfig")
local autosave = require("AutoSave")
local PlayerPilotMode = require("PlayerPilotMode")
local TerrainClutter = require("TerrainClutter")
local CRCoop = require("CRCoop")
local LEADER_TEAM = 1
local ENEMY_TEAM = 6
local FRIENDLY_TEAM = 7
local M
local ApplyDifficultyObjectives

local LABEL_BSCAV = "misn02b_bscav"
local LABEL_BSCOUT = "misn02b_bscout"
local LABEL_SCAV2 = "misn02b_scav2"
local STOCK_PLAYER_START = { x = 3898.14, y = 108.9, z = 99443.6 }
local CLUTTER_PROFILE = {
    name = "CR_Misn02b_GrassPrototype",
    mesh = "crgrass.mesh",
    material = "CR/GrassPrototype",
    center = STOCK_PLAYER_START,
    radius = 45.0,
    -- Density is instances per square unit, so the count follows the area:
    -- pi * 45^2 = 6362 sq units. The prototype originally shipped 0.018 with
    -- maxInstances = 128, which is 115 blades at 7.4 units apart -- roughly a
    -- blade per tank length, which reads as bare ground rather than as grass,
    -- and no amount of raising the density could change that while the cap sat
    -- at 128. 0.35 gives 2227 blades at 1.69 units apart, which is ground
    -- cover. That is 8908 triangles batched by Ogre StaticGeometry into the
    -- four 64-unit regions below, so the frame cost is a rounding error; the
    -- one-off cost is the terrain sampling at mission load, which the
    -- build log reports as startupMs.
    density = 0.35,
    minScale = 0.80,
    maxScale = 1.40,
    slopeMin = 0.0,
    slopeMax = 22.0,
    heightMin = -500.0,
    heightMax = 5000.0,
    seed = 1001,
    maxInstances = 4096,
    exclusionCircles = {
        { center = STOCK_PLAYER_START, radius = 12.0 },
    },
    regionDimensions = { x = 64.0, y = 128.0, z = 64.0 },
    renderingDistance = 260.0,
    castShadows = false,
}
local RefreshHandlesAfterLoad
local PilotModeCanManageHandle

local difficulty = 2
local hardDifficultyObjective = { "hard_diff", "yellow", 8.0, "High Difficulty: Enemy presence intensified." }
local easyDifficultyObjective = { "easy_diff", "blue", 8.0, "Low Difficulty: Enemy presence reduced." }

-- Mission presentation transport. Only the campaign leader runs the mission
-- below; HUD/audio/removal/end calls are explicitly delivered to every peer.
-- E/A are an ordered, acknowledged event stream (eight small packets in flight,
-- retried every 0.2s). C is a replaceable camera snapshot. No tables go on wire.
-- These types do not collide with CRCoop's H/Q/K/P protocol. Join-in-progress
-- still requires a restart: native world reconstruction is not available here.
local unpackArgs = unpack or table.unpack
local native = {
    ClearObjectives = ClearObjectives, AddObjective = AddObjective,
    UpdateObjective = UpdateObjective, SetObjectiveOn = SetObjectiveOn,
    SetObjectiveOff = SetObjectiveOff, SetObjectiveName = SetObjectiveName,
    SetUserTarget = SetUserTarget, RemoveObject = RemoveObject,
    SucceedMission = SucceedMission, FailMission = FailMission,
    CameraReady = CameraReady, CameraPath = CameraPath,
    CameraFinish = CameraFinish, CameraCancelled = CameraCancelled,
    Play = subtit.Play, Queue = subtit.Queue, Stop = subtit.Stop,
}
local events, acknowledgements = {}, {}
local receivedEvent = 0
local nextEventSend, nextCameraSend = 0, 0
local cameraFrame, cameraGeneration, cameraSerial = nil, 0, 0
local remoteCameraSerial, localCameraGeneration = 0, 0
local cameraSkipped, localCameraActive = false, false
local remoteCamera

local function FromLeader(from)
    local player = CRCoop.GetPlayers()[from]
    return player and player.team == LEADER_TEAM
end

local function ApplyPresentation(op, ...)
    if op == "Resources" then
        local team, scrap, pilots = ...
        -- Each human owns their team resources. Do not mutate a remote team.
        if CRCoop.GetLocalTeam() == team then
            SetScrap(team, scrap)
            SetPilot(team, pilots)
        end
    elseif op == "Difficulty" then
        difficulty = ...
        M.coopDifficulty = difficulty
        ApplyDifficultyObjectives()
        if exu.SetDifficulty then exu.SetDifficulty(difficulty) end
    elseif op == "SucceedMission" or op == "FailMission" then
        local when, description = ...
        -- Only pop a camera this peer pushed: an empty stack raises the
        -- engine's "Camera Stack 0verfow" alert.
        if localCameraActive then native.CameraFinish() end
        cameraFrame = nil
        localCameraActive = false
        M.coopResult = true
        native[op](math.max(GetTime() + 0.5, when), description)
    else
        return native[op](...)
    end
end

local function Present(op, ...)
    if CRCoop.IsNetworkGame() then
        if not CRCoop.IsAuthority() then return end
        events[#events + 1] = { op = op, args = { ... }, n = select("#", ...), expires = GetTime() + 5 }
    end
    return ApplyPresentation(op, ...)
end

-- Lexical wrappers affect this mission only; shared modules retain stock APIs.
local function ClearObjectives(...) return Present("ClearObjectives", ...) end
local function AddObjective(...) return Present("AddObjective", ...) end
local function UpdateObjective(...) return Present("UpdateObjective", ...) end
local function SetObjectiveOn(...) return Present("SetObjectiveOn", ...) end
local function SetObjectiveOff(...) return Present("SetObjectiveOff", ...) end
local function SetObjectiveName(...) return Present("SetObjectiveName", ...) end
local function SetUserTarget(...) return Present("SetUserTarget", ...) end
local function RemoveObject(...) return Present("RemoveObject", ...) end
-- Preserve the real subtitle module for Update/Initialize and return values.
subtit = setmetatable({
    Play = function(...) return Present("Play", ...) end,
    Queue = function(...) return Present("Queue", ...) end,
    Stop = function(...) return Present("Stop", ...) end,
}, { __index = subtit })

local function EndMission(op, when, description)
    if M.coopResult or M.coopPendingResult then return end
    if CRCoop.IsNetworkGame() then
        -- Flush preceding narrative/cleanup before publishing the result. Keep
        -- five seconds for result retries before native AiMission shuts down.
        M.coopPendingResult = { op, when, description }
    else
        M.coopResult = true
        native[op](when, description)
    end
end
local function SucceedMission(...) return EndMission("SucceedMission", ...) end
local function FailMission(...) return EndMission("FailMission", ...) end

-- localCameraActive tracks whether this peer holds a pushed camera. A skip
-- pops it early, so the film's own CameraFinish must not pop again: an empty
-- stack raises "Camera Stack 0verfow" and aborts the rest of the chunk.
local function CameraReady()
    cameraGeneration = cameraGeneration + 1
    cameraSkipped = false
    if CRCoop.IsNetworkGame() and localCameraActive then native.CameraFinish() end
    localCameraActive = true
    return native.CameraReady()
end
local function CameraPath(path, height, speed, target)
    cameraFrame = { path, height, speed, target }
    if CRCoop.IsNetworkGame() and native.CameraCancelled() then
        cameraSkipped = true
        if localCameraActive then native.CameraFinish() end
        localCameraActive = false
    end
    -- Only the leader's result drives the film, as offline: a finished path
    -- moves on to the next shot. After a leader skip the film's own timers
    -- and audio gates take over.
    if not cameraSkipped then
        return native.CameraPath(path, height, speed, target)
    end
    return false
end
local function CameraCancelled()
    -- A player's skip releases only their own camera; never skips shared
    -- destruction, transport orders, or the success gate for everyone else.
    if CRCoop.IsNetworkGame() then return false end
    return native.CameraCancelled()
end
local function CameraFinish()
    cameraFrame = nil
    cameraSkipped = false
    local wasActive = localCameraActive
    localCameraActive = false
    if not CRCoop.IsNetworkGame() or wasActive then return native.CameraFinish() end
end

local function UpdateRemoteCamera()
    if not remoteCamera then return end
    local generation, path, height, speed, target = unpackArgs(remoteCamera)
    if path == "" or M.coopResult then
        if localCameraActive then native.CameraFinish() end
        localCameraActive = false
        return
    end
    if generation ~= localCameraGeneration then
        localCameraGeneration = generation
        cameraSkipped = false
    end
    if cameraSkipped or not IsValid(target) then return end
    if not localCameraActive then
        native.CameraReady()
        localCameraActive = true
    elseif native.CameraCancelled() then
        cameraSkipped = true
        localCameraActive = false
        native.CameraFinish()
        return
    end
    native.CameraPath(path, height, speed, target)
end

local function UpdatePresentationTransport()
    if not CRCoop.IsNetworkGame() then return end
    if not CRCoop.IsAuthority() then
        UpdateRemoteCamera()
        return
    end
    local now, allDelivered = GetTime(), true
    for id, player in pairs(CRCoop.GetPlayers()) do
        if CRCoop.IsHumanTeam(player.team) and id ~= CRCoop.GetLocalPlayerId() then
            local ack = acknowledgements[id] or 0
            if ack < #events then allDelivered = false end
            if now >= nextEventSend then
                for seq = ack + 1, math.min(ack + 8, #events) do
                    local event = events[seq]
                    Send(id, "E", seq, event.op, event.expires, unpackArgs(event.args, 1, event.n))
                end
            end
        end
    end
    if now >= nextEventSend then nextEventSend = now + 0.2 end
    if M.coopPendingResult and allDelivered then
        local result = M.coopPendingResult
        M.coopPendingResult = nil
        Present(result[1], math.max(now + 5, result[2] or 0), result[3])
    end
    if now >= nextCameraSend then
        nextCameraSend = now + 0.2
        cameraSerial = cameraSerial + 1
        if cameraFrame then
            Send(0, "C", cameraSerial, cameraGeneration, unpackArgs(cameraFrame))
        else
            Send(0, "C", cameraSerial, cameraGeneration, "", 0, 0)
        end
    end
end

local function ReceivePresentation(from, kind, ...)
    if not CRCoop.IsNetworkGame() then return false end
    if kind == "A" then
        local seq = ...
        if CRCoop.IsAuthority() and CRCoop.GetPlayers()[from] and
            type(seq) == "number" and seq >= 0 and seq <= #events and seq == math.floor(seq) then
            acknowledgements[from] = math.max(acknowledgements[from] or 0, seq)
        end
        return true
    end
    if kind ~= "E" and kind ~= "C" then return false end
    if CRCoop.IsAuthority() or not FromLeader(from) then return true end
    if kind == "C" then
        local seq, generation, path, height, speed, target = ...
        if type(seq) == "number" and seq > remoteCameraSerial and type(generation) == "number" and
            type(path) == "string" and type(height) == "number" and type(speed) == "number" then
            remoteCameraSerial = seq
            remoteCamera = { generation, path, height, speed, target }
        end
        return true
    end
    local seq, op, expires = ...
    if type(seq) ~= "number" or type(op) ~= "string" or type(expires) ~= "number" then return true end
    if seq == receivedEvent + 1 and (native[op] or op == "Resources" or op == "Difficulty") then
        local args = { select(4, ...) }
        -- Dynamic handles can arrive after the Lua packet. Withhold the ACK
        -- until the next retransmission resolves it, rather than losing markers.
        local missing = (op == "SetObjectiveOn" or op == "SetObjectiveName" or op == "SetUserTarget") and
            not IsValid(args[1])
        if missing and GetTime() < expires then return true end
        -- A target destroyed before its packet arrived must not block the
        -- stream (and the mission result) forever. Only that stale marker drops.
        if not missing then ApplyPresentation(op, unpackArgs(args, 1, select("#", ...) - 3)) end
        receivedEvent = seq
    end
    Send(from, "A", receivedEvent)
    return true
end


local function RefreshDifficulty()
    if exu and exu.GetDifficulty then
        local d = exu.GetDifficulty()
        if d ~= nil then
            difficulty = d
        end
    end
    return difficulty
end

ApplyDifficultyObjectives = function()
    if difficulty >= 3 then
        AddObjective(hardDifficultyObjective[1], hardDifficultyObjective[2], hardDifficultyObjective[3], hardDifficultyObjective[4])
    elseif difficulty <= 1 then
        AddObjective(easyDifficultyObjective[1], easyDifficultyObjective[2], easyDifficultyObjective[3], easyDifficultyObjective[4])
    end
end

local function ApplyQOL()
    if exu then
        if exu.SetReticleRange then
            exu.SetReticleRange(600)
        end
        if exu.SetOrdnanceVelocInheritance then
            exu.SetOrdnanceVelocInheritance(true)
        end
    end

    if PersistentConfig and PersistentConfig.Initialize then
        PersistentConfig.Initialize()
    end
end

local function InitializeMissionSubtitles()
    subtit.Initialize("durations.csv")
    if PersistentConfig and PersistentConfig.ApplySettings then
        PersistentConfig.ApplySettings()
    end
end

local function TurboValue(team)
    if CRCoop.IsHumanTeam(team) or team == FRIENDLY_TEAM then
        return true
    end
    if team ~= 0 and difficulty and difficulty > 3 then
        return true
    end
end

local function ApplyTurbo(h)
    if CRCoop.IsNetworkGame() and not IsLocal(h) then return end
    if not (exu and exu.SetUnitTurbo and IsCraft(h)) then
        return
    end
    local value = TurboValue(GetTeamNum(h))
    if value ~= nil and value ~= false then
        exu.SetUnitTurbo(h, value)
    else
        exu.SetUnitTurbo(h, false)
    end
end

local function ApplyTurboToAll()
    if not (exu and exu.SetUnitTurbo) then
        return
    end
    for h in AllCraft() do
        ApplyTurbo(h)
    end
end

local function UpdateModules(dt)
    if exu and exu.UpdateOrdnance then
        exu.UpdateOrdnance()
    end
    if subtit and subtit.Update then
        subtit.Update()
    end
    if PersistentConfig then
        if PersistentConfig.UpdateInputs then PersistentConfig.UpdateInputs(localCameraActive) end
        if PersistentConfig.UpdateHeadlights then PersistentConfig.UpdateHeadlights() end
    end
end

local function NewMissionState()
    return {
        camera1 = false,
        camera2 = false,
        camera3 = false,
        found = false,
        found2 = false,
        start_done = false,
        patrol1 = false,
        message1 = false,
        message2 = false,
        message3 = false,
        message4 = false,
        message5 = false,
        mission_won = false,
        mission_lost = false,
        bootstrap_done = false,
        intro_skipped = false,
        wave_timer = 0.0,
        last_wave_time = 99999.0,
        cam_time = 0.0,
        NextSecond = 99999.0,
        bio_timer = 0,
        bscav = nil,
        bscout = nil,
        scav2 = nil,
        audmsg = nil,
        dummy = nil,
        lander = nil,
        bhandle = nil,
        bhome = nil,
        recycler = nil,
        bgoal = nil,
        bhandle2 = nil,
        loading_done = false,
        loadGracePeriod = 0,
        overlayResetPending = false,
        initialObjectiveCompleted = false,
        stagedFighters = {},
    }
end
M = NewMissionState()

local function OrderActivatedFighter(h)
    if not h or not IsAlive(h) then return end
    if not M.found2 then
        M.found2 = true
        M.bscout = h
        if SetLabel then SetLabel(M.bscout, LABEL_BSCOUT) end
        Goto(M.bscout, "patrol1")
        SetObjectiveOn(M.bscout)
    elseif IsAlive(M.bscav) and IsAlive(M.bgoal) and GetDistance(M.bscav, M.bgoal) < 200.0 then
        Attack(h, M.bscav)
    else
        Goto(h, "patrol2")
    end
end

local function StageInitialFighters()
    M.stagedFighters = M.stagedFighters or {}
    if #M.stagedFighters > 0 or M.patrol1 then return end

    -- spawn2 is roughly 900 metres from the player start and outside the
    -- configured 600-metre reticle range. Team 0 plus zero independence keeps
    -- this approach group neutral, inert, and out of mission state until the
    -- scavenger reaches the first field.
    for _ = 1, DiffUtils.ScaleEnemy(1) do
        local fighter = BuildObject("svfigh", 0, "spawn2")
        if fighter and IsValid(fighter) then
            if type(SetIndependence) == "function" then SetIndependence(fighter, 0) end
            SetObjectiveOff(fighter)
            M.stagedFighters[#M.stagedFighters + 1] = fighter
        end
    end
end

local function ActivateStagedFighters()
    local activated = 0
    for _, fighter in ipairs(M.stagedFighters or {}) do
        if fighter and IsAlive(fighter) then
            SetTeamNum(fighter, ENEMY_TEAM)
            if type(SetIndependence) == "function" then SetIndependence(fighter, 1) end
            OrderActivatedFighter(fighter)
            activated = activated + 1
        end
    end
    M.stagedFighters = {}
    return activated
end

function Save()
    M.playerPilotModeState = PlayerPilotMode.Save()
    return M, aiCore.Save(), M.playerPilotModeState
end

function Load(missionData, aiData, pilotModeData)
    M = missionData or M
    M.playerPilotModeState = pilotModeData or M.playerPilotModeState
    if aiData then
        aiCore.Load(aiData)
    end
    M.loading_done = false
    M.loadGracePeriod = GetTime() + 2.0
    M.overlayResetPending = true
end

local function ResetOverlayRuntimeAfterLoad()
    if PersistentConfig and PersistentConfig.EnableOverlayRendererForSession then
        PersistentConfig.EnableOverlayRendererForSession()
    end

    if exu and exu.ResetOverlaySupport then
        local ok, result = pcall(exu.ResetOverlaySupport, "misn02b-load")
        if not ok then
            print("misn02b: overlay reset call failed: " .. tostring(result))
        elseif result == false then
            print("misn02b: overlay reset reported failure")
        else
            print("misn02b: overlay reset completed after load")
        end
    end

    M.overlayResetPending = false
end

local function AudioDone(msg)
    return (not msg) or IsAudioMessageDone(msg)
end

local function KeepSavedHandleOrGet(current, label)
    if current and IsValid(current) then
        return current
    end
    return GetHandle(label)
end

RefreshHandlesAfterLoad = function()
    -- Saved handles are authoritative when still valid. Named lookups are only
    -- fallbacks for older/incomplete saves or objects that were recreated.
    M.dummy = KeepSavedHandleOrGet(M.dummy, "fake_player")
    M.lander = KeepSavedHandleOrGet(M.lander, "avland0_wingman")
    M.bhandle = KeepSavedHandleOrGet(M.bhandle, "sscr_171_scrap")
    M.bhome = KeepSavedHandleOrGet(M.bhome, "abcomm1_i76building")
    M.recycler = KeepSavedHandleOrGet(M.recycler, "avrecy-1_recycler")
    M.bgoal = KeepSavedHandleOrGet(M.bgoal, "apscrap-1_camerapod")
    M.bhandle2 = KeepSavedHandleOrGet(M.bhandle2, "sscr_176_scrap")

    M.bscav = KeepSavedHandleOrGet(M.bscav, LABEL_BSCAV)
    M.bscout = KeepSavedHandleOrGet(M.bscout, LABEL_BSCOUT)
    M.scav2 = KeepSavedHandleOrGet(M.scav2, LABEL_SCAV2)

    local foundScav = IsValid and IsValid(M.bscav)
    local foundScav2 = IsValid and IsValid(M.scav2)
    local foundScout = IsValid and IsValid(M.bscout)

    for h in AllCraft() do
        if not foundScav or not foundScav2 then
            if IsOdf(h, "avscav") and GetTeamNum(h) == 1 then
                if not foundScav then
                    M.bscav = h
                    if SetLabel then SetLabel(M.bscav, LABEL_BSCAV) end
                    foundScav = true
                elseif not foundScav2 then
                    M.scav2 = h
                    if SetLabel then SetLabel(M.scav2, LABEL_SCAV2) end
                    foundScav2 = true
                end
            end
        end

        if not foundScout then
            if IsOdf(h, "svfigh") and GetTeamNum(h) == ENEMY_TEAM then
                M.bscout = h
                if SetLabel then SetLabel(M.bscout, LABEL_BSCOUT) end
                foundScout = true
            end
        end

        if foundScav and foundScav2 and foundScout then break end
    end
end

local function BuildTerrainClutter()
    TerrainClutter.BuildLayer(CLUTTER_PROFILE)
end

local function SetupAI(preserveExisting)
    local playerTeam, enemyTeam
    if preserveExisting and aiCore.ActiveTeams and aiCore.ActiveTeams[1] and aiCore.ActiveTeams[ENEMY_TEAM] then
        playerTeam, enemyTeam = aiCore.ActiveTeams[1], aiCore.ActiveTeams[ENEMY_TEAM]
    else
        playerTeam, enemyTeam = DiffUtils.SetupTeams(aiCore.Factions.NSDF, aiCore.Factions.CCA, ENEMY_TEAM)
    end
    playerTeam:SetConfig("manageFactories", false)
    playerTeam:SetConfig("manageBase", false)
    playerTeam:SetConfig("manageTacticalOrders", false)
    playerTeam:SetConfig("autoRepairWingmen", PersistentConfig.Settings.AutoRepairWingmen)
    playerTeam:SetConfig("enableParatroopers", false)

    -- Every Team 6 combat unit in Mission 02B is mission-scripted. Keep aiCore
    -- available for shared systems, but do not let its strategic managers issue
    -- competing orders to the Soviet patrols/waves.
    enemyTeam:SetConfig("manageFactories", false)
    enemyTeam:SetConfig("manageBase", false)
    enemyTeam:SetConfig("manageTacticalOrders", false)
    enemyTeam:SetConfig("autoManage", false)
    enemyTeam:SetConfig("autoBuild", false)
    enemyTeam:SetConfig("enableParatroopers", false)
end

local function BootstrapPlayerSideAI()
    if CRCoop.IsNetworkGame() then
        -- Bootstrap's world-wide registration can create strategic managers
        -- for guest teams and tune remote human craft. Keep world observation,
        -- but register behavior only for locally owned non-human objects.
        aiCore.ResetObjectCacheTracking()
        for h in AllObjects() do
            aiCore.TrackWorldObject(h)
            if h and IsValid(h) and IsLocal(h) and not CRCoop.IsHumanCraft(h) then
                if GetTeamNum(h) == ENEMY_TEAM then
                    aiCore.AddSpecialObject(h)
                else
                    aiCore.AddObject(h)
                end
            end
        end
        aiCore.RefreshObjectCache(true)
        return
    end
    local restoreIndependence = {}

    -- aiCore.Bootstrap scans the whole world, so temporarily lock Team 6 craft
    -- out of that scan. Their original independence values are restored before
    -- mission logic resumes.
    if type(GetIndependence) == "function" and type(SetIndependence) == "function" then
        for h in AllCraft() do
            if h and IsValid(h) and GetTeamNum(h) == ENEMY_TEAM then
                local ok, value = pcall(GetIndependence, h)
                if ok then
                    restoreIndependence[h] = value
                    pcall(SetIndependence, h, 0)
                end
            end
        end
    end

    aiCore.Bootstrap()

    if type(SetIndependence) == "function" then
        for h, value in pairs(restoreIndependence) do
            if h and IsValid(h) then
                pcall(SetIndependence, h, value)
            end
        end
    end

    -- Add only aiSpecial combat behavior to pre-placed scripted units. This
    -- does not put them into production, squad, or base-management lists.
    for h in AllObjects() do
        if h and IsValid(h) and GetTeamNum(h) == ENEMY_TEAM then
            aiCore.AddSpecialObject(h)
        end
    end
end

PilotModeCanManageHandle = function(h)
    if not h or not IsValid(h) then
        return false
    end

    if h == M.bscav or h == M.scav2 or h == M.dummy then
        return false
    end

    if CRCoop.IsNetworkGame() and (not IsLocal(h) or not CRCoop.HasAllPlayerHandles()) then
        return false
    end
    return not CRCoop.IsHumanCraft(h)
end

local function GetPilotModeObjectiveContext()
    if M.mission_lost or M.mission_won then
        return { key = "terminal", objectiveIds = {}, actions = {} }
    end

    if M.message3 and IsAlive(M.scav2) and IsAlive(M.bhome) then
        return {
            key = "scavenger-return",
            objectiveIds = { "misn02b3.otf" },
            actions = { { id = "escort-rescued-scavenger", command = "follow", target = M.scav2 } },
        }
    end

    if M.message2 and IsAlive(M.bhome) then
        return {
            key = "retreat-to-base",
            objectiveIds = { "misn02b2.otf" },
            actions = { { id = "defend-home-base", command = "defend", target = M.bhome } },
        }
    end

    if M.message1 and IsAlive(M.bscav) then
        return {
            key = "scrap-field-defense",
            objectiveIds = { "misn02b1.otf" },
            actions = { { id = "support-primary-scavenger", command = "follow", target = M.bscav } },
        }
    end

    return { key = "staging", objectiveIds = { "misn02b1.otf" }, actions = {} }
end

local function InitializePilotMode()
    PlayerPilotMode.Initialize({
        profile = {
            autoManage = false,
            autoRescue = true,
            stickToPlayer = true,
            manageFactories = false,
            autoBuild = false,
        },
        shouldManageHandle = PilotModeCanManageHandle,
        getObjectiveContext = GetPilotModeObjectiveContext,
    }, M.playerPilotModeState)
end

local function InitializeMissionRuntime(preserveExisting)
    RefreshDifficulty()
    if not CRCoop.IsNetworkGame() then ApplyDifficultyObjectives() end
    ApplyQOL()
    if CRCoop.IsAuthority() then
        InitializePilotMode()
        SetupAI(preserveExisting)
        BootstrapPlayerSideAI()
    end
    ApplyTurboToAll()
end

local function ApplyPostLoadInit()
    Ally(LEADER_TEAM, FRIENDLY_TEAM)
    Ally(FRIENDLY_TEAM, LEADER_TEAM)
    SetAIP("misn02.aip", ENEMY_TEAM)
    InitializeMissionSubtitles()

    if M.bgoal and IsAlive(M.bgoal) then
        SetUserTarget(M.bgoal)
        SetObjectiveName(M.bgoal, "Scrap Field Alpha")
    end

    for h in AllCraft() do
        SetObjectiveOff(h)
    end
end

function Start()
    M = NewMissionState()
    CRCoop.Initialize({
        getLocalPlayerId = function() return exu.GetMyNetID and exu.GetMyNetID() end,
        leaderTeam = LEADER_TEAM, humanTeamMin = 1, humanTeamMax = 4,
    })
    CRCoop.ApplyCoopAlliances(ENEMY_TEAM)
    for team = 1, 4 do
        Ally(team, FRIENDLY_TEAM)
        Ally(FRIENDLY_TEAM, team)
    end
    if CRCoop.IsNetworkGame() and exu.SetLives then exu.SetLives(999) end
    InitializeMissionSubtitles()
    Ally(LEADER_TEAM, FRIENDLY_TEAM)
    Ally(FRIENDLY_TEAM, LEADER_TEAM)
    if PersistentConfig and PersistentConfig.EnableOverlayRendererForSession then
        PersistentConfig.EnableOverlayRendererForSession()
    end
    InitializeMissionRuntime()
    if not CRCoop.IsNetworkGame() then StageInitialFighters() end
    BuildTerrainClutter()

    for h in AllCraft() do
        SetObjectiveOff(h)
    end

    M.loading_done = true

    --TestEXU()
end

function CreatePlayer(id, name, team)
    CRCoop.CreatePlayer(id, name, team)
    CRCoop.ApplyCoopAlliances(ENEMY_TEAM)
end
function AddPlayer(id, name, team)
    CRCoop.AddPlayer(id, name, team)
    CRCoop.ApplyCoopAlliances(ENEMY_TEAM)
end
function DeletePlayer(id, name, team) CRCoop.DeletePlayer(id) end
function Receive(from, kind, ...)
    if ReceivePresentation(from, kind, ...) then return true end
    return CRCoop.Receive(from, kind, ...)
end

-- AddObject function: Called when a game object is added
function AddObject(h)
    local team = GetTeamNum(h)
    local odf = GetOdf(h)
    if odf then odf = string.gsub(odf, "%z", "") end

    if PersistentConfig and PersistentConfig.OnObjectCreated then
        PersistentConfig.OnObjectCreated(h)
    end
    ApplyTurbo(h)
    if not CRCoop.IsAuthority() then return end

    if team == 1 and odf == "avscav" and M.bscav == nil then
        M.found = true
        M.bscav = h
        if SetLabel then SetLabel(M.bscav, LABEL_BSCAV) end
        SetCritical(M.bscav, true)
        SetObjectiveOn(M.bscav)

        -- Difficulty-based behavior for M.dummy tank
        local d = DiffUtils.Get().index
        if d < 2 and IsAlive(M.dummy) and not M.camera1 and not M.camera2 and not M.camera3 then
            Follow(M.dummy, M.bscav)
        end
    end

    if team == ENEMY_TEAM and odf == "svfigh" then
        OrderActivatedFighter(h)
    end

    -- Team 6 remains script-owned for production and tactical orders, but gets
    -- the reusable aiSpecial combat layer (weapon switching, cloak, sniping,
    -- and craft stealing). Player scavengers still use PlayerPilotMode.
    if team == ENEMY_TEAM then
        aiCore.AddSpecialObject(h)
    end
    if team == 1 and IsOdf(h, "avscav") then
        PlayerPilotMode.AddObject(h)
    end
end

-- Update function: Called every frame
function Update()
    if GetTime() < (M.loadGracePeriod or 0) then
        return
    end
    if not M.loading_done then
        if M.overlayResetPending then
            ResetOverlayRuntimeAfterLoad()
        end
        RefreshHandlesAfterLoad()
        InitializeMissionRuntime(true)
        if not CRCoop.IsNetworkGame() then StageInitialFighters() end
        ApplyPostLoadInit()
        BuildTerrainClutter()
        M.loading_done = true
    end
    local player = GetPlayerHandle()
    CRCoop.Update()
    UpdatePresentationTransport()
    UpdateModules(1.0 / 20.0)
    if M.coopResult or M.coopPendingResult then return end
    if CRCoop.IsNetworkGame() then
        if CRCoop.HasLeaderDeparted() then
            M.coopResult = true
            if localCameraActive then native.CameraFinish() end
            localCameraActive = false
            native.FailMission(GetTime() + 1.0)
            return
        end
        if CRCoop.HasUnsupportedPlayerTeam() or CRCoop.HasLateJoiners() then
            if not M.coopRestartWarned then
                DisplayMessage("Use distinct teams 1-4 and start together. Late join/rejoin requires a mission restart.")
                M.coopRestartWarned = true
            end
            return
        end
        if not CRCoop.IsSessionReady() then return end
    end
    if not M.coopMissionStarted then
        CRCoop.MarkMissionStarted()
        M.coopMissionStarted = true
    end
    if not CRCoop.IsAuthority() then return end
    PlayerPilotMode.Update()
    aiCore.Update()
    if not CRCoop.IsNetworkGame() and autosave and autosave.Update then
        autosave.Update(1.0 / 20.0)
    end

    -- Holographic Bio Logic
    if (M.camera1 or M.camera2 or M.camera3) and GetTime() >= M.bio_timer then
        --if IsAlive(player) then
        -- Spawns the holographic bio above the player
        local pos = GetPosition(player)
        pos.y = pos.y + 10.0
        MakeExplosion("xbio", pos)
        -- end
        M.bio_timer = GetTime() + 10.0
    end

    if not M.start_done then
        if not CRCoop.IsNetworkGame() and IsAlive(player) then
            SetPosition(player, STOCK_PLAYER_START)
        end
        if CRCoop.IsNetworkGame() then
            -- Native MP creates each human's craft. Discard only the offline
            -- actor; keep the authored empty tank available as in the campaign.
            local offlinePlayer = GetHandle("asuser0_person")
            if IsValid(offlinePlayer) and not CRCoop.IsHumanCraft(offlinePlayer) then
                RemoveObject(offlinePlayer)
            end
            StageInitialFighters()
            Present("Difficulty", RefreshDifficulty())
        end

        --[[
        -- Available AI Configuration Flags (Reference from aiCore.lua):
        -- flags marked [Diff] are managed by DiffUtils:SetupTeams() based on difficulty.
        -- playerTeam:SetConfig("difficulty", 1)         -- [Stub]
        -- playerTeam:SetConfig("race", "nsdf")          -- Default "nsdf"
        -- playerTeam:SetConfig("kc", 0)                  -- [Stub]
        -- playerTeam:SetConfig("stratMultiplier", 1.0)   -- [Stub]
        -- playerTeam:SetConfig("autoBuild", true)

        -- Advanced Settings
        -- playerTeam:SetConfig("thumperChance", 10)       -- [Diff]
        -- playerTeam:SetConfig("mortarChance", 20)        -- [Diff]
        -- playerTeam:SetConfig("fieldChance", 10)         -- [Diff]
        -- playerTeam:SetConfig("doubleWeaponChance", 20)  -- [Diff]
        -- playerTeam:SetConfig("howitzerChance", 50)       -- [Diff]

        -- AI Behavior Settings
        -- playerTeam:SetConfig("soldierRange", 50)
        -- playerTeam:SetConfig("sniperSteal", true)
        -- playerTeam:SetConfig("pilotZeal", 0.4)          -- [Diff]
        -- playerTeam:SetConfig("sniperTraining", 75)      -- [Diff]
        -- playerTeam:SetConfig("sniperStealth", 0.5)      -- [Diff]
        -- playerTeam:SetConfig("resourceBoost", false)    -- [Diff]

        -- Timers
        -- playerTeam:SetConfig("upgradeInterval", 240)    -- [Diff]
        -- playerTeam:SetConfig("wreckerInterval", 600)    -- [Diff]
        -- playerTeam:SetConfig("techInterval", 60)
        -- playerTeam:SetConfig("techMax", 4)

        -- Toggles
        -- playerTeam:SetConfig("passiveRegen", false)     -- [Diff] (Player Only)
        -- playerTeam:SetConfig("autoManage", false)
        -- playerTeam:SetConfig("autoRepairWingmen", false) -- [Diff]
        -- playerTeam:SetConfig("autoRescue", false)       -- [Diff] (Player Only)
        -- playerTeam:SetConfig("autoTugs", false)
        -- playerTeam:SetConfig("stickToPlayer", false)    -- [Diff] (Player Only)
        -- playerTeam:SetConfig("dynamicMinefields", false)
        -- playerTeam:SetConfig("scavengerAssist", false) -- [Diff] (Player Only)

        -- Minefield positions
        -- playerTeam:SetConfig("minefields", {}) -- List of positions for minelayers

        -- Automation Sub-config
        -- playerTeam:SetConfig("followPercentage", 30)
        -- playerTeam:SetConfig("patrolPercentage", 30)
        -- playerTeam:SetConfig("guardPercentage", 40)
        -- playerTeam:SetConfig("scavengerCount", 4)
        -- playerTeam:SetConfig("tugCount", 2)
        -- playerTeam:SetConfig("buildingSpacing", 80)
        -- playerTeam:SetConfig("rescueDelay", 2.0)
        -- playerTeam:SetConfig("pilotTopoff", 4)          -- [Diff]

        -- Reinforcements
        -- playerTeam:SetConfig("orbitalReinforce", false) -- Default false

        -- Legacy Features
        -- playerTeam:SetConfig("regenRate", 0.0)          -- [Diff] (Building Regen)
        -- playerTeam:SetConfig("reclaimEngineers", false)

        -- Factory Management
        -- playerTeam:SetConfig("manageFactories", true)

        -- Wreckers & Paratroopers
        -- playerTeam:SetConfig("enableWreckers", false)     -- [Diff]
        -- playerTeam:SetConfig("enableParatroopers", false)  -- [Diff]
        -- playerTeam:SetConfig("paratrooperChance", 0)       -- [Diff]
        -- playerTeam:SetConfig("paratrooperInterval", 600)   -- [Diff]

        -- Construction Defaults
        -- playerTeam:SetConfig("siloMinDistance", 250.0)
        -- playerTeam:SetConfig("siloMaxDistance", 450.0)
        --]]
        local pilots = math.max(1, DiffUtils.ScaleRes(2))
        local scrap = math.max(4, DiffUtils.ScaleRes(5))
        CRCoop.ForEachHumanTeam(function(team)
            Present("Resources", team, scrap, pilots)
        end)
        SetAIP("misn02.aip", ENEMY_TEAM)

        M.dummy = GetHandle("fake_player")
        M.lander = GetHandle("avland0_wingman")
        M.bhandle = GetHandle("sscr_171_scrap")
        M.bhome = GetHandle("abcomm1_i76building")
        M.recycler = GetHandle("avrecy-1_recycler")
        M.bgoal = GetHandle("apscrap-1_camerapod")
        M.bhandle2 = GetHandle("sscr_176_scrap")

        SetUserTarget(M.bgoal)
        SetObjectiveName(M.bgoal, "Scrap Field Alpha")
        --SetObjectiveName(M.recycler, "Recycler Montana")
        M.start_done = true
        InitializeMissionSubtitles()

        -- Establish alliance between player (team 1) and M.dummy tank (team 7)
        Ally(LEADER_TEAM, FRIENDLY_TEAM)

        -- Spawn pilots at Recycler based on difficulty
        local d = DiffUtils.Get().index
        local pilotCount = 0
        if d == 0 then
            pilotCount = 3 -- Very Easy
        elseif d == 1 then
            pilotCount = 2 -- Easy
        elseif d == 2 or d == 3 then
            pilotCount = 1 -- Medium/Hard
        end                -- Very Hard (4) gets 0

        for i = 1, pilotCount do
            BuildObject("aspilo", 1, "avrecy-1_recycler")
        end

        M.camera1 = true
        M.cam_time = GetTime() + 30.0
        CameraReady()
        M.audmsg = subtit.Play("misn0230.wav")
        --M.audmsg = subtit.Play("misn0201.wav")
    end

    -- Camera Logic
    if M.camera1 then
        if CameraPath("fixcam", 1200, 250, M.lander) or CameraCancelled() or AudioDone(M.audmsg)
            or (CRCoop.IsNetworkGame() and GetTime() > M.cam_time) then
            -- Stop audio and subtitles if skipped
            if CameraCancelled() then
                subtit.Stop()
                M.intro_skipped = true
                M.audmsg = nil
            end
            M.camera1 = false
            M.cam_time = GetTime() + 10.0
            M.camera2 = true
        end
    end

    if M.camera2 then
        M.camera2 = false
        M.camera3 = true
        if IsAlive(M.dummy) then
            Goto(M.dummy, "dummy__path")
        end
        M.cam_time = GetTime() + 25.0
    end

    if M.camera3 then
        -- The shot follows the dummy tank; if it is gone, end the shot rather
        -- than leave the camera frozen on its last frame.
        if not IsAlive(M.dummy) or CameraPath("zoomcam", 1200, 800, M.dummy) or AudioDone(M.audmsg) or CameraCancelled()
            or (CRCoop.IsNetworkGame() and GetTime() > M.cam_time) then
            M.camera3 = false
            M.cam_time = 99999.0
            CameraFinish()

            -- Reassign M.dummy tank instead of removing it
            if IsAlive(M.dummy) then
                SetTeamNum(M.dummy, FRIENDLY_TEAM) -- Set to team 7
                Ally(LEADER_TEAM, FRIENDLY_TEAM)           -- Make teams 1 and 7 allies

                local d = DiffUtils.Get().index
                if d < 2 and IsAlive(M.bscav) then
                    Follow(M.dummy, M.bscav)
                elseif IsAlive(M.recycler) then
                    Defend2(M.dummy, M.recycler, 0) -- Set to defend the M.recycler
                end
            end

            --SetPosition(player, "playermove")
            -- Stop previous audio if the user skipped the cinematic, then start the next one
            if CameraCancelled() or M.intro_skipped then
                subtit.Stop()
                M.intro_skipped = true
            end

            if not M.intro_skipped then
                M.audmsg = subtit.Play("misn0201.wav")
            end
            --subtit.Play("misn0224.wav")
            M.wave_timer = GetTime() + DiffUtils.ScaleTimer(30.0)
            AddObjective("misn02b1.otf", "white")
        end
    end

    -- The stock objective starts white and completes when the player enters a
    -- vehicle. Keep the later ClearObjectives transition unchanged.
    if M.start_done and not M.camera1 and not M.camera2 and not M.camera3
        and not M.message2 and not M.initialObjectiveCompleted
        and CRCoop.AllPlayersSatisfy(function(h) return IsAlive(h) and not IsPerson(h) end) then
        UpdateObjective("misn02b1.otf", "green")
        M.initialObjectiveCompleted = true
    end

    -- Patrol 1 Logic
    if not M.patrol1 and M.found and IsAlive(M.bhandle) and IsAlive(M.bscav) and GetDistance(M.bhandle, M.bscav) < 75.0 then
        if ActivateStagedFighters() == 0 then
            -- Compatibility fallback for old saves made before staged fighters
            -- were persisted.
            for _ = 1, DiffUtils.ScaleEnemy(1) do BuildObject("svfigh", ENEMY_TEAM, "spawn1") end
        end

        subtit.Play("misn0233.wav")
        M.message1 = true
        M.patrol1 = true

        if not M.message4 and M.found2 then
            M.message4 = true
        end
    end

    if not M.message4 and M.found2 then
        M.message4 = true
    end

    -- Capture pre-placed player-side units after mission initialization without
    -- allowing aiCore to claim the scripted Team 6 force.
    if M.start_done and not M.bootstrap_done then
        BootstrapPlayerSideAI()
        M.bootstrap_done = true
    end

    -- Wave Logic
    if M.message4 and not M.message5 and IsAlive(M.bscav) and IsAlive(M.bhandle2) and GetDistance(M.bscav, M.bhandle2) < 200.0 then
        BuildObject("svfigh", ENEMY_TEAM, "spawn2")
        M.message5 = true
        M.wave_timer = GetTime() + 30.0
    end

    if M.message5 and GetTime() > M.wave_timer then
        for i = 1, DiffUtils.ScaleEnemy(1) do BuildObject("svfigh", ENEMY_TEAM, "spawn2") end
        M.wave_timer = GetTime() + DiffUtils.ScaleTimer(45.0)
    end

    -- Retreat Logic
    if M.message1 and M.message5 and not M.message2 and IsAlive(M.bscav) and GetLastEnemyShot(M.bscav) > 0 then
        Follow(M.bscav, M.bhome)
        ClearObjectives()
        AddObjective("misn02b2.otf", "white")
        subtit.Play("misn0225.wav")
        local bbase = GetHandle("apbase-1_camerapod")
        SetUserTarget(bbase)
        M.message2 = true
    end

    -- Loss Condition
    -- PORT FIX: Tran05's outer OR keeps base/recycler loss independent of the
    -- first scavenger handle. The old Lua nesting accidentally ignored those
    -- losses before AddObject found bscav. Restore the source grouping; the
    -- convoy checks, failure audio and completion timing stay the same.
    -- Keep the first terminal result: rescue/win must not replace failure's
    -- shared audmsg in this frame, and a settled win must not become a loss.
    if not M.mission_lost and not M.mission_won then
        if (M.bscav ~= nil and ((not CRCoop.IsNetworkGame() and not IsAlive(player)) or not IsAlive(M.bscav) or (M.message3 and not IsAlive(M.scav2))))
            or not IsAlive(M.bhome) or not IsAlive(M.recycler) then
            ClearObjectives()
            AddObjective("misn02b4.otf", "red")
            M.audmsg = subtit.Play("misn0227.wav")
            M.mission_lost = true
        end
    end

    if M.mission_lost and AudioDone(M.audmsg) then
        FailMission(GetTime(), "misn02l1.des")
    end

    -- Rescue Logic
    if not M.mission_lost and not M.mission_won and (CRCoop.IsNetworkGame() or IsAlive(player)) and M.message1 and M.message4 and IsAlive(M.bhome) and IsAlive(M.bscav) and GetDistance(M.bhome, M.bscav) < 300.0 and not M.message3 then
        Follow(M.bscav, M.bhome)
        M.wave_timer = GetTime() + 45.0
        M.scav2 = BuildObject("avscav", 1, "spawn3")
        if SetLabel then SetLabel(M.scav2, LABEL_SCAV2) end
        SetCritical(M.scav2, true)
        Retreat(M.scav2, "retreat")
        SetObjectiveOn(M.scav2)
        SetObjectiveOff(M.bscav)
        subtit.Play("misn0228.wav")
        M.last_wave_time = GetTime() + 10.0
        M.NextSecond = GetTime() + 1.0
        M.message3 = true

        -- Dummy tank follow M.scav2 logic for lower difficulties
        local d = DiffUtils.Get().index
        if d < 2 and IsAlive(M.dummy) then
            Follow(M.dummy, M.scav2)
        end

        -- Flanking Ambush: Spawn enemies behind the player at spawn1
        for i = 1, DiffUtils.ScaleEnemy(1) do
            local h = BuildObject("svfigh", ENEMY_TEAM, "spawn1")
            Attack(h, M.scav2)
        end
    end

    -- Health Regen
    if IsAlive(M.bscav) and M.message3 and GetTime() > M.NextSecond then
        AddHealth(M.bscav, 200.0)
        M.NextSecond = GetTime() + 1.0
    end

    -- Final Wave
    if M.last_wave_time < GetTime() then
        for i = 1, DiffUtils.ScaleEnemy(1) do
            local sid = BuildObject("svfigh", ENEMY_TEAM, "spawn4")
            if IsAlive(M.scav2) then Attack(sid, M.scav2) end
        end
        M.last_wave_time = 99999.0
    end

    -- Win Condition
    if M.message3 and not M.mission_lost and not M.mission_won and IsAlive(M.bhome) and IsAlive(M.scav2) and GetDistance(M.bhome, M.scav2) < 200.0 then
        ClearObjectives()
        SetObjectiveOff(M.scav2)
        if IsAlive(M.bscav) then SetObjectiveOff(M.bscav) end
        AddObjective("misn02b3.otf", "green")
        if IsAlive(M.bscav) then AddHealth(M.bscav, 1000.0) end
        if IsAlive(M.scav2) then AddHealth(M.scav2, 1000.0) end
        M.audmsg = subtit.Play("misn0234.wav")
        M.mission_won = true
    end

    if M.mission_won and AudioDone(M.audmsg) then
        SucceedMission(GetTime(), "misn02w1.des")
    end
end

-- Original DLL comments and cut-content ledger. These are historical C++
-- fragments, kept inactive for reconstruction alongside the complete, verbatim
-- References/EarlyMissionSources/Tran05Mission.cpp. QOL behavior above is retained.
--[==[

Tran05Mission.cpp:17
/*
	Tran05Mission
*/

Tran05Mission.cpp:21
// used by (misn02b.bzn) as first american mission

Tran05Mission.cpp:42
// bools

Tran05Mission.cpp:76
// floats

Tran05Mission.cpp:92
// handles

Tran05Mission.cpp:111
// the base

Tran05Mission.cpp:118
// path pointers

Tran05Mission.cpp:131
// integers

Tran05Mission.cpp:181
// this is the handle thing brad made for me

Tran05Mission.cpp:212
// attack scrap field

Tran05Mission.cpp:225
// hard wired, hope this doesn't change

Tran05Mission.cpp:227
/*
			misn0224
			Commander, we've discovered a deposit of bio metal..
			stay close to the scavenger.  
		*/

Tran05Mission.cpp:237
//	bplayer=GetHandle("player-1_hover");

Tran05Mission.cpp:252
//(GetTime()>cam_time)))

Tran05Mission.cpp:265
// Final actor audio has both tracks in one place

Tran05Mission.cpp:266
//	StopAudioMessage(audmsg);

Tran05Mission.cpp:267
//		audmsg = AudioMessage("misn0232.wav");

Tran05Mission.cpp:301
//bscout=GetHandle("svfigh-1_wingman");

Tran05Mission.cpp:307
// this is in case the AddObject is called in 

Tran05Mission.cpp:308
// a different frame then the BuildObject() above

Tran05Mission.cpp:311
// was bgoal

Tran05Mission.cpp:314
//		if (bscout!=NULL) Attack(bscout,bscav,1);

Tran05Mission.cpp:329
// send the scav home

Tran05Mission.cpp:330
// bscav to bbase

Tran05Mission.cpp:339
/*
			misn0225
			Commander our insturments show that you are heavily
			ounumbered..
		*/

Tran05Mission.cpp:349
// was message2, so we know a scav was built

Tran05Mission.cpp:359
/*
			You or the scav is dead
			*/

Tran05Mission.cpp:364
/*
			misn0227
			Eagle's Nest 1 is being overrun.  
			Our forces are surrendering..
		*/

Tran05Mission.cpp:381
/*
			Now rescue the second
			scavenger
		*/

Tran05Mission.cpp:414
/*
			misn0226
			Good work.  I know you wanted to engage..
		*/

Tran05Mission.cpp:418
//	AudioMessage("misn0226.wav");

Tran05Mission.cpp:457
// bools

Tran05Mission.cpp:462
// floats

Tran05Mission.cpp:467
// Handles

Tran05Mission.cpp:472
// path pointers

Tran05Mission.cpp:478
// ints

Tran05Mission.cpp:489
// hack path to go around buildings

Tran05Mission.cpp:517
// bools

Tran05Mission.cpp:522
// floats

Tran05Mission.cpp:527
// Handles

Tran05Mission.cpp:532
// path pointers

Tran05Mission.cpp:538
// ints
]==]
