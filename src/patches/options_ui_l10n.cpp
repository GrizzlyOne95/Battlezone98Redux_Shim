#include "options_ui_l10n.h"

#include <array>

namespace BZROpenShim::OptionsL10n
{
    const char* const kLanguageColumnNames[kLanguageCount] = {
        "English", "French", "German", "Spanish", "Italian", "Portuguese", "Russian",
    };

    namespace
    {
        std::vector<std::string_view> SplitFields(std::string_view line)
        {
            std::vector<std::string_view> fields;
            size_t start = 0;
            for (;;)
            {
                const size_t tilde = line.find('~', start);
                fields.push_back(line.substr(start, tilde == std::string_view::npos ? std::string_view::npos
                                                                                     : tilde - start));
                if (tilde == std::string_view::npos)
                    return fields;
                start = tilde + 1;
            }
        }
    }

    bool Table::Parse(std::string_view text, std::string* error)
    {
        m_Rows.clear();
        m_Order.clear();

        // A UTF-8 BOM would glue itself to the first key; the format is ANSI.
        if (text.size() >= 3 && static_cast<unsigned char>(text[0]) == 0xEF &&
            static_cast<unsigned char>(text[1]) == 0xBB && static_cast<unsigned char>(text[2]) == 0xBF)
            text.remove_prefix(3);

        // column index in the file for each Language - 1; npos when absent
        std::array<size_t, kLanguageCount> columnFor;
        columnFor.fill(std::string_view::npos);
        bool haveHeader = false;

        size_t start = 0;
        while (start < text.size())
        {
            size_t end = text.find('\n', start);
            if (end == std::string_view::npos)
                end = text.size();
            std::string_view line = text.substr(start, end - start);
            start = end + 1;
            if (!line.empty() && line.back() == '\r')
                line.remove_suffix(1);
            // The engine's loader skips the same lines.
            if (line.empty() || line.front() == '~')
                continue;

            const auto fields = SplitFields(line);
            if (!haveHeader)
            {
                haveHeader = true;
                for (size_t column = 1; column < fields.size(); ++column)
                {
                    for (int language = 0; language < kLanguageCount; ++language)
                    {
                        if (fields[column] == kLanguageColumnNames[language])
                            columnFor[language] = column;
                    }
                }
                if (fields.empty() || fields[0] != "Key" || columnFor[English - 1] == std::string_view::npos)
                {
                    if (error)
                        *error = "header must start with Key~English";
                    return false;
                }
                continue;
            }

            std::vector<std::string> cells(kLanguageCount);
            for (int language = 0; language < kLanguageCount; ++language)
            {
                const size_t column = columnFor[language];
                if (column != std::string_view::npos && column < fields.size())
                    cells[language] = std::string(fields[column]);
            }
            std::string key(fields[0]);
            m_Order.push_back(key);
            m_Rows[std::move(key)] = std::move(cells);
        }

        if (!haveHeader)
        {
            if (error)
                *error = "empty table";
            return false;
        }
        return true;
    }

    const char* Table::Find(std::string_view key, int language) const
    {
        if (language < 1 || language > kLanguageCount)
            return nullptr;
        const auto row = m_Rows.find(std::string(key));
        if (row == m_Rows.end())
            return nullptr;
        const std::string& cell = row->second[language - 1];
        return cell.empty() ? nullptr : cell.c_str();
    }

    const char* Pick(const Table& table, int language, const std::string* keys, size_t keyCount,
                     const char* english)
    {
        if (language <= English || language > kLanguageCount)
            return english;
        for (size_t i = 0; i < keyCount; ++i)
        {
            if (const char* text = table.Find(keys[i], language))
                return text;
        }
        return english;
    }

    std::string Slug(const char* text)
    {
        std::string slug;
        for (const char* p = text; p && *p; ++p)
        {
            const char ch = *p;
            if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9'))
                slug.push_back(ch);
        }
        return slug;
    }

    static std::string RowId(const char* iniKey, const char* label)
    {
        return (iniKey && *iniKey) ? std::string(iniKey) : Slug(label);
    }

    std::string RowKey(const char* iniKey, const char* label, const char* field)
    {
        return "openshim_opt:" + RowId(iniKey, label) + ":" + field;
    }

    std::string RowValueKey(const char* iniKey, const char* label, const char* value)
    {
        return "openshim_opt:" + RowId(iniKey, label) + ":value:" + (value ? value : "");
    }

    std::string CommonValueKey(const char* english)
    {
        return std::string("openshim_value:") + (english ? english : "");
    }

    std::string CategoryKey(const char* name, const char* field)
    {
        return "openshim_cat:" + Slug(name) + ":" + field;
    }
}
