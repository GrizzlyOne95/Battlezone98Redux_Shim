#include "live_reticle_team.h"
#include "test_check.h"
#include <array>
#include <cstring>

using OpenShimTest::Require;
using BZROpenShim::Reticle::ReadLiveActualTeam;
int main()
{
    alignas(void*) std::array<uint8_t, 0x200> object{};
    void* vtable[2] = {nullptr, reinterpret_cast<void*>(uintptr_t{0x12345678})};
    auto* table = vtable;
    std::memcpy(object.data() + 0x18, &table, sizeof(table));
    constexpr uintptr_t expected = 0x12345678;
    for (int actual : {0, 1, 2, 15, -1})
    {
        std::memcpy(object.data() + BZROpenShim::ObjectLayout::kGameObjectActualTeam, &actual, sizeof(actual));
        Require(ReadLiveActualTeam(object.data(), expected) == actual, "actual team, including neutral and unknown");
    }
    int perceived = 0;
    std::memcpy(object.data() + BZROpenShim::ObjectLayout::kGameObjectPerceivedTeam, &perceived, sizeof(perceived));
    Require(ReadLiveActualTeam(object.data(), expected) == -1, "perceived team must not replace actual team");
    vtable[1] = nullptr;
    Require(ReadLiveActualTeam(object.data(), expected) == INT_MIN, "foreign vtable rejected");
    Require(ReadLiveActualTeam(nullptr, expected) == INT_MIN, "null rejected");
    Require(ReadLiveActualTeam(object.data()+1, expected) == INT_MIN, "misaligned pointer rejected");
    Require(ReadLiveActualTeam(object.data(), 0) == INT_MIN, "missing build identity rejected");
    auto* inaccessible = VirtualAlloc(nullptr, 4096, MEM_RESERVE | MEM_COMMIT, PAGE_NOACCESS);
    Require(inaccessible != nullptr, "allocate inaccessible page");
    Require(ReadLiveActualTeam(inaccessible, expected) == INT_MIN, "unreadable object fails safely");
    VirtualFree(inaccessible, 0, MEM_RELEASE);
    table = reinterpret_cast<void**>(uintptr_t{0x10000});
    std::memcpy(object.data()+0x18, &table, sizeof(table));
    Require(ReadLiveActualTeam(object.data(), expected) == INT_MIN, "unreadable table fails safely");
    return 0;
}
