
float10 FUN_00697940(undefined4 param_1,int *param_2,int param_3,undefined4 param_4,
                    undefined4 param_5,int param_6,undefined4 param_7,int *param_8,uint *param_9,
                    undefined4 param_10)

{
  bool bVar1;
  float10 fVar2;
  float10 fVar3;
  double dVar4;
  int local_58;
  uint local_54;
  uint local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  uint local_3c;
  uint local_34;
  uint local_30;
  uint local_2c;
  int local_28;
  byte *local_24;
  byte *local_20;
  byte *local_1c;
  byte *local_18;
  int local_14;
  uint local_10;
  uint local_c;
  byte local_8;
  byte local_7;
  byte local_6;
  byte local_5;
  
  local_c = 0;
  local_28 = 0;
  fVar2 = (float10)FUN_00697c80(param_1,param_2,param_3,param_4,param_5,param_6,param_7,&local_14,
                                &local_10,param_10);
  dVar4 = (double)fVar2;
  if (param_3 < *param_2) {
    local_28 = 1;
  }
  else if (*(char *)(*param_2 * 0x50 + param_6) == '=') {
    if (*(char *)((*param_2 + 1) * 0x50 + param_6) == '=') {
      local_c = 1;
      *param_2 = *param_2 + 1;
    }
  }
  else if (*(char *)(*param_2 * 0x50 + param_6) == '!') {
    if (*(char *)((*param_2 + 1) * 0x50 + param_6) == '=') {
      local_c = 0;
      *param_2 = *param_2 + 1;
    }
  }
  else {
    local_1c = &DAT_008948d4;
    local_18 = (byte *)(*param_2 * 0x50 + param_6);
    do {
      local_5 = *local_18;
      bVar1 = local_5 < *local_1c;
      if (local_5 != *local_1c) {
LAB_00697a91:
        local_2c = -(uint)bVar1 | 1;
        goto LAB_00697a99;
      }
      if (local_5 == 0) break;
      local_6 = local_18[1];
      bVar1 = local_6 < local_1c[1];
      if (local_6 != local_1c[1]) goto LAB_00697a91;
      local_18 = local_18 + 2;
      local_1c = local_1c + 2;
    } while (local_6 != 0);
    local_2c = 0;
LAB_00697a99:
    local_50 = local_2c;
    local_30 = (uint)(local_2c == 0);
    local_c = local_30;
    if (local_30 == 0) {
      local_24 = &DAT_008948cc;
      local_20 = (byte *)(*param_2 * 0x50 + param_6);
      do {
        local_7 = *local_20;
        bVar1 = local_7 < *local_24;
        if (local_7 != *local_24) {
LAB_00697b11:
          local_34 = -(uint)bVar1 | 1;
          goto LAB_00697b19;
        }
        if (local_7 == 0) break;
        local_8 = local_20[1];
        bVar1 = local_8 < local_24[1];
        if (local_8 != local_24[1]) goto LAB_00697b11;
        local_20 = local_20 + 2;
        local_24 = local_24 + 2;
      } while (local_8 != 0);
      local_34 = 0;
LAB_00697b19:
      local_54 = local_34;
      local_c = local_34;
      if (local_34 != 0) {
        local_28 = 1;
      }
    }
  }
  if (local_28 == 0) {
    *param_2 = *param_2 + 1;
    fVar3 = (float10)FUN_00697c80(param_1,param_2,param_3,param_4,param_5,param_6,param_7,&local_58,
                                  &local_40,param_10);
    if ((local_14 == 0) || (local_58 == 0)) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (bVar1) {
      if (local_c == 0) {
        local_44 = (uint)(local_10 != local_40);
        local_10 = local_44;
      }
      else {
        local_3c = (uint)(local_10 == local_40);
        local_10 = local_3c;
      }
    }
    else if (local_c == 0) {
      local_4c = (uint)(dVar4 != (double)fVar3);
      local_10 = local_4c;
    }
    else {
      local_48 = (uint)(dVar4 == (double)fVar3);
      local_10 = local_48;
    }
    local_14 = 1;
  }
  *param_8 = local_14;
  if (local_14 == 0) {
    *param_9 = (int)fVar2;
  }
  else {
    *param_9 = local_10;
    dVar4 = (double)(int)local_10;
  }
  return (float10)dVar4;
}

