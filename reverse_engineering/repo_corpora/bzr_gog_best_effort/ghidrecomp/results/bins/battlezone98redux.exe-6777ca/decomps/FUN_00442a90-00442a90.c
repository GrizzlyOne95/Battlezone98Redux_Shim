
void FUN_00442a90(undefined4 *param_1)

{
  float *pfVar1;
  float10 fVar2;
  undefined1 local_40 [16];
  undefined1 local_30 [4];
  float local_2c;
  undefined4 local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  fVar2 = (float10)FUN_00822d60();
  local_2c = (float)fVar2;
  pfVar1 = (float *)FUN_0062c8f0(local_40,param_1);
  local_18 = *pfVar1;
  local_14 = pfVar1[1];
  local_10 = pfVar1[2];
  local_c = pfVar1[3];
  FUN_0062bec0(*param_1,&local_24,local_30);
  param_1[0x11] = local_18;
  param_1[0x12] = local_14;
  param_1[0x13] = local_10;
  param_1[0x14] = local_2c * local_24 + local_18;
  param_1[0x15] = local_2c * local_20 + local_14;
  param_1[0x16] = local_2c * local_1c + local_10;
  if ((float)param_1[0x14] <= (float)param_1[0x11] && (float)param_1[0x11] != (float)param_1[0x14])
  {
    local_28 = param_1[0x11];
    param_1[0x11] = param_1[0x14];
    param_1[0x14] = local_28;
  }
  if ((float)param_1[0x15] <= (float)param_1[0x12] && (float)param_1[0x12] != (float)param_1[0x15])
  {
    local_28 = param_1[0x12];
    param_1[0x12] = param_1[0x15];
    param_1[0x15] = local_28;
  }
  if ((float)param_1[0x16] <= (float)param_1[0x13] && (float)param_1[0x13] != (float)param_1[0x16])
  {
    local_28 = param_1[0x13];
    param_1[0x13] = param_1[0x16];
    param_1[0x16] = local_28;
  }
  param_1[0x11] = (float)param_1[0x11] - (float)param_1[5];
  param_1[0x12] = (float)param_1[0x12] - (float)param_1[5];
  param_1[0x13] = (float)param_1[0x13] - (float)param_1[5];
  param_1[0x14] = (float)param_1[0x14] + (float)param_1[5];
  param_1[0x15] = (float)param_1[0x15] + (float)param_1[5];
  param_1[0x16] = (float)param_1[0x16] + (float)param_1[5];
  FUN_0083e885();
  return;
}

