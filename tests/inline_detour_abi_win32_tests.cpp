// Executed Win32/x86 ABI regressions for the production inline-detour helper.
//
// Source-byte and instruction-boundary checks cannot prove that optimized
// callbacks, a relocated trampoline, and the caller agree on the x86 ABI.
// In particular, a bool result lives in AL: the upper EAX bytes may be dirty
// even when the callback returns false. Run this fixture in Release (/O2),
// as well as Debug, without launching the game or touching its executable.
#include "bzr_options_ui.h"
#include "shim_log.h"
#include "test_check.h"

#include <Windows.h>
#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace BZROpenShim
{
    void LogShimA(LogLevel, const char*, const char*, ...) {}
    void Log(const wchar_t*, ...) {}
}

namespace
{
    using OpenShimTest::Check;
    using OpenShimTest::Require;
    using RawFn = DWORD (__cdecl*)();
    using BoolFn = bool (__cdecl*)();
    using StdcallFn = DWORD (WINAPI*)(DWORD);
    using ThiscallFn = DWORD (__thiscall*)(void*, DWORD);

    void* volatile g_falseOriginal = nullptr;
    void* volatile g_trueOriginal = nullptr;
    void* volatile g_callOriginal = nullptr;
    void* volatile g_branchOriginal = nullptr;
    void* volatile g_stdcallOriginal = nullptr;
    void* volatile g_thiscallOriginal = nullptr;
    volatile DWORD g_helperCalls = 0;

    template <typename Fn>
    Fn Published(void* volatile* slot)
    {
        return reinterpret_cast<Fn>(InterlockedCompareExchangePointer(slot, nullptr, nullptr));
    }

    // The original machine-code functions return a 0/1 AL while deliberately
    // leaving nonzero garbage in EAX[31:8]. Release optimization must not
    // cause a false AL to be treated as a true 32-bit integer.
    __declspec(noinline) DWORD __cdecl FalseHook()
    {
        const BoolFn original = Published<BoolFn>(&g_falseOriginal);
        return original && original() ? 0xBAD0u : 0x600Du;
    }

    __declspec(noinline) DWORD __cdecl TrueHook()
    {
        const BoolFn original = Published<BoolFn>(&g_trueOriginal);
        return original && original() ? 0x600Du : 0xBAD0u;
    }

    __declspec(noinline) DWORD __cdecl CallHook()
    {
        const RawFn original = Published<RawFn>(&g_callOriginal);
        return original ? original() + 1 : 0;
    }

    __declspec(noinline) DWORD __cdecl BranchHook()
    {
        const RawFn original = Published<RawFn>(&g_branchOriginal);
        return original ? original() + 1 : 0;
    }

    __declspec(noinline) DWORD WINAPI StdcallHook(DWORD value)
    {
        const StdcallFn original = Published<StdcallFn>(&g_stdcallOriginal);
        return original ? original(value) + 10 : 0;
    }

    // On x86 a __fastcall adapter with a dummy EDX parameter is the native
    // bridge shape for a __thiscall method: ECX carries the object and the
    // first explicit argument remains on the stack.
    __declspec(noinline) DWORD __fastcall ThiscallHook(void* object, void*, DWORD value)
    {
        const ThiscallFn original = Published<ThiscallFn>(&g_thiscallOriginal);
        return original ? original(object, value) + 1 : 0;
    }

    // A caller that makes the callee-saved registers, stdcall ESP balance and
    // one x87 stack value observable. The output is [EBX, ESI, EDI, ESP delta,
    // float(1.0) bits]. The wrapper restores the host's own registers.
    extern "C" __declspec(naked) DWORD __cdecl CallWithSentinels(
        void* /*function*/, DWORD /*arg*/, DWORD* /*observed*/)
    {
        __asm
        {
            push ebp
            mov ebp, esp
            push ebx
            push esi
            push edi
            mov ebx, 0x12345678
            mov esi, 0x23456789
            mov edi, 0x3456789A
            mov edx, [ebp + 16]
            mov [edx + 12], esp
            fld1
            push dword ptr [ebp + 12]
            call dword ptr [ebp + 8]
            mov edx, [ebp + 16]
            sub dword ptr [edx + 12], esp
            fstp dword ptr [edx + 16]
            mov [edx], ebx
            mov [edx + 4], esi
            mov [edx + 8], edi
            pop edi
            pop esi
            pop ebx
            pop ebp
            ret
        }
    }

