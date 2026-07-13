
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00615c30(float *param_1,float *param_2,uint param_3,uint param_4)

{
  float fVar1;
  float *pfVar2;
  float10 fVar3;
  undefined1 local_64 [16];
  undefined1 local_54 [16];
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
  local_44 = (float)CONCAT22(local_44._2_2_,0xff);
  local_40 = (float)CONCAT22(local_40._2_2_,0xffff);
  local_28 = (param_2[7] - param_2[5]) * 0.7;
  local_3c = (param_2[7] + param_2[5]) * 0.5;
  local_38 = (param_2[8] + param_2[6]) * 0.5;
  local_18 = 0.0;
  local_14 = 1.0;
  local_10 = 0.0;
  local_c = (float)(param_3 ^ 0x80000000);
  pfVar2 = (float *)FUN_008202b0(local_54,&local_18,param_2 + 0x10);
  local_18 = *pfVar2;
  local_14 = pfVar2[1];
  local_10 = pfVar2[2];
  local_c = pfVar2[3];
  local_20 = local_18 / param_2[2];
  local_24 = local_14 / param_2[3];
  local_2c = local_c / param_2[0x4e] +
             ((local_10 - (local_18 * *param_2) / param_2[2]) - (local_14 * param_2[1]) / param_2[3]
             );
  local_1c = local_20 * local_20 + local_24 * local_24;
  if (1e-09 <= local_1c) {
    fVar3 = (float10)FUN_00820570((double)local_1c);
    fVar1 = (float)fVar3;
    local_20 = local_20 * fVar1;
    local_24 = local_24 * fVar1;
    local_2c = local_2c * fVar1;
    local_1c = local_20 * local_3c + local_2c + local_24 * local_38;
    local_34 = local_3c - local_20 * local_1c;
    local_30 = local_38 - local_24 * local_1c;
    *param_1 = local_34 - local_24 * local_28;
    param_1[1] = local_20 * local_28 + local_30;
    param_1[2] = 1.0 / _DAT_008ead08;
    param_1[3] = 0.0;
    param_1[4] = 0.0;
    param_1[5] = local_44;
    param_1[6] = local_24 * local_28 + local_34;
    param_1[7] = local_30 - local_20 * local_28;
    param_1[8] = 1.0 / _DAT_008ead08;
    param_1[9] = 0.0;
    param_1[10] = 0.0;
    param_1[0xb] = local_44;
    local_18 = 0.0;
    local_14 = 1.0;
    local_10 = 0.0;
    local_c = (float)(param_4 ^ 0x80000000);
    pfVar2 = (float *)FUN_008202b0(local_64,&local_18,param_2 + 0x10);
    local_18 = *pfVar2;
    local_14 = pfVar2[1];
    local_10 = pfVar2[2];
    local_c = pfVar2[3];
    local_20 = local_18 / param_2[2];
    local_24 = local_14 / param_2[3];
    local_2c = local_c / param_2[0x4e] +
               ((local_10 - (local_18 * *param_2) / param_2[2]) -
               (local_14 * param_2[1]) / param_2[3]);
    local_1c = local_20 * local_20 + local_24 * local_24;
    if (1e-09 <= local_1c) {
      fVar3 = (float10)FUN_00820570((double)local_1c);
      fVar1 = (float)fVar3;
      local_20 = local_20 * fVar1;
      local_24 = local_24 * fVar1;
      local_2c = local_2c * fVar1;
      local_1c = local_20 * local_3c + local_2c + local_24 * local_38;
      local_34 = local_3c - local_20 * local_1c;
      local_30 = local_38 - local_24 * local_1c;
      param_1[0xc] = local_24 * local_28 + local_34;
      param_1[0xd] = local_30 - local_20 * local_28;
      param_1[0xe] = 1.0 / _DAT_008ead08;
      param_1[0xf] = 0.0;
      param_1[0x10] = 0.0;
      param_1[0x11] = local_40;
      param_1[0x12] = local_34 - local_24 * local_28;
      param_1[0x13] = local_20 * local_28 + local_30;
      param_1[0x14] = 1.0 / _DAT_008ead08;
      param_1[0x15] = 0.0;
      param_1[0x16] = 0.0;
      param_1[0x17] = local_40;
    }
  }
  FUN_0083e885();
  return;
}

