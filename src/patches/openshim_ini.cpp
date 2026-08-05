#include "openshim_ini.h"

#include <cctype>
#include <cstring>
#include <fstream>

namespace BZROpenShim
{
    bool IniLineIsSectionHeader(const std::string& line, std::string& outName)
    {
        size_t begin = line.find_first_not_of(" \t");
        if (begin == std::string::npos || line[begin] != '[')
            return false;
        const size_t end = line.find(']', begin + 1);
        if (end == std::string::npos)
            return false;
        outName = line.substr(begin + 1, end - begin - 1);
        return true;
    }

    bool IniLineMatchesKey(const std::string& line, const char* key)
    {
        size_t begin = line.find_first_not_of(" \t");
        if (begin == std::string::npos)
            return false;
        const char first = line[begin];
        if (first == ';' || first == '#' || first == '[')
            return false;
        const size_t equals = line.find('=', begin);
        if (equals == std::string::npos)
            return false;
        size_t keyEnd = equals;
        while (keyEnd > begin &&
               std::isspace(static_cast<unsigned char>(line[keyEnd - 1])))
            --keyEnd;
        const size_t keyLen = keyEnd - begin;
        return keyLen == std::strlen(key) &&
               _strnicmp(line.c_str() + begin, key, keyLen) == 0;
    }

    void UpdateIniDocumentValueLossless(std::vector<std::string>& lines,
                                        const char* section,
                                        const char* key,
                                        const char* const* altKeys,
                                        size_t altKeyCount,
                                        const char* value)
    {
        const std::string newLine = std::string(key) + " = " + value;

        // Locate the section and the key line (canonical name first, then
        // any legacy alias) within it.
        size_t sectionStart = std::string::npos;
        size_t sectionEnd = lines.size();  // one past last section line
        std::string headerName;
        for (size_t index = 0; index < lines.size(); ++index)
        {
            if (!IniLineIsSectionHeader(lines[index], headerName))
                continue;
            if (sectionStart != std::string::npos)
            {
                sectionEnd = index;
                break;
            }
            if (_stricmp(headerName.c_str(), section) == 0)
                sectionStart = index;
        }

        if (sectionStart == std::string::npos)
        {
            if (!lines.empty() && !lines.back().empty())
                lines.push_back("");
            lines.push_back(std::string("[") + section + "]");
            lines.push_back(newLine);
            return;
        }

        size_t keyLine = std::string::npos;
        for (size_t index = sectionStart + 1; index < sectionEnd; ++index)
        {
            if (IniLineMatchesKey(lines[index], key))
            {
                keyLine = index;
                break;
            }
        }
        for (size_t alt = 0; keyLine == std::string::npos && alt < altKeyCount; ++alt)
        {
            for (size_t index = sectionStart + 1; index < sectionEnd; ++index)
            {
                if (IniLineMatchesKey(lines[index], altKeys[alt]))
                {
                    keyLine = index;
                    break;
                }
            }
        }

        if (keyLine != std::string::npos)
        {
            lines[keyLine] = newLine;
            return;
        }

        size_t insertAt = sectionEnd;
        while (insertAt > sectionStart + 1 && lines[insertAt - 1].empty())
            --insertAt;
        lines.insert(lines.begin() + insertAt, newLine);
    }

    std::vector<std::string> ReadTextFileLines(const std::filesystem::path& path)
    {
        std::vector<std::string> lines;
        std::ifstream file(path);
        if (!file)
            return lines;

        std::string line;
        while (std::getline(file, line))
        {
            while (!line.empty() && (line.back() == '\r' || line.back() == '\n'))
                line.pop_back();
            lines.push_back(line);
        }
        return lines;
    }
}
