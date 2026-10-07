-- CRFlowProbe: in-mission test probe for same-PC co-op runs.
--
-- BZRCoopMission.ps1 installs this module into the *test instances'* copy of
-- Campaign Reimagined (never the live install or the CR repository) and appends
-- a short Attach() stub to the end of the mission script, where it can see the
-- mission's file-level locals (M, CRCoop, native, ...).
--
-- What it does on every client:
--   * Prints one-line JSON events to BZLogger: "[CRFLOW] {...} #END". Each
--     line ends with " #END" because Redux appends the next log timestamp to a
--     print() line without a newline.
--       attach  the probe is running (mission, Lua version, bzfile present)
--       role    first frame after CRCoop knows authority/team/player id
--       flag    a boolean/string M field changed (mission progression)
--       op      a presentation call reached the native API on this client
--               (objectives, markers, subtitles, camera, result)
--       snap    periodic state snapshot (also written to crflow\state.json)
--       cmd     a harness command ran (seq, ok, error)
--       error   probe-internal failure (the mission keeps running)
--   * Polls crflow\cmd.txt ("seq=<n>" line, then a Lua chunk). A new seq runs
--     once; the result goes to crflow\out.txt as "seq=<n>\nok=<bool>\n<json>\n#END\n".
--
-- The command chunk runs with M, CRCoop, exu, native, L() (mission locals) and
-- the helpers in Helpers below; unknown names fall through to _G. It runs on
-- that client only, so ownership rules apply: the host may move/damage objects
-- it owns (mission AI); each client moves only its own player craft.
--
-- Everything is pcall-guarded: a probe failure prints an error event and the
-- mission continues.

local Probe = {}

local POLL_SECONDS = 0.25
local FLAG_SECONDS = 0.5
local SNAP_SECONDS = 5.0
local MAX_DEPTH = 6
local MAX_ITEMS = 48

local opts, bzfile, root
local NEVER = -1e9
local lastPoll, lastFlags, lastSnap = NEVER, NEVER, NEVER
local lastSeq = -1
local flagState = {}
local roleSent = false
local tasks = {}
local opDedupe = {}
local frame = 0

local function now()
    local ok, t = pcall(GetTime)
    return ok and t or 0
end

-- ------------------------------------------------------------------ JSON --

local function isHandle(v)
    return type(v) == "userdata"
end

local function try(fn, ...)
    if type(fn) ~= "function" then return nil end
    local ok, a = pcall(fn, ...)
    if ok then return a end
    return nil
end

local function round(x, step)
    step = step or 0.1
    return math.floor(x / step + 0.5) * step
end

-- A handle as data both clients can compare: handle values differ per client.
local function describeHandle(h)
    local d = { valid = try(IsValid, h) and true or false }
    if not d.valid then return d end
    d.odf = try(GetOdf, h)
    d.label = try(GetLabel, h)
    d.team = try(GetTeamNum, h)
    d.alive = try(IsAlive, h) and true or false
    local hp = try(GetHealth, h)
    if type(hp) == "number" then d.hp = round(hp, 0.01) end
    local p = try(GetPosition, h)
    if type(p) == "userdata" or type(p) == "table" then
        local ok, x, y, z = pcall(function() return p.x, p.y, p.z end)
        if ok and type(x) == "number" then d.pos = { round(x, 1), round(y, 1), round(z, 1) } end
    end
    d["local"] = try(IsLocal, h) and true or false
    return d
end

local encode

local function encodeString(s)
    return '"' .. s:gsub('[%c"\\]', function(c)
        if c == '"' then return '\\"' end
        if c == '\\' then return '\\\\' end
        if c == '\n' then return '\\n' end
        if c == '\r' then return '\\r' end
        if c == '\t' then return '\\t' end
        return string.format('\\u%04x', c:byte())
    end) .. '"'
end

local function isArray(t)
    local n = 0
    for k in pairs(t) do
        if type(k) ~= "number" or k < 1 or k ~= math.floor(k) then return false end
        n = n + 1
    end
    for i = 1, n do if t[i] == nil then return false end end
    return true, n
end

