#include "campaign_manifest_id.h"
#include <cstdlib>
#include <iostream>
#include <string>

int main()
{
    using BZROpenShim::CampaignManifestId::ValidId;
    const auto valid = [](const std::string& s) { return ValidId(s.data(), s.size()); };
    // IDs must distinguish modes while leaving each package's existing folder
    // key available for its unannotated Commander campaign.
    if (!valid("bz64pilot") || !valid("BZ64_Pilot-2") || !valid(std::string(63, 'x')))
        return EXIT_FAILURE;
    for (const auto* s : {"", ".", "..", "../bz64port", "bz64port/pilot", "bz64port\\pilot",
                         "pilot mode", "pilot.ini", "_pilot", "-pilot", "pilot:1"})
        if (valid(s)) { std::cerr << "unsafe ID accepted: " << s << '\n'; return EXIT_FAILURE; }
    if (ValidId(nullptr, 1) || valid(std::string(64, 'x')) || valid(std::string("pilot\0other", 11)) ||
        valid(std::string("pilot\x80", 6))) return EXIT_FAILURE;
    std::cout << "campaign manifest ID policy passed\n";
    return EXIT_SUCCESS;
}
