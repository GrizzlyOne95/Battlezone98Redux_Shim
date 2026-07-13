/*
 * Entry: 004e74c2
 * Name: SLERP
 * Namespace: Global
 * Signature: void SLERP(float * param_1, float param_2, float * param_3, float * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SLERP(float *param_1,float param_2,float *param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  float *in_ECX;
  float *unaff_ESI;
  float *unaff_EDI;
  float10 fVar3;
  float10 fVar4;
  float10 fVar5;
  float local_10;
  float local_c;
  float local_8;
  
  fVar2 = unaff_EDI[3] * in_ECX[3] +
          *in_ECX * *unaff_EDI + in_ECX[1] * unaff_EDI[1] + in_ECX[2] * unaff_EDI[2];
  fVar1 = *in_ECX;
  if (0.0 <= fVar2) {
    local_10 = in_ECX[1];
    local_c = in_ECX[2];
    local_8 = in_ECX[3];
  }
  else {
    fVar1 = -fVar1;
    local_10 = -in_ECX[1];
    local_c = -in_ECX[2];
    local_8 = -in_ECX[3];
    fVar2 = -fVar2;
  }
  if ((((1e-05 < 1.0 - fVar2) && (fVar1 != 0.0)) && (fVar1 != 1.0)) &&
     ((*unaff_EDI != 0.0 && (*unaff_EDI != 1.0)))) {
    fVar3 = (float10)__CIacos();
    fVar4 = (float10)fsin(fVar3);
    fVar4 = (float10)1 / fVar4;
    fVar5 = (float10)fsin(((float10)1 - (float10)(float)param_1) * fVar3);
    fVar5 = fVar5 * fVar4;
    fVar3 = (float10)fsin(fVar3 * (float10)(float)param_1);
    fVar3 = fVar3 * fVar4;
    unaff_ESI[1] = (float)(fVar3 * (float10)unaff_EDI[1] + fVar5 * (float10)local_10);
    unaff_ESI[2] = (float)(fVar3 * (float10)unaff_EDI[2] + fVar5 * (float10)local_c);
    unaff_ESI[3] = (float)(fVar5 * (float10)local_8 + (float10)unaff_EDI[3] * fVar3);
    *unaff_ESI = (float)(fVar5 * (float10)fVar1 + fVar3 * (float10)*unaff_EDI);
    return;
  }
  fVar2 = 1.0 - (float)param_1;
  unaff_ESI[1] = (float)param_1 * unaff_EDI[1] + fVar2 * local_10;
  unaff_ESI[2] = (float)param_1 * unaff_EDI[2] + fVar2 * local_c;
  unaff_ESI[3] = fVar2 * local_8 + unaff_EDI[3] * (float)param_1;
  fVar1 = (float)param_1 * *unaff_EDI + fVar2 * fVar1;
  *unaff_ESI = fVar1;
  fVar1 = 1.0 / SQRT(unaff_ESI[3] * unaff_ESI[3] +
                     unaff_ESI[2] * unaff_ESI[2] + unaff_ESI[1] * unaff_ESI[1] + fVar1 * fVar1);
  *unaff_ESI = *unaff_ESI * fVar1;
  unaff_ESI[1] = unaff_ESI[1] * fVar1;
  unaff_ESI[2] = fVar1 * unaff_ESI[2];
  unaff_ESI[3] = fVar1 * unaff_ESI[3];
  return;
}
