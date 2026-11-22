#include "handle_sequence_check.h"

#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include "test_check.h"

namespace
{
    using namespace BZROpenShim::HandleSequence;

    void TestConstants()
    {
        CHECK(kExhaustedAt == 0x100000u);
        CHECK(kWarnAt == 943718u);
    }

    void TestClassify()
    {
        CHECK(Classify(0) == Level::Normal);
        CHECK(Classify(1) == Level::Normal);
        CHECK(Classify(kWarnAt - 1) == Level::Normal);
        CHECK(Classify(kWarnAt) == Level::Warn);
        CHECK(Classify(kExhaustedAt - 1) == Level::Warn);
        CHECK(Classify(kExhaustedAt) == Level::Exhausted);
        CHECK(Classify(0xFFFFFFFFu) == Level::Exhausted);
    }

    void TestPercentAndRemaining()
    {
        CHECK(PercentUsed(0) == 0);
        CHECK(PercentUsed(kWarnAt) == 90);
        CHECK(PercentUsed(kExhaustedAt - 1) == 99);
        CHECK(PercentUsed(kExhaustedAt) == 100);
        CHECK(PercentUsed(0xFFFFFFFFu) == 100);
        CHECK(Remaining(1) == kExhaustedAt - 1);
        CHECK(Remaining(kExhaustedAt - 1) == 1);
        CHECK(Remaining(kExhaustedAt) == 0);
        CHECK(Remaining(0xFFFFFFFFu) == 0);
    }

    void TestSteadyClimbReportsEachCrossingOnce()
    {
        Tracker t;
        CHECK(Observe(t, 1) == Event::None);
        CHECK(Observe(t, 500000) == Event::None);
        CHECK(Observe(t, kWarnAt - 1) == Event::None);
        CHECK(Observe(t, kWarnAt) == Event::Warn);
        CHECK(Observe(t, kWarnAt + 1) == Event::None);
        CHECK(Observe(t, kExhaustedAt - 1) == Event::None);
        CHECK(Observe(t, kExhaustedAt) == Event::Exhausted);
        CHECK(Observe(t, kExhaustedAt + 5000) == Event::None);
        CHECK(t.level == Level::Exhausted);
    }

    void TestJumpStraightToExhausted()
    {
        Tracker t;
        CHECK(Observe(t, 10) == Event::None);
        CHECK(Observe(t, kExhaustedAt + 1) == Event::Exhausted);
    }

    void TestFirstReadingAboveThreshold()
    {
        Tracker warn;
        CHECK(Observe(warn, kWarnAt + 10) == Event::Warn);
        Tracker gone;
        CHECK(Observe(gone, kExhaustedAt) == Event::Exhausted);
        Tracker fresh;
        CHECK(Observe(fresh, 1) == Event::None);
    }

    void TestLowerCounterRearms()
    {
        Tracker t;
        CHECK(Observe(t, kExhaustedAt) == Event::Exhausted);
        // A save with a lower seq_count is loaded.
        CHECK(Observe(t, kWarnAt + 3) == Event::Rearmed);
        CHECK(Observe(t, kExhaustedAt) == Event::Exhausted);
        CHECK(Observe(t, 2) == Event::Rearmed);
        CHECK(Observe(t, 3) == Event::None);
        CHECK(Observe(t, kWarnAt) == Event::Warn);
        // A drop that stays inside the same level is silent.
        CHECK(Observe(t, kWarnAt + 100) == Event::None);
        CHECK(Observe(t, kWarnAt + 1) == Event::None);
    }

    // Returns the string value of `key` in the engine_addresses row `name`,
    // or "" when absent. Text search is enough for the shipped file's layout.
    std::string RowField(const std::string& json, const std::string& name, const std::string& key)
    {
        const std::string tag = "\"name\": \"" + name + "\"";
        const size_t row = json.find(tag);
        if (row == std::string::npos)
            return "";
        const size_t end = json.find('}', row);
        const std::string field = "\"" + key + "\": \"";
        const size_t at = json.find(field, row);
        if (at == std::string::npos || at > end)
            return "";
        const size_t start = at + field.size();
        const size_t close = json.find('"', start);
        return close == std::string::npos ? "" : json.substr(start, close - start);
    }

    std::vector<uint32_t> ParseHexBytes(const std::string& text)
    {
        std::vector<uint32_t> bytes;
        size_t i = 0;
        while (i < text.size())
        {
            if (text[i] == ' ')
            {
                ++i;
                continue;
            }
            bytes.push_back(static_cast<uint32_t>(std::strtoul(text.substr(i, 2).c_str(), nullptr, 16)));
            i += 2;
        }
        return bytes;
    }

    // The install reads the counter operands at kCtorOperandOffsets inside the
    // GameObjectCtorSequenceAssign row; they must be the little-endian address
    // of GameObjectSequenceCounter in the row's own guard bytes.
    void TestCtorOperandOffsetsMatchPatchesJson()
    {
        std::ifstream file(BZR_PATCHES_JSON, std::ios::binary);
        CHECK(file.is_open());
        if (!file.is_open())
            return;
        const std::string json((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        const std::vector<uint32_t> bytes = ParseHexBytes(RowField(json, "GameObjectCtorSequenceAssign", "expected"));
        const std::string counterText = RowField(json, "GameObjectSequenceCounter", "address");
        CHECK(!counterText.empty());
        const uint32_t counter = static_cast<uint32_t>(std::strtoul(counterText.c_str(), nullptr, 16));
        CHECK(counter == 0x008E8660u);
        for (uint32_t offset : kCtorOperandOffsets)
        {
            CHECK(offset + 4u <= bytes.size());
            if (offset + 4u > bytes.size())
                continue;
            const uint32_t operand = bytes[offset] | (bytes[offset + 1] << 8) | (bytes[offset + 2] << 16) |
                                     (bytes[offset + 3] << 24);
            CHECK(operand == counter);
        }
    }
}

int main()
{
    TestConstants();
    TestClassify();
    TestPercentAndRemaining();
    TestSteadyClimbReportsEachCrossingOnce();
    TestJumpStraightToExhausted();
    TestFirstReadingAboveThreshold();
    TestLowerCounterRearms();
    TestCtorOperandOffsetsMatchPatchesJson();
    return OpenShimTest::ExitCode();
}
