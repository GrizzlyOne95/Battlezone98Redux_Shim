/*
 * Entry: 00582d1d
 * Name: Virtual_Memory_Alloc
 * Namespace: Global
 * Signature: void * Virtual_Memory_Alloc(long param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl Virtual_Memory_Alloc(long param_1,long param_2)

{
  LPVOID lpAddress;
  LPVOID pvVar1;
  VIRTUAL_MEMORY_CHAIN *pVVar2;
  SIZE_T dwSize;
  SIZE_T dwSize_00;
  _SYSTEM_INFO local_2c;
  DWORD local_8;
  
  GetSystemInfo(&local_2c);
  local_8 = local_2c.dwPageSize;
  dwSize_00 = (-local_2c.dwPageSize & param_1) + local_2c.dwPageSize;
  if (param_2 < (int)dwSize_00) {
    param_2 = dwSize_00;
  }
  dwSize = (param_2 - 1U & 0xffff0000) + 0x10000;
  lpAddress = VirtualAlloc((LPVOID)0x0,dwSize,0x102000,4);
  if (lpAddress != (LPVOID)0x0) {
    pvVar1 = VirtualAlloc(lpAddress,dwSize_00,0x1000,4);
    if ((pvVar1 != (LPVOID)0x0) && (pVVar2 = malloc(0x10), pVVar2 != (VIRTUAL_MEMORY_CHAIN *)0x0)) {
      pVVar2->Page_Size = local_8;
      pVVar2->Maximun_Size = dwSize;
      pVVar2->Base_Address = lpAddress;
      pVVar2->Next = Virtual_Mem_Handle;
      Virtual_Mem_Handle = pVVar2;
      return lpAddress;
    }
    VirtualFree(lpAddress,0,0x8000);
  }
  return (void *)0x0;
}
