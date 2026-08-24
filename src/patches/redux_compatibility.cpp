// redux_compatibility.cpp

#include "redux_compatibility.h"

#include "numeric_locale_compat.h"
#include "patcher.h"
#include "trn_codec.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <bcrypt.h>

#include <array>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iterator>
#include <limits>
#include <sstream>

namespace BZROpenShim
{
    namespace
    {
        constexpr char kLocalePatchName[] = "Redux Numeric Locale Compatibility Call";
        constexpr char kTrnModePatchName[] = "Redux TRN Binary Writer Mode";
        constexpr char kTrnWritePatchName[] = "Redux TRN Canonical Fwrite Hook";
        constexpr char kGogSha256[] = "8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413";
        constexpr char kSteamSha256[] = "D298782FC9A13EDB0665DB934110440C45461031DB5F7FE1A76C8784B61CC90D";

        using LanguageInitializer = int (__cdecl*)();
        using ReduxFwrite = size_t (__cdecl*)(const void*, size_t, size_t, void*);

        LanguageInitializer g_OriginalLanguageInitializer = nullptr;
        SetLocaleFunction g_ReduxSetLocale = nullptr;
        ReduxFwrite g_ReduxFwrite = nullptr;
        char g_TrnBinaryMode[] = "wb";

        bool ComputeSha256(const wchar_t* path, std::string& output, uint64_t& fileSize)
        {
            output.clear();
            fileSize = 0;
            HMODULE bcrypt = LoadLibraryW(L"bcrypt.dll");
            if (!bcrypt)
                return false;

            const auto openProvider = reinterpret_cast<decltype(&BCryptOpenAlgorithmProvider)>(
                GetProcAddress(bcrypt, "BCryptOpenAlgorithmProvider"));
            const auto getProperty = reinterpret_cast<decltype(&BCryptGetProperty)>(
                GetProcAddress(bcrypt, "BCryptGetProperty"));
            const auto createHash = reinterpret_cast<decltype(&BCryptCreateHash)>(
                GetProcAddress(bcrypt, "BCryptCreateHash"));
            const auto hashData = reinterpret_cast<decltype(&BCryptHashData)>(
                GetProcAddress(bcrypt, "BCryptHashData"));
            const auto finishHash = reinterpret_cast<decltype(&BCryptFinishHash)>(
                GetProcAddress(bcrypt, "BCryptFinishHash"));
            const auto destroyHash = reinterpret_cast<decltype(&BCryptDestroyHash)>(
                GetProcAddress(bcrypt, "BCryptDestroyHash"));
            const auto closeProvider = reinterpret_cast<decltype(&BCryptCloseAlgorithmProvider)>(
                GetProcAddress(bcrypt, "BCryptCloseAlgorithmProvider"));
            if (!openProvider || !getProperty || !createHash || !hashData || !finishHash ||
                !destroyHash || !closeProvider)
            {
                FreeLibrary(bcrypt);
                return false;
            }

            BCRYPT_ALG_HANDLE algorithm = nullptr;
            BCRYPT_HASH_HANDLE hash = nullptr;
            HANDLE file = INVALID_HANDLE_VALUE;
            bool success = false;
            do
            {
                if (openProvider(&algorithm, BCRYPT_SHA256_ALGORITHM, nullptr, 0) < 0)
                    break;
                DWORD objectSize = 0;
                DWORD hashSize = 0;
                DWORD resultSize = 0;
                if (getProperty(algorithm, BCRYPT_OBJECT_LENGTH,
                        reinterpret_cast<PUCHAR>(&objectSize), sizeof(objectSize), &resultSize, 0) < 0 ||
                    getProperty(algorithm, BCRYPT_HASH_LENGTH,
                        reinterpret_cast<PUCHAR>(&hashSize), sizeof(hashSize), &resultSize, 0) < 0 ||
                    hashSize != 32)
                {
                    break;
                }

                std::vector<uint8_t> object(objectSize);
                std::array<uint8_t, 32> digest = {};
                if (createHash(algorithm, &hash, object.data(), objectSize, nullptr, 0, 0) < 0)
                    break;

                file = CreateFileW(path, GENERIC_READ,
                    FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                    nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
                if (file == INVALID_HANDLE_VALUE)
                    break;
                LARGE_INTEGER size = {};
                if (!GetFileSizeEx(file, &size) || size.QuadPart < 0)
                    break;
                fileSize = static_cast<uint64_t>(size.QuadPart);

                std::array<uint8_t, 64 * 1024> buffer = {};
                for (;;)
                {
                    DWORD read = 0;
                    if (!ReadFile(file, buffer.data(), static_cast<DWORD>(buffer.size()), &read, nullptr))
                        break;
                    if (read == 0)
                    {
                        if (finishHash(hash, digest.data(), hashSize, 0) < 0)
                            break;
                        std::ostringstream text;
                        text << std::uppercase << std::hex << std::setfill('0');
                        for (const uint8_t byte : digest)
                            text << std::setw(2) << static_cast<unsigned>(byte);
                        output = text.str();
                        success = true;
                        break;
                    }
                    if (hashData(hash, buffer.data(), read, 0) < 0)
                        break;
                }
            } while (false);

            if (file != INVALID_HANDLE_VALUE)
                CloseHandle(file);
            if (hash)
                destroyHash(hash);
            if (algorithm)
                closeProvider(algorithm, 0);
            FreeLibrary(bcrypt);
            return success;
        }

        bool BytesEqual(uint32_t address, const uint8_t* expected, size_t size)
        {
            std::vector<uint8_t> current(size);
            return HookEngine::ReadMemory(address, current.data(), current.size()) &&
                std::memcmp(current.data(), expected, size) == 0;
        }

        bool WaitForSettledCompatibilityBytes(uint32_t moduleBase, bool steam)
        {
            static constexpr uint8_t kLocaleContext[] = {
                0x00, 0x83, 0xC4, 0x04, 0xE8, 0x7F, 0x80, 0x20, 0x00, 0xE8,
                0xBA, 0x50, 0x20, 0x00, 0xE8, 0x95, 0x22, 0x07, 0x00, 0x68,
                0x18, 0x3C, 0x87, 0x00,
            };
            static constexpr uint8_t kTrnWriterContext[] = {
                0x68, 0x5C, 0x67, 0x87, 0x00, 0x8D, 0x85, 0x7C, 0xEF, 0xFF,
                0xFF, 0x50, 0xFF, 0x15, 0xE0, 0x94, 0x86, 0x00, 0x83, 0xC4,
                0x08, 0x89, 0x85, 0x70, 0xDF, 0xFF, 0xFF, 0x83, 0xBD, 0x70,
                0xDF, 0xFF, 0xFF, 0x00, 0x74, 0x4E, 0x8B, 0x8D, 0x70, 0xDF,
                0xFF, 0xFF, 0x51, 0x8B, 0x95, 0x3C, 0xDF, 0xFF, 0xFF, 0x52,
                0x6A, 0x01, 0x8B, 0x85, 0x44, 0xDF, 0xFF, 0xFF, 0x50, 0xFF,
                0x15, 0x84, 0x94, 0x86, 0x00,
            };

            const uint32_t localeAddress = moduleBase + 0x00218E38u;
            const uint32_t trnAddress = moduleBase + 0x00386E5Fu;
            const int attempts = steam ? 3000 : 1;
            for (int attempt = 0; attempt < attempts; ++attempt)
            {
                if (BytesEqual(localeAddress, kLocaleContext, sizeof(kLocaleContext)) &&
                    BytesEqual(trnAddress, kTrnWriterContext, sizeof(kTrnWriterContext)))
                {
                    return true;
                }
                if (attempt + 1 < attempts)
                    Sleep(10);
            }
            return false;
        }

        HookEngine::PatchDef* FindPatch(std::vector<HookEngine::PatchDef>& patches, const char* name)
        {
            for (auto& patch : patches)
            {
                if (patch.name == name)
                    return &patch;
            }
            return nullptr;
        }

        bool PatchHasExpectedBytes(const HookEngine::PatchDef* patch, const uint8_t* expected, size_t size)
        {
            return patch && patch->verified && patch->address != 0 &&
                patch->expected_original.size() == size &&
                std::memcmp(patch->expected_original.data(), expected, size) == 0 &&
                BytesEqual(patch->address, expected, size);
        }

        bool AddressBelongsToModule(const void* address, HMODULE expectedModule)
        {
            HMODULE owner = nullptr;
            return address && expectedModule &&
                GetModuleHandleExW(
                    GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                    reinterpret_cast<LPCWSTR>(address), &owner) &&
                owner == expectedModule;
        }

        int __cdecl ReduxLanguageInitializerHook()
        {
            const int language = g_OriginalLanguageInitializer ? g_OriginalLanguageInitializer() : 0;
            char previousNumeric[96] = {};
            if (g_ReduxSetLocale)
            {
                if (const char* previous = g_ReduxSetLocale(LC_NUMERIC, nullptr))
                    strncpy_s(previousNumeric, previous, _TRUNCATE);
            }
            const bool applied = EnforceCNumericLocale(g_ReduxSetLocale);
            char numericAfter[96] = {};
            char allCategories[256] = {};
            if (g_ReduxSetLocale)
            {
                if (const char* numeric = g_ReduxSetLocale(LC_NUMERIC, nullptr))
                    strncpy_s(numericAfter, numeric, _TRUNCATE);
                if (const char* categories = g_ReduxSetLocale(LC_ALL, nullptr))
                    strncpy_s(allCategories, categories, _TRUNCATE);
            }
            Log(L"[LOCALE] Redux language=%d numericBefore=%hs numericAfter=%hs categories=%hs state=%hs\n",
                language,
                previousNumeric[0] ? previousNumeric : "<query-failed>",
                numericAfter[0] ? numericAfter : "<query-failed>",
                allCategories[0] ? allCategories : "<query-failed>",
                applied ? "applied" : "failed");
            return language;
        }

        size_t __cdecl ReduxTrnCanonicalFwrite(
            const void* buffer, size_t elementSize, size_t elementCount, void* stream)
        {
            if (!g_ReduxFwrite || elementSize == 0 || elementCount == 0)
                return g_ReduxFwrite ? g_ReduxFwrite(buffer, elementSize, elementCount, stream) : 0;
            if (!buffer || elementCount > (std::numeric_limits<size_t>::max)() / elementSize)
                return g_ReduxFwrite(buffer, elementSize, elementCount, stream);

            try
            {
                const size_t byteCount = elementSize * elementCount;
                const auto* bytes = static_cast<const uint8_t*>(buffer);
                std::vector<uint8_t> input(bytes, bytes + byteCount);
                TrnCanonicalResult result = CanonicalizeTrnBytes(input);
                if (result.status != TrnCodecStatus::Ok)
                {
                    // Binary-mode raw preservation is the fail-closed behavior:
                    // unsupported Unicode is not silently reinterpreted or lost.
                    Log(L"[TRN] Producer serializer preserved raw input status=%hs bytes=%u\n",
                        TrnCodecStatusName(result.status), static_cast<unsigned>(byteCount));
                    return g_ReduxFwrite(buffer, elementSize, elementCount, stream);
                }

                const size_t written = g_ReduxFwrite(
                    result.serializedCrLf.data(), 1, result.serializedCrLf.size(), stream);
                Log(L"[TRN] Producer serializer encoding=%hs bytes=%u->%u state=%hs\n",
                    TrnSourceEncodingName(result.sourceEncoding),
                    static_cast<unsigned>(byteCount),
                    static_cast<unsigned>(result.serializedCrLf.size()),
                    written == result.serializedCrLf.size() ? "ok" : "short-write");
                return written == result.serializedCrLf.size() ? elementCount : 0;
            }
            catch (...)
            {
                Log(L"[TRN] Producer serializer exception; preserving raw bytes in binary mode\n");
                return g_ReduxFwrite(buffer, elementSize, elementCount, stream);
            }
        }

        std::vector<uint8_t> MakeCallPayload(uint32_t source, const void* destination, size_t length)
        {
            std::vector<uint8_t> payload(length, 0x90);
            payload[0] = 0xE8;
            const int32_t relative = static_cast<int32_t>(reinterpret_cast<uintptr_t>(destination)) -
                static_cast<int32_t>(source + 5);
            std::memcpy(payload.data() + 1, &relative, sizeof(relative));
            return payload;
        }
    }

