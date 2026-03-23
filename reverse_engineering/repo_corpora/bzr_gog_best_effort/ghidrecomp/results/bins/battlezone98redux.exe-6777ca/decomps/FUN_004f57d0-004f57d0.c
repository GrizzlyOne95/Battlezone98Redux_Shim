
undefined4 __thiscall FUN_004f57d0(int param_1,byte *param_2)

{
  byte bVar1;
  undefined4 uVar2;
  bool bVar3;
  uint local_74;
  uint local_70;
  uint local_6c;
  uint local_68;
  uint local_64;
  uint local_60;
  uint local_5c;
  uint local_58;
  byte *local_54;
  byte *local_50;
  byte *local_4c;
  byte *local_48;
  byte *local_44;
  byte *local_40;
  byte *local_3c;
  byte *local_38;
  byte *local_34;
  byte *local_30;
  byte *local_2c;
  byte *local_28;
  byte *local_24;
  byte *local_20;
  byte *local_1c;
  byte *local_18;
  
  local_20 = *(byte **)(param_1 + 4);
  local_1c = param_2;
  do {
    bVar1 = *local_1c;
    bVar3 = bVar1 < *local_20;
    if (bVar1 != *local_20) {
LAB_004f5828:
      local_58 = -(uint)bVar3 | 1;
      goto LAB_004f5830;
    }
    if (bVar1 == 0) break;
    bVar1 = local_1c[1];
    bVar3 = bVar1 < local_20[1];
    if (bVar1 != local_20[1]) goto LAB_004f5828;
    local_1c = local_1c + 2;
    local_20 = local_20 + 2;
  } while (bVar1 != 0);
  local_58 = 0;
LAB_004f5830:
  if (local_58 == 0) {
    uVar2 = 1;
  }
  else {
    local_28 = &DAT_0087b5a0;
    local_48 = param_2;
    do {
      bVar1 = *local_48;
      bVar3 = bVar1 < *local_28;
      if (bVar1 != *local_28) {
LAB_004f5896:
        local_60 = -(uint)bVar3 | 1;
        goto LAB_004f589e;
      }
      if (bVar1 == 0) break;
      bVar1 = local_48[1];
      bVar3 = bVar1 < local_28[1];
      if (bVar1 != local_28[1]) goto LAB_004f5896;
      local_48 = local_48 + 2;
      local_28 = local_28 + 2;
    } while (bVar1 != 0);
    local_60 = 0;
LAB_004f589e:
    if (local_60 == 0) {
      uVar2 = 1;
    }
    else {
      local_30 = &DAT_0087b4f8;
      local_40 = param_2;
      do {
        bVar1 = *local_40;
        bVar3 = bVar1 < *local_30;
        if (bVar1 != *local_30) {
LAB_004f58fe:
          local_70 = -(uint)bVar3 | 1;
          goto LAB_004f5906;
        }
        if (bVar1 == 0) break;
        bVar1 = local_40[1];
        bVar3 = bVar1 < local_30[1];
        if (bVar1 != local_30[1]) goto LAB_004f58fe;
        local_40 = local_40 + 2;
        local_30 = local_30 + 2;
      } while (bVar1 != 0);
      local_70 = 0;
LAB_004f5906:
      if (local_70 == 0) {
        uVar2 = 1;
      }
      else {
        local_38 = &DAT_0087b500;
        local_50 = param_2;
        do {
          bVar1 = *local_50;
          bVar3 = bVar1 < *local_38;
          if (bVar1 != *local_38) {
LAB_004f596c:
            local_68 = -(uint)bVar3 | 1;
            goto LAB_004f5974;
          }
          if (bVar1 == 0) break;
          bVar1 = local_50[1];
          bVar3 = bVar1 < local_38[1];
          if (bVar1 != local_38[1]) goto LAB_004f596c;
          local_50 = local_50 + 2;
          local_38 = local_38 + 2;
        } while (bVar1 != 0);
        local_68 = 0;
LAB_004f5974:
        if (local_68 == 0) {
          uVar2 = 1;
        }
        else {
          local_24 = &DAT_0087b508;
          local_18 = param_2;
          do {
            bVar1 = *local_18;
            bVar3 = bVar1 < *local_24;
            if (bVar1 != *local_24) {
LAB_004f59d4:
              local_5c = -(uint)bVar3 | 1;
              goto LAB_004f59dc;
            }
            if (bVar1 == 0) break;
            bVar1 = local_18[1];
            bVar3 = bVar1 < local_24[1];
            if (bVar1 != local_24[1]) goto LAB_004f59d4;
            local_18 = local_18 + 2;
            local_24 = local_24 + 2;
          } while (bVar1 != 0);
          local_5c = 0;
LAB_004f59dc:
          if (local_5c == 0) {
            uVar2 = 1;
          }
          else {
            local_34 = &DAT_0087b510;
            local_2c = param_2;
            do {
              bVar1 = *local_2c;
              bVar3 = bVar1 < *local_34;
              if (bVar1 != *local_34) {
LAB_004f5a3c:
                local_64 = -(uint)bVar3 | 1;
                goto LAB_004f5a44;
              }
              if (bVar1 == 0) break;
              bVar1 = local_2c[1];
              bVar3 = bVar1 < local_34[1];
              if (bVar1 != local_34[1]) goto LAB_004f5a3c;
              local_2c = local_2c + 2;
              local_34 = local_34 + 2;
            } while (bVar1 != 0);
            local_64 = 0;
LAB_004f5a44:
            if (local_64 == 0) {
              uVar2 = 1;
            }
            else {
              local_44 = &DAT_0087b518;
              local_3c = param_2;
              do {
                bVar1 = *local_3c;
                bVar3 = bVar1 < *local_44;
                if (bVar1 != *local_44) {
LAB_004f5aaa:
                  local_6c = -(uint)bVar3 | 1;
                  goto LAB_004f5ab2;
                }
                if (bVar1 == 0) break;
                bVar1 = local_3c[1];
                bVar3 = bVar1 < local_44[1];
                if (bVar1 != local_44[1]) goto LAB_004f5aaa;
                local_3c = local_3c + 2;
                local_44 = local_44 + 2;
              } while (bVar1 != 0);
              local_6c = 0;
LAB_004f5ab2:
              if (local_6c == 0) {
                uVar2 = 1;
              }
              else {
                local_54 = &DAT_0087b520;
                local_4c = param_2;
                do {
                  bVar1 = *local_4c;
                  bVar3 = bVar1 < *local_54;
                  if (bVar1 != *local_54) {
LAB_004f5b15:
                    local_74 = -(uint)bVar3 | 1;
                    goto LAB_004f5b1d;
                  }
                  if (bVar1 == 0) break;
                  bVar1 = local_4c[1];
                  bVar3 = bVar1 < local_54[1];
                  if (bVar1 != local_54[1]) goto LAB_004f5b15;
                  local_4c = local_4c + 2;
                  local_54 = local_54 + 2;
                } while (bVar1 != 0);
                local_74 = 0;
LAB_004f5b1d:
                if (local_74 == 0) {
                  uVar2 = 1;
                }
                else {
                  uVar2 = 0;
                }
              }
            }
          }
        }
      }
    }
  }
  return uVar2;
}

