// net_tag_dispatch.cpp -- the one shared Net::Receive detour.
//
// Net::Receive 0x00570500 is __thiscall(Net* this, int arg0, ushort senderId,
// const uchar* buf, uint len), ret 0x10. It switches on the first two payload
// bytes read as a little-endian ushort; an unknown tag falls through
// silently, so an unpatched peer ignores OpenShim's messages.
//
// The 9-byte prologue can be detoured once. Features register a handler per
// tag here; the hook offers each message to the matching handler and calls
// the original for everything else (or when the handler declines).

#include "net_tag_dispatch.h"

#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cstring>

namespace BZROpenShim
{
    namespace NetTagDispatch
    {
        namespace
        {
            constexpr const char* kComponent = "NETTAG";
            constexpr unsigned kMaxHandlers = 8;

            using FnReceive = void(__thiscall*)(void* net, int arg0, unsigned senderId,
                                                const unsigned char* buf, unsigned len);

            // Prologue (push ebp / mov ebp,esp / sub esp,0x240; no relative operands).
            constexpr uint8_t kReceiveStolen[9] = { 0x55, 0x8B, 0xEC, 0x81, 0xEC, 0x40, 0x02, 0x00, 0x00 };

            struct Slot
            {
                uint16_t tag;
                Handler handler;
            };

            SRWLOCK g_Lock = SRWLOCK_INIT;
            Slot g_Slots[kMaxHandlers] = {};
            // Published after the slot is filled; readers never take the lock.
            std::atomic<unsigned> g_Count{ 0 };
            bool g_DetourInstalled = false;
            bool g_DetourFailed = false;
            InlineDetour32 g_ReceiveDetour = {};
            void* volatile g_ReceiveOriginal = nullptr;

            bool CallHandler(Handler handler, unsigned senderId, const unsigned char* buf, unsigned len, uint16_t tag)
            {
                __try
                {
                    return handler(senderId, buf, len);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    // A faulting handler must not take the game's receive
                    // loop down; treat the packet as consumed.
                    LogShimA(LogLevel::Warn, kComponent, "handler for tag 0x%04X faulted", tag);
                    return true;
                }
            }

            // thiscall(Net* this, int arg0, ushort senderId, buf, len), ret 0x10.
            void __fastcall ReceiveHook(void* net, void* /*edx*/, int arg0, unsigned senderId,
                                        const unsigned char* buf, unsigned len)
            {
                if (buf && len >= 2)
                {
                    uint16_t tag = 0;
                    std::memcpy(&tag, buf, sizeof(tag));
                    const unsigned count = g_Count.load(std::memory_order_acquire);
                    for (unsigned i = 0; i < count; ++i)
                    {
                        if (g_Slots[i].tag != tag)
                            continue;
                        if (CallHandler(g_Slots[i].handler, senderId, buf, len, tag))
                            return;
                        break;
                    }
                }
                const FnReceive original = reinterpret_cast<FnReceive>(g_ReceiveOriginal);
                if (original)
                    original(net, arg0, senderId, buf, len);
            }

            // Caller holds g_Lock.
            bool EnsureDetour()
            {
                if (g_DetourInstalled)
                    return true;
                if (g_DetourFailed)
                    return false;
                // Literal name so patch_registration_tests can check it
                // against scripts/patches.json.
                const uint32_t receiveAddr = HookEngine::ResolveNamedAddress("Net::Receive");
                if (!receiveAddr)
                {
                    g_DetourFailed = true;
                    LogShimA(LogLevel::Warn, kComponent, "Net::Receive did not resolve; no OpenShim net messages");
                    return false;
                }
                if (!InstallInlineDetour32(g_ReceiveDetour, receiveAddr, reinterpret_cast<void*>(ReceiveHook),
                                           sizeof(kReceiveStolen), kReceiveStolen, sizeof(kReceiveStolen),
                                           &g_ReceiveOriginal))
                {
                    g_DetourFailed = true;
                    LogShimA(LogLevel::Warn, kComponent,
                             "Net::Receive at 0x%08X failed its byte guard; no OpenShim net messages", receiveAddr);
                    return false;
                }
                g_DetourInstalled = true;
                LogShimA(LogLevel::Info, kComponent, "installed: Net::Receive 0x%08X", receiveAddr);
                return true;
            }
        }

        bool RegisterNetTagHandler(uint16_t tag, Handler handler)
        {
            if (!handler)
                return false;
            bool ok = false;
            AcquireSRWLockExclusive(&g_Lock);
            const unsigned count = g_Count.load(std::memory_order_relaxed);
            bool taken = false;
            for (unsigned i = 0; i < count; ++i)
                taken = taken || g_Slots[i].tag == tag;
            if (!taken && count < kMaxHandlers && EnsureDetour())
            {
                g_Slots[count].tag = tag;
                g_Slots[count].handler = handler;
                g_Count.store(count + 1, std::memory_order_release);
                ok = true;
            }
            ReleaseSRWLockExclusive(&g_Lock);
            if (ok)
                LogShimA(LogLevel::Info, kComponent, "registered handler for tag 0x%04X", tag);
            return ok;
        }
    }
}
