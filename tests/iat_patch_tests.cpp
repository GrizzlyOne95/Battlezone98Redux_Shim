#include "iat_patch.h"

#include <cstdio>
#include <cstdlib>

namespace
{
    void Check(bool ok, const char* message)
    {
        if (!ok) { std::fprintf(stderr, "%s\n", message); std::exit(1); }
    }
    int Original() { return 1; }
    int Replacement() { return 2; }
}

int main()
{
    using namespace BZROpenShim::IatPatch;
    auto* image = static_cast<unsigned char*>(VirtualAlloc(
        nullptr, 0x2000, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));
    Check(image != nullptr, "allocate fixture");
    auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(image);
    dos->e_magic = IMAGE_DOS_SIGNATURE;
    dos->e_lfanew = 0x80;
    auto* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(image + 0x80);
    nt->Signature = IMAGE_NT_SIGNATURE;
    nt->OptionalHeader.Magic = IMAGE_NT_OPTIONAL_HDR_MAGIC;
    nt->OptionalHeader.SizeOfImage = 0x2000;
    nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT] =
        {0x300, 2 * sizeof(IMAGE_IMPORT_DESCRIPTOR)};
    auto* imports = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(image + 0x300);
    imports[0].Name = 0x500;
    imports[0].OriginalFirstThunk = 0x600;
    imports[0].FirstThunk = 0x650;
    strcpy_s(reinterpret_cast<char*>(image + 0x500), 32, "d3d11.dll");
    auto* name = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(image + 0x700);
    strcpy_s(reinterpret_cast<char*>(name->Name), 64, "D3D11CreateDevice");
    auto* names = reinterpret_cast<IMAGE_THUNK_DATA*>(image + 0x600);
    auto* slots = reinterpret_cast<IMAGE_THUNK_DATA*>(image + 0x650);
    names[0].u1.AddressOfData = 0x700;
    void* original = nullptr;
    void** slot = nullptr;
    const auto patch = [&] {
        return PatchImport(reinterpret_cast<HMODULE>(image), "d3d11.dll",
            "D3D11CreateDevice", reinterpret_cast<void*>(&Replacement), &original, &slot);
    };

    // The named thunk exists, but the loader has not snapped its IAT yet.
    slots[0].u1.AddressOfData = 0x700;
    Check(patch() == Result::Faulted, "reject unresolved RVA");
    Check(!original && !slot && slots[0].u1.AddressOfData == 0x700,
        "failed attempt must not publish a predecessor or modify the slot");
    // A full pointer to readable image data is not a function either.
    slots[0].u1.Function = reinterpret_cast<ULONG_PTR>(image + 0x700);
    Check(patch() == Result::Faulted && !original, "reject data predecessor");

    // Simulate completion; retry must preserve a callable forwarding target.
    slots[0].u1.Function = reinterpret_cast<ULONG_PTR>(&Original);
    Check(patch() == Result::Patched, "retry resolved import");
    Check(original == reinterpret_cast<void*>(&Original) &&
        slot == reinterpret_cast<void**>(&slots[0].u1.Function), "save original and slot");
    Check(patch() == Result::Patched && original == reinterpret_cast<void*>(&Original),
        "idempotent retry must not capture our own hook");
    original = nullptr;
    Check(patch() == Result::Faulted, "installed hook without predecessor is not success");

    Check(PatchImport(reinterpret_cast<HMODULE>(image), "d3d11.dll", "Absent",
        reinterpret_cast<void*>(&Replacement), &original) == Result::NotFound,
        "optional missing import remains NotFound");
    VirtualFree(image, 0, MEM_RELEASE);
    std::puts("IAT readiness / forwarding tests passed");
}
