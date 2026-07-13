/*
 * Entry: 0045dd1c
 * Name: GetCircularPos
 * Namespace: Global
 * Signature: VECTOR_3D * GetCircularPos(VECTOR_3D * __return_storage_ptr__, VECTOR_3D * param_1, float param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl
GetCircularPos(VECTOR_3D *__return_storage_ptr__,VECTOR_3D *param_1,float param_2,float param_3)

{
  float10 fVar1;
  float10 fVar2;
  float fVar3;
  
  fVar1 = (float10)fcos((float10)param_3);
  fVar1 = fVar1 * (float10)param_2 + (float10)param_1->x;
  __return_storage_ptr__->x = (float)fVar1;
  fVar2 = (float10)fsin((float10)param_3);
  fVar2 = fVar2 * (float10)param_2 + (float10)param_1->z;
  __return_storage_ptr__->z = (float)fVar2;
  fVar3 = Terrain_FindFloor((double)fVar1,(double)fVar2);
  __return_storage_ptr__->y = fVar3;
  return __return_storage_ptr__;
}
