// objective_objects_fix.cpp -- make the stock Lua ObjectiveObjects() iterator
// list every objective once. The byte facts and the proof the rewrite is safe
// are in include/objective_objects_fix.h.
//
// One in-place rewrite of the ObjectiveObjectsNext body (GOG 0x00502760,
// 0xA4 bytes), verified against the stock body first; anything else stands
// down untouched. The iterator reads the engine's own objective list, so
// objectives set from native code, mission DLLs or a save load are listed
// too, not only ones set through Lua SetObjectiveOn.
//
// EXU (or any other plugin) can ask whether it is in place with the exported
// OpenShimGetObjectiveObjectsFix(): 1 when the fixed iterator is installed,
// else 0. Ask when a script first needs it, not at DLL load: the answer is 0
// until this patch stage has run.

#include "objective_objects_fix.h"
#include "objective_objects_fix_install.h"

#include "bzr_options_ui.h"
#include "env_switch_table.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cstdint>
#include <vector>

namespace BZROpenShim
{
    namespace ObjectiveObjectsFix
    {
        namespace
        {
            constexpr const char* kComponent = "OBJOBJS";

            std::atomic<bool> g_Done{ false };
            std::atomic<bool> g_Active{ false };

            bool IsEnabled()
            {
                bool enabled = true;
                static const EnvSwitches::EnvSwitch rows[] = {
                    { &enabled, EnvSwitches::Kind::KillSwitch,
                      "OPENSHIM_DISABLE_OBJECTIVE_OBJECTS_FIX", "BZR_DISABLE_OBJECTIVE_OBJECTS_FIX" },
                };
                EnvSwitches::Apply(rows, EnvFlagEnabled);
                return enabled;
            }

            bool DoInstall()
            {
                const uint32_t entry = HookEngine::ResolveNamedAddress("Lua::ObjectiveObjectsNext");
                uint8_t body[kBodyLen] = {};
                if (!entry || !HookEngine::ReadMemory(entry, body, sizeof(body)))
                {
                    LogShimA(LogLevel::Warn, kComponent, "iterator step did not resolve; fix not installed");
                    return false;
                }

                switch (Classify(body))
                {
                case BodyState::Patched:
                    LogShimA(LogLevel::Info, kComponent, "iterator at 0x%08X already fixed; nothing written", entry);
                    return true;
                case BodyState::Unknown:
                    LogShimA(LogLevel::Warn, kComponent,
                             "iterator at 0x%08X does not hold the stock body; fix not installed", entry);
                    return false;
                case BodyState::Stock:
                    break;
                }

                const Operands operands = ExtractStockOperands(body, entry);
                if (!LayoutMatches(operands))
                {
                    LogShimA(LogLevel::Warn, kComponent,
                             "objective count 0x%08X is not right after the 32-slot list 0x%08X; fix not installed",
                             operands.count, operands.list);
                    return false;
                }

                HookEngine::PatchDef def;
                def.address = entry;
                def.type = HookEngine::PatchType::BYTES;
                def.payload.resize(kBodyLen);
                BuildPatchedBody(operands, entry, def.payload.data());
                def.name = "Lua::ObjectiveObjectsNext";
                def.verified = true;
                def.expected_original.assign(body, body + kBodyLen);

                std::vector<HookEngine::PatchDef> patches{ def };
                const std::vector<bool> applied = HookEngine::ApplyPatches(patches);
                if (applied.size() != 1 || !applied[0])
                {
                    LogShimA(LogLevel::Warn, kComponent, "write at 0x%08X failed; fix not installed", def.address);
                    return false;
                }
                LogShimA(LogLevel::Info, kComponent, "installed: ObjectiveObjects iterator lists each objective (0x%08X)",
                         def.address);
                return true;
            }
        }

        void InstallObjectiveObjectsFixIfPossible()
        {
            if (g_Done.exchange(true))
                return;
            if (!IsEnabled())
            {
                LogShimA(LogLevel::Info, kComponent, "disabled ([Fixes] ObjectiveObjectsIterator = 0)");
                return;
            }
            g_Active.store(DoInstall());
        }

        bool IsActive()
        {
            return g_Active.load();
        }
    }
}

// Capability probe for EXU and other plugins (GetProcAddress by name).
extern "C" __declspec(dllexport) int __cdecl OpenShimGetObjectiveObjectsFix()
{
    return BZROpenShim::ObjectiveObjectsFix::IsActive() ? 1 : 0;
}

#if defined(_M_IX86)
#pragma comment(linker, "/EXPORT:OpenShimGetObjectiveObjectsFix=_OpenShimGetObjectiveObjectsFix")
#endif
