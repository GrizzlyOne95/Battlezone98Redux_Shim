// stock_enhanced_base_redirect.h
// BZR Open Shim - which stock base-material imports OpenShim Enhanced replaces
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Stock materials inherit their techniques through
// `import * from "BZBase.material"` / `import * from "BZTerrainBase.material"`.
// While OpenShim's Enhanced resources are ready, the import detour in
// ogre_script_import_cache.cpp reads OpenShim's generated copy instead: the
// stock base verbatim plus en-* techniques on OSE_* programs
// (scripts/generate_stock_enhanced_base.py). Pure policy, unit tested.

#pragma once

#include <cstddef>
#include <string_view>

namespace BZROpenShim::StockEnhancedBase
{
    // Kill switch: =1 keeps every stock base import stock.
    constexpr const char* kDisableSwitch = "OPENSHIM_DISABLE_ENHANCED_STOCK_BASE";

    // Kill switch for the terrain base only: =1 keeps BZTerrainBase.material
    // stock while vehicles stay Enhanced. On by default since the PSSM v2
    // manual-compare fix gave Enhanced terrain its shadows back.
    constexpr const char* kTerrainDisableSwitch = "OPENSHIM_DISABLE_ENHANCED_STOCK_TERRAIN";

    struct Redirect
    {
        const char* stockImport;
        const char* payloadFile;
        bool terrain; // also honours kTerrainDisableSwitch
    };

    constexpr Redirect kRedirects[] = {
        { "BZBase.material", "openshim_stock_bzbase.import", false },
        { "BZTerrainBase.material", "openshim_stock_bzterrainbase.import", true },
    };

    // Ogre's resource lookups are case-insensitive on Windows archives, and
    // stock files spell the import both ways.
    inline bool EqualsIgnoreCase(std::string_view a, std::string_view b) noexcept
    {
        if (a.size() != b.size())
            return false;
        for (size_t i = 0; i < a.size(); ++i)
        {
            char x = a[i];
            char y = b[i];
            if (x >= 'A' && x <= 'Z')
                x = static_cast<char>(x - 'A' + 'a');
            if (y >= 'A' && y <= 'Z')
                y = static_cast<char>(y - 'A' + 'a');
            if (x != y)
                return false;
        }
        return true;
    }

    // The OpenShim payload file that replaces `importName`, or nullptr when
    // the import is not a redirected stock base (CR_BZBase.material,
    // sprites.material, a path-qualified name, ...).
    inline const Redirect* RedirectForImport(std::string_view importName) noexcept
    {
        for (const Redirect& r : kRedirects)
        {
            if (EqualsIgnoreCase(importName, r.stockImport))
                return &r;
        }
        return nullptr;
    }

    inline const char* PayloadForImport(std::string_view importName) noexcept
    {
        const Redirect* r = RedirectForImport(importName);
        return r ? r->payloadFile : nullptr;
    }

    struct RedirectInputs
    {
        bool disabled = false;               // kill switch set
        bool terrain = false;                // Redirect::terrain
        bool terrainDisabled = false;        // kTerrainDisableSwitch set
        bool enhancedResourcesReady = false; // OpenShimEnhanced group registered and probed
        bool shadowedInCompilingGroup = false; // a mod ships its own base in this group
        bool payloadPresent = false;         // the .import file is in some resource group
    };

    // Redirect only an import that would otherwise fall through to the stock
    // base in General: a mod that ships its own BZBase.material keeps it, and
    // a missing payload or an unready Enhanced group leaves Ogre untouched
    // (the OSE_* programs the payload references would not resolve).
    inline bool ShouldRedirect(const RedirectInputs& in) noexcept
    {
        return !in.disabled && !(in.terrain && in.terrainDisabled) && in.enhancedResourcesReady &&
               !in.shadowedInCompilingGroup && in.payloadPresent;
    }
}
