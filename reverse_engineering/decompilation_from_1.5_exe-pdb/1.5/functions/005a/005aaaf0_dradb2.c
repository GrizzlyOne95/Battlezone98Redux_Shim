/*
 * Entry: 005aaaf0
 * Name: dradb2
 * Namespace: Global
 * Signature: void dradb2(int param_1, int param_2, float * param_3, float * param_4, float * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl dradb2(int param_1,int param_2,float *param_3,float *param_4,float *param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int in_EAX;
  float *pfVar5;
  float *in_ECX;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  float *pfVar10;
  uint uVar11;
  uint in_EDX;
  int iVar12;
  float *pfVar13;
  float *pfVar14;
  int local_2c;
  float *local_28;
  float *local_24;
  float *local_1c;
  float *local_18;
  float *local_14;
  int local_10;
  int local_c;
  
  iVar6 = in_EDX * param_1;
  iVar7 = 0;
  iVar12 = in_EDX * 2;
  local_2c = 0;
  local_24 = (float *)0x0;
  if (3 < param_1) {
    local_14 = (float *)((param_1 - 4U >> 2) + 1);
    local_24 = (float *)((int)local_14 * 4);
    pfVar10 = in_ECX + iVar6;
    do {
      iVar8 = iVar12 + -1 + local_2c;
      in_ECX[iVar7] = *(float *)(in_EAX + local_2c * 4) + *(float *)(in_EAX + iVar8 * 4);
      iVar7 = iVar7 + in_EDX;
      *pfVar10 = *(float *)(in_EAX + local_2c * 4) - *(float *)(in_EAX + iVar8 * 4);
      pfVar10 = pfVar10 + in_EDX;
      pfVar13 = (float *)(in_EAX + (iVar12 + -1 + iVar7 * 2) * 4);
      in_ECX[iVar7] = *(float *)(in_EAX + iVar7 * 8) + *pfVar13;
      iVar8 = iVar7 + in_EDX;
      *pfVar10 = *(float *)(in_EAX + iVar7 * 8) - *pfVar13;
      pfVar10 = pfVar10 + in_EDX;
      pfVar13 = (float *)(in_EAX + (iVar12 + -1 + iVar8 * 2) * 4);
      in_ECX[iVar8] = *(float *)(in_EAX + iVar8 * 8) + *pfVar13;
      iVar9 = iVar8 + in_EDX;
      *pfVar10 = *(float *)(in_EAX + iVar8 * 8) - *pfVar13;
      pfVar13 = (float *)(in_EAX + (iVar12 + -1 + iVar9 * 2) * 4);
      in_ECX[iVar9] = *(float *)(in_EAX + iVar9 * 8) + *pfVar13;
      iVar7 = iVar9 + in_EDX;
      pfVar10[in_EDX] = *(float *)(in_EAX + iVar9 * 8) - *pfVar13;
      pfVar10 = pfVar10 + in_EDX + in_EDX;
      local_14 = (float *)((int)local_14 + -1);
      local_2c = iVar7 * 2;
    } while (local_14 != (float *)0x0);
  }
  if ((int)local_24 < param_1) {
    local_18 = (float *)(param_1 - (int)local_24);
    local_14 = in_ECX + iVar6 + iVar7;
    do {
      iVar8 = iVar12 + -1 + local_2c;
      in_ECX[iVar7] = *(float *)(in_EAX + local_2c * 4) + *(float *)(in_EAX + iVar8 * 4);
      iVar7 = iVar7 + in_EDX;
      *local_14 = *(float *)(in_EAX + local_2c * 4) - *(float *)(in_EAX + iVar8 * 4);
      local_14 = local_14 + in_EDX;
      local_18 = (float *)((int)local_18 + -1);
      local_2c = iVar7 * 2;
    } while (local_18 != (float *)0x0);
  }
  if (1 < (int)in_EDX) {
    if (in_EDX != 2) {
      iVar7 = 0;
      local_2c = 0;
      if (0 < param_1) {
        local_18 = in_ECX + iVar6;
        local_c = param_1;
        local_14 = in_ECX;
        do {
          if (2 < (int)in_EDX) {
            local_24 = local_18;
            local_1c = local_14;
            local_10 = (in_EDX - 3 >> 1) + 1;
            pfVar10 = (float *)(in_EAX + iVar7 * 4);
            pfVar13 = (float *)(in_EAX + (iVar12 + iVar7) * 4);
            local_28 = (float *)(param_2 + 4);
            do {
              pfVar5 = pfVar10 + 2;
              pfVar14 = pfVar13 + -2;
              local_1c[1] = pfVar10[1] + pfVar13[-3];
              fVar1 = pfVar10[1];
              fVar2 = pfVar13[-3];
              local_1c[2] = *pfVar5 - *pfVar14;
              fVar3 = *pfVar14;
              fVar4 = *pfVar5;
              local_24[1] = (fVar1 - fVar2) * local_28[-1] - (fVar3 + fVar4) * *local_28;
              local_10 = local_10 + -1;
              local_24[2] = (fVar1 - fVar2) * *local_28 + local_28[-1] * (fVar3 + fVar4);
              pfVar10 = pfVar5;
              pfVar13 = pfVar14;
              local_28 = local_28 + 2;
              local_24 = local_24 + 2;
              local_1c = local_1c + 2;
            } while (local_10 != 0);
          }
          local_2c = local_2c + in_EDX;
          local_18 = local_18 + in_EDX;
          local_14 = local_14 + in_EDX;
          iVar7 = local_2c * 2;
          local_c = local_c + -1;
        } while (local_c != 0);
      }
      uVar11 = in_EDX & 0x80000001;
      if ((int)uVar11 < 0) {
        uVar11 = (uVar11 - 1 | 0xfffffffe) + 1;
      }
      if (uVar11 == 1) {
        return;
      }
    }
    iVar7 = in_EDX - 1;
    local_24 = (float *)0x0;
    local_2c = iVar7;
    if (3 < param_1) {
      local_c = (param_1 - 4U >> 2) + 1;
      local_24 = (float *)(local_c * 4);
      pfVar10 = in_ECX + iVar7 + iVar6;
      do {
        fVar1 = *(float *)(in_EAX + iVar7 * 4);
        in_ECX[local_2c] = fVar1 + fVar1;
        fVar1 = *(float *)(in_EAX + 4 + iVar7 * 4);
        iVar7 = iVar7 + iVar12;
        *pfVar10 = -(fVar1 + fVar1);
        pfVar10 = pfVar10 + in_EDX;
        fVar1 = *(float *)(in_EAX + iVar7 * 4);
        in_ECX[local_2c + in_EDX] = fVar1 + fVar1;
        local_2c = local_2c + in_EDX + in_EDX;
        fVar1 = *(float *)(in_EAX + 4 + iVar7 * 4);
        iVar7 = iVar7 + iVar12;
        *pfVar10 = -(fVar1 + fVar1);
        pfVar10 = pfVar10 + in_EDX;
        fVar1 = *(float *)(in_EAX + iVar7 * 4);
        in_ECX[local_2c] = fVar1 + fVar1;
        local_2c = local_2c + in_EDX;
        fVar1 = *(float *)(in_EAX + 4 + iVar7 * 4);
        iVar7 = iVar7 + iVar12;
        *pfVar10 = -(fVar1 + fVar1);
        fVar1 = *(float *)(in_EAX + iVar7 * 4);
        in_ECX[local_2c] = fVar1 + fVar1;
        local_2c = local_2c + in_EDX;
        fVar1 = *(float *)(in_EAX + 4 + iVar7 * 4);
        iVar7 = iVar7 + iVar12;
        pfVar10[in_EDX] = -(fVar1 + fVar1);
        pfVar10 = pfVar10 + in_EDX + in_EDX;
        local_c = local_c + -1;
      } while (local_c != 0);
    }
    if ((int)local_24 < param_1) {
      pfVar10 = in_ECX + local_2c;
      iVar12 = param_1 - (int)local_24;
      pfVar13 = in_ECX + local_2c + iVar6;
      pfVar5 = (float *)(in_EAX + iVar7 * 4);
      do {
        *pfVar10 = *pfVar5 + *pfVar5;
        pfVar10 = pfVar10 + in_EDX;
        pfVar14 = pfVar5 + 1;
        pfVar5 = pfVar5 + in_EDX * 2;
        *pfVar13 = -(*pfVar14 + *pfVar14);
        pfVar13 = pfVar13 + in_EDX;
        iVar12 = iVar12 + -1;
      } while (iVar12 != 0);
    }
  }
  return;
}
