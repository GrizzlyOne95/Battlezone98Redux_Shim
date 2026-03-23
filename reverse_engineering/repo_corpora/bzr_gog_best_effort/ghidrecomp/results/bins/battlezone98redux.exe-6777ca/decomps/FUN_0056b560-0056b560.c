
undefined4 __thiscall FUN_0056b560(int param_1,byte *param_2)

{
  byte bVar1;
  undefined4 uVar2;
  bool bVar3;
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
  
  local_18 = *(byte **)(param_1 + 4);
  local_14 = param_2;
  do {
    bVar1 = *local_14;
    bVar3 = bVar1 < *local_18;
    if (bVar1 != *local_18) {
LAB_0056b5b5:
      local_3c = -(uint)bVar3 | 1;
      goto LAB_0056b5bd;
    }
    if (bVar1 == 0) break;
    bVar1 = local_14[1];
    bVar3 = bVar1 < local_18[1];
    if (bVar1 != local_18[1]) goto LAB_0056b5b5;
    local_14 = local_14 + 2;
    local_18 = local_18 + 2;
  } while (bVar1 != 0);
  local_3c = 0;
LAB_0056b5bd:
  if (local_3c == 0) {
    uVar2 = 1;
  }
  else {
    local_20 = &DAT_00883708;
    local_1c = param_2;
    do {
      bVar1 = *local_1c;
      bVar3 = bVar1 < *local_20;
      if (bVar1 != *local_20) {
LAB_0056b61d:
        local_40 = -(uint)bVar3 | 1;
        goto LAB_0056b625;
      }
      if (bVar1 == 0) break;
      bVar1 = local_1c[1];
      bVar3 = bVar1 < local_20[1];
      if (bVar1 != local_20[1]) goto LAB_0056b61d;
      local_1c = local_1c + 2;
      local_20 = local_20 + 2;
    } while (bVar1 != 0);
    local_40 = 0;
LAB_0056b625:
    if (local_40 == 0) {
      uVar2 = 1;
    }
    else {
      local_28 = &DAT_008836f8;
      local_24 = param_2;
      do {
        bVar1 = *local_24;
        bVar3 = bVar1 < *local_28;
        if (bVar1 != *local_28) {
LAB_0056b685:
          local_44 = -(uint)bVar3 | 1;
          goto LAB_0056b68d;
        }
        if (bVar1 == 0) break;
        bVar1 = local_24[1];
        bVar3 = bVar1 < local_28[1];
        if (bVar1 != local_28[1]) goto LAB_0056b685;
        local_24 = local_24 + 2;
        local_28 = local_28 + 2;
      } while (bVar1 != 0);
      local_44 = 0;
LAB_0056b68d:
      if (local_44 == 0) {
        uVar2 = 1;
      }
      else {
        local_30 = &DAT_008836f0;
        local_2c = param_2;
        do {
          bVar1 = *local_2c;
          bVar3 = bVar1 < *local_30;
          if (bVar1 != *local_30) {
LAB_0056b6ed:
            local_48 = -(uint)bVar3 | 1;
            goto LAB_0056b6f5;
          }
          if (bVar1 == 0) break;
          bVar1 = local_2c[1];
          bVar3 = bVar1 < local_30[1];
          if (bVar1 != local_30[1]) goto LAB_0056b6ed;
          local_2c = local_2c + 2;
          local_30 = local_30 + 2;
        } while (bVar1 != 0);
        local_48 = 0;
LAB_0056b6f5:
        if (local_48 == 0) {
          uVar2 = 1;
        }
        else {
          local_38 = &DAT_00883700;
          local_34 = param_2;
          do {
            bVar1 = *local_34;
            bVar3 = bVar1 < *local_38;
            if (bVar1 != *local_38) {
LAB_0056b752:
              local_4c = -(uint)bVar3 | 1;
              goto LAB_0056b75a;
            }
            if (bVar1 == 0) break;
            bVar1 = local_34[1];
            bVar3 = bVar1 < local_38[1];
            if (bVar1 != local_38[1]) goto LAB_0056b752;
            local_34 = local_34 + 2;
            local_38 = local_38 + 2;
          } while (bVar1 != 0);
          local_4c = 0;
LAB_0056b75a:
          if (local_4c == 0) {
            uVar2 = 1;
          }
          else {
            uVar2 = 0;
          }
        }
      }
    }
  }
  return uVar2;
}

