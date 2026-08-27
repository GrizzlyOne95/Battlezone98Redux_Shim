// Offline CLI Parser Test Suite
// Demonstrates stock Redux strtok comma tokenization defect vs pristine snapshot repair.

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cstdint>
#include <algorithm>

namespace
{
    void ExpectTrue(bool condition, const char* message)
    {
        if (!condition)
        {
            std::cerr << "FAIL: " << message << std::endl;
            std::exit(1);
        }
    }

    // Simulated Stock Redux parser outcome
    struct StockState
    {
        int shellmapMode = 0;       // DAT_009183d4 (1 = shellmap, 2 = largemap)
        uint32_t shellmapPacked = 0;// _DAT_009183c4 ((height << 16) | width)
        bool disableMods = false;   // DAT_00915568
        std::vector<std::string> orphanTokens;
    };

    // Simulate stock Redux parser (FUN_007d5120) with delimiter ", \t\r\n"
    StockState SimulateStockParse(const std::string& rawCmdLine)
    {
        StockState state;
        if (rawCmdLine.empty()) return state;

        std::vector<char> buf(rawCmdLine.begin(), rawCmdLine.end());
        buf.push_back('\0');

        const char* delims = ", \t\r\n";
        char* token = strtok(buf.data(), delims);

        while (token != nullptr)
        {
            if (token[0] == '/' || token[0] == '-' || token[0] == '+')
            {
                const char* opt = token + 1;
                if (strncasecmp(opt, "shellmap", 8) == 0)
                {
                    int w = 108;
                    int h = 89;
                    int res = sscanf(opt + 8, ":%d,%d", &w, &h);
                    if (res == 1)
                    {
                        h = w;
                    }
                    state.shellmapMode = 1;
                    state.shellmapPacked = (static_cast<uint32_t>(h) << 16) | static_cast<uint32_t>(w);
                }
                else if (strncasecmp(opt, "largemap", 8) == 0)
                {
                    int val = 8;
                    sscanf(opt + 8, ":%d", &val);
                    state.shellmapMode = 2;
                    state.shellmapPacked = static_cast<uint32_t>(val);
                }
                else if (strcasecmp(opt, "disablemods") == 0)
                {
                    state.disableMods = true;
                }
            }
            else
            {
                // Positional non-option token in stock
                state.orphanTokens.push_back(token);
            }
            token = strtok(nullptr, delims);
        }
        return state;
    }

    // OpenShim Pristine Snapshot Parser Repair
    struct RepairedState
    {
        int shellmapMode = 0;
        uint32_t shellmapPacked = 0;
        bool disableMods = false;
        int parsedWidth = 0;
        int parsedHeight = 0;
    };

    RepairedState ParsePristineSnapshot(const std::string& cmdLine)
    {
        RepairedState state;
        size_t i = 0;
        while (i < cmdLine.size())
        {
            while (i < cmdLine.size() && (cmdLine[i] == ' ' || cmdLine[i] == '\t' || cmdLine[i] == '\r' || cmdLine[i] == '\n'))
            {
                ++i;
            }
            if (i >= cmdLine.size()) break;

            size_t tokenStart = i;
            bool inQuotes = false;
            while (i < cmdLine.size())
            {
                char c = cmdLine[i];
                if (c == '"')
                {
                    inQuotes = !inQuotes;
                }
                else if (!inQuotes && (c == ' ' || c == '\t' || c == '\r' || c == '\n'))
                {
                    break;
                }
                ++i;
            }

            std::string token = cmdLine.substr(tokenStart, i - tokenStart);
            if (token.empty()) continue;

            if (token[0] == '/' || token[0] == '-' || token[0] == '+')
            {
                std::string opt = token.substr(1);
                // Strip quotes if present
                std::string cleanOpt;
                for (char c : opt)
                {
                    if (c != '"') cleanOpt.push_back(c);
                }

                if (strncasecmp(cleanOpt.c_str(), "shellmap", 8) == 0)
                {
                    int w = 108;
                    int h = 89;
                    const char* valPtr = cleanOpt.c_str() + 8;
                    if (*valPtr == ':' || *valPtr == '=')
                    {
                        ++valPtr;
                    }
                    int res = sscanf(valPtr, "%d,%d", &w, &h);
                    if (res == 1)
                    {
                        h = w;
                    }
                    state.shellmapMode = 1;
                    state.parsedWidth = w;
                    state.parsedHeight = h;
                    state.shellmapPacked = (static_cast<uint32_t>(h) << 16) | static_cast<uint32_t>(w);
                }
                else if (strncasecmp(cleanOpt.c_str(), "largemap", 8) == 0)
                {
                    int val = 8;
                    const char* valPtr = cleanOpt.c_str() + 8;
                    if (*valPtr == ':' || *valPtr == '=') ++valPtr;
                    sscanf(valPtr, "%d", &val);
                    state.shellmapMode = 2;
                    state.shellmapPacked = static_cast<uint32_t>(val);
                }
                else if (strcasecmp(cleanOpt.c_str(), "disablemods") == 0)
                {
                    state.disableMods = true;
                }
            }
        }
        return state;
    }
}

