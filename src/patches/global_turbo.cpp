// global_turbo.cpp
// BZR Open Shim - global and per-unit turbo (SinglePlayer tier) and its
// bridge accessors, split out of bzr_hooks.cpp. Installed and configured
// from there; shared helpers come from bzr_hooks_internal.h.
#include "bzr_hooks.h"
#include "hook_engine.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "global_turbo_mode.h"
#include "patcher.h"
#include "shim_log.h"

#include <Windows.h>

#include <array>
#include <atomic>
#include <climits>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <unordered_map>

namespace BZROpenShim
{
    namespace Hooks
    {
        // --- Global turbo (SinglePlayer tier) ----------------------------------
        // Forces units to turbo, mirroring EXU's GlobalTurbo: redirect the
        // first throttle-tolerance comparison to a 0.9 constant and NOP the
        // second turbo gate so units turbo whenever near full throttle.
        // OpenShim owns the patch sites plus the per-unit begin hook. EXU's
        // Lua APIs delegate here when the hook ownership export is available;
        // its original native implementation remains a standalone fallback.
        // All turbo behavior is hard-disabled in network games.
        //
        // Decoded block (UnitTurboThrottleBlock, scripts/patches.json):
        //   +0x00  mov eax,[ebp-0x70]; fstp [eax+8]   ; begin hook (6 bytes)
        //   +0x09  movss xmm0,[ecx+0xC]               ; throttle
        //   +0x0E  comiss xmm0,[0x008A2604]           ; 1.0f, operand @+0x11
        //   +0x15  jb  no-turbo
        //   +0x17  movss xmm0,[0x008A25C8]            ; gate, operand @+0x1B
        //   +0x1F  comiss xmm0,[ebp-0x54]
        //   +0x23  jbe no-turbo
        // So turbo = throttle >= [tol] && [gate] > [ebp-0x54].
        //
        // Three layouts (GlobalTurboMode::Layout), written only on a change:
        //   Stock     stock bytes (mode 0, network games).
        //   StaticOn  @+0x11 -> g_GlobalTurboTolerance, jbe NOP'd (mode 1).
        //   PerUnit   @+0x11 -> g_TurboTolDynBits, @+0x1B -> g_TurboGateDynBits,
        //             jbe stock. The begin hook fills both cells for each unit
        //             (modes 2/3, or any exu.SetUnitTurbo override live).
        // PerUnit never writes code per unit. One semantic difference from
        // StaticOn: a turbo unit gets gate = FLT_MAX, so a NaN [ebp-0x54]
        // takes the jbe and does not turbo, as in stock; StaticOn's NOP
        // turbos it.
        //
        // Precedence: an EXU per-unit override beats the mode;
        // exu.SetGlobalTurbo replaces the mode with all teams or off until
        // the mission ends, when the ini mode comes back.
        //
        // One row guards the whole stretch, so the sites keep this layout.
        // Both absolute operands are captured live once the guard has
        // passed, for revert.
        static uintptr_t g_GlobalTurboComissOperandAddr = 0;  // +0x11
        static uintptr_t g_GlobalTurboGateOperandAddr = 0;    // +0x1B
        static uintptr_t g_GlobalTurboSecondGateAddr = 0;     // +0x23
        static uint8_t g_GlobalTurboComissOperandExpected[4] = {};
        static uint8_t g_GlobalTurboGateOperandExpected[4] = {};
        // The stock cells the two operands point at.
        static const volatile uint32_t* g_StockTurboToleranceCell = nullptr;
        static const volatile uint32_t* g_StockTurboGateCell = nullptr;
        static constexpr uint8_t kGlobalTurboSecondGateExpected[2] = { 0x76, 0x0C };
        static constexpr uint8_t kGlobalTurboSecondGatePatched[2] = { 0x90, 0x90 };
        static uintptr_t g_UnitTurboBeginHookAddr = 0;

