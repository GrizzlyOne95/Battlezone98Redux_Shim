
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004fb690(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined1 local_c0 [12];
  undefined1 local_b4 [16];
  float local_a4;
  float *local_a0;
  byte *local_9c;
  float *local_98;
  float local_94;
  int local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  float local_68;
  float local_64;
  float local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  float local_50;
  float local_4c;
  float local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  float local_38;
  float local_34;
  float local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  float local_20;
  float local_1c;
  float local_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00820180(DAT_02cecf70);
  FUN_006855e0();
  local_a4 = (float)*(byte *)(param_1 + 0x32) * 0.01 * 0.5;
  for (local_90 = 0; local_90 < *(int *)(param_1 + 0x430); local_90 = local_90 + 1) {
    local_9c = (byte *)(param_1 + 0x30 + local_90 * 4);
    local_98 = (float *)((uint)*local_9c * 0xc + DAT_02cecf70);
    local_a0 = (float *)((uint)local_9c[1] * 0xc + DAT_02cecf70);
    puVar1 = (undefined4 *)FUN_00440130(local_c0,*local_98,local_98[1],local_98[2]);
    local_8c = *puVar1;
    local_88 = puVar1[1];
    local_84 = puVar1[2];
    puVar1 = (undefined4 *)FUN_004462d0(local_b4,0x3f000000);
    local_80 = *puVar1;
    local_7c = puVar1[1];
    local_78 = puVar1[2];
    local_94 = (float)local_9c[2] * 0.01 * 0.5;
    local_74 = local_80;
    local_70 = local_7c;
    local_6c = local_78;
    iVar2 = FUN_006895d0();
    if (iVar2 < 1) {
      local_64 = local_98[1];
      local_60 = local_98[2];
      local_68 = *local_98 + local_a4;
      uStack_5c = 0;
      uStack_58 = 0;
      uStack_54 = 0x3f800000;
      local_4c = local_a0[1];
      local_48 = local_a0[2];
      local_50 = *local_a0 + local_94;
      uStack_44 = 0x3f800000;
      uStack_40 = 0;
      uStack_3c = 0x3f800000;
      local_34 = local_a0[1];
      local_30 = local_a0[2];
      local_38 = *local_a0 - local_94;
      uStack_2c = 0;
      uStack_28 = 0x3f800000;
      uStack_24 = 0x3f800000;
      local_1c = local_98[1];
      local_18 = local_98[2];
      local_20 = *local_98 - local_a4;
      uStack_14 = 0;
      uStack_10 = 0x3f800000;
      uStack_c = 0x3f800000;
      FUN_00686830(param_2);
    }
    local_a4 = local_94;
  }
  FUN_006856e0();
  FUN_0083e885();
  return;
}

