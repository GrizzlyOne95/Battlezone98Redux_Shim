/*
 * Entry: 00582dc3
 * Name: Virtual_Memory_Free
 * Namespace: Global
 * Signature: void Virtual_Memory_Free(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Virtual_Memory_Free(void *param_1)

{
  VIRTUAL_MEMORY_CHAIN **ppVVar1;
  VIRTUAL_MEMORY_CHAIN *pVVar2;
  VIRTUAL_MEMORY_CHAIN *_Memory;
  
  pVVar2 = (VIRTUAL_MEMORY_CHAIN *)0x0;
  _Memory = Virtual_Mem_Handle;
  if (Virtual_Mem_Handle != (VIRTUAL_MEMORY_CHAIN *)0x0) {
    while (_Memory->Base_Address != param_1) {
      ppVVar1 = &_Memory->Next;
      pVVar2 = _Memory;
      _Memory = *ppVVar1;
      if (*ppVVar1 == (VIRTUAL_MEMORY_CHAIN *)0x0) {
        return;
      }
    }
    if (pVVar2 == (VIRTUAL_MEMORY_CHAIN *)0x0) {
      Virtual_Mem_Handle = _Memory->Next;
    }
    else {
      pVVar2->Next = _Memory->Next;
    }
    VirtualFree(param_1,0,0x8000);
    if (hDefaultHeap != (void *)0x0) {
      free(_Memory);
    }
  }
  return;
}
