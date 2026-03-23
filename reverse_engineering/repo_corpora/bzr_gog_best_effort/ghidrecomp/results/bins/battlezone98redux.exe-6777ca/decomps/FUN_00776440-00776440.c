
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00776440(int param_1)

{
  float fVar1;
  float10 fVar2;
  float local_34;
  int local_30;
  int local_2c;
  float *local_28;
  float *local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_24 = (float *)&DAT_02c03f18;
  if (DAT_02c0667c != 0) {
    fVar2 = (float10)_CIfmod();
    local_14 = (float)(*(double *)(param_1 + 0x160) - (double)fVar2);
    local_10 = (float)*(double *)(param_1 + 0x168);
    fVar2 = (float10)_CIfmod();
    local_c = (float)(*(double *)(param_1 + 0x170) - (double)fVar2);
    if (DAT_02c06680 != 0) {
      local_10 = 0.0;
    }
    local_34 = 0.0;
    for (local_30 = DAT_02c0667c; 0 < local_30; local_30 = local_30 + -1) {
      fVar1 = *(float *)(&DAT_02c06688 + (int)local_24[3] * 4);
      FUN_006855a0(&DAT_02c066c8 + (int)local_24[3] * 0x10,0x4e6e6b28);
      local_28 = (float *)&DAT_008f04a0;
      for (local_2c = 9; 0 < local_2c; local_2c = local_2c + -1) {
        local_20 = local_14 + *local_24 + *local_28 * _DAT_02c06684;
        local_1c = (local_10 + local_24[1]) - local_34;
        local_18 = local_c + local_24[2] + local_28[2] * _DAT_02c06684;
        FUN_007761d0(param_1,&local_20,fVar1 * 0.5,local_24[4]);
        local_28 = local_28 + 3;
      }
      local_34 = local_34 - 1.0;
      FUN_006856e0();
      local_24 = local_24 + 5;
    }
  }
  FUN_0083e885();
  return;
}

