/*
 * Entry: 00521736
 * Name: GetTerrainExtents
 * Namespace: Global
 * Signature: void GetTerrainExtents(VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GetTerrainExtents(VECTOR_3D *param_1)

{
  param_1->x = TerMinX;
  param_1[1].x = TerMaxX;
  param_1->y = TerMinY;
  param_1[1].y = TerMaxY;
  param_1->z = TerMinZ;
  param_1[1].z = TerMaxZ;
  return;
}
