-- Vegetation and water bench for GOG BZR 2.2.301, on Achilles.
--
-- lcbench's shape, a different question. lcbench holds a scene fixed and
-- measures frame cost; this holds a scene fixed and asks what ground content
-- LOOKS like. No combat, no spawning, nothing moving.
--
-- Achilles because it is the only vegetated world Redux ships: its terrain
-- types are authored as grass, trees, rocky rock, river, waterfall and base.
-- Grass on Moon can be proven present but never proven to look right, which is
-- why misn02b was the wrong place to judge it.
--
-- Everything is read from lcbvcfg.odf at Start(). Edit that and relaunch: no
-- rebuild, no redeploy.

local MODULUS = 2147483647
local MULTIPLIER = 48271

-- .mat geometry. 4x4 zones of 64x64 cells, two bytes per cell, stored zone by
-- zone: zone_z outer, zone_x inner, and local z outer, local x inner within
-- each zone. It is NOT a flat row-major grid, and treating it as one produces
-- a map that looks almost right and is scrambled across zone boundaries.
local MAT_ZONES = 4
local MAT_ZONE_CELLS = 64
local MAT_DIM = MAT_ZONES * MAT_ZONE_CELLS      -- 256 cells per side
local WORLD_SIZE = 5120.0                       -- must match [Size] in the .trn
local UNITS_PER_CELL = WORLD_SIZE / MAT_DIM     -- 20 world units

-- Achilles material numbering, from its own .trn section comments.
local MATERIAL_NAMES = {
    [0] = "grass", [1] = "trees", [2] = "rocky",
    [3] = "river", [4] = "waterfall", [5] = "base", [7] = "ambiguous",
}

-- Campaign Reimagined's Workshop id. exu.dll, bzfile.dll and TerrainClutter.lua
-- all live in its mod folder; exu.dll is also in the game root.
local CR_WORKSHOP_ID = "3686673790"

-- Extend the Lua search paths before requiring anything.
--
-- An addon mission gets neither the game root nor any mod folder on
-- package.path/cpath, so `require("exu")` fails outright -- and EXU is not
-- optional here, CreateStaticGeometry is a native export with no Lua
-- equivalent. The first run of this mission placed nothing for exactly that
-- reason, reporting "EXU StaticGeometry API is unavailable" five times.
--
-- Deriving the game directory from package.cpath is the community RequireFix
-- technique (DivisionByZero, GrizzlyOne95, VTrider), which exists for this
-- precise problem. Reimplemented compactly here rather than depending on
-- another addon's copy of it.
local pathNotes = {}
local gameRoot = nil