        static bool GlobalTurboAddressesBound()
        {
            static const bool bound = [] {
                uint32_t block = 0;
                const HookEngine::EngineRow rows[] = {
                    { "UnitTurboThrottleBlock", &block },
                };
                if (!HookEngine::BindEngineRows("Global turbo", rows))
                {
                    MarkOptionHookFailed("Turbo", "Unavailable: Global turbo did not hook on this game build (see openshim.log).");
                    return false;
                }
                g_UnitTurboBeginHookAddr = block;
                g_GlobalTurboComissOperandAddr = block + 0x11;
                g_GlobalTurboGateOperandAddr = block + 0x1B;
                g_GlobalTurboSecondGateAddr = block + 0x23;
                std::memcpy(g_GlobalTurboComissOperandExpected,
                            reinterpret_cast<const void*>(g_GlobalTurboComissOperandAddr),
                            sizeof(g_GlobalTurboComissOperandExpected));
                std::memcpy(g_GlobalTurboGateOperandExpected,
                            reinterpret_cast<const void*>(g_GlobalTurboGateOperandAddr),
                            sizeof(g_GlobalTurboGateOperandExpected));
                uint32_t tolCell = 0;
                uint32_t gateCell = 0;
                std::memcpy(&tolCell, g_GlobalTurboComissOperandExpected, sizeof(tolCell));
                std::memcpy(&gateCell, g_GlobalTurboGateOperandExpected, sizeof(gateCell));
                g_StockTurboToleranceCell = reinterpret_cast<const volatile uint32_t*>(
                    static_cast<uintptr_t>(tolCell));
                g_StockTurboGateCell = reinterpret_cast<const volatile uint32_t*>(
                    static_cast<uintptr_t>(gateCell));
                return true;
            }();
            return bound;
        }
        static constexpr uint8_t kUnitTurboBeginHookExpected[6] = {
            0x8B, 0x45, 0x90, 0xD9, 0x58, 0x08
        };
        using GlobalTurboMode::Layout;
        using GlobalTurboMode::Mode;
        static constexpr Mode kGlobalTurboModeDefault = Mode::Off;

        // The StaticOn tolerance operand points here (EXU uses 0.9f). Must
        // live for the process lifetime: its absolute address is written into
        // the instruction, so a namespace-scope static is required.
        static float g_GlobalTurboTolerance = 0.9f;
        // The PerUnit operands point at these two cells, filled per unit by
        // the begin hook. Float bit patterns; same lifetime rule as above.
        static volatile uint32_t g_TurboTolDynBits = 0;
        static volatile uint32_t g_TurboGateDynBits = 0;
        // g_GlobalTurboTolerance as bits, refreshed with the layout.
        static uint32_t g_TurboToleranceBits = 0;

        bool g_GlobalTurboConfigInitialized = false;
        static Mode g_GlobalTurboMode = kGlobalTurboModeDefault;          // live
        static Mode g_GlobalTurboBaselineMode = kGlobalTurboModeDefault;  // openshim.ini
        // exu.SetGlobalTurbo owns the live mode until the mission ends; an
        // options-page apply only moves the baseline meanwhile.
        static bool g_GlobalTurboExuGlobalActive = false;
        static int g_GlobalTurboLoggedMode = -1;
        static bool g_GlobalTurboBaselineCaptured = false;
        // The layout the sites hold, as this file last wrote them.
        static Layout g_GlobalTurboLayout = Layout::Stock;
        static bool g_UnitTurboHooksInstalled = false;
        static bool g_UnitTurboHookMismatchLogged = false;
        static bool g_UnitTurboFallbackLogged = false;
        static bool g_GlobalTurboSitesMismatchLogged = false;
        static std::unordered_map<uint32_t, bool> g_UnitTurboOverrides;

        // Player team and hostile-team mask, refreshed with the layout
        // (every MP-gate tick, 250 ms at most, and on every bridge or
        // options change) instead of two engine calls per unit.
        static std::atomic<int> g_TurboPlayerTeam{ 1 };
        static std::atomic<uint32_t> g_TurboHostileMask{ 0 };

        using FnGameObjectGetHandle = uint32_t(__thiscall*)(void* object);
        using FnExuUpdateCullingForUnit = void(__cdecl*)(void* object);
        using FnGameObjectTeamRelation = bool(__thiscall*)(void* object, int team);
        static FnExuUpdateCullingForUnit g_ExuFn_UpdateCullingForUnit = nullptr;
        static HMODULE g_ExuCullingCallbackModule = nullptr;

