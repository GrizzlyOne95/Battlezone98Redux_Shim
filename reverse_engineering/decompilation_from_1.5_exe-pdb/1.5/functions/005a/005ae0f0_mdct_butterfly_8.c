/*
 * Entry: 005ae0f0
 * Name: mdct_butterfly_8
 * Namespace: Global
 * Signature: void mdct_butterfly_8(float * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl mdct_butterfly_8(float *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float *in_EAX;
  
  fVar1 = in_EAX[6];
  fVar2 = in_EAX[6];
  fVar3 = in_EAX[4];
  fVar4 = *in_EAX;
  in_EAX[6] = fVar1 + in_EAX[2] + *in_EAX + in_EAX[4];
  in_EAX[4] = (fVar1 + in_EAX[2]) - (*in_EAX + in_EAX[4]);
  fVar1 = in_EAX[3];
  *in_EAX = (in_EAX[5] - in_EAX[1]) + (fVar2 - in_EAX[2]);
  in_EAX[2] = (fVar2 - in_EAX[2]) - (in_EAX[5] - in_EAX[1]);
  fVar2 = in_EAX[1];
  fVar5 = in_EAX[7];
  fVar6 = in_EAX[3];
  in_EAX[3] = (in_EAX[7] - fVar1) + (fVar3 - fVar4);
  in_EAX[1] = (in_EAX[7] - fVar1) - (fVar3 - fVar4);
  in_EAX[7] = in_EAX[5] + fVar2 + fVar5 + fVar6;
  in_EAX[5] = (fVar5 + fVar6) - (in_EAX[5] + fVar2);
  return;
}
