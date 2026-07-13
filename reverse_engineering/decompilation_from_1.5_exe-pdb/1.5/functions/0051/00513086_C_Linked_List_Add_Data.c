/*
 * Entry: 00513086
 * Name: C_Linked_List_Add_Data
 * Namespace: Global
 * Signature: tag_c_list_cell * C_Linked_List_Add_Data(tag_c_linked_list * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tag_c_list_cell * __cdecl C_Linked_List_Add_Data(tag_c_linked_list *param_1,void *param_2)

{
  tag_c_list_cell *ptVar1;
  
  Debug_Assert((int)param_1,0xcf,".\\Schedule\\Linklist.c","the_list");
  ptVar1 = c_list_cell_new();
  ptVar1->prev = (tag_c_list_cell *)0x0;
  ptVar1->cell_data = param_2;
  ptVar1->next = param_1->head;
  param_1->head = ptVar1;
  if (param_1->tail == (tag_c_list_cell *)0x0) {
    param_1->tail = ptVar1;
  }
  param_1->last_number_accessed = -999;
  if (ptVar1->next != (tag_c_list_cell *)0x0) {
    ptVar1->next->prev = ptVar1;
  }
  param_1->count = param_1->count + 1;
  return ptVar1;
}
