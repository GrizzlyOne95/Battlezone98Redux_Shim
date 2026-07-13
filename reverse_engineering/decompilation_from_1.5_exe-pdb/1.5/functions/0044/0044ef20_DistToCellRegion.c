/*
 * Entry: 0044ef20
 * Name: DistToCellRegion
 * Namespace: Global
 * Signature: float DistToCellRegion(uchar param_1, VECTOR_3D_LONG * param_2, VECTOR_3D * param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl
DistToCellRegion(uchar param_1,VECTOR_3D_LONG *param_2,VECTOR_3D *param_3,float param_4)

{
  uchar in_AL;
  VECTOR_3D_LONG *in_ECX;
  VECTOR_3D *in_EDX;
  undefined3 in_stack_00000005;
  
  cellRegion0 = in_AL;
  Terrain_FindChange(*in_ECX,*in_EDX,CellRegionChange,(float *)&param_1);
  return _param_1;
}
