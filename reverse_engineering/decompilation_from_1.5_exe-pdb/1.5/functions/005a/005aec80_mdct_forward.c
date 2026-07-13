/*
 * Entry: 005aec80
 * Name: mdct_forward
 * Namespace: Global
 * Signature: void mdct_forward(mdct_lookup * param_1, float * param_2, float * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

void __cdecl mdct_forward(mdct_lookup *param_1,float *param_2,float *param_3)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  mdct_lookup *pmVar7;
  mdct_lookup *pmVar8;
  float *pfVar9;
  float *pfVar10;
  float *pfVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  float *pfVar16;
  mdct_lookup *pmVar17;
  int iVar18;
  float *pfVar19;
  int iVar20;
  float *pfVar21;
  float *pfVar22;
  float afStack_3c [3];
  int *local_8;
  
  pmVar8 = param_1;
  iVar18 = param_1->n;
  iVar12 = iVar18 >> 1;
  iVar13 = iVar18 >> 2;
  iVar20 = iVar18 >> 3;
  afStack_3c[2] = 8.3501e-39;
  iVar6 = iVar18 * -4;
  pfVar21 = (float *)(&stack0xffffffd0 + iVar6);
  pmVar17 = (mdct_lookup *)(param_2 + iVar13 + iVar12);
  pfVar10 = param_1->trig + iVar12;
  iVar14 = 0;
  pfVar9 = pfVar10;
  iVar15 = iVar14;
  param_1 = pmVar17;
  local_8 = &pmVar17->log2n;
  if (0 < iVar20) {
    do {
      pmVar7 = pmVar17 + -1;
      pmVar17 = (mdct_lookup *)&pmVar17[-1].log2n;
      fVar3 = (float)pmVar7->bitrev + (float)*local_8;
      pfVar10 = pfVar9 + -2;
      iVar14 = iVar15 + 2;
      piVar1 = (int *)local_8[2];
      fVar2 = *(float *)pmVar17;
      afStack_3c[(iVar12 + iVar15 + 3) - iVar18] =
           fVar3 * *pfVar10 + ((float)piVar1 + fVar2) * pfVar9[-1];
      afStack_3c[(iVar12 + iVar15 + 4) - iVar18] =
           *pfVar10 * ((float)piVar1 + fVar2) - fVar3 * pfVar9[-1];
      pfVar9 = pfVar10;
      iVar15 = iVar14;
      param_1 = pmVar17;
      local_8 = local_8 + 4;
    } while (iVar14 < iVar20);
  }
  pfVar9 = param_2 + 1;
  for (; iVar14 < iVar12 - iVar20; iVar14 = iVar14 + 2) {
    pmVar17 = param_1 + -1;
    param_1 = (mdct_lookup *)&param_1[-1].log2n;
    fVar4 = (float)pmVar17->bitrev - *pfVar9;
    pfVar11 = pfVar10 + -2;
    fVar2 = *(float *)param_1;
    fVar3 = pfVar9[2];
    afStack_3c[(iVar12 + iVar14 + 3) - iVar18] = fVar4 * *pfVar11 + (fVar2 - fVar3) * pfVar10[-1];
    afStack_3c[(iVar12 + iVar14 + 4) - iVar18] = *pfVar11 * (fVar2 - fVar3) - fVar4 * pfVar10[-1];
    pfVar9 = pfVar9 + 4;
    pfVar10 = pfVar11;
  }
  pfVar11 = param_2 + iVar18;
  for (; iVar14 < iVar12; iVar14 = iVar14 + 2) {
    fVar2 = pfVar11[-2];
    pfVar11 = pfVar11 + -4;
    pfVar16 = pfVar10 + -2;
    fVar3 = *pfVar9;
    fVar4 = *pfVar11;
    fVar5 = pfVar9[2];
    afStack_3c[(iVar12 + iVar14 + 3) - iVar18] =
         (-fVar2 - fVar3) * *pfVar16 + (-fVar4 - fVar5) * pfVar10[-1];
    afStack_3c[(iVar12 + iVar14 + 4) - iVar18] =
         *pfVar16 * (-fVar4 - fVar5) - (-fVar2 - fVar3) * pfVar10[-1];
    pfVar9 = pfVar9 + 4;
    pfVar10 = pfVar16;
  }
  afStack_3c[2 - iVar18] = (float)iVar12;
  afStack_3c[1 - iVar18] = (float)(&stack0xffffffd0 + iVar12 * 4 + iVar6);
  afStack_3c[-iVar18] = 8.350632e-39;
  mdct_butterflies((mdct_lookup *)afStack_3c[1 - iVar18],(float *)afStack_3c[2 - iVar18],
                   *(int *)(&stack0xffffffd0 + iVar6));
  afStack_3c[2 - iVar18] = 8.350649e-39;
  mdct_bitreverse(*(mdct_lookup **)(&stack0xffffffd0 + iVar6),*(float **)(&stack0xffffffd4 + iVar6))
  ;
  pfVar10 = pmVar8->trig + iVar12;
  pfVar9 = param_3 + iVar12;
  iVar18 = 0;
  if (3 < iVar13) {
    iVar14 = (iVar13 - 4U >> 2) + 1;
    iVar18 = iVar14 * 4;
    pfVar11 = pfVar10;
    pfVar16 = pfVar9;
    pfVar19 = param_3 + 2;
    pfVar22 = (float *)(&stack0xffffffd0 + iVar6);
    do {
      pfVar21 = pfVar22 + 8;
      pfVar9 = pfVar16 + -4;
      pfVar10 = pfVar11 + 8;
      iVar14 = iVar14 + -1;
      pfVar19[-2] = (pfVar22[1] * pfVar11[1] + *pfVar11 * *pfVar22) * pmVar8->scale;
      pfVar16[-1] = (pfVar11[1] * *pfVar22 - pfVar22[1] * *pfVar11) * pmVar8->scale;
      pfVar19[-1] = (pfVar11[2] * pfVar22[2] + pfVar11[3] * pfVar22[3]) * pmVar8->scale;
      pfVar16[-2] = (pfVar11[3] * pfVar22[2] - pfVar22[3] * pfVar11[2]) * pmVar8->scale;
      *pfVar19 = (pfVar11[4] * pfVar22[4] + pfVar11[5] * pfVar22[5]) * pmVar8->scale;
      pfVar16[-3] = (pfVar22[4] * pfVar11[5] - pfVar11[4] * pfVar22[5]) * pmVar8->scale;
      pfVar19[1] = (pfVar11[7] * pfVar22[7] + pfVar11[6] * pfVar22[6]) * pmVar8->scale;
      *pfVar9 = (pfVar22[6] * pfVar11[7] - pfVar11[6] * pfVar22[7]) * pmVar8->scale;
      pfVar11 = pfVar10;
      pfVar16 = pfVar9;
      pfVar19 = pfVar19 + 4;
      pfVar22 = pfVar21;
    } while (iVar14 != 0);
  }
  for (; iVar18 < iVar13; iVar18 = iVar18 + 1) {
    pfVar9 = pfVar9 + -1;
    param_3[iVar18] = (pfVar21[1] * pfVar10[1] + *pfVar10 * *pfVar21) * pmVar8->scale;
    *pfVar9 = (pfVar10[1] * *pfVar21 - pfVar21[1] * *pfVar10) * pmVar8->scale;
    pfVar10 = pfVar10 + 2;
    pfVar21 = pfVar21 + 2;
  }
  return;
}
