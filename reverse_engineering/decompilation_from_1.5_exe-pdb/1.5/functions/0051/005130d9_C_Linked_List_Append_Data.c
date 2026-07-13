/*
 * Entry: 005130d9
 * Name: C_Linked_List_Append_Data
 * Namespace: Global
 * Signature: tag_c_list_cell * C_Linked_List_Append_Data(tag_c_linked_list * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tag_c_list_cell * __cdecl C_Linked_List_Append_Data(tag_c_linked_list *param_1,void *param_2)

{
  tag_c_list_cell *ptVar1;
  tag_c_list_cell *ptVar2;
  
  Debug_Assert((int)param_1,0x106,".\\Schedule\\Linklist.c","the_list");
  ptVar2 = c_list_cell_new();
  ptVar2->cell_data = param_2;
  ptVar1 = param_1->tail;
  ptVar2->next = (tag_c_list_cell *)0x0;
  ptVar2->prev = ptVar1;
  param_1->tail = ptVar2;
  if (param_1->head == (tag_c_list_cell *)0x0) {
    param_1->head = ptVar2;
  }
  param_1->last_number_accessed = -999;
  if (ptVar2->prev != (tag_c_list_cell *)0x0) {
    ptVar2->prev->next = ptVar2;
  }
  param_1->count = param_1->count + 1;
  return ptVar2;
}
