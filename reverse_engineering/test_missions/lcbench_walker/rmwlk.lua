-- lcbench walker cockpit jitter fixture (lcbench_walker) — expanded multi-walker + EXU SetAsUser
-- Purpose: deterministic first-person walker laboratory on existing lcbench terrain.
-- Deploy as addon/lcbench/lcbench.lua via runner overlay; do not replace TRN/BZN.
-- Lua 5.1 only, no goto, no ObjectiveObjects(), uses print and GetPositionNear.
-- Covers the 15-point test matrix via polled state + EXU forced perspective.
-- Filenames: rmwlk.lua (5) and rmwcfg.odf (6) satisfy 8-char ODF rule.
-- EXU: uses SetAsUser(handle) from ExtraUtilities when available (global, SEH-guarded
-- via pcall). The harness validates via pcall(SetAsUser, h) per spec: spawn at controlled
-- point, force player into that exact vehicle, stabilize, run case, capture, switch.

local elapsed = 0.0
local nextPoll = 0.0
local nextLog = 0.0
local stage = 0
local subStage = 0
local selectedCase = "stat"
local fixtureCommit = "unknown"
local player = nil
local lastPos = nil
local pollInterval = 0.1
local logInterval = 0.5

-- Walker variants to test — all four stock walkers + principal non-walker control.
-- These are actual stock ODFs (no derivatives unless instrumentation requires it).
-- avtank is the required baseline; an additional scout/tank can be added but not needed.
local walkerVariants = {"avwalk", "svwalk", "bvwalk", "cvwalk", "avtank"}
local holdVariant = nil        -- when set, possess only this variant and never advance
local currentVariantIndex = 1
local spawnedHandles = {}      -- per-variant handles
local walkerHandles = {}       -- walkers only (first 4)
local controlHandle = nil      -- avtank
local activeWalker = nil       -- currently SetAsUser'd handle
local caseStartElapsed = 0.0
local transitionLogBudget = 0  -- high-detail frames around SetAsUser

-- Sanitizer for ODF-returned strings that may contain trailing NULs/padding.
local function Sanitize(s)
    if s == nil then return "" end
    local t = tostring(s)
    local nul = string.find(t, "\0", 1, true)
    if nul then t = string.sub(t, 1, nul - 1) end
    t = string.gsub(t, "^%s+", "")
    t = string.gsub(t, "%s+$", "")
    return t
end

local function VecLen(v)
    if v == nil or v.x == nil then return 0.0 end
    return math.sqrt(v.x*v.x + v.y*v.y + v.z*v.z)
end

local function PlaceNear(refHandle, rMin, rMax)
    if refHandle ~= nil and IsValid(refHandle) then
        return GetPositionNear(GetPosition(refHandle), rMin, rMax)
    end
    if player ~= nil and IsValid(player) then
        return GetPositionNear(GetPosition(player), rMin, rMax)
    end
    return GetPositionNear(SetVector(0, 0, 0), rMin, rMax)
end

local function PlaceAtRange(range, lateral)
    local origin = GetPosition(player)
    local t = GetTransform(player)
    local fx = t.front_x or 0.0
    local fz = t.front_z or 1.0
    local rx = t.right_x or 1.0
    local rz = t.right_z or 0.0
    local base = SetVector(
        origin.x + fx * range + rx * lateral,
        origin.y,
        origin.z + fz * range + rz * lateral)
    return GetPositionNear(base, 2.0, 4.0)
end

local function SpawnWalker(odfName, team, pos)
    local h = BuildObject(odfName, team, pos)
    if IsValid(h) then
        SetIndependence(h, 0)
    end
    return h
end

local function LogHeader(msg)
    print(string.format("[LCWALK][%s][%s] T+%.3f %s", tostring(selectedCase), walkerVariants[currentVariantIndex] or "none", elapsed, msg))
end

