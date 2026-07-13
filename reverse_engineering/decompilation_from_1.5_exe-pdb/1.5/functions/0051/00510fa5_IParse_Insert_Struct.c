/*
 * Entry: 00510fa5
 * Name: IParse_Insert_Struct
 * Namespace: Global
 * Signature: void IParse_Insert_Struct(_domain * param_1, _struct_list_element * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl IParse_Insert_Struct(_domain *param_1,_struct_list_element *param_2)

{
  param_2->next_struct = param_1->the_structs;
  param_1->number_of_structures = param_1->number_of_structures + 1;
  param_1->the_structs = param_2;
  return;
}
