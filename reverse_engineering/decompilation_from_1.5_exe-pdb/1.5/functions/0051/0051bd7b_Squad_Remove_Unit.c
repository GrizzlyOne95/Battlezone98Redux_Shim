/*
 * Entry: 0051bd7b
 * Name: Squad_Remove_Unit
 * Namespace: Global
 * Signature: void Squad_Remove_Unit(tag_squad * param_1, tagUNIT * param_2, tag_team * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Squad_Remove_Unit(tag_squad *param_1,tagUNIT *param_2,tag_team *param_3)

{
  int iVar1;
  
  iVar1 = AI_Match_Get_Unit_Strength(param_2,param_3);
  param_1->strength = param_1->strength - iVar1;
  if ((param_2->ai).the_squad == param_1) {
    (param_2->ai).the_squad = (tag_squad *)0x0;
  }
  C_Linked_List_Remove_Cell(&param_1->my_units,param_2->squads_list_cell_ptr);
  return;
}
