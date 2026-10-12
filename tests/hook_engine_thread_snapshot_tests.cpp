// Actual cross-thread executable writes. A cached snapshot made by A includes
// B; reusing it from B used to suspend B itself while holding the patch mutex.
#include "hook_engine.h"
#include "shim_log.h"
#include "test_check.h"
#include "bzr_options_ui.h"
#include <Windows.h>
#include <atomic>

namespace BZROpenShim {
    void LogShimA(LogLevel, const char*, const char*, ...) {}
    void Log(const wchar_t*, ...) {}
}
namespace
{
    void* volatile original = nullptr;
    std::atomic<bool> badOriginal{false};
    struct Caller { void* target=nullptr; std::atomic<bool> stop{false}; std::atomic<unsigned> calls{0}; };
    DWORD WINAPI CallThread(void* argument)
    {
        auto& caller=*static_cast<Caller*>(argument);
        auto* function=reinterpret_cast<DWORD(WINAPI*)(void*)>(caller.target);
        while(!caller.stop.load())
        {
            if(function(nullptr)!=42) badOriginal.store(true);
            ++caller.calls;
        }
        return 0;
    }
    DWORD WINAPI PublishedHook(void*)
    {
        auto* function = reinterpret_cast<DWORD(WINAPI*)(void*)>(InterlockedCompareExchangePointer(&original,nullptr,nullptr));
        if (!function) { badOriginal.store(true); return 0; }
        return function(nullptr);
    }
    struct Writer
    {
        HANDLE start = nullptr, done = nullptr;
        std::uint32_t address = 0;
        std::atomic<bool> stop{false}, success{false};
    };
    DWORD WINAPI WriteThread(void* input)
    {
        auto& writer = *static_cast<Writer*>(input);
        for (;;)
        {
            WaitForSingleObject(writer.start, INFINITE);
            if (writer.stop.load()) return 0;
            const unsigned char nop = 0x90;
            writer.success.store(HookEngine::WriteMemory(writer.address, &nop, 1));
            SetEvent(writer.done);
        }
    }
}
int main()
{
    static_assert(sizeof(void*) == 4, "Win32 patcher address contract");
    using OpenShimTest::Require;
    auto* page = VirtualAlloc(nullptr, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    Require(page != nullptr, "executable test page");
    Writer writers[2]; HANDLE threads[2]{};
    for (unsigned i = 0; i < 2; ++i)
    {
        writers[i].address = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(page));
        writers[i].start = CreateEventW(nullptr, FALSE, FALSE, nullptr);
        writers[i].done = CreateEventW(nullptr, FALSE, FALSE, nullptr);
        Require(writers[i].start && writers[i].done, "writer event handles");
        threads[i] = CreateThread(nullptr, 0, WriteThread, &writers[i], 0, nullptr);
        Require(threads[i] != nullptr, "two live writer threads");
    }
    for (unsigned round = 0; round < 16; ++round)
        for (auto& writer : writers)
        {
            SetEvent(writer.start);
            Require(WaitForSingleObject(writer.done, 5000) == WAIT_OBJECT_0,
                "alternating patch owners complete without self-suspension");
            Require(writer.success.load(), "executable write succeeded");
        }
    for (unsigned i = 0; i < 2; ++i)
    {
        writers[i].stop.store(true); SetEvent(writers[i].start);
        Require(WaitForSingleObject(threads[i], 5000) == WAIT_OBJECT_0, "writer shutdown");
        CloseHandle(threads[i]); CloseHandle(writers[i].start); CloseHandle(writers[i].done);
    }
    VirtualFree(page, 0, MEM_RELEASE);
    // Keep a real caller executing the target while the inline helper installs
    // its hook. Any hook invocation must already have its callable original.
    const unsigned char body[] = {0xB8,42,0,0,0,0xC2,4,0}; // mov eax,42; ret 4
    auto* target = VirtualAlloc(nullptr,4096,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE);
    Require(target!=nullptr,"inline publication target");
    std::memcpy(target,body,sizeof(body)); FlushInstructionCache(GetCurrentProcess(),target,sizeof(body));
    Caller caller; caller.target=target;
    HANDLE callingThread=CreateThread(nullptr,0,CallThread,&caller,0,nullptr);
    Require(callingThread!=nullptr,"concurrent native target caller");
    const auto deadline=GetTickCount64()+3000;
    while(!caller.calls.load()&&GetTickCount64()<deadline) Sleep(1);
    Require(caller.calls.load()>0,"caller executing target before install");
    BZROpenShim::InlineDetour32 detour{};
    Require(BZROpenShim::InstallInlineDetour32(detour,reinterpret_cast<uintptr_t>(target),reinterpret_cast<void*>(&PublishedHook),5,body,5,&original),"inline install publishes original");
    auto* function=reinterpret_cast<DWORD(WINAPI*)(void*)>(target);
    Require(function(nullptr)==42&&!badOriginal.load(),"reachable hook invokes already published original");
    Require(InterlockedCompareExchangePointer(&original,nullptr,nullptr)==detour.trampoline,"published original is owned trampoline");
    caller.stop.store(true); Require(WaitForSingleObject(callingThread,3000)==WAIT_OBJECT_0,"inline caller stopped");
    Require(!badOriginal.load(),"every concurrent target invocation retained its original"); CloseHandle(callingThread);
    return OpenShimTest::ExitCode();
}
