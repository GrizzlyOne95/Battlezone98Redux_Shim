/*
 * Entry: 005127db
 * Name: IParse_New_Domain
 * Namespace: Global
 * Signature: void * IParse_New_Domain(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl IParse_New_Domain(void)

{
  undefined4 *puVar1;
  
  puVar1 = calloc(1,0x24);
  *puVar1 = 0;
  puVar1[1] = 0;
  puVar1[2] = 0;
  puVar1[3] = 0;
  C_Linked_List_Init((tag_c_linked_list *)(puVar1 + 4));
  return puVar1;
}
