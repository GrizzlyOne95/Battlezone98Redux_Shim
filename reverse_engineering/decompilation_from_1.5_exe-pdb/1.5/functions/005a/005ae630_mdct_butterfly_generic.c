/*
 * Entry: 005ae630
 * Name: mdct_butterfly_generic
 * Namespace: Global
 * Signature: void mdct_butterfly_generic(float * param_1, float * param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl mdct_butterfly_generic(float *param_1,float *param_2,int param_3,int param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float *pfVar5;
  int in_ECX;
  float *pfVar6;
  float *in_EDX;
  float *pfVar7;
  float *pfVar8;
  float *pfVar9;
  float *unaff_EBX;
  
  pfVar5 = unaff_EBX + (in_ECX >> 1) + -8;
  pfVar6 = unaff_EBX + (in_ECX >> 1) + -8 + (in_ECX - (in_ECX >> 1)) + 7;
  do {
    fVar1 = pfVar6[-1];
    fVar2 = pfVar5[6];
    fVar3 = *pfVar6;
    fVar4 = pfVar5[7];
    pfVar6[-1] = pfVar5[6] + pfVar6[-1];
    *pfVar6 = pfVar5[7] + *pfVar6;
    pfVar5[6] = (fVar3 - fVar4) * in_EDX[1] + (fVar1 - fVar2) * *in_EDX;
    pfVar7 = in_EDX + (int)param_1;
    pfVar5[7] = (fVar3 - fVar4) * *in_EDX - in_EDX[1] * (fVar1 - fVar2);
    fVar1 = pfVar6[-3];
    fVar2 = pfVar5[4];
    fVar3 = pfVar6[-2];
    fVar4 = pfVar5[5];
    pfVar6[-3] = pfVar5[4] + pfVar6[-3];
    pfVar6[-2] = pfVar5[5] + pfVar6[-2];
    pfVar5[4] = (fVar3 - fVar4) * pfVar7[1] + (fVar1 - fVar2) * *pfVar7;
    pfVar8 = pfVar7 + (int)param_1;
    pfVar5[5] = (fVar3 - fVar4) * *pfVar7 - pfVar7[1] * (fVar1 - fVar2);
    fVar1 = pfVar6[-5];
    fVar2 = pfVar5[2];
    fVar3 = pfVar6[-4];
    fVar4 = pfVar5[3];
    pfVar6[-5] = pfVar5[2] + pfVar6[-5];
    pfVar6[-4] = pfVar6[-4] + pfVar5[3];
    pfVar5[2] = (fVar3 - fVar4) * pfVar8[1] + (fVar1 - fVar2) * *pfVar8;
    pfVar7 = pfVar5 + -8;
    pfVar9 = pfVar8 + (int)param_1;
    pfVar5[3] = (fVar3 - fVar4) * *pfVar8 - pfVar8[1] * (fVar1 - fVar2);
    fVar1 = pfVar6[-7];
    fVar2 = *pfVar5;
    fVar3 = pfVar6[-6];
    fVar4 = pfVar5[1];
    pfVar6[-7] = *pfVar5 + pfVar6[-7];
    pfVar6[-6] = pfVar5[1] + pfVar6[-6];
    *pfVar5 = (fVar3 - fVar4) * pfVar9[1] + (fVar1 - fVar2) * *pfVar9;
    in_EDX = pfVar9 + (int)param_1;
    pfVar5[1] = (fVar3 - fVar4) * *pfVar9 - pfVar9[1] * (fVar1 - fVar2);
    pfVar5 = pfVar7;
    pfVar6 = pfVar6 + -8;
  } while (unaff_EBX <= pfVar7);
  return;
}