local function ExtendSearchPaths()
    if type(package) ~= "table" or type(package.cpath) ~= "string" then
        pathNotes[#pathNotes + 1] = "package.cpath unavailable; paths untouched"
        return
    end

    local entries = {}
    for entry in string.gmatch(package.cpath, "([^;]+)") do
        entries[#entries + 1] = entry
    end
    -- RequireFix reads entry 2; fall back to the first that yields a directory
    -- so this does not break if the engine ever reorders them.
    local gameDir = nil
    for _, index in ipairs({ 2, 1, 3 }) do
        local entry = entries[index]
        if entry then
            local dir = string.match(entry, "(.*)\\%?")
            if dir and dir ~= "" then
                gameDir = dir
                break
            end
        end
    end
    if not gameDir then
        pathNotes[#pathNotes + 1] = "could not derive the game directory from package.cpath"
        return
    end

    -- ORDER MATTERS, and getting it wrong is silent. There are two exu.dll on
    -- a normal install: the game root ships one, and CR's mod folder ships the
    -- one CR is actually built against. On this machine the root copy is
    -- 886272 bytes and does NOT export CreateStaticGeometry, while CR's is
    -- 907776 bytes and does. With the root searched first, require("exu")
    -- SUCCEEDS and hands back a module missing the one function this mission
    -- needs -- so nothing reports a load failure and five layers just quietly
    -- refuse to build. CR's copy goes first.
    local roots = {
        gameDir .. "\\mods\\" .. CR_WORKSHOP_ID,
        gameDir .. "\\packaged_mods\\" .. CR_WORKSHOP_ID,
        gameDir,                                -- last resort, and often stale
    }
    -- PREPEND, not append. The game root is ALREADY on package.cpath -- that is
    -- precisely how gameDir was derived above -- so appending leaves the root's
    -- stale exu.dll earlier in the search order and it keeps winning. Position
    -- within cpath is the whole mechanism; adding a path that is searched last
    -- achieves nothing when a wrong answer is found first.
    local dllPrefix, luaPrefix = "", ""
    for i = 1, #roots do
        dllPrefix = dllPrefix .. roots[i] .. "\\?.dll;"
        luaPrefix = luaPrefix .. roots[i] .. "\\?.lua;"
    end
    package.cpath = dllPrefix .. package.cpath
    package.path = luaPrefix .. package.path
    gameRoot = gameDir
    pathNotes[#pathNotes + 1] = "search paths extended from " .. gameDir
end

ExtendSearchPaths()

local okExu, exu = pcall(require, "exu")
if not okExu then
    pathNotes[#pathNotes + 1] = "require('exu') failed: " .. tostring(exu)
    exu = nil
elseif type(exu) ~= "table" or type(exu.CreateStaticGeometry) ~= "function" then
    -- Loaded, but not the build we need. "require succeeded" and "the module
    -- works" are different claims, and conflating them cost a round trip.
    --
    -- The usual cause is that something required exu before this script ran.
    -- require() caches in package.loaded, and a cached module ignores any
    -- later cpath change however it is ordered -- so prepending CR's folder
    -- cannot help on its own. Drop the cached entry and ask again.
    pathNotes[#pathNotes + 1] =
        "exu had no CreateStaticGeometry (the game root ships a build that " ..
        "predates it); dropping the cached module and reloading with CR's " ..
        "copy first"
    package.loaded.exu = nil
    local okRetry, retry = pcall(require, "exu")
    if okRetry and type(retry) == "table" and
        type(retry.CreateStaticGeometry) == "function" then
        exu = retry
        pathNotes[#pathNotes + 1] = "reload gave a build with CreateStaticGeometry"
    else
        exu = (okRetry and type(retry) == "table") and retry or exu
        pathNotes[#pathNotes + 1] =
            "reload did NOT help -- the exu.dll in mods\\" .. CR_WORKSHOP_ID ..
            " is the only one with CreateStaticGeometry, so check it is there"
    end
end

local okBzfile, bzfile = pcall(require, "bzfile")
if not okBzfile then
    bzfile = nil
end

local state = {
    reported = false,
    placement = "none",
    terrain = "none",
    layers = {},
    notes = {},
    refusal = nil,
    mat = nil,
    bands = nil,
    diagnosed = false,
    minX = 0.0,
    minZ = 0.0,
}

local function Log(message)
    print("[lcbveg] " .. tostring(message))
end

local function Note(message)
    state.notes[#state.notes + 1] = message
end

local function IsFinite(value)
    return type(value) == "number" and value == value and math.abs(value) < math.huge
end

-- The same LCG as CR's TerrainClutter, so a seed placed by the fallback lands
-- where the same seed placed by CR would.
local function NewRandom(seed)
    local seedState = math.floor(math.abs(tonumber(seed) or 1)) % (MODULUS - 1) + 1
    return function()
        seedState = (seedState * MULTIPLIER) % MODULUS
        return seedState / MODULUS
    end
end

-- ---------------------------------------------------------------- terrain --

-- Load the whole .mat once. It is 128 KiB, it never changes during a mission,
-- and one read beats 2227 of them.
local function LoadMat(name)
    if not (bzfile and type(bzfile.Open) == "function") then
        return nil, "bzfile is unavailable"
    end
    local candidates = { name }
    if gameRoot then
        candidates[#candidates + 1] = gameRoot .. "\\addon\\lcbveg\\" .. name
    end
    local handle = nil
    for i = 1, #candidates do
        local opened = bzfile.Open(candidates[i], "rb")
        if opened then
            handle = opened
            break
        end
    end
    if not handle then
        return nil, "could not open " .. tostring(name) ..
            " (tried " .. #candidates .. " path(s))"
    end
    local expected = MAT_DIM * MAT_DIM * 2
    local payload = handle:Read(expected)
    if type(handle.Close) == "function" then
        pcall(handle.Close, handle)
    end
    if type(payload) ~= "string" then
        return nil, "read returned no data"
    end
    if #payload ~= expected then
        return nil, string.format("read %d bytes, wanted %d", #payload, expected)
    end
    return payload
end

-- Fallback classifier, used when the .mat cannot be read.
--
-- ExtendSearchPaths above should make bzfile reachable, but it depends on
-- deriving the game directory from package.cpath and on CR being installed at
-- the expected id. When either does not hold there is still no file I/O at
-- all, so rather than silently drop terrain filtering, reconstruct it from the
-- terrain itself.
--
-- This works because the map's materials were painted FROM elevation and slope
-- in the first place (see paint_rules in Make-VegBenchTerrain.py), so the same
-- two quantities recover them. It self-calibrates against the map's own height
-- range instead of carrying a raw-to-world height constant, which is the part
-- that would otherwise have to be guessed.
local function CalibrateTerrainBands(samples)
    if type(GetTerrainHeightAndNormal) ~= "function" then
        return nil
    end
    local step = WORLD_SIZE / samples
    local low, high = nil, nil
    for iz = 0, samples - 1 do
        for ix = 0, samples - 1 do
            local probe = SetVector(state.minX + (ix + 0.5) * step, 0.0,
                                    state.minZ + (iz + 0.5) * step)
            local ok, height = pcall(GetTerrainHeightAndNormal, probe)
            if ok and IsFinite(height) then
                if not low or height < low then low = height end
                if not high or height > high then high = height end
            end
        end
    end
    if not low or not high or high <= low then
        return nil
    end
    return { low = low, high = high, range = high - low }
end

local function ClassifyFromTerrain(position)
    local bands = state.bands
    if not bands then
        return nil
    end
    local height, normal = nil, nil
    local ok, h, n = pcall(GetTerrainHeightAndNormal, position)
    if ok and IsFinite(h) and n and IsFinite(n.y) then
        height, normal = h, n
    else
        return nil
    end
    if height <= bands.low + bands.riverFraction * bands.range then
        return 3    -- river
    end
    local up = math.max(-1.0, math.min(1.0, normal.y))
    if (math.acos(up) * 180.0 / math.pi) >= bands.rockSlope then
        return 2    -- rocky rock
    end
    if height >= bands.low + bands.treeFraction * bands.range then
        return 1    -- trees
    end
    return 0        -- grass
end

-- World position -> the Base material of the cell under it, or nil off-map.
local function MaterialAt(position)
    local payload = state.mat
    if not payload then
        return ClassifyFromTerrain(position)
    end
    local cellX = math.floor((position.x - state.minX) / UNITS_PER_CELL)
    local cellZ = math.floor((position.z - state.minZ) / UNITS_PER_CELL)
    if cellX < 0 or cellX >= MAT_DIM or cellZ < 0 or cellZ >= MAT_DIM then
        return nil
    end

    local zoneX = math.floor(cellX / MAT_ZONE_CELLS)
    local zoneZ = math.floor(cellZ / MAT_ZONE_CELLS)
    local localX = cellX - zoneX * MAT_ZONE_CELLS
    local localZ = cellZ - zoneZ * MAT_ZONE_CELLS
    local index = (zoneZ * MAT_ZONES + zoneX) * (MAT_ZONE_CELLS * MAT_ZONE_CELLS)
        + localZ * MAT_ZONE_CELLS + localX

    -- Entry is a little-endian uint16; the second byte is (Base << 4) | Next.
    -- Base is the material the cell is made of; Next is what it transitions
    -- towards. Placement wants Base.
    local high = string.byte(payload, index * 2 + 2)
    if not high then
        return nil
    end
    return math.floor(high / 16)
end

-- ------------------------------------------------------------- placement --

local function SampleTerrain(position)
    if type(GetTerrainHeightAndNormal) ~= "function" then
        return nil
    end
    local ok, height, normal = pcall(GetTerrainHeightAndNormal, position)
    if not ok or not IsFinite(height) or normal == nil or not IsFinite(normal.y) then
        return nil
    end
    return height, normal
end

local function SlopeDegrees(normal)
    local up = math.max(-1.0, math.min(1.0, normal.y))
    return math.acos(up) * 180.0 / math.pi
end

-- Report exactly what the terrain API returns at one known point.
--
-- Both placers reject every candidate while an offline reproduction of the
-- same test over the same .hg2/.mat accepts ~99% of them, so the disagreement
-- is about what the engine hands back, not about the ground. Guessing at that
-- has now cost several round trips; this prints it.
--
-- The specific thing worth ruling out: CalibrateTerrainBands works and only
-- ever reads the FIRST return value, while both placers need normal.y. If the
-- engine returns the normal as three numbers rather than one vector, the
-- height path succeeds and every slope test silently fails.
local function DescribeTerrainApi(position)
    if type(GetTerrainHeightAndNormal) ~= "function" then
        return "GetTerrainHeightAndNormal is " .. type(GetTerrainHeightAndNormal)
    end
    local results = { pcall(GetTerrainHeightAndNormal, position) }
    if not results[1] then
        return "call raised: " .. tostring(results[2])
    end
    local parts = {}
    for index = 2, #results do
        local value = results[index]
        local shown = type(value)
        if type(value) == "number" then
            shown = string.format("number(%.3f)", value)
        elseif type(value) == "table" or type(value) == "userdata" then
            -- Vectors here are userdata, so field access goes through a
            -- metatable and may simply not be there. pcall it: the question
            -- "is this indexable" must not itself throw.
            local okIndex, x, y, z = pcall(function()
                return value.x, value.y, value.z
            end)
            if okIndex then
                shown = string.format("%s(x=%s y=%s z=%s)", type(value),
                    tostring(x), tostring(y), tostring(z))
            else
                shown = type(value) .. "(not indexable: " .. tostring(x) .. ")"
            end
        end
        parts[#parts + 1] = string.format("[%d]=%s", index - 1, shown)
    end
    return string.format("returned %d value(s): %s", #results - 1,
        table.concat(parts, " "))
end

-- Why a layer placed nothing, one sample at a time.
--
-- Both placers reject every candidate while an offline reproduction of the
-- same test over the same .hg2/.mat accepts ~99%. Narrowing that by hypothesis
-- has cost several round trips, so this just prints each filter's input and
-- verdict for a handful of points and lets the numbers say which one bites.
local function DiagnoseLayer(profile, samples)
    local random = NewRandom(profile.seed or 1)
    local lines = {}
    for attempt = 1, samples do
        local radius = profile.radius * math.sqrt(random())
        local angle = random() * math.pi * 2.0
        local x = profile.center.x + math.cos(angle) * radius
        local z = profile.center.z + math.sin(angle) * radius
        local probe = SetVector(x, profile.center.y, z)

        local okSample, height, normal = pcall(GetTerrainHeightAndNormal, probe)
        local normalY, slope = nil, nil
        if okSample and normal ~= nil then
            local okY, value = pcall(function() return normal.y end)
            if okY then normalY = value end
            if type(normalY) == "number" then
                local up = math.max(-1.0, math.min(1.0, normalY))
                slope = math.acos(up) * 180.0 / math.pi
            end
        end
        local material = MaterialAt(probe)
        local wanted = profile.terrainTypes and
            (material ~= nil and profile.terrainTypes[material] == true) or
            (profile.terrainTypes == nil)

        lines[#lines + 1] = string.format(
            "(%.0f,%.0f) call=%s height=%s normal=%s normal.y=%s slope=%s material=%s typeOk=%s slopeOk=%s",
            x, z, tostring(okSample), tostring(height), type(normal),
            tostring(normalY),
            slope and string.format("%.1f", slope) or "nil",
            tostring(material), tostring(wanted),
            tostring(slope ~= nil and slope <= (profile.slopeMax or 90.0)))
    end
    return lines
end

-- Used when CR's TerrainClutter is not reachable. Deliberately the same
-- rejection sampling CR performs, kept short: it exists so the mission still
-- shows something without CR, not as a second implementation to maintain.
local function BuildLayerDirect(profile)
    if not (exu and type(exu.CreateStaticGeometry) == "function") then
        return false, "EXU StaticGeometry API is unavailable"
    end

    local random = NewRandom(profile.seed or 1)
    local area = math.pi * profile.radius * profile.radius
    local target = math.max(1, math.floor(area * profile.density + 0.5))
    target = math.min(target, profile.maxInstances or 8192)
    local maxAttempts = math.max(target, target * 8)
    local instances = {}
    local attempts = 0
    local rejectedByMaterial = 0

    while #instances < target and attempts < maxAttempts do
        attempts = attempts + 1
        local radius = profile.radius * math.sqrt(random())
        local angle = random() * math.pi * 2.0
        local x = profile.center.x + math.cos(angle) * radius
        local z = profile.center.z + math.sin(angle) * radius
        local probe = SetVector(x, profile.center.y, z)
        local height, normal = SampleTerrain(probe)
        local accepted = height ~= nil and SlopeDegrees(normal) <= (profile.slopeMax or 90.0)

        if accepted and profile.terrainTypes then
            local material = MaterialAt(probe)
            if material == nil or profile.terrainTypes[material] ~= true then
                accepted = false
                rejectedByMaterial = rejectedByMaterial + 1
            end
        end

        if accepted then
            instances[#instances + 1] = {
                position = SetVector(x, height + (profile.baseOffset or 0.02), z),
                yaw = random() * math.pi * 2.0,
                scale = profile.minScale +
                    (profile.maxScale - profile.minScale) * random(),
            }
        end
    end

    if #instances == 0 then
        return false, "no valid terrain samples"
    end

    local info, err = exu.CreateStaticGeometry(
        profile.name, profile.mesh, profile.material, instances,
        {
            regionDimensions = { x = 64.0, y = 128.0, z = 64.0 },
            origin = profile.center,
            renderingDistance = profile.renderingDistance or 0.0,
            castShadows = profile.castShadows == true,
            visible = true,
        })
    if not info then
        return false, tostring(err)
    end
    info.instanceCount = info.instanceCount or #instances
    info.rejectedByMaterial = rejectedByMaterial
    return true, info
end

-- ------------------------------------------------------------------ start --

function Start()
    -- OpenODF is only safe once LuaMission startup has entered Start(), which
    -- is why none of this is read at module load.
    local config = OpenODF("lcbvcfg")
    -- The parentheses are load-bearing. GetODF* return TWO values, the value
    -- and whether the key was found. A bare `return GetODFInt(...)` propagates
    -- both, and in a trailing argument position Lua expands both -- so
    -- math.min(12, Int("steps", 5)) became math.min(12, 5, true) and threw
    -- "bad argument #3 to 'min' (number expected, got boolean)". Truncating
    -- here fixes every call site at once rather than one at a time.
    local function Str(key, fallback)
        return (GetODFString(config, "Vegetation", key, fallback))
    end
    local function Num(key, fallback)
        return (GetODFFloat(config, "Vegetation", key, fallback))
    end
    local function Int(key, fallback)
        return (GetODFInt(config, "Vegetation", key, fallback))
    end

    state.minX = Num("worldMinX", 0.0)
    state.minZ = Num("worldMinZ", 0.0)

    -- Terrain-type filtering. Without the .mat this degrades to slope-only
    -- placement rather than failing: grass in a river is a worse bench than no
    -- bench, but no bench at all is worse than both.
    local restrict = Int("restrictToTerrainTypes", 1) ~= 0
    local allowed = nil
    if restrict then
        local payload, matError = LoadMat(Str("matFile", "lcbveg.mat"))
        if payload then
            state.mat = payload
            state.terrain = "lcbveg.mat"
            allowed = {}
            local list = Str("terrainTypes", "0")
            for token in string.gmatch(list, "%d+") do
                allowed[tonumber(token)] = true
            end
        else
            -- No .mat: recover the materials from elevation and slope, which
            -- is what painted them in the first place.
            local samples = math.max(8, math.min(64, Int("calibrationSamples", 32)))
            local bands = CalibrateTerrainBands(samples)
            if bands then
                bands.riverFraction = Num("riverFraction", 0.12)
                bands.treeFraction = Num("treeFraction", 0.55)
                bands.rockSlope = Num("rockSlopeDegrees", 26.0)
                state.bands = bands
                allowed = {}
                for token in string.gmatch(Str("terrainTypes", "0"), "%d+") do
                    allowed[tonumber(token)] = true
                end
                state.terrain = string.format(
                    "derived from terrain (%s; height %.1f..%.1f over %d samples)",
                    tostring(matError), bands.low, bands.high, samples * samples)
                Note("no .mat (" .. tostring(matError) ..
                    "); classifying from elevation and slope instead")
            else
                state.terrain = "unavailable (" .. tostring(matError) .. ")"
                Note("terrain-type filtering is OFF: " .. tostring(matError))
            end
        end
    else
        state.terrain = "disabled by config"
    end

    local shared = {
        mesh = Str("mesh", "crgrass.mesh"),
        material = Str("material", "CR/GrassPrototype"),
        minScale = Num("minScale", 0.80),
        maxScale = Num("maxScale", 1.40),
        slopeMax = Num("slopeMax", 22.0),
        baseOffset = Num("baseOffset", 0.02),
        renderingDistance = Num("renderingDistance", 0.0),
        castShadows = Int("castShadows", 0) ~= 0,
        maxInstances = Int("maxInstances", 8192),
        terrainTypes = allowed,
    }

    -- Prefer CR's module: exercising CR's placement is the point. CR's
    -- BuildLayer already accepts terrainTypes plus a terrainTypeAt callback,
    -- and nothing has ever supplied one, so this is also the first exercise of
    -- that path. The fallback is a courtesy, and the log always says which ran.
    local placer = nil
    local okRequire, clutter = pcall(require, "TerrainClutter")
    if okRequire and type(clutter) == "table" and type(clutter.BuildLayer) == "function" then
        placer = function(profile)
            -- CR wants an ARRAY of accepted types plus a lookup, where this
            -- file carries a set. Convert on a copy: mutating the profile
            -- would leave the built-in placer, which wants the set, unable to
            -- retry the same profile.
            local forCr = {}
            for key, value in pairs(profile) do
                forCr[key] = value
            end
            if profile.terrainTypes then
                local list = {}
                for value in pairs(profile.terrainTypes) do
                    list[#list + 1] = value
                end
                forCr.terrainTypes = list
                forCr.terrainTypeAt = MaterialAt
            end
            return clutter.BuildLayer(forCr)
        end
        state.placement = "CR TerrainClutter"
    else
        placer = BuildLayerDirect
        state.placement = "built-in fallback (CR TerrainClutter not reachable)"
    end

    if exu and type(exu.DestroyAllStaticGeometry) == "function" then
        pcall(exu.DestroyAllStaticGeometry)
    end

    local scenario = string.lower(Str("scenario", "ladder") or "ladder")
    if scenario == "off" then
        state.refusal = "scenario=off: bare Achilles, no clutter placed"
        return
    end

    local player = GetPlayerHandle()
    if not player then
        state.refusal = "no player handle, nothing placed"
        return
    end
    local origin = GetPosition(player)
    if not (origin and IsFinite(origin.x)) then
        state.refusal = "player position unavailable, nothing placed"
        return
    end
    Note(string.format("spawn at (%.0f, %.0f) on %s", origin.x, origin.z,
        MATERIAL_NAMES[MaterialAt(origin) or -1] or "unknown terrain"))
    Note("GetTerrainHeightAndNormal at spawn " .. DescribeTerrainApi(origin))

    -- Direction for the ladder.
    --
    -- Facing is only a HINT. The spawn here looks straight down a wooded
    -- corridor, and with terrainTypes restricted to grass that put all five
    -- patches on ground the filter is obliged to reject -- five "no valid
    -- terrain samples" and an empty field, with nothing actually wrong.
    --
    -- So score the candidate bearings by how much of the ladder footprint
    -- lands on terrain the filter accepts, and only honour facing when it is
    -- competitive. This keeps the bench working when the spawn, the terrain or
    -- terrainTypes change, none of which should require re-aiming by hand.
    local function ScoreDirection(fx, fz, distances)
        local hits, total = 0, 0
        for i = 1, #distances do
            for offset = -1, 1 do
                local along = distances[i]
                local across = offset * 15.0
                local x = origin.x + fx * along - fz * across
                local z = origin.z + fz * along + fx * across
                total = total + 1
                local material = MaterialAt(SetVector(x, origin.y, z))
                if material ~= nil and
                    (allowed == nil or allowed[material] == true) then
                    hits = hits + 1
                end
            end
        end
        return hits / math.max(1, total)
    end

    local scanDistances = {}
    do
        local first = Num("firstDistance", 70.0)
        local spacing = Num("stepSpacing", 85.0)
        local steps = math.max(1, math.min(12, Int("steps", 5)))
        for index = 1, steps do
            scanDistances[index] = first + (index - 1) * spacing
        end
    end

    local forward = { x = 1.0, z = 0.0 }
    if type(GetFront) == "function" then
        local okFront, front = pcall(GetFront, player)
        if okFront and front and IsFinite(front.x) and IsFinite(front.z) then
            local length = math.sqrt(front.x * front.x + front.z * front.z)
            if length > 0.001 then
                forward = { x = front.x / length, z = front.z / length }
            end
        end
    end

    if Int("aimAtAcceptableGround", 1) ~= 0 then
        local facingScore = ScoreDirection(forward.x, forward.z, scanDistances)
        local best, bestScore = forward, facingScore
        for step = 0, 23 do
            local angle = step * math.pi / 12.0
            local fx, fz = math.cos(angle), math.sin(angle)
            local score = ScoreDirection(fx, fz, scanDistances)
            if score > bestScore then
                best, bestScore = { x = fx, z = fz }, score
            end
        end
        -- Prefer straight ahead when it is nearly as good: a ladder you have
        -- to turn around to see is worse than a slightly patchier one in view.
        if bestScore > facingScore + 0.05 then
            Note(string.format(
                "aimed away from facing: facing accepts %.0f percent of the ladder, chosen bearing accepts %.0f percent",
                facingScore * 100.0, bestScore * 100.0))
            forward = best
        else
            Note(string.format("using facing (accepts %.0f percent of the ladder)",
                facingScore * 100.0))
        end
    end

    local plan = {}
    if scenario == "single" then
        plan[1] = {
            name = "lcbveg_single",
            center = origin,
            radius = Num("radius", 45.0),
            density = Num("density", 0.35),
            seed = Int("seed", 1001),
        }
    elseif scenario == "ladder" then
        local steps = math.max(1, math.min(12, Int("steps", 5)))
        local densityMin = Num("densityMin", 0.05)
        local densityMax = Num("densityMax", 0.80)
        local stepRadius = Num("stepRadius", 30.0)
        local spacing = Num("stepSpacing", 85.0)
        local first = Num("firstDistance", 70.0)
        for index = 1, steps do
            -- Geometric, not linear. Density reads closer to logarithmic, so
            -- even steps bunch every interesting value into the first patch or
            -- two and waste the rest of the ladder.
            local t = (steps > 1) and ((index - 1) / (steps - 1)) or 0.0
            local density = densityMin
            if densityMin > 0.0 and densityMax > 0.0 then
                -- `^` rather than math.pow: math.pow was removed in Lua
                -- 5.3, and the operator works on every version.
                density = densityMin * (densityMax / densityMin) ^ t
            end
            local distance = first + (index - 1) * spacing
            plan[index] = {
                name = string.format("lcbveg_ladder_%d", index),
                center = SetVector(origin.x + forward.x * distance,
                                   origin.y,
                                   origin.z + forward.z * distance),
                radius = stepRadius,
                density = density,
                seed = 1000 + index,
            }
        end
    elseif scenario == "closeup" then
        -- Diagnostic scenario. Placement, the mesh, the material and the
        -- shaders all report success while nothing appears on screen, so this
        -- answers the two questions that separates in one launch:
        --
        --   is it drawn at all?   three fat patches at arm's length, at a
        --                         scale that cannot be missed
        --   is it buried?         the same three lifted 0.02, 3 and 10 units
        --                         above the terrain height the engine reports
        --
        -- If none appear, the problem is the material or the render path. If
        -- the lifted ones appear and the flush one does not, the height datum
        -- the sampler returns is not the one the terrain renders at.
        local lifts = { 0.02, 3.0, 10.0 }
        for index = 1, #lifts do
            local across = (index - 2) * 34.0
            plan[index] = {
                name = string.format("lcbveg_closeup_%d", index),
                center = SetVector(origin.x + forward.x * 35.0 - forward.z * across,
                                   origin.y,
                                   origin.z + forward.z * 35.0 + forward.x * across),
                radius = 14.0,
                density = 1.2,
                seed = 2000 + index,
                baseOffset = lifts[index],
                minScale = Num("closeupScale", 3.0),
                maxScale = Num("closeupScale", 3.0) * 1.25,
                -- No terrain filter: this is asking whether anything renders,
                -- and a type rejection here would confuse that answer with a
                -- placement one.
                terrainTypes = false,
            }
        end
    else
        state.refusal = string.format(
            "unknown scenario %s, expected ladder, single, closeup or off", scenario)
        return
    end

    for index = 1, #plan do
        local profile = plan[index]
        for key, value in pairs(shared) do
            if profile[key] == nil then
                profile[key] = value
            end
        end
        -- Each profile gets its own copy: the CR path rewrites terrainTypes
        -- from a set into an array, which would corrupt the next patch.
        if profile.terrainTypes == false then
            profile.terrainTypes = nil          -- explicitly unfiltered
        elseif allowed then
            local copy = {}
            for value in pairs(allowed) do
                copy[value] = true
            end
            profile.terrainTypes = copy
        end

        local ok, info = placer(profile)

        -- If CR's module placed nothing, try the built-in placer on the same
        -- profile before giving up.
        --
        -- This is not belt-and-braces, it is a diagnostic. The two placers run
        -- the same rejection sampling against the same terrain, so if CR's
        -- reports "no valid terrain samples" and this one then succeeds at the
        -- identical positions, the difference is not the terrain -- it is that
        -- a require()d module does not see the mission's engine globals, so
        -- CR's SampleTerrain finds no GetTerrainHeightAndNormal and rejects
        -- every candidate. The log says plainly which one produced the grass.
        local usedFallback = false
        local fallbackError = nil
        if not ok and placer ~= BuildLayerDirect then
            local retryOk, retryInfo = BuildLayerDirect(profile)
            if retryOk then
                ok, info, usedFallback = retryOk, retryInfo, true
            else
                -- Keep it. Discarding the second placer's error the first time
                -- round meant the log could not distinguish "CR failed and the
                -- fallback was never tried" from "both failed", which is
                -- exactly the distinction that mattered.
                fallbackError = tostring(retryInfo)
            end
        end

        -- Both placers refused this layer. Dump a few samples once, for the
        -- first such layer only: five identical dumps say nothing the first
        -- does not.
        if not ok and not state.diagnosed then
            state.diagnosed = true
            local lines = DiagnoseLayer(profile, 6)
            for i = 1, #lines do
                Note("sample " .. i .. ": " .. lines[i])
            end
        end

        local record = {
            name = profile.name,
            density = profile.density,
            radius = profile.radius,
            center = profile.center,
            count = 0,
            fallback = usedFallback,
            fallbackError = fallbackError,
        }
        if ok then
            record.count = (type(info) == "table" and info.instanceCount) or 0
        else
            record.error = tostring(info)
        end
        state.layers[#state.layers + 1] = record
    end
end

function Update(dt)
    if state.reported then
        return
    end
    state.reported = true

    Log("world=Achilles placement=" .. state.placement ..
        " terrain=" .. state.terrain)
    for index = 1, #pathNotes do
        Log("  " .. pathNotes[index])
    end
    for index = 1, #state.notes do
        Log("  " .. state.notes[index])
    end
    if state.refusal then
        Log(state.refusal)
        return
    end

    local total = 0
    for index = 1, #state.layers do
        local layer = state.layers[index]
        total = total + layer.count
        if layer.error then
            Log(string.format("  %-20s density=%.3f radius=%.0f FAILED: %s%s",
                layer.name, layer.density, layer.radius, layer.error,
                layer.fallbackError and
                    ("  | built-in placer also failed: " .. layer.fallbackError) or
                    "  | built-in placer was not tried"))
        else
            -- Spacing is the number that actually predicts whether it reads as
            -- ground cover. Density is the knob; spacing is the outcome.
            local spacing = 0.0
            if layer.count > 0 then
                spacing = math.sqrt((math.pi * layer.radius * layer.radius) / layer.count)
            end
            Log(string.format(
                "  %-20s density=%.3f radius=%.0f instances=%d spacing=%.2f at (%.0f, %.0f) on %s%s",
                layer.name, layer.density, layer.radius, layer.count, spacing,
                layer.center.x, layer.center.z,
                MATERIAL_NAMES[MaterialAt(layer.center) or -1] or "unknown",
                layer.fallback and "  [CR placer found nothing here; built-in did]" or ""))
        end
    end
    Log(string.format("total instances=%d across %d layer(s)", total, #state.layers))
end
