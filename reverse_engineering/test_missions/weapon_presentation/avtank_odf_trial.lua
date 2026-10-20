-- Temporary lcbench.lua fixture for the GOG ODF presentation trial.
-- Requires the prepared avtank/gatstab overrides, matching EXU on Lua's DLL
-- search path, and mod-owned flash resources. Launch/stop with BZRHarness.
-- No Lua flash producer: all flashes must originate from the native ODF hook.
local elapsed, ready, nextReport = 0, false, 0
local shooter, target, exu

function Start()
    exu = require("exu")
    print("[ODFTRIAL] EXU loaded")
end

function Update(dt)
    elapsed = elapsed + (dt or 0)
    local player = GetPlayerHandle()
    if not player or not IsValid(player) then return end
    if not ready and elapsed > 2 then
        local pos = GetPosition(player)
        SetMaxHealth(player, 100000)
        SetCurHealth(player, 100000)
        shooter = BuildObject("avtank", 1, SetVector(pos.x + 8, pos.y, pos.z + 25))
        target = BuildObject("svtank", 2, SetVector(pos.x + 8, pos.y, pos.z + 65))
        SetMaxHealth(shooter, 100000)
        SetCurHealth(shooter, 100000)
        SetMaxAmmo(shooter, 100000)
        SetCurAmmo(shooter, 100000)
        SetMaxHealth(target, 100000)
        SetCurHealth(target, 100000)
        SetIndependence(target, 0)
        Stop(target, 1)
        SetWeaponMask(shooter, 1)
        Attack(shooter, target, 1)
        SetIndependence(shooter, 1)
        CameraReady()
        ready = true
        print("[ODFTRIAL] SHOOTER=" .. tostring(shooter) .. " TARGET=" .. tostring(target))
    end
    if ready then
        CameraObject(shooter, 800, 300, 900, shooter)
        SetCurHealth(target, 100000)
        SetCurAmmo(shooter, 100000)
    end
    if elapsed >= nextReport then
        nextReport = elapsed + 2
        local stats = exu.flash.GetStats()
        print(string.format("[ODFTRIAL] t=%.2f spawned=%s live=%s expired=%s failed=%s",
            elapsed, tostring(stats.spawned), tostring(stats.live),
            tostring(stats.expired), tostring(stats.failed)))
    end
end

function CreateObject(h) end
function AddObject(h) end
function DeleteObject(h) end
