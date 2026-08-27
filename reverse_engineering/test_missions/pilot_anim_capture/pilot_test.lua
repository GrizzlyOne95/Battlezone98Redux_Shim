-- pilot_test.lua
-- Purpose-specific harness for PLAYER PILOT ANIMATION MANAGEMENT investigation.
-- Deploy: copy this file as lcbench.lua alongside lcbench.bzn/.hg2/.lgt/.trn/.mat/.ini
--         inside addon/lcbench (or any Instant Action slot with same basename).
--         Alternatively, load as a standalone Instant Action mission with its own
--         .bzn/.trn/.mat copy (see pilot_anim_capture/README.md).
--
-- Timeline: configurable via pitcfg.odf if present, otherwise defaults below.
-- Prints precise [PILOTTEST] markers so OpenShim's [FPAnim] log can be correlated.
--
-- Lua: 5.1 (no goto, no ::label::, no io/os/debug)
-- ODF filenames: 8-char limit respected (pitcfg.odf, gsnipe, handgun etc.)

local function TrimNullPad(s)
    if s == nil then return "" end
    -- Engine getters may return fixed-width null-padded strings.
    local n = string.find(s, "\0", 1, true)
    if n then
        return string.sub(s, 1, n - 1)
    end
    return s
end

local function SafeOdf(h)
    if not IsValid(h) then return "INVALID" end
    local ok, v = pcall(GetOdf, h)
    if not ok or v == nil then return "UNKNOWN" end
    return TrimNullPad(v)
end

local function SafeClassSig(h)
    if not IsValid(h) then return "INVALID" end
    local ok, v = pcall(GetClassSig, h)
    if not ok or v == nil then return "?" end
    return TrimNullPad(v)
end

local function SafePilotClass(h)
    if not IsValid(h) then return "" end
    local ok, v = pcall(GetPilotClass, h)
    if not ok or v == nil then return "" end
    return TrimNullPad(v)
end

local function SafeWeaponClass(h, slot)
    if not IsValid(h) then return "" end
    local ok, v = pcall(GetWeaponClass, h, slot)
    if not ok or v == nil then return "" end
    return TrimNullPad(v)
end

local function ReadPitConfig()
    -- Use pitcfg.odf if present; otherwise use built-in defaults.
    -- ODF filename is 6 chars so engine limit is satisfied.
    local cfg = nil
    local ok, handle = pcall(OpenODF, "pitcfg")
    if ok and handle ~= nil then cfg = handle end
    local t = {}
    t.hopOutAt      = 2.0
    t.idleEnd       = 6.0
    t.sniperAt      = 8.0
    t.crouchAt      = 10.0
    t.fireAt        = 12.5
    t.moveAt        = 15.0
    t.jumpAt        = 18.0
    t.finalIdleAt   = 22.0
    t.reenterAt     = 26.0
    t.completeAt    = 32.0
    t.sniperWeapon  = "gsnipe"
    t.normalWeapon  = "handgun"
    if cfg ~= nil then
        local v, found
        v, found = GetODFFloat(cfg, "Timeline", "hopOutAt", t.hopOutAt); if found then t.hopOutAt = v end
        v, found = GetODFFloat(cfg, "Timeline", "idleEnd", t.idleEnd); if found then t.idleEnd = v end
        v, found = GetODFFloat(cfg, "Timeline", "sniperAt", t.sniperAt); if found then t.sniperAt = v end
        v, found = GetODFFloat(cfg, "Timeline", "crouchAt", t.crouchAt); if found then t.crouchAt = v end
        v, found = GetODFFloat(cfg, "Timeline", "fireAt", t.fireAt); if found then t.fireAt = v end
        v, found = GetODFFloat(cfg, "Timeline", "moveAt", t.moveAt); if found then t.moveAt = v end
        v, found = GetODFFloat(cfg, "Timeline", "jumpAt", t.jumpAt); if found then t.jumpAt = v end
        v, found = GetODFFloat(cfg, "Timeline", "finalIdleAt", t.finalIdleAt); if found then t.finalIdleAt = v end
        v, found = GetODFFloat(cfg, "Timeline", "reenterAt", t.reenterAt); if found then t.reenterAt = v end
        v, found = GetODFFloat(cfg, "Timeline", "completeAt", t.completeAt); if found then t.completeAt = v end
        local s
        s, found = GetODFString(cfg, "Timeline", "sniperWeapon", t.sniperWeapon); if found and s ~= "" then t.sniperWeapon = TrimNullPad(s) end
        s, found = GetODFString(cfg, "Timeline", "normalWeapon", t.normalWeapon); if found and s ~= "" then t.normalWeapon = TrimNullPad(s) end
    end
    return t
