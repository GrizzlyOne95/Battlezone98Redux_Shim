/*
 * Entry: 00519764
 * Name: AISchedule_PostRun
 * Namespace: Global
 * Signature: void AISchedule_PostRun(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AISchedule_PostRun(void)

{
  AI_Close();
  PREREQ_Done();
  Build_Close();
  Units_Close();
  AI_SpecialForcesClose();
  AI_AIPClose();
  CleanObjectClasses();
  AOI::Clean();
  unitcycles = 0;
  loadedAIP = false;
  return;
}
