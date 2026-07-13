/*
 * Entry: 005a86f0
 * Name: dradf2
 * Namespace: Global
 * Signature: void dradf2(int param_1, int param_2, float * param_3, float * param_4, float * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl dradf2(int param_1,int param_2,float *param_3,float *param_4,float *param_5)

{
  float fVar1;
  float fVar2;
  float *in_EAX;
  float *pfVar3;
  uint in_ECX;
  int iVar4;
  int iVar5;
  int iVar6;
  float *pfVar7;
  uint uVar8;
  float *pfVar9;
  float *pfVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  float *pfVar14;
  float *pfVar15;
  float *unaff_EDI;
  float *local_2c;
  float *local_28;
  float *local_24;
  float *local_20;
  float *local_1c;
  int local_14;
  int local_10;
  int local_c;
  
  iVar12 = in_ECX * param_1;
  iVar4 = 0;
  local_2c = (float *)0x0;
  iVar6 = iVar12;
  if (3 < param_1) {
    iVar11 = (param_1 - 4U >> 2) + 1;
    local_2c = (float *)(iVar11 * 4);
    pfVar10 = unaff_EDI + in_ECX * 2 + -1;
    do {
      unaff_EDI[iVar4 * 2] = in_EAX[iVar4] + in_EAX[iVar6];
      iVar5 = iVar4 + in_ECX;
      iVar13 = iVar6 + in_ECX;
      *pfVar10 = in_EAX[iVar4] - in_EAX[iVar6];
      pfVar10 = pfVar10 + in_ECX * 2;
      unaff_EDI[iVar5 * 2] = in_EAX[iVar5] + in_EAX[iVar13];
      iVar6 = iVar5 + in_ECX;
      iVar4 = iVar13 + in_ECX;
      *pfVar10 = in_EAX[iVar5] - in_EAX[iVar13];
      pfVar10 = pfVar10 + in_ECX * 2;
      unaff_EDI[iVar6 * 2] = in_EAX[iVar6] + in_EAX[iVar4];
      iVar5 = iVar6 + in_ECX;
      iVar13 = iVar4 + in_ECX;
      *pfVar10 = in_EAX[iVar6] - in_EAX[iVar4];
      unaff_EDI[iVar5 * 2] = in_EAX[iVar5] + in_EAX[iVar13];
      iVar4 = iVar5 + in_ECX;
      iVar6 = iVar13 + in_ECX;
      pfVar10[in_ECX * 2] = in_EAX[iVar5] - in_EAX[iVar13];
      pfVar10 = pfVar10 + in_ECX * 2 + in_ECX * 2;
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
  }
  if ((int)local_2c < param_1) {
    pfVar10 = unaff_EDI + iVar4 * 2;
    pfVar3 = in_EAX + iVar4;
    local_28 = unaff_EDI + in_ECX * 2 + iVar4 * 2 + -1;
    local_1c = (float *)(param_1 - (int)local_2c);
    pfVar9 = in_EAX + iVar6;
    do {
      *pfVar10 = *pfVar3 + *pfVar9;
      *local_28 = *pfVar3 - *pfVar9;
      local_28 = local_28 + in_ECX * 2;
      pfVar10 = pfVar10 + in_ECX * 2;
      pfVar3 = pfVar3 + in_ECX;
      pfVar9 = pfVar9 + in_ECX;
      local_1c = (float *)((int)local_1c + -1);
    } while (local_1c != (float *)0x0);
  }
  if (1 < (int)in_ECX) {
    if (in_ECX != 2) {
      if (0 < param_1) {
        local_1c = in_EAX + iVar12;
        local_24 = unaff_EDI + in_ECX * 2;
        local_10 = param_1;
        local_20 = in_EAX;
        pfVar10 = unaff_EDI;
        do {
          if (2 < (int)in_ECX) {
            local_2c = local_24;
            local_14 = (in_ECX - 3 >> 1) + 1;
            pfVar3 = local_1c;
            pfVar9 = (float *)(param_2 + 4);
            pfVar14 = local_20;
            local_28 = pfVar10;
            do {
              pfVar7 = pfVar3 + 2;
              pfVar15 = pfVar14 + 2;
              fVar1 = pfVar3[1] * pfVar9[-1] + *pfVar9 * *pfVar7;
              local_14 = local_14 + -1;
              fVar2 = pfVar9[-1] * *pfVar7 - pfVar3[1] * *pfVar9;
              local_28[2] = fVar2 + *pfVar15;
              local_2c[-2] = fVar2 - *pfVar15;
              local_28[1] = fVar1 + pfVar14[1];
              local_2c[-3] = pfVar14[1] - fVar1;
              pfVar3 = pfVar7;
              pfVar9 = pfVar9 + 2;
              pfVar14 = pfVar15;
              local_2c = local_2c + -2;
              local_28 = local_28 + 2;
            } while (local_14 != 0);
          }
          local_24 = local_24 + in_ECX * 2;
          pfVar10 = pfVar10 + in_ECX * 2;
          local_20 = local_20 + in_ECX;
          local_1c = local_1c + in_ECX;
          local_10 = local_10 + -1;
        } while (local_10 != 0);
      }
      uVar8 = in_ECX & 0x80000001;
      if ((int)uVar8 < 0) {
        uVar8 = (uVar8 - 1 | 0xfffffffe) + 1;
      }
      if (uVar8 == 1) {
        return;
      }
    }
    iVar6 = in_ECX - 1;
    iVar12 = iVar6 + iVar12;
    local_2c = (float *)0x0;
    uVar8 = in_ECX;
    if (3 < param_1) {
      local_c = (param_1 - 4U >> 2) + 1;
      local_2c = (float *)(local_c * 4);
      do {
        iVar4 = in_ECX * 2;
        unaff_EDI[uVar8] = -in_EAX[iVar12];
        unaff_EDI[uVar8 - 1] = in_EAX[iVar6];
        iVar11 = uVar8 + iVar4;
        iVar5 = iVar12 + in_ECX + in_ECX;
        unaff_EDI[iVar11] = -in_EAX[iVar12 + in_ECX];
        iVar12 = iVar6 + in_ECX + in_ECX;
        unaff_EDI[iVar11 + -1] = in_EAX[iVar6 + in_ECX];
        iVar11 = iVar11 + iVar4;
        iVar6 = iVar5 + in_ECX;
        unaff_EDI[iVar11] = -in_EAX[iVar5];
        iVar5 = iVar12 + in_ECX;
        unaff_EDI[iVar11 + -1] = in_EAX[iVar12];
        iVar11 = iVar11 + iVar4;
        iVar12 = iVar6 + in_ECX;
        unaff_EDI[iVar11] = -in_EAX[iVar6];
        iVar6 = iVar5 + in_ECX;
        unaff_EDI[iVar11 + -1] = in_EAX[iVar5];
        uVar8 = iVar11 + iVar4;
        local_c = local_c + -1;
      } while (local_c != 0);
    }
    if ((int)local_2c < param_1) {
      pfVar10 = in_EAX + iVar6;
      pfVar3 = in_EAX + iVar12;
      iVar6 = param_1 - (int)local_2c;
      pfVar9 = unaff_EDI + uVar8;
      do {
        fVar1 = *pfVar3;
        pfVar3 = pfVar3 + in_ECX;
        *pfVar9 = -fVar1;
        fVar1 = *pfVar10;
        pfVar10 = pfVar10 + in_ECX;
        pfVar9[-1] = fVar1;
        pfVar9 = pfVar9 + in_ECX * 2;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
  }
  return;
}
