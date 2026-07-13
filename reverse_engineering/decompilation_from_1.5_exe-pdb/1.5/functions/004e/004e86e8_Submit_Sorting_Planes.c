/*
 * Entry: 004e86e8
 * Name: Submit_Sorting_Planes
 * Namespace: Global
 * Signature: void Submit_Sorting_Planes(_OBJ76 * param_1, MAT_3D * param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Submit_Sorting_Planes(_OBJ76 *param_1,MAT_3D *param_2,long param_3)

{
  _OBJ76 *unaff_ESI;
  CAMERA *unaff_retaddr;
  
  GeoCache_SelectLOD(unaff_ESI,LOD);
  if (unaff_ESI->geom != (_GEOMETRY *)0x0) {
    Add_SortingPlane_to_Tree(param_1,(MAT_3D *)Local_Camera,unaff_retaddr);
  }
  return;
}
