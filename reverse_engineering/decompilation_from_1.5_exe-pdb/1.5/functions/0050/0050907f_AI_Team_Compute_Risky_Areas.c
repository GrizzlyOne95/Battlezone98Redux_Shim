/*
 * Entry: 0050907f
 * Name: AI_Team_Compute_Risky_Areas
 * Namespace: Global
 * Signature: void AI_Team_Compute_Risky_Areas(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Team_Compute_Risky_Areas(tag_team *param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int local_8;
  
  iVar3 = 0;
  local_8 = 0;
  if (0 < (param_1->strategic_targets).grid_rows) {
    do {
      iVar2 = 0;
      if (0 < (param_1->strategic_targets).grid_columns) {
        do {
          piVar1 = (param_1->strategic_targets).base_location[iVar3];
          if (*(float *)((int)(param_1->strategic_targets).grid[iVar3][iVar2] + 100) <= 0.0) {
            piVar1[iVar2] = 0;
          }
          else {
            piVar1[iVar2] = 1;
          }
          iVar2 = iVar2 + 1;
        } while (iVar2 < (param_1->strategic_targets).grid_columns);
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < (param_1->strategic_targets).grid_rows);
  }
  Grassfire_Xform((param_1->strategic_targets).base_location,
                  (param_1->strategic_targets).distance_from_base,1,0,0,8,
                  (param_1->strategic_targets).grid_rows,(param_1->strategic_targets).grid_columns);
  iVar3 = 0;
  if (0 < (param_1->strategic_targets).grid_rows) {
    do {
      if (0 < (param_1->strategic_targets).grid_columns) {
        piVar1 = (param_1->strategic_targets).distance_from_base[iVar3];
        iVar2 = (param_1->strategic_targets).grid_columns;
        do {
          if (local_8 < *piVar1) {
            local_8 = *piVar1;
          }
          piVar1 = piVar1 + 1;
          iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < (param_1->strategic_targets).grid_rows);
  }
  (param_1->strategic_targets).biggest_distance_from_base = local_8;
  return;
}
