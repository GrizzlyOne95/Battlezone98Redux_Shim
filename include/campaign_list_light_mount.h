// campaign_list_light_mount.h
// BZR Open Shim - Custom Campaigns list without a Modable rebuild.
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// The Custom Campaigns screen (0x20) mounts every addon campaign (mode 3) and
// then clears and re-initialises the Ogre "Modable" resource group, which
// recompiles ~1100 material scripts only to show a name, a .des text and a
// preview image. Backing out (mode 4) recompiles the base set again. This
// module keeps the mount but skips that clear+initialise pair on the list, and
// skips it again on Back when nothing else has touched the group since. The
// campaign mount itself (mode 0, at the campaign's own screen) is untouched,
// so the full rebuild now happens once, when a campaign is launched.
//
// Four JMP5 sites in scripts/patches.json, all-or-nothing:
//   Campaign List Light Mount List Store   mode-3 setter, mov [this+8C],3
//   Campaign List Light Mount List Gate    mode-3 setter, clear+initialise block
//   Campaign List Light Mount Main Store   mode-4 setter, mov [this+8C],4
//   Campaign List Light Mount Main Gate    mode-4 setter, clear+initialise block
// Disabled by [General] CampaignListLightMount = 0
// (OPENSHIM_DISABLE_CAMPAIGN_LIST_LIGHT_MOUNT).

#pragma once
#include <cstddef>
#include <cstdint>
#include <string>

namespace BZROpenShim
{
    namespace CampaignListLightMount
    {
        constexpr int kSiteCount = 4;

        bool IsPatchName(const char* name);

        // Validates the site (stolen bytes, IAT identity of both Ogre calls,
        // the "Modable" literal) and returns the detour to JMP5 to, with the
        // number of bytes the detour replaces. nullptr stands the site down.
        void* PrepareSite(const std::string& name, uint32_t address, size_t& stolenLen);
    }
}
