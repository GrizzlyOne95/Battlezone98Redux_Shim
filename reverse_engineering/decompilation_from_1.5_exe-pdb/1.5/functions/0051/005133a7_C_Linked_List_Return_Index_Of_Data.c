/*
 * Entry: 005133a7
 * Name: C_Linked_List_Return_Index_Of_Data
 * Namespace: Global
 * Signature: int C_Linked_List_Return_Index_Of_Data(tag_c_linked_list * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl C_Linked_List_Return_Index_Of_Data(tag_c_linked_list *param_1,void *param_2)

{
  int iVar1;
  tag_c_list_cell *ptVar2;
  
  ptVar2 = param_1->head;
  iVar1 = 0;
  while( true ) {
    if (ptVar2 == (tag_c_list_cell *)0x0) {
      return -1;
    }
    if (ptVar2->cell_data == param_2) break;
    ptVar2 = ptVar2->next;
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}
