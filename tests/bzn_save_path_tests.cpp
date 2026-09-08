#include "bzn_save_path.h"

#include <cstdlib>
#include <filesystem>
#include <iostream>

namespace
{
    int g_failures = 0;

    void Expect(bool condition, const char* message)
    {
        if (condition)
            return;
        ++g_failures;
        std::cerr << "FAIL: " << message << '\n';
    }
}

int main()
{
    using BZROpenShim::ChooseBznSavePath;

    const std::filesystem::path pilotAddon =
        L"C:/Program Files (x86)/GOG Galaxy/Games/Battlezone 98 Redux/addon";
    const auto pilotSource = pilotAddon / L"pilot/pilot.bzn";
    const auto pilotSave = ChooseBznSavePath(
        pilotAddon / L"pilot.bzn", pilotSource, pilotAddon);
    Expect(pilotSave.redirected && pilotSave.target == pilotSource,
        "pilot save returns to its addon subfolder");

    BZROpenShim::BznSourceRegistry registry;
    registry.Remember(pilotSource);
    registry.Remember(pilotSource);
    Expect(registry.Lookup(L"pilot.bzn") == pilotSource,
        "repeated reads preserve an unambiguous source");
    registry.Remember(pilotAddon / L"another/pilot.bzn");
    Expect(registry.Lookup(L"pilot.bzn").empty(),
        "duplicate basenames disable redirection");
    registry.Remember(pilotSource);
    Expect(registry.Lookup(L"pilot.bzn").empty(),
        "later resource scans cannot clear ambiguity");
    Expect(registry.Lookup(L"newname.bzn").empty(),
        "Save As to an unseen name has no source");

    BZROpenShim::BznSourceRegistry terrainRegistry;
    terrainRegistry.Remember(pilotSource);
    auto pilotTrn = pilotSource;
    pilotTrn.replace_extension(L".trn");
    Expect(terrainRegistry.LookupForSave(L"pilot.trn") == pilotTrn,
        "new TRN uses the folder of a same-named BZN source");
    terrainRegistry.Remember(pilotTrn);
    Expect(terrainRegistry.LookupForSave(L"pilot.trn") == pilotTrn,
        "observed TRN retains its exact source path");
    terrainRegistry.Remember(pilotAddon / L"another/pilot.trn");
    Expect(terrainRegistry.LookupForSave(L"pilot.trn").empty(),
        "ambiguous TRN cannot fall back to a unique BZN");

    const auto terrainDecision = ChooseBznSavePath(
        pilotAddon / L"pilot.trn", pilotTrn, pilotAddon);
    Expect(terrainDecision.redirected && terrainDecision.target == pilotTrn,
        "TRN save redirects to its observed subfolder");
    const auto terrainPlan = BZROpenShim::BuildEditorSavePlan(terrainDecision);
    Expect(terrainPlan.possibleWrites.size() == 3 &&
        terrainPlan.possibleWrites[0] == pilotTrn &&
        terrainPlan.possibleWrites[1].extension() == L".hg2" &&
        terrainPlan.possibleWrites[2].extension() == L".mat",
        "TRN plan includes exactly TRN, HG2 and MAT");
    const auto bznPlan = BZROpenShim::BuildEditorSavePlan(pilotSave);
    Expect(bznPlan.possibleWrites.size() == 4 && bznPlan.possibleWrites[0] == pilotSource,
        "BZN plan accounts for terrain writes before BZN serialization");
    for (const auto& path : bznPlan.possibleWrites)
        Expect(path.parent_path() == pilotSource.parent_path(), "all save targets share confirmed folder");

    bool confirmed = false;
    bool blocked = false;
    const bool allowed = BZROpenShim::ApproveEditorSave(bznPlan,
        [](const std::filesystem::path& path) {
            return path.extension() == L".mat" ? BZROpenShim::EditorSaveFileState::Blocked
                : BZROpenShim::EditorSaveFileState::Writable;
        },
        [&confirmed](const std::wstring&) { confirmed = true; return true; },
        [&blocked](const std::filesystem::path&) { blocked = true; });
    Expect(!allowed && blocked && !confirmed,
        "blocked companion rejects whole operation before overwrite approval");

    const std::filesystem::path addon = L"C:/Games/Battlezone 98 Redux/addon";
    const std::filesystem::path requested = addon / L"misn04.bzn";
    const std::filesystem::path source =
        L"C:/Games/Battlezone 98 Redux/mods/3686673790/misn04.bzn";

    auto decision = ChooseBznSavePath(requested, source, addon);
    Expect(decision.redirected, "matching loose map is redirected");
    Expect(decision.target == source, "redirect target is the remembered source");

    decision = ChooseBznSavePath(requested, addon / L"misn04.bzn", addon);
    Expect(!decision.redirected, "root-addon source keeps the stock destination");

    decision = ChooseBznSavePath(requested, source.parent_path() / L"misn05.bzn", addon);
    Expect(!decision.redirected, "different source filename is not selected");

    decision = ChooseBznSavePath(
        L"C:/Games/Battlezone 98 Redux/other/misn04.bzn", source, addon);
    Expect(!decision.redirected, "non-addon destination is not rewritten");

    decision = ChooseBznSavePath(
        requested,
        L"D:/Steam/steamapps/workshop/content/301650/3686673790/misn04.bzn",
        addon);
    Expect(!decision.redirected, "Steam Workshop content remains read-only");

    decision = ChooseBznSavePath(
        L"c:/games/battlezone 98 redux/ADDON/MISN04.BZN",
        L"C:/Games/Battlezone 98 Redux/Mods/Local/misn04.bzn",
        L"C:/Games/Battlezone 98 Redux/addon/");
    Expect(decision.redirected, "Windows path comparisons are case-insensitive");

    if (g_failures != 0)
        return EXIT_FAILURE;

    std::cout << "bzn_save_path_tests: PASS\n";
    return EXIT_SUCCESS;
}
