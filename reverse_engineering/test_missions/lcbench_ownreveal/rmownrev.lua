-- rmownrev.lua -- lcbench owned-object perceivedTeam reveal fixture (Splinter).
--
-- Deploy as addon/lcbench/lcbench.lua and launch
-- `battlezone98redux.exe lcbench.bzn` (bare basename: the engine truncates the
-- mission argument to 15 characters, so a path never survives).
--
-- Run it with the shim trace on:
--   set OPENSHIM_TRACE_OWNED_OBJECT_REVEAL=1
--   set OPENSHIM_TRACE_DAMAGE_REVEAL=1        (optional, much louder)
--
--
-- What this reproduces
-- --------------------
-- A disguised craft -- one whose perceivedTeam still reads the team it used to
-- belong to -- fires a Splinter. The Splinter's spawned child rounds damage
-- that former team, and the firing craft stays disguised: the victims never
-- retaliate and the player keeps a friendly IFF while killing them.
--
-- The reported repro reaches the disguised state by sniping or capturing a
-- team 2 tank. This fixture sets it directly with SetPerceivedTeam so the test
-- measures the reveal and not the capture mechanic, and so the "before" value
-- is a known constant rather than whatever the snipe happened to leave.
--
--
-- The ownership chain, from shipped ODFs and the shipped GOG image
-- ---------------------------------------------------------------
--   gsplint.odf   [WeaponClass] classLabel "mortar", ordName "splintbm"
--   splintbm.odf  [OrdnanceClass] classLabel "spraybomb", deployName "splintb2"
--   splintb2.odf  [SprayBuildingClass] payloadName "splinter"
--   splinter.odf  [OrdnanceClass] classLabel "tracer", damageBallistic 40
--
--   craft --gsplint--> splintbm      Ordnance::Init 0x00585292 stores the
--                                    firing craft's obj76 at ordnance +0xD8,
--                                    and damage.damager is that same obj76.
--   splintbm lands --> splintb2      SprayBomb::Hit 0x005DB080 builds it at
--                                    0x005DB37F via GameObjectClass::Build.
--                                    That call takes a transform and a TEAM and
--                                    nothing else: it never calls SetOwner, so
--                                    the emitter's ownerHandle (+0x224) is 0.
--                                    *** This is where the chain is severed. ***
--   splintb2 --------> splinter x N  SprayBuilding::Simulate 0x005DA6E0 calls
--                                    OrdnanceClass::Build(mat, emitter->obj76)
--                                    at 0x005DAB73, so every child records the
--                                    EMITTER as damage.damager, then forces
--                                    bSend = 0 at 0x005DAB84.
--   splinter hits ---> SetDamageFlags 0x004DC130 reveals damage.damager->gameObj
--                      (+0x8C), which is the emitter. The craft is never
--                      touched, in Redux and in stock BZ 1.5 alike.
--
-- So this is stock behaviour, not a Redux regression. OpenShim's fix relinks
-- the emitter to the firing craft and then walks GameObject::ownerHandle after
-- the hit lands.
--
--
-- What a correct run looks like
-- -----------------------------
-- With OwnedObjectReveal active, the shim log should show, in order:
--   [OWNREVEAL] action=link  kind=splinter-emitter ...   (once per Splinter)
--   [OWNREVEAL] action=write kind=damage-owner    ... pt=2->1
-- and this fixture's own [OWNREVEAL-FIXTURE] heartbeat should report
-- perceived flipping from 2 to the craft's real team on the first landed child
-- hit -- not on the shot, and not on a Splinter that lands nowhere near anyone.
--
-- A run that shows `action=stop kind=no-owner depth=1` for the emitter means
-- the relink did not happen: either the "Splinter Emitter Owner Propagation"
-- call-site patch is not installed (check patches.json in the GAME ROOT, which
-- deploys separately from winmm.dll) or the owner offset is wrong again.
--
--
-- Phases
-- ------
--   DISGUISE  set the player craft's perceivedTeam to ENEMY_TEAM
--   BASELINE  hold, hostile to nobody -- perceived must stay ENEMY_TEAM
--   SPLINTER  fire at the enemy group, children land, reveal expected
--   DRYFIRE   (separate run, DRY_FIRE_ONLY=true) fire into empty terrain --
--             nothing lands on anyone, so perceived must stay ENEMY_TEAM
--
-- Set DRY_FIRE_ONLY to true and re-run to get the non-damaging Splinter arm of
-- the matrix. It is a separate run on purpose: once the craft is revealed, the
-- negative case cannot be observed in the same life.

local ENEMY_TEAM       = 2
local ENEMY_COUNT      = 3
local ENEMY_ODF        = "avtank"
local ENEMY_SPREAD     = 12.0
local ENEMY_DISTANCE   = 70.0
local DRY_FIRE_TARGET  = 220.0   -- far enough that no child round reaches anyone

local DISGUISE_AT      = 2.0
local BASELINE_UNTIL   = 8.0
local FIRE_AT          = 9.0
local RUN_UNTIL        = 45.0
local HEARTBEAT_EVERY  = 1.0

local DRY_FIRE_ONLY    = false

local function Safe(fn, ...)
    local ok, result = pcall(fn, ...)
    if ok then return result end
    return nil
end

