/*
 * Entry: 00474add
 * Name: Cgeom_PolyHeight
 * Namespace: Global
 * Signature: float Cgeom_PolyHeight(_clsn_poly * param_1, float param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Cgeom_PolyHeight(_clsn_poly *param_1,float param_2,float param_3)

{
  return -(((param_1->plane).surf_normal.x * param_2 + (param_1->plane).surf_normal.z * param_3 +
           (param_1->plane).dist) / (param_1->plane).surf_normal.y);
}
