
void FUN_004620b0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  float *pfVar1;
  undefined1 local_30 [12];
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  pfVar1 = (float *)FUN_004401a0(local_30,param_1,param_2,param_3,param_4,param_5,param_6);
  local_20 = *pfVar1;
  local_1c = pfVar1[1];
  local_18 = pfVar1[2];
  local_24 = local_20 * local_20 + local_1c * local_1c + local_18 * local_18;
  local_14 = local_20;
  local_10 = local_1c;
  local_c = local_18;
  FUN_0083e885();
  return;
}

