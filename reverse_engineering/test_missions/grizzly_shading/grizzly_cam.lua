-- Fixture for lcbworld/lcbmars.lua (or any lcb*.lua): spawns one stock avtank
-- Grizzly ahead of the player and runs a cinematic camera through four orbit
-- stations, logging "[GRZ] phase N" so the capture script can time shots.
local elapsed, ready, grz, phase = 0, false, nil, 0
local PHASE_LEN = 10
-- {right, up, forward} in centimetres, local to the tank, looking at the tank.
local STATIONS = {
    {  420, 170,   620 },  -- 1 front 3/4 close (~7.6 m)
    {  800, 300,  1200 },  -- 2 front 3/4 far   (~14.5 m)
    { -420, 170,  -620 },  -- 3 rear 3/4 close
    { -800, 300, -1200 },  -- 4 rear 3/4 far
}
function Start() print("[GRZ] start") end
function Update(dt)
    elapsed = elapsed + (dt or 0)
    local p = GetPlayerHandle()
    if not p or not IsValid(p) then return end
    if not ready and elapsed > 4 then
        local pos = GetPosition(p)
        SetMaxHealth(p, 100000) SetCurHealth(p, 100000)
        grz = BuildObject("avtank", 1, SetVector(pos.x + 30, pos.y, pos.z + 30))
        SetMaxHealth(grz, 100000) SetCurHealth(grz, 100000)
        Stop(grz, 1)
        CameraReady()
        ready = true
        print("[GRZ] spawned grizzly=" .. tostring(grz))
        return
    end
    if ready then
        local want = math.floor((elapsed - 4) / PHASE_LEN) + 1
        if want > #STATIONS then want = #STATIONS end
        if want ~= phase then phase = want print("[GRZ] phase " .. phase) end
        local s = STATIONS[phase]
        CameraObject(grz, s[1], s[2], s[3], grz)
    end
end
function CreateObject(h) end
function AddObject(h) end
function DeleteObject(h) end
