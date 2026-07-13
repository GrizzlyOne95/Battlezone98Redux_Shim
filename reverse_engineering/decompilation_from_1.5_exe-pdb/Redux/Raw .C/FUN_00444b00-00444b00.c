
void FUN_00444b00(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined1 local_44 [16];
  undefined1 local_34 [4];
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
  FUN_0062bec0(*param_2,&local_24,local_34);
  puVar1 = (undefined4 *)FUN_0062c8f0(local_44,param_2);
  local_30 = *puVar1;
  local_2c = puVar1[1];
  local_28 = puVar1[2];
  local_c = puVar1[3];
  *param_1 = local_30;
  param_1[1] = local_2c;
  param_1[2] = local_28;
  param_1[3] = local_24;
  param_1[4] = local_20;
  param_1[5] = local_1c;
  local_18 = local_30;
  local_14 = local_2c;
  local_10 = local_28;
  FUN_0083e885();
  return;
}

