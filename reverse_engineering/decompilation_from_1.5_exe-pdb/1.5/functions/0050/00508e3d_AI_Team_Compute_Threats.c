/*
 * Entry: 00508e3d
 * Name: AI_Team_Compute_Threats
 * Namespace: Global
 * Signature: void AI_Team_Compute_Threats(tag_team * param_1, tag_strategy_map * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Team_Compute_Threats(tag_team *param_1,tag_strategy_map *param_2)

{
  int iVar1;
  void *pvVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 0;
  if (0 < (param_1->strategic_targets).grid_rows) {
    do {
      iVar4 = 0;
      if (0 < (param_1->strategic_targets).grid_columns) {
        do {
          pvVar2 = (param_1->strategic_targets).grid[iVar5][iVar4];
          iVar3 = param_1->AIP->ground_unit_threat * *(int *)((int)pvVar2 + 0x50);
          *(int *)((int)pvVar2 + 0x48) = iVar3;
          iVar1 = (param_1->strategic_targets).max_threat;
          if (iVar3 - iVar1 != 0 && iVar1 <= iVar3) {
            (param_1->strategic_targets).max_threat = iVar3;
          }
          iVar4 = iVar4 + 1;
        } while (iVar4 < (param_1->strategic_targets).grid_columns);
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < (param_1->strategic_targets).grid_rows);
  }
  return;
}
