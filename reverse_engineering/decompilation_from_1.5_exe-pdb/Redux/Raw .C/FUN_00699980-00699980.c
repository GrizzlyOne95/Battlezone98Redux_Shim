
undefined4 FUN_00699980(undefined4 param_1,byte *param_2)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  bool bVar4;
  uint local_a0;
  uint local_9c;
  uint local_98;
  uint local_94;
  uint local_90;
  uint local_8c;
  uint local_88;
  uint local_84;
  uint local_80;
  uint local_7c;
  uint local_78;
  byte *local_74;
  byte *local_70;
  byte *local_6c;
  byte *local_68;
  byte *local_64;
  byte *local_60;
  byte *local_5c;
  byte *local_58;
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
  
  local_28 = &DAT_008948e8;
  local_60 = param_2;
  do {
    bVar1 = *local_60;
    bVar4 = bVar1 < *local_28;
    if (bVar1 != *local_28) {
LAB_006999d3:
      local_78 = -(uint)bVar4 | 1;
      goto LAB_006999db;
    }
    if (bVar1 == 0) break;
    bVar1 = local_60[1];
    bVar4 = bVar1 < local_28[1];
    if (bVar1 != local_28[1]) goto LAB_006999d3;
    local_60 = local_60 + 2;
    local_28 = local_28 + 2;
  } while (bVar1 != 0);
  local_78 = 0;
