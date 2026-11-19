#pragma once

#include <cstdint>

namespace BZROpenShim
{
    // ODF-driven `classLabel = "mru"` (mobile repair unit, Docs/MRU_CLASS.md):
    // a HoverCraftClass alias like `tracked`, with an [MruClass] section. Step
    // 1-2 of the plan in Docs/NIGHTINGALE_RESEARCH.md: the alias, the key
    // parse and a log-only command-menu probe (slots 7-9). It rides on the
    // Find label-compare hook (pond_class_label.cpp) and the HoverCraftClass
    // BuildClass/Build detours (tracked_vehicle_class.cpp), so it waits for
    // tracked to install. Kill switch: OPENSHIM_DISABLE_MRU_CLASS. Safe to
    // call from the normal deferred-hook retry loop.
    void InstallMruClassIfPossible();
    bool IsMruClassInstalled();

    // Find label-compare hook, after stock _stricmp reported a mismatch:
    // true aliases an `mru` ODF onto the registered `hover` descriptor and
    // arms the following HoverCraftClass::BuildClass.
    bool MatchMruClassLabel(const char* registeredLabel,
                            const char* odfLabel,
                            int (__cdecl* stricmp)(const char*, const char*));

    // HoverCraftClass::BuildClass detour: takes (clears) the flag the label
    // compare armed. Call before the stock constructor.
    bool TakeMruBuildPending();
    // HoverCraftClass::BuildClass detour, after the stock constructor, when
    // TakeMruBuildPending returned true: stamps "mru" and reads [MruClass].
    void ConfigureMruClass(void* objectClass, uint32_t odfNameLo, uint32_t odfNameHi);
    // HoverCraftClass::Build detour: gives an mru object with an [MruClass]
    // section the MRU vtable copy. No-op for any other class.
    void OnHoverObjectBuilt(void* objectClass, void* object);

    // rts_commands.cpp DispatchHook, once per selected commandable unit:
    // logs a unit-menu pick on an MRU object (single player, probe active)
    // and returns true when `mode` is one of its MRU entries (Drop Repair,
    // Drop Ammo, Deploy). Such a pick must not reach the stock dispatch.
    bool NoteMruMenuPick(void* object, uint32_t handle, int mode);
    // rts_commands.cpp ModeLabelDecide: true when `object` is an MRU object
    // whose menu shows the MRU entries now.
    bool IsMruMenuObject(void* object);
}
