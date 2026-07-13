/*
 * Entry: 0050ae8c
 * Name: AIBuild_UnassignedCCInit
 * Namespace: Global
 * Signature: void AIBuild_UnassignedCCInit(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_UnassignedCCInit(tag_team *param_1)

{
  C_Linked_List_Init(&(param_1->aibuild).unassigned_construction_crews);
  return;
}
