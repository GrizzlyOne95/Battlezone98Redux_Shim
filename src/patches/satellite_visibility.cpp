// satellite_visibility.cpp
// BZR Open Shim - satellite visibility fix (enter/exit sync, mark-and-sweep,
// SEH leaves), its SATVIS diagnostic capture and validation sampler, and
// the hop-out stale attack-alert suppression that shares the satellite
// view predicate, split out of bzr_hooks.cpp.
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
        static constexpr size_t kGameObjectEnemyShotOffset = 0x1E8;

        // CockpitRadar::Render's "a friendly is under attack" cooldown, the
        // float the growl alert compares enemyShot against
        // (comiss xmm0, [0x009173D0] at 0x00494D35).
        static constexpr uintptr_t kRadarAttackAlertNextBeepRva = 0x005173D0;

        static bool g_HopOutAttackAlertFixEnabled = kHopOutAttackAlertFixEnabledDefault;

        static void* g_HopOutAlertLastUserObject = nullptr;

        static bool g_HopOutAlertPrimed = false;

        static constexpr size_t kPresetViewCurrentViewOffset = 0x8;

        // GameObject visibility fields, complete-object relative. Derived from
        // the shipped GOG image, not the advisory PDB: GameObject::Save passes
        // each field name as a string literal to
        // ::out(file, &this->field, size, "name"), and every one of those
        // literals has exactly one .text cross-reference, immediately preceded
        // by the `add reg, <offset>` that forms &this->field.
        //
        //   "illumination"  .rdata 0x00879D3C  xref 0x004DE199  add ecx, 0x0E8
        //   "seqNo"         .rdata 0x0087405C  xref 0x004DE211  add ecx, 0x15C
        //   "isObjective"   .rdata 0x00879D14  xref 0x004DE28B  add eax, 0x189
        //   "isSelected"    .rdata 0x00879D08  xref 0x004DE2AE  add eax, 0x18A
        //   "isVisible"     .rdata 0x00879CFC  xref 0x004DE2D1  add eax, 0x18C
        //   "seen"          .rdata 0x00879CF4  xref 0x004DE2F4  add eax, 0x190
        //   "perceivedTeam" .rdata 0x00879E2C  xref 0x004DE7E0  add ecx, 0x180
        //
        // The walker offsets ARE complete-object relative -- see the note on
        // kGameObjectActualTeamOffset above. The former "-0xC" rule was wrong
        // and shifted every field here onto its neighbour, which is why
        // illumination read as tiny denormals (0x00000005, 0x001AFC44): +0xDC
        // is not illumination at all. Sanity check for any future revision:
        // Redux is the BZ 1.5 layout shifted by +0xC, and 1.5 has illumination
        // at 0xDC, so 0xDC here was the *1.5* offset, not the Redux one.
        // Verified against ExtraUtilities' GetOgreEntity chain.
        static constexpr size_t kGameObjectRenderOwnerOffset = 0xF0;

        static constexpr size_t kRenderOwnerOgreEntityOffset = 0x94;

        static constexpr size_t kGameObjectIsSelectedOffset = 0x18A;

        // LooksLikeOgreObject without the VirtualQuery, for per-tick sweeps
        // over many objects. The guarded read already turns an unmapped page
        // into "no"; the query only added a syscall per object. The identity
        // test is the same: a vtable inside OgreMain.dll.
        static bool LooksLikeOgreObjectInPlace(const void* candidate)
        {
            const uintptr_t address = reinterpret_cast<uintptr_t>(candidate);
            if (address < 0x00010000 || (address % sizeof(void*)) != 0)
                return false;

            uintptr_t ogreBase = 0;
            uintptr_t ogreEnd = 0;
            if (!TryGetOgreModuleRange(ogreBase, ogreEnd))
                return false;

            uintptr_t vtable = 0;
            __try
            {
                vtable = *reinterpret_cast<const uintptr_t*>(candidate);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }

            return vtable >= ogreBase && vtable < ogreEnd;
        }

        template<typename T>
        static T* ResolveMainModulePtr(uintptr_t rva)
        {
            const uintptr_t base = GetMainModuleBase();
            if (base == 0)
                return nullptr;
            return reinterpret_cast<T*>(base + rva);
        }

        // Main image extent from its PE headers, read once.
        static bool TryGetMainImageRange(uintptr_t& outBase, uintptr_t& outEnd)
        {
            static uintptr_t s_base = 0;
            static uintptr_t s_end = 0;
            if (s_end == 0)
            {
                const uintptr_t base = GetMainModuleBase();
                if (base == 0)
                    return false;
                __try
                {
                    const auto* dosHeader = reinterpret_cast<const IMAGE_DOS_HEADER*>(base);
                    const auto* ntHeaders =
                        reinterpret_cast<const IMAGE_NT_HEADERS*>(base + dosHeader->e_lfanew);
                    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE ||
                        ntHeaders->Signature != IMAGE_NT_SIGNATURE ||
                        ntHeaders->OptionalHeader.SizeOfImage == 0)
                        return false;
                    s_base = base;
                    s_end = base + ntHeaders->OptionalHeader.SizeOfImage;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }
            outBase = s_base;
            outEnd = s_end;
            return true;
        }

        // TryGetGameObjectFieldBase for arena slots, without its two
        // VirtualQuery calls. The arena lives in the exe's own .data, so the
        // slot is always mapped, and a vtable that lies inside the main image
        // is always readable; anything else is rejected before it is touched.
        // The identity proof is unchanged: slot 1 must be GameObject::GetTeam.
        // SyncSatelliteVisibility runs this for every live object every tick.
        static bool TryGetArenaGameObjectFieldBase(void* objectPtr, uint8_t*& outBase)
        {
            outBase = nullptr;
            const auto address = reinterpret_cast<uintptr_t>(objectPtr);
            if (address < 0x00010000 || (address % sizeof(void*)) != 0)
                return false;

            uintptr_t imageBase = 0;
            uintptr_t imageEnd = 0;
            if (!TryGetMainImageRange(imageBase, imageEnd))
                return false;

            __try
            {
                auto* bytes = reinterpret_cast<uint8_t*>(objectPtr);
                auto** vtable = *reinterpret_cast<void***>(bytes + kGameObjectInterfaceOffset);
                const auto vtableAddress = reinterpret_cast<uintptr_t>(vtable);
                constexpr size_t kGetTeamSlot = kGameObjectGetTeamVtableOffset / sizeof(void*);
                if (vtableAddress < imageBase ||
                    vtableAddress + (kGetTeamSlot + 1) * sizeof(void*) > imageEnd)
                    return false;

                const uintptr_t expected =
                    imageBase + (kGogGameObjectGetTeamAddr - kGogPreferredImageBase);
                if (reinterpret_cast<uintptr_t>(vtable[kGetTeamSlot]) != expected)
                    return false;

                outBase = bytes;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        struct SatelliteVisibilityLogEntry
        {
            void* objectPtr = nullptr;
            int team = INT_MIN;
            int perceivedTeam = INT_MIN;
            // Logged three ways at once so the field's type is decided from a
            // capture instead of assumed. BZ 1.5 treats illumination as float
            // (CockpitRadar::Render computes `illumination * 15.0` and uses the
            // result as a colour-ramp index), so a correctly located Redux
            // field should read as a small non-denormal float and as a garbage
            // int -- not the other way round.
            uint32_t illuminationRaw = 0;
            float illumination = 0.0f;
            // Ogre handle discovery. The GameObject -> Ogre entity offset has
            // never been derived, so rather than assume one, record which
            // fields of the object hold a pointer whose vtable lives inside
            // OgreMain. A capture turns that into a known offset.
            void* renderOwner = nullptr;
            void* ogreHandle = nullptr;
            int ogreVisible = -1;          // -1 = unknown, 0/1 = Ogre getVisible()
            char ogreClassName[64] = {};
            uint32_t isVisible = 0;
            uint32_t seen = 0;
            int targetHandle = 0;
            int classType = -1;
            bool isObjective = false;
            bool isSelected = false;
            // Derived, so a capture can be scored straight against the BZ 1.5
            // behaviour table without post-processing.
            bool detectedByUserTeam = false;   // (isVisible  >> userTeam) & 1
            bool discoveredByUserTeam = false; // (seen       >> userTeam) & 1
            bool legacyVisible = false;        // illumination > 0  -- the 1.5 gate
        };

        static bool TryReadCurrentViewId(long& outView)
        {
            outView = -1;
            auto* viewRecord = ResolveMainModulePtr<uint8_t>(kViewRecordRva);
            if (!viewRecord)
                return false;

            __try
            {
                outView =
                    *reinterpret_cast<const long*>(viewRecord + kPresetViewCurrentViewOffset);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool IsSatelliteOverviewActive()
        {
            long currentView = -1;
            return TryReadCurrentViewId(currentView) &&
                   currentView == kCameraTypeOverView;
        }

        // Satellite visibility fix. Redux left every Ogre entity permanently
        // visible; satellite view (view 3) never applies the BZ 1.5
        // illumination > 0 gate. This struct tracks each entity's pre-satellite
        // visibility so the gate can be applied during satellite and reversed on
        // exit. Keyed by GameObject pointer so lifecycle validation is possible.
        struct SatelliteEntityVisibility
        {
            void* gameObject = nullptr;
            void* entity = nullptr;
            bool originalVisible = true;
            bool appliedVisible = true;
            // Mark-and-sweep stamp. The arena has 4096 slots, so pruning by
            // rescanning it once per map entry is quadratic on a busy map;
            // stamping each entry as it is visited makes the sweep linear.
            uint32_t lastSeenTick = 0;
        };

        static bool g_SatelliteVisibilityFixEnabled = true;
        // Configured value AND'd with the single-player gate. This one is
        // client-side only -- it cannot desync anything -- but it is a
        // competitive asymmetry in the shim user's DISfavour: it hides enemies
        // the team has never illuminated, so a shim player would see less on
        // the satellite than a stock peer in the same match. Standing it down
        // in a network game restores parity with stock Redux.
        static bool g_SatelliteVisibilityFixActive = false;

        // Re-readable config for the two engine toggles the settings page can
        // change without a restart. Both are plain flag reads -- no patch site,
        // no hook install -- so re-running them mid-session is safe, and both
        // are called once from ResolveBzrHooks and again from
        // ApplyShimSettingLive's LiveEngineToggle group.
        void InitializeHopOutAttackAlertConfig()
        {
            bool hopOutAlertConfig = false;
            // [General], not [SinglePlayer]: this is audio-only and has no
            // simulation effect, so it does not need that section's
            // hard-disable-in-network-games contract.
            if (TryGetUserConfigBool("General", "SuppressHopOutAttackAlert",
                                     hopOutAlertConfig))
            {
                g_HopOutAttackAlertFixEnabled = hopOutAlertConfig;
            }
            else if (EnvFlagEnabled("OPENSHIM_DISABLE_HOP_OUT_ATTACK_ALERT_FIX") ||
                     EnvFlagEnabled("BZR_DISABLE_HOP_OUT_ATTACK_ALERT_FIX"))
            {
                g_HopOutAttackAlertFixEnabled = false;
            }
            else
            {
                g_HopOutAttackAlertFixEnabled = kHopOutAttackAlertFixEnabledDefault;
            }
            g_HopOutAlertLastUserObject = nullptr;
            g_HopOutAlertPrimed = false;
        }

        void RefreshSatelliteVisibilityFixState()
        {
            g_SatelliteVisibilityFixActive =
                g_SatelliteVisibilityFixEnabled && IsSinglePlayerSession();
        }

        static bool g_SatVisWasActive = false;
        static uint32_t g_SatVisSweepTick = 0;
        static std::unordered_map<void*, SatelliteEntityVisibility> g_SatelliteVisibilityState;

        // Satellite visibility fix. Gates Ogre entity visibility through
        // illumination > 0 when satellite overview (view 3) is active, matching
        // BZ 1.5's Submit_Overview_Entities gate that Redux removed.
        // resetTracking clears what the fix believes it has hidden. That is
        // right at startup and wrong on a live re-read: SyncSatelliteVisibility
        // deliberately keeps running for an inactive feature so that the exit
        // transition puts every entity it hid back, and it recognises that work
        // by the tracking map and the wasActive flag. Dropping them mid-session
        // would strand any entity that is hidden right now.
        void InitializeSatelliteVisibilityFixConfig(bool resetTracking)
        {
            bool satVisFixConfig = false;
            if (TryGetUserConfigBool("SinglePlayer", "SatelliteVisibilityFix",
                                     satVisFixConfig))
            {
                g_SatelliteVisibilityFixEnabled = satVisFixConfig;
            }
            else if (EnvFlagEnabled("OPENSHIM_DISABLE_SATELLITE_VISIBILITY_FIX") ||
                     EnvFlagEnabled("BZR_DISABLE_SATELLITE_VISIBILITY_FIX"))
            {
                g_SatelliteVisibilityFixEnabled = false;
            }
            else
            {
                g_SatelliteVisibilityFixEnabled = true;
            }
            RefreshSatelliteVisibilityFixState();
            if (resetTracking)
            {
                g_SatVisWasActive = false;
                g_SatVisSweepTick = 0;
                g_SatelliteVisibilityState.clear();
            }
        }

        // Validation-only pre-hide hook. Battlezone Lua cannot reach Ogre, so
        // lcbench has no way to construct the "entity was already hidden
        // before satellite was entered" case on its own. When this names a
        // team, every live GameObject on that team has its Ogre entity hidden
        // exactly once, outside satellite, and is then never touched again --
        // which is precisely a pre-hidden entity. Environment-only on purpose:
        // it is a test fixture, not a user-facing option, and it is inert
        // unless OPENSHIM_SATVIS_TEST_PREHIDE_TEAM is set.
        bool g_SatVisTestPreHideEnabled = false;
        int g_SatVisTestPreHideTeam = 0;
        std::unordered_set<void*> g_SatVisTestPreHidden;

        // Bounded validation capture. The general [SATVIS] sampler prints three
        // hidden and three visible objects per sample, which is the right shape
        // for characterising a defect but cannot score a fixture that separates
        // its cases by team. This aggregates the whole arena into one row per
        // team -- population, legacy gate, resulting Ogre visibility, and what
        // the fix believes it did -- so a single line per team per second is
        // enough to score every case. Environment-only, rate-limited, and hard
        // budget capped.
        bool g_SatVisValidateEnabled = false;
        volatile long g_SatVisValidateBudget = 0;
        DWORD g_SatVisValidateLastTick = 0;
        static constexpr int kSatVisValidateTeamCount = 16;

        // Ogre::MovableObject::getVisible, resolved by module offset exactly as
        // ExtraUtilities does. Read-only. Isolated here because the cached
        // static cannot share a frame with __try.
        static FnOgreEntityBoolQuery GetOgreVisibleProc()
        {
            static FnOgreEntityBoolQuery fn =
                ResolveOgreProcByOffset<FnOgreEntityBoolQuery>(0x00005E70);
            return fn;
        }

        static int TryReadOgreVisible(FnOgreEntityBoolQuery getVisible, void* entity)
        {
            __try
            {
                return getVisible(entity) ? 1 : 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return -1;
            }
        }

        // GameObject -> [+0xF0] -> [+0x94] = Ogre entity. Taken from
        // ExtraUtilities (BZR::GameObject::GetOgreEntity, src/bzr.h), which
        // drives its distance culling through exactly this chain. EXU's
        // GameObject base is the same complete object this probe walks: its
        // struct puts carrier at +0x1A0, and Redux's Craft::AbandonPilot reads
        // the carrier at complete+0x1A0.
        //
        // A blind one-level scan could never have found this: the entity is two
        // hops out, and the intermediate at +0xF0 is not itself an Ogre object.
        //
        // Kept in its own function because the Ogre proc is resolved into a
        // function-local static, which cannot live inside a __try frame.
        static void ResolveGameObjectOgreState(const uint8_t* bytes,
                                               void*& outRenderOwner,
                                               void*& outEntity,
                                               int& outVisible,
                                               char* outClassName,
                                               size_t classNameSize)
        {
            outRenderOwner = nullptr;
            outEntity = nullptr;
            outVisible = -1;
            if (!bytes)
                return;

            void* renderOwner = nullptr;
            void* entity = nullptr;
            __try
            {
                renderOwner = *reinterpret_cast<void* const*>(bytes + kGameObjectRenderOwnerOffset);
                if (renderOwner)
                    entity = *reinterpret_cast<void* const*>(
                        reinterpret_cast<const uint8_t*>(renderOwner) + kRenderOwnerOgreEntityOffset);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return;
            }

            outRenderOwner = renderOwner;
            if (!LooksLikeOgreObject(entity))
                return;

            outEntity = entity;
            TryGetRttiClassName(entity, outClassName, classNameSize);

            FnOgreEntityBoolQuery getVisible = GetOgreVisibleProc();
            if (!getVisible)
                return;
            outVisible = TryReadOgreVisible(getVisible, entity);
        }

        static bool CaptureSatelliteVisibilityEntry(void* objectPtr,
                                                    long userTeam,
                                                    SatelliteVisibilityLogEntry& outEntry)
        {
            // Reject anything that is not positively a GameObject before
            // touching a single field. The arena also holds entries whose
            // vtable is an abstract base table, and those are unrecoverable if
            // dispatched through -- see TryGetGameObjectFieldBase.
            uint8_t* bytes = nullptr;
            if (!TryGetGameObjectFieldBase(objectPtr, bytes))
                return false;

            __try
            {
                outEntry.objectPtr = objectPtr;
                outEntry.team =
                    *reinterpret_cast<const int*>(bytes + kGameObjectActualTeamOffset);
                outEntry.perceivedTeam =
                    *reinterpret_cast<const int*>(bytes + kGameObjectPerceivedTeamOffset);
                outEntry.illuminationRaw =
                    *reinterpret_cast<const uint32_t*>(bytes + kGameObjectIlluminationOffset);
                std::memcpy(&outEntry.illumination, &outEntry.illuminationRaw,
                            sizeof(outEntry.illumination));
                outEntry.isVisible =
                    *reinterpret_cast<const uint32_t*>(bytes + kGameObjectIsVisibleOffset);
                outEntry.seen =
                    *reinterpret_cast<const uint32_t*>(bytes + kGameObjectSeenOffset);
                outEntry.targetHandle =
                    *reinterpret_cast<const int*>(bytes + kGameObjectTargetHandleOffset);
                ResolveGameObjectOgreState(bytes, outEntry.renderOwner, outEntry.ogreHandle,
                                           outEntry.ogreVisible, outEntry.ogreClassName,
                                           sizeof(outEntry.ogreClassName));

                outEntry.isObjective =
                    *reinterpret_cast<const uint8_t*>(bytes + kGameObjectIsObjectiveOffset) != 0;
                outEntry.isSelected =
                    *reinterpret_cast<const uint8_t*>(bytes + kGameObjectIsSelectedOffset) != 0;

                // Class type drives the BZ 1.5 special cases: category 2
                // (building) is skipped by Scanner::BasicVisibility's per-frame
                // reset, which is what makes discovered buildings stay visible,
                // and category 4 (person) is skipped by SweepVisibility so
                // pilots never appear. The Redux enum's mapping onto those
                // legacy values is NOT yet confirmed -- log the raw value and
                // read the mapping off a capture containing a known building
                // and a known pilot.
                outEntry.classType = -1;
                if (const auto* objectClass = *reinterpret_cast<uint8_t* const*>(
                        bytes + kGameObjectClassOffset))
                {
                    outEntry.classType =
                        *reinterpret_cast<const int*>(objectClass + kObjectClassTypeOffset);
                }

                if (userTeam >= kGameTeamMin && userTeam <= kGameTeamMax)
                {
                    const uint32_t mask = 1u << static_cast<uint32_t>(userTeam);
                    outEntry.detectedByUserTeam = (outEntry.isVisible & mask) != 0;
                    outEntry.discoveredByUserTeam = (outEntry.seen & mask) != 0;
                }
                outEntry.legacyVisible = outEntry.illumination > 0.0f;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static void LogSatelliteVisibilityEntry(const wchar_t* tag, const SatelliteVisibilityLogEntry& entry)
        {
            if (!tag)
                return;

            // Field order mirrors the BZ 1.5 decision chain: what the object
            // is, then what the scanner pass decided, then what the legacy
            // overview gate would have concluded.
            Log(L"[SATVIS]   %ls obj=0x%08X team=%d perceivedTeam=%d class=%d objective=%d selected=%d "
                L"illumRaw=0x%08X illumInt=%d illumFlt=%.6g "
                L"isVisible=0x%08X seen=0x%08X detected=%d discovered=%d legacyVisible=%d target=0x%08X\n",
                tag,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(entry.objectPtr)),
                entry.team,
                entry.perceivedTeam,
                entry.classType,
                entry.isObjective ? 1 : 0,
                entry.isSelected ? 1 : 0,
                entry.illuminationRaw,
                static_cast<int>(entry.illuminationRaw),
                static_cast<double>(entry.illumination),
                entry.isVisible,
                entry.seen,
                entry.detectedByUserTeam ? 1 : 0,
                entry.discoveredByUserTeam ? 1 : 0,
                entry.legacyVisible ? 1 : 0,
                static_cast<uint32_t>(entry.targetHandle));

            // Second line only when an Ogre handle was actually found, so the
            // absence of one is itself visible in the capture.
            // Always emitted, so a missing Ogre entity is as visible in the
            // capture as a present one. The pairing that matters is
            // legacyVisible=0 with ogreVis=1: an object BZ 1.5 would have
            // withheld from the overview that Redux is still drawing.
            Log(L"[SATVIS]     %ls owner=0x%08X ogre=0x%08X (%hs) ogreVis=%d legacyVisible=%d%hs\n",
                tag,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(entry.renderOwner)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(entry.ogreHandle)),
                entry.ogreClassName[0] ? entry.ogreClassName : "?",
                entry.ogreVisible,
                entry.legacyVisible ? 1 : 0,
                (!entry.legacyVisible && entry.ogreVisible == 1) ? "  <== LEAK" : "");
        }

        // Stop the stale under-attack growl that fires the instant you hop out.
        //
        // CockpitRadar::Render alerts for any friendly whose enemyShot
        // timestamp is newer than the global cooldown, and it excludes exactly
        // one object: the one the player currently is.
        //
        //   0x00494D11  movzx ecx, [ebp-0x131]      ; is this object friendly
        //   0x00494D1A  je   skip
        //   0x00494D28  cmp  eax, [edx+0xc]         ; obj == userObj
        //   0x00494D2B  je   skip                   ; <- the only mask
        //   0x00494D35  comiss xmm0, [0x009173D0]   ; enemyShot > nextBeep
        //   0x00494D3C  jbe  skip
        //                                           ; -> push "cgrowl.wav"
        //
        // Hopping out moves userObj to the pilot, so the craft you just left
        // stops being masked. If an enemy shot it at any point since the last
        // alert, its enemyShot is still sitting there and the very next radar
        // frame replays that old event as a fresh warning -- once, because the
        // alert then sets nextBeep = enemyShot + 1.
        //
        // This is stock behaviour: BZ 1.5's CockpitRadar::Render has the same
        // three conditions, so this is a deliberate quality-of-life deviation
        // rather than a compatibility fix.
        //
        // The fix is deliberately the narrowest thing that works: on the frame
        // the player object changes, raise nextBeep to exactly the previous
        // object's enemyShot. That one stale value stops satisfying the strict
        // `>` comparison, and nothing else changes -- any genuinely newer hit
        // still carries a later timestamp and still beeps, including further
        // fire on the craft you just abandoned. nextBeep is only ever raised,
        // never lowered, so the worst case for a misread is one missing audio
        // cue rather than a suppressed warning stream.

        void MaybeSuppressStaleHopOutAttackAlert()
        {
            if (!g_HopOutAttackAlertFixEnabled)
                return;

            void* const userObject = TryGetHeadlightPlayerObject();
            if (!userObject)
                return;

            void* const previousObject = g_HopOutAlertLastUserObject;
            g_HopOutAlertLastUserObject = userObject;

            // Never treat the first observation of a session as a transition.
            if (!g_HopOutAlertPrimed)
            {
                g_HopOutAlertPrimed = true;
                return;
            }
            if (!previousObject || previousObject == userObject)
                return;

            // Validates the pointer and confirms the GameObject vtable tag, so
            // a stale pointer left by a mission change is rejected rather than
            // dereferenced.
            uint8_t* previousBase = nullptr;
            if (!TryGetGameObjectFieldBase(previousObject, previousBase))
                return;

            auto* nextBeep = ResolveMainModulePtr<float>(kRadarAttackAlertNextBeepRva);
            if (!nextBeep)
                return;

            __try
            {
                const float staleEnemyShot =
                    *reinterpret_cast<const float*>(previousBase + kGameObjectEnemyShotOffset);

                // Objects start at -1e30 and only ever receive a real game
                // timestamp from SetDamageFlags' EnemyP branch, so anything
                // non-positive means this object was never shot by an enemy and
                // there is nothing stale to suppress.
                if (!(staleEnemyShot > 0.0f) || !std::isfinite(staleEnemyShot))
                    return;

                const float currentNextBeep = *nextBeep;
                if (std::isfinite(currentNextBeep) && currentNextBeep >= staleEnemyShot)
                    return;

                *nextBeep = staleEnemyShot;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        void MaybeLogSatelliteVisibilitySample()
        {
            if (!g_TraceSatelliteVisibility)
                return;
            // Deliberately NOT gated on the overview any more. The question is
            // whether an object's effective Ogre visibility changes as the
            // player enters and leaves view 3, so the sampler has to run on
            // both sides of the transition. Every line carries the view id, and
            // the same one-per-second rate limit and sample budget still apply.

            const DWORD now = GetTickCount();
            if (g_SatelliteVisibilityLastTick != 0 &&
                (now - g_SatelliteVisibilityLastTick) < g_SatelliteVisibilityLogIntervalMs)
            {
                return;
            }

            if (InterlockedDecrement(&g_SatelliteVisibilityLogBudget) < 0)
                return;

            g_SatelliteVisibilityLastTick = now;

            auto* viewRecord = ResolveMainModulePtr<uint8_t>(kViewRecordRva);
            if (!viewRecord)
            {
                Log(L"[SATVIS] missing view record pointer 0x%08X\n",
                    static_cast<uint32_t>(GetMainModuleBase() + kViewRecordRva));
                return;
            }

            __try
            {
                const long currentView =
                    *reinterpret_cast<const long*>(viewRecord + kPresetViewCurrentViewOffset);
                void* const userObject = TryGetHeadlightPlayerObject();
                const long userTeam = static_cast<long>(GetGameObjectActualTeam(userObject));

                static void* s_satvisObjects[kGameObjectArenaSlotCapacity];
                const size_t totalObjects =
                    CollectLiveGameObjectsFromArena(s_satvisObjects, kGameObjectArenaSlotCapacity);
                const size_t maxSampleObjects = static_cast<size_t>(g_SatelliteVisibilityObjectLimit);
                const size_t sampleObjects =
                    (totalObjects < maxSampleObjects) ? totalObjects : maxSampleObjects;

                SatelliteVisibilityLogEntry userEntry = {};
                const bool haveUserEntry =
                    CaptureSatelliteVisibilityEntry(userObject, userTeam, userEntry);

                uint32_t rejectedCount = 0;
                uint32_t illuminatedCount = 0;
                uint32_t visibleCount = 0;
                uint32_t seenCount = 0;
                uint32_t detectedCount = 0;
                uint32_t discoveredCount = 0;
                std::array<SatelliteVisibilityLogEntry, 3> hiddenEntries = {};
                std::array<SatelliteVisibilityLogEntry, 3> visibleEntries = {};
                size_t hiddenLogged = 0;
                size_t visibleLogged = 0;

                for (size_t index = 0; index < sampleObjects; ++index)
                {
                    SatelliteVisibilityLogEntry entry = {};
                    if (!CaptureSatelliteVisibilityEntry(s_satvisObjects[index], userTeam, entry))
                    {
                        // Arena entries that are not GameObjects, including the
                        // abstract-vtable ones that used to be fatal.
                        ++rejectedCount;
                        continue;
                    }

                    if (entry.illumination > 0.0f)
                        ++illuminatedCount;
                    if (entry.isVisible != 0)
                        ++visibleCount;
                    if (entry.seen != 0)
                        ++seenCount;
                    if (entry.detectedByUserTeam)
                        ++detectedCount;
                    if (entry.discoveredByUserTeam)
                        ++discoveredCount;

                    // Split on the legacy gate itself (illumination > 0), not
                    // on the raw bitmask, so the two buckets mean exactly what
                    // BZ 1.5's Submit_Overview_Entities would have decided.
                    if (!entry.legacyVisible)
                    {
                        if (hiddenLogged < hiddenEntries.size())
                            hiddenEntries[hiddenLogged++] = entry;
                    }
                    else if (visibleLogged < visibleEntries.size())
                    {
                        visibleEntries[visibleLogged++] = entry;
                    }
                }

                Log(L"[SATVIS] view=%ld userTeam=%ld userObj=0x%08X total=%u sampled=%u rejected=%u illum=%u visible=%u seen=%u "
                    L"detected=%u discovered=%u interval=%lums remaining=%ld\n",
                    currentView,
                    userTeam,
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(userObject)),
                    static_cast<unsigned>(totalObjects),
                    static_cast<unsigned>(sampleObjects),
                    rejectedCount,
                    illuminatedCount,
                    visibleCount,
                    seenCount,
                    detectedCount,
                    discoveredCount,
                    static_cast<unsigned long>(g_SatelliteVisibilityLogIntervalMs),
                    g_SatelliteVisibilityLogBudget);

                if (haveUserEntry)
                    LogSatelliteVisibilityEntry(L"user", userEntry);

                for (size_t index = 0; index < hiddenLogged; ++index)
                    LogSatelliteVisibilityEntry(L"hidden", hiddenEntries[index]);
                for (size_t index = 0; index < visibleLogged; ++index)
                    LogSatelliteVisibilityEntry(L"visible", visibleEntries[index]);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[SATVIS] sample fault code=0x%08X\n", static_cast<uint32_t>(GetExceptionCode()));
            }
        }

        // Satellite visibility fix: gate Ogre entity visibility through
        // illumination > 0 when the satellite overview (view 3) is active.
        // BZ 1.5 applied this gate in Submit_Overview_Entities; Redux removed
        // that path and left every Ogre entity permanently visible. This
        // function restores the gate by toggling MovableObject::setVisible on
        // each GameObject-backed entity during satellite, and restores the
        // pre-satellite visibility on exit.
        //
        // Called from ChunkEffectSimulateHook every sim tick. The call is
        // placed before MaybeLogSatelliteVisibilitySample so the diagnostic
        // sampler observes the post-fix Ogre state.

        // SEH-guarded helpers. Each lives in its own function because MSVC
        // prohibits __try in any function that requires C++ object unwinding,
        // and the main sync function uses std::unordered_map.
        // Both readers below take arena slots (CollectLiveGameObjectsFromArena).
        static bool TryReadObjectIlluminationAndEntity(void* objectPtr,
                                                       float& outIllumination,
                                                       void*& outEntity)
        {
            outIllumination = 0.0f;
            outEntity = nullptr;
            uint8_t* bytes = nullptr;
            if (!TryGetArenaGameObjectFieldBase(objectPtr, bytes))
                return false;
            __try
            {
                outIllumination = *reinterpret_cast<const float*>(
                    bytes + kGameObjectIlluminationOffset);
                void* renderOwner = *reinterpret_cast<void* const*>(
                    bytes + kGameObjectRenderOwnerOffset);
                if (renderOwner)
                    outEntity = *reinterpret_cast<void* const*>(
                        reinterpret_cast<const uint8_t*>(renderOwner) +
                        kRenderOwnerOgreEntityOffset);
                return outEntity != nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool TryResolveEntityFromGameObject(void* objectPtr, void*& outEntity)
        {
            outEntity = nullptr;
            uint8_t* bytes = nullptr;
            if (!TryGetArenaGameObjectFieldBase(objectPtr, bytes))
                return false;
            __try
            {
                void* renderOwner = *reinterpret_cast<void* const*>(
                    bytes + kGameObjectRenderOwnerOffset);
                if (renderOwner)
                    outEntity = *reinterpret_cast<void* const*>(
                        reinterpret_cast<const uint8_t*>(renderOwner) +
                        kRenderOwnerOgreEntityOffset);
                return outEntity != nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool TryCallEntitySetVisible(FnOgreSetVisible setVisible,
                                            void* entity, bool visible)
        {
            __try
            {
                setVisible(entity, visible);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool TryCallEntityGetVisible(FnOgreEntityBoolQuery getVisible,
                                            void* entity, bool& outVisible)
        {
            __try
            {
                outVisible = getVisible(entity);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // A mission change destroys every GameObject without any teardown
        // callback, and the arena is a fixed-address slot table, so the next
        // mission allocates objects at exactly the addresses the previous one
        // used. A state map carried across that boundary can therefore match a
        // brand-new object by address. Rather than try to reconcile it, detect
        // that the world is gone and drop the map -- no pointer in it is worth
        // anything at that point, and the entities it named are already
        // destroyed, so there is nothing to restore.
        bool SatelliteWorldIsLive()
        {
            void* player = TryGetHeadlightPlayerObject();
            return player != nullptr && IsLiveHeadlightObjectSlot(player);
        }

        // Validation fixture; see g_SatVisTestPreHideEnabled. Runs only outside
        // satellite and only touches an entity once, so the satellite path sees
        // a genuinely pre-hidden entity rather than one this hook keeps forcing.
        static void ApplySatelliteVisibilityTestPreHide(FnOgreSetVisible setVisible)
        {
            if (!g_SatVisTestPreHideEnabled || !setVisible)
                return;

            static void* s_preHideObjects[kGameObjectArenaSlotCapacity];
            const size_t totalObjects =
                CollectLiveGameObjectsFromArena(s_preHideObjects, kGameObjectArenaSlotCapacity);

            for (size_t i = 0; i < totalObjects; ++i)
            {
                void* obj = s_preHideObjects[i];
                if (GetGameObjectActualTeam(obj) != g_SatVisTestPreHideTeam)
                    continue;

                void* entity = nullptr;
                if (!TryResolveEntityFromGameObject(obj, entity))
                    continue;
                if (!LooksLikeOgreObjectInPlace(entity))
                    continue;
                if (g_SatVisTestPreHidden.count(entity) != 0)
                    continue;

                if (TryCallEntitySetVisible(setVisible, entity, false))
                {
                    g_SatVisTestPreHidden.insert(entity);
                    if (EnvFlagEnabled("OPENSHIM_TRACE_SATELLITE_VISIBILITY_FIX"))
                    {
                        Log(L"[SATVISFIX] test pre-hide obj=0x%08X ogre=0x%08X team=%d\n",
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(obj)),
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(entity)),
                            g_SatVisTestPreHideTeam);
                    }
                }
            }
        }

        void SyncSatelliteVisibility()
        {
            // Deliberately not an early-out on "inactive". Going inactive while
            // the satellite view is open -- the feature switched off, or a
            // network game starting -- must still reach the exit transition
            // below so every entity this pass hid gets its visibility put back.
            // Only skip when there is genuinely nothing to do or undo.
            if (!g_SatelliteVisibilityFixActive &&
                !g_SatVisWasActive &&
                g_SatelliteVisibilityState.empty())
            {
                return;
            }

            static FnOgreSetVisible setVisible =
                ResolveOgreProc<FnOgreSetVisible>("?setVisible@MovableObject@Ogre@@UAEX_N@Z");
            FnOgreEntityBoolQuery getVisible = GetOgreVisibleProc();

            if (!setVisible || !getVisible)
                return;

            // Mission teardown: forget everything without dereferencing any of
            // it. Must be checked before the exit transition, otherwise the
            // restore pass would walk a fresh mission's arena holding the
            // previous mission's expectations.
            if (!SatelliteWorldIsLive())
            {
                if (!g_SatelliteVisibilityState.empty() || g_SatVisWasActive)
                {
                    if (EnvFlagEnabled("OPENSHIM_TRACE_SATELLITE_VISIBILITY_FIX"))
                    {
                        Log(L"[SATVISFIX] world torn down — dropped %zu tracked objects\n",
                            g_SatelliteVisibilityState.size());
                    }
                    g_SatelliteVisibilityState.clear();
                    g_SatVisWasActive = false;
                }
                g_SatVisTestPreHidden.clear();
                return;
            }

            // An inactive feature reads as "not in satellite view", which is
            // what drives the restore transition below.
            const bool currentSatellite =
                g_SatelliteVisibilityFixActive && IsSatelliteOverviewActive();

            // --- Transition: leaving satellite ---
            // Restore original visibility for every tracked entity that is
            // still live, still owns the same Ogre entity, and still carries
            // the visibility this pass last wrote to it.
            if (!currentSatellite && g_SatVisWasActive)
            {
                size_t restored = 0;
                size_t deferred = 0;
                static void* s_exitObjects[kGameObjectArenaSlotCapacity];
                const size_t totalObjects =
                    CollectLiveGameObjectsFromArena(s_exitObjects, kGameObjectArenaSlotCapacity);

                for (size_t i = 0; i < totalObjects; ++i)
                {
                    auto it = g_SatelliteVisibilityState.find(s_exitObjects[i]);
                    if (it == g_SatelliteVisibilityState.end())
                        continue;

                    SatelliteEntityVisibility& saved = it->second;

                    void* currentEntity = nullptr;
                    if (!TryResolveEntityFromGameObject(saved.gameObject, currentEntity))
                        continue;

                    // The slot was reused, or the GameObject swapped entities
                    // after the last sync tick. Either way this entity was
                    // never written by us, so there is nothing to undo.
                    if (currentEntity != saved.entity)
                        continue;

                    // Re-vet before dispatching a virtual: an entity freed and
                    // its allocation reused would otherwise be called through.
                    if (!LooksLikeOgreObjectInPlace(currentEntity))
                        continue;

                    bool now = false;
                    if (!TryCallEntityGetVisible(getVisible, currentEntity, now))
                        continue;

                    // Somebody else -- chunk fragmentation hiding a source
                    // mesh, for instance -- took ownership of this entity while
                    // satellite was open. Restoring the pre-satellite value
                    // here would clobber their decision, so leave it alone.
                    if (now != saved.appliedVisible)
                    {
                        ++deferred;
                        continue;
                    }

                    if (now == saved.originalVisible)
                        continue;

                    if (TryCallEntitySetVisible(setVisible, currentEntity, saved.originalVisible))
                        ++restored;
                }

                g_SatelliteVisibilityState.clear();
                g_SatVisWasActive = false;

                if (EnvFlagEnabled("OPENSHIM_TRACE_SATELLITE_VISIBILITY_FIX"))
                {
                    Log(L"[SATVISFIX] satellite exited — restored %zu objects (%zu deferred to other owners)\n",
                        restored, deferred);
                }
                return;
            }

            if (!currentSatellite)
            {
                ApplySatelliteVisibilityTestPreHide(setVisible);
                return;
            }

            // --- Entering or already in satellite ---
            const bool entering = !g_SatVisWasActive;
            const uint32_t tick = ++g_SatVisSweepTick;
            size_t synced = 0;
            size_t hidden = 0;

            static void* s_satObjects[kGameObjectArenaSlotCapacity];
            const size_t totalObjects =
                CollectLiveGameObjectsFromArena(s_satObjects, kGameObjectArenaSlotCapacity);

            for (size_t i = 0; i < totalObjects; ++i)
            {
                void* obj = s_satObjects[i];

                auto it = g_SatelliteVisibilityState.find(obj);

                // Stamp on arena presence, not on a successful entity read.
                // A tracked object whose entity fails to resolve for one tick
                // must keep its record: re-capturing later would read back the
                // visibility this pass had already applied and latch it in as
                // the "original", leaving the object hidden after satellite.
                if (it != g_SatelliteVisibilityState.end())
                    it->second.lastSeenTick = tick;

                float illumination = 0.0f;
                void* entity = nullptr;
                if (!TryReadObjectIlluminationAndEntity(obj, illumination, entity))
                    continue;

                if (!LooksLikeOgreObjectInPlace(entity))
                    continue;

                if (it == g_SatelliteVisibilityState.end())
                {
                    // New object (created during satellite, or first frame).
                    // Capture its actual Ogre visibility as the original.
                    bool original = true;
                    if (!TryCallEntityGetVisible(getVisible, entity, original))
                        continue;

                    const bool desired = original && (illumination > 0.0f);

                    SatelliteEntityVisibility entry;
                    entry.gameObject = obj;
                    entry.entity = entity;
                    entry.originalVisible = original;
                    entry.appliedVisible = desired;
                    entry.lastSeenTick = tick;

                    if (desired != original &&
                        !TryCallEntitySetVisible(setVisible, entity, desired))
                        continue;

                    g_SatelliteVisibilityState[obj] = entry;
                    ++synced;
                    if (!desired)
                        ++hidden;
                }
                else
                {
                    SatelliteEntityVisibility& saved = it->second;

                    // Lifecycle check: if the entity pointer changed, this
                    // GameObject was rebuilt (or the slot was reused) and the
                    // new entity has never been written by us. Re-capture its
                    // own visibility as the original rather than carrying the
                    // previous entity's state onto it.
                    if (saved.entity != entity)
                    {
                        bool original = true;
                        if (!TryCallEntityGetVisible(getVisible, entity, original))
                            continue;

                        saved.gameObject = obj;
                        saved.entity = entity;
                        saved.originalVisible = original;
                        saved.appliedVisible = original;
                    }

                    const bool desired = saved.originalVisible &&
                                         (illumination > 0.0f);

                    if (desired != saved.appliedVisible)
                    {
                        if (!TryCallEntitySetVisible(setVisible, entity, desired))
                            continue;
                        saved.appliedVisible = desired;
                    }

                    ++synced;
                    if (!desired)
                        ++hidden;
                }
            }

            // Sweep entries this pass did not visit: the GameObject left the
            // arena (destroyed during satellite), or stopped resolving to a
            // usable Ogre entity. Dropping the record is the whole cleanup --
            // the entity died with the object, so there is nothing to restore
            // and nothing to dereference.
            for (auto it = g_SatelliteVisibilityState.begin();
                 it != g_SatelliteVisibilityState.end();)
            {
                if (it->second.lastSeenTick != tick)
                    it = g_SatelliteVisibilityState.erase(it);
                else
                    ++it;
            }

            g_SatVisWasActive = true;

            if (entering && EnvFlagEnabled("OPENSHIM_TRACE_SATELLITE_VISIBILITY_FIX"))
            {
                Log(L"[SATVISFIX] satellite entered — synced %zu objects (%zu hidden)\n",
                    synced, hidden);
            }
        }

        // One row per populated team. Deliberately free of __try: every read it
        // performs goes through an existing SEH-guarded helper, so the function
        // itself can hold ordinary C++ state.
        struct SatelliteValidationTeamRow
        {
            uint32_t objects = 0;
            uint32_t illuminated = 0;      // the BZ 1.5 gate: illumination > 0
            uint32_t ogreVisible = 0;      // what Ogre will actually draw
            uint32_t ogreUnreadable = 0;   // no entity, or getVisible faulted
            uint32_t tracked = 0;          // present in the satellite state map
            uint32_t trackedOriginal = 0;  // ... of which were visible pre-satellite
            uint32_t trackedApplied = 0;   // ... of which the fix last set visible
        };

        void LogSatelliteVisibilityValidationSample()
        {
            if (!g_SatVisValidateEnabled)
                return;

            const DWORD now = GetTickCount();
            if (g_SatVisValidateLastTick != 0 &&
                (now - g_SatVisValidateLastTick) < kSatVisValidateIntervalMs)
            {
                return;
            }
            if (InterlockedDecrement(&g_SatVisValidateBudget) < 0)
                return;
            g_SatVisValidateLastTick = now;

            FnOgreEntityBoolQuery getVisible = GetOgreVisibleProc();
            if (!getVisible)
                return;

            long currentView = -1;
            TryReadCurrentViewId(currentView);
            void* const userObject = TryGetHeadlightPlayerObject();
            const int userTeam = GetGameObjectActualTeam(userObject);

            static void* s_validateObjects[kGameObjectArenaSlotCapacity];
            const size_t totalObjects =
                CollectLiveGameObjectsFromArena(s_validateObjects, kGameObjectArenaSlotCapacity);

            SatelliteValidationTeamRow rows[kSatVisValidateTeamCount];
            uint32_t offTeam = 0;

            for (size_t i = 0; i < totalObjects; ++i)
            {
                void* obj = s_validateObjects[i];
                const int team = GetGameObjectActualTeam(obj);
                if (team < 0 || team >= kSatVisValidateTeamCount)
                {
                    ++offTeam;
                    continue;
                }

                SatelliteValidationTeamRow& row = rows[team];
                ++row.objects;

                float illumination = 0.0f;
                void* entity = nullptr;
                if (!TryReadObjectIlluminationAndEntity(obj, illumination, entity) ||
                    !LooksLikeOgreObjectInPlace(entity))
                {
                    ++row.ogreUnreadable;
                    continue;
                }

                if (illumination > 0.0f)
                    ++row.illuminated;

                bool visible = false;
                if (TryCallEntityGetVisible(getVisible, entity, visible))
                {
                    if (visible)
                        ++row.ogreVisible;
                }
                else
                {
                    ++row.ogreUnreadable;
                }

                auto it = g_SatelliteVisibilityState.find(obj);
                if (it != g_SatelliteVisibilityState.end() && it->second.entity == entity)
                {
                    ++row.tracked;
                    if (it->second.originalVisible)
                        ++row.trackedOriginal;
                    if (it->second.appliedVisible)
                        ++row.trackedApplied;
                }
            }

            Log(L"[SATVISCHK] view=%ld satellite=%d userTeam=%d userObj=0x%08X total=%u "
                L"offTeam=%u tracked=%zu fix=%d remaining=%ld\n",
                currentView,
                IsSatelliteOverviewActive() ? 1 : 0,
                userTeam,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(userObject)),
                static_cast<unsigned>(totalObjects),
                offTeam,
                g_SatelliteVisibilityState.size(),
                g_SatelliteVisibilityFixEnabled ? 1 : 0,
                g_SatVisValidateBudget);

            for (int team = 0; team < kSatVisValidateTeamCount; ++team)
            {
                const SatelliteValidationTeamRow& row = rows[team];
                if (row.objects == 0)
                    continue;
                Log(L"[SATVISCHK]   team=%d n=%u illum=%u ogreVis=%u unreadable=%u "
                    L"tracked=%u orig=%u applied=%u\n",
                    team,
                    row.objects,
                    row.illuminated,
                    row.ogreVisible,
                    row.ogreUnreadable,
                    row.tracked,
                    row.trackedOriginal,
                    row.trackedApplied);
            }
        }
    }
}
