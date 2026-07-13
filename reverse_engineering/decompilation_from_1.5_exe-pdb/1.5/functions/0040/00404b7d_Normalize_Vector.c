/*
 * Entry: 00404b7d
 * Name: Normalize_Vector
 * Namespace: Global
 * Signature: VECTOR_3D * Normalize_Vector(VECTOR_3D * __return_storage_ptr__, VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl Normalize_Vector(VECTOR_3D *__return_storage_ptr__,VECTOR_3D *param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = param_1->x * param_1->x + param_1->y * param_1->y + param_1->z * param_1->z;
  if (0.0 < fVar1) {
    dVar2 = rsqrt((double)fVar1);
    fVar1 = (float)dVar2;
    __return_storage_ptr__->x = param_1->x * fVar1;
    __return_storage_ptr__->y = param_1->y * fVar1;
    __return_storage_ptr__->z = fVar1 * param_1->z;
    return __return_storage_ptr__;
  }
  __return_storage_ptr__->z = 0.0;
  __return_storage_ptr__->y = 0.0;
  __return_storage_ptr__->x = 0.0;
  return __return_storage_ptr__;
}