-- EXU SetAsUser wrapper: deterministic, pcall-guarded, logs success/failure.
-- Inspected EXU API: ExtraUtilities registers SetAsUser via luaL_register(L,"exu",exuExports)
-- in src/luaexport.cpp:673 { "SetAsUser", &GameObject::SetAsUser }. The established interface
-- is therefore exu.SetAsUser(handle) after require("exu") or via global exu table, not a bare
-- global. We probe exu table first, then bare global, and attempt require("exu") as fallback.
-- This avoids guessing the module contract. All calls are pcall-guarded and transition frames
-- are logged at high detail.
local exuModule = nil
local function ResolveSetAsUserFn()
    -- Already resolved via exu table?
    local exuTbl = rawget(_G, "exu")
    if exuTbl ~= nil and type(exuTbl) == "table" then
        local fn = rawget(exuTbl, "SetAsUser")
        if fn ~= nil then return fn, "exu.SetAsUser" end
    end
    local bare = rawget(_G, "SetAsUser")
    if bare ~= nil then return bare, "Global SetAsUser" end
    -- Attempt require("exu") if not yet loaded (Lua 5.1)
    local okReq, mod = pcall(require, "exu")
    if okReq and mod ~= nil and type(mod) == "table" then
        exuModule = mod
        local fn2 = rawget(mod, "SetAsUser")
        if fn2 ~= nil then return fn2, "require(exu).SetAsUser" end
    end
    -- Also try exu table after require
    exuTbl = rawget(_G, "exu")
    if exuTbl ~= nil and type(exuTbl) == "table" then
        local fn3 = rawget(exuTbl, "SetAsUser")
        if fn3 ~= nil then return fn3, "exu.SetAsUser(post-require)" end
    end
    return nil, "none"
end

local function TrySetAsUser(handle)
    local prevUser = GetPlayerHandle()
    local odfBefore = "unknown"
    if IsValid(prevUser) then
        local ok, odf = pcall(GetOdf, prevUser)
        if ok then odfBefore = Sanitize(odf) end
    end
    local targetOdf = "unknown"
    if IsValid(handle) then
        local ok2, odf2 = pcall(GetOdf, handle)
        if ok2 then targetOdf = Sanitize(odf2) end
    end
    print(string.format("[LCWALK][%s][%s] SETASUSER attempt prev=%s (%s) -> new=%s (%s)", tostring(selectedCase), walkerVariants[currentVariantIndex] or "?", tostring(prevUser), odfBefore, tostring(handle), targetOdf))
    local fn, src = ResolveSetAsUserFn()
    if fn == nil then
        print(string.format("[LCWALK][%s][%s] SETASUSER unavailable (%s) — continuing without forced perspective", tostring(selectedCase), walkerVariants[currentVariantIndex] or "?", src))
        return false
    end
    print(string.format("[LCWALK][%s][%s] SETASUSER via %s", tostring(selectedCase), walkerVariants[currentVariantIndex] or "?", src))
    local ok, result = pcall(fn, handle)
    if not ok then
        print(string.format("[LCWALK][%s][%s] SETASUSER pcall failed: %s", tostring(selectedCase), walkerVariants[currentVariantIndex] or "?", tostring(result)))
        return false
    end
    print(string.format("[LCWALK][%s][%s] SETASUSER pcall ok result=%s", tostring(selectedCase), walkerVariants[currentVariantIndex] or "?", tostring(result)))
    transitionLogBudget = 6
    return true
end

