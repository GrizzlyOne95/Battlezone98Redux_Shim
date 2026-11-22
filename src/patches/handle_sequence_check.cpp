// handle_sequence_check.cpp -- warns before object handles run out of
// sequence numbers. Read-only: no engine byte is written.
//
// Mechanism: once per render-queue update (LegacyWorldUpdateRenderQueueHook in
// bzr_hooks.cpp, so possibly more than once per frame), Tick() reads the
// GameObject sequence counter (engine_addresses "GameObjectSequenceCounter",
// 0x008E8660 on GOG Redux 2.2.301) and feeds it to handle_sequence_check.h,
// which reports a level crossing:
//   >= 90% of the 20-bit sequence space -> one Warn line
//   >= 0x100000                          -> one Error line: every object made
//                                           from now on has a handle the engine
//                                           cannot resolve
//   lower level (save load, new mission) -> one Info line; both lines re-arm
// Each line is budgeted per process, so a session cycling saves cannot flood
// the log. Trade-off: after several save loads that each cross and re-arm, the
// budget can be spent and a later real 90% crossing goes unlogged. Accepted:
// the first crossings are the ones that matter and a flood is worse.
//
// Fail closed: the install binds the constructor site that assigns and
// increments the counter, the handle lookup and the counter itself all or
// nothing. The lookup row's expected bytes (and h & 0xFFFFF, cmp
// [obj+0x15C]) are the proof of the 20-bit sequence compare. The install then
// checks that all three counter operands at the constructor site name the
// bound counter. Any miss leaves Tick() a no-op.

#include "handle_sequence_check.h"
#include "handle_sequence_check_install.h"

#include "bzr_options_ui.h"
#include "env_switch_table.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cstdint>

namespace BZROpenShim
{
    namespace HandleSequence
    {
        namespace
        {
            constexpr const char* kComponent = "HANDLESEQ";

            std::atomic<bool> g_Done{ false };
            std::atomic<uint32_t> g_CounterAddr{ 0 };
            Tracker g_Tracker;  // render thread only

            volatile long g_WarnBudget = 4;
            volatile long g_ErrorBudget = 4;
            volatile long g_RearmBudget = 4;
            volatile long g_ReadFailBudget = 1;

            bool ReadU32(uint32_t address, uint32_t& value)
            {
                __try
                {
                    value = *reinterpret_cast<const volatile uint32_t*>(static_cast<uintptr_t>(address));
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    value = 0;
                    return false;
                }
            }

            bool Spend(volatile long& budget) { return InterlockedDecrement(&budget) >= 0; }

            void Report(Event event, uint32_t counter)
            {
                switch (event)
                {
                case Event::None:
                    return;
                case Event::Warn:
                    if (Spend(g_WarnBudget))
                        LogShimA(LogLevel::Warn, kComponent,
                                 "object handle sequence at %u%% (counter=%u of %u): after %u more objects, new "
                                 "objects get handles the engine cannot resolve",
                                 PercentUsed(counter), counter, kExhaustedAt, Remaining(counter));
                    return;
                case Event::Exhausted:
                    if (Spend(g_ErrorBudget))
                        LogShimA(LogLevel::Error, kComponent,
                                 "object handle sequence EXHAUSTED (counter=%u >= %u): every object created from "
                                 "now on has a handle that resolves to nothing -- scripts cannot reference it and "
                                 "multiplayer peers reject it as invalid. Handles will now break; restart the "
                                 "session (a save keeps the counter)",
                                 counter, kExhaustedAt);
                    return;
                case Event::Rearmed:
                    if (Spend(g_RearmBudget))
                        LogShimA(LogLevel::Info, kComponent,
                                 "object handle sequence counter dropped to %u (%u%%); warnings re-armed",
                                 counter, PercentUsed(counter));
                    return;
                }
            }

            bool Fail(const char* what)
            {
                LogShimA(LogLevel::Warn, kComponent, "%s; handle sequence check stands down", what);
                return false;
            }

            bool IsEnabled()
            {
                bool enabled = true;
                static const EnvSwitches::EnvSwitch rows[] = {
                    { &enabled, EnvSwitches::Kind::KillSwitch,
                      "OPENSHIM_DISABLE_HANDLE_SEQUENCE_CHECK", "BZR_DISABLE_HANDLE_SEQUENCE_CHECK" },
                };
                EnvSwitches::Apply(rows, EnvFlagEnabled);
                return enabled;
            }

            bool DoInstall()
            {
                uint32_t ctorSite = 0, lookup = 0, counter = 0;
                const HookEngine::EngineRow rows[] = {
                    { "GameObjectCtorSequenceAssign", &ctorSite },
                    { "GameObjectHandleLookup", &lookup },
                    { "GameObjectSequenceCounter", &counter },
                };
                if (!HookEngine::BindEngineRows("Handle sequence check", rows))
                    return Fail("an engine address failed its byte guard");

                for (uint32_t offset : kCtorOperandOffsets)
                {
                    uint32_t operand = 0;
                    if (!ReadU32(ctorSite + offset, operand) || operand != counter)
                        return Fail("the constructor site does not use the bound sequence counter");
                }

                uint32_t value = 0;
                if (!ReadU32(counter, value))
                    return Fail("the sequence counter is not readable");

                g_CounterAddr.store(counter, std::memory_order_release);
                LogShimA(LogLevel::Info, kComponent,
                         "installed: counter=0x%08X value=%u warnAt=%u exhaustedAt=%u (read-only)",
                         counter, value, kWarnAt, kExhaustedAt);
                return true;
            }
        }

        void InstallHandleSequenceCheckIfPossible()
        {
            if (g_Done.exchange(true))
                return;
            if (!IsEnabled())
            {
                LogShimA(LogLevel::Info, kComponent, "disabled ([Fixes] HandleSequenceCheck = 0)");
                return;
            }
            DoInstall();
        }

        void TickHandleSequenceCheck()
        {
            const uint32_t address = g_CounterAddr.load(std::memory_order_acquire);
            if (address == 0)
                return;
            uint32_t counter = 0;
            if (!ReadU32(address, counter))
            {
                if (Spend(g_ReadFailBudget))
                    LogShimA(LogLevel::Warn, kComponent, "sequence counter read faulted; check stops");
                g_CounterAddr.store(0, std::memory_order_release);
                return;
            }
            Report(Observe(g_Tracker, counter), counter);
        }
    }
}
