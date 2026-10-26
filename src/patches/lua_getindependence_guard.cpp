// lua_getindependence_guard.cpp -- fail-closed Lua GetIndependence binding.
//
// Mechanism: the Lua registration table row for "GetIndependence"
// (0x008720B8, { "GetIndependence" 0x0087CC24, 0x005041F0 }) has its
// function pointer swapped for an OpenShim lua_CFunction, as the Formation
// fix does. No code byte is rewritten; the stock binding stays intact.
//
// Why: native GetIndependence (0x005CB660) dereferences GameObject+0xFC
// after a null test only. During a save load that field still holds the
// GameObject::Load placeholder until PostLoadAll attaches the real
// AiProcess, so a mission Load() callback that calls GetIndependence faults
// at 0x005CB697 (mov eax,[ecx+0x18], ecx = 2 in the Campaign Reimagined
// misn02b report of 2026-10-26). The guarded binding answers 0 for any
// process that is not a real object in the game image and logs it.

#include "lua_getindependence_guard.h"
#include "lua_getindependence_guard_install.h"

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
    namespace LuaGetIndependence
    {
        namespace
        {
            constexpr const char* kComponent = "LUAINDEPENDENCE";
            constexpr uint32_t kGetIndependenceNameString = 0x0087CC24; // "GetIndependence"
            constexpr uint32_t kProcessFieldOffset = 0xFC;              // GameObject::aiProcess

            std::atomic<bool> g_Done{ false };
            volatile long g_RejectLogBudget = 16;

            using FnGetHandle = int32_t(__cdecl*)(void* L, int index);
            using FnPushInteger = void(__cdecl*)(void* L, int32_t value);
            using FnGetIndependence = int32_t(__cdecl*)(int32_t handle);
            using FnGetObject = void*(__cdecl*)(int32_t handle);

            FnGetHandle g_GetHandle = nullptr;
            FnPushInteger g_PushInteger = nullptr;
            FnGetIndependence g_GetIndependence = nullptr;
            FnGetObject g_GetObject = nullptr;

            uintptr_t g_ImageBase = 0;
            uintptr_t g_ImageEnd = 0;

            // Vtables already proven to carry RTTI; GetIndependence runs per
            // object from AI scripts, so the RTTI walk is done once per class.
            uintptr_t g_KnownVtables[32] = {};
            long g_KnownVtableCount = 0;

            bool InImage(uintptr_t address, size_t size)
            {
                return address >= g_ImageBase && address < g_ImageEnd && size <= g_ImageEnd - address;
            }

            int32_t FwdGetHandle(void* L, int i) { return g_GetHandle(L, i); }
            void FwdPushInteger(void* L, int32_t v) { g_PushInteger(L, v); }
            int32_t FwdGetIndependence(int32_t h) { return g_GetIndependence(h); }
            void* FwdGetObject(int32_t h) { return g_GetObject(h); }

            bool ReadProcess(const void* object, uintptr_t& process)
            {
                process = 0;
                __try
                {
                    process = *reinterpret_cast<const volatile uintptr_t*>(
                        static_cast<const uint8_t*>(object) + kProcessFieldOffset);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    process = 0;
                    return false;
                }
            }

            bool ReadVtable(uintptr_t process, uintptr_t& vtable)
            {
                vtable = 0;
                __try
                {
                    vtable = *reinterpret_cast<const volatile uintptr_t*>(process);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    vtable = 0;
                    return false;
                }
            }

            // MSVC x86 RTTI: vtable[-1] is the complete object locator
            // (signature 0, type descriptor at +12), and the descriptor's
            // decorated name at +8 starts ".?AV" (class) or ".?AU" (struct).
            bool HasGameRtti(uintptr_t vtable)
            {
                __try
                {
                    const uintptr_t col = *reinterpret_cast<const volatile uintptr_t*>(vtable - 4);
                    if (!InImage(col, 16) || *reinterpret_cast<const volatile uint32_t*>(col) != 0)
                        return false;
                    const uintptr_t descriptor = *reinterpret_cast<const volatile uintptr_t*>(col + 12);
                    if (!InImage(descriptor, 12))
                        return false;
                    const volatile char* name = reinterpret_cast<const volatile char*>(descriptor + 8);
                    return name[0] == '.' && name[1] == '?' && name[2] == 'A' &&
                           (name[3] == 'V' || name[3] == 'U');
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool VtableIsGameClass(uintptr_t vtable)
            {
                if (!InImage(vtable, sizeof(uintptr_t)) || vtable < g_ImageBase + 4)
                    return false;
                for (long i = 0; i < g_KnownVtableCount; ++i)
                    if (g_KnownVtables[i] == vtable)
                        return true;
                if (!HasGameRtti(vtable))
                    return false;
                if (g_KnownVtableCount < static_cast<long>(sizeof(g_KnownVtables) / sizeof(g_KnownVtables[0])))
                    g_KnownVtables[g_KnownVtableCount++] = vtable;
                return true;
            }

            void OnReject(int32_t handle, uintptr_t process, uintptr_t vtable, Verdict verdict)
            {
                if (InterlockedDecrement(&g_RejectLogBudget) >= 0)
                    LogShimA(LogLevel::Warn, kComponent,
                             "GetIndependence(0x%08X): AI process 0x%08X (vtable 0x%08X) is %s, "
                             "not a live process; returning 0 instead of reading it. A script most "
                             "likely called GetIndependence while a save was still loading.",
                             static_cast<unsigned>(handle), static_cast<unsigned>(process),
                             static_cast<unsigned>(vtable), VerdictName(verdict));
            }

            // lua_CFunction: int (*)(lua_State*), cdecl, caller pops.
            int __cdecl GetIndependenceBinding(void* L)
            {
                static const Engine engine = { FwdGetHandle, FwdPushInteger, FwdGetIndependence, FwdGetObject,
                                               ReadProcess, ReadVtable, VtableIsGameClass, OnReject };
                return Run(L, engine);
            }

            bool Fail(const char* what)
            {
                LogShimA(LogLevel::Warn, kComponent, "%s; leaving the stock GetIndependence binding", what);
                return false;
            }

            bool Bind(const char* name, uint32_t& address)
            {
                const HookEngine::EngineAddressStatus status = HookEngine::ResolveEngineAddress(name, address);
                if (status == HookEngine::EngineAddressStatus::Bound && address != 0)
                    return true;
                LogShimA(LogLevel::Warn, kComponent,
                         "engine address \"%s\" not verified (status=%d)", name, static_cast<int>(status));
                return false;
            }

            bool IsEnabled()
            {
                bool enabled = true;
                static const EnvSwitches::EnvSwitch rows[] = {
                    { &enabled, EnvSwitches::Kind::KillSwitch,
                      "OPENSHIM_DISABLE_GETINDEPENDENCE_GUARD", "BZR_DISABLE_GETINDEPENDENCE_GUARD" },
                };
                EnvSwitches::Apply(rows, EnvFlagEnabled);
                return enabled;
            }

            bool ReadImageRange()
            {
                const auto* base = reinterpret_cast<const uint8_t*>(GetModuleHandleW(nullptr));
                if (!base)
                    return false;
                const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(base);
                if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                    return false;
                const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS32*>(base + dos->e_lfanew);
                if (nt->Signature != IMAGE_NT_SIGNATURE || nt->OptionalHeader.SizeOfImage == 0)
                    return false;
                g_ImageBase = reinterpret_cast<uintptr_t>(base);
                g_ImageEnd = g_ImageBase + nt->OptionalHeader.SizeOfImage;
                return true;
            }

            bool DoInstall()
            {
                uint32_t binding = 0, getHandle = 0, pushInteger = 0, getIndependence = 0, getObject = 0,
                         slotRow = 0;
                if (!Bind("LuaGetIndependenceBinding", binding) || !Bind("LuaGetHandle", getHandle) ||
                    !Bind("LuaPushInteger", pushInteger) || !Bind("GameGetIndependence", getIndependence) ||
                    !Bind("GameObjectHandleGetObj", getObject))
                    return Fail("a required engine function failed its byte guard");

                if (HookEngine::ResolveEngineAddress("LuaGetIndependenceRegistration", slotRow) !=
                        HookEngine::EngineAddressStatus::BoundData || slotRow == 0)
                    return Fail("the registration row address is not pinned for this build");

                if (!ReadImageRange())
                    return Fail("the game image bounds are unreadable");

                // The row is { const char* name; lua_CFunction fn; }.
                uint32_t row[2] = {};
                char name[24] = {};
                if (!HookEngine::ReadMemory(slotRow, row, sizeof(row)) ||
                    !HookEngine::ReadMemory(row[0], name, sizeof(name) - 1))
                    return Fail("the registration row is unreadable");
                if (row[0] != kGetIndependenceNameString || std::strcmp(name, "GetIndependence") != 0)
                    return Fail("the registration row does not name \"GetIndependence\"");
                if (row[1] != binding)
                    return Fail("the registration row does not hold the stock binding");

                g_GetHandle = reinterpret_cast<FnGetHandle>(static_cast<uintptr_t>(getHandle));
                g_PushInteger = reinterpret_cast<FnPushInteger>(static_cast<uintptr_t>(pushInteger));
                g_GetIndependence = reinterpret_cast<FnGetIndependence>(static_cast<uintptr_t>(getIndependence));
                g_GetObject = reinterpret_cast<FnGetObject>(static_cast<uintptr_t>(getObject));

                const uint32_t replacement =
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&GetIndependenceBinding));
                if (!HookEngine::WriteMemory(slotRow + 4, &replacement, sizeof(replacement)))
                    return Fail("the registration row could not be rewritten");

                LogShimA(LogLevel::Info, kComponent,
                         "installed: row=0x%08X stock=0x%08X now=0x%08X native=0x%08X getObj=0x%08X "
                         "image=0x%08X-0x%08X",
                         slotRow, binding, replacement, getIndependence, getObject,
                         static_cast<unsigned>(g_ImageBase), static_cast<unsigned>(g_ImageEnd));
                return true;
            }
        }

        void InstallLuaGetIndependenceGuardIfPossible()
        {
            if (g_Done.exchange(true))
                return;
            if (!IsEnabled())
            {
                LogShimA(LogLevel::Info, kComponent, "disabled ([Fixes] LuaGetIndependenceGuard = 0)");
                return;
            }
            DoInstall();
        }
    }
}