end

local cfg = nil
local elapsed = 0.0
local playerVehicle = nil
local playerPilot = nil
local pilotDetectedAt = nil
local lastPilotHandle = nil
local stage = 0
local pendingHopOut = false
local hopOutIssuedAt = nil
local didHopOut = false
local fireUntil = nil
local moveUntil = nil
local reenterTarget = nil
local manualStepPending = nil
local exuAvailable = false
local exuAnimChecked = false

local function LogMarker(eventName)
    print(string.format("[PILOTTEST] T+%.3f %s stage=%d veh=%s pilot=%s player=%s odf=%s class=%s weap0=%s weap1=%s pilCls=%s",
        elapsed,
        eventName,
        stage,
        tostring(playerVehicle),
        tostring(playerPilot),
        tostring(GetPlayerHandle()),
        SafeOdf(GetPlayerHandle()),
        SafeClassSig(GetPlayerHandle()),
        SafeWeaponClass(GetPlayerHandle(), 0),
        SafeWeaponClass(GetPlayerHandle(), 1),
        SafePilotClass(GetPlayerHandle())
    ))
end

local function DumpPlayerInfo(prefix)
    local h = GetPlayerHandle()
    if not IsValid(h) then
        print(string.format("[PILOTTEST] T+%.3f %s player INVALID", elapsed, prefix))
        return
    end
    local odf = SafeOdf(h)
    local sig = SafeClassSig(h)
    local base = "?"
    local ok, v = pcall(GetBase, h)
    if ok and v then base = TrimNullPad(v) end
    local cls = "?"
    local ok2, v2 = pcall(GetClassLabel, h)
    if ok2 and v2 then cls = TrimNullPad(v2) end
    local team = -1
    local ok3, t = pcall(GetTeamNum, h)
    if ok3 and t ~= nil then team = t end
    local pos = GetPosition(h)
    local pstr = "nil"
    if pos ~= nil then
        pstr = string.format("(%.1f,%.1f,%.1f)", pos.x, pos.y, pos.z)
    end
    print(string.format("[PILOTTEST] T+%.3f %s handle=%s odf=%s sig=%s base=%s class=%s team=%d pos=%s weap0=%s weap1=%s pilotCls=%s valid=%s alive=%s isPerson=%s",
        elapsed, prefix, tostring(h), odf, sig, base, cls, team, pstr,
        SafeWeaponClass(h,0), SafeWeaponClass(h,1), SafePilotClass(h),
        tostring(IsValid(h)), tostring(IsAlive(h)), tostring(IsPerson(h))
    ))
    -- ExtraUtilities probe: enumerate animation states if available
    if not exuAnimChecked then
        exuAnimChecked = true
        if exu ~= nil and exu.animation ~= nil then
            exuAvailable = true
            print(string.format("[PILOTTEST] T+%.3f EXU animation API present caps=%s", elapsed, tostring(exu.animation.GetCapabilities and "yes" or "no")))
        else
            print(string.format("[PILOTTEST] T+%.3f EXU animation API NOT present", elapsed))
        end
    end
    if exuAvailable then
        local probeAnims = {"idle","runForward","runBackward","runLeft","runRight","stand2Kneel","kneel2stand","fireRecoilSniper","jump","landParachute","idleParachute"}
        for _, aname in ipairs(probeAnims) do
            local has = false
            local okp, res = pcall(function() return exu.animation.Has(h, aname) end)
            if okp then has = res end
            if has then
                local ok2p, info = pcall(function() return exu.animation.GetInfo(h, aname) end)
                if ok2p and info ~= nil then
                    print(string.format("[PILOTTEST] T+%.3f ANIM has=%s en=%s loop=%s w=%.3f t=%.3f len=%.3f nrm=%.3f atEnd=%s",
                        elapsed, aname, tostring(info.enabled), tostring(info.loop), info.weight or 0, info.timePosition or 0, info.length or 0, info.normalizedTime or 0, tostring(info.atEnd)))
                else
                    print(string.format("[PILOTTEST] T+%.3f ANIM has=%s info=nil", elapsed, aname))
                end
            end
        end
    end
