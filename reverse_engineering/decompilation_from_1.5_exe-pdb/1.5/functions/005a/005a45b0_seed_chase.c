/*
 * Entry: 005a45b0
 * Name: seed_chase
 * Namespace: Global
 * Signature: void seed_chase(float * param_1, int param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

void __cdecl seed_chase(float *param_1,int param_2,long param_3)

{
  float fVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  float *pfVar6;
  int iVar7;
  float *pfVar8;
  int iVar9;
  float afStack_2c [2];
  float *local_8;
  
  afStack_2c[1] = 8.290226e-39;
  pfVar8 = (float *)(&stack0xffffffdc + param_3 * -8);
  afStack_2c[1 - param_3] = 8.290239e-39;
  iVar4 = 0;
  iVar7 = 0;
  if (0 < param_3) {
    do {
      if ((1 < iVar7) && (afStack_2c[param_3 * -2 + iVar7 + 1] <= param_1[iVar4])) {
        local_8 = afStack_2c + (iVar7 - param_3);
        do {
          if (((((int)afStack_2c[(iVar7 + 1) - param_3] + param_2 <= iVar4) || (iVar7 < 2)) ||
              (local_8[-param_3] < afStack_2c[param_3 * -2 + iVar7 + 1])) ||
             ((int)*local_8 + param_2 <= iVar4)) break;
          iVar9 = param_3 * -2 + iVar7;
          local_8 = local_8 + -1;
          iVar7 = iVar7 + -1;
        } while (afStack_2c[iVar9] <= param_1[iVar4]);
      }
      fVar1 = param_1[iVar4];
      *(int *)(&stack0xffffffdc + iVar7 * 4 + param_3 * -4) = iVar4;
      *(float *)(&stack0xffffffdc + iVar7 * 4 + param_3 * -8) = fVar1;
      iVar4 = iVar4 + 1;
      iVar7 = iVar7 + 1;
    } while (iVar4 < param_3);
  }
  iVar4 = 0;
  local_8 = (float *)0x0;
  if (0 < iVar7) {
    piVar5 = (int *)(&stack0xffffffe0 + param_3 * -4);
    do {
      if ((iVar7 + -1 <= (int)local_8) || ((float)piVar5[-param_3] <= *pfVar8)) {
        iVar9 = piVar5[-1] + 1 + param_2;
      }
      else {
        iVar9 = *piVar5;
      }
      if (param_3 < iVar9) {
        iVar9 = param_3;
      }
      if (iVar4 < iVar9) {
        if (3 < iVar9 - iVar4) {
          iVar3 = ((iVar9 - iVar4) - 4U >> 2) + 1;
          iVar2 = iVar4 + 2;
          iVar4 = iVar4 + iVar3 * 4;
          pfVar6 = param_1 + iVar2;
          do {
            iVar3 = iVar3 + -1;
            pfVar6[-2] = *pfVar8;
            pfVar6[-1] = *pfVar8;
            *pfVar6 = *pfVar8;
            pfVar6[1] = *pfVar8;
            pfVar6 = pfVar6 + 4;
          } while (iVar3 != 0);
        }
        if (iVar4 < iVar9) {
          fVar1 = *pfVar8;
          iVar9 = iVar9 - iVar4;
          pfVar6 = param_1 + iVar4;
          iVar4 = iVar4 + iVar9;
          for (; iVar9 != 0; iVar9 = iVar9 + -1) {
            *pfVar6 = fVar1;
            pfVar6 = pfVar6 + 1;
          }
        }
      }
      local_8 = (float *)((int)local_8 + 1);
      piVar5 = piVar5 + 1;
      pfVar8 = pfVar8 + 1;
    } while ((int)local_8 < iVar7);
  }
  return;
}
