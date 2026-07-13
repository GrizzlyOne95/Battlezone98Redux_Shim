/*
 * Entry: 0050915a
 * Name: AI_Team_Add_Mapgrid_Goals
 * Namespace: Global
 * Signature: void AI_Team_Add_Mapgrid_Goals(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Team_Add_Mapgrid_Goals(tag_team *param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1->mapgrid_added == 0) {
    iVar1 = 0;
    if (0 < (param_1->strategic_targets).grid_rows) {
      do {
        iVar2 = 0;
        if (0 < (param_1->strategic_targets).grid_columns) {
          do {
            Scheduler::Add_Goal(param_1->scheduler,(param_1->strategic_targets).grid[iVar1][iVar2]);
            iVar2 = iVar2 + 1;
          } while (iVar2 < (param_1->strategic_targets).grid_columns);
        }
        iVar1 = iVar1 + 1;
      } while (iVar1 < (param_1->strategic_targets).grid_rows);
    }
    param_1->mapgrid_added = 1;
  }
  return;
}
