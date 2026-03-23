
void FUN_00444580(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,int param_7,float param_8,float *param_9,
                 undefined4 *param_10)

{
  int iVar1;
  uint local_2c;
  float local_28;
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_28 = param_8;
  local_24 = 1e+30;
  for (local_2c = *(uint *)(param_7 + 0x14);
      local_2c < (uint)(*(int *)(param_7 + 0x10) * 0x18 + *(int *)(param_7 + 0x14));
      local_2c = local_2c + 0x18) {
    iVar1 = FUN_00444690(param_1,param_2,param_3,param_4,param_5,param_6,local_2c,
                         *(undefined4 *)(param_7 + 4),local_28,&local_28,&local_20);
    if ((iVar1 != 0) && (local_28 < local_24)) {
      local_24 = local_28;
      local_14 = local_20;
      local_10 = local_1c;
      local_c = local_18;
    }
  }
  if (local_24 < 1e+30) {
    *param_9 = local_24;
    *param_10 = local_14;
    param_10[1] = local_10;
    param_10[2] = local_c;
  }
  FUN_0083e885();
  return;
}

