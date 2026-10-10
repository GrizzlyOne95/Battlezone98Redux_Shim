-- Test-only probe chunk. No respawn-selection policy changes. Candidate
-- observations immediately bracket service.Update; private peer.since state
-- remains unavailable, so observed age is not the service's eligibility age.
fourDiag = (function()
    local d = { samples = {}, events = {}, observerErrors = {}, released = false,
                sampleDropped = 0, eventDropped = 0, errorDropped = 0 }
    local service = CRCoop.GetRespawn()
    local original = service.Update
    local peers, nextSample, lastSignature = {}, 0, nil
    local function append(list, value, cap, counter)
        if #list >= cap then table.remove(list, 1); d[counter] = d[counter] + 1 end
        list[#list + 1] = value
    end
    local function snapshot()
        local now = GetTime()
        local state = service.GetState()
        local record = state.lastRespawn
        local lastRespawn
        if record then
            lastRespawn = { how = record.how, who = record.who, lives = record.lives }
            if record.pos then lastRespawn.pos = { record.pos.x, record.pos.y, record.pos.z } end
        end
        local row = { time = now, localHandle = tostring(me()), nativeLives = exu.GetLives(), respawns = state.respawns,
                      lastRespawn = lastRespawn, localPlayer = describe(me()), candidates = {} }
        for id, player in pairs(CRCoop.GetPlayers()) do
            local peer = peers[id]
            if not peer or peer.handle ~= player.handle then peer = { handle = player.handle, since = now }; peers[id] = peer end
            local object = describe(player.handle)
            local candidate = { id = id, team = player.team, name = player.name,
                                handle = tostring(player.handle), observedUnchangedSeconds = now - peer.since,
                                valid = object.valid, alive = object.alive, odf = object.odf }
            if object.pos then candidate.x, candidate.y, candidate.z = object.pos[1], object.pos[2], object.pos[3] end
            row.candidates[#row.candidates + 1] = candidate
        end
        return row
    end
    local function signature(row)
        local player = row.localPlayer or {}
        return table.concat({row.localHandle, tostring(player.alive), tostring(row.nativeLives), tostring(row.respawns)}, ':')
    end
    local function observe(fn)
        local ok, value = pcall(fn)
        if ok then return value end
        append(d.observerErrors, { error = tostring(value) }, 32, 'errorDropped')
    end
    local function pack(...) return { n = select('#', ...), ... } end
    service.Update = function(...)
        local before = observe(snapshot)
        -- Always run the real service exactly once. Its own errors propagate;
        -- observation failures never suppress Update or alter its returns.
        local results = pack(original(...))
        local after = observe(snapshot)
        observe(function()
            if not after then return end
            local key = signature(after)
            if key ~= lastSignature or (before and before.respawns ~= after.respawns) then
                append(d.events, { before = before, after = after }, 64, 'eventDropped')
                lastSignature = key
            end
            if after.time >= nextSample then
                nextSample = after.time + 0.25
                append(d.samples, after, 128, 'sampleDropped')
            end
        end)
        return unpack(results, 1, results.n)
    end
    function d.Arm(deadline)
        assert(not d.deadline, 'diagnostic already armed')
        assert(deadline - GetTime() >= 5, 'common deadline too close to arm')
        d.deadline, d.initialLives = deadline, exu.GetLives()
        return { time = GetTime(), deadline = deadline, armed = true, nativeLives = d.initialLives }
    end
    function d.Release()
        assert(d.deadline and d.deadline - GetTime() >= 2, 'common deadline missed before release')
        d.released = true
        return { time = GetTime(), deadline = d.deadline, released = true }
    end
    function d.Reschedule(deadline)
        assert(d.deadline and not d.released, 'reschedule requires armed, held owners')
        assert(deadline - GetTime() >= 5, 'rescheduled deadline too close')
        d.deadline = deadline
        return { time = GetTime(), deadline = deadline, armed = true }
    end
    function d.KillTick()
        if not d.released or GetTime() < d.deadline then return end
        if exu.GetLives() < d.initialLives then
            d.lifeLostAt = d.lifeLostAt or GetTime()
            return true
        end
        if IsAlive(me()) then
            d.firstKillAt = d.firstKillAt or GetTime()
            kill(me())
        end
    end
    function d.Metadata()
        return { deadline = d.deadline, released = d.released, initialLives = d.initialLives,
                 firstKillAt = d.firstKillAt, lifeLostAt = d.lifeLostAt,
                 samples = #d.samples, events = #d.events, observerErrors = #d.observerErrors,
                 sampleDropped = d.sampleDropped, eventDropped = d.eventDropped, errorDropped = d.errorDropped }
    end
    function d.Page(kind, begin)
        assert(kind == 'samples' or kind == 'events' or kind == 'observerErrors', 'invalid diagnostic page')
        local out = {}
        for i = begin, math.min(begin + 15, #d[kind]) do out[#out + 1] = d[kind][i] end
        return out
    end
    function d.Stop()
        d.released = false
        service.Update = original
        return true
    end
    return d
end)()
return true
