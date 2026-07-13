/*
 * Entry: 005b5300
 * Name: Laguerre_With_Deflation
 * Namespace: Global
 * Signature: int Laguerre_With_Deflation(float * param_1, int param_2, float * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

int __cdecl Laguerre_With_Deflation(float *param_1,int param_2,float *param_3)

{
  int in_EAX;
  float *pfVar1;
  int iVar2;
  double *pdVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  undefined1 *puVar8;
  undefined1 *puVar10;
  float10 fVar11;
  float10 fVar12;
  float10 fVar13;
  float10 fVar14;
  float10 fVar15;
  float10 fVar16;
  float10 fVar17;
  float10 fVar18;
  float10 fVar19;
  undefined8 uStack_48;
  undefined1 local_34 [8];
  double local_2c;
  double local_24;
  undefined8 local_1c;
  double local_14;
  int local_c;
  float *local_8;
  undefined4 *puVar9;
  
  uStack_48._4_4_ = 0x5b531a;
  iVar2 = -(in_EAX * 8 + 8);
  puVar8 = &stack0xffffffc0 + iVar2;
  puVar10 = &stack0xffffffc0 + iVar2;
  iVar4 = 0;
  if (-1 < in_EAX) {
    if (3 < in_EAX + 1) {
      uVar6 = in_EAX + 1U >> 2;
      iVar4 = uVar6 * 4;
      pfVar1 = param_1 + 2;
      pdVar3 = (double *)(local_34 + iVar2 + 4);
      do {
        pdVar3[-2] = (double)pfVar1[-2];
        uVar6 = uVar6 - 1;
        pdVar3[-1] = (double)pfVar1[-1];
        *pdVar3 = (double)*pfVar1;
        pdVar3[1] = (double)pfVar1[1];
        pfVar1 = pfVar1 + 4;
        pdVar3 = pdVar3 + 4;
      } while (uVar6 != 0);
    }
    while (iVar4 <= in_EAX) {
      pfVar1 = param_1 + iVar4;
      iVar4 = iVar4 + 1;
      *(double *)((int)&uStack_48 + iVar4 * 8 + iVar2) = (double)*pfVar1;
    }
  }
  if (in_EAX < 1) {
    return 0;
  }
  iVar4 = in_EAX * 8 + -0x10;
  local_c = iVar4;
  local_8 = (float *)(param_2 + -4 + in_EAX * 4);
LAB_005b5394:
  fVar18 = (float10)0;
  iVar2 = in_EAX + -1;
  local_24 = (double)fVar18;
  local_1c = (double)CONCAT44(iVar2,(undefined4)local_1c);
  fVar11 = (float10)iVar2;
  local_2c = (double)iVar2;
  local_14 = (double)in_EAX;
  local_c = iVar4;
  do {
    fVar19 = (float10)0;
    fVar12 = (float10)*(double *)(puVar10 + iVar4 + 0x10);
    local_1c = (double)fVar19;
    iVar2 = in_EAX;
    fVar16 = fVar19;
    fVar17 = fVar19;
    if (3 < in_EAX) {
      iVar5 = (in_EAX - 4U >> 2) + 1;
      iVar2 = in_EAX + iVar5 * -4;
      pdVar3 = (double *)(puVar10 + iVar4);
      do {
        iVar5 = iVar5 + -1;
        fVar13 = fVar17 * fVar18 + fVar12;
        fVar12 = fVar12 * fVar18 + (float10)pdVar3[1];
        fVar14 = fVar13 * fVar18 + fVar12;
        fVar12 = fVar12 * fVar18 + (float10)*pdVar3;
        fVar15 = fVar14 * fVar18 + fVar12;
        fVar12 = fVar12 * fVar18 + (float10)pdVar3[-1];
        fVar16 = (((fVar16 * fVar18 + fVar17) * fVar18 + fVar13) * fVar18 + fVar14) * fVar18 +
                 fVar15;
        fVar17 = fVar15 * fVar18 + fVar12;
        fVar12 = fVar12 * fVar18 + (float10)pdVar3[-2];
        pdVar3 = pdVar3 + -4;
      } while (iVar5 != 0);
      local_1c = (double)fVar17;
      iVar4 = local_c;
    }
    if (0 < iVar2) {
      pdVar3 = (double *)(puVar10 + iVar2 * 8 + -8);
      do {
        iVar2 = iVar2 + -1;
        fVar16 = fVar16 * fVar18 + fVar17;
        fVar17 = fVar17 * fVar18 + fVar12;
        fVar12 = fVar12 * fVar18 + (float10)*pdVar3;
        pdVar3 = pdVar3 + -1;
      } while (0 < iVar2);
      local_1c = (double)fVar17;
    }
    local_34 = (undefined1  [8])(double)((float10)local_14 * fVar12);
    if ((fVar11 * fVar17 * fVar17 - (float10)local_14 * fVar12 * fVar16) * fVar11 < fVar19) {
      return -1;
    }
    if (fVar17 <= fVar19) {
      puVar9 = (undefined4 *)(puVar8 + -4);
      puVar8 = puVar8 + -4;
      *puVar9 = 0x5b54c7;
      fVar11 = (float10)__CIsqrt();
      fVar16 = (float10)-1e-06;
      fVar18 = (float10)local_1c - fVar11;
      if ((float10)local_1c - fVar11 <= fVar16) goto LAB_005b54dd;
    }
    else {
      puVar7 = (undefined4 *)(puVar8 + -4);
      puVar8 = puVar8 + -4;
      *puVar7 = 0x5b54a8;
      fVar11 = (float10)__CIsqrt();
      fVar16 = (float10)1e-06;
      fVar18 = fVar11 + (float10)local_1c;
      if (fVar16 <= fVar11 + (float10)local_1c) {
LAB_005b54dd:
        fVar16 = fVar18;
      }
    }
    fVar16 = (float10)(double)local_34 / fVar16;
    fVar18 = (float10)local_24 - fVar16;
    local_24 = (double)fVar18;
    if (fVar16 < (float10)0) {
      fVar16 = fVar16 * (float10)-1.0;
    }
    if (ABS(fVar16 / fVar18) < (float10)1e-11) break;
    fVar11 = (float10)local_2c;
  } while( true );
  *local_8 = (float)fVar18;
  iVar2 = in_EAX;
  if (3 < in_EAX) {
    iVar5 = (in_EAX - 4U >> 2) + 1;
    iVar2 = in_EAX + iVar5 * -4;
    pdVar3 = (double *)(puVar10 + iVar4);
    do {
      iVar5 = iVar5 + -1;
      fVar11 = (float10)pdVar3[2] * fVar18 + (float10)pdVar3[1];
      pdVar3[1] = (double)fVar11;
      fVar11 = fVar11 * fVar18 + (float10)*pdVar3;
      *pdVar3 = (double)fVar11;
      fVar11 = fVar11 * fVar18 + (float10)pdVar3[-1];
      pdVar3[-1] = (double)fVar11;
      pdVar3[-2] = (double)(fVar11 * fVar18 + (float10)pdVar3[-2]);
      pdVar3 = pdVar3 + -4;
      iVar4 = local_c;
    } while (iVar5 != 0);
  }
  if (0 < iVar2) {
    pdVar3 = (double *)(puVar10 + iVar2 * 8 + -8);
    do {
      iVar2 = iVar2 + -1;
      *pdVar3 = (double)((float10)pdVar3[1] * fVar18 + (float10)*pdVar3);
      pdVar3 = pdVar3 + -1;
    } while (0 < iVar2);
  }
  local_8 = local_8 + -1;
  in_EAX = in_EAX + -1;
  iVar4 = iVar4 + -8;
  puVar10 = puVar10 + 8;
  local_c = iVar4;
  if (in_EAX < 1) {
    return 0;
  }
  goto LAB_005b5394;
}
