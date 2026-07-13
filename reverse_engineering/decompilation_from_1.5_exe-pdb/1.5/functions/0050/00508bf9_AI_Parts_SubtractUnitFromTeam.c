/*
 * Entry: 00508bf9
 * Name: AI_Parts_SubtractUnitFromTeam
 * Namespace: Global
 * Signature: void AI_Parts_SubtractUnitFromTeam(tagUNIT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Parts_SubtractUnitFromTeam(tagUNIT *param_1)

{
  tag_team *ptVar1;
  
  ptVar1 = AI_map->team[param_1->team];
  ptVar1->number_of_active_parts = ptVar1->number_of_active_parts + -1;
  ptVar1->summed_offensive_strength = ptVar1->summed_offensive_strength + -1;
  ptVar1->summed_defensive_strength = ptVar1->summed_defensive_strength + -1;
  ptVar1->summed_strength = ptVar1->summed_defensive_strength + ptVar1->summed_offensive_strength;
  AI_Parts_SubtractPartFromSquad(param_1,ptVar1);
  C_Linked_List_Remove_Data(&ptVar1->my_units,param_1);
  return;
}
