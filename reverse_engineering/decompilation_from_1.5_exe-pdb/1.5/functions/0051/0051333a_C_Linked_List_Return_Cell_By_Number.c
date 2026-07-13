/*
 * Entry: 0051333a
 * Name: C_Linked_List_Return_Cell_By_Number
 * Namespace: Global
 * Signature: tag_c_list_cell * C_Linked_List_Return_Cell_By_Number(tag_c_linked_list * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tag_c_list_cell * __cdecl
C_Linked_List_Return_Cell_By_Number(tag_c_linked_list *param_1,int param_2)

{
  tag_c_list_cell *ptVar1;
  int iVar2;
  
  Debug_Assert((int)param_1,0x24e,".\\Schedule\\Linklist.c","the_list");
  if ((-1 < param_2) && (param_2 < param_1->count)) {
    iVar2 = param_1->last_number_accessed;
    if (param_2 == iVar2 + -1) {
      ptVar1 = param_1->last_cell_accessed->prev;
    }
    else if (param_2 == iVar2 + 1) {
      ptVar1 = param_1->last_cell_accessed->next;
    }
    else if (param_2 == iVar2) {
      ptVar1 = param_1->last_cell_accessed;
    }
    else {
      ptVar1 = param_1->head;
      iVar2 = param_2;
      if (0 < param_2) {
        do {
          iVar2 = iVar2 + -1;
          ptVar1 = ptVar1->next;
        } while (iVar2 != 0);
      }
    }
    param_1->last_number_accessed = param_2;
    param_1->last_cell_accessed = ptVar1;
    return ptVar1;
  }
  return (tag_c_list_cell *)0x0;
}
