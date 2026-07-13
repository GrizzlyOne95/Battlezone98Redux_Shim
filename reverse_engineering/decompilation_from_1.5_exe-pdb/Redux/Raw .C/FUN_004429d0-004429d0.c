
void FUN_004429d0(int param_1)

{
  float *pfVar1;
  undefined1 local_28 [16];
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  pfVar1 = (float *)FUN_0062c8f0(local_28,param_1);
  local_18 = *pfVar1;
  local_14 = pfVar1[1];
  local_10 = pfVar1[2];
  local_c = pfVar1[3];
  *(float *)(param_1 + 0x44) = local_18 - local_c;
  *(float *)(param_1 + 0x48) = local_14 - local_c;
  *(float *)(param_1 + 0x4c) = local_10 - local_c;
  *(float *)(param_1 + 0x50) = local_18 + local_c;
  *(float *)(param_1 + 0x54) = local_14 + local_c;
  *(float *)(param_1 + 0x58) = local_10 + local_c;
  FUN_0083e885();
  return;
}

