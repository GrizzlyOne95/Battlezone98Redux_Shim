
void FUN_004801a0(float *param_1,float *param_2,undefined4 param_3,undefined4 *param_4)

{
  float *pfVar1;
  undefined1 local_38 [12];
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_20 = *param_2;
  local_1c = param_2[1];
  local_18 = param_2[2];
  pfVar1 = (float *)FUN_00439d00(local_38,*param_2,param_2[1],param_2[2],param_3,*param_4,param_4[1]
                                 ,param_4[2]);
  local_2c = *pfVar1;
  local_28 = pfVar1[1];
  local_24 = pfVar1[2];
  local_14 = local_2c;
  local_10 = local_28;
  local_c = local_24;
  if (local_2c < local_20) {
    FUN_0046b580(&local_20,&local_14);
  }
  if (local_10 < local_1c) {
    FUN_0046b580(&local_1c,&local_10);
  }
  if (local_c < local_18) {
    FUN_0046b580(&local_18,&local_c);
  }
  *param_1 = local_20;
  param_1[1] = local_1c;
  param_1[2] = local_18;
  param_1[3] = local_14;
  param_1[4] = local_10;
  param_1[5] = local_c;
  FUN_0083e885();
  return;
}

