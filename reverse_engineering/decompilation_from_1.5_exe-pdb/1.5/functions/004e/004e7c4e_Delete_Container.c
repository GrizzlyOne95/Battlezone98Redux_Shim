/*
 * Entry: 004e7c4e
 * Name: Delete_Container
 * Namespace: Global
 * Signature: void Delete_Container(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Delete_Container(tagENTITY *param_1)

{
  BSP_CONTAINER *pBVar1;
  BSP_CONTAINER *_Memory;
  int iVar2;
  int iVar3;
  
  _Memory = param_1->Bsp_Container;
  iVar2 = Active_Entity_Counter;
  while (Active_Entity_Counter = iVar2, _Memory != (BSP_CONTAINER *)0x0) {
    pBVar1 = _Memory->Next;
    free(_Memory);
    _Memory = pBVar1;
    iVar2 = Active_Entity_Counter;
  }
  param_1->Bsp_Container = (BSP_CONTAINER *)0x0;
  iVar3 = 0;
  if (0 < iVar2) {
    while (Active_Entity_Heap[iVar3] != param_1) {
      iVar3 = iVar3 + 1;
      if (iVar2 <= iVar3) {
        return;
      }
    }
    Active_Entity_Counter = iVar2 + -1;
    Active_Entity_Heap[iVar3] = Active_Entity_Heap[Active_Entity_Counter];
  }
  return;
}
