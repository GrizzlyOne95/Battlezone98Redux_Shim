// mp_ready_diagnostic.cpp -- reports why the main menu's multiplayer entry
// reads "Not Ready". See include/mp_ready_diagnostic.h for the rationale and
// reverse_engineering/mp_not_ready_readiness_chain.md for the derivation.

#include "mp_ready_diagnostic.h"

#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "patcher.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <process.h>

#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace
    {
        // ---- the readiness chain, as the engine evaluates it -------------
        //
        // cNetFriends::GetReadyState                       0x00753810
        //     return (PlatformReady() && GetBzrNetLobby()) ? 3 : 0;
        //
        // PlatformReady                                    0x00764870
        //     switch (g_PlatformMode)                      // 0x008F0470
        //         2 -> GalaxyOk
        //         1 -> SteamOk
        //         3 -> GalaxyOk && SteamOk
        //         4 -> (SteamOk || GalaxyOk) && BzrNetAuthOk
        //
        // SteamOk      0x007647F0  movzx eax,byte [0x00945463]  // SteamAPI_Init
        // GalaxyOk     0x00764810  [0x00945490] && *(int*)(galaxy+8) >= 3
        // BzrNetAuthOk 0x00764840  [0x00945484] && *(int*)(client+4) == 3
        // GetBzrNetLobby 0x00764760 return [0x00945470]
        //
        // Mode 4 is the shipped default, so on a normal install readiness turns
        // on BzrNetAuthOk -- the BZRNet websocket reaching authorized state 3 --
        // which is exactly the term the shell never reports.

        constexpr uintptr_t kPlatformModeAddr = 0x008F0470;
        constexpr uintptr_t kSteamInitFlagAddr = 0x00945463;
        constexpr uintptr_t kGalaxyObjAddr = 0x00945490;
        constexpr uintptr_t kBzrNetClientHolderAddr = 0x00945484;
        constexpr uintptr_t kBzrNetLobbyAddr = 0x00945470;
        constexpr uintptr_t kBzrNetNicknameAddr = 0x009453E0;
        constexpr size_t kBzrNetNicknameCapacity = 0x80;

        constexpr size_t kGalaxyStateOffset = 8;
        constexpr size_t kClientStateOffset = 4;

        // Each guard covers the instruction that names the global above, so a
        // build whose layout moved fails the check instead of reading a
        // plausible-looking value out of an unrelated address.
        struct ByteGuard
        {
            uintptr_t address;
            const uint8_t* bytes;
            size_t length;
            const char* label;
        };

        constexpr uint8_t kReadyGetterBytes[] = {
            // 0x00753810 cNetFriends::GetReadyState: call PlatformReady, test,
            // call GetBzrNetLobby, test, mov eax,3.
            0x55, 0x8B, 0xEC, 0x51, 0x89, 0x4D, 0xFC, 0xE8, 0x54, 0x10, 0x01, 0x00,
            0x85, 0xC0, 0x74, 0x12, 0xE8, 0x3B, 0x0F, 0x01, 0x00, 0x85, 0xC0, 0x74,
            0x09, 0xB8, 0x03, 0x00, 0x00, 0x00
        };
        constexpr uint8_t kPlatformReadyBytes[] = {
            // 0x00764870: cmp dword [0x008F0470], 2
            0x55, 0x8B, 0xEC, 0x83, 0x3D, 0x70, 0x04, 0x8F, 0x00, 0x02, 0x75, 0x13
        };
        constexpr uint8_t kSteamOkBytes[] = {
            // 0x007647F0: movzx eax, byte [0x00945463]
            0x55, 0x8B, 0xEC, 0x0F, 0xB6, 0x05, 0x63, 0x54, 0x94, 0x00, 0x85, 0xC0
        };
        constexpr uint8_t kGalaxyOkBytes[] = {
            // 0x00764810: cmp dword [0x00945490], 0 / mov ecx, [0x00945490]
            0x55, 0x8B, 0xEC, 0x83, 0x3D, 0x90, 0x54, 0x94, 0x00, 0x00, 0x74, 0x19,
            0x8B, 0x0D, 0x90, 0x54, 0x94, 0x00
        };
        constexpr uint8_t kBzrNetAuthOkBytes[] = {
            // 0x00764840: cmp dword [0x00945484], 0 / mov ecx, [0x00945484]
            0x55, 0x8B, 0xEC, 0x83, 0x3D, 0x84, 0x54, 0x94, 0x00, 0x00, 0x74, 0x19,
            0x8B, 0x0D, 0x84, 0x54, 0x94, 0x00
        };
        constexpr uint8_t kGetLobbyBytes[] = {
            // 0x00764760: mov eax, [0x00945470]; ret
            0x55, 0x8B, 0xEC, 0xA1, 0x70, 0x54, 0x94, 0x00, 0x5D, 0xC3
        };
        constexpr uint8_t kGalaxyStateBytes[] = {
            // 0x0073B100: cmp dword [eax+8], 3; jl
            0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x08, 0x89, 0x4D, 0xF8, 0x8B, 0x45, 0xF8,
            0x83, 0x78, 0x08, 0x03, 0x7C
        };
        constexpr uint8_t kClientStateBytes[] = {
            // 0x006C3AA0: cmp dword [eax+4], 3; jne
            0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x08, 0x89, 0x4D, 0xF8, 0x8B, 0x45, 0xF8,
            0x83, 0x78, 0x04, 0x03, 0x75
        };
        constexpr uint8_t kMenuRefreshBytes[] = {
            // 0x0078EB50: the per-frame main-menu refresh that writes the caption.
            0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x1C, 0x89, 0x4D, 0xFC, 0x8B, 0x45, 0xFC,
            0x83, 0xB8, 0x70, 0x01, 0x00, 0x00, 0x00
        };

        constexpr ByteGuard kGuards[] = {
            {0x00753810, kReadyGetterBytes, sizeof(kReadyGetterBytes), "ready-getter"},
            {0x00764870, kPlatformReadyBytes, sizeof(kPlatformReadyBytes), "platform-ready"},
            {0x007647F0, kSteamOkBytes, sizeof(kSteamOkBytes), "steam-ok"},
            {0x00764810, kGalaxyOkBytes, sizeof(kGalaxyOkBytes), "galaxy-ok"},
            {0x00764840, kBzrNetAuthOkBytes, sizeof(kBzrNetAuthOkBytes), "bzrnet-auth-ok"},
            {0x00764760, kGetLobbyBytes, sizeof(kGetLobbyBytes), "get-lobby"},
            {0x0073B100, kGalaxyStateBytes, sizeof(kGalaxyStateBytes), "galaxy-state"},
            {0x006C3AA0, kClientStateBytes, sizeof(kClientStateBytes), "client-state"},
            {0x0078EB50, kMenuRefreshBytes, sizeof(kMenuRefreshBytes), "menu-refresh"},
        };

        // ---- guarded reads ----------------------------------------------
        //
        // Every function that uses __try is kept free of unwindable objects
        // (C2712), which is why these are plain PODs and raw loops.

        bool BytesMatchAt(uintptr_t address, const uint8_t* expected, size_t length)
        {
            __try
            {
                const uint8_t* const at = reinterpret_cast<const uint8_t*>(address);
                for (size_t i = 0; i < length; ++i)
                    if (at[i] != expected[i])
                        return false;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
            return false;
        }

        bool ReadDword(uintptr_t address, uint32_t& out)
        {
            __try
            {
                out = *reinterpret_cast<const uint32_t*>(address);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
            return false;
        }

        bool ReadByte(uintptr_t address, uint8_t& out)
        {
            __try
            {
                out = *reinterpret_cast<const uint8_t*>(address);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
            return false;
        }

        // The BZRNet client holder stores the ADDRESS of a shared_ptr whose
        // first dword is the client, which is why this is a double indirection.
        bool ReadStateThroughHolder(uintptr_t holderAddr, size_t stateOffset,
                                    uint32_t& state, bool& present)
        {
            present = false;
            state = 0;
            __try
            {
                const uint8_t* const holder = *reinterpret_cast<uint8_t* const*>(holderAddr);
                if (!holder)
                    return true;
                const uint8_t* const object = *reinterpret_cast<uint8_t* const*>(holder);
                if (!object)
                    return true;
                present = true;
                state = *reinterpret_cast<const uint32_t*>(object + stateOffset);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
            return false;
        }

        bool ReadStateDirect(uintptr_t objectPtrAddr, size_t stateOffset,
                             uint32_t& state, bool& present)
        {
            present = false;
            state = 0;
            __try
            {
                const uint8_t* const object = *reinterpret_cast<uint8_t* const*>(objectPtrAddr);
                if (!object)
                    return true;
                present = true;
                state = *reinterpret_cast<const uint32_t*>(object + stateOffset);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
            return false;
        }

        // Shape of the name the Authorization body will carry. Reported as a
        // shape, not as the name itself, so a session log stays shareable.
        struct NameShape
        {
            uint32_t length;
            uint32_t nonAscii;   // bytes >= 0x80
            uint32_t control;    // bytes < 0x20
            bool unterminated;   // no NUL inside the engine's own buffer
            bool read;
        };

        NameShape ReadNameShape()
        {
            NameShape shape = {};
            __try
            {
                const uint8_t* const buffer =
                    reinterpret_cast<const uint8_t*>(kBzrNetNicknameAddr);
                size_t i = 0;
                for (; i < kBzrNetNicknameCapacity && buffer[i] != '\0'; ++i)
                {
                    if (buffer[i] >= 0x80)
                        ++shape.nonAscii;
                    else if (buffer[i] < 0x20)
                        ++shape.control;
                }
                shape.length = static_cast<uint32_t>(i);
                shape.unterminated = (i == kBzrNetNicknameCapacity);
                shape.read = true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
            return shape;
        }

        // ---- composed state ---------------------------------------------

        struct Readiness
        {
            uint32_t mode;
            bool steamOk;
            bool galaxyPresent;
            uint32_t galaxyState;
            bool galaxyOk;
            bool clientPresent;
            uint32_t clientState;
            bool bzrNetAuthOk;
            bool lobbyPresent;
            bool platformOk;
            uint32_t code;          // what the shell will read: 3 or 0
        };

        bool Evaluate(Readiness& r)
        {
            r = {};

            uint8_t steamFlag = 0;
            uint32_t lobby = 0;
            if (!ReadDword(kPlatformModeAddr, r.mode) ||
                !ReadByte(kSteamInitFlagAddr, steamFlag) ||
                !ReadDword(kBzrNetLobbyAddr, lobby))
                return false;
            r.steamOk = steamFlag != 0;
            r.lobbyPresent = lobby != 0;

            if (!ReadStateDirect(kGalaxyObjAddr, kGalaxyStateOffset,
                                 r.galaxyState, r.galaxyPresent))
                return false;
            r.galaxyOk = r.galaxyPresent && r.galaxyState >= 3;

            if (!ReadStateThroughHolder(kBzrNetClientHolderAddr, kClientStateOffset,
                                        r.clientState, r.clientPresent))
                return false;
            r.bzrNetAuthOk = r.clientPresent && r.clientState == 3;

            switch (r.mode)
            {
            case 1: r.platformOk = r.steamOk; break;
            case 2: r.platformOk = r.galaxyOk; break;
            case 3: r.platformOk = r.galaxyOk && r.steamOk; break;
            case 4: r.platformOk = (r.steamOk || r.galaxyOk) && r.bzrNetAuthOk; break;
            default: r.platformOk = false; break;
            }

            r.code = (r.platformOk && r.lobbyPresent) ? 3u : 0u;
            return true;
        }

        const wchar_t* ModeName(uint32_t mode)
        {
            switch (mode)
            {
            case 1: return L"steam";
            case 2: return L"gog";
            case 3: return L"steam+gog";
            case 4: return L"auto";
            default: return L"unknown";
            }
        }

        // What the client's connection state means. The value is the single
        // most useful field in the whole line: a client that never leaves 0/1
        // failed to reach the service at all (transport -- DNS, firewall, or an
        // IPv6 route the service does not answer on), whereas one that reaches
        // 2 and stops was refused during Authorization (which is where the
        // player's name is sent).
        const wchar_t* ClientStateName(uint32_t state)
        {
            switch (state)
            {
            case 0: return L"disconnected";
            case 1: return L"connecting";
            case 2: return L"connected-unauthorized";
            case 3: return L"authorized";
            default: return L"unknown";
            }
        }

        void DescribeBlockers(const Readiness& r, wchar_t* out, size_t outChars)
        {
            out[0] = L'\0';
            if (r.code == 3)
            {
                wcscpy_s(out, outChars, L"none");
                return;
            }

            bool first = true;
            const auto add = [&](const wchar_t* term)
            {
                if (!first)
                    wcscat_s(out, outChars, L",");
                wcscat_s(out, outChars, term);
                first = false;
            };

            switch (r.mode)
            {
            case 1:
                if (!r.steamOk) add(L"steam-api-init");
                break;
            case 2:
                if (!r.galaxyOk) add(L"galaxy-signin");
                break;
            case 3:
                if (!r.galaxyOk) add(L"galaxy-signin");
                if (!r.steamOk) add(L"steam-api-init");
                break;
            case 4:
                if (!r.steamOk && !r.galaxyOk) add(L"no-platform-identity");
                if (!r.bzrNetAuthOk) add(L"bzrnet-authorization");
                break;
            default:
                add(L"unknown-platform-mode");
                break;
            }
            if (!r.lobbyPresent) add(L"bzrnet-lobby-absent");
            if (first)
                wcscpy_s(out, outChars, L"none-identified");
        }

        volatile LONG g_Started = 0;

        bool DiagnosticEnabled()
        {
            if (EnvFlagEnabled("OPENSHIM_NO_MP_READY_DIAGNOSTIC"))
                return false;
            // Default on. This writes at most one line per state change and
            // patches nothing, and it is worthless if it has to be switched on
            // after the player has already hit the problem.
            bool enabled = true;
            if (TryGetUserConfigBool("Diagnostics", "LogMultiplayerReadiness", enabled))
                return enabled;
            return true;
        }

        // ---- optional: say why, in the shell itself ----------------------
        //
        // The menu refresh at 0x0078EB50 already knows how to display a reason:
        // for code 1 it writes multi_message/"no inet" into the MPStatus text
        // widget (screen+0x174) and for code 2 multi_message/"no auth". Both
        // branches are dead only because the getter never returns those codes.
        // MPStatus is an ordinary on-screen text element, not a hover tooltip,
        // so reviving a branch is enough to put the reason in front of the
        // player -- the shell blanks MPStatus to "" every frame and fills it
        // only here.
        //
        // Replacing the getter is contained: slot +0x20 resolves to 0x00753810
        // in all three cNetFriends vtables, and of the 41 GetNetFriends call
        // sites in .text exactly one (0x0078EB79, the menu refresh) dispatches
        // that slot. Nothing else in the game reads this value.
        //
        // Defaults OFF: it changes what the shell displays.

        bool ExplainerEnabled()
        {
            if (EnvFlagEnabled("OPENSHIM_NO_EXPLAIN_MP_NOT_READY"))
                return false;
            // Default on. A tester who hits "Not Ready" has no reason to report
            // without it, and a setting they would have had to enable first
            // would never be enabled in time to catch the occurrence.
            bool enabled = true;
            if (TryGetUserConfigBool("Fixes", "ExplainMultiplayerNotReady", enabled))
                return enabled;
            return true;
        }

        // Stands in for cNetFriends::GetReadyState (0x00753810), which takes
        // its object in ecx and returns the code in eax with no stack args.
        //
        // Always reports 1 rather than 2 for a failure. The stock codes only
        // distinguish two causes and their wording fits neither well ("no auth"
        // is "Sign into Game Center", a mobile-port leftover), so the reason is
        // carried by the string instead -- see NotReadyMessage below. Steering
        // every failure through the single code-1 branch means there is exactly
        // one call site to intercept.
        int __fastcall ExplainedGetReadyState(void*)
        {
            Readiness r = {};
            if (!Evaluate(r))
                return 0;   // cannot vouch for a reason; behave like stock
            return (r.code == 3) ? 3 : 1;
        }

        // Stands in for the Localize(section, key) call the code-1 branch makes
        // at 0x0078EC38 -- __cdecl, caller-cleaned, returns the string the shell
        // then writes into MPStatus. Only that one call site is redirected, so
        // every other localization lookup in the game is untouched, and the
        // arguments (always "multi_message"/"no inet" here) are ignored.
        //
        // The returned pointers are static storage, matching the lifetime the
        // localization table's own strings have.
        //
        // English only: these are not in localization_table.csv. That is the
        // deliberate trade for naming the real term -- the stock localized
        // strings can only ever say one of two things, and neither is accurate
        // for a platform sign-in failure.
        const char* __cdecl NotReadyMessage(const char*, const char*)
        {
            Readiness r = {};
            if (!Evaluate(r))
                return "Multiplayer unavailable";

            // Platform identity first: it gates everything after it, and which
            // platform to name depends on which ones this mode actually asks
            // for. Naming the wrong client sends the player to an app they do
            // not have, which is worse than saying nothing.
            switch (r.mode)
            {
            case 1:
                if (!r.steamOk)
                    return "Sign into Steam";
                break;
            case 2:
                if (!r.galaxyOk)
                    return "Sign into GOG Galaxy";
                break;
            case 3:
                if (!r.steamOk && !r.galaxyOk)
                    return "Sign into Steam and Galaxy";
                if (!r.galaxyOk)
                    return "Sign into GOG Galaxy";
                if (!r.steamOk)
                    return "Sign into Steam";
                break;
            case 4:
                if (!r.steamOk && !r.galaxyOk)
                {
                    // A Galaxy object that exists but is short of signed-in is
                    // the ordinary GOG case; name only Galaxy there rather than
                    // sending a GOG player to Steam.
                    if (r.galaxyPresent)
                        return "Sign into GOG Galaxy";
                    return "Sign into Steam or Galaxy";
                }
                break;
            default:
                return "Unsupported platform mode";
            }

            if (!r.bzrNetAuthOk)
            {
                if (!r.clientPresent)
                    return "Connecting to BZRNet";
                // State 2 means the socket reached the service and the
                // Authorization was refused; 0 and 1 mean it never got there,
                // which for the player is the stock reading: no route out.
                if (r.clientState == 2)
                    return "BZRNet sign-in refused";
                return "Connect to internet";
            }

            if (!r.lobbyPresent)
                return "BZRNet lobby unavailable";

            return "Multiplayer unavailable";
        }

        // 0x0078EC38: the call Localize("multi_message","no inet") inside the
        // code-1 branch of the menu refresh.
        constexpr uintptr_t kLocalizeCallSite = 0x0078EC38;
        constexpr uint8_t kLocalizeCallBytes[] = { 0xE8, 0x03, 0xDF, 0x08, 0x00 };

        void InstallExplainer()
        {
            // Guarded separately from kGuards so a layout change here stands
            // down only the explainer, leaving the diagnostic reporting.
            if (!BytesMatchAt(kLocalizeCallSite, kLocalizeCallBytes,
                              sizeof(kLocalizeCallBytes)))
            {
                Log(L"[MPREADY] Explainer stands down: message call site at "
                    L"0x%08X does not match\n",
                    static_cast<uint32_t>(kLocalizeCallSite));
                return;
            }

            HookEngine::PatchDef getter;
            getter.address = 0x00753810;
            getter.type = HookEngine::PatchType::JMP5;
            getter.name = "cNetFriends::GetReadyState/explain";
            getter.verified = true;
            getter.expected_original.assign(kReadyGetterBytes, kReadyGetterBytes + 5);
            getter.payload = HookEngine::MakeJmp5Payload(
                0x00753810,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&ExplainedGetReadyState)));

            if (!HookEngine::ApplyPatch(getter))
            {
                Log(L"[MPREADY] Explainer failed to install at 0x00753810\n");
                return;
            }

            HookEngine::PatchDef message;
            message.address = static_cast<uint32_t>(kLocalizeCallSite);
            message.type = HookEngine::PatchType::REL32;
            message.name = "MainScreen::MPStatus/message";
            message.verified = true;
            message.expected_original.assign(
                kLocalizeCallBytes, kLocalizeCallBytes + sizeof(kLocalizeCallBytes));

            const int32_t rel =
                static_cast<int32_t>(reinterpret_cast<uintptr_t>(&NotReadyMessage)) -
                static_cast<int32_t>(kLocalizeCallSite + 5);
            message.payload.assign(5, 0);
            message.payload[0] = 0xE8;
            std::memcpy(message.payload.data() + 1, &rel, sizeof(rel));

            if (HookEngine::ApplyPatch(message))
                Log(L"[MPREADY] Explainer installed: MPStatus now names the "
                    L"failing term under the multiplayer entry\n");
            else
                Log(L"[MPREADY] Explainer installed the getter but not the "
                    L"message; MPStatus will read \"Connect to internet\"\n");
        }

        unsigned __stdcall WatchProc(void*)
        {
            // The globals live in the exe's own image, so nothing here has to
            // wait on a module load; but the readiness terms are only populated
            // once platform init has run, so give it a moment before the first
            // guard check rather than reporting a torn startup state.
            Sleep(3000);

            for (const ByteGuard& guard : kGuards)
            {
                if (BytesMatchAt(guard.address, guard.bytes, guard.length))
                    continue;
                Log(L"[MPREADY] Byte guard '%hs' mismatched at 0x%08X; readiness "
                    L"diagnostic stands down on this build\n",
                    guard.label, static_cast<uint32_t>(guard.address));
                return 0;
            }

            // The guards above cover the getter this replaces, so the explainer
            // is only ever installed on a build whose layout it was written for.
            if (ExplainerEnabled())
                InstallExplainer();

            if (!DiagnosticEnabled())
                return 0;

            Log(L"[MPREADY] Watching main-menu multiplayer readiness "
                L"(getter 0x00753810, caption 0x0078EB50)\n");

            bool havePrevious = false;
            Readiness previous = {};
            NameShape previousName = {};

            for (;;)
            {
                Readiness now = {};
                if (Evaluate(now))
                {
                    const bool changed =
                        !havePrevious ||
                        now.code != previous.code ||
                        now.mode != previous.mode ||
                        now.steamOk != previous.steamOk ||
                        now.galaxyOk != previous.galaxyOk ||
                        now.galaxyState != previous.galaxyState ||
                        now.clientPresent != previous.clientPresent ||
                        now.clientState != previous.clientState ||
                        now.lobbyPresent != previous.lobbyPresent;

                    if (changed)
                    {
                        wchar_t blockers[192] = {};
                        DescribeBlockers(now, blockers, 192);

                        Log(L"[MPREADY] code=%u button=\"%ls\" mode=%u(%ls) steam-api=%hs "
                            L"galaxy=%hs(state=%u) bzrnet-client=%hs(state=%u:%ls) "
                            L"bzrnet-lobby=%hs blocked-by=%ls\n",
                            now.code,
                            now.code == 3 ? L"Multiplayer" : L"Not Ready",
                            now.mode, ModeName(now.mode),
                            now.steamOk ? "ok" : "not-initialized",
                            now.galaxyPresent ? "present" : "absent", now.galaxyState,
                            now.clientPresent ? "present" : "absent",
                            now.clientState, ClientStateName(now.clientState),
                            now.lobbyPresent ? "present" : "null",
                            blockers);

                        // Only worth printing alongside a state change, and only
                        // when the name is actually capable of being the cause.
                        const NameShape name = ReadNameShape();
                        if (name.read &&
                            (name.length != previousName.length ||
                             name.nonAscii != previousName.nonAscii ||
                             name.control != previousName.control))
                        {
                            Log(L"[MPREADY] Authorization name shape: len=%u non-ascii=%u "
                                L"control=%u unterminated=%hs\n",
                                name.length, name.nonAscii, name.control,
                                name.unterminated ? "yes" : "no");
                            previousName = name;
                        }

                        previous = now;
                        havePrevious = true;
                    }
                }
                Sleep(500);
            }
        }
    }

    void InitializeMpReadyDiagnostic()
    {
        if (InterlockedCompareExchange(&g_Started, 1, 0) != 0)
            return;
        // The worker owns the byte-guard check that both features depend on, so
        // it runs if either wants it.
        if (!DiagnosticEnabled() && !ExplainerEnabled())
            return;

        const uintptr_t thread = _beginthreadex(nullptr, 0, WatchProc, nullptr, 0, nullptr);
        if (thread)
            CloseHandle(reinterpret_cast<HANDLE>(thread));
        else
            Log(L"[MPREADY] Failed to start readiness watcher\n");
    }
}
