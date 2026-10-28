// community_key_auth.cpp
// BZR Open Shim - adds a per-server community identity key to the BZRNet
// Authorization message sent to non-official matchmaking servers, so a
// community server can recognise a returning player. The key is
// HMAC-SHA256(local master secret, "host:port") and is never sent to the
// official host, logged, or traced (bzrnet_protocol.cpp redacts it).
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "bzr_string.h"
#include "community_key.h"
#include "community_key_secret.h"
#include "hook_engine.h"
#include "patcher.h"
#include "net_optimizer.h"
#include "shim_log.h"

#include <Windows.h>

#include <array>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <string>

namespace BZROpenShim
{
    namespace Hooks
    {
        // FUN_006C6E60's Authorization branch calls the json serialize routine
        // (0x007D7970) at row+0x12, right after building the content object, a
        // local at [ebp-0x42C]. The thunk adds the key to that object first.
        constexpr uint32_t kAuthSerializeCallOffset = 0x12;
        constexpr uint32_t kJsonSerializeTarget = 0x007D7970;

        using FnJsonObjectIndex = void*(__thiscall*)(void* object, const BzrString* key);
        using FnJsonAssignString = void(__thiscall*)(void* slot, const BzrString* value);

        static bool g_CommunityKeyHookDone = false;
        static uint32_t g_OriginalSerialize = 0;
        static FnBzrStringCtorFromCStr g_StringCtor = nullptr;
        static FnBzrStringDtor g_StringDtor = nullptr;
        static FnJsonObjectIndex g_JsonIndex = nullptr;
        static FnJsonAssignString g_JsonAssign = nullptr;

        // Locked because the Authorization builder's thread is not proven.
        static SRWLOCK g_SecretLock = SRWLOCK_INIT;
        static std::array<unsigned char, kCommunitySecretBytes> g_Secret = {};
        static bool g_SecretLoaded = false;

        // Deliberately unlatched, like the other lobby-event toggles: it is read
        // once per connect and nothing here is a patch site.
        static bool IsCommunityKeyEnabled()
        {
            if (EnvFlagEnabled("OPENSHIM_DISABLE_COMMUNITY_KEY"))
                return false;
            bool enabled = true;
            if (TryGetUserConfigBool("Network", "CommunityIdentityKey", enabled))
                return enabled;
            return true;
        }

