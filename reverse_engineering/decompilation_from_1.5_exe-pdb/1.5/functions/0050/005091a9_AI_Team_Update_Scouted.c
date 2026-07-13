/*
 * Entry: 005091a9
 * Name: AI_Team_Update_Scouted
 * Namespace: Global
 * Signature: void AI_Team_Update_Scouted(tag_team * param_1, int param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Team_Update_Scouted(tag_team *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = param_2;
  param_2 = (int)((param_2 - param_4) + (param_2 - param_4 >> 0x1f & 7U)) >> 3;
  if (param_2 < 0) {
    param_2 = 0;
  }
  iVar3 = (param_1->strategic_targets).grid_columns;
  iVar4 = (int)(iVar4 + param_4 + (iVar4 + param_4 >> 0x1f & 7U)) >> 3;
  if (iVar3 <= iVar4) {
    iVar4 = iVar3 + -1;
  }
  iVar3 = (int)((param_3 - param_4) + (param_3 - param_4 >> 0x1f & 7U)) >> 3;
  if (iVar3 < 0) {
    iVar3 = 0;
  }
  iVar1 = (param_1->strategic_targets).grid_rows;
  iVar2 = (int)(param_3 + param_4 + (param_3 + param_4 >> 0x1f & 7U)) >> 3;
  if (iVar1 <= iVar2) {
    iVar2 = iVar1 + -1;
  }
  for (; iVar1 = param_2, iVar3 <= iVar2; iVar3 = iVar3 + 1) {
    for (; iVar1 <= iVar4; iVar1 = iVar1 + 1) {
      (param_1->strategic_targets).scouted[iVar3][iVar1] = 1;
    }
  }
  return;
}
