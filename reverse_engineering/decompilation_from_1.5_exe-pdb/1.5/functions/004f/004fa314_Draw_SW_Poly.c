/*
 * Entry: 004fa314
 * Name: Draw_SW_Poly
 * Namespace: Global
 * Signature: void Draw_SW_Poly(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4, long param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Draw_SW_Poly(_GRAPHIC_BUFFER *param_1,POINT_3D *param_2,long param_3,POLYGON_SKIN param_4,
            long param_5)

{
  int unaff_ESI;
  
  Set_Rounding(unaff_ESI);
  (*Draw_3d_Poly_Vtltbl[param_5])(param_1,param_2,param_3,param_4);
  Set_Rounding((int)param_1);
  return;
}
