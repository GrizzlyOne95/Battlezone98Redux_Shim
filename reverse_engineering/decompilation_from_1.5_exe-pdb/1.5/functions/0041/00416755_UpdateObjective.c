/*
 * Entry: 00416755
 * Name: UpdateObjective
 * Namespace: Global
 * Signature: void UpdateObjective(char * param_1, long param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UpdateObjective(char *param_1,long param_2,float param_3)

{
  InfoDisplay::UpdateObjective(&infoDisplay,param_1,param_2,param_3);
  return;
}
