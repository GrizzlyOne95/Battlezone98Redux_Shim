-- Offline harness for lcbveg.lua.
--
-- Stubs the engine globals the mission uses and runs Start()/Update() against a
-- synthetic valley, so the mission can be exercised without launching the game.
--
-- It exists because the first live run died on
--   bad argument #3 to 'min' (number expected, got boolean)
-- which is the Lua multiple-return trap: GetODF* return (value, found), and a
-- bare `return GetODFInt(...)` propagates both, so `math.min(12, Int(...))`
-- expanded to `math.min(12, 5, true)`. The stubs below deliberately return TWO
-- values for exactly that reason -- a harness whose stubs return one value
-- cannot catch the bug the real engine exposes.
--
--   lua Test-LcbVeg.lua [path/to/lcbveg.lua]

local target = arg and arg[1] or "lcbveg.lua"

local failures = 0
local function check(condition, what)
    if condition then
        print("  ok  : " .. what)
    else
        print("  FAIL: " .. what)
        failures = failures + 1
    end
end

-- ------------------------------------------------------------------ config --

local CONFIG = {
    scenario = "ladder",
    mesh = "crgrass.mesh",
    material = "CR/GrassPrototype",
    radius = 45.0, density = 0.35, seed = 1001,
    steps = 5, densityMin = 0.05, densityMax = 0.80,
    stepRadius = 30.0, stepSpacing = 85.0, firstDistance = 70.0,
    minScale = 0.80, maxScale = 1.40, slopeMax = 22.0, baseOffset = 0.02,
    renderingDistance = 0.0, castShadows = 0, maxInstances = 8192,
    restrictToTerrainTypes = 1, terrainTypes = "0", matFile = "lcbveg.mat",
    worldMinX = 0.0, worldMinZ = 0.0,
    calibrationSamples = 16, riverFraction = 0.12,
    treeFraction = 0.55, rockSlopeDegrees = 26.0,
}

-- Two return values, like the engine. This is the whole point of the harness.
function OpenODF(name) return { name = name } end
function GetODFString(_, _, key, fallback)
    local v = CONFIG[key]
    if v == nil then return fallback, false end
    return tostring(v), true
end
function GetODFInt(_, _, key, fallback)
    local v = tonumber(CONFIG[key])
    if v == nil then return fallback, false end
    return math.floor(v), true
end
function GetODFFloat(_, _, key, fallback)
    local v = tonumber(CONFIG[key])
    if v == nil then return fallback, false end
    return v + 0.0, true
end

-- ----------------------------------------------------------------- terrain --

local WORLD = 5120.0

-- A valley of the same shape Make-VegBenchTerrain.py builds: a channel
-- meandering in z, rolling ground either side, steep rim at the edges.
local function TerrainHeight(x, z)
    local u, v = x / WORLD, z / WORLD
    local meander = 0.5 + 0.13 * math.sin(u * math.pi * 2 * 1.15)
    local d = math.abs(v - meander)
    local carve = math.max(0.0, math.min(1.0, (0.075 - d) / (0.075 - 0.022)))
    if d <= 0.022 then carve = 1.0 end
    carve = carve * carve * (3.0 - 2.0 * carve)
    local base = 0.5 + 0.5 * math.sin(u * math.pi * 2 * 1.3) * math.cos(v * math.pi * 2 * 0.9)
    local edge = math.max(math.max((0.09 - u) / 0.09, (u - 0.91) / 0.09),
                          math.max((0.09 - v) / 0.09, (v - 0.91) / 0.09))
    edge = math.max(0.0, math.min(1.0, edge))
    local h = 86.0 + base * 110.0 + edge * edge * 380.0
    return h * (1.0 - carve) + 12.0 * carve
end

function GetTerrainHeightAndNormal(p)
    local h = TerrainHeight(p.x, p.z)
    local e = 2.0
    local dx = (TerrainHeight(p.x + e, p.z) - TerrainHeight(p.x - e, p.z)) / (2 * e)
    local dz = (TerrainHeight(p.x, p.z + e) - TerrainHeight(p.x, p.z - e)) / (2 * e)
    local len = math.sqrt(dx * dx + 1.0 + dz * dz)
    return h, { x = -dx / len, y = 1.0 / len, z = -dz / len }
end

function SetVector(x, y, z) return { x = x, y = y, z = z } end
function GetPlayerHandle() return 1 end
function GetPosition() return { x = 2560.0, y = 100.0, z = 2560.0 } end
function GetFront() return { x = 1.0, y = 0.0, z = 0.0 } end

-- ------------------------------------------------------------ native stubs --

local created = {}
local exuStub = {
    CreateStaticGeometry = function(name, mesh, material, instances)
        created[#created + 1] = {
            name = name, mesh = mesh, material = material,
            count = #instances, instances = instances,
        }
        return { instanceCount = #instances, regionCount = 1, buildMilliseconds = 0 }
    end,
    DestroyAllStaticGeometry = function() return 0 end,
}

-- No bzfile and no TerrainClutter, which is the real addon-launch situation:
-- both live inside the CR mod folder and an addon mission gets neither.
local realRequire = require
function require(name)
    if name == "exu" then return exuStub end
    error("module '" .. name .. "' not found", 2)
end

-- ------------------------------------------------------------------- drive --

print("running " .. target)
local chunk = assert(loadfile(target))
chunk()
require = realRequire

local okStart, startErr = pcall(Start)
check(okStart, "Start() runs without error" ..
    (okStart and "" or (" -- " .. tostring(startErr))))
if not okStart then
    print("FAILURES: " .. failures)
    os.exit(1)
end

local okUpdate, updateErr = pcall(Update, 0.05)
check(okUpdate, "Update() runs without error" ..
    (okUpdate and "" or (" -- " .. tostring(updateErr))))

check(#created == 5, "ladder built 5 layers (got " .. #created .. ")")

local total = 0
for i = 1, #created do total = total + created[i].count end
check(total > 0, "placed some instances (got " .. total .. ")")

-- Density must actually increase along the ladder, or the whole point of the
-- scenario is lost.
local increasing = #created > 1
for i = 2, #created do
    if created[i].count <= created[i - 1].count then increasing = false end
end
check(increasing, "instance count increases across the ladder")

-- The reason terrain filtering exists: nothing in the water.
local inRiver = 0
for i = 1, #created do
    for j = 1, #created[i].instances do
        local p = created[i].instances[j].position
        local h = TerrainHeight(p.x, p.z)
        if h < 30.0 then inRiver = inRiver + 1 end
    end
end
check(inRiver == 0, "no blades placed in the river channel (got " .. inRiver .. ")")

for i = 1, #created do
    check(created[i].mesh == CONFIG.mesh and created[i].material == CONFIG.material,
        "layer " .. i .. " used the configured mesh and material")
end

print(failures == 0 and "ALL PASS" or ("FAILURES: " .. failures))
os.exit(failures == 0 and 0 or 1)
