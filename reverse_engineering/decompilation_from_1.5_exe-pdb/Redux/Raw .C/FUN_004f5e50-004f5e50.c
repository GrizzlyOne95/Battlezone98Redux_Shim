
undefined4 __thiscall FUN_004f5e50(int param_1,byte *param_2)

{
  byte bVar1;
  undefined4 uVar2;
  bool bVar3;
  uint local_ac;
  uint local_a8;
  uint local_a4;
  uint local_a0;
  uint local_9c;
  uint local_98;
  uint local_94;
  uint local_90;
  uint local_8c;
  uint local_88;
  uint local_84;
  uint local_80;
  byte *local_7c;
  byte *local_78;
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
  
  local_28 = *(byte **)(param_1 + 4);
  local_24 = param_2;
  do {
    bVar1 = *local_24;
    bVar3 = bVar1 < *local_28;
    if (bVar1 != *local_28) {
LAB_004f5eae:
      local_80 = -(uint)bVar3 | 1;
      goto LAB_004f5eb6;
    }
    if (bVar1 == 0) break;
    bVar1 = local_24[1];
    bVar3 = bVar1 < local_28[1];
    if (bVar1 != local_28[1]) goto LAB_004f5eae;
    local_24 = local_24 + 2;
    local_28 = local_28 + 2;
  } while (bVar1 != 0);
  local_80 = 0;
LAB_004f5eb6:
  if (local_80 == 0) {
    uVar2 = 1;
  }
  else {
    local_30 = &DAT_0087b5a0;
    local_68 = param_2;
    do {
      bVar1 = *local_68;
      bVar3 = bVar1 < *local_30;
      if (bVar1 != *local_30) {
LAB_004f5f1f:
        local_88 = -(uint)bVar3 | 1;
        goto LAB_004f5f2a;
      }
      if (bVar1 == 0) break;
      bVar1 = local_68[1];
      bVar3 = bVar1 < local_30[1];
      if (bVar1 != local_30[1]) goto LAB_004f5f1f;
      local_68 = local_68 + 2;
      local_30 = local_30 + 2;
    } while (bVar1 != 0);
    local_88 = 0;
LAB_004f5f2a:
    if (local_88 == 0) {
      uVar2 = 1;
    }
    else {
      local_38 = &DAT_0087b4f8;
      local_58 = param_2;
      do {
        bVar1 = *local_58;
        bVar3 = bVar1 < *local_38;
        if (bVar1 != *local_38) {
LAB_004f5f96:
          local_a8 = -(uint)bVar3 | 1;
          goto LAB_004f5fa1;
        }
        if (bVar1 == 0) break;
        bVar1 = local_58[1];
        bVar3 = bVar1 < local_38[1];
        if (bVar1 != local_38[1]) goto LAB_004f5f96;
        local_58 = local_58 + 2;
        local_38 = local_38 + 2;
      } while (bVar1 != 0);
      local_a8 = 0;
LAB_004f5fa1:
      if (local_a8 == 0) {
        uVar2 = 1;
      }
      else {
        local_40 = &DAT_0087b500;
        local_78 = param_2;
        do {
          bVar1 = *local_78;
          bVar3 = bVar1 < *local_40;
          if (bVar1 != *local_40) {
LAB_004f600d:
            local_90 = -(uint)bVar3 | 1;
            goto LAB_004f6018;
          }
          if (bVar1 == 0) break;
          bVar1 = local_78[1];
          bVar3 = bVar1 < local_40[1];
          if (bVar1 != local_40[1]) goto LAB_004f600d;
          local_78 = local_78 + 2;
          local_40 = local_40 + 2;
        } while (bVar1 != 0);
        local_90 = 0;
LAB_004f6018:
        if (local_90 == 0) {
          uVar2 = 1;
        }
        else {
          local_48 = &DAT_0087b508;
          local_60 = param_2;
          do {
            bVar1 = *local_60;
            bVar3 = bVar1 < *local_48;
            if (bVar1 != *local_48) {
LAB_004f6084:
              local_a0 = -(uint)bVar3 | 1;
              goto LAB_004f608f;
            }
            if (bVar1 == 0) break;
            bVar1 = local_60[1];
            bVar3 = bVar1 < local_48[1];
            if (bVar1 != local_48[1]) goto LAB_004f6084;
            local_60 = local_60 + 2;
            local_48 = local_48 + 2;
          } while (bVar1 != 0);
          local_a0 = 0;
LAB_004f608f:
          if (local_a0 == 0) {
            uVar2 = 1;
          }
          else {
            local_50 = &DAT_0087b510;
            local_70 = param_2;
            do {
              bVar1 = *local_70;
              bVar3 = bVar1 < *local_50;
              if (bVar1 != *local_50) {
LAB_004f60fb:
                local_98 = -(uint)bVar3 | 1;
                goto LAB_004f6106;
              }
              if (bVar1 == 0) break;
              bVar1 = local_70[1];
              bVar3 = bVar1 < local_50[1];
              if (bVar1 != local_50[1]) goto LAB_004f60fb;
              local_70 = local_70 + 2;
              local_50 = local_50 + 2;
            } while (bVar1 != 0);
            local_98 = 0;
LAB_004f6106:
            if (local_98 == 0) {
              uVar2 = 1;
            }
            else {
              local_2c = &DAT_0087b518;
              local_20 = param_2;
              do {
                bVar1 = *local_20;
                bVar3 = bVar1 < *local_2c;
                if (bVar1 != *local_2c) {
LAB_004f616f:
                  local_84 = -(uint)bVar3 | 1;
                  goto LAB_004f6177;
                }
                if (bVar1 == 0) break;
                bVar1 = local_20[1];
                bVar3 = bVar1 < local_2c[1];
                if (bVar1 != local_2c[1]) goto LAB_004f616f;
                local_20 = local_20 + 2;
                local_2c = local_2c + 2;
              } while (bVar1 != 0);
              local_84 = 0;
LAB_004f6177:
              if (local_84 == 0) {
                uVar2 = 1;
              }
              else {
                local_3c = &DAT_0087b520;
                local_34 = param_2;
                do {
                  bVar1 = *local_34;
                  bVar3 = bVar1 < *local_3c;
                  if (bVar1 != *local_3c) {
LAB_004f61e0:
                    local_8c = -(uint)bVar3 | 1;
                    goto LAB_004f61eb;
                  }
                  if (bVar1 == 0) break;
                  bVar1 = local_34[1];
                  bVar3 = bVar1 < local_3c[1];
                  if (bVar1 != local_3c[1]) goto LAB_004f61e0;
                  local_34 = local_34 + 2;
                  local_3c = local_3c + 2;
                } while (bVar1 != 0);
                local_8c = 0;
LAB_004f61eb:
                if (local_8c == 0) {
                  uVar2 = 1;
                }
                else {
                  local_4c = &DAT_0087b630;
                  local_44 = param_2;
                  do {
                    bVar1 = *local_44;
                    bVar3 = bVar1 < *local_4c;
                    if (bVar1 != *local_4c) {
LAB_004f6257:
                      local_94 = -(uint)bVar3 | 1;
                      goto LAB_004f6262;
                    }
                    if (bVar1 == 0) break;
                    bVar1 = local_44[1];
                    bVar3 = bVar1 < local_4c[1];
                    if (bVar1 != local_4c[1]) goto LAB_004f6257;
                    local_44 = local_44 + 2;
                    local_4c = local_4c + 2;
                  } while (bVar1 != 0);
                  local_94 = 0;
LAB_004f6262:
                  if (local_94 == 0) {
                    uVar2 = 1;
                  }
                  else {
                    local_5c = &DAT_0087b638;
                    local_54 = param_2;
                    do {
                      bVar1 = *local_54;
                      bVar3 = bVar1 < *local_5c;
                      if (bVar1 != *local_5c) {
LAB_004f62ce:
                        local_9c = -(uint)bVar3 | 1;
                        goto LAB_004f62d9;
                      }
                      if (bVar1 == 0) break;
                      bVar1 = local_54[1];
                      bVar3 = bVar1 < local_5c[1];
                      if (bVar1 != local_5c[1]) goto LAB_004f62ce;
                      local_54 = local_54 + 2;
                      local_5c = local_5c + 2;
                    } while (bVar1 != 0);
                    local_9c = 0;
LAB_004f62d9:
                    if (local_9c == 0) {
                      uVar2 = 1;
                    }
                    else {
                      local_6c = &DAT_0087b640;
                      local_64 = param_2;
                      do {
                        bVar1 = *local_64;
                        bVar3 = bVar1 < *local_6c;
                        if (bVar1 != *local_6c) {
LAB_004f6345:
                          local_a4 = -(uint)bVar3 | 1;
                          goto LAB_004f6350;
                        }
                        if (bVar1 == 0) break;
                        bVar1 = local_64[1];
                        bVar3 = bVar1 < local_6c[1];
                        if (bVar1 != local_6c[1]) goto LAB_004f6345;
                        local_64 = local_64 + 2;
                        local_6c = local_6c + 2;
                      } while (bVar1 != 0);
                      local_a4 = 0;
LAB_004f6350:
                      if (local_a4 == 0) {
                        uVar2 = 1;
                      }
                      else {
                        local_7c = &DAT_0087b648;
                        local_74 = param_2;
                        do {
                          bVar1 = *local_74;
                          bVar3 = bVar1 < *local_7c;
                          if (bVar1 != *local_7c) {
LAB_004f63b9:
                            local_ac = -(uint)bVar3 | 1;
                            goto LAB_004f63c4;
                          }
                          if (bVar1 == 0) break;
                          bVar1 = local_74[1];
                          bVar3 = bVar1 < local_7c[1];
                          if (bVar1 != local_7c[1]) goto LAB_004f63b9;
                          local_74 = local_74 + 2;
                          local_7c = local_7c + 2;
                        } while (bVar1 != 0);
                        local_ac = 0;
LAB_004f63c4:
                        if (local_ac == 0) {
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
        }
      }
    }
  }
  return uVar2;
}

