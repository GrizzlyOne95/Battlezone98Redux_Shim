/*
 * Entry: 0054c50c
 * Name: Transform_Plane
 * Namespace: Global
 * Signature: void Transform_Plane(PLANE * param_1, PLANE * param_2, MAT_3D * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Transform_Plane(PLANE *param_1,PLANE *param_2,MAT_3D *param_3)

{
  float fVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  fVar5 = param_3->front_x * (param_2->surf_normal).z +
          param_3->up_x * (param_2->surf_normal).y + param_3->right_x * (param_2->surf_normal).x;
  fVar7 = param_3->front_y * (param_2->surf_normal).z +
          param_3->up_y * (param_2->surf_normal).y + param_3->right_y * (param_2->surf_normal).x;
  fVar6 = param_3->front_z * (param_2->surf_normal).z +
          param_3->up_z * (param_2->surf_normal).y + param_3->right_z * (param_2->surf_normal).x;
  dVar2 = param_3->posit_x;
  dVar3 = param_3->posit_y;
  dVar4 = param_3->posit_z;
  (param_1->surf_normal).x = fVar5;
  (param_1->surf_normal).z = fVar6;
  fVar1 = param_2->dist;
  (param_1->surf_normal).y = fVar7;
  param_1->dist = fVar1 - (fVar6 * (float)dVar4 + fVar5 * (float)dVar2 + fVar7 * (float)dVar3);
  return;
}