void TestStockParserDefect()
{
    // Case 1: Standard multi-param argument "-shellmap:216,178"
    std::string cmd = "battlezone98redux.exe -shellmap:216,178 -disablemods";
    StockState stock = SimulateStockParse(cmd);

    // Stock fails: width=216, height=216 (truncated at comma) and orphan token "178"
    ExpectTrue(stock.shellmapMode == 1, "Stock recognized shellmap");
    uint32_t stockWidth = stock.shellmapPacked & 0xFFFF;
    uint32_t stockHeight = (stock.shellmapPacked >> 16) & 0xFFFF;
    ExpectTrue(stockWidth == 216, "Stock parsed width 216");
    ExpectTrue(stockHeight == 216, "Stock DEFECT: height truncated to 216 instead of 178");
    bool hasOrphan178 = std::find(stock.orphanTokens.begin(), stock.orphanTokens.end(), "178") != stock.orphanTokens.end();
    ExpectTrue(hasOrphan178, "Stock DEFECT: '178' orphaned by comma tokenization");

    std::cout << "[PASS] TestStockParserDefect (Confirmed stock defect: -shellmap:216,178 -> W="
              << stockWidth << " H=" << stockHeight << ", orphaned token '178' detected)" << std::endl;
}

void TestPristineSnapshotRepair()
{
    // Case 1: Valid 2-value syntax
    {
        RepairedState rep = ParsePristineSnapshot("battlezone98redux.exe -shellmap:216,178 -disablemods");
        ExpectTrue(rep.shellmapMode == 1, "Mode set");
        ExpectTrue(rep.parsedWidth == 216, "Width 216");
        ExpectTrue(rep.parsedHeight == 178, "Height 178");
        ExpectTrue(rep.disableMods, "Disablemods set");
    }

    // Case 2: Reversed separator syntax (= instead of :)
    {
        RepairedState rep = ParsePristineSnapshot("battlezone98redux.exe -shellmap=216,178");
        ExpectTrue(rep.parsedWidth == 216 && rep.parsedHeight == 178, "Equals separator supported");
    }

    // Case 3: Quoted values
    {
        RepairedState rep = ParsePristineSnapshot("battlezone98redux.exe -shellmap:\"216,178\"");
        ExpectTrue(rep.parsedWidth == 216 && rep.parsedHeight == 178, "Quoted values parsed");
    }

    // Case 4: Duplicate options (last wins)
    {
        RepairedState rep = ParsePristineSnapshot("battlezone98redux.exe -shellmap:100,100 -shellmap:216,178");
        ExpectTrue(rep.parsedWidth == 216 && rep.parsedHeight == 178, "Last option wins");
    }

    // Case 5: Single parameter fallback (-shellmap:216)
    {
        RepairedState rep = ParsePristineSnapshot("battlezone98redux.exe -shellmap:216");
        ExpectTrue(rep.parsedWidth == 216 && rep.parsedHeight == 216, "Single parameter fallback height=width");
    }

    // Case 6: Control case (-largemap:16)
    {
        RepairedState rep = ParsePristineSnapshot("battlezone98redux.exe -largemap:16 -disablemods");
        ExpectTrue(rep.shellmapMode == 2, "Largemap mode set");
        ExpectTrue(rep.shellmapPacked == 16, "Largemap val 16");
        ExpectTrue(rep.disableMods, "Disablemods set");
    }

    std::cout << "[PASS] TestPristineSnapshotRepair (All pristine snapshot repair test cases passed)" << std::endl;
}

int main()
{
    std::cout << "Running CLI Parser Parity Tests..." << std::endl;
    TestStockParserDefect();
    TestPristineSnapshotRepair();
    std::cout << "All CLI parser parity tests completed successfully!" << std::endl;
    return 0;
}
