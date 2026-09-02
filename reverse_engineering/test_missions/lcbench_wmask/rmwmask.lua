-- lcbench weaponMask synchronized-volley qualification
-- Deploy as addon/lcbench/lcbench.lua via runner overlay.
-- Lua 5.1, no goto, no ObjectiveObjects, print diagnostics, 8-char ODF names.
--
-- Rewritten for the volley policy. Three rules this harness now obeys that the
-- previous revision broke, each of which silently produced a zero:
--
--   1. Deploy is issued EXACTLY ONCE. Re-issuing it restarts the unit's
--      timeDeploy countdown every frame, so the howitzer never reaches
--      IsDeployed and never fires. The old stage-1 block re-entered on every
--      tick because its guard was `elapsed >= 2.2` with no latch.
--   2. Attack is issued once, then at most two spaced retries. Order spam has
--      the same restart effect on the AI process.
--   3. A stock, unmodified baseline runs in the same fixture. Until stock
--      avartl deploys and fires here, no custom case's zero means anything.
--
-- Volley evidence: ordnance creations are grouped into salvos by arrival time.
-- Several ordnance objects created inside one frame is what "fires in sync"
-- means observably, so the salvo size -- not the total -- is the result.

local elapsed = 0.0
local stage = 0
local selectedCase = "hstk"
local fixtureCommit = "unknown"
local caseDef = nil

local attacker = nil
local target = nil
local mineDest = nil

-- one-shot latches; nothing in this file may issue an order twice without one
local deployIssued = false
local deployIssuedAt = -1.0
local deployedAt = -1.0
local orderIssued = false
local orderIssuedAt = -1.0
local retryCount = 0
local lastRetryAt = -1.0
local countEnabled = false
local blockedReason = ""

local nextPoll = 0.0

-- salvo accounting
local ordTotal = 0
local ordByName = {}
local salvos = {}          -- { t = time, n = count, names = "a,b" }
local curSalvoT = -99.0
local curSalvoN = 0
local curSalvoNames = ""
local maxSalvo = 0

local SALVO_WINDOW = 0.10  -- seconds; one frame at 30-60fps is well inside this

local caseDefs = {
  -- stock controls: no ODF override at all, stock mask, stock hardpoints
  hstk = {odf="avartl", kind="hw", team=1, mask="stock", desc="stock howitzer control"},
  mstk = {odf="avmine", kind="mn", team=1, mask="stock", desc="stock minelayer control"},
  -- howitzer single-bit selection
  hwh5 = {odf="hwh5", kind="hw", team=1, mask="00001", desc="H5 mask bit0 of 2"},
  hwh6 = {odf="hwh6", kind="hw", team=1, mask="00010", desc="H6 mask bit1 of 2"},
  -- howitzer volley
  hwv2 = {odf="hwv2", kind="hw", team=1, mask="00011", desc="HV2 volley 2 mortars"},
  hwh3 = {odf="hwh3", kind="hw", team=1, mask="00011", desc="H3 volley 2 mortars"},
  hwv4 = {odf="hwv4", kind="hw", team=1, mask="01111", desc="HV4 volley 4 mortars"},
  -- minelayer
  mnm5 = {odf="mnm5", kind="mn", team=1, mask="00001", desc="M5 mask bit0 of 2"},
  mnm6 = {odf="mnm6", kind="mn", team=1, mask="00010", desc="M6 mask bit1 of 2"},
  mnm3 = {odf="mnm3", kind="mn", team=1, mask="00011", desc="M3 volley 2 mines"},
}

local function Say(fmt, ...)
  print(string.format("[WMASK][%s] " .. fmt, tostring(selectedCase), ...))
end

local function Sanitize(s)
  if s == nil then return "" end
  local t = tostring(s)
  local nul = string.find(t, "\0", 1, true)
  if nul then t = string.sub(t, 1, nul - 1) end
  t = string.gsub(t, "^%s+", "")
  t = string.gsub(t, "%s+$", "")
  return t
end

local function Ask(fn, ...)
  if fn == nil then return nil end
  local ok, v = pcall(fn, ...)
  if ok then return v end
  return nil
end

-- Read a stock ODF value so the fixture reports the real deploy time and
-- weapon range instead of assuming one.
local function OdfNum(odfName, section, key, default)
  local h = Ask(OpenODF, odfName)
  if h == nil then return default end
  local v = Ask(GetODFFloat, h, section, key, default)
  if v == nil then return default end
  return v
