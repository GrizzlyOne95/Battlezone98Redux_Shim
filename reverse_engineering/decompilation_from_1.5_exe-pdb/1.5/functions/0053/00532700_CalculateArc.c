/*
 * Entry: 00532700
 * Name: CalculateArc
 * Namespace: Global
 * Signature: VECTOR_3D * CalculateArc(VECTOR_3D * __return_storage_ptr__, VECTOR_3D param_1, VECTOR_3D param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl
CalculateArc(VECTOR_3D *__return_storage_ptr__,VECTOR_3D param_1,VECTOR_3D param_2,float param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  VECTOR_3D *unaff_ESI;
  float fVar7;
  
  fVar1 = param_1.z - (float)__return_storage_ptr__;
  fVar2 = param_2.x - param_1.x;
  fVar6 = param_2.y - param_1.y;
  fVar7 = fVar1 * fVar1 + fVar6 * fVar6;
  fVar5 = 1.0 / fVar7;
  fVar4 = fVar2 * fVar2 * fVar5 + 1.0;
  fVar3 = param_2.z * param_2.z - fVar2 * 9.8;
  fVar7 = max<float>(0.0,fVar3 * fVar3 - fVar7 * 24.01 * fVar4 * 4.0);
  if (0.0 < fVar7) {
    fVar3 = fVar3 - SQRT(fVar7);
  }
  fVar3 = SQRT((fVar3 / (fVar4 + fVar4)) * fVar5);
  unaff_ESI->x = fVar1 * fVar3;
  unaff_ESI->y = 4.9 / fVar3 + fVar2 * fVar3;
  unaff_ESI->z = fVar3 * fVar6;
  return unaff_ESI;
}
