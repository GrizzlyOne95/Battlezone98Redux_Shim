/*
 * Entry: 0050a3ec
 * Name: AI_Team_Update_Rapid_Defenses
 * Namespace: Global
 * Signature: void AI_Team_Update_Rapid_Defenses(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Team_Update_Rapid_Defenses(tag_team *param_1)

{
  void *pvVar1;
  tag_strategy_map *ptVar2;
  int iVar3;
  float fVar4;
  int local_8;
  
  local_8 = 0;
  ptVar2 = AI_map;
  if (0 < AI_map->AI_map_rows) {
    do {
      iVar3 = 0;
      if (0 < ptVar2->AI_map_columns) {
        do {
          pvVar1 = (param_1->strategic_targets).grid[local_8][iVar3];
          fVar4 = Get_Time();
          if (120.0 < fVar4 - *(float *)((int)pvVar1 + 0x7c)) {
            AI_Team_End_Rapid_Base_Defense(param_1->team_ID,iVar3,local_8,0);
          }
          iVar3 = iVar3 + 1;
          ptVar2 = AI_map;
        } while (iVar3 < AI_map->AI_map_columns);
      }
      local_8 = local_8 + 1;
    } while (local_8 < ptVar2->AI_map_rows);
  }
  return;
}
