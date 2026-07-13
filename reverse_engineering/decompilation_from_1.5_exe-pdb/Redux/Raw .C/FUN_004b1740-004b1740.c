
undefined4 __thiscall FUN_004b1740(int param_1,byte *param_2)

{
  byte bVar1;
  undefined4 uVar2;
  bool bVar3;
  uint local_20;
  uint local_1c;
  byte *local_18;
  byte *local_14;
  byte *local_10;
  byte *local_c;
  
  local_10 = *(byte **)(param_1 + 4);
  local_c = param_2;
  do {
    bVar1 = *local_c;
    bVar3 = bVar1 < *local_10;
    if (bVar1 != *local_10) {
LAB_004b1795:
      local_1c = -(uint)bVar3 | 1;
      goto LAB_004b179d;
    }
    if (bVar1 == 0) break;
    bVar1 = local_c[1];
    bVar3 = bVar1 < local_10[1];
    if (bVar1 != local_10[1]) goto LAB_004b1795;
    local_c = local_c + 2;
    local_10 = local_10 + 2;
  } while (bVar1 != 0);
  local_1c = 0;
LAB_004b179d:
  if (local_1c == 0) {
    uVar2 = 1;
  }
  else {
    local_18 = &DAT_0087863c;
    local_14 = param_2;
    do {
      bVar1 = *local_14;
      bVar3 = bVar1 < *local_18;
      if (bVar1 != *local_18) {
LAB_004b17fa:
        local_20 = -(uint)bVar3 | 1;
        goto LAB_004b1802;
      }
      if (bVar1 == 0) break;
      bVar1 = local_14[1];
      bVar3 = bVar1 < local_18[1];
      if (bVar1 != local_18[1]) goto LAB_004b17fa;
      local_14 = local_14 + 2;
      local_18 = local_18 + 2;
    } while (bVar1 != 0);
    local_20 = 0;
LAB_004b1802:
    if (local_20 == 0) {
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}

