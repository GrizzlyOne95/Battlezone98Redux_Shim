
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00492460(undefined4 param_1,int param_2,undefined4 param_3,undefined1 param_4)

{
  float *pfVar1;
  int iVar2;
  undefined1 local_34 [12];
  int local_28;
  int local_24;
  int local_20;
  undefined4 local_1c;
  int *local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1c = param_1;
  if (DAT_02cc2b6c == 0) {
    pfVar1 = (float *)FUN_0062e120(local_34,param_2);
    _DAT_02cc2b80 = *pfVar1;
    _DAT_02cc2b84 = pfVar1[1];
    _DAT_02cc2b88 = pfVar1[2];
    local_14 = _DAT_02cc2b80;
    local_10 = _DAT_02cc2b84;
    local_c = _DAT_02cc2b88;
  }
  DAT_02cc2b6c = DAT_02cc2b6c + 1;
  do {
    if (param_2 == 0) {
      DAT_02cc2b6c = DAT_02cc2b6c + -1;
      FUN_0083e885();
      return;
    }
    if (*(int *)(param_2 + 0x80) != 0) {
      FUN_00492460(*(undefined4 *)(param_2 + 0x80),param_3,param_4);
    }
    local_28 = *(int *)(param_2 + 0x7c);
    local_24 = FUN_00618b60(param_2);
    if (local_24 != 0) {
      if (*(int *)(param_2 + 0x84) == 0x3c) {
        local_20 = FUN_00618b60(local_24);
        if (local_20 != 0) {
          iVar2 = FUN_00618b60(local_20);
          if (iVar2 != 0) goto LAB_00492550;
        }
      }
      else {
LAB_00492550:
        local_18 = (int *)FUN_00492aa0(param_2,param_3,param_4);
        if (local_18 != (int *)0x0) {
          local_18[2] = (int)((float)(*(double *)(*local_18 + 0x48) - (double)_DAT_02cc2b80) * 2.0 +
                             (float)local_18[2]);
          local_18[3] = (int)((float)(*(double *)(*local_18 + 0x50) - (double)_DAT_02cc2b84) * 1.0 +
                             (float)local_18[3]);
          local_18[4] = (int)((float)(*(double *)(*local_18 + 0x58) - (double)_DAT_02cc2b88) * 2.0 +
                             (float)local_18[4]);
        }
      }
    }
    param_2 = local_28;
  } while( true );
}