    void WriteRelative(std::uint8_t* instruction, std::size_t fieldOffset,
                       std::size_t instructionSize, const std::uint8_t* destination)
    {
        const std::uint32_t delta =
            static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(destination)) -
            static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(instruction + instructionSize));
        std::memcpy(instruction + fieldOffset, &delta, sizeof(delta));
    }

    std::uint8_t* ExecutablePage()
    {
        auto* page = static_cast<std::uint8_t*>(
            VirtualAlloc(nullptr, 4096, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE));
        Require(page != nullptr, "allocate a private executable test page");
        return page;
    }

    void TestDirtyUpperEaxAndBooleanCallbacks()
    {
        auto* page = ExecutablePage();
        // mov eax,0x7F123400; ret / mov eax,0x7F123401; ret
        const std::uint8_t falseCode[] = { 0xB8, 0x00, 0x34, 0x12, 0x7F, 0xC3 };
        const std::uint8_t trueCode[]  = { 0xB8, 0x01, 0x34, 0x12, 0x7F, 0xC3 };
        auto* falseEntry = page;
        auto* trueEntry = page + 64;
        std::memcpy(falseEntry, falseCode, sizeof(falseCode));
        std::memcpy(trueEntry, trueCode, sizeof(trueCode));
        FlushInstructionCache(GetCurrentProcess(), page, 128);

        Check(reinterpret_cast<RawFn>(falseEntry)() == 0x7F123400u,
              "false callback really has nonzero upper EAX bytes");
        Check(reinterpret_cast<RawFn>(trueEntry)() == 0x7F123401u,
              "true callback really has nonzero upper EAX bytes");

        BZROpenShim::InlineDetour32 falseDetour{}, trueDetour{};
        const std::uint8_t wrongPreimage[] = { 0xB8, 0xFF, 0x34, 0x12, 0x7F };
        Check(!BZROpenShim::InstallInlineDetour32(falseDetour,
            reinterpret_cast<std::uintptr_t>(falseEntry), reinterpret_cast<void*>(&FalseHook),
            5, wrongPreimage, sizeof(wrongPreimage), &g_falseOriginal),
            "mismatched callback preimage must refuse installation");
        Check(!falseDetour.trampoline && !g_falseOriginal &&
              std::memcmp(falseEntry, falseCode, sizeof(falseCode)) == 0,
              "failed install leaves entry and original pointer untouched");

        Require(BZROpenShim::InstallInlineDetour32(falseDetour,
            reinterpret_cast<std::uintptr_t>(falseEntry), reinterpret_cast<void*>(&FalseHook),
            5, falseCode, 5, &g_falseOriginal), "install false AL detour");
        Require(BZROpenShim::InstallInlineDetour32(trueDetour,
            reinterpret_cast<std::uintptr_t>(trueEntry), reinterpret_cast<void*>(&TrueHook),
            5, trueCode, 5, &g_trueOriginal), "install true AL detour");

        for (unsigned i = 0; i < 100; ++i)
        {
            Check(reinterpret_cast<RawFn>(falseEntry)() == 0x600Du,
                  "optimized false callback branches on AL, not dirty EAX");
            Check(reinterpret_cast<RawFn>(trueEntry)() == 0x600Du,
                  "optimized true callback branches on AL");
        }
        Check(!Published<BoolFn>(&g_falseOriginal)(), "false original still returns false through trampoline");
        Check(Published<BoolFn>(&g_trueOriginal)(), "true original still returns true through trampoline");
        Check(Published<RawFn>(&g_falseOriginal)() == 0x7F123400u,
              "trampoline preserves the original 32-bit EAX result");
        VirtualFree(page, 0, MEM_RELEASE);
    }

    void TestRelativeCallAndConditionalBranch()
    {
        auto* page = ExecutablePage();
        // call helper; mov eax,42; ret. The helper increments a real counter.
        auto* callEntry = page;
        auto* helper = page + 64;
        const std::uint8_t callCode[] = { 0xE8, 0, 0, 0, 0, 0xB8, 42, 0, 0, 0, 0xC3 };
        const std::uint8_t helperCode[] = { 0xFF, 0x05, 0, 0, 0, 0, 0xC3 };
        std::memcpy(callEntry, callCode, sizeof(callCode));
        std::memcpy(helper, helperCode, sizeof(helperCode));
        WriteRelative(callEntry, 1, 5, helper);
        const std::uint32_t counterAddress =
            static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&g_helperCalls));
        std::memcpy(helper + 2, &counterAddress, sizeof(counterAddress));

        // cmp eax,eax; je +6 to mov eax,42; ret, skipping mov eax,7; ret.
        auto* branchEntry = page + 128;
        const std::uint8_t branchCode[] = {
            0x39, 0xC0, 0x0F, 0x84, 0, 0, 0, 0,
            0xB8, 7, 0, 0, 0, 0xC3, 0xB8, 42, 0, 0, 0, 0xC3
        };
        std::memcpy(branchEntry, branchCode, sizeof(branchCode));
        WriteRelative(branchEntry + 2, 2, 6, branchEntry + 14);
        FlushInstructionCache(GetCurrentProcess(), page, 256);

        std::uint8_t callPreimage[5] = {};
        std::uint8_t branchPreimage[8] = {};
        std::memcpy(callPreimage, callEntry, sizeof(callPreimage));
        std::memcpy(branchPreimage, branchEntry, sizeof(branchPreimage));

        Check(reinterpret_cast<RawFn>(callEntry)() == 42 && g_helperCalls == 1,
              "unpatched relative CALL reaches its helper");
        Check(reinterpret_cast<RawFn>(branchEntry)() == 42,
              "unpatched conditional branch reaches the taken destination");

        BZROpenShim::InlineDetour32 callDetour{}, branchDetour{};
        Require(BZROpenShim::InstallInlineDetour32(callDetour,
            reinterpret_cast<std::uintptr_t>(callEntry), reinterpret_cast<void*>(&CallHook),
            5, callPreimage, sizeof(callPreimage), &g_callOriginal), "install rel32 CALL detour");
        Require(BZROpenShim::InstallInlineDetour32(branchDetour,
            reinterpret_cast<std::uintptr_t>(branchEntry), reinterpret_cast<void*>(&BranchHook),
            8, branchPreimage, sizeof(branchPreimage), &g_branchOriginal), "install rel32 Jcc detour");

        Check(reinterpret_cast<RawFn>(callEntry)() == 43 && g_helperCalls == 2,
              "relocated CALL reaches the original helper exactly once");
        Check(Published<RawFn>(&g_callOriginal)() == 42 && g_helperCalls == 3,
              "direct call through published CALL trampoline also reaches helper");
        Check(reinterpret_cast<RawFn>(branchEntry)() == 43,
              "relocated Jcc keeps the original taken destination");
        Check(Published<RawFn>(&g_branchOriginal)() == 42,
              "direct Jcc trampoline preserves branch and return");
        VirtualFree(page, 0, MEM_RELEASE);
    }

    void TestStdcallRegistersStackAndX87()
    {
        auto* page = ExecutablePage();
        // push ebx/esi/edi; mov eax,[esp+16]; add eax,1;
        // pop edi/esi/ebx; ret 4. Seven complete stolen prologue bytes.
        const std::uint8_t body[] = {
            0x53, 0x56, 0x57, 0x8B, 0x44, 0x24, 0x10,
            0x83, 0xC0, 0x01, 0x5F, 0x5E, 0x5B, 0xC2, 0x04, 0x00
        };
        std::memcpy(page, body, sizeof(body));
        FlushInstructionCache(GetCurrentProcess(), page, sizeof(body));
        std::array<DWORD, 5> observed{};
        auto invoke = [&](DWORD expected) {
            observed.fill(0);
            const DWORD actual = CallWithSentinels(page, 21, observed.data());
            Check(actual == expected, "stdcall return value from native target");
            Check(observed[0] == 0x12345678 && observed[1] == 0x23456789 &&
                  observed[2] == 0x3456789A, "callee-saved EBX/ESI/EDI survive");
            Check(observed[3] == 0, "stdcall call leaves ESP balanced");
            Check(observed[4] == 0x3F800000, "x87 stack value survives the hook");
        };
        invoke(22);

        BZROpenShim::InlineDetour32 detour{};
        Require(BZROpenShim::InstallInlineDetour32(detour,
            reinterpret_cast<std::uintptr_t>(page), reinterpret_cast<void*>(&StdcallHook),
            7, body, 7, &g_stdcallOriginal), "install seven-byte stdcall detour");
        for (unsigned i = 0; i < 100; ++i) invoke(32);
        Check(Published<StdcallFn>(&g_stdcallOriginal)(21) == 22,
              "published stdcall trampoline returns the original result");
        VirtualFree(page, 0, MEM_RELEASE);
    }

    void TestThiscallObjectAndStackArgument()
    {
        auto* page = ExecutablePage();
        // mov eax,[ecx]; add eax,[esp+4]; ret 4. The stolen six bytes are
        // two complete instructions and leave the original stack layout.
        const std::uint8_t body[] = {
            0x8B, 0x01, 0x03, 0x44, 0x24, 0x04, 0xC2, 0x04, 0x00
        };
        std::memcpy(page, body, sizeof(body));
        FlushInstructionCache(GetCurrentProcess(), page, sizeof(body));
        DWORD objectValue = 40;
        auto* method = reinterpret_cast<ThiscallFn>(page);
        Check(method(&objectValue, 2) == 42, "unpatched thiscall reads ECX and stack argument");

        BZROpenShim::InlineDetour32 detour{};
        Require(BZROpenShim::InstallInlineDetour32(detour,
            reinterpret_cast<std::uintptr_t>(page), reinterpret_cast<void*>(&ThiscallHook),
            6, body, 6, &g_thiscallOriginal), "install six-byte thiscall detour");
        for (unsigned i = 0; i < 100; ++i)
            Check(method(&objectValue, 2) == 43, "fastcall hook retains thiscall ECX and argument");
        Check(Published<ThiscallFn>(&g_thiscallOriginal)(&objectValue, 2) == 42,
              "published thiscall trampoline preserves original parameters");
        VirtualFree(page, 0, MEM_RELEASE);
    }
}

int main()
{
    static_assert(sizeof(void*) == 4, "x86 ABI test requires a Win32 executable");
    TestDirtyUpperEaxAndBooleanCallbacks();
    TestRelativeCallAndConditionalBranch();
    TestStdcallRegistersStackAndX87();
    TestThiscallObjectAndStackArgument();
    if (OpenShimTest::FailureCount() != 0)
        std::fprintf(stderr, "inline_detour_abi_win32_tests: %d failure(s)\n", OpenShimTest::FailureCount());
    else
        std::puts("inline_detour_abi_win32_tests: all checks passed");
    return OpenShimTest::ExitCode();
}
