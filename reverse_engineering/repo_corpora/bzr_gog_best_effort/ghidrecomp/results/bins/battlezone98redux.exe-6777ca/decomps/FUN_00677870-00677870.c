
void FUN_00677870(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar1 = (undefined4 *)FUN_00417780(param_1);
  local_18 = *puVar1;
  local_14 = puVar1[1];
  local_10 = puVar1[2];
  local_c = puVar1[3];
  puVar1 = (undefined4 *)FUN_00417780(param_2);
  *param_1 = *puVar1;
  param_1[1] = puVar1[1];
  param_1[2] = puVar1[2];
  param_1[3] = puVar1[3];
  puVar1 = (undefined4 *)FUN_00417780(&local_18);
  *param_2 = *puVar1;
  param_2[1] = puVar1[1];
  param_2[2] = puVar1[2];
  param_2[3] = puVar1[3];
  FUN_0083e885();
  return;
}

