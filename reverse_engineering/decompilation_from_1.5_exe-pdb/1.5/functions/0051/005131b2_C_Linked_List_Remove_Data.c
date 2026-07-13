/*
 * Entry: 005131b2
 * Name: C_Linked_List_Remove_Data
 * Namespace: Global
 * Signature: int C_Linked_List_Remove_Data(tag_c_linked_list * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl C_Linked_List_Remove_Data(tag_c_linked_list *param_1,void *param_2)

{
  tag_c_list_cell *ptVar1;
  int iVar2;
  
  iVar2 = 0;
  Debug_Assert((int)param_1,0x183,".\\Schedule\\Linklist.c","the_list");
  ptVar1 = param_1->head;
  param_1->last_cell_accessed = (tag_c_list_cell *)0x0;
  param_1->last_number_accessed = -999;
  if (ptVar1 != (tag_c_list_cell *)0x0) {
    do {
      if (iVar2 != 0) goto LAB_005131fc;
      if (ptVar1->cell_data == param_2) {
        iVar2 = 1;
      }
      else {
        ptVar1 = ptVar1->next;
      }
    } while (ptVar1 != (tag_c_list_cell *)0x0);
    if (iVar2 != 0) {
LAB_005131fc:
      C_Linked_List_Remove_Cell(param_1,ptVar1);
    }
  }
  return iVar2;
}
