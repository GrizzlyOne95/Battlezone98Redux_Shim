/*
 * Entry: 0050a19d
 * Name: AI_Team_End_Rapid_Base_Defense
 * Namespace: Global
 * Signature: void AI_Team_End_Rapid_Base_Defense(int param_1, int param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Team_End_Rapid_Base_Defense(int param_1,int param_2,int param_3,int param_4)

{
  Mapgrid_Goal *pMVar1;
  
  if (param_1 == 1) {
    if (param_4 != 0) {
      param_2 = param_2 / AI_map->gridside;
      param_3 = param_3 / AI_map->gridside;
    }
    pMVar1 = (AI_map->team[1]->strategic_targets).grid[param_3][param_2];
    if ((((pMVar1->rapid_defense_state == 1) && (pMVar1->neighbor_flags != '\0')) &&
        (pMVar1->enemy_units < 1)) &&
       (pMVar1->enemy_buildings < 1e-05 != (pMVar1->enemy_buildings == 1e-05))) {
      AI_Team_UnRecruit_Neighbors(AI_map->team[1],pMVar1);
      pMVar1->rapid_defense_state = 0;
    }
  }
  return;
}
