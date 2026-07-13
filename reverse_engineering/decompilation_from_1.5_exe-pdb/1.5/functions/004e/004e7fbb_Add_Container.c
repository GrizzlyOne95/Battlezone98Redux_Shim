/*
 * Entry: 004e7fbb
 * Name: Add_Container
 * Namespace: Global
 * Signature: void Add_Container(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Add_Container(tagENTITY *param_1)

{
  BSP_CONTAINER *pBVar1;
  BSP_CONTAINER *pBVar2;
  BSP_CONTAINER *pBVar3;
  long lVar4;
  
  pBVar2 = malloc(0x1000);
  for (lVar4 = Active_Entity_Counter; 0 < lVar4; lVar4 = lVar4 + -1) {
    if (pBVar2 != (BSP_CONTAINER *)0x0) goto LAB_004e7ffd;
    LRU_Replace_Container();
    pBVar2 = malloc(0x1000);
  }
  if (pBVar2 == (BSP_CONTAINER *)0x0) {
    DEBUG_systemError("Bsp Cache Geometry failure. See Julio...");
  }
LAB_004e7ffd:
  pBVar2->Next = (BSP_CONTAINER *)0x0;
  pBVar2->Bsp_Geom = (BSP_POLYGON *)0x0;
  Poly_Leading_Ptr = (BSP_POLYGON *)(pBVar2 + 1);
  pBVar1 = param_1->Bsp_Container;
  Poly_Base_Ptr = (long)pBVar2;
  if (param_1->Bsp_Container == (BSP_CONTAINER *)0x0) {
    param_1->Bsp_Container = pBVar2;
  }
  else {
    do {
      pBVar3 = pBVar1;
      pBVar1 = pBVar3->Next;
    } while (pBVar1 != (BSP_CONTAINER *)0x0);
    pBVar3->Next = pBVar2;
  }
  return;
}
