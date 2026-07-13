/*
 * Entry: 0050ae61
 * Name: AIBuild_UnassignedCCRemove
 * Namespace: Global
 * Signature: void AIBuild_UnassignedCCRemove(tag_team * param_1, tagUNIT * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_UnassignedCCRemove(tag_team *param_1,tagUNIT *param_2)

{
  tlog_gdm("AIBuild_UnassignedCCRemove team %d CC %d\n");
  C_Linked_List_Remove_Data(&(param_1->aibuild).unassigned_construction_crews,param_2);
  return;
}
