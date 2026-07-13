/*
 * Entry: 004e7be7
 * Name: Cache_Create_Bsp_Heap
 * Namespace: Global
 * Signature: int Cache_Create_Bsp_Heap(long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Cache_Create_Bsp_Heap(long param_1)

{
  MACHINE_CAPS *pMVar1;
  int iVar2;
  ulong *puVar3;
  MACHINE_CAPS local_34;
  ulong local_1c [6];
  
  pMVar1 = GetMachineCaps(&local_34);
  LOD = -1;
  puVar3 = local_1c;
  for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = pMVar1->PhysicalRAM;
    pMVar1 = (MACHINE_CAPS *)&pMVar1->VideoRAM;
    puVar3 = puVar3 + 1;
  }
  Bsp_Heap_Handle = (void *)0x1;
  Entity_Vertex_Count = 0;
  Moving_Objects_Counter = 0;
  Poly_Base_Ptr = 0;
  Active_Entity_Counter = 0;
  Poly_Leading_Ptr = (BSP_POLYGON *)0x0;
  Root_Polygon = (BSP_POLYGON *)0x0;
  Local_Camera = (CAMERA *)0x0;
  Bsp_Moving_Objects = (MATRIX_LIST *)0x0;
  Current_Entity = (tagENTITY *)0x0;
  return 1;
}