local function SnapshotDetailed(label)
    local curUser = GetPlayerHandle()
    local curOdf = "nil"
    if IsValid(curUser) then
        local ok, odf = pcall(GetOdf, curUser)
        if ok then curOdf = Sanitize(odf) end
    end
    local walkHandle = activeWalker
    local pPos = nil
    local pVel = nil
    local pTrans = nil
    if walkHandle ~= nil and IsValid(walkHandle) then
        pPos = GetPosition(walkHandle)
        local okv, v = pcall(GetVelocity, walkHandle)
        if okv then pVel = v end
        local okt, tr = pcall(GetTransform, walkHandle)
        if okt then pTrans = tr end
    elseif curUser ~= nil and IsValid(curUser) then
        pPos = GetPosition(curUser)
        local okv, v = pcall(GetVelocity, curUser)
        if okv then pVel = v end
        local okt, tr = pcall(GetTransform, curUser)
        if okt then pTrans = tr end
    end
    local posStr = "nil"
    local velStr = "nil"
    local transStr = "nil"
    if pPos then posStr = string.format("(%.2f,%.2f,%.2f)", pPos.x, pPos.y, pPos.z) end
    if pVel then velStr = string.format("(%.3f,%.3f,%.3f) len=%.3f", pVel.x, pVel.y, pVel.z, VecLen(pVel)) end
    if pTrans then
        transStr = string.format("f(%.3f,%.3f,%.3f) r(%.3f,%.3f,%.3f) u(%.3f,%.3f,%.3f) pos(%.2f,%.2f,%.2f)",
            pTrans.front_x or 0, pTrans.front_y or 0, pTrans.front_z or 0,
            pTrans.right_x or 0, pTrans.right_y or 0, pTrans.right_z or 0,
            pTrans.up_x or 0, pTrans.up_y or 0, pTrans.up_z or 0,
            pTrans.posit_x or 0, pTrans.posit_y or 0, pTrans.posit_z or 0)
    end
    local isPilot = 0
    if IsValid(curUser) then
        local ok, v = pcall(IsPerson, curUser)
        if ok and v then isPilot = 1 end
    end
    -- Camera owner heuristic: native trace logs MainCam/cameraOwner at higher fidelity.
    -- Here we log the Lua-visible user handle which the native trace correlates via generation.
    print(string.format("[LCWALK][%s][%s] %s curUser=%s curOdf=%s activeWalker=%s pos=%s vel=%s t=[%s] isPilot=%d elapsed=%.3f",
        tostring(selectedCase), walkerVariants[currentVariantIndex] or "?", label, tostring(curUser), curOdf, tostring(walkHandle), posStr, velStr, transStr, isPilot, elapsed))
    if walkHandle ~= nil and IsValid(walkHandle) then
        local ok, odf = pcall(GetOdf, walkHandle)
        if ok then
            local s = Sanitize(odf)
            print(string.format("[LCWALK][%s][%s] ODF rawLen=%d sanitized=%s", tostring(selectedCase), walkerVariants[currentVariantIndex] or "?", string.len(tostring(odf)), s))
        end
    end
    if pPos and lastPos then
        local dx = pPos.x - lastPos.x
        local dy = pPos.y - lastPos.y
        local dz = pPos.z - lastPos.z
        local dist = math.sqrt(dx*dx + dy*dy + dz*dz)
        print(string.format("[LCWALK][%s][%s] DELTA dist=%.4f dt=%.3f", tostring(selectedCase), walkerVariants[currentVariantIndex] or "?", dist, pollInterval))
    end
    if pPos then lastPos = {x=pPos.x, y=pPos.y, z=pPos.z} end
    -- High-detail transition burst: log extra frame immediately after SetAsUser
    if transitionLogBudget > 0 then
        print(string.format("[LCWALK][%s][%s] TRANSITION_DETAIL budget=%d", tostring(selectedCase), walkerVariants[currentVariantIndex] or "?", transitionLogBudget))
        transitionLogBudget = transitionLogBudget - 1
    end
end

local refObjects = {}

function Start()
    elapsed = 0.0
    nextPoll = 0.0
    nextLog = 0.0
    stage = 0
    subStage = 0
    currentVariantIndex = 1
    local cfg = OpenODF("rmwcfg")
    selectedCase = Sanitize(GetODFString(cfg, "Roadmap", "case", "stat"))
    if selectedCase == "" then selectedCase = "stat" end
    -- Hold mode ("hold_<odf>", e.g. hold_avwalk). The cycling matrix cannot be
    -- used for a motion run: the possessed walker has to stay possessed for the
    -- whole drive window so external input reaches one vehicle through the
    -- normal player-control path. This selects a single variant and disables
    -- the per-variant advance; it adds no new capture logic.
    holdVariant = nil
    if string.sub(selectedCase, 1, 5) == "hold_" then
        local want = string.sub(selectedCase, 6)
        local i
        for i = 1, #walkerVariants do
            if walkerVariants[i] == want then holdVariant = i end
        end
        if holdVariant == nil then holdVariant = 1 end
    end
    fixtureCommit = Sanitize(GetODFString(cfg, "Roadmap", "commit", "unknown"))
    player = GetPlayerHandle()
    print(string.format("[LCWALK] START build=2.2.301 case=%s commit=%s player=%s variants=%s", tostring(selectedCase), tostring(fixtureCommit), tostring(player), table.concat(walkerVariants, ",")))
    local probed = 0
    local idx
    for idx = 1, #walkerVariants do
        print(string.format("[LCWALK] PROBE odf=%s index=%d", walkerVariants[idx], idx))
        probed = probed + 1
    end
    local _, src = ResolveSetAsUserFn()
    print(string.format("[LCWALK] EXU probe SetAsUser via %s exists=%s", tostring(src), tostring(src ~= "none")))
