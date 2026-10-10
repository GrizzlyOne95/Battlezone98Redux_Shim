-- Load-hitch probe: two of each target. The first destruction of a type pays
-- every first-use cost (mesh, texture, shader, chunk payload); the second
-- destruction of the same type is the warm control.
SetAIControl(2, false)
local names = {"ivsabr", "ivrecy", "ibcmmd", "fbcomm", "zvtnk"}
local order, targets, start, wave = {}, {}, 0, 0
function Start()
    local p = GetPosition(GetPlayerHandle())
    SetMaxHealth(GetPlayerHandle(), 10000000)
    SetCurHealth(GetPlayerHandle(), 10000000)
    for row = 1, 2 do
        for i, name in ipairs(names) do
            local h = BuildObject(name, 2, SetVector(p.x+(i-3)*32, p.y, p.z+95+(row-1)*70))
            if IsValid(h) then Stop(h) end
            targets[#targets+1] = h
            order[#order+1] = name .. (row == 1 and ":cold" or ":warm")
            print("[PIVOTPROBE] spawned "..name.." row="..row.." valid="..tostring(IsValid(h)))
        end
    end
    start = GetTime()
end
function Update(dt)
    local elapsed = GetTime()-start
    if wave < #targets and elapsed >= 6 + wave*5 then
        wave = wave+1
        if IsValid(targets[wave]) then Damage(targets[wave], GetMaxHealth(targets[wave])*2) end
        print("[PIVOTPROBE] destroyed "..order[wave].." elapsed="..elapsed)
    end
end
