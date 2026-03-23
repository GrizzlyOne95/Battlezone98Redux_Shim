
undefined4
FUN_0069a790(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,int param_5,
            undefined4 param_6,undefined4 param_7)

{
  bool bVar1;
  float10 fVar2;
  undefined1 local_24 [4];
  uint local_20;
  undefined4 local_1c;
  uint local_18;
  int local_14;
  byte *local_10;
  byte *local_c;
  byte local_6;
  byte local_5;
  
  local_1c = 0;
  local_10 = &DAT_00871540;
  local_c = (byte *)(param_5 + 0x50);
  do {
    local_5 = *local_c;
    bVar1 = local_5 < *local_10;
    if (local_5 != *local_10) {
LAB_0069a7ef:
      local_18 = -(uint)bVar1 | 1;
      goto LAB_0069a7f7;
    }
    if (local_5 == 0) break;
    local_6 = local_c[1];
    bVar1 = local_6 < local_10[1];
    if (local_6 != local_10[1]) goto LAB_0069a7ef;
    local_c = local_c + 2;
    local_10 = local_10 + 2;
  } while (local_6 != 0);
  local_18 = 0;
LAB_0069a7f7:
  local_20 = local_18;
  if (local_18 == 0) {
    local_14 = FUN_006994c0(param_7,param_5);
    fVar2 = (float10)FUN_006978d0(param_1,2,param_2 + -1,param_3,param_4,param_5,param_6,local_24,
                                  local_14 + 0xc,&local_1c);
    *(double *)(local_14 + 0x10) = (double)fVar2;
  }
  else {
    if (param_2 != 1) {
      return 0xffffffff;
    }
    local_14 = FUN_006994c0(param_7,param_5);
  }
  FUN_00699650(param_1,local_14);
  return local_1c;
}

