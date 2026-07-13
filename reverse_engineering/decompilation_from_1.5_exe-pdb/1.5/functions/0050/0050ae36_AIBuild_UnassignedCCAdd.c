/*
 * Entry: 0050ae36
 * Name: AIBuild_UnassignedCCAdd
 * Namespace: Global
 * Signature: void AIBuild_UnassignedCCAdd(tag_team * param_1, tagUNIT * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_UnassignedCCAdd(tag_team *param_1,tagUNIT *param_2)

{
  tlog_gdm("AIBuild_UnassignedCCAdd team %d CC %d\n");
  C_Linked_List_Add_Data(&(param_1->aibuild).unassigned_construction_crews,param_2);
  return;
}
