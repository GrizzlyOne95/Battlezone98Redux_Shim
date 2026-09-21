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

local okExu, exu = pcall(require, "exu")
if not okExu then
    exu = nil
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
    local handle = bzfile.Open(name, "rb")
    if not handle then
        return nil, "could not open " .. tostring(name)
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
-- bzfile.dll and TerrainClutter.lua both live inside the Campaign Reimagined
-- mod folder, and an addon mission does not get a mod's Lua search path or its
-- native modules -- so on a direct launch neither is reachable, whatever is
-- installed. Rather than silently drop terrain filtering, reconstruct it from
-- the terrain itself.
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
            if profile.terrainTypes then
                -- CR wants an array of accepted types plus a lookup.
                local list = {}
                for value in pairs(profile.terrainTypes) do
                    list[#list + 1] = value
                end
                profile.terrainTypes = list
                profile.terrainTypeAt = MaterialAt
            end
            return clutter.BuildLayer(profile)
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

    -- Along the player's facing, so the ladder is walked into rather than
    -- hunted for. GetFront is guarded: a missing one should cost the
    -- convenience, not the mission.
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
    else
        state.refusal = string.format(
            "unknown scenario %s, expected single, ladder or off", scenario)
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
        if allowed then
            local copy = {}
            for value in pairs(allowed) do
                copy[value] = true
            end
            profile.terrainTypes = copy
        end

        local ok, info = placer(profile)
        local record = {
            name = profile.name,
            density = profile.density,
            radius = profile.radius,
            center = profile.center,
            count = 0,
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
            Log(string.format("  %-20s density=%.3f radius=%.0f FAILED: %s",
                layer.name, layer.density, layer.radius, layer.error))
        else
            -- Spacing is the number that actually predicts whether it reads as
            -- ground cover. Density is the knob; spacing is the outcome.
            local spacing = 0.0
            if layer.count > 0 then
                spacing = math.sqrt((math.pi * layer.radius * layer.radius) / layer.count)
            end
            Log(string.format(
                "  %-20s density=%.3f radius=%.0f instances=%d spacing=%.2f at (%.0f, %.0f) on %s",
                layer.name, layer.density, layer.radius, layer.count, spacing,
                layer.center.x, layer.center.z,
                MATERIAL_NAMES[MaterialAt(layer.center) or -1] or "unknown"))
        end
    end
    Log(string.format("total instances=%d across %d layer(s)", total, #state.layers))
end
