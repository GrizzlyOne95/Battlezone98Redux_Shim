/*
 * Entry: 0051298f
 * Name: IParse_Trash_Domain
 * Namespace: Global
 * Signature: void IParse_Trash_Domain(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl IParse_Trash_Domain(void *param_1)

{
  void *_Memory;
  int iVar1;
  
  IParse_Trash_Structs(*(_struct_list_element **)((int)param_1 + 0xc));
  IParse_Trash_Variables(*(_variable_struct **)((int)param_1 + 4));
  iVar1 = *(int *)((int)param_1 + 0x18) + -1;
  if (-1 < iVar1) {
    do {
      _Memory = C_Linked_List_Return_Data_By_Number
                          ((tag_c_linked_list *)((int)param_1 + 0x10),iVar1);
      free(_Memory);
      iVar1 = iVar1 + -1;
    } while (-1 < iVar1);
  }
  C_Linked_List_Empty((tag_c_linked_list *)((int)param_1 + 0x10));
  free(param_1);
  return;
}
