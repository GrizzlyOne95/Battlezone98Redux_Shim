/*
 * Entry: 004e7f3b
 * Name: Cache_Delete_Bsp_Heap
 * Namespace: Global
 * Signature: void Cache_Delete_Bsp_Heap(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Cache_Delete_Bsp_Heap(void)

{
  BSP_CONTAINER *pBVar1;
  BSP_CONTAINER *_Memory;
  tagENTITY *ptVar2;
  
  reset_entity_pointer();
  ptVar2 = get_entity();
  while (ptVar2 != (tagENTITY *)0x0) {
    _Memory = ptVar2->Bsp_Container;
    while (_Memory != (BSP_CONTAINER *)0x0) {
      pBVar1 = _Memory->Next;
      free(_Memory);
      _Memory = pBVar1;
    }
    ptVar2->Bsp_Container = (BSP_CONTAINER *)0x0;
    ptVar2 = get_entity();
  }
  return;
}