-- GetPerceivedTeam is a stock binding; guard it anyway so a build without it
-- degrades to "unknown" instead of aborting the mission chunk.
local function Perceived(handle)
    if handle == nil or not IsValid(handle) then return nil end
    return Safe(GetPerceivedTeam, handle)
end

local function Actual(handle)
    if handle == nil or not IsValid(handle) then return nil end
    return Safe(GetTeamNum, handle)
end

local function Describe(label, handle)
    if handle == nil or not IsValid(handle) then
        return string.format("%s=invalid", label)
    end
    return string.format("%s=%s actual=%s perceived=%s",
        label, tostring(handle), tostring(Actual(handle)), tostring(Perceived(handle)))
end

local function Vec(x, y, z)
    return Safe(SetVector, x, y, z)
end

function Start()
    elapsed        = 0.0
    player         = nil
    disguised      = false
    fired          = false
    revealed       = false
    revealAt       = nil
    enemies        = {}
    nextHeartbeat  = 0.0
    baselineHeld   = true

    Marker(string.format("START owned-object reveal fixture dryfire=%s",
                         tostring(DRY_FIRE_ONLY)))
end

local function SpawnEnemies(origin)
    for i = 1, ENEMY_COUNT do
        local where = Vec(origin.x + (i - 2) * ENEMY_SPREAD,
                          origin.y,
                          origin.z + ENEMY_DISTANCE)
        if where ~= nil then
            local h = Safe(BuildObject, ENEMY_ODF, ENEMY_TEAM, where)
            if h ~= nil then
                enemies[#enemies + 1] = h
                Marker(string.format("ENEMY_SPAWNED %s", Describe("enemy", h)))
            end
        end
    end
end

function Update(dt)
    elapsed = elapsed + (dt or 0.0)

    if player == nil then
        local h = Safe(GetPlayerHandle)
        if h ~= nil and IsValid(h) then
            player = h
            Marker(string.format("PLAYER_FOUND %s", Describe("player", player)))
            local p = Safe(GetPosition, player)
            if p ~= nil then SpawnEnemies(p) end
        end
        return
    end

    -- DISGUISE. This is the state a snipe or capture leaves behind: the craft
    -- belongs to the player's team but still reads as ENEMY_TEAM to everyone
    -- else's targeting and to the radar.
    if not disguised and elapsed >= DISGUISE_AT then
        Safe(SetPerceivedTeam, player, ENEMY_TEAM)
        disguised = true
        Marker(string.format("DISGUISED %s expected_perceived=%d",
                             Describe("player", player), ENEMY_TEAM))
    end

    -- BASELINE. Doing nothing hostile must not reveal anything.
    if disguised and not fired and elapsed < BASELINE_UNTIL then
        if Perceived(player) ~= ENEMY_TEAM and baselineHeld then
            baselineHeld = false
            Marker(string.format("BASELINE_FAIL revealed without firing %s",
                                 Describe("player", player)))
        end
    end

    -- SPLINTER. Aim at the enemy group, or far past it for the dry-fire arm.
    if disguised and not fired and elapsed >= FIRE_AT then
        local p = Safe(GetPosition, player)
        if p ~= nil then
            local reach = DRY_FIRE_ONLY and DRY_FIRE_TARGET or ENEMY_DISTANCE
            local aim = Vec(p.x, p.y, p.z + reach)
            if aim ~= nil then Safe(SetTarget, player, aim) end
        end
        -- The weapon has to be the Splinter itself; a cannon hit reveals through
        -- stock SetDamageFlags and would pass the test for the wrong reason.
        Safe(GiveWeapon, player, "gsplint")
        Safe(SetWeaponMask, player, 1)
        fired = true
        Marker(string.format("SPLINTER_FIRED dryfire=%s %s",
                             tostring(DRY_FIRE_ONLY), Describe("player", player)))
    end

    if disguised and not revealed then
        local pt = Perceived(player)
        if pt ~= nil and pt ~= ENEMY_TEAM then
            revealed = true
            revealAt = elapsed
            Marker(string.format("REVEALED t=%.2f %s", elapsed,
                                 Describe("player", player)))
        end
    end

    if elapsed >= nextHeartbeat then
        nextHeartbeat = elapsed + HEARTBEAT_EVERY
        local alive = 0
        for _, h in ipairs(enemies) do
            if h ~= nil and IsValid(h) then alive = alive + 1 end
        end
        Marker(string.format(
            "[OWNREVEAL-FIXTURE] t=%.1f %s fired=%s enemiesAlive=%d/%d",
            elapsed, Describe("player", player), tostring(fired),
            alive, ENEMY_COUNT))
    end

    if elapsed >= RUN_UNTIL then
        -- One line that states the arm's verdict, so a run can be scored
        -- without reading the whole log back.
        local verdict
        if DRY_FIRE_ONLY then
            verdict = revealed and "FAIL revealed on a Splinter that landed no damage"
                                or "PASS stayed disguised without landed damage"
        else
            verdict = revealed and string.format("PASS revealed at t=%.2f", revealAt or -1.0)
                                or "FAIL still disguised after landed child damage"
        end
        if not baselineHeld then
            verdict = verdict .. " (BASELINE also failed)"
        end
        Marker(string.format("RESULT %s -- %s", verdict, Describe("player", player)))
        Marker("END owned-object reveal fixture")
        RUN_UNTIL = math.huge
    end
end
