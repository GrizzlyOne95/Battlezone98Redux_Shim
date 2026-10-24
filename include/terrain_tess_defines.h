#pragma once
#include <cctype>
#include <string>

namespace BZROpenShim::TerrainTess
{
    // True when name occurs in source as a whole identifier.
    inline bool MentionsIdentifier(const std::string& source, const std::string& name)
    {
        const auto word = [](char c) { return std::isalnum(static_cast<unsigned char>(c)) || c == '_'; };
        for (size_t at = source.find(name); at != std::string::npos; at = source.find(name, at + 1))
            if ((at == 0 || !word(source[at - 1])) &&
                (at + name.size() == source.size() || !word(source[at + name.size()])))
                return true;
        return false;
    }

    // Keeps only the pass defines (Ogre's comma or semicolon list) whose names
    // the hull/domain source mentions. Terrain passes differ in pixel-stage
    // switches the tessellation stages never read, and every distinct define
    // string costs a hull and domain compile on the game thread at map load;
    // a name the source never mentions cannot change its bytecode.
    inline std::string RelevantDefines(const std::string& defines, const std::string& source)
    {
        std::string kept;
        for (size_t start = 0; start <= defines.size();)
        {
            size_t end = defines.find_first_of(",;", start);
            if (end == std::string::npos) end = defines.size();
            std::string token = defines.substr(start, end - start);
            const size_t first = token.find_first_not_of(" \t");
            token = first == std::string::npos ? std::string() : token.substr(first, token.find_last_not_of(" \t") - first + 1);
            std::string name = token.substr(0, token.find('='));
            name.erase(name.find_last_not_of(" \t") + 1);
            if (!name.empty() && MentionsIdentifier(source, name))
                kept += (kept.empty() ? "" : ",") + token;
            start = end + 1;
        }
        return kept;
    }
}
