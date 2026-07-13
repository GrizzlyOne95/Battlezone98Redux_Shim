/*
 * Entry: 00513001
 * Name: C_Linked_List_Empty
 * Namespace: Global
 * Signature: void C_Linked_List_Empty(tag_c_linked_list * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl C_Linked_List_Empty(tag_c_linked_list *param_1)

{
  tag_c_list_cell *_Memory;
  int iVar1;
  
  Debug_Assert((int)param_1,0x86,".\\Schedule\\Linklist.c","the_list");
  iVar1 = 0;
  if (0 < param_1->count) {
    do {
      _Memory = param_1->head;
      if (_Memory != (tag_c_list_cell *)0x0) {
        param_1->head = _Memory->next;
        free(_Memory);
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < param_1->count);
  }
  param_1->count = 0;
  param_1->head = (tag_c_list_cell *)0x0;
  param_1->tail = (tag_c_list_cell *)0x0;
  param_1->last_cell_accessed = (tag_c_list_cell *)0x0;
  param_1->last_number_accessed = -999;
  return;
}
