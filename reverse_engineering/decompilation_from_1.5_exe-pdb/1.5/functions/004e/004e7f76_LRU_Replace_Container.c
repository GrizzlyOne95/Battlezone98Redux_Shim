/*
 * Entry: 004e7f76
 * Name: LRU_Replace_Container
 * Namespace: Global
 * Signature: void LRU_Replace_Container(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl LRU_Replace_Container(void)

{
  tagENTITY *ptVar1;
  ulong uVar2;
  int iVar3;
  int iVar4;
  
  uVar2 = Get_Frame_Count();
  iVar4 = -1;
  iVar3 = 0;
  if (0 < Active_Entity_Counter) {
    do {
      if (Active_Entity_Heap[iVar3]->Bsp_LRU_Stamp < (int)uVar2) {
        uVar2 = Active_Entity_Heap[iVar3]->Bsp_LRU_Stamp;
        iVar4 = iVar3;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < Active_Entity_Counter);
  }
  ptVar1 = Active_Entity_Heap[iVar4];
  Cache_Invalidate_Bsp(ptVar1);
  Delete_Container(ptVar1);
  return;
}
