// lua_send_length.cpp -- make Lua Send string lengths and table counts safe
// on the wire. Design, evidence and failure modes:
// Docs/LUA_SEND_STRING_LENGTH_20261018.md.
//
// Mechanism:
//   * Decoders (FUN_005059B0 strings, FUN_00505B50 tables): the extension
//     byte load `movsx edx, byte [ecx]` becomes `movzx`, one byte each, so a
//     received length of 128..255 is read as such instead of going negative
//     (the stock string path then faults in lua_pushlstring).
//   * Encoders (FUN_005058D0 strings, FUN_00505A10 tables): a JMP into a small
//     stub in front of the existing buffer-room check rejects lengths above
//     255 through that check's own `xor al,al` exit, so Send drops the
//     argument and logs it exactly as it does for an argument that does not
//     fit the packet, instead of emitting a wrapped low byte.
// All four writes go in together or not at all.

#include "lua_send_length.h"
#include "lua_send_length_install.h"

#include "bzr_options_ui.h"
#include "env_switch_table.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace LuaSendLength
    {
        namespace
        {
            constexpr const char* kComponent = "LUASENDLEN";
            constexpr size_t kStubSlot = 64;

            std::atomic<bool> g_Done{ false };
            std::atomic<bool> g_Installed{ false };

            bool Fail(const char* what)
            {
                LogShimA(LogLevel::Warn, kComponent, "%s; Lua Send length fix not installed", what);
                return false;
            }

            bool IsEnabled()
            {
                bool enabled = true;
                static const EnvSwitches::EnvSwitch rows[] = {
                    { &enabled, EnvSwitches::Kind::KillSwitch,
                      "OPENSHIM_DISABLE_LUA_SEND_LENGTH_FIX", "BZR_DISABLE_LUA_SEND_LENGTH_FIX" },
                };
                EnvSwitches::Apply(rows, EnvFlagEnabled);
                return enabled;
            }

            bool BuildDecoderPatch(const char* name, uint32_t site, HookEngine::PatchDef& def)
            {
                uint8_t bytes[3] = {};
                if (!site || !HookEngine::ReadMemory(site, bytes, sizeof(bytes)))
                {
                    LogShimA(LogLevel::Warn, kComponent, "\"%s\" did not resolve", name);
                    return false;
                }
                if (!DecoderSiteIsStock(bytes))
                {
                    LogShimA(LogLevel::Warn, kComponent, "\"%s\" at 0x%08X is %02X %02X %02X, not movsx edx,[ecx]",
                             name, site, bytes[0], bytes[1], bytes[2]);
                    return false;
                }
                def.address = site + static_cast<uint32_t>(kDecoderFlipOffset);
                def.type = HookEngine::PatchType::BYTE1;
                def.payload.assign(1, kDecoderMovzxOpcode);
                def.name = name;
                def.verified = true;
                def.expected_original.assign(1, kDecoderOriginal[kDecoderFlipOffset]);
                return true;
            }

            bool BuildEncoderPatch(const EncoderSite& site, uint32_t address, uint8_t* stub,
                                   HookEngine::PatchDef& def)
            {
                uint8_t bytes[32] = {};
                if (!address || site.expectedLen > sizeof(bytes) ||
                    !HookEngine::ReadMemory(address, bytes, site.expectedLen))
                {
                    LogShimA(LogLevel::Warn, kComponent, "\"%s\" did not resolve", site.resolveName);
                    return false;
                }
                if (std::memcmp(bytes, site.expected, site.expectedLen) != 0)
                {
                    LogShimA(LogLevel::Warn, kComponent, "\"%s\" at 0x%08X does not hold the stock room check",
                             site.resolveName, address);
                    return false;
                }

                const uint32_t stubAddr = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(stub));
                const std::vector<uint8_t> code = BuildGuardStub(site, address, stubAddr);
                if (code.size() > kStubSlot)
                    return false;
                std::memcpy(stub, code.data(), code.size());

                def.address = address;
                def.type = HookEngine::PatchType::BYTES;
                def.payload = BuildDetour(site, address, stubAddr);
                def.name = site.resolveName;
                def.verified = true;
                def.expected_original.assign(site.expected, site.expected + site.replayLen);
                return true;
            }

            bool DoInstall()
            {
                // Literal names so patch_registration_tests can check them
                // against scripts/patches.json; they equal the header's
                // kStringDecoderName / kTableDecoderName / EncoderSite names.
                const uint32_t stringDecoder = HookEngine::ResolveNamedAddress("Lua::UnpackString length extension load");
                const uint32_t tableDecoder = HookEngine::ResolveNamedAddress("Lua::UnpackTable count extension load");
                const uint32_t stringEncoder = HookEngine::ResolveNamedAddress("Lua::PackString length room check");
                const uint32_t tableEncoder = HookEngine::ResolveNamedAddress("Lua::PackTable count room check");

                std::vector<HookEngine::PatchDef> patches(4);
                if (!BuildDecoderPatch(kStringDecoderName, stringDecoder, patches[0]) ||
                    !BuildDecoderPatch(kTableDecoderName, tableDecoder, patches[1]))
                    return Fail("a decoder site failed its byte guard");

                // Never freed: the detours point here for the life of the process.
                auto* stubs = static_cast<uint8_t*>(
                    VirtualAlloc(nullptr, 2 * kStubSlot, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
                if (!stubs)
                    return Fail("no executable memory for the encoder guards");
                if (!BuildEncoderPatch(kStringEncoder, stringEncoder, stubs, patches[2]) ||
                    !BuildEncoderPatch(kTableEncoder, tableEncoder, stubs + kStubSlot, patches[3]))
                {
                    VirtualFree(stubs, 0, MEM_RELEASE);
                    return Fail("an encoder site failed its byte guard");
                }
                DWORD oldProtect = 0;
                VirtualProtect(stubs, 2 * kStubSlot, PAGE_EXECUTE_READ, &oldProtect);
                FlushInstructionCache(GetCurrentProcess(), stubs, 2 * kStubSlot);

                const std::vector<bool> applied = HookEngine::ApplyPatches(patches);
                size_t appliedCount = 0;
                for (bool ok : applied)
                    appliedCount += ok ? 1 : 0;
                if (appliedCount != patches.size())
                {
                    // Half a codec is worse than none: a peer that encodes
                    // stock but decodes fixed (or the reverse) is untested.
                    bool restored = true;
                    for (size_t i = 0; i < patches.size(); ++i)
                    {
                        if (!applied[i])
                            continue;
                        const std::vector<uint8_t>& original = patches[i].expected_original;
                        restored = HookEngine::WriteMemory(patches[i].address, original.data(), original.size()) && restored;
                    }
                    if (restored)
                        VirtualFree(stubs, 0, MEM_RELEASE);
                    LogShimA(LogLevel::Warn, kComponent, "%u of %u writes applied; %s",
                             static_cast<unsigned>(appliedCount), static_cast<unsigned>(patches.size()),
                             restored ? "rolled back" : "ROLLBACK FAILED, stubs kept alive");
                    return false;
                }

                LogShimA(LogLevel::Info, kComponent,
                         "installed: decoders movzx at 0x%08X/0x%08X; encoder guards (max %u) at 0x%08X->0x%08X, "
                         "0x%08X->0x%08X",
                         patches[0].address, patches[1].address, kMaxWireLength,
                         patches[2].address, static_cast<uint32_t>(reinterpret_cast<uintptr_t>(stubs)),
                         patches[3].address, static_cast<uint32_t>(reinterpret_cast<uintptr_t>(stubs + kStubSlot)));
                return true;
            }
        }

        void InstallLuaSendLengthFixIfPossible()
        {
            if (g_Done.exchange(true))
                return;
            if (!IsEnabled())
            {
                LogShimA(LogLevel::Info, kComponent, "disabled ([Fixes] LuaSendLengthUnsigned = 0)");
                return;
            }
            g_Installed.store(DoInstall());
        }
    }
}
