/*
 * Entry: 0050a99c
 * Name: AI_Team_Compute_Houses
 * Namespace: Global
 * Signature: int AI_Team_Compute_Houses(tag_team * param_1, tag_strategy_map * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AI_Team_Compute_Houses(tag_team *param_1,tag_strategy_map *param_2)

{
  tagBUILDING *ptVar1;
  tagITERATOR local_5c;
  int local_c;
  int local_8;
  
  local_c = 0;
  local_8 = 0;
  ITERATE_BUILDINIT_ALL(&local_5c);
  ptVar1 = Iterate_BuildNext(&local_5c);
  while (ptVar1 != (tagBUILDING *)0x0) {
    AI_Team_Find_Houses(param_2,ptVar1,param_1,&local_8,&local_c);
    ptVar1 = Iterate_BuildNext(&local_5c);
  }
  return local_8;
}
