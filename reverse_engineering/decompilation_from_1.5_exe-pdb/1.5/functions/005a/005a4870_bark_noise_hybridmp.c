/*
 * Entry: 005a4870
 * Name: bark_noise_hybridmp
 * Namespace: Global
 * Signature: void bark_noise_hybridmp(int param_1, long * param_2, float * param_3, float * param_4, float param_5, int param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

void __cdecl
bark_noise_hybridmp(int param_1,long *param_2,float *param_3,float *param_4,float param_5,
                   int param_6)

{
  float **ppfVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float *pfVar8;
  uint uVar9;
  float fVar10;
  undefined1 *puVar11;
  float *pfVar12;
  int iVar13;
  float *pfVar14;
  float *pfVar15;
  uint uVar16;
  int iVar17;
  float *pfVar18;
  undefined4 uStack_8c;
  float *local_7c;
  float local_78;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  undefined1 *local_60;
  int local_5c;
  float *local_58;
  float *local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  float *local_40;
  float *local_3c;
  float **local_34;
  float *local_30;
  float local_2c;
  float local_28;
  float local_24;
  float *local_20;
  int local_1c;
  float *local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  fVar10 = param_5;
  iVar2 = param_1 * -4;
  (&uStack_8c)[-param_1] = 0x5a4890;
  (&uStack_8c)[param_1 * -2] = 0x5a4899;
  (&uStack_8c)[param_1 * -3] = 0x5a48a7;
  local_58 = (float *)(&stack0xffffff78 + param_1 * -0x10);
  (&uStack_8c)[param_1 * -4] = 0x5a48b6;
  pfVar18 = local_58;
  local_28 = 0.0;
  local_24 = 0.0;
  local_2c = 1.0;
  local_8 = 0.0;
  local_c = 0.0;
  local_10 = param_5 + *param_3;
  if (local_10 < 1.0) {
    local_10 = 1.0;
    local_10 = 1.0;
  }
  local_1c = 1;
  fVar3 = local_10 * local_10 * 0.5;
  pfVar15 = (float *)(fVar3 + 0.0);
  local_20 = pfVar15;
  local_18 = pfVar15;
  local_14 = fVar3 * local_10 + 0.0;
  *(float **)(&stack0xffffff78 + iVar2) = pfVar15;
  *(float **)(&stack0xffffff78 + param_1 * -8) = local_18;
  *(undefined4 *)(&stack0xffffff78 + param_1 * -0xc) = 0;
  fVar3 = local_14;
  *local_58 = local_14;
  *(undefined4 *)(&stack0xffffff78 + param_1 * -0x14) = 0;
  param_5 = 1.0;
  if (1 < param_1) {
    if (3 < param_1 + -1) {
      local_3c = local_58 + 1;
      local_40 = &local_78 + param_1 * -3;
      local_34 = &local_7c + param_1 * -2;
      local_30 = (float *)(&stack0xffffff80 + iVar2);
      local_44 = (int)param_3 - (int)(&stack0xffffff78 + iVar2);
      local_48 = iVar2;
      local_4c = param_1 * -8;
      local_50 = (int)local_58 - (int)(&stack0xffffff78 + iVar2);
      local_54 = (float *)(param_1 * -0x10);
      local_64 = (int)param_3 - (int)(&stack0xffffff78 + param_1 * -8);
      local_68 = iVar2;
      local_6c = (int)local_58 - (int)(&stack0xffffff78 + param_1 * -8);
      local_70 = param_1 * -0xc;
      local_74 = (int)param_3 - (int)(&stack0xffffff78 + param_1 * -0xc);
      local_78 = (float)((int)local_58 - (int)(&stack0xffffff78 + param_1 * -0xc));
      local_7c = (float *)(param_1 * -8);
      local_5c = (int)param_3 - (int)local_58;
      iVar13 = param_1 * -0x14 - (int)local_58;
      local_58 = (float *)((param_1 - 5U >> 2) + 1);
      local_60 = &stack0xffffff78 + iVar13;
      local_1c = (int)local_58 * 4 + 1;
      do {
        pfVar8 = local_3c;
        fVar3 = *(float *)(local_5c + (int)local_3c) + fVar10;
        if (fVar3 < 1.0) {
          fVar3 = 1.0;
        }
        fVar5 = fVar3 * fVar3;
        fVar7 = param_5 * fVar5;
        local_18 = (float *)((float)local_18 + fVar7);
        local_c = param_5 * fVar7 + local_c;
        local_14 = local_14 + fVar3 * fVar5;
        local_8 = local_8 + fVar3 * fVar7;
        local_30[-1] = fVar5 + (float)pfVar15;
        local_34[-2] = local_18;
        local_40[-3] = local_c;
        puVar11 = local_60;
        *pfVar8 = local_14;
        pfVar12 = local_30;
        iVar13 = local_48;
        *(float *)(puVar11 + (int)pfVar8) = local_8;
        fVar7 = param_5 + 1.0;
        fVar3 = *(float *)(local_44 + (int)local_30) + fVar10;
        if (fVar3 < 1.0) {
          fVar3 = 1.0;
        }
        fVar6 = fVar3 * fVar3;
        fVar5 = fVar6 + fVar5 + (float)pfVar15;
        fVar4 = fVar7 * fVar6;
        local_18 = (float *)((float)local_18 + fVar4);
        local_c = fVar7 * fVar4 + local_c;
        local_14 = local_14 + fVar3 * fVar6;
        local_8 = fVar4 * fVar3 + local_8;
        *local_30 = fVar5;
        ppfVar1 = local_34;
        *(float **)(iVar13 + (int)pfVar12) = local_18;
        *(float *)(local_4c + (int)pfVar12) = local_c;
        *(float *)(local_50 + (int)pfVar12) = local_14;
        *(float *)((int)local_54 + (int)pfVar12) = local_8;
        fVar7 = fVar7 + 1.0;
        fVar3 = *(float *)(local_64 + (int)local_34) + fVar10;
        if (fVar3 < 1.0) {
          fVar3 = 1.0;
        }
        fVar6 = fVar3 * fVar3;
        fVar5 = fVar6 + fVar5;
        fVar4 = fVar7 * fVar6;
        local_18 = (float *)((float)local_18 + fVar4);
        local_c = local_c + fVar7 * fVar4;
        local_14 = local_14 + fVar3 * fVar6;
        local_8 = fVar3 * fVar4 + local_8;
        local_30[1] = fVar5;
        iVar13 = local_68;
        *ppfVar1 = local_18;
        pfVar12 = local_30;
        pfVar8 = local_40;
        *(float *)(iVar13 + (int)ppfVar1) = local_c;
        *(float *)(local_6c + (int)ppfVar1) = local_14;
        *(float *)(local_70 + (int)ppfVar1) = local_8;
        fVar7 = fVar7 + 1.0;
        local_10 = *(float *)(local_74 + (int)local_40) + fVar10;
        if (local_10 < 1.0) {
          local_10 = 1.0;
          local_10 = 1.0;
        }
        fVar4 = local_10 * local_10;
        local_30 = local_30 + 4;
        local_3c = local_3c + 4;
        pfVar14 = local_40 + 4;
        local_40 = pfVar14;
        pfVar15 = (float *)(fVar4 + fVar5);
        local_20 = pfVar15;
        fVar3 = fVar7 * fVar4;
        local_18 = (float *)((float)local_18 + fVar3);
        local_c = fVar7 * fVar3 + local_c;
        local_14 = local_14 + local_10 * fVar4;
        local_8 = fVar3 * local_10 + local_8;
        pfVar12[2] = (float)pfVar15;
        iVar13 = (int)local_58 + -1;
        local_58 = (float *)iVar13;
        ppfVar1 = local_34 + 1;
        local_34 = local_34 + 4;
        *ppfVar1 = local_18;
        fVar3 = local_78;
        *pfVar8 = local_c;
        *(float *)((int)fVar3 + -0x10 + (int)pfVar14) = local_14;
        *(float *)((int)(local_7c + -4) + (int)pfVar14) = local_8;
        param_5 = fVar7 + 1.0;
        fVar3 = local_14;
      } while (iVar13 != 0);
    }
    local_14 = fVar3;
    if (local_1c < param_1) {
      local_7c = (float *)(&stack0xffffff78 + local_1c * 4 + iVar2);
      iVar13 = (int)param_3 - (int)(&stack0xffffff78 + iVar2);
      local_44 = iVar13;
      local_48 = iVar2;
      local_4c = param_1 * -8;
      local_50 = (int)pfVar18 - (int)(&stack0xffffff78 + iVar2);
      local_54 = (float *)(param_1 * -0x10);
      param_3 = (float *)(param_1 - local_1c);
      pfVar15 = (float *)(&stack0xffffff78 + local_1c * 4 + iVar2);
      do {
        local_10 = *(float *)((int)pfVar15 + iVar13) + fVar10;
        if (local_10 < 1.0) {
          local_10 = 1.0;
        }
        fVar7 = local_10 * local_10;
        param_3 = (float *)((int)param_3 + -1);
        local_20 = (float *)(fVar7 + (float)local_20);
        fVar3 = param_5 * fVar7;
        pfVar8 = (float *)((float)local_18 + fVar3);
        local_18 = pfVar8;
        fVar5 = param_5 * fVar3 + local_c;
        local_c = fVar5;
        fVar7 = local_10 * fVar7 + local_14;
        local_14 = fVar7;
        fVar3 = fVar3 * local_10 + local_8;
        local_8 = fVar3;
        *pfVar15 = (float)local_20;
        pfVar15[-param_1] = (float)pfVar8;
        pfVar15[param_1 * -2] = fVar5;
        *(float *)((int)pfVar15 + ((int)pfVar18 - (int)(&stack0xffffff78 + iVar2))) = fVar7;
        pfVar15[param_1 * -4] = fVar3;
        param_5 = param_5 + 1.0;
        pfVar15 = pfVar15 + 1;
      } while (param_3 != (float *)0x0);
    }
  }
  uVar16 = *param_2;
  param_5 = 0.0;
  iVar13 = (int)uVar16 >> 0x10;
  local_1c = 0;
  if (iVar13 < 0) {
    local_34 = (float **)0x0;
    do {
      uVar16 = uVar16 & 0xffff;
      iVar17 = iVar13 * -4;
      local_20 = (float *)(*(float *)(&stack0xffffff78 + uVar16 * 4 + iVar2) +
                          *(float *)(&stack0xffffff78 + iVar17 + iVar2));
      local_18 = (float *)(*(float *)(&stack0xffffff78 + uVar16 * 4 + param_1 * -8) -
                          *(float *)(&stack0xffffff78 + iVar17 + param_1 * -8));
      local_c = *(float *)(&stack0xffffff78 + uVar16 * 4 + param_1 * -0xc) +
                *(float *)(&stack0xffffff78 + iVar17 + param_1 * -0xc);
      local_14 = pfVar18[uVar16] + pfVar18[-iVar13];
      local_8 = *(float *)(&stack0xffffff78 + uVar16 * 4 + param_1 * -0x14) -
                *(float *)(&stack0xffffff78 + iVar17 + param_1 * -0x14);
      local_28 = local_14 * local_c - (float)local_18 * local_8;
      local_24 = (float)local_20 * local_8 - (float)local_18 * local_14;
      local_2c = local_c * (float)local_20 - (float)local_18 * (float)local_18;
      param_3 = (float *)((local_28 + local_24 * param_5) / local_2c);
      if ((float)param_3 < 0.0) {
        param_3 = (float *)0x0;
      }
      *(float *)((int)local_34 + (int)param_4) = (float)param_3 - fVar10;
      local_1c = local_1c + 1;
      param_5 = param_5 + 1.0;
      uVar16 = param_2[local_1c];
      local_34 = (float **)(local_1c * 4);
      iVar13 = (int)uVar16 >> 0x10;
    } while (iVar13 < 0);
  }
  local_34 = (float **)(local_1c * 4);
  uVar16 = param_2[local_1c];
  while (uVar9 = uVar16 & 0xffff, (int)uVar9 < param_1) {
    param_3 = (float *)((int)uVar16 >> 0x10);
    local_20 = (float *)(*(float *)(&stack0xffffff78 + uVar9 * 4 + iVar2) -
                        *(float *)(&stack0xffffff78 + (int)param_3 * 4 + iVar2));
    local_18 = (float *)(*(float *)(&stack0xffffff78 + uVar9 * 4 + param_1 * -8) -
                        *(float *)(&stack0xffffff78 + (int)param_3 * 4 + param_1 * -8));
    local_c = *(float *)(&stack0xffffff78 + uVar9 * 4 + param_1 * -0xc) -
              *(float *)(&stack0xffffff78 + (int)param_3 * 4 + param_1 * -0xc);
    local_14 = pfVar18[uVar9] - pfVar18[(int)param_3];
    local_8 = *(float *)(&stack0xffffff78 + uVar9 * 4 + param_1 * -0x14) -
              *(float *)(&stack0xffffff78 + (int)param_3 * 4 + param_1 * -0x14);
    local_28 = local_14 * local_c - (float)local_18 * local_8;
    local_24 = (float)local_20 * local_8 - (float)local_18 * local_14;
    local_2c = local_c * (float)local_20 - (float)local_18 * (float)local_18;
    param_3 = (float *)((local_28 + local_24 * param_5) / local_2c);
    if ((float)param_3 < 0.0) {
      param_3 = (float *)0x0;
    }
    *(float *)((int)local_34 + (int)param_4) = (float)param_3 - fVar10;
    local_1c = local_1c + 1;
    param_5 = param_5 + 1.0;
    local_34 = (float **)(local_1c * 4);
    uVar16 = param_2[local_1c];
  }
  for (; local_1c < param_1; local_1c = local_1c + 1) {
    param_3 = (float *)((param_5 * local_24 + local_28) / local_2c);
    if ((float)param_3 < 0.0) {
      param_3 = (float *)0x0;
    }
    param_4[local_1c] = (float)param_3 - fVar10;
    param_5 = param_5 + 1.0;
  }
  if (0 < param_6) {
    param_5 = 0.0;
    iVar13 = param_6 / 2;
    local_1c = 0;
    if (iVar13 - param_6 < 0) {
      local_7c = (float *)(iVar13 * 4);
      local_50 = iVar13 - param_6;
      local_54 = (float *)(iVar13 * 4);
      iVar17 = (iVar13 - param_6) * -4;
      local_58 = (float *)((param_6 - iVar13) * 4);
      do {
        local_20 = (float *)(*(float *)(&stack0xffffff78 + iVar17 + iVar2) +
                            *(float *)(&stack0xffffff78 + (int)local_54 + iVar2));
        local_18 = (float *)(*(float *)(&stack0xffffff78 + (int)local_54 + param_1 * -8) -
                            *(float *)(&stack0xffffff78 + iVar17 + param_1 * -8));
        local_c = *(float *)(&stack0xffffff78 + iVar17 + param_1 * -0xc) +
                  *(float *)(&stack0xffffff78 + (int)local_54 + param_1 * -0xc);
        local_14 = *(float *)(iVar17 + (int)pfVar18) + *(float *)((int)local_54 + (int)pfVar18);
        local_8 = *(float *)(&stack0xffffff78 + (int)local_54 + param_1 * -0x14) -
                  *(float *)(&stack0xffffff78 + iVar17 + param_1 * -0x14);
        local_28 = local_c * local_14 - (float)local_18 * local_8;
        local_24 = (float)local_20 * local_8 - (float)local_18 * local_14;
        local_2c = local_c * (float)local_20 - (float)local_18 * (float)local_18;
        fVar3 = (local_28 + local_24 * param_5) / local_2c - fVar10;
        if (fVar3 < param_4[local_1c]) {
          param_4[local_1c] = fVar3;
        }
        local_54 = (float *)((int)local_54 + 4);
        param_5 = param_5 + 1.0;
        local_1c = local_1c + 1;
        iVar17 = (int)local_58 + -4;
        local_50 = local_50 + 1;
        local_58 = (float *)iVar17;
      } while (local_50 < 0);
    }
    local_7c = (float *)(local_1c + iVar13);
    if ((int)local_7c < param_1) {
      local_54 = local_7c;
      param_3 = (float *)(((int)local_7c - param_6) * 4);
      local_58 = (float *)((int)local_7c * 4);
      local_50 = (int)local_7c * 4;
      param_2 = (long *)(((iVar13 - param_6) + local_1c) * 4);
      do {
        local_20 = (float *)(*(float *)(&stack0xffffff78 + local_50 + iVar2) -
                            *(float *)((int)param_3 + (int)(&stack0xffffff78 + iVar2)));
        local_18 = (float *)(*(float *)(&stack0xffffff78 + local_50 + param_1 * -8) -
                            *(float *)((int)param_3 + (int)(&stack0xffffff78 + param_1 * -8)));
        local_c = *(float *)(&stack0xffffff78 + local_50 + param_1 * -0xc) -
                  *(float *)((int)param_3 + (int)(&stack0xffffff78 + param_1 * -0xc));
        local_14 = *(float *)(local_50 + (int)pfVar18) - *(float *)((int)param_3 + (int)pfVar18);
        local_8 = *(float *)(&stack0xffffff78 + local_50 + param_1 * -0x14) -
                  *(float *)((int)param_3 + (int)(&stack0xffffff78 + param_1 * -0x14));
        local_28 = local_c * local_14 - (float)local_18 * local_8;
        local_24 = (float)local_20 * local_8 - (float)local_18 * local_14;
        local_2c = local_c * (float)local_20 - (float)local_18 * (float)local_18;
        fVar3 = (local_28 + local_24 * param_5) / local_2c - fVar10;
        if (fVar3 < param_4[local_1c]) {
          param_4[local_1c] = fVar3;
        }
        param_2 = param_2 + 1;
        param_5 = param_5 + 1.0;
        local_1c = local_1c + 1;
        local_54 = (float *)((int)local_54 + 1);
        local_58 = (float *)(local_50 + 4);
        local_50 = local_50 + 4;
        param_3 = (float *)param_2;
      } while ((int)local_54 < param_1);
    }
    if (local_1c < param_1) {
      iVar2 = local_1c;
      if (3 < param_1 - local_1c) {
        iVar13 = ((param_1 - local_1c) - 4U >> 2) + 1;
        iVar2 = local_1c + iVar13 * 4;
        pfVar18 = param_4 + local_1c + 2;
        do {
          fVar3 = (param_5 * local_24 + local_28) / local_2c - fVar10;
          if (fVar3 < pfVar18[-2]) {
            pfVar18[-2] = fVar3;
          }
          fVar3 = ((param_5 + 1.0) * local_24 + local_28) / local_2c - fVar10;
          if (fVar3 < pfVar18[-1]) {
            pfVar18[-1] = fVar3;
          }
          fVar7 = param_5 + 1.0 + 1.0;
          fVar3 = (fVar7 * local_24 + local_28) / local_2c - fVar10;
          if (fVar3 < *pfVar18) {
            *pfVar18 = fVar3;
          }
          fVar7 = fVar7 + 1.0;
          fVar3 = (fVar7 * local_24 + local_28) / local_2c - fVar10;
          if (fVar3 < pfVar18[1]) {
            pfVar18[1] = fVar3;
          }
          param_5 = fVar7 + 1.0;
          pfVar18 = pfVar18 + 4;
          iVar13 = iVar13 + -1;
        } while (iVar13 != 0);
      }
      for (; iVar2 < param_1; iVar2 = iVar2 + 1) {
        fVar3 = (param_5 * local_24 + local_28) / local_2c - fVar10;
        if (fVar3 < param_4[iVar2]) {
          param_4[iVar2] = fVar3;
        }
        param_5 = param_5 + 1.0;
      }
    }
    return;
  }
  return;
}
