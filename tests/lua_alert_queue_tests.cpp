// Unit tests for the deferred Lua callback alert queue (include/lua_alert_queue.h).
#include "lua_alert_queue.h"

#include <cstdlib>
#include <iostream>
#include <string>

using namespace BZROpenShim::LuaAlertQueue;

namespace
{
    void Check(bool ok, const char* what)
    {
        if (!ok)
        {
            std::cerr << "lua_alert_queue_tests failure: " << what << "\n";
            std::exit(1);
        }
    }

    const char kDelete[] = "Lua script DeleteObject error:\n%s";
    const char kUpdate[] = "Lua script Update error:\n%s";
}

int main()
{
    Queue q;
    Check(q.Empty(), "starts empty");

    // Duplicates collapse; the same text from another callback does not.
    Check(q.Push(kDelete, "map.lua:15: boom") == PushResult::Added, "first add");
    Check(q.Push(kDelete, "map.lua:15: boom") == PushResult::Merged, "duplicate merges");
    Check(q.Push(kDelete, "map.lua:15: boom") == PushResult::Merged, "third merges");
    Check(q.Push(kUpdate, "map.lua:15: boom") == PushResult::Added, "other format is distinct");
    Check(q.Push(kDelete, "map.lua:16: other") == PushResult::Added, "other message is distinct");
    Check(q.Size() == 3 && !q.Empty(), "three entries");

    // A non-string error object reads as NULL; stock prints "(null)".
    Check(q.Push(kDelete, nullptr) == PushResult::Added, "null message");
    Check(q.Push(kDelete, "(null)") == PushResult::Merged, "null equals (null)");

    // Full: new distinct errors are counted, duplicates of queued ones still merge.
    Check(q.Size() == Queue::kMaxEntries, "queue full");
    Check(q.Push(kUpdate, "new") == PushResult::Dropped, "overflow drops");
    Check(q.Push(kUpdate, "newer") == PushResult::Dropped, "overflow drops again");
    Check(q.Push(kUpdate, "map.lua:15: boom") == PushResult::Merged, "merge when full");
    Check(q.Dropped() == 2, "dropped count");

    uint32_t dropped = 0;
    auto entries = q.Drain(&dropped);
    Check(dropped == 2, "drain reports dropped");
    Check(q.Empty() && q.Size() == 0 && q.Dropped() == 0, "drain empties");
    Check(entries.size() == 4, "four drained");
    Check(entries[0].format == kDelete && entries[0].count == 3, "arrival order, count");
    Check(entries[1].format == kUpdate && entries[1].count == 2, "second entry count");
    Check(entries[3].message == "(null)", "null text");

    Check(DisplayMessage(entries[0]) == "map.lua:15: boom\n(repeated 3 times this frame)", "repeat note");
    Check(DisplayMessage(entries[2]) == "map.lua:16: other", "no note for one");

    // Drain resets the cap, so the next frame can queue again.
    Queue refill;
    for (size_t i = 0; i < Queue::kMaxEntries + 1; ++i)
        refill.Push(kDelete, std::to_string(i).c_str());
    Check(refill.Dropped() == 1 && !refill.Empty(), "fills then drops");
    refill.Drain();
    Check(refill.Empty(), "empty after drain");
    Check(refill.Push(kDelete, "again") == PushResult::Added, "reusable after drain");

    // Long messages are cut so the engine's 1024-byte format buffer never truncates.
    const std::string longText(5000, 'x');
    Queue cut;
    cut.Push(kDelete, longText.c_str());
    Check(cut.Push(kDelete, std::string(Queue::kMaxMessageChars, 'x').c_str()) == PushResult::Merged,
          "truncated text merges with its prefix");
    auto cutEntries = cut.Drain();
    Check(cutEntries.size() == 1 && cutEntries[0].message.size() == Queue::kMaxMessageChars, "truncated");
    Entry big = cutEntries[0];
    big.count = UINT32_MAX;
    const std::string shown = DisplayMessage(big) + "Lua script CreatePlayer error:\n\n";
    Check(shown.size() < 1023, "fits the engine buffer");

    // A multibyte character straddling the limit is dropped whole.
    std::string utf8(Queue::kMaxMessageChars - 1, 'a');
    utf8 += "\xC3\xA9tail";
    Queue u;
    u.Push(kDelete, utf8.c_str());
    auto uEntries = u.Drain();
    Check(uEntries[0].message == std::string(Queue::kMaxMessageChars - 1, 'a'), "utf-8 safe cut");

    std::cout << "lua_alert_queue_tests passed\n";
    return 0;
}
