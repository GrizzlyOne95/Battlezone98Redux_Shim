/*
 * Entry: 005b55c0
 * Name: Newton_Raphson
 * Namespace: Global
 * Signature: int Newton_Raphson(float * param_1, int param_2, float * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

int __cdecl Newton_Raphson(float *param_1,int param_2,float *param_3)

{
  double dVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  float *pfVar10;
  double *pdVar11;
  int iVar12;
  uint uVar13;
  uint unaff_ESI;
  int iVar14;
  undefined8 uStack_1c;
  int local_8;
  
  local_8 = 0;
  uStack_1c._4_4_ = 0x5b55db;
  iVar2 = unaff_ESI * -8;
  iVar12 = 0;
  if (3 < (int)unaff_ESI) {
    iVar14 = (unaff_ESI - 4 >> 2) + 1;
    iVar12 = iVar14 * 4;
    pfVar10 = (float *)(param_2 + 8);
    pdVar11 = (double *)(&stack0xfffffffc + iVar2);
    do {
      pdVar11[-2] = (double)pfVar10[-2];
      iVar14 = iVar14 + -1;
      pdVar11[-1] = (double)pfVar10[-1];
      *pdVar11 = (double)*pfVar10;
      pdVar11[1] = (double)pfVar10[1];
      pfVar10 = pfVar10 + 4;
      pdVar11 = pdVar11 + 4;
    } while (iVar14 != 0);
  }
  while (iVar12 < (int)unaff_ESI) {
    iVar14 = iVar12 * 4;
    iVar12 = iVar12 + 1;
    (&uStack_1c)[iVar12 - unaff_ESI] = (double)*(float *)(param_2 + iVar14);
  }
  dVar9 = 0.0;
  while( true ) {
    iVar12 = 0;
    dVar3 = dVar9;
    if (0 < (int)unaff_ESI) {
      do {
        dVar1 = *(double *)(&stack0xffffffec + iVar12 * 8 + iVar2);
        iVar14 = unaff_ESI - 1;
        dVar4 = (double)param_1[unaff_ESI];
        dVar5 = dVar9;
        if (-1 < iVar14) {
          if (3 < (int)unaff_ESI) {
            uVar13 = unaff_ESI >> 2;
            iVar14 = iVar14 + uVar13 * -4;
            pfVar10 = param_1 + (unaff_ESI - 3);
            do {
              uVar13 = uVar13 - 1;
              dVar6 = dVar4 * dVar1 + (double)pfVar10[2];
              dVar7 = dVar6 * dVar1 + (double)pfVar10[1];
              dVar8 = dVar7 * dVar1 + (double)*pfVar10;
              dVar5 = dVar1 * (dVar1 * (dVar1 * (dVar1 * dVar5 + dVar4) + dVar6) + dVar7) + dVar8;
              dVar4 = dVar8 * dVar1 + (double)pfVar10[-1];
              pfVar10 = pfVar10 + -4;
            } while (uVar13 != 0);
          }
          for (; -1 < iVar14; iVar14 = iVar14 + -1) {
            dVar5 = dVar1 * dVar5 + dVar4;
            dVar4 = dVar4 * dVar1 + (double)param_1[iVar14];
          }
        }
        iVar12 = iVar12 + 1;
        dVar4 = dVar4 / dVar5;
        (&uStack_1c)[iVar12 - unaff_ESI] = (double)(&uStack_1c)[iVar12 - unaff_ESI] - dVar4;
        dVar3 = dVar4 * dVar4 + dVar3;
      } while (iVar12 < (int)unaff_ESI);
    }
    if (0x28 < local_8) break;
    local_8 = local_8 + 1;
    if (dVar3 <= 1e-20) {
      iVar12 = 0;
      if (3 < (int)unaff_ESI) {
        iVar14 = (unaff_ESI - 4 >> 2) + 1;
        iVar12 = iVar14 * 4;
        pdVar11 = (double *)(&stack0xfffffffc + iVar2);
        pfVar10 = (float *)(param_2 + 8);
        do {
          pfVar10[-2] = (float)pdVar11[-2];
          iVar14 = iVar14 + -1;
          pfVar10[-1] = (float)pdVar11[-1];
          *pfVar10 = (float)*pdVar11;
          pfVar10[1] = (float)pdVar11[1];
          pdVar11 = pdVar11 + 4;
          pfVar10 = pfVar10 + 4;
        } while (iVar14 != 0);
      }
      for (; iVar12 < (int)unaff_ESI; iVar12 = iVar12 + 1) {
        *(float *)(param_2 + iVar12 * 4) = (float)*(double *)(&stack0xffffffec + iVar12 * 8 + iVar2)
        ;
      }
      return 0;
    }
  }
  return -1;
}
