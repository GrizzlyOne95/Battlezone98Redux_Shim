// Execute the actual registered x86 patch bytes against the stock stack slot.
// The boundary regression is a fatal range check in the game, so exercise the
// copy-length decision in isolation without loading or modifying the game.
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include "patches.h"
#include <nlohmann/json.hpp>
#include "test_check.h"
#include <algorithm>
#include <array>
#include <cstring>
#include <fstream>
#include <sstream>

using OpenShimTest::Check;
using OpenShimTest::Require;

__declspec(naked) static uint32_t __cdecl RunClamp(const void*, uint32_t)
{
    __asm {
        push ebp
        mov ebp, esp
        sub esp, 09ACh
        mov eax, [ebp + 12]
        mov [ebp - 09ACh], eax
        call dword ptr [ebp + 8]
        mov esp, ebp
        pop ebp
        ret
    }
}

int main()
{
    const auto patches = BZROpenShim::BuildPatchList();
    const auto patch = std::find_if(patches.begin(), patches.end(), [](const auto& p) {
        return p.name == "Map Description Bounds Guard";
    });
    Require(patch != patches.end(), "description guard is registered");
    Require(patch->type == HookEngine::PatchType::BYTES && patch->payload.size() == 22,
            "both clamp immediates are changed in one guarded write");
    std::ifstream input(BZR_PATCHES_JSON);
    Require(input.is_open(), "open patch configuration");
    const auto config = nlohmann::json::parse(input);
    const auto& entries = config.at("patches");
    const auto entry = std::find_if(entries.begin(), entries.end(), [](const auto& p) {
        return p.at("name") == "Map Description Bounds Guard";
    });
    Require(entry != entries.end(), "description guard has a scanned site");
    Check(entry->at("require_unique") == true && entry->at("fallback") == "0x00000000",
          "unknown and ambiguous builds cannot use a fixed address");
    Check(entry->at("offset") == 0 && entry->at("expected_size") == 22,
          "expected byte guard spans both immediates");

    std::istringstream pattern(entry->at("pattern").get<std::string>());
    std::vector<uint8_t> original;
    for (size_t i = 0; i < patch->payload.size(); ++i) {
        std::string token;
        Require(static_cast<bool>(pattern >> token) && token != "??",
                "all overwritten instruction bytes are verified");
        original.push_back(static_cast<uint8_t>(std::stoul(token, nullptr, 16)));
    }
    const auto loadAndReturn = std::array<uint8_t, 7>{0x8B, 0x85, 0x54, 0xF6, 0xFF, 0xFF, 0xC3};
    auto code = static_cast<uint8_t*>(VirtualAlloc(nullptr, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));
    Require(code != nullptr, "allocate isolated instruction buffer");
    std::memcpy(code, patch->payload.data(), patch->payload.size());
    std::memcpy(code + 22, loadAndReturn.data(), loadAndReturn.size());
    std::memcpy(code + 64, original.data(), original.size());
    std::memcpy(code + 64 + 22, loadAndReturn.data(), loadAndReturn.size());
    DWORD oldProtection = 0;
    Require(VirtualProtect(code, 4096, PAGE_EXECUTE_READ, &oldProtection) != FALSE,
            "make instruction buffer executable");
    Require(FlushInstructionCache(GetCurrentProcess(), code, 4096) != FALSE,
            "publish instruction buffer");
    // Cover the exact boundary, the crash's actual resource length, and the
    // unsigned comparison used by GetItemSize, including large high-bit sizes.
    for (const uint32_t size : {0u, 1u, 2398u, 2399u, 2400u, 2401u, 3020u, 0x80000000u, 0xFFFFFFFFu}) {
        const auto length = RunClamp(code, size);
        Check(length == std::min(size, 2399u), "patched copy length reserves the terminator");
        Check(length < 2400, "terminator index passes the stock range check");
        Check(RunClamp(code + 64, size) == std::min(size, 2400u), "original instructions reproduce unsafe limit");
        std::array<char, 2401> buffer{};
        buffer.fill('x');
        buffer[length] = '\0';
        Check(buffer[2400] == 'x', "terminator leaves the byte beyond the array untouched");
    }
    VirtualFree(code, 0, MEM_RELEASE);
    return OpenShimTest::FailureCount() == 0 ? 0 : 1;
}
