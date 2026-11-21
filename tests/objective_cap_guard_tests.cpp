#include "objective_cap_guard.h"

#include <cstdint>
#include <cstdio>
#include <cstring>
#include "test_check.h"

namespace
{
    using namespace BZROpenShim::ObjectiveCap;

    // Fake objective list with the engine's Remove semantics: first
    // case-insensitive 16-char name match, count--, tail moved down.
    struct FakeList
    {
        char names[kCapacity + 4][kNameLength] = {};
        int32_t count = 0;
        bool countReadable = true;
        bool nameReadable = true;
        bool removeWorks = true;
        int adds = 0;
        int removes = 0;
        int drops = 0;
        int rejects = 0;
        char lastRemoved[kNameLength] = {};
        char lastDropped[kNameLength] = {};
    };
    FakeList g;

    // Bounded copy that always terminates (strncpy trips /W4 /WX on MSVC).
    void CopyName(char (&dst)[kNameLength], const char* src)
    {
        uint32_t i = 0;
        for (; i + 1 < kNameLength && src[i] != '\0'; ++i)
            dst[i] = src[i];
        for (; i < kNameLength; ++i)
            dst[i] = '\0';
    }

    bool ReadCount(void*, int32_t& count)
    {
        count = g.countReadable ? g.count : 0;
        return g.countReadable;
    }
    bool ReadOldestName(void*, char (&out)[kNameLength])
    {
        if (!g.nameReadable)
            return false;
        // Deliberately unterminated copy: the guard must terminate it.
        std::memcpy(out, g.names[0], kNameLength);
        return true;
    }
    void Remove(void*, const char* name)
    {
        ++g.removes;
        CopyName(g.lastRemoved, name);
        if (!g.removeWorks)
            return;
        for (int32_t i = 0; i < g.count; ++i)
        {
            if (std::strncmp(g.names[i], name, kNameLength) == 0)
            {
                for (int32_t j = i; j + 1 < g.count; ++j)
                    std::memcpy(g.names[j], g.names[j + 1], kNameLength);
                --g.count;
                std::memset(g.names[g.count], 0, kNameLength);
                return;
            }
        }
    }
    void Add(void*, const char* name, uint32_t, float, const char*)
    {
        ++g.adds;
        CHECK(g.count >= 0 && g.count < kCapacity);
        CopyName(g.names[g.count], name);
        ++g.count;
    }
    void OnDrop(const char* dropped, const char*)
    {
        ++g.drops;
        CopyName(g.lastDropped, dropped);
    }
    void OnReject(int32_t, const char*, const char*) { ++g.rejects; }

    const Engine kEngine = { ReadCount, ReadOldestName, Remove, Add, OnDrop, OnReject };

    void Fill(int32_t n)
    {
        g = FakeList();
        for (int32_t i = 0; i < n; ++i)
            std::snprintf(g.names[i], kNameLength, "obj%d.otf", static_cast<int>(i % 100));
        g.count = n;
    }

    void TestDecide()
    {
        CHECK(Decide(0) == Action::Add);
        CHECK(Decide(9) == Action::Add);
        CHECK(Decide(10) == Action::DropOldestThenAdd);
        CHECK(Decide(11) == Action::Reject);
        CHECK(Decide(-1) == Action::Reject);
        CHECK(Decide(0x7FFFFFFF) == Action::Reject);
    }

    void TestRoomLeftAddsStock()
    {
        Fill(9);
        CHECK(Run(kEngine, nullptr, "new.otf", 0, 0.0f, nullptr) == Action::Add);
        CHECK(g.adds == 1);
        CHECK(g.removes == 0);
        CHECK(g.count == 10);
        CHECK(g.drops == 0 && g.rejects == 0);
    }

    void TestFullDropsOldestThenAdds()
    {
        Fill(10);
        CHECK(Run(kEngine, nullptr, "new.otf", 0, 0.0f, nullptr) == Action::DropOldestThenAdd);
        CHECK(g.removes == 1);
        CHECK(std::strcmp(g.lastRemoved, "obj0.otf") == 0);
        CHECK(g.adds == 1);
        CHECK(g.count == 10);
        CHECK(std::strcmp(g.names[0], "obj1.otf") == 0);
        CHECK(std::strcmp(g.names[9], "new.otf") == 0);
        CHECK(g.drops == 1);
        CHECK(std::strcmp(g.lastDropped, "obj0.otf") == 0);

        // Many adds in a row keep the list at capacity.
        for (int i = 0; i < 25; ++i)
            Run(kEngine, nullptr, "more.otf", 0, 0.0f, nullptr);
        CHECK(g.count == 10);
    }

    void TestFullNameIsTerminated()
    {
        Fill(10);
        std::memset(g.names[0], 'A', kNameLength);  // all 16 bytes non-NUL
        CHECK(Run(kEngine, nullptr, "new.otf", 0, 0.0f, nullptr) == Action::DropOldestThenAdd);
        CHECK(std::strlen(g.lastRemoved) == kNameLength - 1);
    }

    void TestCorruptCountRejects()
    {
        const int32_t bad[] = { -1, 11, 200 };
        for (int32_t c : bad)
        {
            Fill(0);
            g.count = c;
            CHECK(Run(kEngine, nullptr, "new.otf", 0, 0.0f, nullptr) == Action::Reject);
            CHECK(g.adds == 0);
            CHECK(g.removes == 0);
            CHECK(g.rejects == 1);
        }
    }

    void TestUnreadableRejects()
    {
        Fill(5);
        g.countReadable = false;
        CHECK(Run(kEngine, nullptr, "new.otf", 0, 0.0f, nullptr) == Action::Reject);
        CHECK(g.adds == 0 && g.rejects == 1);

        Fill(10);
        g.nameReadable = false;
        CHECK(Run(kEngine, nullptr, "new.otf", 0, 0.0f, nullptr) == Action::Reject);
        CHECK(g.adds == 0 && g.removes == 0 && g.rejects == 1);
    }

    void TestDropThatMakesNoRoomRejects()
    {
        Fill(10);
        g.removeWorks = false;
        CHECK(Run(kEngine, nullptr, "new.otf", 0, 0.0f, nullptr) == Action::Reject);
        CHECK(g.removes == 1);
        CHECK(g.adds == 0);
        CHECK(g.drops == 0 && g.rejects == 1);
    }

    void TestNullHooksTolerated()
    {
        const Engine quiet = { ReadCount, ReadOldestName, Remove, Add, nullptr, nullptr };
        Fill(10);
        CHECK(Run(quiet, nullptr, "new.otf", 0, 0.0f, nullptr) == Action::DropOldestThenAdd);
        Fill(0);
        g.count = 11;
        CHECK(Run(quiet, nullptr, "new.otf", 0, 0.0f, nullptr) == Action::Reject);
    }
}

int main()
{
    TestDecide();
    TestRoomLeftAddsStock();
    TestFullDropsOldestThenAdds();
    TestFullNameIsTerminated();
    TestCorruptCountRejects();
    TestUnreadableRejects();
    TestDropThatMakesNoRoomRejects();
    TestNullHooksTolerated();
    return OpenShimTest::ExitCode();
}
