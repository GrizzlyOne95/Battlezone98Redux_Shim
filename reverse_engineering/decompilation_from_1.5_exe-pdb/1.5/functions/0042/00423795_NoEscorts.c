/*
 * Entry: 00423795
 * Name: NoEscorts
 * Namespace: Global
 * Signature: void NoEscorts(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl NoEscorts(void)

{
  tagAIP_struct *ptVar1;
  
  if (((AI_map != (tag_strategy_map *)0x0) && (AI_map->team[2] != (tag_team *)0x0)) &&
     (ptVar1 = AI_map->team[2]->AIP, ptVar1 != (tagAIP_struct *)0x0)) {
    ptVar1->escort_priority = 0;
    ptVar1->min_escort_force = 100;
    ptVar1->max_escort_force = 100;
    ptVar1->perimeter_priority = 0;
    ptVar1->min_perimeter_force = 100;
    ptVar1->max_perimeter_force = 100;
    ptVar1->defend_buildings_priority = 0;
    ptVar1->min_building_defense_force = 100;
    ptVar1->max_building_defense_force = 100;
  }
  return;
}
