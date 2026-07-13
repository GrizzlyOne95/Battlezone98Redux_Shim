
void FUN_005d1cd0(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined1 local_3c [12];
  undefined4 local_30;
  float local_2c;
  undefined4 local_28;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_004c9ab0(param_1,param_2);
  puVar1 = (undefined4 *)FUN_00439de0(local_3c,param_1);
  local_20 = *puVar1;
  local_1c = puVar1[1];
  local_18 = puVar1[2];
  local_28 = *(undefined4 *)(*(int *)(local_24 + 8) + 0x3c);
  local_30 = *(undefined4 *)(*(int *)(local_24 + 8) + 0x50);
  local_2c = ((float)*(int *)(*(int *)(local_24 + 8) + 0x34) * 0.5) /
             *(float *)(*(int *)(local_24 + 8) + 0x38);
  local_14 = local_20;
  local_10 = local_1c;
  local_c = local_18;
  FUN_005d1e00(&local_20,local_28,local_30,local_2c);
  FUN_0083e885();
  return;
}

