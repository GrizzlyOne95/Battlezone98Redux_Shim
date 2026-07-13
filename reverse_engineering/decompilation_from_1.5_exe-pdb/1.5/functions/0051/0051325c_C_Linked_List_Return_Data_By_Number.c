/*
 * Entry: 0051325c
 * Name: C_Linked_List_Return_Data_By_Number
 * Namespace: Global
 * Signature: void * C_Linked_List_Return_Data_By_Number(tag_c_linked_list * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl C_Linked_List_Return_Data_By_Number(tag_c_linked_list *param_1,int param_2)

{
  int iVar1;
  void *pvVar2;
  tag_c_list_cell *ptVar3;
  
  iVar1 = param_2;
  Debug_Assert((int)param_1,0x1eb,".\\Schedule\\Linklist.c","the_list");
  if ((param_2 < 0) || (param_1->count <= param_2)) {
    pvVar2 = (void *)0x0;
  }
  else {
    if (param_2 == param_1->last_number_accessed + -1) {
      ptVar3 = param_1->last_cell_accessed->prev;
    }
    else if (param_2 == param_1->last_number_accessed + 1) {
      ptVar3 = param_1->last_cell_accessed->next;
    }
    else {
      ptVar3 = param_1->head;
      Debug_Assert((int)ptVar3,0x1fc,".\\Schedule\\Linklist.c","current_cell");
      if (0 < param_2) {
        do {
          ptVar3 = ptVar3->next;
          Debug_Assert((int)ptVar3,0x201,".\\Schedule\\Linklist.c","current_cell");
          param_2 = param_2 + -1;
        } while (param_2 != 0);
      }
    }
    param_1->last_cell_accessed = ptVar3;
    param_1->last_number_accessed = iVar1;
    pvVar2 = ptVar3->cell_data;
  }
  return pvVar2;
}
