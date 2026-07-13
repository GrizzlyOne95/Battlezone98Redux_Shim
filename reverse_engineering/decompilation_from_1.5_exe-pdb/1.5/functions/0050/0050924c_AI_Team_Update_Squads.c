/*
 * Entry: 0050924c
 * Name: AI_Team_Update_Squads
 * Namespace: Global
 * Signature: void AI_Team_Update_Squads(tag_strategy_map * param_1, tag_team * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Team_Update_Squads(tag_strategy_map *param_1,tag_team *param_2)

{
  void ***pppvVar1;
  int iVar2;
  tagUNIT *ptVar3;
  int iVar4;
  tag_squad *ptVar5;
  tag_c_list_cell *ptVar6;
  void ***pppvVar7;
  int iVar8;
  int local_8;
  
  pppvVar1 = param_2->gridcell_squads;
  iVar8 = 0;
  pppvVar7 = pppvVar1;
  if (0 < (param_2->strategic_targets).grid_rows) {
    do {
      iVar2 = 0;
      if (0 < (param_2->strategic_targets).grid_columns) {
        do {
          (*pppvVar7)[iVar2] = (void *)0x0;
          iVar2 = iVar2 + 1;
        } while (iVar2 < (param_2->strategic_targets).grid_columns);
      }
      iVar8 = iVar8 + 1;
      pppvVar7 = pppvVar7 + 1;
    } while (iVar8 < (param_2->strategic_targets).grid_rows);
  }
  local_8 = 0;
  if (0 < (param_2->my_units).count) {
    do {
      ptVar3 = C_Linked_List_Return_Data_By_Number(&param_2->my_units,local_8);
      iVar8 = (ptVar3->tilepos).y;
      iVar2 = param_1->gridside;
      iVar4 = (ptVar3->tilepos).x / iVar2;
      AI_Team_Update_Scouted(param_2,(ptVar3->tilepos).x,iVar8,(uint)ptVar3->type->seeingrange);
      Glue_Check_Unit(ptVar3);
      if ((ptVar3->ai).the_squad == (tag_squad *)0x0) {
        pppvVar7 = pppvVar1 + iVar8 / iVar2;
        if ((*pppvVar7)[iVar4] == (void *)0x0) {
          ptVar5 = Squad_New();
          (*pppvVar7)[iVar4] = ptVar5;
          *(int *)(*pppvVar7)[iVar4] = param_2->max_squad_ID;
          param_2->max_squad_ID = param_2->max_squad_ID + 1;
          *(tag_team **)((int)(*pppvVar7)[iVar4] + 0x40) = param_2;
          Squad_Check_Squad_List_Valid_Body(&param_2->my_squads,".\\Schedule\\ai_team.cpp",0x51e);
          ptVar6 = C_Linked_List_Add_Data(&param_2->my_squads,(*pppvVar7)[iVar4]);
          *(tag_c_list_cell **)((int)(*pppvVar7)[iVar4] + 0x44) = ptVar6;
          Squad_Check_Squad_List_Valid_Body(&param_2->my_squads,".\\Schedule\\ai_team.cpp",0x522);
        }
        ptVar5 = (*pppvVar7)[iVar4];
        Squad_Add_Unit(ptVar5,ptVar3,param_2);
        (ptVar3->ai).the_squad = ptVar5;
      }
      local_8 = local_8 + 1;
    } while (local_8 < (param_2->my_units).count);
  }
  return;
}
