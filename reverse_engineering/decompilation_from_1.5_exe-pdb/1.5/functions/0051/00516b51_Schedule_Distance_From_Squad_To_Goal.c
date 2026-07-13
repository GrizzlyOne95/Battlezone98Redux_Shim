/*
 * Entry: 00516b51
 * Name: Schedule_Distance_From_Squad_To_Goal
 * Namespace: Global
 * Signature: double Schedule_Distance_From_Squad_To_Goal(tag_strategy_map * param_1, tag_squad * param_2, Mapgrid_Goal * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

double __cdecl
Schedule_Distance_From_Squad_To_Goal
          (tag_strategy_map *param_1,tag_squad *param_2,Mapgrid_Goal *param_3)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_1->gridside;
  iVar1 = param_2->x - (param_3->column * iVar2 + iVar2 / 2);
  iVar2 = param_2->y - (param_3->row * iVar2 + iVar2 / 2);
  return SQRT((double)(iVar1 * iVar1 + iVar2 * iVar2)) * 10.0;
}
