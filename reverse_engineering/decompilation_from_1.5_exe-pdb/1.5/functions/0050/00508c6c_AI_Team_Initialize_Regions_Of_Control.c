/*
 * Entry: 00508c6c
 * Name: AI_Team_Initialize_Regions_Of_Control
 * Namespace: Global
 * Signature: void AI_Team_Initialize_Regions_Of_Control(tag_team * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Team_Initialize_Regions_Of_Control(tag_team *param_1,int param_2,int param_3)

{
  tagTARGETS *ptVar1;
  tag_team *ptVar2;
  int **ppiVar3;
  int iVar4;
  
  ptVar2 = param_1;
  ppiVar3 = NR_Imatrix(0,param_3,0,param_2);
  (param_1->strategic_targets).base_location = ppiVar3;
  ppiVar3 = NR_Imatrix(0,param_3,0,param_2);
  ptVar1 = &param_1->strategic_targets;
  (param_1->strategic_targets).distance_from_base = ppiVar3;
  param_1 = (tag_team *)0x0;
  if (0 < ptVar1->grid_rows) {
    do {
      iVar4 = 0;
      if (0 < (ptVar2->strategic_targets).grid_columns) {
        do {
          (ptVar2->strategic_targets).base_location[(int)param_1][iVar4] = 0;
          (ptVar2->strategic_targets).distance_from_base[(int)param_1][iVar4] =
               (ptVar2->strategic_targets).grid_rows;
          iVar4 = iVar4 + 1;
        } while (iVar4 < (ptVar2->strategic_targets).grid_columns);
      }
      param_1 = (tag_team *)((int)&param_1->team_ID + 1);
    } while ((int)param_1 < (ptVar2->strategic_targets).grid_rows);
  }
  ppiVar3 = NR_Imatrix(0,param_3,0,param_2);
  (ptVar2->strategic_targets).scouted = ppiVar3;
  ppiVar3 = NR_Imatrix(0,param_3,0,param_2);
  (ptVar2->strategic_targets).distance_from_scouted = ppiVar3;
  param_1 = (tag_team *)0x0;
  if (0 < (ptVar2->strategic_targets).grid_rows) {
    do {
      iVar4 = 0;
      if (0 < (ptVar2->strategic_targets).grid_columns) {
        do {
          (ptVar2->strategic_targets).scouted[(int)param_1][iVar4] = 0;
          (ptVar2->strategic_targets).distance_from_scouted[(int)param_1][iVar4] =
               (ptVar2->strategic_targets).grid_rows;
          iVar4 = iVar4 + 1;
        } while (iVar4 < (ptVar2->strategic_targets).grid_columns);
      }
      param_1 = (tag_team *)((int)&param_1->team_ID + 1);
    } while ((int)param_1 < (ptVar2->strategic_targets).grid_rows);
  }
  return;
}
