/*
 * Entry: 0054c343
 * Name: Vector_Transform
 * Namespace: Global
 * Signature: void Vector_Transform(VECTOR_3D * param_1, VECTOR_3D * param_2, long param_3, MAT_3D * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Vector_Transform(VECTOR_3D *param_1,VECTOR_3D *param_2,long param_3,MAT_3D *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  double dVar13;
  double dVar14;
  bool bVar15;
  
  bVar15 = false;
  for (; param_3 != 0 && bVar15 == param_3 < 0; param_3 = param_3 + -1) {
    fVar1 = param_4->right_y;
    fVar2 = param_2->x;
    fVar3 = param_4->right_z;
    fVar4 = param_2->x;
    fVar5 = param_4->up_y;
    fVar6 = param_2->y;
    fVar7 = param_4->up_z;
    fVar8 = param_2->y;
    fVar9 = param_4->front_y;
    fVar10 = param_2->z;
    fVar11 = param_4->front_z;
    fVar12 = param_2->z;
    dVar13 = param_4->posit_y;
    dVar14 = param_4->posit_z;
    param_1->x = param_4->front_x * param_2->z +
                 param_4->up_x * param_2->y + param_4->right_x * param_2->x +
                 (float)param_4->posit_x;
    param_1->z = fVar11 * fVar12 + fVar7 * fVar8 + fVar3 * fVar4 + (float)dVar14;
    param_1->y = fVar9 * fVar10 + fVar5 * fVar6 + fVar1 * fVar2 + (float)dVar13;
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
    bVar15 = SBORROW4(param_3,1);
  }
  return;
}
