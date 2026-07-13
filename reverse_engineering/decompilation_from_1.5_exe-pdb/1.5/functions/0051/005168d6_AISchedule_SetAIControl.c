/*
 * Entry: 005168d6
 * Name: AISchedule_SetAIControl
 * Namespace: Global
 * Signature: void AISchedule_SetAIControl(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AISchedule_SetAIControl(int param_1,int param_2)

{
  teamdata[param_1].aicontrol = (uchar)param_2;
  return;
}
