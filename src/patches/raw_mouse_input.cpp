// raw_mouse_input.cpp
// BZR Open Shim - raw mouse input: enables Redux's own Win32 raw-input
// mouse path behind verified gate bytes, with its packet hook, preference
// resolution and bridge accessors, split out of bzr_hooks.cpp.
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
        // -----------------------------------------------------------------
        // Raw mouse input
        // -----------------------------------------------------------------
        //
        // Redux already ships a complete Win32 raw-input mouse path. It never
        // runs because its enable flag lives in zero-initialised .data and the
        // only thing that ever sets it is the stock `rawinput` command-line
        // token. Recovered from the GOG 2.2.301 image (the decrypted Steam
        // image has the same layout):
        //
        //   0x00918424  int g_RawInputEnabled
        //   0x00618E82  startup gate. cmp [flag],0 / je skips
        //               RegisterRawInputDevices({usagePage 1, usage 2,
        //               flags 0, hwnd 0}) and then stores the returned BOOL
        //               back into the flag.
        //   0x00619717  WndProc mouse-message gate. cmp [flag],0 / jne skips
        //               ProcessMouseMessages(uMsg, wParam, lParam) outright.
        //   0x0061954A  WM_INPUT case. Reads the packet with GetRawInputData,
        //               requires RIM_TYPEMOUSE, then calls
        //               ProcessMouseRawInput(&raw->data.mouse).
        //   0x004357D0  ProcessMouseRawInput. Decodes usButtonFlags into the
        //               button masks, then accumulates lLastX / lLastY into
        //               0x02CEBCA0 / 0x02CEBCA4.
        //   0x00623C39  look consumer. Applies the stock magnitude-based
        //               acceleration curve to those accumulators, scales them
        //               by the same sensitivity table the legacy path uses,
        //               and zeroes them.
        //
        // Two properties of that design carry the requirements for free. The
        // legacy WM_MOUSEMOVE path is already mutually exclusive with the raw
        // path in stock code, so nothing has to be suppressed by hand; and the
        // accumulators are drained once per look update, so raw deltas stay
        // frame-rate independent with no scaling of ours.
        //
        // What OpenShim adds is turning the flag on, guarding the write, and
        // covering the one case the stock handler gets wrong (below).

        constexpr uintptr_t kRawMouseInputRegisterGateAddr = 0x00618E82;
        constexpr uintptr_t kRawMouseInputLegacyGateAddr = 0x00619717;
        constexpr uintptr_t kRawMouseInputConsumerGateAddr = 0x00623C39;

        // An absolute-mode device that goes quiet for this long is treated as
        // having moved elsewhere meanwhile (alt-tab, menu, another monitor),
        // so the next packet re-seeds the origin instead of differencing
        // against a stale one and slamming the camera.
        constexpr ULONGLONG kRawMouseAbsoluteReseedMs = 500;

        bool g_RawMouseInputSignaturesChecked = false;
        bool g_RawMouseInputSignaturesMatch = false;
        bool g_RawMouseInputProcessHookInstalled = false;
        bool g_RawMouseInputFirstPacketLogged = false;
        bool g_RawMouseAbsoluteNoticeLogged = false;
        bool g_RawMouseAbsoluteOriginValid = false;
        LONG g_RawMouseAbsoluteLastX = 0;
        LONG g_RawMouseAbsoluteLastY = 0;
        ULONGLONG g_RawMouseAbsoluteLastPacketTick = 0;
        long g_RawMouseInputTraceBudget = 0;
        unsigned long long g_RawMouseInputPacketCount = 0;

        using FnProcessMouseRawInput = void(__cdecl*)(RAWMOUSE*);
        InlineDetour32 g_RawMouseInputProcessDetour;
        FnProcessMouseRawInput g_BzrFn_ProcessMouseRawInputOriginal = nullptr;

        bool ShouldTraceRawMouseInput()
        {
            return EnvFlagEnabled("OPENSHIM_TRACE_RAW_INPUT") ||
                   EnvFlagEnabled("OPENSHIM_TRACE_MOUSE_INPUT");
        }

        // Anchors on the whole `cmp dword ptr [0x00918424], 0` instruction plus
        // the branch opcode that consumes it, at all three sites that read the
        // flag. Anchoring on the operand alone would match any unrelated
        // reference to the same address.
        bool RawMouseInputSignaturesMatch()
        {
            if (g_RawMouseInputSignaturesChecked)
                return g_RawMouseInputSignaturesMatch;

            g_RawMouseInputSignaturesChecked = true;
            g_RawMouseInputSignaturesMatch = false;

            // Every address here is an absolute operand, so the image has to be
            // at its preferred base.
            if (reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr)) != 0x00400000)
            {
                Log(L"[RAWINPUT] Executable relocated; stock raw-input path unavailable\n");
                return false;
            }

            static const uint8_t kRegisterGate[] =
            { 0x83, 0x3D, 0x24, 0x84, 0x91, 0x00, 0x00, 0x74 };
            static const uint8_t kLegacyGate[] =
            { 0x83, 0x3D, 0x24, 0x84, 0x91, 0x00, 0x00, 0x75 };
            static const uint8_t kConsumerGate[] =
            { 0x83, 0x3D, 0x24, 0x84, 0x91, 0x00, 0x00, 0x74 };
            static const uint8_t kProcessRawInput[] =
            { 0x55, 0x8B, 0xEC, 0x8B, 0x45, 0x08, 0x0F, 0xB7, 0x48, 0x04 };

            struct Site
            {
                uintptr_t address;
                const uint8_t* bytes;
                size_t length;
                const char* name;
            };
            const Site sites[] =
            {
                { kRawMouseInputRegisterGateAddr, kRegisterGate, sizeof(kRegisterGate), "register gate" },
                { kRawMouseInputLegacyGateAddr, kLegacyGate, sizeof(kLegacyGate), "legacy-suppress gate" },
                { kRawMouseInputConsumerGateAddr, kConsumerGate, sizeof(kConsumerGate), "look-consumer gate" },
                { kRawMouseInputProcessAddr, kProcessRawInput, sizeof(kProcessRawInput), "ProcessMouseRawInput" },
            };
            for (const Site& site : sites)
            {
                if (!ExpectedBytesMatchAt(site.address, site.bytes, site.length))
                {
                    Log(L"[RAWINPUT] Signature mismatch at 0x%08X (%hs); staying on the legacy mouse path\n",
                        static_cast<uint32_t>(site.address),
                        site.name);
                    return false;
                }
            }

            g_RawMouseInputSignaturesMatch = true;
            return true;
        }

        // The stock handler adds lLastX / lLastY into the look accumulator
        // without ever testing usFlags. For a device that reports
        // MOUSE_MOVE_ABSOLUTE -- remote desktop, most VM and KVM guest mice,
        // pen tablets -- those fields are a position in a normalised 0..65535
        // space, not a delta, so the stock code slams the camera to the edge
        // and pins it there. Differencing successive positions turns them back
        // into the relative movement the rest of the path expects.
        void __cdecl ProcessMouseRawInputHook(RAWMOUSE* raw)
        {
            if (raw)
            {
                const ULONGLONG now = GetTickCount64();
                ++g_RawMouseInputPacketCount;

                if ((raw->usFlags & MOUSE_MOVE_ABSOLUTE) != 0)
                {
                    const LONG x = raw->lLastX;
                    const LONG y = raw->lLastY;
                    const bool stale =
                        g_RawMouseAbsoluteLastPacketTick != 0 &&
                        now - g_RawMouseAbsoluteLastPacketTick > kRawMouseAbsoluteReseedMs;
                    const bool haveOrigin = g_RawMouseAbsoluteOriginValid && !stale;

                    raw->lLastX = haveOrigin ? x - g_RawMouseAbsoluteLastX : 0;
                    raw->lLastY = haveOrigin ? y - g_RawMouseAbsoluteLastY : 0;
                    g_RawMouseAbsoluteLastX = x;
                    g_RawMouseAbsoluteLastY = y;
                    g_RawMouseAbsoluteOriginValid = true;

                    if (!g_RawMouseAbsoluteNoticeLogged)
                    {
                        g_RawMouseAbsoluteNoticeLogged = true;
                        Log(L"[RAWINPUT] Absolute-mode mouse detected (usFlags=0x%04X); differencing positions into relative deltas\n",
                            static_cast<unsigned>(raw->usFlags));
                    }
                }
                else if (g_RawMouseAbsoluteOriginValid)
                {
                    // Back to a relative reporting device; drop the origin so a
                    // later absolute packet re-seeds instead of differencing
                    // against something ancient.
                    g_RawMouseAbsoluteOriginValid = false;
                }

                g_RawMouseAbsoluteLastPacketTick = now;

                if (!g_RawMouseInputFirstPacketLogged)
                {
                    g_RawMouseInputFirstPacketLogged = true;
                    Log(L"[RAWINPUT] First raw mouse packet received; raw look path is live\n");
                }

                if (g_RawMouseInputTraceBudget > 0 && ShouldTraceRawMouseInput())
                {
                    --g_RawMouseInputTraceBudget;
                    Log(L"[RAWINPUT] packet #%llu usFlags=0x%04X buttons=0x%04X data=%d dx=%ld dy=%ld\n",
                        g_RawMouseInputPacketCount,
                        static_cast<unsigned>(raw->usFlags),
                        static_cast<unsigned>(raw->usButtonFlags),
                        static_cast<int>(static_cast<short>(raw->usButtonData)),
                        static_cast<long>(raw->lLastX),
                        static_cast<long>(raw->lLastY));
                }
            }

            if (g_BzrFn_ProcessMouseRawInputOriginal)
                g_BzrFn_ProcessMouseRawInputOriginal(raw);
        }

        void InstallRawMouseInputProcessHookIfPossible()
        {
            if (g_RawMouseInputProcessHookInstalled || !RawMouseInputSignaturesMatch())
                return;

            // push ebp; mov ebp,esp; mov eax,[ebp+8]  -- a whole-instruction
            // boundary at 6 bytes, so the trampoline can replay it verbatim.
            static const uint8_t kExpectedPrologue[] =
            { 0x55, 0x8B, 0xEC, 0x8B, 0x45, 0x08 };
            if (!InstallInlineDetour32(g_RawMouseInputProcessDetour,
                                       kRawMouseInputProcessAddr,
                                       reinterpret_cast<void*>(ProcessMouseRawInputHook),
                                       sizeof(kExpectedPrologue),
                                       kExpectedPrologue,
                                       sizeof(kExpectedPrologue)))
            {
                // Not fatal. Without the hook the raw path still works for every
                // ordinary relative mouse; only the absolute-mode guard and the
                // packet diagnostics are lost.
                Log(L"[RAWINPUT] ProcessMouseRawInput hook install failed at 0x%08X; absolute-mode guard unavailable\n",
                    static_cast<uint32_t>(kRawMouseInputProcessAddr));
                return;
            }

            g_BzrFn_ProcessMouseRawInputOriginal =
                reinterpret_cast<FnProcessMouseRawInput>(g_RawMouseInputProcessDetour.trampoline);
            g_RawMouseInputProcessHookInstalled = true;
            Log(L"[RAWINPUT] Installed ProcessMouseRawInput guard at 0x%08X\n",
                static_cast<uint32_t>(kRawMouseInputProcessAddr));
        }

        bool TryReadRawMouseInputFlag(int& out)
        {
            if (!RawMouseInputSignaturesMatch())
                return false;
            __try
            {
                out = *reinterpret_cast<const int*>(kRawMouseInputEnabledAddr);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool TryWriteRawMouseInputFlag(int value)
        {
            if (!RawMouseInputSignaturesMatch())
                return false;
            __try
            {
                *reinterpret_cast<int*>(kRawMouseInputEnabledAddr) = value;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Matches a whole command-line token, so an install path that happens to
        // contain the word does not flip the setting. The stock parser compares
        // argv[i]+1 with _stricmp, i.e. one leading switch character.
        bool CommandLineHasToken(const std::string& lowerCommandLine, const char* token)
        {
            const size_t tokenLen = std::strlen(token);
            for (size_t pos = lowerCommandLine.find(token);
                 pos != std::string::npos;
                 pos = lowerCommandLine.find(token, pos + 1))
            {
                if (pos == 0)
                    continue;
                const char before = lowerCommandLine[pos - 1];
                if (before != '-' && before != '/')
                    continue;
                const size_t after = pos + tokenLen;
                if (after < lowerCommandLine.size() &&
                    !std::isspace(static_cast<unsigned char>(lowerCommandLine[after])))
                {
                    continue;
                }
                return true;
            }
            return false;
        }

        // Resolution order, most specific first: the stock command-line tokens,
        // then the legacy env overrides, then openshim.ini, then the default.
        bool ResolveRawMouseInputPreference(const char*& outSource)
        {
            std::string commandLine;
            if (const char* raw = GetCommandLineA())
                commandLine.assign(raw);
            std::transform(commandLine.begin(), commandLine.end(), commandLine.begin(),
                [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });

            // Test the negative token first: "norawinput" contains "rawinput".
            if (CommandLineHasToken(commandLine, "norawinput"))
            {
                outSource = "command line (norawinput)";
                return false;
            }
            if (CommandLineHasToken(commandLine, "rawinput"))
            {
                outSource = "command line (rawinput)";
                return true;
            }
            if (EnvFlagEnabled("OPENSHIM_DISABLE_RAW_MOUSE_INPUT") ||
                EnvFlagEnabled("BZR_DISABLE_RAW_MOUSE_INPUT"))
            {
                outSource = "environment";
                return false;
            }

            bool configured = false;
            if (TryGetUserConfigBool("General", "RawMouseInput", configured))
            {
                outSource = "openshim.ini";
                return configured;
            }

            outSource = "default";
            return false;
        }
    }

    using namespace Hooks;

    bool GetRawMouseInputEnabledFromBridge()
    {
        // Set by the stock `rawinput` / `norawinput` command-line parser and
        // consumed by startup before RegisterRawInputDevices. The stock code
        // then stores the registration result back into the same value.
        int flag = 0;
        return TryReadRawMouseInputFlag(flag) && flag != 0;
    }

    bool SetRawMouseInputEnabledFromBridge(bool enabled)
    {
        if (!RawMouseInputSignaturesMatch())
            return false;

        // Registration is idempotent and does not need a window: hwndTarget 0
        // means WM_INPUT follows keyboard focus, which is also what makes
        // alt-tab behave -- an unfocused window simply stops receiving
        // packets, and starts again on focus return with no re-registration.
        // Doing it here rather than relying on the stock startup gate covers
        // both orderings, since OpenShim can resolve either side of the
        // engine's own window-init pass.
        RAWINPUTDEVICE device = {};
        device.usUsagePage = 0x01; // Generic desktop controls
        device.usUsage = 0x02;     // Mouse
        device.dwFlags = enabled ? 0u : RIDEV_REMOVE;
        device.hwndTarget = nullptr;

        if (!RegisterRawInputDevices(&device, 1, sizeof(device)))
        {
            const unsigned long error = GetLastError();
            // RIDEV_REMOVE without a prior registration is not a failure worth
            // reporting; anything else leaves the flag clear so the engine
            // stays on its legacy mouse path.
            if (enabled || error != ERROR_INVALID_PARAMETER)
            {
                Log(L"[RAWINPUT] Runtime %hs failed win32=%lu; leaving the legacy mouse path active\n",
                    enabled ? "enable" : "disable",
                    error);
            }
            if (enabled)
                return false;
        }

        if (enabled)
            InstallRawMouseInputProcessHookIfPossible();

        if (!TryWriteRawMouseInputFlag(enabled ? 1 : 0))
        {
            Log(L"[RAWINPUT] Could not write the enable flag at 0x%08X; legacy mouse path stays active\n",
                static_cast<uint32_t>(kRawMouseInputEnabledAddr));
            return false;
        }

        // A fresh enable must not difference against a position captured
        // before the gap.
        g_RawMouseAbsoluteOriginValid = false;
        g_RawMouseAbsoluteLastPacketTick = 0;

        Log(L"[RAWINPUT] Runtime raw mouse input %hs\n",
            enabled ? "enabled" : "disabled");
        return true;
    }
}
