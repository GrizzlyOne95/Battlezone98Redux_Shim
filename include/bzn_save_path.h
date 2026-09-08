// bzn_save_path.h
// BZR Open Shim - World Builder loose-map save routing policy
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#pragma once

#include <algorithm>
#include <cwctype>
#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

namespace BZROpenShim
{
    struct BznSavePathDecision
    {
        std::filesystem::path target;
        bool redirected = false;
    };

    inline std::wstring NormalizeBznPathForComparison(const std::filesystem::path& path)
    {
        std::wstring value = path.lexically_normal().wstring();
        std::transform(value.begin(), value.end(), value.begin(), [](wchar_t ch)
        {
            if (ch == L'\\')
                return L'/';
            return static_cast<wchar_t>(std::towlower(ch));
        });
        while (value.size() > 1 && value.back() == L'/')
            value.pop_back();
        return value;
    }

    inline bool IsBznFilePath(const std::filesystem::path& path)
    {
        std::wstring extension = path.extension().wstring();
        std::transform(extension.begin(), extension.end(), extension.begin(), [](wchar_t ch)
        {
            return static_cast<wchar_t>(std::towlower(ch));
        });
        return extension == L".bzn";
    }

    inline bool IsSteamWorkshopContentPath(const std::filesystem::path& path)
    {
        const std::wstring normalized = NormalizeBznPathForComparison(path);
        return normalized.find(L"/steamapps/workshop/content/301650/") != std::wstring::npos;
    }

    inline bool IsEditorSourcePath(const std::filesystem::path& path)
    {
        const auto extension = NormalizeBznPathForComparison(path.extension());
        return extension == L".bzn" || extension == L".trn";
    }

    // File opens include resource scans, not just mission loads. Never let
    // enumeration order choose which of two same-named files to overwrite.
    // An empty value is a sticky ambiguity marker for this process lifetime.
    class BznSourceRegistry
    {
    public:
        void Remember(const std::filesystem::path& source)
        {
            if (!IsEditorSourcePath(source))
                return;
            const auto key = NormalizeBznPathForComparison(source.filename());
            const auto [it, inserted] = sources_.emplace(key, source);
            if (!inserted && NormalizeBznPathForComparison(it->second) !=
                NormalizeBznPathForComparison(source))
                it->second.clear();
        }

        std::filesystem::path Lookup(const std::filesystem::path& requested) const
        {
            const auto it = sources_.find(
                NormalizeBznPathForComparison(requested.filename()));
            return it == sources_.end() ? std::filesystem::path{} : it->second;
        }

        std::filesystem::path LookupForSave(const std::filesystem::path& requested) const
        {
            const auto it = sources_.find(
                NormalizeBznPathForComparison(requested.filename()));
            // An ambiguous exact name must not fall back to another extension.
            if (it != sources_.end())
                return it->second;
            auto sibling = requested;
            sibling.replace_extension(IsBznFilePath(requested) ? L".trn" : L".bzn");
            auto source = Lookup(sibling);
            if (!source.empty())
                source.replace_extension(requested.extension());
            return source;
        }

    private:
        std::unordered_map<std::wstring, std::filesystem::path> sources_;
    };

    inline BznSavePathDecision ChooseBznSavePath(
        const std::filesystem::path& requested,
        const std::filesystem::path& rememberedSource,
        const std::filesystem::path& rootAddon)
    {
        BznSavePathDecision decision{ requested, false };
        if (requested.empty() || rememberedSource.empty() || rootAddon.empty())
            return decision;
        if (!IsEditorSourcePath(requested) || !IsEditorSourcePath(rememberedSource))
            return decision;
        if (NormalizeBznPathForComparison(requested.parent_path()) !=
            NormalizeBznPathForComparison(rootAddon))
        {
            return decision;
        }
        if (NormalizeBznPathForComparison(requested.filename()) !=
            NormalizeBznPathForComparison(rememberedSource.filename()))
        {
            return decision;
        }
        if (NormalizeBznPathForComparison(requested) ==
            NormalizeBznPathForComparison(rememberedSource))
        {
            return decision;
        }
        if (IsSteamWorkshopContentPath(rememberedSource))
            return decision;

        decision.target = rememberedSource;
        decision.redirected = true;
        return decision;
    }

    struct EditorSavePlan
    {
        std::filesystem::path target;
        bool redirected = false;
        std::vector<std::filesystem::path> possibleWrites;
    };

    inline EditorSavePlan BuildEditorSavePlan(const BznSavePathDecision& decision)
    {
        EditorSavePlan plan{ decision.target, decision.redirected, {} };
        if (!IsEditorSourcePath(plan.target))
            return plan;
        if (IsBznFilePath(plan.target))
            plan.possibleWrites.push_back(plan.target);
        // SaveGame invokes SaveZoneFiles first for dirty BZN terrain and
        // unconditionally for TRN. SaveZoneFiles derives these three siblings
        // from the selected filename. List them conservatively for BZN saves.
        for (const auto* extension : { L".trn", L".hg2", L".mat" })
        {
            auto companion = plan.target;
            companion.replace_extension(extension);
            plan.possibleWrites.push_back(companion);
        }
        return plan;
    }

    enum class EditorSaveFileState { Missing, Writable, Blocked };

    inline std::wstring EditorSaveConfirmationText(
        const EditorSavePlan& plan,
        const std::vector<std::filesystem::path>& existing)
    {
        std::wstring message = L"Save to:\n" + plan.target.wstring();
        if (!existing.empty())
        {
            message += L"\n\nExisting files that may be overwritten:\n";
            for (const auto& path : existing)
                message += L"\n" + path.wstring();
        }
        message += L"\n\nContinue with this save?";
        return message;
    }

    // Called after native filename selection but BEFORE returning success to
    // PromptSaveMission. No serializer, terrain state mutation or file write
    // may happen until this returns true. Callbacks make cancellation testable.
    template<class Inspect, class Confirm, class ReportBlocked>
    bool ApproveEditorSave(const EditorSavePlan& plan, Inspect inspect,
        Confirm confirm, ReportBlocked reportBlocked)
    {
        std::vector<std::filesystem::path> existing;
        for (const auto& path : plan.possibleWrites)
        {
            const auto state = inspect(path);
            if (state == EditorSaveFileState::Blocked)
            {
                reportBlocked(path);
                return false;
            }
            if (state == EditorSaveFileState::Writable)
                existing.push_back(path);
        }
        return (!plan.redirected && existing.empty()) ||
            confirm(EditorSaveConfirmationText(plan, existing));
    }
}
