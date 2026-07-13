/*
 * Entry: 0051312c
 * Name: C_Linked_List_Remove_Cell
 * Namespace: Global
 * Signature: void C_Linked_List_Remove_Cell(tag_c_linked_list * param_1, tag_c_list_cell * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl C_Linked_List_Remove_Cell(tag_c_linked_list *param_1,tag_c_list_cell *param_2)

{
  tag_c_list_cell *ptVar1;
  tag_c_list_cell *ptVar2;
  
  Debug_Assert((int)param_1,0x138,".\\Schedule\\Linklist.c","the_list");
  ptVar2 = (tag_c_list_cell *)0x0;
  param_1->last_number_accessed = -999;
  param_1->last_cell_accessed = (tag_c_list_cell *)0x0;
  if (param_2 == param_1->head) {
    if (param_1->tail == param_2) {
      param_1->tail = (tag_c_list_cell *)0x0;
    }
    ptVar1 = param_2->next;
    param_1->head = ptVar1;
    if (ptVar1 == (tag_c_list_cell *)0x0) goto LAB_005131a5;
  }
  else {
    if (param_2 == param_1->tail) {
      ptVar2 = param_2->prev;
      param_1->tail = ptVar2;
      if (ptVar2 != (tag_c_list_cell *)0x0) {
        ptVar2->next = (tag_c_list_cell *)0x0;
      }
      goto LAB_005131a5;
    }
    if (param_2 == (tag_c_list_cell *)0x0) goto LAB_005131a5;
    if (param_2->prev != (tag_c_list_cell *)0x0) {
      param_2->prev->next = param_2->next;
    }
    ptVar1 = param_2->next;
    if (ptVar1 == (tag_c_list_cell *)0x0) goto LAB_005131a5;
    ptVar2 = param_2->prev;
  }
  ptVar1->prev = ptVar2;
LAB_005131a5:
  free(param_2);
  param_1->count = param_1->count + -1;
  return;
}
