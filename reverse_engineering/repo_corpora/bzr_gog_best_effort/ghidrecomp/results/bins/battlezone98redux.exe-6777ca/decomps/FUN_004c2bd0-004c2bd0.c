
void __thiscall FUN_004c2bd0(int param_1,undefined4 param_2)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int local_c4;
  int local_c0;
  int local_b0;
  int local_a4;
  int local_a0;
  int aiStack_98 [5];
  undefined4 uStack_84;
  int iStack_80;
  int iStack_7c;
  undefined4 uStack_78;
  int iStack_74;
  int iStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  int iStack_50;
  int iStack_4c;
  char local_48 [64];
  uint local_8;
  
  fVar1 = DAT_00920ef4;
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  DAT_00920ef4 = DAT_00920ef4 + 0.03;
  FUN_0068af70(DAT_00917580,*(undefined4 *)(param_1 + 0x100),*(undefined4 *)(param_1 + 0x104),
               *(undefined4 *)(param_1 + 0x108),*(undefined4 *)(param_1 + 0x10c),DAT_00917588);
  switch(param_2) {
  case 0xd:
    sprintf(local_48,"Width=%2d");
    break;
  case 0xe:
    sprintf(local_48,"Height=%.1f",(double)*(float *)(param_1 + 0xf4));
    break;
  case 0xf:
    sprintf(local_48,"Incr=%.1f",(double)*(float *)(param_1 + 0xf8));
    break;
  case 0x13:
    sprintf(local_48,"Depth=%2d");
    break;
  case 0x14:
    sprintf(local_48,"Bell width=%.2f",(double)*(float *)(param_1 + 0xfc));
  }
  FUN_00689cb0(DAT_0091552c);
  uVar2 = FUN_0083f040();
  *(undefined4 *)(param_1 + 0xdc) = uVar2;
  DAT_00920ef4 = fVar1 + 0.02;
  FUN_0068af70(DAT_00917580,*(int *)(param_1 + 0x100) + 2,*(int *)(param_1 + 0x104) + 2,
               *(int *)(param_1 + 0x108) + -2,
               *(int *)(param_1 + 0x104) + 4 + *(int *)(param_1 + 0xd8),
               *(undefined4 *)(param_1 + 0xe4));
  std::_Init_atomic_counter(DAT_0091552c,*(ulong *)(param_1 + 0xe0));
  DAT_00920ef4 = fVar1 + 0.01;
  FUN_00689d10(DAT_0091552c,DAT_00917580,*(int *)(param_1 + 0x100) + 4,*(int *)(param_1 + 0x104) + 4
               ,local_48);
  iVar3 = *(int *)(param_1 + 0x110) + -6;
  iVar5 = (*(int *)(param_1 + 0x114) + -6) - *(int *)(param_1 + 0xd8);
  iStack_50 = iVar3 / 2 + *(int *)(param_1 + 0x100) + 3;
  iStack_4c = (*(int *)(param_1 + 0x10c) + -3) - iVar5 / 6;
  local_b0 = 0;
  for (local_a4 = -1; local_a4 < 2; local_a4 = local_a4 + 1) {
    for (local_a0 = -1; local_a0 < 2; local_a0 = local_a0 + 1) {
      aiStack_98[local_b0 * 2] =
           (iVar3 * *(int *)(param_1 + 0xec) * local_a0) / 0xbd + iStack_50 +
           (iVar5 * *(int *)(param_1 + 0xf0) * local_a4) / 0x17a;
      aiStack_98[local_b0 * 2 + 1] =
           iStack_4c - (iVar5 * *(int *)(param_1 + 0xf0) * local_a4) / 0x17a;
      local_b0 = local_b0 + 1;
    }
  }
  iStack_4c = iStack_4c -
              (int)(((float)(iVar5 * 2) * *(float *)(param_1 + 0xf4)) / (DAT_00992364 * 3.0));
  DAT_00920ef4 = fVar1 + 0.01;
  FUN_0068af40(DAT_00917580,aiStack_98[2],aiStack_98[3],uStack_60,uStack_5c,DAT_00917588,0);
  FUN_0068af40(DAT_00917580,iStack_80,iStack_7c,iStack_70,uStack_6c,DAT_00917588,0);
  FUN_0068af40(DAT_00917580,aiStack_98[0],aiStack_98[1],aiStack_98[4],uStack_84,DAT_0091755c,0);
  FUN_0068af40(DAT_00917580,aiStack_98[4],uStack_84,uStack_58,uStack_54,DAT_0091755c,0);
  FUN_0068af40(DAT_00917580,uStack_58,uStack_54,uStack_68,uStack_64,DAT_0091755c,0);
  FUN_0068af40(DAT_00917580,uStack_68,uStack_64,aiStack_98[0],aiStack_98[1],DAT_0091755c,0);
  FUN_0068af40(DAT_00917580,uStack_78,iStack_74,iStack_50,iStack_4c,DAT_0091755c,0);
  if ((1 < *(int *)(param_1 + 0xf0)) && (1 < *(int *)(param_1 + 0xec))) {
    if ((*(float *)(param_1 + 0x144) != *(float *)(param_1 + 0xfc)) ||
       ((*(int *)(param_1 + 0x13c) != *(int *)(param_1 + 0xec) ||
        (*(int *)(param_1 + 0x140) != *(int *)(param_1 + 0xf0))))) {
      FUN_004c4370();
    }
    local_c4 = iStack_80;
    local_c0 = iStack_7c;
    for (local_a4 = 0; local_a4 <= *(int *)(param_1 + 0xf0); local_a4 = local_a4 + 1) {
      for (local_a0 = 0; local_a0 <= *(int *)(param_1 + 0xec); local_a0 = local_a0 + 1) {
        iVar3 = ((iStack_70 - iStack_80) * local_a0) / *(int *)(param_1 + 0xec) + iStack_80;
        iVar4 = iStack_74 -
                (int)((*(float *)(param_1 + 0x148 + local_a4 * 0x100 + local_a0 * 4) * 2.0 *
                       (float)iVar5 * *(float *)(param_1 + 0xf4)) / (DAT_00992364 * 3.0));
        FUN_0068af40(DAT_00917580,local_c4,local_c0,iVar3,iVar4);
        local_c4 = iVar3;
        local_c0 = iVar4;
      }
    }
  }
  FUN_004c5b20(DAT_00917580,*(undefined4 *)(param_1 + 0x100),*(undefined4 *)(param_1 + 0x104),
               *(undefined4 *)(param_1 + 0x110),DAT_0091755c);
  FUN_004c5b20(DAT_00917580,*(int *)(param_1 + 0x100) + 1,*(int *)(param_1 + 0x104) + 1,
               *(int *)(param_1 + 0x110) + -2,DAT_00917588);
  FUN_004c5b20(DAT_00917580,*(int *)(param_1 + 0x100) + 2,*(int *)(param_1 + 0x104) + 2,
               *(int *)(param_1 + 0x110) + -4,DAT_0091755c);
  FUN_0068af40(DAT_00917580,*(int *)(param_1 + 0x100) + 2,*(int *)(param_1 + 0x104) + 2,
               *(int *)(param_1 + 0x108) + -2,*(int *)(param_1 + 0x104) + 2,DAT_00917584,0);
  FUN_0068af40(DAT_00917580,*(int *)(param_1 + 0x100) + 2,*(int *)(param_1 + 0x104) + 2,
               *(int *)(param_1 + 0x100) + 2,*(int *)(param_1 + 0x10c) + -2,DAT_00917584,0);
  FUN_0068af40(DAT_00917580,*(undefined4 *)(param_1 + 0x108),*(undefined4 *)(param_1 + 0x10c),
               *(undefined4 *)(param_1 + 0x100),*(undefined4 *)(param_1 + 0x10c),DAT_00917584,0);
  FUN_0068af40(DAT_00917580,*(undefined4 *)(param_1 + 0x108),*(undefined4 *)(param_1 + 0x104),
               *(undefined4 *)(param_1 + 0x108),*(undefined4 *)(param_1 + 0x10c),DAT_00917584,0);
  DAT_00920ef4 = fVar1;
  FUN_0083e885();
  return;
}

