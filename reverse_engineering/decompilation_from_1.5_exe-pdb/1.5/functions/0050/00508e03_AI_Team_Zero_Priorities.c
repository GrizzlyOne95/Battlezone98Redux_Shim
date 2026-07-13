/*
 * Entry: 00508e03
 * Name: AI_Team_Zero_Priorities
 * Namespace: Global
 * Signature: void AI_Team_Zero_Priorities(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Team_Zero_Priorities(tag_team *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  if (0 < (param_1->strategic_targets).grid_rows) {
    iVar1 = (param_1->strategic_targets).grid_columns;
    do {
      iVar3 = 0;
      if (0 < iVar1) {
        do {
          Mapgrid_Goal::Clear_Goal((param_1->strategic_targets).grid[iVar2][iVar3]);
          iVar1 = (param_1->strategic_targets).grid_columns;
          iVar3 = iVar3 + 1;
        } while (iVar3 < iVar1);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < (param_1->strategic_targets).grid_rows);
  }
  return;
}
