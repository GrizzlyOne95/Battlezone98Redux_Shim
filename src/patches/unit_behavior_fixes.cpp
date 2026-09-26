// unit_behavior_fixes.cpp
// BZR Open Shim - stock unit behaviour fixes: base Producer script
// predicates, the Splinter undead gate, tug cargo post-load deploy, the
// constructor recycle stale target, APC allied-target deploy and the
// constructor remote-build death cleanup, split out of bzr_hooks.cpp.
#include "bzr_hooks.h"
#include "bzr_object_layout.h"
#include "bzr_hooks_internal.h"
#include "engine_globals.h"
#include "game_state.h"
#include "openshim_ini.h"
#include "openshim_preset_migration.h"
#include "openshim_assets.h"
#include "terrain_proxy.h"
#include "terrain_tile_blend.h"
#include "bzr_options_ui.h"
#include "remembered_mesh_bounds_table.h"
#include "patches.h"
#include "patcher.h"
#include "fog_wake_feature.h"
#include "render_queue_trace.h"
#include "mp_vehicle_preview_fix.h"
#include "shim_log.h"
#include "x86_length.h"
#include "ogre_shader_cache.h"
#include "ogre_enhanced_light_selection.h"
#include "render_effect_intent.h"
#include "render_profile_runtime.h"
#include "native_ui.h"
#include "../engine/native_ui_validation.h"
#include "ogre_animation_profiler.h"
#include "ogre_profiler_algorithms.h"
#include "weapon_convergence.h"
#include "headlight_falloff.h"
#include "shadow_far_distance.h"
#include "sun_flash.h"
#include "chunk_batch_invalidation.h"
#include "ai_range_policy.h"
#include "lcbench_safety_policy.h"
#include "hook_engine.h"
#include "ui_performance.h"
#include "openshim_events.h"
#include "player_kill_trace.h"
#include "net_optimizer.h"
#include "pond_class_label.h"
#include <Windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <array>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <intrin.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <exception>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <new>
#include <string>
#include <string_view>
#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace BZROpenShim
{
	using FnCraftUndeploy = void(__fastcall*)(void* craft);

    using FnProducerPredicate = bool(__thiscall*)(void* thisPtr);

	static FnTugPostLoad g_BzrFn_TugPostLoadOriginal = nullptr;

	static FnRigProcessCleanUState2 g_BzrFn_RigProcessCleanUState2Original = nullptr;

	static FnGameObjectHandleGetObj g_BzrFn_GameObjectHandleGetObj = nullptr;

    namespace Hooks
    {
        // ScriptUtils::CanBuild/IsBusy accept the four legacy producer
        // signatures but omit the base Producer signature (PROD). The two
        // functions are adjacent in settled Redux 2.2.301 and are identical
        // on GOG and the settled Steam image.
        constexpr uintptr_t kGogScriptCanBuildAddr = 0x005CB4E0;

        constexpr uintptr_t kGogScriptIsBusyAddr = 0x005CB550;

        constexpr uintptr_t kGogProducerCanBuildAddr = 0x004738B0;

        constexpr uintptr_t kGogProducerIsBusyAddr = 0x004723D0;

        constexpr uint32_t kProducerClassSignature = 0x50524F44u; // 'PROD'

        constexpr size_t kScriptProducerPredicateDetourLen = 9;

        // Splinter (spraybomb) undead bug (#46). SprayBuilding::Simulate keeps
        // spinning its payload fire loop after the deployed splinter is damaged
        // below zero because it overrides Building::Simulate without preserving
        // the base destroyed/remove gate. GOG addresses re-derived via RTTI on
        // the live 2.2.301 exe (advisory-PDB VA 0x005242F0 had drifted): the
        // SprayBuilding vtable is 0x008881EC and Simulate is slot 15.
        constexpr uintptr_t kGogSprayBuildingSimulateAddr = 0x005DA6E0;

		constexpr uintptr_t kSprayBuildingSimulateVtableSlotAddr = 0x00888228;

		// Tug::PostLoad restores the cargo relationship but does not reconcile a
		// newly created/loaded tug's deployment state.  With cargo attached and
		// state==UNDEPLOYED, a later Deploy command starts the *load* transition
		// instead of the drop transition.  This is the native equivalent of the
		// long-standing Lua workaround `if HasCargo(tug) then Deploy(tug) end`.
		// Current Redux 2.2.301 Tug primary vtable: 0x00889008; PostLoad is slot 22.
		constexpr uintptr_t kGogTugPostLoadAddr = 0x005EC430;

		constexpr uintptr_t kTugVtableAddr = 0x00889008;

		constexpr uintptr_t kTugPostLoadVtableSlotAddr = 0x00889060;

		constexpr size_t kTugDeployStateOffset = 0x228;

		constexpr size_t kTugControlBlockOffset = 0x230;

		constexpr size_t kTugControlDeployOffset = 0xE0;

		constexpr size_t kTugCargoOffset = 0x300;

		// Constructor recycle leaves the losing rig permanently deployed. Two
		// Constructors ordered onto the same building each run their own unbuild
		// countdown; the first to expire deletes the building, and the other is
		// left deployed for the rest of the mission, accepting orders it can never
		// act on.
		//
		// The only undeploy on the recycle path is in UnBuild::DoNear's completion
		// branch (0x0049EC50), reached when ConstructionRig::IsUnbuilding goes
		// false. A rig whose target died first never reaches it: the task reports
		// itself done on the next AI tick, RigProcess leaves the unbuild state, and
		// RigProcess::CleanUState2 (0x0049EE10) destroys the task before DoNear is
		// ticked again. CleanUState2 calls ConstructionRig::CancelUnbuild
		// (0x0049CDB0), so the unbuild handle is cleared correctly -- but nothing
		// undeploys the craft.
		//
		// The detour asks for the undeploy that the completion branch would have
		// asked for, and only when the recycle target no longer resolves, so every
		// other way of leaving this state stays stock.
		//
		// Reproduced with controls by reverse_engineering/run_lcroad_recycle.ps1.
		constexpr uintptr_t kGogRigProcessCleanUState2Addr = 0x0049EE10;

		constexpr uintptr_t kGogGameObjectHandleGetObjAddr = 0x00462630;

		constexpr size_t kRigProcessCleanUState2DetourLen = 6;

		constexpr size_t kRigProcessCraftOffset = 0x34;

		constexpr size_t kRigProcessUnbuildTargetHandleOffset = 0x3C;

		// Craft deploy state, same field as kCraftDeployStateOffset further down
		// this file; declared here because this fix sits above that declaration.
		constexpr size_t kCraftDeployStateOffsetEarly = 0x228;

		constexpr uint32_t kCraftDeployStateDeploying = 1;

		constexpr uint32_t kCraftDeployStateDeployed = 2;

		// Craft::Undeploy, vtable byte offset 0x64 (index 25). Confirmed live: the
		// slot resolves to 0x004AE330, which asks the control block for an undeploy
		// only while the craft is deployed (2) or still deploying (1).
		constexpr size_t kCraftUndeployVtableIndex = 0x64 / sizeof(void*);

		// APC::Simulate checks a selected target before its existing nearby-enemy
		// scan.  If that target is allied, both relation failures jump straight to
		// the "cannot deploy" result.  Retarget those two stock branches to the
		// existing no-target scan so a selected ally does not mask nearby enemies.
		constexpr uintptr_t kGogApcTargetActualTeamRejectBranchAddr = 0x004700E6;

		constexpr uintptr_t kGogApcTargetPerceivedTeamRejectBranchAddr = 0x00470108;

		constexpr uint8_t kGogApcTargetActualTeamRejectOriginal[6] =
			{ 0x0F, 0x84, 0xA5, 0x00, 0x00, 0x00 };

		constexpr uint8_t kGogApcTargetActualTeamRejectPatched[6] =
			{ 0x0F, 0x84, 0xC0, 0x00, 0x00, 0x00 };

		constexpr uint8_t kGogApcTargetPerceivedTeamRejectOriginal[6] =
			{ 0x0F, 0x84, 0x83, 0x00, 0x00, 0x00 };

		constexpr uint8_t kGogApcTargetPerceivedTeamRejectPatched[6] =
			{ 0x0F, 0x84, 0x9E, 0x00, 0x00, 0x00 };

        // Building::Simulate reads flags at [[this+0xF4]+0x14] and early-outs on
        // destroyed (0x1000000) / marked-for-remove (0x200) by dispatching the
        // stock explode/remove virtuals.
        constexpr size_t kBuildingStateBlockOffset = 0xF4;

        constexpr size_t kBuildingStateFlagsOffset = 0x14;

        constexpr uint32_t kBuildingDestroyedOrRemoveMask = 0x01000200u;

        constexpr size_t kAIUnitRemoveDetourLen = 11;

        constexpr uintptr_t kAiGameInitialisedAddr = 0x00930F08;

        constexpr uintptr_t kAiTeamTableAddr = 0x00920F04;

        constexpr uintptr_t kAiTeamDataBaseAddr = 0x02CE9B18;

        constexpr size_t kAiTeamDataStride = 0x1E0;

        constexpr size_t kUnitTypeOffset = 0x08;

        constexpr size_t kUnitTeamOffset = 0x10;

        constexpr size_t kUnitTypeAbilitiesOffset = 0x70;

        constexpr size_t kUnitAiConstructTypeOffset = 0x30;

        constexpr size_t kUnitAiConstructCostOffset = 0x34;

        constexpr size_t kUnitAiConstructingOffset = 0x38;

        constexpr size_t kUnitAiReservedAreaOffset = 0x3C;

        constexpr size_t kUnitAiAccountOffset = 0x40;

        constexpr uint32_t kConstructorAbilityMask = 0x2;

        struct ConstructorCleanupSnapshot
        {
            int teamId = 0;
            void* teamPtr = nullptr;
            uint32_t constructType = 0;
            uint32_t constructCost = 0;
            uint32_t constructing = 0;
            uint32_t reservedArea = 0;
            uint32_t account = 0;
        };

        static InlineDetour32 g_AIUnitRemoveDetour = {};

        static InlineDetour32 g_RigProcessCleanUState2Detour = {};

        static bool g_ApcAlliedTargetDeployPatchActive = false;

        static bool TryGetGameObjectClassSignature(void* objectPtr, uint32_t& outSignature)
        {
            outSignature = 0;
            if (!objectPtr)
                return false;

            using FnGetObjectClass = void* (__thiscall*)(void* classInterface);
            __try
            {
                void* classInterface =
                    reinterpret_cast<uint8_t*>(objectPtr) + 0x18;
                void** vtable = *reinterpret_cast<void***>(classInterface);
                if (!vtable || !vtable[0])
                    return false;

                void* objectClass =
                    reinterpret_cast<FnGetObjectClass>(vtable[0])(classInterface);
                if (!objectClass)
                    return false;

                outSignature = *reinterpret_cast<const uint32_t*>(
                    reinterpret_cast<const uint8_t*>(objectClass) + 0x14);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool CallProducerPredicateForBaseProducer(int handle,
                                                         FnProducerPredicate predicate)
        {
            if (!predicate)
                return false;

            void* objectPtr = GameObjectFromHandleGog(handle);
            uint32_t signature = 0;
            if (!objectPtr ||
                !TryGetGameObjectClassSignature(objectPtr, signature) ||
                signature != kProducerClassSignature)
            {
                return false;
            }

            __try
            {
                return predicate(objectPtr);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool __cdecl ScriptCanBuildProducerHook(int handle)
        {
            if (g_BzrFn_ScriptCanBuildOriginal &&
                g_BzrFn_ScriptCanBuildOriginal(handle))
            {
                return true;
            }

            return CallProducerPredicateForBaseProducer(
                handle,
                reinterpret_cast<FnProducerPredicate>(kGogProducerCanBuildAddr));
        }

        static bool __cdecl ScriptIsBusyProducerHook(int handle)
        {
            if (g_BzrFn_ScriptIsBusyOriginal &&
                g_BzrFn_ScriptIsBusyOriginal(handle))
            {
                return true;
            }

            return CallProducerPredicateForBaseProducer(
                handle,
                reinterpret_cast<FnProducerPredicate>(kGogProducerIsBusyAddr));
        }

        void InstallProducerScriptPredicateHooksIfPossible()
        {
            if (!g_ProducerScriptPredicateHooksEnabled)
                return;

            if (g_ProducerScriptPredicateHooksInstalled)
                return;

            static const uint8_t kExpectedPredicateEntry[
                kScriptProducerPredicateDetourLen] =
            {
                0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x08, 0x8B, 0x45, 0x08
            };
            static const uint8_t kExpectedCanBuildMethod[9] =
            {
                0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x08, 0x89, 0x4D, 0xFC
            };
            static const uint8_t kExpectedIsBusyMethod[7] =
            {
                0x55, 0x8B, 0xEC, 0x51, 0x89, 0x4D, 0xFC
            };

            if (!ExpectedBytesMatchAt(kGogProducerCanBuildAddr,
                                      kExpectedCanBuildMethod,
                                      sizeof(kExpectedCanBuildMethod)) ||
                !ExpectedBytesMatchAt(kGogProducerIsBusyAddr,
                                      kExpectedIsBusyMethod,
                                      sizeof(kExpectedIsBusyMethod)))
            {
                return;
            }

            if (!g_ScriptCanBuildDetour.trampoline &&
                !InstallInlineDetour32(g_ScriptCanBuildDetour,
                                       kGogScriptCanBuildAddr,
                                       reinterpret_cast<void*>(ScriptCanBuildProducerHook),
                                       kScriptProducerPredicateDetourLen,
                                       kExpectedPredicateEntry,
                                       sizeof(kExpectedPredicateEntry)))
            {
                return;
            }
            g_BzrFn_ScriptCanBuildOriginal =
                reinterpret_cast<FnScriptProducerPredicate>(
                    g_ScriptCanBuildDetour.trampoline);

            if (!g_ScriptIsBusyDetour.trampoline &&
                !InstallInlineDetour32(g_ScriptIsBusyDetour,
                                       kGogScriptIsBusyAddr,
                                       reinterpret_cast<void*>(ScriptIsBusyProducerHook),
                                       kScriptProducerPredicateDetourLen,
                                       kExpectedPredicateEntry,
                                       sizeof(kExpectedPredicateEntry)))
            {
                return;
            }
            g_BzrFn_ScriptIsBusyOriginal =
                reinterpret_cast<FnScriptProducerPredicate>(
                    g_ScriptIsBusyDetour.trampoline);

            g_ProducerScriptPredicateHooksInstalled =
                g_BzrFn_ScriptCanBuildOriginal && g_BzrFn_ScriptIsBusyOriginal;
            if (g_ProducerScriptPredicateHooksInstalled)
            {
                Log(L"[PRODSCRIPT] Added PROD support to ScriptUtils CanBuild/IsBusy canBuild=0x%08X isBusy=0x%08X\n",
                    static_cast<uint32_t>(kGogScriptCanBuildAddr),
                    static_cast<uint32_t>(kGogScriptIsBusyAddr));
            }
        }

        static bool ShouldTraceSplinterUndeadFix()
        {
            return EnvFlagEnabled("OPENSHIM_TRACE_SPLINTER_UNDEAD") ||
                   EnvFlagEnabled("BZR_TRACE_SPLINTER_UNDEAD");
        }

        // Splinter (spraybomb) undead fix (#46): a deployed splinter that has
        // been damaged below zero is still marked dead by Building::DamageAlloc
        // (flags |= 0x1000200), but SprayBuilding::Simulate overrides
        // Building::Simulate without preserving the base destroyed/remove gate,
        // so it keeps spawning payload ordnance until ammo depletion. Restore the
        // missing gate: when the object is destroyed/marked-for-remove, route the
        // frame through stock Building::Simulate (which dispatches the explode /
        // remove virtuals and returns) instead of the payload fire loop.
        static void RunSprayBuildingSimulateWithDeadGate(void* sprayPtr, float dt)
        {
            if (!sprayPtr || !g_BzrFn_SprayBuildingSimulateOriginal)
            {
                if (g_BzrFn_SprayBuildingSimulateOriginal)
                    g_BzrFn_SprayBuildingSimulateOriginal(sprayPtr, dt);
                return;
            }

            bool routeToBase = false;
            if (g_SplinterUndeadFixActive && g_BzrFn_BuildingSimulate)
            {
                __try
                {
                    auto* stateBlock = *reinterpret_cast<void* const*>(
                        reinterpret_cast<const uint8_t*>(sprayPtr) + kBuildingStateBlockOffset);
                    if (stateBlock)
                    {
                        const uint32_t flags = *reinterpret_cast<const uint32_t*>(
                            reinterpret_cast<const uint8_t*>(stateBlock) + kBuildingStateFlagsOffset);
                        routeToBase = (flags & kBuildingDestroyedOrRemoveMask) != 0;
                    }
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    routeToBase = false;
                }
            }

            if (routeToBase)
            {
                if (ShouldTraceSplinterUndeadFix())
                {
                    const long remaining = InterlockedDecrement(&g_SplinterUndeadTraceBudget);
                    if (remaining >= 0)
                        Log(L"[SPLINTER] Dead splinter routed to base Building::Simulate remaining=%ld unit=0x%08X\n",
                            remaining,
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(sprayPtr)));
                }
                g_BzrFn_BuildingSimulate(sprayPtr, dt);
                return;
            }

            g_BzrFn_SprayBuildingSimulateOriginal(sprayPtr, dt);
        }

        void __fastcall SprayBuildingSimulateUndeadFixHook(void* thisPtr, void* /*edx*/, float dt)
        {
            RunSprayBuildingSimulateWithDeadGate(thisPtr, dt);
        }

		void InstallSplinterUndeadFixIfPossible()
        {
            if (!g_SplinterUndeadFixEnabled)
                return;
            if (g_SprayBuildingSimulateHookInstalled)
                return;

            if (!g_BzrFn_SprayBuildingSimulateOriginal)
                g_BzrFn_SprayBuildingSimulateOriginal =
                    reinterpret_cast<FnSprayBuildingSimulate>(kGogSprayBuildingSimulateAddr);
            if (!g_BzrFn_BuildingSimulate)
                g_BzrFn_BuildingSimulate =
                    reinterpret_cast<FnShieldTowerSimulate>(kGogBuildingSimulateAddr);

            void* current = nullptr;
            __try
            {
                current = *reinterpret_cast<void**>(kSprayBuildingSimulateVtableSlotAddr);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                current = nullptr;
            }

            if (current != reinterpret_cast<void*>(SprayBuildingSimulateUndeadFixHook) &&
                current != reinterpret_cast<void*>(kGogSprayBuildingSimulateAddr))
            {
                Log(L"[SPLINTER] SprayBuilding::Simulate vtable mismatch slot=0x%08X current=0x%08X expected=0x%08X\n",
                    static_cast<uint32_t>(kSprayBuildingSimulateVtableSlotAddr),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)),
                    static_cast<uint32_t>(kGogSprayBuildingSimulateAddr));
                return;
            }

            const bool patched =
                (current == reinterpret_cast<void*>(SprayBuildingSimulateUndeadFixHook)) ||
                WritePointerValue(kSprayBuildingSimulateVtableSlotAddr,
                                  reinterpret_cast<void*>(SprayBuildingSimulateUndeadFixHook));
            g_SprayBuildingSimulateHookInstalled =
                patched &&
                g_BzrFn_SprayBuildingSimulateOriginal &&
                g_BzrFn_BuildingSimulate;

            if (g_SprayBuildingSimulateHookInstalled)
            {
                Log(L"[SPLINTER] Installed splinter undead fix slot=0x%08X original=0x%08X base=0x%08X trace=%hs\n",
                    static_cast<uint32_t>(kSprayBuildingSimulateVtableSlotAddr),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_BzrFn_SprayBuildingSimulateOriginal)),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_BzrFn_BuildingSimulate)),
                    BoolText(ShouldTraceSplinterUndeadFix()));
            }
		}

		bool __fastcall TugPostLoadCargoDeployFixHook(void* thisPtr, void* /*edx*/)
		{
			const bool loaded = g_BzrFn_TugPostLoadOriginal
				? g_BzrFn_TugPostLoadOriginal(thisPtr)
				: false;

			if (!loaded || !g_TugCargoPostLoadFixActive || !thisPtr)
				return loaded;

			bool armedDeploy = false;
			__try
			{
				auto* tug = static_cast<uint8_t*>(thisPtr);
				const bool hasCargo =
					*reinterpret_cast<void**>(tug + kTugCargoOffset) != nullptr;
				const uint32_t state =
					*reinterpret_cast<const uint32_t*>(tug + kTugDeployStateOffset);
				auto* control =
					*reinterpret_cast<uint8_t**>(tug + kTugControlBlockOffset);

				// Craft::Deploy only arms control.deploy while UNDEPLOYED (state 0).
				// Let Tug::Simulate perform the stock animation and state transition.
				if (hasCargo && state == 0 && control)
				{
					*reinterpret_cast<uint32_t*>(control + kTugControlDeployOffset) = 1;
					armedDeploy = true;
				}
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
				armedDeploy = false;
			}

			if (armedDeploy)
			{
				const long remaining = InterlockedDecrement(&g_TugCargoPostLoadLogBudget);
				if (remaining >= 0)
					Log(L"[TUGCARGO] Armed stock deploy transition after cargo PostLoad remaining=%ld tug=0x%08X\n",
						remaining,
						static_cast<uint32_t>(reinterpret_cast<uintptr_t>(thisPtr)));
			}

			return loaded;
		}

		// RigProcess::CleanUState2. Runs whenever the constructor leaves its
		// unbuild state. Stock cancels the unbuild here but never undeploys, and
		// the only undeploy on the recycle path lives in UnBuild::DoNear's
		// completion branch -- which a rig whose target died first never reaches,
		// because this teardown removes its task before it is ticked again.
		//
		// Scoped deliberately to the one case that is broken: the recycle target
		// no longer resolves. Every other way of leaving this state -- finishing
		// the unbuild, or the player replacing the order -- is left stock.
		void __fastcall RigProcessCleanUState2FixHook(void* process)
		{
			bool undeployed = false;
			uint32_t targetHandle = 0;
			void* rig = nullptr;

			if (g_ConstructorRecycleStaleTargetFixActive && process &&
				g_BzrFn_GameObjectHandleGetObj)
			{
				__try
				{
					auto* bytes = static_cast<uint8_t*>(process);
					rig = *reinterpret_cast<void**>(bytes + kRigProcessCraftOffset);
					targetHandle = *reinterpret_cast<uint32_t*>(
						bytes + kRigProcessUnbuildTargetHandleOffset);

					if (rig && targetHandle != 0 &&
						g_BzrFn_GameObjectHandleGetObj(targetHandle) == nullptr)
					{
						const uint32_t deployState = *reinterpret_cast<uint32_t*>(
							static_cast<uint8_t*>(rig) + kCraftDeployStateOffsetEarly);

						// Only a rig that is deployed or still deploying has an
						// undeploy to ask for. One already undeploying (3) or
						// undeployed (0) is left alone, so the rig that finished
						// its unbuild normally is never touched.
						if (deployState == kCraftDeployStateDeployed ||
							deployState == kCraftDeployStateDeploying)
						{
							auto** vtable = *reinterpret_cast<void***>(rig);
							auto undeploy = reinterpret_cast<FnCraftUndeploy>(
								vtable[kCraftUndeployVtableIndex]);
							undeploy(rig);
							undeployed = true;
						}
					}
				}
				__except (EXCEPTION_EXECUTE_HANDLER)
				{
					undeployed = false;
				}
			}

			if (g_BzrFn_RigProcessCleanUState2Original)
				g_BzrFn_RigProcessCleanUState2Original(process);

			if (undeployed)
			{
				const long remaining =
					InterlockedDecrement(&g_ConstructorRecycleStaleTargetLogBudget);
				if (remaining >= 0)
					Log(L"[RIGRECYCLE] Undeployed constructor whose recycle target vanished remaining=%ld process=0x%08X rig=0x%08X handle=0x%08X\n",
						remaining,
						static_cast<uint32_t>(reinterpret_cast<uintptr_t>(process)),
						static_cast<uint32_t>(reinterpret_cast<uintptr_t>(rig)),
						targetHandle);
			}
		}

		void InstallConstructorRecycleStaleTargetFixIfPossible()
		{
			if (!g_ConstructorRecycleStaleTargetFixEnabled ||
				g_ConstructorRecycleStaleTargetFixInstalled)
				return;

			// Guard on instructions, not on the operands they carry. The entry
			// prologue alone is shared by thousands of functions, so identity
			// comes from the body: the load of the craft at +0x34 feeding the
			// call to ConstructionRig::CancelUnbuild, and the load of the task
			// pointer at +0x38 that this function exists to destroy.
			static const uint8_t kExpectedEntryBytes[kRigProcessCleanUState2DetourLen] =
			{
				0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x10
			};
			// mov ecx,[eax+0x34] ; call ConstructionRig::CancelUnbuild (0x0049CDB0)
			static const uint8_t kExpectedCancelUnbuildCallBytes[] =
			{
				0x8B, 0x48, 0x34, 0xE8, 0x8C, 0xDF, 0xFF, 0xFF
			};
			// mov edx,[ecx+0x38]  -- the UnBuild task about to be deleted
			static const uint8_t kExpectedTaskLoadBytes[] =
			{
				0x8B, 0x51, 0x38
			};
			// GameObjectHandle::GetObj prologue: push ebp; mov ebp,esp; push ecx;
			// mov eax,[ebp+8]; push eax  -- __cdecl, one stack argument.
			static const uint8_t kExpectedGetObjBytes[] =
			{
				0x55, 0x8B, 0xEC, 0x51, 0x8B, 0x45, 0x08, 0x50
			};

			const uintptr_t entry = kGogRigProcessCleanUState2Addr;
			if (!ExpectedBytesMatchAt(entry, kExpectedEntryBytes, sizeof(kExpectedEntryBytes)) ||
				!ExpectedBytesMatchAt(entry + 0x0C, kExpectedCancelUnbuildCallBytes, sizeof(kExpectedCancelUnbuildCallBytes)) ||
				!ExpectedBytesMatchAt(entry + 0x17, kExpectedTaskLoadBytes, sizeof(kExpectedTaskLoadBytes)) ||
				!ExpectedBytesMatchAt(kGogGameObjectHandleGetObjAddr, kExpectedGetObjBytes, sizeof(kExpectedGetObjBytes)))
			{
				if (!g_ConstructorRecycleStaleTargetMismatchLogged)
				{
					Log(L"[RIGRECYCLE] RigProcess::CleanUState2 bytes not settled at 0x%08X; deferring recycle undeploy fix\n",
						static_cast<uint32_t>(entry));
					g_ConstructorRecycleStaleTargetMismatchLogged = true;
				}
				return;
			}

			if (!g_BzrFn_GameObjectHandleGetObj)
				g_BzrFn_GameObjectHandleGetObj =
					reinterpret_cast<FnGameObjectHandleGetObj>(kGogGameObjectHandleGetObjAddr);

			if (!InstallInlineDetour32(g_RigProcessCleanUState2Detour,
									   entry,
									   reinterpret_cast<void*>(RigProcessCleanUState2FixHook),
									   kRigProcessCleanUState2DetourLen,
									   kExpectedEntryBytes,
									   sizeof(kExpectedEntryBytes)))
			{
				Log(L"[RIGRECYCLE] Failed installing RigProcess::CleanUState2 detour at 0x%08X\n",
					static_cast<uint32_t>(entry));
				return;
			}

			g_BzrFn_RigProcessCleanUState2Original =
				reinterpret_cast<FnRigProcessCleanUState2>(
					g_RigProcessCleanUState2Detour.trampoline);
			g_ConstructorRecycleStaleTargetFixInstalled =
				(g_BzrFn_RigProcessCleanUState2Original != nullptr);

			if (g_ConstructorRecycleStaleTargetFixInstalled)
			{
				g_ConstructorRecycleStaleTargetMismatchLogged = false;
				Log(L"[RIGRECYCLE] Installed constructor recycle undeploy fix entry=0x%08X trampoline=0x%08X getObj=0x%08X\n",
					static_cast<uint32_t>(entry),
					static_cast<uint32_t>(reinterpret_cast<uintptr_t>(
						g_RigProcessCleanUState2Detour.trampoline)),
					static_cast<uint32_t>(kGogGameObjectHandleGetObjAddr));
			}
		}

		void InstallTugCargoPostLoadFixIfPossible()
		{
			if (!g_TugCargoPostLoadFixEnabled || g_TugCargoPostLoadFixInstalled)
				return;

			if (!VtableTypeNameMatches(kTugVtableAddr, ".?AVTug@@"))
			{
				Log(L"[TUGCARGO] Tug RTTI mismatch vtable=0x%08X; cargo PostLoad fix skipped\n",
					static_cast<uint32_t>(kTugVtableAddr));
				return;
			}

			void* current = nullptr;
			__try { current = *reinterpret_cast<void**>(kTugPostLoadVtableSlotAddr); }
			__except (EXCEPTION_EXECUTE_HANDLER) { current = nullptr; }

			if (current != reinterpret_cast<void*>(TugPostLoadCargoDeployFixHook) &&
				current != reinterpret_cast<void*>(kGogTugPostLoadAddr))
			{
				Log(L"[TUGCARGO] Tug::PostLoad vtable mismatch slot=0x%08X current=0x%08X expected=0x%08X\n",
					static_cast<uint32_t>(kTugPostLoadVtableSlotAddr),
					static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)),
					static_cast<uint32_t>(kGogTugPostLoadAddr));
				return;
			}

			if (!g_BzrFn_TugPostLoadOriginal)
				g_BzrFn_TugPostLoadOriginal =
					reinterpret_cast<FnTugPostLoad>(kGogTugPostLoadAddr);

			g_TugCargoPostLoadFixInstalled =
				(current == reinterpret_cast<void*>(TugPostLoadCargoDeployFixHook)) ||
				WritePointerValue(kTugPostLoadVtableSlotAddr,
					reinterpret_cast<void*>(TugPostLoadCargoDeployFixHook));

			if (g_TugCargoPostLoadFixInstalled)
			{
				Log(L"[TUGCARGO] Installed cargo PostLoad deploy-state fix slot=0x%08X original=0x%08X\n",
					static_cast<uint32_t>(kTugPostLoadVtableSlotAddr),
					static_cast<uint32_t>(kGogTugPostLoadAddr));
			}
		}

		// Writes both APC relation branches together. A half-applied pair leaves
		// one relation test rewritten and the other stock, which is neither the
		// fixed behaviour nor the stock one, so both writes are reported as one.
		static bool WriteApcAlliedTargetDeployBranches(bool patched)
		{
			const bool firstOk = WritePatchBytes(
				kGogApcTargetActualTeamRejectBranchAddr,
				patched ? kGogApcTargetActualTeamRejectPatched
				        : kGogApcTargetActualTeamRejectOriginal,
				sizeof(kGogApcTargetActualTeamRejectPatched));
			const bool secondOk = WritePatchBytes(
				kGogApcTargetPerceivedTeamRejectBranchAddr,
				patched ? kGogApcTargetPerceivedTeamRejectPatched
				        : kGogApcTargetPerceivedTeamRejectOriginal,
				sizeof(kGogApcTargetPerceivedTeamRejectPatched));

			if (firstOk && secondOk)
				return true;

			Log(L"[APCDEPLOY] Failed writing allied-target deployment branches patched=%hs first=%hs second=%hs\n",
				BoolText(patched), BoolText(firstOk), BoolText(secondOk));
			return false;
		}

		// Multiplayer gate. Unlike the other four [Fixes] entries this one is two
		// rewritten branch displacements rather than a flag inside a hook, so the
		// stock bytes have to go back for the duration of a network game. Only
		// touches .text when the wanted state actually differs.
		void RefreshApcAlliedTargetDeployFixState()
		{
			if (!g_ApcAlliedTargetDeployFixInstalled)
				return;

			const bool wantActive =
				g_ApcAlliedTargetDeployFixEnabled && IsSinglePlayerSession();
			if (wantActive == g_ApcAlliedTargetDeployPatchActive)
				return;

			if (!WriteApcAlliedTargetDeployBranches(wantActive))
				return;

			g_ApcAlliedTargetDeployPatchActive = wantActive;
			Log(L"[APCDEPLOY] Allied-target deployment branches %hs (%hs)\n",
				wantActive ? "applied" : "reverted to stock",
				wantActive ? "single-player" : "network game");
		}

		void InstallApcAlliedTargetDeployFixIfPossible()
		{
			if (!g_ApcAlliedTargetDeployFixEnabled || g_ApcAlliedTargetDeployFixInstalled)
				return;

			const bool firstOriginal = ExpectedBytesMatchAt(
				kGogApcTargetActualTeamRejectBranchAddr,
				kGogApcTargetActualTeamRejectOriginal,
				sizeof(kGogApcTargetActualTeamRejectOriginal));
			const bool firstPatched = ExpectedBytesMatchAt(
				kGogApcTargetActualTeamRejectBranchAddr,
				kGogApcTargetActualTeamRejectPatched,
				sizeof(kGogApcTargetActualTeamRejectPatched));
			const bool secondOriginal = ExpectedBytesMatchAt(
				kGogApcTargetPerceivedTeamRejectBranchAddr,
				kGogApcTargetPerceivedTeamRejectOriginal,
				sizeof(kGogApcTargetPerceivedTeamRejectOriginal));
			const bool secondPatched = ExpectedBytesMatchAt(
				kGogApcTargetPerceivedTeamRejectBranchAddr,
				kGogApcTargetPerceivedTeamRejectPatched,
				sizeof(kGogApcTargetPerceivedTeamRejectPatched));

			if ((!firstOriginal && !firstPatched) || (!secondOriginal && !secondPatched))
			{
				Log(L"[APCDEPLOY] APC::Simulate relation branches drifted; allied-target fix skipped first=0x%08X second=0x%08X\n",
					static_cast<uint32_t>(kGogApcTargetActualTeamRejectBranchAddr),
					static_cast<uint32_t>(kGogApcTargetPerceivedTeamRejectBranchAddr));
				return;
			}

			// Both guards passed, so the site is ours to drive. Seed the active
			// flag from what the bytes already say before handing the write to the
			// gate: a re-resolve with the patch already in place must not read as
			// "not applied yet" and then skip the revert a network game needs.
			g_ApcAlliedTargetDeployPatchActive = firstPatched && secondPatched;
			g_ApcAlliedTargetDeployFixInstalled = true;
			RefreshApcAlliedTargetDeployFixState();
			if (g_ApcAlliedTargetDeployPatchActive)
			{
				Log(L"[APCDEPLOY] Allied targets now fall through to stock nearby-enemy deployment scan (SP-only)\n");
			}
		}

        bool ShouldTraceConstructorRemoteBuildFix()
        {
            return EnvFlagEnabled("OPENSHIM_TRACE_CONSTRUCTOR_REMOTE_BUILD") ||
                   EnvFlagEnabled("OPENSHIM_TRACE_CONSTRUCTOR_BUILD_CLEANUP") ||
                   EnvFlagEnabled("BZR_TRACE_CONSTRUCTOR_REMOTE_BUILD");
        }

        static void TraceConstructorRemoteBuildEvent(const char* action,
                                                     const char* reason,
                                                     void* unitPtr,
                                                     const ConstructorCleanupSnapshot* snapshot)
        {
            if (!ShouldTraceConstructorRemoteBuildFix())
                return;

            const long remaining = InterlockedDecrement(&g_ConstructorRemoteBuildTraceBudget);
            if (remaining < 0)
                return;

            const ConstructorCleanupSnapshot empty = {};
            const ConstructorCleanupSnapshot& current = snapshot ? *snapshot : empty;
            Log(L"[AICONSTRUCT] trace remaining=%ld action=%hs reason=%hs team=%d teamPtr=0x%08X unit=0x%08X constructType=%u cost=%u constructing=%u account=%u reservedArea=%u helpers=end:%hs reserved:%hs refund:%hs add:%hs stop:%hs\n",
                remaining,
                action ? action : "unknown",
                reason ? reason : "unspecified",
                current.teamId,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current.teamPtr)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(unitPtr)),
                current.constructType,
                current.constructCost,
                current.constructing,
                current.account,
                current.reservedArea,
                BoolText(g_BzrFn_AIBuildConstructionEnd != nullptr),
                BoolText(g_BzrFn_AIBuildReservedAreaRemove != nullptr),
                BoolText(g_BzrFn_AISpentCreditRefund != nullptr),
                BoolText(g_BzrFn_AIBuildUnassignedCCAdd != nullptr),
                BoolText(g_BzrFn_UnitsSOrderStop != nullptr));
        }

        static bool TryCaptureConstructorCleanupSnapshot(void* unitPtr,
                                                        ConstructorCleanupSnapshot& outSnapshot,
                                                        const char** outReason)
        {
            outSnapshot = {};
            if (outReason)
                *outReason = "unknown";
            if (!unitPtr)
            {
                if (outReason)
                    *outReason = "null_unit";
                return false;
            }

            __try
            {
                if (*reinterpret_cast<const uint32_t*>(kAiGameInitialisedAddr) == 0)
                {
                    if (outReason)
                        *outReason = "ai_not_ready";
                    return false;
                }

                auto* unitBytes = reinterpret_cast<const uint8_t*>(unitPtr);
                const int teamId =
                    static_cast<int>(*reinterpret_cast<const int8_t*>(unitBytes + kUnitTeamOffset));
                if (teamId < 0)
                {
                    if (outReason)
                        *outReason = "team_invalid";
                    return false;
                }

                auto* teamAicontrol =
                    reinterpret_cast<const uint8_t*>(kAiTeamDataBaseAddr + (teamId * kAiTeamDataStride));
                if (*teamAicontrol == 0)
                {
                    if (outReason)
                        *outReason = "team_not_ai";
                    return false;
                }

                auto* teamTable = reinterpret_cast<void* const*>(kAiTeamTableAddr);
                outSnapshot.teamPtr = teamTable[teamId];
                if (!outSnapshot.teamPtr)
                {
                    if (outReason)
                        *outReason = "team_ptr_missing";
                    return false;
                }

                void* typePtr = *reinterpret_cast<void* const*>(unitBytes + kUnitTypeOffset);
                if (!typePtr)
                {
                    if (outReason)
                        *outReason = "missing_type";
                    return false;
                }

                const uint32_t abilities =
                    *reinterpret_cast<const uint32_t*>(reinterpret_cast<const uint8_t*>(typePtr) +
                                                       kUnitTypeAbilitiesOffset);
                if ((abilities & kConstructorAbilityMask) == 0)
                {
                    if (outReason)
                        *outReason = "not_constructor";
                    return false;
                }

                outSnapshot.teamId = teamId;
                outSnapshot.constructType =
                    *reinterpret_cast<const uint32_t*>(unitBytes + kUnitAiConstructTypeOffset);
                outSnapshot.constructCost =
                    *reinterpret_cast<const uint32_t*>(unitBytes + kUnitAiConstructCostOffset);
                outSnapshot.constructing =
                    *reinterpret_cast<const uint32_t*>(unitBytes + kUnitAiConstructingOffset);
                outSnapshot.reservedArea =
                    *reinterpret_cast<const uint32_t*>(unitBytes + kUnitAiReservedAreaOffset);
                outSnapshot.account =
                    *reinterpret_cast<const uint32_t*>(unitBytes + kUnitAiAccountOffset);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                outSnapshot = {};
                if (outReason)
                    *outReason = "access_fault";
                return false;
            }

            if (outReason)
                *outReason = "eligible";
            return true;
        }

        static bool TryApplyConstructorRemoteBuildDeathCleanup(void* unitPtr,
                                                               ConstructorCleanupSnapshot& outSnapshot,
                                                               const char** outReason)
        {
            outSnapshot = {};
            if (outReason)
                *outReason = "unknown";

            if (!g_ConstructorRemoteBuildFixActive ||
                !g_BzrFn_AIBuildConstructionEnd ||
                !g_BzrFn_AIBuildReservedAreaRemove ||
                !g_BzrFn_AISpentCreditRefund ||
                !g_BzrFn_AIBuildUnassignedCCAdd ||
                !unitPtr)
            {
                if (outReason)
                    *outReason = !g_ConstructorRemoteBuildFixActive
                        ? (g_ConstructorRemoteBuildFixEnabled ? "network_game" : "fix_disabled")
                        : (!unitPtr ? "null_unit" : "helpers_missing");
                return false;
            }

            if (!TryCaptureConstructorCleanupSnapshot(unitPtr, outSnapshot, outReason))
                return false;

            if (outSnapshot.constructType == 0)
            {
                if (outReason)
                    *outReason = "construct_type_zero";
                return false;
            }

            if (outSnapshot.constructing == 0)
            {
                if (outReason)
                    *outReason = "constructing_zero";
                return false;
            }

            g_BzrFn_AIBuildConstructionEnd(outSnapshot.teamId, static_cast<int>(outSnapshot.constructType));
            g_BzrFn_AIBuildReservedAreaRemove(outSnapshot.teamId, static_cast<int>(outSnapshot.reservedArea));
            g_BzrFn_AISpentCreditRefund(outSnapshot.teamId, nullptr, unitPtr);
            if (outSnapshot.teamPtr)
                g_BzrFn_AIBuildUnassignedCCAdd(outSnapshot.teamPtr, unitPtr);
            if (g_BzrFn_UnitsSOrderStop)
                g_BzrFn_UnitsSOrderStop(unitPtr);

            auto* unitBytes = reinterpret_cast<uint8_t*>(unitPtr);
            *reinterpret_cast<uint32_t*>(unitBytes + kUnitAiConstructTypeOffset) = 0;
            *reinterpret_cast<uint32_t*>(unitBytes + kUnitAiConstructCostOffset) = 0;
            *reinterpret_cast<uint32_t*>(unitBytes + kUnitAiConstructingOffset) = 0;
            *reinterpret_cast<uint32_t*>(unitBytes + kUnitAiAccountOffset) = 0;
            *reinterpret_cast<uint32_t*>(unitBytes + kUnitAiReservedAreaOffset) = 0;

            Log(L"[AICONSTRUCT] Applied constructor death cleanup action=death_cleanup team=%d teamPtr=0x%08X unit=0x%08X constructType=%u cost=%u constructing=%u account=%u reservedArea=%u end=0x%08X reserved=0x%08X refund=0x%08X add=0x%08X stop=0x%08X\n",
                outSnapshot.teamId,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(outSnapshot.teamPtr)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(unitPtr)),
                outSnapshot.constructType,
                outSnapshot.constructCost,
                outSnapshot.constructing,
                outSnapshot.account,
                outSnapshot.reservedArea,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_BzrFn_AIBuildConstructionEnd)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_BzrFn_AIBuildReservedAreaRemove)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_BzrFn_AISpentCreditRefund)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_BzrFn_AIBuildUnassignedCCAdd)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_BzrFn_UnitsSOrderStop)));

            if (outReason)
                *outReason = "applied";
            TraceConstructorRemoteBuildEvent("death_cleanup", "applied", unitPtr, &outSnapshot);

            return true;
        }

        void __cdecl AIUnitRemoveConstructorCleanupHook(void* unitPtr)
        {
            ConstructorCleanupSnapshot snapshot = {};
            const char* reason = nullptr;
            const bool applied = TryApplyConstructorRemoteBuildDeathCleanup(unitPtr, snapshot, &reason);

            TraceConstructorRemoteBuildEvent(applied ? "forward_after_cleanup" : "fallback", reason, unitPtr, &snapshot);
            if (g_BzrFn_AIUnitRemove)
                g_BzrFn_AIUnitRemove(unitPtr);
        }

        void InstallConstructorRemoteBuildFixIfPossible()
        {
            if (!g_ConstructorRemoteBuildFixEnabled)
                return;

            if (g_ConstructorRemoteBuildFixInstalled)
                return;

            if (g_AIUnitRemoveDetour.trampoline && g_BzrFn_AIUnitRemove)
            {
                g_ConstructorRemoteBuildFixInstalled = true;
                return;
            }

            static const uint8_t kExpectedAIUnitRemoveBytes[kAIUnitRemoveDetourLen] =
            {
                0x55, 0x8B, 0xEC, 0x51, 0x83, 0x3D, 0x08, 0x0F, 0x93, 0x00, 0x00
            };

            if (!ExpectedBytesMatchAt(kGogAIUnitRemoveEntryAddr,
                                      kExpectedAIUnitRemoveBytes,
                                      sizeof(kExpectedAIUnitRemoveBytes)))
            {
                if (!g_ConstructorRemoteBuildFixMismatchLogged)
                {
                    Log(L"[AICONSTRUCT] AI_UnitRemove entry bytes not settled at 0x%08X; deferring constructor death cleanup hook\n",
                        static_cast<uint32_t>(kGogAIUnitRemoveEntryAddr));
                    g_ConstructorRemoteBuildFixMismatchLogged = true;
                }
                return;
            }

            if (!InstallInlineDetour32(g_AIUnitRemoveDetour,
                                       kGogAIUnitRemoveEntryAddr,
                                       reinterpret_cast<void*>(AIUnitRemoveConstructorCleanupHook),
                                       kAIUnitRemoveDetourLen,
                                       kExpectedAIUnitRemoveBytes,
                                       sizeof(kExpectedAIUnitRemoveBytes)))
            {
                Log(L"[AICONSTRUCT] Failed installing AI_UnitRemove cleanup hook at 0x%08X\n",
                    static_cast<uint32_t>(kGogAIUnitRemoveEntryAddr));
                return;
            }

            g_BzrFn_AIUnitRemove =
                reinterpret_cast<FnAIUnitRemove>(g_AIUnitRemoveDetour.trampoline);
            g_ConstructorRemoteBuildFixInstalled = (g_BzrFn_AIUnitRemove != nullptr);
            if (g_ConstructorRemoteBuildFixInstalled)
            {
                g_ConstructorRemoteBuildFixMismatchLogged = false;
                Log(L"[AICONSTRUCT] Installed AI_UnitRemove cleanup hook entry=0x%08X trampoline=0x%08X trace=%hs\n",
                    static_cast<uint32_t>(kGogAIUnitRemoveEntryAddr),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_AIUnitRemoveDetour.trampoline)),
                    BoolText(ShouldTraceConstructorRemoteBuildFix()));
            }
        }
    }

}
