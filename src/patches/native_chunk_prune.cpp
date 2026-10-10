#include "native_chunk_prune.h"
#include <algorithm>
#include <chrono>
#include <mutex>
#include <set>
#include <system_error>

namespace BZROpenShim::NativeChunks
{
namespace
{
using FileClock = std::filesystem::file_time_type::clock;

int64_t toSeconds(std::filesystem::file_time_type t)
{
    return std::chrono::duration_cast<std::chrono::seconds>(t.time_since_epoch()).count();
}

struct TreeSpec
{
    std::string group;   // "native"
    std::string version; // "v4"
    bool models;         // children of the current version are per-model folders
};

// "native/v4/" -> {"native", "v4"}
TreeSpec parseTree(const char *constant, bool models)
{
    std::string text(constant);
    while (!text.empty() && text.back() == '/')
        text.pop_back();
    const auto slash = text.find('/');
    return {text.substr(0, slash), slash == std::string::npos ? std::string() : text.substr(slash + 1), models};
}

std::vector<TreeSpec> trees()
{
    return {parseTree(OPENSHIM_CHUNK_CACHE_NATIVE_DIR, true), parseTree(OPENSHIM_CHUNK_CACHE_GIBS_DIR, true),
            parseTree(OPENSHIM_CHUNK_CACHE_FALLBACK_DIR, false), parseTree(OPENSHIM_CHUNK_CACHE_CASINGS_DIR, false)};
}

bool isLink(const std::filesystem::path &path)
{
    std::error_code ec;
    const auto status = std::filesystem::symlink_status(path, ec);
    if (ec)
        return true; // unreadable: treat as untouchable
    if (status.type() == std::filesystem::file_type::symlink)
        return true;
#ifdef _MSC_VER
    if (status.type() == std::filesystem::file_type::junction)
        return true;
#endif
    return false;
}

bool isDir(const std::filesystem::path &path)
{
    std::error_code ec;
    const auto status = std::filesystem::symlink_status(path, ec);
    return !ec && status.type() == std::filesystem::file_type::directory;
}

// Regular files only; links are never followed or counted.
uint64_t treeBytes(const std::filesystem::path &path)
{
    std::error_code ec;
    const auto status = std::filesystem::symlink_status(path, ec);
    if (ec)
        return 0;
    if (status.type() == std::filesystem::file_type::regular)
    {
        const auto size = std::filesystem::file_size(path, ec);
        return ec ? 0 : size;
    }
    if (status.type() != std::filesystem::file_type::directory)
        return 0;
    uint64_t total = 0;
    std::filesystem::recursive_directory_iterator it(path, std::filesystem::directory_options::skip_permission_denied,
                                                    ec),
        end;
    for (; !ec && it != end; it.increment(ec))
    {
        std::error_code entryEc;
        if (it->symlink_status(entryEc).type() == std::filesystem::file_type::regular && !entryEc)
        {
            const auto size = it->file_size(entryEc);
            if (!entryEc)
                total += size;
        }
    }
    return total;
}

int64_t lastWrite(const std::filesystem::path &path, int64_t fallback)
{
    std::error_code ec;
    const auto t = std::filesystem::last_write_time(path, ec);
    return ec ? fallback : toSeconds(t);
}

bool modelName(const std::string &name)
{
    return !name.empty() && name.size() <= 16 && name.find_first_not_of("0123456789abcdef") == std::string::npos;
}

std::string lowerAscii(std::string s)
{
    for (auto &c : s)
        if (c >= 'A' && c <= 'Z')
            c += 'a' - 'A';
    return s;
}

void add(std::vector<PruneEntry> &out, const std::filesystem::path &root, const std::filesystem::path &path,
         PruneKind kind, int64_t now)
{
    PruneEntry entry;
    entry.path = path.lexically_relative(root).generic_string();
    entry.kind = kind;
    entry.lastUse = lastWrite(path, now);
    entry.bytes = treeBytes(path);
    out.push_back(std::move(entry));
}

std::vector<PruneEntry> scan(const std::filesystem::path &root, int64_t now)
{
    std::vector<PruneEntry> out;
    const auto specs = trees();
    std::error_code ec;
    std::filesystem::directory_iterator top(root, ec), end;
    for (; !ec && top != end; top.increment(ec))
    {
        const auto path = top->path();
        const auto name = path.filename().string();
        if (isLink(path))
        {
            add(out, root, path, PruneKind::Unknown, now);
            continue;
        }
        const TreeSpec *spec = nullptr;
        for (const auto &candidate : specs)
            if (isDir(path) && name == candidate.group)
                spec = &candidate;
        if (!spec)
        {
            const bool material = !isDir(path) && lowerAscii(path.extension().string()) == ".material";
            add(out, root, path, material ? PruneKind::Protected : PruneKind::Unknown, now);
            continue;
        }
        std::error_code childEc;
        std::filesystem::directory_iterator children(path, childEc);
        for (; !childEc && children != end; children.increment(childEc))
        {
            const auto child = children->path();
            const auto childName = child.filename().string();
            if (isLink(child) || !isDir(child))
            {
                add(out, root, child, PruneKind::Unknown, now);
                continue;
            }
            if (childName != spec->version)
            {
                add(out, root, child, PruneKind::ObsoleteTree, now);
                continue;
            }
            if (!spec->models)
            {
                add(out, root, child, PruneKind::Protected, now);
                continue;
            }
            std::error_code modelEc;
            std::filesystem::directory_iterator models(child, modelEc);
            for (; !modelEc && models != end; models.increment(modelEc))
            {
                const auto model = models->path();
                const bool ok = !isLink(model) && isDir(model) && modelName(model.filename().string());
                add(out, root, model, ok ? PruneKind::ModelFolder : PruneKind::Unknown, now);
            }
        }
    }
    return out;
}

bool strictlyUnder(const std::filesystem::path &root, const std::filesystem::path &target)
{
    std::error_code ec;
    const auto canonicalRoot = std::filesystem::weakly_canonical(root, ec);
    if (ec)
        return false;
    const auto canonicalTarget = std::filesystem::weakly_canonical(target, ec);
    if (ec || canonicalTarget == canonicalRoot)
        return false;
    const auto relative = canonicalTarget.lexically_relative(canonicalRoot);
    if (relative.empty() || relative.is_absolute())
        return false;
    return *relative.begin() != "..";
}
} // namespace

std::vector<std::string> SelectPruneVictims(const std::vector<PruneEntry> &entries, int64_t now,
                                            const PrunePolicy &policy)
{
    std::vector<std::string> victims;
    std::vector<const PruneEntry *> models;
    uint64_t total = 0;
    for (const auto &entry : entries)
    {
        if (entry.kind == PruneKind::ObsoleteTree)
        {
            victims.push_back(entry.path);
            continue;
        }
        if (entry.kind == PruneKind::ModelFolder && policy.maxAgeSeconds > 0 &&
            now - entry.lastUse > policy.maxAgeSeconds)
        {
            victims.push_back(entry.path);
            continue;
        }
        total += entry.bytes;
        if (entry.kind == PruneKind::ModelFolder)
            models.push_back(&entry);
    }
    if (policy.maxBytes > 0 && total > policy.maxBytes)
    {
        // Oldest first; equal times fall back to the path so the result is stable.
        std::sort(models.begin(), models.end(), [](const PruneEntry *a, const PruneEntry *b) {
            return a->lastUse != b->lastUse ? a->lastUse < b->lastUse : a->path < b->path;
        });
        for (const auto *model : models)
        {
            if (total <= policy.maxBytes)
                break;
            victims.push_back(model->path);
            total -= std::min(total, model->bytes);
        }
    }
    return victims;
}

PruneResult PruneChunkCache(const std::filesystem::path &root, const PrunePolicy &policy)
{
    PruneResult result;
    try
    {
        if (!isDir(root))
            return result;
        const int64_t now = toSeconds(FileClock::now());
        const auto entries = scan(root, now);
        result.scanned = true;
        const auto victims = SelectPruneVictims(entries, now, policy);
        const std::set<std::string> doomed(victims.begin(), victims.end());
        for (const auto &entry : entries)
        {
            bool kept = true;
            if (doomed.count(entry.path))
            {
                const auto target = root / std::filesystem::path(entry.path);
                if (!isLink(target) && strictlyUnder(root, target))
                {
                    std::error_code removeEc, statEc;
                    std::filesystem::remove_all(target, removeEc);
                    if (!removeEc && !std::filesystem::exists(std::filesystem::symlink_status(target, statEc)))
                    {
                        kept = false;
                        ++result.removed;
                        result.freedBytes += entry.bytes;
                        if (entry.kind == PruneKind::ObsoleteTree)
                            result.obsoleteTrees.push_back(entry.path);
                    }
                }
            }
            if (kept)
            {
                result.keptBytes += entry.bytes;
                if (entry.kind == PruneKind::ModelFolder)
                    ++result.keptModels;
            }
        }
    }
    catch (...)
    {
    }
    return result;
}

void TouchCacheFolder(const std::filesystem::path &folder)
{
    try
    {
        static std::mutex mutex;
        static std::set<std::filesystem::path> touched;
        {
            std::lock_guard<std::mutex> lock(mutex);
            if (!touched.insert(folder).second)
                return;
        }
        std::error_code ec;
        std::filesystem::last_write_time(folder, FileClock::now(), ec);
    }
    catch (...)
    {
    }
}
} // namespace BZROpenShim::NativeChunks
