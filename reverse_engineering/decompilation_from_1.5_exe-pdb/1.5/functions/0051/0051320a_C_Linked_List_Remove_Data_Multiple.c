/*
 * Entry: 0051320a
 * Name: C_Linked_List_Remove_Data_Multiple
 * Namespace: Global
 * Signature: int C_Linked_List_Remove_Data_Multiple(tag_c_linked_list * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl C_Linked_List_Remove_Data_Multiple(tag_c_linked_list *param_1,void *param_2)

{
  tag_c_list_cell *ptVar1;
  tag_c_list_cell *ptVar2;
  int iVar3;
  
  Debug_Assert((int)param_1,0x1b9,".\\Schedule\\Linklist.c","the_list");
  iVar3 = 0;
  param_1->last_number_accessed = -999;
  param_1->last_cell_accessed = (tag_c_list_cell *)0x0;
  ptVar1 = param_1->head;
  while (ptVar2 = ptVar1, ptVar2 != (tag_c_list_cell *)0x0) {
    ptVar1 = ptVar2->next;
    if (ptVar2->cell_data == param_2) {
      C_Linked_List_Remove_Cell(param_1,ptVar2);
      iVar3 = iVar3 + 1;
    }
  }
  return iVar3;
}
