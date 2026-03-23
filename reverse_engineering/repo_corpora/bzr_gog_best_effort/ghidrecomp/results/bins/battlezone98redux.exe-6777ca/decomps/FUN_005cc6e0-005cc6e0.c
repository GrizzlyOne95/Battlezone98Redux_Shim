
void FUN_005cc6e0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  int local_2c;
  int local_28;
  undefined4 local_24;
  int local_20;
  undefined4 local_1c;
  void *local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c87c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_14 = FUN_00462630(param_1,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if ((local_14 != 0) && (local_20 = FUN_004ff060(param_2), local_20 != 0)) {
    iVar1 = (*(code *)**(undefined4 **)(local_14 + 0x18))();
    if (*(int *)(iVar1 + 0x14) == 0x434e5354) {
      uVar2 = FUN_00462490();
      FUN_0049cf90(param_3,uVar2);
    }
    FUN_00477ce0();
    local_44 = param_4;
    local_40 = 0x15;
    local_3c = 0;
    local_18 = operator_new(0x18);
    local_8 = 0;
    if (local_18 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      uVar2 = (**(code **)(*(int *)(local_14 + 0x18) + 0xc))(param_3);
      local_1c = FUN_00460490(uVar2,param_3);
    }
    local_24 = local_1c;
    local_8 = 0xffffffff;
    local_38 = local_1c;
    local_28 = local_20 >> 0x1f;
    local_2c = local_20;
    FUN_004dbaf0(&local_44);
  }
  ExceptionList = local_10;
  return;
}

