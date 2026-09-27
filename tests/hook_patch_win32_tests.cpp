// Windows-only tests for the shared hook patchers: IatPatch (import-table
// entries) and ComVtablePatch (COM vtable entries). The IAT cases patch this
// test executable's own import of GetTickCount and call through it.

#include "com_vtable_patch.h"
#include "iat_patch.h"

#include <cstdio>

namespace
{
    int g_failures = 0;

    void Check(bool cond, const char* what, int line)
    {
        if (!cond)
        {
            ++g_failures;
            std::printf("FAIL %d: %s\n", line, what);
        }
    }

#define CHECK(c) Check((c), #c, __LINE__)

    using BZROpenShim::IatPatch::PatchImport;
    using BZROpenShim::IatPatch::PatchImportFromAnyDll;
    using IatResult = BZROpenShim::IatPatch::Result;

    constexpr DWORD kFakeTicks = 0x12345678u;

    DWORD WINAPI FakeGetTickCount()
    {
        return kFakeTicks;
    }

    // The compiler treats an import pointer as constant and may reuse an
    // address it loaded before the patch, so the checks read the IAT slot
    // itself rather than calling GetTickCount by name.
    void* SlotValue(void** slot)
    {
        return slot ? *static_cast<void* volatile*>(slot) : nullptr;
    }

    DWORD CallThrough(void** slot)
    {
        using Fn = DWORD(WINAPI*)();
        return reinterpret_cast<Fn>(SlotValue(slot))();
    }

    void TestPatchImportByDllName()
    {
        HMODULE self = GetModuleHandleW(nullptr);
        void* realGetTickCount = reinterpret_cast<void*>(
            GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "GetTickCount"));

        void* original = nullptr;
        void** slot = nullptr;
        CHECK(PatchImport(self, "kernel32.dll", "GetTickCount",
                          reinterpret_cast<void*>(&FakeGetTickCount), &original, &slot) ==
              IatResult::Patched);
        CHECK(slot != nullptr);
        CHECK(original == realGetTickCount);
        CHECK(SlotValue(slot) == reinterpret_cast<void*>(&FakeGetTickCount));
        CHECK(CallThrough(slot) == kFakeTicks);

        // Patching again is a no-op and keeps the saved original.
        void** secondSlot = nullptr;
        CHECK(PatchImport(self, "KERNEL32.DLL", "GetTickCount",
                          reinterpret_cast<void*>(&FakeGetTickCount), &original, &secondSlot) ==
              IatResult::Patched);
        CHECK(secondSlot == slot);
        CHECK(original == realGetTickCount);