LAB_006999db:
  if (local_78 == 0) {
    uVar2 = 1;
  }
  else {
    local_30 = (byte *)0x89485c;
    local_50 = param_2;
    do {
      bVar1 = *local_50;
      bVar4 = bVar1 < *local_30;
      if (bVar1 != *local_30) {
LAB_00699a44:
        local_9c = -(uint)bVar4 | 1;
        goto LAB_00699a4f;
      }
      if (bVar1 == 0) break;
      bVar1 = local_50[1];
      bVar4 = bVar1 < local_30[1];
      if (bVar1 != local_30[1]) goto LAB_00699a44;
      local_50 = local_50 + 2;
      local_30 = local_30 + 2;
    } while (bVar1 != 0);
    local_9c = 0;
LAB_00699a4f:
    if (local_9c == 0) {
      uVar2 = 2;
    }
    else {
      local_38 = (byte *)0x894894;
      local_70 = param_2;
      do {
        bVar1 = *local_70;
        bVar4 = bVar1 < *local_38;
        if (bVar1 != *local_38) {
LAB_00699ab8:
          local_84 = -(uint)bVar4 | 1;
          goto LAB_00699ac0;
        }
        if (bVar1 == 0) break;
        bVar1 = local_70[1];
        bVar4 = bVar1 < local_38[1];
        if (bVar1 != local_38[1]) goto LAB_00699ab8;
        local_70 = local_70 + 2;
        local_38 = local_38 + 2;
      } while (bVar1 != 0);
      local_84 = 0;
LAB_00699ac0:
      if (local_84 == 0) {
        uVar2 = 3;
      }
      else {
        local_40 = &DAT_008948e0;
        local_58 = param_2;
        do {
          bVar1 = *local_58;
          bVar4 = bVar1 < *local_40;
          if (bVar1 != *local_40) {
LAB_00699b29:
            local_94 = -(uint)bVar4 | 1;
            goto LAB_00699b34;
          }
          if (bVar1 == 0) break;
          bVar1 = local_58[1];
          bVar4 = bVar1 < local_40[1];
          if (bVar1 != local_40[1]) goto LAB_00699b29;
          local_58 = local_58 + 2;
          local_40 = local_40 + 2;
        } while (bVar1 != 0);
        local_94 = 0;
LAB_00699b34:
        if (local_94 == 0) {
          uVar2 = 4;
        }
        else {
          local_48 = (byte *)0x894958;
          local_68 = param_2;
          do {
            bVar1 = *local_68;
            bVar4 = bVar1 < *local_48;
            if (bVar1 != *local_48) {
LAB_00699ba0:
              local_8c = -(uint)bVar4 | 1;
              goto LAB_00699bab;
            }
            if (bVar1 == 0) break;
            bVar1 = local_68[1];
            bVar4 = bVar1 < local_48[1];
            if (bVar1 != local_48[1]) goto LAB_00699ba0;
            local_68 = local_68 + 2;
            local_48 = local_48 + 2;
          } while (bVar1 != 0);
          local_8c = 0;
LAB_00699bab:
          if (local_8c == 0) {
            uVar2 = 5;
          }
          else {
            local_24 = (byte *)0x89497c;
            local_20 = param_2;
            do {
              bVar1 = *local_20;
              bVar4 = bVar1 < *local_24;
              if (bVar1 != *local_24) {
LAB_00699c14:
                local_7c = -(uint)bVar4 | 1;
                goto LAB_00699c1c;
              }
              if (bVar1 == 0) break;
              bVar1 = local_20[1];
              bVar4 = bVar1 < local_24[1];
              if (bVar1 != local_24[1]) goto LAB_00699c14;
              local_20 = local_20 + 2;
              local_24 = local_24 + 2;
            } while (bVar1 != 0);
            local_7c = 0;
LAB_00699c1c:
            if (local_7c == 0) {
              uVar2 = 7;
            }
            else {
              local_34 = (byte *)0x894970;
              local_2c = param_2;
              do {
                bVar1 = *local_2c;
                bVar4 = bVar1 < *local_34;
                if (bVar1 != *local_34) {
LAB_00699c82:
                  local_80 = -(uint)bVar4 | 1;
                  goto LAB_00699c8a;
                }
                if (bVar1 == 0) break;
                bVar1 = local_2c[1];
                bVar4 = bVar1 < local_34[1];
                if (bVar1 != local_34[1]) goto LAB_00699c82;
                local_2c = local_2c + 2;
                local_34 = local_34 + 2;
              } while (bVar1 != 0);
              local_80 = 0;
LAB_00699c8a:
              if (local_80 == 0) {
                uVar2 = 0x10;
              }
              else {
                local_44 = &DAT_0089498c;
                local_3c = param_2;
                do {
                  bVar1 = *local_3c;
                  bVar4 = bVar1 < *local_44;
                  if (bVar1 != *local_44) {
LAB_00699cf3:
                    local_88 = -(uint)bVar4 | 1;
                    goto LAB_00699cfe;
                  }
                  if (bVar1 == 0) break;
                  bVar1 = local_3c[1];
                  bVar4 = bVar1 < local_44[1];
                  if (bVar1 != local_44[1]) goto LAB_00699cf3;
                  local_3c = local_3c + 2;
                  local_44 = local_44 + 2;
                } while (bVar1 != 0);
                local_88 = 0;
LAB_00699cfe:
                if (local_88 == 0) {
                  uVar2 = 0xb;
                }
                else {
                  local_54 = &DAT_00894984;
                  local_4c = param_2;
                  do {
                    bVar1 = *local_4c;
                    bVar4 = bVar1 < *local_54;
                    if (bVar1 != *local_54) {
LAB_00699d6a:
                      local_90 = -(uint)bVar4 | 1;
                      goto LAB_00699d75;
                    }
                    if (bVar1 == 0) break;
                    bVar1 = local_4c[1];
                    bVar4 = bVar1 < local_54[1];
                    if (bVar1 != local_54[1]) goto LAB_00699d6a;
                    local_4c = local_4c + 2;
                    local_54 = local_54 + 2;
                  } while (bVar1 != 0);
                  local_90 = 0;
LAB_00699d75:
                  if (local_90 == 0) {
                    uVar2 = 0xe;
                  }
                  else {
                    local_64 = &DAT_008949a4;
                    local_5c = param_2;
                    do {
                      bVar1 = *local_5c;
                      bVar4 = bVar1 < *local_64;
                      if (bVar1 != *local_64) {
LAB_00699de1:
                        local_98 = -(uint)bVar4 | 1;
                        goto LAB_00699dec;
                      }
                      if (bVar1 == 0) break;
                      bVar1 = local_5c[1];
                      bVar4 = bVar1 < local_64[1];
                      if (bVar1 != local_64[1]) goto LAB_00699de1;
                      local_5c = local_5c + 2;
                      local_64 = local_64 + 2;
                    } while (bVar1 != 0);
                    local_98 = 0;
LAB_00699dec:
                    if (local_98 == 0) {
                      uVar2 = 0xc;
                    }
                    else {
                      local_74 = &DAT_0087d198;
                      local_6c = param_2;
                      do {
                        bVar1 = *local_6c;
                        bVar4 = bVar1 < *local_74;
                        if (bVar1 != *local_74) {
LAB_00699e58:
                          local_a0 = -(uint)bVar4 | 1;
                          goto LAB_00699e63;
                        }
                        if (bVar1 == 0) break;
                        bVar1 = local_6c[1];
                        bVar4 = bVar1 < local_74[1];
                        if (bVar1 != local_74[1]) goto LAB_00699e58;
                        local_6c = local_6c + 2;
                        local_74 = local_74 + 2;
                      } while (bVar1 != 0);
                      local_a0 = 0;
LAB_00699e63:
                      if (local_a0 == 0) {
                        uVar2 = 0xd;
                      }
                      else {
                        iVar3 = FUN_00699800(param_1,param_2);
                        if (iVar3 == 0) {
                          iVar3 = FUN_006998c0(param_1,param_2);
                          if (iVar3 == 0) {
                            uVar2 = 0xfffffffd;
                          }
                          else {
                            uVar2 = 9;
                          }
                        }
                        else {
                          uVar2 = 8;
                        }
                      }
                    }
                  }
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

