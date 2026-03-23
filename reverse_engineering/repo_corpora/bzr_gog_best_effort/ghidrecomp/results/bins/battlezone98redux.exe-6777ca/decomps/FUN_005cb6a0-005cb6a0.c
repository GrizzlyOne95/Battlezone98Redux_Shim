
void FUN_005cb6a0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  undefined4 uVar1;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  void *local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c7dc;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_14 = FUN_00462630(param_1,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (local_14 != 0) {
    FUN_00477ce0();
    local_40 = param_3;
    local_3c = param_2;
    local_38 = param_4;
    local_18 = operator_new(0x18);
    local_8 = 0;
    if (local_18 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      uVar1 = (**(code **)(*(int *)(local_14 + 0x18) + 0xc))(param_5);
      local_1c = FUN_00460490(uVar1,param_5);
    }
    local_20 = local_1c;
    local_8 = 0xffffffff;
    local_34 = local_1c;
    local_30 = param_6;
    local_28 = param_7;
    local_24 = param_8;
    FUN_004dbaf0(&local_40);
  }
  ExceptionList = local_10;
  return;
}

