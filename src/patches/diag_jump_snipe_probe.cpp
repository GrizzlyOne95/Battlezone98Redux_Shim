// diag_jump_snipe_probe.cpp
// BZR Open Shim - jump-sniping research probe (diagnostic only): the opt-in
// Person::Simulate probe that logs local-player state changes around a
// jump, split out of bzr_hooks.cpp. The shipped crouch-on-landing fix
// lives in jump_snipe_crouch.cpp.
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
    namespace Hooks
    {
        // Real GOG Person::Simulate. The old 0x004F4370 was a version/string
        // builder (advisory-PDB drift); relocated by content (SNIP sig compare
        // + anim FSM). Prologue: 55 8B EC 6A FF 68 D6 C1 84 00.
        constexpr uintptr_t kGogPersonSimulateEntryAddr = 0x0059D340;

        constexpr size_t kPersonSimulateDetourLen = 10;

        constexpr uint32_t kWeaponSigSnip = 0x534E4950u;

        // Live GOG Person offsets, re-derived from disassembly of the shipped
        // exe (the advisory beta PDB is drifted). Uniform +8 vs the PDB through
        // the vehicle fields, then +0x20 for the animation tail. See
        // reverse_engineering/jump_sniping_crouch_fix_20260713.md.
        constexpr size_t kPersonObjOffset = 0x0F0;          // PDB 0xE8 render obj

        constexpr size_t kGameObjectVelocityYOffset = 0x12C; // PDB 0x124 euler.v.y

        constexpr size_t kPersonVehiclePtrOffset = 0x230;   // PDB 0x228 vhcl (VEHICLE*)

        constexpr size_t kVehicleGroundFlagsOffset = 0x114; // VEHICLE flags word

        constexpr uint32_t kVehicleGroundedFlagBit = 0x80;  // set = grounded

        // Person on-foot animation state machine index (0..3), also the field
        // the crouch FSM switches on.
        constexpr size_t kPersonAnimStateOffset = 0x228;    // PDB 0x220 craft state

        constexpr size_t kPersonCurAnimOffset = 0x2A8;      // PDB 0x288

        constexpr size_t kPersonAnimHandleOffset = 0x2AC;   // PDB 0x28C

        constexpr size_t kCarrierWeaponsOffset = 0x18;

        constexpr size_t kCarrierSelectedOffset = 0x30;

        constexpr size_t kWeaponClassOffset = 0x08;

        constexpr size_t kWeaponClassSigOffset = 0x0C;

        constexpr size_t kWeaponClassOdfOffset = 0x20;

        constexpr float kJumpSnipeVelocityBandThreshold = 0.15f;

        enum class VerticalBand
        {
            Down,
            Flat,
            Up,
        };

        static InlineDetour32 g_PersonSimulateDetour = {};

        static bool g_JumpSnipeProbeMismatchLogged = false;

        template <typename T>
        static T ReadValueAtOffset(const void* base, size_t offset)
        {
            return *reinterpret_cast<const T*>(reinterpret_cast<const uint8_t*>(base) + offset);
        }

        static bool ShouldEnableJumpSnipingProbe()
        {
            static int s_cached = -1;
            if (s_cached < 0)
            {
                char value[8] = {};
                DWORD len = GetEnvironmentVariableA("OPENSHIM_TRACE_JUMP_SNIPING",
                                                    value,
                                                    static_cast<DWORD>(sizeof(value)));
                if (!(len > 0 && len < sizeof(value) && value[0] != '0'))
                {
                    ZeroMemory(value, sizeof(value));
                    len = GetEnvironmentVariableA("OPENSHIM_TRACE_JUMPSNIPE",
                                                  value,
                                                  static_cast<DWORD>(sizeof(value)));
                }
                s_cached = (len > 0 && len < sizeof(value) && value[0] != '0') ? 1 : 0;
            }
            return s_cached != 0;
        }


        const char* BoolText(bool value)
        {
            return value ? "true" : "false";
        }

        static VerticalBand ClassifyVerticalBand(float velY)
        {
            if (velY > kJumpSnipeVelocityBandThreshold)
                return VerticalBand::Up;
            if (velY < -kJumpSnipeVelocityBandThreshold)
                return VerticalBand::Down;
            return VerticalBand::Flat;
        }

        static const char* VerticalBandText(VerticalBand band)
        {
            switch (band)
            {
            case VerticalBand::Down:
                return "down";
            case VerticalBand::Up:
                return "up";
            default:
                return "flat";
            }
        }

        static void FormatSigString(uint32_t sig, char (&out)[5])
        {
            out[0] = static_cast<char>((sig >> 24) & 0xFFu);
            out[1] = static_cast<char>((sig >> 16) & 0xFFu);
            out[2] = static_cast<char>((sig >> 8) & 0xFFu);
            out[3] = static_cast<char>(sig & 0xFFu);
            out[4] = '\0';

            for (size_t i = 0; i < 4; ++i)
            {
                const unsigned char ch = static_cast<unsigned char>(out[i]);
                if (ch < 32 || ch > 126)
                    out[i] = '.';
            }
        }



        static bool TryCaptureLocalPlayerSnapshot(JumpSnipeProbeSnapshot& out)
        {
            out = {};

            if (!g_BzrFn_GetPlayerHandle || !g_BzrFn_GameObjectGetObjByHandle)
                return false;

            __try
            {
                const int playerHandle = g_BzrFn_GetPlayerHandle();
                if (playerHandle == 0)
                    return false;

                void* person = g_BzrFn_GameObjectGetObjByHandle(playerHandle);
                if (!person)
                    return false;

                out.valid = true;
                out.playerHandle = playerHandle;
                out.person = person;
                out.obj = ReadValueAtOffset<void*>(person, kPersonObjOffset);
                out.velY = ReadValueAtOffset<float>(person, kGameObjectVelocityYOffset);
                out.animState = ReadValueAtOffset<uint32_t>(person, kPersonAnimStateOffset);
                out.curAnim = ReadValueAtOffset<long>(person, kPersonCurAnimOffset);
                out.animHandle = ReadValueAtOffset<int>(person, kPersonAnimHandleOffset);

                void* vhcl = ReadValueAtOffset<void*>(person, kPersonVehiclePtrOffset);
                if (vhcl)
                {
                    const uint32_t flags =
                        ReadValueAtOffset<uint32_t>(vhcl, kVehicleGroundFlagsOffset);
                    out.grounded = (flags & kVehicleGroundedFlagBit) != 0;
                }

                void* carrier = ReadValueAtOffset<void*>(person, kPersonCarrierOffset);
                if (!carrier)
                    return true;

                out.selectedMask = ReadValueAtOffset<uint32_t>(carrier, kCarrierSelectedOffset);
                auto** weapons =
                    reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(carrier) + kCarrierWeaponsOffset);

                for (int slot = 0; slot < 5; ++slot)
                {
                    if ((out.selectedMask & (1u << slot)) == 0)
                        continue;

                    out.selectedSlot = slot;
                    void* weapon = weapons[slot];
                    if (!weapon)
                        break;

                    void* weaponClass = ReadValueAtOffset<void*>(weapon, kWeaponClassOffset);
                    if (!weaponClass)
                        break;

                    out.selectedSig = ReadValueAtOffset<uint32_t>(weaponClass, kWeaponClassSigOffset);
                    const char* odf = reinterpret_cast<const char*>(
                        reinterpret_cast<const uint8_t*>(weaponClass) + kWeaponClassOdfOffset);
                    strncpy_s(out.selectedOdf, odf ? odf : "", _TRUNCATE);
                    out.sniperSelected = (out.selectedSig == kWeaponSigSnip);
                    break;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                out = {};
                return false;
            }

            return out.valid;
        }

        static bool HasMeaningfulJumpSnipeChange(const JumpSnipeProbeSnapshot& lhs,
                                                 const JumpSnipeProbeSnapshot& rhs)
        {
            return lhs.person != rhs.person ||
                   lhs.obj != rhs.obj ||
                   lhs.animState != rhs.animState ||
                   lhs.grounded != rhs.grounded ||
                   lhs.curAnim != rhs.curAnim ||
                   lhs.animHandle != rhs.animHandle ||
                   lhs.selectedMask != rhs.selectedMask ||
                   lhs.selectedSlot != rhs.selectedSlot ||
                   lhs.selectedSig != rhs.selectedSig ||
                   lhs.sniperSelected != rhs.sniperSelected ||
                   strcmp(lhs.selectedOdf, rhs.selectedOdf) != 0 ||
                   ClassifyVerticalBand(lhs.velY) != ClassifyVerticalBand(rhs.velY);
        }

        static void LogJumpSnipeProbeState(const JumpSnipeProbeSnapshot& before,
                                           const JumpSnipeProbeSnapshot& after,
                                           float dt)
        {
            if (!after.valid)
                return;

            char beforeSig[5] = {};
            char afterSig[5] = {};
            FormatSigString(before.selectedSig, beforeSig);
            FormatSigString(after.selectedSig, afterSig);

            Log(L"[JUMPSNIPE] dt=%.3f handle=%d person=0x%08X obj=0x%08X fsm=%u->%u grounded=%hs->%hs anim=%ld->%ld animH=%d->%d velY=%.3f->%.3f band=%hs->%hs sel=0x%08X->0x%08X slot=%d->%d sig=%hs->%hs odf=%hs->%hs sniper=%hs->%hs\n",
                dt,
                after.playerHandle,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(after.person)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(after.obj)),
                before.animState,
                after.animState,
                BoolText(before.grounded),
                BoolText(after.grounded),
                before.curAnim,
                after.curAnim,
                before.animHandle,
                after.animHandle,
                before.velY,
                after.velY,
                VerticalBandText(ClassifyVerticalBand(before.velY)),
                VerticalBandText(ClassifyVerticalBand(after.velY)),
                before.selectedMask,
                after.selectedMask,
                before.selectedSlot,
                after.selectedSlot,
                beforeSig,
                afterSig,
                before.selectedOdf,
                after.selectedOdf,
                BoolText(before.sniperSelected),
                BoolText(after.sniperSelected));
        }

        void __fastcall PersonSimulateJumpSnipeProbeHook(void* thisPtr, void* /*edx*/, float dt)
        {
            JumpSnipeProbeSnapshot before = {};
            TryCaptureLocalPlayerSnapshot(before);

            g_BzrFn_PersonSimulate(thisPtr, dt);

            JumpSnipeProbeSnapshot after = {};
            TryCaptureLocalPlayerSnapshot(after);

            if ((!before.valid || before.person != thisPtr) &&
                (!after.valid || after.person != thisPtr))
            {
                return;
            }

            const JumpSnipeProbeSnapshot& current = after.valid ? after : before;
            if (!g_JumpSnipeProbeLogState.initialized ||
                HasMeaningfulJumpSnipeChange(g_JumpSnipeProbeLogState.last, current))
            {
                LogJumpSnipeProbeState(before, after.valid ? after : before, dt);
                g_JumpSnipeProbeLogState.initialized = true;
                g_JumpSnipeProbeLogState.last = current;
            }
        }

        void InstallJumpSnipingProbeIfRequested()
        {
            if (!ShouldEnableJumpSnipingProbe() || g_JumpSnipeProbeInstalled)
                return;

            if (g_PersonSimulateDetour.trampoline && g_BzrFn_PersonSimulate)
            {
                g_JumpSnipeProbeInstalled = true;
                return;
            }

            // push ebp; mov ebp,esp; push -1; push 0x84C1D6; (SEH frame setup).
            // 10 bytes lands on the instruction boundary after the push imm32.
            static const uint8_t kExpectedPersonSimulateBytes[kPersonSimulateDetourLen] =
            {
                0x55, 0x8B, 0xEC, 0x6A, 0xFF, 0x68, 0xD6, 0xC1, 0x84, 0x00
            };

            if (!ExpectedBytesMatchAt(kGogPersonSimulateEntryAddr,
                                      kExpectedPersonSimulateBytes,
                                      sizeof(kExpectedPersonSimulateBytes)))
            {
                // Called every sim tick until the probe installs, so say it once.
                if (!g_JumpSnipeProbeMismatchLogged)
                {
                    g_JumpSnipeProbeMismatchLogged = true;
                    Log(L"[JUMPSNIPE] Person::Simulate entry at 0x%08X does not match; probe and player-handle lookup stand down\n",
                        static_cast<uint32_t>(kGogPersonSimulateEntryAddr));
                }
                return;
            }

            // The entry bytes just checked (an SEH frame naming this build's
            // handler) are the identity proof for the GOG constants, so they
            // are published only now. They used to be written before the
            // check, so a build that then failed it still handed every later
            // consumer -- career stats, the kill trace,
            // TryGetLocalPlayerWorldPosition -- an unverified address.
            g_BzrFn_GetPlayerHandle = reinterpret_cast<FnGetPlayerHandle>(kGogGetPlayerHandleAddr);
            g_BzrFn_GameObjectGetObjByHandle =
                &GameObjectFromHandleGog; // was 0x0046B160 (wrong fn; crashed)

            if (!InstallInlineDetour32(g_PersonSimulateDetour,
                                       kGogPersonSimulateEntryAddr,
                                       reinterpret_cast<void*>(PersonSimulateJumpSnipeProbeHook),
                                       kPersonSimulateDetourLen,
                                       kExpectedPersonSimulateBytes,
                                       sizeof(kExpectedPersonSimulateBytes)))
            {
                Log(L"[JUMPSNIPE] Failed to install Person::Simulate probe at 0x%08X\n",
                    static_cast<uint32_t>(kGogPersonSimulateEntryAddr));
                return;
            }

            g_BzrFn_PersonSimulate =
                reinterpret_cast<FnPersonSimulate>(g_PersonSimulateDetour.trampoline);
            g_JumpSnipeProbeInstalled = (g_BzrFn_PersonSimulate != nullptr);
            if (g_JumpSnipeProbeInstalled)
            {
                Log(L"[JUMPSNIPE] Installed %hs player Person::Simulate probe entry=0x%08X trampoline=0x%08X env=OPENSHIM_TRACE_JUMP_SNIPING\n",
                    g_IsSteamExe ? "Steam" : "GOG",
                    static_cast<uint32_t>(kGogPersonSimulateEntryAddr),
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_PersonSimulateDetour.trampoline)));
            }
        }
    }

}
