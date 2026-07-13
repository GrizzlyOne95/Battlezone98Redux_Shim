/*
 * Entry: 0045dff2
 * Name: SetAIControl
 * Namespace: Global
 * Signature: void SetAIControl(int param_1, bool param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetAIControl(int param_1,bool param_2)

{
  AISchedule_SetAIControl(param_1,(uint)param_2);
  return;
}
