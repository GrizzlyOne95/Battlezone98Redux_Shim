#pragma once
// mp_any_nation.h -- "Any Nation" multiplayer lobby toggle (1.5 parity).
// See src/patches/mp_any_nation.cpp. Any Nation OFF only restricts players
// running OpenShim; stock clients still see the full pool. Lobby stays
// compatible either way.

namespace BZROpenShim { namespace AnyNation {

    // [Fixes] AnyNationToggle (default ON). When OFF nothing is installed.
    bool IsEnabled();

    // Needs MpFactionRestrict::InstallMpFactionRestrictIfPossible to have run.
    // Fails closed and logs when any address or byte check does not verify.
    void InstallAnyNationToggleIfPossible();

}} // namespace BZROpenShim::AnyNation
