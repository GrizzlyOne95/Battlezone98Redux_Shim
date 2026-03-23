
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_006a6da0(int param_1)

{
  bool bVar1;
  int iVar2;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int *local_8;
  
  local_14 = 0;
  bVar1 = false;
  if (*(int *)(param_1 + 8) == 0) {
    local_c = param_1;
    if ((*(int *)(*(int *)(param_1 + 0x40) + 0x60) != 0) &&
       (0 < *(int *)(*(int *)(*(int *)(param_1 + 0x40) + 0x60) + 0x408))) {
      _DAT_009310bc = "Schedule\\scheduler.cpp";
      _DAT_009310c0 = 0x170;
      FUN_006a5f50(0x800,"Initing a subscheduling phase");
    }
    local_10 = *(int *)(local_c + 0x1c);
    while ((-1 < local_10 && (local_14 == 0))) {
      local_8 = (int *)FUN_006a8750(*(undefined4 *)(local_c + 0x20),local_10);
      if ((*(int *)(*(int *)(*(int *)(local_c + 0x40) + 0x60) + 0x40c + local_8[1] * 4) == -1) ||
         (*(int *)(local_c + 0x48 + local_8[1] * 4) <
          *(int *)(*(int *)(*(int *)(local_c + 0x40) + 0x60) + 0x40c + local_8[1] * 4))) {
        *(int *)(local_c + 0x48 + local_8[1] * 4) = *(int *)(local_c + 0x48 + local_8[1] * 4) + 1;
        iVar2 = (**(code **)(*local_8 + 0xc))(&local_18);
        if (iVar2 == 0) {
          local_14 = 1;
          FUN_006a89e0(local_8[5]);
          local_8[0xb] = 0;
        }
        else {
          if (((0 < local_18) && (*(int *)(*(int *)(local_c + 0x40) + 0x60) != 0)) &&
             (2 < *(int *)(*(int *)(*(int *)(local_c + 0x40) + 0x60) + 0x408))) {
            _DAT_009310bc = "Schedule\\scheduler.cpp";
            _DAT_009310c0 = 0x1a5;
            FUN_006a5f50(0x800,"EXCESS TROOPS: Strength %d.",local_18);
          }
          if (local_8[5] != 0) {
            *(undefined4 *)(local_8[5] + 0x38) = 1;
          }
          local_8[0xb] = 1;
          local_10 = local_10 + -1;
        }
      }
      else {
        local_10 = local_10 + -1;
        if (local_8[5] != 0) {
          FUN_006a89e0(local_8[5]);
        }
      }
    }
    if (local_14 != 0) {
      while ((-1 < local_10 && (!bVar1))) {
        local_8 = (int *)FUN_006a8750(*(undefined4 *)(local_c + 0x20),local_10);
        if ((*(int *)(*(int *)(*(int *)(local_c + 0x40) + 0x60) + 0x40c + local_8[1] * 4) == -1) ||
           (*(int *)(local_c + 0x48 + local_8[1] * 4) <
            *(int *)(*(int *)(*(int *)(local_c + 0x40) + 0x60) + 0x40c + local_8[1] * 4))) {
          *(int *)(local_c + 0x48 + local_8[1] * 4) = *(int *)(local_c + 0x48 + local_8[1] * 4) + 1;
          iVar2 = (**(code **)(*local_8 + 0xc))(&local_18);
          if (iVar2 == 0) {
            FUN_0069d3c0(*(undefined4 *)(local_c + 0x28),local_8);
            FUN_006a89e0(local_8[5]);
            local_8[0xb] = 0;
            local_10 = local_10 + -1;
          }
          else {
            bVar1 = true;
            local_8[0xb] = 1;
          }
        }
        else {
          local_10 = local_10 + -1;
          if (local_8[5] != 0) {
            FUN_006a89e0(local_8[5]);
          }
        }
      }
    }
    *(int *)(local_c + 0x1c) = local_10;
    *(undefined4 *)(local_c + 8) = 1;
  }
  return;
}

