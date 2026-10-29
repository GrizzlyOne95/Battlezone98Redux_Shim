#include "direct_lan_redux_adapter.h"
#include "test_check.h"
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#include "streaming_sha256.h"
#endif

using namespace BZROpenShim::DirectLan;
namespace R = BZROpenShim::DirectLan::Redux;
namespace
{
    Id ID(uint32_t n) { Id id; for (size_t i = 0; i < 4; ++i) id.bytes[i] = uint8_t(n >> (i * 8)); return id; }
    View Snapshot()
    {
        View v; v.session = ID(1000); v.owner = ID(1); v.revision = 1; v.phase = Phase::Lobby; v.config.capacity = 4;
        v.members = {{ID(1), 0, "Host", {0x7F000001, 21000}}, {ID(2), 1, "Guest", {0x7F000001, 21001}}, {ID(3), 2, "Other", {0x7F000001, 21002}}};
        return v;
    }
    void Projection()
    {
        R::Adapter host(ID(1)), guest(ID(2)); R::Identity mine, other, owner;
        CHECK(R::DirectIdentity(*host.Local(&mine)) && !host.HasLobby());
        auto view = Snapshot(); CHECK(host.Apply(view)); CHECK(guest.Apply(view));
        CHECK(host.Members() == 3 && guest.Members() == 3 && R::Equal(host.Lobby(), guest.Lobby()));
        CHECK(R::Equal(*host.Local(&mine), *guest.Owner(&owner, guest.Lobby())));
        CHECK(R::Equal(*host.Local(&mine), *host.Owner(&owner, host.Lobby())));
        CHECK(!R::Equal(*guest.Local(&other), owner));
        const auto native = other;
        CHECK(host.Find(native) && host.Find(native)->local == ID(2) && host.Find(native)->slot == 1);
        const auto initial = mine;
        // Both clients see the same native ordering even if snapshot traversal differs.
        std::swap(view.members[1], view.members[2]); CHECK(guest.Apply(view));
        for (int32_t i = 0; i < 3; ++i) CHECK(R::Equal(*host.Member(&mine, host.Lobby(), i), *guest.Member(&other, guest.Lobby(), i)));
        auto disguised = native; disguised.discriminator = 1; CHECK(!host.Find(disguised));
        view.members.erase(std::remove_if(view.members.begin(), view.members.end(), [](const Member& m) { return m.id == ID(2); }), view.members.end());
        ++view.revision; CHECK(host.Apply(view)); CHECK(!host.Find(native));
        CHECK(R::Equal(*host.Local(&mine), initial));
        view.members.push_back({ID(2), 5, "Guest returns", {0x7F000001, 21005}}); ++view.revision;
        CHECK(host.Apply(view)); CHECK(host.Find(native) && host.Find(native)->slot == 5);
        auto padding = R::Identity{}; padding.untouched.fill(0xA5);
        CHECK(host.Member(&padding, host.Lobby(), -1) == &padding && padding.discriminator == 0 && padding.untouched[0] == 0xA5);
        CHECK(host.Member(&padding, host.Lobby(), 3) == &padding && padding.discriminator == 0);
        auto badLobby = host.Lobby(); badLobby.word8 ^= 1;
        CHECK(host.Owner(&padding, badLobby) == &padding && padding.discriminator == 0);
        const auto oldLobby = host.Lobby(); view.phase = Phase::Closed; CHECK(host.Apply(view));
        CHECK(!host.HasLobby() && !host.Find(native));
        CHECK(R::DirectIdentity(*host.Local(&mine))); // avoids invalid==invalid ownership after close
        CHECK(!R::Equal(*host.Owner(&owner, oldLobby), mine));
        view = Snapshot(); CHECK(!host.Apply(view)); host.Reset(); CHECK(host.Apply(view));
        CHECK(R::Equal(host.Lobby(), oldLobby));
        view.session = ID(1001); CHECK(!host.Apply(view) && !host.HasLobby());
        host.Reset(); CHECK(host.Apply(view));
    }
    void InvalidSnapshots()
    {
        for (int bad = 0; bad < 9; ++bad)
        {
            R::Adapter adapter(ID(1)); auto view = Snapshot(); CHECK(adapter.Apply(view));
            if (bad == 0) view.members[1].id = view.members[0].id;
            if (bad == 1) view.members[1].slot = view.members[0].slot;
            if (bad == 2) view.members[1].endpoint = view.members[0].endpoint;
            if (bad == 3) view.members[0].id = ID(9);
            if (bad == 4) view.members[1].endpoint.ipv4 = 0x08080808;
            if (bad == 5) view.members[1].endpoint.gamePort = 0;
            if (bad == 6) view.config.capacity = 2;
            if (bad == 7) view.revision = 0;
            if (bad == 8) view.members[0].slot = 1;
            CHECK(!adapter.Apply(view) && !adapter.HasLobby() && !adapter.Error().empty());
        }
        R::Adapter adapter(ID(1)); auto view = Snapshot(); view.members.resize(2);
        CHECK(adapter.Apply(view));
        for (uint32_t id = 3; id <= 256; ++id)
        { view.members[1].id = ID(id); ++view.revision; CHECK(adapter.Apply(view)); }
        view.members[1].id = ID(257); ++view.revision;
        CHECK(!adapter.Apply(view) && !adapter.HasLobby()); // bounded tombstones, no ID recycling
        adapter.Reset(); CHECK(adapter.Apply(view));
        view.phase = Phase::Running; view.launch = 1; CHECK(adapter.Apply(view));
        view.phase = Phase::Lobby; CHECK(!adapter.Apply(view));
        R::Adapter absent(ID(99)); CHECK(!absent.Apply(Snapshot()));
        R::Adapter invalid({}); CHECK(!invalid.Apply(Snapshot()));
    }
    void IdOperations()
    {
        R::Identity a{3, {}, 42, 100}, b = a, out;
        a.untouched.fill(0x11); b.untouched.fill(0x99); out.untouched.fill(0xA5);
        CHECK(R::Equal(a, b) && R::DirectIdentity(a));
        CHECK(R::Copy(&out, a) == &out && R::Equal(out, a) && out.untouched[0] == 0xA5);
        CHECK(!R::Copy(nullptr, a));
        a.discriminator = 1; CHECK(!R::Equal(a, b) && !R::DirectIdentity(a));
        a.discriminator = 3; a.word8 = a.word12 = 0; CHECK(!R::DirectIdentity(a));
    }
#if defined(_WIN32) && defined(_M_IX86)
    using LocalFn = R::Identity*(__thiscall*)(void*, R::Identity*);
    using OwnerFn = R::Identity*(__thiscall*)(void*, R::Identity*, const R::Identity*);
    using MemberFn = R::Identity*(__thiscall*)(void*, R::Identity*, const R::Identity*, int32_t);
    void NativeAbi()
    {
        static_assert(sizeof(void*) == 4);
        R::Adapter adapter(ID(1)); CHECK(adapter.Apply(Snapshot()));
        void* object = adapter.QualificationObject();
        const auto table = *static_cast<const uintptr_t**>(object);
        for (size_t i = 0; i < 32; ++i) CHECK(bool(table[i]) == (i == 0x38 / 4 || i == 0x44 / 4 || i == 0x48 / 4 || i == 0x68 / 4));
        const auto local = reinterpret_cast<LocalFn>(table[0x38 / 4]);
        const auto owner = reinterpret_cast<OwnerFn>(table[0x68 / 4]);
        const auto member = reinterpret_cast<MemberFn>(table[0x48 / 4]);
        using CountFn = uint32_t(__thiscall*)(void*, const R::Identity*);
        const auto count = reinterpret_cast<CountFn>(table[0x44 / 4]);
        R::Identity a, b, expected; const auto lobby = adapter.Lobby();
        a.untouched.fill(0x55); b.untouched.fill(0x77);
        uintptr_t before = 0, after = 0;
        for (int32_t i = 0; i < 10000; ++i)
        {
            __asm mov before, esp
            CHECK(local(object, &a) == &a);
            CHECK(owner(object, &b, &lobby) == &b && R::Equal(a, b));
            CHECK(member(object, &b, &lobby, i % 4 - 1) == &b);
            CHECK(count(object, &lobby) == 3);
            __asm mov after, esp
            CHECK(before == after);
            CHECK(R::Equal(b, *adapter.Member(&expected, lobby, i % 4 - 1)));
            CHECK(a.untouched[0] == 0x55 && b.untouched[0] == 0x77);
        }
    }
    struct ReleasedImage
    {
        uint8_t* mapped = nullptr;
        uint32_t base = 0;
        explicit ReleasedImage(const char* path)
        {
            std::ifstream file(path, std::ios::binary);
            std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(file)), {});
            BZROpenShim::Sha256 hash; hash.Update(bytes.data(), bytes.size());
            OpenShimTest::Require(hash.Finish() == "8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413", "exact released GOG image hash");
            const auto dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(bytes.data());
            const auto nt = reinterpret_cast<const IMAGE_NT_HEADERS32*>(bytes.data() + dos->e_lfanew);
            OpenShimTest::Require(nt->Signature == IMAGE_NT_SIGNATURE && nt->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC &&
                nt->OptionalHeader.SizeOfImage < 128 * 1024 * 1024, "qualified PE32 bounds");
            base = nt->OptionalHeader.ImageBase;
            mapped = static_cast<uint8_t*>(VirtualAlloc(nullptr, nt->OptionalHeader.SizeOfImage, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
            OpenShimTest::Require(mapped != nullptr, "private released-code mapping");
            std::memcpy(mapped, bytes.data(), nt->OptionalHeader.SizeOfHeaders);
            const auto sections = IMAGE_FIRST_SECTION(nt);
            for (uint16_t i = 0; i < nt->FileHeader.NumberOfSections; ++i)
            {
                const auto& s = sections[i];
                OpenShimTest::Require(size_t(s.PointerToRawData) + s.SizeOfRawData <= bytes.size() &&
                    size_t(s.VirtualAddress) + s.SizeOfRawData <= nt->OptionalHeader.SizeOfImage, "qualified PE section bounds");
                std::memcpy(mapped + s.VirtualAddress, bytes.data() + s.PointerToRawData, s.SizeOfRawData);
            }
            // Only the two owner predicates and their relative-call leaf
            // paths (kind 3 validity/equality) are invoked. They require no
            // absolute relocation, imports, provider initialization or SEH.
            DWORD previous = 0;
            OpenShimTest::Require(VirtualProtect(mapped, nt->OptionalHeader.SizeOfImage, PAGE_EXECUTE_READ, &previous) != 0,
                "released-code execute/read protection");
            FlushInstructionCache(GetCurrentProcess(), mapped, nt->OptionalHeader.SizeOfImage);
        }
        ~ReleasedImage() { if (mapped) VirtualFree(mapped, 0, MEM_RELEASE); }
        void* At(uint32_t va) const { return mapped + (va - base); }
    };
    void ReleasedOwnerPredicates(const char* exe)
    {
        ReleasedImage image(exe);
        const auto current = reinterpret_cast<bool(__thiscall*)(void*)>(image.At(0x00742CF0));
        const auto explicitLobby = reinterpret_cast<bool(__thiscall*)(void*, const R::Identity*)>(image.At(0x00742D50));
        R::Adapter host(ID(1)), guest(ID(2)); const auto view = Snapshot();
        CHECK(host.Apply(view) && guest.Apply(view));
        auto lobby = host.Lobby();
        for (int i = 0; i < 1000; ++i)
        {
            CHECK(current(host.QualificationObject())); CHECK(!current(guest.QualificationObject()));
            CHECK(explicitLobby(host.QualificationObject(), &lobby)); CHECK(!explicitLobby(guest.QualificationObject(), &lobby));
        }
        auto wrong = lobby; wrong.word8 ^= 1;
        CHECK(!explicitLobby(host.QualificationObject(), &wrong));
        host.Reset(); CHECK(!current(host.QualificationObject()));
        CHECK(!explicitLobby(host.QualificationObject(), &lobby));
        std::puts("Released GOG owner predicates executed against compiled query adapter; no game/provider initialization");
    }
#endif
    int OracleInput()
    {
        uint32_t count = 0; std::string line;
        while (std::getline(std::cin, line))
        {
            std::istringstream in(line); R::Identity a, b, expected, out; uint32_t equal = 0, direct = 0, less = 0;
            uint32_t paddingA = 0, paddingB = 0;
            OpenShimTest::Require(bool(in >> a.discriminator >> paddingA >> a.word8 >> a.word12 >>
                b.discriminator >> paddingB >> b.word8 >> b.word12 >> equal >> direct >> less), "oracle input row");
            std::memcpy(a.untouched.data(), &paddingA, 4); std::memcpy(b.untouched.data(), &paddingB, 4);
            out.untouched.fill(0xA5); expected = a; expected.untouched.fill(0xA5);
            CHECK(R::Copy(&out, a) == &out && !std::memcmp(&out, &expected, sizeof(out)));
            CHECK(R::Equal(a, b) == bool(equal)); CHECK(R::DirectIdentity(a) == bool(direct));
            CHECK(R::Less(a, b) == bool(less));
            OpenShimTest::Require(++count <= 20000, "bounded oracle input");
        }
        CHECK(count > 0); return OpenShimTest::ExitCode();
    }
}
int main(int argc, char** argv)
{
    if (argc == 2 && std::string(argv[1]) == "--identity-oracle") return OracleInput();
    IdOperations(); Projection(); InvalidSnapshots();
#if defined(_WIN32) && defined(_M_IX86)
    NativeAbi();
    if (argc == 3 && std::string(argv[1]) == "--released-exe") ReleasedOwnerPredicates(argv[2]);
    else if (argc != 1) return 2;
#else
    (void)argc; (void)argv;
#endif
    std::printf("direct_lan_redux_adapter_tests: %d checks\n", OpenShimTest::CheckCount());
    return OpenShimTest::ExitCode();
}
