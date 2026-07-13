/*
 * Entry: 004e80cf
 * Name: Cache_Sorting_Planes
 * Namespace: Global
 * Signature: void Cache_Sorting_Planes(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Cache_Sorting_Planes(_OBJ76 *param_1)

{
  GeoCache_SelectLOD(param_1,LOD);
  if (param_1->geom != (_GEOMETRY *)0x0) {
    Cache_SortingPlanes_To_Bsp_Tree(param_1);
  }
  return;
}
