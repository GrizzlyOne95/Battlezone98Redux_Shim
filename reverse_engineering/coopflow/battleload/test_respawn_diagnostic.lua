local now, lives, player, kills = 0, 8, 11, 0
local state = { respawns = 1 }
local calls, originalError = 0, false
local service = { GetState = function() return state end, Update = function()
    calls = calls + 1
    if originalError then error('original failure') end
    return 'keep', nil, 3
end }
local original = service.Update
CRCoop = { GetRespawn = function() return service end,
           GetPlayers = function() return {[1]={team=1,handle=player},[2]={team=2,handle=22}} end }
exu = { GetLives = function() return lives end }
GetTime = function() return now end
me = function() return player end
describe = function(h) return {valid=true,alive=true,odf='aspilo',pos={h,0,0}} end
IsAlive = function() return true end
kill = function() kills = kills + 1 end
assert(dofile(arg[1] or 'four_respawn_diagnostic.lua'))
assert(not pcall(fourDiag.Arm, 4), 'must reject insufficient arm lead')
fourDiag.Arm(10)
assert(fourDiag.Reschedule(10).deadline == 10)
now = 10
fourDiag.KillTick()
assert(kills == 0, 'unreleased schedule must never kill')
assert(not pcall(fourDiag.Release), 'late release must fail')
now = 1
fourDiag.Release()
assert(not pcall(fourDiag.Reschedule, 20), 'released owners cannot be rescheduled')
fourDiag.KillTick()
assert(kills == 0, 'common deadline must hold')
now = 10
fourDiag.KillTick()
assert(kills == 1 and fourDiag.Metadata().firstKillAt == 10)
lives = 7
assert(fourDiag.KillTick() and fourDiag.Metadata().lifeLostAt == 10)
service.Update()
player = 12
state = {respawns=2,lastRespawn={how='rally',lives=3,pos={x=1,y=2,z=3}}}
service.Update()
local events = fourDiag.Page('events',1)
assert(#events == 2 and events[2].after.localHandle == '12')
assert(events[2].after.lastRespawn.pos[3] == 3, 'vectors must be explicit arrays')
for i=1,200 do now = now+.25; service.Update() end
local metadata = fourDiag.Metadata()
assert(metadata.samples == 128 and metadata.sampleDropped > 0, 'sample retention must be bounded')
assert(#fourDiag.Page('samples',1) == 16, 'pages must fit probe serializer')
local describeOriginal = describe
describe = function() error('observer failure') end
local priorCalls = calls
local a,b,c = service.Update()
assert(calls == priorCalls + 1 and a == 'keep' and b == nil and c == 3,
       'observer errors must preserve original call and return tuple')
assert(fourDiag.Metadata().observerErrors == 2)
describe = describeOriginal
originalError = true
priorCalls = calls
local ok, err = pcall(service.Update)
assert(not ok and tostring(err):find('original failure') and calls == priorCalls + 1,
       'original error must propagate exactly once')
assert(fourDiag.Stop() and service.Update == original, 'restore service callback')
assert(not fourDiag.Metadata().released)
print('PASS: common deadline, release guards, life transition, handle events, bounded pages, vector encoding, callback restore')
