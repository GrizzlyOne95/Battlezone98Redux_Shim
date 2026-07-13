/*
 * Entry: 00582e9a
 * Name: Total_Virtual_Memory_Used
 * Namespace: Global
 * Signature: long Total_Virtual_Memory_Used(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Total_Virtual_Memory_Used(void)

{
  VIRTUAL_MEMORY_CHAIN *pVVar1;
  int iVar2;
  _MEMORY_BASIC_INFORMATION local_20;
  
  iVar2 = 0;
  for (pVVar1 = Virtual_Mem_Handle; pVVar1 != (VIRTUAL_MEMORY_CHAIN *)0x0; pVVar1 = pVVar1->Next) {
    VirtualQuery(pVVar1->Base_Address,&local_20,0x1c);
    iVar2 = iVar2 + local_20.RegionSize;
  }
  return iVar2;
}