end

local function DetectPilotChange()
    local cur = GetPlayerHandle()
    if cur ~= lastPilotHandle then
        local prev = lastPilotHandle
        lastPilotHandle = cur
        print(string.format("[PILOTTEST] T+%.3f PLAYER_HANDLE_CHANGED prev=%s cur=%s odf=%s isPerson=%s",
            elapsed, tostring(prev), tostring(cur), SafeOdf(cur), tostring(IsPerson(cur))))
        -- capture new pilot handle if it is a Person
        if IsValid(cur) and IsPerson(cur) then
            playerPilot = cur
            if pilotDetectedAt == nil then pilotDetectedAt = elapsed end
            print(string.format("[PILOTTEST] T+%.3f PILOT_DETECTED handle=%s odf=%s class=%s",
                elapsed, tostring(cur), SafeOdf(cur), SafeClassSig(cur)))
            DumpPlayerInfo("PILOT_INFO")
        elseif IsValid(cur) then
            print(string.format("[PILOTTEST] T+%.3f PLAYER_IS_VEHICLE handle=%s odf=%s", elapsed, tostring(cur), SafeOdf(cur)))
        end
    end
end

local function TryHopOut()
    local h = GetPlayerHandle()
    if not IsValid(h) then
        print(string.format("[PILOTTEST] T+%.3f HOP_OUT skip: player invalid", elapsed))
        return false
    end
    if IsPerson(h) then
        print(string.format("[PILOTTEST] T+%.3f HOP_OUT skip: already Person (on foot) odf=%s", elapsed, SafeOdf(h)))
        return false
    end
    local ok, err = pcall(HopOut, h)
    if not ok then
        print(string.format("[PILOTTEST] T+%.3f HOP_OUT pcall failed err=%s player=%s", elapsed, tostring(err), tostring(h)))
        return false
    end
    print(string.format("[PILOTTEST] T+%.3f HOP_OUT issued player=%s odf=%s", elapsed, tostring(h), SafeOdf(h)))
    LogMarker("HOP_OUT")
    hopOutIssuedAt = elapsed
    pendingHopOut = true
    didHopOut = true
    return true
end

local function TryEquipWeapon(weapName, reason)
    local h = GetPlayerHandle()
    if not IsValid(h) then
        print(string.format("[PILOTTEST] T+%.3f EQUIP skip invalid weap=%s reason=%s", elapsed, weapName, reason))
        return
    end
    -- GiveWeapon may need slot; try slot 0 by default, then check.
    local ok, res = pcall(GiveWeapon, h, weapName, 0)
    if not ok then
        print(string.format("[PILOTTEST] T+%.3f EQUIP pcall failed weap=%s err=%s", elapsed, weapName, tostring(res)))
        return
    end
    print(string.format("[PILOTTEST] T+%.3f EQUIP weap=%s reason=%s result=%s weap0 now=%s weap1=%s",
        elapsed, weapName, reason, tostring(res), SafeWeaponClass(h,0), SafeWeaponClass(h,1)))
    -- Also try SetWeaponMask to ensure selection
    -- Use GiveWeapon without slot to let engine pick
    local ok2, res2 = pcall(GiveWeapon, h, weapName)
    if ok2 then
        print(string.format("[PILOTTEST] T+%.3f EQUIP second GiveWeapon no-slot result=%s weap0=%s", elapsed, tostring(res2), SafeWeaponClass(h,0)))
    end
    LogMarker("EQUIP_" .. string.upper(weapName))
end

