/*
 * Entry: 00415e0d
 * Name: AddObjective
 * Namespace: Global
 * Signature: void AddObjective(char * param_1, long param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AddObjective(char *param_1,long param_2,float param_3)

{
  InfoDisplay::AddObjective(&infoDisplay,param_1,param_2,param_3);
  return;
}
