/*
 * Entry: 005ae8a0
 * Name: mdct_bitreverse
 * Namespace: Global
 * Signature: void mdct_bitreverse(mdct_lookup * param_1, float * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl mdct_bitreverse(mdct_lookup *param_1,float *param_2)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int *in_EAX;
  float *pfVar8;
  float *pfVar9;
  float *in_EDX;
  float *pfVar10;
  float *pfVar11;
  int *piVar12;
  int iVar13;
  
  piVar12 = (int *)in_EAX[3];
  iVar13 = *in_EAX >> 1;
  pfVar8 = (float *)(in_EAX[2] + *in_EAX * 4);
  pfVar9 = in_EDX + iVar13 + 3;
  pfVar10 = in_EDX;
  do {
    pfVar1 = in_EDX + iVar13 + *piVar12;
    pfVar2 = in_EDX + iVar13 + piVar12[1];
    fVar4 = (in_EDX[iVar13 + *piVar12 + 1] - in_EDX[iVar13 + piVar12[1] + 1]) * pfVar8[1] +
            (*pfVar2 + *pfVar1) * *pfVar8;
    fVar5 = (*pfVar2 + *pfVar1) * pfVar8[1] -
            *pfVar8 * (in_EDX[iVar13 + *piVar12 + 1] - in_EDX[iVar13 + piVar12[1] + 1]);
    fVar6 = (pfVar2[1] + pfVar1[1]) * 0.5;
    fVar7 = (*pfVar1 - *pfVar2) * 0.5;
    *pfVar10 = fVar6 + fVar4;
    pfVar9[-5] = fVar6 - fVar4;
    pfVar10[1] = fVar7 + fVar5;
    pfVar9[-4] = fVar5 - fVar7;
    pfVar2 = in_EDX + iVar13 + piVar12[2];
    pfVar3 = in_EDX + iVar13 + piVar12[3];
    fVar6 = (in_EDX[iVar13 + piVar12[2] + 1] - in_EDX[iVar13 + piVar12[3] + 1]) * pfVar8[3] +
            (*pfVar3 + *pfVar2) * pfVar8[2];
    fVar7 = pfVar8[3] * (*pfVar3 + *pfVar2) -
            (in_EDX[iVar13 + piVar12[2] + 1] - in_EDX[iVar13 + piVar12[3] + 1]) * pfVar8[2];
    fVar4 = (pfVar3[1] + pfVar2[1]) * 0.5;
    pfVar11 = pfVar10 + 4;
    pfVar1 = pfVar9 + -7;
    pfVar8 = pfVar8 + 4;
    piVar12 = piVar12 + 4;
    fVar5 = (*pfVar2 - *pfVar3) * 0.5;
    pfVar10[2] = fVar4 + fVar6;
    pfVar9[-7] = fVar4 - fVar6;
    pfVar10[3] = fVar5 + fVar7;
    pfVar9[-6] = fVar7 - fVar5;
    pfVar9 = pfVar9 + -4;
    pfVar10 = pfVar11;
  } while (pfVar11 < pfVar1);
  return;
}
