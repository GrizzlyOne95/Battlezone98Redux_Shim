/*
 * Entry: 0051bd4e
 * Name: Squad_Add_Unit
 * Namespace: Global
 * Signature: void Squad_Add_Unit(tag_squad * param_1, tagUNIT * param_2, tag_team * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Squad_Add_Unit(tag_squad *param_1,tagUNIT *param_2,tag_team *param_3)

{
  tag_c_list_cell *ptVar1;
  int iVar2;
  
  ptVar1 = C_Linked_List_Add_Data(&param_1->my_units,param_2);
  param_2->squads_list_cell_ptr = ptVar1;
  iVar2 = AI_Match_Get_Unit_Strength(param_2,param_3);
  param_1->strength = param_1->strength + iVar2;
  (param_2->ai).the_squad = param_1;
  return;
}
