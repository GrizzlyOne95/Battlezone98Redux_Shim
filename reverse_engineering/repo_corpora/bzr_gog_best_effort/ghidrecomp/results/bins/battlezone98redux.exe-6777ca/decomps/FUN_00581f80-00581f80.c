
void FUN_00581f80(float *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,float param_8)

{
  float *pfVar1;
  float10 fVar2;
  undefined1 local_6c [12];
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
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
  pfVar1 = (float *)FUN_004401a0(local_6c,param_5,param_6,param_7,param_2,param_3,param_4);
  local_20 = *pfVar1;
  local_1c = pfVar1[1];
  local_18 = pfVar1[2];
  local_5c = param_8 * param_8;
  local_54 = local_20 * local_20;
  local_48 = local_1c * local_1c;
  local_4c = local_18 * local_18;
  local_38 = local_54 + local_4c;
  local_3c = local_48 / local_38 + 1.0;
  local_34 = local_5c - local_1c * 9.8;
  local_50 = local_38 * 24.01;
  local_14 = local_20;
  local_10 = local_1c;
  local_c = local_18;
  fVar2 = (float10)FUN_0044fb20(0,local_34 * local_34 - local_3c * 4.0 * local_50);
  local_40 = (float)fVar2;
  if (local_40 <= 0.0) {
    local_44 = local_34;
  }
  else {
    fVar2 = (float10)FUN_00417910(local_40);
    local_60 = (float)fVar2;
    local_44 = local_34 - local_60;
  }
  local_58 = local_44 / (local_3c + local_3c);
  fVar2 = (float10)FUN_00417910(local_58 / local_38);
  local_30 = (float)fVar2;
  local_2c = local_14 * local_30;
  local_28 = local_10 * local_30 + 4.9 / local_30;
  local_24 = local_c * local_30;
  *param_1 = local_2c;
  param_1[1] = local_28;
  param_1[2] = local_24;
  FUN_0083e885();
  return;
}

