/*
 * Entry: 00415e28
 * Name: StartCockpitTimer
 * Namespace: Global
 * Signature: void StartCockpitTimer(long param_1, long param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl StartCockpitTimer(long param_1,long param_2,long param_3)

{
  CockpitTimer::SetTimerDown(&cockpitTimer,param_1,param_2,param_3);
  CockpitTimer::ShowTimer(&cockpitTimer);
  return;
}
