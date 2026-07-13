/*
 * Entry: 005ab410
 * Name: dradb4
 * Namespace: Global
 * Signature: void dradb4(int param_1, int param_2, float * param_3, float * param_4, float * param_5, float * param_6, float * param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
dradb4(int param_1,int param_2,float *param_3,float *param_4,float *param_5,float *param_6,
      float *param_7)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  int in_EAX;
  float *pfVar20;
  int in_ECX;
  uint in_EDX;
  int iVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  int iVar25;
  float *pfVar26;
  int iVar27;
  uint uVar28;
  uint local_64;
  int local_60;
  int local_54;
  int local_48;
  float *local_44;
  float *local_40;
  float *local_3c;
  float *local_38;
  float *local_34;
  int local_30;
  float *local_2c;
  int local_28;
  float *local_24;
  int local_c;
  int local_8;
  
  iVar21 = in_EDX * param_1;
  local_64 = 0;
  iVar24 = in_EDX * 4;
  local_60 = 0;
  local_34 = (float *)0x0;
  if (3 < param_1) {
    iVar27 = in_EDX * 8;
    local_48 = iVar21 * 4;
    local_24 = (float *)((param_1 - 4U >> 2) + 1);
    local_34 = (float *)((int)local_24 * 4);
    iVar25 = iVar27;
    do {
      fVar4 = *(float *)(in_EAX + -4 + iVar25);
      fVar4 = fVar4 + fVar4;
      fVar5 = *(float *)(iVar25 + in_EAX) + *(float *)(iVar25 + in_EAX);
      fVar6 = *(float *)(in_EAX + local_60 * 4) - *(float *)(in_EAX + -4 + iVar27 + iVar25);
      fVar7 = *(float *)(in_EAX + -4 + iVar27 + iVar25) + *(float *)(in_EAX + local_60 * 4);
      local_60 = local_60 + iVar24;
      *(float *)(in_ECX + local_64 * 4) = fVar4 + fVar7;
      *(float *)(in_ECX + local_48) = fVar6 - fVar5;
      iVar23 = local_48 + iVar21 * 4;
      *(float *)(in_ECX + iVar23) = fVar7 - fVar4;
      *(float *)(iVar21 * 4 + iVar23 + in_ECX) = fVar6 + fVar5;
      local_48 = local_48 + in_EDX * 4;
      iVar25 = iVar25 + in_EDX * 0x10;
      fVar4 = *(float *)(in_EAX + -4 + iVar25);
      fVar4 = fVar4 + fVar4;
      fVar5 = *(float *)(iVar25 + in_EAX) + *(float *)(iVar25 + in_EAX);
      fVar6 = *(float *)(in_EAX + local_60 * 4) - *(float *)(in_EAX + -4 + iVar27 + iVar25);
      fVar7 = *(float *)(in_EAX + -4 + iVar27 + iVar25) + *(float *)(in_EAX + local_60 * 4);
      local_60 = local_60 + iVar24;
      iVar23 = local_64 + in_EDX + in_EDX;
      *(float *)(in_ECX + (local_64 + in_EDX) * 4) = fVar4 + fVar7;
      *(float *)(local_48 + in_ECX) = fVar6 - fVar5;
      iVar22 = local_48 + iVar21 * 4;
      *(float *)(iVar22 + in_ECX) = fVar7 - fVar4;
      *(float *)(iVar22 + iVar21 * 4 + in_ECX) = fVar6 + fVar5;
      local_48 = local_48 + in_EDX * 4;
      iVar25 = iVar25 + in_EDX * 0x10;
      fVar4 = *(float *)(in_EAX + -4 + iVar25);
      fVar4 = fVar4 + fVar4;
      fVar5 = *(float *)(iVar25 + in_EAX) + *(float *)(iVar25 + in_EAX);
      fVar6 = *(float *)(in_EAX + local_60 * 4) - *(float *)(in_EAX + -4 + iVar27 + iVar25);
      fVar7 = *(float *)(in_EAX + -4 + iVar27 + iVar25) + *(float *)(in_EAX + local_60 * 4);
      *(float *)(in_ECX + iVar23 * 4) = fVar4 + fVar7;
      *(float *)(local_48 + in_ECX) = fVar6 - fVar5;
      iVar22 = local_48 + iVar21 * 4;
      *(float *)(iVar22 + in_ECX) = fVar7 - fVar4;
      local_60 = local_60 + iVar24;
      *(float *)(iVar22 + iVar21 * 4 + in_ECX) = fVar6 + fVar5;
      local_48 = local_48 + in_EDX * 4;
      iVar25 = iVar25 + in_EDX * 0x10;
      fVar4 = *(float *)(in_EAX + -4 + iVar25);
      fVar4 = fVar4 + fVar4;
      iVar23 = iVar23 + in_EDX;
      fVar5 = *(float *)(iVar25 + in_EAX) + *(float *)(iVar25 + in_EAX);
      fVar6 = *(float *)(in_EAX + local_60 * 4) - *(float *)(in_EAX + -4 + iVar27 + iVar25);
      fVar7 = *(float *)(in_EAX + -4 + iVar27 + iVar25) + *(float *)(in_EAX + local_60 * 4);
      local_64 = iVar23 + in_EDX;
      local_60 = local_60 + iVar24;
      *(float *)(in_ECX + iVar23 * 4) = fVar4 + fVar7;
      *(float *)(local_48 + in_ECX) = fVar6 - fVar5;
      iVar23 = local_48 + iVar21 * 4;
      *(float *)(iVar23 + in_ECX) = fVar7 - fVar4;
      *(float *)(iVar23 + iVar21 * 4 + in_ECX) = fVar6 + fVar5;
      local_48 = local_48 + in_EDX * 4;
      iVar25 = iVar25 + in_EDX * 0x10;
      local_24 = (float *)((int)local_24 + -1);
    } while (local_24 != (float *)0x0);
  }
  if ((int)local_34 < param_1) {
    local_30 = (local_64 + iVar21) * 4;
    local_3c = (float *)((local_60 + in_EDX * 2) * 4);
    local_24 = (float *)(in_ECX + local_64 * 4);
    local_2c = (float *)(param_1 - (int)local_34);
    local_40 = (float *)(in_EAX + local_60 * 4);
    do {
      fVar4 = *(float *)((int)local_3c + -4 + in_EAX);
      fVar4 = fVar4 + fVar4;
      iVar27 = (int)local_3c + in_EDX * 8;
      fVar5 = *(float *)((int)local_3c + in_EAX) + *(float *)((int)local_3c + in_EAX);
      fVar6 = *local_40 - *(float *)(iVar27 + -4 + in_EAX);
      fVar7 = *local_40 + *(float *)(iVar27 + -4 + in_EAX);
      *local_24 = fVar4 + fVar7;
      *(float *)(local_30 + in_ECX) = fVar6 - fVar5;
      iVar27 = local_30 + iVar21 * 4;
      *(float *)(iVar27 + in_ECX) = fVar7 - fVar4;
      *(float *)(iVar27 + iVar21 * 4 + in_ECX) = fVar6 + fVar5;
      local_30 = local_30 + in_EDX * 4;
      local_24 = local_24 + in_EDX;
      local_3c = (float *)((int)local_3c + in_EDX * 0x10);
      local_40 = local_40 + in_EDX * 4;
      local_2c = (float *)((int)local_2c + -1);
    } while (local_2c != (float *)0x0);
  }
  if (1 < (int)in_EDX) {
    if (in_EDX != 2) {
      local_64 = 0;
      if (0 < param_1) {
        local_24 = (float *)0x0;
        local_8 = param_1;
        do {
          iVar27 = local_64 * 4 + in_EDX * 2;
          if (2 < (int)in_EDX) {
            local_40 = (float *)(in_EAX + iVar27 * 4);
            local_44 = param_4;
            iVar25 = local_64 * 4 - (int)local_24;
            local_28 = (iVar25 + iVar21) * 4;
            local_c = (in_EDX - 3 >> 1) + 1;
            pfVar26 = (float *)(param_2 + 4);
            local_3c = local_40;
            local_38 = (float *)(in_EAX + (iVar27 + in_EDX * 2) * 4);
            local_34 = (float *)(in_EAX + local_64 * 0x10);
            local_2c = (float *)(in_ECX + iVar25 * 4);
            do {
              pfVar20 = local_34 + 2;
              pfVar1 = local_3c + 2;
              pfVar2 = local_40 + -2;
              fVar4 = *pfVar20;
              local_28 = local_28 + 8;
              pfVar3 = local_38 + -2;
              fVar5 = *pfVar3;
              fVar6 = *pfVar20;
              fVar7 = *pfVar3;
              fVar8 = *pfVar1;
              fVar9 = *pfVar2;
              fVar10 = *pfVar1;
              fVar11 = *pfVar2;
              fVar12 = local_34[1];
              fVar13 = local_38[-3];
              fVar14 = local_34[1];
              fVar15 = local_38[-3];
              fVar16 = local_3c[1];
              fVar17 = local_40[-3];
              fVar18 = local_3c[1];
              fVar19 = local_40[-3];
              local_2c[1] = fVar18 + fVar19 + fVar14 + fVar15;
              fVar14 = (fVar14 + fVar15) - (fVar18 + fVar19);
              local_2c[2] = (fVar6 - fVar7) + (fVar8 - fVar9);
              fVar6 = (fVar6 - fVar7) - (fVar8 - fVar9);
              fVar8 = (fVar12 - fVar13) - (fVar10 + fVar11);
              fVar7 = fVar10 + fVar11 + (fVar12 - fVar13);
              fVar9 = fVar4 + fVar5 + (fVar16 - fVar17);
              fVar5 = (fVar4 + fVar5) - (fVar16 - fVar17);
              *(float *)(in_ECX + -4 + local_28) = fVar8 * pfVar26[-1] - fVar9 * *pfVar26;
              iVar27 = local_28 + iVar21 * 4;
              *(float *)(in_ECX + local_28) = fVar8 * *pfVar26 + pfVar26[-1] * fVar9;
              *(float *)(in_ECX + -4 + iVar27) =
                   fVar14 * *(float *)((int)local_44 + ((int)param_3 - (int)param_4)) -
                   fVar6 * *(float *)((int)pfVar26 + ((int)param_3 - param_2));
              *(float *)(iVar27 + in_ECX) =
                   fVar14 * *(float *)((int)pfVar26 + ((int)param_3 - param_2)) +
                   *(float *)((int)local_44 + ((int)param_3 - (int)param_4)) * fVar6;
              iVar27 = iVar27 + iVar21 * 4;
              *(float *)(in_ECX + -4 + iVar27) =
                   fVar7 * *local_44 - fVar5 * *(float *)((int)pfVar26 + ((int)param_4 - param_2));
              fVar4 = *local_44;
              local_44 = local_44 + 2;
              local_c = local_c + -1;
              *(float *)(in_ECX + iVar27) =
                   fVar7 * *(float *)((int)pfVar26 + ((int)param_4 - param_2)) + fVar4 * fVar5;
              pfVar26 = pfVar26 + 2;
              local_40 = pfVar2;
              local_3c = pfVar1;
              local_38 = pfVar3;
              local_34 = pfVar20;
              local_2c = local_2c + 2;
            } while (local_c != 0);
          }
          local_64 = local_64 + in_EDX;
          local_24 = (float *)((int)local_24 + in_EDX * 3);
          local_8 = local_8 + -1;
        } while (local_8 != 0);
      }
      uVar28 = in_EDX & 0x80000001;
      if ((int)uVar28 < 0) {
        uVar28 = (uVar28 - 1 | 0xfffffffe) + 1;
      }
      if (uVar28 == 1) {
        return;
      }
    }
    fVar4 = sqrt2;
    local_60 = in_EDX - 1;
    local_54 = in_EDX * 3;
    local_34 = (float *)0x0;
    local_64 = in_EDX;
    if (3 < param_1) {
      fVar5 = -sqrt2;
      local_8 = (param_1 - 4U >> 2) + 1;
      iVar27 = (local_60 + iVar21) * 4;
      local_34 = (float *)(local_8 * 4);
      do {
        fVar6 = *(float *)(in_EAX + local_54 * 4) + *(float *)(in_EAX + local_64 * 4);
        fVar7 = *(float *)(in_EAX + local_54 * 4) - *(float *)(in_EAX + local_64 * 4);
        fVar8 = *(float *)(in_EAX + -4 + local_64 * 4) - *(float *)(in_EAX + -4 + local_54 * 4);
        fVar9 = *(float *)(in_EAX + -4 + local_54 * 4) + *(float *)(in_EAX + -4 + local_64 * 4);
        iVar22 = local_64 + iVar24;
        *(float *)(in_ECX + local_60 * 4) = fVar9 + fVar9;
        iVar25 = iVar27 + iVar21 * 4;
        *(float *)(iVar27 + in_ECX) = fVar4 * (fVar8 - fVar6);
        *(float *)(in_ECX + iVar25) = fVar7 + fVar7;
        *(float *)(in_ECX + iVar25 + iVar21 * 4) = (fVar6 + fVar8) * fVar5;
        iVar27 = iVar27 + in_EDX * 4;
        local_54 = local_54 + iVar24;
        fVar6 = *(float *)(in_EAX + local_54 * 4) + *(float *)(in_EAX + iVar22 * 4);
        fVar7 = *(float *)(in_EAX + local_54 * 4) - *(float *)(in_EAX + iVar22 * 4);
        fVar8 = *(float *)(in_EAX + -4 + iVar22 * 4) - *(float *)(in_EAX + -4 + local_54 * 4);
        fVar9 = *(float *)(in_EAX + -4 + local_54 * 4) + *(float *)(in_EAX + -4 + iVar22 * 4);
        *(float *)(in_ECX + (local_60 + in_EDX) * 4) = fVar9 + fVar9;
        iVar25 = iVar27 + iVar21 * 4;
        *(float *)(iVar27 + in_ECX) = fVar4 * (fVar8 - fVar6);
        *(float *)(in_ECX + iVar25) = fVar7 + fVar7;
        iVar22 = iVar22 + iVar24;
        iVar23 = local_60 + in_EDX + in_EDX;
        *(float *)(in_ECX + iVar25 + iVar21 * 4) = (fVar6 + fVar8) * fVar5;
        iVar27 = iVar27 + in_EDX * 4;
        local_54 = local_54 + iVar24;
        fVar6 = *(float *)(in_EAX + local_54 * 4) + *(float *)(in_EAX + iVar22 * 4);
        fVar7 = *(float *)(in_EAX + local_54 * 4) - *(float *)(in_EAX + iVar22 * 4);
        fVar8 = *(float *)(in_EAX + -4 + iVar22 * 4) - *(float *)(in_EAX + -4 + local_54 * 4);
        fVar9 = *(float *)(in_EAX + -4 + local_54 * 4) + *(float *)(in_EAX + -4 + iVar22 * 4);
        iVar22 = iVar22 + iVar24;
        local_60 = iVar23 + in_EDX;
        *(float *)(in_ECX + iVar23 * 4) = fVar9 + fVar9;
        iVar25 = iVar27 + iVar21 * 4;
        *(float *)(iVar27 + in_ECX) = fVar4 * (fVar8 - fVar6);
        *(float *)(in_ECX + iVar25) = fVar7 + fVar7;
        *(float *)(in_ECX + iVar25 + iVar21 * 4) = (fVar6 + fVar8) * fVar5;
        iVar27 = iVar27 + in_EDX * 4;
        local_54 = local_54 + iVar24;
        fVar6 = *(float *)(in_EAX + local_54 * 4) + *(float *)(in_EAX + iVar22 * 4);
        fVar7 = *(float *)(in_EAX + local_54 * 4) - *(float *)(in_EAX + iVar22 * 4);
        fVar8 = *(float *)(in_EAX + -4 + iVar22 * 4) - *(float *)(in_EAX + -4 + local_54 * 4);
        fVar9 = *(float *)(in_EAX + -4 + local_54 * 4) + *(float *)(in_EAX + -4 + iVar22 * 4);
        *(float *)(in_ECX + local_60 * 4) = fVar9 + fVar9;
        local_60 = local_60 + in_EDX;
        local_64 = iVar22 + iVar24;
        local_54 = local_54 + iVar24;
        iVar25 = iVar27 + iVar21 * 4;
        *(float *)(iVar27 + in_ECX) = fVar4 * (fVar8 - fVar6);
        *(float *)(in_ECX + iVar25) = fVar7 + fVar7;
        *(float *)(in_ECX + iVar25 + iVar21 * 4) = (fVar6 + fVar8) * fVar5;
        iVar27 = iVar27 + in_EDX * 4;
        local_8 = local_8 + -1;
      } while (local_8 != 0);
    }
    if ((int)local_34 < param_1) {
      local_c = param_1 - (int)local_34;
      iVar24 = (local_60 + iVar21) * 4;
      param_1 = in_ECX + local_60 * 4;
      pfVar26 = (float *)(in_EAX + local_54 * 4);
      pfVar20 = (float *)(in_EAX + local_64 * 4);
      do {
        fVar5 = *pfVar20;
        fVar6 = *pfVar26;
        fVar7 = *pfVar26;
        fVar8 = *pfVar20;
        fVar9 = pfVar20[-1];
        fVar10 = pfVar26[-1];
        *(float *)param_1 = pfVar26[-1] + pfVar20[-1] + pfVar26[-1] + pfVar20[-1];
        param_1 = param_1 + in_EDX * 4;
        *(float *)(iVar24 + in_ECX) = fVar4 * ((fVar9 - fVar10) - (fVar5 + fVar6));
        iVar27 = iVar24 + iVar21 * 4;
        *(float *)(iVar27 + in_ECX) = (fVar7 - fVar8) + (fVar7 - fVar8);
        *(float *)(iVar27 + iVar21 * 4 + in_ECX) = (fVar5 + fVar6 + (fVar9 - fVar10)) * -fVar4;
        iVar24 = iVar24 + in_EDX * 4;
        pfVar20 = pfVar20 + in_EDX * 4;
        pfVar26 = pfVar26 + in_EDX * 4;
        local_c = local_c + -1;
      } while (local_c != 0);
    }
  }
  return;
}
