/*
 * Entry: 00512fa5
 * Name: C_Linked_List_Init
 * Namespace: Global
 * Signature: void C_Linked_List_Init(tag_c_linked_list * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl C_Linked_List_Init(tag_c_linked_list *param_1)

{
  Debug_Assert((int)param_1,0x45,".\\Schedule\\Linklist.c","the_list");
  param_1->count = 0;
  param_1->head = (tag_c_list_cell *)0x0;
  param_1->tail = (tag_c_list_cell *)0x0;
  param_1->last_cell_accessed = (tag_c_list_cell *)0x0;
  param_1->last_number_accessed = -999;
  return;
}
