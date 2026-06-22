#include "hook_engine.h"
#include "shim_log.h"
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <algorithm>
#include <sstream>

namespace HookEngine
{

    std::vector<uint16_t> ParseIdaPattern(const std::string& hex)
    {
        std::vector<uint16_t> pattern;
        std::stringstream ss(hex);
        std::string item;
        while (ss >> item)
        {
            if (item == "?" || item == "??")
                pattern.push_back(0x100); // Wildcard
            else
                pattern.push_back(static_cast<uint16_t>(std::stoul(item, nullptr, 16)));
        }
        return pattern;
    }

    std::vector<uint8_t> ParseHexPattern(const std::string& hex)
    {
        std::vector<uint8_t> bytes;
        std::stringstream ss(hex);
        std::string item;
        while (ss >> item)
        {
            bytes.push_back(static_cast<uint8_t>(std::stoul(item, nullptr, 16)));
        }
        return bytes;
    }

    bool ReadMemory(uint32_t address, void* buffer, size_t len)
    {
        SIZE_T read = 0;
        return ReadProcessMemory(GetCurrentProcess(), reinterpret_cast<LPCVOID>(address), buffer, len, &read) && read == len;
    }

    bool WriteMemory(uint32_t address, const void* data, size_t len)
    {
        HANDLE hProc = GetCurrentProcess();
        DWORD oldProtect = 0;
        void* ptr = reinterpret_cast<void*>(address);

        if (!VirtualProtect(ptr, len, PAGE_EXECUTE_READWRITE, &oldProtect))
            return false;

        SIZE_T written = 0;
        BOOL ok = WriteProcessMemory(hProc, ptr, data, len, &written);

        VirtualProtect(ptr, len, oldProtect, &oldProtect);
        return ok && written == len;
    }

    bool ApplyPatch(const PatchDef& patch)
    {
        if (patch.address == 0) return false;

        if (!patch.expected_original.empty())
        {
            std::vector<uint8_t> current(patch.expected_original.size());
            if (!ReadMemory(patch.address, current.data(), current.size())) return false;
            if (memcmp(current.data(), patch.expected_original.data(), current.size()) != 0) return false;
        }

        return WriteMemory(patch.address, patch.payload.data(), patch.payload.size());
    }

    void* ResolveRelCallTarget(uint32_t instrAddr)
    {
        uint8_t op;
        if (!ReadMemory(instrAddr, &op, 1) || op != 0xE8) return nullptr;

        int32_t rel = 0;
        if (!ReadMemory(instrAddr + 1, &rel, 4)) return nullptr;

        return reinterpret_cast<void*>(instrAddr + 5 + rel);
    }

    std::vector<uint8_t> MakeJmp5Payload(uint32_t src, uint32_t dst, size_t total_len)
    {
        int32_t rel = static_cast<int32_t>(dst) - static_cast<int32_t>(src + 5);
        std::vector<uint8_t> buf(total_len, 0x90);
        buf[0] = 0xE9;
        memcpy(&buf[1], &rel, 4);
        return buf;
    }


    void* ResolveRelCallTargetWithRetry(uint32_t instrAddr, int maxAttempts, uint32_t delayMs)
    {
        for (int attempt = 0; attempt < maxAttempts; ++attempt)
        {
            if (void* target = ResolveRelCallTarget(instrAddr))
            {
                return target;
            }
            if (attempt + 1 < maxAttempts)
                Sleep(delayMs);
        }
        return nullptr;
    }


    void ScanForPatterns(const std::string& moduleName, std::vector<PatchDef>& patches, const std::vector<ScanTarget>& targets)
    {
        HMODULE hMod = GetModuleHandleA(moduleName.empty() ? nullptr : moduleName.c_str());
        if (!hMod) return;

        MODULEINFO mi;
        if (!GetModuleInformation(GetCurrentProcess(), hMod, &mi, sizeof(mi))) return;

        uint8_t* base = reinterpret_cast<uint8_t*>(mi.lpBaseOfDll);
        size_t size = mi.SizeOfImage;
        uint8_t* end = base + size;

        HANDLE hProc = GetCurrentProcess();
        MEMORY_BASIC_INFORMATION mbi = {};
        uint8_t* addr = base;

        // Collect executable regions
        std::vector<std::pair<uint8_t*, size_t>> regions;
        while (addr < end && VirtualQuery(addr, &mbi, sizeof(mbi)) == sizeof(mbi))
        {
            uint8_t* rBase = reinterpret_cast<uint8_t*>(mbi.BaseAddress);
            uint8_t* rEnd = rBase + mbi.RegionSize;
            if (rEnd <= base || rBase >= end)
            {
                addr = rEnd;
                continue;
            }
            uint8_t* clipStart = (rBase < base) ? base : rBase;
            uint8_t* clipEnd = (rEnd > end) ? end : rEnd;
            size_t clipSize = static_cast<size_t>(clipEnd - clipStart);

            if (clipSize > 0 && mbi.State == MEM_COMMIT &&
                (mbi.Protect & (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)))
            {
                regions.push_back({ clipStart, clipSize });
            }
            addr = rEnd;
        }

        for (const auto& target : targets)
        {
            auto idaPattern = ParseIdaPattern(target.ida_pattern);
            if (idaPattern.empty()) continue;

            bool found = false;
            for (const auto& region : regions)
            {
                std::vector<uint8_t> buf(region.second);
                SIZE_T read = 0;
                if (!ReadProcessMemory(hProc, region.first, buf.data(), region.second, &read) || read == 0)
                    continue;
                if (read < idaPattern.size())
                    continue;

                for (size_t i = 0; i <= read - idaPattern.size(); i++)
                {
                    bool match = true;
                    for (size_t j = 0; j < idaPattern.size(); j++)
                    {
                        if (idaPattern[j] < 0x100 && buf[i + j] != static_cast<uint8_t>(idaPattern[j]))
                        {
                            match = false;
                            break;
                        }
                    }

                    if (match)
                    {
                        uint32_t patchAddr = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(region.first + i + target.offset));

                        for (auto& p : patches)
                        {
                            if (p.name == target.name)
                            {
                                p.address = patchAddr;
                                p.verified = true;
                                p.expected_original.clear();
                                for (size_t j = 0; j < target.expected_size && (i + target.offset + j) < read; ++j)
                                    p.expected_original.push_back(buf[i + target.offset + j]);

                                found = true;
                                break;
                            }
                        }
                        break;
                    }
                }
                if (found) break;
            }
        }
    }

}