end

function Update(dt)
    elapsed = elapsed + (dt or 0.0)

    -- Stage 0: wait 1s for world settle, then spawn all 5 vehicles at distinct GetPositionNear points
    if stage == 0 and elapsed >= 1.0 then
        print(string.format("[LCWALK][%s] BUILD begin multi-walker", tostring(selectedCase)))
        player = GetPlayerHandle()
        if not IsValid(player) then
            print(string.format("[LCWALK][%s] ERROR no player handle", tostring(selectedCase)))
            stage = 99
            return
        end
        -- Spawn each variant at a distinct ring around the controlled test point (origin near player).
        -- Use GetPositionNear so they do not overlap — spec requires this.
        local base = GetPosition(player)
        local spawnedCount = 0
        local i
        for i = 1, #walkerVariants do
            local odf = walkerVariants[i]
            -- Distinct range per index: 20+ i*8 to avoid overlap
            local pos = GetPositionNear(base, 20 + i*8, 28 + i*8)
            local h = SpawnWalker(odf, 1, pos)
            spawnedHandles[i] = h
            if i <= 4 then
                walkerHandles[i] = h
            else
                controlHandle = h
            end
            local odfLog = "nil"
            if IsValid(h) then
                local ok, odfGot = pcall(GetOdf, h)
                if ok then odfLog = Sanitize(odfGot) end
                spawnedCount = spawnedCount + 1
            end
            print(string.format("[LCWALK][%s][%s] SPAWN idx=%d handle=%s odf=%s posNear=(%.1f,%.1f)", tostring(selectedCase), odf, i, tostring(h), odfLog, pos.x, pos.z))
        end
        -- Fixed visual references (buildings) at separate points — optional but aids camera stability
        local ref1 = BuildObject("avwalk", 1, GetPositionNear(base, 60, 66))
        local ref2 = BuildObject("svwalk", 2, GetPositionNear(base, 66, 72))
        refObjects = {ref1, ref2}
        for i = 1, #refObjects do
            if IsValid(refObjects[i]) then SetIndependence(refObjects[i], 0); Stop(refObjects[i], 1) end
        end
        print(string.format("[LCWALK][%s] SPAWN_SUMMARY count=%d", tostring(selectedCase), spawnedCount))
        -- Start with first walker
        currentVariantIndex = holdVariant or 1
        activeWalker = spawnedHandles[currentVariantIndex]
        -- Force player into first walker via EXU
        TrySetAsUser(activeWalker)
        -- Allow frames for camera/owner stabilization
        caseStartElapsed = elapsed
        SnapshotDetailed("BUILT")
        nextPoll = elapsed + pollInterval
        nextLog = elapsed + logInterval
        stage = 1
        subStage = 0
        return
    end

    if stage == 1 then
        -- For each variant, run the case for ~4 seconds, capturing at 10Hz + transition detail
        local variantTime = elapsed - caseStartElapsed
        -- High-detail: first 0.4s after SetAsUser already burst-logged via transitionLogBudget
        -- Normal poll
        if elapsed >= nextPoll then
            SnapshotDetailed("POLL")
            nextPoll = nextPoll + pollInterval
        end
        if elapsed >= nextLog then
            print(string.format("[LCWALK][%s][%s] heartbeat variantTime=%.2f", tostring(selectedCase), walkerVariants[currentVariantIndex] or "?", variantTime))
            nextLog = nextLog + logInterval
        end

        -- Per-variant case execution (reuse prior stat/fwd/slope/switch etc. but now per-variant)
        local h = activeWalker
        if variantTime >= 0.5 and variantTime < 0.6 and subStage == 0 then
            -- Stabilized after SetAsUser — issue case-specific order
            if selectedCase == "fwd" and IsValid(h) then
                Goto(h, GetPositionNear(GetPosition(h), 80, 90))
                print(string.format("[LCWALK][%s][%s] ACTION Goto fwd", tostring(selectedCase), walkerVariants[currentVariantIndex]))
            elseif selectedCase == "rev" and IsValid(h) then
                local g = PlaceAtRange(-60, 0)
                -- PlaceAtRange uses player origin; for per-variant we want handle origin
                g = GetPositionNear(GetPosition(h), 60, 70)
                -- reverse by going opposite of facing: compute behind
                local tr = GetTransform(h)
                local fx = tr.front_x or 0
                local fz = tr.front_z or 1
                local p = GetPosition(h)
                local behind = SetVector(p.x - fx*40, p.y, p.z - fz*40)
                Goto(h, GetPositionNear(behind, 2, 4))
                print(string.format("[LCWALK][%s][%s] ACTION Goto rev", tostring(selectedCase), walkerVariants[currentVariantIndex]))
            elseif selectedCase == "rot" and IsValid(h) then
                local p = GetPosition(h)
                local tgt = SetVector(p.x + 5, p.y, p.z + 5)
                Goto(h, tgt)
                print(string.format("[LCWALK][%s][%s] ACTION rot", tostring(selectedCase), walkerVariants[currentVariantIndex]))
            elseif selectedCase == "slope" and IsValid(h) then
                Goto(h, GetPositionNear(SetVector(800, 0, 800), 20, 30))
                print(string.format("[LCWALK][%s][%s] ACTION slope to 800,800", tostring(selectedCase), walkerVariants[currentVariantIndex]))
            elseif selectedCase == "haim" and IsValid(h) then
                -- Find enemy walker to aim at
                local enemy = nil
                local j
                for j = 1, #spawnedHandles do
                    if j ~= currentVariantIndex and IsValid(spawnedHandles[j]) then enemy = spawnedHandles[j]; break end
                end
                if enemy and IsValid(enemy) then Attack(h, enemy, 1); print(string.format("[LCWALK][%s][%s] ACTION haim Attack %s", tostring(selectedCase), walkerVariants[currentVariantIndex], tostring(enemy))) end
            elseif selectedCase == "vaim" and IsValid(h) then
                local enemy = nil
                for j = 1, #spawnedHandles do if j ~= currentVariantIndex and IsValid(spawnedHandles[j]) then enemy = spawnedHandles[j]; break end end
                if enemy then Attack(h, enemy, 1); print(string.format("[LCWALK][%s][%s] ACTION vaim Attack", tostring(selectedCase), walkerVariants[currentVariantIndex])) end
            elseif selectedCase == "movaim" and IsValid(h) then
                Goto(h, GetPositionNear(GetPosition(h), 60, 70))
                print(string.format("[LCWALK][%s][%s] ACTION movaim Goto", tostring(selectedCase), walkerVariants[currentVariantIndex]))
            elseif selectedCase == "fire" and IsValid(h) then
                local enemy = nil
                for j = 1, #spawnedHandles do if j ~= currentVariantIndex and IsValid(spawnedHandles[j]) then enemy = spawnedHandles[j]; break end end
                if enemy then Attack(h, enemy, 1); print(string.format("[LCWALK][%s][%s] ACTION fire Attack", tostring(selectedCase), walkerVariants[currentVariantIndex])) end
            elseif selectedCase == "enter" and IsValid(h) then
                print(string.format("[LCWALK][%s][%s] ENTER SetAsUser already done — capturing FPV entry transition", tostring(selectedCase), walkerVariants[currentVariantIndex]))
            elseif selectedCase == "leave" and IsValid(h) then
                print(string.format("[LCWALK][%s][%s] LEAVE will hop at 2s", tostring(selectedCase), walkerVariants[currentVariantIndex]))
            elseif selectedCase == "switch" and IsValid(h) then
                print(string.format("[LCWALK][%s][%s] SWITCH variant %d/%d", tostring(selectedCase), walkerVariants[currentVariantIndex], currentVariantIndex, #walkerVariants))
            end
            subStage = 1
        end
        if selectedCase == "movaim" and variantTime >= 1.5 and variantTime < 1.6 and subStage == 1 then
            local enemy = nil
            for j = 1, #spawnedHandles do if j ~= currentVariantIndex and IsValid(spawnedHandles[j]) then enemy = spawnedHandles[j]; break end end
            if IsValid(h) and IsValid(enemy) then Attack(h, enemy, 1); print(string.format("[LCWALK][%s][%s] ACTION movaim Attack delayed", tostring(selectedCase), walkerVariants[currentVariantIndex])) end
            subStage = 2
        end
        if selectedCase == "leave" and variantTime >= 2.0 and variantTime < 2.1 then
            -- Explicit SetAsUser transition walker -> next vehicle (or back to first)
            local nextIdx = currentVariantIndex % #walkerVariants + 1
            local nextHandle = spawnedHandles[nextIdx]
            print(string.format("[LCWALK][%s][%s] LEAVE SetAsUser transition %s -> %s", tostring(selectedCase), walkerVariants[currentVariantIndex], tostring(h), tostring(nextHandle)))
            TrySetAsUser(nextHandle)
        end
        if selectedCase == "switch" and variantTime >= 1.0 and variantTime < 1.1 and subStage == 1 then
            -- For switch case, explicitly exercise SetAsUser(old->walker) and walker->next already handled by variant loop;
            -- here we do an extra intra-case hop to test stale parent retention.
            local other = controlHandle
            if walkerVariants[currentVariantIndex] == "avtank" then other = walkerHandles[1] end
            print(string.format("[LCWALK][%s][%s] SWITCH intra-case hop to %s", tostring(selectedCase), walkerVariants[currentVariantIndex], tostring(other)))
            TrySetAsUser(other)
            subStage = 2
        end
        if selectedCase == "switch" and variantTime >= 2.0 and variantTime < 2.1 and subStage == 2 then
            -- Hop back
            TrySetAsUser(h)
            subStage = 3
        end

        -- Variant duration: 4 seconds per walker (enough for stat idle, fwd accel, slope climb, etc.)
        -- For switch/leave we use same duration but with extra hops inside.
        local variantDuration = 4.0
        if selectedCase == "stat" then variantDuration = 3.0 end
        if holdVariant ~= nil then variantDuration = 1e9 end
        if variantTime >= variantDuration then
            SnapshotDetailed("VARIANT_RESULT")
            print(string.format("[LCWALK][%s][%s] VARIANT_COMPLETE variant=%d/%d time=%.2f", tostring(selectedCase), walkerVariants[currentVariantIndex], currentVariantIndex, #walkerVariants, variantTime))
            -- Capture several frames before next transition — already done via POLL
            -- Move to next walker variant, or finish
            if currentVariantIndex < #walkerVariants then
                -- Explicit SetAsUser transition: old -> new, capturing several frames before/after
                local oldHandle = activeWalker
                local oldOdf = "nil"
                if IsValid(oldHandle) then local ok, odf = pcall(GetOdf, oldHandle); if ok then oldOdf = Sanitize(odf) end end
                currentVariantIndex = currentVariantIndex + 1
                activeWalker = spawnedHandles[currentVariantIndex]
                local newOdf = "nil"
                if IsValid(activeWalker) then local ok, odf = pcall(GetOdf, activeWalker); if ok then newOdf = Sanitize(odf) end end
                print(string.format("[LCWALK][%s] TRANSITION %s (%s) -> %s (%s) elapsed=%.3f", tostring(selectedCase), tostring(oldHandle), oldOdf, tostring(activeWalker), newOdf, elapsed))
                -- Snapshot before transition
                SnapshotDetailed("PRE_TRANSITION")
                TrySetAsUser(activeWalker)
                -- Snapshot immediately after
                SnapshotDetailed("POST_TRANSITION")
                caseStartElapsed = elapsed
                subStage = 0
                lastPos = nil -- reset delta baseline for next variant
                -- Allow 0.4s stabilization already via transitionLogBudget
            else
                -- All variants done for this case
                print(string.format("[LCWALK][%s] ALL_VARIANTS_COMPLETE case=%s elapsed=%.3f", tostring(selectedCase), tostring(selectedCase), elapsed))
                SnapshotDetailed("RESULT")
                print(string.format("[LCWALK][%s] COMPLETE elapsed=%.3f variants=%d", tostring(selectedCase), elapsed, #walkerVariants))
                FailMission(GetTime() + 0.5)
                stage = 2
            end
        end
    end
end

function CreateObject(h) print(string.format("[LCWALK] CreateObject h=%s", tostring(h))) end
function AddObject(h) print(string.format("[LCWALK] AddObject h=%s", tostring(h))) end
function DeleteObject(h) print(string.format("[LCWALK] DeleteObject h=%s", tostring(h))) end
function CreatePlayer(id, name, team) print(string.format("[LCWALK] CreatePlayer id=%s team=%s", tostring(id), tostring(team))) end
function AddPlayer(id, name, team) print(string.format("[LCWALK] AddPlayer id=%s team=%s", tostring(id), tostring(team))) end
function DeletePlayer(id, name, team) print(string.format("[LCWALK] DeletePlayer id=%s team=%s", tostring(id), tostring(team))) end
