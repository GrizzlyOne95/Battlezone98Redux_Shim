
void __thiscall FUN_005a9a50(int param_1,int *param_2,int param_3)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  undefined1 local_ec [24];
  undefined1 local_d4 [12];
  undefined1 local_c8 [12];
  uint local_bc;
  uint local_b8;
  int local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  int local_68;
  int local_64;
  int local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50 [2];
  int local_48 [2];
  float local_40;
  float local_3c;
  undefined4 local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  float local_20;
  undefined4 local_1c;
  float local_18;
  float local_14;
  undefined4 local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (*param_2 == 0) {
    param_2[0x14] = param_3;
  }
  local_5c = (*(float *)(*(int *)(param_1 + 0xf4) + 0xb0) +
             *(float *)(*(int *)(param_1 + 0xf4) + 0xbc)) * 0.5;
  local_58 = (*(float *)(*(int *)(param_1 + 0xf4) + 0xb4) +
             *(float *)(*(int *)(param_1 + 0xf4) + 0xc0)) * 0.5;
  local_54 = (*(float *)(*(int *)(param_1 + 0xf4) + 0xb8) +
             *(float *)(*(int *)(param_1 + 0xf4) + 0xc4)) * 0.5;
  local_48[0] = *(int *)(*(int *)(param_1 + 0xf4) + 0xc4);
  local_48[1] = *(undefined4 *)(*(int *)(param_1 + 0xf4) + 0xb0);
  local_38 = *(undefined4 *)(*(int *)(param_1 + 0xf4) + 0xbc);
  local_24 = *(undefined4 *)(*(int *)(param_1 + 0xf4) + 0xb8);
  local_1c = *(undefined4 *)(*(int *)(param_1 + 0xf4) + 0xb4);
  local_10 = *(undefined4 *)(*(int *)(param_1 + 0xf4) + 0xc0);
  local_b4 = param_1;
  local_50[0] = local_5c;
  local_50[1] = local_58;
  local_40 = local_58;
  local_3c = local_54;
  local_34 = local_58;
  local_30 = local_54;
  local_2c = local_5c;
  local_28 = local_58;
  local_20 = local_5c;
  local_18 = local_54;
  local_14 = local_5c;
  local_c = local_54;
  for (local_b8 = 0; local_b8 < 6; local_b8 = local_b8 + 1) {
    puVar1 = (undefined4 *)
             FUN_0081fd40(local_ec,local_50 + local_b8 * 3,*(int *)(local_b4 + 0xf4) + 0x20);
    local_98 = *puVar1;
    local_94 = puVar1[1];
    local_90 = puVar1[2];
    local_8c = puVar1[3];
    local_88 = puVar1[4];
    local_84 = puVar1[5];
    local_80 = local_98;
    local_7c = local_94;
    local_78 = local_90;
    local_74 = local_8c;
    local_70 = local_88;
    local_6c = local_84;
    puVar1 = (undefined4 *)
             FUN_00444ba0(local_c8,local_50[local_b8 * 3],local_50[local_b8 * 3 + 1],
                          local_48[local_b8 * 3],*(undefined4 *)(local_b4 + 0xf4));
    local_b0 = *puVar1;
    local_ac = puVar1[1];
    local_a8 = puVar1[2];
    local_a4 = local_b0;
    local_a0 = local_ac;
    local_9c = local_a8;
    iVar2 = FUN_00784620(local_80,local_7c,local_78,local_74,local_70,local_6c,local_b0,local_ac,
                         local_a8,param_2 + 0x14,param_2 + 0x1b);
    if (iVar2 != 0) {
      *param_2 = 1;
      param_2[1] = 0;
      FUN_00444970(param_2 + 2);
      piVar3 = (int *)FUN_004a7520(local_d4,local_b0,local_ac,local_a8);
      local_68 = *piVar3;
      local_64 = piVar3[1];
      local_60 = piVar3[2];
      param_2[0x18] = local_68;
      param_2[0x19] = local_64;
      param_2[0x1a] = local_60;
      param_2[0x15] = (int)local_50[local_b8 * 3];
      param_2[0x16] = (int)local_50[local_b8 * 3 + 1];
      param_2[0x17] = local_48[local_b8 * 3];
    }
  }
  local_bc = (uint)(0 < *param_2);
  FUN_0083e885();
  return;
}

