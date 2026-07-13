/*
 * Entry: 005a8a20
 * Name: dradf4
 * Namespace: Global
 * Signature: void dradf4(int param_1, int param_2, float * param_3, float * param_4, float * param_5, float * param_6, float * param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
dradf4(int param_1,int param_2,float *param_3,float *param_4,float *param_5,float *param_6,
      float *param_7)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  int in_EAX;
  float *pfVar9;
  uint in_ECX;
  float *pfVar10;
  float *in_EDX;
  float *pfVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  float *pfVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  float *pfVar22;
  uint uVar23;
  float *local_68;
  float *local_60;
  float *local_5c;
  float *local_54;
  float *local_50;
  float *local_48;
  float *local_44;
  int local_40;
  float *local_30;
  int local_2c;
  int local_28;
  int local_24;
  
  iVar14 = in_ECX * param_1;
  local_60 = (float *)(iVar14 * 2);
  iVar15 = 0;
  local_68 = (float *)(iVar14 * 3);
  local_48 = (float *)0x0;
  iVar13 = iVar14;
  if (3 < param_1) {
    local_40 = (param_1 - 4U >> 2) + 1;
    local_48 = (float *)(local_40 * 4);
    do {
      fVar1 = *(float *)(in_EAX + iVar13 * 4) + *(float *)(in_EAX + (int)local_68 * 4);
      fVar2 = *(float *)(in_EAX + (int)local_60 * 4) + *(float *)(in_EAX + iVar15 * 4);
      in_EDX[iVar15 * 4] = fVar1 + fVar2;
      in_EDX[iVar15 * 4 + in_ECX * 4 + -1] = fVar2 - fVar1;
      iVar12 = iVar15 * 4 + in_ECX * 2;
      iVar16 = iVar15 + in_ECX;
      in_EDX[iVar12 + -1] = *(float *)(in_EAX + iVar15 * 4) - *(float *)(in_EAX + (int)local_60 * 4)
      ;
      iVar15 = (int)local_68 + in_ECX;
      iVar19 = iVar13 + in_ECX;
      in_EDX[iVar12] = *(float *)(in_EAX + (int)local_68 * 4) - *(float *)(in_EAX + iVar13 * 4);
      iVar12 = (int)local_60 + in_ECX;
      fVar1 = *(float *)(in_EAX + iVar19 * 4) + *(float *)(in_EAX + iVar15 * 4);
      fVar2 = *(float *)(in_EAX + iVar12 * 4) + *(float *)(in_EAX + iVar16 * 4);
      in_EDX[iVar16 * 4] = fVar1 + fVar2;
      in_EDX[iVar16 * 4 + in_ECX * 4 + -1] = fVar2 - fVar1;
      iVar13 = iVar16 * 4 + in_ECX * 2;
      iVar17 = iVar16 + in_ECX;
      in_EDX[iVar13 + -1] = *(float *)(in_EAX + iVar16 * 4) - *(float *)(in_EAX + iVar12 * 4);
      iVar16 = iVar15 + in_ECX;
      iVar20 = iVar19 + in_ECX;
      in_EDX[iVar13] = *(float *)(in_EAX + iVar15 * 4) - *(float *)(in_EAX + iVar19 * 4);
      iVar12 = iVar12 + in_ECX;
      fVar1 = *(float *)(in_EAX + iVar20 * 4) + *(float *)(in_EAX + iVar16 * 4);
      fVar2 = *(float *)(in_EAX + iVar12 * 4) + *(float *)(in_EAX + iVar17 * 4);
      in_EDX[iVar17 * 4] = fVar1 + fVar2;
      in_EDX[iVar17 * 4 + in_ECX * 4 + -1] = fVar2 - fVar1;
      iVar13 = iVar17 * 4 + in_ECX * 2;
      iVar19 = iVar17 + in_ECX;
      in_EDX[iVar13 + -1] = *(float *)(in_EAX + iVar17 * 4) - *(float *)(in_EAX + iVar12 * 4);
      iVar17 = iVar16 + in_ECX;
      iVar21 = iVar20 + in_ECX;
      in_EDX[iVar13] = *(float *)(in_EAX + iVar16 * 4) - *(float *)(in_EAX + iVar20 * 4);
      iVar12 = iVar12 + in_ECX;
      fVar1 = *(float *)(in_EAX + iVar21 * 4) + *(float *)(in_EAX + iVar17 * 4);
      fVar2 = *(float *)(in_EAX + iVar12 * 4) + *(float *)(in_EAX + iVar19 * 4);
      in_EDX[iVar19 * 4] = fVar1 + fVar2;
      in_EDX[iVar19 * 4 + in_ECX * 4 + -1] = fVar2 - fVar1;
      iVar16 = iVar19 * 4 + in_ECX * 2;
      local_60 = (float *)(iVar12 + in_ECX);
      iVar15 = iVar19 + in_ECX;
      in_EDX[iVar16 + -1] = *(float *)(in_EAX + iVar19 * 4) - *(float *)(in_EAX + iVar12 * 4);
      local_68 = (float *)(iVar17 + in_ECX);
      iVar13 = iVar21 + in_ECX;
      local_40 = local_40 + -1;
      in_EDX[iVar16] = *(float *)(in_EAX + iVar17 * 4) - *(float *)(in_EAX + iVar21 * 4);
    } while (local_40 != 0);
  }
  if ((int)local_48 < param_1) {
    local_50 = (float *)(in_EAX + (int)local_60 * 4);
    local_48 = (float *)(param_1 - (int)local_48);
    pfVar22 = (float *)(in_EAX + iVar13 * 4);
    local_44 = (float *)(in_EAX + (int)local_68 * 4);
    do {
      fVar1 = *local_44;
      fVar2 = *pfVar22;
      fVar3 = *(float *)(in_EAX + iVar15 * 4) + *local_50;
      in_EDX[iVar15 * 4] = fVar1 + fVar2 + fVar3;
      in_EDX[iVar15 * 4 + in_ECX * 4 + -1] = fVar3 - (fVar1 + fVar2);
      iVar13 = iVar15 * 4 + in_ECX * 2;
      fVar1 = *local_50;
      local_50 = local_50 + in_ECX;
      in_EDX[iVar13 + -1] = *(float *)(in_EAX + iVar15 * 4) - fVar1;
      iVar15 = iVar15 + in_ECX;
      fVar1 = *pfVar22;
      pfVar22 = pfVar22 + in_ECX;
      local_48 = (float *)((int)local_48 + -1);
      in_EDX[iVar13] = *local_44 - fVar1;
      local_44 = local_44 + in_ECX;
    } while (local_48 != (float *)0x0);
  }
  if (1 < (int)in_ECX) {
    if (in_ECX != 2) {
      local_28 = 0;
      if (0 < param_1) {
        local_40 = iVar14 * 4;
        local_24 = param_1;
        local_68 = in_EDX;
        do {
          iVar15 = in_ECX * 2;
          iVar13 = iVar15 + local_28 * 4;
          if (2 < (int)in_ECX) {
            local_48 = local_68;
            local_30 = param_4;
            pfVar18 = (float *)(param_2 + 4);
            local_2c = (in_ECX - 3 >> 1) + 1;
            iVar12 = local_40;
            pfVar22 = (float *)(in_EAX + local_28 * 4);
            local_60 = in_EDX + iVar13 + iVar15;
            local_54 = in_EDX + iVar15 + local_28 * 4;
            local_50 = in_EDX + iVar13;
            do {
              iVar13 = iVar12 + 8;
              pfVar11 = pfVar22 + 2;
              fVar1 = *pfVar18 * *(float *)(iVar13 + in_EAX) +
                      pfVar18[-1] * *(float *)(iVar12 + 4 + in_EAX);
              iVar15 = iVar14 * 4 + iVar13;
              fVar2 = pfVar18[-1] * *(float *)(iVar13 + in_EAX) -
                      *pfVar18 * *(float *)(iVar12 + 4 + in_EAX);
              fVar3 = *(float *)((int)local_30 + ((int)param_3 - (int)param_4)) *
                      *(float *)(iVar15 + -4 + in_EAX) +
                      *(float *)(iVar15 + in_EAX) *
                      *(float *)(((int)param_3 - param_2) + (int)pfVar18);
              fVar4 = *(float *)(iVar15 + in_EAX) *
                      *(float *)((int)local_30 + ((int)param_3 - (int)param_4)) -
                      *(float *)(iVar15 + -4 + in_EAX) *
                      *(float *)((int)pfVar18 + ((int)param_3 - param_2));
              iVar15 = iVar15 + iVar14 * 4;
              pfVar10 = (float *)(iVar15 + -4 + in_EAX);
              fVar5 = *(float *)(iVar15 + in_EAX) *
                      *(float *)((int)pfVar18 + ((int)param_4 - param_2)) + *pfVar10 * *local_30;
              fVar6 = *(float *)(iVar15 + in_EAX) * *local_30 -
                      *pfVar10 * *(float *)((int)pfVar18 + ((int)param_4 - param_2));
              fVar7 = fVar1 + fVar5;
              fVar5 = fVar5 - fVar1;
              fVar1 = fVar2 + fVar6;
              fVar2 = fVar2 - fVar6;
              local_30 = local_30 + 2;
              pfVar18 = pfVar18 + 2;
              local_2c = local_2c + -1;
              fVar6 = fVar4 + *pfVar11;
              fVar4 = *pfVar11 - fVar4;
              fVar8 = fVar3 + pfVar22[1];
              fVar3 = pfVar22[1] - fVar3;
              local_48[1] = fVar7 + fVar8;
              local_48[2] = fVar1 + fVar6;
              local_50[-3] = fVar3 - fVar2;
              local_50[-2] = fVar5 - fVar4;
              local_54[1] = fVar2 + fVar3;
              local_54[2] = fVar4 + fVar5;
              local_60[-3] = fVar8 - fVar7;
              local_60[-2] = fVar1 - fVar6;
              iVar12 = iVar13;
              pfVar22 = pfVar11;
              local_60 = local_60 + -2;
              local_54 = local_54 + 2;
              local_50 = local_50 + -2;
              local_48 = local_48 + 2;
            } while (local_2c != 0);
          }
          local_68 = local_68 + in_ECX * 4;
          local_40 = local_40 + in_ECX * 4;
          local_28 = local_28 + in_ECX;
          local_24 = local_24 + -1;
        } while (local_24 != 0);
      }
      if ((in_ECX & 1) != 0) {
        return;
      }
    }
    fVar1 = hsqt2;
    iVar13 = iVar14 + -1 + in_ECX;
    local_68 = (float *)(iVar13 + iVar14 * 2);
    local_48 = (float *)0x0;
    uVar23 = in_ECX;
    local_50 = (float *)in_ECX;
    if (3 < param_1) {
      fVar2 = -hsqt2;
      local_60 = in_EDX + in_ECX * 3;
      local_5c = (float *)(in_EAX + (iVar14 + iVar13) * 4);
      local_54 = (float *)(in_ECX * 4 + -4 + in_EAX);
      local_24 = (param_1 - 4U >> 2) + 1;
      local_48 = (float *)(local_24 * 4);
      do {
        iVar15 = (int)local_68 + in_ECX;
        local_50 = (float *)((int)local_50 + in_ECX * 4);
        fVar3 = (*(float *)(in_EAX + iVar13 * 4) + *(float *)(in_EAX + (int)local_68 * 4)) * fVar2;
        iVar12 = iVar13 + in_ECX;
        fVar4 = (*(float *)(in_EAX + iVar13 * 4) - *(float *)(in_EAX + (int)local_68 * 4)) * fVar1;
        in_EDX[uVar23 - 1] = fVar4 + *local_54;
        local_60[-1] = *local_54 - fVar4;
        pfVar22 = local_5c + in_ECX;
        in_EDX[uVar23] = fVar3 - *local_5c;
        iVar17 = uVar23 + in_ECX * 4;
        pfVar18 = local_60 + in_ECX * 4;
        *local_60 = fVar3 + *local_5c;
        local_54 = local_54 + in_ECX;
        iVar13 = iVar15 + in_ECX;
        fVar3 = (*(float *)(in_EAX + iVar12 * 4) + *(float *)(in_EAX + iVar15 * 4)) * fVar2;
        iVar16 = iVar12 + in_ECX;
        fVar4 = (*(float *)(in_EAX + iVar12 * 4) - *(float *)(in_EAX + iVar15 * 4)) * fVar1;
        in_EDX[iVar17 + -1] = fVar4 + *local_54;
        pfVar18[-1] = *local_54 - fVar4;
        in_EDX[iVar17] = fVar3 - *pfVar22;
        *pfVar18 = fVar3 + *pfVar22;
        pfVar22 = pfVar22 + in_ECX;
        iVar17 = iVar17 + in_ECX * 4;
        pfVar18 = pfVar18 + in_ECX * 4;
        local_54 = local_54 + in_ECX;
        fVar3 = (*(float *)(in_EAX + iVar16 * 4) + *(float *)(in_EAX + iVar13 * 4)) * fVar2;
        iVar15 = iVar13 + in_ECX;
        iVar12 = iVar16 + in_ECX;
        fVar4 = (*(float *)(in_EAX + iVar16 * 4) - *(float *)(in_EAX + iVar13 * 4)) * fVar1;
        in_EDX[iVar17 + -1] = fVar4 + *local_54;
        pfVar18[-1] = *local_54 - fVar4;
        in_EDX[iVar17] = fVar3 - *pfVar22;
        *pfVar18 = fVar3 + *pfVar22;
        pfVar22 = pfVar22 + in_ECX;
        iVar17 = iVar17 + in_ECX * 4;
        pfVar18 = pfVar18 + in_ECX * 4;
        local_54 = local_54 + in_ECX;
        local_68 = (float *)(iVar15 + in_ECX);
        fVar3 = (*(float *)(in_EAX + iVar12 * 4) + *(float *)(in_EAX + iVar15 * 4)) * fVar2;
        iVar13 = iVar12 + in_ECX;
        fVar4 = (*(float *)(in_EAX + iVar12 * 4) - *(float *)(in_EAX + iVar15 * 4)) * fVar1;
        in_EDX[iVar17 + -1] = fVar4 + *local_54;
        pfVar18[-1] = *local_54 - fVar4;
        in_EDX[iVar17] = fVar3 - *pfVar22;
        *pfVar18 = fVar3 + *pfVar22;
        local_5c = pfVar22 + in_ECX;
        uVar23 = iVar17 + in_ECX * 4;
        local_60 = pfVar18 + in_ECX * 4;
        local_54 = local_54 + in_ECX;
        local_24 = local_24 + -1;
      } while (local_24 != 0);
    }
    if ((int)local_48 < param_1) {
      pfVar22 = in_EDX + uVar23 + in_ECX * 2;
      local_54 = (float *)(in_EAX + (int)local_68 * 4);
      pfVar18 = (float *)(in_EAX + iVar13 * 4);
      pfVar10 = (float *)(in_EAX + (iVar13 + iVar14) * 4);
      pfVar9 = (float *)(in_EAX + -4 + (int)local_50 * 4);
      param_1 = param_1 - (int)local_48;
      pfVar11 = in_EDX + uVar23;
      do {
        fVar4 = (*local_54 + *pfVar18) * -fVar1;
        fVar2 = *pfVar18;
        pfVar18 = pfVar18 + in_ECX;
        fVar3 = *local_54;
        local_54 = local_54 + in_ECX;
        fVar3 = (fVar2 - fVar3) * fVar1;
        pfVar11[-1] = fVar3 + *pfVar9;
        fVar2 = *pfVar9;
        pfVar9 = pfVar9 + in_ECX;
        pfVar22[-1] = fVar2 - fVar3;
        *pfVar11 = fVar4 - *pfVar10;
        pfVar11 = pfVar11 + in_ECX * 4;
        fVar2 = *pfVar10;
        pfVar10 = pfVar10 + in_ECX;
        *pfVar22 = fVar4 + fVar2;
        pfVar22 = pfVar22 + in_ECX * 4;
        param_1 = param_1 + -1;
      } while (param_1 != 0);
    }
  }
  return;
}
