/*
 * Entry: 0041677f
 * Name: StartCockpitTimerUp
 * Namespace: Global
 * Signature: void StartCockpitTimerUp(long param_1, long param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl StartCockpitTimerUp(long param_1,long param_2,long param_3)

{
  CockpitTimer::SetTimerUp(&cockpitTimer,param_1,param_2,param_3);
  CockpitTimer::ShowTimer(&cockpitTimer);
  return;
}
