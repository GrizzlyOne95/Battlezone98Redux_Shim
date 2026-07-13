/*
 * Entry: 004e8369
 * Name: Cache_Add_All_Moving_Parts
 * Namespace: Global
 * Signature: void Cache_Add_All_Moving_Parts(MATRIX_LIST * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Cache_Add_All_Moving_Parts(MATRIX_LIST *param_1,long param_2)

{
  BSP_POLYGON *pBVar1;
  MAT_3D *pMVar2;
  BSP_POLYGON *unaff_EDI;
  
  if (0 < param_2) {
    do {
      pMVar2 = &param_1->Mat;
      pBVar1 = Cache_Make_Object_Bsp(*(_OBJ76 **)((int)(pMVar2 + -1) + 0x3c),pMVar2);
      if (Root_Polygon == (BSP_POLYGON *)0x0) {
        Root_Polygon = Poly_Leading_Ptr;
      }
      else {
        Polygon_To_Cache_List(unaff_EDI);
      }
      param_1 = (MATRIX_LIST *)(pMVar2 + 1);
      param_2 = param_2 + -1;
      Poly_Leading_Ptr = pBVar1;
    } while (param_2 != 0);
  }
  return;
}
