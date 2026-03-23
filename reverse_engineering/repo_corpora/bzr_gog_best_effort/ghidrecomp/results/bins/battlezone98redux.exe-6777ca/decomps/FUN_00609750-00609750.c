
void FUN_00609750(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined1 local_b0 [24];
  undefined1 local_98 [12];
  undefined1 local_8c [12];
  undefined1 local_80 [16];
  int local_70;
  uint local_6c;
  undefined4 local_68;
  int local_64;
  int local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_68 = FUN_00417ca0();
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_64 = 0;
  local_6c = FUN_00417f90();
  for (local_60 = 0; local_60 < 5; local_60 = local_60 + 1) {
    if ((1 << ((byte)local_60 & 0x1f) & local_6c) != 0) {
      local_70 = FUN_00417f60(local_60);
      puVar1 = (undefined4 *)FUN_00439de0(local_8c,local_70 + 0x28);
      local_5c = *puVar1;
      local_58 = puVar1[1];
      local_54 = puVar1[2];
      local_14 = local_5c;
      local_10 = local_58;
      local_c = local_54;
      puVar1 = (undefined4 *)
               FUN_00440130(local_80,local_50,local_4c,local_48,local_5c,local_58,local_54);
      local_50 = *puVar1;
      local_4c = puVar1[1];
      local_48 = puVar1[2];
      local_64 = local_64 + 1;
      local_44 = local_50;
      local_40 = local_4c;
      local_3c = local_48;
    }
  }
  if (1 < local_64) {
    puVar1 = (undefined4 *)FUN_004462d0(local_98,1.0 / (float)local_64,local_50,local_4c,local_48);
    local_50 = *puVar1;
    local_4c = puVar1[1];
    local_48 = puVar1[2];
    local_38 = local_50;
    local_34 = local_4c;
    local_30 = local_48;
  }
  puVar1 = (undefined4 *)FUN_0049c4f0(local_b0,local_50,local_4c,local_48);
  local_2c = *puVar1;
  local_28 = puVar1[1];
  local_24 = puVar1[2];
  local_20 = puVar1[3];
  local_1c = puVar1[4];
  local_18 = puVar1[5];
  *param_1 = local_2c;
  param_1[1] = local_28;
  param_1[2] = local_24;
  param_1[3] = local_20;
  param_1[4] = local_1c;
  param_1[5] = local_18;
  FUN_0083e885();
  return;
}

