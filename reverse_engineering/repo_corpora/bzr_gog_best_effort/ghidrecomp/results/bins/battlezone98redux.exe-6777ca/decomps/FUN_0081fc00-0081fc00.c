
void FUN_0081fc00(undefined4 *param_1,float *param_2,float *param_3,float *param_4)

{
  undefined4 *puVar1;
  float10 fVar2;
  undefined1 local_58 [12];
  undefined1 local_4c [12];
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_30 = *param_3 - *param_2;
  local_2c = param_3[1] - param_2[1];
  local_28 = param_3[2] - param_2[2];
  local_3c = *param_4 - *param_2;
  local_38 = param_4[1] - param_2[1];
  local_34 = param_4[2] - param_2[2];
  puVar1 = (undefined4 *)FUN_004440d0(local_4c,&local_30,&local_3c);
  local_14 = *puVar1;
  local_10 = puVar1[1];
  local_c = puVar1[2];
  puVar1 = (undefined4 *)FUN_004621a0(local_58,&local_14);
  local_24 = *puVar1;
  local_20 = puVar1[1];
  local_1c = puVar1[2];
  local_14 = local_24;
  local_10 = local_20;
  local_c = local_1c;
  fVar2 = (float10)FUN_004428b0(&local_14,param_2);
  local_40 = (float)fVar2;
  local_18 = -local_40;
  *param_1 = local_24;
  param_1[1] = local_20;
  param_1[2] = local_1c;
  param_1[3] = local_18;
  FUN_0083e885();
  return;
}