    bool IsReduxCompatibilityPatchName(const char* name)
    {
        return name && (std::strcmp(name, kLocalePatchName) == 0 ||
            std::strcmp(name, kTrnModePatchName) == 0 ||
            std::strcmp(name, kTrnWritePatchName) == 0);
    }

    ReduxCompatibilityGate PrepareReduxCompatibilityGate(bool steam)
    {
        ReduxCompatibilityGate gate;
        gate.steam = steam;
        HMODULE module = GetModuleHandleW(nullptr);
        gate.moduleBase = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(module));
        if (module)
        {
            const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(module);
            if (dos->e_magic == IMAGE_DOS_SIGNATURE)
            {
                const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS32*>(
                    reinterpret_cast<const uint8_t*>(module) + dos->e_lfanew);
                if (nt->Signature == IMAGE_NT_SIGNATURE)
                    gate.imageSize = nt->OptionalHeader.SizeOfImage;
            }
        }

        wchar_t path[MAX_PATH] = {};
        const DWORD pathLength = GetModuleFileNameW(nullptr, path, MAX_PATH);
        if (pathLength > 0 && pathLength < MAX_PATH)
            ComputeSha256(path, gate.sha256, gate.fileSize);
        const char* expectedHash = steam ? kSteamSha256 : kGogSha256;
        gate.supportedHash = !gate.sha256.empty() && gate.sha256 == expectedHash;
        gate.settledBytes = gate.supportedHash &&
            WaitForSettledCompatibilityBytes(gate.moduleBase, steam);

