
-- ===== Scrap-accumulation bench (appended to a staged nbattle.lua copy) =====
-- Run-BZRCoopScrapBench.ps1 appends this chunk, so M and vehicleOdfs are the
-- nbattle.lua upvalues. Read-only census plus an opt-in scrap removal used as
-- the control arm. Called through CRFlowProbe on every client.
function ScrapBenchCensus()
    local c = {objects = 0, craftAlive = 0, army5 = 0, army6 = 0, pilots = 0,
               scrap = 0, scrapArena = 0, classes = {}}
    for h in AllObjects() do
        c.objects = c.objects + 1
        local label = GetClassLabel(h) or "?"
        c.classes[label] = (c.classes[label] or 0) + 1
        if label == "scrap" then
            c.scrap = c.scrap + 1
            local p = GetPosition(h)
            if (p.x - 2560)^2 + (p.z - 2740)^2 < 600^2 then c.scrapArena = c.scrapArena + 1 end
        end
    end
    for h in AllCraft() do
        if IsAlive(h) then
            c.craftAlive = c.craftAlive + 1
            local t = GetTeamNum(h)
            if t == 5 or t == 6 then
                if vehicleOdfs[GetOdf(h)] then c["army" .. t] = c["army" .. t] + 1
                else c.pilots = c.pilots + 1 end
            end
        end
    end
    c.deaths, c.spawned, c.simTime = M.deaths, M.spawned, GetTime()
    c.running, c.finished = M.running, M.finished
    return c
end

function ScrapBenchClear()
    local remove = {}
    for h in AllObjects() do if GetClassLabel(h) == "scrap" then remove[#remove + 1] = h end end
    local removed = 0
    for _, h in ipairs(remove) do
        if IsValid(h) then RemoveObject(h); removed = removed + 1 end
    end
    return removed
end
