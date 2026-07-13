/*
 * Entry: 0050a8cf
 * Name: AI_Team_Find_Houses
 * Namespace: Global
 * Signature: void AI_Team_Find_Houses(tag_strategy_map * param_1, tagBUILDING * param_2, tag_team * param_3, int * param_4, int * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
AI_Team_Find_Houses(tag_strategy_map *param_1,tagBUILDING *param_2,tag_team *param_3,int *param_4,
                   int *param_5)

{
  float *pfVar1;
  void *pvVar2;
  TEAM_RELATION TVar3;
  int extraout_EAX;
  
  pvVar2 = (param_3->strategic_targets).grid
           [(int)(param_2->tiley + (param_2->tiley >> 0x1f & 7U)) >> 3]
           [(int)(param_2->tilex + (param_2->tilex >> 0x1f & 7U)) >> 3];
  TVar3 = Team_GetRelation(param_3->team_ID,param_2->team);
  if ((TVar3 == TR_ENEMY) &&
     (TVar3 = Team_GetRelation(param_3->team_ID,param_2->perceived_team), TVar3 == TR_ENEMY)) {
    pfVar1 = (float *)((int)pvVar2 + 0x60);
    *pfVar1 = param_3->AIP->building_multiplier
              [*(uint *)&param_2->buildingtype->field_0x24 >> 10 & 0xff] + *pfVar1;
    *param_4 = *param_4 + 1;
    if (*pfVar1 <= (float)*param_5) {
      return;
    }
    _ftol2_sse();
    *param_5 = extraout_EAX;
    return;
  }
  if (param_3->team_ID == param_2->team) {
    AI_Team_Update_Scouted(param_3,param_2->tilex,param_2->tiley,(uint)param_2->seeingrange);
    *(float *)((int)pvVar2 + 100) =
         param_3->AIP->building_multiplier[*(uint *)&param_2->buildingtype->field_0x24 >> 10 & 0xff]
         + *(float *)((int)pvVar2 + 100);
  }
  return;
}
