/*
 * Entry: 0051bf15
 * Name: Squad_Matching_Delete
 * Namespace: Global
 * Signature: void Squad_Matching_Delete(tag_squad_matching * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Squad_Matching_Delete(tag_squad_matching *param_1)

{
  tag_squad *ptVar1;
  
  if (((param_1->used == 0) &&
      (ptVar1 = param_1->transfer_units, ptVar1->my_strategic_goal == (Goal *)0x0)) &&
     (ptVar1 != (tag_squad *)0x0)) {
    Squad_Delete(ptVar1);
  }
  free(param_1);
  return;
}
