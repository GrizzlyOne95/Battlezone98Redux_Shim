/*
 * Entry: 0051bc79
 * Name: Squad_New
 * Namespace: Global
 * Signature: tag_squad * Squad_New(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tag_squad * __cdecl Squad_New(void)

{
  tag_squad *ptVar1;
  
  ptVar1 = calloc(1,0x48);
  C_Linked_List_Init(&ptVar1->my_units);
  ptVar1->x = -1;
  ptVar1->y = -1;
  ptVar1->my_strategic_goal = (Goal *)0x0;
  ptVar1->strength = 0;
  ptVar1->the_team = (tag_team *)0x0;
  ptVar1->my_squads_cell_ptr = (tag_c_list_cell *)0x0;
  return ptVar1;
}
