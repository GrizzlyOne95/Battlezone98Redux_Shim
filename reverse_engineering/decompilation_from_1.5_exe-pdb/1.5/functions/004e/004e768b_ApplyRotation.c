/*
 * Entry: 004e768b
 * Name: ApplyRotation
 * Namespace: Global
 * Signature: void ApplyRotation(MAT_3D * param_1, float * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ApplyRotation(MAT_3D *param_1,float *param_2)

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
  float *in_EAX;
  float *in_ECX;
  
  fVar1 = in_EAX[1] * in_EAX[1] * 2.0;
  fVar9 = in_EAX[2] * in_EAX[1] * 2.0;
  fVar8 = in_EAX[3] * in_EAX[1] * 2.0;
  fVar2 = in_EAX[2] * in_EAX[2] * 2.0;
  fVar3 = in_EAX[3] * in_EAX[2] * 2.0;
  fVar4 = in_EAX[3] * in_EAX[3] * 2.0;
  fVar5 = *in_EAX * in_EAX[1] * 2.0;
  fVar6 = in_EAX[2] * *in_EAX * 2.0;
  fVar7 = in_EAX[3] * *in_EAX * 2.0;
  *in_ECX = 1.0 - (fVar4 + fVar2);
  in_ECX[1] = fVar9 - fVar7;
  in_ECX[2] = fVar6 + fVar8;
  in_ECX[3] = fVar7 + fVar9;
  in_ECX[4] = 1.0 - (fVar4 + fVar1);
  in_ECX[5] = fVar3 - fVar5;
  in_ECX[6] = fVar8 - fVar6;
  in_ECX[7] = fVar5 + fVar3;
  in_ECX[8] = 1.0 - (fVar2 + fVar1);
  return;
}
