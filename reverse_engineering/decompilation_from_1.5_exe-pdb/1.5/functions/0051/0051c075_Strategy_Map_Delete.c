/*
 * Entry: 0051c075
 * Name: Strategy_Map_Delete
 * Namespace: Global
 * Signature: void Strategy_Map_Delete(tag_strategy_map * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Strategy_Map_Delete(tag_strategy_map *param_1)

{
  matrix<unsigned_char> *this;
  tag_team *ptVar1;
  int iVar2;
  
  Debug_Assert((int)param_1,0x71,".\\Schedule\\Stratmap.cpp","AI_map");
  iVar2 = 0;
  do {
    this = param_1->hunt_map[iVar2];
    if (this != (matrix<unsigned_char> *)0x0) {
      matrix<unsigned_char>::Clean_Up(this);
      operator_delete(this);
    }
    ptVar1 = param_1->team[iVar2];
    if (ptVar1 != (tag_team *)0x0) {
      AI_Team_Delete(ptVar1);
      param_1->team[iVar2] = (tag_team *)0x0;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x10);
  free(param_1);
  return;
}
