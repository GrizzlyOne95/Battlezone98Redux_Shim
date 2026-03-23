
void __fastcall FUN_004c5be0(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  undefined8 uVar8;
  float local_94 [2];
  float local_8c;
  float local_88;
  float fStack_84;
  float fStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  float fStack_58;
  float fStack_54;
  float fStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  int local_28;
  int iStack_24;
  int iStack_20;
  int iStack_1c;
  uint local_8;
  
  fVar4 = DAT_00920ef4;
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  *(int *)(param_1 + 0x70) =
       ((*(int *)(DAT_00917580 + 0x10) - *(int *)(DAT_00917580 + 8)) - *(int *)(param_1 + 0x80)) +
       -0x10;
  *(int *)(param_1 + 0x78) = *(int *)(param_1 + 0x70) + -1 + *(int *)(param_1 + 0x80);
  *(int *)(param_1 + 0x74) =
       ((*(int *)(DAT_00917580 + 0x14) - *(int *)(DAT_00917580 + 0xc)) - *(int *)(param_1 + 0x84)) +
       -0x10;
  *(int *)(param_1 + 0x7c) = *(int *)(param_1 + 0x74) + -1 + *(int *)(param_1 + 0x84);
  DAT_00920ef4 = DAT_00920ef4 + 0.03;
  fStack_80 = 1.0 / DAT_00920ef4;
  local_88 = (float)*(int *)(param_1 + 0x70);
  fStack_84 = (float)*(int *)(param_1 + 0x74);
  uStack_7c = 0;
  uStack_78 = 0;
  uStack_74 = 0x3f800000;
  fStack_70 = (float)*(int *)(param_1 + 0x78);
  fStack_6c = (float)*(int *)(param_1 + 0x74);
  uStack_64 = 0x3f800000;
  uStack_60 = 0;
  uStack_5c = 0x3f800000;
  fStack_58 = (float)*(int *)(param_1 + 0x78);
  fStack_54 = (float)*(int *)(param_1 + 0x7c);
  uStack_4c = 0x3f800000;
  uStack_48 = 0x3f800000;
  uStack_44 = 0x3f800000;
  fStack_40 = (float)*(int *)(param_1 + 0x70);
  fStack_3c = (float)*(int *)(param_1 + 0x7c);
  uStack_34 = 0;
  uStack_30 = 0x3f800000;
  uStack_2c = 0x3f800000;
  fStack_68 = fStack_80;
  fStack_50 = fStack_80;
  fStack_38 = fStack_80;
  FUN_00687d40(param_1 + 0xc4,DAT_00920ef4);
  FUN_00686600(DAT_00917594,&local_88,4,0xffffffff);
  FUN_006856e0();
  iVar5 = *(int *)(param_1 + 0x70);
  iVar1 = *(int *)(param_1 + 0x78);
  iVar2 = *(int *)(param_1 + 0x74);
  iVar3 = *(int *)(param_1 + 0x7c);
  DAT_00920ef4 = fVar4 + 0.02;
  FUN_004c5b20(DAT_00917580,iVar5 + -3,iVar2 + -3,*(int *)(param_1 + 0x80) + 6,DAT_0091755c);
  FUN_004c5b20(DAT_00917580,iVar5 + -1,iVar2 + -1,*(int *)(param_1 + 0x80) + 2,DAT_0091755c);
  FUN_004c5b20(DAT_00917580,iVar5 + -2,iVar2 + -2,*(int *)(param_1 + 0x80) + 4,DAT_00917588);
  FUN_0068af40(DAT_00917580,iVar5 + -1,iVar2 + -1,iVar1 + 1,iVar2 + -1,DAT_00917584,0);
  FUN_0068af40(DAT_00917580,iVar5 + -1,iVar2 + -1,iVar5 + -1,iVar3 + 1,DAT_00917584,0);
  FUN_0068af40(DAT_00917580,iVar5 + -3,iVar3 + 3,iVar1 + 3,iVar3 + 3,DAT_00917584,0);
  FUN_0068af40(DAT_00917580,iVar1 + 3,iVar2 + -3,iVar1 + 3,iVar3 + 3,DAT_00917584,0);
  local_28 = *(int *)(*(int *)(DAT_00917594 + 0x38) + 0x10) -
             *(int *)(*(int *)(DAT_00917594 + 0x38) + 8) >> 1;
  iStack_24 = *(int *)(*(int *)(DAT_00917594 + 0x38) + 0x14) -
              *(int *)(*(int *)(DAT_00917594 + 0x38) + 0xc) >> 1;
  iVar5 = FUN_004c7010(local_94,&local_28,DAT_00917594);
  if (iVar5 != 0) {
    fVar6 = local_94[0] - *(float *)(param_1 + 0x98);
    fVar7 = local_8c - *(float *)(param_1 + 0xa0);
    iVar5 = (int)(((float)*(int *)(param_1 + 0x80) * 0.25 * DAT_02ce99c8) /
                 *(float *)(param_1 + 0xb0));
    *(int *)(param_1 + 0x88) =
         (*(int *)(param_1 + 0x70) +
         (int)(((float)*(int *)(param_1 + 0x80) * fVar6) / *(float *)(param_1 + 0xb0))) - iVar5;
    *(int *)(param_1 + 0x8c) =
         (*(int *)(param_1 + 0x7c) -
         (int)(((float)*(int *)(param_1 + 0x84) * fVar7) / *(float *)(param_1 + 0xb8))) - iVar5;
    *(int *)(param_1 + 0x90) = *(int *)(param_1 + 0x88) + -1 + iVar5 * 2;
    *(int *)(param_1 + 0x94) = *(int *)(param_1 + 0x8c) + -1 + iVar5 * 2;
    DAT_00920ef4 = fVar4 + 0.01;
    FUN_004c5b20(DAT_00917580,*(undefined4 *)(param_1 + 0x88),*(undefined4 *)(param_1 + 0x8c),
                 iVar5 << 1,DAT_0091755c);
    uVar8 = FUN_008205a0(*(undefined4 *)(param_1 + 100));
    local_28 = (int)(((float)*(int *)(param_1 + 0x80) * fVar6) / *(float *)(param_1 + 0xb0)) +
               *(int *)(param_1 + 0x70);
    iStack_24 = *(int *)(param_1 + 0x7c) -
                (int)(((float)*(int *)(param_1 + 0x84) * fVar7) / *(float *)(param_1 + 0xb8));
    iStack_20 = local_28 - (int)((float)(iVar5 << 1) * (float)uVar8);
    iStack_1c = iStack_24 - (int)((float)(iVar5 << 1) * (float)((ulonglong)uVar8 >> 0x20));
    FUN_0068af40(DAT_00917580,local_28,iStack_24,iStack_20,iStack_1c,DAT_0091755c,0);
  }
  DAT_00920ef4 = fVar4;
  FUN_0083e885();
  return;
}