local function TryFire()
    local h = GetPlayerHandle()
    if not IsValid(h) then return end
    -- FireAt self target not valid; we need an enemy. For animation test, try to fire at ground point or create dummy.
    -- Minimal: check if we can call FireAt on a dummy object. Create a distant dummy if not present.
    -- Instead, we try to use the weapon directly: the act of firing is input-driven, but we can test animation via EXU.
    -- We will attempt exu.animation.Play for fireRecoilSniper if available, else lament manual action.
    if exuAvailable then
        local ok, res = pcall(function() return exu.animation.Play(h, "fireRecoilSniper", {restart=true, loop=false, weight=1.0}) end)
        print(string.format("[PILOTTEST] T+%.3f FIRE_ANIM_PLAY exu fireRecoilSniper ok=%s res=%s", elapsed, tostring(ok), tostring(res)))
    end
    -- Also try normal weapon anim if present
    local target = GetNearestEnemy(h)
    if target ~= nil and IsValid(target) then
        local ok, err = pcall(FireAt, h, target)
        print(string.format("[PILOTTEST] T+%.3f FIRE_AT enemy=%s ok=%s err=%s", elapsed, tostring(target), tostring(ok), tostring(err)))
    else
        print(string.format("[PILOTTEST] T+%.3f FIRE_AT no enemy; manual fire recommended. Hold fire key now for 3 seconds.", elapsed))
    end
    LogMarker("FIRE_WINDOW")
end

local function TryMoveTest()
    local h = GetPlayerHandle()
    if not IsValid(h) then return end
    -- Attempt to issue Goto to a nearby point to trigger walk/run anim without manual WASD.
    -- This is not guaranteed to drive Person locomotion, but it exercises AI path.
    local pos = GetPosition(h)
    if pos == nil then
        print(string.format("[PILOTTEST] T+%.3f MOVE skip no position", elapsed))
        return
    end
    local dest = SetVector(pos.x + 25.0, pos.y, pos.z + 5.0)
    local ok, err = pcall(Goto, h, dest, 0)
    print(string.format("[PILOTTEST] T+%.3f MOVE Goto dest=(%.1f,%.1f,%.1f) ok=%s err=%s", elapsed, dest.x, dest.y, dest.z, tostring(ok), tostring(err)))
    LogMarker("MOVE_WINDOW")
    if not ok then
        print(string.format("[PILOTTEST] T+%.3f MANUAL ACTION: strafe/move now for 3 seconds (WASD)", elapsed))
    end
    moveUntil = elapsed + 3.0
    -- Also try exu animation directly for walk
    if exuAvailable then
        local ok2, res2 = pcall(function() return exu.animation.Play(h, "runForward", {restart=true, loop=true, weight=1.0}) end)
        print(string.format("[PILOTTEST] T+%.3f MOVE_ANIM_PLAY runForward ok=%s res=%s", elapsed, tostring(ok2), tostring(res2)))
    end
end

local function TryJump()
    local h = GetPlayerHandle()
    if not IsValid(h) then return end
    -- There is no direct Lua Jump API for Person; jumping is input-driven.
    -- We log that manual jump is required if automation unavailable.
    print(string.format("[PILOTTEST] T+%.3f JUMP phase: no deterministic Lua Jump API known; MANUAL ACTION: press Jump now", elapsed))
    print(string.format("[PILOTTEST] T+%.3f MANUAL ACTION: TAP JUMP (Space) now, then remain idle for landing observation", elapsed))
    LogMarker("JUMP_WINDOW")
    -- Try to exercise via SetVelocity if permitted (may not trigger anim but moves)
    local vel = GetVelocity(h)
    if vel ~= nil then
        print(string.format("[PILOTTEST] T+%.3f JUMP vel before y=%.3f", elapsed, vel.y or 0))
    end
    -- Also try to play jump anim via EXU for feasibility
    if exuAvailable then
        local ok, res = pcall(function() return exu.animation.Play(h, "jump", {restart=true, loop=false, weight=1.0}) end)
        print(string.format("[PILOTTEST] T+%.3f JUMP_ANIM_PLAY jump ok=%s res=%s (isolated, will restore to idle after)", elapsed, tostring(ok), tostring(res)))
    end
end

