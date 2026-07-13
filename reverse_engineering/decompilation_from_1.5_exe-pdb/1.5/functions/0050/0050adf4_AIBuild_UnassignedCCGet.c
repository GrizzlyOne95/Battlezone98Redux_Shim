/*
 * Entry: 0050adf4
 * Name: AIBuild_UnassignedCCGet
 * Namespace: Global
 * Signature: tagUNIT * AIBuild_UnassignedCCGet(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagUNIT * __cdecl AIBuild_UnassignedCCGet(tag_team *param_1)

{
  tagUNIT *ptVar1;
  
  ptVar1 = C_Linked_List_Return_Data_By_Number(&(param_1->aibuild).unassigned_construction_crews,0);
  if (ptVar1 == (tagUNIT *)0x0) {
    tlog_gdm("UnassignedCCGet team %d no cc\n");
  }
  else {
    tlog_gdm("UnassignedCCGet team %d cc %d\n");
  }
  return ptVar1;
}
