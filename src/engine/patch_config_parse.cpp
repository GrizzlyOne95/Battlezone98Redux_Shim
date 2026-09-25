// patch_config_parse.cpp
// See patch_config_parse.h. Nothing here throws: every nlohmann access goes
// through find()/is_*() checks, and the hex parser is hand-rolled so a bad
// string is a false return rather than std::invalid_argument.

#include "patch_config_parse.h"

namespace BZROpenShim::PatchConfig
{
    namespace
    {
        bool IsSpace(char c)
        {
            return c == ' ' || c == '\t' || c == '\r' || c == '\n';
        }

        int HexDigit(char c)
        {
            if (c >= '0' && c <= '9') return c - '0';
            if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
            if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
            return -1;
        }

        // root[key] when root is an object holding that key, else nullptr.
        const nlohmann::json* Member(const nlohmann::json& node, const char* key)
        {
            if (!node.is_object()) return nullptr;
            const auto it = node.find(key);
            return it == node.end() ? nullptr : &*it;
        }

        bool ReadString(const nlohmann::json& node, const char* key, std::string& out, std::string& error)
        {
            const nlohmann::json* value = Member(node, key);
            if (!value) { error = std::string(key) + " is missing"; return false; }
            if (!value->is_string()) { error = std::string(key) + " is not a string"; return false; }
            out = value->get_ref<const std::string&>();
            return true;
        }

        bool ReadHex(const nlohmann::json& node, const char* key, uint32_t& out, std::string& error)
        {
            std::string text;
            if (!ReadString(node, key, text, error)) return false;
            if (!ParseHexAddress32(text, out))
            {
                error = std::string(key) + " '" + text + "' is not a 32-bit hex value";
                return false;
            }
            return true;
        }

        // A non-negative integer that fits 32 bits. Floats are rejected even
        // when integral, since 0x2F.0 in a hand-edited file is a typo.
        bool ReadU32(const nlohmann::json& node, const char* key, uint32_t& out, std::string& error)
        {
            const nlohmann::json* value = Member(node, key);
            if (!value) { error = std::string(key) + " is missing"; return false; }
            if (value->is_number_unsigned())
            {
                const uint64_t v = value->get<uint64_t>();
                if (v > 0xFFFFFFFFull) { error = std::string(key) + " does not fit 32 bits"; return false; }
                out = static_cast<uint32_t>(v);
                return true;
            }
            if (value->is_number_integer())
            {
                const int64_t v = value->get<int64_t>();
                if (v < 0) { error = std::string(key) + " is negative"; return false; }
                if (v > 0xFFFFFFFFll) { error = std::string(key) + " does not fit 32 bits"; return false; }
                out = static_cast<uint32_t>(v);
                return true;
            }
            error = std::string(key) + " is not an integer";
            return false;
        }

        // Optional boolean: absent leaves `out` untouched.
        bool ReadOptionalBool(const nlohmann::json& node, const char* key, bool& out, std::string& error)
        {
            const nlohmann::json* value = Member(node, key);
            if (!value) return true;
            if (!value->is_boolean()) { error = std::string(key) + " is not a boolean"; return false; }
            out = value->get<bool>();
            return true;
        }
    }

    bool ParseHexAddress32(const std::string& text, uint32_t& out)
    {
        const size_t n = text.size();
        size_t i = 0;
        while (i < n && IsSpace(text[i])) ++i;
        if (i + 1 < n && text[i] == '0' && (text[i + 1] == 'x' || text[i + 1] == 'X')) i += 2;

        uint64_t value = 0;
        size_t digits = 0;             // every digit consumed
        size_t significant = 0;        // digits after the leading zeros
        for (; i < n; ++i)
        {
            const int d = HexDigit(text[i]);
            if (d < 0) break;
            ++digits;
            if (significant > 0 || d != 0) ++significant;
            if (significant > 8) return false;
            value = (value << 4) | static_cast<uint64_t>(d);
        }
        if (digits == 0) return false;
        while (i < n && IsSpace(text[i])) ++i;
        if (i != n) return false;
        out = static_cast<uint32_t>(value);
        return true;
    }

