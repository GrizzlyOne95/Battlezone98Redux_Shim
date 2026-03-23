
void FUN_004e0040(float *param_1,undefined4 param_2)

{
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_0062e650(param_2,&local_14,&local_20);
  local_14 = (local_14 + local_20) * 0.5;
  local_10 = (local_10 + local_1c) * 0.5;
  local_c = (local_c + local_18) * 0.5;
  *param_1 = local_14;
  param_1[1] = local_10;
  param_1[2] = local_c;
  FUN_0083e885();
  return;
}

