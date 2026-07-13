/*
 * Entry: 00540bef
 * Name: Draw_D3D_Poly
 * Namespace: Global
 * Signature: void Draw_D3D_Poly(POINT_3D * param_1, long param_2, POLYGON_SKIN param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Draw_D3D_Poly(POINT_3D *param_1,long param_2,POLYGON_SKIN param_3,long param_4)

{
  int unaff_ESI;
  
  Set_Rounding(unaff_ESI);
  (*Submit_D3D_TL_Vtltbl[param_4 & 0xff])(param_1,param_2,param_3);
  Set_Rounding((int)param_1);
  return;
}
