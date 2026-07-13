/*
 * Entry: 005132f4
 * Name: C_Linked_List_Already_In_List
 * Namespace: Global
 * Signature: int C_Linked_List_Already_In_List(tag_c_linked_list * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl C_Linked_List_Already_In_List(tag_c_linked_list *param_1,void *param_2)

{
  int iVar1;
  tag_c_list_cell *ptVar2;
  int iVar3;
  
  Debug_Assert((int)param_1,0x225,".\\Schedule\\Linklist.c","the_list");
  iVar1 = param_1->count;
  if (iVar1 != 0) {
    ptVar2 = param_1->head;
    iVar3 = 0;
    if (0 < iVar1) {
      do {
        if (ptVar2->cell_data == param_2) {
          return 1;
        }
        ptVar2 = ptVar2->next;
        iVar3 = iVar3 + 1;
      } while (iVar3 < iVar1);
    }
  }
  return 0;
}