        // Put the real function back.
        void* ignored = nullptr;
        CHECK(PatchImport(self, "kernel32.dll", "GetTickCount", original, &ignored) ==
              IatResult::Patched);
        CHECK(SlotValue(slot) == realGetTickCount);
    }

    void TestPatchImportFromAnyDll()
    {
        HMODULE self = GetModuleHandleW(nullptr);
        void* original = nullptr;
        void** slot = nullptr;
        CHECK(PatchImportFromAnyDll(self, "GetTickCount",
                                    reinterpret_cast<void*>(&FakeGetTickCount), &original, &slot) ==
              IatResult::Patched);
        CHECK(slot != nullptr && original != nullptr);
        CHECK(SlotValue(slot) == reinterpret_cast<void*>(&FakeGetTickCount));
        CHECK(CallThrough(slot) == kFakeTicks);

        void* ignored = nullptr;
        void** restoreSlot = nullptr;
        CHECK(PatchImportFromAnyDll(self, "GetTickCount", original, &ignored, &restoreSlot) == IatResult::Patched);
        CHECK(restoreSlot == slot);
        CHECK(SlotValue(slot) == original);
    }

    void TestPatchImportNotFound()
    {
        HMODULE self = GetModuleHandleW(nullptr);
        void* original = nullptr;
        void** slot = nullptr;
        void* hook = reinterpret_cast<void*>(&FakeGetTickCount);
        CHECK(PatchImport(self, "kernel32.dll", "NoSuchImport", hook, &original, &slot) ==
              IatResult::NotFound);
        CHECK(PatchImport(self, "no_such_dll.dll", "GetTickCount", hook, &original, &slot) ==
              IatResult::NotFound);
        CHECK(PatchImportFromAnyDll(self, "NoSuchImport", hook, &original, &slot) ==
              IatResult::NotFound);
        CHECK(PatchImport(nullptr, "kernel32.dll", "GetTickCount", hook, &original) ==
              IatResult::NotFound);
        CHECK(original == nullptr);
        CHECK(slot == nullptr);
    }

    // A stand-in COM object: its first member points at a writable table.
    void* g_Vtable[4] = {};
    struct FakeObject
    {
        void** vtable = g_Vtable;
    };

    int First() { return 1; }
    int Second() { return 2; }
    int Hook() { return 3; }
    int OtherHook() { return 4; }

    using BZROpenShim::ComVtablePatch::OnForeignWrapper;
    using BZROpenShim::ComVtablePatch::PatchEntry;
    using VtResult = BZROpenShim::ComVtablePatch::Result;

    void TestVtablePatchSavesOriginalOnce()
    {
        g_Vtable[1] = reinterpret_cast<void*>(&First);
        FakeObject object;
        void* original = nullptr;
        CHECK(PatchEntry(&object, 1, reinterpret_cast<void*>(&Hook), original,
                         OnForeignWrapper::Refuse) == VtResult::Patched);
        CHECK(g_Vtable[1] == reinterpret_cast<void*>(&Hook));
        CHECK(original == reinterpret_cast<void*>(&First));

        CHECK(PatchEntry(&object, 1, reinterpret_cast<void*>(&Hook), original,
                         OnForeignWrapper::Refuse) == VtResult::AlreadyHooked);

        // The entry reverted to the saved original: re-patch it.
        g_Vtable[1] = reinterpret_cast<void*>(&First);
        CHECK(PatchEntry(&object, 1, reinterpret_cast<void*>(&Hook), original,
                         OnForeignWrapper::Refuse) == VtResult::Patched);
        CHECK(original == reinterpret_cast<void*>(&First));
    }

    void TestVtablePatchForeignWrapperPolicy()
    {
        FakeObject object;
        void* original = reinterpret_cast<void*>(&First);

        g_Vtable[2] = reinterpret_cast<void*>(&OtherHook);
        CHECK(PatchEntry(&object, 2, reinterpret_cast<void*>(&Hook), original,
                         OnForeignWrapper::Refuse) == VtResult::ForeignWrapper);
        CHECK(g_Vtable[2] == reinterpret_cast<void*>(&OtherHook));

        CHECK(PatchEntry(&object, 2, reinterpret_cast<void*>(&Hook), original,
                         OnForeignWrapper::Overwrite) == VtResult::Patched);
        CHECK(g_Vtable[2] == reinterpret_cast<void*>(&Hook));
        CHECK(original == reinterpret_cast<void*>(&First));
    }

    void TestVtablePatchTypedOverloadAndNulls()
    {
        using Fn = int (*)();
        g_Vtable[3] = reinterpret_cast<void*>(&Second);
        FakeObject object;
        Fn original = nullptr;
        CHECK(PatchEntry(&object, 3, &Hook, original, OnForeignWrapper::Refuse) == VtResult::Patched);
        CHECK(original == &Second);

        void* none = nullptr;
        CHECK(PatchEntry(nullptr, 0, reinterpret_cast<void*>(&Hook), none,
                         OnForeignWrapper::Refuse) == VtResult::NoObject);
        FakeObject empty;
        empty.vtable = nullptr;
        CHECK(PatchEntry(&empty, 0, reinterpret_cast<void*>(&Hook), none,
                         OnForeignWrapper::Refuse) == VtResult::NoObject);
    }
}

int main()
{
    // Keeps GetTickCount in this executable's import table for the IAT cases.
    std::printf("hook_patch_win32_tests: start tick=%lu\n", static_cast<unsigned long>(GetTickCount()));
    TestPatchImportByDllName();
    TestPatchImportFromAnyDll();
    TestPatchImportNotFound();
    TestVtablePatchSavesOriginalOnce();
    TestVtablePatchForeignWrapperPolicy();
    TestVtablePatchTypedOverloadAndNulls();
    if (g_failures == 0)
        std::printf("hook_patch_win32_tests: all passed\n");
    return g_failures == 0 ? 0 : 1;
}