local function TryReenter()
    local h = GetPlayerHandle()
    if not IsValid(h) or not IsPerson(h) then
        print(string.format("[PILOTTEST] T+%.3f REENTER skip not Person h=%s isPerson=%s", elapsed, tostring(h), tostring(IsPerson(h))))
        return
    end
    -- Find nearest vehicle (excluding self) to enter
    local veh = GetNearestVehicle(h)
    if veh == nil or not IsValid(veh) or veh == h then
        -- Spawn a fresh vehicle nearby for reentry test
        local pos = GetPosition(h)
        if pos ~= nil then
            local spawnPos = SetVector(pos.x + 8.0, pos.y, pos.z)
            local veh2 = BuildObject("avtank", GetTeamNum(h), spawnPos)
            if IsValid(veh2) then
                veh = veh2
                print(string.format("[PILOTTEST] T+%.3f REENTER spawned vehicle %s at (%.1f,%.1f,%.1f)", elapsed, tostring(veh), spawnPos.x, spawnPos.y, spawnPos.z))
            end
        end
    end
    reenterTarget = veh
    if veh ~= nil and IsValid(veh) then
        local ok, err = pcall(GetIn, h, veh, 1)
        print(string.format("[PILOTTEST] T+%.3f REENTER GetIn pilot=%s veh=%s ok=%s err=%s", elapsed, tostring(h), tostring(veh), tostring(ok), tostring(err)))
        LogMarker("REENTER_WINDOW")
    else
        print(string.format("[PILOTTEST] T+%.3f REENTER no vehicle found; MANUAL ACTION: walk to vehicle and press USE", elapsed))
    end
end

local function PollPilotState()
    local h = GetPlayerHandle()
    if IsValid(h) and IsPerson(h) then
        -- Periodically log anim info every ~2 sec while idle
        if math.floor(elapsed*2) % 4 == 0 then
            -- thin logging, already covered by inventory poll in native
        end
    end
end

function Start()
    cfg = ReadPitConfig()
    print(string.format("[PILOTTEST] T+%.3f START mission lcbench pilot animation harness cfg hopOut=%.1f idleEnd=%.1f sniper=%.1f crouch=%.1f fire=%.1f move=%.1f jump=%.1f finalIdle=%.1f reenter=%.1f complete=%.1f sniperW=%s normalW=%s",
        0.0, cfg.hopOutAt, cfg.idleEnd, cfg.sniperAt, cfg.crouchAt, cfg.fireAt, cfg.moveAt, cfg.jumpAt, cfg.finalIdleAt, cfg.reenterAt, cfg.completeAt, cfg.sniperWeapon, cfg.normalWeapon))
    local p = GetPlayerHandle()
    print(string.format("[PILOTTEST] T+0.000 INIT player=%s valid=%s odf=%s isPerson=%s team=%s pos=%s",
        tostring(p), tostring(IsValid(p)), SafeOdf(p), tostring(IsPerson(p)), tostring(IsValid(p) and GetTeamNum(p) or "?"), tostring(IsValid(p) and GetPosition(p) or "nil")))
    DumpPlayerInfo("INIT")
    LogMarker("INIT")
    playerVehicle = p
    lastPilotHandle = p
    stage = 0
    elapsed = 0.0
    -- Ensure player starts in vehicle; if already Person, we already have harness
    if IsValid(p) and IsPerson(p) then
        print(string.format("[PILOTTEST] T+0.000 ALREADY_ON_FOOT pilot=%s", tostring(p)))
        didHopOut = true
        playerPilot = p
        stage = 2
    else
        print(string.format("[PILOTTEST] T+0.000 WAITING_FOR_HOP_OUT at T+%.1f", cfg.hopOutAt))
    end
end

