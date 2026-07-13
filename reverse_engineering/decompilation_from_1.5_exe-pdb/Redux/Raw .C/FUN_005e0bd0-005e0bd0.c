
undefined4 FUN_005e0bd0(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 local_30;
  int local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  int local_10;
  int local_c;
  char local_5;
  
  if (DAT_009173b7 == '\0') {
    if (DAT_00917b20 < 0x401) {
      uVar2 = 1;
    }
    else {
      local_5 = '\x01';
      if (DAT_00917b20 < 0x410) {
        local_14 = 8;
      }
      else {
        local_14 = 0x10;
      }
      local_2c = local_14;
      local_10 = 0;
      while ((local_10 < local_2c && (local_5 != '\0'))) {
        local_c = *(int *)(&DAT_00918370 + local_10 * 4);
        if (local_5 == '\0') {
LAB_005e0c82:
          local_18 = 0;
        }
        else {
          cVar1 = FUN_004ce910(param_1,&local_30,4);
          if (cVar1 == '\0') goto LAB_005e0c82;
          local_18 = 1;
        }
        local_5 = (char)local_18;
        FUN_005e10d0(local_30);
        if (local_5 == '\0') {
LAB_005e0ccb:
          local_1c = 0;
        }
        else {
          cVar1 = FUN_004ce910(param_1,local_c + 0x170,4);
          if (cVar1 == '\0') goto LAB_005e0ccb;
          local_1c = 1;
        }
        local_5 = (char)local_1c;
        if ((char)local_1c == '\0') {
LAB_005e0d08:
          local_20 = 0;
        }
        else {
          cVar1 = FUN_004ce910(param_1,local_c + 0x174,4);
          if (cVar1 == '\0') goto LAB_005e0d08;
          local_20 = 1;
        }
        local_5 = (char)local_20;
        if ((char)local_20 == '\0') {
LAB_005e0d44:
          local_24 = 0;
        }
        else {
          cVar1 = FUN_004ce910(param_1,local_c + 0x178,4);
          if (cVar1 == '\0') goto LAB_005e0d44;
          local_24 = 1;
        }
        local_5 = (char)local_24;
        if ((char)local_24 == '\0') {
LAB_005e0d81:
          local_28 = 0;
        }
        else {
          cVar1 = FUN_004cea20(param_1,local_c + 0x17c,4);
          if (cVar1 == '\0') goto LAB_005e0d81;
          local_28 = 1;
        }
        local_10 = local_10 + 1;
        local_5 = (char)local_28;
      }
      uVar2 = CONCAT31((int3)((uint)local_10 >> 8),local_5);
    }
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

