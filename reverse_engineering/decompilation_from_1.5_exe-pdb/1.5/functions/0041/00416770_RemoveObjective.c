/*
 * Entry: 00416770
 * Name: RemoveObjective
 * Namespace: Global
 * Signature: void RemoveObjective(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl RemoveObjective(char *param_1)

{
  InfoDisplay::RemoveObjective(&infoDisplay,param_1);
  return;
}
