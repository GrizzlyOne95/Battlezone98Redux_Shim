/*
 * Entry: 005ae4d0
 * Name: mdct_butterfly_first
 * Namespace: Global
 * Signature: void mdct_butterfly_first(float * param_1, float * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl mdct_butterfly_first(float *param_1,float *param_2,int param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float *pfVar5;
  float *pfVar6;
  int in_ECX;
  float *pfVar7;
  float *in_EDX;
  float *unaff_EDI;
  
  pfVar5 = unaff_EDI + (in_ECX >> 1) + -8;
  pfVar7 = unaff_EDI + (in_ECX >> 1) + -8 + (in_ECX - (in_ECX >> 1)) + 7;
  do {
    fVar1 = pfVar7[-1];
    fVar2 = pfVar5[6];
    fVar3 = *pfVar7;
    fVar4 = pfVar5[7];
    pfVar7[-1] = pfVar5[6] + pfVar7[-1];
    *pfVar7 = pfVar5[7] + *pfVar7;
    pfVar5[6] = (fVar3 - fVar4) * in_EDX[1] + (fVar1 - fVar2) * *in_EDX;
    pfVar5[7] = (fVar3 - fVar4) * *in_EDX - in_EDX[1] * (fVar1 - fVar2);
    fVar1 = pfVar7[-3];
    fVar2 = pfVar5[4];
    fVar3 = pfVar7[-2];
    fVar4 = pfVar5[5];
    pfVar7[-3] = pfVar5[4] + pfVar7[-3];
    pfVar7[-2] = pfVar7[-2] + pfVar5[5];
    pfVar5[4] = (fVar1 - fVar2) * in_EDX[4] + (fVar3 - fVar4) * in_EDX[5];
    pfVar5[5] = in_EDX[4] * (fVar3 - fVar4) - (fVar1 - fVar2) * in_EDX[5];
    fVar1 = pfVar7[-5];
    fVar2 = pfVar5[2];
    fVar3 = pfVar7[-4];
    fVar4 = pfVar5[3];
    pfVar7[-5] = pfVar7[-5] + pfVar5[2];
    pfVar7[-4] = pfVar7[-4] + pfVar5[3];
    pfVar5[2] = (fVar3 - fVar4) * in_EDX[9] + (fVar1 - fVar2) * in_EDX[8];
    pfVar6 = pfVar5 + -8;
    pfVar5[3] = in_EDX[8] * (fVar3 - fVar4) - (fVar1 - fVar2) * in_EDX[9];
    fVar1 = pfVar7[-7];
    fVar2 = *pfVar5;
    fVar3 = pfVar7[-6];
    fVar4 = pfVar5[1];
    pfVar7[-7] = *pfVar5 + pfVar7[-7];
    pfVar7[-6] = pfVar5[1] + pfVar7[-6];
    *pfVar5 = (fVar3 - fVar4) * in_EDX[0xd] + (fVar1 - fVar2) * in_EDX[0xc];
    pfVar5[1] = in_EDX[0xc] * (fVar3 - fVar4) - (fVar1 - fVar2) * in_EDX[0xd];
    pfVar5 = pfVar6;
    pfVar7 = pfVar7 + -8;
    in_EDX = in_EDX + 0x10;
  } while (unaff_EDI <= pfVar6);
  return;
}
