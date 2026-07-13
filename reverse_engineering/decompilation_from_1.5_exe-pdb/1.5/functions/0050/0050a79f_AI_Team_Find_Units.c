/*
 * Entry: 0050a79f
 * Name: AI_Team_Find_Units
 * Namespace: Global
 * Signature: void AI_Team_Find_Units(tag_strategy_map * param_1, tagUNIT * param_2, tag_team * param_3, int * param_4, int * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
AI_Team_Find_Units(tag_strategy_map *param_1,tagUNIT *param_2,tag_team *param_3,int *param_4,
                  int *param_5)

{
  void *pvVar1;
  int iVar2;
  int iVar3;
  TEAM_RELATION TVar4;
  
  iVar2 = (param_2->tilepos).y / param_1->gridside;
  iVar3 = (param_2->tilepos).x / param_1->gridside;
  pvVar1 = (param_3->strategic_targets).grid[iVar2][iVar3];
  TVar4 = Team_GetRelation(param_3->team_ID,(int)param_2->team);
  if ((TVar4 != TR_ENEMY) ||
     (TVar4 = Team_GetRelation(param_3->team_ID,(int)param_2->perceived_team), TVar4 != TR_ENEMY)) {
    if ((int)param_2->team == param_3->team_ID) {
      AI_Team_Update_Scouted
                (param_3,(param_2->tilepos).x,(param_2->tilepos).y,(uint)param_2->type->seeingrange)
      ;
      *(int *)((int)pvVar1 + 0x58) = *(int *)((int)pvVar1 + 0x58) + 1;
    }
    return;
  }
  if ((param_3->strategic_targets).scouted[iVar2][iVar3] == 0) {
    return;
  }
  *(int *)((int)pvVar1 + 0x50) = *(int *)((int)pvVar1 + 0x50) + 1;
  *param_4 = *param_4 + 1;
  *(int *)((int)pvVar1 + 0x84) = param_2->handle;
  iVar2 = AI_Match_Get_Unit_Strength(param_2,param_3);
  iVar3 = Units_IsFlyUnit(param_2);
  if (iVar3 == 0) {
    *(int *)((int)pvVar1 + 0x54) = *(int *)((int)pvVar1 + 0x54) + iVar2;
  }
  if (*(int *)((int)pvVar1 + 0x50) <= *param_5) {
    return;
  }
  *param_5 = *(int *)((int)pvVar1 + 0x50);
  return;
}
