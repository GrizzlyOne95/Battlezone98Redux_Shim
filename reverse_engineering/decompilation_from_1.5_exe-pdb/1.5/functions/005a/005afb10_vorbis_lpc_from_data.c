/*
 * Entry: 005afb10
 * Name: vorbis_lpc_from_data
 * Namespace: Global
 * Signature: float vorbis_lpc_from_data(float * param_1, float * param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

float __cdecl vorbis_lpc_from_data(float *param_1,float *param_2,int param_3,int param_4)

{
  float fVar1;
  double dVar2;
  double dVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  int iVar8;
  double *pdVar9;
  double *pdVar10;
  double *pdVar11;
  float *pfVar12;
  float *pfVar13;
  int iVar14;
  int iVar15;
  float10 fVar16;
  float10 fVar17;
  int aiStack_34 [2];
  undefined8 uStack_2c;
  undefined1 local_18 [8];
  double *local_10;
  double *local_c;
  float *local_8;
  
  uStack_2c._4_4_ = 0x5afb2b;
  iVar4 = -(param_4 * 8 + 8);
  local_c = (double *)(&stack0xffffffdc + iVar4);
  *(undefined4 *)((int)&uStack_2c + iVar4 + 4) = 0x5afb35;
  iVar5 = param_4 * -8;
  iVar15 = param_4 + 1;
  if (iVar15 != 0) {
    fVar7 = 0.0;
    local_8 = param_1 + param_4 + 3;
    local_10 = (double *)(param_3 - iVar15);
    do {
      local_8 = local_8 + -1;
      iVar15 = iVar15 + -1;
      local_10 = (double *)((int)local_10 + 1);
      fVar6 = fVar7;
      if (iVar15 < param_3) {
        iVar14 = iVar15;
        if (3 < (int)local_10) {
          iVar8 = ((param_3 - iVar15) - 4U >> 2) + 1;
          iVar14 = iVar15 + iVar8 * 4;
          pfVar12 = local_8;
          pfVar13 = param_1 + 2;
          do {
            iVar8 = iVar8 + -1;
            fVar6 = pfVar13[1] * pfVar12[1] +
                    *pfVar13 * *pfVar12 +
                    pfVar13[-1] * pfVar12[-1] + pfVar13[-2] * pfVar12[-2] + fVar6;
            pfVar12 = pfVar12 + 4;
            pfVar13 = pfVar13 + 4;
          } while (iVar8 != 0);
        }
        if (iVar14 < param_3) {
          pfVar12 = param_1 + (iVar14 - iVar15);
          do {
            pfVar13 = param_1 + iVar14;
            iVar14 = iVar14 + 1;
            fVar1 = *pfVar12;
            pfVar12 = pfVar12 + 1;
            fVar6 = *pfVar13 * fVar1 + fVar6;
          } while (iVar14 < param_3);
        }
      }
      local_c[iVar15] = (double)fVar6;
    } while (iVar15 != 0);
  }
  fVar16 = (float10)*local_c * (float10)1.0000000001;
  local_8 = (float *)0x0;
  local_18 = (undefined1  [8])(double)fVar16;
  dVar2 = *local_c;
  if (0 < param_4) {
    pdVar10 = local_c + -2;
    local_10 = pdVar10;
    local_18._0_4_ = SUB84((double)fVar16,0);
    local_18._4_4_ = &stack0xffffffdc + ((iVar5 + iVar4) - (int)local_c);
    do {
      pfVar12 = local_8;
      fVar17 = -(float10)pdVar10[3];
      local_10 = pdVar10;
      if (fVar16 < (float10)dVar2 * (float10)1e-09 + (float10)1e-10) {
        local_18 = (undefined1  [8])(double)fVar16;
        *(int *)((int)&uStack_2c + iVar5 + iVar4 + 4) = (param_4 - (int)local_8) * 8;
        *(undefined4 *)((int)&uStack_2c + iVar5 + iVar4) = 0;
        *(undefined1 **)((int)aiStack_34 + iVar5 + iVar4 + 4) =
             &stack0xffffffdc + (int)pfVar12 * 8 + iVar5 + iVar4;
        *(undefined4 *)((int)aiStack_34 + iVar5 + iVar4) = 0x5afdac;
        memset();
        fVar16 = (float10)(double)local_18;
        goto LAB_005afdb6;
      }
      iVar15 = 0;
      if (3 < (int)local_8) {
        iVar14 = ((int)local_8 - 4U >> 2) + 1;
        iVar15 = iVar14 * 4;
        pdVar9 = (double *)(local_18 + iVar5 + iVar4 + 4);
        pdVar11 = pdVar10;
        do {
          iVar14 = iVar14 + -1;
          fVar17 = (((fVar17 - (float10)pdVar11[2] * (float10)pdVar9[-2]) -
                    (float10)pdVar11[1] * (float10)pdVar9[-1]) -
                   (float10)*pdVar9 * (float10)*pdVar11) - (float10)pdVar11[-1] * (float10)pdVar9[1]
          ;
          pdVar9 = pdVar9 + 4;
          pdVar11 = pdVar11 + -4;
        } while (iVar14 != 0);
      }
      if (iVar15 < (int)local_8) {
        pdVar9 = local_c + ((int)local_8 - iVar15);
        do {
          iVar14 = iVar15 * 8;
          iVar15 = iVar15 + 1;
          dVar3 = *pdVar9;
          pdVar9 = pdVar9 + -1;
          fVar17 = fVar17 - (float10)*(double *)(&stack0xffffffdc + iVar14 + iVar5 + iVar4) *
                            (float10)dVar3;
        } while (iVar15 < (int)local_8);
      }
      fVar17 = fVar17 / fVar16;
      iVar15 = 0;
      *(double *)(&stack0xffffffdc + (int)local_8 * 8 + iVar5 + iVar4) = (double)fVar17;
      iVar14 = (int)pfVar12 / 2;
      if (3 < iVar14) {
        iVar8 = (iVar14 - 4U >> 2) + 1;
        iVar15 = iVar8 * 4;
        pdVar9 = (double *)(local_18 + iVar5 + iVar4 + 4);
        pdVar11 = (double *)(local_18._4_4_ + (int)pdVar10);
        do {
          dVar3 = pdVar9[-2];
          iVar8 = iVar8 + -1;
          pdVar9[-2] = (double)((float10)pdVar11[1] * fVar17 + (float10)pdVar9[-2]);
          pdVar11[1] = (double)((float10)dVar3 * fVar17 + (float10)pdVar11[1]);
          dVar3 = pdVar9[-1];
          pdVar9[-1] = (double)((float10)*pdVar11 * fVar17 + (float10)pdVar9[-1]);
          *pdVar11 = (double)((float10)dVar3 * fVar17 + (float10)*pdVar11);
          dVar3 = *pdVar9;
          *pdVar9 = (double)((float10)pdVar11[-1] * fVar17 + (float10)*pdVar9);
          pdVar11[-1] = (double)((float10)dVar3 * fVar17 + (float10)pdVar11[-1]);
          dVar3 = pdVar9[1];
          pdVar9[1] = (double)((float10)pdVar11[-2] * fVar17 + (float10)pdVar9[1]);
          pdVar11[-2] = (double)((float10)dVar3 * fVar17 + (float10)pdVar11[-2]);
          pdVar9 = pdVar9 + 4;
          pdVar11 = pdVar11 + -4;
          pdVar10 = local_10;
        } while (iVar8 != 0);
      }
      if (iVar15 < iVar14) {
        pdVar9 = (double *)((int)&uStack_2c + ((int)local_8 - iVar15) * 8 + iVar5 + iVar4);
        do {
          dVar3 = *(double *)(&stack0xffffffdc + iVar15 * 8 + iVar5 + iVar4);
          iVar15 = iVar15 + 1;
          *(double *)((int)&uStack_2c + iVar15 * 8 + iVar5 + iVar4) =
               (double)((float10)*pdVar9 * fVar17 +
                       (float10)*(double *)((int)&uStack_2c + iVar15 * 8 + iVar5 + iVar4));
          *pdVar9 = (double)((float10)dVar3 * fVar17 + (float10)*pdVar9);
          pdVar9 = pdVar9 + -1;
        } while (iVar15 < iVar14);
      }
      if (((uint)local_8 & 1) != 0) {
        *(double *)(&stack0xffffffdc + iVar15 * 8 + iVar5 + iVar4) =
             (double)((float10)*(double *)(&stack0xffffffdc + iVar15 * 8 + iVar5 + iVar4) * fVar17 +
                     (float10)*(double *)(&stack0xffffffdc + iVar15 * 8 + iVar5 + iVar4));
      }
      local_8 = (float *)((int)local_8 + 1);
      pdVar10 = pdVar10 + 1;
      local_10 = pdVar10;
      fVar16 = ((float10)1 - fVar17 * fVar17) * fVar16;
    } while ((int)local_8 < param_4);
    local_18 = (undefined1  [8])(double)fVar16;
  }
LAB_005afdb6:
  iVar15 = 0;
  dVar2 = 0.99;
  if (3 < param_4) {
    iVar14 = (param_4 - 4U >> 2) + 1;
    iVar15 = iVar14 * 4;
    pdVar10 = (double *)(local_18 + iVar5 + iVar4 + 4);
    do {
      iVar14 = iVar14 + -1;
      pdVar10[-2] = dVar2 * pdVar10[-2];
      pdVar10[-1] = pdVar10[-1] * dVar2 * 0.99;
      dVar2 = dVar2 * 0.99 * 0.99;
      *pdVar10 = dVar2 * *pdVar10;
      dVar2 = dVar2 * 0.99;
      pdVar10[1] = pdVar10[1] * dVar2;
      dVar2 = dVar2 * 0.99;
      pdVar10 = pdVar10 + 4;
    } while (iVar14 != 0);
  }
  while (iVar15 < param_4) {
    iVar14 = iVar15 * 8;
    iVar15 = iVar15 + 1;
    *(double *)((int)&uStack_2c + iVar15 * 8 + iVar5 + iVar4) =
         *(double *)(&stack0xffffffdc + iVar14 + iVar5 + iVar4) * dVar2;
    dVar2 = dVar2 * 0.99;
  }
  iVar15 = 0;
  if (3 < param_4) {
    iVar14 = (param_4 - 4U >> 2) + 1;
    iVar15 = iVar14 * 4;
    pdVar10 = (double *)(local_18 + iVar5 + iVar4 + 4);
    pfVar12 = param_2 + 2;
    do {
      pfVar12[-2] = (float)pdVar10[-2];
      iVar14 = iVar14 + -1;
      pfVar12[-1] = (float)pdVar10[-1];
      *pfVar12 = (float)*pdVar10;
      pfVar12[1] = (float)pdVar10[1];
      pdVar10 = pdVar10 + 4;
      pfVar12 = pfVar12 + 4;
    } while (iVar14 != 0);
  }
  for (; iVar15 < param_4; iVar15 = iVar15 + 1) {
    param_2[iVar15] = (float)*(double *)(&stack0xffffffdc + iVar15 * 8 + iVar5 + iVar4);
  }
  return (float)fVar16;
}
