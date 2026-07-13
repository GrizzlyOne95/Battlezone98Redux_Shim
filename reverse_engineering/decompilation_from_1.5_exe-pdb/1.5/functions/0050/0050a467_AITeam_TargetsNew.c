/*
 * Entry: 0050a467
 * Name: AITeam_TargetsNew
 * Namespace: Global
 * Signature: void AITeam_TargetsNew(tag_team * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AITeam_TargetsNew(tag_team *param_1,int param_2,int param_3)

{
  int iVar1;
  tagTARGETS *ptVar2;
  tag_team *ptVar3;
  void ***pppvVar4;
  Mapgrid_Goal *pMVar5;
  int iVar6;
  
  ptVar3 = param_1;
  (param_1->strategic_targets).grid_columns = param_2;
  (param_1->strategic_targets).grid_rows = param_3;
  AI_Team_Planning_Status_Reset(param_1);
  pppvVar4 = NR_Ptr_Matrix(0,(param_1->strategic_targets).grid_rows,0,
                           (param_1->strategic_targets).grid_columns);
  (param_1->strategic_targets).grid = pppvVar4;
  param_2 = (int)calloc(1,(param_1->strategic_targets).grid_rows *
                          (param_1->strategic_targets).grid_columns * 0x88);
  ptVar2 = &param_1->strategic_targets;
  param_1 = (tag_team *)0x0;
  if (0 < ptVar2->grid_rows) {
    do {
      iVar6 = 0;
      if (0 < (ptVar3->strategic_targets).grid_columns) {
        do {
          iVar1 = param_2 + 0x88;
          if (param_2 == 0) {
            pMVar5 = (Mapgrid_Goal *)0x0;
          }
          else {
            pMVar5 = Mapgrid_Goal::Mapgrid_Goal
                               ((Mapgrid_Goal *)param_2,(int)param_1,iVar6,AI_map,ptVar3);
          }
          pMVar5->our_buildings = 0.0;
          (ptVar3->strategic_targets).grid[(int)param_1][iVar6] = pMVar5;
          pMVar5->rapid_defense_state = 0;
          pMVar5->neighbor_flags = '\0';
          pMVar5->_padding_ = 0;
          pMVar5->scripted_value = 0;
          pMVar5->min_scripted_force = 0;
          pMVar5->max_scripted_force = 0;
          (ptVar3->strategic_targets).grid[(int)param_1][iVar6] = pMVar5;
          iVar6 = iVar6 + 1;
          param_2 = iVar1;
        } while (iVar6 < (ptVar3->strategic_targets).grid_columns);
      }
      param_1 = (tag_team *)((int)&param_1->team_ID + 1);
    } while ((int)param_1 < (ptVar3->strategic_targets).grid_rows);
  }
  return;
}
