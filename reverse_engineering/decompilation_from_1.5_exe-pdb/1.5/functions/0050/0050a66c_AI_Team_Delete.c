/*
 * Entry: 0050a66c
 * Name: AI_Team_Delete
 * Namespace: Global
 * Signature: void AI_Team_Delete(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Team_Delete(tag_team *param_1)

{
  tag_c_linked_list *ptVar1;
  Scheduler *this;
  tag_squad *ptVar2;
  int iVar3;
  
  tlog_gdm("AI_Team::Delete Begins\n");
  NR_Free_Ptr_Matrix(param_1->gridcell_squads,0,(param_1->strategic_targets).grid_rows + -1,0,
                     (param_1->strategic_targets).grid_columns + -1);
  AIBuild_TeamClose(param_1);
  AI_Match_Team_Close(param_1);
  AI_Team_Trash_Regions_Of_Control(param_1);
  AIBuild_TeamClearConstructionProgram(param_1);
  if (param_1->AIP != (tagAIP_struct *)0x0) {
    param_1->AIP = (tagAIP_struct *)0x0;
  }
  tlog_gdm("AI_Team::Delete   freeing all squads\n");
  ptVar1 = &param_1->my_squads;
  Squad_Check_Squad_List_Valid_Body(ptVar1,".\\Schedule\\ai_team.cpp",0x1f7);
  iVar3 = 0;
  if (0 < (param_1->my_squads).count) {
    do {
      ptVar2 = C_Linked_List_Return_Data_By_Number(ptVar1,iVar3);
      Squad_Delete(ptVar2);
      iVar3 = iVar3 + 1;
    } while (iVar3 < (param_1->my_squads).count);
  }
  iVar3 = 0;
  if (0 < (param_1->attack_squads).count) {
    do {
      ptVar2 = C_Linked_List_Return_Data_By_Number(&param_1->attack_squads,iVar3);
      Squad_Delete(ptVar2);
      iVar3 = iVar3 + 1;
    } while (iVar3 < (param_1->attack_squads).count);
  }
  tlog_gdm("AI_Team::Delete   freeing linked list of pointers to attack_squads\n");
  C_Linked_List_Empty(&param_1->attack_squads);
  tlog_gdm("AI_Team::Delete   freeing linked list of pointers to squads\n");
  C_Linked_List_Empty(ptVar1);
  tlog_gdm("AI_Team::Delete   freeing linked list of pointers to units\n");
  C_Linked_List_Empty(&param_1->my_units);
  tlog_gdm("AI_Team::Delete   freeing targets\n");
  AITeam_TargetsDelete(param_1);
  this = param_1->scheduler;
  if (this != (Scheduler *)0x0) {
    Scheduler::~Scheduler(this);
    operator_delete(this);
  }
  tlog_gdm("AI_Team::Delete   freeing team structure memory\n");
  free(param_1);
  tlog_gdm("AI_Team::Delete Ends\n");
  return;
}
