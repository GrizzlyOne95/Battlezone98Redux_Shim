/*
 * Entry: 0050ae9d
 * Name: AIBuild_UnassignedCCClose
 * Namespace: Global
 * Signature: void AIBuild_UnassignedCCClose(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_UnassignedCCClose(tag_team *param_1)

{
  C_Linked_List_Empty(&(param_1->aibuild).unassigned_construction_crews);
  return;
}
