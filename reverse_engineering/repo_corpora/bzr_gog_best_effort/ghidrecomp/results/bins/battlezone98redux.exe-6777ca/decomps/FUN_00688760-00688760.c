
void FUN_00688760(float *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  undefined4 *puVar1;
  int *piVar2;
  float *pfVar3;
  float fVar4;
  float fVar5;
  undefined1 local_cc [16];
  undefined1 local_bc [16];
  undefined1 local_ac [16];
  undefined1 local_9c [16];
  undefined1 local_8c [16];
  undefined1 local_7c [16];
  undefined1 local_6c [16];
  undefined1 local_5c [16];
  double local_4c;
  float local_44;
  float local_40;
  float local_3c;
  int local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar1 = (undefined4 *)FUN_00688340(local_5c,param_1[0xe]);
  local_34 = *puVar1;
  local_30 = puVar1[1];
  local_2c = puVar1[2];
  local_28 = puVar1[3];
  FUN_00689fa0(param_1[0xe],param_2,param_3,param_4,param_5);
  piVar2 = (int *)FUN_00688340(local_7c,param_1[0xe]);
  local_24 = *piVar2;
  local_20 = piVar2[1];
  local_1c = piVar2[2];
  local_18 = piVar2[3];
  fVar4 = param_1[0xe];
  *(undefined4 *)((int)fVar4 + 8) = local_34;
  *(undefined4 *)((int)fVar4 + 0xc) = local_30;
  *(undefined4 *)((int)fVar4 + 0x10) = local_2c;
  *(undefined4 *)((int)fVar4 + 0x14) = local_28;
  param_1[5] = (float)local_24;
  param_1[6] = (float)local_20;
  param_1[7] = (float)local_1c;
  param_1[8] = (float)local_18;
  fVar4 = 0.1 / param_1[2];
  fVar5 = 0.1 / param_1[3];
  param_1[0x40] = (param_1[5] - *param_1) * fVar4;
  param_1[0x41] = (param_1[6] - param_1[1]) * fVar5;
  param_1[0x42] = 0.1;
  param_1[0x43] = (param_1[7] - *param_1) * fVar4;
  param_1[0x44] = (param_1[6] - param_1[1]) * fVar5;
  param_1[0x45] = 0.1;
  param_1[0x46] = (param_1[7] - *param_1) * fVar4;
  param_1[0x47] = (param_1[8] - param_1[1]) * fVar5;
  param_1[0x48] = 0.1;
  param_1[0x49] = (param_1[5] - *param_1) * fVar4;
  param_1[0x4a] = (param_1[8] - param_1[1]) * fVar5;
  param_1[0x4b] = 0.1;
  local_3c = param_1[4];
  if (1e+09 <= local_3c) {
    local_3c = 1e+09;
  }
  local_40 = local_3c / param_1[2];
  local_44 = local_3c / param_1[3];
  param_1[0x4c] = (param_1[5] - *param_1) * local_40;
  param_1[0x4d] = (param_1[6] - param_1[1]) * local_44;
  param_1[0x4e] = local_3c;
  param_1[0x4f] = (param_1[7] - *param_1) * local_40;
  param_1[0x50] = (param_1[6] - param_1[1]) * local_44;
  param_1[0x51] = local_3c;
  param_1[0x52] = (param_1[7] - *param_1) * local_40;
  param_1[0x53] = (param_1[8] - param_1[1]) * local_44;
  param_1[0x54] = local_3c;
  param_1[0x55] = (param_1[5] - *param_1) * local_40;
  param_1[0x56] = (param_1[8] - param_1[1]) * local_44;
  param_1[0x57] = local_3c;
  local_14 = 0.0;
  local_10 = 0.0;
  local_c = 0.0;
  pfVar3 = (float *)FUN_0081fc00(local_bc,&local_14,param_1 + 0x4c,param_1 + 0x55);
  param_1[0x28] = *pfVar3;
  param_1[0x29] = pfVar3[1];
  param_1[0x2a] = pfVar3[2];
  param_1[0x2b] = pfVar3[3];
  pfVar3 = (float *)FUN_0081fc00(local_9c,&local_14,param_1 + 0x4f,param_1 + 0x52);
  param_1[0x2c] = *pfVar3;
  param_1[0x2d] = pfVar3[1];
  param_1[0x2e] = pfVar3[2];
  param_1[0x2f] = pfVar3[3];
  pfVar3 = (float *)FUN_0081fc00(local_6c,&local_14,param_1 + 0x4c,param_1 + 0x4f);
  param_1[0x30] = *pfVar3;
  param_1[0x31] = pfVar3[1];
  param_1[0x32] = pfVar3[2];
  param_1[0x33] = pfVar3[3];
  pfVar3 = (float *)FUN_0081fc00(local_8c,&local_14,param_1 + 0x52,param_1 + 0x55);
  param_1[0x34] = *pfVar3;
  param_1[0x35] = pfVar3[1];
  param_1[0x36] = pfVar3[2];
  param_1[0x37] = pfVar3[3];
  pfVar3 = (float *)FUN_0081fc00(local_ac,param_1 + 0x4c,param_1 + 0x4f,param_1 + 0x52);
  param_1[0x38] = *pfVar3;
  param_1[0x39] = pfVar3[1];
  param_1[0x3a] = pfVar3[2];
  param_1[0x3b] = pfVar3[3];
  pfVar3 = (float *)FUN_0081fc00(local_cc,param_1 + 0x40,param_1 + 0x43,param_1 + 0x46);
  param_1[0x3c] = *pfVar3;
  param_1[0x3d] = pfVar3[1];
  param_1[0x3e] = pfVar3[2];
  param_1[0x3f] = pfVar3[3];
  for (local_38 = 0; local_38 < 4; local_38 = local_38 + 1) {
    local_14 = local_14 + param_1[(local_38 + 4) * 3 + 0x40];
    local_10 = local_10 + param_1[(local_38 + 4) * 3 + 0x41];
    local_c = local_c + param_1[(local_38 + 4) * 3 + 0x42];
  }
  local_14 = local_14 * 0.2;
  local_10 = local_10 * 0.2;
  local_c = local_c * 0.2;
  for (local_38 = 0; local_38 < 6; local_38 = local_38 + 1) {
    local_4c = (double)(param_1[local_38 * 4 + 0x28] * local_14 +
                        param_1[local_38 * 4 + 0x29] * local_10 +
                        param_1[local_38 * 4 + 0x2a] * local_c + param_1[local_38 * 4 + 0x2b]);
    if (local_4c < 0.0) {
      param_1[local_38 * 4 + 0x28] = -param_1[local_38 * 4 + 0x28];
      param_1[local_38 * 4 + 0x29] = -param_1[local_38 * 4 + 0x29];
      param_1[local_38 * 4 + 0x2a] = -param_1[local_38 * 4 + 0x2a];
      param_1[local_38 * 4 + 0x2b] = -param_1[local_38 * 4 + 0x2b];
    }
  }
  FUN_0083e885();
  return;
}

