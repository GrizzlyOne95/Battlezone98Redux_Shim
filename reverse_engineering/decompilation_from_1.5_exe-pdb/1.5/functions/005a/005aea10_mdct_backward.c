/*
 * Entry: 005aea10
 * Name: mdct_backward
 * Namespace: Global
 * Signature: void mdct_backward(mdct_lookup * param_1, float * param_2, float * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl mdct_backward(mdct_lookup *param_1,float *param_2,float *param_3)

{
  float fVar1;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  float *unaff_ESI;
  float *pfVar9;
  mdct_lookup *unaff_EDI;
  float *pfVar10;
  
  iVar2 = param_1->n >> 2;
  pfVar9 = (float *)(param_1->n >> 1);
  pfVar4 = param_3 + iVar2 + (int)pfVar9;
  pfVar3 = param_1->trig + iVar2;
  pfVar5 = param_2 + (int)pfVar9 + -7;
  pfVar8 = pfVar4;
  do {
    pfVar10 = pfVar5 + -8;
    pfVar8[-4] = -pfVar5[2] * pfVar3[3] - *pfVar5 * pfVar3[2];
    pfVar8[-3] = *pfVar5 * pfVar3[3] - pfVar3[2] * pfVar5[2];
    pfVar8[-2] = -pfVar5[6] * pfVar3[1] - *pfVar3 * pfVar5[4];
    pfVar8[-1] = pfVar3[1] * pfVar5[4] - pfVar5[6] * *pfVar3;
    pfVar3 = pfVar3 + 4;
    pfVar5 = pfVar10;
    pfVar8 = pfVar8 + -4;
  } while (param_2 <= pfVar10);
  pfVar3 = param_1->trig + iVar2;
  pfVar5 = param_2 + (int)(pfVar9 + -2);
  pfVar8 = pfVar4;
  do {
    pfVar10 = pfVar3 + -4;
    pfVar6 = pfVar5 + -8;
    *pfVar8 = pfVar3[-1] * pfVar5[4] + pfVar3[-2] * pfVar5[6];
    pfVar8[1] = pfVar3[-2] * pfVar5[4] - pfVar5[6] * pfVar3[-1];
    pfVar8[2] = *pfVar10 * pfVar5[2] + *pfVar5 * pfVar3[-3];
    pfVar8[3] = *pfVar5 * *pfVar10 - pfVar3[-3] * pfVar5[2];
    pfVar3 = pfVar10;
    pfVar5 = pfVar6;
    pfVar8 = pfVar8 + 4;
  } while (param_2 <= pfVar6);
  mdct_butterflies((mdct_lookup *)(param_3 + (int)pfVar9),pfVar9,(int)unaff_EDI);
  mdct_bitreverse(unaff_EDI,unaff_ESI);
  pfVar3 = param_1->trig + (int)pfVar9;
  pfVar5 = param_3 + 3;
  pfVar8 = pfVar4;
  pfVar10 = pfVar4;
  do {
    pfVar7 = pfVar8 + -4;
    pfVar6 = pfVar5 + 5;
    pfVar8[-1] = pfVar3[1] * pfVar5[-3] - pfVar5[-2] * *pfVar3;
    *pfVar10 = -(*pfVar3 * pfVar5[-3] + pfVar5[-2] * pfVar3[1]);
    pfVar8[-2] = pfVar5[-1] * pfVar3[3] - pfVar3[2] * *pfVar5;
    pfVar10[1] = -(pfVar3[3] * *pfVar5 + pfVar5[-1] * pfVar3[2]);
    pfVar8[-3] = pfVar5[1] * pfVar3[5] - pfVar5[2] * pfVar3[4];
    pfVar10[2] = -(pfVar5[1] * pfVar3[4] + pfVar5[2] * pfVar3[5]);
    *pfVar7 = pfVar5[3] * pfVar3[7] - pfVar3[6] * pfVar5[4];
    pfVar10[3] = -(pfVar5[4] * pfVar3[7] + pfVar3[6] * pfVar5[3]);
    pfVar3 = pfVar3 + 8;
    pfVar5 = pfVar5 + 8;
    pfVar8 = pfVar7;
    pfVar10 = pfVar10 + 4;
  } while (pfVar6 < pfVar7);
  pfVar3 = pfVar4;
  pfVar5 = param_3 + iVar2 + 2;
  pfVar8 = pfVar4 + (2 - (int)pfVar9);
  do {
    fVar1 = pfVar3[-1];
    pfVar7 = pfVar3 + -4;
    pfVar8[-3] = fVar1;
    pfVar10 = pfVar5 + 2;
    pfVar5[-2] = -fVar1;
    fVar1 = pfVar3[-2];
    pfVar8[-4] = fVar1;
    pfVar5[-1] = -fVar1;
    fVar1 = pfVar3[-3];
    pfVar8[-5] = fVar1;
    *pfVar5 = -fVar1;
    fVar1 = *pfVar7;
    pfVar8[-6] = fVar1;
    pfVar5[1] = -fVar1;
    pfVar3 = pfVar7;
    pfVar6 = pfVar4;
    pfVar5 = pfVar5 + 4;
    pfVar8 = pfVar8 + -4;
  } while (pfVar10 < pfVar7);
  do {
    pfVar3 = pfVar4 + -4;
    *pfVar3 = pfVar6[3];
    pfVar4[-3] = pfVar6[2];
    pfVar4[-2] = pfVar6[1];
    pfVar4[-1] = *pfVar6;
    pfVar4 = pfVar3;
    pfVar6 = pfVar6 + 4;
  } while ((mdct_lookup *)(param_3 + (int)pfVar9) < pfVar3);
  return;
}
