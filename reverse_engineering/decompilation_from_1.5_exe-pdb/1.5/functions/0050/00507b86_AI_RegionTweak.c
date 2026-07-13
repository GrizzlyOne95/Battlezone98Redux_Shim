/*
 * Entry: 00507b86
 * Name: AI_RegionTweak
 * Namespace: Global
 * Signature: void AI_RegionTweak(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_RegionTweak(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  tag_team *ptVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  tlog_gdm("AI_RegionTweak team %d, value %d (%d, %d) -> (%d, %d)\n");
  ptVar1 = AI_map->team[param_1];
  iVar4 = (int)(param_3 + (param_3 >> 0x1f & 7U)) >> 3;
  if (iVar4 < 0) {
    iVar4 = 0;
  }
  iVar5 = (int)(param_4 + (param_4 >> 0x1f & 7U)) >> 3;
  if (iVar5 < 0) {
    iVar5 = 0;
  }
  iVar2 = (ptVar1->strategic_targets).grid_columns;
  iVar6 = (int)(param_5 + (param_5 >> 0x1f & 7U)) >> 3;
  if (iVar2 < iVar6) {
    iVar6 = iVar2;
  }
  iVar2 = (ptVar1->strategic_targets).grid_rows;
  iVar3 = (int)(param_6 + (param_6 >> 0x1f & 7U)) >> 3;
  if (iVar2 < iVar3) {
    iVar3 = iVar2;
  }
  for (; iVar2 = iVar4, iVar5 <= iVar3; iVar5 = iVar5 + 1) {
    for (; iVar2 <= iVar6; iVar2 = iVar2 + 1) {
      *(int *)((int)(ptVar1->strategic_targets).grid[iVar5][iVar2] + 0x68) = param_2;
    }
  }
  AI_ScriptedValueDump(param_1);
  tlog_gdm("AI_RegionTweak Ends");
  return;
}
