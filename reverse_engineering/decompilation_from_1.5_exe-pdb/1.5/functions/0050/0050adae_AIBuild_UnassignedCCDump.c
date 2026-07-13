/*
 * Entry: 0050adae
 * Name: AIBuild_UnassignedCCDump
 * Namespace: Global
 * Signature: void AIBuild_UnassignedCCDump(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_UnassignedCCDump(tag_team *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (param_1->aibuild).unassigned_construction_crews.count;
  tlog_gdm("Unassigned CC\'s Team %d\n");
  iVar2 = 0;
  if (0 < iVar1) {
    do {
      C_Linked_List_Return_Data_By_Number(&(param_1->aibuild).unassigned_construction_crews,iVar2);
      tlog_gdm("  Unassigned #%d %08x\n");
      iVar2 = iVar2 + 1;
    } while (iVar2 < iVar1);
  }
  return;
}
