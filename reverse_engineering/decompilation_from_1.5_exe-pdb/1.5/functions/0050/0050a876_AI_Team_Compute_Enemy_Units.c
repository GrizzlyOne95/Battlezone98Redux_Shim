/*
 * Entry: 0050a876
 * Name: AI_Team_Compute_Enemy_Units
 * Namespace: Global
 * Signature: int AI_Team_Compute_Enemy_Units(tag_team * param_1, tag_strategy_map * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AI_Team_Compute_Enemy_Units(tag_team *param_1,tag_strategy_map *param_2)

{
  tagUNIT *ptVar1;
  tagITERATOR local_5c;
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_c = 0;
  Iterate_UnitInitAll(&local_5c);
  ptVar1 = Iterate_UnitNext(&local_5c);
  while (ptVar1 != (tagUNIT *)0x0) {
    AI_Team_Find_Units(param_2,ptVar1,param_1,&local_c,&local_8);
    ptVar1 = Iterate_UnitNext(&local_5c);
  }
  (param_1->strategic_targets).max_enemy_units = local_8;
  param_1->summed_enemy_strength = local_c;
  return local_c;
}
