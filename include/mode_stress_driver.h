#pragma once
// mode_stress_driver.h
// BZR Open Shim - unattended mode-transition stress driver
// (src/patches/mode_stress_driver.cpp). Release qualification only.
//
// Off unless OPENSHIM_MODE_STRESS_PLAN=<path> names a plan file (format in
// include/mode_stress_plan.h). When on, it chains mission and Instant Action
// loads in one process through the stock shell paths, returning to the main
// menu between steps, and logs [MODESTRESS] markers that
// reverse_engineering/Run-BZRModeStress.ps1 parses. Keep the line formats
// exact (Docs/RELEASE_QUALIFICATION.md, "Mode-transition stress").

namespace BZROpenShim
{
    // Reads OPENSHIM_MODE_STRESS_PLAN and parses the plan. No-op when unset.
    void InitializeModeStressDriver();

    // Main-thread seams (shell screen factory, world render queue update).
    // Installs the Ogre frame listener that drives the plan; one branch after.
    void ModeStressRenderTick();

    // Stops driving; logs when the plan did not finish.
    void ShutdownModeStressDriver();
}
