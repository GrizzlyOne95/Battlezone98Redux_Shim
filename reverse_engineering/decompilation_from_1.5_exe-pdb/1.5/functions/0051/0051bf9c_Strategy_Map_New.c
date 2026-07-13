/*
 * Entry: 0051bf9c
 * Name: Strategy_Map_New
 * Namespace: Global
 * Signature: tag_strategy_map * Strategy_Map_New(int param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tag_strategy_map * __cdecl Strategy_Map_New(int param_1,int param_2,int param_3)

{
  tag_strategy_map *ptVar1;
  matrix<unsigned_char> *pmVar2;
  int iVar3;
  int iVar4;
  tag_strategy_map *ptVar5;
  int local_c;
  matrix<unsigned_char> **local_8;
  
  ptVar1 = calloc(1,0x94);
  Debug_Assert((int)ptVar1,0x36,".\\Schedule\\Stratmap.cpp","new_AI_map");
  ptVar5 = ptVar1;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    ptVar5->team[0] = (tag_team *)0x0;
    ptVar5 = (tag_strategy_map *)(ptVar5->team + 1);
  }
  local_8 = ptVar1->hunt_map;
  local_c = 0x10;
  do {
    pmVar2 = operator_new(0x10);
    if (pmVar2 == (matrix<unsigned_char> *)0x0) {
      pmVar2 = (matrix<unsigned_char> *)0x0;
    }
    else {
      pmVar2 = matrix<unsigned_char>::matrix<unsigned_char>(pmVar2,param_1,param_2);
    }
    iVar3 = 0;
    *local_8 = pmVar2;
    if (0 < param_1) {
      do {
        iVar4 = 0;
        if (0 < param_2) {
          do {
            pmVar2->data[iVar4 + pmVar2->columns * iVar3] = '\0';
            iVar4 = iVar4 + 1;
          } while (iVar4 < param_2);
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 < param_1);
    }
    local_8 = local_8 + 1;
    local_c = local_c + -1;
  } while (local_c != 0);
  ptVar1->dont_move_enemies = 0;
  ptVar1->ai_omniscient = 0;
  ptVar1->AI_map_columns = param_1;
  ptVar1->AI_map_rows = param_2;
  ptVar1->gridside = param_3;
  return ptVar1;
}
