
int FUN_0069aeb0(undefined4 param_1,int *param_2,undefined4 param_3,int param_4,int param_5)

{
  byte bVar1;
  bool bVar2;
  uint local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  uint local_3c;
  byte *local_38;
  byte *local_34;
  byte *local_30;
  byte *local_2c;
  byte *local_28;
  byte *local_24;
  byte *local_20;
  byte *local_1c;
  byte *local_18;
  byte *local_14;
  
  local_18 = &DAT_008948e0;
  local_14 = (byte *)(*param_2 * 0x50 + param_5);
  do {
    bVar1 = *local_14;
    bVar2 = bVar1 < *local_18;
    if (bVar1 != *local_18) {
LAB_0069af06:
      local_3c = -(uint)bVar2 | 1;
      goto LAB_0069af0e;
    }
    if (bVar1 == 0) break;
    bVar1 = local_14[1];
    bVar2 = bVar1 < local_18[1];
    if (bVar1 != local_18[1]) goto LAB_0069af06;
    local_14 = local_14 + 2;
    local_18 = local_18 + 2;
  } while (bVar1 != 0);
  local_3c = 0;
LAB_0069af0e:
  if (local_3c == 0) {
    local_20 = (byte *)&DAT_00871534;
    local_1c = (byte *)((*param_2 + 2) * 0x50 + param_5);
    do {
      bVar1 = *local_1c;
      bVar2 = bVar1 < *local_20;
      if (bVar1 != *local_20) {
LAB_0069af73:
        local_40 = -(uint)bVar2 | 1;
        goto LAB_0069af7b;
      }
      if (bVar1 == 0) break;
      bVar1 = local_1c[1];
      bVar2 = bVar1 < local_20[1];
      if (bVar1 != local_20[1]) goto LAB_0069af73;
      local_1c = local_1c + 2;
      local_20 = local_20 + 2;
    } while (bVar1 != 0);
    local_40 = 0;
LAB_0069af7b:
    if (local_40 == 0) {
      FUN_0069adb0(param_1,param_2,param_3,param_5,10,*(undefined4 *)(param_4 + 0xc + *param_2 * 4))
      ;
    }
    else {
      FUN_0069adb0(param_1,param_2,param_3,param_5,4,1);
    }
  }
  else {
    local_28 = &DAT_008948e8;
    local_24 = (byte *)(*param_2 * 0x50 + param_5);
    do {
      bVar1 = *local_24;
      bVar2 = bVar1 < *local_28;
      if (bVar1 != *local_28) {
LAB_0069b021:
        local_44 = -(uint)bVar2 | 1;
        goto LAB_0069b029;
      }
      if (bVar1 == 0) break;
      bVar1 = local_24[1];
      bVar2 = bVar1 < local_28[1];
      if (bVar1 != local_28[1]) goto LAB_0069b021;
      local_24 = local_24 + 2;
      local_28 = local_28 + 2;
    } while (bVar1 != 0);
    local_44 = 0;
LAB_0069b029:
    if (local_44 == 0) {
      FUN_0069adb0(param_1,param_2,param_3,param_5,1,4);
    }
    else {
      local_30 = (byte *)0x89485c;
      local_2c = (byte *)(*param_2 * 0x50 + param_5);
      do {
        bVar1 = *local_2c;
        bVar2 = bVar1 < *local_30;
        if (bVar1 != *local_30) {
LAB_0069b0a6:
          local_48 = -(uint)bVar2 | 1;
          goto LAB_0069b0ae;
        }
        if (bVar1 == 0) break;
        bVar1 = local_2c[1];
        bVar2 = bVar1 < local_30[1];
        if (bVar1 != local_30[1]) goto LAB_0069b0a6;
        local_2c = local_2c + 2;
        local_30 = local_30 + 2;
      } while (bVar1 != 0);
      local_48 = 0;
LAB_0069b0ae:
      if (local_48 == 0) {
        FUN_0069adb0(param_1,param_2,param_3,param_5,2,4);
      }
      else {
        local_38 = (byte *)0x894894;
        local_34 = (byte *)(*param_2 * 0x50 + param_5);
        do {
          bVar1 = *local_34;
          bVar2 = bVar1 < *local_38;
          if (bVar1 != *local_38) {
LAB_0069b12b:
            local_4c = -(uint)bVar2 | 1;
            goto LAB_0069b133;
          }
          if (bVar1 == 0) break;
          bVar1 = local_34[1];
          bVar2 = bVar1 < local_38[1];
          if (bVar1 != local_38[1]) goto LAB_0069b12b;
          local_34 = local_34 + 2;
          local_38 = local_38 + 2;
        } while (bVar1 != 0);
        local_4c = 0;
LAB_0069b133:
        if (local_4c == 0) {
          FUN_0069adb0(param_1,param_2,param_3,param_5,3,8);
        }
        else {
          FUN_00699180("Bad field name",1);
        }
      }
    }
  }
  return *param_2;
}

