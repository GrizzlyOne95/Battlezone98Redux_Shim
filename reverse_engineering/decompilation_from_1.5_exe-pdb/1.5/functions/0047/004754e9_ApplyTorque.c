/*
 * Entry: 004754e9
 * Name: ApplyTorque
 * Namespace: Global
 * Signature: void ApplyTorque(VECTOR_3D * param_1, VECTOR_3D * param_2, VECTOR_3D param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ApplyTorque(VECTOR_3D *param_1,VECTOR_3D *param_2,VECTOR_3D param_3,float param_4)

{
  VECTOR_3D *pVVar1;
  VECTOR_3D local_28;
  VECTOR_3D local_1c;
  float local_10;
  float local_c;
  float local_8;
  
  pVVar1 = ScaleVector(&local_28,param_4,param_3);
  local_10 = pVVar1->x;
  local_c = pVVar1->y;
  local_8 = pVVar1->z;
  pVVar1 = AddMultVectors(&local_28,*param_2,0.5,*pVVar1);
  pVVar1 = ScaleVector(&local_1c,param_4,*pVVar1);
  param_1->x = pVVar1->x;
  param_1->y = pVVar1->y;
  param_1->z = pVVar1->z;
  param_2->x = local_10 + param_2->x;
  param_2->y = local_c + param_2->y;
  param_2->z = local_8 + param_2->z;
  return;
}
