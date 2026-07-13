
float10 FUN_00697c80(undefined4 param_1,int *param_2,int param_3,undefined4 param_4,
                    undefined4 param_5,int param_6,undefined4 param_7,int *param_8,uint *param_9,
                    undefined4 param_10)

{
  double dVar1;
  bool bVar2;
  float10 fVar3;
  int local_9c;
  uint local_98;
  uint local_94;
  uint local_90;
  uint local_84;
  uint local_80;
  uint local_7c;
  uint local_78;
  uint local_74;
  uint local_6c;
  uint local_68;
  uint local_64;
  uint local_60;
  uint local_5c;
  uint local_58;
  uint local_54;
  uint local_50;
  double local_4c;
  int local_44;
  int local_40;
  int local_3c;
  byte *local_38;
  byte *local_34;
  byte *local_30;
  byte *local_2c;
  int local_28;
  byte *local_24;
  byte *local_20;
  int local_1c;
  uint local_18;
  uint local_14;
  byte local_e;
  byte local_d;
  byte local_c;
  byte local_b;
  byte local_a;
  byte local_9;
  uint local_8;
  
  local_3c = 0;
  local_14 = 0;
  local_44 = 0;
  local_18 = 0;
  local_40 = 0;
  fVar3 = (float10)FUN_006980b0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,&local_1c,
                                &local_8,param_10);
  local_4c = (double)fVar3;
  if (param_3 < *param_2) {
    local_3c = 1;
  }
  else {
    local_30 = &DAT_008948dc;
    local_20 = (byte *)(*param_2 * 0x50 + param_6);
    do {
      local_e = *local_20;
      bVar2 = local_e < *local_30;
      if (local_e != *local_30) {
LAB_00697d45:
        local_50 = -(uint)bVar2 | 1;
        goto LAB_00697d4d;
      }
      if (local_e == 0) break;
      local_b = local_20[1];
      bVar2 = local_b < local_30[1];
      if (local_b != local_30[1]) goto LAB_00697d45;
      local_20 = local_20 + 2;
      local_30 = local_30 + 2;
    } while (local_b != 0);
    local_50 = 0;
LAB_00697d4d:
    local_90 = local_50;
    local_80 = (uint)(local_50 == 0);
    local_14 = local_80;
    if (local_80 == 0) {
      local_38 = &DAT_008948d8;
      local_2c = (byte *)(*param_2 * 0x50 + param_6);
      do {
        local_d = *local_2c;
        bVar2 = local_d < *local_38;
        if (local_d != *local_38) {
LAB_00697dcf:
          local_58 = -(uint)bVar2 | 1;
          goto LAB_00697dd7;
        }
        if (local_d == 0) break;
        local_c = local_2c[1];
        bVar2 = local_c < local_38[1];
        if (local_c != local_38[1]) goto LAB_00697dcf;
        local_2c = local_2c + 2;
        local_38 = local_38 + 2;
      } while (local_c != 0);
      local_58 = 0;
LAB_00697dd7:
      local_94 = local_58;
      local_6c = (uint)(local_58 == 0);
      local_18 = local_6c;
      if (local_6c == 0) {
        local_3c = 1;
      }
    }
  }
  if (local_3c == 0) {
    *param_2 = *param_2 + 1;
    local_24 = &DAT_00871540;
    local_34 = (byte *)(*param_2 * 0x50 + param_6);
    do {
      local_9 = *local_34;
      bVar2 = local_9 < *local_24;
      if (local_9 != *local_24) {
LAB_00697e73:
        local_60 = -(uint)bVar2 | 1;
        goto LAB_00697e7b;
      }
      if (local_9 == 0) break;
      local_a = local_34[1];
      bVar2 = local_a < local_24[1];
      if (local_a != local_24[1]) goto LAB_00697e73;
      local_34 = local_34 + 2;
      local_24 = local_24 + 2;
    } while (local_a != 0);
    local_60 = 0;
LAB_00697e7b:
    local_98 = local_60;
    if (local_60 == 0) {
      if (local_14 != 0) {
        local_14 = 0;
        local_44 = 1;
      }
      if (local_18 != 0) {
        local_18 = 0;
        local_40 = 1;
      }
      *param_2 = *param_2 + 1;
    }
    fVar3 = (float10)FUN_006980b0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,&local_9c,
                                  &local_28,param_10);
    dVar1 = (double)fVar3;
    if ((local_1c == 0) || (local_9c == 0)) {
      bVar2 = false;
    }
    else {
      bVar2 = true;
    }
    if (bVar2) {
      if (local_44 != 0) {
        local_68 = (uint)(local_28 <= (int)local_8);
        local_8 = local_68;
      }
      if (local_40 != 0) {
        local_78 = (uint)((int)local_8 <= local_28);
        local_8 = local_78;
      }
      if (local_14 != 0) {
        local_84 = (uint)(local_28 < (int)local_8);
        local_8 = local_84;
      }
      if (local_18 != 0) {
        local_74 = (uint)((int)local_8 < local_28);
        local_8 = local_74;
      }
    }
    else {
      if (local_44 != 0) {
        local_7c = (uint)(dVar1 <= local_4c);
        local_8 = local_7c;
      }
      if (local_40 != 0) {
        local_54 = (uint)(local_4c <= dVar1);
        local_8 = local_54;
      }
      if (local_14 != 0) {
        local_5c = (uint)(dVar1 < local_4c);
        local_8 = local_5c;
      }
      if (local_18 != 0) {
        local_64 = (uint)(local_4c < dVar1);
        local_8 = local_64;
      }
    }
    local_1c = 1;
  }
  *param_8 = local_1c;
  if (local_1c == 0) {
    *param_9 = (int)local_4c;
  }
  else {
    *param_9 = local_8;
    local_4c = (double)(int)local_8;
  }
  return (float10)local_4c;
}

