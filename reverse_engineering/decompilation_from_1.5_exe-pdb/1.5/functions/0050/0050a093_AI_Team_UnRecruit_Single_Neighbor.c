/*
 * Entry: 0050a093
 * Name: AI_Team_UnRecruit_Single_Neighbor
 * Namespace: Global
 * Signature: void AI_Team_UnRecruit_Single_Neighbor(tag_team * param_1, Mapgrid_Goal * param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
AI_Team_UnRecruit_Single_Neighbor
          (tag_team *param_1,Mapgrid_Goal *param_2,int param_3,int param_4,int param_5)

{
  void *pvVar1;
  
  pvVar1 = (param_1->strategic_targets).grid[param_2->row + param_4][param_2->column + param_3];
  if (*(tag_squad **)((int)pvVar1 + 0x14) != (tag_squad *)0x0) {
    *(undefined4 *)((int)pvVar1 + 0x74) = 0;
    *(undefined1 *)((int)pvVar1 + 0x78) = 0;
    Squad_Send_Units(AI_map,*(tag_squad **)((int)pvVar1 + 0x14));
  }
  param_2->neighbor_flags = param_2->neighbor_flags & ~(byte)param_5;
  return;
}
