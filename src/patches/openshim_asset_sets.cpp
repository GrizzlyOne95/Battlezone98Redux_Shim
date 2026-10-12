#include "openshim_asset_sets.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <cstring>
#include <exception>
#include <fstream>
#include <iterator>
#include <regex>
#include <sstream>
#include <system_error>

namespace BZROpenShim
{
    namespace
    {
        namespace fs = std::filesystem;

        constexpr char kRendererSet[] = "renderer";
        constexpr char kWidgetsSet[] = "customWidgets";

        std::string Lower(std::string value)
        {
            std::transform(value.begin(), value.end(), value.begin(), [](unsigned char ch)
            {
                return static_cast<char>(std::tolower(ch));
            });
            return value;
        }

        bool IsSha256(const std::string& value)
        {
            return value.size() == 64 &&
                std::all_of(value.begin(), value.end(), [](unsigned char ch)
                {
                    return std::isxdigit(ch) != 0;
                });
        }

        // Lua escaping in the manifest: only "\\" is meaningful. Any other
        // backslash sequence cannot be a legal path, so it is rejected.
        bool UnescapeBackslashes(const std::string& raw, std::string& out)
        {
            out.clear();
            for (size_t index = 0; index < raw.size(); ++index)
            {
                if (raw[index] == '\\')
                {
                    if (index + 1 >= raw.size() || raw[index + 1] != '\\')
                        return false;
                    ++index;
                }
                out.push_back(raw[index]);
            }
            return true;
        }

        // Relative, backslash-separated, [A-Za-z0-9_.-] components, no empty
        // component, no ".." anywhere, no component that Windows would
        // silently trim (trailing dot).
        bool IsSafeRelativePath(const std::string& path)
        {
            if (path.empty() || path.front() == '\\' || path.back() == '\\')
                return false;
            if (path.find("..") != std::string::npos)
                return false;
            size_t begin = 0;
            while (begin <= path.size())
            {
                size_t end = path.find('\\', begin);
                if (end == std::string::npos)
                    end = path.size();
                const std::string part = path.substr(begin, end - begin);
                if (part.empty() || part.back() == '.')
                    return false;
                for (const unsigned char ch : part)
                {
                    if (!(std::isalnum(ch) || ch == '_' || ch == '.' || ch == '-'))
                        return false;
                }
                begin = end + 1;
            }
            return true;
        }

        fs::path ToPath(const std::string& relative)
        {
            std::string converted = relative;
            std::replace(converted.begin(), converted.end(), '\\', '/');
            return fs::path(converted);
        }

        bool IsKnownSet(const std::string& name)
        {
            return name == kRendererSet || name == kWidgetsSet;
        }

        std::vector<std::string> SplitLines(const std::string& text)
        {
            std::vector<std::string> lines;
            std::istringstream stream(text);
            std::string line;
            while (std::getline(stream, line))
            {
                while (!line.empty() && (line.back() == '\r' || line.back() == ' ' || line.back() == '\t'))
                    line.pop_back();
                size_t first = 0;
                while (first < line.size() && (line[first] == ' ' || line[first] == '\t'))
                    ++first;
                lines.push_back(line.substr(first));
            }
            return lines;
        }

