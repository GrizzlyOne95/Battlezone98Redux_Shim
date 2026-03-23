
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_005dc300(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  float fVar7;
  int iVar8;
  int iVar9;
  float fVar10;
  int iVar11;
  undefined4 uVar12;
  int iVar13;
  int iVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  byte bVar17;
  int iVar18;
  int iVar19;
  float extraout_EDX;
  float extraout_EDX_00;
  int iVar20;
  float extraout_EDX_01;
  float extraout_EDX_02;
  float extraout_EDX_03;
  float extraout_EDX_04;
  float extraout_EDX_05;
  float extraout_EDX_06;
  float extraout_EDX_07;
  float extraout_EDX_08;
  float extraout_EDX_09;
  float extraout_EDX_10;
  float extraout_EDX_11;
  float extraout_EDX_12;
  float extraout_EDX_13;
  float extraout_EDX_14;
  float extraout_EDX_15;
  float10 fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  undefined8 uVar27;
  ulong local_f4;
  ulong local_ec;
  int local_e4;
  float local_d4;
  int local_d0;
  float local_cc;
  uint local_c8;
  uint local_c4;
  char local_c0;
  ulong local_b8;
  int local_b0;
  int local_90;
  int local_78;
  int local_70;
  uint local_6c;
  int local_4c;
  char local_10 [8];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  cVar3 = FUN_0047c070();
  if (cVar3 == 'a') {
    DAT_00918364 = DAT_00918348;
    *(undefined4 *)(param_1 + 0x1c) = DAT_00918360;
    *(undefined4 *)(param_1 + 0x10) = DAT_00918350;
  }
  else {
    DAT_00918364 = DAT_00918354;
    *(undefined4 *)(param_1 + 0x1c) = DAT_0091834c;
    *(undefined4 *)(param_1 + 0x10) = DAT_0091833c;
  }
  iVar4 = FUN_00417c70();
  if (iVar4 != 0) {
    uVar5 = FUN_004d9b40();
    iVar6 = FUN_00417ca0();
    fVar7 = (float)FUN_00689eb0();
    iVar8 = (DAT_02cecee0 * DAT_008ea368) / 2 + (int)((float)_DAT_008ea360 * fVar7);
    FUN_00689eb0();
    iVar9 = (DAT_02cecee4 * DAT_008ea36c) / 2 + (int)((float)_DAT_008ea364 * extraout_EDX);
    fVar7 = (float)DAT_02cecee0 / (float)_DAT_008ea3c0;
    fVar22 = (float)DAT_02cecee4 / (float)_DAT_008ea3c4;
    local_cc = fVar22;
    if (fVar7 < fVar22) {
      local_cc = fVar7;
    }
    fVar23 = (float)_DAT_00918358;
    fVar24 = (float)_DAT_0091835c;
    fVar25 = (float)_DAT_00918358;
    fVar26 = (float)_DAT_0091835c;
    fVar10 = (float)FUN_00689eb0();
    iVar18 = (int)((float)_DAT_008ea3c8 * fVar7 + (float)_DAT_00918340 * local_cc +
                   (float)(int)((fVar25 * fVar7 - fVar23 * local_cc) / 2.0) +
                  (float)_DAT_008ea370 * fVar10);
    FUN_00689eb0();
    iVar20 = (int)((float)_DAT_008ea3cc * fVar22 + (float)_DAT_00918344 * local_cc +
                   (float)(int)((fVar26 * fVar22 - fVar24 * local_cc) / 2.0) +
                  (float)_DAT_008ea374 * extraout_EDX_00);
    if (iVar6 == 0) {
      local_c4 = 0;
      local_c8 = 0;
    }
    else {
      local_c4 = FUN_00417f90();
      local_c8 = FUN_00417fb0();
    }
    iVar11 = FUN_00417c80();
    uVar12 = FUN_0046d060();
    fVar7 = DAT_00920ef4;
    local_78 = 0;
    local_6c = 0;
    for (local_4c = 0; local_4c < 5; local_4c = local_4c + 1) {
      FUN_00689eb0();
      iVar19 = (int)((float)(local_4c * 0xb) * extraout_EDX_01);
      fVar22 = DAT_00920ef4;
      if (((400 < DAT_02cecee0) &&
          (DAT_00920ef4 = DAT_00920ef4 + 0.0001, fVar22 = fVar7, DAT_00915567 == '\0')) &&
         (local_4c == 0)) {
        fVar10 = (float)FUN_00689eb0();
        iVar13 = FUN_0068f090(DAT_00918364);
        FUN_00689eb0();
        iVar14 = FUN_0068f0c0(DAT_00918364);
        FUN_00689eb0();
        fVar23 = (float)FUN_00689eb0();
        FUN_0068ca30(DAT_00917580,uVar5,DAT_00918364,iVar18 - (int)(fVar23 * 10.0),
                     iVar20 - (int)(extraout_EDX_03 * 16.0),
                     (int)(((float)(iVar13 + 0x2d) * fVar10) / 2.0),
                     (int)(((float)iVar14 * extraout_EDX_02) / 2.0),0,0);
      }
      DAT_00920ef4 = fVar22;
      if (iVar6 == 0) {
        local_d0 = 0;
      }
      else {
        local_d0 = FUN_00417f40(local_4c);
      }
      if (local_d0 == 0) {
        local_90 = 0;
      }
      else if ((*(int *)(local_d0 + 0x84) < 0x46) || (0x4a < *(int *)(local_d0 + 0x84))) {
        local_90 = 0;
      }
      else {
        local_90 = *(int *)(&DAT_008ea39c + (*(int *)(local_d0 + 0x84) + -0x46) * 8);
      }
      if (iVar6 == 0) {
        local_e4 = 0;
      }
      else {
        local_e4 = FUN_00417f60(local_4c);
      }
      if (local_e4 == 0) {
        local_70 = 0;
        local_b0 = 0;
      }
      else {
        local_70 = *(int *)(local_e4 + 8) + 0x38;
        local_b0 = *(int *)(local_e4 + 0xb0);
      }
      bVar17 = (byte)local_4c;
      if (iVar11 < local_b0) {
        local_6c = 1 << (bVar17 & 0x1f) | local_6c;
      }
      if ((1 << (bVar17 & 0x1f) & local_c4) == 0) {
        if ((~local_6c & local_c8 & 1 << (bVar17 & 0x1f)) == 0) {
          local_f4 = DAT_00917588;
        }
        else {
          local_f4 = DAT_009175b0;
        }
        local_b8 = local_f4;
      }
      else {
        local_78 = local_78 + local_b0;
        if ((~local_6c & local_c8 & 1 << (bVar17 & 0x1f)) == 0) {
          local_ec = DAT_0091755c;
        }
        else {
          local_ec = DAT_00917560;
        }
        local_b8 = local_ec;
      }
      if (DAT_00915567 == '\0') {
        FUN_00417990(local_b8);
        if (local_90 != 0) {
          FUN_00689eb0();
          fVar22 = (float)FUN_00689eb0();
          FUN_0068c560(DAT_00917580,local_90,(int)(fVar22 * 8.0) + iVar18,
                       iVar20 + iVar19 + (int)(extraout_EDX_04 * 1.0),5,0);
        }
        if (local_70 != 0) {
          uVar15 = FUN_0081cb40("names",local_70);
          std::_Init_atomic_counter(DAT_0091552c,local_b8);
          fVar22 = (float)FUN_00689eb0();
          FUN_00689d10(DAT_0091552c,DAT_00917580,(int)(fVar22 * 18.0) + iVar18,iVar20 + iVar19,
                       uVar15);
        }
      }
    }
    if ((local_6c == 0) || (local_6c != local_c8)) {
      local_c0 = '\0';
    }
    else {
      local_c0 = '\x01';
    }
    if ((*(char *)(param_1 + 0x29) == '\0') && (local_c0 != '\0')) {
      FUN_0047c330(iVar4);
    }
    *(char *)(param_1 + 0x29) = local_c0;
    fVar21 = (float10)(**(code **)(*(int *)(iVar4 + 0x18) + 0x1c))(uVar12);
    if ((*(char *)(param_1 + 0x28) == '\0') && ((float)fVar21 < 0.25)) {
      FUN_0047c380(iVar4);
    }
    *(bool *)(param_1 + 0x28) = (float)fVar21 < 0.25;
    uVar12 = *(undefined4 *)(DAT_00917580 + 8);
    uVar15 = *(undefined4 *)(DAT_00917580 + 0xc);
    uVar1 = *(undefined4 *)(DAT_00917580 + 0x10);
    uVar2 = *(undefined4 *)(DAT_00917580 + 0x14);
    uVar16 = FUN_005db9b0(*(undefined4 *)(param_1 + 0x18));
    fVar7 = (float)FUN_00689eb0();
    fVar23 = (float)_DAT_008ea378;
    FUN_00689eb0();
    iVar20 = (int)(((float)_DAT_008ea37c * extraout_EDX_05) / 2.0) + iVar9;
    fVar22 = (float)FUN_00689eb0();
    iVar11 = (int)(((float)_DAT_008ea380 * fVar22) / 2.0) + iVar8;
    FUN_00689eb0();
    iVar4 = (int)(((float)_DAT_008ea384 * extraout_EDX_06) / 2.0) + iVar9;
    FUN_00417990(uVar16);
    fVar22 = (float)FUN_00689eb0();
    iVar6 = FUN_0068f090(*(undefined4 *)(param_1 + 0x10));
    FUN_00689eb0();
    iVar18 = FUN_0068f0c0(*(undefined4 *)(param_1 + 0x10));
    fVar10 = (float)FUN_00689eb0();
    FUN_0068ca30(DAT_00917580,uVar5,*(undefined4 *)(param_1 + 0x10),
                 iVar11 - (int)((fVar10 * 20.0) / 2.0),iVar4,(int)(((float)iVar6 * fVar22) / 2.0),
                 (int)(((float)iVar18 * extraout_EDX_07) / 2.0),0x20005,0);
    iVar18 = (int)((1.0 - *(float *)(param_1 + 0x18)) * (float)((iVar4 - iVar20) + 1));
    *(int *)(DAT_00917580 + 8) = (int)((fVar23 * fVar7) / 2.0) + iVar8;
    *(int *)(DAT_00917580 + 0xc) = iVar20 + iVar18;
    *(int *)(DAT_00917580 + 0x10) = iVar11;
    *(int *)(DAT_00917580 + 0x14) = iVar4;
    fVar7 = (float)FUN_00689eb0();
    iVar4 = FUN_0068f090(*(undefined4 *)(param_1 + 0x14));
    FUN_00689eb0();
    iVar6 = FUN_0068f0c0(*(undefined4 *)(param_1 + 0x14));
    FUN_0068ca30(DAT_00917580,uVar5,*(undefined4 *)(param_1 + 0x14),0,-iVar18,
                 (int)(((float)iVar4 * fVar7) / 2.0),(int)(((float)iVar6 * extraout_EDX_08) / 2.0),
                 0x200005,0);
    iVar4 = DAT_00917580;
    *(undefined4 *)(DAT_00917580 + 8) = uVar12;
    *(undefined4 *)(iVar4 + 0xc) = uVar15;
    *(undefined4 *)(iVar4 + 0x10) = uVar1;
    *(undefined4 *)(iVar4 + 0x14) = uVar2;
    uVar16 = DAT_00917578;
    fVar7 = (float)FUN_00689eb0();
    iVar6 = (int)(((float)_DAT_008ea388 * fVar7) / 2.0) + iVar8;
    FUN_00689eb0();
    iVar11 = (int)(((float)_DAT_008ea38c * extraout_EDX_09) / 2.0) + iVar9;
    FUN_00689eb0();
    iVar8 = (int)(((float)_DAT_008ea390 * extraout_EDX_10) / 2.0) + iVar8;
    FUN_00689eb0();
    iVar9 = (int)(((float)_DAT_008ea394 * extraout_EDX_11) / 2.0) + iVar9;
    fVar7 = (float)FUN_00689eb0();
    iVar4 = FUN_0068f090(*(undefined4 *)(param_1 + 0x1c));
    FUN_00689eb0();
    iVar18 = FUN_0068f0c0(*(undefined4 *)(param_1 + 0x1c));
    FUN_00417990(uVar16);
    FUN_00689eb0();
    FUN_0068ca30(DAT_00917580,uVar5,*(undefined4 *)(param_1 + 0x1c),iVar6,
                 (int)(extraout_EDX_13 * 2.0) + iVar9,(int)(((float)iVar4 * fVar7) / 2.0),
                 (int)(((float)iVar18 * extraout_EDX_12) / 2.0),5,0);
    iVar18 = (int)((1.0 - *(float *)(param_1 + 0x24)) * (float)((iVar9 - iVar11) + 1));
    *(int *)(DAT_00917580 + 8) = iVar6;
    *(int *)(DAT_00917580 + 0xc) = iVar11 + iVar18;
    *(int *)(DAT_00917580 + 0x10) = iVar8;
    *(int *)(DAT_00917580 + 0x14) = iVar9;
    fVar7 = (float)FUN_00689eb0();
    iVar4 = FUN_0068f090(*(undefined4 *)(param_1 + 0x20));
    FUN_00689eb0();
    iVar20 = FUN_0068f0c0(*(undefined4 *)(param_1 + 0x20));
    FUN_0068ca30(DAT_00917580,uVar5,*(undefined4 *)(param_1 + 0x20),0,-iVar18,
                 (int)(((float)iVar4 * fVar7) / 2.0),(int)(((float)iVar20 * extraout_EDX_14) / 2.0),
                 0x200001,0);
    iVar4 = DAT_00917580;
    *(undefined4 *)(DAT_00917580 + 8) = uVar12;
    *(undefined4 *)(iVar4 + 0xc) = uVar15;
    *(undefined4 *)(iVar4 + 0x10) = uVar1;
    *(undefined4 *)(iVar4 + 0x14) = uVar2;
    if (0 < local_78) {
      std::_Init_atomic_counter(DAT_0091552c,DAT_0091755c);
      iVar4 = FUN_00417c80();
      sprintf(local_10,"%4ld",iVar4 / local_78);
      uVar27 = FUN_00689eb0();
      if (DAT_00915567 != '\0') {
        FUN_00689ec0((float)uVar27 * 0.9,(float)((ulonglong)uVar27 >> 0x20) * 0.9);
      }
      FUN_00689eb0();
      FUN_00689d10(DAT_0091552c,DAT_00917580,iVar6,
                   (iVar11 - (int)((extraout_EDX_15 * 20.0) / 2.0)) + iVar18,local_10);
      if (DAT_00915567 != '\0') {
        FUN_00689ec0(uVar27);
      }
    }
    iVar4 = FUN_0046d060();
    if (iVar4 == 0) {
      local_d4 = 0.0;
    }
    else {
      iVar4 = FUN_0046d060();
      local_d4 = (float)local_78 / (float)iVar4;
    }
    local_d4 = *(float *)(param_1 + 0x24) - local_d4;
    if (0.0 < local_d4) {
      iVar4 = (int)((float)iVar9 + (float)((iVar11 - iVar9) + 1) * local_d4);
      FUN_0068af70(DAT_00917580,iVar8 + -5,iVar4,iVar8,iVar4,DAT_0091755c,0);
      FUN_0068af70(DAT_00917580,iVar8 + -3,iVar4 + 1,iVar8,iVar4 + 1,DAT_0091755c,0);
      FUN_0068af70(DAT_00917580,iVar8 + -1,iVar4 + 2,iVar8,iVar4 + 2,DAT_0091755c,0);
    }
  }
  FUN_0083e885();
  return;
}

