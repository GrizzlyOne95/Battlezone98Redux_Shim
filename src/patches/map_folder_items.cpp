// map_folder_items.cpp
// BZR Open Shim - gap-only item store for a lobby map's own folder. See
// include/map_folder_items.h for why the waiting room needs it.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "map_folder_items.h"

#include "shim_log.h"

#include <fstream>
#include <mutex>
#include <unordered_map>
#include <unordered_set>

namespace BZROpenShim::MapFolderItems
{
namespace
{

constexpr std::size_t kMaxItemBytes = 1024u * 1024u; // .vxt/.des/.odf are kilobytes

struct Item
{
    std::string bytes; // one NUL past the end, so the buffer reads as a C string
    std::size_t size = 0;
    std::filesystem::path folder;
    int refcount = 0;
};

std::recursive_mutex g_Mutex;
IndexHasFn g_IndexHas = nullptr;
std::filesystem::path g_Folder;
std::unordered_map<std::string, Item> g_Items; // key: lowercase name
std::unordered_set<std::string> g_Logged;

std::string Lower(const std::string& s)
{
    std::string out = s;
    for (char& c : out)
    {
        if (c >= 'A' && c <= 'Z')
            c = static_cast<char>(c + ('a' - 'A'));
    }
    return out;
}

bool HasServedExtension(const std::string& lower)
{
    if (lower.size() < 5)
        return false;
    const std::string ext = lower.substr(lower.size() - 4);
    return ext == ".vxt" || ext == ".des" || ext == ".odf";
}

// A bare file name: the engine asks for items by name, never by path.
bool IsBareName(const std::string& name)
{
    return name.find_first_of("/\\:") == std::string::npos && name.find("..") == std::string::npos;
}

bool FileExists(const std::filesystem::path& p)
{
    std::error_code ec;
    return std::filesystem::is_regular_file(p, ec) && !ec;
}

bool ReadFileBytes(const std::filesystem::path& p, std::string& out)
{
    std::error_code ec;
    const auto size = std::filesystem::file_size(p, ec);
    if (ec || size == 0 || size > kMaxItemBytes)
        return false;
    std::ifstream in(p, std::ios::binary);
    if (!in)
        return false;
    out.assign(static_cast<std::size_t>(size) + 1, '\0');
    in.read(out.data(), static_cast<std::streamsize>(size));
    if (in.gcount() != static_cast<std::streamsize>(size))
    {
        out.clear();
        return false;
    }
    return true;
}

bool CanServeLocked(const std::string& name, const std::string& key)
{
    if (g_Folder.empty() || !g_IndexHas || !HasServedExtension(key) || !IsBareName(name))
        return false;
    if (g_IndexHas(name.c_str()))
        return false; // the engine has it; never shadow
    return FileExists(g_Folder / name);
}

// Loads (or reuses) the record for a servable name. Null when unreadable.
Item* LoadLocked(const std::string& name, const std::string& key)
{
    auto it = g_Items.find(key);
    if (it != g_Items.end() && it->second.folder == g_Folder)
        return &it->second;
    Item item;
    if (!ReadFileBytes(g_Folder / name, item.bytes))
    {
        LogShimA(LogLevel::Warn, "vehicle", "[VXT] '%s' in '%s' is unreadable, empty or over %zu bytes",
                 name.c_str(), g_Folder.string().c_str(), kMaxItemBytes);
        return nullptr;
    }
    item.size = item.bytes.size() - 1;
    item.folder = g_Folder;
    if (g_Logged.insert(key).second)
        LogShimA(LogLevel::Info, "vehicle", "[VXT] serving '%s' (%zu bytes) from map folder '%s'",
                 name.c_str(), item.size, g_Folder.string().c_str());
    // Callers serve a held record before getting here, so any record still
    // present is unheld and can be replaced.
    Item& slot = g_Items[key];
    slot = std::move(item);
    return &slot;
}

} // namespace

void SetIndexCheck(IndexHasFn fn)
{
    std::lock_guard<std::recursive_mutex> lock(g_Mutex);
    g_IndexHas = fn;
}

void SetFolder(const std::filesystem::path& folder)
{
    std::lock_guard<std::recursive_mutex> lock(g_Mutex);
    if (folder == g_Folder)
        return;
    g_Folder = folder;
    for (auto it = g_Items.begin(); it != g_Items.end();)
    {
        if (it->second.refcount <= 0)
            it = g_Items.erase(it);
        else
            ++it;
    }
}

std::filesystem::path CurrentFolder()
{
    std::lock_guard<std::recursive_mutex> lock(g_Mutex);
    return g_Folder;
}

std::filesystem::path FindMapFolder(const std::vector<std::filesystem::path>& roots,
                                    const std::string& base)
{
    if (base.empty() || !IsBareName(base))
        return {};
    for (const auto& root : roots)
    {
        if (root.empty())
            continue;
        if (FileExists(root / (base + ".vxt")) && FileExists(root / (base + ".bzn")))
            return root;
    }
    return {};
}

bool CanServe(const char* name)
{
    if (!name || !name[0])
        return false;
    std::lock_guard<std::recursive_mutex> lock(g_Mutex);
    const std::string n(name);
    return CanServeLocked(n, Lower(n));
}

bool Acquire(const char* name, void*& data)
{
    data = nullptr;
    if (!name || !name[0])
        return false;
    std::lock_guard<std::recursive_mutex> lock(g_Mutex);
    const std::string n(name);
    const std::string key = Lower(n);
    auto it = g_Items.find(key);
    if (it != g_Items.end() && it->second.refcount > 0)
    {
        ++it->second.refcount;
        data = it->second.bytes.data();
        return true;
    }
    if (!CanServeLocked(n, key))
        return false;
    Item* item = LoadLocked(n, key);
    if (!item)
        return false;
    ++item->refcount;
    data = item->bytes.data();
    return true;
}

bool Size(const char* name, std::size_t& size)
{
    size = 0;
    if (!name || !name[0])
        return false;
    std::lock_guard<std::recursive_mutex> lock(g_Mutex);
    const std::string n(name);
    const std::string key = Lower(n);
    auto it = g_Items.find(key);
    if (it != g_Items.end() && it->second.refcount > 0)
    {
        size = it->second.size;
        return true;
    }
    if (!CanServeLocked(n, key))
        return false;
    Item* item = LoadLocked(n, key);
    if (!item)
        return false;
    size = item->size;
    return true;
}

bool Release(const char* name)
{
    if (!name || !name[0])
        return false;
    std::lock_guard<std::recursive_mutex> lock(g_Mutex);
    auto it = g_Items.find(Lower(name));
    if (it == g_Items.end() || it->second.refcount <= 0)
        return false;
    if (--it->second.refcount == 0 && it->second.folder != g_Folder)
        g_Items.erase(it);
    return true;
}

std::size_t CachedItemCount()
{
    std::lock_guard<std::recursive_mutex> lock(g_Mutex);
    return g_Items.size();
}

int Refcount(const char* name)
{
    std::lock_guard<std::recursive_mutex> lock(g_Mutex);
    auto it = g_Items.find(Lower(name ? name : ""));
    return it == g_Items.end() ? -1 : it->second.refcount;
}

void ResetForTesting()
{
    std::lock_guard<std::recursive_mutex> lock(g_Mutex);
    g_IndexHas = nullptr;
    g_Folder.clear();
    g_Items.clear();
    g_Logged.clear();
}

} // namespace BZROpenShim::MapFolderItems