        bool ParseText(const std::string& text, OpenShimAssetSets& out, std::string& error)
        {
            const std::regex sectionStart(R"(^(assetSets|assetFiles)\s*=\s*\{$)");
            const std::regex setLine(
                R"MANIFEST(^(\w+)\s*=\s*\{\s*source\s*=\s*"([^"]*)"\s*,\s*destination\s*=\s*"([^"]*)"\s*,\s*sha256\s*=\s*"([^"]*)"\s*,\s*files\s*=\s*([0-9]+)\s*\}\s*,?$)MANIFEST");
            const std::regex fileLine(
                R"MANIFEST(^\{\s*set\s*=\s*"([^"]*)"\s*,\s*path\s*=\s*"([^"]*)"\s*,\s*sha256\s*=\s*"([^"]*)"\s*,\s*size\s*=\s*([0-9]+)\s*\}\s*,?$)MANIFEST");

            struct PendingFile
            {
                std::string set;
                OpenShimAssetFile file;
            };
            std::vector<PendingFile> files;
            bool sawSets = false;
            bool sawFiles = false;

            const std::vector<std::string> lines = SplitLines(text);
            for (size_t index = 0; index < lines.size(); ++index)
            {
                std::smatch match;
                if (!std::regex_match(lines[index], match, sectionStart))
                    continue;
                const bool isSets = match[1].str() == "assetSets";
                if (isSets ? sawSets : sawFiles)
                {
                    error = "asset manifest section appears twice";
                    return false;
                }
                (isSets ? sawSets : sawFiles) = true;

                bool closed = false;
                for (++index; index < lines.size(); ++index)
                {
                    const std::string& line = lines[index];
                    if (line.empty() || line.compare(0, 2, "--") == 0)
                        continue;
                    if (line[0] == '}')
                    {
                        closed = true;
                        break;
                    }
                    std::smatch entry;
                    if (isSets)
                    {
                        if (!std::regex_match(line, entry, setLine))
                        {
                            error = "malformed assetSets entry";
                            return false;
                        }
                        OpenShimAssetSet set;
                        set.name = entry[1].str();
                        if (!IsKnownSet(set.name))
                        {
                            out.ignored.push_back(set.name);
                            continue;
                        }
                        if (!UnescapeBackslashes(entry[2].str(), set.source) ||
                            !UnescapeBackslashes(entry[3].str(), set.destination) ||
                            !IsSha256(entry[4].str()) || entry[5].str().size() > 6)
                        {
                            error = "invalid assetSets entry for " + set.name;
                            return false;
                        }
                        set.sha256 = Lower(entry[4].str());
                        set.files = static_cast<uint32_t>(std::stoul(entry[5].str()));
                        if (!IsSafeRelativePath(set.source) || !IsSafeRelativePath(set.destination))
                        {
                            error = "unsafe path in assetSets entry for " + set.name;
                            return false;
                        }
                        for (const auto& existing : out.sets)
                        {
                            if (existing.name == set.name)
                            {
                                error = "duplicate asset set " + set.name;
                                return false;
                            }
                        }
                        out.sets.push_back(std::move(set));
                    }
                    else
                    {
                        if (!std::regex_match(line, entry, fileLine))
                        {
                            error = "malformed assetFiles entry";
                            return false;
                        }
                        PendingFile pending;
                        pending.set = entry[1].str();
                        if (!IsKnownSet(pending.set))
                            continue;
                        if (!UnescapeBackslashes(entry[2].str(), pending.file.path) ||
                            !IsSha256(entry[3].str()) || entry[4].str().size() > 15)
                        {
                            error = "invalid assetFiles entry in set " + pending.set;
                            return false;
                        }
                        pending.file.sha256 = Lower(entry[3].str());
                        pending.file.size = std::stoull(entry[4].str());
                        if (!IsSafeRelativePath(pending.file.path))
                        {
                            error = "unsafe file path in set " + pending.set;
                            return false;
                        }
                        files.push_back(std::move(pending));
                    }
                }
                if (!closed)
                {
                    error = "asset manifest section is not closed";
                    return false;
                }
            }

            for (auto& pending : files)
            {
                auto set = std::find_if(out.sets.begin(), out.sets.end(),
                    [&](const OpenShimAssetSet& candidate) { return candidate.name == pending.set; });
                if (set == out.sets.end())
                {
                    error = "assetFiles names undeclared set " + pending.set;
                    return false;
                }
                const std::string key = Lower(pending.file.path);
                for (const auto& existing : set->entries)
                {
                    if (Lower(existing.path) == key)
                    {
                        error = "duplicate file " + pending.file.path + " in set " + pending.set;
                        return false;
                    }
                }
                set->entries.push_back(std::move(pending.file));
            }
            for (const auto& set : out.sets)
            {
                if (set.files == 0 || set.entries.size() != set.files)
                {
                    error = "file count does not match the entries for set " + set.name;
                    return false;
                }
            }
            return true;
        }

        // Streaming SHA-256 (FIPS 180-4).
        class Sha256
        {
        public:
            void Update(const void* data, size_t length)
            {
                const unsigned char* bytes = static_cast<const unsigned char*>(data);
                total_ += length;
                while (length > 0)
                {
                    const size_t take = (std::min)(length, block_.size() - used_);
                    std::memcpy(block_.data() + used_, bytes, take);
                    used_ += take;
                    bytes += take;
                    length -= take;
                    if (used_ == block_.size())
                    {
                        Compress();
                        used_ = 0;
                    }
                }
            }

            std::string Finish()
            {
                const uint64_t bits = total_ * 8;
                const unsigned char one = 0x80;
                Update(&one, 1);
                const unsigned char zero = 0;
                while (used_ != 56)
                    Update(&zero, 1);
                unsigned char length[8];
                for (int index = 0; index < 8; ++index)
                    length[index] = static_cast<unsigned char>(bits >> (56 - 8 * index));
                Update(length, 8);

                static const char digits[] = "0123456789abcdef";
                std::string hex;
                for (const uint32_t word : state_)
                {
                    for (int shift = 28; shift >= 0; shift -= 4)
                        hex.push_back(digits[(word >> shift) & 0xF]);
                }
                return hex;
            }

        private:
            static uint32_t Rotr(uint32_t value, unsigned bits)
            {
                return (value >> bits) | (value << (32 - bits));
            }

            void Compress()
            {
                static const uint32_t k[64] = {
                    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
                    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
                    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
                    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
                    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
                    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
                    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
                    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2 };
                uint32_t w[64];
                for (int index = 0; index < 16; ++index)
                {
                    w[index] = (uint32_t(block_[index * 4]) << 24) | (uint32_t(block_[index * 4 + 1]) << 16) |
                               (uint32_t(block_[index * 4 + 2]) << 8) | uint32_t(block_[index * 4 + 3]);
                }
                for (int index = 16; index < 64; ++index)
                {
                    const uint32_t s0 = Rotr(w[index - 15], 7) ^ Rotr(w[index - 15], 18) ^ (w[index - 15] >> 3);
                    const uint32_t s1 = Rotr(w[index - 2], 17) ^ Rotr(w[index - 2], 19) ^ (w[index - 2] >> 10);
                    w[index] = w[index - 16] + s0 + w[index - 7] + s1;
                }
                uint32_t a = state_[0], b = state_[1], c = state_[2], d = state_[3];
                uint32_t e = state_[4], f = state_[5], g = state_[6], h = state_[7];
                for (int index = 0; index < 64; ++index)
                {
                    const uint32_t s1 = Rotr(e, 6) ^ Rotr(e, 11) ^ Rotr(e, 25);
                    const uint32_t choose = (e & f) ^ (~e & g);
                    const uint32_t t1 = h + s1 + choose + k[index] + w[index];
                    const uint32_t s0 = Rotr(a, 2) ^ Rotr(a, 13) ^ Rotr(a, 22);
                    const uint32_t majority = (a & b) ^ (a & c) ^ (b & c);
                    const uint32_t t2 = s0 + majority;
                    h = g; g = f; f = e; e = d + t1;
                    d = c; c = b; b = a; a = t1 + t2;
                }
                state_[0] += a; state_[1] += b; state_[2] += c; state_[3] += d;
                state_[4] += e; state_[5] += f; state_[6] += g; state_[7] += h;
            }

            std::array<uint32_t, 8> state_ = { 0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                                               0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 };
            std::array<unsigned char, 64> block_ = {};
            size_t used_ = 0;
            uint64_t total_ = 0;
        };

        bool VerifyFile(const fs::path& file, const OpenShimAssetFile& entry, std::string& problem)
        {
            std::string hex;
            uint64_t size = 0;
            if (!Sha256HexOfFile(file, hex, size))
            {
                problem = "cannot read " + entry.path;
                return false;
            }
            if (size != entry.size || hex != entry.sha256)
            {
                problem = entry.path + " does not match the manifest";
                return false;
            }
            return true;
        }

        std::string ReadMarker(const fs::path& file)
        {
            std::ifstream input(file, std::ios::binary);
            std::string text((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
            while (!text.empty() && (text.back() == '\n' || text.back() == '\r' || text.back() == ' '))
                text.pop_back();
            return text;
        }

        bool WriteMarker(const fs::path& file, const std::string& hash)
        {
            std::ofstream output(file, std::ios::binary | std::ios::trunc);
            output << hash << '\n';
            output.flush();
            return static_cast<bool>(output);
        }

        OpenShimAssetSyncOutcome Outcome(OpenShimAssetSyncResult result, std::string detail,
                                         uint32_t installed = 0)
        {
            OpenShimAssetSyncOutcome outcome;
            outcome.result = result;
            outcome.detail = std::move(detail);
            outcome.filesInstalled = installed;
            return outcome;
        }

        OpenShimAssetSyncOutcome SyncRenderer(const fs::path& source, const fs::path& destination,
                                              const OpenShimAssetSet& set,
                                              const OpenShimAssetSetValidator& validator)
        {
            const fs::path pending = destination.parent_path() / (destination.filename().string() + ".pending");
            const fs::path old = destination.parent_path() / (destination.filename().string() + ".old");
            std::error_code ec;

            fs::remove_all(pending, ec);
            ec.clear();
            fs::create_directories(pending, ec);
            if (ec)
                return Outcome(OpenShimAssetSyncResult::Deferred, "cannot create " + pending.filename().string());

            auto fail = [&](OpenShimAssetSyncResult result, const std::string& why)
            {
                std::error_code cleanup;
                fs::remove_all(pending, cleanup);
                return Outcome(result, why);
            };

            for (const auto& entry : set.entries)
            {
                const fs::path target = pending / ToPath(entry.path);
                fs::create_directories(target.parent_path(), ec);
                ec.clear();
                fs::copy_file(source / ToPath(entry.path), target, fs::copy_options::overwrite_existing, ec);
                std::string problem;
                if (ec || !VerifyFile(target, entry, problem))
                    return fail(OpenShimAssetSyncResult::Refused, "could not stage " + entry.path);
            }
            if (!WriteMarker(pending / OpenShimAssetSetMarkerName(set.name), set.sha256))
                return fail(OpenShimAssetSyncResult::Deferred, "could not write marker");
            std::string problem;
            if (validator && !validator(pending, problem))
                return fail(OpenShimAssetSyncResult::Refused, "staged copy failed validation: " + problem);

            ec.clear();
            if (fs::exists(destination, ec))
            {
                fs::remove_all(old, ec);
                ec.clear();
                fs::rename(destination, old, ec);
                if (ec)
                    return fail(OpenShimAssetSyncResult::Deferred, "live directory is locked");
                fs::rename(pending, destination, ec);
                if (ec)
                {
                    std::error_code restore;
                    fs::rename(old, destination, restore);
                    return fail(OpenShimAssetSyncResult::Deferred, "could not move the new copy into place");
                }
                fs::remove_all(old, ec);
            }
            else
            {
                ec.clear();
                fs::create_directories(destination.parent_path(), ec);
                ec.clear();
                fs::rename(pending, destination, ec);
                if (ec)
                    return fail(OpenShimAssetSyncResult::Deferred, "could not move the new copy into place");
            }
            return Outcome(OpenShimAssetSyncResult::Installed, "", set.files);
        }

        OpenShimAssetSyncOutcome SyncWidgets(const fs::path& source, const fs::path& destination,
                                             const OpenShimAssetSet& set)
        {
            std::error_code ec;
            fs::create_directories(destination, ec);
            if (ec)
                return Outcome(OpenShimAssetSyncResult::Deferred, "cannot create destination");

            uint32_t installed = 0;
            for (const auto& entry : set.entries)
            {
                const fs::path target = destination / ToPath(entry.path);
                std::string problem;
                // Already correct: leave it alone rather than rewrite a file
                // the game may have open.
                ec.clear();
                if (fs::is_regular_file(target, ec) && VerifyFile(target, entry, problem))
                    continue;

                const fs::path temporary = target.parent_path() / (target.filename().string() + ".tmp");
                ec.clear();
                fs::create_directories(target.parent_path(), ec);
                ec.clear();
                fs::copy_file(source / ToPath(entry.path), temporary, fs::copy_options::overwrite_existing, ec);
                if (!ec && VerifyFile(temporary, entry, problem))
                    fs::rename(temporary, target, ec);
                else if (!ec)
                    ec = std::make_error_code(std::errc::io_error);
                if (ec)
                {
                    std::error_code cleanup;
                    fs::remove(temporary, cleanup);
                    return Outcome(OpenShimAssetSyncResult::Deferred,
                                   entry.path + " could not be replaced", installed);
                }
                ++installed;
            }
            if (!WriteMarker(destination / OpenShimAssetSetMarkerName(set.name), set.sha256))
                return Outcome(OpenShimAssetSyncResult::Deferred, "could not write marker", installed);
            return Outcome(OpenShimAssetSyncResult::Installed, "", installed);
        }
    }

    bool ParseOpenShimAssetSets(const std::string& text,
                                OpenShimAssetSets& out,
                                std::string& error)
    {
        out = {};
        error.clear();
        // std::regex can throw on pathological input and the manifest is
        // untrusted text from a Workshop download.
        try
        {
            if (ParseText(text, out, error))
                return true;
        }
        catch (const std::exception&)
        {
            error = "asset manifest sections could not be parsed";
        }
        out = {};
        return false;
    }

    std::string ComputeOpenShimAssetSetHash(const std::vector<OpenShimAssetFile>& entries)
    {
        std::vector<std::string> lines;
        lines.reserve(entries.size());
        for (const auto& entry : entries)
        {
            lines.push_back(Lower(entry.path) + "|" + Lower(entry.sha256) + "|" +
                            std::to_string(entry.size) + "\n");
        }
        // Sort on the path field alone so a later field can never reorder
        // two entries (a path that prefixes another sorts first either way).
        std::sort(lines.begin(), lines.end(), [](const std::string& left, const std::string& right)
        {
            return left.substr(0, left.find('|')) < right.substr(0, right.find('|'));
        });
        Sha256 hash;
        for (const auto& line : lines)
            hash.Update(line.data(), line.size());
        return hash.Finish();
    }

    std::string Sha256Hex(const void* data, size_t length)
    {
        Sha256 hash;
        hash.Update(data, length);
        return hash.Finish();
    }

    bool Sha256HexOfFile(const std::filesystem::path& path, std::string& hex, uint64_t& size)
    {
        hex.clear();
        size = 0;
        std::ifstream input(path, std::ios::binary);
        if (!input.is_open())
            return false;
        Sha256 hash;
        std::array<char, 64 * 1024> buffer;
        while (input.read(buffer.data(), static_cast<std::streamsize>(buffer.size())) || input.gcount() > 0)
        {
            hash.Update(buffer.data(), static_cast<size_t>(input.gcount()));
            size += static_cast<uint64_t>(input.gcount());
        }
        if (input.bad())
            return false;
        hex = hash.Finish();
        return true;
    }

    const char* OpenShimAssetSetMarkerName(const std::string& setName)
    {
        if (setName == kRendererSet)
            return "openshim_set.sha256";
        if (setName == kWidgetsSet)
            return "openshim_widgets.sha256";
        return "";
    }

    OpenShimAssetSyncOutcome SyncOpenShimAssetSet(const std::filesystem::path& itemDir,
                                                  const std::filesystem::path& gameDir,
                                                  const OpenShimAssetSet& set,
                                                  const OpenShimAssetSetValidator& validator)
    {
        const std::string markerName = OpenShimAssetSetMarkerName(set.name);
        if (markerName.empty())
            return Outcome(OpenShimAssetSyncResult::Refused, "unknown asset set");

        const fs::path source = itemDir / ToPath(set.source);
        const fs::path destination = gameDir / ToPath(set.destination);

        if (ReadMarker(destination / markerName) == set.sha256)
            return Outcome(OpenShimAssetSyncResult::Current, "");

        if (ComputeOpenShimAssetSetHash(set.entries) != set.sha256)
            return Outcome(OpenShimAssetSyncResult::Refused, "declared set hash does not match its file list");
        for (const auto& entry : set.entries)
        {
            std::string problem;
            if (!VerifyFile(source / ToPath(entry.path), entry, problem))
                return Outcome(OpenShimAssetSyncResult::Refused, "Workshop copy: " + problem);
        }

        if (set.name == kRendererSet)
        {
            std::string problem;
            if (validator && !validator(source, problem))
                return Outcome(OpenShimAssetSyncResult::Refused, "Workshop copy failed validation: " + problem);
            return SyncRenderer(source, destination, set, validator);
        }
        return SyncWidgets(source, destination, set);
    }
}
