/*
 * Entry: 00512f75
 * Name: c_list_cell_new
 * Namespace: Global
 * Signature: tag_c_list_cell * c_list_cell_new(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tag_c_list_cell * __cdecl c_list_cell_new(void)

{
  tag_c_list_cell *ptVar1;
  
  ptVar1 = calloc(1,0xc);
  Debug_Assert((int)ptVar1,0x28,".\\Schedule\\Linklist.c","new_cell");
  ptVar1->cell_data = (void *)0x0;
  ptVar1->next = (tag_c_list_cell *)0x0;
  ptVar1->prev = (tag_c_list_cell *)0x0;
  return ptVar1;
}
