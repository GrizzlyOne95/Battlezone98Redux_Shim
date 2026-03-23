
void FUN_005cb9d0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined8 local_2c;
  undefined4 local_24;
  undefined4 local_20;
  void *local_1c;
  int local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c80c;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = FUN_00462630(param_1,uVar1);
  if ((local_14 != 0) && (local_18 = FUN_00462630(param_2,uVar1), local_18 != 0)) {
    FUN_00477ce0();
    local_44 = param_3;
    local_40 = 3;
    local_3c = param_2;
    local_1c = operator_new(0x18);
    local_8 = 0;
    if (local_1c == (void *)0x0) {
      local_20 = 0;
    }
    else {
      uVar2 = (**(code **)(*(int *)(local_18 + 0x18) + 0xc))();
      uVar3 = (**(code **)(*(int *)(local_14 + 0x18) + 0xc))(uVar2);
      local_20 = FUN_00460490(uVar3,uVar2);
    }
    local_24 = local_20;
    local_8 = 0xffffffff;
    local_38 = local_20;
    local_2c = 0;
    FUN_004dbaf0(&local_44);
  }
  ExceptionList = local_10;
  return;
}

