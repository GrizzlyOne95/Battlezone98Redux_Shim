// Store-only zip writer behind the Options "Build Troubleshooting Bundle" row:
// the archive must open in Explorer and any unzip tool, and a capped file
// must keep its newest bytes.
#include "troubleshooting_bundle.h"

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include "test_check.h"

namespace
{
    using BZROpenShim::Crc32Update;
    using BZROpenShim::StoreZipWriter;

    uint32_t Get32(const std::vector<unsigned char>& b, size_t at)
    {
        return b[at] | (b[at + 1] << 8) | (b[at + 2] << 16) | (static_cast<uint32_t>(b[at + 3]) << 24);
    }
    uint16_t Get16(const std::vector<unsigned char>& b, size_t at)
    {
        return static_cast<uint16_t>(b[at] | (b[at + 1] << 8));
    }

    std::wstring TempPath(const wchar_t* name)
    {
        wchar_t dir[MAX_PATH] = {};
        GetTempPathW(MAX_PATH, dir);
        return std::wstring(dir) + name;
    }

    std::vector<unsigned char> ReadAll(const std::wstring& path)
    {
        std::ifstream in(path, std::ios::binary);
        return std::vector<unsigned char>(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
    }

    void TestCrcMatchesTheZipPolynomial()
    {
        CHECK(Crc32Update(0, "hello", 5) == 0x3610A686u);
        // Chunked updates equal one pass.
        CHECK(Crc32Update(Crc32Update(0, "hel", 3), "lo", 2) == 0x3610A686u);
        CHECK(Crc32Update(0, "", 0) == 0u);
    }

    void TestArchiveLayout()
    {
        const std::wstring source = TempPath(L"openshim_bundle_test_source.txt");
        const std::wstring zipPath = TempPath(L"openshim_bundle_test.zip");
        {
            std::ofstream out(source, std::ios::binary);
            out << "0123456789";
        }

        StoreZipWriter zip;
        OpenShimTest::Require(zip.Open(zipPath), "zip.Open(zipPath)");
        CHECK(zip.AddBytes("summary.txt", "hello", 5));
        uint64_t copied = 0;
        uint64_t total = 0;
        CHECK(zip.AddFile("logs/tail.txt", source, 4, copied, total));
        CHECK(copied == 4 && total == 10);
        CHECK(!zip.AddFile("missing.txt", TempPath(L"openshim_bundle_no_such_file"), 4, copied, total));
        OpenShimTest::Require(zip.Close(), "zip.Close()");

        const std::vector<unsigned char> bytes = ReadAll(zipPath);
        OpenShimTest::Require(bytes.size() > 22, "bytes.size() > 22");
        const size_t eocd = bytes.size() - 22;
        CHECK(Get32(bytes, eocd) == 0x06054B50u);
        CHECK(Get16(bytes, eocd + 10) == 2);
        const size_t directory = Get32(bytes, eocd + 16);
        CHECK(directory + Get32(bytes, eocd + 12) == eocd);

        // First entry: local header patched with the crc and size.
        CHECK(Get32(bytes, 0) == 0x04034B50u);
        CHECK(Get32(bytes, 14) == 0x3610A686u);
        CHECK(Get32(bytes, 18) == 5 && Get32(bytes, 22) == 5);
        CHECK(std::memcmp(&bytes[30], "summary.txt", 11) == 0);
        CHECK(std::memcmp(&bytes[41], "hello", 5) == 0);

        // Second entry keeps the last four bytes of the source.
        const size_t second = 46;
        CHECK(Get32(bytes, second) == 0x04034B50u);
        CHECK(Get32(bytes, second + 18) == 4);
        CHECK(Get32(bytes, second + 14) == Crc32Update(0, "6789", 4));
        CHECK(std::memcmp(&bytes[second + 30 + 13], "6789", 4) == 0);

        // Central directory points back at both local headers.
        CHECK(Get32(bytes, directory) == 0x02014B50u);
        CHECK(Get32(bytes, directory + 42) == 0);
        const size_t nextCentral = directory + 46 + 11;
        CHECK(Get32(bytes, nextCentral) == 0x02014B50u);
        CHECK(Get32(bytes, nextCentral + 42) == second);
        CHECK(Get32(bytes, nextCentral + 16) == Crc32Update(0, "6789", 4));

        DeleteFileW(source.c_str());
        DeleteFileW(zipPath.c_str());
    }
}

int main()
{
    TestCrcMatchesTheZipPolynomial();
    TestArchiveLayout();
    if (OpenShimTest::FailureCount() == 0)
        std::printf("troubleshooting_bundle_tests: all passed\n");
    return OpenShimTest::ExitCode();
}
