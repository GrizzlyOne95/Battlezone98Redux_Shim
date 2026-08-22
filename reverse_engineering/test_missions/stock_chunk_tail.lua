-- Controlled stock destruction tail for native renderer profiling.
--
-- Deploy beside a copied .bzn with the same basename. The donor map supplies
-- terrain and the player craft; this script owns the test objects and performs
-- one destruction burst, followed by an idle observation window.

local spawned = {}
local elapsed = 0.0
local destroyed = false
local tailMarkers = {
    { seconds = 2.0, label = "alpha-effects-active" },
    { seconds = 5.0, label = "short-effects-expired" },
    { seconds = 10.0, label = "persistent-debris-tail" },
    { seconds = 20.0, label = "long-idle-tail" },
}
local nextTailMarker = 1

local function trace(message)
    print(string.format("[STOCK_CHUNK_TAIL] t=%.3f %s", elapsed, message))
end

local function spawnTestGroup()
    local player = GetPlayerHandle()
    if not IsValid(player) then
        trace("ERROR player handle unavailable")
        return
    end

    local transform = GetTransform(player)
    local playerPos = GetPosition(player)
    local frontX = transform.front_x or 0.0
    local frontZ = transform.front_z or 1.0
    local rightX = transform.right_x or 1.0
    local rightZ = transform.right_z or 0.0

    -- Seven staggered rows of eight craft keep the burst visible while
    -- producing a sustained CPU-side submission tail on fast modern systems.
    -- svtank is a known positive control for full native fragmentation.
    for row = 0, 6 do
        for column = 0, 7 do
            local forward = 34.0 + row * 9.0
            local lateral = (column - 3.5) * 8.0
            local x = playerPos.x + frontX * forward + rightX * lateral
            local z = playerPos.z + frontZ * forward + rightZ * lateral
            -- BuildObject settles craft onto the terrain; keeping the player's
            -- current height avoids depending on optional terrain-query APIs.
            local y = playerPos.y
            local handle = BuildObject("svtank", 2, SetVector(x, y, z))
            if IsValid(handle) then
                SetIndependence(handle, 0)
                spawned[#spawned + 1] = handle
            end
        end
    end

    trace(string.format("spawned=%d odf=svtank", #spawned))
end

function Start()
    trace("start")
    spawnTestGroup()
    trace("baseline-window-begin")
end

function Update(dt)
    elapsed = elapsed + (dt or 0.0)

    if not destroyed and elapsed >= 3.0 then
        destroyed = true
        trace(string.format("destroy-begin count=%d", #spawned))
        for _, handle in ipairs(spawned) do
            if IsValid(handle) then
                Damage(handle, 1000000)
            end
        end
        trace("destroy-complete idle-tail-begin")
    end

    if destroyed then
        local tailElapsed = elapsed - 3.0
        while nextTailMarker <= #tailMarkers and
              tailElapsed >= tailMarkers[nextTailMarker].seconds do
            trace(tailMarkers[nextTailMarker].label)
            nextTailMarker = nextTailMarker + 1
        end
    end
end
