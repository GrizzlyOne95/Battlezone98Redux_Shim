#pragma once

#include <cstdint>

namespace BZROpenShim
{
    namespace LcbenchSafetyPolicy
    {
        // Person::Simulate uses the selected-weapon mask only to classify the
        // current on-foot animation. A missing carrier therefore has the same
        // safe local meaning as "no weapon selected": mask zero. The caller
        // continues through the rest of Person::Simulate unchanged.
        inline uint32_t SelectedMaskForMissingCarrier()
        {
            return 0u;
        }

        // Preserve the stock EnemyP result everywhere except the one patched
        // ControlPanel target-list call. Enabling the option adds only team 0
        // to the list of explicit player-order targets; it does not redefine
        // diplomacy, autonomous acquisition, damage, or EnemyP globally.
        inline bool AllowExplicitAttackTarget(bool stockEnemy,
                                              int targetTeam,
                                              bool allowNeutralAttackOrders)
        {
            return stockEnemy || (allowNeutralAttackOrders && targetTeam == 0);
        }
    }
}
