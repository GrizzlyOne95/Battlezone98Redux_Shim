#pragma once

namespace BZROpenShim
{
    // Shortens the options screen's resolution cycle list
    // (src/patches/resolution_list_filter.cpp). On by default:
    //
    //   [Graphics]
    //   ResolutionListFilter = 1
    //
    // OPENSHIM_DISABLE_RESOLUTION_LIST_FILTER=1 turns it off.
    void InitializeResolutionListFilter();
}