encode = function(v, depth, seen)
    local tv = type(v)
    if tv == "nil" then return "null" end
    if tv == "boolean" then return v and "true" or "false" end
    if tv == "number" then
        if v ~= v or v == math.huge or v == -math.huge then return "null" end
        if v == math.floor(v) and math.abs(v) < 1e15 then return string.format("%d", v) end
        return string.format("%.4f", v)
    end
    if tv == "string" then return encodeString(v) end
    if isHandle(v) then return encode(describeHandle(v), depth, seen) end
    if tv ~= "table" then return encodeString("<" .. tv .. ">") end
    depth, seen = depth or 0, seen or {}
    if seen[v] or depth >= MAX_DEPTH then return '"<table>"' end
    seen[v] = true
    local parts = {}
    local array, n = isArray(v)
    if array then
        for i = 1, math.min(n, MAX_ITEMS) do parts[#parts + 1] = encode(v[i], depth + 1, seen) end
        if n > MAX_ITEMS then parts[#parts + 1] = '"<+' .. (n - MAX_ITEMS) .. '>"' end
        seen[v] = nil
        return "[" .. table.concat(parts, ",") .. "]"
    end
    local keys = {}
    for k in pairs(v) do keys[#keys + 1] = k end
    table.sort(keys, function(a, b) return tostring(a) < tostring(b) end)
    for i, k in ipairs(keys) do
        if i > MAX_ITEMS then parts[#parts + 1] = '"<more>":' .. (#keys - MAX_ITEMS); break end
        parts[#parts + 1] = encodeString(tostring(k)) .. ":" .. encode(v[k], depth + 1, seen)
    end
    seen[v] = nil
    return "{" .. table.concat(parts, ",") .. "}"
end

Probe.Encode = encode

-- ---------------------------------------------------------------- output --

local function emit(kind, data)
    data = data or {}
    data.k = kind
    data.t = round(now(), 0.01)
    data.f = frame
    local ok, line = pcall(encode, data)
    if not ok then line = '{"k":"error","msg":' .. encodeString("encode failed: " .. tostring(line)) .. '}' end
    print("[CRFLOW] " .. line .. " #END")
end

local function writeFile(name, text)
    if not root then return false end
    local f = try(bzfile.Open, root .. name, "w", "trunc")
    if not f then return false end
    local ok = pcall(function() f:Write(text) end)
    pcall(function() f:Close() end)
    return ok
end

local function readFile(name)
    if not root then return nil end
    if bzfile.Exists and not try(bzfile.Exists, root .. name) then return nil end
    local f = try(bzfile.Open, root .. name, "r")
    if not f then return nil end
    local ok, data = pcall(function() return f:Dump() end)
    pcall(function() f:Close() end)
    if not ok or type(data) ~= "string" then return nil end
    -- Older bzfile builds pad text-mode Dump output with NULs.
    return (data:gsub("%z+$", ""))
end

-- ----------------------------------------------------------------- state --

local function getM()
    local M = opts.getM and try(opts.getM)
    if type(M) == "table" then return M end
    return nil
end

local function getLocals()
    local t = opts.getLocals and try(opts.getLocals)
    return type(t) == "table" and t or {}
end

local function coop(name, ...)
    local C = opts.CRCoop
    if type(C) ~= "table" then return nil end
    return try(C[name], ...)
end

local function roleInfo()
    local net = try(IsNetGame) and true or false
    return {
        net = net,
        authority = coop("IsAuthority") and true or false,
        team = coop("GetLocalTeam"),
        playerId = coop("GetLocalPlayerId"),
        hosting = try(IsHosting) and true or false,
        phase = coop("GetMissionPhase"),
        ready = coop("IsSessionReady") and true or false,
        lateJoiners = coop("HasLateJoiners") and true or false,
        leaderDeparted = coop("HasLeaderDeparted") and true or false,
    }
end

local function players()
    local list = {}
    local all = coop("GetPlayers")
    if type(all) ~= "table" then return list end
    for id, p in pairs(all) do
        list[#list + 1] = { id = id, name = p.name, team = p.team,
            handle = p.handle and describeHandle(p.handle) or nil }
    end
    table.sort(list, function(a, b) return tostring(a.id) < tostring(b.id) end)
    return list
end

-- Scalars from M, plus handles described and small tables kept shallow.
local function missionState()
    local M = getM()
    if not M then return nil end
    local flags, numbers, handles, tables = {}, {}, {}, {}
    for k, v in pairs(M) do
        local tv = type(v)
        if tv == "boolean" or tv == "string" then
            flags[tostring(k)] = v
        elseif tv == "number" then
            numbers[tostring(k)] = round(v, 0.01)
        elseif isHandle(v) then
            handles[tostring(k)] = describeHandle(v)
        elseif tv == "table" then
            tables[tostring(k)] = v
        end
    end
    return { flags = flags, numbers = numbers, handles = handles, tables = tables }
end

local function teamCounts()
    local counts = {}
    if type(AllCraft) ~= "function" then return counts end
    pcall(function()
        for h in AllCraft() do
            local team = tostring(try(GetTeamNum, h) or "?")
            counts[team] = (counts[team] or 0) + 1
        end
    end)
    return counts
end

local function snapshot()
    local me = try(GetPlayerHandle)
    return {
        mission = opts.mission,
        role = roleInfo(),
        player = me and describeHandle(me) or nil,
        players = players(),
        locals = getLocals(),
        teams = teamCounts(),
        M = missionState(),
    }
end

local function diffFlags()
    local M = getM()
    if not M then return end
    for k, v in pairs(M) do
        local tv = type(v)
        if tv == "boolean" or tv == "string" then
            local key = tostring(k)
            if flagState[key] ~= v then
                emit("flag", { key = key, from = flagState[key], to = v })
                flagState[key] = v
            end
        end
    end
    for key, old in pairs(flagState) do
        local v = M[key]
        if v == nil and old ~= nil then
            emit("flag", { key = key, from = old, to = nil })
            flagState[key] = nil
        end
    end
end

-- ----------------------------------------------------- presentation hooks --

-- Health-percentage objective names are refreshed every frame on every peer.
local function isNoise(op, args)
    if op == "SetObjectiveName" and type(args[2]) == "string" and args[2]:find("%d+%%$") then return true end
    if op == "CameraCancelled" then return true end
    return false
end

local function hookNative()
    local native = opts.native
    if type(native) ~= "table" then return end
    for op, fn in pairs(native) do
        if type(fn) == "function" then
            native[op] = function(...)
                local args, n = { ... }, select("#", ...)
                pcall(function()
                    if isNoise(op, args) then return end
                    local first = args[1]
                    local key = op .. ":" .. (isHandle(first) and tostring(first) or "")
                    local sig
                    if op == "CameraPath" then
                        -- Called every frame during a film; log path changes only.
                        sig = tostring(args[1])
                        key = "CameraPath"
                    else
                        sig = encode(args)
                    end
                    if op == "CameraPath" or op == "SetObjectiveName" or op == "SetCurHealth" or op == "SetMaxHealth" then
                        if opDedupe[key] == sig then return end
                        opDedupe[key] = sig
                    end
                    if op == "CameraReady" or op == "CameraFinish" then opDedupe.CameraPath = nil end
                    local out = {}
                    for i = 1, math.min(n, 4) do out[i] = args[i] end
                    emit("op", { op = op, args = out })
                end)
                return fn(...)
            end
        end
    end
end

-- -------------------------------------------------------------- commands --

local Helpers = {}

function Helpers.me() return try(GetPlayerHandle) end

local function resolve(target)
    if type(target) == "string" then
        local M = getM()
        if M and isHandle(M[target]) then return M[target] end
        return try(GetHandle, target) or target
    end
    return target
end
Helpers.resolve = resolve

function Helpers.describe(h) return describeHandle(resolve(h)) end

-- Places a handle (default: own craft) near a target handle/label/path.
function Helpers.put(h, target, dist)
    h, target = resolve(h), resolve(target)
    dist = dist or 30
    local pos = GetPositionNear(GetPosition(target), dist, dist + 10)
    SetPosition(h, pos)
    return describeHandle(h)
end

function Helpers.tp(target, dist) return Helpers.put(Helpers.me(), target, dist) end

function Helpers.kill(h)
    h = resolve(h)
    if not try(IsAlive, h) then return false end
    Damage(h, 1e7)
    return true
end

-- Kills this client's own craft of a team (optionally only odf prefixes and
-- within radius of a handle). Returns the number damaged.
function Helpers.killTeam(team, odfPattern, near, radius)
    near = near and resolve(near)
    local n = 0
    for h in AllCraft() do
        if GetTeamNum(h) == team and try(IsLocal, h) ~= false and try(IsAlive, h) then
            local odf = try(GetOdf, h) or ""
            local okOdf = not odfPattern or odf:find(odfPattern)
            local okNear = not near or (try(GetDistance, h, near) or math.huge) <= (radius or 500)
            if okOdf and okNear then Damage(h, 1e7); n = n + 1 end
        end
    end
    return n
end

-- Kills enemy craft near any human player's craft (as seen on this client).
function Helpers.clearAroundPlayers(team, odfPattern, radius)
    local n = 0
    for _, rec in pairs(coop("GetPlayers") or {}) do
        if rec.handle and try(IsValid, rec.handle) then
            n = n + Helpers.killTeam(team, odfPattern, rec.handle, radius or 500)
        end
    end
    return n
end

function Helpers.heal(h)
    h = resolve(h)
    if not try(IsAlive, h) then return false end
    SetCurHealth(h, GetMaxHealth(h))
    return true
end

-- Moves pending mission timers in M (numbers in the future) to now. Pattern
-- is a Lua pattern on the field name; required, so timers are pulled deliberately.
function Helpers.ff(pattern, lead)
    assert(type(pattern) == "string", "ff(pattern) needs a field-name pattern")
    local M, t, changed = getM(), now(), {}
    for k, v in pairs(M) do
        if type(v) == "number" and type(k) == "string" and k:find(pattern) and v > t and v < t + 7200 then
            M[k] = t + (lead or 0)
            changed[#changed + 1] = k
        end
    end
    table.sort(changed)
    return changed
end

-- Positions travel between clients as plain numbers.
function Helpers.at(x, y, z)
    if type(SetVector) == "function" then return SetVector(x, y, z) end
    return { x = x, y = y, z = z }
end
function Helpers.xyz(target)
    local p = GetPosition(resolve(target))
    return { p.x, p.y, p.z }
end
function Helpers.near(target, dmin, dmax)
    local p = GetPositionNear(GetPosition(resolve(target)), dmin or 60, dmax or dmin or 60)
    return { p.x, p.y, p.z }
end

-- The handle of the object of this odf nearest to (x, z) within radius, as
-- this client sees it (AllObjects covers buildings as well as craft).
function Helpers.findNear(odf, x, z, radius)
    local best, bestD = nil, radius or 20
    local iter = (type(AllObjects) == "function" and AllObjects) or AllCraft
    for h in iter() do
        if (not odf or try(GetOdf, h) == odf) then
            local p = try(GetPosition, h)
            if p then
                local d = math.sqrt((p.x - x) ^ 2 + (p.z - z) ^ 2)
                if d <= bestD then best, bestD = h, d end
            end
        end
    end
    return best
end

-- Test messages (kind "~") sent with Send() land here instead of the
-- mission's Receive; inbox() returns and clears them.
local inbox = {}
function Helpers.inbox()
    local out = inbox
    inbox = {}
    return out
end

function Helpers.snap() return snapshot() end
function Helpers.role() return roleInfo() end
function Helpers.players() return players() end
function Helpers.L() return getLocals() end
function Helpers.setCameraActive(v)
    if not opts.setCameraActive then return false end
    opts.setCameraActive(v)
    return getLocals().localCameraActive == (v == true)
end

function Helpers.craft(team)
    local list = {}
    for h in AllCraft() do
        if team == nil or GetTeamNum(h) == team then list[#list + 1] = describeHandle(h) end
    end
    return list
end

-- Runs fn every `seconds` of game time until it returns true or is cancelled.
function Helpers.every(name, seconds, fn)
    assert(type(name) == "string" and type(fn) == "function", "every(name, seconds, fn)")
    tasks[name] = { every = seconds or 1, nextAt = 0, fn = fn, runs = 0 }
    return name
end
function Helpers.cancel(name) local had = tasks[name] ~= nil; tasks[name] = nil; return had end
function Helpers.tasks()
    local list = {}
    for name, t in pairs(tasks) do list[#list + 1] = { name = name, runs = t.runs, err = t.err } end
    return list
end
function Helpers.log(msg, data) emit("note", { msg = tostring(msg), data = data }); return true end

-- Variables a command assigns persist for later commands without touching _G.
local vars = {}
local commandEnv = setmetatable({}, {
    __index = function(_, k)
        if vars[k] ~= nil then return vars[k] end
        if k == "M" then return getM() end
        if k == "CRCoop" then return opts.CRCoop end
        if k == "exu" then return opts.exu end
        if k == "native" then return opts.native end
        local h = Helpers[k]
        if h ~= nil then return h end
        return _G[k]
    end,
    __newindex = function(_, k, v) vars[k] = v end,
})

local function compile(code, name)
    if setfenv and loadstring then
        local fn, err = loadstring(code, name)
        if fn then setfenv(fn, commandEnv) end
        return fn, err
    end
    return load(code, name, "t", commandEnv)
end

local function runCommand(text)
    local seq, code = text:match("^seq=(%d+)\r?\n(.*)$")
    seq = tonumber(seq)
    if not seq or seq <= lastSeq then return end
    lastSeq = seq
    local fn, err = compile(code, "=crflow" .. seq)
    local ok, result
    if fn then
        local packed = { pcall(fn) }
        ok = packed[1]
        if ok then
            result = packed[2]
            if #packed > 2 then result = { select(2, (table.unpack or unpack)(packed)) } end
        else
            err = packed[2]
        end
    else
        ok = false
    end
    local body = ok and encode(result) or encode({ error = tostring(err) })
    writeFile("out.txt", "seq=" .. seq .. "\nok=" .. tostring(ok) .. "\n" .. body .. "\n#END\n")
    emit("cmd", { seq = seq, ok = ok, err = (not ok) and tostring(err) or nil })
end

local function runTasks(t)
    for name, task in pairs(tasks) do
        if t >= task.nextAt then
            task.nextAt = t + task.every
            task.runs = task.runs + 1
            local ok, done = pcall(task.fn)
            if not ok then
                task.err = tostring(done)
                emit("error", { where = "task " .. name, msg = task.err })
                tasks[name] = nil
            elseif done == true then
                emit("note", { msg = "task done", task = name, runs = task.runs })
                tasks[name] = nil
            end
        end
    end
end

-- ------------------------------------------------------------------ tick --

local function tick()
    frame = frame + 1
    local t = now()
    if not roleSent and opts.CRCoop and coop("GetLocalPlayerId") ~= nil then
        roleSent = true
        emit("role", roleInfo())
    end
    if t - lastFlags >= FLAG_SECONDS or t < lastFlags then
        lastFlags = t
        diffFlags()
    end
    if t - lastPoll >= POLL_SECONDS or t < lastPoll then
        lastPoll = t
        local text = readFile("cmd.txt")
        if text then runCommand(text) end
    end
    runTasks(t)
    if t - lastSnap >= SNAP_SECONDS or t < lastSnap then
        lastSnap = t
        local s = snapshot()
        emit("snap", s)
        writeFile("state.json", encode(s))
    end
end

function Probe.Attach(options)
    opts = options or {}
    local okFile, mod = pcall(require, "bzfile")
    bzfile = okFile and type(mod) == "table" and mod or nil
    if bzfile then
        local wd = try(bzfile.GetWorkingDirectory)
        if type(wd) == "string" and wd ~= "" then
            root = wd:gsub("[\\/]+$", "") .. "\\crflow\\"
            if bzfile.MakeDirectory then pcall(bzfile.MakeDirectory, root:sub(1, -2)) end
        end
    end
    hookNative()
    local missionUpdate = rawget(_G, "Update")
    if type(missionUpdate) ~= "function" then
        emit("error", { msg = "mission has no global Update to wrap" })
        return false
    end
    _G.Update = function(...)
        local r = { missionUpdate(...) }
        local ok, err = pcall(tick)
        if not ok then emit("error", { where = "tick", msg = tostring(err) }) end
        return (table.unpack or unpack)(r)
    end
    local missionReceive = rawget(_G, "Receive")
    _G.Receive = function(from, kind, ...)
        if kind == "~" then
            local args, n = { ... }, select("#", ...)
            local rec = { from = from, t = now(), n = n, args = {} }
            for i = 1, n do
                local v = args[i]
                -- Keep the raw handle (for IsValid etc.) and how it resolved here.
                rec.args[i] = isHandle(v) and { handle = v, seen = describeHandle(v) } or v
            end
            inbox[#inbox + 1] = rec
            emit("recv", { from = from, n = n, args = rec.args })
            return true
        end
        if type(missionReceive) == "function" then return missionReceive(from, kind, ...) end
        return false
    end
    -- Craft creation and deletion trace (who made what, where, on which peer).
    -- Buildings, scrap and powerups are left out to keep the log small.
    local function isTraced(h)
        return try(IsCraft, h) or try(IsPerson, h)
    end
    local missionAdd = rawget(_G, "AddObject")
    _G.AddObject = function(h, ...)
        if isTraced(h) then emit("add", { h = tostring(h), obj = describeHandle(h) }) end
        if type(missionAdd) == "function" then return missionAdd(h, ...) end
    end
    local missionDelete = rawget(_G, "DeleteObject")
    _G.DeleteObject = function(h, ...)
        if isTraced(h) then emit("del", { h = tostring(h), obj = describeHandle(h) }) end
        if type(missionDelete) == "function" then return missionDelete(h, ...) end
    end
    -- Start the command sequence after whatever a previous run left behind.
    local stale = readFile("cmd.txt")
    if stale then lastSeq = tonumber(stale:match("^seq=(%d+)")) or -1 end
    emit("attach", { mission = opts.mission, lua = _VERSION, bzfile = bzfile ~= nil,
        root = root, staleSeq = lastSeq })
    return true
end

-- Offline tests reach the internals through here.
Probe._test = { Helpers = Helpers, tick = tick, snapshot = snapshot, runCommand = runCommand,
    reset = function()
        lastPoll, lastFlags, lastSnap, lastSeq = NEVER, NEVER, NEVER, -1
        flagState, tasks, opDedupe, roleSent, frame = {}, {}, {}, false, 0
        for k in pairs(vars) do vars[k] = nil end
    end }

return Probe
