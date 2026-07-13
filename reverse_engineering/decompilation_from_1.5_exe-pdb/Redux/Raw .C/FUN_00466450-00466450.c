
void FUN_00466450(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  undefined4 uVar1;
  undefined1 local_74 [4];
  undefined4 local_70;
  undefined4 *local_6c;
  undefined1 local_68 [4];
  int local_64;
  undefined4 *local_60;
  int local_5c;
  int local_58;
  void *local_54;
  int local_50;
  void *local_4c;
  int local_48;
  int local_44;
  undefined4 *local_40;
  undefined4 *local_3c;
  int local_38;
  undefined4 *local_34;
  int local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847468;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_2c = param_1;
  local_28 = 0x447a0000;
  local_24 = param_2;
  local_20 = param_3;
  local_1c = 0x447a0000;
  local_18 = param_4;
  FUN_0058fb40(param_5,param_6,local_14);
  local_34 = (undefined4 *)FUN_005903b0(&local_2c,&local_20);
  if ((local_34[4] & 1) == 0) {
    local_44 = FUN_0046b240();
    local_4c = operator_new(0x18);
    local_8 = 1;
    if (local_4c == (void *)0x0) {
      local_50 = 0;
    }
    else {
      local_50 = FUN_00460390(0,local_44);
    }
    local_64 = local_50;
    local_8 = 0xffffffff;
    local_48 = local_50;
    FID_conflict_begin(local_68);
    local_40 = *(undefined4 **)(local_48 + 8);
    for (local_38 = 0; local_38 < local_44; local_38 = local_38 + 1) {
      FUN_0046b290(local_74,0);
      local_60 = (undefined4 *)FUN_00421ec0();
      uVar1 = local_60[1];
      *local_40 = *local_60;
      local_40[1] = uVar1;
      local_40 = local_40 + 2;
    }
    FUN_00590b90(local_34);
  }
  else {
    local_6c = local_34;
    local_3c = local_34;
    if (local_34 == (undefined4 *)0x0) {
      local_70 = 0;
    }
    else {
      local_70 = (**(code **)*local_34)(1);
    }
    local_54 = operator_new(0x18);
    local_8 = 0;
    if (local_54 == (void *)0x0) {
      local_58 = 0;
    }
    else {
      local_58 = FUN_00460390(0,2);
    }
    local_5c = local_58;
    local_8 = 0xffffffff;
    local_30 = local_58;
    **(undefined4 **)(local_58 + 8) = param_1;
    *(undefined4 *)(*(int *)(local_58 + 8) + 4) = param_2;
    *(undefined4 *)(*(int *)(local_58 + 8) + 8) = param_3;
    *(undefined4 *)(*(int *)(local_58 + 8) + 0xc) = param_4;
    *(undefined4 *)(local_58 + 0x10) = 3;
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

