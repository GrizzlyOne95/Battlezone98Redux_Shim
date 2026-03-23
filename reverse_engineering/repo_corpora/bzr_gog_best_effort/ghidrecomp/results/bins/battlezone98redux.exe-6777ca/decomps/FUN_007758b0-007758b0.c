
void FUN_007758b0(undefined4 *param_1,int param_2)

{
  undefined4 *puVar1;
  float fVar2;
  int local_30c;
  undefined4 local_308 [192];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  param_1[6] = ((float)*(double *)(param_2 + 0x168) + 50.0) - (float)(int)param_1[9] * 0.01;
  DAT_02ceefc8 = (double)(float)param_1[5];
  DAT_02ceefd0 = (double)(float)param_1[6];
  DAT_02ceefd8 = (double)(float)param_1[7];
  fVar2 = (float)(int)param_1[9] * 0.01 * 0.5;
  param_1[0xd] = -fVar2 + (float)param_1[5];
  param_1[0xe] = (float)param_1[6] + 0.0;
  param_1[0xf] = -fVar2 + (float)param_1[7];
  param_1[0x10] = fVar2 + (float)param_1[5];
  param_1[0x11] = (float)param_1[6] + 0.0;
  param_1[0x12] = -fVar2 + (float)param_1[7];
  param_1[0x13] = fVar2 + (float)param_1[5];
  param_1[0x14] = (float)param_1[6] + 0.0;
  param_1[0x15] = fVar2 + (float)param_1[7];
  param_1[0x16] = -fVar2 + (float)param_1[5];
  param_1[0x17] = (float)param_1[6] + 0.0;
  param_1[0x18] = fVar2 + (float)param_1[7];
  FUN_00820180(param_1 + 0xd,param_1 + 0xd,4,param_2 + 0x40);
  for (local_30c = 0; local_30c < 4; local_30c = local_30c + 1) {
    local_308[local_30c * 6 + 3] = *(undefined4 *)(&DAT_008f0510 + local_30c * 8);
    local_308[local_30c * 6 + 4] = *(undefined4 *)(&DAT_008f0514 + local_30c * 8);
    local_308[local_30c * 6 + 5] = 0x3f800000;
    puVar1 = param_1 + local_30c * 3 + 0xd;
    local_308[local_30c * 6] = *puVar1;
    local_308[local_30c * 6 + 1] = puVar1[1];
    local_308[local_30c * 6 + 2] = puVar1[2];
  }
  FUN_006855a0(*param_1,0x4e6e6b28);
  FUN_00685a40(param_2,local_308,4);
  FUN_006856e0();
  FUN_0083e885();
  return;
}