end

local function LogUnit(h, label)
  if h == nil or not IsValid(h) then
    Say("%s INVALID handle", label)
    return
  end
  local odf = Sanitize(Ask(GetOdf, h))
  local cls = Sanitize(Ask(GetClassLabel, h))
  Say("%s odf=%s class=%s", label, odf, cls)
  local fitted = 0
  for slot = 0, 4 do
    local w = Sanitize(Ask(GetWeaponClass, h, slot))
    if w ~= "" then
      Say("%s slot %d weaponClass=%s", label, slot, w)
      fitted = fitted + 1
    end
  end
  Say("%s fittedSlots=%d declaredMask=%s", label, fitted, tostring(caseDef.mask))
end

local function Snapshot(label)
  local v = attacker ~= nil and IsValid(attacker)
  local cmd, dep, can, ammo, hp = "nil", "nil", "nil", -1, -1
  if v then
    cmd = tostring(Ask(GetCurrentCommand, attacker))
    dep = tostring(Ask(IsDeployed, attacker))
    can = tostring(Ask(CanCommand, attacker))
    ammo = Ask(GetAmmo, attacker) or -1
    hp = Ask(GetHealth, attacker) or -1
  end
  Say("T+%.2f %s valid=%s cmd=%s dep=%s canCmd=%s hp=%.3f ammo=%.3f ord=%d maxSalvo=%d",
      elapsed, label, tostring(v), cmd, dep, can, hp, ammo, ordTotal, maxSalvo)
end

