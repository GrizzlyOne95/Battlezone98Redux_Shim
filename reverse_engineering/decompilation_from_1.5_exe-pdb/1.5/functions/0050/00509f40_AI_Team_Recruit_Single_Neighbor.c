/*
 * Entry: 00509f40
 * Name: AI_Team_Recruit_Single_Neighbor
 * Namespace: Global
 * Signature: void AI_Team_Recruit_Single_Neighbor(tag_team * param_1, Mapgrid_Goal * param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, GameObject * param_9)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
AI_Team_Recruit_Single_Neighbor
          (tag_team *param_1,Mapgrid_Goal *param_2,int param_3,int param_4,int param_5,int param_6,
          int param_7,int param_8,GameObject *param_9)

{
  void *pvVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = param_2->column + param_3;
  iVar3 = param_2->row + param_4;
  if ((((-1 < iVar2) && (-1 < iVar3)) && (iVar2 < AI_map->AI_map_columns)) &&
     (iVar3 < AI_map->AI_map_rows)) {
    pvVar1 = (param_1->strategic_targets).grid[iVar3][iVar2];
    if (((*(tag_squad **)((int)pvVar1 + 0x14) != (tag_squad *)0x0) &&
        (*(int *)((int)pvVar1 + 0x74) == 0)) &&
       ((*(int *)((int)pvVar1 + 4) == 6 || (*(int *)((int)pvVar1 + 4) == 1)))) {
      *(undefined4 *)((int)pvVar1 + 0x74) = 2;
      *(undefined1 *)((int)pvVar1 + 0x78) = (undefined1)param_6;
      Squad_Send_Rapid_Base_Defense(*(tag_squad **)((int)pvVar1 + 0x14),param_2,param_9);
      param_2->neighbor_flags = param_2->neighbor_flags | (byte)param_5;
    }
  }
  return;
}
