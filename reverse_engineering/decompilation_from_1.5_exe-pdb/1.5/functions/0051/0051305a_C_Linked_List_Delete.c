/*
 * Entry: 0051305a
 * Name: C_Linked_List_Delete
 * Namespace: Global
 * Signature: void C_Linked_List_Delete(tag_c_linked_list * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl C_Linked_List_Delete(tag_c_linked_list *param_1)

{
  Debug_Assert((int)param_1,0xb0,".\\Schedule\\Linklist.c","the_list");
  C_Linked_List_Empty(param_1);
  free(param_1);
  return;
}
