/*
 * Entry: 0045e004
 * Name: GetAIControl
 * Namespace: Global
 * Signature: bool GetAIControl(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl GetAIControl(int param_1)

{
  return teamdata[param_1].aicontrol != '\0';
}
