
void FUN_0044b810(undefined4 param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  undefined1 local_58 [24];
  undefined1 local_40 [16];
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
  puVar1 = (undefined4 *)FUN_0081f1e0(local_40,param_1);
  local_30 = *puVar1;
  local_2c = puVar1[1];
  local_28 = puVar1[2];
  local_24 = puVar1[3];
  *param_2 = local_30;
  param_2[1] = local_2c;
  param_2[2] = local_28;
  param_2[3] = local_24;
  puVar1 = (undefined4 *)FUN_00447f60(local_58,param_1);
  local_20 = *puVar1;
  local_1c = puVar1[1];
  local_18 = puVar1[2];
  local_14 = puVar1[3];
  local_10 = puVar1[4];
  local_c = puVar1[5];
  *param_3 = local_20;
  param_3[1] = local_1c;
  param_3[2] = local_18;
  param_3[3] = local_14;
  param_3[4] = local_10;
  param_3[5] = local_c;
  FUN_0083e885();
  return;
}

