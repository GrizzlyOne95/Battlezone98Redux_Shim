/*
 * Entry: 004e8086
 * Name: Cache_SortingPlanes_To_Bsp_Tree
 * Namespace: Global
 * Signature: void Cache_SortingPlanes_To_Bsp_Tree(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Cache_SortingPlanes_To_Bsp_Tree(_OBJ76 *param_1)

{
  FACE *pFVar1;
  BSP_POLYGON *pBVar2;
  BSP_POLYGON *unaff_EDI;
  
  for (pFVar1 = param_1->geom->faces; pFVar1 != (FACE *)0x0; pFVar1 = pFVar1->front_facet) {
    pBVar2 = Cache_MakeSortingPlane(pFVar1);
    if (Root_Polygon == (BSP_POLYGON *)0x0) {
      Root_Polygon = Poly_Leading_Ptr;
    }
    else {
      Polygon_To_Cache_List(unaff_EDI);
    }
    Poly_Leading_Ptr = pBVar2;
  }
  return;
}
