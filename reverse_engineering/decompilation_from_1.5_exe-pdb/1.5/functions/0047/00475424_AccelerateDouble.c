/*
 * Entry: 00475424
 * Name: AccelerateDouble
 * Namespace: Global
 * Signature: void AccelerateDouble(VECTOR_3D_LONG * param_1, VECTOR_3D * param_2, VECTOR_3D * param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
AccelerateDouble(VECTOR_3D_LONG *param_1,VECTOR_3D *param_2,VECTOR_3D *param_3,float param_4)

{
  float fVar1;
  float fVar2;
  VECTOR_3D *pVVar3;
  VECTOR_3D local_34;
  VECTOR_3D local_28;
  float local_1c;
  float local_18;
  float local_14;
  
  pVVar3 = ScaleVector(&local_28,param_4,*param_3);
  local_1c = pVVar3->x;
  local_18 = pVVar3->y;
  local_14 = pVVar3->z;
  pVVar3 = AddMultVectors(&local_28,*param_2,0.5,*pVVar3);
  pVVar3 = ScaleVector(&local_34,param_4,*pVVar3);
  fVar1 = pVVar3->y;
  fVar2 = pVVar3->z;
  param_1->x = (double)(pVVar3->x + (float)param_1->x);
  param_1->y = (double)(fVar1 + (float)param_1->y);
  param_1->z = (double)(fVar2 + (float)param_1->z);
  param_2->x = local_1c + param_2->x;
  param_2->y = local_18 + param_2->y;
  param_2->z = local_14 + param_2->z;
  return;
}
