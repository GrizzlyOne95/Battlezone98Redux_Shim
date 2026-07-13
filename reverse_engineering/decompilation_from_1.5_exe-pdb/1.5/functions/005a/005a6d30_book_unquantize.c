/*
 * Entry: 005a6d30
 * Name: _book_unquantize
 * Namespace: Global
 * Signature: float * _book_unquantize(static_codebook * param_1, int param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float * __cdecl _book_unquantize(static_codebook *param_1,int param_2,int *param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  long *plVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float *pfVar9;
  int iVar10;
  long lVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int *piVar15;
  double dVar16;
  int local_1c;
  float local_14;
  float local_10;
  int *local_8;
  
  iVar14 = 0;
  if ((param_1->maptype != 1) && (param_1->maptype != 2)) {
    return (float *)0x0;
  }
  uVar1 = param_1->q_min;
  dVar16 = (double)(uVar1 & 0x1fffff);
  if ((int)uVar1 < 0) {
    dVar16 = -dVar16;
  }
  dVar16 = ldexp(dVar16,((int)uVar1 >> 0x15 & 0x3ffU) - 0x314);
  fVar6 = (float)dVar16;
  uVar1 = param_1->q_delta;
  dVar16 = (double)(uVar1 & 0x1fffff);
  if ((int)uVar1 < 0) {
    dVar16 = -dVar16;
  }
  dVar16 = ldexp(dVar16,((int)uVar1 >> 0x15 & 0x3ffU) - 0x314);
  fVar7 = (float)dVar16;
  pfVar9 = calloc(param_1->dim * param_2,4);
  if (param_1->maptype == 1) {
    lVar11 = _book_maptype1_quantvals(param_1);
    iVar2 = param_1->entries;
    local_1c = 0;
    if (0 < iVar2) {
      do {
        if ((param_3 == (int *)0x0) || (*(char *)(local_1c + (int)param_1->lengthlist) != '\0')) {
          local_10 = 0.0;
          iVar3 = param_1->dim;
          iVar10 = 0;
          iVar12 = 1;
          if (3 < iVar3) {
            plVar4 = param_1->quantlist;
            iVar5 = param_1->q_sequencep;
            do {
              fVar8 = ABS((float)plVar4[(local_1c / iVar12) % lVar11]) * fVar7 + fVar6 + local_10;
              if (iVar5 != 0) {
                local_10 = fVar8;
              }
              iVar13 = iVar14;
              if (param_3 != (int *)0x0) {
                iVar13 = param_3[iVar14];
              }
              pfVar9[iVar13 * iVar3 + iVar10] = fVar8;
              fVar8 = ABS((float)plVar4[(local_1c / (iVar12 * lVar11)) % lVar11]) * fVar7 + fVar6 +
                      local_10;
              if (iVar5 != 0) {
                local_10 = fVar8;
              }
              iVar13 = iVar14;
              if (param_3 != (int *)0x0) {
                iVar13 = param_3[iVar14];
              }
              iVar12 = iVar12 * lVar11 * lVar11;
              pfVar9[iVar13 * iVar3 + iVar10 + 1] = fVar8;
              fVar8 = ABS((float)plVar4[(local_1c / iVar12) % lVar11]) * fVar7 + fVar6 + local_10;
              if (iVar5 != 0) {
                local_10 = fVar8;
              }
              iVar13 = iVar14;
              if (param_3 != (int *)0x0) {
                iVar13 = param_3[iVar14];
              }
              iVar12 = iVar12 * lVar11;
              pfVar9[iVar13 * iVar3 + iVar10 + 2] = fVar8;
              fVar8 = ABS((float)plVar4[(local_1c / iVar12) % lVar11]) * fVar7 + fVar6 + local_10;
              if (iVar5 != 0) {
                local_10 = fVar8;
              }
              iVar13 = iVar14;
              if (param_3 != (int *)0x0) {
                iVar13 = param_3[iVar14];
              }
              iVar12 = iVar12 * lVar11;
              iVar13 = iVar13 * iVar3 + iVar10;
              iVar10 = iVar10 + 4;
              pfVar9[iVar13 + 3] = fVar8;
            } while (iVar10 < iVar3 + -3);
          }
          if (iVar10 < iVar3) {
            plVar4 = param_1->quantlist;
            iVar5 = param_1->q_sequencep;
            do {
              fVar8 = ABS((float)plVar4[(local_1c / iVar12) % lVar11]) * fVar7 + fVar6 + local_10;
              if (iVar5 != 0) {
                local_10 = fVar8;
              }
              iVar13 = iVar14;
              if (param_3 != (int *)0x0) {
                iVar13 = param_3[iVar14];
              }
              iVar12 = iVar12 * lVar11;
              iVar13 = iVar13 * iVar3 + iVar10;
              iVar10 = iVar10 + 1;
              pfVar9[iVar13] = fVar8;
            } while (iVar10 < iVar3);
          }
          iVar14 = iVar14 + 1;
        }
        local_1c = local_1c + 1;
      } while (local_1c < iVar2);
    }
  }
  else if (param_1->maptype == 2) {
    iVar2 = param_1->entries;
    local_1c = 0;
    if (0 < iVar2) {
      do {
        if ((param_3 == (int *)0x0) || (*(char *)(local_1c + (int)param_1->lengthlist) != '\0')) {
          iVar3 = param_1->dim;
          local_14 = 0.0;
          iVar10 = 0;
          if (3 < iVar3) {
            iVar12 = param_1->q_sequencep;
            piVar15 = param_1->quantlist + iVar3 * local_1c + 2;
            local_8 = param_1->quantlist + iVar3 * local_1c + 1;
            do {
              fVar8 = ABS((float)piVar15[-2]) * fVar7 + fVar6 + local_14;
              if (iVar12 != 0) {
                local_14 = fVar8;
              }
              iVar5 = iVar14;
              if (param_3 != (int *)0x0) {
                iVar5 = param_3[iVar14];
              }
              pfVar9[iVar5 * iVar3 + iVar10] = fVar8;
              fVar8 = ABS((float)*local_8) * fVar7 + fVar6 + local_14;
              if (iVar12 != 0) {
                local_14 = fVar8;
              }
              iVar5 = iVar14;
              if (param_3 != (int *)0x0) {
                iVar5 = param_3[iVar14];
              }
              pfVar9[iVar5 * iVar3 + iVar10 + 1] = fVar8;
              fVar8 = ABS((float)*piVar15) * fVar7 + fVar6 + local_14;
              if (iVar12 != 0) {
                local_14 = fVar8;
              }
              iVar5 = iVar14;
              if (param_3 != (int *)0x0) {
                iVar5 = param_3[iVar14];
              }
              pfVar9[iVar5 * iVar3 + iVar10 + 2] = fVar8;
              fVar8 = ABS((float)piVar15[1]) * fVar7 + fVar6 + local_14;
              if (iVar12 != 0) {
                local_14 = fVar8;
              }
              iVar5 = iVar14;
              if (param_3 != (int *)0x0) {
                iVar5 = param_3[iVar14];
              }
              local_8 = local_8 + 4;
              pfVar9[iVar5 * iVar3 + iVar10 + 3] = fVar8;
              iVar10 = iVar10 + 4;
              piVar15 = piVar15 + 4;
            } while (iVar10 < iVar3 + -3);
          }
          if (iVar10 < iVar3) {
            local_8 = param_1->quantlist + iVar3 * local_1c + iVar10;
            do {
              fVar8 = ABS((float)*local_8) * fVar7 + fVar6 + local_14;
              if (param_1->q_sequencep != 0) {
                local_14 = fVar8;
              }
              iVar12 = iVar14;
              if (param_3 != (int *)0x0) {
                iVar12 = param_3[iVar14];
              }
              local_8 = local_8 + 1;
              iVar12 = iVar12 * iVar3 + iVar10;
              iVar10 = iVar10 + 1;
              pfVar9[iVar12] = fVar8;
            } while (iVar10 < iVar3);
          }
          iVar14 = iVar14 + 1;
        }
        local_1c = local_1c + 1;
      } while (local_1c < iVar2);
      return pfVar9;
    }
  }
  return pfVar9;
}
