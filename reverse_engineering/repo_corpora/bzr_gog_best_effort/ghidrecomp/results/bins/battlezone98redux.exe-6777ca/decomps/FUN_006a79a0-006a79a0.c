
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_006a79a0(int param_1)

{
  undefined4 uVar1;
  undefined1 local_1c [4];
  undefined4 *local_18;
  undefined4 *local_14;
  int local_10;
  int *local_c;
  int local_8;
  
  if (*(int *)(param_1 + 0x18) == 0) {
    local_8 = param_1;
    if ((*(int *)(*(int *)(param_1 + 0x40) + 0x60) != 0) &&
       (0 < *(int *)(*(int *)(*(int *)(param_1 + 0x40) + 0x60) + 0x408))) {
      _DAT_009310bc = "Schedule\\scheduler.cpp";
      _DAT_009310c0 = 0x445;
      FUN_006a5f50(0x800,"Updating Squads");
    }
    FUN_006a8760(*(int *)(local_8 + 0x40) + 0x1c,"Schedule\\scheduler.cpp",0x449);
    for (local_10 = 0; local_10 < *(int *)(*(int *)(local_8 + 0x2c) + 8); local_10 = local_10 + 1) {
      local_c = (int *)FUN_0069d590(*(undefined4 *)(local_8 + 0x2c),local_10);
      uVar1 = FUN_0069d330(*(int *)(local_8 + 0x40) + 0x1c,*local_c);
      *(undefined4 *)(*local_c + 0x44) = uVar1;
      FUN_006a8760(*(int *)(local_8 + 0x40) + 0x1c,"Schedule\\scheduler.cpp",0x458);
      local_c[8] = 1;
      if (*(int *)(local_c[2] + 0x14) == 0) {
        FUN_006a8980(*local_c,local_c[2]);
        if ((*(int *)(*(int *)(local_8 + 0x40) + 0x60) != 0) &&
           (2 < *(int *)(*(int *)(*(int *)(local_8 + 0x40) + 0x60) + 0x408))) {
          _DAT_009310bc = "Schedule\\scheduler.cpp";
          _DAT_009310c0 = 0x46c;
          FUN_006a5f50(0x800,"Using squad %d for goal",*(undefined4 *)*local_c);
        }
      }
      else {
        local_18 = *(undefined4 **)(local_c[2] + 0x14);
        if ((*(int *)(*(int *)(local_8 + 0x40) + 0x60) != 0) &&
           (2 < *(int *)(*(int *)(*(int *)(local_8 + 0x40) + 0x60) + 0x408))) {
          _DAT_009310bc = "Schedule\\scheduler.cpp";
          _DAT_009310c0 = 0x485;
          FUN_006a5f50(0x800,"Merging squad %d into squad %d.",*(undefined4 *)*local_c,*local_18);
        }
        FUN_006a8b90(*(undefined4 *)(local_8 + 0x40),*local_c,local_18,
                     *(undefined4 *)(*local_c + 0x34),local_1c);
      }
    }
    local_10 = *(int *)(*(int *)(local_8 + 0x40) + 0x24);
    while (local_10 = local_10 + -1, -1 < local_10) {
      local_14 = (undefined4 *)FUN_0069d590(*(int *)(local_8 + 0x40) + 0x1c,local_10);
      if ((int)local_14[5] < 1) {
        if ((*(int *)(*(int *)(local_8 + 0x40) + 0x60) != 0) &&
           (2 < *(int *)(*(int *)(*(int *)(local_8 + 0x40) + 0x60) + 0x408))) {
          _DAT_009310bc = "Schedule\\scheduler.cpp";
          _DAT_009310c0 = 0x4a8;
          FUN_006a5f50(0x800,"Deleting SQUAD %d.",*local_14);
        }
        FUN_0069d440(*(int *)(local_8 + 0x40) + 0x1c,local_14[0x11]);
        FUN_006a8900(local_14);
      }
    }
    FUN_006a8760(*(int *)(local_8 + 0x40) + 0x1c,"Schedule\\scheduler.cpp",0x4ba);
    *(undefined4 *)(local_8 + 0x18) = 1;
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