    const nlohmann::json* ArraySection(const nlohmann::json& root, const char* key)
    {
        const nlohmann::json* section = Member(root, key);
        return (section && section->is_array()) ? section : nullptr;
    }

    std::string EntryName(const nlohmann::json& node)
    {
        const nlohmann::json* name = Member(node, "name");
        return (name && name->is_string()) ? name->get_ref<const std::string&>() : std::string();
    }

    LookupStatus ReadStaticPointer(const nlohmann::json& root, const std::string& name,
                                   uint32_t& out, std::string& error)
    {
        const nlohmann::json* table = Member(root, "static_pointers");
        if (!table) return LookupStatus::Absent;
        if (!table->is_array()) { error = "static_pointers is not an array"; return LookupStatus::Malformed; }
        for (const auto& entry : *table)
        {
            if (EntryName(entry) != name) continue;
            return ReadHex(entry, "address", out, error) ? LookupStatus::Found : LookupStatus::Malformed;
        }
        return LookupStatus::Absent;
    }

    LookupStatus ReadFeatureBool(const nlohmann::json& root, const std::string& name,
                                 bool& out, std::string& error)
    {
        if (const nlohmann::json* features = Member(root, "features"))
        {
            if (!features->is_object()) { error = "features is not an object"; return LookupStatus::Malformed; }
            if (const nlohmann::json* value = Member(*features, name.c_str()))
            {
                if (!value->is_boolean()) { error = "features." + name + " is not a boolean"; return LookupStatus::Malformed; }
                out = value->get<bool>();
                return LookupStatus::Found;
            }
        }
        if (const nlohmann::json* value = Member(root, name.c_str()))
        {
            if (!value->is_boolean()) { error = name + " is not a boolean"; return LookupStatus::Malformed; }
            out = value->get<bool>();
            return LookupStatus::Found;
        }
        return LookupStatus::Absent;
    }

    LookupStatus ReadSectionPattern(const nlohmann::json& root, const char* section,
                                    std::string& out, std::string& error)
    {
        const nlohmann::json* node = Member(root, section);
        if (!node) return LookupStatus::Absent;
        if (!node->is_object()) { error = std::string(section) + " is not an object"; return LookupStatus::Malformed; }
        return ReadString(*node, "pattern", out, error) ? LookupStatus::Found : LookupStatus::Malformed;
    }

    bool ParseScanEntry(const nlohmann::json& node, ScanEntry& out, std::string& error)
    {
        if (!node.is_object()) { error = "entry is not an object"; return false; }
        ScanEntry entry;
        if (!ReadString(node, "name", entry.name, error)) return false;
        if (!ReadString(node, "pattern", entry.pattern, error)) return false;
        if (!ReadU32(node, "offset", entry.offset, error)) return false;
        if (!ReadU32(node, "expected_size", entry.expectedSize, error)) return false;
        if (!ReadHex(node, "fallback", entry.fallback, error)) return false;
        if (!ReadOptionalBool(node, "require_unique", entry.requireUnique, error)) return false;
        out = std::move(entry);
        return true;
    }

    bool ParseGlobalEntry(const nlohmann::json& node, bool isSteam, GlobalEntry& out, std::string& error)
    {
        if (!node.is_object()) { error = "entry is not an object"; return false; }
        GlobalEntry entry;
        if (!ReadString(node, "name", entry.name, error)) return false;
        if (!ReadString(node, "expected_original", entry.expectedOriginal, error)) return false;

        // Same precedence the patcher always had: the distribution-specific
        // address when the entry carries one and it is non-zero, else the
        // shared one. A key that is present but unparsable fails the entry
        // rather than silently landing on the shared address.
        const char* specific = isSteam ? "fallback_steam" : "fallback_gog";
        uint32_t address = 0;
        if (Member(node, specific) && !ReadHex(node, specific, address, error)) return false;
        if (address == 0 && Member(node, "fallback") && !ReadHex(node, "fallback", address, error)) return false;
        entry.fallback = address;
        out = std::move(entry);
        return true;
    }
}