local function CloseSalvo()
  if curSalvoN > 0 then
    salvos[#salvos + 1] = {t = curSalvoT, n = curSalvoN, names = curSalvoNames}
    if curSalvoN > maxSalvo then maxSalvo = curSalvoN end
    Say("SALVO t=%.3f size=%d ord=[%s]", curSalvoT, curSalvoN, curSalvoNames)
    curSalvoN = 0
    curSalvoNames = ""
  end
end

function Start()
  elapsed = 0.0
  stage = 0
  local cfg = Ask(OpenODF, "rmwcfg")
  if cfg ~= nil then
    selectedCase = Sanitize(Ask(GetODFString, cfg, "Roadmap", "case", "hstk"))
    fixtureCommit = Sanitize(Ask(GetODFString, cfg, "Roadmap", "commit", "unknown"))
  end
  if selectedCase == "" then selectedCase = "hstk" end
  caseDef = caseDefs[selectedCase]
  if caseDef == nil then
    selectedCase = "hstk"
    caseDef = caseDefs["hstk"]
  end
  Say("START build=2.2.301 case=%s odf=%s mask=%s kind=%s commit=%s",
      selectedCase, caseDef.odf, caseDef.mask, caseDef.kind, fixtureCommit)
  Say("ODFFACT avartl.timeDeploy=%.2f/%.2f ghartill.ordName=%s",
      OdfNum("avartl", "HoverCraftClass", "timeDeploy", -1),
      OdfNum("avartl", "GameObjectClass", "timeDeploy", -1),
      tostring(Ask(GetODFString, Ask(OpenODF, "ghartill"), "LauncherClass", "ordName", "?")))
end

function Update(dt)
  elapsed = elapsed + (dt or 0.0)

  -- close any open salvo once its window has passed
  if curSalvoN > 0 and (elapsed - curSalvoT) > SALVO_WINDOW then
    CloseSalvo()
  end

  ----------------------------------------------------------------- stage 0
  -- Build the attacker. Runs once.
  if stage == 0 and elapsed >= 1.0 then
    local player = GetPlayerHandle()
    local base = SetVector(0, 0, 0)
    if IsValid(player) then base = GetPosition(player) end
    local posA = GetPositionNear(base, 25.0, 35.0)

    Say("T+%.2f BUILD odf=%s team=%d", elapsed, caseDef.odf, caseDef.team)
    local h = Ask(BuildObject, caseDef.odf, caseDef.team, posA)
    if h == nil or not IsValid(h) then
      blockedReason = "BuildObject failed for " .. tostring(caseDef.odf)
      Say("T+%.2f BUILD FAILED -- %s", elapsed, blockedReason)
      stage = 9
      return
    end
    attacker = h
    Ask(SetIndependence, attacker, 0)
    LogUnit(attacker, "ATTACKER")
    stage = 1
    nextPoll = elapsed + 0.5
    return
  end

  ----------------------------------------------------------------- stage 1
  -- Settle, then issue Deploy exactly once (howitzer only).
  if stage == 1 then
    if not IsValid(attacker) then
      blockedReason = "attacker went invalid before deploy"
      stage = 9
      return
    end
    if caseDef.kind == "mn" then
      -- minelayers do not deploy
      stage = 3
      return
    end
    if not deployIssued and elapsed >= 2.0 then
      local can = Ask(CanCommand, attacker)
      Say("T+%.2f PRE_DEPLOY canCmd=%s dep=%s", elapsed, tostring(can), tostring(Ask(IsDeployed, attacker)))
      local ok = Ask(Deploy, attacker)
      deployIssued = true
      deployIssuedAt = elapsed
      Say("T+%.2f DEPLOY ISSUED ONCE ok=%s", elapsed, tostring(ok))
      stage = 2
      nextPoll = elapsed + 0.5
    end
    return
  end

  ----------------------------------------------------------------- stage 2
  -- Wait for IsDeployed. NEVER re-issue Deploy here.
  if stage == 2 then
    if elapsed >= nextPoll then
      nextPoll = elapsed + 0.5
      Snapshot("DEPLOY_WAIT")
    end
    if Ask(IsDeployed, attacker) == true then
      deployedAt = elapsed
      Say("T+%.2f DEPLOYED after %.2fs", elapsed, elapsed - deployIssuedAt)
      stage = 3
      return
    end
    if elapsed - deployIssuedAt > 20.0 then
      blockedReason = string.format("never reached IsDeployed within 20s of a single Deploy (canCmd=%s)",
                                    tostring(Ask(CanCommand, attacker)))
      Say("T+%.2f DEPLOY TIMEOUT -- %s", elapsed, blockedReason)
      stage = 9
      return
    end
    return
  end

  ----------------------------------------------------------------- stage 3
  -- Spawn the objective and issue the order exactly once.
  if stage == 3 then
    if not IsValid(attacker) then
      blockedReason = "attacker went invalid before order"
      stage = 9
      return
    end
    local can = Ask(CanCommand, attacker)
    Say("T+%.2f READY canCmd=%s dep=%s", elapsed, tostring(can), tostring(Ask(IsDeployed, attacker)))

    if caseDef.kind == "hw" then
      -- place the target well inside artillery reach but outside minimum range
      local posT = GetPositionNear(GetPosition(attacker), 180.0, 220.0)
      local th = Ask(BuildObject, "avtank", 2, posT)
      if th == nil or not IsValid(th) then
        blockedReason = "target BuildObject failed"
        stage = 9
        return
      end
      target = th
      Ask(SetIndependence, target, 0)
      Ask(Stop, target, 1)
      local d = Ask(GetDistance, attacker, target) or -1
      Say("T+%.2f TARGET built dist=%.1f", elapsed, d)
      countEnabled = true
      local ok = Ask(Attack, attacker, target, 1)
      orderIssued = true
      orderIssuedAt = elapsed
      Say("T+%.2f ATTACK ISSUED ONCE ok=%s", elapsed, tostring(ok))
    else
      mineDest = GetPositionNear(GetPosition(attacker), 40.0, 60.0)
      countEnabled = true
      local ok = Ask(Mine, attacker, mineDest, 1)
      if ok == nil and SetCommand ~= nil and AiCommand ~= nil and AiCommand.LAY_MINES ~= nil then
        ok = Ask(SetCommand, attacker, AiCommand.LAY_MINES, 1, nil, mineDest, 0, "")
        Say("T+%.2f LAYMINES via SetCommand ok=%s", elapsed, tostring(ok))
      end
      orderIssued = true
      orderIssuedAt = elapsed
      Say("T+%.2f MINE ISSUED ONCE ok=%s dest=(%.1f,%.1f)", elapsed, tostring(ok), mineDest.x, mineDest.z)
    end

    Snapshot("ORDERED")
    stage = 4
    nextPoll = elapsed + 1.0
    return
  end

  ----------------------------------------------------------------- stage 4
  -- Observe. At most two spaced retries, only while nothing has fired.
  if stage == 4 then
    if elapsed >= nextPoll then
      nextPoll = elapsed + 1.0
      Snapshot("POLL")
    end

    if ordTotal == 0 and retryCount < 2 and (elapsed - orderIssuedAt) > 6.0
       and (lastRetryAt < 0 or (elapsed - lastRetryAt) > 6.0) then
      local cmd = Ask(GetCurrentCommand, attacker)
      if cmd == 0 then
        retryCount = retryCount + 1
        lastRetryAt = elapsed
        if caseDef.kind == "hw" and target ~= nil and IsValid(target) then
          Say("T+%.2f RETRY %d Attack (cmd was NONE)", elapsed, retryCount)
          Ask(Attack, attacker, target, 1)
        elseif caseDef.kind == "mn" and mineDest ~= nil then
          Say("T+%.2f RETRY %d Mine (cmd was NONE)", elapsed, retryCount)
          Ask(Mine, attacker, mineDest, 1)
        end
      end
    end

    if elapsed >= 78.0 then
      CloseSalvo()
      Snapshot("RESULT")
      local parts = {}
      for k, v in pairs(ordByName) do parts[#parts + 1] = string.format("%s=%d", k, v) end
      table.sort(parts)
      Say("COMPLETE ord=%d maxSalvo=%d salvos=%d byName[%s] retries=%d",
          ordTotal, maxSalvo, #salvos, table.concat(parts, " "), retryCount)
      for i = 1, #salvos do
        Say("COMPLETE salvo[%d] t=%.3f size=%d [%s]", i, salvos[i].t, salvos[i].n, salvos[i].names)
      end
      Say("COMPLETE case=%s mask=%s deployedAt=%.2f blocked=%s",
          selectedCase, tostring(caseDef.mask), deployedAt, (blockedReason == "" and "none" or blockedReason))
      Say("FINAL_MARKER")
      FailMission(GetTime() + 0.8)
      stage = 5
    end
    return
  end

  ----------------------------------------------------------------- stage 9
  -- Fixture blocked: say so loudly and end, rather than logging a silent zero.
  if stage == 9 then
    Say("FIXTURE_BLOCKED reason=%s", blockedReason)
    Say("COMPLETE ord=%d maxSalvo=%d blocked=%s", ordTotal, maxSalvo, blockedReason)
    Say("FINAL_MARKER")
    FailMission(GetTime() + 0.8)
    stage = 5
    return
  end
end

local seen = {}
local createLogBudget = 80

-- Anything the fixture itself built. Everything else created while the order is
-- live is treated as ordnance, so a mortar whose ODF name we do not know in
-- advance is still counted.
local function IsFixtureUnit(name)
  return name == "avartl" or name == "avmine" or name == "avtank"
      or name == "hwh3" or name == "hwh5" or name == "hwh6"
      or name == "hwv2" or name == "hwv4"
      or name == "mnm3" or name == "mnm5" or name == "mnm6"
end

function CreateObject(h)
  if h == nil or not countEnabled then return end
  -- CreateObject and AddObject both fire for the same object; de-duplicate.
  local key = tostring(h)
  if seen[key] then return end
  local name = string.lower(Sanitize(Ask(GetOdf, h)))
  local cls = string.lower(Sanitize(Ask(GetClassLabel, h)))
  if createLogBudget > 0 then
    createLogBudget = createLogBudget - 1
    Say("RAWCREATE t=%.3f odf=%s class=%s", elapsed, name, cls)
  end
  if name == "" or IsFixtureUnit(name) then return end
  seen[key] = true

  ordTotal = ordTotal + 1
  ordByName[name] = (ordByName[name] or 0) + 1

  if curSalvoN > 0 and (elapsed - curSalvoT) <= SALVO_WINDOW then
    curSalvoN = curSalvoN + 1
    curSalvoNames = curSalvoNames .. "," .. name
  else
    CloseSalvo()
    curSalvoT = elapsed
    curSalvoN = 1
    curSalvoNames = name
  end
  Say("CREATE t=%.3f ord=%s total=%d", elapsed, name, ordTotal)
end

function AddObject(h) CreateObject(h) end
function DeleteObject(h) end
function CreatePlayer(id, name, team) end
function AddPlayer(id, name, team) end
function DeletePlayer(id, name, team) end
