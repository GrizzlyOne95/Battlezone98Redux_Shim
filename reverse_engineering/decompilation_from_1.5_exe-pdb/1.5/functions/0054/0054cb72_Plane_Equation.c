/*
 * Entry: 0054cb72
 * Name: Plane_Equation
 * Namespace: Global
 * Signature: PLANE * Plane_Equation(PLANE * __return_storage_ptr__, VECTOR_3D * param_1, VECTOR_3D * param_2, VECTOR_3D * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PLANE * __cdecl
Plane_Equation(PLANE *__return_storage_ptr__,VECTOR_3D *param_1,VECTOR_3D *param_2,
              VECTOR_3D *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  VECTOR_3D *pVVar4;
  VECTOR_3D local_28;
  VECTOR_3D local_1c;
  VECTOR_3D local_10;
  
  local_1c.x = param_2->x - param_1->x;
  local_1c.y = param_2->y - param_1->y;
  local_1c.z = param_2->z - param_1->z;
  local_10.x = param_3->x - param_1->x;
  local_10.y = param_3->y - param_1->y;
  local_10.z = param_3->z - param_1->z;
  pVVar4 = Cross_Product(&local_28,&local_1c,&local_10);
  local_10.x = pVVar4->x;
  local_10.y = pVVar4->y;
  local_10.z = pVVar4->z;
  pVVar4 = Normalize_Vector(&local_28,&local_10);
  fVar1 = pVVar4->x;
  fVar2 = pVVar4->y;
  fVar3 = pVVar4->z;
  (__return_storage_ptr__->surf_normal).x = fVar1;
  (__return_storage_ptr__->surf_normal).y = fVar2;
  (__return_storage_ptr__->surf_normal).z = fVar3;
  __return_storage_ptr__->dist = -(param_1->z * fVar3 + param_1->x * fVar1 + param_1->y * fVar2);
  return __return_storage_ptr__;
}