        struct GlobalTurboSiteBytes
        {
            uint8_t tolOperand[4];
            uint8_t gateOperand[4];
            uint8_t gate[2];
        };

        static GlobalTurboSiteBytes GetGlobalTurboLayoutBytes(Layout layout)
        {
            GlobalTurboSiteBytes bytes = {};
            std::memcpy(bytes.tolOperand, g_GlobalTurboComissOperandExpected, sizeof(bytes.tolOperand));
            std::memcpy(bytes.gateOperand, g_GlobalTurboGateOperandExpected, sizeof(bytes.gateOperand));
            std::memcpy(bytes.gate, kGlobalTurboSecondGateExpected, sizeof(bytes.gate));
            if (layout == Layout::StaticOn)
            {
                const uint32_t tolAddr =
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&g_GlobalTurboTolerance));
                std::memcpy(bytes.tolOperand, &tolAddr, sizeof(bytes.tolOperand));
                std::memcpy(bytes.gate, kGlobalTurboSecondGatePatched, sizeof(bytes.gate));
            }
            else if (layout == Layout::PerUnit)
            {
                const uint32_t tolAddr = static_cast<uint32_t>(
                    reinterpret_cast<uintptr_t>(const_cast<uint32_t*>(&g_TurboTolDynBits)));
                const uint32_t gateAddr = static_cast<uint32_t>(
                    reinterpret_cast<uintptr_t>(const_cast<uint32_t*>(&g_TurboGateDynBits)));
                std::memcpy(bytes.tolOperand, &tolAddr, sizeof(bytes.tolOperand));
                std::memcpy(bytes.gateOperand, &gateAddr, sizeof(bytes.gateOperand));
            }
            return bytes;
        }

        static bool GlobalTurboSitesHold(const GlobalTurboSiteBytes& bytes)
        {
            return ExpectedBytesMatchAt(g_GlobalTurboComissOperandAddr, bytes.tolOperand,
                                        sizeof(bytes.tolOperand)) &&
                   ExpectedBytesMatchAt(g_GlobalTurboGateOperandAddr, bytes.gateOperand,
                                        sizeof(bytes.gateOperand)) &&
                   ExpectedBytesMatchAt(g_GlobalTurboSecondGateAddr, bytes.gate,
                                        sizeof(bytes.gate));
        }

        // Writes only the sites that differ. Intermediate states are safe in
        // any order this file uses: each operand points at a valid float.
        static bool WriteGlobalTurboLayoutBytes(const GlobalTurboSiteBytes& from,
                                                const GlobalTurboSiteBytes& to)
        {
            if (std::memcmp(from.tolOperand, to.tolOperand, sizeof(to.tolOperand)) != 0 &&
                !WritePatchBytes(g_GlobalTurboComissOperandAddr, to.tolOperand, sizeof(to.tolOperand)))
                return false;
            if (std::memcmp(from.gateOperand, to.gateOperand, sizeof(to.gateOperand)) != 0 &&
                !WritePatchBytes(g_GlobalTurboGateOperandAddr, to.gateOperand, sizeof(to.gateOperand)))
                return false;
            if (std::memcmp(from.gate, to.gate, sizeof(to.gate)) != 0 &&
                !WritePatchBytes(g_GlobalTurboSecondGateAddr, to.gate, sizeof(to.gate)))
                return false;
            return true;
        }

        // Moves the sites to `target`. Writes nothing when the layout is
        // already there, and nothing when the sites no longer hold the bytes
        // this file last wrote (another owner changed them): that is left
        // untouched, and a revert to stock then just forgets the layout.
        static bool ApplyGlobalTurboLayout(Layout target)
        {
            if (target == g_GlobalTurboLayout)
                return true;

            const GlobalTurboSiteBytes current = GetGlobalTurboLayoutBytes(g_GlobalTurboLayout);
            if (!GlobalTurboSitesHold(current))
            {
                if (!g_GlobalTurboSitesMismatchLogged)
                {
                    g_GlobalTurboSitesMismatchLogged = true;
                    Log(L"[TURBO] Turbo sites changed under us (expected %hs); leaving them\n",
                        GlobalTurboMode::Name(g_GlobalTurboLayout));
                }
                if (target == Layout::Stock)
                    g_GlobalTurboLayout = Layout::Stock;
                return false;
            }
            g_GlobalTurboSitesMismatchLogged = false;

            if (target == Layout::PerUnit)
            {
                // Cells hold stock values until the hook's first unit.
                g_TurboTolDynBits = *g_StockTurboToleranceCell;
                g_TurboGateDynBits = *g_StockTurboGateCell;
            }

            if (!WriteGlobalTurboLayoutBytes(current, GetGlobalTurboLayoutBytes(target)))
            {
                Log(L"[TURBO] Turbo layout write %hs -> %hs failed\n",
                    GlobalTurboMode::Name(g_GlobalTurboLayout), GlobalTurboMode::Name(target));
                return false;
            }

            Log(L"[TURBO] Turbo layout %hs -> %hs (tolerance=%.3f) tol@0x%08X gate@0x%08X jbe@0x%08X\n",
                GlobalTurboMode::Name(g_GlobalTurboLayout), GlobalTurboMode::Name(target),
                static_cast<double>(g_GlobalTurboTolerance),
                static_cast<uint32_t>(g_GlobalTurboComissOperandAddr),
                static_cast<uint32_t>(g_GlobalTurboGateOperandAddr),
                static_cast<uint32_t>(g_GlobalTurboSecondGateAddr));
            g_GlobalTurboLayout = target;
            return true;
        }

        // GameObject::EnemyP(int team) at the HudPaletteEnemyTeam row.
        // UNVERIFIED on Redux: 1.5 decompile lines 182139-182145 show true
        // for team >= 1 not in the ally mask. IsHostileTeam excludes team 0
        // and the player's team itself, so the code does not rely on it.
        static FnGameObjectTeamRelation ResolveTurboEnemyP()
        {
            static const FnGameObjectTeamRelation fn = [] {
                uint32_t enemyP = 0;
                const HookEngine::EngineRow rows[] = { { "HudPaletteEnemyTeam", &enemyP } };
                if (!HookEngine::BindEngineRows("Turbo enemy teams", rows))
                {
                    Log(L"[TURBO] Alliance test unavailable; enemy-teams mode turbos no team\n");
                    return static_cast<FnGameObjectTeamRelation>(nullptr);
                }
                return reinterpret_cast<FnGameObjectTeamRelation>(static_cast<uintptr_t>(enemyP));
            }();
            return fn;
        }

        // The current player GameObject (HudFadeGetPlayer: returns the
        // global at 0x00917AFC; the same getter contextual_hud uses).
        // Player handles have the top bit set (0xFFF00001 seen live), so
        // the handle path cannot be trusted for this.
        using FnCurrentPlayer = void* (__cdecl*)();
        static FnCurrentPlayer ResolveTurboCurrentPlayer()
        {
            static const FnCurrentPlayer fn = [] {
                uint32_t getter = 0;
                const HookEngine::EngineRow rows[] = { { "HudFadeGetPlayer", &getter } };
                if (!HookEngine::BindEngineRows("Turbo player object", rows))
                    return static_cast<FnCurrentPlayer>(nullptr);
                return reinterpret_cast<FnCurrentPlayer>(static_cast<uintptr_t>(getter));
            }();
            return fn;
        }

        // SEH leaf: the getter reads an engine global.
        static void* TryGetTurboCurrentPlayer(FnCurrentPlayer getter)
        {
            __try
            {
                return getter ? getter() : nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        // SEH leaf: no RAII locals. Bit t set when EnemyP(player, t).
        static bool TryReadHostileTeamMask(FnGameObjectTeamRelation enemyP, void* player,
                                           uint32_t& outMask)
        {
            __try
            {
                uint32_t mask = 0;
                for (int team = 1; team < GlobalTurboMode::kTeamCount; ++team)
                {
                    if (enemyP(player, team))
                        mask |= 1u << team;
                }
                outMask = mask;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // The player's team and hostile teams, read once per refresh
        // and only while a filter mode is live. The player team falls back
        // to 1 as LegacyTankAi mode 2 does; an unreadable mask keeps the
        // last one.
        static void RefreshTurboTeamCache()
        {
            int playerTeam = 1;
            int playerHandle = 0;
            void* player = TryGetTurboCurrentPlayer(ResolveTurboCurrentPlayer());
            const int objectTeam = player ? GetGameObjectActualTeam(player) : INT_MIN;
            if (objectTeam > 0 && objectTeam < GlobalTurboMode::kTeamCount)
            {
                playerTeam = objectTeam;
            }
            else if (g_BzrFn_GetPlayerHandle && g_BzrFn_GetTeamNum)
            {
                // Handles carry the top bit, so test != 0, not > 0.
                playerHandle = g_BzrFn_GetPlayerHandle();
                const int team = playerHandle != 0 ? g_BzrFn_GetTeamNum(playerHandle) : 0;
                if (team > 0)
                    playerTeam = team;
            }
            g_TurboPlayerTeam.store(playerTeam, std::memory_order_relaxed);

            if (g_GlobalTurboMode != Mode::EnemyTeams)
                return;
            const FnGameObjectTeamRelation enemyP = ResolveTurboEnemyP();
            uint32_t mask = 0;
            const bool read = enemyP && player && TryReadHostileTeamMask(enemyP, player, mask);
            if (read)
                g_TurboHostileMask.store(mask, std::memory_order_relaxed);

            // Change-only: the per-unit decision is silent, so log what it
            // will see whenever the inputs move.
            static int s_loggedTeam = -1, s_loggedHandle = -1;
            static uint32_t s_loggedMask = ~0u;
            static bool s_loggedRead = false;
            if (playerTeam != s_loggedTeam || playerHandle != s_loggedHandle ||
                mask != s_loggedMask || read != s_loggedRead)
            {
                s_loggedTeam = playerTeam;
                s_loggedHandle = playerHandle;
                s_loggedMask = mask;
                s_loggedRead = read;
                Log(L"[TURBO] enemy filter: player=0x%08X obj=%p team=%d enemyP=%hs read=%hs mask=0x%04X\n",
                    static_cast<uint32_t>(playerHandle), player, playerTeam,
                    enemyP ? "yes" : "no", read ? "yes" : "no",
                    g_TurboHostileMask.load(std::memory_order_relaxed));
            }
        }

        static void SetGlobalTurboMode(Mode mode, const char* source)
        {
            g_GlobalTurboMode = mode;
            if (static_cast<int>(mode) == g_GlobalTurboLoggedMode)
                return;
            g_GlobalTurboLoggedMode = static_cast<int>(mode);
            Log(L"[TURBO] mode=%hs (%hs)\n", GlobalTurboMode::Name(mode), source);
        }

        static FnExuUpdateCullingForUnit ResolveExuCullingCallback()
        {
            // Two loader lookups per unit per tick added up. The module set
            // only changes at load time, so re-probe once a second and answer
            // from the cache in between.
            static ULONGLONG s_nextProbeTick = 0;
            const ULONGLONG now = GetTickCount64();
            if (now < s_nextProbeTick)
                return g_ExuFn_UpdateCullingForUnit;
            s_nextProbeTick = now + 1000;
            HMODULE module = GetModuleHandleA("exu.dll");
            if (!module)
                module = GetModuleHandleA("ExtraUtilities.dll");
            if (module != g_ExuCullingCallbackModule)
            {
                g_ExuCullingCallbackModule = module;
                g_ExuFn_UpdateCullingForUnit = module
                    ? reinterpret_cast<FnExuUpdateCullingForUnit>(
                        GetProcAddress(module, "EXU_UpdateCullingForUnit"))
                    : nullptr;
            }
            return g_ExuFn_UpdateCullingForUnit;
        }

        static bool TryGetTurboObjectHandle(void* object, uint32_t& outHandle)
        {
            outHandle = 0;
            if (!object || g_GameObjectGetHandleAddr == 0)
                return false;
            __try
            {
                outHandle = reinterpret_cast<FnGameObjectGetHandle>(
                    g_GameObjectGetHandleAddr)(object);
                return outHandle != 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Keep SEH in a leaf with no STL/RAII locals. Debug MSVC iterators
        // require object unwinding, which cannot coexist with __try in the same
        // function (C2712).
        static void TryUpdateExuCullingForUnit(FnExuUpdateCullingForUnit updateCulling,
                                               void* object)
        {
            if (!updateCulling)
                return;
            __try
            {
                updateCulling(object);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        // PerUnit layout: decide this unit and fill the two cells the
        // redirected operands read. Data only; no code bytes change. Runs
        // with an x87 value pending (the displaced fstp), so it copies bit
        // patterns and does no float work.
        static void DecideUnitTurbo(void* object)
        {
            const bool singlePlayer = ReadLocalPlayerNetIdValue() == 0;
            uint32_t handle = 0;
            bool hasOverride = false;
            bool overrideValue = false;
            if (!g_UnitTurboOverrides.empty() && TryGetTurboObjectHandle(object, handle))
            {
                const auto overrideIt = g_UnitTurboOverrides.find(handle);
                if (overrideIt != g_UnitTurboOverrides.end())
                {
                    hasOverride = true;
                    overrideValue = overrideIt->second;
                }
            }

            int unitTeam = INT_MIN;
            if (singlePlayer && !hasOverride && GlobalTurboMode::IsTeamFiltered(g_GlobalTurboMode))
            {
                unitTeam = GetGameObjectActualTeam(object);
                // The direct read rejects anything that is not a GameObject;
                // ask the engine by handle before treating the team as unknown.
                if (unitTeam == INT_MIN && g_BzrFn_GetTeamNum &&
                    (handle != 0 || TryGetTurboObjectHandle(object, handle)))
                {
                    unitTeam = g_BzrFn_GetTeamNum(static_cast<int>(handle));
                }
            }

            const bool turbo = GlobalTurboMode::UnitWantsTurbo(
                g_GlobalTurboMode, singlePlayer, hasOverride, overrideValue,
                unitTeam != INT_MIN, unitTeam,
                g_TurboPlayerTeam.load(std::memory_order_relaxed),
                g_TurboHostileMask.load(std::memory_order_relaxed));
            const GlobalTurboMode::ThresholdBits bits = GlobalTurboMode::UnitThresholdBits(
                turbo, g_TurboToleranceBits, *g_StockTurboToleranceCell, *g_StockTurboGateCell);
            g_TurboTolDynBits = bits.tolerance;
            g_TurboGateDynBits = bits.gate;
        }

        static void __cdecl HandleUnitTurboBegin(void* object)
        {
            TryUpdateExuCullingForUnit(ResolveExuCullingCallback(), object);
            if (g_GlobalTurboLayout == Layout::PerUnit)
                DecideUnitTurbo(object);
        }

        static void __declspec(naked) UnitTurboBeginHook()
        {
            __asm
            {
                // Stolen instructions first: the fstp pops the clamp result
                // (0x00447ED0 returns in ST0), so C++ runs with an empty x87
                // stack. eax on entry is that call's leftover, not the unit:
                // the GameObject is [[ebp-0x68]+0x10] (UnitTask `this` stored
                // at 0x00601743, its +0x10 read at 0x00601749). Same contract
                // as EXU's TurboGateThunk.h, which also verifies nothing
                // branches into 0x00601C98-0x00601CC2.
                mov eax, [ebp - 0x70]
                fstp dword ptr [eax + 0x08]
                pushfd
                pushad
                mov ecx, [ebp - 0x68]
                push dword ptr [ecx + 0x10]
                call HandleUnitTurboBegin
                add esp, 4
                popad
                popfd
                ret
            }
        }

        static bool WriteUnitTurboCallHook(
            uintptr_t address,
            size_t length,
            const void* target)
        {
            if (length < 5 || !target)
                return false;
            std::array<uint8_t, 9> patch = {};
            patch.fill(0x90);
            patch[0] = 0xE8;
            const int32_t relative =
                static_cast<int32_t>(reinterpret_cast<uintptr_t>(target)) -
                static_cast<int32_t>(address + 5);
            std::memcpy(patch.data() + 1, &relative, sizeof(relative));
            return WritePatchBytes(address, patch.data(), length);
        }

        void InstallUnitTurboHooksIfPossible()
        {
            if (g_UnitTurboHooksInstalled)
                return;
            if (!GlobalTurboAddressesBound())
                return;
            if (!ExpectedBytesMatchAt(
                    g_UnitTurboBeginHookAddr,
                    kUnitTurboBeginHookExpected,
                    sizeof(kUnitTurboBeginHookExpected)))
            {
                if (!g_UnitTurboHookMismatchLogged)
                {
                    g_UnitTurboHookMismatchLogged = true;
                    Log(L"[TURBO] Per-unit hook bytes not ready/mismatched; deferring\n");
                }
                return;
            }

            if (!WriteUnitTurboCallHook(
                    g_UnitTurboBeginHookAddr,
                    sizeof(kUnitTurboBeginHookExpected),
                    reinterpret_cast<const void*>(UnitTurboBeginHook)))
            {
                return;
            }

            g_UnitTurboHooksInstalled = true;
            g_UnitTurboHookMismatchLogged = false;
            Log(L"[TURBO] Installed shim-owned per-unit hook begin=0x%08X\n",
                static_cast<uint32_t>(g_UnitTurboBeginHookAddr));
        }

        // Reconciles the sites with the live mode, the overrides and the net
        // id. Called from the MP-gate tick, the bridge and options apply.
        void RefreshGlobalTurboPatchState()
        {
            const bool singlePlayer = ReadLocalPlayerNetIdValue() == 0;
            const bool anyOverride = !g_UnitTurboOverrides.empty();
            const bool wantsAnything =
                singlePlayer && (g_GlobalTurboMode != Mode::Off || anyOverride);
            if (!wantsAnything && g_GlobalTurboLayout == Layout::Stock)
                return;
            if (!GlobalTurboAddressesBound())
                return;

            // The per-unit path needs the begin hook; retry its install
            // here (it may have been deferred while Steam's bytes settled).
            const bool needsPerUnit =
                GlobalTurboMode::NeedsPerUnit(g_GlobalTurboMode, singlePlayer, anyOverride);
            if (needsPerUnit && !g_UnitTurboHooksInstalled)
                InstallUnitTurboHooksIfPossible();
            const Layout layout = GlobalTurboMode::ChooseLayout(
                g_GlobalTurboMode, singlePlayer, anyOverride, g_UnitTurboHooksInstalled);

            const bool fallingBack = needsPerUnit && layout != Layout::PerUnit;
            if (fallingBack != g_UnitTurboFallbackLogged)
            {
                g_UnitTurboFallbackLogged = fallingBack;
                if (fallingBack)
                {
                    Log(L"[TURBO] Per-unit hook not installed; mode=%hs falls back to %hs%hs\n",
                        GlobalTurboMode::Name(g_GlobalTurboMode), GlobalTurboMode::Name(layout),
                        anyOverride ? " (exu.SetUnitTurbo overrides ignored)" : "");
                    MarkOptionHookFailed("Turbo", "Unavailable: team-filtered turbo did not hook on this game build (see openshim.log).");
                }
            }

            if (layout == Layout::PerUnit)
            {
                uint32_t tolBits = 0;
                std::memcpy(&tolBits, &g_GlobalTurboTolerance, sizeof(tolBits));
                g_TurboToleranceBits = tolBits;
                if (GlobalTurboMode::IsTeamFiltered(g_GlobalTurboMode))
                    RefreshTurboTeamCache();
            }
            ApplyGlobalTurboLayout(layout);
        }

        void InitializeGlobalTurboConfig()
        {
            if (g_GlobalTurboConfigInitialized)
                return;
            g_GlobalTurboConfigInitialized = true;

            Mode mode = kGlobalTurboModeDefault;

            // Global user baseline (openshim.ini [SinglePlayer]): 0-3, and
            // true/false still read as 1/0.
            std::string text;
            if (TryGetUserConfigString(kUserConfigSinglePlayerSection, "Turbo", text) &&
                !GlobalTurboMode::TryParse(text.data(), text.size(), mode))
            {
                Log(L"[TURBO] Ignoring invalid Turbo=%hs (expected 0, 1, 2 or 3)\n", text.c_str());
            }

            // Env overrides / kill switch (parity with the other features).
            if (EnvFlagEnabled("OPENSHIM_GLOBAL_TURBO") || EnvFlagEnabled("BZR_GLOBAL_TURBO"))
                mode = Mode::AllTeams;
            else if (EnvFlagEnabled("OPENSHIM_DISABLE_GLOBAL_TURBO") ||
                     EnvFlagEnabled("BZR_DISABLE_GLOBAL_TURBO"))
                mode = Mode::Off;

            // Advanced: override the throttle tolerance (default 0.9 matches EXU).
            float tol = g_GlobalTurboTolerance;
            if (TryGetEnvFloat("OPENSHIM_GLOBAL_TURBO_TOLERANCE", tol))
                g_GlobalTurboTolerance = tol;

            // An options-page apply re-runs this mid-mission: it moves the
            // baseline, and the live mode only while no exu.SetGlobalTurbo
            // owns it (that mission gets the new value at its end).
            g_GlobalTurboBaselineMode = mode;
            g_GlobalTurboBaselineCaptured = true;
            if (!g_GlobalTurboExuGlobalActive)
                SetGlobalTurboMode(mode, "ini");

            InstallUnitTurboHooksIfPossible();
            Log(L"[TURBO] Global turbo baseline=%hs live=%hs tolerance=%.3f (SP-only; shim-owned)\n",
                GlobalTurboMode::Name(mode),
                GlobalTurboMode::Name(g_GlobalTurboMode),
                static_cast<double>(g_GlobalTurboTolerance));

            RefreshGlobalTurboPatchState();
        }

        void RevertGlobalTurboToBaseline()
        {
            InitializeGlobalTurboConfig();  // idempotent; ensures baseline captured
            if (!g_GlobalTurboBaselineCaptured)
                return;
            g_UnitTurboOverrides.clear();
            g_GlobalTurboExuGlobalActive = false;
            // Do not carry last mission's hostile teams into the next one.
            g_TurboHostileMask.store(0, std::memory_order_relaxed);
            g_TurboPlayerTeam.store(1, std::memory_order_relaxed);
            SetGlobalTurboMode(g_GlobalTurboBaselineMode, "ini");
            RefreshGlobalTurboPatchState();
        }
    }

    using namespace Hooks;

    // EXU's exu.GetGlobalTurbo: true for any mode other than off, so the
    // team filter modes (2, 3) read as true too.
    bool GetGlobalTurboFromBridge()
    {
        InitializeGlobalTurboConfig();
        return g_GlobalTurboMode != Mode::Off;
    }

    bool SetGlobalTurboFromBridge(bool enabled)
    {
        InitializeGlobalTurboConfig();
        InstallUnitTurboHooksIfPossible();
        // A mission's global switch means every team or off, whatever the
        // ini filter; the ini mode returns at mission end.
        g_GlobalTurboExuGlobalActive = true;
        SetGlobalTurboMode(enabled ? Mode::AllTeams : Mode::Off, "exu");
        RefreshGlobalTurboPatchState();
        Log(L"[MISSIONHOOK] global turbo %hs layout=%hs\n",
            enabled ? "enabled" : "disabled",
            GlobalTurboMode::Name(g_GlobalTurboLayout));
        return !enabled || g_GlobalTurboLayout != Layout::Stock;
    }

    bool HasUnitTurboHooksFromBridge()
    {
        InstallUnitTurboHooksIfPossible();
        return g_UnitTurboHooksInstalled;
    }

    bool GetUnitTurboFromBridge(uint32_t handle)
    {
        const auto it = g_UnitTurboOverrides.find(handle);
        return it != g_UnitTurboOverrides.end() && it->second;
    }

    bool SetUnitTurboFromBridge(uint32_t handle, bool enabled)
    {
        if (handle == 0)
            return false;
        // Accept the mission override even if Steam's runtime bytes have not
        // settled yet. Refresh retries the hook install and moves the sites
        // to the per-unit layout as soon as the guarded hook site is ready.
        g_UnitTurboOverrides[handle] = enabled;
        InstallUnitTurboHooksIfPossible();
        RefreshGlobalTurboPatchState();
        return true;
    }
}
