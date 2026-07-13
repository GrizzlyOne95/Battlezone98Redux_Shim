
undefined4
FUN_0069b800(undefined4 param_1,int *param_2,undefined4 param_3,undefined4 param_4,int param_5,
            undefined4 param_6,undefined4 param_7,byte *param_8,undefined4 param_9)

{
  bool bVar1;
  undefined1 local_3c [4];
  undefined1 local_38 [4];
  undefined1 local_34 [4];
  int local_30;
  uint local_2c;
  undefined4 local_28;
  int local_24;
  uint local_20;
  int local_1c;
  int local_18;
  int local_14;
  byte *local_10;
  byte *local_c;
  byte local_6;
  byte local_5;
  
  local_28 = 0;
  local_24 = 0;
  local_10 = &DAT_008949c0;
  local_c = param_8;
  do {
    local_5 = *local_c;
    bVar1 = local_5 < *local_10;
    if (local_5 != *local_10) {
LAB_0069b866:
      local_20 = -(uint)bVar1 | 1;
      goto LAB_0069b86e;
    }
    if (local_5 == 0) break;
    local_6 = local_c[1];
    bVar1 = local_6 < local_10[1];
    if (local_6 != local_10[1]) goto LAB_0069b866;
    local_c = local_c + 2;
    local_10 = local_10 + 2;
  } while (local_6 != 0);
  local_20 = 0;
LAB_0069b86e:
  local_2c = local_20;
  if (local_20 == 0) {
    FUN_006978d0(param_4,1,param_5 + -1,param_6,param_7,param_8,param_9,local_3c,&local_30,&local_28
                );
    local_14 = *param_2;
    FUN_0069b690(param_1,&local_14,param_3,param_4,local_34,&local_18);
    local_14 = local_18 + 1;
    local_24 = FUN_0069b750(param_1,&local_14,param_3,param_4,local_38,&local_1c);
    if (local_24 == 0) {
      local_1c = local_18;
    }
    if (local_30 == 0) {
      FUN_0069c150(param_1,local_38,local_1c,param_4);
    }
    else {
      FUN_0069c150(param_1,local_34,local_18,param_4);
    }
    *param_2 = local_1c + 1;
  }
  else {
    local_28 = 0xffffffff;
  }
  return local_28;
}

