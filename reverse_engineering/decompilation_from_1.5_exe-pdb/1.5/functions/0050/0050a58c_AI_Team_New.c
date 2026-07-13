/*
 * Entry: 0050a58c
 * Name: AI_Team_New
 * Namespace: Global
 * Signature: tag_team * AI_Team_New(tag_strategy_map * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tag_team * __cdecl AI_Team_New(tag_strategy_map *param_1,int param_2,int param_3)

{
  tag_team *ptVar1;
  Scheduler *pSVar2;
  void ***pppvVar3;
  
  ptVar1 = calloc(1,0x59c);
  ptVar1->team_ID = param_2;
  ptVar1->aicontrol = param_3;
  C_Linked_List_Init(&ptVar1->my_units);
  C_Linked_List_Init(&ptVar1->my_squads);
  Squad_Check_Squad_List_Valid_Body(&ptVar1->my_squads,".\\Schedule\\ai_team.cpp",0x19c);
  C_Linked_List_Init(&ptVar1->attack_squads);
  ptVar1->max_squad_ID = 1000;
  ptVar1->priorities_changed = 0;
  ptVar1->AIP = (tagAIP_struct *)0x0;
  AIBuild_TeamInit(ptVar1);
  AI_Match_Team_Init(ptVar1);
  AITeam_TargetsNew(ptVar1,param_1->AI_map_columns,param_1->AI_map_rows);
  pSVar2 = operator_new(0xa0);
  if (pSVar2 == (Scheduler *)0x0) {
    pSVar2 = (Scheduler *)0x0;
  }
  else {
    pSVar2 = Scheduler::Scheduler(pSVar2,param_1,ptVar1);
  }
  ptVar1->scheduler = pSVar2;
  ptVar1->mapgrid_added = 0;
  AI_Team_Initialize_Regions_Of_Control(ptVar1,param_1->AI_map_columns,param_1->AI_map_rows);
  pppvVar3 = NR_Ptr_Matrix(0,param_1->AI_map_rows + -1,0,param_1->AI_map_columns + -1);
  ptVar1->gridcell_squads = pppvVar3;
  return ptVar1;
}
