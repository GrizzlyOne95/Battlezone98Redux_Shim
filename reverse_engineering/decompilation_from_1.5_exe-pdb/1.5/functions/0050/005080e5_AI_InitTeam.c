/*
 * Entry: 005080e5
 * Name: AI_InitTeam
 * Namespace: Global
 * Signature: void AI_InitTeam(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_InitTeam(int param_1)

{
  tag_team *ptVar1;
  tagUNIT *ptVar2;
  tagBUILDING *ptVar3;
  int iVar4;
  tagITERATOR local_54;
  
  tlog_gdm("AI   About to create team %d\n");
  ptVar1 = AI_Team_New(AI_map,param_1,1);
  AI_map->team[param_1] = ptVar1;
  Debug_Assert((int)AI_map->team[param_1],0xb8,".\\Schedule\\Ai.cpp","AI_map->team[team]");
  ITERATE_UNITINIT_TEAM(&local_54,param_1);
  ptVar2 = Iterate_UnitNext(&local_54);
  while (ptVar2 != (tagUNIT *)0x0) {
    AI_PartIntoTeam(ptVar2);
    ptVar2 = Iterate_UnitNext(&local_54);
  }
  ITERATE_BUILDINIT_TEAM(&local_54,param_1);
  ptVar3 = Iterate_BuildNext(&local_54);
  while (ptVar3 != (tagBUILDING *)0x0) {
    AI_BuildingIntoTeam(ptVar3);
    ptVar3 = Iterate_BuildNext(&local_54);
  }
  iVar4 = 0;
  do {
    if (iVar4 != param_1) {
      Team_SetRelation(param_1,iVar4,TR_ENEMY);
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x10);
  return;
}
