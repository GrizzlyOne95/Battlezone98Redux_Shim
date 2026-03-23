
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_006a7680(void)

{
  undefined4 uVar1;
  double dVar2;
  int local_28;
  int local_24;
  undefined4 local_20;
  int local_1c;
  int *local_18;
  int local_14;
  int local_10;
  int local_c;
  int *local_8;
  
  local_20 = 1;
  local_18 = (int *)0x0;
  dVar2 = 1000000000.0;
  local_1c = 0;
  local_14 = FUN_0069d250();
  for (local_c = 0; local_c < *(int *)(*(int *)(local_10 + 0x2c) + 8); local_c = local_c + 1) {
    local_8 = (int *)FUN_0069d590(*(undefined4 *)(local_10 + 0x2c),local_c);
    local_24 = (*(code *)**(undefined4 **)local_8[2])();
    if (local_24 == 0) {
      *(undefined4 *)(local_8[2] + 0x18) = 1;
    }
    else {
      if ((double)*(float *)(local_8[2] + 0x1c) < dVar2) {
        dVar2 = (double)*(float *)(local_8[2] + 0x1c);
        local_18 = local_8;
        FUN_0069d280(local_14);
      }
      if (local_18[2] == local_8[2]) {
        FUN_0069d330(local_14,local_8);
      }
    }
  }
  if (local_18 != (int *)0x0) {
    local_20 = 0;
    *(undefined4 *)(local_18[2] + 0x18) = 1;
    if ((*(int *)(*(int *)(local_10 + 0x40) + 0x60) != 0) &&
       (2 < *(int *)(*(int *)(*(int *)(local_10 + 0x40) + 0x60) + 0x408))) {
      _DAT_009310bc = "Schedule\\scheduler.cpp";
      _DAT_009310c0 = 0x3b9;
      FUN_006a5f50(0x800,"SCHEDULER: Freeing goal ");
    }
    for (local_c = 0; local_c < *(int *)(local_14 + 8); local_c = local_c + 1) {
      local_8 = (int *)FUN_0069d590(local_14,local_c);
      uVar1 = FUN_006a8b90(*(undefined4 *)(local_10 + 0x40),*local_8,local_8[1],
                           *(undefined4 *)(*local_8 + 0x34),&local_28);
      *(int *)(local_8[2] + 8) = *(int *)(local_8[2] + 8) - local_8[3];
      *(int *)(local_8[1] + 0x20) = *(int *)(local_8[1] + 0x20) - local_8[3];
      local_8[3] = 0;
      local_1c = local_1c + local_28;
      FUN_0069d440(*(undefined4 *)(local_10 + 0x2c),local_8[9],dVar2,uVar1);
      local_8[8] = 0;
    }
  }
  FUN_0069d310(local_14);
  *(int *)(local_10 + 0x3c) = *(int *)(local_10 + 0x3c) - local_1c;
  return local_20;
}

