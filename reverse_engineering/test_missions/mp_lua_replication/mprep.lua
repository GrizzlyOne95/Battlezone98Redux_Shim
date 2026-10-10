-- Individual-operation qualification probe, Lua 5.1. No replication API.
-- Receive only observes; it never runs a gameplay mutation from a packet.
local M = {}
local unpackValues = unpack or table.unpack

function M.new(options)
    options = options or {}
    local P = { subjects = {}, watches = {}, peers = {}, sequence = 0 }
    local wire = options.messageType or "~"
    assert(type(wire) == "string" and #wire == 1, "reserve one message byte")
    local magic = "MPRE1"
    local objective = "mpre_obj"
    local objectiveActive = false
    local emit = options.log or print
    local function note(text)
        emit("[MPRE] " .. tostring(GetTime()) .. " " .. text)
    end
    local function valid(h) return h ~= nil and IsValid(h) end
    local function compact(value)
        if type(value) == "string" then
            return string.format("string[%d]=%q", #value, string.sub(value, 1, 80))
        end
        return type(value) .. "=" .. tostring(value)
    end
    local function checkString(s, limit)
        assert(type(s) == "string" and #s <= limit, "string too long or not a string")
    end
    local function subject(h)
        assert(P.subjects[h] and valid(h), "only mutate a live disposable probe subject")
        assert(h ~= GetPlayerHandle(), "never mutate the local player object")
    end
    local function query(fn, ...)
        if type(fn) ~= "function" then return "unavailable" end
        local ok, value = pcall(fn, ...)
        if ok then return tostring(value) end
        return "query-error"
    end

    function P.Sample(tag, h)
        checkString(tag, 32)
        local parts = { "sample=" .. tag, "handle=" .. tostring(h), "valid=" .. tostring(valid(h)),
                        "hosting=" .. tostring(IsHosting()), "net=" .. tostring(IsNetGame()) }
        if valid(h) then
            parts[#parts + 1] = "local=" .. query(IsLocal, h)
            parts[#parts + 1] = "remote=" .. query(IsRemote, h)
            parts[#parts + 1] = "team=" .. query(GetTeamNum, h)
            parts[#parts + 1] = "name=" .. query(GetObjectiveName, h)
            parts[#parts + 1] = "label=" .. query(GetLabel, h)
            parts[#parts + 1] = "command=" .. query(GetCurrentCommand, h)
            if type(GetPosition) == "function" then
                local ok, pos = pcall(GetPosition, h)
                if ok and pos then
                    parts[#parts + 1] = string.format("position=%.3f,%.3f,%.3f", pos.x, pos.y, pos.z)
                end
            end
            for slot = 0, 4 do
                parts[#parts + 1] = "weapon" .. slot .. "=" .. query(GetWeaponClass, h, slot)
            end
        end
        local text = table.concat(parts, " ")
        note(text)
        return text
    end

    function P.Watch(tag, h)
        checkString(tag, 32)
        if valid(h) then P.subjects[h] = true end
        P.watches[tag] = { h = h, start = GetTime(), nextSample = 0 }
        P.Sample(tag, h)
    end

    function P.Update()
        local now = GetTime()
        for tag, watch in pairs(P.watches) do
            if now - watch.start > 10 then
                P.watches[tag] = nil
            elseif now >= watch.nextSample then
                P.Sample(tag, watch.h)
                watch.nextSample = now + 1
            end
        end
    end

    function P.AllowPeer(id)
        assert(type(id) == "number" and id > 0 and id <= 65535 and id == math.floor(id), "net ID required")
        P.peers[id] = true
    end

    function P.DeletePlayer(id) P.peers[id] = nil end

    function P.Announce(to, tag, h)
        checkString(tag, 32)
        subject(h)
        local sent = Send(to, wire, magic, "watch", tag, h)
        note("announce=" .. tag .. " result=" .. tostring(sent))
        return sent
    end

    -- Scalar-only transport probe. Limits are conservative, not a discovered MTU.
    function P.Payload(to, tag, ...)
        checkString(tag, 32)
        local values = { n = select("#", ...), ... }
        assert(values.n <= 8, "at most eight values")
        local budget = 32 + #tag
        for i = 1, values.n do
            local v, kind = values[i], type(values[i])
            assert(kind == "nil" or kind == "boolean" or kind == "number" or kind == "string", "scalar only")
            if kind == "number" then
                assert(v == v and v >= -2147483647 and v <= 2147483647, "finite int32-range number required")
            end
            if kind == "string" then
                checkString(v, 127)
                budget = budget + #v + 2
            else
                budget = budget + 9
            end
        end
        assert(budget <= 200, "probe packet budget exceeded")
        P.sequence = P.sequence + 1
        local sent = Send(to, wire, magic, "payload", tag, P.sequence, unpackValues(values, 1, values.n))
        note("payload=" .. tag .. " sequence=" .. P.sequence .. " result=" .. tostring(sent))
        return sent
    end

    function P.Receive(from, kind, ...)
        if kind ~= wire then return false end
        local args = { n = select("#", ...), ... }
        if args[1] ~= magic then return false end
        if not P.peers[from] then
            note("rejected unregistered sender=" .. tostring(from))
            return true
        end
        if type(args[3]) ~= "string" or #args[3] > 32 then
            note("malformed probe message")
            return true
        end
        if args[2] == "watch" and args.n == 4 then
            if args[4] ~= nil and type(args[4]) ~= "userdata" then
                note("malformed probe handle")
                return true
            end
            note("watch received from=" .. tostring(from) .. " tag=" .. args[3])
            -- A nil handle is evidence of an unresolved reference. Reannounce
            -- explicitly after spawn; never manufacture a replacement locally.
            P.Watch(args[3], args[4])
        elseif args[2] == "payload" then
            local parts = { "payload received from=" .. tostring(from), "tag=" .. args[3] }
            for i = 4, args.n do parts[#parts + 1] = compact(args[i]) end
            note(table.concat(parts, " "))
        else
            note("unrecognized probe message")
        end
        return true
    end

    function P.Spawn(mode, odf, team, where)
        checkString(odf, 32)
        assert(type(team) == "number" and team >= 0 and team <= 15 and team == math.floor(team), "team 0..15 required")
        local build
        if mode == "stock" then build = BuildObject
        elseif mode == "sync" then build = options.exu and options.exu.BuildSyncObject
        elseif mode == "async" then build = options.exu and options.exu.BuildAsyncObject
        else error("unknown spawn mode") end
        assert(type(build) == "function", "spawn capability unavailable")
        local h = build(odf, team, where)
        if valid(h) then P.subjects[h] = true end
        P.Sample("spawn_" .. mode, h)
        return h
    end

    -- Exactly one local primitive per invocation. The observer packets do not
    -- apply it elsewhere. Repeat locally on each peer for the explicit case.
    function P.Run(operation, h, value, slot)
        subject(h)
        P.Sample("before_" .. operation, h)
        local result
        if operation == "SetName" or operation == "SetObjectiveName" then
            checkString(value, 64)
            if operation == "SetName" then SetName(h, value) else SetObjectiveName(h, value) end
        elseif operation == "SetObjectiveOn" then SetObjectiveOn(h)
        elseif operation == "SetObjectiveOff" then SetObjectiveOff(h)
        elseif operation == "GiveWeapon" then
            assert(type(slot) == "number" and slot >= 0 and slot <= 4 and slot == math.floor(slot), "slot 0..4 required")
            if value ~= nil then checkString(value, 32) end
            result = GiveWeapon(h, value, slot)
        elseif operation == "RemoveObject" then RemoveObject(h)
        elseif operation == "SetPosition" then SetPosition(h, value)
        elseif operation == "SetVelocity" then SetVelocity(h, value)
        elseif operation == "SetTeamNum" then
            assert(type(value) == "number" and value >= 0 and value <= 15 and value == math.floor(value), "team 0..15 required")
            SetTeamNum(h, value)
        elseif operation == "SetLocal" then
            assert(options.allowOwnershipClaim == true, "ownership-claim experiment disabled")
            SetLocal(h)
        else error("unknown operation") end
        note("operation=" .. operation .. " result=" .. tostring(result))
        P.Watch("after_" .. operation, h)
        return result
    end

    function P.Objective(operation, text)
        if operation == "add" then
            assert(not objectiveActive, "probe objective already exists")
            checkString(text, 100)
            AddObjective(objective, "WHITE", 30, text)
            objectiveActive = true
        elseif operation == "update" then
            assert(objectiveActive, "add probe objective first")
            checkString(text, 100)
            UpdateObjective(objective, "GREEN", 30, text)
        elseif operation == "remove" then
            if objectiveActive then RemoveObjective(objective) end
            objectiveActive = false
        else error("unknown objective operation") end
        note("objective=" .. operation)
    end

    note("probe initialized; local operations only")
    return P
end

return M
