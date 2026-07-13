/*
 * Entry: 00508ed3
 * Name: AI_Team_Relax_Threats
 * Namespace: Global
 * Signature: void AI_Team_Relax_Threats(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Team_Relax_Threats(tag_team *param_1)

{
  void *pvVar1;
  Mapgrid_Goal *pMVar2;
  bool bVar3;
  tag_team *ptVar4;
  undefined1 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int local_10;
  int local_c;
  
  ptVar4 = param_1;
  iVar8 = 0;
  if (0 < (param_1->strategic_targets).grid_rows) {
    iVar6 = (param_1->strategic_targets).grid_columns;
    do {
      iVar7 = 0;
      if (0 < iVar6) {
        do {
          pvVar1 = (param_1->strategic_targets).grid[iVar8][iVar7];
          *(undefined4 *)((int)pvVar1 + 0x4c) = *(undefined4 *)((int)pvVar1 + 0x48);
          iVar6 = (param_1->strategic_targets).grid_columns;
          iVar7 = iVar7 + 1;
        } while (iVar7 < iVar6);
      }
      iVar8 = iVar8 + 1;
    } while (iVar8 < (param_1->strategic_targets).grid_rows);
  }
  local_10 = 0;
  if (0 < param_1->AIP->relaxation_cycles) {
    do {
      param_1 = (tag_team *)0x0;
      if (0 < (ptVar4->strategic_targets).grid_rows) {
        iVar8 = (ptVar4->strategic_targets).grid_columns;
        do {
          if (0 < iVar8) {
            puVar5 = (undefined1 *)((int)&param_1[-1].gridcell_squads + 3);
            local_c = 0;
            iVar6 = 1;
            do {
              pMVar2 = *(Mapgrid_Goal **)
                        (local_c + (int)(ptVar4->strategic_targets).grid[(int)param_1]);
              AI_Team_Relax_Two_Cells(ptVar4,pMVar2,(int)puVar5,iVar6 + -1,1.0);
              AI_Team_Relax_Two_Cells
                        (ptVar4,pMVar2,(int)((int)&param_1->team_ID + 1),iVar6 + -1,1.0);
              AI_Team_Relax_Two_Cells(ptVar4,pMVar2,(int)param_1,iVar6 + -2,1.0);
              AI_Team_Relax_Two_Cells(ptVar4,pMVar2,(int)param_1,iVar6,1.0);
              AI_Team_Relax_Two_Cells(ptVar4,pMVar2,(int)puVar5,iVar6 + -2,1.41);
              AI_Team_Relax_Two_Cells(ptVar4,pMVar2,(int)puVar5,iVar6,1.41);
              AI_Team_Relax_Two_Cells
                        (ptVar4,pMVar2,(int)((int)&param_1->team_ID + 1),iVar6 + -2,1.41);
              AI_Team_Relax_Two_Cells(ptVar4,pMVar2,(int)((int)&param_1->team_ID + 1),iVar6,1.41);
              local_c = local_c + 4;
              iVar8 = (ptVar4->strategic_targets).grid_columns;
              bVar3 = iVar6 < iVar8;
              iVar6 = iVar6 + 1;
            } while (bVar3);
          }
          param_1 = (tag_team *)((int)&param_1->team_ID + 1);
        } while ((int)param_1 < (ptVar4->strategic_targets).grid_rows);
      }
      iVar8 = 0;
      if (0 < (ptVar4->strategic_targets).grid_rows) {
        iVar6 = (ptVar4->strategic_targets).grid_columns;
        do {
          iVar7 = 0;
          if (0 < iVar6) {
            do {
              pvVar1 = (ptVar4->strategic_targets).grid[iVar8][iVar7];
              *(undefined4 *)((int)pvVar1 + 0x48) = *(undefined4 *)((int)pvVar1 + 0x4c);
              iVar6 = (ptVar4->strategic_targets).grid_columns;
              iVar7 = iVar7 + 1;
            } while (iVar7 < iVar6);
          }
          iVar8 = iVar8 + 1;
        } while (iVar8 < (ptVar4->strategic_targets).grid_rows);
      }
      local_10 = local_10 + 1;
    } while (local_10 < ptVar4->AIP->relaxation_cycles);
  }
  return;
}