        static void SafeStringDtor(BzrString* text)
        {
            __try
            {
                g_StringDtor(text);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        // Engine calls only, in a function free of unwindable objects so it
        // can use __try (C2712). Builds the two engine strings, stores the
        // value under "communityKey" in the content object, destroys both.
        static bool AttachEngineKey(void* content, const char* hex)
        {
            __declspec(align(8)) BzrString key;
            __declspec(align(8)) BzrString value;
            bool keyBuilt = false;
            bool valueBuilt = false;
            bool ok = false;
            __try
            {
                g_StringCtor(&key, "communityKey");
                keyBuilt = true;
                g_StringCtor(&value, hex);
                valueBuilt = true;
                void* const slot = g_JsonIndex(content, &key);
                if (slot)
                {
                    g_JsonAssign(slot, &value);
                    ok = true;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                ok = false;
            }
            if (valueBuilt)
                SafeStringDtor(&value);
            if (keyBuilt)
                SafeStringDtor(&key);
            return ok;
        }

        // Called from the thunk with the Authorization content object. Never
        // throws or faults into the engine; any failure sends no key.
        static void __cdecl AddCommunityKey(void* content)
        {
            static bool s_loggedDisabled = false;
            static bool s_loggedOfficial = false;
            static bool s_loggedNoSecret = false;
            try
            {
                if (!content)
                    return;
                if (!IsCommunityKeyEnabled())
                {
                    if (!s_loggedDisabled)
                    {
                        s_loggedDisabled = true;
                        Log(L"[BZRNET] Community identity key disabled; sending none\n");
                    }
                    return;
                }
                std::string server;
                bool official = false;
                if (!GetBzrNetEffectiveEndpoint(server, official))
                    return;
                if (official)
                {
                    if (!s_loggedOfficial)
                    {
                        s_loggedOfficial = true;
                        Log(L"[BZRNET] Official matchmaking server; community identity key not sent\n");
                    }
                    return;
                }
                std::string hex;
                AcquireSRWLockExclusive(&g_SecretLock);
                if (!g_SecretLoaded)
                {
                    const std::filesystem::path path = GetConfigModuleDirectory() / kCommunitySecretFileName;
                    g_SecretLoaded = LoadOrCreateCommunitySecret(path, g_Secret);
                }
                if (g_SecretLoaded)
                    hex = DeriveCommunityKey(g_Secret.data(), g_Secret.size(), server);
                const bool secretLoaded = g_SecretLoaded;
                ReleaseSRWLockExclusive(&g_SecretLock);
                if (!secretLoaded)
                {
                    if (!s_loggedNoSecret)
                    {
                        s_loggedNoSecret = true;
                        Log(L"[BZRNET] Community identity secret unavailable; sending no key\n");
                    }
                    return;
                }
                if (hex.empty())
                    return;
                const bool attached = AttachEngineKey(content, hex.c_str());
                SecureZeroMemory(&hex[0], hex.size());
                if (attached)
                    Log(L"[BZRNET] Community identity key attached for %hs\n", server.c_str());
                else
                    Log(L"[BZRNET] Community identity key could not be attached for %hs\n", server.c_str());
            }
            catch (...)
            {
            }
        }

        // Replaces the call to the json serializer. The return address stays
        // on the stack and the original is reached with jmp, so the engine sees
        // an unchanged call. The caller's ebp still addresses its locals.
        static __declspec(naked) void CommunityKeyAuthThunk()
        {
            __asm
            {
                push ecx
                push edx
                push dword ptr [ebp-0x42C]
                call AddCommunityKey
                add esp, 4
                pop edx
                pop ecx
                jmp dword ptr [g_OriginalSerialize]
            }
        }

        void InstallCommunityKeyAuthHookIfPossible()
        {
            if (g_CommunityKeyHookDone)
                return;
            g_CommunityKeyHookDone = true;

            uint32_t serializeRow = 0, contentLocal = 0, jsonIndex = 0, jsonAssign = 0, stringCtor = 0, stringDtor = 0;
            const HookEngine::EngineRow rows[] = {
                { "BzrNetAuthContentSerializeCall", &serializeRow },
                { "BzrNetAuthContentLocal", &contentLocal },
                { "BzrJsonObjectIndex", &jsonIndex },
                { "BzrJsonAssignString", &jsonAssign },
                { "BzrStringCtorFromCStr", &stringCtor },
                { "BzrStringDtor", &stringDtor },
            };
            bool installed = false;
            if (HookEngine::BindEngineRows("Community identity key", rows))
            {
                const uint32_t site = serializeRow + kAuthSerializeCallOffset;
                uint8_t call[5] = {};
                if (HookEngine::ReadMemory(site, call, sizeof(call)) && call[0] == 0xE8)
                {
                    int32_t relative = 0;
                    std::memcpy(&relative, call + 1, sizeof(relative));
                    const uint32_t target = site + 5 + static_cast<uint32_t>(relative);
                    if (target == kJsonSerializeTarget)
                    {
                        g_OriginalSerialize = target;
                        g_StringCtor = reinterpret_cast<FnBzrStringCtorFromCStr>(stringCtor);
                        g_StringDtor = reinterpret_cast<FnBzrStringDtor>(stringDtor);
                        g_JsonIndex = reinterpret_cast<FnJsonObjectIndex>(jsonIndex);
                        g_JsonAssign = reinterpret_cast<FnJsonAssignString>(jsonAssign);
                        installed = RedirectCallTarget(site, target,
                            reinterpret_cast<uintptr_t>(&CommunityKeyAuthThunk));
                    }
                }
            }
            if (installed)
                Log(L"[BZRNET] Community identity key hook installed\n");
            else
                Log(L"[BZRNET] Community identity key hook unavailable; no key will be sent\n");
        }
    }
}
