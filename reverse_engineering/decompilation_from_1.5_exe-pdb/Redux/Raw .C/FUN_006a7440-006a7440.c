
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_006a7440(int param_1)

{
  undefined4 uVar1;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  undefined4 *local_8;
  
  local_18 = *(int *)(*(int *)(param_1 + 0x40) + 0x10) - *(int *)(param_1 + 0x3c);
  local_c = param_1;
  if ((*(int *)(*(int *)(param_1 + 0x40) + 0x60) != 0) &&
     (0 < *(int *)(*(int *)(*(int *)(param_1 + 0x40) + 0x60) + 0x408))) {
    _DAT_009310bc = "Schedule\\scheduler.cpp";
    _DAT_009310c0 = 0x2ef;
    FUN_006a5f50(0x800,"Start allocated_troops = %d",*(undefined4 *)(param_1 + 0x3c));
  }
  local_10 = *(int *)(*(int *)(local_c + 0x24) + 8);
  while ((local_10 = local_10 + -1, -1 < local_10 && (0 < local_18))) {
    local_8 = (undefined4 *)FUN_006a8750(*(undefined4 *)(local_c + 0x24),local_10);
    if ((local_8 != (undefined4 *)0x0) &&
       (((*(int *)(local_8[2] + 0x18) == 0 &&
         (local_20 = *(int *)(local_8[1] + 0x34), 0 < *(int *)(local_8[1] + 0x14))) &&
        (local_1c = *(int *)(local_8[2] + 0xc) - *(int *)(local_8[2] + 8), 0 < local_1c)))) {
      local_24 = local_1c;
      if (local_20 < local_1c) {
        local_24 = local_20;
      }
      local_14 = FUN_006a8c50(*(undefined4 *)(local_c + 0x40),local_8[1],*local_8,local_24,&local_28
                              ,local_8[2]);
      if (0 < local_14) {
        local_8[3] = local_14;
        *(int *)(local_8[2] + 8) = *(int *)(local_8[2] + 8) + local_14;
        *(int *)(local_8[1] + 0x20) = *(int *)(local_8[1] + 0x20) + local_14;
        local_18 = local_18 - local_28;
        if (local_8[8] == 0) {
          local_8[8] = 1;
          uVar1 = FUN_0069d330(*(undefined4 *)(local_c + 0x2c),local_8);
          local_8[9] = uVar1;
        }
      }
    }
  }
  *(int *)(local_c + 0x3c) = *(int *)(*(int *)(local_c + 0x40) + 0x10) - local_18;
  if ((*(int *)(*(int *)(local_c + 0x40) + 0x60) != 0) &&
     (0 < *(int *)(*(int *)(*(int *)(local_c + 0x40) + 0x60) + 0x408))) {
    _DAT_009310bc = "Schedule\\scheduler.cpp";
    _DAT_009310c0 = 0x357;
    FUN_006a5f50(0x800,"End allocated_troops = %d.  @(%d, %d)",*(undefined4 *)(local_c + 0x3c),
                 (*(int *)(*(int *)(local_c + 0x24) + 8) + -1) - local_10,
                 *(undefined4 *)(*(int *)(local_c + 0x24) + 8));
  }
  return;
}