function Update(dt)
    elapsed = elapsed + (dt or 0.0)
    DetectPilotChange()

    -- Periodic state poll
    if stage >= 0 then
        PollPilotState()
    end

    -- Stage 0: wait for hopOutAt
    if stage == 0 then
        if elapsed >= cfg.hopOutAt then
            LogMarker("HOP_OUT")
            TryHopOut()
            stage = 1
        end
        return
    end

    -- Stage 1: waiting for pilot to appear after HopOut
    if stage == 1 then
        -- If pilot detected, advance to idle observation
        if playerPilot ~= nil and IsValid(playerPilot) and IsPerson(playerPilot) then
            -- Give a moment for entity creation
            if elapsed >= (hopOutIssuedAt or cfg.hopOutAt) + 1.0 then
                print(string.format("[PILOTTEST] T+%.3f IDLE_WINDOW begin (stationary observation)", elapsed))
                LogMarker("IDLE_WINDOW")
                DumpPlayerInfo("IDLE_START")
                stage = 2
            end
        else
            -- Timeout if hopOut failed
            if hopOutIssuedAt and elapsed >= hopOutIssuedAt + 4.0 then
                print(string.format("[PILOTTEST] T+%.3f HOP_OUT timeout, pilot not detected; retry or manual HopOut", elapsed))
                -- Retry once
                if didHopOut and elapsed < hopOutIssuedAt + 6.0 then
                    -- wait
                else
                    TryHopOut()
                    hopOutIssuedAt = elapsed
                end
                if elapsed >= cfg.hopOutAt + 10.0 and playerPilot == nil then
                    print(string.format("[PILOTTEST] T+%.3f MANUAL ACTION REQUIRED: press HopOut key (default: E) now", elapsed))
                    stage = 2 -- proceed anyway to not block timeline
                end
            end
        end
        return
    end

    -- Stage 2: idle baseline until sniperAt
    if stage == 2 then
        if elapsed >= cfg.sniperAt then
            print(string.format("[PILOTTEST] T+%.3f SET_SNIPER weapon=%s", elapsed, cfg.sniperWeapon))
            LogMarker("SET_SNIPER")
            DumpPlayerInfo("PRE_SNIPER")
            TryEquipWeapon(cfg.sniperWeapon, "sniper equip")
            stage = 3
        end
        return
    end

    -- Stage 3: sniper equip observation until crouchAt
    if stage == 3 then
        if elapsed >= cfg.crouchAt then
            print(string.format("[PILOTTEST] T+%.3f CROUCH_EXPECTED (sniper selected should drive stand2Kneel->crouch)", elapsed))
            LogMarker("CROUCH_EXPECTED")
            DumpPlayerInfo("CROUCH_START")
            -- Sniper crouch is automatic after equip; we just wait and observe.
            -- Optionally try to ensure weapon still sniper
            if SafeWeaponClass(GetPlayerHandle(),0) ~= cfg.sniperWeapon and SafeWeaponClass(GetPlayerHandle(),1) ~= cfg.sniperWeapon then
                print(string.format("[PILOTTEST] T+%.3f CROUCH weapon mismatch, re-equip sniper", elapsed))
                TryEquipWeapon(cfg.sniperWeapon, "crouch re-equip")
            end
            -- Manual hint if automation cannot force crouch
            print(string.format("[PILOTTEST] T+%.3f MANUAL ACTION: if not already crouched, select sniper weapon and remain still for 3 sec", elapsed))
            print(string.format("[PILOTTEST] T+%.3f CAPTURE WINDOW: 3 seconds (crouch anim should be active)", elapsed))
            stage = 4
        end
        return
    end

    -- Stage 4: crouch/sniper phase until fireAt
    if stage == 4 then
        if elapsed >= cfg.fireAt then
            print(string.format("[PILOTTEST] T+%.3f FIRE_WINDOW begin", elapsed))
            LogMarker("FIRE_WINDOW")
            DumpPlayerInfo("PRE_FIRE")
            TryFire()
            fireUntil = elapsed + 2.0
            stage = 5
        end
        return
    end

    -- Stage 5: firing window
    if stage == 5 then
        if elapsed >= fireUntil + 0.5 then
            -- After firing, brief idle
            print(string.format("[PILOTTEST] T+%.3f FIRE done, checking weapon anim state", elapsed))
            DumpPlayerInfo("POST_FIRE")
            stage = 6
        end
        return
    end

    if stage == 6 then
        if elapsed >= cfg.moveAt then
            print(string.format("[PILOTTEST] T+%.3f MOVE_WINDOW begin", elapsed))
            LogMarker("MOVE_WINDOW")
            DumpPlayerInfo("PRE_MOVE")
            TryMoveTest()
            stage = 7
        end
        return
    end

    if stage == 7 then
        if elapsed >= moveUntil then
            print(string.format("[PILOTTEST] T+%.3f MOVE done", elapsed))
            DumpPlayerInfo("POST_MOVE")
            -- Restore idle before jump
            local h = GetPlayerHandle()
            if exuAvailable and IsValid(h) then
                pcall(function() exu.animation.Stop(h, "runForward", false) end)
                pcall(function() exu.animation.Play(h, "idle", {restart=true, loop=true, weight=1.0}) end)
            end
            if IsValid(h) then Stop(h, 1) end
            stage = 8
        end
        return
    end

    if stage == 8 then
        if elapsed >= cfg.jumpAt then
            print(string.format("[PILOTTEST] T+%.3f JUMP_WINDOW begin", elapsed))
            LogMarker("JUMP_WINDOW")
            DumpPlayerInfo("PRE_JUMP")
            TryJump()
            stage = 9
        end
        return
    end

    if stage == 9 then
        -- Give 4 sec for jump/land observation (includes manual jump + land)
        if elapsed >= cfg.jumpAt + 4.0 then
            print(string.format("[PILOTTEST] T+%.3f LANDING observation end", elapsed))
            LogMarker("LANDING_WINDOW_END")
            DumpPlayerInfo("POST_JUMP")
            -- Try to reassert crouch if sniper still selected (Redux regression case)
            if SafeWeaponClass(GetPlayerHandle(),0) == cfg.sniperWeapon or SafeWeaponClass(GetPlayerHandle(),1) == cfg.sniperWeapon then
                print(string.format("[PILOTTEST] T+%.3f POST_JUMP sniper still selected; expect re-crouch (stand2Kneel) if fixed", elapsed))
            end
            stage = 10
        end
        return
    end

    if stage == 10 then
        if elapsed >= cfg.finalIdleAt then
            print(string.format("[PILOTTEST] T+%.3f FINAL_IDLE begin (return to idle)", elapsed))
            LogMarker("FINAL_IDLE")
            DumpPlayerInfo("FINAL_IDLE_START")
            -- If sniper still equipped, switch back to normal weapon to observe kneel2stand
            if SafeWeaponClass(GetPlayerHandle(),0) == cfg.sniperWeapon or SafeWeaponClass(GetPlayerHandle(),1) == cfg.sniperWeapon then
                TryEquipWeapon(cfg.normalWeapon, "final idle switch to normal")
                print(string.format("[PILOTTEST] T+%.3f MANUAL ACTION: deselect sniper, switch to handgun/rifle for uncrouch anim", elapsed))
            end
            stage = 11
        end
        return
    end

    if stage == 11 then
        if elapsed >= cfg.reenterAt then
            print(string.format("[PILOTTEST] T+%.3f REENTER_WINDOW begin", elapsed))
            LogMarker("REENTER_WINDOW")
            DumpPlayerInfo("PRE_REENTER")
            TryReenter()
            stage = 12
        end
        return
    end

    if stage == 12 then
        if elapsed >= cfg.completeAt then
            print(string.format("[PILOTTEST] T+%.3f TEST_COMPLETE player=%s pilot=%s veh=%s", elapsed, tostring(GetPlayerHandle()), tostring(playerPilot), tostring(reenterTarget)))
            LogMarker("TEST_COMPLETE")
            DumpPlayerInfo("FINAL")
            -- Summary for automation
            print(string.format("[PILOTTEST] SUMMARY hopOut=%s pilotDetected=%s pilotHandle=%s reenterTarget=%s",
                tostring(didHopOut), tostring(playerPilot ~= nil), tostring(playerPilot), tostring(reenterTarget)))
            stage = 13
        end
        return
    end

    if stage == 13 then
        -- Remain idle post-complete
        return
    end
end

function CreateObject(h) end
function AddObject(h) end
function DeleteObject(h)
    -- Detect vehicle/pilot destruction during harness
    if h == playerPilot then
        print(string.format("[PILOTTEST] T+%.3f DeleteObject pilot=%s", elapsed, tostring(h)))
        playerPilot = nil
    end
    if h == playerVehicle then
        print(string.format("[PILOTTEST] T+%.3f DeleteObject vehicle=%s", elapsed, tostring(h)))
    end
    if h == reenterTarget then
        print(string.format("[PILOTTEST] T+%.3f DeleteObject reenterTarget=%s", elapsed, tostring(h)))
    end
end
function CreatePlayer(id, name, team) print(string.format("[PILOTTEST] T+%.3f CreatePlayer id=%d name=%s team=%d", elapsed, id, name, team)) end
function AddPlayer(id, name, team) print(string.format("[PILOTTEST] T+%.3f AddPlayer id=%d name=%s team=%d", elapsed, id, name, team)) end
function DeletePlayer(id, name, team) print(string.format("[PILOTTEST] T+%.3f DeletePlayer id=%d name=%s team=%d", elapsed, id, name, team)) end
