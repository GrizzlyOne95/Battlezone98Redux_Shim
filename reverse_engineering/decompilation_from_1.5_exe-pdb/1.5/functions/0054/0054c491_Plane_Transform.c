/*
 * Entry: 0054c491
 * Name: Plane_Transform
 * Namespace: Global
 * Signature: PLANE * Plane_Transform(PLANE * __return_storage_ptr__, PLANE * param_1, MAT_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PLANE * __cdecl Plane_Transform(PLANE *__return_storage_ptr__,PLANE *param_1,MAT_3D *param_2)

{
  float fVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  fVar5 = param_2->front_x * (param_1->surf_normal).z +
          param_2->up_x * (param_1->surf_normal).y + param_2->right_x * (param_1->surf_normal).x;
  fVar7 = param_2->front_y * (param_1->surf_normal).z +
          param_2->up_y * (param_1->surf_normal).y + param_2->right_y * (param_1->surf_normal).x;
  fVar6 = param_2->front_z * (param_1->surf_normal).z +
          param_2->up_z * (param_1->surf_normal).y + param_2->right_z * (param_1->surf_normal).x;
  dVar2 = param_2->posit_x;
  dVar3 = param_2->posit_y;
  dVar4 = param_2->posit_z;
  (__return_storage_ptr__->surf_normal).x = fVar5;
  (__return_storage_ptr__->surf_normal).z = fVar6;
  fVar1 = param_1->dist;
  (__return_storage_ptr__->surf_normal).y = fVar7;
  __return_storage_ptr__->dist =
       fVar1 - (fVar6 * (float)dVar4 + fVar5 * (float)dVar2 + fVar7 * (float)dVar3);
  return __return_storage_ptr__;
}
