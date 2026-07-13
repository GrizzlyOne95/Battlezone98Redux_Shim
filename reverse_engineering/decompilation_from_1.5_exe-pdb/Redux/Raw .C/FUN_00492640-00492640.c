
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00492640(undefined4 param_1,int param_2,undefined4 param_3,undefined1 param_4)

{
  float *pfVar1;
  undefined1 local_2c [12];
  int local_20;
  undefined4 local_1c;
  int *local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1c = param_1;
  if (DAT_02cc2b70 == 0) {
    pfVar1 = (float *)FUN_0062e120(local_2c,param_2);
    _DAT_02cc2b74 = *pfVar1;
    _DAT_02cc2b78 = pfVar1[1];
    _DAT_02cc2b7c = pfVar1[2];
    local_14 = _DAT_02cc2b74;
    local_10 = _DAT_02cc2b78;
    local_c = _DAT_02cc2b7c;
  }
  DAT_02cc2b70 = DAT_02cc2b70 + 1;
  while (param_2 != 0) {
    if (*(int *)(param_2 + 0x80) != 0) {
      FUN_00492640(*(undefined4 *)(param_2 + 0x80),param_3,param_4);
    }
    local_20 = *(int *)(param_2 + 0x7c);
    if (*(int *)(param_2 + 0x78) != 0) {
      local_18 = (int *)FUN_00492aa0(param_2,param_3,param_4);
      if (local_18 != (int *)0x0) {
        local_18[2] = (int)((float)(*(double *)(*local_18 + 0x48) - (double)_DAT_02cc2b74) * 2.0 +
                           (float)local_18[2]);
        local_18[3] = (int)((float)(*(double *)(*local_18 + 0x50) - (double)_DAT_02cc2b78) * 1.0 +
                           (float)local_18[3]);
        local_18[4] = (int)((float)(*(double *)(*local_18 + 0x58) - (double)_DAT_02cc2b7c) * 2.0 +
                           (float)local_18[4]);
      }
    }
    param_2 = local_20;
  }
  DAT_02cc2b70 = DAT_02cc2b70 + -1;
  FUN_0083e885();
  return;
}

