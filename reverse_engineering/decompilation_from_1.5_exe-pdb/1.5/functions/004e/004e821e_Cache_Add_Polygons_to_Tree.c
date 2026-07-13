/*
 * Entry: 004e821e
 * Name: Cache_Add_Polygons_to_Tree
 * Namespace: Global
 * Signature: void Cache_Add_Polygons_to_Tree(_OBJ76 * param_1, MAT_3D * param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Cache_Add_Polygons_to_Tree(_OBJ76 *param_1,MAT_3D *param_2,long param_3)

{
  FACE *pFVar1;
  BSP_POLYGON *pBVar2;
  BSP_POLYGON *unaff_EDI;
  
  for (pFVar1 = param_1->geom->faces; pFVar1 != (FACE *)0x0; pFVar1 = pFVar1->front_facet) {
    pBVar2 = Cache_Make_Poly(param_1,pFVar1,param_2,param_3);
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
