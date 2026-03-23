
void FUN_00452000(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_68 [4];
  undefined1 local_64 [4];
  undefined1 local_60 [4];
  undefined1 local_5c [8];
  int local_54;
  undefined4 local_50;
  int local_4c;
  undefined4 local_48;
  int *local_44;
  int local_40;
  undefined4 local_3c;
  int local_38;
  undefined4 local_34;
  undefined4 *local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int *local_1c;
  int *local_18;
  undefined4 *local_14;
  undefined4 *local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_20 = DAT_00915660;
  FUN_00430590();
  puVar2 = (undefined4 *)FUN_0044ea80(local_5c);
  local_8 = *puVar2;
  while( true ) {
    uVar3 = FUN_0044eaa0(local_60);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') break;
    iVar4 = FUN_0042da60();
    local_10 = *(undefined4 **)(iVar4 + 4);
    if (local_10 != (undefined4 *)local_10[0x36]) {
      local_30 = local_10;
      local_14 = local_10;
      if (local_10 == (undefined4 *)0x0) {
        local_34 = 0;
      }
      else {
        local_34 = (**(code **)*local_10)(1);
      }
    }
    FUN_0042da80();
  }
  local_38 = DAT_00915660;
  local_24 = DAT_00915660;
  if (DAT_00915660 == 0) {
    local_3c = 0;
  }
  else {
    local_3c = FUN_004521d0(1);
  }
  if (DAT_0091565c != 0) {
    local_40 = DAT_0091565c;
    operator_delete((void *)DAT_0091565c);
  }
  local_28 = DAT_00915658;
  FUN_00430590();
  puVar2 = (undefined4 *)FUN_0044ea80(local_64);
  local_c = *puVar2;
  while( true ) {
    uVar3 = FUN_0044eaa0(local_68);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') break;
    iVar4 = FUN_0042da60();
    local_18 = *(int **)(iVar4 + 4);
    if (local_18 != (int *)local_18[0x36]) {
      local_44 = local_18;
      local_1c = local_18;
      if (local_18 == (int *)0x0) {
        local_48 = 0;
      }
      else {
        local_48 = (**(code **)(*local_18 + 4))(1);
      }
    }
    FUN_0042da80();
  }
  local_4c = DAT_00915658;
  local_2c = DAT_00915658;
  if (DAT_00915658 == 0) {
    local_50 = 0;
  }
  else {
    local_50 = FUN_004521d0(1);
  }
  if (DAT_00915654 != 0) {
    local_54 = DAT_00915654;
    operator_delete((void *)DAT_00915654);
  }
  return;
}

