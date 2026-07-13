/*
 * Entry: 00582e19
 * Name: Virtual_Memory_Execption_Handler
 * Namespace: Global
 * Signature: long Virtual_Memory_Execption_Handler(_EXCEPTION_POINTERS * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Virtual_Memory_Execption_Handler(_EXCEPTION_POINTERS *param_1)

{
  LPCVOID pvVar1;
  LPCVOID lpAddress;
  LPCVOID pvVar2;
  VIRTUAL_MEMORY_CHAIN *pVVar3;
  _MEMORY_BASIC_INFORMATION local_20;
  
  if (param_1->ExceptionRecord->ExceptionCode != 0xc0000005) {
    return 0;
  }
  pvVar1 = (LPCVOID)param_1->ExceptionRecord->ExceptionInformation[1];
  pVVar3 = Virtual_Mem_Handle;
  while( true ) {
    if (pVVar3 == (VIRTUAL_MEMORY_CHAIN *)0x0) {
      return 0;
    }
    lpAddress = pVVar3->Base_Address;
    pvVar2 = (LPCVOID)(pVVar3->Maximun_Size + (int)lpAddress);
    if ((lpAddress <= pvVar1) && (pvVar1 < pvVar2)) break;
    pVVar3 = pVVar3->Next;
  }
  VirtualQuery(lpAddress,&local_20,0x1c);
  if ((LPVOID)((int)pvVar2 - pVVar3->Page_Size) <=
      (LPVOID)((int)local_20.BaseAddress + local_20.RegionSize)) {
    DEBUG_systemWarning("Virtual Access Violation Error Cr2=%p, Aborting Program");
    return 0;
  }
  VirtualAlloc((LPVOID)((int)local_20.BaseAddress + local_20.RegionSize),pVVar3->Page_Size,0x1000,4)
  ;
  return -1;
}
