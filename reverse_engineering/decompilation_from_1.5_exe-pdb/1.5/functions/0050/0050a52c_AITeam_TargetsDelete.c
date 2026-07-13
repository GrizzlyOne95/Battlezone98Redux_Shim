/*
 * Entry: 0050a52c
 * Name: AITeam_TargetsDelete
 * Namespace: Global
 * Signature: void AITeam_TargetsDelete(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AITeam_TargetsDelete(tag_team *param_1)

{
  void ****ppppvVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = 0;
  if (0 < (param_1->strategic_targets).grid_rows) {
    iVar2 = (param_1->strategic_targets).grid_columns;
    do {
      iVar4 = 0;
      if (0 < iVar2) {
        do {
          Mapgrid_Goal::~Mapgrid_Goal((param_1->strategic_targets).grid[iVar3][iVar4]);
          iVar2 = (param_1->strategic_targets).grid_columns;
          iVar4 = iVar4 + 1;
        } while (iVar4 < iVar2);
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < (param_1->strategic_targets).grid_rows);
  }
  ppppvVar1 = &(param_1->strategic_targets).grid;
  free(***ppppvVar1);
  NR_Free_Ptr_Matrix(*ppppvVar1,0,(param_1->strategic_targets).grid_rows,0,
                     (param_1->strategic_targets).grid_columns);
  return;
}
