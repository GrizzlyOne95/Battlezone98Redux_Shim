/*
 * Entry: 00512fd5
 * Name: C_Linked_List_New
 * Namespace: Global
 * Signature: tag_c_linked_list * C_Linked_List_New(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tag_c_linked_list * __cdecl C_Linked_List_New(void)

{
  tag_c_linked_list *ptVar1;
  
  ptVar1 = calloc(1,0x14);
  Debug_Assert((int)ptVar1,0x68,".\\Schedule\\Linklist.c","new_list");
  C_Linked_List_Init(ptVar1);
  return ptVar1;
}
