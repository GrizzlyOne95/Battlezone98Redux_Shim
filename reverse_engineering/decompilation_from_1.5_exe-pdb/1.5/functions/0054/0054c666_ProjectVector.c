/*
 * Entry: 0054c666
 * Name: ProjectVector
 * Namespace: Global
 * Signature: void ProjectVector(VECTOR_3D param_1, VECTOR_3D param_2, VECTOR_3D * param_3, VECTOR_3D * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
ProjectVector(VECTOR_3D param_1,VECTOR_3D param_2,VECTOR_3D *param_3,VECTOR_3D *param_4)

{
  float fVar1;
  float fVar2;
  VECTOR_3D *pVVar3;
  VECTOR_3D local_1c [2];
  
  pVVar3 = ScaleVector(local_1c,(param_2.x * param_1.x +
                                param_2.y * param_1.y + param_2.z * param_1.z) /
                                (param_2.x * param_2.x +
                                param_2.y * param_2.y + param_2.z * param_2.z),param_2);
  param_3->x = pVVar3->x;
  param_3->y = pVVar3->y;
  param_3->z = pVVar3->z;
  fVar1 = pVVar3->y;
  fVar2 = pVVar3->z;
  param_4->x = param_1.x - pVVar3->x;
  param_4->y = param_1.y - fVar1;
  param_4->z = param_1.z - fVar2;
  return;
}