        Log(L"[COMPAT] build=%hs sha256=%hs fileSize=%llu base=0x%08X imageSize=%u hashGate=%hs settledBytes=%hs\n",
            steam ? "Steam-2.2.301" : "GOG-2.2.301",
            gate.sha256.empty() ? "<unavailable>" : gate.sha256.c_str(),
            static_cast<unsigned long long>(gate.fileSize),
            gate.moduleBase,
            gate.imageSize,
            gate.supportedHash ? "pass" : "fail",
            gate.settledBytes ? "pass" : "fail");
        return gate;
    }

    int ApplyReduxCompatibilityPatches(
        std::vector<HookEngine::PatchDef>& patches,
        const ReduxCompatibilityGate& gate)
    {
        if (!gate.supportedHash || !gate.settledBytes)
        {
            Log(L"[COMPAT] Locale/TRN patches not applied: build gate failed closed\n");
            return 0;
        }

        auto* localePatch = FindPatch(patches, kLocalePatchName);
        auto* modePatch = FindPatch(patches, kTrnModePatchName);
        auto* writePatch = FindPatch(patches, kTrnWritePatchName);
        static constexpr uint8_t kLocaleExpected[] = { 0xE8, 0xBA, 0x50, 0x20, 0x00 };
        static constexpr uint8_t kModeExpected[] = { 0x68, 0x5C, 0x67, 0x87, 0x00 };
        static constexpr uint8_t kWriteExpected[] = { 0xFF, 0x15, 0x84, 0x94, 0x86, 0x00 };

        HMODULE msvcr120 = GetModuleHandleW(L"msvcr120.dll");
        auto* setLocaleIat = reinterpret_cast<SetLocaleFunction*>(gate.moduleBase + 0x00469544u);
        auto* fwriteIat = reinterpret_cast<ReduxFwrite*>(gate.moduleBase + 0x00469484u);
        g_ReduxSetLocale = setLocaleIat ? *setLocaleIat : nullptr;
        g_ReduxFwrite = fwriteIat ? *fwriteIat : nullptr;

        int applied = 0;
        if (PatchHasExpectedBytes(localePatch, kLocaleExpected, sizeof(kLocaleExpected)))
        {
            g_OriginalLanguageInitializer = reinterpret_cast<LanguageInitializer>(
                HookEngine::ResolveRelCallTarget(localePatch->address));
            if (g_OriginalLanguageInitializer &&
                reinterpret_cast<uintptr_t>(g_OriginalLanguageInitializer) == gate.moduleBase + 0x0041DF00u &&
                AddressBelongsToModule(reinterpret_cast<void*>(g_ReduxSetLocale), msvcr120))
            {
                localePatch->payload = MakeCallPayload(
                    localePatch->address, reinterpret_cast<void*>(ReduxLanguageInitializerHook), 5);
                if (HookEngine::ApplyPatch(*localePatch))
                {
                    ++applied;
                    Log(L"[LOCALE] Applied guarded post-language LC_NUMERIC=C call hook at 0x%08X\n",
                        localePatch->address);
                }
                else
                {
                    Log(L"[LOCALE] Not applied: expected bytes changed before write\n");
                }
            }
            else
            {
                Log(L"[LOCALE] Not applied: initializer or MSVCR120 ownership check failed\n");
            }
        }
        else
        {
            Log(L"[LOCALE] Not applied: unique signature/expected-byte check failed\n");
        }

        const bool trnReady =
            PatchHasExpectedBytes(modePatch, kModeExpected, sizeof(kModeExpected)) &&
            PatchHasExpectedBytes(writePatch, kWriteExpected, sizeof(kWriteExpected)) &&
            AddressBelongsToModule(reinterpret_cast<void*>(g_ReduxFwrite), msvcr120);
        if (!trnReady)
        {
            Log(L"[TRN] Producer correction not applied: unique signatures, bytes, or MSVCR120 ownership failed\n");
            return applied;
        }

        modePatch->payload.assign(std::begin(kModeExpected), std::end(kModeExpected));
        const uint32_t binaryModeAddress = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_TrnBinaryMode));
        std::memcpy(modePatch->payload.data() + 1, &binaryModeAddress, sizeof(binaryModeAddress));
        writePatch->payload = MakeCallPayload(
            writePatch->address, reinterpret_cast<void*>(ReduxTrnCanonicalFwrite), 6);

        if (!HookEngine::ApplyPatch(*modePatch))
        {
            Log(L"[TRN] Producer correction not applied: binary-mode write failed\n");
            return applied;
        }
        if (!HookEngine::ApplyPatch(*writePatch))
        {
            const bool rolledBack = HookEngine::WriteMemory(
                modePatch->address, kModeExpected, sizeof(kModeExpected));
            Log(L"[TRN] Producer correction not applied: serializer hook failed; mode rollback=%hs\n",
                rolledBack ? "ok" : "failed");
            return applied;
        }

        applied += 2;
        Log(L"[TRN] Applied guarded binary-mode/canonical serializer producer correction mode=0x%08X write=0x%08X\n",
            modePatch->address, writePatch->address);
        return applied;
    }
}
